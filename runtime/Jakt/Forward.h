/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Jakt/Types.h>

namespace Jakt {

class Bitmap;
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

template<typename T, Jakt::MemoryOrder DefaultMemoryOrder>
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

template<typename T, typename ErrorType = Error>
class [[nodiscard]] ErrorOr;

template<typename T, typename = void>
struct Formatter;

}
