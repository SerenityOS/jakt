/*
 * Copyright (c) 2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Jakt/Optional.h>
#include <Jakt/Try.h>
#include <Jakt/Variant.h>

#if defined(__serenity__) && defined(KERNEL)
#    include <LibC/errno_codes.h>
#else
#    include <errno.h>
#    include <string.h>
#endif

namespace Jakt {

class Error {
public:
    static Error from_errno(int code) { return Error(code); }

    bool is_errno() const { return m_code != 0; }

    int code() const { return m_code; }

protected:
    Error(int code)
        : m_code(code)
    {
    }

private:
    int m_code { 0 };
    bool m_syscall { false };
};

template<typename T, typename ErrorType>
class [[nodiscard]] ErrorOr final : public Variant<T, ErrorType> {
public:
    using Variant<T, ErrorType>::Variant;

    template<typename U>
    ALWAYS_INLINE ErrorOr(U&& value) requires(!IsSame<RemoveCVReference<U>, ErrorOr<T>>)
        : Variant<T, ErrorType>(forward<U>(value))
    {
    }

#ifdef __serenity__
    ErrorOr(ErrnoCode code)
        : Variant<T, ErrorType>(Error::from_errno(code))
    {
    }
#endif

    T& value()
    {
        return this->template get<T>();
    }
    T const& value() const { return this->template get<T>(); }
    ErrorType& error() { return this->template get<ErrorType>(); }
    ErrorType const& error() const { return this->template get<ErrorType>(); }

    bool is_error() const { return this->template has<ErrorType>(); }

    T release_value() { return move(value()); }
    ErrorType release_error() { return move(error()); }

    T release_value_but_fixme_should_propagate_errors()
    {
        VERIFY(!is_error());
        return release_value();
    }
};

// Partial specialization for void value type
template<typename ErrorType>
class [[nodiscard]] ErrorOr<void, ErrorType> {
public:
    ErrorOr(ErrorType error)
        : m_error(move(error))
    {
    }

#ifdef __serenity__
    ErrorOr(ErrnoCode code)
        : m_error(Error::from_errno(code))
    {
    }
#endif

    ErrorOr() = default;
    ErrorOr(ErrorOr&& other) = default;
    ErrorOr(ErrorOr const& other) = default;
    ~ErrorOr() = default;

    ErrorOr& operator=(ErrorOr&& other) = default;
    ErrorOr& operator=(ErrorOr const& other) = default;

    ErrorType& error() { return m_error.value(); }
    bool is_error() const { return m_error.has_value(); }
    ErrorType release_error() { return m_error.release_value(); }
    void release_value() { }

private:
    Optional<ErrorType> m_error;
};

}
