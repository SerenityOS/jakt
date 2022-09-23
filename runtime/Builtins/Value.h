/*
 * Copyright (c) 2022, Daniel Grießhaber <dangrie158@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include <Builtins/Dictionary.h>
#include <Builtins/Set.h>
#include <Jakt/Forward.h>
#include <Jakt/Optional.h>
#include <Jakt/RefPtr.h>
#include <Jakt/String.h>
#include <Jakt/StringBuilder.h>
#include <Jakt/Tuple.h>
#include <Jakt/Variant.h>

namespace Jakt {
namespace JaktValue_Details {
struct Void;
struct Bool;
struct U8;
struct U16;
struct U32;
struct U64;
struct I8;
struct I16;
struct I32;
struct I64;
struct F32;
struct F64;
struct USize;
struct JaktString;
struct CChar;
struct CInt;
struct JaktArray;
struct JaktDictionary;
struct JaktSet;
struct JaktOptional;
struct JaktRawPtr;
struct JaktNone;
}
struct JaktValue;

namespace JaktValue_Details {
struct Void { };
struct Bool {
    bool value;
    template<typename _MemberT0>
    Bool(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct U8 {
    u8 value;
    template<typename _MemberT0>
    U8(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct U16 {
    u16 value;
    template<typename _MemberT0>
    U16(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct U32 {
    u32 value;
    template<typename _MemberT0>
    U32(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct U64 {
    u64 value;
    template<typename _MemberT0>
    U64(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct I8 {
    i8 value;
    template<typename _MemberT0>
    I8(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct I16 {
    i16 value;
    template<typename _MemberT0>
    I16(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct I32 {
    i32 value;
    template<typename _MemberT0>
    I32(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct I64 {
    i64 value;
    template<typename _MemberT0>
    I64(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct F32 {
    f32 value;
    template<typename _MemberT0>
    F32(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct F64 {
    f64 value;
    template<typename _MemberT0>
    F64(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct USize {
    size_t value;
    template<typename _MemberT0>
    USize(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct JaktString {
    String value;
    template<typename _MemberT0>
    JaktString(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct CChar {
    char value;
    template<typename _MemberT0>
    CChar(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct CInt {
    int value;
    template<typename _MemberT0>
    CInt(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct JaktArray {
    JaktInternal::Array<NonnullRefPtr<JaktValue>> value;
    template<typename _MemberT0>
    JaktArray(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct JaktDictionary {
    JaktInternal::Dictionary<NonnullRefPtr<JaktValue>, NonnullRefPtr<JaktValue>> value;
    template<typename _MemberT0>
    JaktDictionary(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct JaktSet {
    JaktInternal::Set<NonnullRefPtr<JaktValue>> value;
    template<typename _MemberT0>
    JaktSet(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct JaktOptional {
    NonnullRefPtr<JaktValue> value;
    template<typename _MemberT0>
    JaktOptional(_MemberT0&& member_0)
        : value { forward<_MemberT0>(member_0) }
    {
    }
};
struct JaktRawPtr {
    size_t value;
    NonnullRefPtr<JaktValue> type;
    template<typename _MemberT0, typename _MemberT1>
    JaktRawPtr(_MemberT0&& member_0, _MemberT1&& member_1)
        : value { forward<_MemberT0>(member_0) }
        , type { forward<_MemberT1>(member_1) }
    {
    }
};
struct JaktNone { };
}

struct JaktValue : public Variant<JaktValue_Details::Void, JaktValue_Details::Bool, JaktValue_Details::U8, JaktValue_Details::U16, JaktValue_Details::U32, JaktValue_Details::U64, JaktValue_Details::I8, JaktValue_Details::I16, JaktValue_Details::I32, JaktValue_Details::I64, JaktValue_Details::F32, JaktValue_Details::F64, JaktValue_Details::USize, JaktValue_Details::JaktString, JaktValue_Details::CChar, JaktValue_Details::CInt, JaktValue_Details::JaktArray, JaktValue_Details::JaktDictionary, JaktValue_Details::JaktSet, JaktValue_Details::JaktOptional, JaktValue_Details::JaktRawPtr, JaktValue_Details::JaktNone>
    , public RefCounted<JaktValue> {
    using Variant<JaktValue_Details::Void, JaktValue_Details::Bool, JaktValue_Details::U8, JaktValue_Details::U16, JaktValue_Details::U32, JaktValue_Details::U64, JaktValue_Details::I8, JaktValue_Details::I16, JaktValue_Details::I32, JaktValue_Details::I64, JaktValue_Details::F32, JaktValue_Details::F64, JaktValue_Details::USize, JaktValue_Details::JaktString, JaktValue_Details::CChar, JaktValue_Details::CInt, JaktValue_Details::JaktArray, JaktValue_Details::JaktDictionary, JaktValue_Details::JaktSet, JaktValue_Details::JaktOptional, JaktValue_Details::JaktRawPtr, JaktValue_Details::JaktNone>::Variant;
    using Void = JaktValue_Details::Void;
    using Bool = JaktValue_Details::Bool;
    using U8 = JaktValue_Details::U8;
    using U16 = JaktValue_Details::U16;
    using U32 = JaktValue_Details::U32;
    using U64 = JaktValue_Details::U64;
    using I8 = JaktValue_Details::I8;
    using I16 = JaktValue_Details::I16;
    using I32 = JaktValue_Details::I32;
    using I64 = JaktValue_Details::I64;
    using F32 = JaktValue_Details::F32;
    using F64 = JaktValue_Details::F64;
    using USize = JaktValue_Details::USize;
    using JaktString = JaktValue_Details::JaktString;
    using CChar = JaktValue_Details::CChar;
    using CInt = JaktValue_Details::CInt;
    using JaktArray = JaktValue_Details::JaktArray;
    using JaktDictionary = JaktValue_Details::JaktDictionary;
    using JaktSet = JaktValue_Details::JaktSet;
    using JaktOptional = JaktValue_Details::JaktOptional;
    using JaktRawPtr = JaktValue_Details::JaktRawPtr;
    using JaktNone = JaktValue_Details::JaktNone;

    template<typename V, typename... Args>
    static auto create(Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(V(forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(u8 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::U8(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(u16 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::U16(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(u32 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::U32(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(u64 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::U64(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(i8 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::I8(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(i16 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::I16(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(i32 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::I32(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(i64 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::I64(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(f32 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::F32(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(f64 value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::F64(value, forward<Args>(args)...)));
    }

    template<typename... Args>
    static auto create(String value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue::JaktString(value, forward<Args>(args)...)));
    }

    template<typename T, typename... Args>
    static ErrorOr<NonnullRefPtr<JaktValue>> create(Array<T> values, Args&&... args)
    {
        auto wrapped_values = TRY(Array<NonnullRefPtr<JaktValue>>::create_empty());
        TRY(wrapped_values.ensure_capacity(values.size()));

        auto iterator = values.iterator();
        auto current = iterator.next();

        for (; current.has_value(); current = iterator.next()) {
            auto wrapped_value = TRY(JaktValue::template create((current.value())));
            TRY(wrapped_values.push(wrapped_value));
        }
        return JaktValue::template create<JaktValue::JaktArray>(JaktArray(wrapped_values));
    }

    template<typename K, typename V, typename... Args>
    const static ErrorOr<NonnullRefPtr<JaktValue>> create(Dictionary<K, V> values)
    {
        auto wrapped_values = TRY(Dictionary<NonnullRefPtr<JaktValue>, NonnullRefPtr<JaktValue>>::create_empty());
        TRY(wrapped_values.ensure_capacity(values.size()));

        auto iterator = values.iterator();
        auto current = iterator.next();

        for (; current.has_value(); current = iterator.next()) {
            auto wrapped_key = TRY(JaktValue::template create((current.value()).template get<0>()));
            auto wrapped_value = TRY(JaktValue::template create((current.value()).template get<1>()));
            TRY(wrapped_values.set(wrapped_key, wrapped_value));
        }
        return JaktValue::template create<JaktValue::JaktDictionary>(JaktDictionary(wrapped_values));
    }

    template<typename T, typename... Args>
    static ErrorOr<NonnullRefPtr<JaktValue>> create(Set<T> values, Args&&... args)
    {
        auto wrapped_values = TRY(Set<NonnullRefPtr<JaktValue>>::create_empty());
        TRY(wrapped_values.ensure_capacity(values.size()));

        auto iterator = values.iterator();
        auto current = iterator.next();

        for (; current.has_value(); current = iterator.next()) {
            auto wrapped_value = TRY(JaktValue::template create((current.value())));
            TRY(wrapped_values.add(wrapped_value));
        }
        return JaktValue::template create<JaktValue::JaktSet>(JaktSet(wrapped_values));
    }

    template<typename T, typename... Args>
    static ErrorOr<NonnullRefPtr<JaktValue>> create(Optional<T> value, Args&&... args)
    {
        if (!value.has_value()) {
            auto empty_value = TRY(JaktValue::template create<typename JaktValue_Details::JaktNone>());
            return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue_Details::JaktOptional(empty_value, forward<Args>(args)...)));
        }
        auto wrapped_value = TRY(JaktValue::template create((value.value())));
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue_Details::JaktOptional(wrapped_value, forward<Args>(args)...)));
    }

    template<typename T, typename... Args>
    static ErrorOr<NonnullRefPtr<JaktValue>> create(RawPtr<T> value, Args&&... args)
    {
        return adopt_nonnull_ref_or_enomem(new (nothrow) JaktValue(JaktValue_Details::JaktRawPtr(value, forward<Args>(args)...)));
    }

    ErrorOr<String> debug_description() const
    {
        auto builder = TRY(StringBuilder::create());
        switch (this->index()) {
        case 0 /* Void */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::Void>();
            TRY(builder.append("JaktValue::Void"));
            break;
        }
        case 1 /* Bool */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::Bool>();
            TRY(builder.append("JaktValue::Bool"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 2 /* U8 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::U8>();
            TRY(builder.append("JaktValue::U8"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 3 /* U16 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::U16>();
            TRY(builder.append("JaktValue::U16"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 4 /* U32 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::U32>();
            TRY(builder.append("JaktValue::U32"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 5 /* U64 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::U64>();
            TRY(builder.append("JaktValue::U64"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 6 /* I8 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::I8>();
            TRY(builder.append("JaktValue::I8"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 7 /* I16 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::I16>();
            TRY(builder.append("JaktValue::I16"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 8 /* I32 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::I32>();
            TRY(builder.append("JaktValue::I32"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 9 /* I64 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::I64>();
            TRY(builder.append("JaktValue::I64"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 10 /* F32 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::F32>();
            TRY(builder.append("JaktValue::F32"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 11 /* F64 */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::F64>();
            TRY(builder.append("JaktValue::F64"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 12 /* USize */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::USize>();
            TRY(builder.append("JaktValue::USize"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 13 /* JaktString */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::JaktString>();
            TRY(builder.append("JaktValue::JaktString"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: \"{}\"", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 14 /* CChar */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::CChar>();
            TRY(builder.append("JaktValue::CChar"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 15 /* CInt */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::CInt>();
            TRY(builder.append("JaktValue::CInt"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 16 /* JaktArray */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::JaktArray>();
            TRY(builder.append("JaktValue::JaktArray"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 17 /* JaktDictionary */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::JaktDictionary>();
            TRY(builder.append("JaktValue::JaktDictionary"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 18 /* JaktSet */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::JaktSet>();
            TRY(builder.append("JaktValue::JaktSet"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 19 /* JaktOptional */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::JaktOptional>();
            TRY(builder.append("JaktValue::JaktOptional"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
            }
            TRY(builder.append(")"));
            break;
        }
        case 20 /* JaktRawPtr */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::JaktRawPtr>();
            TRY(builder.append("JaktValue::JaktRawPtr"));
            TRY(builder.append("("));
            {
                JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("value: {}", that.value));
                TRY(builder.append(", "));
                TRY(JaktInternal::PrettyPrint::output_indentation(builder));
                TRY(builder.appendff("type: {}", that.type));
            }
            TRY(builder.append(")"));
            break;
        }
        case 21 /* JaktNone */: {
            [[maybe_unused]] auto const& that = this->template get<JaktValue::JaktNone>();
            TRY(builder.append("JaktValue::JaktNone"));
            break;
        }
        }
        return builder.to_string();
    }
    ErrorOr<String> to_string() const;
    ErrorOr<String> to_representation() const;
};
ErrorOr<String> JaktValue::to_string() const
{
    {
        return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>> {
            auto&& __jakt_match_variant = *this;
            switch (__jakt_match_variant.index()) {
            case 0: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<typename JaktValue::Void>();
                return JaktInternal::ExplicitValue(String(""));
            }; /*case end*/
            case 1: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::Bool>();
                bool const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 2: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::U8>();
                u8 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 3: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::U16>();
                u16 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 4: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::U32>();
                u32 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 5: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::U64>();
                u64 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 6: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::I8>();
                i8 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 7: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::I16>();
                i16 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 8: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::I32>();
                i32 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 9: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::I64>();
                i64 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 10: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::F32>();
                f32 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 11: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::F64>();
                f64 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 12: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::USize>();
                size_t const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 14: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::CChar>();
                char const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 15: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::CInt>();
                int const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 13: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::JaktString>();
                String const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 16: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::JaktArray>();
                JaktInternal::Array<NonnullRefPtr<JaktValue>> const& value = __jakt_match_value.value;
                {
                    String array_representation = String("[");
                    bool first = true;
                    {
                        JaktInternal::ArrayIterator<NonnullRefPtr<JaktValue>> _magic = ((value).iterator());
                        for (;;) {
                            JaktInternal::Optional<NonnullRefPtr<JaktValue>> _magic_value = ((_magic).next());
                            if ((!(((_magic_value).has_value())))) {
                                break;
                            }
                            NonnullRefPtr<JaktValue> entry = (_magic_value.value());
                            {
                                if ((!(first))) {
                                    (array_representation += String(", "));
                                } else {
                                    (first = false);
                                }

                                (array_representation += TRY((String::formatted(String("{}"), TRY((((entry)->to_representation())))))));
                            }
                        }
                    }

                    (array_representation += String("]"));
                    return (array_representation);
                }
            }; /*case end*/
            case 17: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::JaktDictionary>();
                JaktInternal::Dictionary<NonnullRefPtr<JaktValue>, NonnullRefPtr<JaktValue>> const& value = __jakt_match_value.value;
                {
                    String dict_representation = String("[");
                    bool first = true;
                    {
                        JaktInternal::DictionaryIterator<NonnullRefPtr<JaktValue>, NonnullRefPtr<JaktValue>> _magic = ((value).iterator());
                        for (;;) {
                            JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<JaktValue>, NonnullRefPtr<JaktValue>>> _magic_value = ((_magic).next());
                            if ((!(((_magic_value).has_value())))) {
                                break;
                            }
                            JaktInternal::Tuple<NonnullRefPtr<JaktValue>, NonnullRefPtr<JaktValue>> key__entry__ = (_magic_value.value());
                            {
                                const JaktInternal::Tuple<NonnullRefPtr<JaktValue>, NonnullRefPtr<JaktValue>> jakt__key__entry__ = key__entry__;
                                const NonnullRefPtr<JaktValue> key = ((jakt__key__entry__).get<0>());
                                const NonnullRefPtr<JaktValue> entry = ((jakt__key__entry__).get<1>());

                                if ((!(first))) {
                                    (dict_representation += String(", "));
                                } else {
                                    (first = false);
                                }

                                (dict_representation += TRY((String::formatted(String("{}: {}"), TRY((((key)->to_representation()))), TRY((((entry)->to_representation())))))));
                            }
                        }
                    }

                    (dict_representation += String("]"));
                    return (dict_representation);
                }
            }; /*case end*/
            case 18: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::JaktSet>();
                JaktInternal::Set<NonnullRefPtr<JaktValue>> const& value = __jakt_match_value.value;
                {
                    String set_representation = String("{{");
                    bool first = true;
                    {
                        JaktInternal::SetIterator<NonnullRefPtr<JaktValue>> _magic = ((value).iterator());
                        for (;;) {
                            JaktInternal::Optional<NonnullRefPtr<JaktValue>> _magic_value = ((_magic).next());
                            if ((!(((_magic_value).has_value())))) {
                                break;
                            }
                            NonnullRefPtr<JaktValue> entry = (_magic_value.value());
                            {
                                if ((!(first))) {
                                    (set_representation += String(", "));
                                } else {
                                    (first = false);
                                }

                                (set_representation += TRY((String::formatted(String("{}"), TRY((((entry)->to_representation())))))));
                            }
                        }
                    }

                    (set_representation += String("}}"));
                    return (set_representation);
                }
            }; /*case end*/
            case 19: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::JaktOptional>();
                NonnullRefPtr<JaktValue> const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 20: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::JaktRawPtr>();
                size_t const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{:p}"), value))));
            }; /*case end*/
            case 21: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<typename JaktValue::JaktNone>();
                return JaktInternal::ExplicitValue(String(""));
            }; /*case end*/
            default:
                VERIFY_NOT_REACHED();
            } /*switch end*/
        }())));
    }
}

ErrorOr<String> JaktValue::to_representation() const
{
    {
        return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>> {
            auto&& __jakt_match_variant = *this;
            switch (__jakt_match_variant.index()) {
            case 0: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<typename JaktValue::Void>();
                return JaktInternal::ExplicitValue(String("Void"));
            }; /*case end*/
            case 1: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::Bool>();
                bool const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}"), value))));
            }; /*case end*/
            case 2: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::U8>();
                u8 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}u8"), value))));
            }; /*case end*/
            case 3: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::U16>();
                u16 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}u16"), value))));
            }; /*case end*/
            case 4: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::U32>();
                u32 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}u32"), value))));
            }; /*case end*/
            case 5: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::U64>();
                u64 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}u64"), value))));
            }; /*case end*/
            case 6: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::I8>();
                i8 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}i8"), value))));
            }; /*case end*/
            case 7: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::I16>();
                i16 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}i16"), value))));
            }; /*case end*/
            case 8: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::I32>();
                i32 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}i32"), value))));
            }; /*case end*/
            case 9: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::I64>();
                i64 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}i64"), value))));
            }; /*case end*/
            case 10: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::F32>();
                f32 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}f32"), value))));
            }; /*case end*/
            case 11: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::F64>();
                f64 const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}f64"), value))));
            }; /*case end*/
            case 12: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::USize>();
                size_t const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}uz"), value))));
            }; /*case end*/
            case 13: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::JaktString>();
                String const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("\"{}\""), value))));
            }; /*case end*/
            case 20: {
                auto&& __jakt_match_value = __jakt_match_variant.template get<JaktValue::JaktRawPtr>();
                size_t const& value = __jakt_match_value.value;
                return JaktInternal::ExplicitValue(TRY((String::formatted(String("{{Raw Pointer @{:p}}}"), value))));
            }; /*case end*/
            default: {
                return JaktInternal::ExplicitValue(TRY((((*this).to_string()))));
            }; /*case end*/
            }  /*switch end*/
        }())));
    }
}

template<>
struct Formatter<JaktValue> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, JaktValue const& value)
    {
        JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };
        ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));
        return format_error;
    }
};
} // namespace Jakt
