// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
// Copyright (c) 2022, Andrew Kaster <akaster@serenityos.org>
//
// SPDX-License-Identifier: BSD-2-Clause
#include "os.h"

#include <AK/ByteString.h>
// FIXME:  StringBuilder fails to compile because
// adopt_nonnull_ref_or_enomem isn't included.
#include <AK/RefPtr.h>
#include <Jakt/ByteStringBuilder.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#include <signal.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sysinfoapi.h>
#include <direct.h>
#endif

namespace Jakt::os {
#ifndef _WIN32
ErrorOr<size_t> get_num_cpus()
{
    long result = sysconf(_SC_NPROCESSORS_ONLN);
    if (result == -1)
        return Error::from_errno(errno);
    return static_cast<size_t>(result);
}

ErrorOr<ByteString> get_system_temporary_directory()
{
    auto builder = ByteStringBuilder::create();
    auto const result = getenv("TMP_DIR");
    TRY(builder.append_c_string(result ?: "/tmp"));
    return TRY(builder.to_string());
}
ErrorOr<void> ignore_sigchild()
{
    struct sigaction action { };
    action.sa_handler = [](int) {};
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask, SIGCHLD);
    action.sa_flags = SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &action, NULL) == -1)
        return Error::from_errno(errno);
    return {};
}

ErrorOr<ByteString> get_script_execution_string()
{
    return ByteString("python3"sv);
}
#else
ErrorOr<size_t> get_num_cpus()
{
    SYSTEM_INFO sys_info = {};
    GetSystemInfo(&sys_info);
    return sys_info.dwNumberOfProcessors;
}

ErrorOr<ByteString> get_system_temporary_directory()
{
    auto builder = ByteStringBuilder::create();
    TRY(builder.append_c_string(getenv("TEMP")));
    return TRY(builder.to_string());
}

ErrorOr<void> ignore_sigchild()
{
    return {};
}

ErrorOr<ByteString> get_script_execution_string()
{
    return ByteString("python3.exe"sv);
}
#endif
}
