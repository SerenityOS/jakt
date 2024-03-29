/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Builtins/Dictionary.h>
#include <Builtins/Set.h>

#include <Jakt/AKIntegration.h>
#include <Jakt/PrettyPrint.h>

#include <AK/ByteString.h>
#include <AK/Format.h>
#include <AK/Forward.h>
#include <AK/Optional.h>
#include <AK/String.h>
#include <AK/StringView.h>
#include <AK/Tuple.h>

#include <stdarg.h>

namespace Jakt {

class ByteStringBuilder {
public:
    static ByteStringBuilder create();

    ~ByteStringBuilder() = default;

    void append(StringView);
    void append_code_point(u32);
    void append(char);
    template<typename... Parameters>
    void appendff(CheckedFormatString<Parameters...> fmtstr, Parameters const&... parameters)
    {
        StringBuilder builder;
        builder.appendff(fmtstr.view(), parameters...);
        append(builder.string_view());
    }
    void append(char const*, size_t);
    void append_escaped_for_json(StringView);

    [[nodiscard]] ByteString to_string() const;

    void must_append(StringView string) { append(string); }
    void must_append_code_point(u32 codepoint) { append_code_point(codepoint); }
    void must_append(char ch) { append(ch); }
    template<typename... Parameters>
    void must_appendff(CheckedFormatString<Parameters...> fmtstr, Parameters const&... parameters)
    {
        StringBuilder builder;
        builder.appendff(fmtstr.view(), parameters...);
        append(builder.string_view());
    }
    void must_append(char const* c, size_t s) { append(c, s); }
    void must_append_escaped_for_json(StringView v) { append_escaped_for_json(v); }

    ByteString must_to_string() const { return to_string(); }

    [[nodiscard]] StringView string_view() const;
    void clear();

    [[nodiscard]] size_t length() const { return m_buffer.has_value() ? m_buffer->size() : 0; }
    [[nodiscard]] bool is_empty() const { return !m_buffer.has_value() || m_buffer->is_empty(); }

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
        return {};
    }

    void append_c_string(char const* string) { return append(string, strlen(string)); }

private:
    ByteStringBuilder();

    void will_append(size_t);
    u8* data()
    {
        if (m_buffer.has_value())
            return m_buffer->unsafe_data();
        return nullptr;
    }
    u8 const* data() const
    {
        if (m_buffer.has_value())
            return m_buffer->unsafe_data();
        return nullptr;
    }

    Optional<DynamicArray<u8>> m_buffer;
};

}

namespace Jakt {

template<typename T>
void append_value(ByteStringBuilder& string_builder, T const& value, bool alternative_form = false)
{
    if constexpr (IsSame<ByteString, T>)
        string_builder.append("\""sv);
    string_builder.appendff(alternative_form ? "{:#}"sv : "{}"sv, value);
    if constexpr (IsSame<ByteString, T>)
        string_builder.append("\""sv);
}

}

template<typename T>
struct Jakt::Formatter<T> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, T const&)
    {
        return Jakt::Formatter<Jakt::StringView>::format(builder, "<Unformattable Object>"sv);
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::DynamicArray<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::DynamicArray<T> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        string_builder.append("["sv);
        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            for (size_t i = 0; i < value.size(); ++i) {
                JaktInternal::PrettyPrint::must_output_indentation(string_builder);
                append_value(string_builder, value[i], m_alternative_form);
                if (i != value.size() - 1)
                    string_builder.append(", "sv);
            }
        }
        string_builder.append("]"sv);

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::ArraySlice<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::ArraySlice<T> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        string_builder.append("["sv);
        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            for (size_t i = 0; i < value.size(); ++i) {
                JaktInternal::PrettyPrint::must_output_indentation(string_builder);
                append_value(string_builder, value[i], m_alternative_form);
                if (i != value.size() - 1)
                    string_builder.append(", "sv);
            }
        }
        string_builder.append("]"sv);

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::ArrayIterator<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::ArrayIterator<T> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        string_builder.append("ArrayIterator"sv);

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::Set<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::Set<T> const& set)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        string_builder.append("{"sv);
        auto iter = set.iterator();
        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            for (size_t i = 0; i < set.size(); ++i) {
                JaktInternal::PrettyPrint::must_output_indentation(string_builder);
                append_value(string_builder, iter.next().value(), m_alternative_form);
                if (i != set.size() - 1)
                    string_builder.append(", "sv);
            }
        }
        string_builder.append("}"sv);

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::SetIterator<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::SetIterator<T> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        string_builder.append("SetIterator"sv);

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::Range<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::Range<T> const& range)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            JaktInternal::PrettyPrint::must_output_indentation(string_builder);
            append_value(string_builder, range.start, m_alternative_form);
            string_builder.append(".."sv);
            append_value(string_builder, range.end, m_alternative_form);
        }

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};

template<typename K, typename V>
struct Jakt::Formatter<JaktInternal::Dictionary<K, V>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::Dictionary<K, V> const& dict)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        string_builder.append("["sv);
        auto iter = dict.iterator();

        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            for (size_t i = 0; i < dict.size(); ++i) {
                auto item = iter.next().value();
                JaktInternal::PrettyPrint::must_output_indentation(string_builder);
                append_value(string_builder, item.template get<0>(), m_alternative_form);
                string_builder.append(": "sv);
                append_value(string_builder, item.template get<1>(), m_alternative_form);
                if (i != dict.size() - 1)
                    string_builder.append(", "sv);
            }
        }
        string_builder.append("]"sv);

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};

template<typename K, typename V>
struct Jakt::Formatter<JaktInternal::DictionaryIterator<K, V>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::DictionaryIterator<K, V> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        string_builder.append("DictionaryIterator"sv);

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};

template<typename... Ts>
struct Jakt::Formatter<Jakt::Tuple<Ts...>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::Tuple<Ts...> const& tuple)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::ByteStringBuilder::create();
        string_builder.append("("sv);
        if constexpr (sizeof...(Ts) > 0) {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            tuple.apply_as_args([&](auto first, auto... args) {
                auto append_helper = [&](Jakt::ByteStringBuilder& string_builder, Jakt::StringView value) {
                    string_builder.append(value);
                };
                auto append_value_helper = [&](Jakt::ByteStringBuilder& string_builder, auto const& value) {
                    JaktInternal::PrettyPrint::must_output_indentation(string_builder);
                    append_value(string_builder, value, m_alternative_form);
                };

                append_value_helper(string_builder, first);
                ((append_helper(string_builder, ", "sv), append_value_helper(string_builder, args)), ...);
            });
        }
        string_builder.append(")"sv);

        return Jakt::Formatter<Jakt::StringView>::format(builder, string_builder.to_string());
    }
};
