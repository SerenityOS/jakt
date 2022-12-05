#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "lexer.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace parser {
namespace ParsedCapture_Details {
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
struct ParsedCapture : public Variant<ParsedCapture_Details::ByValue, ParsedCapture_Details::ByReference, ParsedCapture_Details::ByMutableReference> {
using Variant<ParsedCapture_Details::ByValue, ParsedCapture_Details::ByReference, ParsedCapture_Details::ByMutableReference>::Variant;
    using ByValue = ParsedCapture_Details::ByValue;
    using ByReference = ParsedCapture_Details::ByReference;
    using ByMutableReference = ParsedCapture_Details::ByMutableReference;
ErrorOr<String> debug_description() const;
String name() const;
utility::Span span() const;
};
struct ParsedBlock {
  public:
JaktInternal::Array<NonnullRefPtr<parser::ParsedStatement>> stmts;bool equals(parser::ParsedBlock const rhs_block) const;
ParsedBlock(JaktInternal::Array<NonnullRefPtr<parser::ParsedStatement>> a_stmts);

JaktInternal::Optional<utility::Span> find_yield_span() const;
ErrorOr<JaktInternal::Optional<utility::Span>> span(parser::Parser const parser) const;
JaktInternal::Optional<utility::Span> find_yield_keyword_span() const;
ErrorOr<String> debug_description() const;
};namespace ParsedMatchBody_Details {
struct Expression{
NonnullRefPtr<parser::ParsedExpression> value;
template<typename _MemberT0>
Expression(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Block{
parser::ParsedBlock value;
template<typename _MemberT0>
Block(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct ParsedMatchBody : public Variant<ParsedMatchBody_Details::Expression, ParsedMatchBody_Details::Block> {
using Variant<ParsedMatchBody_Details::Expression, ParsedMatchBody_Details::Block>::Variant;
    using Expression = ParsedMatchBody_Details::Expression;
    using Block = ParsedMatchBody_Details::Block;
ErrorOr<String> debug_description() const;
};
struct ParsedMatchCase {
  public:
JaktInternal::Array<parser::ParsedMatchPattern> patterns;utility::Span marker_span;parser::ParsedMatchBody body;bool equals(parser::ParsedMatchCase const rhs_match_case) const;
ParsedMatchCase(JaktInternal::Array<parser::ParsedMatchPattern> a_patterns, utility::Span a_marker_span, parser::ParsedMatchBody a_body);

ErrorOr<String> debug_description() const;
};namespace FunctionType_Details {
struct Normal {
};
struct ImplicitConstructor {
};
struct ImplicitEnumConstructor {
};
struct ExternalClassConstructor {
};
struct Expression {
};
struct Closure {
};
}
struct FunctionType : public Variant<FunctionType_Details::Normal, FunctionType_Details::ImplicitConstructor, FunctionType_Details::ImplicitEnumConstructor, FunctionType_Details::ExternalClassConstructor, FunctionType_Details::Expression, FunctionType_Details::Closure> {
using Variant<FunctionType_Details::Normal, FunctionType_Details::ImplicitConstructor, FunctionType_Details::ImplicitEnumConstructor, FunctionType_Details::ExternalClassConstructor, FunctionType_Details::Expression, FunctionType_Details::Closure>::Variant;
    using Normal = FunctionType_Details::Normal;
    using ImplicitConstructor = FunctionType_Details::ImplicitConstructor;
    using ImplicitEnumConstructor = FunctionType_Details::ImplicitEnumConstructor;
    using ExternalClassConstructor = FunctionType_Details::ExternalClassConstructor;
    using Expression = FunctionType_Details::Expression;
    using Closure = FunctionType_Details::Closure;
ErrorOr<String> debug_description() const;
};
struct ParsedVarDecl {
  public:
String name;NonnullRefPtr<parser::ParsedType> parsed_type;bool is_mutable;JaktInternal::Optional<utility::Span> inlay_span;utility::Span span;ParsedVarDecl(String a_name, NonnullRefPtr<parser::ParsedType> a_parsed_type, bool a_is_mutable, JaktInternal::Optional<utility::Span> a_inlay_span, utility::Span a_span);

bool equals(parser::ParsedVarDecl const rhs_var_decl) const;
ErrorOr<String> debug_description() const;
};namespace NumericConstant_Details {
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
struct UnknownSigned{
i64 value;
template<typename _MemberT0>
UnknownSigned(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct UnknownUnsigned{
u64 value;
template<typename _MemberT0>
UnknownUnsigned(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct NumericConstant : public Variant<NumericConstant_Details::I8, NumericConstant_Details::I16, NumericConstant_Details::I32, NumericConstant_Details::I64, NumericConstant_Details::U8, NumericConstant_Details::U16, NumericConstant_Details::U32, NumericConstant_Details::U64, NumericConstant_Details::USize, NumericConstant_Details::F32, NumericConstant_Details::F64, NumericConstant_Details::UnknownSigned, NumericConstant_Details::UnknownUnsigned> {
using Variant<NumericConstant_Details::I8, NumericConstant_Details::I16, NumericConstant_Details::I32, NumericConstant_Details::I64, NumericConstant_Details::U8, NumericConstant_Details::U16, NumericConstant_Details::U32, NumericConstant_Details::U64, NumericConstant_Details::USize, NumericConstant_Details::F32, NumericConstant_Details::F64, NumericConstant_Details::UnknownSigned, NumericConstant_Details::UnknownUnsigned>::Variant;
    using I8 = NumericConstant_Details::I8;
    using I16 = NumericConstant_Details::I16;
    using I32 = NumericConstant_Details::I32;
    using I64 = NumericConstant_Details::I64;
    using U8 = NumericConstant_Details::U8;
    using U16 = NumericConstant_Details::U16;
    using U32 = NumericConstant_Details::U32;
    using U64 = NumericConstant_Details::U64;
    using USize = NumericConstant_Details::USize;
    using F32 = NumericConstant_Details::F32;
    using F64 = NumericConstant_Details::F64;
    using UnknownSigned = NumericConstant_Details::UnknownSigned;
    using UnknownUnsigned = NumericConstant_Details::UnknownUnsigned;
ErrorOr<String> debug_description() const;
size_t to_usize() const;
};
struct ParsedCall {
  public:
JaktInternal::Array<String> namespace_;String name;JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> args;JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> type_args;ParsedCall(JaktInternal::Array<String> a_namespace_, String a_name, JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> a_args, JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> a_type_args);

bool equals(parser::ParsedCall const rhs_parsed_call) const;
ErrorOr<String> debug_description() const;
};namespace TypeCast_Details {
struct Fallible{
NonnullRefPtr<parser::ParsedType> value;
template<typename _MemberT0>
Fallible(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Infallible{
NonnullRefPtr<parser::ParsedType> value;
template<typename _MemberT0>
Infallible(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct TypeCast : public Variant<TypeCast_Details::Fallible, TypeCast_Details::Infallible> {
using Variant<TypeCast_Details::Fallible, TypeCast_Details::Infallible>::Variant;
    using Fallible = TypeCast_Details::Fallible;
    using Infallible = TypeCast_Details::Infallible;
ErrorOr<String> debug_description() const;
NonnullRefPtr<parser::ParsedType> parsed_type() const;
};
namespace ParsedType_Details {
struct Name {
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Name(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct NamespacedName {
String name;
JaktInternal::Array<String> namespaces;
JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> params;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
NamespacedName(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
name{ forward<_MemberT0>(member_0)},
namespaces{ forward<_MemberT1>(member_1)},
params{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct GenericType {
String name;
JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> generic_parameters;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
GenericType(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
name{ forward<_MemberT0>(member_0)},
generic_parameters{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct JaktArray {
NonnullRefPtr<parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
JaktArray(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Dictionary {
NonnullRefPtr<parser::ParsedType> key;
NonnullRefPtr<parser::ParsedType> value;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Dictionary(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
key{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct JaktTuple {
JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> types;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
JaktTuple(_MemberT0&& member_0, _MemberT1&& member_1):
types{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Set {
NonnullRefPtr<parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Set(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Optional {
NonnullRefPtr<parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Optional(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Reference {
NonnullRefPtr<parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Reference(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct MutableReference {
NonnullRefPtr<parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
MutableReference(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct RawPtr {
NonnullRefPtr<parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
RawPtr(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct WeakPtr {
NonnullRefPtr<parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
WeakPtr(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Function {
JaktInternal::Array<parser::ParsedParameter> params;
bool can_throw;
NonnullRefPtr<parser::ParsedType> return_type;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
params{ forward<_MemberT0>(member_0)},
can_throw{ forward<_MemberT1>(member_1)},
return_type{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Empty {
};
}
struct ParsedType : public Variant<ParsedType_Details::Name, ParsedType_Details::NamespacedName, ParsedType_Details::GenericType, ParsedType_Details::JaktArray, ParsedType_Details::Dictionary, ParsedType_Details::JaktTuple, ParsedType_Details::Set, ParsedType_Details::Optional, ParsedType_Details::Reference, ParsedType_Details::MutableReference, ParsedType_Details::RawPtr, ParsedType_Details::WeakPtr, ParsedType_Details::Function, ParsedType_Details::Empty>, public RefCounted<ParsedType> {
using Variant<ParsedType_Details::Name, ParsedType_Details::NamespacedName, ParsedType_Details::GenericType, ParsedType_Details::JaktArray, ParsedType_Details::Dictionary, ParsedType_Details::JaktTuple, ParsedType_Details::Set, ParsedType_Details::Optional, ParsedType_Details::Reference, ParsedType_Details::MutableReference, ParsedType_Details::RawPtr, ParsedType_Details::WeakPtr, ParsedType_Details::Function, ParsedType_Details::Empty>::Variant;
    using Name = ParsedType_Details::Name;
    using NamespacedName = ParsedType_Details::NamespacedName;
    using GenericType = ParsedType_Details::GenericType;
    using JaktArray = ParsedType_Details::JaktArray;
    using Dictionary = ParsedType_Details::Dictionary;
    using JaktTuple = ParsedType_Details::JaktTuple;
    using Set = ParsedType_Details::Set;
    using Optional = ParsedType_Details::Optional;
    using Reference = ParsedType_Details::Reference;
    using MutableReference = ParsedType_Details::MutableReference;
    using RawPtr = ParsedType_Details::RawPtr;
    using WeakPtr = ParsedType_Details::WeakPtr;
    using Function = ParsedType_Details::Function;
    using Empty = ParsedType_Details::Empty;
template<typename V, typename... Args> static auto create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) ParsedType(V(forward<Args>(args)...)));
}
ErrorOr<String> debug_description() const;
bool equals(NonnullRefPtr<parser::ParsedType> const rhs_parsed_type) const;
utility::Span span() const;
};
namespace UnaryOperator_Details {
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
parser::TypeCast value;
template<typename _MemberT0>
TypeCast(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Is{
NonnullRefPtr<parser::ParsedType> value;
template<typename _MemberT0>
Is(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct IsEnumVariant {
NonnullRefPtr<parser::ParsedType> inner;
JaktInternal::Array<parser::EnumVariantPatternArgument> bindings;
template<typename _MemberT0, typename _MemberT1>
IsEnumVariant(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
bindings{ forward<_MemberT1>(member_1)}
{}
};
}
struct UnaryOperator : public Variant<UnaryOperator_Details::PreIncrement, UnaryOperator_Details::PostIncrement, UnaryOperator_Details::PreDecrement, UnaryOperator_Details::PostDecrement, UnaryOperator_Details::Negate, UnaryOperator_Details::Dereference, UnaryOperator_Details::RawAddress, UnaryOperator_Details::Reference, UnaryOperator_Details::MutableReference, UnaryOperator_Details::LogicalNot, UnaryOperator_Details::BitwiseNot, UnaryOperator_Details::TypeCast, UnaryOperator_Details::Is, UnaryOperator_Details::IsEnumVariant> {
using Variant<UnaryOperator_Details::PreIncrement, UnaryOperator_Details::PostIncrement, UnaryOperator_Details::PreDecrement, UnaryOperator_Details::PostDecrement, UnaryOperator_Details::Negate, UnaryOperator_Details::Dereference, UnaryOperator_Details::RawAddress, UnaryOperator_Details::Reference, UnaryOperator_Details::MutableReference, UnaryOperator_Details::LogicalNot, UnaryOperator_Details::BitwiseNot, UnaryOperator_Details::TypeCast, UnaryOperator_Details::Is, UnaryOperator_Details::IsEnumVariant>::Variant;
    using PreIncrement = UnaryOperator_Details::PreIncrement;
    using PostIncrement = UnaryOperator_Details::PostIncrement;
    using PreDecrement = UnaryOperator_Details::PreDecrement;
    using PostDecrement = UnaryOperator_Details::PostDecrement;
    using Negate = UnaryOperator_Details::Negate;
    using Dereference = UnaryOperator_Details::Dereference;
    using RawAddress = UnaryOperator_Details::RawAddress;
    using Reference = UnaryOperator_Details::Reference;
    using MutableReference = UnaryOperator_Details::MutableReference;
    using LogicalNot = UnaryOperator_Details::LogicalNot;
    using BitwiseNot = UnaryOperator_Details::BitwiseNot;
    using TypeCast = UnaryOperator_Details::TypeCast;
    using Is = UnaryOperator_Details::Is;
    using IsEnumVariant = UnaryOperator_Details::IsEnumVariant;
ErrorOr<String> debug_description() const;
bool equals(parser::UnaryOperator const rhs_op) const;
};
namespace BinaryOperator_Details {
struct Add {
};
struct Subtract {
};
struct Multiply {
};
struct Divide {
};
struct Modulo {
};
struct LessThan {
};
struct LessThanOrEqual {
};
struct GreaterThan {
};
struct GreaterThanOrEqual {
};
struct Equal {
};
struct NotEqual {
};
struct BitwiseAnd {
};
struct BitwiseXor {
};
struct BitwiseOr {
};
struct BitwiseLeftShift {
};
struct BitwiseRightShift {
};
struct ArithmeticLeftShift {
};
struct ArithmeticRightShift {
};
struct LogicalAnd {
};
struct LogicalOr {
};
struct NoneCoalescing {
};
struct Assign {
};
struct BitwiseAndAssign {
};
struct BitwiseOrAssign {
};
struct BitwiseXorAssign {
};
struct BitwiseLeftShiftAssign {
};
struct BitwiseRightShiftAssign {
};
struct AddAssign {
};
struct SubtractAssign {
};
struct MultiplyAssign {
};
struct ModuloAssign {
};
struct DivideAssign {
};
struct NoneCoalescingAssign {
};
struct Garbage {
};
}
struct BinaryOperator : public Variant<BinaryOperator_Details::Add, BinaryOperator_Details::Subtract, BinaryOperator_Details::Multiply, BinaryOperator_Details::Divide, BinaryOperator_Details::Modulo, BinaryOperator_Details::LessThan, BinaryOperator_Details::LessThanOrEqual, BinaryOperator_Details::GreaterThan, BinaryOperator_Details::GreaterThanOrEqual, BinaryOperator_Details::Equal, BinaryOperator_Details::NotEqual, BinaryOperator_Details::BitwiseAnd, BinaryOperator_Details::BitwiseXor, BinaryOperator_Details::BitwiseOr, BinaryOperator_Details::BitwiseLeftShift, BinaryOperator_Details::BitwiseRightShift, BinaryOperator_Details::ArithmeticLeftShift, BinaryOperator_Details::ArithmeticRightShift, BinaryOperator_Details::LogicalAnd, BinaryOperator_Details::LogicalOr, BinaryOperator_Details::NoneCoalescing, BinaryOperator_Details::Assign, BinaryOperator_Details::BitwiseAndAssign, BinaryOperator_Details::BitwiseOrAssign, BinaryOperator_Details::BitwiseXorAssign, BinaryOperator_Details::BitwiseLeftShiftAssign, BinaryOperator_Details::BitwiseRightShiftAssign, BinaryOperator_Details::AddAssign, BinaryOperator_Details::SubtractAssign, BinaryOperator_Details::MultiplyAssign, BinaryOperator_Details::ModuloAssign, BinaryOperator_Details::DivideAssign, BinaryOperator_Details::NoneCoalescingAssign, BinaryOperator_Details::Garbage> {
using Variant<BinaryOperator_Details::Add, BinaryOperator_Details::Subtract, BinaryOperator_Details::Multiply, BinaryOperator_Details::Divide, BinaryOperator_Details::Modulo, BinaryOperator_Details::LessThan, BinaryOperator_Details::LessThanOrEqual, BinaryOperator_Details::GreaterThan, BinaryOperator_Details::GreaterThanOrEqual, BinaryOperator_Details::Equal, BinaryOperator_Details::NotEqual, BinaryOperator_Details::BitwiseAnd, BinaryOperator_Details::BitwiseXor, BinaryOperator_Details::BitwiseOr, BinaryOperator_Details::BitwiseLeftShift, BinaryOperator_Details::BitwiseRightShift, BinaryOperator_Details::ArithmeticLeftShift, BinaryOperator_Details::ArithmeticRightShift, BinaryOperator_Details::LogicalAnd, BinaryOperator_Details::LogicalOr, BinaryOperator_Details::NoneCoalescing, BinaryOperator_Details::Assign, BinaryOperator_Details::BitwiseAndAssign, BinaryOperator_Details::BitwiseOrAssign, BinaryOperator_Details::BitwiseXorAssign, BinaryOperator_Details::BitwiseLeftShiftAssign, BinaryOperator_Details::BitwiseRightShiftAssign, BinaryOperator_Details::AddAssign, BinaryOperator_Details::SubtractAssign, BinaryOperator_Details::MultiplyAssign, BinaryOperator_Details::ModuloAssign, BinaryOperator_Details::DivideAssign, BinaryOperator_Details::NoneCoalescingAssign, BinaryOperator_Details::Garbage>::Variant;
    using Add = BinaryOperator_Details::Add;
    using Subtract = BinaryOperator_Details::Subtract;
    using Multiply = BinaryOperator_Details::Multiply;
    using Divide = BinaryOperator_Details::Divide;
    using Modulo = BinaryOperator_Details::Modulo;
    using LessThan = BinaryOperator_Details::LessThan;
    using LessThanOrEqual = BinaryOperator_Details::LessThanOrEqual;
    using GreaterThan = BinaryOperator_Details::GreaterThan;
    using GreaterThanOrEqual = BinaryOperator_Details::GreaterThanOrEqual;
    using Equal = BinaryOperator_Details::Equal;
    using NotEqual = BinaryOperator_Details::NotEqual;
    using BitwiseAnd = BinaryOperator_Details::BitwiseAnd;
    using BitwiseXor = BinaryOperator_Details::BitwiseXor;
    using BitwiseOr = BinaryOperator_Details::BitwiseOr;
    using BitwiseLeftShift = BinaryOperator_Details::BitwiseLeftShift;
    using BitwiseRightShift = BinaryOperator_Details::BitwiseRightShift;
    using ArithmeticLeftShift = BinaryOperator_Details::ArithmeticLeftShift;
    using ArithmeticRightShift = BinaryOperator_Details::ArithmeticRightShift;
    using LogicalAnd = BinaryOperator_Details::LogicalAnd;
    using LogicalOr = BinaryOperator_Details::LogicalOr;
    using NoneCoalescing = BinaryOperator_Details::NoneCoalescing;
    using Assign = BinaryOperator_Details::Assign;
    using BitwiseAndAssign = BinaryOperator_Details::BitwiseAndAssign;
    using BitwiseOrAssign = BinaryOperator_Details::BitwiseOrAssign;
    using BitwiseXorAssign = BinaryOperator_Details::BitwiseXorAssign;
    using BitwiseLeftShiftAssign = BinaryOperator_Details::BitwiseLeftShiftAssign;
    using BitwiseRightShiftAssign = BinaryOperator_Details::BitwiseRightShiftAssign;
    using AddAssign = BinaryOperator_Details::AddAssign;
    using SubtractAssign = BinaryOperator_Details::SubtractAssign;
    using MultiplyAssign = BinaryOperator_Details::MultiplyAssign;
    using ModuloAssign = BinaryOperator_Details::ModuloAssign;
    using DivideAssign = BinaryOperator_Details::DivideAssign;
    using NoneCoalescingAssign = BinaryOperator_Details::NoneCoalescingAssign;
    using Garbage = BinaryOperator_Details::Garbage;
ErrorOr<String> debug_description() const;
bool equals(parser::BinaryOperator const rhs_op) const;
bool is_assignment() const;
};
struct EnumVariantPatternArgument {
  public:
JaktInternal::Optional<String> name;String binding;utility::Span span;bool is_reference;bool is_mutable;EnumVariantPatternArgument(JaktInternal::Optional<String> a_name, String a_binding, utility::Span a_span, bool a_is_reference, bool a_is_mutable);

bool equals(parser::EnumVariantPatternArgument const rhs_variant_pattern_argument) const;
ErrorOr<String> debug_description() const;
};namespace ParsedExpression_Details {
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
parser::NumericConstant val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
NumericConstant(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
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
struct SingleQuotedString {
String val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
SingleQuotedString(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct SingleQuotedByteString {
String val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
SingleQuotedByteString(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Call {
parser::ParsedCall call;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Call(_MemberT0&& member_0, _MemberT1&& member_1):
call{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct MethodCall {
NonnullRefPtr<parser::ParsedExpression> expr;
parser::ParsedCall call;
bool is_optional;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
MethodCall(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
call{ forward<_MemberT1>(member_1)},
is_optional{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct IndexedTuple {
NonnullRefPtr<parser::ParsedExpression> expr;
size_t index;
bool is_optional;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
IndexedTuple(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
is_optional{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct IndexedStruct {
NonnullRefPtr<parser::ParsedExpression> expr;
String field_name;
bool is_optional;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
IndexedStruct(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
field_name{ forward<_MemberT1>(member_1)},
is_optional{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Var {
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Var(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct IndexedExpression {
NonnullRefPtr<parser::ParsedExpression> base;
NonnullRefPtr<parser::ParsedExpression> index;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
IndexedExpression(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
base{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct UnaryOp {
NonnullRefPtr<parser::ParsedExpression> expr;
parser::UnaryOperator op;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
UnaryOp(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
expr{ forward<_MemberT0>(member_0)},
op{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct BinaryOp {
NonnullRefPtr<parser::ParsedExpression> lhs;
parser::BinaryOperator op;
NonnullRefPtr<parser::ParsedExpression> rhs;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
BinaryOp(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
lhs{ forward<_MemberT0>(member_0)},
op{ forward<_MemberT1>(member_1)},
rhs{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Operator {
parser::BinaryOperator op;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Operator(_MemberT0&& member_0, _MemberT1&& member_1):
op{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct OptionalSome {
NonnullRefPtr<parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
OptionalSome(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct OptionalNone{
utility::Span value;
template<typename _MemberT0>
OptionalNone(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct JaktArray {
JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> values;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> fill_size;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
JaktArray(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
values{ forward<_MemberT0>(member_0)},
fill_size{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct JaktDictionary {
JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>>> values;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
JaktDictionary(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Set {
JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> values;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Set(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct JaktTuple {
JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> values;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
JaktTuple(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Range {
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> from;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> to;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Range(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
from{ forward<_MemberT0>(member_0)},
to{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct ForcedUnwrap {
NonnullRefPtr<parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ForcedUnwrap(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Match {
NonnullRefPtr<parser::ParsedExpression> expr;
JaktInternal::Array<parser::ParsedMatchCase> cases;
utility::Span span;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Match(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
cases{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
marker_span{ forward<_MemberT3>(member_3)}
{}
};
struct EnumVariantArg {
NonnullRefPtr<parser::ParsedExpression> expr;
parser::EnumVariantPatternArgument arg;
NonnullRefPtr<parser::ParsedType> enum_variant;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
EnumVariantArg(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
arg{ forward<_MemberT1>(member_1)},
enum_variant{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct NamespacedVar {
String name;
JaktInternal::Array<String> namespace_;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
NamespacedVar(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
name{ forward<_MemberT0>(member_0)},
namespace_{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Function {
JaktInternal::Array<parser::ParsedCapture> captures;
JaktInternal::Array<parser::ParsedParameter> params;
bool can_throw;
bool is_fat_arrow;
NonnullRefPtr<parser::ParsedType> return_type;
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6):
captures{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
can_throw{ forward<_MemberT2>(member_2)},
is_fat_arrow{ forward<_MemberT3>(member_3)},
return_type{ forward<_MemberT4>(member_4)},
block{ forward<_MemberT5>(member_5)},
span{ forward<_MemberT6>(member_6)}
{}
};
struct Try {
NonnullRefPtr<parser::ParsedExpression> expr;
JaktInternal::Optional<parser::ParsedBlock> catch_block;
JaktInternal::Optional<String> catch_name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Try(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
catch_block{ forward<_MemberT1>(member_1)},
catch_name{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct TryBlock {
NonnullRefPtr<parser::ParsedStatement> stmt;
String error_name;
utility::Span error_span;
parser::ParsedBlock catch_block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
TryBlock(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
stmt{ forward<_MemberT0>(member_0)},
error_name{ forward<_MemberT1>(member_1)},
error_span{ forward<_MemberT2>(member_2)},
catch_block{ forward<_MemberT3>(member_3)},
span{ forward<_MemberT4>(member_4)}
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
struct ParsedExpression : public Variant<ParsedExpression_Details::Boolean, ParsedExpression_Details::NumericConstant, ParsedExpression_Details::QuotedString, ParsedExpression_Details::SingleQuotedString, ParsedExpression_Details::SingleQuotedByteString, ParsedExpression_Details::Call, ParsedExpression_Details::MethodCall, ParsedExpression_Details::IndexedTuple, ParsedExpression_Details::IndexedStruct, ParsedExpression_Details::Var, ParsedExpression_Details::IndexedExpression, ParsedExpression_Details::UnaryOp, ParsedExpression_Details::BinaryOp, ParsedExpression_Details::Operator, ParsedExpression_Details::OptionalSome, ParsedExpression_Details::OptionalNone, ParsedExpression_Details::JaktArray, ParsedExpression_Details::JaktDictionary, ParsedExpression_Details::Set, ParsedExpression_Details::JaktTuple, ParsedExpression_Details::Range, ParsedExpression_Details::ForcedUnwrap, ParsedExpression_Details::Match, ParsedExpression_Details::EnumVariantArg, ParsedExpression_Details::NamespacedVar, ParsedExpression_Details::Function, ParsedExpression_Details::Try, ParsedExpression_Details::TryBlock, ParsedExpression_Details::Garbage>, public RefCounted<ParsedExpression> {
using Variant<ParsedExpression_Details::Boolean, ParsedExpression_Details::NumericConstant, ParsedExpression_Details::QuotedString, ParsedExpression_Details::SingleQuotedString, ParsedExpression_Details::SingleQuotedByteString, ParsedExpression_Details::Call, ParsedExpression_Details::MethodCall, ParsedExpression_Details::IndexedTuple, ParsedExpression_Details::IndexedStruct, ParsedExpression_Details::Var, ParsedExpression_Details::IndexedExpression, ParsedExpression_Details::UnaryOp, ParsedExpression_Details::BinaryOp, ParsedExpression_Details::Operator, ParsedExpression_Details::OptionalSome, ParsedExpression_Details::OptionalNone, ParsedExpression_Details::JaktArray, ParsedExpression_Details::JaktDictionary, ParsedExpression_Details::Set, ParsedExpression_Details::JaktTuple, ParsedExpression_Details::Range, ParsedExpression_Details::ForcedUnwrap, ParsedExpression_Details::Match, ParsedExpression_Details::EnumVariantArg, ParsedExpression_Details::NamespacedVar, ParsedExpression_Details::Function, ParsedExpression_Details::Try, ParsedExpression_Details::TryBlock, ParsedExpression_Details::Garbage>::Variant;
    using Boolean = ParsedExpression_Details::Boolean;
    using NumericConstant = ParsedExpression_Details::NumericConstant;
    using QuotedString = ParsedExpression_Details::QuotedString;
    using SingleQuotedString = ParsedExpression_Details::SingleQuotedString;
    using SingleQuotedByteString = ParsedExpression_Details::SingleQuotedByteString;
    using Call = ParsedExpression_Details::Call;
    using MethodCall = ParsedExpression_Details::MethodCall;
    using IndexedTuple = ParsedExpression_Details::IndexedTuple;
    using IndexedStruct = ParsedExpression_Details::IndexedStruct;
    using Var = ParsedExpression_Details::Var;
    using IndexedExpression = ParsedExpression_Details::IndexedExpression;
    using UnaryOp = ParsedExpression_Details::UnaryOp;
    using BinaryOp = ParsedExpression_Details::BinaryOp;
    using Operator = ParsedExpression_Details::Operator;
    using OptionalSome = ParsedExpression_Details::OptionalSome;
    using OptionalNone = ParsedExpression_Details::OptionalNone;
    using JaktArray = ParsedExpression_Details::JaktArray;
    using JaktDictionary = ParsedExpression_Details::JaktDictionary;
    using Set = ParsedExpression_Details::Set;
    using JaktTuple = ParsedExpression_Details::JaktTuple;
    using Range = ParsedExpression_Details::Range;
    using ForcedUnwrap = ParsedExpression_Details::ForcedUnwrap;
    using Match = ParsedExpression_Details::Match;
    using EnumVariantArg = ParsedExpression_Details::EnumVariantArg;
    using NamespacedVar = ParsedExpression_Details::NamespacedVar;
    using Function = ParsedExpression_Details::Function;
    using Try = ParsedExpression_Details::Try;
    using TryBlock = ParsedExpression_Details::TryBlock;
    using Garbage = ParsedExpression_Details::Garbage;
template<typename V, typename... Args> static auto create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) ParsedExpression(V(forward<Args>(args)...)));
}
ErrorOr<String> debug_description() const;
bool equals(NonnullRefPtr<parser::ParsedExpression> const rhs_expression) const;
utility::Span span() const;
i64 precedence() const;
};
struct ParsedPatternDefault {
  public:
parser::ParsedVarDecl variable;NonnullRefPtr<parser::ParsedExpression> value;ParsedPatternDefault(parser::ParsedVarDecl a_variable, NonnullRefPtr<parser::ParsedExpression> a_value);

ErrorOr<String> debug_description() const;
};namespace ParsedStatement_Details {
struct Expression {
NonnullRefPtr<parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Expression(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Defer {
NonnullRefPtr<parser::ParsedStatement> statement;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Defer(_MemberT0&& member_0, _MemberT1&& member_1):
statement{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct UnsafeBlock {
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
UnsafeBlock(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct DestructuringAssignment {
JaktInternal::Array<parser::ParsedVarDecl> vars;
NonnullRefPtr<parser::ParsedStatement> var_decl;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
DestructuringAssignment(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
vars{ forward<_MemberT0>(member_0)},
var_decl{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct VarDecl {
parser::ParsedVarDecl var;
NonnullRefPtr<parser::ParsedExpression> init;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
VarDecl(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
var{ forward<_MemberT0>(member_0)},
init{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct If {
NonnullRefPtr<parser::ParsedExpression> condition;
parser::ParsedBlock then_block;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> else_statement;
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
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Block(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Loop {
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Loop(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct While {
NonnullRefPtr<parser::ParsedExpression> condition;
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
While(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
condition{ forward<_MemberT0>(member_0)},
block{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct For {
String iterator_name;
utility::Span name_span;
NonnullRefPtr<parser::ParsedExpression> range;
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
For(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
iterator_name{ forward<_MemberT0>(member_0)},
name_span{ forward<_MemberT1>(member_1)},
range{ forward<_MemberT2>(member_2)},
block{ forward<_MemberT3>(member_3)},
span{ forward<_MemberT4>(member_4)}
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
struct Return {
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Return(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Throw {
NonnullRefPtr<parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Throw(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Yield {
NonnullRefPtr<parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Yield(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct InlineCpp {
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
InlineCpp(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Guard {
NonnullRefPtr<parser::ParsedExpression> expr;
parser::ParsedBlock else_block;
parser::ParsedBlock remaining_code;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Guard(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
else_block{ forward<_MemberT1>(member_1)},
remaining_code{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
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
struct ParsedStatement : public Variant<ParsedStatement_Details::Expression, ParsedStatement_Details::Defer, ParsedStatement_Details::UnsafeBlock, ParsedStatement_Details::DestructuringAssignment, ParsedStatement_Details::VarDecl, ParsedStatement_Details::If, ParsedStatement_Details::Block, ParsedStatement_Details::Loop, ParsedStatement_Details::While, ParsedStatement_Details::For, ParsedStatement_Details::Break, ParsedStatement_Details::Continue, ParsedStatement_Details::Return, ParsedStatement_Details::Throw, ParsedStatement_Details::Yield, ParsedStatement_Details::InlineCpp, ParsedStatement_Details::Guard, ParsedStatement_Details::Garbage>, public RefCounted<ParsedStatement> {
using Variant<ParsedStatement_Details::Expression, ParsedStatement_Details::Defer, ParsedStatement_Details::UnsafeBlock, ParsedStatement_Details::DestructuringAssignment, ParsedStatement_Details::VarDecl, ParsedStatement_Details::If, ParsedStatement_Details::Block, ParsedStatement_Details::Loop, ParsedStatement_Details::While, ParsedStatement_Details::For, ParsedStatement_Details::Break, ParsedStatement_Details::Continue, ParsedStatement_Details::Return, ParsedStatement_Details::Throw, ParsedStatement_Details::Yield, ParsedStatement_Details::InlineCpp, ParsedStatement_Details::Guard, ParsedStatement_Details::Garbage>::Variant;
    using Expression = ParsedStatement_Details::Expression;
    using Defer = ParsedStatement_Details::Defer;
    using UnsafeBlock = ParsedStatement_Details::UnsafeBlock;
    using DestructuringAssignment = ParsedStatement_Details::DestructuringAssignment;
    using VarDecl = ParsedStatement_Details::VarDecl;
    using If = ParsedStatement_Details::If;
    using Block = ParsedStatement_Details::Block;
    using Loop = ParsedStatement_Details::Loop;
    using While = ParsedStatement_Details::While;
    using For = ParsedStatement_Details::For;
    using Break = ParsedStatement_Details::Break;
    using Continue = ParsedStatement_Details::Continue;
    using Return = ParsedStatement_Details::Return;
    using Throw = ParsedStatement_Details::Throw;
    using Yield = ParsedStatement_Details::Yield;
    using InlineCpp = ParsedStatement_Details::InlineCpp;
    using Guard = ParsedStatement_Details::Guard;
    using Garbage = ParsedStatement_Details::Garbage;
template<typename V, typename... Args> static auto create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) ParsedStatement(V(forward<Args>(args)...)));
}
ErrorOr<String> debug_description() const;
bool equals(NonnullRefPtr<parser::ParsedStatement> const rhs_statement) const;
utility::Span span() const;
};
namespace FunctionLinkage_Details {
struct Internal {
};
struct External {
};
}
struct FunctionLinkage : public Variant<FunctionLinkage_Details::Internal, FunctionLinkage_Details::External> {
using Variant<FunctionLinkage_Details::Internal, FunctionLinkage_Details::External>::Variant;
    using Internal = FunctionLinkage_Details::Internal;
    using External = FunctionLinkage_Details::External;
ErrorOr<String> debug_description() const;
};
namespace Visibility_Details {
struct Public {
};
struct Private {
};
struct Restricted {
JaktInternal::Array<parser::VisibilityRestriction> whitelist;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Restricted(_MemberT0&& member_0, _MemberT1&& member_1):
whitelist{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct Visibility : public Variant<Visibility_Details::Public, Visibility_Details::Private, Visibility_Details::Restricted> {
using Variant<Visibility_Details::Public, Visibility_Details::Private, Visibility_Details::Restricted>::Variant;
    using Public = Visibility_Details::Public;
    using Private = Visibility_Details::Private;
    using Restricted = Visibility_Details::Restricted;
ErrorOr<String> debug_description() const;
};
struct ParsedFunction {
  public:
String name;utility::Span name_span;parser::Visibility visibility;JaktInternal::Array<parser::ParsedParameter> params;JaktInternal::Array<parser::ParsedGenericParameter> generic_parameters;parser::ParsedBlock block;NonnullRefPtr<parser::ParsedType> return_type;utility::Span return_type_span;bool can_throw;parser::FunctionType type;parser::FunctionLinkage linkage;bool must_instantiate;bool is_comptime;bool is_fat_arrow;ParsedFunction(String a_name, utility::Span a_name_span, parser::Visibility a_visibility, JaktInternal::Array<parser::ParsedParameter> a_params, JaktInternal::Array<parser::ParsedGenericParameter> a_generic_parameters, parser::ParsedBlock a_block, NonnullRefPtr<parser::ParsedType> a_return_type, utility::Span a_return_type_span, bool a_can_throw, parser::FunctionType a_type, parser::FunctionLinkage a_linkage, bool a_must_instantiate, bool a_is_comptime, bool a_is_fat_arrow);

bool equals(parser::ParsedFunction const other) const;
ErrorOr<String> debug_description() const;
};struct ParsedMethod {
  public:
parser::ParsedFunction parsed_function;parser::Visibility visibility;bool is_virtual;bool is_override;ParsedMethod(parser::ParsedFunction a_parsed_function, parser::Visibility a_visibility, bool a_is_virtual, bool a_is_override);

ErrorOr<String> debug_description() const;
};struct ParsedExternalTraitImplementation {
  public:
NonnullRefPtr<parser::ParsedType> for_type;JaktInternal::Array<parser::ParsedNameWithGenericParameters> traits;JaktInternal::Array<parser::ParsedMethod> methods;ParsedExternalTraitImplementation(NonnullRefPtr<parser::ParsedType> a_for_type, JaktInternal::Array<parser::ParsedNameWithGenericParameters> a_traits, JaktInternal::Array<parser::ParsedMethod> a_methods);

ErrorOr<String> debug_description() const;
};struct ParsedNamespace {
  public:
JaktInternal::Optional<String> name;JaktInternal::Optional<utility::Span> name_span;JaktInternal::Array<parser::ParsedFunction> functions;JaktInternal::Array<parser::ParsedRecord> records;JaktInternal::Array<parser::ParsedTrait> traits;JaktInternal::Array<parser::ParsedExternalTraitImplementation> external_trait_implementations;JaktInternal::Array<parser::ParsedNamespace> namespaces;JaktInternal::Array<parser::ParsedModuleImport> module_imports;JaktInternal::Array<parser::ParsedExternImport> extern_imports;JaktInternal::Optional<String> import_path_if_extern;JaktInternal::Array<parser::IncludeAction> generating_import_extern_before_include;JaktInternal::Array<parser::IncludeAction> generating_import_extern_after_include;ErrorOr<void> add_child_namespace(parser::ParsedNamespace const namespace_);
ParsedNamespace(JaktInternal::Optional<String> a_name, JaktInternal::Optional<utility::Span> a_name_span, JaktInternal::Array<parser::ParsedFunction> a_functions, JaktInternal::Array<parser::ParsedRecord> a_records, JaktInternal::Array<parser::ParsedTrait> a_traits, JaktInternal::Array<parser::ParsedExternalTraitImplementation> a_external_trait_implementations, JaktInternal::Array<parser::ParsedNamespace> a_namespaces, JaktInternal::Array<parser::ParsedModuleImport> a_module_imports, JaktInternal::Array<parser::ParsedExternImport> a_extern_imports, JaktInternal::Optional<String> a_import_path_if_extern, JaktInternal::Array<parser::IncludeAction> a_generating_import_extern_before_include, JaktInternal::Array<parser::IncludeAction> a_generating_import_extern_after_include);

bool is_equivalent_to(parser::ParsedNamespace const other) const;
ErrorOr<void> add_extern_import(parser::ParsedExternImport const import_);
ErrorOr<void> merge_with(parser::ParsedNamespace const namespace_);
ErrorOr<void> add_module_import(parser::ParsedModuleImport const import_);
ErrorOr<String> debug_description() const;
};struct ParsedName {
  public:
String name;utility::Span span;ParsedName(String a_name, utility::Span a_span);

ErrorOr<String> debug_description() const;
};namespace ParsedMatchPattern_Details {
struct EnumVariant {
JaktInternal::Dictionary<String,parser::ParsedPatternDefault> defaults;
JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>> variant_names;
JaktInternal::Array<parser::EnumVariantPatternArgument> variant_arguments;
utility::Span arguments_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
EnumVariant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
defaults{ forward<_MemberT0>(member_0)},
variant_names{ forward<_MemberT1>(member_1)},
variant_arguments{ forward<_MemberT2>(member_2)},
arguments_span{ forward<_MemberT3>(member_3)}
{}
};
struct Expression{
JaktInternal::Dictionary<String,parser::ParsedPatternDefault> defaults;
NonnullRefPtr<parser::ParsedExpression> value;
template<typename _MemberT0, typename _MemberT1>
Expression(_MemberT0&& member_0, _MemberT1&& member_1):
defaults{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct CatchAll {
JaktInternal::Dictionary<String,parser::ParsedPatternDefault> defaults;
JaktInternal::Array<parser::EnumVariantPatternArgument> variant_arguments;
utility::Span arguments_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
CatchAll(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
defaults{ forward<_MemberT0>(member_0)},
variant_arguments{ forward<_MemberT1>(member_1)},
arguments_span{ forward<_MemberT2>(member_2)}
{}
};
struct Invalid {
JaktInternal::Dictionary<String,parser::ParsedPatternDefault> defaults;
template<typename _MemberT0>
Invalid(_MemberT0&& member_0):
defaults{ forward<_MemberT0>(member_0)}
{}
};
}
struct ParsedMatchPattern : public Variant<ParsedMatchPattern_Details::EnumVariant, ParsedMatchPattern_Details::Expression, ParsedMatchPattern_Details::CatchAll, ParsedMatchPattern_Details::Invalid> {
using Variant<ParsedMatchPattern_Details::EnumVariant, ParsedMatchPattern_Details::Expression, ParsedMatchPattern_Details::CatchAll, ParsedMatchPattern_Details::Invalid>::Variant;
    using EnumVariant = ParsedMatchPattern_Details::EnumVariant;
    using Expression = ParsedMatchPattern_Details::Expression;
    using CatchAll = ParsedMatchPattern_Details::CatchAll;
    using Invalid = ParsedMatchPattern_Details::Invalid;
ErrorOr<String> debug_description() const;
JaktInternal::Dictionary<String,parser::ParsedPatternDefault> const& defaults() const { switch(this->index()) {case 0 /* EnumVariant */: return this->template get<ParsedMatchPattern::EnumVariant>().defaults;
case 1 /* Expression */: return this->template get<ParsedMatchPattern::Expression>().defaults;
case 2 /* CatchAll */: return this->template get<ParsedMatchPattern::CatchAll>().defaults;
case 3 /* Invalid */: return this->template get<ParsedMatchPattern::Invalid>().defaults;
default: VERIFY_NOT_REACHED();
}
}
bool equals(parser::ParsedMatchPattern const rhs_parsed_match_pattern) const;
bool defaults_equal(JaktInternal::Dictionary<String,parser::ParsedPatternDefault> const defaults) const;
};
struct SumEnumVariant {
  public:
String name;utility::Span span;JaktInternal::Optional<JaktInternal::Array<parser::ParsedVarDecl>> params;SumEnumVariant(String a_name, utility::Span a_span, JaktInternal::Optional<JaktInternal::Array<parser::ParsedVarDecl>> a_params);

ErrorOr<String> debug_description() const;
};namespace ImportName_Details {
struct Literal {
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Literal(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Comptime {
NonnullRefPtr<parser::ParsedExpression> expression;
template<typename _MemberT0>
Comptime(_MemberT0&& member_0):
expression{ forward<_MemberT0>(member_0)}
{}
};
}
struct ImportName : public Variant<ImportName_Details::Literal, ImportName_Details::Comptime> {
using Variant<ImportName_Details::Literal, ImportName_Details::Comptime>::Variant;
    using Literal = ImportName_Details::Literal;
    using Comptime = ImportName_Details::Comptime;
ErrorOr<String> debug_description() const;
String literal_name() const;
bool equals(parser::ImportName const other) const;
utility::Span span() const;
};
struct ParsedVariable {
  public:
String name;NonnullRefPtr<parser::ParsedType> parsed_type;bool is_mutable;utility::Span span;bool equals(parser::ParsedVariable const rhs_parsed_varible) const;
ParsedVariable(String a_name, NonnullRefPtr<parser::ParsedType> a_parsed_type, bool a_is_mutable, utility::Span a_span);

ErrorOr<String> debug_description() const;
};struct ParsedGenericParameter {
  public:
String name;utility::Span span;JaktInternal::Optional<JaktInternal::Array<parser::ParsedNameWithGenericParameters>> requires_list;ParsedGenericParameter(String a_name, utility::Span a_span, JaktInternal::Optional<JaktInternal::Array<parser::ParsedNameWithGenericParameters>> a_requires_list);

ErrorOr<String> debug_description() const;
};struct Parser {
  public:
size_t index;JaktInternal::Array<lexer::Token> tokens;NonnullRefPtr<compiler::Compiler> compiler;ErrorOr<JaktInternal::Tuple<JaktInternal::Array<parser::ValueEnumVariant>,JaktInternal::Array<parser::ParsedMethod>>> parse_value_enum_body(parser::ParsedRecord const partial_enum, parser::DefinitionLinkage const definition_linkage);
ErrorOr<parser::ParsedMethod> parse_method(parser::FunctionLinkage const linkage, parser::Visibility const visibility, bool const is_virtual, bool const is_override, bool const is_comptime);
ErrorOr<parser::ParsedExternalTraitImplementation> parse_external_trait_implementation();
ErrorOr<NonnullRefPtr<parser::ParsedStatement>> parse_statement(bool const inside_block);
ErrorOr<String> parse_argument_label();
ErrorOr<JaktInternal::Array<parser::ParsedMatchPattern>> parse_match_patterns();
ErrorOr<parser::ParsedTrait> parse_trait();
ErrorOr<NonnullRefPtr<parser::ParsedType>> parse_type_shorthand_array_or_dictionary();
ErrorOr<parser::ParsedBlock> parse_fat_arrow();
ErrorOr<parser::Visibility> parse_restricted_visibility_modifier();
ErrorOr<NonnullRefPtr<parser::ParsedType>> parse_typename();
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_range();
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_match_expression();
ErrorOr<void> error_with_hint(String const message, utility::Span const span, String const hint, utility::Span const hint_span);
ErrorOr<parser::ParsedRecord> parse_class(parser::DefinitionLinkage const definition_linkage);
bool eof() const;
ErrorOr<parser::ParsedRecord> parse_enum(parser::DefinitionLinkage const definition_linkage, bool const is_boxed);
utility::Span span(size_t const start, size_t const end) const;
ErrorOr<JaktInternal::Array<parser::ParsedVarDecl>> parse_destructuring_assignment(bool const is_mutable);
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_operand_base();
ErrorOr<parser::ParsedFunction> parse_function(parser::FunctionLinkage const linkage, parser::Visibility const visibility, bool const is_comptime, bool const allow_missing_body);
ErrorOr<JaktInternal::Optional<JaktInternal::Array<parser::IncludeAction>>> parse_include_action();
ErrorOr<parser::ParsedModuleImport> parse_module_import();
ErrorOr<parser::ParsedBlock> parse_block();
ErrorOr<NonnullRefPtr<parser::ParsedType>> parse_type_longhand();
ErrorOr<NonnullRefPtr<parser::ParsedStatement>> parse_if_statement();
ErrorOr<void> error(String const message, utility::Span const span);
ErrorOr<JaktInternal::Tuple<JaktInternal::Array<parser::SumEnumVariant>,JaktInternal::Array<parser::ParsedField>,JaktInternal::Array<parser::ParsedMethod>>> parse_sum_enum_body(parser::ParsedRecord const partial_enum, parser::DefinitionLinkage const definition_linkage, bool const is_boxed);
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_operator(bool const allow_assignments);
ErrorOr<NonnullRefPtr<parser::ParsedStatement>> parse_for_statement();
ErrorOr<JaktInternal::Array<parser::ParsedParameter>> parse_function_parameters();
ErrorOr<JaktInternal::Optional<parser::ParsedCall>> parse_call();
ErrorOr<parser::ParsedRecord> parse_struct(parser::DefinitionLinkage const definition_linkage);
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_array_or_dictionary_literal();
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_operand();
void skip_newlines();
bool eol() const;
ErrorOr<parser::ParsedMatchPattern> parse_match_pattern();
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_lambda();
ErrorOr<JaktInternal::Optional<JaktInternal::Array<parser::ParsedNameWithGenericParameters>>> parse_trait_list();
ErrorOr<JaktInternal::Tuple<JaktInternal::Array<parser::ParsedField>,JaktInternal::Array<parser::ParsedMethod>>> parse_struct_class_body(parser::DefinitionLinkage const definition_linkage, parser::Visibility const default_visibility, bool const is_class);
ErrorOr<parser::ParsedExternImport> parse_extern_import(parser::ParsedNamespace& parent);
ErrorOr<JaktInternal::Array<parser::EnumVariantPatternArgument>> parse_variant_arguments();
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_set_literal();
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_asterisk();
ErrorOr<parser::ParsedNamespace> parse_namespace();
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_ampersand();
static ErrorOr<parser::ParsedNamespace> parse(NonnullRefPtr<compiler::Compiler> const compiler, JaktInternal::Array<lexer::Token> const tokens);
ErrorOr<NonnullRefPtr<parser::ParsedStatement>> parse_guard_statement();
lexer::Token peek(size_t const steps) const;
ErrorOr<NonnullRefPtr<parser::ParsedType>> parse_type_shorthand_tuple();
ErrorOr<JaktInternal::Optional<parser::NumericConstant>> make_integer_numeric_constant(u64 const number, lexer::LiteralSuffix const suffix, utility::Span const span);
ErrorOr<JaktInternal::Array<parser::ParsedCapture>> parse_captures();
ErrorOr<JaktInternal::Optional<parser::NumericConstant>> make_float_numeric_constant(f64 const number, lexer::LiteralSuffix const suffix, utility::Span const span);
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_postfix_colon_colon(utility::Span const start, NonnullRefPtr<parser::ParsedExpression> const expr);
Parser(size_t a_index, JaktInternal::Array<lexer::Token> a_tokens, NonnullRefPtr<compiler::Compiler> a_compiler);

ErrorOr<void> parse_import(parser::ParsedNamespace& parent);
ErrorOr<JaktInternal::Array<parser::ParsedMatchCase>> parse_match_cases();
ErrorOr<NonnullRefPtr<parser::ParsedType>> parse_type_shorthand_set();
ErrorOr<parser::ParsedField> parse_field(parser::Visibility const visibility);
lexer::Token current() const;
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_expression(bool const allow_assignments, bool const allow_newlines);
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_try_block();
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_number(lexer::LiteralPrefix const prefix, String const number, lexer::LiteralSuffix suffix, utility::Span const span);
ErrorOr<parser::ParsedRecord> parse_record(parser::DefinitionLinkage const definition_linkage);
ErrorOr<NonnullRefPtr<parser::ParsedType>> parse_type_shorthand();
utility::Span empty_span() const;
lexer::Token previous() const;
ErrorOr<parser::ParsedVarDecl> parse_variable_declaration(bool const is_mutable);
ErrorOr<NonnullRefPtr<parser::ParsedExpression>> parse_operand_postfix_operator(utility::Span const start, NonnullRefPtr<parser::ParsedExpression> const expr);
ErrorOr<JaktInternal::Array<parser::ParsedGenericParameter>> parse_generic_parameters();
ErrorOr<String> debug_description() const;
};struct ParsedExternImport {
  public:
bool is_c;parser::ParsedNamespace assigned_namespace;JaktInternal::Array<parser::IncludeAction> before_include;JaktInternal::Array<parser::IncludeAction> after_include;ErrorOr<bool> is_equivalent_to(parser::ParsedExternImport const other) const;
ParsedExternImport(bool a_is_c, parser::ParsedNamespace a_assigned_namespace, JaktInternal::Array<parser::IncludeAction> a_before_include, JaktInternal::Array<parser::IncludeAction> a_after_include);

String get_name() const;
String get_path() const;
ErrorOr<String> debug_description() const;
};namespace ImportList_Details {
struct List{
JaktInternal::Array<parser::ImportName> value;
template<typename _MemberT0>
List(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct All {
};
}
struct ImportList : public Variant<ImportList_Details::List, ImportList_Details::All> {
using Variant<ImportList_Details::List, ImportList_Details::All>::Variant;
    using List = ImportList_Details::List;
    using All = ImportList_Details::All;
ErrorOr<String> debug_description() const;
ErrorOr<void> add(parser::ImportName const name);
bool is_empty() const;
};
struct ParsedModuleImport {
  public:
parser::ImportName module_name;JaktInternal::Optional<parser::ImportName> alias_name;parser::ImportList import_list;ParsedModuleImport(parser::ImportName a_module_name, JaktInternal::Optional<parser::ImportName> a_alias_name, parser::ImportList a_import_list);

bool is_equivalent_to(parser::ParsedModuleImport const other) const;
bool has_same_alias_than(parser::ParsedModuleImport const other) const;
bool has_same_import_semantics(parser::ParsedModuleImport const other) const;
ErrorOr<void> merge_import_list(parser::ImportList const list);
ErrorOr<String> debug_description() const;
};namespace IncludeAction_Details {
struct Define {
String name;
utility::Span span;
String value;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Define(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
value{ forward<_MemberT2>(member_2)}
{}
};
struct Undefine {
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Undefine(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct IncludeAction : public Variant<IncludeAction_Details::Define, IncludeAction_Details::Undefine> {
using Variant<IncludeAction_Details::Define, IncludeAction_Details::Undefine>::Variant;
    using Define = IncludeAction_Details::Define;
    using Undefine = IncludeAction_Details::Undefine;
ErrorOr<String> debug_description() const;
};
struct ParsedNameWithGenericParameters {
  public:
String name;utility::Span name_span;JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> generic_parameters;ParsedNameWithGenericParameters(String a_name, utility::Span a_name_span, JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> a_generic_parameters);

ErrorOr<String> debug_description() const;
};namespace RecordType_Details {
struct Struct {
JaktInternal::Array<parser::ParsedField> fields;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> super_type;
template<typename _MemberT0, typename _MemberT1>
Struct(_MemberT0&& member_0, _MemberT1&& member_1):
fields{ forward<_MemberT0>(member_0)},
super_type{ forward<_MemberT1>(member_1)}
{}
};
struct Class {
JaktInternal::Array<parser::ParsedField> fields;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> super_type;
template<typename _MemberT0, typename _MemberT1>
Class(_MemberT0&& member_0, _MemberT1&& member_1):
fields{ forward<_MemberT0>(member_0)},
super_type{ forward<_MemberT1>(member_1)}
{}
};
struct ValueEnum {
NonnullRefPtr<parser::ParsedType> underlying_type;
JaktInternal::Array<parser::ValueEnumVariant> variants;
template<typename _MemberT0, typename _MemberT1>
ValueEnum(_MemberT0&& member_0, _MemberT1&& member_1):
underlying_type{ forward<_MemberT0>(member_0)},
variants{ forward<_MemberT1>(member_1)}
{}
};
struct SumEnum {
bool is_boxed;
JaktInternal::Array<parser::ParsedField> fields;
JaktInternal::Array<parser::SumEnumVariant> variants;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
SumEnum(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
is_boxed{ forward<_MemberT0>(member_0)},
fields{ forward<_MemberT1>(member_1)},
variants{ forward<_MemberT2>(member_2)}
{}
};
struct Garbage {
};
}
struct RecordType : public Variant<RecordType_Details::Struct, RecordType_Details::Class, RecordType_Details::ValueEnum, RecordType_Details::SumEnum, RecordType_Details::Garbage> {
using Variant<RecordType_Details::Struct, RecordType_Details::Class, RecordType_Details::ValueEnum, RecordType_Details::SumEnum, RecordType_Details::Garbage>::Variant;
    using Struct = RecordType_Details::Struct;
    using Class = RecordType_Details::Class;
    using ValueEnum = RecordType_Details::ValueEnum;
    using SumEnum = RecordType_Details::SumEnum;
    using Garbage = RecordType_Details::Garbage;
ErrorOr<String> debug_description() const;
String record_type_name() const;
};
namespace DefinitionLinkage_Details {
struct Internal {
};
struct External {
};
}
struct DefinitionLinkage : public Variant<DefinitionLinkage_Details::Internal, DefinitionLinkage_Details::External> {
using Variant<DefinitionLinkage_Details::Internal, DefinitionLinkage_Details::External>::Variant;
    using Internal = DefinitionLinkage_Details::Internal;
    using External = DefinitionLinkage_Details::External;
ErrorOr<String> debug_description() const;
};
struct ParsedRecord {
  public:
String name;utility::Span name_span;JaktInternal::Array<parser::ParsedGenericParameter> generic_parameters;parser::DefinitionLinkage definition_linkage;JaktInternal::Optional<JaktInternal::Array<parser::ParsedNameWithGenericParameters>> implements_list;JaktInternal::Array<parser::ParsedMethod> methods;parser::RecordType record_type;ParsedRecord(String a_name, utility::Span a_name_span, JaktInternal::Array<parser::ParsedGenericParameter> a_generic_parameters, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Optional<JaktInternal::Array<parser::ParsedNameWithGenericParameters>> a_implements_list, JaktInternal::Array<parser::ParsedMethod> a_methods, parser::RecordType a_record_type);

ErrorOr<String> debug_description() const;
};struct ParsedField {
  public:
parser::ParsedVarDecl var_decl;parser::Visibility visibility;JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> default_value;ParsedField(parser::ParsedVarDecl a_var_decl, parser::Visibility a_visibility, JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> a_default_value);

ErrorOr<String> debug_description() const;
};struct VisibilityRestriction {
  public:
JaktInternal::Array<String> namespace_;String name;VisibilityRestriction(JaktInternal::Array<String> a_namespace_, String a_name);

ErrorOr<String> debug_description() const;
};struct ParsedTrait {
  public:
String name;utility::Span name_span;JaktInternal::Array<parser::ParsedGenericParameter> generic_parameters;JaktInternal::Array<parser::ParsedFunction> methods;ParsedTrait(String a_name, utility::Span a_name_span, JaktInternal::Array<parser::ParsedGenericParameter> a_generic_parameters, JaktInternal::Array<parser::ParsedFunction> a_methods);

ErrorOr<String> debug_description() const;
};struct ParsedParameter {
  public:
bool requires_label;parser::ParsedVariable variable;JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> default_argument;utility::Span span;bool equals(parser::ParsedParameter const rhs_param) const;
ParsedParameter(bool a_requires_label, parser::ParsedVariable a_variable, JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> a_default_argument, utility::Span a_span);

ErrorOr<String> debug_description() const;
};struct ValueEnumVariant {
  public:
String name;utility::Span span;JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> value;ValueEnumVariant(String a_name, utility::Span a_span, JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> a_value);

ErrorOr<String> debug_description() const;
};template <typename T>
T u64_to_float(u64 const number) {
{
T float_value = static_cast<i64>(0LL);
{
float_value = number;
}

return (float_value);
}
}

}
template<>struct Formatter<parser::ParsedCapture> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedCapture const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedBlock> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedBlock const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedMatchBody> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedMatchBody const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedMatchCase> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedMatchCase const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::FunctionType> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::FunctionType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedVarDecl> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedVarDecl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::NumericConstant> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::NumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedCall> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedCall const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::TypeCast> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::TypeCast const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedType> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::UnaryOperator> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::UnaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::BinaryOperator> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::BinaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::EnumVariantPatternArgument> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::EnumVariantPatternArgument const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedExpression> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedExpression const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedPatternDefault> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedPatternDefault const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedStatement> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedStatement const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::FunctionLinkage> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::FunctionLinkage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::Visibility> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::Visibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedFunction> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedFunction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedMethod> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedMethod const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedExternalTraitImplementation> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedExternalTraitImplementation const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedNamespace> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedName> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedMatchPattern> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedMatchPattern const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::SumEnumVariant> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::SumEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ImportName> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ImportName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedVariable> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedVariable const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedGenericParameter> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::Parser> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::Parser const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedExternImport> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedExternImport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ImportList> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ImportList const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedModuleImport> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedModuleImport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::IncludeAction> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::IncludeAction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedNameWithGenericParameters> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedNameWithGenericParameters const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::RecordType> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::RecordType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::DefinitionLinkage> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::DefinitionLinkage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedRecord> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedRecord const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedField> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedField const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::VisibilityRestriction> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::VisibilityRestriction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedTrait> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedTrait const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ParsedParameter> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ParsedParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<parser::ValueEnumVariant> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, parser::ValueEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
