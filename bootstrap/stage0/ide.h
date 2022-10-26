#pragma once
#include "__unified_forward.h"
#include "parser.h"
#include "typechecker.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace ide {
namespace VarVisibility_Details {
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
ErrorOr<String> debug_description() const;
};
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
ErrorOr<String> debug_description() const;
};
struct JaktSymbol {
  public:
String name;JaktInternal::Optional<String> detail;String kind;utility::Span range;utility::Span selection_range;JaktInternal::Array<ide::JaktSymbol> children;JaktSymbol(String a_name, JaktInternal::Optional<String> a_detail, String a_kind, utility::Span a_range, utility::Span a_selection_range, JaktInternal::Array<ide::JaktSymbol> a_children);

ErrorOr<String> to_json() const;
ErrorOr<String> debug_description() const;
};namespace Mutability_Details {
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
ErrorOr<String> debug_description() const;
};
namespace Usage_Details {
struct Variable {
utility::Span span;
String name;
types::TypeId type_id;
ide::Mutability mutability;
ide::VarType var_type;
ide::VarVisibility visibility;
JaktInternal::Optional<types::TypeId> struct_type_id;
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
types::FunctionId value;
template<typename _MemberT0>
Call(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Typename{
types::TypeId value;
template<typename _MemberT0>
Typename(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct NameSet{
JaktInternal::Array<String> value;
template<typename _MemberT0>
NameSet(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct EnumVariant {
utility::Span span;
String name;
types::TypeId type_id;
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> variants;
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
ErrorOr<String> debug_description() const;
};
}
template<>struct Formatter<ide::VarVisibility> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, ide::VarVisibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<ide::VarType> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, ide::VarType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<ide::JaktSymbol> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, ide::JaktSymbol const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<ide::Mutability> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, ide::Mutability const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<ide::Usage> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, ide::Usage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
