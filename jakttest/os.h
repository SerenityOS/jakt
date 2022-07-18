// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#pragma once
#include <Jakt/Types.h>
#include <Jakt/Error.h>

namespace Jakt::os {
    ErrorOr<size_t> get_num_cpus();
    ErrorOr<String> get_system_temporary_directory();
}
