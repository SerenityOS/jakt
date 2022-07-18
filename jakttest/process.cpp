//
// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#include "process.h"
#include <Jakt/Assertions.h>
#include <signal.h>
#include <sys/wait.h>

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

ErrorOr<void> exec(Array<String> args)
{
    // this time I don't have to use dup_argv, since
    // none of the arguments will be deallocated if
    // the process can be executed(because execvp gets in the way)
    // We'll just allocate an array of pointers to `args`, plus the NULL pointer.
    auto const argv_byte_size = (Checked<size_t>(args.size()) + Checked<size_t>(1)) * Checked<size_t>(sizeof(char*));
    if (argv_byte_size.has_overflow()) {
        return Error::from_errno(EOVERFLOW);
    }

    // SAFE: since `execvp` expects `char * const *`, we have to fill the argv
    // array with pointers.
    auto argv = reinterpret_cast<char**>(malloc(argv_byte_size.value_unchecked()));
    if (argv == NULL) {
        return Error::from_errno(ENOMEM);
    }

    for (size_t i = 0; i != args.size(); ++i) {
        // SAFETY: const_cast is safe:
        // If execvp() succeeds it doesn't return, and the argument strings
        // can't be modified by us; ownership of this memory has been
        // transferred to the executed program. Which means that we can cast
        // them to `char *`; the memory is not touched by whoever passed args
        // anymore (we're not returning control).
        //
        // If it doesn't, these pointers in `argv` become invalid, because the
        // memory continues to be owned by whoever passed the references to the
        // strings. These now invalid pointers are not used by this function (or
        // future paths) once they're invalid; in fact; the memory of `argv` is
        // released.
        argv[i] = const_cast<char*>(args[i].c_string());
    }
    argv[args.size()] = NULL;

    if (::execvp(argv[0], argv) == -1) {
        // do not touch again this array. Its pointers are invalid (see safety
        // comment above `const_cast`).
        free(argv);
        return Error::from_errno(errno);
    }

    VERIFY_NOT_REACHED();
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

ErrorOr<Optional<i32>> poll_process_exit(i32 pid)
{
    i32 wstatus;
    auto const result = waitpid(pid, &wstatus, WNOHANG);
    if (result == -1) {
        return Error::from_errno(errno);
    }
    // not exited.
    if (result == 0) {
        return JaktInternal::NullOptional {};
    }
    // NOTE: compiler seems to struggle to find a constructor when
    // nesting error & optional
    return Optional<i32>(WEXITSTATUS(wstatus));
}

ErrorOr<void> forcefully_kill_process(i32 pid)
{
    if (kill(pid, SIGKILL) < 0) {
        return Error::from_errno(errno);
    }
    return ErrorOr<void> {};
}

}
