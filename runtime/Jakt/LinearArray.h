/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Jakt/Iterator.h>
#include <Jakt/Span.h>

namespace Jakt {

template<typename T, size_t Size>
struct LinearArray {
    using ValueType = T;

    [[nodiscard]] constexpr T const* data() const { return __data; }
    [[nodiscard]] constexpr T* data() { return __data; }

    [[nodiscard]] constexpr size_t size() const { return Size; }

    [[nodiscard]] constexpr Span<T const> span() const { return { __data, Size }; }
    [[nodiscard]] constexpr Span<T> span() { return { __data, Size }; }

    [[nodiscard]] constexpr T const& at(size_t index) const
    {
        VERIFY(index < size());
        return __data[index];
    }
    [[nodiscard]] constexpr T& at(size_t index)
    {
        VERIFY(index < size());
        return __data[index];
    }

    [[nodiscard]] constexpr T const& first() const { return at(0); }
    [[nodiscard]] constexpr T& first() { return at(0); }

    [[nodiscard]] constexpr T const& last() const requires(Size > 0) { return at(Size - 1); }
    [[nodiscard]] constexpr T& last() requires(Size > 0) { return at(Size - 1); }

    [[nodiscard]] constexpr bool is_empty() const { return size() == 0; }

    [[nodiscard]] constexpr T const& operator[](size_t index) const { return at(index); }
    [[nodiscard]] constexpr T& operator[](size_t index) { return at(index); }

    template<typename T2, size_t Size2>
    [[nodiscard]] constexpr bool operator==(LinearArray<T2, Size2> const& other) const { return span() == other.span(); }

    using ConstIterator = SimpleIterator<LinearArray const, T const>;
    using Iterator = SimpleIterator<LinearArray, T>;

    [[nodiscard]] constexpr ConstIterator begin() const { return ConstIterator::begin(*this); }
    [[nodiscard]] constexpr Iterator begin() { return Iterator::begin(*this); }

    [[nodiscard]] constexpr ConstIterator end() const { return ConstIterator::end(*this); }
    [[nodiscard]] constexpr Iterator end() { return Iterator::end(*this); }

    [[nodiscard]] constexpr operator Span<T const>() const { return span(); }
    [[nodiscard]] constexpr operator Span<T>() { return span(); }

    constexpr size_t fill(T const& value)
    {
        for (size_t idx = 0; idx < Size; ++idx)
            __data[idx] = value;

        return Size;
    }

    [[nodiscard]] constexpr T max() const requires(requires(T x, T y) { x < y; })
    {
        static_assert(Size > 0, "No values to max() over");

        T value = __data[0];
        for (size_t i = 1; i < Size; ++i)
            value = Jakt::max(__data[i], value);
        return value;
    }

    [[nodiscard]] constexpr T min() const requires(requires(T x, T y) { x > y; })
    {
        static_assert(Size > 0, "No values to min() over");

        T value = __data[0];
        for (size_t i = 1; i < Size; ++i)
            value = Jakt::min(__data[i], value);
        return value;
    }

    T __data[Size];
};

template<typename T, typename... Types>
LinearArray(T, Types...) -> LinearArray<T, sizeof...(Types) + 1>;

namespace Detail {
template<typename T, size_t... Is>
constexpr auto integer_sequence_generate_LinearArray([[maybe_unused]] T const offset, IntegerSequence<T, Is...>) -> LinearArray<T, sizeof...(Is)>
{
    return { { (offset + Is)... } };
}
}

template<typename T, T N>
constexpr static auto iota_LinearArray(T const offset = {})
{
    static_assert(N >= T {}, "Negative sizes not allowed in iota_LinearArray()");
    return Detail::integer_sequence_generate_LinearArray<T>(offset, MakeIntegerSequence<T, N>());
}

}
