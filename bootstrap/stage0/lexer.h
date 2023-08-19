#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace lexer {
namespace LiteralPrefix_Details {
struct None {
};
struct Hexadecimal {
};
struct Octal {
};
struct Binary {
};
}
struct LiteralPrefix : public Variant<LiteralPrefix_Details::None, LiteralPrefix_Details::Hexadecimal, LiteralPrefix_Details::Octal, LiteralPrefix_Details::Binary> {
using Variant<LiteralPrefix_Details::None, LiteralPrefix_Details::Hexadecimal, LiteralPrefix_Details::Octal, LiteralPrefix_Details::Binary>::Variant;
    using None = LiteralPrefix_Details::None;
    using Hexadecimal = LiteralPrefix_Details::Hexadecimal;
    using Octal = LiteralPrefix_Details::Octal;
    using Binary = LiteralPrefix_Details::Binary;
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<DeprecatedString> to_string() const;
};
namespace LiteralSuffix_Details {
struct None {
};
struct UZ {
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
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<DeprecatedString> to_string() const;
};
namespace Token_Details {
struct SingleQuotedString {
DeprecatedString quote;
JaktInternal::Optional<DeprecatedString> prefix;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
SingleQuotedString(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
quote{ forward<_MemberT0>(member_0)},
prefix{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct QuotedString {
DeprecatedString quote;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
QuotedString(_MemberT0&& member_0, _MemberT1&& member_1):
quote{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Number {
lexer::LiteralPrefix prefix;
DeprecatedString number;
lexer::LiteralSuffix suffix;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Number(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
prefix{ forward<_MemberT0>(member_0)},
number{ forward<_MemberT1>(member_1)},
suffix{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Identifier {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Identifier(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Semicolon{
utility::Span value;
template<typename _MemberT0>
Semicolon(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Colon{
utility::Span value;
template<typename _MemberT0>
Colon(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct ColonColon{
utility::Span value;
template<typename _MemberT0>
ColonColon(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct LParen{
utility::Span value;
template<typename _MemberT0>
LParen(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct RParen{
utility::Span value;
template<typename _MemberT0>
RParen(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct LCurly{
utility::Span value;
template<typename _MemberT0>
LCurly(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct RCurly{
utility::Span value;
template<typename _MemberT0>
RCurly(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct LSquare{
utility::Span value;
template<typename _MemberT0>
LSquare(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct RSquare{
utility::Span value;
template<typename _MemberT0>
RSquare(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct PercentSign{
utility::Span value;
template<typename _MemberT0>
PercentSign(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Plus{
utility::Span value;
template<typename _MemberT0>
Plus(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Minus{
utility::Span value;
template<typename _MemberT0>
Minus(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Equal{
utility::Span value;
template<typename _MemberT0>
Equal(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct PlusEqual{
utility::Span value;
template<typename _MemberT0>
PlusEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct PlusPlus{
utility::Span value;
template<typename _MemberT0>
PlusPlus(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct MinusEqual{
utility::Span value;
template<typename _MemberT0>
MinusEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct MinusMinus{
utility::Span value;
template<typename _MemberT0>
MinusMinus(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct AsteriskEqual{
utility::Span value;
template<typename _MemberT0>
AsteriskEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct ForwardSlashEqual{
utility::Span value;
template<typename _MemberT0>
ForwardSlashEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct PercentSignEqual{
utility::Span value;
template<typename _MemberT0>
PercentSignEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct NotEqual{
utility::Span value;
template<typename _MemberT0>
NotEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct DoubleEqual{
utility::Span value;
template<typename _MemberT0>
DoubleEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct GreaterThan{
utility::Span value;
template<typename _MemberT0>
GreaterThan(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct GreaterThanOrEqual{
utility::Span value;
template<typename _MemberT0>
GreaterThanOrEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct LessThan{
utility::Span value;
template<typename _MemberT0>
LessThan(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct LessThanOrEqual{
utility::Span value;
template<typename _MemberT0>
LessThanOrEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct LeftArithmeticShift{
utility::Span value;
template<typename _MemberT0>
LeftArithmeticShift(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct LeftShift{
utility::Span value;
template<typename _MemberT0>
LeftShift(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct LeftShiftEqual{
utility::Span value;
template<typename _MemberT0>
LeftShiftEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct RightShift{
utility::Span value;
template<typename _MemberT0>
RightShift(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct RightArithmeticShift{
utility::Span value;
template<typename _MemberT0>
RightArithmeticShift(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct RightShiftEqual{
utility::Span value;
template<typename _MemberT0>
RightShiftEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Asterisk{
utility::Span value;
template<typename _MemberT0>
Asterisk(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Ampersand{
utility::Span value;
template<typename _MemberT0>
Ampersand(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct AmpersandEqual{
utility::Span value;
template<typename _MemberT0>
AmpersandEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct AmpersandAmpersand{
utility::Span value;
template<typename _MemberT0>
AmpersandAmpersand(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Pipe{
utility::Span value;
template<typename _MemberT0>
Pipe(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct PipeEqual{
utility::Span value;
template<typename _MemberT0>
PipeEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct PipePipe{
utility::Span value;
template<typename _MemberT0>
PipePipe(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Caret{
utility::Span value;
template<typename _MemberT0>
Caret(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct CaretEqual{
utility::Span value;
template<typename _MemberT0>
CaretEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Dollar{
utility::Span value;
template<typename _MemberT0>
Dollar(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Tilde{
utility::Span value;
template<typename _MemberT0>
Tilde(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct ForwardSlash{
utility::Span value;
template<typename _MemberT0>
ForwardSlash(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct ExclamationPoint{
utility::Span value;
template<typename _MemberT0>
ExclamationPoint(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct QuestionMark{
utility::Span value;
template<typename _MemberT0>
QuestionMark(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct QuestionMarkQuestionMark{
utility::Span value;
template<typename _MemberT0>
QuestionMarkQuestionMark(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct QuestionMarkQuestionMarkEqual{
utility::Span value;
template<typename _MemberT0>
QuestionMarkQuestionMarkEqual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Comma{
utility::Span value;
template<typename _MemberT0>
Comma(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Dot{
utility::Span value;
template<typename _MemberT0>
Dot(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct DotDot{
utility::Span value;
template<typename _MemberT0>
DotDot(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Eol {
JaktInternal::Optional<DeprecatedString> comment;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Eol(_MemberT0&& member_0, _MemberT1&& member_1):
comment{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Eof{
utility::Span value;
template<typename _MemberT0>
Eof(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct FatArrow{
utility::Span value;
template<typename _MemberT0>
FatArrow(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Arrow{
utility::Span value;
template<typename _MemberT0>
Arrow(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct And{
utility::Span value;
template<typename _MemberT0>
And(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Anon{
utility::Span value;
template<typename _MemberT0>
Anon(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct As{
utility::Span value;
template<typename _MemberT0>
As(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Boxed{
utility::Span value;
template<typename _MemberT0>
Boxed(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Break{
utility::Span value;
template<typename _MemberT0>
Break(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Catch{
utility::Span value;
template<typename _MemberT0>
Catch(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Class{
utility::Span value;
template<typename _MemberT0>
Class(_MemberT0&& member_0):
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
struct Cpp{
utility::Span value;
template<typename _MemberT0>
Cpp(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Defer{
utility::Span value;
template<typename _MemberT0>
Defer(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Destructor{
utility::Span value;
template<typename _MemberT0>
Destructor(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Else{
utility::Span value;
template<typename _MemberT0>
Else(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Enum{
utility::Span value;
template<typename _MemberT0>
Enum(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Extern{
utility::Span value;
template<typename _MemberT0>
Extern(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct False{
utility::Span value;
template<typename _MemberT0>
False(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct For{
utility::Span value;
template<typename _MemberT0>
For(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Fn{
utility::Span value;
template<typename _MemberT0>
Fn(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Comptime{
utility::Span value;
template<typename _MemberT0>
Comptime(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct If{
utility::Span value;
template<typename _MemberT0>
If(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Import{
utility::Span value;
template<typename _MemberT0>
Import(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct In{
utility::Span value;
template<typename _MemberT0>
In(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Is{
utility::Span value;
template<typename _MemberT0>
Is(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Let{
utility::Span value;
template<typename _MemberT0>
Let(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Loop{
utility::Span value;
template<typename _MemberT0>
Loop(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Match{
utility::Span value;
template<typename _MemberT0>
Match(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Mut{
utility::Span value;
template<typename _MemberT0>
Mut(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Namespace{
utility::Span value;
template<typename _MemberT0>
Namespace(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Not{
utility::Span value;
template<typename _MemberT0>
Not(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Or{
utility::Span value;
template<typename _MemberT0>
Or(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Override{
utility::Span value;
template<typename _MemberT0>
Override(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Private{
utility::Span value;
template<typename _MemberT0>
Private(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Public{
utility::Span value;
template<typename _MemberT0>
Public(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Raw{
utility::Span value;
template<typename _MemberT0>
Raw(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Reflect{
utility::Span value;
template<typename _MemberT0>
Reflect(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Return{
utility::Span value;
template<typename _MemberT0>
Return(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Restricted{
utility::Span value;
template<typename _MemberT0>
Restricted(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Sizeof{
utility::Span value;
template<typename _MemberT0>
Sizeof(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Struct{
utility::Span value;
template<typename _MemberT0>
Struct(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct This{
utility::Span value;
template<typename _MemberT0>
This(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Throw{
utility::Span value;
template<typename _MemberT0>
Throw(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Throws{
utility::Span value;
template<typename _MemberT0>
Throws(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct True{
utility::Span value;
template<typename _MemberT0>
True(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Try{
utility::Span value;
template<typename _MemberT0>
Try(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Unsafe{
utility::Span value;
template<typename _MemberT0>
Unsafe(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Virtual{
utility::Span value;
template<typename _MemberT0>
Virtual(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Weak{
utility::Span value;
template<typename _MemberT0>
Weak(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct While{
utility::Span value;
template<typename _MemberT0>
While(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Yield{
utility::Span value;
template<typename _MemberT0>
Yield(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Guard{
utility::Span value;
template<typename _MemberT0>
Guard(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Implements{
utility::Span value;
template<typename _MemberT0>
Implements(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Requires{
utility::Span value;
template<typename _MemberT0>
Requires(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Trait{
utility::Span value;
template<typename _MemberT0>
Trait(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Garbage {
JaktInternal::Optional<DeprecatedString> consumed;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Garbage(_MemberT0&& member_0, _MemberT1&& member_1):
consumed{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct Token : public Variant<Token_Details::SingleQuotedString, Token_Details::QuotedString, Token_Details::Number, Token_Details::Identifier, Token_Details::Semicolon, Token_Details::Colon, Token_Details::ColonColon, Token_Details::LParen, Token_Details::RParen, Token_Details::LCurly, Token_Details::RCurly, Token_Details::LSquare, Token_Details::RSquare, Token_Details::PercentSign, Token_Details::Plus, Token_Details::Minus, Token_Details::Equal, Token_Details::PlusEqual, Token_Details::PlusPlus, Token_Details::MinusEqual, Token_Details::MinusMinus, Token_Details::AsteriskEqual, Token_Details::ForwardSlashEqual, Token_Details::PercentSignEqual, Token_Details::NotEqual, Token_Details::DoubleEqual, Token_Details::GreaterThan, Token_Details::GreaterThanOrEqual, Token_Details::LessThan, Token_Details::LessThanOrEqual, Token_Details::LeftArithmeticShift, Token_Details::LeftShift, Token_Details::LeftShiftEqual, Token_Details::RightShift, Token_Details::RightArithmeticShift, Token_Details::RightShiftEqual, Token_Details::Asterisk, Token_Details::Ampersand, Token_Details::AmpersandEqual, Token_Details::AmpersandAmpersand, Token_Details::Pipe, Token_Details::PipeEqual, Token_Details::PipePipe, Token_Details::Caret, Token_Details::CaretEqual, Token_Details::Dollar, Token_Details::Tilde, Token_Details::ForwardSlash, Token_Details::ExclamationPoint, Token_Details::QuestionMark, Token_Details::QuestionMarkQuestionMark, Token_Details::QuestionMarkQuestionMarkEqual, Token_Details::Comma, Token_Details::Dot, Token_Details::DotDot, Token_Details::Eol, Token_Details::Eof, Token_Details::FatArrow, Token_Details::Arrow, Token_Details::And, Token_Details::Anon, Token_Details::As, Token_Details::Boxed, Token_Details::Break, Token_Details::Catch, Token_Details::Class, Token_Details::Continue, Token_Details::Cpp, Token_Details::Defer, Token_Details::Destructor, Token_Details::Else, Token_Details::Enum, Token_Details::Extern, Token_Details::False, Token_Details::For, Token_Details::Fn, Token_Details::Comptime, Token_Details::If, Token_Details::Import, Token_Details::In, Token_Details::Is, Token_Details::Let, Token_Details::Loop, Token_Details::Match, Token_Details::Mut, Token_Details::Namespace, Token_Details::Not, Token_Details::Or, Token_Details::Override, Token_Details::Private, Token_Details::Public, Token_Details::Raw, Token_Details::Reflect, Token_Details::Return, Token_Details::Restricted, Token_Details::Sizeof, Token_Details::Struct, Token_Details::This, Token_Details::Throw, Token_Details::Throws, Token_Details::True, Token_Details::Try, Token_Details::Unsafe, Token_Details::Virtual, Token_Details::Weak, Token_Details::While, Token_Details::Yield, Token_Details::Guard, Token_Details::Implements, Token_Details::Requires, Token_Details::Trait, Token_Details::Garbage> {
using Variant<Token_Details::SingleQuotedString, Token_Details::QuotedString, Token_Details::Number, Token_Details::Identifier, Token_Details::Semicolon, Token_Details::Colon, Token_Details::ColonColon, Token_Details::LParen, Token_Details::RParen, Token_Details::LCurly, Token_Details::RCurly, Token_Details::LSquare, Token_Details::RSquare, Token_Details::PercentSign, Token_Details::Plus, Token_Details::Minus, Token_Details::Equal, Token_Details::PlusEqual, Token_Details::PlusPlus, Token_Details::MinusEqual, Token_Details::MinusMinus, Token_Details::AsteriskEqual, Token_Details::ForwardSlashEqual, Token_Details::PercentSignEqual, Token_Details::NotEqual, Token_Details::DoubleEqual, Token_Details::GreaterThan, Token_Details::GreaterThanOrEqual, Token_Details::LessThan, Token_Details::LessThanOrEqual, Token_Details::LeftArithmeticShift, Token_Details::LeftShift, Token_Details::LeftShiftEqual, Token_Details::RightShift, Token_Details::RightArithmeticShift, Token_Details::RightShiftEqual, Token_Details::Asterisk, Token_Details::Ampersand, Token_Details::AmpersandEqual, Token_Details::AmpersandAmpersand, Token_Details::Pipe, Token_Details::PipeEqual, Token_Details::PipePipe, Token_Details::Caret, Token_Details::CaretEqual, Token_Details::Dollar, Token_Details::Tilde, Token_Details::ForwardSlash, Token_Details::ExclamationPoint, Token_Details::QuestionMark, Token_Details::QuestionMarkQuestionMark, Token_Details::QuestionMarkQuestionMarkEqual, Token_Details::Comma, Token_Details::Dot, Token_Details::DotDot, Token_Details::Eol, Token_Details::Eof, Token_Details::FatArrow, Token_Details::Arrow, Token_Details::And, Token_Details::Anon, Token_Details::As, Token_Details::Boxed, Token_Details::Break, Token_Details::Catch, Token_Details::Class, Token_Details::Continue, Token_Details::Cpp, Token_Details::Defer, Token_Details::Destructor, Token_Details::Else, Token_Details::Enum, Token_Details::Extern, Token_Details::False, Token_Details::For, Token_Details::Fn, Token_Details::Comptime, Token_Details::If, Token_Details::Import, Token_Details::In, Token_Details::Is, Token_Details::Let, Token_Details::Loop, Token_Details::Match, Token_Details::Mut, Token_Details::Namespace, Token_Details::Not, Token_Details::Or, Token_Details::Override, Token_Details::Private, Token_Details::Public, Token_Details::Raw, Token_Details::Reflect, Token_Details::Return, Token_Details::Restricted, Token_Details::Sizeof, Token_Details::Struct, Token_Details::This, Token_Details::Throw, Token_Details::Throws, Token_Details::True, Token_Details::Try, Token_Details::Unsafe, Token_Details::Virtual, Token_Details::Weak, Token_Details::While, Token_Details::Yield, Token_Details::Guard, Token_Details::Implements, Token_Details::Requires, Token_Details::Trait, Token_Details::Garbage>::Variant;
    using SingleQuotedString = Token_Details::SingleQuotedString;
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
    using AmpersandAmpersand = Token_Details::AmpersandAmpersand;
    using Pipe = Token_Details::Pipe;
    using PipeEqual = Token_Details::PipeEqual;
    using PipePipe = Token_Details::PipePipe;
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
    using Destructor = Token_Details::Destructor;
    using Else = Token_Details::Else;
    using Enum = Token_Details::Enum;
    using Extern = Token_Details::Extern;
    using False = Token_Details::False;
    using For = Token_Details::For;
    using Fn = Token_Details::Fn;
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
    using Reflect = Token_Details::Reflect;
    using Return = Token_Details::Return;
    using Restricted = Token_Details::Restricted;
    using Sizeof = Token_Details::Sizeof;
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
    using Implements = Token_Details::Implements;
    using Requires = Token_Details::Requires;
    using Trait = Token_Details::Trait;
    using Garbage = Token_Details::Garbage;
ErrorOr<DeprecatedString> debug_description() const;
static ErrorOr<lexer::Token> from_keyword_or_identifier(DeprecatedString const string, utility::Span const span);
utility::Span span() const;
};
struct Lexer {
  public:
public: size_t index;public: JaktInternal::DynamicArray<u8> input;public: NonnullRefPtr<compiler::Compiler> compiler;public: JaktInternal::Optional<JaktInternal::DynamicArray<u8>> comment_contents;public: JaktInternal::Set<DeprecatedString> illegal_cpp_keywords;public: ErrorOr<JaktInternal::Optional<DeprecatedString>> consume_comment_contents();
public: ErrorOr<lexer::Token> lex_quoted_string(u8 const delimiter);
public: ErrorOr<JaktInternal::Optional<lexer::Token>> next();
public: ErrorOr<lexer::Token> lex_character_constant_or_name();
public: lexer::Token lex_dot();
public: lexer::Token lex_question_mark();
public: ErrorOr<lexer::Token> lex_forward_slash();
public: u8 peek_behind(size_t const steps) const;
public: u8 peek_ahead(size_t const steps) const;
public: lexer::Token lex_asterisk();
public: lexer::Token lex_minus();
public: u8 peek() const;
public: lexer::Token lex_percent_sign();
public: ErrorOr<lexer::Token> lex_number_or_name();
public: lexer::Token lex_less_than();
public: bool eof() const;
public: Lexer(size_t a_index, JaktInternal::DynamicArray<u8> a_input, NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> a_comment_contents, JaktInternal::Set<DeprecatedString> a_illegal_cpp_keywords);

public: lexer::Token lex_ampersand();
public: utility::Span span(size_t const start, size_t const end) const;
public: lexer::Token lex_plus();
public: lexer::Token lex_exclamation_point();
public: ErrorOr<lexer::LiteralSuffix> consume_numeric_literal_suffix();
public: lexer::Token lex_colon();
public: bool valid_digit(lexer::LiteralPrefix const prefix, u8 const digit, bool const decimal_allowed);
public: ErrorOr<void> error(DeprecatedString const message, utility::Span const span);
public: lexer::Token lex_equals();
public: ErrorOr<DeprecatedString> substring(size_t const start, size_t const length) const;
public: lexer::Token lex_greater_than();
public: lexer::Token lex_pipe();
public: lexer::Token lex_caret();
public: ErrorOr<lexer::Token> lex_number();
public: static ErrorOr<JaktInternal::DynamicArray<lexer::Token>> lex(NonnullRefPtr<compiler::Compiler> const compiler);
public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::LiteralPrefix> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::LiteralPrefix const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::LiteralSuffix> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::LiteralSuffix const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::Token> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::Token const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::lexer::Lexer> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::lexer::Lexer const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
