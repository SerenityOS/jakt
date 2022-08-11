// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#pragma once
#include <Jakt/Error.h>
#include <Jakt/Types.h>

namespace Jakt::os {
ErrorOr<size_t> get_num_cpus();
ErrorOr<String> get_system_temporary_directory();
ErrorOr<Optional<size_t>> read_nonblocking(i32 fd, u8* buffer, size_t max_len);
ErrorOr<Optional<size_t>> write_nonblocking(i32 fd, u8 const* buffer, size_t max_len);
ErrorOr<void> close(i32 fd);
struct RawPipe {
    i32 read_end;
    i32 write_end;
};
ErrorOr<RawPipe> pipe_nonblocking();
ErrorOr<void> dup2(i32 old, i32 replace_with);
}
