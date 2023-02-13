/*
 * Copyright (c) 2022, Ali Mohammad Pur <mpfard@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/RedBlackTree.h>

namespace AK {
template<Integral K, typename V>
class IntervalMap {
public:
    IntervalMap()
        : m_tree(make<RedBlackTree<K, Optional<V>>>())
    {
    }

    ~IntervalMap() = default;

    IntervalMap(IntervalMap&& other)
        : m_tree(move(other.m_tree))
    {
    }

    enum class ShouldOverwrite {
        No,
        Yes,
    };

    void set(K start, K end, V value, ShouldOverwrite should_overwrite = ShouldOverwrite::Yes)
    {
        if (start > end)
            swap(start, end);

        Optional<V> final_value;
        if (should_overwrite == ShouldOverwrite::Yes) {
            final_value = clear_range(start, end);
        } else {
            auto it = m_tree->find_largest_not_above_iterator(end);
            if (!it.is_end())
                final_value = *it;
        }

        m_tree->insert(start, move(value));
        m_tree->insert(end, move(final_value));
    }

    Optional<V> clear_range(K start, K end)
    {
        if (start > end)
            swap(start, end);

        auto it = m_tree->find_smallest_not_below_iterator(start);
        Optional<V> final_value;
        while (it != m_tree->end() && it->start <= end) {
            auto current = it.key();
            ++it;
            final_value = move(m_tree->find(current));
            m_tree->remove(current);
        }
        return final_value;
    }

    Optional<V> const& get(K key) const
    {
        auto it = m_tree->find_largest_not_above_iterator(key);
        if (it.is_end())
            return {};
        return *it;
    }

    Optional<V>& get(K key)
    {
        return const_cast<Optional<V>&>(const_cast<IntervalMap const&>(*this).get(key));
    }

    void move_range(K start, K end, K new_start)
    {
        if (start > end)
            swap(start, end);

        auto it = m_tree->find_smallest_not_below_iterator(start);
        if (it.is_end())
            return;

        Vector<K> keys;
        Vector<Optional<V>> values;
        while (it != m_tree->end() && it->start <= end) {
            keys.append(it.key());
            values.append(move(m_tree->find(it.key())));
            ++it;
        }

        for (auto& key : keys)
            m_tree->remove(key);

        for (size_t i = 0; i < keys.size(); ++i)
            m_tree->insert(keys[i] + new_start - start, move(values[i]));
    }

    Optional<V> const& operator[](K key) const { return get(key); }
    Optional<V>& operator[](K key) { return get(key); }

    void clear()
    {
        m_tree->clear();
    }

    bool is_empty() const { return m_tree->is_empty(); }

    template<typename R, CallableAs<R(K, K, V const&)> Callback>
    typename ErrorOr<R>::UnwrappedIfErrorOr for_each_interval_intersecting(K start, K end, Callback callback) const
        requires(!IsSpecializationOf<R, ErrorOr> || IsSame<typename R::ValueType, IterationDecision> || IsSame<typename R::ValueType, void>)
    {
        if (start > end)
            swap(start, end);

        auto it = m_tree->find_smallest_not_below_iterator(start);
        while (it != m_tree->end() && it->start <= end) {
            auto current = it.key();
            ++it;
            if (current > end)
                break;
            auto result = callback(current, it.key(), *it);
            if constexpr (IsSpecializationOf<RemoveCVReference<decltype(result)>, ErrorOr>) {
                if (result.is_error())
                    return result;

                if constexpr (IsSame<typename R::ValueType, IterationDecision>) {
                    if (result.value() == IterationDecision::Break)
                        break;
                }
            } else if constexpr (IsSame<RemoveCVReference<decltype(result)>, IterationDecision>) {
                if (result == IterationDecision::Break)
                    break;
            }
        }

        return {};
    }

private:
    NonnullOwnPtr<RedBlackTree<K, Optional<V>>> m_tree;
};
}

using AK::IntervalMap;
