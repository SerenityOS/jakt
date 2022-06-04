/*
 * Copyright (c) 2020-2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <Jakt/Assertions.h>
#include <Jakt/Checked.h>
#include <Jakt/Optional.h>
#include <Jakt/Platform.h>
#include <Jakt/StdLibExtras.h>

namespace Jakt {

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

}
