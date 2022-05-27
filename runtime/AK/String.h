/*
 * Copyright (c) 2018-2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/CheckedFormatString.h>
#include <AK/Format.h>
#include <AK/Forward.h>
#include <AK/NonnullRefPtr.h>
#include <AK/RefCounted.h>
#include <AK/Span.h>
#include <AK/StringView.h>
#include <AK/Traits.h>
#include <AK/Types.h>
#include <AK/kmalloc.h>
#include <Builtins/Array.h>

namespace AK {

class StringStorage : public RefCounted<StringStorage> {
public:
    static ErrorOr<NonnullRefPtr<StringStorage>> create_uninitialized(size_t length, char*& buffer);
    static ErrorOr<NonnullRefPtr<StringStorage>> create(char const* c_string, size_t length);

    void operator delete(void* ptr);

    static StringStorage& the_empty_string();

    ~StringStorage();

    size_t length() const { return m_length; }

    // NOTE: Always includes null terminator.
    char const* c_string() const { return &m_inline_buffer[0]; }

    StringView view() const { return { c_string(), length() }; }

    char const& operator[](size_t i) const
    {
        VERIFY(i < m_length);
        return c_string()[i];
    }

    bool operator==(StringStorage const& other) const
    {
        if (length() != other.length())
            return false;
        return __builtin_memcmp(c_string(), other.c_string(), length()) == 0;
    }

    unsigned hash() const
    {
        if (!m_has_hash)
            compute_hash();
        return m_hash;
    }

    unsigned existing_hash() const
    {
        return m_hash;
    }

private:
    enum ConstructTheEmptyStringStorageTag {
        ConstructTheEmptyStringStorage
    };
    explicit StringStorage(ConstructTheEmptyStringStorageTag)
    {
        m_inline_buffer[0] = '\0';
    }

    enum ConstructWithInlineBufferTag {
        ConstructWithInlineBuffer
    };
    StringStorage(ConstructWithInlineBufferTag, size_t length);

    void compute_hash() const;

    size_t m_length { 0 };
    mutable unsigned m_hash { 0 };
    mutable bool m_has_hash { false };
    char m_inline_buffer[0];
};

inline size_t allocation_size_for_StringStorage(size_t length)
{
    return sizeof(StringStorage) + (sizeof(char) * length) + sizeof(char);
}

class String {
public:
    String(String const&) = default;
    String(String&&) = default;
    String& operator=(String&&) = default;
    String& operator=(String const&) = default;

    // FIXME: Remove this constructor!
    explicit String(char const* c_string)
        : m_storage(MUST(StringStorage::create(c_string, strlen(c_string))))
    {
    }

    ~String() = default;

    [[nodiscard]] static String empty() { return String { StringStorage::the_empty_string() }; }
    static ErrorOr<String> from_utf8(StringView);
    static ErrorOr<String> copy(StringView);

    [[nodiscard]] static ErrorOr<String> vformatted(StringView fmtstr, TypeErasedFormatParams&);

    template<typename... Parameters>
    [[nodiscard]] static ErrorOr<String> formatted(CheckedFormatString<Parameters...>&& fmtstr, Parameters const&... parameters)
    {
        VariadicFormatParams variadic_format_parameters { parameters... };
        return vformatted(fmtstr.view(), variadic_format_parameters);
    }

    StringView view() const { return { c_string(), length() }; }

    static ErrorOr<String> repeated(char, size_t count);

    template<typename T = int>
    Optional<T> to_int(TrimWhitespace = TrimWhitespace::Yes) const;
    template<typename T = unsigned>
    Optional<T> to_uint(TrimWhitespace = TrimWhitespace::Yes) const;

    [[nodiscard]] bool is_whitespace() const;

    [[nodiscard]] bool equals_ignoring_case(StringView) const;

    [[nodiscard]] bool contains(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    [[nodiscard]] bool contains(char, CaseSensitivity = CaseSensitivity::CaseSensitive) const;

    ErrorOr<Array<String>> split(char separator, bool keep_empty = false) const;
    ErrorOr<Array<String>> split_limit(char separator, size_t limit, bool keep_empty) const;

    [[nodiscard]] ErrorOr<String> substring(size_t start, size_t length) const;

    [[nodiscard]] bool is_empty() const { return length() == 0; }
    [[nodiscard]] size_t length() const { return m_storage->length(); }

    // Guaranteed to include null terminator.
    [[nodiscard]] char const* c_string() const { return m_storage->c_string(); }

    [[nodiscard]] ALWAYS_INLINE char const& operator[](size_t i) const
    {
        return (*m_storage)[i];
    }

    [[nodiscard]] bool starts_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    [[nodiscard]] bool ends_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const;
    [[nodiscard]] bool starts_with(char) const;
    [[nodiscard]] bool ends_with(char) const;

    bool operator==(String const&) const;
    bool operator!=(String const& other) const { return !(*this == other); }

    bool operator==(StringView) const;
    bool operator!=(StringView other) const { return !(*this == other); }

    bool operator<(String const&) const;
    bool operator<(char const*) const;
    bool operator>=(String const& other) const { return !(*this < other); }
    bool operator>=(char const* other) const { return !(*this < other); }

    bool operator>(String const&) const;
    bool operator>(char const*) const;
    bool operator<=(String const& other) const { return !(*this > other); }
    bool operator<=(char const* other) const { return !(*this > other); }

    bool operator==(char const* cstring) const;
    bool operator!=(char const* cstring) const { return !(*this == cstring); }

    [[nodiscard]] StringStorage& storage() { return *m_storage; }
    [[nodiscard]] StringStorage const& storage() const { return *m_storage; }

    [[nodiscard]] u32 hash() const
    {
        return m_storage->hash();
    }

    template<typename T>
    [[nodiscard]] static ErrorOr<String> number(T value) requires IsArithmetic<T>
    {
        return formatted("{}", value);
    }

private:
    String(NonnullRefPtr<StringStorage> storage)
        : m_storage(move(storage))
    {
    }

    NonnullRefPtr<StringStorage> m_storage;
};
template<>
struct Formatter<StringStorage> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, StringStorage const& value)
    {
        return Formatter<StringView>::format(builder, { value.c_string(), value.length() });
    }
};

template<>
struct Traits<String> : public GenericTraits<String> {
    static unsigned hash(String const& s) { return s.storage().hash(); }
};

template<typename T>
struct Formatter<NonnullRefPtr<T>> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, NonnullRefPtr<T> const& value)
    {
        auto str = TRY(AK::String::formatted("{}", *value));
        return Formatter<StringView>::format(builder, str);
    }
};

template<typename T>
struct Formatter<Optional<T>> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, Optional<T> const& value)
    {
        if (!value.has_value())
            return Formatter<StringView>::format(builder, "None");
        auto str = TRY(AK::String::formatted("{}", *value));
        return Formatter<StringView>::format(builder, str);
    }
};

}

using AK::String;
