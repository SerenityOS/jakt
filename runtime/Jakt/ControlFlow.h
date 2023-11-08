/*
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

namespace JaktInternal {
template<typename T>
struct ExtractThrownReturnType {
    using Type = T;
};
template<typename T, typename E>
struct ExtractThrownReturnType<Jakt::ErrorOr<T, E>> {
    using Type = T;
};

template<typename T>
static inline constexpr auto IsThrowsyVoid = Jakt::Detail::IsVoid<T> || Jakt::Detail::IsVoid<typename ExtractThrownReturnType<T>::Type>;
}

namespace Jakt {

template<typename Value>
struct ExplicitValue {
    ExplicitValue(Value&& v)
        : value(move(v))
    {
    }
    ExplicitValue(Value const& v)
        : value(v)
    {
    }

    Value value;
};

template<>
struct ExplicitValue<void> {
    ExplicitValue()
    {
    }
};

struct LoopBreak { };
struct LoopContinue { };

template<typename Value, typename Return>
struct ExplicitValueOrControlFlow {
    template<typename U>
    ExplicitValueOrControlFlow(ExplicitValue<U>&& v) requires(!IsVoid<Value> && !IsVoid<U>)
        : value(ExplicitValue<Value> { move(v.value) })
    {
    }

    ExplicitValueOrControlFlow(ExplicitValue<void>&&) requires(IsVoid<Value>)
        : value(ExplicitValue<void> {})
    {
    }

    template<typename U>
    ExplicitValueOrControlFlow(U&& v) requires(!IsVoid<Return> && !IsSpecializationOf<U, ExplicitValue>)
        : value(Return { forward<U>(v) })
    {
    }

    ExplicitValueOrControlFlow(void) requires(JaktInternal::IsThrowsyVoid<Return>)
        : value(Empty {})
    {
    }

    ExplicitValueOrControlFlow(LoopContinue)
        : value(LoopContinue {})
    {
    }

    ExplicitValueOrControlFlow(LoopBreak)
        : value(LoopBreak {})
    {
    }

    bool is_return() const
    {
        return value.template has<Conditional<IsVoid<Return>, Empty, Return>>();
    }

    bool is_loop_break() const
    {
        return value.template has<LoopBreak>();
    }

    bool is_loop_continue() const
    {
        return value.template has<LoopContinue>();
    }

    Return release_return()
    {
        if constexpr (IsVoid<Return>)
            return;
        else
            return move(move(value).template get<Return>());
    }

    Value release_value()
    {
        if constexpr (IsVoid<Value>)
            return;
        else
            return move(move(value).template get<ExplicitValue<Value>>().value);
    }

    Variant<Conditional<IsVoid<Return>, Empty, Return>, ExplicitValue<Value>, LoopContinue, LoopBreak> value;
};

#define JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(x) ({ \
    auto&& _jakt_value = x;                                           \
    if (_jakt_value.is_return())                                      \
        return _jakt_value.release_return();                          \
    _jakt_value.release_value();                                      \
})

// XXX: `break` might not work if codegen is inside a switch block.
#define JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(x) ({ \
    auto&& _jakt_value = x;                                       \
    if (_jakt_value.is_return())                                  \
        return _jakt_value.release_return();                      \
    else if (_jakt_value.is_loop_break())                         \
        break;                                                    \
    else if (_jakt_value.is_loop_continue())                      \
        continue;                                                 \
    _jakt_value.release_value();                                  \
})

#define JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(x) ({ \
    auto&& _jakt_value = x;                                                    \
    if (_jakt_value.is_return())                                               \
        return _jakt_value.release_return();                                   \
    else if (_jakt_value.is_loop_break())                                      \
        return JaktInternal::LoopBreak {};                                     \
    else if (_jakt_value.is_loop_continue())                                   \
        return JaktInternal::LoopContinue {};                                  \
    _jakt_value.release_value();                                               \
})
}

