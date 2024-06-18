#pragma once

#include <Jakt/AKIntegration.h>

#include <AK/AllOf.h>
#include <AK/Array.h>
#include <AK/Assertions.h>
#include <AK/Atomic.h>
#include <AK/BitCast.h>
#include <AK/CharacterTypes.h>
#include <AK/Checked.h>
#include <AK/Concepts.h>
#include <AK/Debug.h>
#include <AK/Error.h>
#include <AK/Find.h>
#include <AK/Format.h>
#include <AK/Forward.h>
#include <AK/Function.h>
#include <AK/GenericLexer.h>
#include <AK/HashFunctions.h>
#include <AK/HashTable.h>
#include <AK/Iterator.h>
#include <AK/Memory.h>
#include <AK/Noncopyable.h>
#include <AK/NonnullRefPtr.h>
#include <AK/NumericLimits.h>
#include <AK/Optional.h>
#include <AK/Platform.h>
#include <AK/RefCounted.h>
#include <AK/RefPtr.h>
#include <AK/ScopeGuard.h>
#include <AK/Span.h>
#include <AK/StdLibExtraDetails.h>
#include <AK/StdLibExtras.h>
#include <AK/String.h>
#include <AK/StringBuilder.h>
#include <AK/StringHash.h>
#include <AK/StringUtils.h>
#include <AK/StringView.h>
#include <AK/Traits.h>
#include <AK/Try.h>
#include <AK/Tuple.h>
#include <AK/TypeCasts.h>
#include <AK/TypeList.h>
#include <AK/TypedTransfer.h>
#include <AK/Types.h>
#include <AK/UnicodeUtils.h>
#include <AK/Variant.h>
#include <AK/WeakPtr.h>
#include <AK/Weakable.h>
#include <AK/kmalloc.h>
#include <AK/kstdio.h>
#include <Jakt/ControlFlow.h>
#include <Jakt/PrettyPrint.h>

namespace JaktInternal {
template<typename T>
class Set;
}

#include <Builtins/Dictionary.h>
#include <Builtins/DynamicArray.h>
#include <Builtins/Set.h>
#include <Jakt/ByteString.h>
#include <Jakt/ByteStringBuilder.h>

#include <IO/File.h>

#include <Jakt/Operators.h>

#include <math.h>

namespace JaktInternal {

#ifdef JAKT_CONTINUE_ON_PANIC
constexpr auto continue_on_panic = true;
#else
constexpr auto continue_on_panic = false;
#endif

using OptionalNone = Jakt::OptionalNone;

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
inline constexpr T unchecked_add(T value, IdentityType<T> other)
{
    return value + other;
}

template<typename T>
inline constexpr T unchecked_sub(T value, IdentityType<T> other)
{
    return value - other;
}

template<typename T>
inline constexpr T unchecked_mul(T value, IdentityType<T> other)
{
    return value * other;
}

template<typename T>
inline constexpr T unchecked_div(T value, IdentityType<T> other)
{
    return value / other;
}

template<typename T>
inline constexpr T checked_add(T value, IdentityType<T> other)
{
    Checked<T> checked = value;
    checked += other;
    if (checked.has_overflow())
        panic(MUST(String::formatted("Overflow in checked addition '{} + {}'", value, other)));
    return checked.value_unchecked();
}

template<typename T>
inline constexpr T checked_sub(T value, IdentityType<T> other)
{
    Checked<T> checked = value;
    checked -= other;
    if (checked.has_overflow())
        panic(MUST(String::formatted("Overflow in checked subtraction '{} - {}'", value, other)));
    return checked.value_unchecked();
}

template<typename T>
inline constexpr T checked_mul(T value, IdentityType<T> other)
{
    Checked<T> checked = value;
    checked *= other;
    if (checked.has_overflow())
        panic(MUST(String::formatted("Overflow in checked multiplication '{} * {}'", value, other)));
    return checked.value_unchecked();
}

template<typename T>
inline constexpr T checked_div(T value, IdentityType<T> other)
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
inline constexpr T checked_mod(T value, IdentityType<T> other)
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

template<typename T>
ALWAYS_INLINE auto assert_type(T&& input) -> decltype(input)
{
    return forward<T>(input);
}

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

template<typename OutputType, typename InputType>
ALWAYS_INLINE Optional<OutputType> fallible_float_cast(InputType input)
{
    if constexpr (IsEnum<InputType>) {
        return fallible_float_cast<OutputType>(to_underlying(input));
    } else {
        static_assert(IsFloatingPoint<InputType> || IsFloatingPoint<OutputType>);
        // FIXME: Check whether input is representable as OutputType:
        //        - What should happen if input isn't a whole number? (truncate or None?)
        //        - What should happen if input is not exactly representable as OutputType? (None or closest representable value?)
        if constexpr (IsFloatingPoint<InputType> && IsIntegral<OutputType>) {
            if (isnan(input) || isinf(input))
                return {};
            // FIXME: Fractionals...?
        } else if constexpr (IsIntegral<InputType> && IsFloatingPoint<OutputType>) {
            // FIXME: Numbers that are not exactly representable?
        } else if constexpr (IsFloatingPoint<InputType> && IsFloatingPoint<OutputType>) {
            // FIXME: Numbers that are not exactly representable?
        }

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
ALWAYS_INLINE constexpr OutputType infallible_enum_cast(InputType input)
{
    return static_cast<OutputType>(infallible_integer_cast<UnderlyingType<OutputType>>(input));
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE constexpr OutputType infallible_float_cast(InputType input)
{
    if constexpr (IsEnum<InputType>) {
        return infallible_float_cast<OutputType>(to_underlying(input));
    } else {
        static_assert(IsFloatingPoint<InputType> || IsFloatingPoint<OutputType>);

        // FIXME: Check whether input is representable as OutputType:
        //        - What should happen if input isn't a whole number? (truncate or None?)
        //        - What should happen if input is not exactly representable as OutputType? (None or closest representable value?)
        if constexpr (IsFloatingPoint<InputType> && IsIntegral<OutputType>) {
            if (is_constant_evaluated()) {
                if (isnan(input) || isinf(input))
                    compiletime_fail("Invalid floating point to integer cast");
            } else {
                VERIFY(!isnan(input) && !isinf(input));
            }
            // FIXME: Fractionals...?
        } else if constexpr (IsIntegral<InputType> && IsFloatingPoint<OutputType>) {
            // FIXME: Numbers that are not exactly representable?
        } else if constexpr (IsFloatingPoint<InputType> && IsFloatingPoint<OutputType>) {
            // FIXME: Numbers that are not exactly representable?
        }

        return static_cast<OutputType>(input);
    }
}

template<AK::Concepts::SpecializationOf<AK::NonnullRefPtr> T, AK::Concepts::SpecializationOf<AK::NonnullRefPtr> U>
inline Optional<T> fallible_class_cast(U const& ptr)
{
    if (!is<typename T::ElementType>(*ptr))
        return Optional<T> {};
    return T(static_cast<typename T::ElementType const&>(*ptr));
}

template<AK::Concepts::SpecializationOf<AK::NonnullRefPtr> T, AK::Concepts::SpecializationOf<AK::NonnullRefPtr> U>
inline T infallible_class_cast(U const& ptr)
{
    VERIFY(is<typename T::ElementType>(*ptr));
    return T(static_cast<typename T::ElementType const&>(*ptr));
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

inline ErrorOr<ByteString> ___jakt_get_target_triple_string()
{
#ifdef __JAKT_BUILD_TARGET
    return ByteString(__JAKT_BUILD_TARGET sv);
#else
// Pure guesswork.
#    if defined(_WIN64) // X86_64 or ARM64
#        if defined(_M_ARM64)
    return ByteString("arm64-unknown-windows-unknown"sv);
#        else
    return ByteString("amd64-unknown-windows-unknown"sv);
#        endif
#    elif defined(_WIN32)
    return ByteString("i686-unknown-windows-unknown"sv);
#    elif defined(__linux__)
    return ByteString("x86_64-unknown-linux-unknown"sv);
#    elif defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    return ByteString("x86_64-unknown-bsd-unknown"sv);
#    elif defined(__APPLE__)
#        if defined(__arm64__)
    return ByteString("arm64-unknown-darwin-unknown"sv);
#        else
    return ByteString("x86_64-unknown-darwin-unknown"sv);
#        endif
#    elif defined(__serenity__)
#        if defined(__i686__)
    return ByteString("i686-unknown-serenityos-unknown"sv);
#        elif defined(__x86_64__)
    return ByteString("x86_64-unknown-serenityos-unknown"sv);
#        elif defined(__aarch64__)
    return ByteString("aarch64-unknown-serenityos-unknown"sv);
#        else
    return ByteString("unknown-unknown-serenityos-unknown"sv);
#        endif
#    elif defined(__unix__)
    return ByteString("x86_64-unknown-unix-unknown"sv);
#    else
    return ByteString("unknown-unknown-unknown-unknown"sv);
#    endif
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

namespace Detail {
template<auto... Xs>
struct DependentValue { };

template<typename T>
struct UnderlyingClassTypeOf {
    using Type = T;
};

template<typename T>
struct UnderlyingClassTypeOf<NonnullRefPtr<T>> {
    using Type = T;
};
}

template<typename T, auto Reason>
T fail_comptime_call()
{
    static_assert(DependentFalse<Detail::DependentValue<Reason>>);
    return declval<T>();
}

template<typename T>
using UnderlyingClassTypeOf = typename Detail::UnderlyingClassTypeOf<RemoveCVReference<T>>::Type;
}

namespace Jakt {
using JaktInternal::___jakt_get_target_triple_string;
using JaktInternal::abort;
using JaktInternal::as_saturated;
using JaktInternal::as_truncated;
using JaktInternal::assert_type;
using JaktInternal::fallible_class_cast;
using JaktInternal::fallible_float_cast;
using JaktInternal::fallible_integer_cast;
using JaktInternal::infallible_class_cast;
using JaktInternal::infallible_enum_cast;
using JaktInternal::infallible_float_cast;
using JaktInternal::infallible_integer_cast;
using JaktInternal::Range;
using JaktInternal::unchecked_add;
using JaktInternal::unchecked_div;
using JaktInternal::unchecked_mul;
using JaktInternal::unchecked_sub;
using JaktInternal::UnderlyingClassTypeOf;
}

// We place main in a separate namespace to ensure it has access to the same identifiers as other functions
namespace Jakt {
ErrorOr<int> main(DynamicArray<ByteString>);
}
