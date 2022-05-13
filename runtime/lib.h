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
#include <AK/Error.h>
#include <AK/Find.h>
#include <AK/FixedPoint.h>
#include <AK/Format.h>
#include <AK/Forward.h>
#include <AK/Function.h>
#include <AK/GenericLexer.h>
#include <AK/HashFunctions.h>
#include <AK/HashMap.h>
#include <AK/HashTable.h>
#include <AK/IntegralMath.h>
#include <AK/IterationDecision.h>
#include <AK/Iterator.h>
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
#include <AK/RefVector.h>
#include <AK/Result.h>
#include <AK/ReverseIterator.h>
#include <AK/ScopeGuard.h>
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

using f32 = float;
using f64 = double;

// FIXME: Remove this once we can call qualified functions like "String::number" directly from jakt
inline String runtime_helper_number_to_string(i64 number)
{
    return String::number(number);
}

int __jakt_main(RefVector<String>);

int main(int argc, char** argv)
{
    RefVector<String> args;
    for (int i = 0; i < argc; ++i) {
        args.append(argv[i]);
    }
    return __jakt_main(move(args));
}
