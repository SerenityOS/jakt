// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#include "os.h"
#include <Jakt/String.h>
// FIXME:  StringBuilder fails to compile because
// adopt_nonnull_ref_or_enomem isn't included.
#include <Jakt/RefPtr.h>
#include <Jakt/StringBuilder.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

namespace Jakt::os {
ErrorOr<size_t> get_num_cpus()
{
    long result = sysconf(_SC_NPROCESSORS_ONLN);
    if (result == -1)
        return Error::from_errno(errno);
    return static_cast<size_t>(result);
}

ErrorOr<String> get_system_temporary_directory()
{
    auto builder = TRY(StringBuilder::create());
#ifdef __WIN32
    TRY(builder.append_c_string(getenv("TEMP")));
#else
    auto const result = getenv("TMP_DIR");
    TRY(builder.append_c_string(result == NULL ? "/tmp" : result));
#endif
    return TRY(builder.to_string());
}

ErrorOr<Optional<size_t>> read_nonblocking(i32 fd, u8* buffer, size_t max_len)
{
    auto const ret = ::read(fd, buffer, max_len);
    if (ret == -1) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            return JaktInternal::NullOptional {};
        } else {
            return Error::from_errno(errno);
        }
    }
    return Optional<size_t>(static_cast<size_t>(ret));
}

ErrorOr<Optional<size_t>> write_nonblocking(i32 fd, u8 const* buffer, size_t max_len)
{
    auto const ret = ::write(fd, buffer, max_len);
    if (ret == -1) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            return JaktInternal::NullOptional {};
        } else {
            return Error::from_errno(errno);
        }
    }
    return Optional<size_t>(static_cast<size_t>(ret));
}
ErrorOr<void> close(i32 fd)
{
    if (::close(fd) == -1) {
        return Error::from_errno(errno);
    }
    return ErrorOr<void> {};
}
ErrorOr<RawPipe> pipe_nonblocking()
{
    i32 pipefds[2];
    if (::pipe(&pipefds[0]) == -1) {
        return Error::from_errno(errno);
    }
    auto const pipe = RawPipe { pipefds[0], pipefds[1] };
    auto const read_end_flags = ::fcntl(pipe.read_end, F_GETFL);
    auto const write_end_flags = ::fcntl(pipe.write_end, F_GETFL);

    if (read_end_flags == -1 || write_end_flags == -1) {
        return Error::from_errno(errno);
    }

    if (::fcntl(pipe.read_end, F_SETFL, read_end_flags | O_NONBLOCK) == -1 || ::fcntl(pipe.write_end, F_SETFL, write_end_flags | O_NONBLOCK) == -1) {
        return Error::from_errno(errno);
    }
    return pipe;
}

ErrorOr<void> dup2(i32 old, i32 replace_with)
{
    if (::dup2(old, replace_with) == -1)
        return Error::from_errno(errno);
    return ErrorOr<void> {};
}
}
