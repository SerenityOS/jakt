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
#include <Jakt/ByteStringBuilder.h>

namespace Jakt {

ByteStringBuilder ByteStringBuilder::create()
{
    return ByteStringBuilder {};
}

inline void ByteStringBuilder::will_append(size_t size)
{
    if (!m_buffer.has_value()) {
        m_buffer = DynamicArray<u8>::create_empty();
    }
    m_buffer->add_capacity(size);
}

ByteStringBuilder::ByteStringBuilder() = default;

void ByteStringBuilder::append(StringView string)
{
    if (string.is_empty())
        return;
    will_append(string.length());
    m_buffer->push_values((u8 const*)string.characters_without_null_termination(), string.length());
}

void ByteStringBuilder::append(char ch)
{
    will_append(1);
    m_buffer->push(ch);
}

void ByteStringBuilder::append(char const* characters, size_t length)
{
    return append(StringView { characters, length });
}

ByteString ByteStringBuilder::to_string() const
{
    if (is_empty())
        return ByteString::empty();
    return ByteString(string_view());
}

StringView ByteStringBuilder::string_view() const
{
    return StringView { data(), length() };
}

void ByteStringBuilder::clear()
{
    m_buffer = {};
}

void ByteStringBuilder::append_code_point(u32 code_point)
{
    auto nwritten = Jakt::UnicodeUtils::code_point_to_utf8(code_point, [this](char c) {
        append(c);
    });

    if (nwritten < 0) {
        append(0xef);
        append(0xbf);
        append(0xbd);
    }
}

void ByteStringBuilder::append_escaped_for_json(StringView string)
{
    for (auto ch : string) {
        switch (ch) {
        case '\b':
            append("\\b"sv);
            break;
        case '\n':
            append("\\n"sv);
            break;
        case '\t':
            append("\\t"sv);
            break;
        case '\"':
            append("\\\""sv);
            break;
        case '\\':
            append("\\\\"sv);
            break;
        default:
            if (ch >= 0 && ch <= 0x1f)
                appendff("\\u{:04x}", ch);
            else
                append(ch);
        }
    }
}

}
