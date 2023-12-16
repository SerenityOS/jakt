//
// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
// Copyright (c) 2022, Andrew Kaster <akaster@serenityos.org>
//
// SPDX-License-Identifier: BSD-2-Clause
#include "process.h"

#include <AK/Assertions.h>
#include <AK/HashMap.h>
#include <AK/RefPtr.h>
#include <Jakt/ByteString.h>
#include <time.h>
#ifndef _WIN32
#include <signal.h>
#include <sys/wait.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <system_error>
#include <processthreadsapi.h>
#endif

namespace Jakt::process {

#ifndef _WIN32
// Allocates & fills one array, which contains:
// - the argv array with all the pointers into later offsets of the array, at the front
// - the string arguments that follow the last argv NULL pointer, terminated by zeroes.
static ErrorOr<char**> dup_argv(DynamicArray<ByteString> args)
{

    // 1. Calculate the total size  of all the pointers + all the strings, accounting
    // for the last NULL pointer and each argument's NUL terminator.
    auto const argv_size = Checked(args.size()) + Checked<size_t>(1ul);
    auto const argv_malloc_size = argv_size * Checked(sizeof(char*));
    // ensure argv malloc size has no overflow because we're going to use it
    // as the offset for the start of the string array.
    if (argv_malloc_size.has_overflow()) {
        return Error::from_errno(EOVERFLOW);
    }

    // join all the strings in one allocation
    auto total_string_size = Checked<size_t>(0);
    for (size_t i = 0; i != args.size(); ++i) {
        total_string_size += args[i].length();
    }
    total_string_size += args.size();

    auto const total_allocation_size = argv_malloc_size + total_string_size;
    if (total_allocation_size.has_overflow()) {
        return Error::from_errno(EOVERFLOW);
    }

    // 2. Allocate the full array
    auto const full_array = malloc(total_allocation_size.value_unchecked());
    if (!full_array) {
        return Error::from_errno(ENOMEM);
    }

    // 3. Fill all strings & argv offsets.
    // NOTE: argv *is* the start of the allocation, so any free()s to this data structure must point to `argv`.
    auto const argv = reinterpret_cast<char**>(full_array);

    {
        char* arg = reinterpret_cast<char*>(full_array) + argv_malloc_size.value_unchecked();
        for (u64 i = 0; i != args.size(); ++i) {
            // copy the string
            memcpy(arg, args[i].characters(), args[i].length());
            arg[args[i].length()] = 0;
            // set the argument pointer
            argv[i] = arg;
            // add the offset
            arg += args[i].length() + 1;
        }
        argv[args.size()] = NULL;
    }

    return argv;
}

ErrorOr<i32> start_background_process(DynamicArray<ByteString> args)
{
    // We have to fully duplicate argv because execvp wants
    // *modifiable* arguments (char* const*)
    auto const argv = TRY(dup_argv(args));
    auto const pid = fork();
    if (pid == -1) {
        return Error::from_errno(errno);
    }
    if (pid == 0) {
        // child process, execute the command
        execvp(argv[0], argv);
    }

    // Allocated memory got dup'd, so we'll free the parent side.
    // NOTE: See point 3 on dup_argv
    free(argv);

    return pid;
}

ErrorOr<Optional<ExitPollResult>> poll_process_exit(i32 pid)
{
    i32 wstatus;
    auto const result = waitpid(pid, &wstatus, WNOHANG);
    if (result == -1) {
        // no children
        if (errno == ECHILD) {
            return JaktInternal::OptionalNone {};
        }
        return Error::from_errno(errno);
    }


    // not exited.
    if (result == 0) {
        return JaktInternal::OptionalNone {};
    }
    // NOTE: compiler seems to struggle to find a constructor when
    // nesting error & optional
    return Optional<ExitPollResult>(ExitPollResult { WEXITSTATUS(wstatus), result });
}

ErrorOr<void> forcefully_kill_process(i32 pid)
{
    if (kill(pid, SIGKILL) < 0) {
        return Error::from_errno(errno);
    }
    return ErrorOr<void> {};
}
#else

static ErrorOr<ByteString> join(DynamicArray<ByteString> const strings, const ByteString separator)
{
    ByteString output = ByteString(""sv);
    size_t i = 0;
    ArrayIterator<ByteString> it = strings.iterator();
    for (;;) {
        Optional<ByteString> maybe_next = it.next();
        if (!maybe_next.has_value())
            break;
        output += maybe_next.release_value();
        if (i < strings.size() - 1) {
            output += separator;
        }
        ++i;
    }
    return output;
}

static int last_error_to_errno(DWORD error)
{
    // Shh, there's no ::std here
    return ::std::system_category().default_error_condition(error).value();
}

// FIXME: encapsulate this data and these methods into a singleton or something
static HashMap<i32, PROCESS_INFORMATION> s_process_handles;
static i32 s_next_process_handle = 0;

ErrorOr<i32> start_background_process(DynamicArray<ByteString> args)
{
    STARTUPINFO si = {};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {};

    ByteString command_line_str = TRY(join(args, ByteString(" "sv)));

    char command_line[4096] = {};
    strncpy(command_line, command_line_str.characters(), min(sizeof(command_line) - 1, command_line_str.length()));

    if (!CreateProcess(nullptr, command_line, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi))
        return Error::from_errno(last_error_to_errno(GetLastError()));

    i32 pid = ++s_next_process_handle;
    (void)TRY(s_process_handles.try_set(pid, move(pi)));

    return pid;
}

static ErrorOr<Optional<DWORD>> get_process_status(PROCESS_INFORMATION process)
{
    DWORD exit_code = STILL_ACTIVE;
    if (!GetExitCodeProcess(process.hProcess, &exit_code))
        return Error::from_errno(last_error_to_errno(GetLastError()));
    if (exit_code == STILL_ACTIVE)
        return Optional<DWORD> {};

    CloseHandle(process.hProcess);
    CloseHandle(process.hThread);

    return Optional<DWORD> { exit_code };
}


static ErrorOr<Optional<ExitPollResult>> poll_any_process(DWORD timeout = 0)
{
    if (s_process_handles.is_empty())
        return Optional<ExitPollResult> {};

    // FIXME: Can we use RegisterWaitForSingleObject here?
    // Barring that, can probably bookeep this array along with the other static lists
    auto handles = TRY(DynamicArray<HANDLE>::create_empty());
    TRY(handles.ensure_capacity(s_process_handles.size()));

    for (auto const& element : s_process_handles)
        MUST(handles.push(element.value.hProcess));

    DWORD ret = WaitForMultipleObjects(handles.size(), handles.unsafe_data(), FALSE, timeout);
    if (ret == WAIT_FAILED)
        return Error::from_errno(last_error_to_errno(GetLastError()));
    if (ret == WAIT_TIMEOUT)
        return Optional<ExitPollResult> {};

    VERIFY(ret >= WAIT_OBJECT_0);

    size_t index = ret - WAIT_OBJECT_0;

    auto bucket = find_if(s_process_handles.begin(), s_process_handles.end(), [&](auto& element) { return element.value.hProcess == handles[index]; });
    VERIFY(bucket != s_process_handles.end());

    auto maybe_exit_code = TRY(get_process_status(bucket->value));
    if (!maybe_exit_code.has_value())
        return Optional<ExitPollResult> {};

    auto pid = bucket->key;
    auto removed = s_process_handles.remove(bucket->key);
    VERIFY(removed);
    return ExitPollResult { static_cast<i32>(maybe_exit_code.value()), pid };
}

ErrorOr<Optional<ExitPollResult>> poll_process_exit(i32 pid)
{
    if (pid == -1) {
        DWORD timeout_ms = 10000; // 10 seconds
        return poll_any_process(timeout_ms);
    }

    auto maybe_process = s_process_handles.get(pid);
    if (!maybe_process.has_value())
        return Error::from_errno(ESRCH);

    PROCESS_INFORMATION process_handle = maybe_process.release_value();

    DWORD ret = WaitForSingleObject(process_handle.hProcess, 0);
    if (ret == WAIT_FAILED)
        return Error::from_errno(last_error_to_errno(GetLastError()));
    if (ret == WAIT_TIMEOUT)
        return Optional<ExitPollResult> {};

    VERIFY(ret == WAIT_OBJECT_0);

    auto maybe_exit_code = TRY(get_process_status(process_handle));
    if (!maybe_exit_code.has_value())
        return Optional<ExitPollResult> {};

    auto removed = s_process_handles.remove(pid);
    VERIFY(removed);
    return ExitPollResult { static_cast<i32>(maybe_exit_code.value()), pid };
}

ErrorOr<void> forcefully_kill_process(i32 pid)
{
    auto it = s_process_handles.find(pid);
    if (it == s_process_handles.end())
        return Error::from_errno(ESRCH);

    PROCESS_INFORMATION process_handle = it->value;

    if (!TerminateProcess(process_handle.hProcess, 1))
        return Error::from_errno(last_error_to_errno(GetLastError()));

    constexpr DWORD timeout_ms = 1000;
    (void)WaitForSingleObject(process_handle.hProcess, timeout_ms);

    CloseHandle(process_handle.hProcess);
    CloseHandle(process_handle.hThread);

    auto removed = s_process_handles.remove(pid);
    VERIFY(removed);
    return {};
}
#endif

}
