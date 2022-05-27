/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Format.h>
#include <AK/Forward.h>
#include <AK/String.h>
#include <AK/StringView.h>
#include <Builtins/Array.h>
#include <Builtins/Set.h>
#include <stdarg.h>

namespace AK {

class StringBuilder {
public:
    using OutputType = String;

    explicit StringBuilder();
    ~StringBuilder() = default;

    ErrorOr<void> try_append(StringView);
    ErrorOr<void> try_append_code_point(u32);
    ErrorOr<void> try_append(char);
    template<typename... Parameters>
    ErrorOr<void> try_appendff(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters)
    {
        VariadicFormatParams variadic_format_params { parameters... };
        return vformat(*this, fmtstr.view(), variadic_format_params);
    }
    ErrorOr<void> try_append(char const*, size_t);
    ErrorOr<void> try_append_escaped_for_json(StringView);

    void append(StringView);
    void append(char);
    void append_code_point(u32);
    void append(char const*, size_t);

    void append_as_lowercase(char);
    void append_escaped_for_json(StringView);

    template<typename... Parameters>
    void appendff(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters)
    {
        VariadicFormatParams variadic_format_params { parameters... };
        MUST(vformat(*this, fmtstr.view(), variadic_format_params));
    }

#ifndef KERNEL
    [[nodiscard]] String build() const;
    [[nodiscard]] String to_string() const;
#endif

    [[nodiscard]] StringView string_view() const;
    void clear();

    [[nodiscard]] size_t length() const { return m_buffer.size(); }
    [[nodiscard]] bool is_empty() const { return m_buffer.is_empty(); }

    template<class SeparatorType, class CollectionType>
    void join(SeparatorType const& separator, CollectionType const& collection, StringView fmtstr = "{}"sv)
    {
        bool first = true;
        for (auto& item : collection) {
            if (first)
                first = false;
            else
                append(separator);
            appendff(fmtstr, item);
        }
    }

private:
    ErrorOr<void> will_append(size_t);
    u8* data() { return m_buffer.unsafe_data(); }
    u8 const* data() const { return const_cast<StringBuilder*>(this)->m_buffer.unsafe_data(); }

    Array<u8> m_buffer;
};

}

using AK::StringBuilder;

namespace AK {

template<typename T>
void append_value(StringBuilder& string_builder, T const& value)
{
    if constexpr (IsSame<String, T>)
        string_builder.append("\"");
    string_builder.appendff("{}", value);
    if constexpr (IsSame<String, T>)
        string_builder.append("\"");
}

template<typename T>
struct Formatter<JaktInternal::Array<T>> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, JaktInternal::Array<T> const& value)
    {
        StringBuilder string_builder;
        string_builder.append("[");
        for (size_t i = 0; i < value.size(); ++i) {
            append_value(string_builder, value[i]);
            if (i != value.size() - 1)
                string_builder.append(", ");
        }
        string_builder.append("]");
        return Formatter<StringView>::format(builder, string_builder.to_string());
    }
};

template<typename T>
struct Formatter<JaktInternal::Set<T>> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, JaktInternal::Set<T> const& set)
    {
        StringBuilder string_builder;
        string_builder.append("{");
        auto iter = set.iterator();

        for (size_t i = 0; i < set.size(); ++i) {
            append_value(string_builder, iter.next().value());
            if (i != set.size() - 1)
                string_builder.append(", ");
        }
        string_builder.append("}");
        return Formatter<StringView>::format(builder, string_builder.to_string());
    }
};

}
