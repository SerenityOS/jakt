#pragma once

#include <Jakt/AllOf.h>
#include <Jakt/Assertions.h>
#include <Jakt/Atomic.h>
#include <Jakt/BitCast.h>
#include <Jakt/CharacterTypes.h>
#include <Jakt/Checked.h>
#include <Jakt/Concepts.h>
#include <Jakt/Debug.h>
#include <Jakt/Error.h>
#include <Jakt/Find.h>
#include <Jakt/Format.h>
#include <Jakt/Forward.h>
#include <Jakt/Function.h>
#include <Jakt/GenericLexer.h>
#include <Jakt/HashFunctions.h>
#include <Jakt/HashTable.h>
#include <Jakt/Iterator.h>
#include <Jakt/LinearArray.h>
#include <Jakt/Memory.h>
#include <Jakt/Noncopyable.h>
#include <Jakt/NonnullRefPtr.h>
#include <Jakt/NumericLimits.h>
#include <Jakt/Optional.h>
#include <Jakt/Platform.h>
#include <Jakt/PrettyPrint.h>
#include <Jakt/RefCounted.h>
#include <Jakt/RefPtr.h>
#include <Jakt/ScopeGuard.h>
#include <Jakt/Span.h>
#include <Jakt/StdLibExtraDetails.h>
#include <Jakt/StdLibExtras.h>
#include <Jakt/String.h>
#include <Jakt/StringBuilder.h>
#include <Jakt/StringHash.h>
#include <Jakt/StringUtils.h>
#include <Jakt/StringView.h>
#include <Jakt/Traits.h>
#include <Jakt/Try.h>
#include <Jakt/Tuple.h>
#include <Jakt/TypeCasts.h>
#include <Jakt/TypeList.h>
#include <Jakt/TypedTransfer.h>
#include <Jakt/Types.h>
#include <Jakt/UnicodeUtils.h>
#include <Jakt/Variant.h>
#include <Jakt/WeakPtr.h>
#include <Jakt/Weakable.h>
#include <Jakt/kmalloc.h>
#include <Jakt/kstdio.h>

namespace JaktInternal {
template<typename T>
class Set;
}

#include <Builtins/Array.h>
#include <Builtins/Dictionary.h>
#include <Builtins/Set.h>

#include <IO/File.h>

using f32 = float;
using f64 = double;

namespace JaktInternal {

#ifdef JAKT_CONTINUE_ON_PANIC
constexpr auto continue_on_panic = true;
#else
constexpr auto continue_on_panic = false;
#endif

using OptionalNone = Jakt::NullOptional;

inline void panic(StringView message)
{
    warnln("Panic: {}", message);
    if (continue_on_panic)
        return;
    VERIFY_NOT_REACHED();
}

[[noreturn]] inline void abort()
{
    ::abort();
}

template<typename T>
inline constexpr T unchecked_add(T value, T other)
{
    return value + other;
}

template<typename T>
inline constexpr T unchecked_mul(T value, T other)
{
    return value * other;
}

template<typename T>
inline constexpr T checked_add(T value, T other)
{
    Checked<T> checked = value;
    checked += other;
    if (checked.has_overflow())
        panic(MUST(String::formatted("Overflow in checked addition '{} + {}'", value, other)));
    return checked.value_unchecked();
}

template<typename T>
inline constexpr T checked_sub(T value, T other)
{
    Checked<T> checked = value;
    checked -= other;
    if (checked.has_overflow())
        panic(MUST(String::formatted("Overflow in checked subtraction '{} - {}'", value, other)));
    return checked.value_unchecked();
}

template<typename T>
inline constexpr T checked_mul(T value, T other)
{
    Checked<T> checked = value;
    checked *= other;
    if (checked.has_overflow())
        panic(MUST(String::formatted("Overflow in checked multiplication '{} * {}'", value, other)));
    return checked.value_unchecked();
}

template<typename T>
inline constexpr T checked_div(T value, T other)
{
    Checked<T> checked = value;
    checked /= other;
    if (checked.has_overflow()) {
        if (other == 0)
            panic(MUST(String::formatted("Division by zero in checked division '{} / {}'", value, other)));
        else
            panic(MUST(String::formatted("Overflow in checked division '{} / {}'", value, other)));
    }
    return checked.value_unchecked();
}

template<typename T>
inline constexpr T checked_mod(T value, T other)
{
    Checked<T> checked = value;
    checked %= other;
    if (checked.has_overflow()) {
        if (other == 0)
            panic(MUST(String::formatted("Division by zero in checked modulo '{} % {}'", value, other)));
        else
            panic(MUST(String::formatted("Overflow in checked modulo '{} % {}'", value, other)));
    }
    return checked.value_unchecked();
}

template<typename T>
inline constexpr T arithmetic_shift_right(T value, size_t steps)
{
    if constexpr (IsSigned<T>) {
        if constexpr (sizeof(T) == 1) {
            auto sign = (value & 0x80);
            // 8-bit variant
            return ((value >> steps) | sign);
        } else if constexpr (sizeof(T) == 2) {
            auto sign = (value & 0x8000);
            // 16-bit variant
            return ((value >> steps) | sign);
        } else if constexpr (sizeof(T) == 4) {
            auto sign = (value & 0x80000000);
            // 32-bit variant
            return ((value >> steps) | sign);
        } else if constexpr (sizeof(T) == 8) {
            auto sign = (value & 0x8000000000000000);
            // 64-bit variant
            return ((value >> steps) | sign);
        }
    } else {
        return (value >> steps);
    }
}

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

    ExplicitValueOrControlFlow(void) requires(IsVoid<Return>)
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
            return move(value).template get<Return>();
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

template<typename OutputType, typename InputType>
ALWAYS_INLINE Optional<OutputType> fallible_integer_cast(InputType input)
{
    if constexpr (IsEnum<InputType>) {
        return fallible_integer_cast<OutputType>(to_underlying(input));
    } else {
        static_assert(IsIntegral<InputType>);
        if (!Jakt::is_within_range<OutputType>(input))
            return {};
        return static_cast<OutputType>(input);
    }
}

template<typename... Ts>
void compiletime_fail(Ts...) { }

template<typename OutputType, typename InputType>
ALWAYS_INLINE constexpr OutputType infallible_integer_cast(InputType input)
{
    if constexpr (IsEnum<InputType>) {
        return infallible_integer_cast<OutputType>(to_underlying(input));
    } else {
        static_assert(IsIntegral<InputType>);
        if (is_constant_evaluated()) {
            if (!Jakt::is_within_range<OutputType>(input))
                compiletime_fail("Integer cast out of range");
        } else {
            VERIFY(Jakt::is_within_range<OutputType>(input));
        }
        return static_cast<OutputType>(input);
    }
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE constexpr OutputType as_saturated(InputType input)
{
    if constexpr (IsEnum<InputType>) {
        return as_saturated<OutputType>(to_underlying(input));
    } else {
        static_assert(IsIntegral<InputType>);
        if (!Jakt::is_within_range<OutputType>(input)) {
            if constexpr (IsSigned<InputType>) {
                if (input < 0)
                    return NumericLimits<OutputType>::min();
            }
            return NumericLimits<OutputType>::max();
        }
        return static_cast<OutputType>(input);
    }
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE constexpr OutputType as_truncated(InputType input)
{
    if constexpr (IsEnum<InputType>) {
        return as_truncated<OutputType>(to_underlying(input));
    } else {
        static_assert(IsIntegral<InputType>);
        return static_cast<OutputType>(input);
    }
}

inline String ___jakt_get_target_triple_string()
{
#ifdef __JAKT_BUILD_TARGET
    return String(__JAKT_BUILD_TARGET);
#else
// Pure guesswork.
#   if defined(_WIN32)
    return String("i686-pc-windows-msvc");
#   elif defined(_WIN64)
    return String("x86_64-pc-windows-msvc");
#   elif defined(__linux__)
    return String("x86_64-pc-linux-gnu");
#   elif defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    return String("x86_64-pc-bsd-unknown");
#   elif defined(__APPLE__)
    return String("x86_64-apple-darwin-unknown");
#   elif defined(__unix__)
    return String("x86_64-pc-unix-unknown");
#   elif defined(__serenity__)
    return String("unknown-pc-serenity-serenity");
#   else
    return String("unknown-unknown-unknown-unknown");
#   endif
#endif
}

template<typename T>
struct _RemoveRefPtr {
    using Type = T;
};

template<typename T>
struct _RemoveRefPtr<NonnullRefPtr<T>> {
    using Type = T;
};

template<typename T>
using RemoveRefPtr = typename _RemoveRefPtr<RemoveCVReference<T>>::Type;

template<typename T>
ALWAYS_INLINE decltype(auto) deref_if_ref_pointer(T&& value)
{
    if constexpr (IsSpecializationOf<RemoveCVReference<T>, NonnullRefPtr>)
        return static_cast<CopyConst<RemoveReference<T>, RemoveRefPtr<T>>&>(*value);
    else
        return static_cast<Conditional<IsRvalueReference<T>, RemoveReference<T>, T>>(value);
}

}

namespace Jakt {
using JaktInternal::abort;
using JaktInternal::as_saturated;
using JaktInternal::as_truncated;
using JaktInternal::fallible_integer_cast;
using JaktInternal::infallible_integer_cast;
using JaktInternal::Range;
using JaktInternal::unchecked_add;
using JaktInternal::unchecked_mul;
using JaktInternal::___jakt_get_target_triple_string;
}

// We place main in a separate namespace to ensure it has access to the same identifiers as other functions
namespace Jakt {
ErrorOr<int> main(Array<String>);
}
