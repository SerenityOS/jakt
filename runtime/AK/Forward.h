/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Types.h>

namespace AK {

namespace Detail {
template<size_t inline_capacity>
class ByteBuffer;
}

class Bitmap;
using ByteBuffer = AK::Detail::ByteBuffer<32>;
class Error;
class GenericLexer;
class String;
class StringBuilder;
class StringImpl;
class StringView;
class Time;
class Utf8CodePointIterator;
class Utf8View;

template<typename T>
class Span;

template<typename T, size_t Size>
struct LinearArray;

template<typename Container, typename ValueType>
class SimpleIterator;

using ReadonlyBytes = Span<const u8>;
using Bytes = Span<u8>;

template<typename T, AK::MemoryOrder DefaultMemoryOrder>
class Atomic;

template<typename T>
struct Traits;

template<typename T, typename TraitsForT = Traits<T>, bool IsOrdered = false>
class HashTable;

template<typename T, typename TraitsForT = Traits<T>>
using OrderedHashTable = HashTable<T, TraitsForT, true>;

template<typename K, typename V, typename KeyTraits = Traits<K>, bool IsOrdered = false>
class HashMap;

template<typename K, typename V, typename KeyTraits = Traits<K>>
using OrderedHashMap = HashMap<K, V, KeyTraits, true>;

template<typename T>
class Badge;

template<size_t precision, typename Underlying = i32>
class FixedPoint;

template<typename>
class Function;

template<typename Out, typename... In>
class Function<Out(In...)>;

template<typename T>
class NonnullRefPtr;

template<typename T>
class Optional;

#ifdef KERNEL
template<typename T>
struct RefPtrTraits;

template<typename T, typename PtrTraits = RefPtrTraits<T>>
class RefPtr;
#else
template<typename T>
class RefPtr;
#endif

template<typename T>
class WeakPtr;

template<typename T, size_t inline_capacity = 0>
requires(!IsRvalueReference<T>) class Vector;

template<typename T, typename ErrorType = Error>
class [[nodiscard]] ErrorOr;

}

using AK::Atomic;
using AK::Badge;
using AK::Bitmap;
using AK::ByteBuffer;
using AK::Bytes;
using AK::Error;
using AK::ErrorOr;
using AK::FixedPoint;
using AK::Function;
using AK::GenericLexer;
using AK::HashMap;
using AK::HashTable;
using AK::LinearArray;
using AK::NonnullRefPtr;
using AK::Optional;
using AK::ReadonlyBytes;
using AK::RefPtr;
using AK::Span;
using AK::String;
using AK::StringBuilder;
using AK::StringImpl;
using AK::StringView;
using AK::Time;
using AK::Traits;
using AK::Utf8CodePointIterator;
using AK::Utf8View;
using AK::Vector;
