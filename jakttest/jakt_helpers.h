#include <Builtins/Array.h>
#include <Jakt/RefPtr.h>
#include <Jakt/Types.h>

namespace Jakt {
template<typename T>
T* get_array_unsafe_pointer(Array<T> array)
{
    return array.unsafe_data();
}

// naive implementation of a FIFO queue with a growable circular buffer.
// FIXME: needs tests for:
// - pop():
//  - if pushed something, must give a value.
//  - if empty, must give null optional.
//  - must not invoke any copy constructors.
//  - must not invoke any destructor.
//  - if invoked multiple times, it should return the rest of objects, one on
//  each call, unless the queue becomes empty.
// - push():
//  - does not overwrite valid objects.
//  - pushed items must come out of pop() in the same order they were introduced
//  - ^ also holds when the storage is extended.
//  - must not extend the storage if there are unused slots.
//  - must not invoke any copy constructors.
//  - must not invoke any destructor.
// - is_empty():
//  - must not be true if anything has been pushed.
//  - must be true when a pop() returns NullOptional
//  - must be true after a sequenced push() and pop() on a previously empty
//  state.
//  - must be true upon instancing the queue.
template<typename T>
class Queue {
    using Storage = JaktInternal::ArrayStorage<T>;
    NonnullRefPtr<Storage> m_storage;
    size_t m_read = 0;
    size_t m_write = 0;

    constexpr size_t available_slots() const noexcept
    {
        return m_write > m_read ? m_storage->size() - (m_write - m_read) : m_read - m_write;
    }

    explicit Queue(NonnullRefPtr<Storage> storage)
        : m_storage(move(storage))
        , m_read(0)
        , m_write(0)
    {
    }

public:
    static ErrorOr<Queue<T>> create_empty()
    {
        auto storage = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Storage));
        return Queue(move(storage));
    }
    static ErrorOr<NonnullRefPtr<Queue<T>>> create()
    {
        auto queue = TRY(create_empty());
        return adopt_nonnull_ref_or_enomem(new (nothrow) Queue(move(queue)));
    }
    ErrorOr<void> ensure_capacity(size_t capacity)
    {
        if (available_slots() >= capacity)
            return ErrorOr<void> {};
        return m_storage->ensure_capacity(capacity - available_slots());
    }
    constexpr size_t size() const noexcept
    {
        if (m_storage->is_empty())
            return 0;
        return m_write > m_read ? m_write - m_read : m_storage->size() - (m_read - m_write);
    }
    constexpr bool is_empty() const noexcept
    {
        return available_slots() == m_storage->size();
    }
    Optional<T> pop()
    {
        if (is_empty())
            return JaktInternal::NullOptional {};
        auto value = move(m_storage->at(m_read));
        // advance the read pointer to mark a slot as now invalid.
        m_read = (m_read + 1) % m_storage->size();

        return value;
    }

    ErrorOr<void> push(T value)
    {
        if (available_slots() == 0) {
            TRY(m_storage->push(value));
            // Rearrange the storage so that the new value is at m_write + 1.
            // We're effectively displacing everything in m_write..storage end
            // one slot to the right.
            for (size_t index = m_storage->size() - 1; index != m_write; --index) {
                swap(m_storage->at(index), value);
            }
            // since we've displaced everything one slot to the right, we'll
            // have to displace the read handle.
            m_read = (m_read + 1) % m_storage->size();
        } else {
            // NOTE: this *should* avoid calling the destructor of the invalid
            // slot.
            new (&m_storage->at(m_write)) T(move(value));
        }
        m_write = (m_write + 1) % m_storage->size();
        return ErrorOr<void> {};
    }
};

// FIXME: #1025 prevents this from being a static method.
template<typename T>
ErrorOr<Queue<T>> create_queue()
{
    return Queue<T>::create_empty();
}

template<typename T>
struct Formatter<Queue<T>> : Formatter<FormatString> {
    ErrorOr<void> format(FormatBuilder& builder, Queue<T> const& queue)
    {
        return Formatter<FormatString>::format(builder, "Queue(size={})", queue.size());
    }
};
}
