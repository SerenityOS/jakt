// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#pragma once

#include <Jakt/AKIntegration.h>

#include <AK/Types.h>
#include <AK/Error.h>

namespace Jakt::os {
    ErrorOr<size_t> get_num_cpus();
    ErrorOr<ByteString> get_system_temporary_directory();
    ErrorOr<void> ignore_sigchild();
    ErrorOr<ByteString> get_script_execution_string();
}
