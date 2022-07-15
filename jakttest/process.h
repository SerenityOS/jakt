//
// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#include <Builtins/Array.h>
#include <Jakt/Error.h>
#include <Jakt/String.h>

namespace Jakt::process {
ErrorOr<i32> start_background_process(Array<String> args);
ErrorOr<Optional<i32>> poll_process_exit(i32 pid);
ErrorOr<void> forcefully_kill_process(i32 pid);
}
