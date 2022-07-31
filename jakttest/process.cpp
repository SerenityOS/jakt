//
// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#include "process.h"
#include <Jakt/Assertions.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

namespace Jakt::process {
// Allocates & fills one array, which contains:
// - the argv array with all the pointers into later offsets of the array, at the front
// - the string arguments that follow the last argv NULL pointer, terminated by zeroes.
static ErrorOr<char**> dup_argv(Array<String> args)
{

    // 1. Calculate the total size  of all the pointers + all the strings, accounting
    // for the last NULL pointer and each argument's NUL terminator.
    auto const argv_size = Checked(args.size()) + Checked(1ul);
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
            memcpy(arg, args[i].c_string(), args[i].length());
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

ErrorOr<i32> start_background_process(Array<String> args)
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
            return JaktInternal::NullOptional {};
        }
        return Error::from_errno(errno);
    }
    // not exited.
    if (result == 0) {
        return JaktInternal::NullOptional {};
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
}
