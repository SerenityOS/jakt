/*
 * Copyright (c) 2022, Mustafa Quraish <mustafa@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "AK/HashTable.h"
#include <initializer_list>

namespace AK {

template<typename T, typename TraitsForT, bool IsOrdered>
class Set : public HashTable<T, TraitsForT, IsOrdered> {
private:
    using HashTableType = HashTable<T, TraitsForT, IsOrdered>;

public:
    using HashTableType::HashTable;

    Set(std::initializer_list<T> list)
    {
        MUST(ensure_capacity(list.size()));
        for (auto& item : list)
            MUST(add(item));
    }

    using HashTableType::contains;

    ErrorOr<HashSetResult> add(T const& value) { return HashTableType::try_set(value); }
    ErrorOr<HashSetResult> add(T&& value) { return HashTableType::try_set(move(value)); }
    ErrorOr<void> ensure_capacity(size_t capacity) { return HashTableType::try_ensure_capacity(capacity); }

    using HashTableType::capacity;
    using HashTableType::clear;
    using HashTableType::remove;
    using HashTableType::size;

    [[nodiscard]] u32 hash() const
    {
        u32 hash = 0;
        for (auto& value : *this) {
            hash = pair_int_hash(hash, value.hash());
        }
        return hash;
    }
};

}

using AK::Set;
