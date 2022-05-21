#pragma once

#include <AK/Assertions.h>
#include <AK/Concepts.h>
#include <AK/NumericLimits.h>

template<Integral T>
T __checked_add(T lhs, T rhs)
{
    if ((rhs > 0) && (lhs > NumericLimits<T>::max() - rhs))
        VERIFY(false && "Integer overflow");
    if ((rhs < 0) && (lhs < NumericLimits<T>::min() - rhs))
        VERIFY(false && "Integer underflow");
    return lhs + rhs;
}
