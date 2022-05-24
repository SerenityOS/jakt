#pragma once

#include <AK/Checked.h>
#include <AK/Error.h>
#include <AK/RefCounted.h>
#include <initializer_list>
#include <stdlib.h>

namespace JaktInternal {

template<typename T>
class ArrayStorage : public RefCounted<ArrayStorage<T>> {
public:
    ArrayStorage() { }

    bool is_empty() const { return m_size == 0; }
    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }

    ErrorOr<void> ensure_capacity(size_t capacity)
    {
        if (m_capacity >= capacity) {
            return {};
        }
        if (Checked<size_t>::multiplication_would_overflow(capacity, sizeof(T))) {
            return Error::from_errno(EOVERFLOW);
        }
        auto* new_elements = static_cast<T*>(malloc(capacity * sizeof(T)));
        if (!new_elements) {
            return Error::from_errno(ENOMEM);
        }
        for (size_t i = 0; i < m_size; ++i) {
            new (&new_elements[i]) T(move(m_elements[i]));
            m_elements[i].~T();
        }
        free(m_elements);
        m_elements = new_elements;
        m_capacity = capacity;
        return {};
    }

    ErrorOr<void> add_capacity(size_t capacity)
    {
        if (Checked<size_t>::addition_would_overflow(m_capacity, capacity)) {
            return Error::from_errno(EOVERFLOW);
        }
        TRY(ensure_capacity(m_capacity + capacity));
        return {};
    }

    ErrorOr<void> add_size(size_t size)
    {
        if (Checked<size_t>::addition_would_overflow(m_size, size)) {
            return Error::from_errno(EOVERFLOW);
        }
        TRY(resize(m_size + size));
        return {};
    }

    ErrorOr<void> resize(size_t size)
    {
        TRY(ensure_capacity(size));
        if (size > m_size) {
            for (size_t i = m_size; i < size; ++i) {
                new (&m_elements[i]) T();
            }
        } else {
            for (size_t i = size; i < m_size; ++i) {
                m_elements[i].~T();
            }
        }
        m_size = size;
        return {};
    }

    T const& at(size_t index) const
    {
        VERIFY(index < m_size);
        return m_elements[index];
    }

    T& at(size_t index)
    {
        VERIFY(index < m_size);
        return m_elements[index];
    }

    ErrorOr<void> push(T value)
    {
        TRY(ensure_capacity(m_size + 1));
        new (&m_elements[m_size]) T(move(value));
        ++m_size;
        return {};
    }

    T* unsafe_data() { return m_elements; }

private:
    size_t m_size { 0 };
    size_t m_capacity { 0 };
    T* m_elements { nullptr };
};

template<typename T>
class ArraySlice {
public:
    ArraySlice() = default;
    ArraySlice(ArraySlice const&) = default;
    ArraySlice(ArraySlice&&) = default;
    ArraySlice& operator=(ArraySlice const&) = default;
    ArraySlice& operator=(ArraySlice&&) = default;
    ~ArraySlice() = default;

    ArraySlice(NonnullRefPtr<ArrayStorage<T>> storage, size_t offset, size_t size)
        : m_storage(move(storage))
        , m_offset(offset)
        , m_size(size)
    {
        VERIFY(m_storage);
        VERIFY(m_offset < m_storage->size());
    }

    bool is_empty() const { return size() == 0; }
    size_t size() const
    {
        if (!m_storage)
            return 0;
        if (m_offset >= m_storage->size())
            return 0;
        size_t available_in_storage = m_storage->size() - m_offset;
        return max(m_size, available_in_storage);
    }

    T const& at(size_t index) const { return m_storage->at(m_offset + index); }
    T& at(size_t index) { return m_storage->at(m_offset + index); }
    T const& operator[](size_t index) const { return at(index); }
    T& operator[](size_t index) { return at(index); }

private:
    RefPtr<ArrayStorage<T>> m_storage;
    size_t m_offset { 0 };
    size_t m_size { 0 };
};

template<typename T>
class Array {
public:
    Array() = default;
    Array(Array const&) = default;
    Array(Array&&) = default;
    Array& operator=(Array const&) = default;
    Array& operator=(Array&&) = default;
    ~Array() = default;

    Array(std::initializer_list<T> list) requires(!IsLvalueReference<T>)
    {
        // FIXME: Should not MUST()
        MUST(ensure_capacity(list.size()));
        for (auto& item : list)
            MUST(push(item));
    }

    bool is_empty() const { return !m_storage || m_storage->is_empty(); }
    size_t size() const { return m_storage ? m_storage->size() : 0; }
    size_t capacity() const { return m_storage ? m_storage->capacity() : 0; }

    ErrorOr<void> push(T value)
    {
        auto* storage = TRY(ensure_storage());
        TRY(storage->push(move(value)));
        return {};
    }

    T const& at(size_t index) const
    {
        VERIFY(m_storage);
        return m_storage->at(index);
    }

    T& at(size_t index)
    {
        VERIFY(m_storage);
        return m_storage->at(index);
    }

    T const& operator[](size_t index) const { return at(index); }
    T& operator[](size_t index) { return at(index); }

    ErrorOr<void> ensure_capacity(size_t capacity)
    {
        auto* storage = TRY(ensure_storage());
        TRY(storage->ensure_capacity(capacity));
        return {};
    }

    ErrorOr<void> add_capacity(size_t capacity)
    {
        auto* storage = TRY(ensure_storage());
        TRY(storage->add_capacity(capacity));
        return {};
    }

    ErrorOr<void> add_size(size_t size)
    {
        auto* storage = TRY(ensure_storage());
        TRY(storage->add_size(size));
        return {};
    }

    ArraySlice<T> slice(size_t offset, size_t size)
    {
        if (!m_storage)
            return {};
        return { *m_storage, offset, size };
    }

    ErrorOr<void> resize(size_t size)
    {
        if (size != this->size()) {
            auto* storage = TRY(ensure_storage());
            TRY(storage->resize(size));
        }
        return {};
    }

    Optional<T> pop()
    {
        if (is_empty())
            return {};
        auto value = move(at(size() - 1));
        resize(size() - 1);
        return value;
    }

    static ErrorOr<Array> filled(size_t size, T value)
    {
        Array array;
        TRY(array.ensure_capacity(size));
        for (size_t i = 0; i < size; ++i) {
            TRY(array.push(value));
        }
        return array;
    }

    Array(Vector<T> const& ak_vector)
    {
        MUST(ensure_capacity(ak_vector.size()));
        for (auto value : ak_vector)
            MUST(push(move(value)));
    }

    T* unsafe_data()
    {
        if (!m_storage)
            return nullptr;
        return m_storage->unsafe_data();
    }

private:
    ErrorOr<ArrayStorage<T>*> ensure_storage()
    {
        if (!m_storage) {
            m_storage = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) ArrayStorage<T>));
        }
        return m_storage.ptr();
    }

    RefPtr<ArrayStorage<T>> m_storage;
};

}

using JaktInternal::Array;
