// Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause
#include "os.h"
#include <Jakt/String.h>
// FIXME:  StringBuilder fails to compile because
// adopt_nonnull_ref_or_enomem isn't included.
#include <Jakt/RefPtr.h>
#include <Jakt/StringBuilder.h>
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
}
