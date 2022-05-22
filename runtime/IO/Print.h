/*
 * Copyright (c) 2022, Ali Mohammad Pur <mpfard@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Format.h>
#include <AK/Tuple.h>

namespace JaktInternal {

template<SpecializationOf<Tuple> T>
void println(String format, T values)
{
    values.apply_as_args([&](auto... values) {
        outln(format, values...);
    });
}

template<SpecializationOf<Tuple> T>
void print(String format, T values)
{
    values.apply_as_args([&](auto... values) {
        out(format, values...);
    });
}

template<SpecializationOf<Tuple> T>
void eprintln(String format, T values)
{
    values.apply_as_args([&](auto... values) {
        warnln(format, values...);
    });
}

}

using JaktInternal::eprintln;
using JaktInternal::print;
using JaktInternal::println;
