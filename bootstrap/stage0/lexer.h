#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace lexer {
namespace NumericConstant_Details {
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
struct UnknownSigned{
i64 value;
template<typename... Args>
UnknownSigned(Args&&... args): value { forward<Args>(args)... } {}
};
struct UnknownUnsigned{
u64 value;
template<typename... Args>
UnknownUnsigned(Args&&... args): value { forward<Args>(args)... } {}
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
namespace Token_Details {
struct SingleQuotedString {
String quote;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
SingleQuotedString(_MemberT0&& member_0, _MemberT1&& member_1):
quote{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct SingleQuotedByteString {
String quote;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
SingleQuotedByteString(_MemberT0&& member_0, _MemberT1&& member_1):
quote{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct QuotedString {
String quote;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
QuotedString(_MemberT0&& member_0, _MemberT1&& member_1):
quote{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Number {
lexer::NumericConstant number;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Number(_MemberT0&& member_0, _MemberT1&& member_1):
number{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Identifier {
String name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Identifier(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Semicolon{
utility::Span value;
template<typename... Args>
Semicolon(Args&&... args): value { forward<Args>(args)... } {}
};
struct Colon{
utility::Span value;
template<typename... Args>
Colon(Args&&... args): value { forward<Args>(args)... } {}
};
struct ColonColon{
utility::Span value;
template<typename... Args>
ColonColon(Args&&... args): value { forward<Args>(args)... } {}
};
struct LParen{
utility::Span value;
template<typename... Args>
LParen(Args&&... args): value { forward<Args>(args)... } {}
};
struct RParen{
utility::Span value;
template<typename... Args>
RParen(Args&&... args): value { forward<Args>(args)... } {}
};
struct LCurly{
utility::Span value;
template<typename... Args>
LCurly(Args&&... args): value { forward<Args>(args)... } {}
};
struct RCurly{
utility::Span value;
template<typename... Args>
RCurly(Args&&... args): value { forward<Args>(args)... } {}
};
struct LSquare{
utility::Span value;
template<typename... Args>
LSquare(Args&&... args): value { forward<Args>(args)... } {}
};
struct RSquare{
utility::Span value;
template<typename... Args>
RSquare(Args&&... args): value { forward<Args>(args)... } {}
};
struct PercentSign{
utility::Span value;
template<typename... Args>
PercentSign(Args&&... args): value { forward<Args>(args)... } {}
};
struct Plus{
utility::Span value;
template<typename... Args>
Plus(Args&&... args): value { forward<Args>(args)... } {}
};
struct Minus{
utility::Span value;
template<typename... Args>
Minus(Args&&... args): value { forward<Args>(args)... } {}
};
struct Equal{
utility::Span value;
template<typename... Args>
Equal(Args&&... args): value { forward<Args>(args)... } {}
};
struct PlusEqual{
utility::Span value;
template<typename... Args>
PlusEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct PlusPlus{
utility::Span value;
template<typename... Args>
PlusPlus(Args&&... args): value { forward<Args>(args)... } {}
};
struct MinusEqual{
utility::Span value;
template<typename... Args>
MinusEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct MinusMinus{
utility::Span value;
template<typename... Args>
MinusMinus(Args&&... args): value { forward<Args>(args)... } {}
};
struct AsteriskEqual{
utility::Span value;
template<typename... Args>
AsteriskEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct ForwardSlashEqual{
utility::Span value;
template<typename... Args>
ForwardSlashEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct PercentSignEqual{
utility::Span value;
template<typename... Args>
PercentSignEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct NotEqual{
utility::Span value;
template<typename... Args>
NotEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct DoubleEqual{
utility::Span value;
template<typename... Args>
DoubleEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct GreaterThan{
utility::Span value;
template<typename... Args>
GreaterThan(Args&&... args): value { forward<Args>(args)... } {}
};
struct GreaterThanOrEqual{
utility::Span value;
template<typename... Args>
GreaterThanOrEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct LessThan{
utility::Span value;
template<typename... Args>
LessThan(Args&&... args): value { forward<Args>(args)... } {}
};
struct LessThanOrEqual{
utility::Span value;
template<typename... Args>
LessThanOrEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct LeftArithmeticShift{
utility::Span value;
template<typename... Args>
LeftArithmeticShift(Args&&... args): value { forward<Args>(args)... } {}
};
struct LeftShift{
utility::Span value;
template<typename... Args>
LeftShift(Args&&... args): value { forward<Args>(args)... } {}
};
struct LeftShiftEqual{
utility::Span value;
template<typename... Args>
LeftShiftEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct RightShift{
utility::Span value;
template<typename... Args>
RightShift(Args&&... args): value { forward<Args>(args)... } {}
};
struct RightArithmeticShift{
utility::Span value;
template<typename... Args>
RightArithmeticShift(Args&&... args): value { forward<Args>(args)... } {}
};
struct RightShiftEqual{
utility::Span value;
template<typename... Args>
RightShiftEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct Asterisk{
utility::Span value;
template<typename... Args>
Asterisk(Args&&... args): value { forward<Args>(args)... } {}
};
struct Ampersand{
utility::Span value;
template<typename... Args>
Ampersand(Args&&... args): value { forward<Args>(args)... } {}
};
struct AmpersandEqual{
utility::Span value;
template<typename... Args>
AmpersandEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct Pipe{
utility::Span value;
template<typename... Args>
Pipe(Args&&... args): value { forward<Args>(args)... } {}
};
struct PipeEqual{
utility::Span value;
template<typename... Args>
PipeEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct Caret{
utility::Span value;
template<typename... Args>
Caret(Args&&... args): value { forward<Args>(args)... } {}
};
struct CaretEqual{
utility::Span value;
template<typename... Args>
CaretEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct Dollar{
utility::Span value;
template<typename... Args>
Dollar(Args&&... args): value { forward<Args>(args)... } {}
};
struct Tilde{
utility::Span value;
template<typename... Args>
Tilde(Args&&... args): value { forward<Args>(args)... } {}
};
struct ForwardSlash{
utility::Span value;
template<typename... Args>
ForwardSlash(Args&&... args): value { forward<Args>(args)... } {}
};
struct ExclamationPoint{
utility::Span value;
template<typename... Args>
ExclamationPoint(Args&&... args): value { forward<Args>(args)... } {}
};
struct QuestionMark{
utility::Span value;
template<typename... Args>
QuestionMark(Args&&... args): value { forward<Args>(args)... } {}
};
struct QuestionMarkQuestionMark{
utility::Span value;
template<typename... Args>
QuestionMarkQuestionMark(Args&&... args): value { forward<Args>(args)... } {}
};
struct QuestionMarkQuestionMarkEqual{
utility::Span value;
template<typename... Args>
QuestionMarkQuestionMarkEqual(Args&&... args): value { forward<Args>(args)... } {}
};
struct Comma{
utility::Span value;
template<typename... Args>
Comma(Args&&... args): value { forward<Args>(args)... } {}
};
struct Dot{
utility::Span value;
template<typename... Args>
Dot(Args&&... args): value { forward<Args>(args)... } {}
};
struct DotDot{
utility::Span value;
template<typename... Args>
DotDot(Args&&... args): value { forward<Args>(args)... } {}
};
struct Eol {
JaktInternal::Optional<String> comment;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Eol(_MemberT0&& member_0, _MemberT1&& member_1):
comment{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Eof{
utility::Span value;
template<typename... Args>
Eof(Args&&... args): value { forward<Args>(args)... } {}
};
struct FatArrow{
utility::Span value;
template<typename... Args>
FatArrow(Args&&... args): value { forward<Args>(args)... } {}
};
struct Arrow{
utility::Span value;
template<typename... Args>
Arrow(Args&&... args): value { forward<Args>(args)... } {}
};
struct And{
utility::Span value;
template<typename... Args>
And(Args&&... args): value { forward<Args>(args)... } {}
};
struct Anon{
utility::Span value;
template<typename... Args>
Anon(Args&&... args): value { forward<Args>(args)... } {}
};
struct As{
utility::Span value;
template<typename... Args>
As(Args&&... args): value { forward<Args>(args)... } {}
};
struct Boxed{
utility::Span value;
template<typename... Args>
Boxed(Args&&... args): value { forward<Args>(args)... } {}
};
struct Break{
utility::Span value;
template<typename... Args>
Break(Args&&... args): value { forward<Args>(args)... } {}
};
struct Catch{
utility::Span value;
template<typename... Args>
Catch(Args&&... args): value { forward<Args>(args)... } {}
};
struct Class{
utility::Span value;
template<typename... Args>
Class(Args&&... args): value { forward<Args>(args)... } {}
};
struct Continue{
utility::Span value;
template<typename... Args>
Continue(Args&&... args): value { forward<Args>(args)... } {}
};
struct Cpp{
utility::Span value;
template<typename... Args>
Cpp(Args&&... args): value { forward<Args>(args)... } {}
};
struct Defer{
utility::Span value;
template<typename... Args>
Defer(Args&&... args): value { forward<Args>(args)... } {}
};
struct Else{
utility::Span value;
template<typename... Args>
Else(Args&&... args): value { forward<Args>(args)... } {}
};
struct Enum{
utility::Span value;
template<typename... Args>
Enum(Args&&... args): value { forward<Args>(args)... } {}
};
struct Extern{
utility::Span value;
template<typename... Args>
Extern(Args&&... args): value { forward<Args>(args)... } {}
};
struct False{
utility::Span value;
template<typename... Args>
False(Args&&... args): value { forward<Args>(args)... } {}
};
struct For{
utility::Span value;
template<typename... Args>
For(Args&&... args): value { forward<Args>(args)... } {}
};
struct Function{
utility::Span value;
template<typename... Args>
Function(Args&&... args): value { forward<Args>(args)... } {}
};
struct Comptime{
utility::Span value;
template<typename... Args>
Comptime(Args&&... args): value { forward<Args>(args)... } {}
};
struct If{
utility::Span value;
template<typename... Args>
If(Args&&... args): value { forward<Args>(args)... } {}
};
struct Import{
utility::Span value;
template<typename... Args>
Import(Args&&... args): value { forward<Args>(args)... } {}
};
struct In{
utility::Span value;
template<typename... Args>
In(Args&&... args): value { forward<Args>(args)... } {}
};
struct Is{
utility::Span value;
template<typename... Args>
Is(Args&&... args): value { forward<Args>(args)... } {}
};
struct Let{
utility::Span value;
template<typename... Args>
Let(Args&&... args): value { forward<Args>(args)... } {}
};
struct Loop{
utility::Span value;
template<typename... Args>
Loop(Args&&... args): value { forward<Args>(args)... } {}
};
struct Match{
utility::Span value;
template<typename... Args>
Match(Args&&... args): value { forward<Args>(args)... } {}
};
struct Mut{
utility::Span value;
template<typename... Args>
Mut(Args&&... args): value { forward<Args>(args)... } {}
};
struct Namespace{
utility::Span value;
template<typename... Args>
Namespace(Args&&... args): value { forward<Args>(args)... } {}
};
struct Not{
utility::Span value;
template<typename... Args>
Not(Args&&... args): value { forward<Args>(args)... } {}
};
struct Or{
utility::Span value;
template<typename... Args>
Or(Args&&... args): value { forward<Args>(args)... } {}
};
struct Override{
utility::Span value;
template<typename... Args>
Override(Args&&... args): value { forward<Args>(args)... } {}
};
struct Private{
utility::Span value;
template<typename... Args>
Private(Args&&... args): value { forward<Args>(args)... } {}
};
struct Public{
utility::Span value;
template<typename... Args>
Public(Args&&... args): value { forward<Args>(args)... } {}
};
struct Raw{
utility::Span value;
template<typename... Args>
Raw(Args&&... args): value { forward<Args>(args)... } {}
};
struct Return{
utility::Span value;
template<typename... Args>
Return(Args&&... args): value { forward<Args>(args)... } {}
};
struct Restricted{
utility::Span value;
template<typename... Args>
Restricted(Args&&... args): value { forward<Args>(args)... } {}
};
struct Struct{
utility::Span value;
template<typename... Args>
Struct(Args&&... args): value { forward<Args>(args)... } {}
};
struct This{
utility::Span value;
template<typename... Args>
This(Args&&... args): value { forward<Args>(args)... } {}
};
struct Throw{
utility::Span value;
template<typename... Args>
Throw(Args&&... args): value { forward<Args>(args)... } {}
};
struct Throws{
utility::Span value;
template<typename... Args>
Throws(Args&&... args): value { forward<Args>(args)... } {}
};
struct True{
utility::Span value;
template<typename... Args>
True(Args&&... args): value { forward<Args>(args)... } {}
};
struct Try{
utility::Span value;
template<typename... Args>
Try(Args&&... args): value { forward<Args>(args)... } {}
};
struct Unsafe{
utility::Span value;
template<typename... Args>
Unsafe(Args&&... args): value { forward<Args>(args)... } {}
};
struct Virtual{
utility::Span value;
template<typename... Args>
Virtual(Args&&... args): value { forward<Args>(args)... } {}
};
struct Weak{
utility::Span value;
template<typename... Args>
Weak(Args&&... args): value { forward<Args>(args)... } {}
};
struct While{
utility::Span value;
template<typename... Args>
While(Args&&... args): value { forward<Args>(args)... } {}
};
struct Yield{
utility::Span value;
template<typename... Args>
Yield(Args&&... args): value { forward<Args>(args)... } {}
};
struct Guard{
utility::Span value;
template<typename... Args>
Guard(Args&&... args): value { forward<Args>(args)... } {}
};
struct Garbage{
utility::Span value;
template<typename... Args>
Garbage(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct Token : public Variant<Token_Details::SingleQuotedString, Token_Details::SingleQuotedByteString, Token_Details::QuotedString, Token_Details::Number, Token_Details::Identifier, Token_Details::Semicolon, Token_Details::Colon, Token_Details::ColonColon, Token_Details::LParen, Token_Details::RParen, Token_Details::LCurly, Token_Details::RCurly, Token_Details::LSquare, Token_Details::RSquare, Token_Details::PercentSign, Token_Details::Plus, Token_Details::Minus, Token_Details::Equal, Token_Details::PlusEqual, Token_Details::PlusPlus, Token_Details::MinusEqual, Token_Details::MinusMinus, Token_Details::AsteriskEqual, Token_Details::ForwardSlashEqual, Token_Details::PercentSignEqual, Token_Details::NotEqual, Token_Details::DoubleEqual, Token_Details::GreaterThan, Token_Details::GreaterThanOrEqual, Token_Details::LessThan, Token_Details::LessThanOrEqual, Token_Details::LeftArithmeticShift, Token_Details::LeftShift, Token_Details::LeftShiftEqual, Token_Details::RightShift, Token_Details::RightArithmeticShift, Token_Details::RightShiftEqual, Token_Details::Asterisk, Token_Details::Ampersand, Token_Details::AmpersandEqual, Token_Details::Pipe, Token_Details::PipeEqual, Token_Details::Caret, Token_Details::CaretEqual, Token_Details::Dollar, Token_Details::Tilde, Token_Details::ForwardSlash, Token_Details::ExclamationPoint, Token_Details::QuestionMark, Token_Details::QuestionMarkQuestionMark, Token_Details::QuestionMarkQuestionMarkEqual, Token_Details::Comma, Token_Details::Dot, Token_Details::DotDot, Token_Details::Eol, Token_Details::Eof, Token_Details::FatArrow, Token_Details::Arrow, Token_Details::And, Token_Details::Anon, Token_Details::As, Token_Details::Boxed, Token_Details::Break, Token_Details::Catch, Token_Details::Class, Token_Details::Continue, Token_Details::Cpp, Token_Details::Defer, Token_Details::Else, Token_Details::Enum, Token_Details::Extern, Token_Details::False, Token_Details::For, Token_Details::Function, Token_Details::Comptime, Token_Details::If, Token_Details::Import, Token_Details::In, Token_Details::Is, Token_Details::Let, Token_Details::Loop, Token_Details::Match, Token_Details::Mut, Token_Details::Namespace, Token_Details::Not, Token_Details::Or, Token_Details::Override, Token_Details::Private, Token_Details::Public, Token_Details::Raw, Token_Details::Return, Token_Details::Restricted, Token_Details::Struct, Token_Details::This, Token_Details::Throw, Token_Details::Throws, Token_Details::True, Token_Details::Try, Token_Details::Unsafe, Token_Details::Virtual, Token_Details::Weak, Token_Details::While, Token_Details::Yield, Token_Details::Guard, Token_Details::Garbage> {
using Variant<Token_Details::SingleQuotedString, Token_Details::SingleQuotedByteString, Token_Details::QuotedString, Token_Details::Number, Token_Details::Identifier, Token_Details::Semicolon, Token_Details::Colon, Token_Details::ColonColon, Token_Details::LParen, Token_Details::RParen, Token_Details::LCurly, Token_Details::RCurly, Token_Details::LSquare, Token_Details::RSquare, Token_Details::PercentSign, Token_Details::Plus, Token_Details::Minus, Token_Details::Equal, Token_Details::PlusEqual, Token_Details::PlusPlus, Token_Details::MinusEqual, Token_Details::MinusMinus, Token_Details::AsteriskEqual, Token_Details::ForwardSlashEqual, Token_Details::PercentSignEqual, Token_Details::NotEqual, Token_Details::DoubleEqual, Token_Details::GreaterThan, Token_Details::GreaterThanOrEqual, Token_Details::LessThan, Token_Details::LessThanOrEqual, Token_Details::LeftArithmeticShift, Token_Details::LeftShift, Token_Details::LeftShiftEqual, Token_Details::RightShift, Token_Details::RightArithmeticShift, Token_Details::RightShiftEqual, Token_Details::Asterisk, Token_Details::Ampersand, Token_Details::AmpersandEqual, Token_Details::Pipe, Token_Details::PipeEqual, Token_Details::Caret, Token_Details::CaretEqual, Token_Details::Dollar, Token_Details::Tilde, Token_Details::ForwardSlash, Token_Details::ExclamationPoint, Token_Details::QuestionMark, Token_Details::QuestionMarkQuestionMark, Token_Details::QuestionMarkQuestionMarkEqual, Token_Details::Comma, Token_Details::Dot, Token_Details::DotDot, Token_Details::Eol, Token_Details::Eof, Token_Details::FatArrow, Token_Details::Arrow, Token_Details::And, Token_Details::Anon, Token_Details::As, Token_Details::Boxed, Token_Details::Break, Token_Details::Catch, Token_Details::Class, Token_Details::Continue, Token_Details::Cpp, Token_Details::Defer, Token_Details::Else, Token_Details::Enum, Token_Details::Extern, Token_Details::False, Token_Details::For, Token_Details::Function, Token_Details::Comptime, Token_Details::If, Token_Details::Import, Token_Details::In, Token_Details::Is, Token_Details::Let, Token_Details::Loop, Token_Details::Match, Token_Details::Mut, Token_Details::Namespace, Token_Details::Not, Token_Details::Or, Token_Details::Override, Token_Details::Private, Token_Details::Public, Token_Details::Raw, Token_Details::Return, Token_Details::Restricted, Token_Details::Struct, Token_Details::This, Token_Details::Throw, Token_Details::Throws, Token_Details::True, Token_Details::Try, Token_Details::Unsafe, Token_Details::Virtual, Token_Details::Weak, Token_Details::While, Token_Details::Yield, Token_Details::Guard, Token_Details::Garbage>::Variant;
    using SingleQuotedString = Token_Details::SingleQuotedString;
    using SingleQuotedByteString = Token_Details::SingleQuotedByteString;
    using QuotedString = Token_Details::QuotedString;
    using Number = Token_Details::Number;
    using Identifier = Token_Details::Identifier;
    using Semicolon = Token_Details::Semicolon;
    using Colon = Token_Details::Colon;
    using ColonColon = Token_Details::ColonColon;
    using LParen = Token_Details::LParen;
    using RParen = Token_Details::RParen;
    using LCurly = Token_Details::LCurly;
    using RCurly = Token_Details::RCurly;
    using LSquare = Token_Details::LSquare;
    using RSquare = Token_Details::RSquare;
    using PercentSign = Token_Details::PercentSign;
    using Plus = Token_Details::Plus;
    using Minus = Token_Details::Minus;
    using Equal = Token_Details::Equal;
    using PlusEqual = Token_Details::PlusEqual;
    using PlusPlus = Token_Details::PlusPlus;
    using MinusEqual = Token_Details::MinusEqual;
    using MinusMinus = Token_Details::MinusMinus;
    using AsteriskEqual = Token_Details::AsteriskEqual;
    using ForwardSlashEqual = Token_Details::ForwardSlashEqual;
    using PercentSignEqual = Token_Details::PercentSignEqual;
    using NotEqual = Token_Details::NotEqual;
    using DoubleEqual = Token_Details::DoubleEqual;
    using GreaterThan = Token_Details::GreaterThan;
    using GreaterThanOrEqual = Token_Details::GreaterThanOrEqual;
    using LessThan = Token_Details::LessThan;
    using LessThanOrEqual = Token_Details::LessThanOrEqual;
    using LeftArithmeticShift = Token_Details::LeftArithmeticShift;
    using LeftShift = Token_Details::LeftShift;
    using LeftShiftEqual = Token_Details::LeftShiftEqual;
    using RightShift = Token_Details::RightShift;
    using RightArithmeticShift = Token_Details::RightArithmeticShift;
    using RightShiftEqual = Token_Details::RightShiftEqual;
    using Asterisk = Token_Details::Asterisk;
    using Ampersand = Token_Details::Ampersand;
    using AmpersandEqual = Token_Details::AmpersandEqual;
    using Pipe = Token_Details::Pipe;
    using PipeEqual = Token_Details::PipeEqual;
    using Caret = Token_Details::Caret;
    using CaretEqual = Token_Details::CaretEqual;
    using Dollar = Token_Details::Dollar;
    using Tilde = Token_Details::Tilde;
    using ForwardSlash = Token_Details::ForwardSlash;
    using ExclamationPoint = Token_Details::ExclamationPoint;
    using QuestionMark = Token_Details::QuestionMark;
    using QuestionMarkQuestionMark = Token_Details::QuestionMarkQuestionMark;
    using QuestionMarkQuestionMarkEqual = Token_Details::QuestionMarkQuestionMarkEqual;
    using Comma = Token_Details::Comma;
    using Dot = Token_Details::Dot;
    using DotDot = Token_Details::DotDot;
    using Eol = Token_Details::Eol;
    using Eof = Token_Details::Eof;
    using FatArrow = Token_Details::FatArrow;
    using Arrow = Token_Details::Arrow;
    using And = Token_Details::And;
    using Anon = Token_Details::Anon;
    using As = Token_Details::As;
    using Boxed = Token_Details::Boxed;
    using Break = Token_Details::Break;
    using Catch = Token_Details::Catch;
    using Class = Token_Details::Class;
    using Continue = Token_Details::Continue;
    using Cpp = Token_Details::Cpp;
    using Defer = Token_Details::Defer;
    using Else = Token_Details::Else;
    using Enum = Token_Details::Enum;
    using Extern = Token_Details::Extern;
    using False = Token_Details::False;
    using For = Token_Details::For;
    using Function = Token_Details::Function;
    using Comptime = Token_Details::Comptime;
    using If = Token_Details::If;
    using Import = Token_Details::Import;
    using In = Token_Details::In;
    using Is = Token_Details::Is;
    using Let = Token_Details::Let;
    using Loop = Token_Details::Loop;
    using Match = Token_Details::Match;
    using Mut = Token_Details::Mut;
    using Namespace = Token_Details::Namespace;
    using Not = Token_Details::Not;
    using Or = Token_Details::Or;
    using Override = Token_Details::Override;
    using Private = Token_Details::Private;
    using Public = Token_Details::Public;
    using Raw = Token_Details::Raw;
    using Return = Token_Details::Return;
    using Restricted = Token_Details::Restricted;
    using Struct = Token_Details::Struct;
    using This = Token_Details::This;
    using Throw = Token_Details::Throw;
    using Throws = Token_Details::Throws;
    using True = Token_Details::True;
    using Try = Token_Details::Try;
    using Unsafe = Token_Details::Unsafe;
    using Virtual = Token_Details::Virtual;
    using Weak = Token_Details::Weak;
    using While = Token_Details::While;
    using Yield = Token_Details::Yield;
    using Guard = Token_Details::Guard;
    using Garbage = Token_Details::Garbage;
ErrorOr<String> debug_description() const;
static lexer::Token from_keyword_or_identifier(const String string, const utility::Span span);
utility::Span span() const;
};
struct Lexer {
  public:
size_t index;JaktInternal::Array<u8> input;NonnullRefPtr<compiler::Compiler> compiler;JaktInternal::Optional<JaktInternal::Array<u8>> comment_contents;ErrorOr<lexer::Token> lex_quoted_string(const u8 delimiter);
ErrorOr<JaktInternal::Optional<lexer::Token>> next();
ErrorOr<JaktInternal::Optional<String>> consume_comment_contents();
bool is_whitespace(const u8 ch) const;
ErrorOr<lexer::Token> lex_character_constant_or_name();
lexer::Token lex_dot();
ErrorOr<lexer::Token> make_integer_token(const u64 number, const lexer::LiteralSuffix suffix, const utility::Span span);
ErrorOr<lexer::Token> lex_forward_slash();
lexer::Token lex_question_mark();
u8 peek_behind(const size_t steps) const;
u8 peek_ahead(const size_t steps) const;
lexer::Token lex_asterisk();
u8 peek() const;
lexer::Token lex_percent_sign();
ErrorOr<lexer::Token> lex_number_or_name();
lexer::Token lex_minus();
bool eof() const;
lexer::Token lex_ampersand();
utility::Span span(const size_t start, const size_t end) const;
lexer::Token lex_plus();
lexer::Token lex_exclamation_point();
JaktInternal::Optional<lexer::LiteralSuffix> consume_numeric_literal_suffix();
lexer::Token lex_colon();
Lexer(size_t a_index, JaktInternal::Array<u8> a_input, NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Optional<JaktInternal::Array<u8>> a_comment_contents);

ErrorOr<void> error(const String message, const utility::Span span);
ErrorOr<String> substring(const size_t start, const size_t length) const;
lexer::Token lex_greater_than();
lexer::Token lex_pipe();
lexer::Token lex_caret();
ErrorOr<lexer::Token> lex_number();
lexer::Token lex_less_than();
lexer::Token lex_equals();
static ErrorOr<JaktInternal::Array<lexer::Token>> lex(const NonnullRefPtr<compiler::Compiler> compiler);
ErrorOr<String> debug_description() const;
};namespace LiteralSuffix_Details {
struct None {};
struct UZ {};
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
}
struct LiteralSuffix : public Variant<LiteralSuffix_Details::None, LiteralSuffix_Details::UZ, LiteralSuffix_Details::U8, LiteralSuffix_Details::U16, LiteralSuffix_Details::U32, LiteralSuffix_Details::U64, LiteralSuffix_Details::I8, LiteralSuffix_Details::I16, LiteralSuffix_Details::I32, LiteralSuffix_Details::I64, LiteralSuffix_Details::F32, LiteralSuffix_Details::F64> {
using Variant<LiteralSuffix_Details::None, LiteralSuffix_Details::UZ, LiteralSuffix_Details::U8, LiteralSuffix_Details::U16, LiteralSuffix_Details::U32, LiteralSuffix_Details::U64, LiteralSuffix_Details::I8, LiteralSuffix_Details::I16, LiteralSuffix_Details::I32, LiteralSuffix_Details::I64, LiteralSuffix_Details::F32, LiteralSuffix_Details::F64>::Variant;
    using None = LiteralSuffix_Details::None;
    using UZ = LiteralSuffix_Details::UZ;
    using U8 = LiteralSuffix_Details::U8;
    using U16 = LiteralSuffix_Details::U16;
    using U32 = LiteralSuffix_Details::U32;
    using U64 = LiteralSuffix_Details::U64;
    using I8 = LiteralSuffix_Details::I8;
    using I16 = LiteralSuffix_Details::I16;
    using I32 = LiteralSuffix_Details::I32;
    using I64 = LiteralSuffix_Details::I64;
    using F32 = LiteralSuffix_Details::F32;
    using F64 = LiteralSuffix_Details::F64;
ErrorOr<String> debug_description() const;
};
template <typename T>
T u64_to_float(const u64 number) {
{
T float_value = static_cast<i64>(0LL);
{
float_value = number;
}

return (float_value);
}
}

}
template<>struct Formatter<lexer::NumericConstant> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, lexer::NumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<lexer::Token> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, lexer::Token const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<lexer::Lexer> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, lexer::Lexer const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<lexer::LiteralSuffix> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, lexer::LiteralSuffix const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
