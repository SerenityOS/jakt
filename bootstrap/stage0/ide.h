#pragma once
#include "__unified_forward.h"
#include "parser.h"
#include "typechecker.h"
#include "types.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace ide {
namespace VarType_Details {
struct Variable {
};
struct Field {
};
}
struct VarType : public Variant<VarType_Details::Variable, VarType_Details::Field> {
using Variant<VarType_Details::Variable, VarType_Details::Field>::Variant;
    using Variable = VarType_Details::Variable;
    using Field = VarType_Details::Field;
ErrorOr<DeprecatedString> debug_description() const;
};
struct JaktSymbol {
  public:
public: DeprecatedString name;public: JaktInternal::Optional<DeprecatedString> detail;public: DeprecatedString kind;public: utility::Span range;public: utility::Span selection_range;public: JaktInternal::DynamicArray<ide::JaktSymbol> children;public: JaktSymbol(DeprecatedString a_name, JaktInternal::Optional<DeprecatedString> a_detail, DeprecatedString a_kind, utility::Span a_range, utility::Span a_selection_range, JaktInternal::DynamicArray<ide::JaktSymbol> a_children);

public: ErrorOr<DeprecatedString> to_json() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace VarVisibility_Details {
struct DoesNotApply {
};
struct Public {
};
struct Private {
};
struct Restricted {
};
}
struct VarVisibility : public Variant<VarVisibility_Details::DoesNotApply, VarVisibility_Details::Public, VarVisibility_Details::Private, VarVisibility_Details::Restricted> {
using Variant<VarVisibility_Details::DoesNotApply, VarVisibility_Details::Public, VarVisibility_Details::Private, VarVisibility_Details::Restricted>::Variant;
    using DoesNotApply = VarVisibility_Details::DoesNotApply;
    using Public = VarVisibility_Details::Public;
    using Private = VarVisibility_Details::Private;
    using Restricted = VarVisibility_Details::Restricted;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace Mutability_Details {
struct DoesNotApply {
};
struct Immutable {
};
struct Mutable {
};
}
struct Mutability : public Variant<Mutability_Details::DoesNotApply, Mutability_Details::Immutable, Mutability_Details::Mutable> {
using Variant<Mutability_Details::DoesNotApply, Mutability_Details::Immutable, Mutability_Details::Mutable>::Variant;
    using DoesNotApply = Mutability_Details::DoesNotApply;
    using Immutable = Mutability_Details::Immutable;
    using Mutable = Mutability_Details::Mutable;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace Usage_Details {
struct Variable {
utility::Span span;
DeprecatedString name;
ids::TypeId type_id;
ide::Mutability mutability;
ide::VarType var_type;
ide::VarVisibility visibility;
JaktInternal::Optional<ids::TypeId> struct_type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6>
Variable(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6):
span{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)},
mutability{ forward<_MemberT3>(member_3)},
var_type{ forward<_MemberT4>(member_4)},
visibility{ forward<_MemberT5>(member_5)},
struct_type_id{ forward<_MemberT6>(member_6)}
{}
};
struct Call{
ids::FunctionId value;
template<typename _MemberT0>
Call(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Typename{
ids::TypeId value;
template<typename _MemberT0>
Typename(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct NameSet{
JaktInternal::DynamicArray<DeprecatedString> value;
template<typename _MemberT0>
NameSet(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct EnumVariant {
utility::Span span;
DeprecatedString name;
ids::TypeId type_id;
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,ids::TypeId>> variants;
JaktInternal::Optional<types::NumberConstant> number_constant;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
EnumVariant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
span{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)},
variants{ forward<_MemberT3>(member_3)},
number_constant{ forward<_MemberT4>(member_4)}
{}
};
}
struct Usage : public Variant<Usage_Details::Variable, Usage_Details::Call, Usage_Details::Typename, Usage_Details::NameSet, Usage_Details::EnumVariant> {
using Variant<Usage_Details::Variable, Usage_Details::Call, Usage_Details::Typename, Usage_Details::NameSet, Usage_Details::EnumVariant>::Variant;
    using Variable = Usage_Details::Variable;
    using Call = Usage_Details::Call;
    using Typename = Usage_Details::Typename;
    using NameSet = Usage_Details::NameSet;
    using EnumVariant = Usage_Details::EnumVariant;
ErrorOr<DeprecatedString> debug_description() const;
};
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::VarType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::VarType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::JaktSymbol> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::JaktSymbol const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::VarVisibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::VarVisibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::Mutability> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::Mutability const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::Usage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::Usage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
