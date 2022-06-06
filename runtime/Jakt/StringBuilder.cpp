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

ErrorOr<void> StringBuilder::try_append(StringView string)
{
    if (string.is_empty())
        return {};
    TRY(will_append(string.length()));
    TRY(m_buffer.push_values((u8 const*)string.characters_without_null_termination(), string.length()));
    return {};
}

ErrorOr<void> StringBuilder::try_append(char ch)
{
    TRY(will_append(1));
    TRY(m_buffer.push(ch));
    return {};
}

void StringBuilder::append(StringView string)
{
    MUST(try_append(string));
}

ErrorOr<void> StringBuilder::try_append(char const* characters, size_t length)
{
    return try_append(StringView { characters, length });
}

void StringBuilder::append(char const* characters, size_t length)
{
    MUST(try_append(characters, length));
}

void StringBuilder::append(char ch)
{
    MUST(try_append(ch));
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

ErrorOr<void> StringBuilder::try_append_code_point(u32 code_point)
{
    auto nwritten = Jakt::UnicodeUtils::code_point_to_utf8(code_point, [this](char c) { append(c); });
    if (nwritten < 0) {
        TRY(try_append(0xef));
        TRY(try_append(0xbf));
        TRY(try_append(0xbd));
    }
    return {};
}

void StringBuilder::append_code_point(u32 code_point)
{
    MUST(try_append_code_point(code_point));
}

void StringBuilder::append_as_lowercase(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        append(ch + 0x20);
    else
        append(ch);
}

void StringBuilder::append_escaped_for_json(StringView string)
{
    MUST(try_append_escaped_for_json(string));
}

ErrorOr<void> StringBuilder::try_append_escaped_for_json(StringView string)
{
    for (auto ch : string) {
        switch (ch) {
        case '\b':
            TRY(try_append("\\b"));
            break;
        case '\n':
            TRY(try_append("\\n"));
            break;
        case '\t':
            TRY(try_append("\\t"));
            break;
        case '\"':
            TRY(try_append("\\\""));
            break;
        case '\\':
            TRY(try_append("\\\\"));
            break;
        default:
            if (ch >= 0 && ch <= 0x1f)
                TRY(try_appendff("\\u{:04x}", ch));
            else
                TRY(try_append(ch));
        }
    }
    return {};
}

}
