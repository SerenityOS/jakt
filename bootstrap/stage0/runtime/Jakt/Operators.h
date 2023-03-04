/*
 * Copyright (c) 2023, Ali Mohammad Pur <mpfard@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Jakt/AKIntegration.h>
#include <AK/String.h>

namespace JaktInternal::Operators {

template<Integral T>
T add(T a, T b)
{
    return a + b;
}

inline ErrorOr<DeprecatedString> add(DeprecatedString const& a, DeprecatedString const& b)
{
    return DeprecatedString::formatted("{}{}", a, b);
}

}
