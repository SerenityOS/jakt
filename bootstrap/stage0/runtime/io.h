/*
 * Copyright (c) 2022, Andrew Kaster <akaster@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

// This file is a workaround for missing os-detection logic for extern "C" imports in jakt
// On Win32, we want the header, on Unix-like OS's we don't.
// See #1015
#ifdef _WIN32
#    include_next <io.h>
#endif
