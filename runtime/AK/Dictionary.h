/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/HashMap.h>
#include <AK/NonnullRefPtr.h>
#include <AK/RefCounted.h>

namespace AK {

template<typename K, typename V>
struct DictionaryStorage : public RefCounted<DictionaryStorage<K, V>> {
    HashMap<K, V> map;
};

template<typename K, typename V>
class Dictionary {
    using Storage = DictionaryStorage<K, V>;

public:
    bool is_empty() const { return m_storage->map.is_empty(); }
    size_t size() const { return m_storage->map.size(); }
    void clear() { m_storage->map.clear(); }

    ErrorOr<void> set(K const& key, V value)
    {
        TRY(m_storage->map.set(key, move(value)));
        return {};
    }

    bool remove(K const& key) { return m_storage->map.remove(key); }
    bool contains(K const& key) const { return m_storage->map.contains(key); }

    Optional<V> get(K const& key) const { return m_storage->map.get(key); }

    Vector<K> keys() const { return m_storage->map.keys(); }

    ErrorOr<void> ensure_capacity(size_t capacity)
    {
        TRY(m_storage->map.ensure_capacity(capacity));
        return {};
    }

    // FIXME: Remove this constructor once jakt knows how to call Dictionary::create_empty()
    Dictionary()
        : m_storage(MUST(adopt_nonnull_ref_or_enomem(new (nothrow) Storage)))
    {
    }

    // FIXME: Remove this constructor once jakt knows how to call Dictionary::create_with_entries()
    struct Entry {
        K key;
        V value;
    };
    Dictionary(std::initializer_list<Entry> list)
        : m_storage(MUST(adopt_nonnull_ref_or_enomem(new (nothrow) Storage)))
    {
        MUST(ensure_capacity(list.size()));
        for (auto& item : list)
            MUST(set(item.key, item.value));
    }

    static ErrorOr<Dictionary> create_empty()
    {
        auto storage = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Storage));
        return Dictionary { move(storage) };
    }

    static ErrorOr<Dictionary> create_with_entries(std::initializer_list<Entry> list)
    {
        auto dictionary = TRY(create_empty());
        TRY(dictionary.ensure_capacity(list.size()));
        for (auto& item : list)
            TRY(dictionary.set(item.key, item.value));
        return dictionary;
    }

private:
    explicit Dictionary(NonnullRefPtr<Storage> storage)
        : m_storage(move(storage))
    {
    }

    NonnullRefPtr<Storage> m_storage;
};

}

using AK::Dictionary;
