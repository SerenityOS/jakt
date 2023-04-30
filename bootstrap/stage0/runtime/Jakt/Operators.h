/*
 * Copyright (c) 2023, Ali Mohammad Pur <mpfard@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Jakt/AKIntegration.h>

namespace JaktInternal {

template<typename T, typename U>
bool less_than(T const& a, U const& b) { return a < b; }

template<typename T, typename U>
bool greater_than(T const& a, U const& b) { return a > b; }

template<typename T, typename U>
bool less_than_or_equal(T const& a, U const& b) { return a <= b; }

template<typename T, typename U>
bool greater_than_or_equal(T const& a, U const& b) { return a >= b; }

template<typename T, typename U>
bool equal(T const& a, U const& b) { return a == b; }

template<typename T, typename U>
bool not_equal(T const& a, U const& b) { return a != b; }

template<typename T, typename U>
u8 compare(T const& a, U const& b) {
    // NOTE: Keep in sync with enum Ordering in operators.jakt
    enum Ordering : u8 {
        Less = 0,
        Equal = 1,
        Greater = 2,
    };

    if (a < b)
        return Ordering::Less;

    if (a > b)
        return Ordering::Greater;

    return Ordering::Equal;
}

}
