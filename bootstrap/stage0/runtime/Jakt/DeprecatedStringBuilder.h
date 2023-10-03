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

#include <AK/DeprecatedString.h>
#include <AK/Format.h>
#include <AK/Forward.h>
#include <AK/Optional.h>
#include <AK/String.h>
#include <AK/StringView.h>
#include <AK/Tuple.h>

#include <stdarg.h>

namespace Jakt {

class DeprecatedStringBuilder {
public:
    static DeprecatedStringBuilder create();

    ~DeprecatedStringBuilder() = default;

    ErrorOr<void> append(StringView);
    ErrorOr<void> append_code_point(u32);
    ErrorOr<void> append(char);
    template<typename... Parameters>
    ErrorOr<void> appendff(CheckedFormatString<Parameters...> fmtstr, Parameters const&... parameters)
    {
        StringBuilder builder;
        TRY(builder.try_appendff(fmtstr.view(), parameters...));
        return append(builder.string_view());
    }
    ErrorOr<void> append(char const*, size_t);
    ErrorOr<void> append_escaped_for_json(StringView);

    [[nodiscard]] ErrorOr<DeprecatedString> to_string() const;

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

    // FIXME: These only exist because we don't support function overloading in Jakt yet.
    ErrorOr<void> append_string(DeprecatedString const& string) { return append(string.view()); }
    ErrorOr<void> append_c_string(char const* string) { return append(string, strlen(string)); }

private:
    DeprecatedStringBuilder();

    ErrorOr<void> will_append(size_t);
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
ErrorOr<void> append_value(DeprecatedStringBuilder& string_builder, T const& value, bool alternative_form=false)
{
    if constexpr (IsSame<DeprecatedString, T>)
        TRY(string_builder.append("\""sv));
    TRY(string_builder.appendff(alternative_form ? "{:#}"sv : "{}"sv, value));
    if constexpr (IsSame<DeprecatedString, T>)
        TRY(string_builder.append("\""sv));
    return {};
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

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        TRY(string_builder.append("["sv));
        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            for (size_t i = 0; i < value.size(); ++i) {
                TRY(JaktInternal::PrettyPrint::output_indentation(string_builder));
                TRY(append_value(string_builder, value[i], m_alternative_form));
                if (i != value.size() - 1)
                    TRY(string_builder.append(", "sv));
            }
        }
        TRY(string_builder.append("]"sv));

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::ArraySlice<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::ArraySlice<T> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        TRY(string_builder.append("["sv));
        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            for (size_t i = 0; i < value.size(); ++i) {
                TRY(JaktInternal::PrettyPrint::output_indentation(string_builder));
                TRY(append_value(string_builder, value[i], m_alternative_form));
                if (i != value.size() - 1)
                    TRY(string_builder.append(", "sv));
            }
        }
        TRY(string_builder.append("]"sv));

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::ArrayIterator<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::ArrayIterator<T> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        TRY(string_builder.append("ArrayIterator"sv));

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::Set<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::Set<T> const& set)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        TRY(string_builder.append("{"sv));
        auto iter = set.iterator();
        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            for (size_t i = 0; i < set.size(); ++i) {
                TRY(JaktInternal::PrettyPrint::output_indentation(string_builder));
                TRY(append_value(string_builder, iter.next().value(), m_alternative_form));
                if (i != set.size() - 1)
                    TRY(string_builder.append(", "sv));
            }
        }
        TRY(string_builder.append("}"sv));

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::SetIterator<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::SetIterator<T> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        TRY(string_builder.append("SetIterator"sv));

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename T>
struct Jakt::Formatter<JaktInternal::Range<T>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::Range<T> const& range)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            TRY(JaktInternal::PrettyPrint::output_indentation(string_builder));
            TRY(append_value(string_builder, range.start, m_alternative_form));
            TRY(string_builder.append(".."sv));
            TRY(append_value(string_builder, range.end, m_alternative_form));
        }

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename K, typename V>
struct Jakt::Formatter<JaktInternal::Dictionary<K, V>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::Dictionary<K, V> const& dict)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        TRY(string_builder.append("["sv));
        auto iter = dict.iterator();

        {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            for (size_t i = 0; i < dict.size(); ++i) {
                auto item = iter.next().value();
                TRY(JaktInternal::PrettyPrint::output_indentation(string_builder));
                TRY(append_value(string_builder, item.template get<0>(), m_alternative_form));
                TRY(string_builder.append(": "sv));
                TRY(append_value(string_builder, item.template get<1>(), m_alternative_form));
                if (i != dict.size() - 1)
                    TRY(string_builder.append(", "sv));
            }
        }
        TRY(string_builder.append("]"sv));

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename K, typename V>
struct Jakt::Formatter<JaktInternal::DictionaryIterator<K, V>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, JaktInternal::DictionaryIterator<K, V> const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        TRY(string_builder.append("DictionaryIterator"sv));

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};

template<typename... Ts>
struct Jakt::Formatter<Jakt::Tuple<Ts...>> : Jakt::Formatter<Jakt::StringView> {
    Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::Tuple<Ts...> const& tuple)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };

        auto string_builder = Jakt::DeprecatedStringBuilder::create();
        TRY(string_builder.append("("sv));
        if constexpr (sizeof...(Ts) > 0) {
            JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
            TRY(tuple.apply_as_args([&](auto first, auto... args) {
                Jakt::ErrorOr<void> append_error = {};

                auto append_helper = [&](Jakt::DeprecatedStringBuilder& string_builder, Jakt::StringView value) {
                    if (!append_error.is_error())
                        append_error = string_builder.append(value);
                };
                auto append_value_helper = [&](Jakt::DeprecatedStringBuilder& string_builder, auto const& value) {
                    (void) JaktInternal::PrettyPrint::output_indentation(string_builder);
                    if (!append_error.is_error())
                        append_error = append_value(string_builder, value, m_alternative_form);
                };

                append_value_helper(string_builder, first);
                ((append_helper(string_builder, ", "sv), append_value_helper(string_builder, args)), ...);
                return append_error;
            }));
        }
        TRY(string_builder.append(")"sv));

        return Jakt::Formatter<Jakt::StringView>::format(builder, TRY(string_builder.to_string()));
    }
};
