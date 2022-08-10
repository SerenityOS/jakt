#pragma once

#include <Builtins/Array.h>
#include <errno.h>

namespace JaktInternal {
using namespace Jakt;

template<typename T>
ErrorOr<String> Array<T>::join(String const& separator) const
{
    auto builder = MUST(StringBuilder::create());
    
    bool first = true;
    for (size_t i = 0; i<size(); ++i) {
        if (first)
            first = false;
        else
            TRY(builder.append(separator));
        TRY(builder.appendff("{}"sv, at(i)));
    }

    return TRY(builder.to_string());
}

template<typename T>
ErrorOr<String> ArraySlice<T>::join(String const& separator) const
{
    auto builder = MUST(StringBuilder::create());
    
    bool first = true;
    for (size_t i = 0; i<size(); ++i) {
        if (first)
            first = false;
        else
            TRY(builder.append(separator));
        TRY(builder.appendff("{}"sv, at(i)));
    }

    return TRY(builder.to_string());
}

}