/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Jakt/Checked.h>
#include <Jakt/StdLibExtras.h>
#include <Jakt/StringBuilder.h>
#include <Jakt/StringView.h>
#include <Jakt/UnicodeUtils.h>

namespace Jakt {

inline ErrorOr<void> StringBuilder::will_append(size_t size)
{
    TRY(m_buffer.add_capacity(size));
    return {};
}

StringBuilder::StringBuilder(Array<u8> buffer)
    : m_buffer(buffer)
{
}

ErrorOr<void> StringBuilder::append(StringView string)
{
    if (string.is_empty())
        return {};
    TRY(will_append(string.length()));
    TRY(m_buffer.push_values((u8 const*)string.characters_without_null_termination(), string.length()));
    return {};
}

ErrorOr<void> StringBuilder::append(char ch)
{
    TRY(will_append(1));
    TRY(m_buffer.push(ch));
    return {};
}

ErrorOr<void> StringBuilder::append(char const* characters, size_t length)
{
    return append(StringView { characters, length });
}
ErrorOr<String> StringBuilder::to_string() const
{
    if (is_empty())
        return String::empty();
    return String::copy(string_view());
}

StringView StringBuilder::string_view() const
{
    return StringView { data(), m_buffer.size() };
}

void StringBuilder::clear()
{
    static_cast<void>(m_buffer.resize(0));
}

ErrorOr<void> StringBuilder::append_code_point(u32 code_point)
{
    ErrorOr<void> error_from_code_point = {};
    auto nwritten = Jakt::UnicodeUtils::code_point_to_utf8(code_point, [this, &error_from_code_point](char c) {
        auto maybe_error = append(c);
        if (maybe_error.is_error())
            error_from_code_point = maybe_error;
    });
    if (error_from_code_point.is_error())
        return error_from_code_point.release_error();
    if (nwritten < 0) {
        TRY(append(0xef));
        TRY(append(0xbf));
        TRY(append(0xbd));
    }
    return {};
}

ErrorOr<void> StringBuilder::append_escaped_for_json(StringView string)
{
    for (auto ch : string) {
        switch (ch) {
        case '\b':
            TRY(append("\\b"));
            break;
        case '\n':
            TRY(append("\\n"));
            break;
        case '\t':
            TRY(append("\\t"));
            break;
        case '\"':
            TRY(append("\\\""));
            break;
        case '\\':
            TRY(append("\\\\"));
            break;
        default:
            if (ch >= 0 && ch <= 0x1f)
                TRY(appendff("\\u{:04x}", ch));
            else
                TRY(append(ch));
        }
    }
    return {};
}

}
