/*
 * Copyright (c) 2020-2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Assertions.h>
#include <AK/Checked.h>
#include <AK/Optional.h>
#include <AK/Platform.h>
#include <AK/StdLibExtras.h>

namespace AK {

template<typename OutputType, typename InputType>
ALWAYS_INLINE bool is(InputType& input)
{
    if constexpr (requires { input.template fast_is<OutputType>(); }) {
        return input.template fast_is<OutputType>();
    }
    return dynamic_cast<CopyConst<InputType, OutputType>*>(&input);
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE bool is(InputType* input)
{
    return input && is<OutputType>(*input);
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE bool is(NonnullRefPtr<InputType> const& input)
{
    return is<OutputType>(*input);
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE CopyConst<InputType, OutputType>* verify_cast(InputType* input)
{
    static_assert(IsBaseOf<InputType, OutputType>);
    VERIFY(!input || is<OutputType>(*input));
    return static_cast<CopyConst<InputType, OutputType>*>(input);
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE CopyConst<InputType, OutputType>& verify_cast(InputType& input)
{
    static_assert(IsBaseOf<InputType, OutputType>);
    VERIFY(is<OutputType>(input));
    return static_cast<CopyConst<InputType, OutputType>&>(input);
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE Optional<OutputType> fallible_integer_cast(InputType input)
{
    static_assert(IsIntegral<InputType>);
    if (!is_within_range<OutputType>(input))
        return {};
    return static_cast<OutputType>(input);
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE OutputType infallible_integer_cast(InputType input)
{
    static_assert(IsIntegral<InputType>);
    VERIFY(is_within_range<OutputType>(input));
    return static_cast<OutputType>(input);
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE OutputType saturating_integer_cast(InputType input)
{
    static_assert(IsIntegral<InputType>);
    if (!is_within_range<OutputType>(input)) {
        if constexpr (IsSigned<InputType>) {
            if (input < 0)
                return NumericLimits<OutputType>::min();
        }
        return NumericLimits<OutputType>::max();
    }
    return static_cast<OutputType>(input);
}

template<typename OutputType, typename InputType>
ALWAYS_INLINE OutputType truncating_integer_cast(InputType input)
{
    static_assert(IsIntegral<InputType>);
    return static_cast<OutputType>(input);
}

}

using AK::fallible_integer_cast;
using AK::infallible_integer_cast;
using AK::is;
using AK::saturating_integer_cast;
using AK::truncating_integer_cast;
using AK::verify_cast;