#pragma once
#include "__unified_forward.h"
#include "parser.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace types {
namespace SafetyMode_Details {
struct Safe {};
struct Unsafe {};
}
struct SafetyMode : public Variant<SafetyMode_Details::Safe, SafetyMode_Details::Unsafe> {
using Variant<SafetyMode_Details::Safe, SafetyMode_Details::Unsafe>::Variant;
    using Safe = SafetyMode_Details::Safe;
    using Unsafe = SafetyMode_Details::Unsafe;
ErrorOr<String> debug_description() const;
};
struct ModuleId {
  public:
size_t id;ModuleId(size_t a_id);

bool equals(const types::ModuleId rhs) const;
ErrorOr<String> debug_description() const;
};struct FunctionId {
  public:
types::ModuleId module;size_t id;bool equals(const types::FunctionId rhs) const;
FunctionId(types::ModuleId a_module, size_t a_id);

ErrorOr<String> debug_description() const;
};struct TypeId {
  public:
types::ModuleId module;size_t id;ErrorOr<String> to_string() const;
static JaktInternal::Optional<types::TypeId> none();
bool equals(const types::TypeId rhs) const;
TypeId(types::ModuleId a_module, size_t a_id);

static ErrorOr<types::TypeId> from_string(const String type_id_string);
ErrorOr<String> debug_description() const;
};struct CheckedCall {
  public:
JaktInternal::Array<types::ResolvedNamespace> namespace_;String name;JaktInternal::Array<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> args;JaktInternal::Array<types::TypeId> type_args;JaktInternal::Optional<types::FunctionId> function_id;types::TypeId return_type;bool callee_throws;CheckedCall(JaktInternal::Array<types::ResolvedNamespace> a_namespace_, String a_name, JaktInternal::Array<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> a_args, JaktInternal::Array<types::TypeId> a_type_args, JaktInternal::Optional<types::FunctionId> a_function_id, types::TypeId a_return_type, bool a_callee_throws);

ErrorOr<String> debug_description() const;
};namespace CheckedVisibility_Details {
struct Public {};
struct Private {};
struct Restricted {
JaktInternal::Array<NonnullRefPtr<types::MaybeResolvedScope>> scopes;
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
ErrorOr<String> debug_description() const;
};
struct ScopeId {
  public:
types::ModuleId module_id;size_t id;bool equals(const types::ScopeId other) const;
ScopeId(types::ModuleId a_module_id, size_t a_id);

ErrorOr<String> debug_description() const;
};namespace BlockControlFlow_Details {
struct AlwaysReturns {};
struct AlwaysTransfersControl {
bool might_break;
template<typename _MemberT0>
AlwaysTransfersControl(_MemberT0&& member_0):
might_break{ forward<_MemberT0>(member_0)}
{}
};
struct NeverReturns {};
struct MayReturn {};
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
ErrorOr<String> debug_description() const;
bool always_transfers_control() const;
types::BlockControlFlow partial() const;
bool always_returns() const;
types::BlockControlFlow updated(const types::BlockControlFlow second) const;
bool may_break() const;
bool is_reachable() const;
bool never_returns() const;
types::BlockControlFlow definitive() const;
bool may_return() const;
types::BlockControlFlow unify_with(const types::BlockControlFlow second) const;
};
struct CheckedBlock {
  public:
JaktInternal::Array<NonnullRefPtr<types::CheckedStatement>> statements;types::ScopeId scope_id;types::BlockControlFlow control_flow;JaktInternal::Optional<types::TypeId> yielded_type;bool yielded_none;CheckedBlock(JaktInternal::Array<NonnullRefPtr<types::CheckedStatement>> a_statements, types::ScopeId a_scope_id, types::BlockControlFlow a_control_flow, JaktInternal::Optional<types::TypeId> a_yielded_type, bool a_yielded_none);

ErrorOr<String> debug_description() const;
};struct GenericInferences {
  public:
JaktInternal::Dictionary<String,String> values;GenericInferences(JaktInternal::Dictionary<String,String> a_values);

JaktInternal::DictionaryIterator<String,String> iterator() const;
void restore(const JaktInternal::Dictionary<String,String> checkpoint);
String map(const String type) const;
JaktInternal::Optional<String> get(const String key) const;
ErrorOr<JaktInternal::Dictionary<String,String>> perform_checkpoint(const bool reset);
ErrorOr<void> set(const String key, const String value);
ErrorOr<String> debug_description() const;
};struct LoadedModule {
  public:
types::ModuleId module_id;utility::FileId file_id;LoadedModule(types::ModuleId a_module_id, utility::FileId a_file_id);

ErrorOr<String> debug_description() const;
};struct ResolvedNamespace {
  public:
String name;JaktInternal::Optional<JaktInternal::Array<types::TypeId>> generic_parameters;ResolvedNamespace(String a_name, JaktInternal::Optional<JaktInternal::Array<types::TypeId>> a_generic_parameters);

ErrorOr<String> debug_description() const;
};namespace CheckedMatchBody_Details {
struct Expression{
NonnullRefPtr<types::CheckedExpression> value;
template<typename... Args>
Expression(Args&&... args): value { forward<Args>(args)... } {}
};
struct Block{
types::CheckedBlock value;
template<typename... Args>
Block(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct CheckedMatchBody : public Variant<CheckedMatchBody_Details::Expression, CheckedMatchBody_Details::Block> {
using Variant<CheckedMatchBody_Details::Expression, CheckedMatchBody_Details::Block>::Variant;
    using Expression = CheckedMatchBody_Details::Expression;
    using Block = CheckedMatchBody_Details::Block;
ErrorOr<String> debug_description() const;
};
namespace CheckedMatchCase_Details {
struct EnumVariant {
String name;
JaktInternal::Array<parser::EnumVariantPatternArgument> args;
types::TypeId subject_type_id;
size_t index;
types::ScopeId scope_id;
types::CheckedMatchBody body;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6>
EnumVariant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6):
name{ forward<_MemberT0>(member_0)},
args{ forward<_MemberT1>(member_1)},
subject_type_id{ forward<_MemberT2>(member_2)},
index{ forward<_MemberT3>(member_3)},
scope_id{ forward<_MemberT4>(member_4)},
body{ forward<_MemberT5>(member_5)},
marker_span{ forward<_MemberT6>(member_6)}
{}
};
struct Expression {
NonnullRefPtr<types::CheckedExpression> expression;
types::CheckedMatchBody body;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Expression(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
expression{ forward<_MemberT0>(member_0)},
body{ forward<_MemberT1>(member_1)},
marker_span{ forward<_MemberT2>(member_2)}
{}
};
struct CatchAll {
bool has_arguments;
types::CheckedMatchBody body;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
CatchAll(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
has_arguments{ forward<_MemberT0>(member_0)},
body{ forward<_MemberT1>(member_1)},
marker_span{ forward<_MemberT2>(member_2)}
{}
};
}
struct CheckedMatchCase : public Variant<CheckedMatchCase_Details::EnumVariant, CheckedMatchCase_Details::Expression, CheckedMatchCase_Details::CatchAll> {
using Variant<CheckedMatchCase_Details::EnumVariant, CheckedMatchCase_Details::Expression, CheckedMatchCase_Details::CatchAll>::Variant;
    using EnumVariant = CheckedMatchCase_Details::EnumVariant;
    using Expression = CheckedMatchCase_Details::Expression;
    using CatchAll = CheckedMatchCase_Details::CatchAll;
ErrorOr<String> debug_description() const;
};
namespace CheckedNumericConstant_Details {
struct I8{
i8 value;
template<typename... Args>
I8(Args&&... args): value { forward<Args>(args)... } {}
};
struct I16{
i16 value;
template<typename... Args>
I16(Args&&... args): value { forward<Args>(args)... } {}
};
struct I32{
i32 value;
template<typename... Args>
I32(Args&&... args): value { forward<Args>(args)... } {}
};
struct I64{
i64 value;
template<typename... Args>
I64(Args&&... args): value { forward<Args>(args)... } {}
};
struct U8{
u8 value;
template<typename... Args>
U8(Args&&... args): value { forward<Args>(args)... } {}
};
struct U16{
u16 value;
template<typename... Args>
U16(Args&&... args): value { forward<Args>(args)... } {}
};
struct U32{
u32 value;
template<typename... Args>
U32(Args&&... args): value { forward<Args>(args)... } {}
};
struct U64{
u64 value;
template<typename... Args>
U64(Args&&... args): value { forward<Args>(args)... } {}
};
struct USize{
u64 value;
template<typename... Args>
USize(Args&&... args): value { forward<Args>(args)... } {}
};
struct F32{
f32 value;
template<typename... Args>
F32(Args&&... args): value { forward<Args>(args)... } {}
};
struct F64{
f64 value;
template<typename... Args>
F64(Args&&... args): value { forward<Args>(args)... } {}
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
ErrorOr<String> debug_description() const;
JaktInternal::Optional<types::NumberConstant> number_constant() const;
};
namespace CheckedTypeCast_Details {
struct Fallible{
types::TypeId value;
template<typename... Args>
Fallible(Args&&... args): value { forward<Args>(args)... } {}
};
struct Infallible{
types::TypeId value;
template<typename... Args>
Infallible(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct CheckedTypeCast : public Variant<CheckedTypeCast_Details::Fallible, CheckedTypeCast_Details::Infallible> {
using Variant<CheckedTypeCast_Details::Fallible, CheckedTypeCast_Details::Infallible>::Variant;
    using Fallible = CheckedTypeCast_Details::Fallible;
    using Infallible = CheckedTypeCast_Details::Infallible;
ErrorOr<String> debug_description() const;
types::TypeId type_id() const;
};
struct EnumId {
  public:
types::ModuleId module;size_t id;bool equals(const types::EnumId rhs) const;
EnumId(types::ModuleId a_module, size_t a_id);

ErrorOr<String> debug_description() const;
};namespace CheckedEnumVariant_Details {
struct Untyped {
types::EnumId enum_id;
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Untyped(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
enum_id{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Typed {
types::EnumId enum_id;
String name;
types::TypeId type_id;
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
types::EnumId enum_id;
String name;
NonnullRefPtr<types::CheckedExpression> expr;
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
types::EnumId enum_id;
String name;
JaktInternal::Array<types::VarId> fields;
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
ErrorOr<String> debug_description() const;
types::EnumId enum_id() const;
String name() const;
bool equals(const types::CheckedEnumVariant other) const;
utility::Span span() const;
};
namespace CheckedUnaryOperator_Details {
struct PreIncrement {};
struct PostIncrement {};
struct PreDecrement {};
struct PostDecrement {};
struct Negate {};
struct Dereference {};
struct RawAddress {};
struct Reference {};
struct MutableReference {};
struct LogicalNot {};
struct BitwiseNot {};
struct TypeCast{
types::CheckedTypeCast value;
template<typename... Args>
TypeCast(Args&&... args): value { forward<Args>(args)... } {}
};
struct Is{
types::TypeId value;
template<typename... Args>
Is(Args&&... args): value { forward<Args>(args)... } {}
};
struct IsEnumVariant {
types::CheckedEnumVariant enum_variant;
JaktInternal::Array<types::CheckedEnumVariantBinding> bindings;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
IsEnumVariant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
enum_variant{ forward<_MemberT0>(member_0)},
bindings{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
}
struct CheckedUnaryOperator : public Variant<CheckedUnaryOperator_Details::PreIncrement, CheckedUnaryOperator_Details::PostIncrement, CheckedUnaryOperator_Details::PreDecrement, CheckedUnaryOperator_Details::PostDecrement, CheckedUnaryOperator_Details::Negate, CheckedUnaryOperator_Details::Dereference, CheckedUnaryOperator_Details::RawAddress, CheckedUnaryOperator_Details::Reference, CheckedUnaryOperator_Details::MutableReference, CheckedUnaryOperator_Details::LogicalNot, CheckedUnaryOperator_Details::BitwiseNot, CheckedUnaryOperator_Details::TypeCast, CheckedUnaryOperator_Details::Is, CheckedUnaryOperator_Details::IsEnumVariant> {
using Variant<CheckedUnaryOperator_Details::PreIncrement, CheckedUnaryOperator_Details::PostIncrement, CheckedUnaryOperator_Details::PreDecrement, CheckedUnaryOperator_Details::PostDecrement, CheckedUnaryOperator_Details::Negate, CheckedUnaryOperator_Details::Dereference, CheckedUnaryOperator_Details::RawAddress, CheckedUnaryOperator_Details::Reference, CheckedUnaryOperator_Details::MutableReference, CheckedUnaryOperator_Details::LogicalNot, CheckedUnaryOperator_Details::BitwiseNot, CheckedUnaryOperator_Details::TypeCast, CheckedUnaryOperator_Details::Is, CheckedUnaryOperator_Details::IsEnumVariant>::Variant;
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
ErrorOr<String> debug_description() const;
};
struct CheckedEnumVariantBinding {
  public:
JaktInternal::Optional<String> name;String binding;types::TypeId type_id;utility::Span span;CheckedEnumVariantBinding(JaktInternal::Optional<String> a_name, String a_binding, types::TypeId a_type_id, utility::Span a_span);

ErrorOr<String> debug_description() const;
};struct CheckedVariable {
  public:
String name;types::TypeId type_id;bool is_mutable;utility::Span definition_span;JaktInternal::Optional<utility::Span> type_span;types::CheckedVisibility visibility;CheckedVariable(String a_name, types::TypeId a_type_id, bool a_is_mutable, utility::Span a_definition_span, JaktInternal::Optional<utility::Span> a_type_span, types::CheckedVisibility a_visibility);

ErrorOr<String> debug_description() const;
};struct VarId {
  public:
types::ModuleId module;size_t id;VarId(types::ModuleId a_module, size_t a_id);

ErrorOr<String> debug_description() const;
};namespace CheckedStatement_Details {
struct Expression {
NonnullRefPtr<types::CheckedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Expression(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Defer {
NonnullRefPtr<types::CheckedStatement> statement;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Defer(_MemberT0&& member_0, _MemberT1&& member_1):
statement{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct DestructuringAssignment {
JaktInternal::Array<NonnullRefPtr<types::CheckedStatement>> vars;
NonnullRefPtr<types::CheckedStatement> var_decl;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
DestructuringAssignment(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
vars{ forward<_MemberT0>(member_0)},
var_decl{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct VarDecl {
types::VarId var_id;
NonnullRefPtr<types::CheckedExpression> init;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
VarDecl(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
var_id{ forward<_MemberT0>(member_0)},
init{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct If {
NonnullRefPtr<types::CheckedExpression> condition;
types::CheckedBlock then_block;
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> else_statement;
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
NonnullRefPtr<types::CheckedExpression> condition;
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
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> val;
JaktInternal::Optional<utility::Span> span;
template<typename _MemberT0, typename _MemberT1>
Return(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Break{
utility::Span value;
template<typename... Args>
Break(Args&&... args): value { forward<Args>(args)... } {}
};
struct Continue{
utility::Span value;
template<typename... Args>
Continue(Args&&... args): value { forward<Args>(args)... } {}
};
struct Throw {
NonnullRefPtr<types::CheckedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Throw(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Yield {
NonnullRefPtr<types::CheckedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Yield(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct InlineCpp {
JaktInternal::Array<String> lines;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
InlineCpp(_MemberT0&& member_0, _MemberT1&& member_1):
lines{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Garbage{
utility::Span value;
template<typename... Args>
Garbage(Args&&... args): value { forward<Args>(args)... } {}
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
template<typename V, typename... Args> static auto create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) CheckedStatement(V(forward<Args>(args)...)));
}
ErrorOr<String> debug_description() const;
static JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> none();
JaktInternal::Optional<utility::Span> span() const;
};
namespace CheckedExpression_Details {
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
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
NumericConstant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct QuotedString {
String val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
QuotedString(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByteConstant {
String val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByteConstant(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct CharacterConstant {
String val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
CharacterConstant(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct UnaryOp {
NonnullRefPtr<types::CheckedExpression> expr;
types::CheckedUnaryOperator op;
utility::Span span;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
UnaryOp(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
op{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)}
{}
};
struct BinaryOp {
NonnullRefPtr<types::CheckedExpression> lhs;
parser::BinaryOperator op;
NonnullRefPtr<types::CheckedExpression> rhs;
utility::Span span;
types::TypeId type_id;
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
JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> vals;
utility::Span span;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
JaktTuple(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
vals{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct Range {
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> from;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> to;
utility::Span span;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Range(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
from{ forward<_MemberT0>(member_0)},
to{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)}
{}
};
struct JaktArray {
JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> vals;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> repeat;
utility::Span span;
types::TypeId type_id;
types::TypeId inner_type_id;
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
JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> vals;
utility::Span span;
types::TypeId type_id;
types::TypeId inner_type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
JaktSet(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
vals{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)},
inner_type_id{ forward<_MemberT3>(member_3)}
{}
};
struct JaktDictionary {
JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> vals;
utility::Span span;
types::TypeId type_id;
types::TypeId key_type_id;
types::TypeId value_type_id;
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
NonnullRefPtr<types::CheckedExpression> expr;
NonnullRefPtr<types::CheckedExpression> index;
utility::Span span;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
IndexedExpression(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)}
{}
};
struct IndexedDictionary {
NonnullRefPtr<types::CheckedExpression> expr;
NonnullRefPtr<types::CheckedExpression> index;
utility::Span span;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
IndexedDictionary(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)}
{}
};
struct IndexedTuple {
NonnullRefPtr<types::CheckedExpression> expr;
size_t index;
utility::Span span;
bool is_optional;
types::TypeId type_id;
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
NonnullRefPtr<types::CheckedExpression> expr;
String index;
utility::Span span;
bool is_optional;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
IndexedStruct(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
is_optional{ forward<_MemberT3>(member_3)},
type_id{ forward<_MemberT4>(member_4)}
{}
};
struct Match {
NonnullRefPtr<types::CheckedExpression> expr;
JaktInternal::Array<types::CheckedMatchCase> match_cases;
utility::Span span;
types::TypeId type_id;
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
NonnullRefPtr<types::CheckedExpression> expr;
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
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Call(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
call{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct MethodCall {
NonnullRefPtr<types::CheckedExpression> expr;
types::CheckedCall call;
utility::Span span;
bool is_optional;
types::TypeId type_id;
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
JaktInternal::Array<types::CheckedNamespace> namespaces;
types::CheckedVariable var;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
NamespacedVar(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
namespaces{ forward<_MemberT0>(member_0)},
var{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Var {
types::CheckedVariable var;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Var(_MemberT0&& member_0, _MemberT1&& member_1):
var{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct OptionalNone {
utility::Span span;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1>
OptionalNone(_MemberT0&& member_0, _MemberT1&& member_1):
span{ forward<_MemberT0>(member_0)},
type_id{ forward<_MemberT1>(member_1)}
{}
};
struct OptionalSome {
NonnullRefPtr<types::CheckedExpression> expr;
utility::Span span;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
OptionalSome(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct ForcedUnwrap {
NonnullRefPtr<types::CheckedExpression> expr;
utility::Span span;
types::TypeId type_id;
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
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Block(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct Function {
JaktInternal::Array<types::CheckedCapture> captures;
JaktInternal::Array<types::CheckedParameter> params;
bool can_throw;
types::TypeId return_type_id;
types::CheckedBlock block;
utility::Span span;
types::TypeId type_id;
JaktInternal::Optional<types::FunctionId> pseudo_function_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6, typename _MemberT7>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6, _MemberT7&& member_7):
captures{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
can_throw{ forward<_MemberT2>(member_2)},
return_type_id{ forward<_MemberT3>(member_3)},
block{ forward<_MemberT4>(member_4)},
span{ forward<_MemberT5>(member_5)},
type_id{ forward<_MemberT6>(member_6)},
pseudo_function_id{ forward<_MemberT7>(member_7)}
{}
};
struct Try {
NonnullRefPtr<types::CheckedExpression> expr;
JaktInternal::Optional<types::CheckedBlock> catch_block;
JaktInternal::Optional<String> catch_name;
utility::Span span;
types::TypeId type_id;
types::TypeId inner_type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5>
Try(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5):
expr{ forward<_MemberT0>(member_0)},
catch_block{ forward<_MemberT1>(member_1)},
catch_name{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)},
type_id{ forward<_MemberT4>(member_4)},
inner_type_id{ forward<_MemberT5>(member_5)}
{}
};
struct TryBlock {
NonnullRefPtr<types::CheckedStatement> stmt;
types::CheckedBlock catch_block;
String error_name;
utility::Span error_span;
utility::Span span;
types::TypeId type_id;
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
struct Garbage{
utility::Span value;
template<typename... Args>
Garbage(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct CheckedExpression : public Variant<CheckedExpression_Details::Boolean, CheckedExpression_Details::NumericConstant, CheckedExpression_Details::QuotedString, CheckedExpression_Details::ByteConstant, CheckedExpression_Details::CharacterConstant, CheckedExpression_Details::UnaryOp, CheckedExpression_Details::BinaryOp, CheckedExpression_Details::JaktTuple, CheckedExpression_Details::Range, CheckedExpression_Details::JaktArray, CheckedExpression_Details::JaktSet, CheckedExpression_Details::JaktDictionary, CheckedExpression_Details::IndexedExpression, CheckedExpression_Details::IndexedDictionary, CheckedExpression_Details::IndexedTuple, CheckedExpression_Details::IndexedStruct, CheckedExpression_Details::Match, CheckedExpression_Details::EnumVariantArg, CheckedExpression_Details::Call, CheckedExpression_Details::MethodCall, CheckedExpression_Details::NamespacedVar, CheckedExpression_Details::Var, CheckedExpression_Details::OptionalNone, CheckedExpression_Details::OptionalSome, CheckedExpression_Details::ForcedUnwrap, CheckedExpression_Details::Block, CheckedExpression_Details::Function, CheckedExpression_Details::Try, CheckedExpression_Details::TryBlock, CheckedExpression_Details::Garbage>, public RefCounted<CheckedExpression> {
using Variant<CheckedExpression_Details::Boolean, CheckedExpression_Details::NumericConstant, CheckedExpression_Details::QuotedString, CheckedExpression_Details::ByteConstant, CheckedExpression_Details::CharacterConstant, CheckedExpression_Details::UnaryOp, CheckedExpression_Details::BinaryOp, CheckedExpression_Details::JaktTuple, CheckedExpression_Details::Range, CheckedExpression_Details::JaktArray, CheckedExpression_Details::JaktSet, CheckedExpression_Details::JaktDictionary, CheckedExpression_Details::IndexedExpression, CheckedExpression_Details::IndexedDictionary, CheckedExpression_Details::IndexedTuple, CheckedExpression_Details::IndexedStruct, CheckedExpression_Details::Match, CheckedExpression_Details::EnumVariantArg, CheckedExpression_Details::Call, CheckedExpression_Details::MethodCall, CheckedExpression_Details::NamespacedVar, CheckedExpression_Details::Var, CheckedExpression_Details::OptionalNone, CheckedExpression_Details::OptionalSome, CheckedExpression_Details::ForcedUnwrap, CheckedExpression_Details::Block, CheckedExpression_Details::Function, CheckedExpression_Details::Try, CheckedExpression_Details::TryBlock, CheckedExpression_Details::Garbage>::Variant;
    using Boolean = CheckedExpression_Details::Boolean;
    using NumericConstant = CheckedExpression_Details::NumericConstant;
    using QuotedString = CheckedExpression_Details::QuotedString;
    using ByteConstant = CheckedExpression_Details::ByteConstant;
    using CharacterConstant = CheckedExpression_Details::CharacterConstant;
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
    using Try = CheckedExpression_Details::Try;
    using TryBlock = CheckedExpression_Details::TryBlock;
    using Garbage = CheckedExpression_Details::Garbage;
template<typename V, typename... Args> static auto create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) CheckedExpression(V(forward<Args>(args)...)));
}
ErrorOr<String> debug_description() const;
bool can_throw() const;
utility::Span span() const;
JaktInternal::Optional<types::NumberConstant> to_number_constant(const NonnullRefPtr<types::CheckedProgram> program) const;
types::TypeId type() const;
types::BlockControlFlow control_flow() const;
bool is_mutable(const NonnullRefPtr<types::CheckedProgram> program) const;
};
struct CheckedVarDecl {
  public:
String name;bool is_mutable;utility::Span span;types::TypeId type_id;CheckedVarDecl(String a_name, bool a_is_mutable, utility::Span a_span, types::TypeId a_type_id);

ErrorOr<String> debug_description() const;
};namespace NumberConstant_Details {
struct Signed{
i64 value;
template<typename... Args>
Signed(Args&&... args): value { forward<Args>(args)... } {}
};
struct Unsigned{
u64 value;
template<typename... Args>
Unsigned(Args&&... args): value { forward<Args>(args)... } {}
};
struct Floating{
f64 value;
template<typename... Args>
Floating(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct NumberConstant : public Variant<NumberConstant_Details::Signed, NumberConstant_Details::Unsigned, NumberConstant_Details::Floating> {
using Variant<NumberConstant_Details::Signed, NumberConstant_Details::Unsigned, NumberConstant_Details::Floating>::Variant;
    using Signed = NumberConstant_Details::Signed;
    using Unsigned = NumberConstant_Details::Unsigned;
    using Floating = NumberConstant_Details::Floating;
ErrorOr<String> debug_description() const;
size_t to_usize() const;
bool can_fit_number(const types::TypeId type_id, const NonnullRefPtr<types::CheckedProgram> program) const;
};
namespace FunctionGenericParameter_Details {
struct InferenceGuide{
types::TypeId value;
template<typename... Args>
InferenceGuide(Args&&... args): value { forward<Args>(args)... } {}
};
struct Parameter{
types::TypeId value;
template<typename... Args>
Parameter(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct FunctionGenericParameter : public Variant<FunctionGenericParameter_Details::InferenceGuide, FunctionGenericParameter_Details::Parameter> {
using Variant<FunctionGenericParameter_Details::InferenceGuide, FunctionGenericParameter_Details::Parameter>::Variant;
    using InferenceGuide = FunctionGenericParameter_Details::InferenceGuide;
    using Parameter = FunctionGenericParameter_Details::Parameter;
ErrorOr<String> debug_description() const;
types::TypeId type_id() const;
};
struct CheckedNamespace {
  public:
String name;types::ScopeId scope;CheckedNamespace(String a_name, types::ScopeId a_scope);

ErrorOr<String> debug_description() const;
};struct StructId {
  public:
types::ModuleId module;size_t id;bool equals(const types::StructId rhs) const;
StructId(types::ModuleId a_module, size_t a_id);

ErrorOr<String> debug_description() const;
};struct Value {
  public:
NonnullRefPtr<types::ValueImpl> impl;utility::Span span;ErrorOr<types::Value> copy() const;
Value(NonnullRefPtr<types::ValueImpl> a_impl, utility::Span a_span);

ErrorOr<types::Value> cast(const types::Value expected, const utility::Span span) const;
String type_name() const;
ErrorOr<String> debug_description() const;
};namespace ValueImpl_Details {
struct Void {};
struct Bool{
bool value;
template<typename... Args>
Bool(Args&&... args): value { forward<Args>(args)... } {}
};
struct U8{
u8 value;
template<typename... Args>
U8(Args&&... args): value { forward<Args>(args)... } {}
};
struct U16{
u16 value;
template<typename... Args>
U16(Args&&... args): value { forward<Args>(args)... } {}
};
struct U32{
u32 value;
template<typename... Args>
U32(Args&&... args): value { forward<Args>(args)... } {}
};
struct U64{
u64 value;
template<typename... Args>
U64(Args&&... args): value { forward<Args>(args)... } {}
};
struct I8{
i8 value;
template<typename... Args>
I8(Args&&... args): value { forward<Args>(args)... } {}
};
struct I16{
i16 value;
template<typename... Args>
I16(Args&&... args): value { forward<Args>(args)... } {}
};
struct I32{
i32 value;
template<typename... Args>
I32(Args&&... args): value { forward<Args>(args)... } {}
};
struct I64{
i64 value;
template<typename... Args>
I64(Args&&... args): value { forward<Args>(args)... } {}
};
struct F32{
f32 value;
template<typename... Args>
F32(Args&&... args): value { forward<Args>(args)... } {}
};
struct F64{
f64 value;
template<typename... Args>
F64(Args&&... args): value { forward<Args>(args)... } {}
};
struct USize{
size_t value;
template<typename... Args>
USize(Args&&... args): value { forward<Args>(args)... } {}
};
struct JaktString{
String value;
template<typename... Args>
JaktString(Args&&... args): value { forward<Args>(args)... } {}
};
struct CChar{
char value;
template<typename... Args>
CChar(Args&&... args): value { forward<Args>(args)... } {}
};
struct CInt{
int value;
template<typename... Args>
CInt(Args&&... args): value { forward<Args>(args)... } {}
};
struct Struct {
JaktInternal::Array<types::Value> fields;
types::StructId struct_id;
JaktInternal::Optional<types::FunctionId> constructor;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Struct(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
fields{ forward<_MemberT0>(member_0)},
struct_id{ forward<_MemberT1>(member_1)},
constructor{ forward<_MemberT2>(member_2)}
{}
};
struct Class {
JaktInternal::Array<types::Value> fields;
types::StructId struct_id;
JaktInternal::Optional<types::FunctionId> constructor;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Class(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
fields{ forward<_MemberT0>(member_0)},
struct_id{ forward<_MemberT1>(member_1)},
constructor{ forward<_MemberT2>(member_2)}
{}
};
struct Enum {
JaktInternal::Array<types::Value> fields;
types::EnumId enum_id;
types::FunctionId constructor;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Enum(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
fields{ forward<_MemberT0>(member_0)},
enum_id{ forward<_MemberT1>(member_1)},
constructor{ forward<_MemberT2>(member_2)}
{}
};
struct JaktArray {
JaktInternal::Array<types::Value> values;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1>
JaktArray(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
type_id{ forward<_MemberT1>(member_1)}
{}
};
struct JaktDictionary {
JaktInternal::Array<types::Value> keys;
JaktInternal::Array<types::Value> values;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
JaktDictionary(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
keys{ forward<_MemberT0>(member_0)},
values{ forward<_MemberT1>(member_1)},
type_id{ forward<_MemberT2>(member_2)}
{}
};
struct RawPtr{
NonnullRefPtr<types::ValueImpl> value;
template<typename... Args>
RawPtr(Args&&... args): value { forward<Args>(args)... } {}
};
struct OptionalSome {
types::Value value;
template<typename _MemberT0>
OptionalSome(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct OptionalNone {};
struct JaktTuple {
JaktInternal::Array<types::Value> fields;
types::TypeId type_id;
template<typename _MemberT0, typename _MemberT1>
JaktTuple(_MemberT0&& member_0, _MemberT1&& member_1):
fields{ forward<_MemberT0>(member_0)},
type_id{ forward<_MemberT1>(member_1)}
{}
};
struct Function {
JaktInternal::Dictionary<String,types::Value> captures;
JaktInternal::Dictionary<String,JaktInternal::Tuple<types::TypeId,JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>>>> params;
types::TypeId return_type_id;
types::TypeId type_id;
types::CheckedBlock block;
bool can_throw;
JaktInternal::Array<types::CheckedParameter> checked_params;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6):
captures{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
return_type_id{ forward<_MemberT2>(member_2)},
type_id{ forward<_MemberT3>(member_3)},
block{ forward<_MemberT4>(member_4)},
can_throw{ forward<_MemberT5>(member_5)},
checked_params{ forward<_MemberT6>(member_6)}
{}
};
}
struct ValueImpl : public Variant<ValueImpl_Details::Void, ValueImpl_Details::Bool, ValueImpl_Details::U8, ValueImpl_Details::U16, ValueImpl_Details::U32, ValueImpl_Details::U64, ValueImpl_Details::I8, ValueImpl_Details::I16, ValueImpl_Details::I32, ValueImpl_Details::I64, ValueImpl_Details::F32, ValueImpl_Details::F64, ValueImpl_Details::USize, ValueImpl_Details::JaktString, ValueImpl_Details::CChar, ValueImpl_Details::CInt, ValueImpl_Details::Struct, ValueImpl_Details::Class, ValueImpl_Details::Enum, ValueImpl_Details::JaktArray, ValueImpl_Details::JaktDictionary, ValueImpl_Details::RawPtr, ValueImpl_Details::OptionalSome, ValueImpl_Details::OptionalNone, ValueImpl_Details::JaktTuple, ValueImpl_Details::Function>, public RefCounted<ValueImpl> {
using Variant<ValueImpl_Details::Void, ValueImpl_Details::Bool, ValueImpl_Details::U8, ValueImpl_Details::U16, ValueImpl_Details::U32, ValueImpl_Details::U64, ValueImpl_Details::I8, ValueImpl_Details::I16, ValueImpl_Details::I32, ValueImpl_Details::I64, ValueImpl_Details::F32, ValueImpl_Details::F64, ValueImpl_Details::USize, ValueImpl_Details::JaktString, ValueImpl_Details::CChar, ValueImpl_Details::CInt, ValueImpl_Details::Struct, ValueImpl_Details::Class, ValueImpl_Details::Enum, ValueImpl_Details::JaktArray, ValueImpl_Details::JaktDictionary, ValueImpl_Details::RawPtr, ValueImpl_Details::OptionalSome, ValueImpl_Details::OptionalNone, ValueImpl_Details::JaktTuple, ValueImpl_Details::Function>::Variant;
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
    using CChar = ValueImpl_Details::CChar;
    using CInt = ValueImpl_Details::CInt;
    using Struct = ValueImpl_Details::Struct;
    using Class = ValueImpl_Details::Class;
    using Enum = ValueImpl_Details::Enum;
    using JaktArray = ValueImpl_Details::JaktArray;
    using JaktDictionary = ValueImpl_Details::JaktDictionary;
    using RawPtr = ValueImpl_Details::RawPtr;
    using OptionalSome = ValueImpl_Details::OptionalSome;
    using OptionalNone = ValueImpl_Details::OptionalNone;
    using JaktTuple = ValueImpl_Details::JaktTuple;
    using Function = ValueImpl_Details::Function;
template<typename V, typename... Args> static auto create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) ValueImpl(V(forward<Args>(args)...)));
}
ErrorOr<String> debug_description() const;
bool equals(const NonnullRefPtr<types::ValueImpl> other) const;
ErrorOr<NonnullRefPtr<types::ValueImpl>> copy() const;
};
class Scope : public RefCounted<Scope>, public Weakable<Scope> {
  public:
virtual ~Scope() = default;
JaktInternal::Optional<String> namespace_name;JaktInternal::Dictionary<String,types::VarId> vars;JaktInternal::Dictionary<String,types::Value> comptime_bindings;JaktInternal::Dictionary<String,types::StructId> structs;JaktInternal::Dictionary<String,types::FunctionId> functions;JaktInternal::Dictionary<String,types::EnumId> enums;JaktInternal::Dictionary<String,types::TypeId> types;JaktInternal::Dictionary<String,types::ModuleId> imports;JaktInternal::Optional<types::ScopeId> parent;JaktInternal::Array<types::ScopeId> children;bool can_throw;JaktInternal::Optional<String> import_path_if_extern;JaktInternal::Array<parser::IncludeAction> after_extern_include;JaktInternal::Array<parser::IncludeAction> before_extern_include;String debug_name;protected:
explicit Scope(JaktInternal::Optional<String>&& a_namespace_name, JaktInternal::Dictionary<String,types::VarId>&& a_vars, JaktInternal::Dictionary<String,types::Value>&& a_comptime_bindings, JaktInternal::Dictionary<String,types::StructId>&& a_structs, JaktInternal::Dictionary<String,types::FunctionId>&& a_functions, JaktInternal::Dictionary<String,types::EnumId>&& a_enums, JaktInternal::Dictionary<String,types::TypeId>&& a_types, JaktInternal::Dictionary<String,types::ModuleId>&& a_imports, JaktInternal::Optional<types::ScopeId>&& a_parent, JaktInternal::Array<types::ScopeId>&& a_children, bool&& a_can_throw, JaktInternal::Optional<String>&& a_import_path_if_extern, JaktInternal::Array<parser::IncludeAction>&& a_after_extern_include, JaktInternal::Array<parser::IncludeAction>&& a_before_extern_include, String&& a_debug_name);
public:
static ErrorOr<NonnullRefPtr<Scope>> create(JaktInternal::Optional<String> namespace_name, JaktInternal::Dictionary<String,types::VarId> vars, JaktInternal::Dictionary<String,types::Value> comptime_bindings, JaktInternal::Dictionary<String,types::StructId> structs, JaktInternal::Dictionary<String,types::FunctionId> functions, JaktInternal::Dictionary<String,types::EnumId> enums, JaktInternal::Dictionary<String,types::TypeId> types, JaktInternal::Dictionary<String,types::ModuleId> imports, JaktInternal::Optional<types::ScopeId> parent, JaktInternal::Array<types::ScopeId> children, bool can_throw, JaktInternal::Optional<String> import_path_if_extern, JaktInternal::Array<parser::IncludeAction> after_extern_include, JaktInternal::Array<parser::IncludeAction> before_extern_include, String debug_name);

ErrorOr<String> debug_description() const;
};class Module : public RefCounted<Module>, public Weakable<Module> {
  public:
virtual ~Module() = default;
types::ModuleId id;String name;JaktInternal::Array<NonnullRefPtr<types::CheckedFunction>> functions;JaktInternal::Array<types::CheckedStruct> structures;JaktInternal::Array<types::CheckedEnum> enums;JaktInternal::Array<NonnullRefPtr<types::Scope>> scopes;JaktInternal::Array<NonnullRefPtr<types::Type>> types;JaktInternal::Array<types::CheckedVariable> variables;JaktInternal::Array<types::ModuleId> imports;String resolved_import_path;bool is_root;protected:
explicit Module(types::ModuleId&& a_id, String&& a_name, JaktInternal::Array<NonnullRefPtr<types::CheckedFunction>>&& a_functions, JaktInternal::Array<types::CheckedStruct>&& a_structures, JaktInternal::Array<types::CheckedEnum>&& a_enums, JaktInternal::Array<NonnullRefPtr<types::Scope>>&& a_scopes, JaktInternal::Array<NonnullRefPtr<types::Type>>&& a_types, JaktInternal::Array<types::CheckedVariable>&& a_variables, JaktInternal::Array<types::ModuleId>&& a_imports, String&& a_resolved_import_path, bool&& a_is_root);
public:
static ErrorOr<NonnullRefPtr<Module>> create(types::ModuleId id, String name, JaktInternal::Array<NonnullRefPtr<types::CheckedFunction>> functions, JaktInternal::Array<types::CheckedStruct> structures, JaktInternal::Array<types::CheckedEnum> enums, JaktInternal::Array<NonnullRefPtr<types::Scope>> scopes, JaktInternal::Array<NonnullRefPtr<types::Type>> types, JaktInternal::Array<types::CheckedVariable> variables, JaktInternal::Array<types::ModuleId> imports, String resolved_import_path, bool is_root);

ErrorOr<types::TypeId> new_type_variable();
ErrorOr<types::FunctionId> add_function(const NonnullRefPtr<types::CheckedFunction> checked_function);
bool is_prelude() const;
ErrorOr<types::VarId> add_variable(const types::CheckedVariable checked_variable);
types::FunctionId next_function_id() const;
ErrorOr<String> debug_description() const;
};namespace BuiltinType_Details {
struct Void {};
struct Bool {};
struct U8 {};
struct U16 {};
struct U32 {};
struct U64 {};
struct I8 {};
struct I16 {};
struct I32 {};
struct I64 {};
struct F32 {};
struct F64 {};
struct Usize {};
struct JaktString {};
struct CChar {};
struct CInt {};
struct Unknown {};
struct Never {};
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
ErrorOr<String> debug_description() const;
size_t id() const;
};
namespace StructOrEnumId_Details {
struct Struct{
types::StructId value;
template<typename... Args>
Struct(Args&&... args): value { forward<Args>(args)... } {}
};
struct Enum{
types::EnumId value;
template<typename... Args>
Enum(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct StructOrEnumId : public Variant<StructOrEnumId_Details::Struct, StructOrEnumId_Details::Enum> {
using Variant<StructOrEnumId_Details::Struct, StructOrEnumId_Details::Enum>::Variant;
    using Struct = StructOrEnumId_Details::Struct;
    using Enum = StructOrEnumId_Details::Enum;
ErrorOr<String> debug_description() const;
};
namespace Type_Details {
struct Void {};
struct Bool {};
struct U8 {};
struct U16 {};
struct U32 {};
struct U64 {};
struct I8 {};
struct I16 {};
struct I32 {};
struct I64 {};
struct F32 {};
struct F64 {};
struct Usize {};
struct JaktString {};
struct CChar {};
struct CInt {};
struct Unknown {};
struct Never {};
struct TypeVariable{
String value;
template<typename... Args>
TypeVariable(Args&&... args): value { forward<Args>(args)... } {}
};
struct GenericInstance {
types::StructId id;
JaktInternal::Array<types::TypeId> args;
template<typename _MemberT0, typename _MemberT1>
GenericInstance(_MemberT0&& member_0, _MemberT1&& member_1):
id{ forward<_MemberT0>(member_0)},
args{ forward<_MemberT1>(member_1)}
{}
};
struct GenericEnumInstance {
types::EnumId id;
JaktInternal::Array<types::TypeId> args;
template<typename _MemberT0, typename _MemberT1>
GenericEnumInstance(_MemberT0&& member_0, _MemberT1&& member_1):
id{ forward<_MemberT0>(member_0)},
args{ forward<_MemberT1>(member_1)}
{}
};
struct GenericResolvedType {
types::StructId id;
JaktInternal::Array<types::TypeId> args;
template<typename _MemberT0, typename _MemberT1>
GenericResolvedType(_MemberT0&& member_0, _MemberT1&& member_1):
id{ forward<_MemberT0>(member_0)},
args{ forward<_MemberT1>(member_1)}
{}
};
struct Struct{
types::StructId value;
template<typename... Args>
Struct(Args&&... args): value { forward<Args>(args)... } {}
};
struct Enum{
types::EnumId value;
template<typename... Args>
Enum(Args&&... args): value { forward<Args>(args)... } {}
};
struct RawPtr{
types::TypeId value;
template<typename... Args>
RawPtr(Args&&... args): value { forward<Args>(args)... } {}
};
struct Reference{
types::TypeId value;
template<typename... Args>
Reference(Args&&... args): value { forward<Args>(args)... } {}
};
struct MutableReference{
types::TypeId value;
template<typename... Args>
MutableReference(Args&&... args): value { forward<Args>(args)... } {}
};
struct Function {
JaktInternal::Array<types::TypeId> params;
bool can_throw;
types::TypeId return_type_id;
types::FunctionId pseudo_function_id;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
params{ forward<_MemberT0>(member_0)},
can_throw{ forward<_MemberT1>(member_1)},
return_type_id{ forward<_MemberT2>(member_2)},
pseudo_function_id{ forward<_MemberT3>(member_3)}
{}
};
}
struct Type : public Variant<Type_Details::Void, Type_Details::Bool, Type_Details::U8, Type_Details::U16, Type_Details::U32, Type_Details::U64, Type_Details::I8, Type_Details::I16, Type_Details::I32, Type_Details::I64, Type_Details::F32, Type_Details::F64, Type_Details::Usize, Type_Details::JaktString, Type_Details::CChar, Type_Details::CInt, Type_Details::Unknown, Type_Details::Never, Type_Details::TypeVariable, Type_Details::GenericInstance, Type_Details::GenericEnumInstance, Type_Details::GenericResolvedType, Type_Details::Struct, Type_Details::Enum, Type_Details::RawPtr, Type_Details::Reference, Type_Details::MutableReference, Type_Details::Function>, public RefCounted<Type> {
using Variant<Type_Details::Void, Type_Details::Bool, Type_Details::U8, Type_Details::U16, Type_Details::U32, Type_Details::U64, Type_Details::I8, Type_Details::I16, Type_Details::I32, Type_Details::I64, Type_Details::F32, Type_Details::F64, Type_Details::Usize, Type_Details::JaktString, Type_Details::CChar, Type_Details::CInt, Type_Details::Unknown, Type_Details::Never, Type_Details::TypeVariable, Type_Details::GenericInstance, Type_Details::GenericEnumInstance, Type_Details::GenericResolvedType, Type_Details::Struct, Type_Details::Enum, Type_Details::RawPtr, Type_Details::Reference, Type_Details::MutableReference, Type_Details::Function>::Variant;
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
    using GenericInstance = Type_Details::GenericInstance;
    using GenericEnumInstance = Type_Details::GenericEnumInstance;
    using GenericResolvedType = Type_Details::GenericResolvedType;
    using Struct = Type_Details::Struct;
    using Enum = Type_Details::Enum;
    using RawPtr = Type_Details::RawPtr;
    using Reference = Type_Details::Reference;
    using MutableReference = Type_Details::MutableReference;
    using Function = Type_Details::Function;
template<typename V, typename... Args> static auto create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) Type(V(forward<Args>(args)...)));
}
ErrorOr<String> debug_description() const;
bool is_signed() const;
u64 max() const;
bool equals(const NonnullRefPtr<types::Type> rhs) const;
String constructor_name() const;
i64 get_bits() const;
bool is_builtin() const;
i64 min() const;
ErrorOr<types::TypeId> flip_signedness() const;
};
class CheckedProgram : public RefCounted<CheckedProgram>, public Weakable<CheckedProgram> {
  public:
virtual ~CheckedProgram() = default;
NonnullRefPtr<compiler::Compiler> compiler;JaktInternal::Array<NonnullRefPtr<types::Module>> modules;JaktInternal::Dictionary<String,types::LoadedModule> loaded_modules;bool is_floating(const types::TypeId type_id) const;
types::ScopeId prelude_scope_id() const;
ErrorOr<JaktInternal::Optional<types::StructId>> find_struct_in_scope(const types::ScopeId scope_id, const String name) const;
ErrorOr<void> set_loaded_module(const String module_name, const types::LoadedModule loaded_module);
bool is_integer(const types::TypeId type_id) const;
ErrorOr<types::ScopeId> create_scope(const JaktInternal::Optional<types::ScopeId> parent_scope_id, const bool can_throw, const String debug_name, const types::ModuleId module_id);
NonnullRefPtr<types::Module> get_module(const types::ModuleId id) const;
ErrorOr<types::TypeId> substitute_typevars_in_type_helper(const types::TypeId type_id, const types::GenericInferences generic_inferences, const types::ModuleId module_id);
bool is_string(const types::TypeId type_id) const;
types::CheckedVariable get_variable(const types::VarId id) const;
protected:
explicit CheckedProgram(NonnullRefPtr<compiler::Compiler>&& a_compiler, JaktInternal::Array<NonnullRefPtr<types::Module>>&& a_modules, JaktInternal::Dictionary<String,types::LoadedModule>&& a_loaded_modules);
public:
static ErrorOr<NonnullRefPtr<CheckedProgram>> create(NonnullRefPtr<compiler::Compiler> compiler, JaktInternal::Array<NonnullRefPtr<types::Module>> modules, JaktInternal::Dictionary<String,types::LoadedModule> loaded_modules);

NonnullRefPtr<types::CheckedFunction> get_function(const types::FunctionId id) const;
ErrorOr<JaktInternal::Optional<types::Value>> find_comptime_binding_in_scope(const types::ScopeId scope_id, const String name) const;
i64 get_bits(const types::TypeId type_id) const;
NonnullRefPtr<types::Type> get_type(const types::TypeId id) const;
ErrorOr<types::TypeId> find_or_add_type_id(const NonnullRefPtr<types::Type> type, const types::ModuleId module_id);
ErrorOr<types::StructId> find_struct_in_prelude(const String name) const;
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>>> find_namespace_in_scope(const types::ScopeId scope_id, const String name) const;
types::CheckedEnum get_enum(const types::EnumId id) const;
ErrorOr<String> type_name(const types::TypeId type_id) const;
ErrorOr<JaktInternal::Optional<types::CheckedVariable>> find_var_in_scope(const types::ScopeId scope_id, const String var) const;
bool is_signed(const types::TypeId type_id) const;
ErrorOr<JaktInternal::Optional<types::FunctionId>> find_function_in_scope(const types::ScopeId parent_scope_id, const String function_name) const;
types::CheckedStruct get_struct(const types::StructId id) const;
ErrorOr<JaktInternal::Optional<types::StructId>> check_and_extract_weak_ptr(const types::StructId struct_id, const JaktInternal::Array<types::TypeId> args) const;
ErrorOr<JaktInternal::Optional<types::EnumId>> find_enum_in_scope(const types::ScopeId scope_id, const String name) const;
JaktInternal::Optional<types::LoadedModule> get_loaded_module(const String module_name) const;
bool is_numeric(const types::TypeId type_id) const;
ErrorOr<types::TypeId> substitute_typevars_in_type(const types::TypeId type_id, const types::GenericInferences generic_inferences, const types::ModuleId module_id);
ErrorOr<NonnullRefPtr<types::Scope>> get_scope(const types::ScopeId id) const;
ErrorOr<String> debug_description() const;
};class FunctionGenerics : public RefCounted<FunctionGenerics>, public Weakable<FunctionGenerics> {
  public:
virtual ~FunctionGenerics() = default;
JaktInternal::Array<types::CheckedParameter> base_params;JaktInternal::Array<types::FunctionGenericParameter> params;JaktInternal::Array<JaktInternal::Array<types::TypeId>> specializations;protected:
explicit FunctionGenerics(JaktInternal::Array<types::CheckedParameter>&& a_base_params, JaktInternal::Array<types::FunctionGenericParameter>&& a_params, JaktInternal::Array<JaktInternal::Array<types::TypeId>>&& a_specializations);
public:
static ErrorOr<NonnullRefPtr<FunctionGenerics>> create(JaktInternal::Array<types::CheckedParameter> base_params, JaktInternal::Array<types::FunctionGenericParameter> params, JaktInternal::Array<JaktInternal::Array<types::TypeId>> specializations);

bool is_specialized_for_types(const JaktInternal::Array<types::TypeId> types) const;
ErrorOr<String> debug_description() const;
};class CheckedFunction : public RefCounted<CheckedFunction>, public Weakable<CheckedFunction> {
  public:
virtual ~CheckedFunction() = default;
String name;utility::Span name_span;types::CheckedVisibility visibility;types::TypeId return_type_id;JaktInternal::Optional<utility::Span> return_type_span;JaktInternal::Array<types::CheckedParameter> params;NonnullRefPtr<types::FunctionGenerics> generics;types::CheckedBlock block;bool can_throw;parser::FunctionType type;parser::FunctionLinkage linkage;types::ScopeId function_scope_id;bool is_instantiated;JaktInternal::Optional<parser::ParsedFunction> parsed_function;bool is_comptime;bool is_virtual;bool is_override;bool is_static() const;
bool is_mutating() const;
parser::ParsedFunction to_parsed_function() const;
bool is_specialized_for_types(const JaktInternal::Array<types::TypeId> types) const;
protected:
explicit CheckedFunction(String&& a_name, utility::Span&& a_name_span, types::CheckedVisibility&& a_visibility, types::TypeId&& a_return_type_id, JaktInternal::Optional<utility::Span>&& a_return_type_span, JaktInternal::Array<types::CheckedParameter>&& a_params, NonnullRefPtr<types::FunctionGenerics>&& a_generics, types::CheckedBlock&& a_block, bool&& a_can_throw, parser::FunctionType&& a_type, parser::FunctionLinkage&& a_linkage, types::ScopeId&& a_function_scope_id, bool&& a_is_instantiated, JaktInternal::Optional<parser::ParsedFunction>&& a_parsed_function, bool&& a_is_comptime, bool&& a_is_virtual, bool&& a_is_override);
public:
static ErrorOr<NonnullRefPtr<CheckedFunction>> create(String name, utility::Span name_span, types::CheckedVisibility visibility, types::TypeId return_type_id, JaktInternal::Optional<utility::Span> return_type_span, JaktInternal::Array<types::CheckedParameter> params, NonnullRefPtr<types::FunctionGenerics> generics, types::CheckedBlock block, bool can_throw, parser::FunctionType type, parser::FunctionLinkage linkage, types::ScopeId function_scope_id, bool is_instantiated, JaktInternal::Optional<parser::ParsedFunction> parsed_function, bool is_comptime, bool is_virtual, bool is_override);

ErrorOr<void> add_param(const types::CheckedParameter checked_param);
ErrorOr<void> set_params(const JaktInternal::Array<types::CheckedParameter> checked_params);
ErrorOr<String> debug_description() const;
};struct CheckedStruct {
  public:
String name;utility::Span name_span;JaktInternal::Array<types::TypeId> generic_parameters;JaktInternal::Array<types::VarId> fields;types::ScopeId scope_id;parser::DefinitionLinkage definition_linkage;parser::RecordType record_type;types::TypeId type_id;JaktInternal::Optional<types::StructId> super_struct_id;CheckedStruct(String a_name, utility::Span a_name_span, JaktInternal::Array<types::TypeId> a_generic_parameters, JaktInternal::Array<types::VarId> a_fields, types::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, parser::RecordType a_record_type, types::TypeId a_type_id, JaktInternal::Optional<types::StructId> a_super_struct_id);

ErrorOr<String> debug_description() const;
};struct FieldRecord {
  public:
types::StructId struct_id;types::VarId field_id;FieldRecord(types::StructId a_struct_id, types::VarId a_field_id);

ErrorOr<String> debug_description() const;
};namespace MaybeResolvedScope_Details {
struct Resolved{
types::ScopeId value;
template<typename... Args>
Resolved(Args&&... args): value { forward<Args>(args)... } {}
};
struct Unresolved {
NonnullRefPtr<types::MaybeResolvedScope> parent_scope;
String relative_name;
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
template<typename V, typename... Args> static auto create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) MaybeResolvedScope(V(forward<Args>(args)...)));
}
ErrorOr<String> debug_description() const;
ErrorOr<NonnullRefPtr<types::MaybeResolvedScope>> try_resolve(const NonnullRefPtr<types::CheckedProgram> program) const;
};
struct CheckedEnum {
  public:
String name;utility::Span name_span;JaktInternal::Array<types::TypeId> generic_parameters;JaktInternal::Array<types::CheckedEnumVariant> variants;types::ScopeId scope_id;parser::DefinitionLinkage definition_linkage;parser::RecordType record_type;types::TypeId underlying_type_id;types::TypeId type_id;bool is_boxed;CheckedEnum(String a_name, utility::Span a_name_span, JaktInternal::Array<types::TypeId> a_generic_parameters, JaktInternal::Array<types::CheckedEnumVariant> a_variants, types::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, parser::RecordType a_record_type, types::TypeId a_underlying_type_id, types::TypeId a_type_id, bool a_is_boxed);

ErrorOr<String> debug_description() const;
};struct CheckedParameter {
  public:
bool requires_label;types::CheckedVariable variable;JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> default_value;CheckedParameter(bool a_requires_label, types::CheckedVariable a_variable, JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> a_default_value);

ErrorOr<String> debug_description() const;
};namespace CheckedCapture_Details {
struct ByValue {
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByValue(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByReference {
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByReference(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByMutableReference {
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByMutableReference(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct CheckedCapture : public Variant<CheckedCapture_Details::ByValue, CheckedCapture_Details::ByReference, CheckedCapture_Details::ByMutableReference> {
using Variant<CheckedCapture_Details::ByValue, CheckedCapture_Details::ByReference, CheckedCapture_Details::ByMutableReference>::Variant;
    using ByValue = CheckedCapture_Details::ByValue;
    using ByReference = CheckedCapture_Details::ByReference;
    using ByMutableReference = CheckedCapture_Details::ByMutableReference;
ErrorOr<String> debug_description() const;
String name() const;
utility::Span span() const;
};
}
template<>struct Formatter<types::SafetyMode> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::SafetyMode const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::ModuleId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::ModuleId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::FunctionId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::FunctionId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::TypeId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::TypeId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedCall> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedCall const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedVisibility> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedVisibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::ScopeId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::ScopeId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::BlockControlFlow> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::BlockControlFlow const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedBlock> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedBlock const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::GenericInferences> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::GenericInferences const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::LoadedModule> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::LoadedModule const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::ResolvedNamespace> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::ResolvedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedMatchBody> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedMatchBody const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedMatchCase> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedMatchCase const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedNumericConstant> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedNumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedTypeCast> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedTypeCast const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::EnumId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::EnumId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedEnumVariant> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedUnaryOperator> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedUnaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedEnumVariantBinding> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedEnumVariantBinding const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedVariable> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedVariable const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::VarId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::VarId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedStatement> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedStatement const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedExpression> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedExpression const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedVarDecl> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedVarDecl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::NumberConstant> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::NumberConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::FunctionGenericParameter> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::FunctionGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedNamespace> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::StructId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::StructId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::Value> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::Value const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::ValueImpl> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::ValueImpl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::Scope> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::Scope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::Module> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::Module const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::BuiltinType> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::BuiltinType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::StructOrEnumId> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::StructOrEnumId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::Type> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::Type const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedProgram> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedProgram const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::FunctionGenerics> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::FunctionGenerics const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedFunction> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedFunction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedStruct> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedStruct const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::FieldRecord> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::FieldRecord const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::MaybeResolvedScope> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::MaybeResolvedScope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedEnum> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedEnum const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedParameter> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<types::CheckedCapture> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, types::CheckedCapture const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
