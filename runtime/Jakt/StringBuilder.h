/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Builtins/Array.h>
#include <Builtins/Dictionary.h>
#include <Builtins/Set.h>
#include <Jakt/Format.h>
#include <Jakt/Forward.h>
#include <Jakt/String.h>
#include <Jakt/StringView.h>
#include <Jakt/Tuple.h>
#include <stdarg.h>

namespace Jakt {

class StringBuilder {
public:
    static ErrorOr<StringBuilder> create()
    {
        auto array = TRY(Array<u8>::create_empty());
        return StringBuilder { move(array) };
    }
    ~StringBuilder() = default;

    ErrorOr<void> append(StringView);
    ErrorOr<void> append_code_point(u32);
    ErrorOr<void> append(char);
    template<typename... Parameters>
    ErrorOr<void> appendff(StringView&& fmtstr, Parameters const&... parameters)
    {
        VariadicFormatParams variadic_format_params { parameters... };
        return vformat(*this, fmtstr, variadic_format_params);
    }
    ErrorOr<void> append(char const*, size_t);
    ErrorOr<void> append_escaped_for_json(StringView);

    [[nodiscard]] ErrorOr<String> to_string() const;

    [[nodiscard]] StringView string_view() const;
    void clear();

    [[nodiscard]] size_t length() const { return m_buffer.size(); }
    [[nodiscard]] bool is_empty() const { return m_buffer.is_empty(); }

    template<class SeparatorType, class CollectionType>
    ErrorOr<void> join(SeparatorType const& separator, CollectionType const& collection, StringView fmtstr = "{}"sv)
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
    explicit StringBuilder(Array<u8> buffer);

    ErrorOr<void> will_append(size_t);
    u8* data() { return m_buffer.unsafe_data(); }
    u8 const* data() const { return const_cast<StringBuilder*>(this)->m_buffer.unsafe_data(); }

    Array<u8> m_buffer;
};

}

namespace Jakt {

template<typename T>
ErrorOr<void> append_value(StringBuilder& string_builder, T const& value)
{
    if constexpr (IsSame<String, T>)
        TRY(string_builder.append("\""));
    TRY(string_builder.appendff("{}", value));
    if constexpr (IsSame<String, T>)
        TRY(string_builder.append("\""));
    return {};
}

template<typename T>
struct Formatter<JaktInternal::Array<T>> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, JaktInternal::Array<T> const& value)
    {
        auto string_builder = TRY(StringBuilder::create());
        TRY(string_builder.append("["));
        for (size_t i = 0; i < value.size(); ++i) {
            TRY(append_value(string_builder, value[i]));
            if (i != value.size() - 1)
                TRY(string_builder.append(", "));
        }
        TRY(string_builder.append("]"));
        return Formatter<StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename T>
struct Formatter<JaktInternal::Set<T>> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, JaktInternal::Set<T> const& set)
    {
        auto string_builder = TRY(StringBuilder::create());
        TRY(string_builder.append("{"));
        auto iter = set.iterator();

        for (size_t i = 0; i < set.size(); ++i) {
            TRY(append_value(string_builder, iter.next().value()));
            if (i != set.size() - 1)
                TRY(string_builder.append(", "));
        }
        TRY(string_builder.append("}"));
        return Formatter<StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename K, typename V>
struct Formatter<JaktInternal::Dictionary<K, V>> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, JaktInternal::Dictionary<K, V> const& dict)
    {
        auto string_builder = TRY(StringBuilder::create());
        TRY(string_builder.append("["));
        auto iter = dict.iterator();

        for (size_t i = 0; i < dict.size(); ++i) {
            auto item = iter.next().value();
            TRY(append_value(string_builder, item.template get<0>()));
            TRY(string_builder.append(": "));
            TRY(append_value(string_builder, item.template get<1>()));
            if (i != dict.size() - 1)
                TRY(string_builder.append(", "));
        }
        TRY(string_builder.append("]"));
        return Formatter<StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename... Ts>
struct Formatter<Jakt::Tuple<Ts...>> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, Jakt::Tuple<Ts...> const& tuple)
    {
        auto string_builder = TRY(StringBuilder::create());
        TRY(string_builder.append("("));
        if constexpr (sizeof...(Ts) > 0) {
            TRY(tuple.apply_as_args([&](auto first, auto... args) {
                ErrorOr<void> append_error = {};

                auto append_helper = [&](StringBuilder& string_builder, StringView value) {
                    if (!append_error.is_error())
                        append_error = string_builder.append(value);
                };
                auto append_value_helper = [&](StringBuilder& string_builder, auto const& value) {
                    if (!append_error.is_error())
                        append_error = append_value(string_builder, value);
                };

                append_value_helper(string_builder, first);
                ((append_helper(string_builder, ", "), append_value_helper(string_builder, args)), ...);

                return append_error;
            }));
        }

        TRY(string_builder.append(")"));
        return Formatter<StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

}
