/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Jakt/AKIntegration.h>

#include <AK/HashMap.h>
#include <AK/NonnullRefPtr.h>
#include <AK/RefCounted.h>
#include <AK/Tuple.h>
#include <Builtins/DynamicArray.h>

namespace JaktInternal {
using namespace Jakt;

template<typename T>
struct DirectlyPeekableTraits : public Traits<T> {
    using PeekType = T&;
    using ConstPeekType = T const&;
};

template<typename T>
struct JaktHashableKeyTraits : public Traits<T> {
    ALWAYS_INLINE static constexpr bool equals(T const& a, T const& b) {
        if constexpr (requires { { a.equals(b) } -> SameAs<bool>; })
            return a.equals(b);
        else
            return a == b;
    }

    ALWAYS_INLINE static constexpr unsigned hash(T value)
    {
        if constexpr (requires { { value.hash() } -> SameAs<u32>; })
            return value.hash();
        else
            return Traits<T>::hash(value);
    }
};

template<typename K, typename V>
struct DictionaryStorage : public RefCounted<DictionaryStorage<K, V>> {
    HashMap<K, V, JaktHashableKeyTraits<K>, DirectlyPeekableTraits<V>> map;
};

template<typename K, typename V>
class DictionaryIterator {
    using Storage = DictionaryStorage<K, V>;
    using Iterator = typename decltype(declval<Storage&>().map)::IteratorType;

public:
    DictionaryIterator(NonnullRefPtr<Storage> storage)
        : m_storage(move(storage))
        , m_iterator(m_storage->map.begin())
    {
    }

    Optional<Tuple<K, V>> next()
    {
        if (m_iterator == m_storage->map.end())
            return {};
        auto res = *m_iterator;
        ++m_iterator;
        return Tuple<K, V>(res.key, res.value);
    }

private:
    NonnullRefPtr<Storage> m_storage;
    Iterator m_iterator;
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
        TRY(m_storage->map.try_set(key, move(value)));
        return {};
    }

    bool remove(K const& key) { return m_storage->map.remove(key); }
    bool contains(K const& key) const { return m_storage->map.contains(key); }

    Optional<V> get(K const& key) const {
        return m_storage->map.get(key).map([](auto& x) -> V { return x; });
    }
    V& operator[](K const& key) { return m_storage->map.get(key).value(); }
    V const& operator[](K const& key) const { return m_storage->map.get(key).value(); }

    ErrorOr<DynamicArray<K>> keys() const
    {
        DynamicArray<K> keys = TRY(DynamicArray<K>::create_empty());
        TRY(keys.ensure_capacity(m_storage->map.size()));
        for (auto& it : m_storage->map) {
            MUST(keys.push(it.key));
        }
        return keys;
    }

    ErrorOr<void> ensure_capacity(size_t capacity)
    {
        TRY(m_storage->map.try_ensure_capacity(capacity));
        return {};
    }

    // FIXME: Remove this constructor once Jakt knows how to call Dictionary::create_empty()
    Dictionary()
        : m_storage(MUST(adopt_nonnull_ref_or_enomem(new (nothrow) Storage)))
    {
    }

    static ErrorOr<Dictionary> create_empty()
    {
        auto storage = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Storage));
        return Dictionary { move(storage) };
    }

    struct Entry {
        K key;
        V value;
    };
    static ErrorOr<Dictionary> create_with_entries(std::initializer_list<Entry> list)
    {
        auto dictionary = TRY(create_empty());
        TRY(dictionary.ensure_capacity(list.size()));
        for (auto& item : list)
            TRY(dictionary.set(item.key, item.value));
        return dictionary;
    }

    DictionaryIterator<K, V> iterator() const { return DictionaryIterator<K, V> { m_storage }; }

private:
    explicit Dictionary(NonnullRefPtr<Storage> storage)
        : m_storage(move(storage))
    {
    }

    NonnullRefPtr<Storage> m_storage;
};

}

namespace Jakt {
using JaktInternal::Dictionary;
using JaktInternal::DictionaryIterator;
}
