/*
 * Copyright (c) 2018-2020, Andreas Kling <awesomekling@gmail.com>
 * Copyright (c) 2020, Fei Wu <f.eiwu@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/CharacterTypes.h>
#include <AK/MemMem.h>
#include <AK/Memory.h>
#include <AK/Optional.h>
#include <AK/String.h>
#include <AK/StringBuilder.h>
#include <AK/StringUtils.h>
#include <AK/StringView.h>

namespace AK {

namespace StringUtils {

template<typename T>
Optional<T> convert_to_int(StringView str, TrimWhitespace trim_whitespace)
{
    auto string = trim_whitespace == TrimWhitespace::Yes
        ? str.trim_whitespace()
        : str;
    if (string.is_empty())
        return {};

    T sign = 1;
    size_t i = 0;
    auto const characters = string.characters_without_null_termination();

    if (characters[0] == '-' || characters[0] == '+') {
        if (string.length() == 1)
            return {};
        i++;
        if (characters[0] == '-')
            sign = -1;
    }

    T value = 0;
    for (; i < string.length(); i++) {
        if (characters[i] < '0' || characters[i] > '9')
            return {};

        if (__builtin_mul_overflow(value, 10, &value))
            return {};

        if (__builtin_add_overflow(value, sign * (characters[i] - '0'), &value))
            return {};
    }
    return value;
}

template Optional<i8> convert_to_int(StringView str, TrimWhitespace);
template Optional<i16> convert_to_int(StringView str, TrimWhitespace);
template Optional<i32> convert_to_int(StringView str, TrimWhitespace);
template Optional<long> convert_to_int(StringView str, TrimWhitespace);
template Optional<long long> convert_to_int(StringView str, TrimWhitespace);

template<typename T>
Optional<T> convert_to_uint(StringView str, TrimWhitespace trim_whitespace)
{
    auto string = trim_whitespace == TrimWhitespace::Yes
        ? str.trim_whitespace()
        : str;
    if (string.is_empty())
        return {};

    T value = 0;
    auto const characters = string.characters_without_null_termination();

    for (size_t i = 0; i < string.length(); i++) {
        if (characters[i] < '0' || characters[i] > '9')
            return {};

        if (__builtin_mul_overflow(value, 10, &value))
            return {};

        if (__builtin_add_overflow(value, characters[i] - '0', &value))
            return {};
    }
    return value;
}

template Optional<u8> convert_to_uint(StringView str, TrimWhitespace);
template Optional<u16> convert_to_uint(StringView str, TrimWhitespace);
template Optional<u32> convert_to_uint(StringView str, TrimWhitespace);
template Optional<unsigned long> convert_to_uint(StringView str, TrimWhitespace);
template Optional<unsigned long long> convert_to_uint(StringView str, TrimWhitespace);
template Optional<long> convert_to_uint(StringView str, TrimWhitespace);
template Optional<long long> convert_to_uint(StringView str, TrimWhitespace);

template<typename T>
Optional<T> convert_to_uint_from_hex(StringView str, TrimWhitespace trim_whitespace)
{
    auto string = trim_whitespace == TrimWhitespace::Yes
        ? str.trim_whitespace()
        : str;
    if (string.is_empty())
        return {};

    T value = 0;
    auto const count = string.length();
    const T upper_bound = NumericLimits<T>::max();

    for (size_t i = 0; i < count; i++) {
        char digit = string[i];
        u8 digit_val;
        if (value > (upper_bound >> 4))
            return {};

        if (digit >= '0' && digit <= '9') {
            digit_val = digit - '0';
        } else if (digit >= 'a' && digit <= 'f') {
            digit_val = 10 + (digit - 'a');
        } else if (digit >= 'A' && digit <= 'F') {
            digit_val = 10 + (digit - 'A');
        } else {
            return {};
        }

        value = (value << 4) + digit_val;
    }
    return value;
}

template Optional<u8> convert_to_uint_from_hex(StringView str, TrimWhitespace);
template Optional<u16> convert_to_uint_from_hex(StringView str, TrimWhitespace);
template Optional<u32> convert_to_uint_from_hex(StringView str, TrimWhitespace);
template Optional<u64> convert_to_uint_from_hex(StringView str, TrimWhitespace);

template<typename T>
Optional<T> convert_to_uint_from_octal(StringView str, TrimWhitespace trim_whitespace)
{
    auto string = trim_whitespace == TrimWhitespace::Yes
        ? str.trim_whitespace()
        : str;
    if (string.is_empty())
        return {};

    T value = 0;
    auto const count = string.length();
    const T upper_bound = NumericLimits<T>::max();

    for (size_t i = 0; i < count; i++) {
        char digit = string[i];
        u8 digit_val;
        if (value > (upper_bound >> 3))
            return {};

        if (digit >= '0' && digit <= '7') {
            digit_val = digit - '0';
        } else {
            return {};
        }

        value = (value << 3) + digit_val;
    }
    return value;
}

template Optional<u8> convert_to_uint_from_octal(StringView str, TrimWhitespace);
template Optional<u16> convert_to_uint_from_octal(StringView str, TrimWhitespace);
template Optional<u32> convert_to_uint_from_octal(StringView str, TrimWhitespace);
template Optional<u64> convert_to_uint_from_octal(StringView str, TrimWhitespace);

bool equals_ignoring_case(StringView a, StringView b)
{
    if (a.length() != b.length())
        return false;
    for (size_t i = 0; i < a.length(); ++i) {
        if (to_ascii_lowercase(a.characters_without_null_termination()[i]) != to_ascii_lowercase(b.characters_without_null_termination()[i]))
            return false;
    }
    return true;
}

bool ends_with(StringView str, StringView end, CaseSensitivity case_sensitivity)
{
    if (end.is_empty())
        return true;
    if (str.is_empty())
        return false;
    if (end.length() > str.length())
        return false;

    if (case_sensitivity == CaseSensitivity::CaseSensitive)
        return !memcmp(str.characters_without_null_termination() + (str.length() - end.length()), end.characters_without_null_termination(), end.length());

    auto str_chars = str.characters_without_null_termination();
    auto end_chars = end.characters_without_null_termination();

    size_t si = str.length() - end.length();
    for (size_t ei = 0; ei < end.length(); ++si, ++ei) {
        if (to_ascii_lowercase(str_chars[si]) != to_ascii_lowercase(end_chars[ei]))
            return false;
    }
    return true;
}

bool starts_with(StringView str, StringView start, CaseSensitivity case_sensitivity)
{
    if (start.is_empty())
        return true;
    if (str.is_empty())
        return false;
    if (start.length() > str.length())
        return false;
    if (str.characters_without_null_termination() == start.characters_without_null_termination())
        return true;

    if (case_sensitivity == CaseSensitivity::CaseSensitive)
        return !memcmp(str.characters_without_null_termination(), start.characters_without_null_termination(), start.length());

    auto str_chars = str.characters_without_null_termination();
    auto start_chars = start.characters_without_null_termination();

    size_t si = 0;
    for (size_t starti = 0; starti < start.length(); ++si, ++starti) {
        if (to_ascii_lowercase(str_chars[si]) != to_ascii_lowercase(start_chars[starti]))
            return false;
    }
    return true;
}

bool contains(StringView str, StringView needle, CaseSensitivity case_sensitivity)
{
    if (str.is_null() || needle.is_null() || str.is_empty() || needle.length() > str.length())
        return false;
    if (needle.is_empty())
        return true;
    auto str_chars = str.characters_without_null_termination();
    auto needle_chars = needle.characters_without_null_termination();
    if (case_sensitivity == CaseSensitivity::CaseSensitive)
        return memmem(str_chars, str.length(), needle_chars, needle.length()) != nullptr;

    auto needle_first = to_ascii_lowercase(needle_chars[0]);
    for (size_t si = 0; si < str.length(); si++) {
        if (to_ascii_lowercase(str_chars[si]) != needle_first)
            continue;
        for (size_t ni = 0; si + ni < str.length(); ni++) {
            if (to_ascii_lowercase(str_chars[si + ni]) != to_ascii_lowercase(needle_chars[ni])) {
                if (ni > 0)
                    si += ni - 1;
                break;
            }
            if (ni + 1 == needle.length())
                return true;
        }
    }
    return false;
}

bool is_whitespace(StringView str)
{
    return all_of(str, is_ascii_space);
}

StringView trim(StringView str, StringView characters, TrimMode mode)
{
    size_t substring_start = 0;
    size_t substring_length = str.length();

    if (mode == TrimMode::Left || mode == TrimMode::Both) {
        for (size_t i = 0; i < str.length(); ++i) {
            if (substring_length == 0)
                return "";
            if (!characters.contains(str[i]))
                break;
            ++substring_start;
            --substring_length;
        }
    }

    if (mode == TrimMode::Right || mode == TrimMode::Both) {
        for (size_t i = str.length() - 1; i > 0; --i) {
            if (substring_length == 0)
                return "";
            if (!characters.contains(str[i]))
                break;
            --substring_length;
        }
    }

    return str.substring_view(substring_start, substring_length);
}

StringView trim_whitespace(StringView str, TrimMode mode)
{
    return trim(str, " \n\t\v\f\r", mode);
}

Optional<size_t> find(StringView haystack, char needle, size_t start)
{
    if (start >= haystack.length())
        return {};
    for (size_t i = start; i < haystack.length(); ++i) {
        if (haystack[i] == needle)
            return i;
    }
    return {};
}

Optional<size_t> find(StringView haystack, StringView needle, size_t start)
{
    if (start > haystack.length())
        return {};
    auto index = AK::memmem_optional(
        haystack.characters_without_null_termination() + start, haystack.length() - start,
        needle.characters_without_null_termination(), needle.length());
    return index.has_value() ? (*index + start) : index;
}

Optional<size_t> find_last(StringView haystack, char needle)
{
    for (size_t i = haystack.length(); i > 0; --i) {
        if (haystack[i - 1] == needle)
            return i - 1;
    }
    return {};
}

ErrorOr<JaktInternal::Array<size_t>> find_all(StringView haystack, StringView needle)
{
    JaktInternal::Array<size_t> positions;
    size_t current_position = 0;
    while (current_position <= haystack.length()) {
        auto maybe_position = AK::memmem_optional(
            haystack.characters_without_null_termination() + current_position, haystack.length() - current_position,
            needle.characters_without_null_termination(), needle.length());
        if (!maybe_position.has_value())
            break;
        TRY(positions.push(current_position + *maybe_position));
        current_position += *maybe_position + 1;
    }
    return positions;
}

Optional<size_t> find_any_of(StringView haystack, StringView needles, SearchDirection direction)
{
    if (haystack.is_empty() || needles.is_empty())
        return {};
    if (direction == SearchDirection::Forward) {
        for (size_t i = 0; i < haystack.length(); ++i) {
            if (needles.contains(haystack[i]))
                return i;
        }
    } else if (direction == SearchDirection::Backward) {
        for (size_t i = haystack.length(); i > 0; --i) {
            if (needles.contains(haystack[i - 1]))
                return i - 1;
        }
    }
    return {};
}
// TODO: Benchmark against KMP (AK/MemMem.h) and switch over if it's faster for short strings too
size_t count(StringView str, StringView needle)
{
    if (needle.is_empty())
        return str.length();

    size_t count = 0;
    for (size_t i = 0; i < str.length() - needle.length() + 1; ++i) {
        if (str.substring_view(i).starts_with(needle))
            count++;
    }
    return count;
}

}

}
