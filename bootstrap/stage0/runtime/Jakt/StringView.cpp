/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Jakt/Find.h>
#include <Jakt/Function.h>
#include <Jakt/Memory.h>
#include <Jakt/StringView.h>

#ifndef KERNEL
#    include <Jakt/String.h>
#endif

namespace Jakt {

StringView::StringView(String const& string)
    : m_characters(string.c_string())
    , m_length(string.length())
{
}

bool StringView::starts_with(char ch) const
{
    if (is_empty())
        return false;
    return ch == characters_without_null_termination()[0];
}

bool StringView::starts_with(StringView str, CaseSensitivity case_sensitivity) const
{
    return StringUtils::starts_with(*this, str, case_sensitivity);
}

bool StringView::ends_with(char ch) const
{
    if (is_empty())
        return false;
    return ch == characters_without_null_termination()[length() - 1];
}

bool StringView::ends_with(StringView str, CaseSensitivity case_sensitivity) const
{
    return StringUtils::ends_with(*this, str, case_sensitivity);
}

bool StringView::contains(char needle) const
{
    for (char current : *this) {
        if (current == needle)
            return true;
    }
    return false;
}

bool StringView::contains(StringView needle, CaseSensitivity case_sensitivity) const
{
    return StringUtils::contains(*this, needle, case_sensitivity);
}

bool StringView::equals_ignoring_case(StringView other) const
{
    return StringUtils::equals_ignoring_case(*this, other);
}

template<typename T>
Optional<T> StringView::to_int() const
{
    return StringUtils::convert_to_int<T>(*this);
}

template Optional<i8> StringView::to_int() const;
template Optional<i16> StringView::to_int() const;
template Optional<i32> StringView::to_int() const;
template Optional<long> StringView::to_int() const;
template Optional<long long> StringView::to_int() const;

template<typename T>
Optional<T> StringView::to_uint() const
{
    return StringUtils::convert_to_uint<T>(*this);
}

template Optional<u8> StringView::to_uint() const;
template Optional<u16> StringView::to_uint() const;
template Optional<u32> StringView::to_uint() const;
template Optional<unsigned long> StringView::to_uint() const;
template Optional<unsigned long long> StringView::to_uint() const;
template Optional<long> StringView::to_uint() const;
template Optional<long long> StringView::to_uint() const;

bool StringView::operator==(String const& string) const
{
    return *this == string.view();
}

ErrorOr<String> StringView::to_string() const { return String::copy(*this); }

ErrorOr<Array<size_t>> StringView::find_all(StringView needle) const
{
    return StringUtils::find_all(*this, needle);
}

}
