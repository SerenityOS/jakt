//
// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#pragma once
#include <Builtins/Array.h>
#include <Jakt/Error.h>
#include <Jakt/String.h>

namespace Jakt::process {
// NOTE: I need a class declaration with getters because that's the only way to
// make Jakt not re-declare the structure (using extern struct)
class ExitPollResult {
    i32 m_exit_code;
    i32 m_pid;

public:
    constexpr ExitPollResult(i32 exit_code, i32 pid)
        : m_pid(pid)
        , m_exit_code(exit_code)
    {
    }

    i32 exit_code() const { return m_exit_code; }
    i32 pid() const { return m_pid; }
};
ErrorOr<i32> start_background_process(Array<String> args);
ErrorOr<Optional<ExitPollResult>> poll_process_exit(i32 pid);
ErrorOr<void> forcefully_kill_process(i32 pid);
ErrorOr<void> exec(Array<String> args);
ErrorOr<i32> fork();
}
