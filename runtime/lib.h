#pragma once

#include <AK/AllOf.h>
#include <AK/AnyOf.h>
#include <AK/Array.h>
#include <AK/Assertions.h>
#include <AK/Atomic.h>
#include <AK/Badge.h>
#include <AK/BitCast.h>
#include <AK/BuiltinWrappers.h>
#include <AK/ByteBuffer.h>
#include <AK/CharacterTypes.h>
#include <AK/Checked.h>
#include <AK/CheckedFormatString.h>
#include <AK/Concepts.h>
#include <AK/Debug.h>
#include <AK/Dictionary.h>
#include <AK/Error.h>
#include <AK/Find.h>
#include <AK/FixedPoint.h>
#include <AK/Format.h>
#include <AK/Forward.h>
#include <AK/Function.h>
#include <AK/GenericLexer.h>
#include <AK/HashFunctions.h>
#include <AK/HashTable.h>
#include <AK/IntegralMath.h>
#include <AK/IterationDecision.h>
#include <AK/Iterator.h>
#include <AK/LinearArray.h>
#include <AK/Math.h>
#include <AK/Memory.h>
#include <AK/Noncopyable.h>
#include <AK/NonnullOwnPtr.h>
#include <AK/NonnullRefPtr.h>
#include <AK/NumericLimits.h>
#include <AK/Optional.h>
#include <AK/OwnPtr.h>
#include <AK/Platform.h>
#include <AK/RefCounted.h>
#include <AK/RefPtr.h>
#include <AK/Result.h>
#include <AK/ReverseIterator.h>
#include <AK/ScopeGuard.h>
#include <AK/Set.h>
#include <AK/Span.h>
#include <AK/StdLibExtraDetails.h>
#include <AK/StdLibExtras.h>
#include <AK/String.h>
#include <AK/StringBuilder.h>
#include <AK/StringHash.h>
#include <AK/StringImpl.h>
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
#include <AK/Utf8View.h>
#include <AK/Variant.h>
#include <AK/Vector.h>
#include <AK/WeakPtr.h>
#include <AK/Weakable.h>
#include <AK/kmalloc.h>
#include <AK/kstdio.h>

#include <AK/Format.cpp>
#include <AK/GenericLexer.cpp>
#include <AK/String.cpp>
#include <AK/StringBuilder.cpp>
#include <AK/StringImpl.cpp>
#include <AK/StringUtils.cpp>
#include <AK/StringView.cpp>
#include <AK/Utf8View.cpp>
#include <AK/kmalloc.cpp>

#include <IO/File.h>

#include <IO/File.cpp>

#ifdef JAKT_CONTINUE_ON_PANIC
constexpr auto _jakt_continue_on_panic = true;
#else
constexpr auto _jakt_continue_on_panic = false;
#endif

using f32 = float;
using f64 = double;

template<typename T>
struct Range {
    using IndexType = T;
    T start {};
    T end {};
};

// FIXME: Remove this once we can call qualified functions like "String::number" directly from jakt
inline String runtime_helper_number_to_string(i64 number)
{
    return String::number(number);
}

ErrorOr<int> _jakt_main(Array<String>);

template<typename T>
inline constexpr T __arithmetic_shift_right(T value, size_t steps)
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
struct _JaktExplicitValue {
    _JaktExplicitValue(Value&& v)
        : value(move(v))
    {
    }
    _JaktExplicitValue(Value const& v)
        : value(v)
    {
    }

    Value value;
};

template<>
struct _JaktExplicitValue<void> {
    _JaktExplicitValue()
    {
    }
};

template<typename Value, typename Return>
struct _JaktExplicitValueOrReturn {
    template<typename U>
    _JaktExplicitValueOrReturn(_JaktExplicitValue<U>&& v)
        : value(_JaktExplicitValue<Value> { move(v.value) })
    {
    }

    _JaktExplicitValueOrReturn(_JaktExplicitValue<void>&&)
        : value(_JaktExplicitValue<void> { })
    {
    }

    template<typename U>
    _JaktExplicitValueOrReturn(U&& v) requires(!IsVoid<Return>)
        : value(Return { forward<U>(v) })
    {
    }

    _JaktExplicitValueOrReturn(void) requires(IsVoid<Return>)
        : value(Empty {})
    {
    }

    bool is_return() const {
        return value.template has<Conditional<IsVoid<Return>, Empty, Return>>();
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
            return move(value).template get<_JaktExplicitValue<Value>>().value;
    }

    Variant<Conditional<IsVoid<Return>, Empty, Return>, _JaktExplicitValue<Value>> value;
};

#define JAKT_RESOLVE_EXPLICIT_VALUE_OR_RETURN(x) ({ \
    auto&& _jakt_value = x;                         \
    if (_jakt_value.is_return())                    \
        return _jakt_value.release_return();        \
    _jakt_value.release_value();                    \
})

int main(int argc, char** argv)
{
    Array<String> args;
    for (int i = 0; i < argc; ++i) {
        MUST(args.push(argv[i]));
    }
    auto result = _jakt_main(move(args));
    if (result.is_error()) {
        warnln("Runtime error: {}", result.error());
        return 1;
    }
    return result.value();
}
