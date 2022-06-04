/*
 * Copyright (c) 2018-2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Jakt/Checked.h>
#include <Jakt/Format.h>
#include <Jakt/Memory.h>
#include <Jakt/StdLibExtras.h>
#include <Jakt/String.h>
#include <Jakt/StringUtils.h>

namespace Jakt {

ErrorOr<String> String::copy(StringView view)
{
    auto storage = TRY(StringStorage::create(view.characters_without_null_termination(), view.length()));
    return String { storage };
}

ErrorOr<String> String::vformatted(StringView fmtstr, TypeErasedFormatParams& params)
{
    StringBuilder builder;
    TRY(vformat(builder, fmtstr, params));
    return builder.to_string();
}

bool String::operator==(String const& other) const
{
    return m_storage == other.storage() || view() == other.view();
}

bool String::operator==(StringView other) const
{
    return view() == other;
}

bool String::operator<(String const& other) const
{
    return view() < other.view();
}

bool String::operator>(String const& other) const
{
    return view() > other.view();
}

ErrorOr<String> String::substring(size_t start, size_t length) const
{
    if (!length)
        return String::empty();
    VERIFY(!Checked<size_t>::addition_would_overflow(start, length));
    VERIFY(start + length <= m_storage->length());
    return String::copy(StringView { c_string() + start, length });
}

ErrorOr<Array<String>> String::split(char separator, bool keep_empty) const
{
    return split_limit(separator, 0, keep_empty);
}

ErrorOr<Array<String>> String::split_limit(char separator, size_t limit, bool keep_empty) const
{
    auto v = Array<String>();
    if (is_empty())
        return v;

    size_t substart = 0;
    for (size_t i = 0; i < length() && (v.size() + 1) != limit; ++i) {
        char ch = c_string()[i];
        if (ch == separator) {
            size_t sublen = i - substart;
            if (sublen != 0 || keep_empty)
                TRY(v.push(TRY(substring(substart, sublen))));
            substart = i + 1;
        }
    }
    size_t taillen = length() - substart;
    if (taillen != 0 || keep_empty)
        TRY(v.push(TRY(substring(substart, taillen))));
    return v;
}

template<typename T>
Optional<T> String::to_int(TrimWhitespace trim_whitespace) const
{
    return Jakt::StringUtils::convert_to_int<T>(view(), trim_whitespace);
}

template Optional<i8> String::to_int(TrimWhitespace) const;
template Optional<i16> String::to_int(TrimWhitespace) const;
template Optional<i32> String::to_int(TrimWhitespace) const;
template Optional<i64> String::to_int(TrimWhitespace) const;

template<typename T>
Optional<T> String::to_uint(TrimWhitespace trim_whitespace) const
{
    return Jakt::StringUtils::convert_to_uint<T>(view(), trim_whitespace);
}

template Optional<u8> String::to_uint(TrimWhitespace) const;
template Optional<u16> String::to_uint(TrimWhitespace) const;
template Optional<u32> String::to_uint(TrimWhitespace) const;
template Optional<unsigned long> String::to_uint(TrimWhitespace) const;
template Optional<unsigned long long> String::to_uint(TrimWhitespace) const;

bool String::starts_with(StringView str, CaseSensitivity case_sensitivity) const
{
    return Jakt::StringUtils::starts_with(view(), str, case_sensitivity);
}

bool String::starts_with(char ch) const
{
    if (is_empty())
        return false;
    return c_string()[0] == ch;
}

bool String::ends_with(StringView str, CaseSensitivity case_sensitivity) const
{
    return Jakt::StringUtils::ends_with(view(), str, case_sensitivity);
}

bool String::ends_with(char ch) const
{
    if (is_empty())
        return false;
    return c_string()[length() - 1] == ch;
}

ErrorOr<String> String::repeated(char ch, size_t count)
{
    if (!count)
        return empty();
    char* buffer;
    auto storage = TRY(StringStorage::create_uninitialized(count, buffer));
    memset(buffer, ch, count);
    return String { *storage };
}

bool String::contains(StringView needle, CaseSensitivity case_sensitivity) const
{
    return Jakt::StringUtils::contains(view(), needle, case_sensitivity);
}

bool String::contains(char needle, CaseSensitivity case_sensitivity) const
{
    return Jakt::StringUtils::contains(view(), StringView(&needle, 1), case_sensitivity);
}

bool String::equals_ignoring_case(StringView other) const
{
    return Jakt::StringUtils::equals_ignoring_case(view(), other);
}

bool operator<(char const* characters, String const& string)
{
    return string.view() > characters;
}

bool operator>=(char const* characters, String const& string)
{
    return string.view() <= characters;
}

bool operator>(char const* characters, String const& string)
{
    return string.view() < characters;
}

bool operator<=(char const* characters, String const& string)
{
    return string.view() >= characters;
}

bool String::operator==(char const* c_string) const
{
    return view() == c_string;
}

void StringStorage::operator delete(void* ptr)
{
    free(ptr);
}

static StringStorage* s_the_empty_string_storage = nullptr;

StringStorage& StringStorage::the_empty_string()
{
    if (!s_the_empty_string_storage) {
        void* slot = malloc(sizeof(StringStorage) + sizeof(char));
        s_the_empty_string_storage = new (slot) StringStorage(ConstructTheEmptyStringStorage);
    }
    return *s_the_empty_string_storage;
}

StringStorage::StringStorage(ConstructWithInlineBufferTag, size_t length)
    : m_length(length)
{
}

StringStorage::~StringStorage()
{
}

constexpr size_t allocation_size_for_string_storage(size_t length)
{
    return sizeof(StringStorage) + (sizeof(char) * length) + sizeof(char);
}

ErrorOr<NonnullRefPtr<StringStorage>> StringStorage::create_uninitialized(size_t length, char*& buffer)
{
    VERIFY(length);
    void* slot = malloc(allocation_size_for_string_storage(length));
    if (!slot) {
        return Error::from_errno(ENOMEM);
    }
    auto new_string_storage = adopt_ref(*new (slot) StringStorage(ConstructWithInlineBuffer, length));
    buffer = const_cast<char*>(new_string_storage->c_string());
    buffer[length] = '\0';
    return new_string_storage;
}

ErrorOr<NonnullRefPtr<StringStorage>> StringStorage::create(char const* c_string, size_t length)
{
    if (!length)
        return the_empty_string();

    VERIFY(c_string);

    char* buffer;
    auto new_string_storage = TRY(create_uninitialized(length, buffer));
    memcpy(buffer, c_string, length * sizeof(char));

    return new_string_storage;
}

void StringStorage::compute_hash() const
{
    if (!length())
        m_hash = 0;
    else
        m_hash = string_hash(c_string(), m_length);
    m_has_hash = true;
}

}
