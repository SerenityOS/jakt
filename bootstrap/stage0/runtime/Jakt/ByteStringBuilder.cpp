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

inline ErrorOr<void> ByteStringBuilder::will_append(size_t size)
{
    if (!m_buffer.has_value()) {
        m_buffer = TRY(DynamicArray<u8>::create_empty());
    }
    TRY(m_buffer->add_capacity(size));
    return {};
}

ByteStringBuilder::ByteStringBuilder() = default;

ErrorOr<void> ByteStringBuilder::append(StringView string)
{
    if (string.is_empty())
        return {};
    TRY(will_append(string.length()));
    TRY(m_buffer->push_values((u8 const*)string.characters_without_null_termination(), string.length()));
    return {};
}

ErrorOr<void> ByteStringBuilder::append(char ch)
{
    TRY(will_append(1));
    TRY(m_buffer->push(ch));
    return {};
}

ErrorOr<void> ByteStringBuilder::append(char const* characters, size_t length)
{
    return append(StringView { characters, length });
}
ErrorOr<ByteString> ByteStringBuilder::to_string() const
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

ErrorOr<void> ByteStringBuilder::append_code_point(u32 code_point)
{
    auto nwritten = TRY(Jakt::UnicodeUtils::try_code_point_to_utf8(code_point, [this](char c) -> ErrorOr<void> {
        TRY(append(c));
        return {};
    }));

    if (nwritten < 0) {
        TRY(append(0xef));
        TRY(append(0xbf));
        TRY(append(0xbd));
    }

    return {};
}

ErrorOr<void> ByteStringBuilder::append_escaped_for_json(StringView string)
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
