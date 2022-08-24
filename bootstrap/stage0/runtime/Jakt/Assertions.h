/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#if defined(KERNEL)
#    include <Kernel/Assertions.h>
#else
#    include <assert.h>
#    define _TRAP_NORETURN(expr)       \
        []() __attribute__((noreturn)) \
        {                              \
            assert(false && #expr);    \
            __builtin_trap();          \
            __builtin_unreachable();   \
        }                              \
        ()
#    define VERIFY(expr) (__builtin_expect(!(expr), 0) ? _TRAP_NORETURN(expr) : (void)0)
#    define VERIFY_NOT_REACHED() VERIFY(false) /* NOLINT(cert-dcl03-c,misc-static-assert) No, this can't be static_assert, it's a runtime check */
namespace Jakt {
static constexpr bool TODO = false;
}
#    define TODO() VERIFY(Jakt::TODO)          /* NOLINT(cert-dcl03-c,misc-static-assert) No, this can't be static_assert, it's a runtime check */
#endif
