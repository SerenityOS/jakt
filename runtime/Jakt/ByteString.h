#pragma once

#include <Jakt/AKIntegration.h>

#include <AK/CheckedFormatString.h>
#include <AK/ByteString.h>
#include <AK/Utf8View.h>

namespace Jakt {
template<typename... Ts>
inline ByteString __jakt_format(CheckedFormatString<Ts...> fmt, Ts const&... args)
{
    return ByteString::formatted(fmt.view(), args...);
}

inline ByteString operator+(ByteString const& a, ByteString const& b)
{
    return ByteString::formatted("{}{}", a, b);
}

inline ByteString& operator+=(ByteString& a, ByteString const& b)
{
    auto result = ByteString::formatted("{}{}", a, b);
    *bit_cast<RefPtr<StringImpl const>*>(&a) = result.impl(); // I'm sorry.
    return a;
}
}
