#pragma once
#include "__unified_forward.h"
#include "parser.h"
#include "utility.h"
#include "compiler.h"
#include "ids.h"
namespace Jakt {
namespace types {
namespace CheckedTraitRequirements_Details {
struct Nothing {
};
struct Methods{
JaktInternal::Dictionary<DeprecatedString,ids::FunctionId> value;
template<typename _MemberT0>
Methods(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct ComptimeExpression{
NonnullRefPtr<typename types::CheckedExpression> value;
template<typename _MemberT0>
ComptimeExpression(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct CheckedTraitRequirements : public Variant<CheckedTraitRequirements_Details::Nothing, CheckedTraitRequirements_Details::Methods, CheckedTraitRequirements_Details::ComptimeExpression> {
using Variant<CheckedTraitRequirements_Details::Nothing, CheckedTraitRequirements_Details::Methods, CheckedTraitRequirements_Details::ComptimeExpression>::Variant;
    using Nothing = CheckedTraitRequirements_Details::Nothing;
    using Methods = CheckedTraitRequirements_Details::Methods;
    using ComptimeExpression = CheckedTraitRequirements_Details::ComptimeExpression;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace MaybeResolvedScope_Details {
struct Resolved{
ids::ScopeId value;
template<typename _MemberT0>
Resolved(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Unresolved {
NonnullRefPtr<typename types::MaybeResolvedScope> parent_scope;
DeprecatedString relative_name;
template<typename _MemberT0, typename _MemberT1>
Unresolved(_MemberT0&& member_0, _MemberT1&& member_1):
parent_scope{ forward<_MemberT0>(member_0)},
relative_name{ forward<_MemberT1>(member_1)}
{}
};
}
struct MaybeResolvedScope : public Variant<MaybeResolvedScope_Details::Resolved, MaybeResolvedScope_Details::Unresolved>, public RefCounted<MaybeResolvedScope> {
using Variant<MaybeResolvedScope_Details::Resolved, MaybeResolvedScope_Details::Unresolved>::Variant;
    using Resolved = MaybeResolvedScope_Details::Resolved;
    using Unresolved = MaybeResolvedScope_Details::Unresolved;
template<typename V, typename... Args> static auto __jakt_create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) MaybeResolvedScope(V(forward<Args>(args)...)));
}
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<NonnullRefPtr<typename types::MaybeResolvedScope>> try_resolve(NonnullRefPtr<types::CheckedProgram> const program) const;
};
struct FieldRecord {
  public:
public: ids::StructId struct_id;public: ids::VarId field_id;public: FieldRecord(ids::StructId a_struct_id, ids::VarId a_field_id);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct CheckedCall {
  public:
public: JaktInternal::DynamicArray<types::ResolvedNamespace> namespace_;public: DeprecatedString name;public: JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>> args;public: JaktInternal::DynamicArray<ids::TypeId> type_args;public: JaktInternal::Optional<ids::FunctionId> function_id;public: ids::TypeId return_type;public: bool callee_throws;public: JaktInternal::Optional<parser::ExternalName> external_name;public: parser::InlineState force_inline;public: CheckedCall(JaktInternal::DynamicArray<types::ResolvedNamespace> a_namespace_, DeprecatedString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>> a_args, JaktInternal::DynamicArray<ids::TypeId> a_type_args, JaktInternal::Optional<ids::FunctionId> a_function_id, ids::TypeId a_return_type, bool a_callee_throws, JaktInternal::Optional<parser::ExternalName> a_external_name, parser::InlineState a_force_inline);

public: parser::ExternalName name_for_codegen() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct OperatorTraitImplementation {
  public:
public: ids::TraitId trait_id;public: JaktInternal::DynamicArray<ids::TypeId> trait_generic_arguments;public: types::CheckedCall call_expression;public: OperatorTraitImplementation(ids::TraitId a_trait_id, JaktInternal::DynamicArray<ids::TypeId> a_trait_generic_arguments, types::CheckedCall a_call_expression);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct LoadedModule {
  public:
public: ids::ModuleId module_id;public: utility::FileId file_id;public: LoadedModule(ids::ModuleId a_module_id, utility::FileId a_file_id);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ResolvedForallChunk {
  public:
public: JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> parameters;public: parser::ParsedNamespace parsed_namespace;public: JaktInternal::DynamicArray<ids::ScopeId> generated_scopes;public: ResolvedForallChunk(JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> a_parameters, parser::ParsedNamespace a_parsed_namespace, JaktInternal::DynamicArray<ids::ScopeId> a_generated_scopes);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace BlockControlFlow_Details {
struct AlwaysReturns {
};
struct AlwaysTransfersControl {
bool might_break;
template<typename _MemberT0>
AlwaysTransfersControl(_MemberT0&& member_0):
might_break{ forward<_MemberT0>(member_0)}
{}
};
struct NeverReturns {
};
struct MayReturn {
};
struct PartialAlwaysReturns {
bool might_break;
template<typename _MemberT0>
PartialAlwaysReturns(_MemberT0&& member_0):
might_break{ forward<_MemberT0>(member_0)}
{}
};
struct PartialAlwaysTransfersControl {
bool might_break;
template<typename _MemberT0>
PartialAlwaysTransfersControl(_MemberT0&& member_0):
might_break{ forward<_MemberT0>(member_0)}
{}
};
struct PartialNeverReturns {
bool might_break;
template<typename _MemberT0>
PartialNeverReturns(_MemberT0&& member_0):
might_break{ forward<_MemberT0>(member_0)}
{}
};
}
struct BlockControlFlow : public Variant<BlockControlFlow_Details::AlwaysReturns, BlockControlFlow_Details::AlwaysTransfersControl, BlockControlFlow_Details::NeverReturns, BlockControlFlow_Details::MayReturn, BlockControlFlow_Details::PartialAlwaysReturns, BlockControlFlow_Details::PartialAlwaysTransfersControl, BlockControlFlow_Details::PartialNeverReturns> {
using Variant<BlockControlFlow_Details::AlwaysReturns, BlockControlFlow_Details::AlwaysTransfersControl, BlockControlFlow_Details::NeverReturns, BlockControlFlow_Details::MayReturn, BlockControlFlow_Details::PartialAlwaysReturns, BlockControlFlow_Details::PartialAlwaysTransfersControl, BlockControlFlow_Details::PartialNeverReturns>::Variant;
    using AlwaysReturns = BlockControlFlow_Details::AlwaysReturns;
    using AlwaysTransfersControl = BlockControlFlow_Details::AlwaysTransfersControl;
    using NeverReturns = BlockControlFlow_Details::NeverReturns;
    using MayReturn = BlockControlFlow_Details::MayReturn;
    using PartialAlwaysReturns = BlockControlFlow_Details::PartialAlwaysReturns;
    using PartialAlwaysTransfersControl = BlockControlFlow_Details::PartialAlwaysTransfersControl;
    using PartialNeverReturns = BlockControlFlow_Details::PartialNeverReturns;
ErrorOr<DeprecatedString> debug_description() const;
types::BlockControlFlow updated(types::BlockControlFlow const second) const;
bool is_reachable() const;
bool always_returns() const;
bool always_transfers_control() const;
types::BlockControlFlow branch_unify_with(types::BlockControlFlow const second) const;
types::BlockControlFlow definitive() const;
types::BlockControlFlow partial() const;
bool may_break() const;
types::BlockControlFlow unify_with(types::BlockControlFlow const second) const;
bool may_return() const;
bool never_returns() const;
};
struct CheckedBlock {
  public:
public: JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> statements;public: ids::ScopeId scope_id;public: types::BlockControlFlow control_flow;public: JaktInternal::Optional<ids::TypeId> yielded_type;public: bool yielded_none;public: CheckedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> a_statements, ids::ScopeId a_scope_id, types::BlockControlFlow a_control_flow, JaktInternal::Optional<ids::TypeId> a_yielded_type, bool a_yielded_none);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace CheckedMatchBody_Details {
struct Expression{
NonnullRefPtr<typename types::CheckedExpression> value;
template<typename _MemberT0>
Expression(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Block{
types::CheckedBlock value;
template<typename _MemberT0>
Block(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct CheckedMatchBody : public Variant<CheckedMatchBody_Details::Expression, CheckedMatchBody_Details::Block> {
using Variant<CheckedMatchBody_Details::Expression, CheckedMatchBody_Details::Block>::Variant;
    using Expression = CheckedMatchBody_Details::Expression;
    using Block = CheckedMatchBody_Details::Block;
ErrorOr<DeprecatedString> debug_description() const;
};
struct ClassInstanceRebind {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: bool is_mutable;public: bool is_reference;public: ClassInstanceRebind(DeprecatedString a_name, utility::Span a_name_span, bool a_is_mutable, bool a_is_reference);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace CheckedMatchCase_Details {
struct EnumVariant {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults;
DeprecatedString name;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> args;
ids::TypeId subject_type_id;
size_t index;
ids::ScopeId scope_id;
types::CheckedMatchBody body;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6, typename _MemberT7>
EnumVariant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6, _MemberT7&& member_7):
defaults{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
args{ forward<_MemberT2>(member_2)},
subject_type_id{ forward<_MemberT3>(member_3)},
index{ forward<_MemberT4>(member_4)},
scope_id{ forward<_MemberT5>(member_5)},
body{ forward<_MemberT6>(member_6)},
marker_span{ forward<_MemberT7>(member_7)}
{}
};
struct Expression {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults;
NonnullRefPtr<typename types::CheckedExpression> expression;
types::CheckedMatchBody body;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Expression(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
defaults{ forward<_MemberT0>(member_0)},
expression{ forward<_MemberT1>(member_1)},
body{ forward<_MemberT2>(member_2)},
marker_span{ forward<_MemberT3>(member_3)}
{}
};
struct ClassInstance {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults;
ids::TypeId type;
types::CheckedMatchBody body;
JaktInternal::Optional<types::ClassInstanceRebind> rebind_name;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
ClassInstance(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
defaults{ forward<_MemberT0>(member_0)},
type{ forward<_MemberT1>(member_1)},
body{ forward<_MemberT2>(member_2)},
rebind_name{ forward<_MemberT3>(member_3)},
marker_span{ forward<_MemberT4>(member_4)}
{}
};
struct CatchAll {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults;
bool has_arguments;
types::CheckedMatchBody body;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
CatchAll(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
defaults{ forward<_MemberT0>(member_0)},
has_arguments{ forward<_MemberT1>(member_1)},
body{ forward<_MemberT2>(member_2)},
marker_span{ forward<_MemberT3>(member_3)}
{}
};
}
struct CheckedMatchCase : public Variant<CheckedMatchCase_Details::EnumVariant, CheckedMatchCase_Details::Expression, CheckedMatchCase_Details::ClassInstance, CheckedMatchCase_Details::CatchAll> {
using Variant<CheckedMatchCase_Details::EnumVariant, CheckedMatchCase_Details::Expression, CheckedMatchCase_Details::ClassInstance, CheckedMatchCase_Details::CatchAll>::Variant;
    using EnumVariant = CheckedMatchCase_Details::EnumVariant;
    using Expression = CheckedMatchCase_Details::Expression;
    using ClassInstance = CheckedMatchCase_Details::ClassInstance;
    using CatchAll = CheckedMatchCase_Details::CatchAll;
ErrorOr<DeprecatedString> debug_description() const;
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> const& defaults() const { switch(this->index()) {case 0 /* EnumVariant */: return this->template get<CheckedMatchCase::EnumVariant>().defaults;
case 1 /* Expression */: return this->template get<CheckedMatchCase::Expression>().defaults;
case 2 /* ClassInstance */: return this->template get<CheckedMatchCase::ClassInstance>().defaults;
case 3 /* CatchAll */: return this->template get<CheckedMatchCase::CatchAll>().defaults;
default: VERIFY_NOT_REACHED();
}
}
};
namespace CheckedTypeCast_Details {
struct Fallible{
ids::TypeId value;
template<typename _MemberT0>
Fallible(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Infallible{
ids::TypeId value;
template<typename _MemberT0>
Infallible(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct CheckedTypeCast : public Variant<CheckedTypeCast_Details::Fallible, CheckedTypeCast_Details::Infallible> {
using Variant<CheckedTypeCast_Details::Fallible, CheckedTypeCast_Details::Infallible>::Variant;
    using Fallible = CheckedTypeCast_Details::Fallible;
    using Infallible = CheckedTypeCast_Details::Infallible;
ErrorOr<DeprecatedString> debug_description() const;
ids::TypeId type_id() const;
};
namespace CheckedEnumVariant_Details {
struct Untyped {
ids::EnumId enum_id;
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Untyped(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
enum_id{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Typed {
ids::EnumId enum_id;
DeprecatedString name;
ids::TypeId type_id;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Typed(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
enum_id{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct WithValue {
ids::EnumId enum_id;
DeprecatedString name;
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
WithValue(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
enum_id{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
expr{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct StructLike {
ids::EnumId enum_id;
DeprecatedString name;
JaktInternal::DynamicArray<ids::VarId> fields;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
StructLike(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
enum_id{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
fields{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
}
struct CheckedEnumVariant : public Variant<CheckedEnumVariant_Details::Untyped, CheckedEnumVariant_Details::Typed, CheckedEnumVariant_Details::WithValue, CheckedEnumVariant_Details::StructLike> {
using Variant<CheckedEnumVariant_Details::Untyped, CheckedEnumVariant_Details::Typed, CheckedEnumVariant_Details::WithValue, CheckedEnumVariant_Details::StructLike>::Variant;
    using Untyped = CheckedEnumVariant_Details::Untyped;
    using Typed = CheckedEnumVariant_Details::Typed;
    using WithValue = CheckedEnumVariant_Details::WithValue;
    using StructLike = CheckedEnumVariant_Details::StructLike;
ErrorOr<DeprecatedString> debug_description() const;
ids::EnumId enum_id() const;
DeprecatedString name() const;
bool equals(types::CheckedEnumVariant const other) const;
utility::Span span() const;
};
namespace CheckedUnaryOperator_Details {
struct PreIncrement {
};
struct PostIncrement {
};
struct PreDecrement {
};
struct PostDecrement {
};
struct Negate {
};
struct Dereference {
};
struct RawAddress {
};
struct Reference {
};
struct MutableReference {
};
struct LogicalNot {
};
struct BitwiseNot {
};
struct TypeCast{
types::CheckedTypeCast value;
template<typename _MemberT0>
TypeCast(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Is{
ids::TypeId value;
template<typename _MemberT0>
Is(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct IsEnumVariant {
types::CheckedEnumVariant enum_variant;
JaktInternal::DynamicArray<types::CheckedEnumVariantBinding> bindings;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
IsEnumVariant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
enum_variant{ forward<_MemberT0>(member_0)},
bindings{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct IsSome {
};
struct IsNone {
};
struct Sizeof{
ids::TypeId value;
template<typename _MemberT0>
Sizeof(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct CheckedUnaryOperator : public Variant<CheckedUnaryOperator_Details::PreIncrement, CheckedUnaryOperator_Details::PostIncrement, CheckedUnaryOperator_Details::PreDecrement, CheckedUnaryOperator_Details::PostDecrement, CheckedUnaryOperator_Details::Negate, CheckedUnaryOperator_Details::Dereference, CheckedUnaryOperator_Details::RawAddress, CheckedUnaryOperator_Details::Reference, CheckedUnaryOperator_Details::MutableReference, CheckedUnaryOperator_Details::LogicalNot, CheckedUnaryOperator_Details::BitwiseNot, CheckedUnaryOperator_Details::TypeCast, CheckedUnaryOperator_Details::Is, CheckedUnaryOperator_Details::IsEnumVariant, CheckedUnaryOperator_Details::IsSome, CheckedUnaryOperator_Details::IsNone, CheckedUnaryOperator_Details::Sizeof> {
using Variant<CheckedUnaryOperator_Details::PreIncrement, CheckedUnaryOperator_Details::PostIncrement, CheckedUnaryOperator_Details::PreDecrement, CheckedUnaryOperator_Details::PostDecrement, CheckedUnaryOperator_Details::Negate, CheckedUnaryOperator_Details::Dereference, CheckedUnaryOperator_Details::RawAddress, CheckedUnaryOperator_Details::Reference, CheckedUnaryOperator_Details::MutableReference, CheckedUnaryOperator_Details::LogicalNot, CheckedUnaryOperator_Details::BitwiseNot, CheckedUnaryOperator_Details::TypeCast, CheckedUnaryOperator_Details::Is, CheckedUnaryOperator_Details::IsEnumVariant, CheckedUnaryOperator_Details::IsSome, CheckedUnaryOperator_Details::IsNone, CheckedUnaryOperator_Details::Sizeof>::Variant;
    using PreIncrement = CheckedUnaryOperator_Details::PreIncrement;
    using PostIncrement = CheckedUnaryOperator_Details::PostIncrement;
    using PreDecrement = CheckedUnaryOperator_Details::PreDecrement;
    using PostDecrement = CheckedUnaryOperator_Details::PostDecrement;
    using Negate = CheckedUnaryOperator_Details::Negate;
    using Dereference = CheckedUnaryOperator_Details::Dereference;
    using RawAddress = CheckedUnaryOperator_Details::RawAddress;
    using Reference = CheckedUnaryOperator_Details::Reference;
    using MutableReference = CheckedUnaryOperator_Details::MutableReference;
    using LogicalNot = CheckedUnaryOperator_Details::LogicalNot;
    using BitwiseNot = CheckedUnaryOperator_Details::BitwiseNot;
    using TypeCast = CheckedUnaryOperator_Details::TypeCast;
    using Is = CheckedUnaryOperator_Details::Is;
    using IsEnumVariant = CheckedUnaryOperator_Details::IsEnumVariant;
    using IsSome = CheckedUnaryOperator_Details::IsSome;
    using IsNone = CheckedUnaryOperator_Details::IsNone;
    using Sizeof = CheckedUnaryOperator_Details::Sizeof;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace CheckedVisibility_Details {
struct Public {
};
struct Private {
};
struct Restricted {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> scopes;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Restricted(_MemberT0&& member_0, _MemberT1&& member_1):
scopes{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct CheckedVisibility : public Variant<CheckedVisibility_Details::Public, CheckedVisibility_Details::Private, CheckedVisibility_Details::Restricted> {
using Variant<CheckedVisibility_Details::Public, CheckedVisibility_Details::Private, CheckedVisibility_Details::Restricted>::Variant;
    using Public = CheckedVisibility_Details::Public;
    using Private = CheckedVisibility_Details::Private;
    using Restricted = CheckedVisibility_Details::Restricted;
ErrorOr<DeprecatedString> debug_description() const;
};
class CheckedTrait :public RefCounted<CheckedTrait>, public Weakable<CheckedTrait> {
  public:
virtual ~CheckedTrait() = default;
public: DeprecatedString name;public: utility::Span name_span;public: types::CheckedTraitRequirements requirements;public: JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters;public: ids::ScopeId scope_id;public: protected:
explicit CheckedTrait(DeprecatedString a_name, utility::Span a_name_span, types::CheckedTraitRequirements a_requirements, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, ids::ScopeId a_scope_id);
public:
static ErrorOr<NonnullRefPtr<CheckedTrait>> __jakt_create(DeprecatedString name, utility::Span name_span, types::CheckedTraitRequirements requirements, JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters, ids::ScopeId scope_id);

public: ErrorOr<DeprecatedString> debug_description() const;
};class CheckedFunction :public RefCounted<CheckedFunction>, public Weakable<CheckedFunction> {
  public:
virtual ~CheckedFunction() = default;
public: DeprecatedString name;public: utility::Span name_span;public: types::CheckedVisibility visibility;public: ids::TypeId return_type_id;public: JaktInternal::Optional<utility::Span> return_type_span;public: JaktInternal::DynamicArray<types::CheckedParameter> params;public: NonnullRefPtr<types::FunctionGenerics> generics;public: types::CheckedBlock block;public: bool can_throw;public: parser::FunctionType type;public: parser::FunctionLinkage linkage;public: ids::ScopeId function_scope_id;public: JaktInternal::Optional<ids::StructId> struct_id;public: bool is_instantiated;public: JaktInternal::Optional<parser::ParsedFunction> parsed_function;public: bool is_comptime;public: bool is_virtual;public: bool is_override;public: bool is_unsafe;public: JaktInternal::Optional<size_t> specialization_index;public: JaktInternal::Optional<ids::ScopeId> owner_scope;public: bool is_fully_checked;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Optional<DeprecatedString> deprecated_message;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> stores_arguments;public: parser::InlineState force_inline;public: ErrorOr<void> map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map);
public: ErrorOr<bool> is_static() const;
public: ErrorOr<bool> is_mutating() const;
public: protected:
explicit CheckedFunction(DeprecatedString a_name, utility::Span a_name_span, types::CheckedVisibility a_visibility, ids::TypeId a_return_type_id, JaktInternal::Optional<utility::Span> a_return_type_span, JaktInternal::DynamicArray<types::CheckedParameter> a_params, NonnullRefPtr<types::FunctionGenerics> a_generics, types::CheckedBlock a_block, bool a_can_throw, parser::FunctionType a_type, parser::FunctionLinkage a_linkage, ids::ScopeId a_function_scope_id, JaktInternal::Optional<ids::StructId> a_struct_id, bool a_is_instantiated, JaktInternal::Optional<parser::ParsedFunction> a_parsed_function, bool a_is_comptime, bool a_is_virtual, bool a_is_override, bool a_is_unsafe, JaktInternal::Optional<size_t> a_specialization_index, JaktInternal::Optional<ids::ScopeId> a_owner_scope, bool a_is_fully_checked, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<DeprecatedString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> a_stores_arguments, parser::InlineState a_force_inline);
public:
static ErrorOr<NonnullRefPtr<CheckedFunction>> __jakt_create(DeprecatedString name, utility::Span name_span, types::CheckedVisibility visibility, ids::TypeId return_type_id, JaktInternal::Optional<utility::Span> return_type_span, JaktInternal::DynamicArray<types::CheckedParameter> params, NonnullRefPtr<types::FunctionGenerics> generics, types::CheckedBlock block, bool can_throw, parser::FunctionType type, parser::FunctionLinkage linkage, ids::ScopeId function_scope_id, JaktInternal::Optional<ids::StructId> struct_id, bool is_instantiated, JaktInternal::Optional<parser::ParsedFunction> parsed_function, bool is_comptime, bool is_virtual, bool is_override, bool is_unsafe, JaktInternal::Optional<size_t> specialization_index, JaktInternal::Optional<ids::ScopeId> owner_scope, bool is_fully_checked, JaktInternal::Optional<parser::ExternalName> external_name, JaktInternal::Optional<DeprecatedString> deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> stores_arguments, parser::InlineState force_inline);

public: ErrorOr<parser::ParsedFunction> to_parsed_function() const;
public: bool is_specialized_for_types(JaktInternal::DynamicArray<ids::TypeId> const types) const;
public: void set_param_default_value(size_t const param_index, NonnullRefPtr<typename types::CheckedExpression> const default_value);
public: ErrorOr<bool> signature_matches(NonnullRefPtr<types::CheckedFunction> const other, bool const ignore_this) const;
public: ErrorOr<NonnullRefPtr<types::CheckedFunction>> copy() const;
public: parser::ExternalName name_for_codegen() const;
public: ErrorOr<void> add_param(types::CheckedParameter const checked_param);
public: ErrorOr<void> set_params(JaktInternal::DynamicArray<types::CheckedParameter> const checked_params);
public: ErrorOr<DeprecatedString> debug_description() const;
};struct CheckedEnumVariantBinding {
  public:
public: JaktInternal::Optional<DeprecatedString> name;public: DeprecatedString binding;public: ids::TypeId type_id;public: utility::Span span;public: CheckedEnumVariantBinding(JaktInternal::Optional<DeprecatedString> a_name, DeprecatedString a_binding, ids::TypeId a_type_id, utility::Span a_span);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace NumericOrStringValue_Details {
struct StringValue{
DeprecatedString value;
template<typename _MemberT0>
StringValue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct SignedNumericValue{
i64 value;
template<typename _MemberT0>
SignedNumericValue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct UnsignedNumericValue{
u64 value;
template<typename _MemberT0>
UnsignedNumericValue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct NumericOrStringValue : public Variant<NumericOrStringValue_Details::StringValue, NumericOrStringValue_Details::SignedNumericValue, NumericOrStringValue_Details::UnsignedNumericValue> {
using Variant<NumericOrStringValue_Details::StringValue, NumericOrStringValue_Details::SignedNumericValue, NumericOrStringValue_Details::UnsignedNumericValue>::Variant;
    using StringValue = NumericOrStringValue_Details::StringValue;
    using SignedNumericValue = NumericOrStringValue_Details::SignedNumericValue;
    using UnsignedNumericValue = NumericOrStringValue_Details::UnsignedNumericValue;
ErrorOr<DeprecatedString> debug_description() const;
};
struct SpecializedType {
  public:
public: ids::TypeId base_type_id;public: JaktInternal::DynamicArray<ids::TypeId> arguments;public: ids::TypeId type_id;public: SpecializedType(ids::TypeId a_base_type_id, JaktInternal::DynamicArray<ids::TypeId> a_arguments, ids::TypeId a_type_id);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace FunctionGenericParameterKind_Details {
struct InferenceGuide {
};
struct Parameter {
};
}
struct FunctionGenericParameterKind : public Variant<FunctionGenericParameterKind_Details::InferenceGuide, FunctionGenericParameterKind_Details::Parameter> {
using Variant<FunctionGenericParameterKind_Details::InferenceGuide, FunctionGenericParameterKind_Details::Parameter>::Variant;
    using InferenceGuide = FunctionGenericParameterKind_Details::InferenceGuide;
    using Parameter = FunctionGenericParameterKind_Details::Parameter;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace StructLikeId_Details {
struct Struct{
JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments;
ids::StructId value;
template<typename _MemberT0, typename _MemberT1>
Struct(_MemberT0&& member_0, _MemberT1&& member_1):
generic_arguments{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct Enum{
JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments;
ids::EnumId value;
template<typename _MemberT0, typename _MemberT1>
Enum(_MemberT0&& member_0, _MemberT1&& member_1):
generic_arguments{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct Trait{
JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments;
ids::TraitId value;
template<typename _MemberT0, typename _MemberT1>
Trait(_MemberT0&& member_0, _MemberT1&& member_1):
generic_arguments{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
}
struct StructLikeId : public Variant<StructLikeId_Details::Struct, StructLikeId_Details::Enum, StructLikeId_Details::Trait> {
using Variant<StructLikeId_Details::Struct, StructLikeId_Details::Enum, StructLikeId_Details::Trait>::Variant;
    using Struct = StructLikeId_Details::Struct;
    using Enum = StructLikeId_Details::Enum;
    using Trait = StructLikeId_Details::Trait;
ErrorOr<DeprecatedString> debug_description() const;
JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const& generic_arguments() const { switch(this->index()) {case 0 /* Struct */: return this->template get<StructLikeId::Struct>().generic_arguments;
case 1 /* Enum */: return this->template get<StructLikeId::Enum>().generic_arguments;
case 2 /* Trait */: return this->template get<StructLikeId::Trait>().generic_arguments;
default: VERIFY_NOT_REACHED();
}
}
static ErrorOr<JaktInternal::Optional<types::StructLikeId>> from_type_id(ids::TypeId const type_id, NonnullRefPtr<types::CheckedProgram> const& program);
ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> generic_parameters(NonnullRefPtr<types::CheckedProgram> const& program) const;
ErrorOr<ids::ScopeId> associated_scope_id(NonnullRefPtr<types::CheckedProgram> const& program) const;
ErrorOr<JaktInternal::DynamicArray<types::CheckedGenericParameter>> generic_parameters_as_checked(NonnullRefPtr<types::CheckedProgram> const& program) const;
ErrorOr<ids::ScopeId> scope_id(NonnullRefPtr<types::CheckedProgram> const& program) const;
ErrorOr<ids::TypeId> specialized_by(JaktInternal::DynamicArray<ids::TypeId> const arguments, NonnullRefPtr<types::CheckedProgram>& program, ids::ModuleId const module_id, parser::CheckedQualifiers const qualifiers) const;
};
namespace StructOrEnumId_Details {
struct Struct{
ids::StructId value;
template<typename _MemberT0>
Struct(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Enum{
ids::EnumId value;
template<typename _MemberT0>
Enum(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct StructOrEnumId : public Variant<StructOrEnumId_Details::Struct, StructOrEnumId_Details::Enum> {
using Variant<StructOrEnumId_Details::Struct, StructOrEnumId_Details::Enum>::Variant;
    using Struct = StructOrEnumId_Details::Struct;
    using Enum = StructOrEnumId_Details::Enum;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace CheckedStatement_Details {
struct Expression {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Expression(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Defer {
NonnullRefPtr<typename types::CheckedStatement> statement;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Defer(_MemberT0&& member_0, _MemberT1&& member_1):
statement{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct DestructuringAssignment {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> vars;
NonnullRefPtr<typename types::CheckedStatement> var_decl;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
DestructuringAssignment(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
vars{ forward<_MemberT0>(member_0)},
var_decl{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct VarDecl {
ids::VarId var_id;
NonnullRefPtr<typename types::CheckedExpression> init;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
VarDecl(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
var_id{ forward<_MemberT0>(member_0)},
init{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct If {
NonnullRefPtr<typename types::CheckedExpression> condition;
types::CheckedBlock then_block;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> else_statement;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
If(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
condition{ forward<_MemberT0>(member_0)},
then_block{ forward<_MemberT1>(member_1)},
else_statement{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Block {
types::CheckedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Block(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Loop {
types::CheckedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Loop(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct While {
NonnullRefPtr<typename types::CheckedExpression> condition;
types::CheckedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
While(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
condition{ forward<_MemberT0>(member_0)},
block{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Return {
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> val;
JaktInternal::Optional<utility::Span> span;
template<typename _MemberT0, typename _MemberT1>
Return(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Break{
utility::Span value;
template<typename _MemberT0>
Break(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Continue{
utility::Span value;
template<typename _MemberT0>
Continue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Throw {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Throw(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Yield {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Yield(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct InlineCpp {
JaktInternal::DynamicArray<DeprecatedString> lines;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
InlineCpp(_MemberT0&& member_0, _MemberT1&& member_1):
lines{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Garbage{
utility::Span value;
template<typename _MemberT0>
Garbage(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct CheckedStatement : public Variant<CheckedStatement_Details::Expression, CheckedStatement_Details::Defer, CheckedStatement_Details::DestructuringAssignment, CheckedStatement_Details::VarDecl, CheckedStatement_Details::If, CheckedStatement_Details::Block, CheckedStatement_Details::Loop, CheckedStatement_Details::While, CheckedStatement_Details::Return, CheckedStatement_Details::Break, CheckedStatement_Details::Continue, CheckedStatement_Details::Throw, CheckedStatement_Details::Yield, CheckedStatement_Details::InlineCpp, CheckedStatement_Details::Garbage>, public RefCounted<CheckedStatement> {
using Variant<CheckedStatement_Details::Expression, CheckedStatement_Details::Defer, CheckedStatement_Details::DestructuringAssignment, CheckedStatement_Details::VarDecl, CheckedStatement_Details::If, CheckedStatement_Details::Block, CheckedStatement_Details::Loop, CheckedStatement_Details::While, CheckedStatement_Details::Return, CheckedStatement_Details::Break, CheckedStatement_Details::Continue, CheckedStatement_Details::Throw, CheckedStatement_Details::Yield, CheckedStatement_Details::InlineCpp, CheckedStatement_Details::Garbage>::Variant;
    using Expression = CheckedStatement_Details::Expression;
    using Defer = CheckedStatement_Details::Defer;
    using DestructuringAssignment = CheckedStatement_Details::DestructuringAssignment;
    using VarDecl = CheckedStatement_Details::VarDecl;
    using If = CheckedStatement_Details::If;
    using Block = CheckedStatement_Details::Block;
    using Loop = CheckedStatement_Details::Loop;
    using While = CheckedStatement_Details::While;
    using Return = CheckedStatement_Details::Return;
    using Break = CheckedStatement_Details::Break;
    using Continue = CheckedStatement_Details::Continue;
    using Throw = CheckedStatement_Details::Throw;
    using Yield = CheckedStatement_Details::Yield;
    using InlineCpp = CheckedStatement_Details::InlineCpp;
    using Garbage = CheckedStatement_Details::Garbage;
template<typename V, typename... Args> static auto __jakt_create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) CheckedStatement(V(forward<Args>(args)...)));
}
ErrorOr<DeprecatedString> debug_description() const;
JaktInternal::Optional<utility::Span> span() const;
static JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> none();
};
struct CheckedField {
  public:
public: ids::VarId variable_id;public: JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> default_value;public: JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> default_value_expression;public: CheckedField(ids::VarId a_variable_id, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> a_default_value, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_default_value_expression);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace BuiltinType_Details {
struct Void {
};
struct Bool {
};
struct U8 {
};
struct U16 {
};
struct U32 {
};
struct U64 {
};
struct I8 {
};
struct I16 {
};
struct I32 {
};
struct I64 {
};
struct F32 {
};
struct F64 {
};
struct Usize {
};
struct JaktString {
};
struct CChar {
};
struct CInt {
};
struct Unknown {
};
struct Never {
};
}
struct BuiltinType : public Variant<BuiltinType_Details::Void, BuiltinType_Details::Bool, BuiltinType_Details::U8, BuiltinType_Details::U16, BuiltinType_Details::U32, BuiltinType_Details::U64, BuiltinType_Details::I8, BuiltinType_Details::I16, BuiltinType_Details::I32, BuiltinType_Details::I64, BuiltinType_Details::F32, BuiltinType_Details::F64, BuiltinType_Details::Usize, BuiltinType_Details::JaktString, BuiltinType_Details::CChar, BuiltinType_Details::CInt, BuiltinType_Details::Unknown, BuiltinType_Details::Never> {
using Variant<BuiltinType_Details::Void, BuiltinType_Details::Bool, BuiltinType_Details::U8, BuiltinType_Details::U16, BuiltinType_Details::U32, BuiltinType_Details::U64, BuiltinType_Details::I8, BuiltinType_Details::I16, BuiltinType_Details::I32, BuiltinType_Details::I64, BuiltinType_Details::F32, BuiltinType_Details::F64, BuiltinType_Details::Usize, BuiltinType_Details::JaktString, BuiltinType_Details::CChar, BuiltinType_Details::CInt, BuiltinType_Details::Unknown, BuiltinType_Details::Never>::Variant;
    using Void = BuiltinType_Details::Void;
    using Bool = BuiltinType_Details::Bool;
    using U8 = BuiltinType_Details::U8;
    using U16 = BuiltinType_Details::U16;
    using U32 = BuiltinType_Details::U32;
    using U64 = BuiltinType_Details::U64;
    using I8 = BuiltinType_Details::I8;
    using I16 = BuiltinType_Details::I16;
    using I32 = BuiltinType_Details::I32;
    using I64 = BuiltinType_Details::I64;
    using F32 = BuiltinType_Details::F32;
    using F64 = BuiltinType_Details::F64;
    using Usize = BuiltinType_Details::Usize;
    using JaktString = BuiltinType_Details::JaktString;
    using CChar = BuiltinType_Details::CChar;
    using CInt = BuiltinType_Details::CInt;
    using Unknown = BuiltinType_Details::Unknown;
    using Never = BuiltinType_Details::Never;
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<DeprecatedString> constructor_name() const;
size_t id() const;
};
struct CheckedNamespace {
  public:
public: DeprecatedString name;public: ids::ScopeId scope;public: CheckedNamespace(DeprecatedString a_name, ids::ScopeId a_scope);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace StringLiteral_Details {
struct Static{
DeprecatedString value;
template<typename _MemberT0>
Static(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct StringLiteral : public Variant<StringLiteral_Details::Static> {
using Variant<StringLiteral_Details::Static>::Variant;
    using Static = StringLiteral_Details::Static;
ErrorOr<DeprecatedString> debug_description() const;
DeprecatedString to_string() const;
};
class Module :public RefCounted<Module>, public Weakable<Module> {
  public:
virtual ~Module() = default;
public: ids::ModuleId id;public: DeprecatedString name;public: JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> functions;public: JaktInternal::DynamicArray<types::CheckedStruct> structures;public: JaktInternal::DynamicArray<types::CheckedEnum> enums;public: JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> scopes;public: JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> types;public: JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> traits;public: JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> variables;public: JaktInternal::DynamicArray<ids::ModuleId> imports;public: DeprecatedString resolved_import_path;public: JaktInternal::Dictionary<size_t,ids::StructId> builtin_implementation_structs;public: bool is_root;public: ids::FunctionId next_function_id() const;
public: ErrorOr<ids::FunctionId> add_function(NonnullRefPtr<types::CheckedFunction> const checked_function);
public: bool is_prelude() const;
public: protected:
explicit Module(ids::ModuleId a_id, DeprecatedString a_name, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> a_functions, JaktInternal::DynamicArray<types::CheckedStruct> a_structures, JaktInternal::DynamicArray<types::CheckedEnum> a_enums, JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> a_scopes, JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> a_types, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> a_traits, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> a_variables, JaktInternal::DynamicArray<ids::ModuleId> a_imports, DeprecatedString a_resolved_import_path, JaktInternal::Dictionary<size_t,ids::StructId> a_builtin_implementation_structs, bool a_is_root);
public:
static ErrorOr<NonnullRefPtr<Module>> __jakt_create(ids::ModuleId id, DeprecatedString name, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> functions, JaktInternal::DynamicArray<types::CheckedStruct> structures, JaktInternal::DynamicArray<types::CheckedEnum> enums, JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> scopes, JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> types, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> traits, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> variables, JaktInternal::DynamicArray<ids::ModuleId> imports, DeprecatedString resolved_import_path, JaktInternal::Dictionary<size_t,ids::StructId> builtin_implementation_structs, bool is_root);

public: ErrorOr<ids::VarId> add_variable(NonnullRefPtr<types::CheckedVariable> const checked_variable);
public: ErrorOr<ids::TypeId> new_type_variable(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const implemented_traits);
public: ErrorOr<DeprecatedString> debug_description() const;
};struct CheckedGenericParameter {
  public:
public: ids::TypeId type_id;public: JaktInternal::DynamicArray<ids::TraitId> constraints;public: utility::Span span;public: static ErrorOr<types::CheckedGenericParameter> make(ids::TypeId const type_id, utility::Span const span);
public: CheckedGenericParameter(ids::TypeId a_type_id, JaktInternal::DynamicArray<ids::TraitId> a_constraints, utility::Span a_span);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct FunctionGenericParameter {
  public:
public: types::FunctionGenericParameterKind kind;public: types::CheckedGenericParameter checked_parameter;public: static ErrorOr<types::FunctionGenericParameter> parameter(ids::TypeId const type_id, utility::Span const span);
public: ids::TypeId type_id() const;
public: FunctionGenericParameter(types::FunctionGenericParameterKind a_kind, types::CheckedGenericParameter a_checked_parameter);

public: ErrorOr<DeprecatedString> debug_description() const;
};class TypecheckFunctions :public RefCounted<TypecheckFunctions>, public Weakable<TypecheckFunctions> {
  public:
virtual ~TypecheckFunctions() = default;
public: Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>)> block;public: Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> register_function;public: protected:
explicit TypecheckFunctions(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>)> a_block, Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> a_register_function);
public:
static ErrorOr<NonnullRefPtr<TypecheckFunctions>> __jakt_create(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>)> block, Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> register_function);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ResolvedNamespace {
  public:
public: DeprecatedString name;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_parameters;public: ResolvedNamespace(DeprecatedString a_name, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> a_generic_parameters);

public: parser::ExternalName name_for_codegen() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct CheckedStruct {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>> generic_parameter_defaults;public: JaktInternal::DynamicArray<types::CheckedField> fields;public: ids::ScopeId scope_id;public: parser::DefinitionLinkage definition_linkage;public: JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> trait_implementations;public: parser::RecordType record_type;public: ids::TypeId type_id;public: JaktInternal::Optional<ids::StructId> super_struct_id;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Optional<ids::TypeId> implements_type;public: CheckedStruct(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>> a_generic_parameter_defaults, JaktInternal::DynamicArray<types::CheckedField> a_fields, ids::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> a_trait_implementations, parser::RecordType a_record_type, ids::TypeId a_type_id, JaktInternal::Optional<ids::StructId> a_super_struct_id, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<ids::TypeId> a_implements_type);

public: parser::ExternalName name_for_codegen() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace CheckedNumericConstant_Details {
struct I8{
i8 value;
template<typename _MemberT0>
I8(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I16{
i16 value;
template<typename _MemberT0>
I16(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I32{
i32 value;
template<typename _MemberT0>
I32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I64{
i64 value;
template<typename _MemberT0>
I64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U8{
u8 value;
template<typename _MemberT0>
U8(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U16{
u16 value;
template<typename _MemberT0>
U16(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U32{
u32 value;
template<typename _MemberT0>
U32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U64{
u64 value;
template<typename _MemberT0>
U64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct USize{
u64 value;
template<typename _MemberT0>
USize(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct F32{
f32 value;
template<typename _MemberT0>
F32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct F64{
f64 value;
template<typename _MemberT0>
F64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct CheckedNumericConstant : public Variant<CheckedNumericConstant_Details::I8, CheckedNumericConstant_Details::I16, CheckedNumericConstant_Details::I32, CheckedNumericConstant_Details::I64, CheckedNumericConstant_Details::U8, CheckedNumericConstant_Details::U16, CheckedNumericConstant_Details::U32, CheckedNumericConstant_Details::U64, CheckedNumericConstant_Details::USize, CheckedNumericConstant_Details::F32, CheckedNumericConstant_Details::F64> {
using Variant<CheckedNumericConstant_Details::I8, CheckedNumericConstant_Details::I16, CheckedNumericConstant_Details::I32, CheckedNumericConstant_Details::I64, CheckedNumericConstant_Details::U8, CheckedNumericConstant_Details::U16, CheckedNumericConstant_Details::U32, CheckedNumericConstant_Details::U64, CheckedNumericConstant_Details::USize, CheckedNumericConstant_Details::F32, CheckedNumericConstant_Details::F64>::Variant;
    using I8 = CheckedNumericConstant_Details::I8;
    using I16 = CheckedNumericConstant_Details::I16;
    using I32 = CheckedNumericConstant_Details::I32;
    using I64 = CheckedNumericConstant_Details::I64;
    using U8 = CheckedNumericConstant_Details::U8;
    using U16 = CheckedNumericConstant_Details::U16;
    using U32 = CheckedNumericConstant_Details::U32;
    using U64 = CheckedNumericConstant_Details::U64;
    using USize = CheckedNumericConstant_Details::USize;
    using F32 = CheckedNumericConstant_Details::F32;
    using F64 = CheckedNumericConstant_Details::F64;
ErrorOr<DeprecatedString> debug_description() const;
JaktInternal::Optional<types::NumberConstant> number_constant() const;
};
struct CheckedVarDecl {
  public:
public: DeprecatedString name;public: bool is_mutable;public: utility::Span span;public: ids::TypeId type_id;public: CheckedVarDecl(DeprecatedString a_name, bool a_is_mutable, utility::Span a_span, ids::TypeId a_type_id);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct CheckedEnum {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters;public: JaktInternal::DynamicArray<types::CheckedEnumVariant> variants;public: JaktInternal::DynamicArray<types::CheckedField> fields;public: ids::ScopeId scope_id;public: parser::DefinitionLinkage definition_linkage;public: JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> trait_implementations;public: parser::RecordType record_type;public: ids::TypeId underlying_type_id;public: ids::TypeId type_id;public: bool is_boxed;public: CheckedEnum(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, JaktInternal::DynamicArray<types::CheckedEnumVariant> a_variants, JaktInternal::DynamicArray<types::CheckedField> a_fields, ids::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> a_trait_implementations, parser::RecordType a_record_type, ids::TypeId a_underlying_type_id, ids::TypeId a_type_id, bool a_is_boxed);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct CheckedStringLiteral {
  public:
public: types::StringLiteral value;public: ids::TypeId type_id;public: bool may_throw;public: DeprecatedString to_string() const;
public: CheckedStringLiteral(types::StringLiteral a_value, ids::TypeId a_type_id, bool a_may_throw);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace SafetyMode_Details {
struct Safe {
};
struct Unsafe {
};
}
struct SafetyMode : public Variant<SafetyMode_Details::Safe, SafetyMode_Details::Unsafe> {
using Variant<SafetyMode_Details::Safe, SafetyMode_Details::Unsafe>::Variant;
    using Safe = SafetyMode_Details::Safe;
    using Unsafe = SafetyMode_Details::Unsafe;
ErrorOr<DeprecatedString> debug_description() const;
};
class CheckedVariable :public RefCounted<CheckedVariable>, public Weakable<CheckedVariable> {
  public:
virtual ~CheckedVariable() = default;
public: DeprecatedString name;public: ids::TypeId type_id;public: bool is_mutable;public: utility::Span definition_span;public: JaktInternal::Optional<utility::Span> type_span;public: types::CheckedVisibility visibility;public: JaktInternal::Optional<ids::ScopeId> owner_scope;public: JaktInternal::Optional<parser::ExternalName> external_name;public: ErrorOr<NonnullRefPtr<types::CheckedVariable>> map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) const;
public: parser::ExternalName name_for_codegen() const;
public: protected:
explicit CheckedVariable(DeprecatedString a_name, ids::TypeId a_type_id, bool a_is_mutable, utility::Span a_definition_span, JaktInternal::Optional<utility::Span> a_type_span, types::CheckedVisibility a_visibility, JaktInternal::Optional<ids::ScopeId> a_owner_scope, JaktInternal::Optional<parser::ExternalName> a_external_name);
public:
static ErrorOr<NonnullRefPtr<CheckedVariable>> __jakt_create(DeprecatedString name, ids::TypeId type_id, bool is_mutable, utility::Span definition_span, JaktInternal::Optional<utility::Span> type_span, types::CheckedVisibility visibility, JaktInternal::Optional<ids::ScopeId> owner_scope, JaktInternal::Optional<parser::ExternalName> external_name);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct CheckedParameter {
  public:
public: bool requires_label;public: NonnullRefPtr<types::CheckedVariable> variable;public: JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> default_value;public: ErrorOr<types::CheckedParameter> map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) const;
public: CheckedParameter(bool a_requires_label, NonnullRefPtr<types::CheckedVariable> a_variable, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> a_default_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct Value {
  public:
public: NonnullRefPtr<typename types::ValueImpl> impl;public: utility::Span span;public: ErrorOr<types::Value> copy() const;
public: ErrorOr<DeprecatedString> type_name() const;
public: Value(NonnullRefPtr<typename types::ValueImpl> a_impl, utility::Span a_span);

public: ErrorOr<types::Value> cast(types::Value const expected, utility::Span const span) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace Type_Details {
struct Void {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
Void(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct Bool {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
Bool(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct U8 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
U8(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct U16 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
U16(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct U32 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
U32(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct U64 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
U64(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct I8 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
I8(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct I16 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
I16(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct I32 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
I32(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct I64 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
I64(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct F32 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
F32(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct F64 {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
F64(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct Usize {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
Usize(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct JaktString {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
JaktString(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct CChar {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
CChar(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct CInt {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
CInt(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct Unknown {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
Unknown(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct Never {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
Never(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct TypeVariable {
parser::CheckedQualifiers qualifiers;
DeprecatedString name;
JaktInternal::DynamicArray<ids::TypeId> trait_implementations;
bool is_value;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
TypeVariable(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
qualifiers{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
trait_implementations{ forward<_MemberT2>(member_2)},
is_value{ forward<_MemberT3>(member_3)}
{}
};
struct Dependent {
parser::CheckedQualifiers qualifiers;
ids::TypeId namespace_type;
DeprecatedString name;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Dependent(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
namespace_type{ forward<_MemberT1>(member_1)},
name{ forward<_MemberT2>(member_2)}
{}
};
struct GenericInstance {
parser::CheckedQualifiers qualifiers;
ids::StructId id;
JaktInternal::DynamicArray<ids::TypeId> args;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
GenericInstance(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
id{ forward<_MemberT1>(member_1)},
args{ forward<_MemberT2>(member_2)}
{}
};
struct GenericEnumInstance {
parser::CheckedQualifiers qualifiers;
ids::EnumId id;
JaktInternal::DynamicArray<ids::TypeId> args;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
GenericEnumInstance(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
id{ forward<_MemberT1>(member_1)},
args{ forward<_MemberT2>(member_2)}
{}
};
struct GenericTraitInstance {
parser::CheckedQualifiers qualifiers;
ids::TraitId id;
JaktInternal::DynamicArray<ids::TypeId> args;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
GenericTraitInstance(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
id{ forward<_MemberT1>(member_1)},
args{ forward<_MemberT2>(member_2)}
{}
};
struct GenericResolvedType {
parser::CheckedQualifiers qualifiers;
ids::StructId id;
JaktInternal::DynamicArray<ids::TypeId> args;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
GenericResolvedType(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
id{ forward<_MemberT1>(member_1)},
args{ forward<_MemberT2>(member_2)}
{}
};
struct Struct{
parser::CheckedQualifiers qualifiers;
ids::StructId value;
template<typename _MemberT0, typename _MemberT1>
Struct(_MemberT0&& member_0, _MemberT1&& member_1):
qualifiers{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct Enum{
parser::CheckedQualifiers qualifiers;
ids::EnumId value;
template<typename _MemberT0, typename _MemberT1>
Enum(_MemberT0&& member_0, _MemberT1&& member_1):
qualifiers{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct RawPtr{
parser::CheckedQualifiers qualifiers;
ids::TypeId value;
template<typename _MemberT0, typename _MemberT1>
RawPtr(_MemberT0&& member_0, _MemberT1&& member_1):
qualifiers{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct Trait{
parser::CheckedQualifiers qualifiers;
ids::TraitId value;
template<typename _MemberT0, typename _MemberT1>
Trait(_MemberT0&& member_0, _MemberT1&& member_1):
qualifiers{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct Reference{
parser::CheckedQualifiers qualifiers;
ids::TypeId value;
template<typename _MemberT0, typename _MemberT1>
Reference(_MemberT0&& member_0, _MemberT1&& member_1):
qualifiers{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct MutableReference{
parser::CheckedQualifiers qualifiers;
ids::TypeId value;
template<typename _MemberT0, typename _MemberT1>
MutableReference(_MemberT0&& member_0, _MemberT1&& member_1):
qualifiers{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct Function {
parser::CheckedQualifiers qualifiers;
JaktInternal::DynamicArray<ids::TypeId> params;
bool can_throw;
ids::TypeId return_type_id;
ids::FunctionId pseudo_function_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
qualifiers{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
can_throw{ forward<_MemberT2>(member_2)},
return_type_id{ forward<_MemberT3>(member_3)},
pseudo_function_id{ forward<_MemberT4>(member_4)}
{}
};
struct Self {
parser::CheckedQualifiers qualifiers;
template<typename _MemberT0>
Self(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
struct Const{
parser::CheckedQualifiers qualifiers;
types::Value value;
template<typename _MemberT0, typename _MemberT1>
Const(_MemberT0&& member_0, _MemberT1&& member_1):
qualifiers{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
}
struct Type : public Variant<Type_Details::Void, Type_Details::Bool, Type_Details::U8, Type_Details::U16, Type_Details::U32, Type_Details::U64, Type_Details::I8, Type_Details::I16, Type_Details::I32, Type_Details::I64, Type_Details::F32, Type_Details::F64, Type_Details::Usize, Type_Details::JaktString, Type_Details::CChar, Type_Details::CInt, Type_Details::Unknown, Type_Details::Never, Type_Details::TypeVariable, Type_Details::Dependent, Type_Details::GenericInstance, Type_Details::GenericEnumInstance, Type_Details::GenericTraitInstance, Type_Details::GenericResolvedType, Type_Details::Struct, Type_Details::Enum, Type_Details::RawPtr, Type_Details::Trait, Type_Details::Reference, Type_Details::MutableReference, Type_Details::Function, Type_Details::Self, Type_Details::Const>, public RefCounted<Type> {
using Variant<Type_Details::Void, Type_Details::Bool, Type_Details::U8, Type_Details::U16, Type_Details::U32, Type_Details::U64, Type_Details::I8, Type_Details::I16, Type_Details::I32, Type_Details::I64, Type_Details::F32, Type_Details::F64, Type_Details::Usize, Type_Details::JaktString, Type_Details::CChar, Type_Details::CInt, Type_Details::Unknown, Type_Details::Never, Type_Details::TypeVariable, Type_Details::Dependent, Type_Details::GenericInstance, Type_Details::GenericEnumInstance, Type_Details::GenericTraitInstance, Type_Details::GenericResolvedType, Type_Details::Struct, Type_Details::Enum, Type_Details::RawPtr, Type_Details::Trait, Type_Details::Reference, Type_Details::MutableReference, Type_Details::Function, Type_Details::Self, Type_Details::Const>::Variant;
    using Void = Type_Details::Void;
    using Bool = Type_Details::Bool;
    using U8 = Type_Details::U8;
    using U16 = Type_Details::U16;
    using U32 = Type_Details::U32;
    using U64 = Type_Details::U64;
    using I8 = Type_Details::I8;
    using I16 = Type_Details::I16;
    using I32 = Type_Details::I32;
    using I64 = Type_Details::I64;
    using F32 = Type_Details::F32;
    using F64 = Type_Details::F64;
    using Usize = Type_Details::Usize;
    using JaktString = Type_Details::JaktString;
    using CChar = Type_Details::CChar;
    using CInt = Type_Details::CInt;
    using Unknown = Type_Details::Unknown;
    using Never = Type_Details::Never;
    using TypeVariable = Type_Details::TypeVariable;
    using Dependent = Type_Details::Dependent;
    using GenericInstance = Type_Details::GenericInstance;
    using GenericEnumInstance = Type_Details::GenericEnumInstance;
    using GenericTraitInstance = Type_Details::GenericTraitInstance;
    using GenericResolvedType = Type_Details::GenericResolvedType;
    using Struct = Type_Details::Struct;
    using Enum = Type_Details::Enum;
    using RawPtr = Type_Details::RawPtr;
    using Trait = Type_Details::Trait;
    using Reference = Type_Details::Reference;
    using MutableReference = Type_Details::MutableReference;
    using Function = Type_Details::Function;
    using Self = Type_Details::Self;
    using Const = Type_Details::Const;
template<typename V, typename... Args> static auto __jakt_create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) Type(V(forward<Args>(args)...)));
}
ErrorOr<DeprecatedString> debug_description() const;
parser::CheckedQualifiers const& qualifiers() const { switch(this->index()) {case 0 /* Void */: return this->template get<Type::Void>().qualifiers;
case 1 /* Bool */: return this->template get<Type::Bool>().qualifiers;
case 2 /* U8 */: return this->template get<Type::U8>().qualifiers;
case 3 /* U16 */: return this->template get<Type::U16>().qualifiers;
case 4 /* U32 */: return this->template get<Type::U32>().qualifiers;
case 5 /* U64 */: return this->template get<Type::U64>().qualifiers;
case 6 /* I8 */: return this->template get<Type::I8>().qualifiers;
case 7 /* I16 */: return this->template get<Type::I16>().qualifiers;
case 8 /* I32 */: return this->template get<Type::I32>().qualifiers;
case 9 /* I64 */: return this->template get<Type::I64>().qualifiers;
case 10 /* F32 */: return this->template get<Type::F32>().qualifiers;
case 11 /* F64 */: return this->template get<Type::F64>().qualifiers;
case 12 /* Usize */: return this->template get<Type::Usize>().qualifiers;
case 13 /* JaktString */: return this->template get<Type::JaktString>().qualifiers;
case 14 /* CChar */: return this->template get<Type::CChar>().qualifiers;
case 15 /* CInt */: return this->template get<Type::CInt>().qualifiers;
case 16 /* Unknown */: return this->template get<Type::Unknown>().qualifiers;
case 17 /* Never */: return this->template get<Type::Never>().qualifiers;
case 18 /* TypeVariable */: return this->template get<Type::TypeVariable>().qualifiers;
case 19 /* Dependent */: return this->template get<Type::Dependent>().qualifiers;
case 20 /* GenericInstance */: return this->template get<Type::GenericInstance>().qualifiers;
case 21 /* GenericEnumInstance */: return this->template get<Type::GenericEnumInstance>().qualifiers;
case 22 /* GenericTraitInstance */: return this->template get<Type::GenericTraitInstance>().qualifiers;
case 23 /* GenericResolvedType */: return this->template get<Type::GenericResolvedType>().qualifiers;
case 24 /* Struct */: return this->template get<Type::Struct>().qualifiers;
case 25 /* Enum */: return this->template get<Type::Enum>().qualifiers;
case 26 /* RawPtr */: return this->template get<Type::RawPtr>().qualifiers;
case 27 /* Trait */: return this->template get<Type::Trait>().qualifiers;
case 28 /* Reference */: return this->template get<Type::Reference>().qualifiers;
case 29 /* MutableReference */: return this->template get<Type::MutableReference>().qualifiers;
case 30 /* Function */: return this->template get<Type::Function>().qualifiers;
case 31 /* Self */: return this->template get<Type::Self>().qualifiers;
case 32 /* Const */: return this->template get<Type::Const>().qualifiers;
default: VERIFY_NOT_REACHED();
}
}
u64 max() const;
bool equals(NonnullRefPtr<typename types::Type> const rhs) const;
ErrorOr<DeprecatedString> constructor_name() const;
bool is_concrete() const;
i64 get_bits() const;
i64 specificity(NonnullRefPtr<types::CheckedProgram> const program, i64 const base_specificity) const;
types::BuiltinType as_builtin_type() const;
bool is_builtin() const;
i64 min() const;
ErrorOr<ids::TypeId> flip_signedness() const;
bool is_boxed(NonnullRefPtr<types::CheckedProgram> const program) const;
bool is_signed() const;
};
class CheckedProgram :public RefCounted<CheckedProgram>, public Weakable<CheckedProgram> {
  public:
virtual ~CheckedProgram() = default;
public: NonnullRefPtr<compiler::Compiler> compiler;public: JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> modules;public: JaktInternal::Dictionary<DeprecatedString,types::LoadedModule> loaded_modules;public: ErrorOr<ids::TypeId> substitute_typevars_in_type(ids::TypeId const type_id, types::GenericInferences const generic_inferences, ids::ModuleId const module_id);
public: ids::ModuleId prelude_module_id() const;
public: ErrorOr<JaktInternal::Optional<ids::ScopeId>> find_namespace_in_immediate_children_of_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const treat_aliases_as_imports) const;
public: ErrorOr<ids::StructId> find_struct_in_prelude(DeprecatedString const name) const;
public: ErrorOr<NonnullRefPtr<types::Scope>> get_scope(ids::ScopeId const id) const;
public: bool is_floating(ids::TypeId const type_id) const;
public: ErrorOr<JaktInternal::Optional<ids::FunctionId>> find_default_constructors_in_scope(ids::ScopeId const parent_scope_id, DeprecatedString const function_name) const;
public: ErrorOr<JaktInternal::Optional<ids::StructId>> find_struct_in_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const ignore_mixin_scopes) const;
public: ErrorOr<JaktInternal::Optional<ids::TypeId>> find_type_in_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const ignore_mixin_scopes) const;
public: ErrorOr<void> set_loaded_module(DeprecatedString const module_name, types::LoadedModule const loaded_module);
public: ErrorOr<ids::ScopeId> find_type_scope_id(ids::TypeId const type_id);
public: bool is_integer(ids::TypeId const type_id) const;
public: ErrorOr<ids::ScopeId> create_scope(JaktInternal::Optional<ids::ScopeId> const parent_scope_id, bool const can_throw, DeprecatedString const debug_name, ids::ModuleId const module_id, bool const for_block);
public: NonnullRefPtr<types::Module> get_module(ids::ModuleId const id) const;
public: ErrorOr<DeprecatedString> type_name(ids::TypeId const type_id, bool const debug_mode) const;
private: ErrorOr<JaktInternal::Optional<bool>> for_each_scope_accessible_unqualified_from_scope_impl(ids::ScopeId const scope_id, Function<ErrorOr<typename utility::IterationDecision<bool>>(ids::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback, bool const ignore_mixin_scopes) const;
public: ErrorOr<bool> is_scope_directly_accessible_from(ids::ScopeId const check_scope_id, ids::ScopeId const scope_id, bool const ignore_mixin_scopes) const;
public: ErrorOr<bool> is_string(ids::TypeId const type_id) const;
public: ids::ScopeId prelude_scope_id() const;
public: NonnullRefPtr<types::CheckedTrait> get_trait(ids::TraitId const id) const;
public: NonnullRefPtr<types::CheckedVariable> get_variable(ids::VarId const id) const;
public: protected:
explicit CheckedProgram(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> a_modules, JaktInternal::Dictionary<DeprecatedString,types::LoadedModule> a_loaded_modules);
public:
static ErrorOr<NonnullRefPtr<CheckedProgram>> __jakt_create(NonnullRefPtr<compiler::Compiler> compiler, JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> modules, JaktInternal::Dictionary<DeprecatedString,types::LoadedModule> loaded_modules);

public: ErrorOr<ids::ModuleId> create_module(DeprecatedString const name, bool const is_root, JaktInternal::Optional<DeprecatedString> const path);
public: NonnullRefPtr<types::CheckedFunction> get_function(ids::FunctionId const id) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> find_type_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const ignore_mixin_scopes) const;
public: ErrorOr<ids::StructId> builtin_implementation_struct(types::BuiltinType const builtin, ids::ModuleId const for_module);
public: ErrorOr<JaktInternal::Optional<types::Value>> find_comptime_binding_in_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const ignore_mixin_scopes) const;
private: ErrorOr<ids::TypeId> substitute_typevars_in_type_helper(ids::TypeId const type_id, types::GenericInferences const generic_inferences, ids::ModuleId const module_id);
private: ErrorOr<JaktInternal::Optional<bool>> for_each_scope_accessible_unqualified_from_scope_direct_chain(ids::ScopeId const scope_id, Function<ErrorOr<typename utility::IterationDecision<bool>>(ids::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const;
public: i64 get_bits(ids::TypeId const type_id) const;
public: NonnullRefPtr<typename types::Type> get_type(ids::TypeId const id) const;
public: ErrorOr<ids::TypeId> find_or_add_type_id(NonnullRefPtr<typename types::Type> const type, ids::ModuleId const module_id, bool const only_in_current_module);
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>>> find_namespace_in_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const treat_aliases_as_imports, bool const ignore_mixin_scopes) const;
public: ErrorOr<JaktInternal::Optional<ids::TraitId>> find_trait_in_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const ignore_mixin_scopes) const;
public: types::CheckedEnum get_enum(ids::EnumId const id) const;
public: ErrorOr<ids::TypeId> apply_qualifiers_to_type(parser::CheckedQualifiers const qualifiers, ids::TypeId const type_id);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>>> find_functions_with_name_in_scope(ids::ScopeId const parent_scope_id, DeprecatedString const function_name, bool const ignore_mixin_scopes) const;
public: ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> find_var_in_scope(ids::ScopeId const scope_id, DeprecatedString const var, bool const ignore_mixin_scopes) const;
public: ErrorOr<JaktInternal::Optional<ids::FunctionId>> find_function_in_scope(ids::ScopeId const parent_scope_id, DeprecatedString const function_name) const;
public: types::CheckedStruct get_struct(ids::StructId const id) const;
public: ErrorOr<JaktInternal::Optional<ids::StructId>> check_and_extract_weak_ptr(ids::StructId const struct_id, JaktInternal::DynamicArray<ids::TypeId> const args) const;
public: ErrorOr<JaktInternal::Optional<ids::EnumId>> find_enum_in_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const ignore_mixin_scopes) const;
public: JaktInternal::Optional<types::LoadedModule> get_loaded_module(DeprecatedString const module_name) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> find_scoped_functions_with_name_in_scope(ids::ScopeId const parent_scope_id, DeprecatedString const function_name, bool const ignore_mixin_scopes) const;
public: bool is_signed(ids::TypeId const type_id) const;
public: bool is_numeric(ids::TypeId const type_id) const;
public: template <typename T>
ErrorOr<JaktInternal::Optional<T>> for_each_scope_accessible_unqualified_from_scope(ids::ScopeId const scope_id, Function<ErrorOr<typename utility::IterationDecision<T>>(ids::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback, bool const ignore_mixin_scopes) const;
public: public: public: public: public: public: public: public: public: public: ErrorOr<types::StructOrEnumId> find_reflected_primitive(DeprecatedString const primitive) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace CheckedCapture_Details {
struct ByValue {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByValue(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByReference {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByReference(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByMutableReference {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByMutableReference(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByComptimeDependency {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByComptimeDependency(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct AllByReference {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
AllByReference(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct CheckedCapture : public Variant<CheckedCapture_Details::ByValue, CheckedCapture_Details::ByReference, CheckedCapture_Details::ByMutableReference, CheckedCapture_Details::ByComptimeDependency, CheckedCapture_Details::AllByReference> {
using Variant<CheckedCapture_Details::ByValue, CheckedCapture_Details::ByReference, CheckedCapture_Details::ByMutableReference, CheckedCapture_Details::ByComptimeDependency, CheckedCapture_Details::AllByReference>::Variant;
    using ByValue = CheckedCapture_Details::ByValue;
    using ByReference = CheckedCapture_Details::ByReference;
    using ByMutableReference = CheckedCapture_Details::ByMutableReference;
    using ByComptimeDependency = CheckedCapture_Details::ByComptimeDependency;
    using AllByReference = CheckedCapture_Details::AllByReference;
ErrorOr<DeprecatedString> debug_description() const;
DeprecatedString const& name() const { switch(this->index()) {case 0 /* ByValue */: return this->template get<CheckedCapture::ByValue>().name;
case 1 /* ByReference */: return this->template get<CheckedCapture::ByReference>().name;
case 2 /* ByMutableReference */: return this->template get<CheckedCapture::ByMutableReference>().name;
case 3 /* ByComptimeDependency */: return this->template get<CheckedCapture::ByComptimeDependency>().name;
case 4 /* AllByReference */: return this->template get<CheckedCapture::AllByReference>().name;
default: VERIFY_NOT_REACHED();
}
}
utility::Span const& span() const { switch(this->index()) {case 0 /* ByValue */: return this->template get<CheckedCapture::ByValue>().span;
case 1 /* ByReference */: return this->template get<CheckedCapture::ByReference>().span;
case 2 /* ByMutableReference */: return this->template get<CheckedCapture::ByMutableReference>().span;
case 3 /* ByComptimeDependency */: return this->template get<CheckedCapture::ByComptimeDependency>().span;
case 4 /* AllByReference */: return this->template get<CheckedCapture::AllByReference>().span;
default: VERIFY_NOT_REACHED();
}
}
};
struct GenericInferences {
  public:
public: JaktInternal::Dictionary<ids::TypeId,ids::TypeId> values;public: ErrorOr<void> set_all(JaktInternal::DynamicArray<types::CheckedGenericParameter> const keys, JaktInternal::DynamicArray<ids::TypeId> const values);
public: ErrorOr<void> set_from(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const checkpoint);
public: ErrorOr<JaktInternal::Optional<ids::TypeId>> find_and_map(DeprecatedString const name, NonnullRefPtr<types::CheckedProgram> const& program) const;
public: GenericInferences(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> a_values);

public: void restore(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const checkpoint);
public: ErrorOr<void> debug_description(NonnullRefPtr<types::CheckedProgram> const& program) const;
public: ids::TypeId map(ids::TypeId const type) const;
public: ErrorOr<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> perform_checkpoint(bool const reset);
public: JaktInternal::Optional<ids::TypeId> get(ids::TypeId const key) const;
public: JaktInternal::Dictionary<ids::TypeId,ids::TypeId> iterator() const;
public: ErrorOr<void> set(ids::TypeId const key, ids::TypeId const value);
public: ErrorOr<DeprecatedString> debug_description() const;
};struct CheckedBinaryOperator {
  public:
public: parser::BinaryOperator op;public: JaktInternal::Optional<types::OperatorTraitImplementation> trait_implementation;public: CheckedBinaryOperator(parser::BinaryOperator a_op, JaktInternal::Optional<types::OperatorTraitImplementation> a_trait_implementation);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace CheckedExpression_Details {
struct Boolean {
bool val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Boolean(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct NumericConstant {
types::CheckedNumericConstant val;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
NumericConstant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct QuotedString {
types::CheckedStringLiteral val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
QuotedString(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByteConstant {
DeprecatedString val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByteConstant(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct CharacterConstant {
DeprecatedString val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
CharacterConstant(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct CCharacterConstant {
DeprecatedString val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
CCharacterConstant(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct UnaryOp {
NonnullRefPtr<typename types::CheckedExpression> expr;
types::CheckedUnaryOperator op;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
UnaryOp(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
op{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)}
{}
};
struct BinaryOp {
NonnullRefPtr<typename types::CheckedExpression> lhs;
types::CheckedBinaryOperator op;
NonnullRefPtr<typename types::CheckedExpression> rhs;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
BinaryOp(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
lhs{ forward<_MemberT0>(member_0)},
op{ forward<_MemberT1>(member_1)},
rhs{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)},
type_id{ forward<_MemberT4>(member_4)}
{}
};
struct JaktTuple {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
JaktTuple(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
vals{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct Range {
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> to;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Range(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
from{ forward<_MemberT0>(member_0)},
to{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)}
{}
};
struct JaktArray {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> repeat;
utility::Span span;
ids::TypeId type_id;
ids::TypeId inner_type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
JaktArray(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
vals{ forward<_MemberT0>(member_0)},
repeat{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)},
inner_type_id{ forward<_MemberT4>(member_4)}
{}
};
struct JaktSet {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals;
utility::Span span;
ids::TypeId type_id;
ids::TypeId inner_type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
JaktSet(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
vals{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)},
inner_type_id{ forward<_MemberT3>(member_3)}
{}
};
struct JaktDictionary {
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> vals;
utility::Span span;
ids::TypeId type_id;
ids::TypeId key_type_id;
ids::TypeId value_type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
JaktDictionary(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
vals{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)},
key_type_id{ forward<_MemberT3>(member_3)},
value_type_id{ forward<_MemberT4>(member_4)}
{}
};
struct IndexedExpression {
NonnullRefPtr<typename types::CheckedExpression> expr;
NonnullRefPtr<typename types::CheckedExpression> index;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
IndexedExpression(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)}
{}
};
struct IndexedDictionary {
NonnullRefPtr<typename types::CheckedExpression> expr;
NonnullRefPtr<typename types::CheckedExpression> index;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
IndexedDictionary(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)}
{}
};
struct IndexedTuple {
NonnullRefPtr<typename types::CheckedExpression> expr;
size_t index;
utility::Span span;
bool is_optional;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
IndexedTuple(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
is_optional{ forward<_MemberT3>(member_3)},
type_id{ forward<_MemberT4>(member_4)}
{}
};
struct IndexedStruct {
NonnullRefPtr<typename types::CheckedExpression> expr;
DeprecatedString name;
JaktInternal::Optional<ids::VarId> index;
utility::Span span;
bool is_optional;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5>
IndexedStruct(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5):
expr{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
index{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)},
is_optional{ forward<_MemberT4>(member_4)},
type_id{ forward<_MemberT5>(member_5)}
{}
};
struct IndexedCommonEnumMember {
NonnullRefPtr<typename types::CheckedExpression> expr;
DeprecatedString index;
utility::Span span;
bool is_optional;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
IndexedCommonEnumMember(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
is_optional{ forward<_MemberT3>(member_3)},
type_id{ forward<_MemberT4>(member_4)}
{}
};
struct ComptimeIndex {
NonnullRefPtr<typename types::CheckedExpression> expr;
NonnullRefPtr<typename types::CheckedExpression> index;
bool is_optional;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
ComptimeIndex(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
is_optional{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Match {
NonnullRefPtr<typename types::CheckedExpression> expr;
JaktInternal::DynamicArray<types::CheckedMatchCase> match_cases;
utility::Span span;
ids::TypeId type_id;
bool all_variants_constant;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
Match(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
expr{ forward<_MemberT0>(member_0)},
match_cases{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)},
all_variants_constant{ forward<_MemberT4>(member_4)}
{}
};
struct EnumVariantArg {
NonnullRefPtr<typename types::CheckedExpression> expr;
types::CheckedEnumVariantBinding arg;
types::CheckedEnumVariant enum_variant;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
EnumVariantArg(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
arg{ forward<_MemberT1>(member_1)},
enum_variant{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Call {
types::CheckedCall call;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Call(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
call{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct MethodCall {
NonnullRefPtr<typename types::CheckedExpression> expr;
types::CheckedCall call;
utility::Span span;
bool is_optional;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
MethodCall(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
expr{ forward<_MemberT0>(member_0)},
call{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
is_optional{ forward<_MemberT3>(member_3)},
type_id{ forward<_MemberT4>(member_4)}
{}
};
struct NamespacedVar {
JaktInternal::DynamicArray<types::CheckedNamespace> namespaces;
NonnullRefPtr<types::CheckedVariable> var;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
NamespacedVar(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
namespaces{ forward<_MemberT0>(member_0)},
var{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Var {
NonnullRefPtr<types::CheckedVariable> var;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Var(_MemberT0&& member_0, _MemberT1&& member_1):
var{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct OptionalNone {
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1>
OptionalNone(_MemberT0&& member_0, _MemberT1&& member_1):
span{ forward<_MemberT0>(member_0)},
type_id{ forward<_MemberT1>(member_1)}
{}
};
struct OptionalSome {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
OptionalSome(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct ForcedUnwrap {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
ForcedUnwrap(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct Block {
types::CheckedBlock block;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Block(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct Function {
JaktInternal::DynamicArray<types::CheckedCapture> captures;
JaktInternal::DynamicArray<types::CheckedParameter> params;
bool can_throw;
ids::TypeId return_type_id;
types::CheckedBlock block;
utility::Span span;
ids::TypeId type_id;
JaktInternal::Optional<ids::FunctionId> pseudo_function_id;
ids::ScopeId scope_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6, typename _MemberT7, typename _MemberT8>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6, _MemberT7&& member_7, _MemberT8&& member_8):
captures{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
can_throw{ forward<_MemberT2>(member_2)},
return_type_id{ forward<_MemberT3>(member_3)},
block{ forward<_MemberT4>(member_4)},
span{ forward<_MemberT5>(member_5)},
type_id{ forward<_MemberT6>(member_6)},
pseudo_function_id{ forward<_MemberT7>(member_7)},
scope_id{ forward<_MemberT8>(member_8)}
{}
};
struct DependentFunction {
JaktInternal::DynamicArray<types::CheckedCapture> captures;
JaktInternal::DynamicArray<types::CheckedParameter> params;
bool can_throw;
ids::TypeId return_type_id;
parser::ParsedBlock block;
utility::Span span;
ids::TypeId type_id;
JaktInternal::Optional<ids::FunctionId> pseudo_function_id;
ids::ScopeId scope_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6, typename _MemberT7, typename _MemberT8>
DependentFunction(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6, _MemberT7&& member_7, _MemberT8&& member_8):
captures{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
can_throw{ forward<_MemberT2>(member_2)},
return_type_id{ forward<_MemberT3>(member_3)},
block{ forward<_MemberT4>(member_4)},
span{ forward<_MemberT5>(member_5)},
type_id{ forward<_MemberT6>(member_6)},
pseudo_function_id{ forward<_MemberT7>(member_7)},
scope_id{ forward<_MemberT8>(member_8)}
{}
};
struct Try {
NonnullRefPtr<typename types::CheckedExpression> expr;
JaktInternal::Optional<types::CheckedBlock> catch_block;
JaktInternal::Optional<utility::Span> catch_span;
JaktInternal::Optional<DeprecatedString> catch_name;
utility::Span span;
ids::TypeId type_id;
ids::TypeId inner_type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6>
Try(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6):
expr{ forward<_MemberT0>(member_0)},
catch_block{ forward<_MemberT1>(member_1)},
catch_span{ forward<_MemberT2>(member_2)},
catch_name{ forward<_MemberT3>(member_3)},
span{ forward<_MemberT4>(member_4)},
type_id{ forward<_MemberT5>(member_5)},
inner_type_id{ forward<_MemberT6>(member_6)}
{}
};
struct TryBlock {
NonnullRefPtr<typename types::CheckedStatement> stmt;
types::CheckedBlock catch_block;
DeprecatedString error_name;
utility::Span error_span;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5>
TryBlock(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5):
stmt{ forward<_MemberT0>(member_0)},
catch_block{ forward<_MemberT1>(member_1)},
error_name{ forward<_MemberT2>(member_2)},
error_span{ forward<_MemberT3>(member_3)},
span{ forward<_MemberT4>(member_4)},
type_id{ forward<_MemberT5>(member_5)}
{}
};
struct Reflect {
ids::TypeId type;
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Reflect(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
type{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct Garbage {
utility::Span span;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1>
Garbage(_MemberT0&& member_0, _MemberT1&& member_1):
span{ forward<_MemberT0>(member_0)},
type_id{ forward<_MemberT1>(member_1)}
{}
};
}
struct CheckedExpression : public Variant<CheckedExpression_Details::Boolean, CheckedExpression_Details::NumericConstant, CheckedExpression_Details::QuotedString, CheckedExpression_Details::ByteConstant, CheckedExpression_Details::CharacterConstant, CheckedExpression_Details::CCharacterConstant, CheckedExpression_Details::UnaryOp, CheckedExpression_Details::BinaryOp, CheckedExpression_Details::JaktTuple, CheckedExpression_Details::Range, CheckedExpression_Details::JaktArray, CheckedExpression_Details::JaktSet, CheckedExpression_Details::JaktDictionary, CheckedExpression_Details::IndexedExpression, CheckedExpression_Details::IndexedDictionary, CheckedExpression_Details::IndexedTuple, CheckedExpression_Details::IndexedStruct, CheckedExpression_Details::IndexedCommonEnumMember, CheckedExpression_Details::ComptimeIndex, CheckedExpression_Details::Match, CheckedExpression_Details::EnumVariantArg, CheckedExpression_Details::Call, CheckedExpression_Details::MethodCall, CheckedExpression_Details::NamespacedVar, CheckedExpression_Details::Var, CheckedExpression_Details::OptionalNone, CheckedExpression_Details::OptionalSome, CheckedExpression_Details::ForcedUnwrap, CheckedExpression_Details::Block, CheckedExpression_Details::Function, CheckedExpression_Details::DependentFunction, CheckedExpression_Details::Try, CheckedExpression_Details::TryBlock, CheckedExpression_Details::Reflect, CheckedExpression_Details::Garbage>, public RefCounted<CheckedExpression> {
using Variant<CheckedExpression_Details::Boolean, CheckedExpression_Details::NumericConstant, CheckedExpression_Details::QuotedString, CheckedExpression_Details::ByteConstant, CheckedExpression_Details::CharacterConstant, CheckedExpression_Details::CCharacterConstant, CheckedExpression_Details::UnaryOp, CheckedExpression_Details::BinaryOp, CheckedExpression_Details::JaktTuple, CheckedExpression_Details::Range, CheckedExpression_Details::JaktArray, CheckedExpression_Details::JaktSet, CheckedExpression_Details::JaktDictionary, CheckedExpression_Details::IndexedExpression, CheckedExpression_Details::IndexedDictionary, CheckedExpression_Details::IndexedTuple, CheckedExpression_Details::IndexedStruct, CheckedExpression_Details::IndexedCommonEnumMember, CheckedExpression_Details::ComptimeIndex, CheckedExpression_Details::Match, CheckedExpression_Details::EnumVariantArg, CheckedExpression_Details::Call, CheckedExpression_Details::MethodCall, CheckedExpression_Details::NamespacedVar, CheckedExpression_Details::Var, CheckedExpression_Details::OptionalNone, CheckedExpression_Details::OptionalSome, CheckedExpression_Details::ForcedUnwrap, CheckedExpression_Details::Block, CheckedExpression_Details::Function, CheckedExpression_Details::DependentFunction, CheckedExpression_Details::Try, CheckedExpression_Details::TryBlock, CheckedExpression_Details::Reflect, CheckedExpression_Details::Garbage>::Variant;
    using Boolean = CheckedExpression_Details::Boolean;
    using NumericConstant = CheckedExpression_Details::NumericConstant;
    using QuotedString = CheckedExpression_Details::QuotedString;
    using ByteConstant = CheckedExpression_Details::ByteConstant;
    using CharacterConstant = CheckedExpression_Details::CharacterConstant;
    using CCharacterConstant = CheckedExpression_Details::CCharacterConstant;
    using UnaryOp = CheckedExpression_Details::UnaryOp;
    using BinaryOp = CheckedExpression_Details::BinaryOp;
    using JaktTuple = CheckedExpression_Details::JaktTuple;
    using Range = CheckedExpression_Details::Range;
    using JaktArray = CheckedExpression_Details::JaktArray;
    using JaktSet = CheckedExpression_Details::JaktSet;
    using JaktDictionary = CheckedExpression_Details::JaktDictionary;
    using IndexedExpression = CheckedExpression_Details::IndexedExpression;
    using IndexedDictionary = CheckedExpression_Details::IndexedDictionary;
    using IndexedTuple = CheckedExpression_Details::IndexedTuple;
    using IndexedStruct = CheckedExpression_Details::IndexedStruct;
    using IndexedCommonEnumMember = CheckedExpression_Details::IndexedCommonEnumMember;
    using ComptimeIndex = CheckedExpression_Details::ComptimeIndex;
    using Match = CheckedExpression_Details::Match;
    using EnumVariantArg = CheckedExpression_Details::EnumVariantArg;
    using Call = CheckedExpression_Details::Call;
    using MethodCall = CheckedExpression_Details::MethodCall;
    using NamespacedVar = CheckedExpression_Details::NamespacedVar;
    using Var = CheckedExpression_Details::Var;
    using OptionalNone = CheckedExpression_Details::OptionalNone;
    using OptionalSome = CheckedExpression_Details::OptionalSome;
    using ForcedUnwrap = CheckedExpression_Details::ForcedUnwrap;
    using Block = CheckedExpression_Details::Block;
    using Function = CheckedExpression_Details::Function;
    using DependentFunction = CheckedExpression_Details::DependentFunction;
    using Try = CheckedExpression_Details::Try;
    using TryBlock = CheckedExpression_Details::TryBlock;
    using Reflect = CheckedExpression_Details::Reflect;
    using Garbage = CheckedExpression_Details::Garbage;
template<typename V, typename... Args> static auto __jakt_create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) CheckedExpression(V(forward<Args>(args)...)));
}
ErrorOr<DeprecatedString> debug_description() const;
bool can_throw() const;
JaktInternal::Optional<types::NumberConstant> to_number_constant(NonnullRefPtr<types::CheckedProgram> const program) const;
utility::Span span() const;
ids::TypeId type() const;
ErrorOr<types::BlockControlFlow> control_flow() const;
bool is_mutable(NonnullRefPtr<types::CheckedProgram> const program) const;
};
namespace NumberConstant_Details {
struct Signed{
i64 value;
template<typename _MemberT0>
Signed(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Unsigned{
u64 value;
template<typename _MemberT0>
Unsigned(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Floating{
f64 value;
template<typename _MemberT0>
Floating(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct NumberConstant : public Variant<NumberConstant_Details::Signed, NumberConstant_Details::Unsigned, NumberConstant_Details::Floating> {
using Variant<NumberConstant_Details::Signed, NumberConstant_Details::Unsigned, NumberConstant_Details::Floating>::Variant;
    using Signed = NumberConstant_Details::Signed;
    using Unsigned = NumberConstant_Details::Unsigned;
    using Floating = NumberConstant_Details::Floating;
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<bool> can_fit_number(ids::TypeId const type_id, NonnullRefPtr<types::CheckedProgram> const program) const;
ErrorOr<size_t> to_usize() const;
};
namespace ValueImpl_Details {
struct Void {
};
struct Bool{
bool value;
template<typename _MemberT0>
Bool(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U8{
u8 value;
template<typename _MemberT0>
U8(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U16{
u16 value;
template<typename _MemberT0>
U16(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U32{
u32 value;
template<typename _MemberT0>
U32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U64{
u64 value;
template<typename _MemberT0>
U64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I8{
i8 value;
template<typename _MemberT0>
I8(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I16{
i16 value;
template<typename _MemberT0>
I16(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I32{
i32 value;
template<typename _MemberT0>
I32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I64{
i64 value;
template<typename _MemberT0>
I64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct F32{
f32 value;
template<typename _MemberT0>
F32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct F64{
f64 value;
template<typename _MemberT0>
F64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct USize{
size_t value;
template<typename _MemberT0>
USize(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct JaktString{
DeprecatedString value;
template<typename _MemberT0>
JaktString(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct StringView{
DeprecatedString value;
template<typename _MemberT0>
StringView(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct CChar{
char value;
template<typename _MemberT0>
CChar(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct CInt{
int value;
template<typename _MemberT0>
CInt(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Struct {
JaktInternal::DynamicArray<types::Value> fields;
ids::StructId struct_id;
JaktInternal::Optional<ids::FunctionId> constructor;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Struct(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
fields{ forward<_MemberT0>(member_0)},
struct_id{ forward<_MemberT1>(member_1)},
constructor{ forward<_MemberT2>(member_2)}
{}
};
struct Class {
JaktInternal::DynamicArray<types::Value> fields;
ids::StructId struct_id;
JaktInternal::Optional<ids::FunctionId> constructor;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Class(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
fields{ forward<_MemberT0>(member_0)},
struct_id{ forward<_MemberT1>(member_1)},
constructor{ forward<_MemberT2>(member_2)}
{}
};
struct Enum {
JaktInternal::DynamicArray<types::Value> fields;
ids::EnumId enum_id;
ids::FunctionId constructor;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Enum(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
fields{ forward<_MemberT0>(member_0)},
enum_id{ forward<_MemberT1>(member_1)},
constructor{ forward<_MemberT2>(member_2)}
{}
};
struct JaktArray {
JaktInternal::DynamicArray<types::Value> values;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1>
JaktArray(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
type_id{ forward<_MemberT1>(member_1)}
{}
};
struct JaktDictionary {
JaktInternal::DynamicArray<types::Value> keys;
JaktInternal::DynamicArray<types::Value> values;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
JaktDictionary(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
keys{ forward<_MemberT0>(member_0)},
values{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct JaktSet {
JaktInternal::DynamicArray<types::Value> values;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1>
JaktSet(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
type_id{ forward<_MemberT1>(member_1)}
{}
};
struct RawPtr{
NonnullRefPtr<typename types::ValueImpl> value;
template<typename _MemberT0>
RawPtr(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct OptionalSome {
types::Value value;
template<typename _MemberT0>
OptionalSome(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct OptionalNone {
};
struct JaktTuple {
JaktInternal::DynamicArray<types::Value> fields;
ids::TypeId type_id;
template<typename _MemberT0, typename _MemberT1>
JaktTuple(_MemberT0&& member_0, _MemberT1&& member_1):
fields{ forward<_MemberT0>(member_0)},
type_id{ forward<_MemberT1>(member_1)}
{}
};
struct Function {
JaktInternal::Dictionary<DeprecatedString,types::Value> captures;
JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>>>> params;
ids::TypeId return_type_id;
ids::TypeId type_id;
types::CheckedBlock block;
bool can_throw;
JaktInternal::DynamicArray<types::CheckedParameter> checked_params;
ids::ScopeId scope_id;
JaktInternal::Optional<ids::FunctionId> pseudo_function_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6, typename _MemberT7, typename _MemberT8>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6, _MemberT7&& member_7, _MemberT8&& member_8):
captures{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
return_type_id{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)},
block{ forward<_MemberT4>(member_4)},
can_throw{ forward<_MemberT5>(member_5)},
checked_params{ forward<_MemberT6>(member_6)},
scope_id{ forward<_MemberT7>(member_7)},
pseudo_function_id{ forward<_MemberT8>(member_8)}
{}
};
}
struct ValueImpl : public Variant<ValueImpl_Details::Void, ValueImpl_Details::Bool, ValueImpl_Details::U8, ValueImpl_Details::U16, ValueImpl_Details::U32, ValueImpl_Details::U64, ValueImpl_Details::I8, ValueImpl_Details::I16, ValueImpl_Details::I32, ValueImpl_Details::I64, ValueImpl_Details::F32, ValueImpl_Details::F64, ValueImpl_Details::USize, ValueImpl_Details::JaktString, ValueImpl_Details::StringView, ValueImpl_Details::CChar, ValueImpl_Details::CInt, ValueImpl_Details::Struct, ValueImpl_Details::Class, ValueImpl_Details::Enum, ValueImpl_Details::JaktArray, ValueImpl_Details::JaktDictionary, ValueImpl_Details::JaktSet, ValueImpl_Details::RawPtr, ValueImpl_Details::OptionalSome, ValueImpl_Details::OptionalNone, ValueImpl_Details::JaktTuple, ValueImpl_Details::Function>, public RefCounted<ValueImpl> {
using Variant<ValueImpl_Details::Void, ValueImpl_Details::Bool, ValueImpl_Details::U8, ValueImpl_Details::U16, ValueImpl_Details::U32, ValueImpl_Details::U64, ValueImpl_Details::I8, ValueImpl_Details::I16, ValueImpl_Details::I32, ValueImpl_Details::I64, ValueImpl_Details::F32, ValueImpl_Details::F64, ValueImpl_Details::USize, ValueImpl_Details::JaktString, ValueImpl_Details::StringView, ValueImpl_Details::CChar, ValueImpl_Details::CInt, ValueImpl_Details::Struct, ValueImpl_Details::Class, ValueImpl_Details::Enum, ValueImpl_Details::JaktArray, ValueImpl_Details::JaktDictionary, ValueImpl_Details::JaktSet, ValueImpl_Details::RawPtr, ValueImpl_Details::OptionalSome, ValueImpl_Details::OptionalNone, ValueImpl_Details::JaktTuple, ValueImpl_Details::Function>::Variant;
    using Void = ValueImpl_Details::Void;
    using Bool = ValueImpl_Details::Bool;
    using U8 = ValueImpl_Details::U8;
    using U16 = ValueImpl_Details::U16;
    using U32 = ValueImpl_Details::U32;
    using U64 = ValueImpl_Details::U64;
    using I8 = ValueImpl_Details::I8;
    using I16 = ValueImpl_Details::I16;
    using I32 = ValueImpl_Details::I32;
    using I64 = ValueImpl_Details::I64;
    using F32 = ValueImpl_Details::F32;
    using F64 = ValueImpl_Details::F64;
    using USize = ValueImpl_Details::USize;
    using JaktString = ValueImpl_Details::JaktString;
    using StringView = ValueImpl_Details::StringView;
    using CChar = ValueImpl_Details::CChar;
    using CInt = ValueImpl_Details::CInt;
    using Struct = ValueImpl_Details::Struct;
    using Class = ValueImpl_Details::Class;
    using Enum = ValueImpl_Details::Enum;
    using JaktArray = ValueImpl_Details::JaktArray;
    using JaktDictionary = ValueImpl_Details::JaktDictionary;
    using JaktSet = ValueImpl_Details::JaktSet;
    using RawPtr = ValueImpl_Details::RawPtr;
    using OptionalSome = ValueImpl_Details::OptionalSome;
    using OptionalNone = ValueImpl_Details::OptionalNone;
    using JaktTuple = ValueImpl_Details::JaktTuple;
    using Function = ValueImpl_Details::Function;
template<typename V, typename... Args> static auto __jakt_create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) ValueImpl(V(forward<Args>(args)...)));
}
ErrorOr<DeprecatedString> debug_description() const;
bool equals(NonnullRefPtr<typename types::ValueImpl> const other) const;
ErrorOr<ids::TypeId> type_id(NonnullRefPtr<types::CheckedProgram>& program) const;
ErrorOr<NonnullRefPtr<typename types::ValueImpl>> copy() const;
};
class Scope :public RefCounted<Scope>, public Weakable<Scope> {
  public:
virtual ~Scope() = default;
public: JaktInternal::Optional<DeprecatedString> namespace_name;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Dictionary<DeprecatedString,ids::VarId> vars;public: JaktInternal::Dictionary<DeprecatedString,types::Value> comptime_bindings;public: JaktInternal::Dictionary<DeprecatedString,ids::StructId> structs;public: JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<ids::FunctionId>> functions;public: JaktInternal::Dictionary<DeprecatedString,ids::EnumId> enums;public: JaktInternal::Dictionary<DeprecatedString,ids::TypeId> types;public: JaktInternal::Dictionary<DeprecatedString,ids::TraitId> traits;public: JaktInternal::Dictionary<DeprecatedString,ids::ModuleId> imports;public: JaktInternal::Dictionary<DeprecatedString,ids::ScopeId> aliases;public: JaktInternal::Optional<ids::ScopeId> parent;public: JaktInternal::Optional<ids::ScopeId> alias_scope;public: JaktInternal::DynamicArray<ids::ScopeId> children;public: bool can_throw;public: JaktInternal::Optional<DeprecatedString> import_path_if_extern;public: JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> alias_path;public: JaktInternal::DynamicArray<parser::IncludeAction> after_extern_include;public: JaktInternal::DynamicArray<parser::IncludeAction> before_extern_include;public: DeprecatedString debug_name;public: JaktInternal::DynamicArray<ids::ScopeId> resolution_mixins;public: bool is_block_scope;public: JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> resolved_forall_chunks;public: JaktInternal::Dictionary<DeprecatedString,types::SpecializedType> explicitly_specialized_types;public: protected:
explicit Scope(JaktInternal::Optional<DeprecatedString> a_namespace_name, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Dictionary<DeprecatedString,ids::VarId> a_vars, JaktInternal::Dictionary<DeprecatedString,types::Value> a_comptime_bindings, JaktInternal::Dictionary<DeprecatedString,ids::StructId> a_structs, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<ids::FunctionId>> a_functions, JaktInternal::Dictionary<DeprecatedString,ids::EnumId> a_enums, JaktInternal::Dictionary<DeprecatedString,ids::TypeId> a_types, JaktInternal::Dictionary<DeprecatedString,ids::TraitId> a_traits, JaktInternal::Dictionary<DeprecatedString,ids::ModuleId> a_imports, JaktInternal::Dictionary<DeprecatedString,ids::ScopeId> a_aliases, JaktInternal::Optional<ids::ScopeId> a_parent, JaktInternal::Optional<ids::ScopeId> a_alias_scope, JaktInternal::DynamicArray<ids::ScopeId> a_children, bool a_can_throw, JaktInternal::Optional<DeprecatedString> a_import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> a_alias_path, JaktInternal::DynamicArray<parser::IncludeAction> a_after_extern_include, JaktInternal::DynamicArray<parser::IncludeAction> a_before_extern_include, DeprecatedString a_debug_name, JaktInternal::DynamicArray<ids::ScopeId> a_resolution_mixins, bool a_is_block_scope, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> a_resolved_forall_chunks, JaktInternal::Dictionary<DeprecatedString,types::SpecializedType> a_explicitly_specialized_types);
public:
static ErrorOr<NonnullRefPtr<Scope>> __jakt_create(JaktInternal::Optional<DeprecatedString> namespace_name, JaktInternal::Optional<parser::ExternalName> external_name, JaktInternal::Dictionary<DeprecatedString,ids::VarId> vars, JaktInternal::Dictionary<DeprecatedString,types::Value> comptime_bindings, JaktInternal::Dictionary<DeprecatedString,ids::StructId> structs, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<ids::FunctionId>> functions, JaktInternal::Dictionary<DeprecatedString,ids::EnumId> enums, JaktInternal::Dictionary<DeprecatedString,ids::TypeId> types, JaktInternal::Dictionary<DeprecatedString,ids::TraitId> traits, JaktInternal::Dictionary<DeprecatedString,ids::ModuleId> imports, JaktInternal::Dictionary<DeprecatedString,ids::ScopeId> aliases, JaktInternal::Optional<ids::ScopeId> parent, JaktInternal::Optional<ids::ScopeId> alias_scope, JaktInternal::DynamicArray<ids::ScopeId> children, bool can_throw, JaktInternal::Optional<DeprecatedString> import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> alias_path, JaktInternal::DynamicArray<parser::IncludeAction> after_extern_include, JaktInternal::DynamicArray<parser::IncludeAction> before_extern_include, DeprecatedString debug_name, JaktInternal::DynamicArray<ids::ScopeId> resolution_mixins, bool is_block_scope, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> resolved_forall_chunks, JaktInternal::Dictionary<DeprecatedString,types::SpecializedType> explicitly_specialized_types);

public: JaktInternal::Optional<parser::ExternalName> namespace_name_for_codegen() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};class FunctionGenerics :public RefCounted<FunctionGenerics>, public Weakable<FunctionGenerics> {
  public:
virtual ~FunctionGenerics() = default;
public: ids::ScopeId base_scope_id;public: JaktInternal::DynamicArray<types::CheckedParameter> base_params;public: JaktInternal::DynamicArray<types::FunctionGenericParameter> params;public: JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> specializations;public: protected:
explicit FunctionGenerics(ids::ScopeId a_base_scope_id, JaktInternal::DynamicArray<types::CheckedParameter> a_base_params, JaktInternal::DynamicArray<types::FunctionGenericParameter> a_params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> a_specializations);
public:
static ErrorOr<NonnullRefPtr<FunctionGenerics>> __jakt_create(ids::ScopeId base_scope_id, JaktInternal::DynamicArray<types::CheckedParameter> base_params, JaktInternal::DynamicArray<types::FunctionGenericParameter> params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> specializations);

public: bool is_specialized_for_types(JaktInternal::DynamicArray<ids::TypeId> const types) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTraitRequirements> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTraitRequirements const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::MaybeResolvedScope> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::MaybeResolvedScope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FieldRecord> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FieldRecord const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedCall> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedCall const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::OperatorTraitImplementation> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::OperatorTraitImplementation const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::LoadedModule> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::LoadedModule const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ResolvedForallChunk> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ResolvedForallChunk const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::BlockControlFlow> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::BlockControlFlow const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedBlock> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedBlock const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedMatchBody> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedMatchBody const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ClassInstanceRebind> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ClassInstanceRebind const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedMatchCase> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedMatchCase const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTypeCast> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTypeCast const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedUnaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedUnaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVisibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVisibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTrait> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTrait const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedFunction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedFunction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnumVariantBinding> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnumVariantBinding const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::NumericOrStringValue> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::NumericOrStringValue const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::SpecializedType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::SpecializedType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenericParameterKind> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenericParameterKind const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StructLikeId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StructLikeId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StructOrEnumId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StructOrEnumId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStatement> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStatement const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedField> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedField const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::BuiltinType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::BuiltinType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StringLiteral> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StringLiteral const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Module> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Module const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::TypecheckFunctions> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::TypecheckFunctions const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ResolvedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ResolvedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStruct> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStruct const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedNumericConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedNumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVarDecl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVarDecl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnum> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnum const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStringLiteral> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStringLiteral const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::SafetyMode> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::SafetyMode const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVariable> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVariable const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Value> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Value const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Type> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Type const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedProgram> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedProgram const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedCapture> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedCapture const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::GenericInferences> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::GenericInferences const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedBinaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedBinaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedExpression> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedExpression const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::NumberConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::NumberConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ValueImpl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ValueImpl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Scope> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Scope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenerics> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenerics const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
