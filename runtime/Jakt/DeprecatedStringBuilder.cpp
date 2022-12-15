/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Builtins/DynamicArray.h>

#include <AK/Checked.h>
#include <AK/StdLibExtras.h>
#include <AK/StringView.h>
#include <AK/UnicodeUtils.h>
#include <Jakt/DeprecatedStringBuilder.h>

namespace Jakt {

inline ErrorOr<void> DeprecatedStringBuilder::will_append(size_t size)
{
    TRY(m_buffer.add_capacity(size));
    return {};
}

DeprecatedStringBuilder::DeprecatedStringBuilder(DynamicArray<u8> buffer)
    : m_buffer(buffer)
{
}

ErrorOr<void> DeprecatedStringBuilder::append(StringView string)
{
    if (string.is_empty())
        return {};
    TRY(will_append(string.length()));
    TRY(m_buffer.push_values((u8 const*)string.characters_without_null_termination(), string.length()));
    return {};
}

ErrorOr<void> DeprecatedStringBuilder::append(char ch)
{
    TRY(will_append(1));
    TRY(m_buffer.push(ch));
    return {};
}

ErrorOr<void> DeprecatedStringBuilder::append(char const* characters, size_t length)
{
    return append(StringView { characters, length });
}
ErrorOr<DeprecatedString> DeprecatedStringBuilder::to_string() const
{
    if (is_empty())
        return DeprecatedString::empty();
    return DeprecatedString(string_view());
}

StringView DeprecatedStringBuilder::string_view() const
{
    return StringView { data(), m_buffer.size() };
}

void DeprecatedStringBuilder::clear()
{
    static_cast<void>(m_buffer.resize(0));
}

ErrorOr<void> DeprecatedStringBuilder::append_code_point(u32 code_point)
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

ErrorOr<void> DeprecatedStringBuilder::append_escaped_for_json(StringView string)
{
    for (auto ch : string) {
        switch (ch) {
        case '\b':
            TRY(append("\\b"sv));
            break;
        case '\n':
            TRY(append("\\n"sv));
            break;
        case '\t':
            TRY(append("\\t"sv));
            break;
        case '\"':
            TRY(append("\\\""sv));
            break;
        case '\\':
            TRY(append("\\\\"sv));
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
