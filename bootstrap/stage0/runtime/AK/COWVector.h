/*
 * Copyright (c) 2022, Ali Mohammad Pur <mpfard@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Concepts.h>
#include <AK/RefCounted.h>
#include <AK/RefPtr.h>
#include <AK/Vector.h>

namespace AK {
template<typename T>
class COWVector {
    struct Detail : RefCounted<Detail> {
        Vector<T> m_members;
    };

public:
    COWVector()
        : m_detail(make_ref_counted<Detail>())
    {
    }

    COWVector(COWVector const&) = default;
    COWVector(COWVector&&) = default;

    COWVector(Vector<T>&& data)
        : m_detail(make_ref_counted<Detail>())
    {
        m_detail->m_members = move(data);
    }

    COWVector(Vector<T> const& data)
        : m_detail(make_ref_counted<Detail>())
    {
        m_detail->m_members = data;
    }

    COWVector& operator=(COWVector const&) = default;
    COWVector& operator=(COWVector&&) = default;

    Vector<T> release() &&
    {
        if (m_detail->ref_count() == 1)
            return exchange(m_detail->m_members, Vector<T>());

        return m_detail->m_members;
    }

    void append(T const& value)
    {
        return append(T { value });
    }

    void append(T&& value)
    {
        copy();
        m_detail->m_members.append(move(value));
    }

    void prepend(T const& value)
    {
        return prepend(T { value });
    }

    void prepend(T&& value)
    {
        copy();
        m_detail->m_members.prepend(move(value));
    }

    void extend(Vector<T> const& other)
    {
        copy();
        m_detail->m_members.extend(other);
    }

    void extend(Vector<T>&& other)
    {
        copy();
        m_detail->m_members.extend(move(other));
    }

    void resize(size_t size)
    {
        copy();
        m_detail->m_members.resize(size);
    }

    void ensure_capacity(size_t capacity)
    {
        if (m_detail->m_members.capacity() >= capacity)
            return;

        copy();
        m_detail->m_members.ensure_capacity(capacity);
    }

    template<typename... Args>
    void empend(Args&&... args)
    {
        copy();
        m_detail->m_members.empend(forward<Args>(args)...);
    }

    void clear()
    {
        if (m_detail->ref_count() > 1)
            m_detail = make_ref_counted<Detail>();
        else
            m_detail->m_members.clear();
    }

    T& at(size_t index)
    {
        // We're handing out a mutable reference, so make sure we own the data exclusively.
        copy();
        return m_detail->m_members.at(index);
    }

    T const& at(size_t index) const
    {
        return m_detail->m_members.at(index);
    }

    T& operator[](size_t index)
    {
        // We're handing out a mutable reference, so make sure we own the data exclusively.
        copy();
        return m_detail->m_members[index];
    }

    T const& operator[](size_t index) const
    {
        return m_detail->m_members[index];
    }

    size_t capacity() const
    {
        return m_detail->m_members.capacity();
    }

    size_t size() const
    {
        return m_detail->m_members.size();
    }

    bool is_empty() const
    {
        return m_detail->m_members.is_empty();
    }

    T const& first() const
    {
        return m_detail->m_members.first();
    }

    T const& last() const
    {
        return m_detail->m_members.last();
    }

private:
    void copy()
    {
        if (m_detail->ref_count() <= 1)
            return;
        auto new_detail = make_ref_counted<Detail>();
        new_detail->m_members = m_detail->m_members;
        m_detail = new_detail;
    }

    NonnullRefPtr<Detail> m_detail;
};
}

using AK::COWVector;
