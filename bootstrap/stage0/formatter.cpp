#include "formatter.h"
namespace Jakt {
namespace formatter {
void bubble_sort(JaktInternal::Array<String> values) {
{
i64 i = static_cast<i64>(0LL);
while ((i < (JaktInternal::checked_sub<i64>((infallible_integer_cast<i64>((((values).size())))),static_cast<i64>(1LL))))){
i64 j = static_cast<i64>(0LL);
while ((j < (JaktInternal::checked_sub<i64>((JaktInternal::checked_sub<i64>((infallible_integer_cast<i64>((((values).size())))),i)),static_cast<i64>(1LL))))){
if ((((values)[j]) > ((values)[(JaktInternal::checked_add<i64>(j,static_cast<i64>(1LL)))]))){
String const tmp = ((values)[j]);
(((values)[j]) = ((values)[(JaktInternal::checked_add<i64>(j,static_cast<i64>(1LL)))]));
(((values)[(JaktInternal::checked_add<i64>(j,static_cast<i64>(1LL)))]) = tmp);
}
(++(j));
}
(++(i));
}
}
}

ErrorOr<String> formatter::FormattedToken::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("FormattedToken("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("token: "));TRY(builder.appendff("{}, ", token));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("indent: "));TRY(builder.appendff("{}, ", indent));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("trailing_trivia: "));TRY(builder.appendff("{}, ", trailing_trivia));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("preceding_trivia: "));TRY(builder.appendff("{}", preceding_trivia));
}
TRY(builder.append(")"));return builder.to_string(); }
formatter::FormattedToken::FormattedToken(lexer::Token a_token, size_t a_indent, JaktInternal::Array<u8> a_trailing_trivia, JaktInternal::Array<u8> a_preceding_trivia) :token(a_token), indent(a_indent), trailing_trivia(a_trailing_trivia), preceding_trivia(a_preceding_trivia){}

ErrorOr<String> formatter::FormattedToken::token_text() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = ((*this).token);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::SingleQuotedString>();String const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("'{}'"),quote))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::SingleQuotedByteString>();String const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("b'{}'"),quote))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::QuotedString>();String const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("\"{}\""),quote))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Number>();lexer::LiteralPrefix const& prefix = __jakt_match_value.prefix;
String const& number = __jakt_match_value.number;
lexer::LiteralSuffix const& suffix = __jakt_match_value.suffix;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("{}{}{}"),((prefix).to_string()),number,((suffix).to_string())))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();String const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Semicolon>();
return JaktInternal::ExplicitValue(String(";"));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
return JaktInternal::ExplicitValue(String(":"));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ColonColon>();
return JaktInternal::ExplicitValue(String("::"));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(String("("));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(String(")"));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(String("{"));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(String("}"));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue(String("["));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
return JaktInternal::ExplicitValue(String("]"));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSign>();
return JaktInternal::ExplicitValue(String("%"));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Plus>();
return JaktInternal::ExplicitValue(String("+"));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Minus>();
return JaktInternal::ExplicitValue(String("-"));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
return JaktInternal::ExplicitValue(String("="));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusEqual>();
return JaktInternal::ExplicitValue(String("+="));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusPlus>();
return JaktInternal::ExplicitValue(String("++"));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusEqual>();
return JaktInternal::ExplicitValue(String("-="));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusMinus>();
return JaktInternal::ExplicitValue(String("--"));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AsteriskEqual>();
return JaktInternal::ExplicitValue(String("*="));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlashEqual>();
return JaktInternal::ExplicitValue(String("/="));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSignEqual>();
return JaktInternal::ExplicitValue(String("%="));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::NotEqual>();
return JaktInternal::ExplicitValue(String("!="));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DoubleEqual>();
return JaktInternal::ExplicitValue(String("=="));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
return JaktInternal::ExplicitValue(String(">"));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThanOrEqual>();
return JaktInternal::ExplicitValue(String(">="));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
return JaktInternal::ExplicitValue(String("<"));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThanOrEqual>();
return JaktInternal::ExplicitValue(String("<="));
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftArithmeticShift>();
return JaktInternal::ExplicitValue(String("<<<"));
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShift>();
return JaktInternal::ExplicitValue(String("<<"));
};/*case end*/
case 33: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShiftEqual>();
return JaktInternal::ExplicitValue(String("<<="));
};/*case end*/
case 34: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShift>();
return JaktInternal::ExplicitValue(String(">>"));
};/*case end*/
case 35: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightArithmeticShift>();
return JaktInternal::ExplicitValue(String(">>>"));
};/*case end*/
case 36: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShiftEqual>();
return JaktInternal::ExplicitValue(String(">>="));
};/*case end*/
case 37: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Asterisk>();
return JaktInternal::ExplicitValue(String("*"));
};/*case end*/
case 38: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Ampersand>();
return JaktInternal::ExplicitValue(String("&"));
};/*case end*/
case 39: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandEqual>();
return JaktInternal::ExplicitValue(String("&="));
};/*case end*/
case 40: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandAmpersand>();
return JaktInternal::ExplicitValue(String("&&"));
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
return JaktInternal::ExplicitValue(String("|"));
};/*case end*/
case 42: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipeEqual>();
return JaktInternal::ExplicitValue(String("|="));
};/*case end*/
case 43: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipePipe>();
return JaktInternal::ExplicitValue(String("||"));
};/*case end*/
case 44: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Caret>();
return JaktInternal::ExplicitValue(String("^"));
};/*case end*/
case 45: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::CaretEqual>();
return JaktInternal::ExplicitValue(String("^="));
};/*case end*/
case 46: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Dollar>();
return JaktInternal::ExplicitValue(String("$"));
};/*case end*/
case 47: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Tilde>();
return JaktInternal::ExplicitValue(String("~"));
};/*case end*/
case 48: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlash>();
return JaktInternal::ExplicitValue(String("/"));
};/*case end*/
case 49: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ExclamationPoint>();
return JaktInternal::ExplicitValue(String("!"));
};/*case end*/
case 50: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMark>();
return JaktInternal::ExplicitValue(String("?"));
};/*case end*/
case 51: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMark>();
return JaktInternal::ExplicitValue(String("??"));
};/*case end*/
case 52: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMarkEqual>();
return JaktInternal::ExplicitValue(String("??="));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(String(","));
};/*case end*/
case 54: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Dot>();
return JaktInternal::ExplicitValue(String("."));
};/*case end*/
case 55: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DotDot>();
return JaktInternal::ExplicitValue(String(".."));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(String(""));
};/*case end*/
case 57: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Eof>();
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
return JaktInternal::ExplicitValue(String("=>"));
};/*case end*/
case 59: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Arrow>();
return JaktInternal::ExplicitValue(String("->"));
};/*case end*/
case 60: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::And>();
return JaktInternal::ExplicitValue(String("and"));
};/*case end*/
case 61: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Anon>();
return JaktInternal::ExplicitValue(String("anon"));
};/*case end*/
case 62: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::As>();
return JaktInternal::ExplicitValue(String("as"));
};/*case end*/
case 63: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Boxed>();
return JaktInternal::ExplicitValue(String("boxed"));
};/*case end*/
case 64: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Break>();
return JaktInternal::ExplicitValue(String("break"));
};/*case end*/
case 65: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Catch>();
return JaktInternal::ExplicitValue(String("catch"));
};/*case end*/
case 66: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Class>();
return JaktInternal::ExplicitValue(String("class"));
};/*case end*/
case 67: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Continue>();
return JaktInternal::ExplicitValue(String("continue"));
};/*case end*/
case 68: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Cpp>();
return JaktInternal::ExplicitValue(String("cpp"));
};/*case end*/
case 69: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Defer>();
return JaktInternal::ExplicitValue(String("defer"));
};/*case end*/
case 70: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Else>();
return JaktInternal::ExplicitValue(String("else"));
};/*case end*/
case 71: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Enum>();
return JaktInternal::ExplicitValue(String("enum"));
};/*case end*/
case 72: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Extern>();
return JaktInternal::ExplicitValue(String("extern"));
};/*case end*/
case 73: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::False>();
return JaktInternal::ExplicitValue(String("false"));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(String("for"));
};/*case end*/
case 75: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Function>();
return JaktInternal::ExplicitValue(String("function"));
};/*case end*/
case 76: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comptime>();
return JaktInternal::ExplicitValue(String("comptime"));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(String("if"));
};/*case end*/
case 78: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Import>();
return JaktInternal::ExplicitValue(String("import"));
};/*case end*/
case 79: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::In>();
return JaktInternal::ExplicitValue(String("in"));
};/*case end*/
case 80: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Is>();
return JaktInternal::ExplicitValue(String("is"));
};/*case end*/
case 81: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Let>();
return JaktInternal::ExplicitValue(String("let"));
};/*case end*/
case 82: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Loop>();
return JaktInternal::ExplicitValue(String("loop"));
};/*case end*/
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(String("match"));
};/*case end*/
case 84: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Mut>();
return JaktInternal::ExplicitValue(String("mut"));
};/*case end*/
case 85: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Namespace>();
return JaktInternal::ExplicitValue(String("namespace"));
};/*case end*/
case 86: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Not>();
return JaktInternal::ExplicitValue(String("not"));
};/*case end*/
case 87: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Or>();
return JaktInternal::ExplicitValue(String("or"));
};/*case end*/
case 89: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Private>();
return JaktInternal::ExplicitValue(String("private"));
};/*case end*/
case 90: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Public>();
return JaktInternal::ExplicitValue(String("public"));
};/*case end*/
case 91: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Raw>();
return JaktInternal::ExplicitValue(String("raw"));
};/*case end*/
case 92: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Return>();
return JaktInternal::ExplicitValue(String("return"));
};/*case end*/
case 93: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Restricted>();
return JaktInternal::ExplicitValue(String("restricted"));
};/*case end*/
case 94: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Struct>();
return JaktInternal::ExplicitValue(String("struct"));
};/*case end*/
case 95: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::This>();
return JaktInternal::ExplicitValue(String("this"));
};/*case end*/
case 96: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throw>();
return JaktInternal::ExplicitValue(String("throw"));
};/*case end*/
case 97: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throws>();
return JaktInternal::ExplicitValue(String("throws"));
};/*case end*/
case 98: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::True>();
return JaktInternal::ExplicitValue(String("true"));
};/*case end*/
case 99: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Try>();
return JaktInternal::ExplicitValue(String("try"));
};/*case end*/
case 100: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Unsafe>();
return JaktInternal::ExplicitValue(String("unsafe"));
};/*case end*/
case 102: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Weak>();
return JaktInternal::ExplicitValue(String("weak"));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(String("while"));
};/*case end*/
case 104: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Yield>();
return JaktInternal::ExplicitValue(String("yield"));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(String("guard"));
};/*case end*/
case 88: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Override>();
return JaktInternal::ExplicitValue(String("override"));
};/*case end*/
case 101: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Virtual>();
return JaktInternal::ExplicitValue(String("virtual"));
};/*case end*/
case 106: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Implements>();
return JaktInternal::ExplicitValue(String("implements"));
};/*case end*/
case 107: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Requires>();
return JaktInternal::ExplicitValue(String("requires"));
};/*case end*/
case 108: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Trait>();
return JaktInternal::ExplicitValue(String("trait"));
};/*case end*/
case 109: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Garbage>();return JaktInternal::ExplicitValue(String(""));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> formatter::FormattedToken::debug_text() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = ((*this).token);
switch(__jakt_match_variant.index()) {
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();String const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("Identifier: {}"),name))));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();JaktInternal::Optional<String> const& comment = __jakt_match_value.comment;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("Eol: {}"),comment.value_or_lazy_evaluated([&] { return String(""); })))));
};/*case end*/
case 57: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Eof>();
return JaktInternal::ExplicitValue(String("Eof"));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).token_text()))));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<String> formatter::ReflowState::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("ReflowState("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("token: "));TRY(builder.appendff("{}, ", token));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("state: "));TRY(builder.appendff("{}, ", state));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("enclosures_to_ignore: "));TRY(builder.appendff("{}", enclosures_to_ignore));
}
TRY(builder.append(")"));return builder.to_string(); }
formatter::ReflowState::ReflowState(formatter::FormattedToken a_token, formatter::State a_state, size_t a_enclosures_to_ignore) :token(a_token), state(a_state), enclosures_to_ignore(a_enclosures_to_ignore){}

ErrorOr<String> formatter::Formatter::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Formatter("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("token_provider: "));TRY(builder.appendff("{}, ", token_provider));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_line: "));TRY(builder.appendff("{}, ", current_line));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_line_length: "));TRY(builder.appendff("{}, ", current_line_length));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("max_allowed_line_length: "));TRY(builder.appendff("{}, ", max_allowed_line_length));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("breakable_points_in_current_line: "));TRY(builder.appendff("{}, ", breakable_points_in_current_line));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("tokens_to_reflow: "));TRY(builder.appendff("{}, ", tokens_to_reflow));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("replace_commas_in_enclosure: "));TRY(builder.appendff("{}, ", replace_commas_in_enclosure));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("enclosures_to_ignore: "));TRY(builder.appendff("{}, ", enclosures_to_ignore));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("in_condition_expr: "));TRY(builder.appendff("{}, ", in_condition_expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("in_condition_expr_indented: "));TRY(builder.appendff("{}, ", in_condition_expr_indented));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("logical_break_indent: "));TRY(builder.appendff("{}, ", logical_break_indent));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("empty_line_count: "));TRY(builder.appendff("{}", empty_line_count));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>> formatter::Formatter::next() {
{
JaktInternal::Optional<formatter::ReflowState> const reflown_token = ((((*this).tokens_to_reflow)).pop());
JaktInternal::Optional<formatter::FormattedToken> maybe_next_underlying_token = TRY((((reflown_token).map([](auto& _value) { return _value.token; })).try_value_or_lazy_evaluated_optional([&]() -> ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> { return TRY((((((*this).token_provider)).next()))); })));
formatter::State current_state = ((reflown_token).map([](auto& _value) { return _value.state; })).value_or_lazy_evaluated([&] { return ((((*this).token_provider)).state()); });
if (((maybe_next_underlying_token).has_value())){
lexer::Token next_underlying_token = (((maybe_next_underlying_token.value())).token);
bool accepted_at_least_one_token = false;
while (((!(((next_underlying_token).index() == 57 /* Eof */))) && (!(((next_underlying_token).index() == 56 /* Eol */))))){
size_t const projected_added_length = TRY((((*this).token_length((maybe_next_underlying_token.value())))));
if (((((*this).logical_break_indent)).has_value())){
((((maybe_next_underlying_token.value())).indent) = (((*this).logical_break_indent).value()));
}
if (((((*this).in_condition_expr) && ((next_underlying_token).index() == 10 /* LCurly */)) || ((next_underlying_token).index() == 70 /* Else */))){
(((*this).in_condition_expr) = false);
(((*this).in_condition_expr_indented) = false);
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
{
(accepted_at_least_one_token = true);
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, projected_added_length);});
if ((!(formatter::Formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
)));
}
else {
(breakable_point = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
)));
}

if (((breakable_point).has_value())){
TRY((((((*this).breakable_points_in_current_line)).push((breakable_point.value())))));
}
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
}
else {
({auto& _jakt_ref = ((*this).enclosures_to_ignore);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
{
(accepted_at_least_one_token = true);
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, projected_added_length);});
if ((!(formatter::Formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
)));
}
else {
(breakable_point = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
)));
}

if (((breakable_point).has_value())){
TRY((((((*this).breakable_points_in_current_line)).push((breakable_point.value())))));
}
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
}
else {
({auto& _jakt_ref = ((*this).enclosures_to_ignore);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
{
(accepted_at_least_one_token = true);
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, projected_added_length);});
if ((!(formatter::Formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
)));
}
else {
(breakable_point = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
)));
}

if (((breakable_point).has_value())){
TRY((((((*this).breakable_points_in_current_line)).push((breakable_point.value())))));
}
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
}
else {
({auto& _jakt_ref = ((*this).enclosures_to_ignore);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
{
bool ignore = false;
if ((((*this).enclosures_to_ignore) > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ((*this).enclosures_to_ignore);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
(ignore = true);
}
if (((!(ignore)) && (!(formatter::Formatter::Formatter::should_ignore_state(current_state))))){
lexer::Token const replacement = formatter::collapse<lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
formatter::FormattedToken const new_token = formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length(new_token)))));});
if (((replacement).index() == 56 /* Eol */)){
TRY((((((*this).tokens_to_reflow)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
return JaktInternal::LoopBreak{};
}
}
else {
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length((maybe_next_underlying_token.value()))))));});
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
{
bool ignore = false;
if ((((*this).enclosures_to_ignore) > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ((*this).enclosures_to_ignore);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
(ignore = true);
}
if (((!(ignore)) && (!(formatter::Formatter::Formatter::should_ignore_state(current_state))))){
lexer::Token const replacement = formatter::collapse<lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
formatter::FormattedToken const new_token = formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length(new_token)))));});
if (((replacement).index() == 56 /* Eol */)){
TRY((((((*this).tokens_to_reflow)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
return JaktInternal::LoopBreak{};
}
}
else {
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length((maybe_next_underlying_token.value()))))));});
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
{
bool ignore = false;
if ((((*this).enclosures_to_ignore) > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ((*this).enclosures_to_ignore);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
(ignore = true);
}
if (((!(ignore)) && (!(formatter::Formatter::Formatter::should_ignore_state(current_state))))){
lexer::Token const replacement = formatter::collapse<lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
formatter::FormattedToken const new_token = formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length(new_token)))));});
if (((replacement).index() == 56 /* Eol */)){
TRY((((((*this).tokens_to_reflow)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
return JaktInternal::LoopBreak{};
}
}
else {
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length((maybe_next_underlying_token.value()))))));});
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
{
(accepted_at_least_one_token = true);
if ((!(formatter::Formatter::Formatter::should_ignore_state(current_state)))){
lexer::Token const replacement = formatter::collapse<lexer::Token>(((((*this).replace_commas_in_enclosure)).last())).value_or_lazy_evaluated([&] { return next_underlying_token; });
formatter::FormattedToken const new_token = formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length(new_token)))));});
if (((replacement).index() == 56 /* Eol */)){
return JaktInternal::LoopBreak{};
}
}
else {
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length((maybe_next_underlying_token.value()))))));});
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
lexer::Token const newline =  lexer::Token { typename lexer::Token::Eol(JaktInternal::OptionalNone(),((next_underlying_token).span())) } ;
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if (((((next_token.value())).indent) > (((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if (((((next_token.value())).indent) > (((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if (((((next_token.value())).indent) > (((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if (((((next_token.value())).indent) > (((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if (((((next_token.value())).indent) > (((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
if ((((((*this).logical_break_indent)).has_value()) && (((next_underlying_token).index() == 60 /* And */) || ((next_underlying_token).index() == 87 /* Or */)))){
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length((maybe_next_underlying_token.value()))))));});
formatter::FormattedToken const new_token = formatter::FormattedToken(newline,(((*this).logical_break_indent).value()),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({})))));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, TRY((((*this).token_length(new_token)))));});
return JaktInternal::LoopBreak{};
}
size_t const real_line_length = (JaktInternal::checked_add<size_t>((JaktInternal::checked_add<size_t>(((*this).current_line_length),projected_added_length)),(((maybe_next_underlying_token.value())).indent)));
size_t const most_desirable_breaking_point_index = ((*this).pick_breaking_point_index());
if ((accepted_at_least_one_token && ((real_line_length > ((*this).max_allowed_line_length)) && ((!(((((*this).breakable_points_in_current_line)).is_empty()))) && ((((((((*this).breakable_points_in_current_line))[most_desirable_breaking_point_index])).point()) < ((((*this).current_line)).size())) && (!(formatter::Formatter::Formatter::should_ignore_state(current_state)))))))){
formatter::BreakablePoint const breakable_point = ((((*this).breakable_points_in_current_line))[most_desirable_breaking_point_index]);
if ((!(((((*this).replace_commas_in_enclosure)).is_empty())))){
(((((*this).replace_commas_in_enclosure))[(JaktInternal::checked_sub<size_t>(((((*this).replace_commas_in_enclosure)).size()),static_cast<size_t>(1ULL)))]) = newline);
}
size_t const point = ((breakable_point).point());
if (((breakable_point).index() == 3 /* Logical */)){
if ((!(((((*this).logical_break_indent)).has_value())))){
(((*this).logical_break_indent) = ((((((((*this).current_line))[point])).token)).indent));
if ((!(((*this).in_condition_expr_indented)))){
({auto& _jakt_ref = (((*this).logical_break_indent).value());_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
}
}
(((*this).tokens_to_reflow) = TRY((((((((*this).current_line))[(JaktInternal::Range<size_t>{static_cast<size_t>(point),static_cast<size_t>(9223372036854775807LL)})])).to_array()))));
TRY((((((*this).tokens_to_reflow)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
TRY((((*this).fixup_tokens_to_reflow())));
formatter::State const final_state = ((((((*this).current_line))[point])).state);
(((*this).enclosures_to_ignore) = ((((((*this).current_line))[point])).enclosures_to_ignore));
(((*this).current_line) = TRY((((((((*this).current_line))[(JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(point)})])).to_array()))));
TRY((((((*this).current_line)).push(formatter::ReflowState(formatter::FormattedToken(newline,(((maybe_next_underlying_token.value())).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))),final_state,((*this).enclosures_to_ignore))))));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
return JaktInternal::LoopBreak{};
}
(accepted_at_least_one_token = true);
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
({auto& _jakt_ref = ((*this).current_line_length);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, projected_added_length);});
if ((((*this).in_condition_expr) && (((next_underlying_token).index() == 60 /* And */) || ((next_underlying_token).index() == 87 /* Or */)))){
TRY((((((*this).breakable_points_in_current_line)).push( formatter::BreakablePoint { typename formatter::BreakablePoint::Logical(((((*this).current_line)).size()),((*this).current_line_length)) } ))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
if (((((*this).tokens_to_reflow)).is_empty())){
(maybe_next_underlying_token = TRY((((((*this).token_provider)).next()))));
(current_state = ((((*this).token_provider)).state()));
}
else {
JaktInternal::Optional<formatter::ReflowState> const reflown_token = ((((*this).tokens_to_reflow)).pop());
(maybe_next_underlying_token = ((reflown_token).map([](auto& _value) { return _value.token; })));
(current_state = ((reflown_token).map([](auto& _value) { return _value.state; })).value_or_lazy_evaluated([&] { return current_state; }));
}

if ((!(((maybe_next_underlying_token).has_value())))){
break;
}
(next_underlying_token = (((maybe_next_underlying_token.value())).token));
}
size_t const allowed_empty_lines_in_state = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = current_state;
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::TypeContext>();return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::ImportList>();return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::ParameterList>();return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::Toplevel>();return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
}/*switch end*/
}()
));
JaktInternal::Array<formatter::ReflowState> line = ((*this).current_line);
(((*this).current_line) = (TRY((Array<formatter::ReflowState>::create_with({})))));
(((*this).breakable_points_in_current_line) = (TRY((Array<formatter::BreakablePoint>::create_with({})))));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
(((*this).enclosures_to_ignore) = static_cast<size_t>(0ULL));
if ((!(((*this).in_condition_expr)))){
(((*this).logical_break_indent) = JaktInternal::OptionalNone());
}
if ((((line).is_empty()) || (!((((((((((line).last()).value())).token)).token)).index() == 56 /* Eol */))))){
TRY((((line).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
}
if ((((line).size()) == static_cast<size_t>(1ULL))){
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((((((line).last()).value())).token)).token);
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();JaktInternal::Optional<String> const& comment = __jakt_match_value.comment;
{
if (((((*this).empty_line_count) >= allowed_empty_lines_in_state) && (!(((comment).has_value()))))){
return (TRY((((*this).next()))));
}
if (((comment).has_value())){
(((*this).empty_line_count) = static_cast<size_t>(0ULL));
}
else {
({auto& _jakt_ref = ((*this).empty_line_count);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(((*this).empty_line_count) = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
else {
(((*this).empty_line_count) = static_cast<size_t>(0ULL));
}

if ((((line).size()) > static_cast<size_t>(1ULL))){
(((((((line)[(JaktInternal::checked_sub<size_t>(((line).size()),static_cast<size_t>(2ULL)))])).token)).trailing_trivia) = (TRY((Array<u8>::create_with({})))));
}
(((((((line)[(JaktInternal::checked_sub<size_t>(((line).size()),static_cast<size_t>(1ULL)))])).token)).preceding_trivia) = (TRY((Array<u8>::create_with({})))));
(((((((line)[(JaktInternal::checked_sub<size_t>(((line).size()),static_cast<size_t>(1ULL)))])).token)).trailing_trivia) = (TRY((Array<u8>::create_with({})))));
TRY((((*this).fixup_closing_enclosures(((line))))));
JaktInternal::Array<formatter::FormattedToken> result = (TRY((Array<formatter::FormattedToken>::create_with({}))));
{
JaktInternal::ArrayIterator<formatter::ReflowState> _magic = ((line).iterator());
for (;;){
JaktInternal::Optional<formatter::ReflowState> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
formatter::ReflowState state = (_magic_value.value());
{
TRY((((result).push(((state).token)))));
}

}
}

return (result);
}
else {
if (((((*this).current_line)).is_empty())){
return (JaktInternal::OptionalNone());
}
JaktInternal::Array<formatter::ReflowState> const line = ((*this).current_line);
(((*this).current_line) = (TRY((Array<formatter::ReflowState>::create_with({})))));
(((*this).breakable_points_in_current_line) = (TRY((Array<formatter::BreakablePoint>::create_with({})))));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
(((*this).enclosures_to_ignore) = static_cast<size_t>(0ULL));
(((*this).in_condition_expr) = false);
(((*this).in_condition_expr_indented) = false);
(((*this).logical_break_indent) = JaktInternal::OptionalNone());
JaktInternal::Array<formatter::FormattedToken> result = (TRY((Array<formatter::FormattedToken>::create_with({}))));
{
JaktInternal::ArrayIterator<formatter::ReflowState> _magic = ((line).iterator());
for (;;){
JaktInternal::Optional<formatter::ReflowState> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
formatter::ReflowState state = (_magic_value.value());
{
TRY((((result).push(((state).token)))));
}

}
}

return (result);
}

}
}

bool formatter::Formatter::should_ignore_state(formatter::State const state) {
{
return ((((state).index() == 11 /* TypeContext */) || ((state).index() == 9 /* VariableDeclaration */)));
}
}

formatter::Formatter::Formatter(formatter::Stage0 a_token_provider, JaktInternal::Array<formatter::ReflowState> a_current_line, size_t a_current_line_length, size_t a_max_allowed_line_length, JaktInternal::Array<formatter::BreakablePoint> a_breakable_points_in_current_line, JaktInternal::Array<formatter::ReflowState> a_tokens_to_reflow, JaktInternal::Array<JaktInternal::Optional<lexer::Token>> a_replace_commas_in_enclosure, size_t a_enclosures_to_ignore, bool a_in_condition_expr, bool a_in_condition_expr_indented, JaktInternal::Optional<size_t> a_logical_break_indent, size_t a_empty_line_count) :token_provider(a_token_provider), current_line(a_current_line), current_line_length(a_current_line_length), max_allowed_line_length(a_max_allowed_line_length), breakable_points_in_current_line(a_breakable_points_in_current_line), tokens_to_reflow(a_tokens_to_reflow), replace_commas_in_enclosure(a_replace_commas_in_enclosure), enclosures_to_ignore(a_enclosures_to_ignore), in_condition_expr(a_in_condition_expr), in_condition_expr_indented(a_in_condition_expr_indented), logical_break_indent(a_logical_break_indent), empty_line_count(a_empty_line_count){}

ErrorOr<size_t> formatter::Formatter::token_length(formatter::FormattedToken const token) const {
{
size_t length = ((((token).preceding_trivia)).size());
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<size_t>>{
auto&& __jakt_match_variant = ((token).token);
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();JaktInternal::Optional<String> const& comment = __jakt_match_value.comment;
{
if (((comment).has_value())){
u8 next_char = ' ';
if (((((comment.value())).length()) != static_cast<size_t>(0ULL))){
(next_char = (((comment.value())).byte_at(static_cast<size_t>(0ULL))));
}
size_t const space = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (next_char);
if (__jakt_enum_value == ' ') {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
}
else if (__jakt_enum_value == '\t') {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
}
else if (__jakt_enum_value == '/') {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
}
else {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
}
}()))
;
({auto& _jakt_ref = length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, space);});
({auto& _jakt_ref = length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, (((comment.value())).length()));});
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
({auto& _jakt_ref = length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, ((TRY((((token).token_text())))).length()));});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
({auto& _jakt_ref = length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, ((((token).trailing_trivia)).size()));});
return (length);
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Formatter::peek() {
{
JaktInternal::Optional<formatter::ReflowState> reflown_token = JaktInternal::OptionalNone();
if ((((((*this).tokens_to_reflow)).size()) > static_cast<size_t>(0ULL))){
(reflown_token = ((((*this).tokens_to_reflow))[(JaktInternal::checked_sub<size_t>(((((*this).tokens_to_reflow)).size()),static_cast<size_t>(1ULL)))]));
}
return (TRY((((reflown_token).map([](auto& _value) { return _value.token; })).try_value_or_lazy_evaluated_optional([&]() -> ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> { return TRY((((((*this).token_provider)).formatted_peek()))); }))));
}
}

ErrorOr<formatter::Formatter> formatter::Formatter::for_tokens(JaktInternal::Array<lexer::Token> const tokens,bool const debug,size_t const max_allowed_line_length) {
{
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
return (formatter::Formatter(TRY((formatter::Stage0::Stage0::for_tokens(tokens,debug))),(TRY((Array<formatter::ReflowState>::create_with({})))),static_cast<size_t>(0ULL),max_allowed_line_length,(TRY((Array<formatter::BreakablePoint>::create_with({})))),(TRY((Array<formatter::ReflowState>::create_with({})))),(TRY((Array<JaktInternal::Optional<lexer::Token>>::create_with({none})))),static_cast<size_t>(0ULL),false,false,JaktInternal::OptionalNone(),static_cast<size_t>(0ULL)));
}
}

ErrorOr<JaktInternal::Array<u8>> formatter::Formatter::to_array(String const s) {
{
JaktInternal::Array<u8> result = (TRY((Array<u8>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((s).length()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((result).push(((s).byte_at(i))))));
}

}
}

return (result);
}
}

ErrorOr<void> formatter::Formatter::fixup_tokens_to_reflow() {
{
if (((((*this).tokens_to_reflow)).is_empty())){
return {};
}
size_t i = static_cast<size_t>(0ULL);
size_t j = (JaktInternal::checked_sub<size_t>(((((*this).tokens_to_reflow)).size()),static_cast<size_t>(1ULL)));
while ((i < j)){
formatter::ReflowState const a = ((((*this).tokens_to_reflow))[i]);
(((((*this).tokens_to_reflow))[i]) = ((((*this).tokens_to_reflow))[j]));
(((((*this).tokens_to_reflow))[j]) = a);
({auto& _jakt_ref = i;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
({auto& _jakt_ref = j;_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
}
return {};
}

ErrorOr<void> formatter::Formatter::fixup_closing_enclosures(JaktInternal::Array<formatter::ReflowState>& line) const {
{
if (((((line))).is_empty())){
return {};
}
(((((((((line)))[static_cast<i64>(0LL)])).token)).preceding_trivia) = (TRY((Array<u8>::create_with({})))));
size_t enclosure_run_length = static_cast<size_t>(0ULL);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>((JaktInternal::checked_sub<size_t>(((((line))).size()),static_cast<size_t>(1ULL)))),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((((((((line)))[i])).token)).token);
switch(__jakt_match_variant.index()) {
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
{
({auto& _jakt_ref = enclosure_run_length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
{
({auto& _jakt_ref = enclosure_run_length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
{
({auto& _jakt_ref = enclosure_run_length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enclosure_run_length)});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t j = (_magic_value.value());
{
(((((((line)))[(JaktInternal::checked_sub<size_t>(i,j))])).token) = formatter::FormattedToken(((((((((line)))[(JaktInternal::checked_sub<size_t>(i,j))])).token)).token),((((((((line)))[(JaktInternal::checked_sub<size_t>(i,enclosure_run_length))])).token)).indent),((((((((line)))[(JaktInternal::checked_sub<size_t>(i,j))])).token)).trailing_trivia),((((((((line)))[(JaktInternal::checked_sub<size_t>(i,j))])).token)).preceding_trivia)));
}

}
}

(enclosure_run_length = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}

}
}

{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enclosure_run_length)});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t j = (_magic_value.value());
{
(((((((line)))[j])).token) = formatter::FormattedToken(((((((((line)))[j])).token)).token),((((((((line)))[enclosure_run_length])).token)).indent),((((((((line)))[j])).token)).trailing_trivia),((((((((line)))[j])).token)).preceding_trivia)));
}

}
}

}
return {};
}

size_t formatter::Formatter::pick_breaking_point_index() const {
{
return (static_cast<size_t>(0ULL));
}
}

ErrorOr<String> formatter::Stage0::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Stage0("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("tokens: "));TRY(builder.appendff("{}, ", tokens));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("index: "));TRY(builder.appendff("{}, ", index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("states: "));TRY(builder.appendff("{}, ", states));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("indent: "));TRY(builder.appendff("{}, ", indent));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("already_seen_enclosure_in_current_line: "));TRY(builder.appendff("{}, ", already_seen_enclosure_in_current_line));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dedents_to_skip: "));TRY(builder.appendff("{}, ", dedents_to_skip));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("debug: "));TRY(builder.appendff("{}", debug));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next() {
{
return (TRY((((*this).next_impl(false)))));
}
}

ErrorOr<void> formatter::Stage0::replace_state(formatter::State const state) {
{
JaktInternal::Optional<formatter::State> const dummy = ((((*this).states)).pop());
TRY((((((*this).states)).push(state))));
}
return {};
}

formatter::State formatter::Stage0::state() const {
{
return ((((((*this).states)).last()).value()));
}
}

ErrorOr<void> formatter::Stage0::push_state(formatter::State const state) {
{
TRY((((((*this).states)).push(state))));
}
return {};
}

ErrorOr<formatter::Stage0> formatter::Stage0::for_tokens(JaktInternal::Array<lexer::Token> const tokens,bool const debug) {
{
return (formatter::Stage0(tokens,static_cast<size_t>(0ULL),(TRY((Array<formatter::State>::create_with({ formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)) } })))),static_cast<size_t>(0ULL),false,(TRY((Array<size_t>::create_with({static_cast<size_t>(0ULL)})))),debug));
}
}

ErrorOr<formatter::Stage0> formatter::Stage0::create(NonnullRefPtr<compiler::Compiler> compiler,JaktInternal::Array<u8> const source,bool const debug) {
{
JaktInternal::Array<u8> const old_file_contents = ((compiler)->current_file_contents);
(((compiler)->current_file_contents) = source);
ScopeGuard __jakt_var_442([&] {
{
(((compiler)->current_file_contents) = old_file_contents);
}

});
JaktInternal::Array<lexer::Token> const tokens = TRY((lexer::Lexer::Lexer::lex(compiler)));
return (formatter::Stage0(tokens,static_cast<size_t>(0ULL),(TRY((Array<formatter::State>::create_with({ formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)) } })))),static_cast<size_t>(0ULL),false,(TRY((Array<size_t>::create_with({static_cast<size_t>(0ULL)})))),debug));
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_impl(bool const reconsume) {
{
if ((((*this).index) >= ((((*this).tokens)).size()))){
return (JaktInternal::OptionalNone());
}
if ((((((*this).states)).is_empty()) && (((*this).index) < ((((*this).tokens)).size())))){
abort();
}
lexer::Token token = ((*this).consume());
i64 indent_change = static_cast<i64>(0LL);
if ((!(reconsume))){
if (((!(((*this).already_seen_enclosure_in_current_line))) && ((((token).index() == 8 /* LParen */) || ((token).index() == 10 /* LCurly */)) || ((token).index() == 12 /* LSquare */)))){
(((*this).already_seen_enclosure_in_current_line) = true);
TRY((((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)))));
(indent_change = static_cast<i64>(1LL));
}
else if (((token).index() == 56 /* Eol */)){
(((*this).already_seen_enclosure_in_current_line) = false);
}
if (((((token).index() == 8 /* LParen */) || ((token).index() == 10 /* LCurly */)) || ((token).index() == 12 /* LSquare */))){
((((((*this).dedents_to_skip))[(JaktInternal::checked_sub<size_t>(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL)))])++));
}
if (((((token).index() == 9 /* RParen */) || ((token).index() == 11 /* RCurly */)) || ((token).index() == 13 /* RSquare */))){
if (((((((*this).dedents_to_skip)).last()).value()) == static_cast<size_t>(1ULL))){
if ((((((*this).dedents_to_skip)).size()) > static_cast<size_t>(1ULL))){
JaktInternal::Optional<size_t> const dummy = ((((*this).dedents_to_skip)).pop());
}
({auto& _jakt_ref = ((*this).indent);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
(((*this).already_seen_enclosure_in_current_line) = false);
}
else if (((((((*this).dedents_to_skip)).last()).value()) > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ((((*this).dedents_to_skip))[(JaktInternal::checked_sub<size_t>(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL)))]);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
}
}
ScopeGuard __jakt_var_443([&] {
{
if ((indent_change > static_cast<i64>(0LL))){
({auto& _jakt_ref = ((*this).indent);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, (infallible_integer_cast<size_t>((indent_change))));});
}
else if ((indent_change < static_cast<i64>(0LL))){
({auto& _jakt_ref = ((*this).indent);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, (infallible_integer_cast<size_t>(((-(indent_change))))));});
}
}

});
if (((*this).debug)){
warnln();
warnln(String("Token: {} -- Indent: {}"),TRY((((formatter::FormattedToken(token,static_cast<size_t>(0ULL),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({})))))).debug_text()))),((*this).indent));
{
JaktInternal::ArrayIterator<formatter::State> _magic = ((((*this).states)).iterator());
for (;;){
JaktInternal::Optional<formatter::State> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
formatter::State state = (_magic_value.value());
{
warnln(String("- State: {}"),state);
}

}
}

warnln();
}
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).state());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::Toplevel>();size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 71: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Enum>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_444; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL)) } ))));
JaktInternal::Array<u8> trailing_trivia = (TRY((Array<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */))))){
TRY((((trailing_trivia).push(' '))));
}
__jakt_var_444 = formatter::FormattedToken(token,((*this).indent),trailing_trivia,(TRY((Array<u8>::create_with({}))))); goto __jakt_label_404;

}
__jakt_label_404:; __jakt_var_444.release_value(); }));
};/*case end*/
case 66: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Class>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_445; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL)) } ))));
JaktInternal::Array<u8> trailing_trivia = (TRY((Array<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */))))){
TRY((((trailing_trivia).push(' '))));
}
__jakt_var_445 = formatter::FormattedToken(token,((*this).indent),trailing_trivia,(TRY((Array<u8>::create_with({}))))); goto __jakt_label_405;

}
__jakt_label_405:; __jakt_var_445.release_value(); }));
};/*case end*/
case 94: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Struct>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_446; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL)) } ))));
JaktInternal::Array<u8> trailing_trivia = (TRY((Array<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */))))){
TRY((((trailing_trivia).push(' '))));
}
__jakt_var_446 = formatter::FormattedToken(token,((*this).indent),trailing_trivia,(TRY((Array<u8>::create_with({}))))); goto __jakt_label_406;

}
__jakt_label_406:; __jakt_var_446.release_value(); }));
};/*case end*/
case 75: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Function>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_447; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL)) } ))));
JaktInternal::Array<u8> trailing_trivia = (TRY((Array<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */))))){
TRY((((trailing_trivia).push(' '))));
}
__jakt_var_447 = formatter::FormattedToken(token,((*this).indent),trailing_trivia,(TRY((Array<u8>::create_with({}))))); goto __jakt_label_407;

}
__jakt_label_407:; __jakt_var_447.release_value(); }));
};/*case end*/
case 76: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comptime>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_448; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL)) } ))));
JaktInternal::Array<u8> trailing_trivia = (TRY((Array<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */))))){
TRY((((trailing_trivia).push(' '))));
}
__jakt_var_448 = formatter::FormattedToken(token,((*this).indent),trailing_trivia,(TRY((Array<u8>::create_with({}))))); goto __jakt_label_408;

}
__jakt_label_408:; __jakt_var_448.release_value(); }));
};/*case end*/
case 85: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Namespace>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_449; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL)) } ))));
JaktInternal::Array<u8> trailing_trivia = (TRY((Array<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */))))){
TRY((((trailing_trivia).push(' '))));
}
__jakt_var_449 = formatter::FormattedToken(token,((*this).indent),trailing_trivia,(TRY((Array<u8>::create_with({}))))); goto __jakt_label_409;

}
__jakt_label_409:; __jakt_var_449.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_450; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(open_parens,open_curlies,(JaktInternal::checked_add<size_t>(open_squares,static_cast<size_t>(1ULL)))) } ))));
__jakt_var_450 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_410;

}
__jakt_label_410:; __jakt_var_450.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_451; {
if ((open_squares == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(open_parens,open_curlies,(JaktInternal::checked_sub<size_t>(open_squares,static_cast<size_t>(1ULL)))) } ))));
__jakt_var_451 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_411;

}
__jakt_label_411:; __jakt_var_451.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_452; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel((JaktInternal::checked_add<size_t>(open_parens,static_cast<size_t>(1ULL))),open_curlies,open_squares) } ))));
__jakt_var_452 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_412;

}
__jakt_label_412:; __jakt_var_452.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_453; {
if ((open_parens == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel((JaktInternal::checked_sub<size_t>(open_parens,static_cast<size_t>(1ULL))),open_curlies,open_squares) } ))));
__jakt_var_453 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_413;

}
__jakt_label_413:; __jakt_var_453.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_454; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(open_parens,(JaktInternal::checked_add<size_t>(open_curlies,static_cast<size_t>(1ULL))),open_squares) } ))));
__jakt_var_454 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_414;

}
__jakt_label_414:; __jakt_var_454.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_455; {
if ((open_curlies == static_cast<size_t>(0ULL))){
((*this).pop_state());
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(open_parens,(JaktInternal::checked_sub<size_t>(open_curlies,static_cast<size_t>(1ULL))),open_squares) } ))));
__jakt_var_455 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_415;

}
__jakt_label_415:; __jakt_var_455.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_456; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),true) } ))));
__jakt_var_456 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_416;

}
__jakt_label_416:; __jakt_var_456.release_value(); }));
};/*case end*/
case 78: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Import>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_457; {
TRY((((*this).push_state( formatter::State { typename formatter::State::Import(((((*this).peek(static_cast<i64>(0LL)))).index() == 72 /* Extern */)) } ))));
__jakt_var_457 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_417;

}
__jakt_label_417:; __jakt_var_457.release_value(); }));
};/*case end*/
case 90: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Public>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 89: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Private>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 101: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Virtual>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 88: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Override>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 72: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Extern>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 63: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Boxed>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 93: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Restricted>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_458; {
TRY((((*this).push_state( formatter::State { typename formatter::State::RestrictionList() } ))));
__jakt_var_458 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_418;

}
__jakt_label_418:; __jakt_var_458.release_value(); }));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::Import>();bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 72: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Extern>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 62: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::As>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_459; {
if (((!(is_extern)) && ((((*this).peek(static_cast<i64>(0LL)))).index() == 8 /* LParen */))){
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),JaktInternal::OptionalNone(),false, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,static_cast<size_t>(0ULL)) } ))));
return (formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
}
if (((!(is_extern)) && ((!(((((*this).peek(static_cast<i64>(0LL)))).index() == 10 /* LCurly */))) && (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 62 /* As */)))))){
((*this).pop_state());
}
__jakt_var_459 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_419;

}
__jakt_label_419:; __jakt_var_459.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_460; {
if (is_extern){
TRY((((*this).push_state( formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)) } ))));
}
else {
TRY((((*this).push_state( formatter::State { typename formatter::State::ImportList(true) } ))));
}

__jakt_var_460 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_420;

}
__jakt_label_420:; __jakt_var_460.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_461; {
((*this).pop_state());
__jakt_var_461 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_421;

}
__jakt_label_421:; __jakt_var_461.release_value(); }));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_462; {
__jakt_var_462 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_422;

}
__jakt_label_422:; __jakt_var_462.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::ImportList>();bool const& emitted_comma = __jakt_match_value.emitted_comma;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
{
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_463; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::ImportList(true) } ))));
__jakt_var_463 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_423;

}
__jakt_label_423:; __jakt_var_463.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();{
return (TRY((((*this).next()))));
}
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_464; {
JaktInternal::Array<String> collection = (TRY((Array<String>::create_with({}))));
String output = String("");
utility::Span const span = ((token).span());
while ((!(((token).index() == 11 /* RCurly */)))){
if (((token).index() == 4 /* Identifier */)){
String const name = ((token).get<lexer::Token::Identifier>()).name;
TRY((((collection).push(name))));
}
(token = ((*this).consume()));
}
formatter::bubble_sort(collection);
bool first = true;
bool overflow = false;
size_t current_len = static_cast<size_t>(0ULL);
size_t const indent_amount = static_cast<size_t>(4ULL);
{
JaktInternal::ArrayIterator<String> _magic = ((collection).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String item = (_magic_value.value());
{
if (((JaktInternal::checked_add<size_t>((JaktInternal::checked_add<size_t>(current_len,((item).length()))),static_cast<size_t>(2ULL))) > (JaktInternal::checked_sub<size_t>(static_cast<size_t>(120ULL),indent_amount)))){
(overflow = true);
(output += String("\n"));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(indent_amount)});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(" "));
}

}
}

(current_len = indent_amount);
}
else if ((!(first))){
(output += String(", "));
({auto& _jakt_ref = current_len;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(2ULL));});
}
else {
(first = false);
}

(output += item);
({auto& _jakt_ref = current_len;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, ((item).length()));});
}

}
}

if (overflow){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(indent_amount)});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output = (String(" ") + output));
}

}
}

(output = (String("\n") + output));
(output += String("\n"));
}
else {
(output = ((String(" ") + output) + String(" ")));
}

((*this).pop_state());
((((*this).index)--));
__jakt_var_464 = formatter::FormattedToken( lexer::Token { typename lexer::Token::Identifier(output,span) } ,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_424;

}
__jakt_label_424:; __jakt_var_464.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::EntityDeclaration>();formatter::Entity const& entity = __jakt_match_value.entity;
bool const& accept_generics = __jakt_match_value.accept_generics;
bool const& has_generics = __jakt_match_value.has_generics;
size_t const& generic_nesting = __jakt_match_value.generic_nesting;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_465; {
if (accept_generics){
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDeclaration(entity,accept_generics,true,(JaktInternal::checked_add<size_t>(generic_nesting,static_cast<size_t>(1ULL)))) } ))));
}
__jakt_var_465 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_425;

}
__jakt_label_425:; __jakt_var_465.release_value(); }));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_466; {
if (accept_generics){
if ((generic_nesting > static_cast<size_t>(1ULL))){
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDeclaration(entity,accept_generics,has_generics,(JaktInternal::checked_sub<size_t>(generic_nesting,static_cast<size_t>(1ULL)))) } ))));
}
else {
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDefinition(entity) } ))));
}

}
__jakt_var_466 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_426;

}
__jakt_label_426:; __jakt_var_466.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_467; {
if (((generic_nesting == static_cast<size_t>(0ULL)) && ((!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */))) && (!(has_generics))))){
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDefinition(entity) } ))));
}
__jakt_var_467 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_427;

}
__jakt_label_427:; __jakt_var_467.release_value(); }));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_468; {
((*this).pop_state());
__jakt_var_468 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_428;

}
__jakt_label_428:; __jakt_var_468.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_469; {
((*this).pop_state());
__jakt_var_469 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_429;

}
__jakt_label_429:; __jakt_var_469.release_value(); }));
};/*case end*/
case 90: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Public>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 89: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Private>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 101: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Virtual>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 88: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Override>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 93: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Restricted>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_470; {
TRY((((*this).push_state( formatter::State { typename formatter::State::RestrictionList() } ))));
__jakt_var_470 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_430;

}
__jakt_label_430:; __jakt_var_470.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::EntityDefinition>();formatter::Entity const& entity = __jakt_match_value.entity;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = entity;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::Entity::Enum>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_471; {
((*this).pop_state());
__jakt_var_471 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
))); goto __jakt_label_431;

}
__jakt_label_431:; __jakt_var_471.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_472; {
TRY((((*this).push_state( formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)) } ))));
__jakt_var_472 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_432;

}
__jakt_label_432:; __jakt_var_472.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::Entity::Struct>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_473; {
((*this).pop_state());
__jakt_var_473 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
))); goto __jakt_label_433;

}
__jakt_label_433:; __jakt_var_473.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_474; {
TRY((((*this).push_state( formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)) } ))));
__jakt_var_474 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_434;

}
__jakt_label_434:; __jakt_var_474.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::Entity::Namespace>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_475; {
((*this).pop_state());
__jakt_var_475 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
))); goto __jakt_label_435;

}
__jakt_label_435:; __jakt_var_475.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_476; {
TRY((((*this).push_state( formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)) } ))));
__jakt_var_476 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_436;

}
__jakt_label_436:; __jakt_var_476.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::Entity::Function>();bool const& arrow = __jakt_match_value.arrow;
bool const& indented = __jakt_match_value.indented;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_477; {
bool const next_is_eol = ((((*this).peek(static_cast<i64>(0LL)))).index() == 56 /* Eol */);
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDefinition( formatter::Entity { typename formatter::Entity::Function(true,next_is_eol) } ) } ))));
if (next_is_eol){
if ((!(((*this).already_seen_enclosure_in_current_line)))){
(((*this).already_seen_enclosure_in_current_line) = true);
TRY((((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)))));
}
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, static_cast<i64>(1LL));});
({auto& _jakt_ref = ((((*this).dedents_to_skip))[(JaktInternal::checked_sub<size_t>(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL)))]);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
size_t eols_allowed = static_cast<size_t>(0ULL);
if (next_is_eol){
(eols_allowed = static_cast<size_t>(1ULL));
}
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),eols_allowed,false, formatter::ExpressionMode { typename formatter::ExpressionMode::BeforeExpressions() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_477 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_437;

}
__jakt_label_437:; __jakt_var_477.release_value(); }));
};/*case end*/
case 59: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Arrow>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_478; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_478 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_438;

}
__jakt_label_438:; __jakt_var_478.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_479; {
TRY((((*this).push_state( formatter::State { typename formatter::State::ParameterList(static_cast<size_t>(0ULL)) } ))));
__jakt_var_479 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_439;

}
__jakt_label_439:; __jakt_var_479.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 97: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throws>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
)),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_480; {
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),JaktInternal::OptionalNone(),false, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_480 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_440;

}
__jakt_label_440:; __jakt_var_480.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_481; {
((*this).pop_state());
__jakt_var_481 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_441;

}
__jakt_label_441:; __jakt_var_481.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_482; {
if ((!(arrow))){
return (TRY((((*this).next()))));
}
((*this).pop_state());
if (indented){
if (((((((*this).dedents_to_skip)).last()).value()) == static_cast<size_t>(1ULL))){
if ((((((*this).dedents_to_skip)).size()) > static_cast<size_t>(1ULL))){
JaktInternal::Optional<size_t> const dummy = ((((*this).dedents_to_skip)).pop());
}
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_sub<i64>(_jakt_ref, static_cast<i64>(1LL));});
}
else if (((((((*this).dedents_to_skip)).last()).value()) > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ((((*this).dedents_to_skip))[(JaktInternal::checked_sub<size_t>(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL)))]);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
}
__jakt_var_482 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_442;

}
__jakt_label_442:; __jakt_var_482.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::StatementContext>();size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& arrow_indents = __jakt_match_value.arrow_indents;
JaktInternal::Optional<size_t> const& allow_eol = __jakt_match_value.allow_eol;
bool const& inserted_comma = __jakt_match_value.inserted_comma;
formatter::ExpressionMode const& expression_mode = __jakt_match_value.expression_mode;
size_t const& dedents_on_open_curly = __jakt_match_value.dedents_on_open_curly;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 81: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Let>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_483; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::VariableDeclaration(static_cast<size_t>(0ULL)) } ))));
__jakt_var_483 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_443;

}
__jakt_label_443:; __jakt_var_483.release_value(); }));
};/*case end*/
case 84: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Mut>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_484; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
if (((expression_mode).index() == 0 /* OutsideExpression */)){
TRY((((*this).push_state( formatter::State { typename formatter::State::VariableDeclaration(static_cast<size_t>(0ULL)) } ))));
}
__jakt_var_484 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_444;

}
__jakt_label_444:; __jakt_var_484.release_value(); }));
};/*case end*/
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_485; {
size_t const added_indent = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_486; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_486 = indent; goto __jakt_label_446;

}
__jakt_label_446:; __jakt_var_486.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_487; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_487 = indent; goto __jakt_label_447;

}
__jakt_label_447:; __jakt_var_487.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_488; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_488 = indent; goto __jakt_label_448;

}
__jakt_label_448:; __jakt_var_488.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_489; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_489 = indent; goto __jakt_label_449;

}
__jakt_label_449:; __jakt_var_489.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_490; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_490 = indent; goto __jakt_label_450;

}
__jakt_label_450:; __jakt_var_490.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_add<size_t>(dedents_on_open_curly,added_indent))) } ))));
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, (infallible_integer_cast<i64>((added_indent))));});
__jakt_var_485 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_445;

}
__jakt_label_445:; __jakt_var_485.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_491; {
size_t const added_indent = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_492; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_492 = indent; goto __jakt_label_452;

}
__jakt_label_452:; __jakt_var_492.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_493; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_493 = indent; goto __jakt_label_453;

}
__jakt_label_453:; __jakt_var_493.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_494; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_494 = indent; goto __jakt_label_454;

}
__jakt_label_454:; __jakt_var_494.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_495; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_495 = indent; goto __jakt_label_455;

}
__jakt_label_455:; __jakt_var_495.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_496; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_496 = indent; goto __jakt_label_456;

}
__jakt_label_456:; __jakt_var_496.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_add<size_t>(dedents_on_open_curly,added_indent))) } ))));
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, (infallible_integer_cast<i64>((added_indent))));});
__jakt_var_491 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_451;

}
__jakt_label_451:; __jakt_var_491.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_497; {
size_t const added_indent = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_498; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_498 = indent; goto __jakt_label_458;

}
__jakt_label_458:; __jakt_var_498.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_499; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_499 = indent; goto __jakt_label_459;

}
__jakt_label_459:; __jakt_var_499.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_500; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_500 = indent; goto __jakt_label_460;

}
__jakt_label_460:; __jakt_var_500.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_501; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_501 = indent; goto __jakt_label_461;

}
__jakt_label_461:; __jakt_var_501.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_502; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_502 = indent; goto __jakt_label_462;

}
__jakt_label_462:; __jakt_var_502.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_add<size_t>(dedents_on_open_curly,added_indent))) } ))));
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, (infallible_integer_cast<i64>((added_indent))));});
__jakt_var_497 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_457;

}
__jakt_label_457:; __jakt_var_497.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_503; {
size_t const added_indent = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_504; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_504 = indent; goto __jakt_label_464;

}
__jakt_label_464:; __jakt_var_504.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_505; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_505 = indent; goto __jakt_label_465;

}
__jakt_label_465:; __jakt_var_505.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_506; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_506 = indent; goto __jakt_label_466;

}
__jakt_label_466:; __jakt_var_506.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_507; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_507 = indent; goto __jakt_label_467;

}
__jakt_label_467:; __jakt_var_507.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_508; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_508 = indent; goto __jakt_label_468;

}
__jakt_label_468:; __jakt_var_508.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_add<size_t>(dedents_on_open_curly,added_indent))) } ))));
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, (infallible_integer_cast<i64>((added_indent))));});
__jakt_var_503 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_463;

}
__jakt_label_463:; __jakt_var_503.release_value(); }));
};/*case end*/
case 99: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Try>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_509; {
size_t const added_indent = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_510; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_510 = indent; goto __jakt_label_470;

}
__jakt_label_470:; __jakt_var_510.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_511; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_511 = indent; goto __jakt_label_471;

}
__jakt_label_471:; __jakt_var_511.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_512; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_512 = indent; goto __jakt_label_472;

}
__jakt_label_472:; __jakt_var_512.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_513; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_513 = indent; goto __jakt_label_473;

}
__jakt_label_473:; __jakt_var_513.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_514; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_514 = indent; goto __jakt_label_474;

}
__jakt_label_474:; __jakt_var_514.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_add<size_t>(dedents_on_open_curly,added_indent))) } ))));
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, (infallible_integer_cast<i64>((added_indent))));});
__jakt_var_509 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_469;

}
__jakt_label_469:; __jakt_var_509.release_value(); }));
};/*case end*/
case 82: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Loop>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_515; {
size_t const added_indent = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_516; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_516 = indent; goto __jakt_label_476;

}
__jakt_label_476:; __jakt_var_516.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_517; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_517 = indent; goto __jakt_label_477;

}
__jakt_label_477:; __jakt_var_517.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_518; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_518 = indent; goto __jakt_label_478;

}
__jakt_label_478:; __jakt_var_518.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_519; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_519 = indent; goto __jakt_label_479;

}
__jakt_label_479:; __jakt_var_519.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_520; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_520 = indent; goto __jakt_label_480;

}
__jakt_label_480:; __jakt_var_520.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_add<size_t>(dedents_on_open_curly,added_indent))) } ))));
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, (infallible_integer_cast<i64>((added_indent))));});
__jakt_var_515 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_475;

}
__jakt_label_475:; __jakt_var_515.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_521; {
size_t const added_indent = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_522; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_522 = indent; goto __jakt_label_482;

}
__jakt_label_482:; __jakt_var_522.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_523; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_523 = indent; goto __jakt_label_483;

}
__jakt_label_483:; __jakt_var_523.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_524; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_524 = indent; goto __jakt_label_484;

}
__jakt_label_484:; __jakt_var_524.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_525; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_525 = indent; goto __jakt_label_485;

}
__jakt_label_485:; __jakt_var_525.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_526; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_526 = indent; goto __jakt_label_486;

}
__jakt_label_486:; __jakt_var_526.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_add<size_t>(dedents_on_open_curly,added_indent))) } ))));
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, (infallible_integer_cast<i64>((added_indent))));});
__jakt_var_521 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_481;

}
__jakt_label_481:; __jakt_var_521.release_value(); }));
};/*case end*/
case 69: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Defer>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_527; {
size_t const added_indent = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_528; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_528 = indent; goto __jakt_label_488;

}
__jakt_label_488:; __jakt_var_528.release_value(); }));
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_529; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_529 = indent; goto __jakt_label_489;

}
__jakt_label_489:; __jakt_var_529.release_value(); }));
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_530; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_530 = indent; goto __jakt_label_490;

}
__jakt_label_490:; __jakt_var_530.release_value(); }));
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_531; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_531 = indent; goto __jakt_label_491;

}
__jakt_label_491:; __jakt_var_531.release_value(); }));
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_532; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_532 = indent; goto __jakt_label_492;

}
__jakt_label_492:; __jakt_var_532.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_add<size_t>(dedents_on_open_curly,added_indent))) } ))));
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, (infallible_integer_cast<i64>((added_indent))));});
__jakt_var_527 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_487;

}
__jakt_label_487:; __jakt_var_527.release_value(); }));
};/*case end*/
case 65: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Catch>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_533; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_533 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
))); goto __jakt_label_493;

}
__jakt_label_493:; __jakt_var_533.release_value(); }));
};/*case end*/
case 70: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Else>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_534; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_534 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
))); goto __jakt_label_494;

}
__jakt_label_494:; __jakt_var_534.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_535; {
if ((((expression_mode).index() == 1 /* BeforeExpressions */) && ((((*this).peek(static_cast<i64>(0LL)))).index() == 56 /* Eol */))){
return (TRY((((*this).next()))));
}
if ((((allow_eol).has_value()) && (((allow_eol.value()) == static_cast<size_t>(0ULL)) && ((JaktInternal::checked_add<size_t>((JaktInternal::checked_add<size_t>(open_parens,open_curlies)),open_squares)) == static_cast<size_t>(0ULL))))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
size_t new_arrow_indents = arrow_indents;
JaktInternal::Optional<size_t> new_allow_eol = allow_eol;
formatter::ExpressionMode new_expression_mode =  formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ;
if (((expression_mode).index() == 1 /* BeforeExpressions */)){
(new_expression_mode =  formatter::ExpressionMode { typename formatter::ExpressionMode::BeforeExpressions() } );
}
else {
if ((((allow_eol).has_value()) && ((allow_eol.value()) > static_cast<size_t>(0ULL)))){
(new_allow_eol = (JaktInternal::checked_sub<size_t>((allow_eol.value()),static_cast<size_t>(1ULL))));
}
if ((arrow_indents > static_cast<size_t>(0ULL))){
if (((((((*this).dedents_to_skip)).last()).value()) == static_cast<size_t>(1ULL))){
if ((((((*this).dedents_to_skip)).size()) > static_cast<size_t>(1ULL))){
JaktInternal::Optional<size_t> const dummy = ((((*this).dedents_to_skip)).pop());
}
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_sub<i64>(_jakt_ref, static_cast<i64>(1LL));});
}
else if (((((((*this).dedents_to_skip)).last()).value()) > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ((((*this).dedents_to_skip))[(JaktInternal::checked_sub<size_t>(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL)))]);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
((new_arrow_indents--));
}
}

TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,new_arrow_indents,new_allow_eol,inserted_comma,new_expression_mode,dedents_on_open_curly) } ))));
__jakt_var_535 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_495;

}
__jakt_label_495:; __jakt_var_535.release_value(); }));
};/*case end*/
case 75: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Function>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_536; {
TRY((((*this).push_state( formatter::State { typename formatter::State::FunctionTypeContext(false) } ))));
__jakt_var_536 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_496;

}
__jakt_label_496:; __jakt_var_536.release_value(); }));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<formatter::FormattedToken>> __jakt_var_537; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_537 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)); goto __jakt_label_497;

}
__jakt_label_497:; __jakt_var_537.release_value(); }));
};/*case end*/
case 92: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Return>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Semicolon>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_538; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_538 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_498;

}
__jakt_label_498:; __jakt_var_538.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_539; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_539 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_499;

}
__jakt_label_499:; __jakt_var_539.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_540; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_540 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_500;

}
__jakt_label_500:; __jakt_var_540.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 96: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throw>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Semicolon>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_541; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_541 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_501;

}
__jakt_label_501:; __jakt_var_541.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_542; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_542 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_502;

}
__jakt_label_502:; __jakt_var_542.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_543; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_543 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_503;

}
__jakt_label_503:; __jakt_var_543.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 104: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Yield>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Semicolon>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_544; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_544 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_504;

}
__jakt_label_504:; __jakt_var_544.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_545; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_545 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_505;

}
__jakt_label_505:; __jakt_var_545.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_546; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_546 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_506;

}
__jakt_label_506:; __jakt_var_546.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_547; {
bool const next_is_eol = ((((*this).peek(static_cast<i64>(0LL)))).index() == 56 /* Eol */);
size_t new_arrow_indents = arrow_indents;
if (next_is_eol){
if ((!(((*this).already_seen_enclosure_in_current_line)))){
(((*this).already_seen_enclosure_in_current_line) = true);
TRY((((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)))));
}
({auto& _jakt_ref = indent_change;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, static_cast<i64>(1LL));});
({auto& _jakt_ref = ((((*this).dedents_to_skip))[(JaktInternal::checked_sub<size_t>(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL)))]);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
((new_arrow_indents++));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,new_arrow_indents,allow_eol,inserted_comma,JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<formatter::ExpressionMode, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue( formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::ExpressionMode { typename formatter::ExpressionMode::BeforeExpressions() } );
};/*case end*/
}/*switch end*/
}()
)),dedents_on_open_curly) } ))));
__jakt_var_547 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_507;

}
__jakt_label_507:; __jakt_var_547.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_548; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,(JaktInternal::checked_add<size_t>(open_squares,static_cast<size_t>(1ULL))),arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_548 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_508;

}
__jakt_label_508:; __jakt_var_548.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_549; {
if ((open_squares == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,(JaktInternal::checked_sub<size_t>(open_squares,static_cast<size_t>(1ULL))),arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_549 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_509;

}
__jakt_label_509:; __jakt_var_549.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_550; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext((JaktInternal::checked_add<size_t>(open_parens,static_cast<size_t>(1ULL))),open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_550 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_510;

}
__jakt_label_510:; __jakt_var_550.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_551; {
if ((open_parens == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext((JaktInternal::checked_sub<size_t>(open_parens,static_cast<size_t>(1ULL))),open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_551 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_511;

}
__jakt_label_511:; __jakt_var_551.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_552; {
size_t dedented = static_cast<size_t>(0ULL);
if ((dedents_on_open_curly > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ((*this).indent);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
(dedented = static_cast<size_t>(1ULL));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,(JaktInternal::checked_add<size_t>(open_curlies,static_cast<size_t>(1ULL))),open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,(JaktInternal::checked_sub<size_t>(dedents_on_open_curly,dedented))) } ))));
__jakt_var_552 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::ExpressionMode::AtExpressionStart>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::ExpressionMode::BeforeExpressions>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
}/*switch end*/
}()
)),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 70: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Else>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 99: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Try>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 65: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Catch>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 82: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Loop>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 69: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Defer>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
))); goto __jakt_label_512;

}
__jakt_label_512:; __jakt_var_552.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_553; {
if ((open_curlies == static_cast<size_t>(0ULL))){
((*this).pop_state());
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,(JaktInternal::checked_sub<size_t>(open_curlies,static_cast<size_t>(1ULL))),open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_553 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
))); goto __jakt_label_513;

}
__jakt_label_513:; __jakt_var_553.release_value(); }));
};/*case end*/
case 86: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Not>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_554; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_554 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_514;

}
__jakt_label_514:; __jakt_var_554.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_555; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_555 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_515;

}
__jakt_label_515:; __jakt_var_555.release_value(); }));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Minus>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_556; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
JaktInternal::Array<u8> const trivia = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::ExpressionMode::InExpression>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
));
__jakt_var_556 = formatter::FormattedToken(token,((*this).indent),trivia,trivia); goto __jakt_label_516;

}
__jakt_label_516:; __jakt_var_556.release_value(); }));
};/*case end*/
case 37: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Asterisk>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_557; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
JaktInternal::Array<u8> const trivia = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::ExpressionMode::InExpression>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
));
__jakt_var_557 = formatter::FormattedToken(token,((*this).indent),trivia,trivia); goto __jakt_label_517;

}
__jakt_label_517:; __jakt_var_557.release_value(); }));
};/*case end*/
case 38: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Ampersand>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_558; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
JaktInternal::Array<u8> const trivia = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::ExpressionMode::InExpression>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
));
__jakt_var_558 = formatter::FormattedToken(token,((*this).indent),trivia,trivia); goto __jakt_label_518;

}
__jakt_label_518:; __jakt_var_558.release_value(); }));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSign>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_559; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_559 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_519;

}
__jakt_label_519:; __jakt_var_559.release_value(); }));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Plus>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_560; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_560 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_520;

}
__jakt_label_520:; __jakt_var_560.release_value(); }));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_561; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_561 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_521;

}
__jakt_label_521:; __jakt_var_561.release_value(); }));
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_562; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_562 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_522;

}
__jakt_label_522:; __jakt_var_562.release_value(); }));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_563; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_563 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_523;

}
__jakt_label_523:; __jakt_var_563.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_564; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_564 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_524;

}
__jakt_label_524:; __jakt_var_564.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AsteriskEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_565; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_565 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_525;

}
__jakt_label_525:; __jakt_var_565.release_value(); }));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlashEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_566; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_566 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_526;

}
__jakt_label_526:; __jakt_var_566.release_value(); }));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSignEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_567; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_567 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_527;

}
__jakt_label_527:; __jakt_var_567.release_value(); }));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::NotEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_568; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_568 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_528;

}
__jakt_label_528:; __jakt_var_568.release_value(); }));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DoubleEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_569; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_569 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_529;

}
__jakt_label_529:; __jakt_var_569.release_value(); }));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_570; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_570 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_530;

}
__jakt_label_530:; __jakt_var_570.release_value(); }));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThanOrEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_571; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_571 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_531;

}
__jakt_label_531:; __jakt_var_571.release_value(); }));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_572; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_572 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_532;

}
__jakt_label_532:; __jakt_var_572.release_value(); }));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThanOrEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_573; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_573 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_533;

}
__jakt_label_533:; __jakt_var_573.release_value(); }));
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftArithmeticShift>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_574; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_574 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_534;

}
__jakt_label_534:; __jakt_var_574.release_value(); }));
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShift>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_575; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_575 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_535;

}
__jakt_label_535:; __jakt_var_575.release_value(); }));
};/*case end*/
case 34: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShift>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_576; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_576 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_536;

}
__jakt_label_536:; __jakt_var_576.release_value(); }));
};/*case end*/
case 33: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShiftEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_577; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_577 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_537;

}
__jakt_label_537:; __jakt_var_577.release_value(); }));
};/*case end*/
case 35: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightArithmeticShift>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_578; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_578 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_538;

}
__jakt_label_538:; __jakt_var_578.release_value(); }));
};/*case end*/
case 36: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShiftEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_579; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_579 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_539;

}
__jakt_label_539:; __jakt_var_579.release_value(); }));
};/*case end*/
case 39: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_580; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_580 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_540;

}
__jakt_label_540:; __jakt_var_580.release_value(); }));
};/*case end*/
case 42: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipeEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_581; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_581 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_541;

}
__jakt_label_541:; __jakt_var_581.release_value(); }));
};/*case end*/
case 44: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Caret>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_582; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_582 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_542;

}
__jakt_label_542:; __jakt_var_582.release_value(); }));
};/*case end*/
case 45: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::CaretEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_583; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_583 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_543;

}
__jakt_label_543:; __jakt_var_583.release_value(); }));
};/*case end*/
case 48: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlash>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_584; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_584 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_544;

}
__jakt_label_544:; __jakt_var_584.release_value(); }));
};/*case end*/
case 51: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMark>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_585; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_585 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_545;

}
__jakt_label_545:; __jakt_var_585.release_value(); }));
};/*case end*/
case 52: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMarkEqual>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_586; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_586 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_546;

}
__jakt_label_546:; __jakt_var_586.release_value(); }));
};/*case end*/
case 60: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::And>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_587; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_587 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_547;

}
__jakt_label_547:; __jakt_var_587.release_value(); }));
};/*case end*/
case 79: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::In>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_588; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_588 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_548;

}
__jakt_label_548:; __jakt_var_588.release_value(); }));
};/*case end*/
case 87: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Or>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_589; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_589 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_549;

}
__jakt_label_549:; __jakt_var_589.release_value(); }));
};/*case end*/
case 80: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Is>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_590; {
TRY((((*this).push_state( formatter::State { typename formatter::State::MatchPattern(static_cast<size_t>(0ULL),false) } ))));
__jakt_var_590 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_550;

}
__jakt_label_550:; __jakt_var_590.release_value(); }));
};/*case end*/
case 62: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::As>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 50: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMark>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
case 49: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ExclamationPoint>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
}/*switch end*/
}()
)),(TRY((Array<u8>::create_with({' '}))))));
};/*case end*/
case 50: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMark>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 62: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::As>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_591; {
__jakt_var_591 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_551;

}
__jakt_label_551:; __jakt_var_591.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 49: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ExclamationPoint>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 62: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::As>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_592; {
__jakt_var_592 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_552;

}
__jakt_label_552:; __jakt_var_592.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_593; {
if ((((((*this).peek((-(static_cast<i64>(1LL)))))).index() == 4 /* Identifier */) && (!(inserted_comma)))){
((((*this).index)--));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,true, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
return (formatter::FormattedToken( lexer::Token { typename lexer::Token::Comma(((token).span())) } ,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,false, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
if (((((*this).peek(static_cast<i64>(0LL)))).index() == 8 /* LParen */)){
return (formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
}
if ((!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */)))){
return (formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
}
i64 open_angles = static_cast<i64>(1LL);
i64 lookahead_index = static_cast<i64>(2LL);
while ((open_angles > static_cast<i64>(0LL))){
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(((lookahead_index++))));
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
{
({auto& _jakt_ref = open_angles;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, static_cast<i64>(1LL));});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
{
({auto& _jakt_ref = open_angles;_jakt_ref = JaktInternal::checked_sub<i64>(_jakt_ref, static_cast<i64>(1LL));});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSign>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Plus>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Minus>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AsteriskEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlashEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSignEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::NotEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DoubleEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThanOrEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThanOrEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftArithmeticShift>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShift>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShift>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShiftEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightArithmeticShift>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShiftEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 37: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Asterisk>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 39: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 42: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipeEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Caret>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 45: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::CaretEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 48: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlash>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMark>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMarkEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::And>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::In>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Is>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Or>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
if (((open_angles == static_cast<i64>(0LL)) && ((((*this).peek(lookahead_index))).index() == 8 /* LParen */))){
TRY((((*this).push_state( formatter::State { typename formatter::State::GenericCallTypeParams(static_cast<size_t>(0ULL)) } ))));
}
__jakt_var_593 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_553;

}
__jakt_label_553:; __jakt_var_593.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Number>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_594; {
if ((((((*this).peek((-(static_cast<i64>(1LL)))))).index() == 4 /* Identifier */) && (!(inserted_comma)))){
((((*this).index)--));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,true, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
return (formatter::FormattedToken( lexer::Token { typename lexer::Token::Comma(((token).span())) } ,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,false, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
if (((((*this).peek(static_cast<i64>(0LL)))).index() == 8 /* LParen */)){
return (formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
}
if ((!(((((*this).peek(static_cast<i64>(0LL)))).index() == 29 /* LessThan */)))){
return (formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
}
i64 open_angles = static_cast<i64>(1LL);
i64 lookahead_index = static_cast<i64>(2LL);
while ((open_angles > static_cast<i64>(0LL))){
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(((lookahead_index++))));
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
{
({auto& _jakt_ref = open_angles;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, static_cast<i64>(1LL));});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
{
({auto& _jakt_ref = open_angles;_jakt_ref = JaktInternal::checked_sub<i64>(_jakt_ref, static_cast<i64>(1LL));});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSign>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Plus>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Minus>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AsteriskEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlashEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSignEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::NotEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DoubleEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThanOrEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThanOrEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftArithmeticShift>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShift>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShift>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShiftEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightArithmeticShift>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShiftEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 37: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Asterisk>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 39: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 42: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipeEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Caret>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 45: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::CaretEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 48: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlash>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMark>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMarkEqual>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::And>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::In>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Is>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Or>();
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
if (((open_angles == static_cast<i64>(0LL)) && ((((*this).peek(lookahead_index))).index() == 8 /* LParen */))){
TRY((((*this).push_state( formatter::State { typename formatter::State::GenericCallTypeParams(static_cast<size_t>(0ULL)) } ))));
}
__jakt_var_594 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_554;

}
__jakt_label_554:; __jakt_var_594.release_value(); }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Semicolon>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_595; {
if ((open_squares == static_cast<size_t>(0ULL))){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(TRY((((*this).next()))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken( lexer::Token { typename lexer::Token::Eol(JaktInternal::OptionalNone(),((token).span())) } ,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
}
__jakt_var_595 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_555;

}
__jakt_label_555:; __jakt_var_595.release_value(); }));
};/*case end*/
case 91: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Raw>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_596; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_596 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_556;

}
__jakt_label_556:; __jakt_var_596.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_597; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_597 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_557;

}
__jakt_label_557:; __jakt_var_597.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::GenericCallTypeParams>();size_t const& open_angles = __jakt_match_value.open_angles;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_598; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_598 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_558;

}
__jakt_label_558:; __jakt_var_598.release_value(); }));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_599; {
if ((open_angles <= static_cast<size_t>(1ULL))){
((*this).pop_state());
}
else {
TRY((((*this).replace_state( formatter::State { typename formatter::State::GenericCallTypeParams((JaktInternal::checked_sub<size_t>(open_angles,static_cast<size_t>(1ULL)))) } ))));
}

__jakt_var_599 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_559;

}
__jakt_label_559:; __jakt_var_599.release_value(); }));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_600; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_600 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_560;

}
__jakt_label_560:; __jakt_var_600.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::VariableDeclaration>();size_t const& open_parens = __jakt_match_value.open_parens;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_601; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_601 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_561;

}
__jakt_label_561:; __jakt_var_601.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_602; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::VariableDeclaration((JaktInternal::checked_add<size_t>(open_parens,static_cast<size_t>(1ULL)))) } ))));
__jakt_var_602 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_562;

}
__jakt_label_562:; __jakt_var_602.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_603; {
if ((open_parens == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::VariableDeclaration((JaktInternal::checked_sub<size_t>(open_parens,static_cast<size_t>(1ULL)))) } ))));
__jakt_var_603 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_563;

}
__jakt_label_563:; __jakt_var_603.release_value(); }));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_604; {
((*this).pop_state());
__jakt_var_604 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_564;

}
__jakt_label_564:; __jakt_var_604.release_value(); }));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::State::RestrictionList>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_605; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_605 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_565;

}
__jakt_label_565:; __jakt_var_605.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_606; {
((*this).pop_state());
__jakt_var_606 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_566;

}
__jakt_label_566:; __jakt_var_606.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::ParameterList>();size_t const& open_parens = __jakt_match_value.open_parens;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 61: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Anon>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 84: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Mut>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_607; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_607 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_567;

}
__jakt_label_567:; __jakt_var_607.release_value(); }));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_608; {
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_608 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_568;

}
__jakt_label_568:; __jakt_var_608.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_609; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::ParameterList((JaktInternal::checked_add<size_t>(open_parens,static_cast<size_t>(1ULL)))) } ))));
__jakt_var_609 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_569;

}
__jakt_label_569:; __jakt_var_609.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_610; {
if ((open_parens == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::ParameterList((JaktInternal::checked_sub<size_t>(open_parens,static_cast<size_t>(1ULL)))) } ))));
__jakt_var_610 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_570;

}
__jakt_label_570:; __jakt_var_610.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::TypeContext>();size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& open_angles = __jakt_match_value.open_angles;
bool const& seen_start = __jakt_match_value.seen_start;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_611; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,(JaktInternal::checked_add<size_t>(open_angles,static_cast<size_t>(1ULL))),seen_start) } ))));
__jakt_var_611 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_571;

}
__jakt_label_571:; __jakt_var_611.release_value(); }));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_612; {
if ((open_angles == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,(JaktInternal::checked_sub<size_t>(open_angles,static_cast<size_t>(1ULL))),seen_start) } ))));
__jakt_var_612 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_572;

}
__jakt_label_572:; __jakt_var_612.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_613; {
if (((JaktInternal::checked_add<size_t>((JaktInternal::checked_add<size_t>((JaktInternal::checked_add<size_t>(open_parens,open_curlies)),open_squares)),open_angles)) == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
__jakt_var_613 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_573;

}
__jakt_label_573:; __jakt_var_613.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_614; {
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,(JaktInternal::checked_add<size_t>(open_squares,static_cast<size_t>(1ULL))),open_angles,true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_614 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_574;

}
__jakt_label_574:; __jakt_var_614.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_615; {
if ((open_squares == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,(JaktInternal::checked_sub<size_t>(open_squares,static_cast<size_t>(1ULL))),open_angles,seen_start) } ))));
__jakt_var_615 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_575;

}
__jakt_label_575:; __jakt_var_615.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_616; {
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext((JaktInternal::checked_add<size_t>(open_parens,static_cast<size_t>(1ULL))),open_curlies,open_squares,open_angles,true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_616 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_576;

}
__jakt_label_576:; __jakt_var_616.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_617; {
if ((open_parens == static_cast<size_t>(0ULL))){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext((JaktInternal::checked_sub<size_t>(open_parens,static_cast<size_t>(1ULL))),open_curlies,open_squares,open_angles,seen_start) } ))));
__jakt_var_617 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_577;

}
__jakt_label_577:; __jakt_var_617.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_618; {
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,(JaktInternal::checked_add<size_t>(open_curlies,static_cast<size_t>(1ULL))),open_squares,open_angles,true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_618 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_578;

}
__jakt_label_578:; __jakt_var_618.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_619; {
if ((open_curlies == static_cast<size_t>(0ULL))){
((*this).pop_state());
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,(JaktInternal::checked_sub<size_t>(open_curlies,static_cast<size_t>(1ULL))),open_squares,open_angles,seen_start) } ))));
__jakt_var_619 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_579;

}
__jakt_label_579:; __jakt_var_619.release_value(); }));
};/*case end*/
case 91: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Raw>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_620; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
__jakt_var_620 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_580;

}
__jakt_label_580:; __jakt_var_620.release_value(); }));
};/*case end*/
case 84: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Mut>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_621; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
__jakt_var_621 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_581;

}
__jakt_label_581:; __jakt_var_621.release_value(); }));
};/*case end*/
case 38: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Ampersand>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_622; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
__jakt_var_622 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_582;

}
__jakt_label_582:; __jakt_var_622.release_value(); }));
};/*case end*/
case 75: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Function>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_623; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::FunctionTypeContext(false) } ))));
__jakt_var_623 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_583;

}
__jakt_label_583:; __jakt_var_623.release_value(); }));
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_624; {
if (((JaktInternal::checked_add<size_t>(open_angles,open_parens)) == static_cast<size_t>(0ULL))){
((((*this).index)--));
((*this).pop_state());
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_624 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_584;

}
__jakt_label_584:; __jakt_var_624.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_625; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
__jakt_var_625 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_585;

}
__jakt_label_585:; __jakt_var_625.release_value(); }));
};/*case end*/
case 102: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Weak>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_626; {
__jakt_var_626 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_586;

}
__jakt_label_586:; __jakt_var_626.release_value(); }));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
{
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
};/*case end*/
case 59: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Arrow>();
{
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
};/*case end*/
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
{
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
};/*case end*/
default: {
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::FunctionTypeContext>();bool const& seen_final_type = __jakt_match_value.seen_final_type;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
{
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
{
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
};/*case end*/
case 59: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Arrow>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_627; {
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::FunctionTypeContext(true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_627 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_587;

}
__jakt_label_587:; __jakt_var_627.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_628; {
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).push_state( formatter::State { typename formatter::State::ParameterList(static_cast<size_t>(0ULL)) } ))));
__jakt_var_628 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_588;

}
__jakt_label_588:; __jakt_var_628.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_629; {
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
__jakt_var_629 = formatter::FormattedToken(token,((*this).indent),JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 97: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throws>();
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({' '})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
)),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_589;

}
__jakt_label_589:; __jakt_var_629.release_value(); }));
};/*case end*/
case 97: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throws>();
return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_630; {
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return (TRY((((*this).next_impl(true)))));
}
__jakt_var_630 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_590;

}
__jakt_label_590:; __jakt_var_630.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::MatchPattern>();size_t const& open_parens = __jakt_match_value.open_parens;
bool const& allow_multiple = __jakt_match_value.allow_multiple;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_631; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::MatchPattern((JaktInternal::checked_add<size_t>(open_parens,static_cast<size_t>(1ULL))),allow_multiple) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_631 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_591;

}
__jakt_label_591:; __jakt_var_631.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_632; {
if ((open_parens == static_cast<size_t>(0ULL))){
((*this).pop_state());
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
return (TRY((((*this).next_impl(true)))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::MatchPattern((JaktInternal::checked_sub<size_t>(open_parens,static_cast<size_t>(1ULL))),allow_multiple) } ))));
__jakt_var_632 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_592;

}
__jakt_label_592:; __jakt_var_632.release_value(); }));
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_633; {
if ((!(allow_multiple))){
((*this).pop_state());
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
return (TRY((((*this).next_impl(true)))));
}
__jakt_var_633 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))); goto __jakt_label_593;

}
__jakt_label_593:; __jakt_var_633.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();return JaktInternal::ExplicitValue(formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({})))),(TRY((Array<u8>::create_with({}))))));
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_634; {
if ((!(allow_multiple))){
((*this).pop_state());
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
return (TRY((((*this).next_impl(true)))));
}
__jakt_var_634 = formatter::FormattedToken(token,((*this).indent),(TRY((Array<u8>::create_with({' '})))),(TRY((Array<u8>::create_with({' '}))))); goto __jakt_label_594;

}
__jakt_label_594:; __jakt_var_634.release_value(); }));
};/*case end*/
default: {
{
((*this).pop_state());
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
return (TRY((((*this).next_impl(true)))));
}
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

lexer::Token formatter::Stage0::peek(i64 const offset) const {
{
size_t const effective_index = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,lexer::Token>{
auto __jakt_enum_value = (offset);
if (__jakt_enum_value == static_cast<i64>(0LL)) {
return JaktInternal::ExplicitValue(((*this).index));
}
else {
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>(((JaktInternal::checked_sub<i64>((JaktInternal::checked_add<i64>((infallible_integer_cast<i64>((((*this).index)))),offset)),static_cast<i64>(1LL)))))));
}
}()))
;
if ((effective_index >= ((((*this).tokens)).size()))){
return ( lexer::Token { typename lexer::Token::Eof((((((((*this).tokens)).last()).value())).span())) } );
}
return (((((*this).tokens))[effective_index]));
}
}

bool formatter::Stage0::line_has_indent() const {
{
i64 offset = static_cast<i64>(0LL);
for (;;){
lexer::Token const token = ((*this).peek(offset));
if (((token).index() == 10 /* LCurly */)){
return (true);
}
if ((((token).index() == 56 /* Eol */) || ((token).index() == 57 /* Eof */))){
break;
}
((offset++));
}
return (false);
}
}

ErrorOr<JaktInternal::Array<u8>> formatter::Stage0::to_array(String const x) {
{
JaktInternal::Array<u8> res = (TRY((Array<u8>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((x).length()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((res).push(((x).byte_at(i))))));
}

}
}

return (res);
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::formatted_peek() {
{
JaktInternal::Array<formatter::State> const states_cache = TRY((((((((*this).states))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})])).to_array())));
size_t const index_cache = ((*this).index);
JaktInternal::Optional<formatter::FormattedToken> const token = TRY((((*this).next_impl(true))));
(((*this).index) = index_cache);
(((*this).states) = states_cache);
return (token);
}
}

void formatter::Stage0::pop_state() {
{
JaktInternal::Optional<formatter::State> const dummy = ((((*this).states)).pop());
}
}

formatter::Stage0::Stage0(JaktInternal::Array<lexer::Token> a_tokens, size_t a_index, JaktInternal::Array<formatter::State> a_states, size_t a_indent, bool a_already_seen_enclosure_in_current_line, JaktInternal::Array<size_t> a_dedents_to_skip, bool a_debug) :tokens(a_tokens), index(a_index), states(a_states), indent(a_indent), already_seen_enclosure_in_current_line(a_already_seen_enclosure_in_current_line), dedents_to_skip(a_dedents_to_skip), debug(a_debug){}

lexer::Token formatter::Stage0::consume() {
{
return (((((*this).tokens))[((((*this).index)++))]));
}
}

ErrorOr<String> formatter::BreakablePoint::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Paren */: {
[[maybe_unused]] auto const& that = this->template get<BreakablePoint::Paren>();
TRY(builder.append("BreakablePoint::Paren"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("point: {}", that.point));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("length: {}", that.length));
}
TRY(builder.append(")"));
break;}
case 1 /* Curly */: {
[[maybe_unused]] auto const& that = this->template get<BreakablePoint::Curly>();
TRY(builder.append("BreakablePoint::Curly"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("point: {}", that.point));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("length: {}", that.length));
}
TRY(builder.append(")"));
break;}
case 2 /* Square */: {
[[maybe_unused]] auto const& that = this->template get<BreakablePoint::Square>();
TRY(builder.append("BreakablePoint::Square"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("point: {}", that.point));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("length: {}", that.length));
}
TRY(builder.append(")"));
break;}
case 3 /* Logical */: {
[[maybe_unused]] auto const& that = this->template get<BreakablePoint::Logical>();
TRY(builder.append("BreakablePoint::Logical"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("point: {}", that.point));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("length: {}", that.length));
}
TRY(builder.append(")"));
break;}
}
return builder.to_string();
}
size_t formatter::BreakablePoint::length() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::BreakablePoint::Paren>();size_t const& length = __jakt_match_value.length;
return JaktInternal::ExplicitValue(length);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::BreakablePoint::Curly>();size_t const& length = __jakt_match_value.length;
return JaktInternal::ExplicitValue(length);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::BreakablePoint::Square>();size_t const& length = __jakt_match_value.length;
return JaktInternal::ExplicitValue(length);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::BreakablePoint::Logical>();size_t const& length = __jakt_match_value.length;
return JaktInternal::ExplicitValue(length);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

size_t formatter::BreakablePoint::point() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::BreakablePoint::Paren>();size_t const& point = __jakt_match_value.point;
return JaktInternal::ExplicitValue(point);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::BreakablePoint::Curly>();size_t const& point = __jakt_match_value.point;
return JaktInternal::ExplicitValue(point);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::BreakablePoint::Square>();size_t const& point = __jakt_match_value.point;
return JaktInternal::ExplicitValue(point);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::BreakablePoint::Logical>();size_t const& point = __jakt_match_value.point;
return JaktInternal::ExplicitValue(point);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> formatter::State::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Toplevel */: {
[[maybe_unused]] auto const& that = this->template get<State::Toplevel>();
TRY(builder.append("State::Toplevel"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}", that.open_parens));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_curlies: {}", that.open_curlies));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_squares: {}", that.open_squares));
}
TRY(builder.append(")"));
break;}
case 1 /* Import */: {
[[maybe_unused]] auto const& that = this->template get<State::Import>();
TRY(builder.append("State::Import"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_extern: {}", that.is_extern));
}
TRY(builder.append(")"));
break;}
case 2 /* ImportList */: {
[[maybe_unused]] auto const& that = this->template get<State::ImportList>();
TRY(builder.append("State::ImportList"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("emitted_comma: {}", that.emitted_comma));
}
TRY(builder.append(")"));
break;}
case 3 /* EntityDeclaration */: {
[[maybe_unused]] auto const& that = this->template get<State::EntityDeclaration>();
TRY(builder.append("State::EntityDeclaration"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("entity: {}", that.entity));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("accept_generics: {}", that.accept_generics));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("has_generics: {}", that.has_generics));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("generic_nesting: {}", that.generic_nesting));
}
TRY(builder.append(")"));
break;}
case 4 /* ParameterList */: {
[[maybe_unused]] auto const& that = this->template get<State::ParameterList>();
TRY(builder.append("State::ParameterList"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}", that.open_parens));
}
TRY(builder.append(")"));
break;}
case 5 /* RestrictionList */: {
[[maybe_unused]] auto const& that = this->template get<State::RestrictionList>();
TRY(builder.append("State::RestrictionList"));
break;}
case 6 /* EntityDefinition */: {
[[maybe_unused]] auto const& that = this->template get<State::EntityDefinition>();
TRY(builder.append("State::EntityDefinition"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("entity: {}", that.entity));
}
TRY(builder.append(")"));
break;}
case 7 /* StatementContext */: {
[[maybe_unused]] auto const& that = this->template get<State::StatementContext>();
TRY(builder.append("State::StatementContext"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}", that.open_parens));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_curlies: {}", that.open_curlies));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_squares: {}", that.open_squares));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("arrow_indents: {}", that.arrow_indents));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("allow_eol: {}", that.allow_eol));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("inserted_comma: {}", that.inserted_comma));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expression_mode: {}", that.expression_mode));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("dedents_on_open_curly: {}", that.dedents_on_open_curly));
}
TRY(builder.append(")"));
break;}
case 8 /* MatchPattern */: {
[[maybe_unused]] auto const& that = this->template get<State::MatchPattern>();
TRY(builder.append("State::MatchPattern"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}", that.open_parens));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("allow_multiple: {}", that.allow_multiple));
}
TRY(builder.append(")"));
break;}
case 9 /* VariableDeclaration */: {
[[maybe_unused]] auto const& that = this->template get<State::VariableDeclaration>();
TRY(builder.append("State::VariableDeclaration"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}", that.open_parens));
}
TRY(builder.append(")"));
break;}
case 10 /* GenericCallTypeParams */: {
[[maybe_unused]] auto const& that = this->template get<State::GenericCallTypeParams>();
TRY(builder.append("State::GenericCallTypeParams"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_angles: {}", that.open_angles));
}
TRY(builder.append(")"));
break;}
case 11 /* TypeContext */: {
[[maybe_unused]] auto const& that = this->template get<State::TypeContext>();
TRY(builder.append("State::TypeContext"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}", that.open_parens));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_curlies: {}", that.open_curlies));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_squares: {}", that.open_squares));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_angles: {}", that.open_angles));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("seen_start: {}", that.seen_start));
}
TRY(builder.append(")"));
break;}
case 12 /* FunctionTypeContext */: {
[[maybe_unused]] auto const& that = this->template get<State::FunctionTypeContext>();
TRY(builder.append("State::FunctionTypeContext"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("seen_final_type: {}", that.seen_final_type));
}
TRY(builder.append(")"));
break;}
}
return builder.to_string();
}
ErrorOr<String> formatter::State::name() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::Toplevel>();return JaktInternal::ExplicitValue(String("toplevel"));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::Import>();return JaktInternal::ExplicitValue(String("import"));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::ImportList>();return JaktInternal::ExplicitValue(String("import list"));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::EntityDeclaration>();return JaktInternal::ExplicitValue(String("entity declaration"));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::ParameterList>();return JaktInternal::ExplicitValue(String("parameter list"));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename formatter::State::RestrictionList>();
return JaktInternal::ExplicitValue(String("restriction list"));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::EntityDefinition>();return JaktInternal::ExplicitValue(String("entity definition"));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::StatementContext>();return JaktInternal::ExplicitValue(String("statement context"));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::MatchPattern>();return JaktInternal::ExplicitValue(String("match pattern"));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::VariableDeclaration>();return JaktInternal::ExplicitValue(String("variable declaration"));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::GenericCallTypeParams>();return JaktInternal::ExplicitValue(String("generic call type params"));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::TypeContext>();size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& open_angles = __jakt_match_value.open_angles;
bool const& seen_start = __jakt_match_value.seen_start;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("type context (p{} c{} s{} a{} s:{})"),open_parens,open_curlies,open_squares,open_angles,seen_start))));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::FunctionTypeContext>();return JaktInternal::ExplicitValue(String("function type context"));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> formatter::Entity::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Struct */: {
[[maybe_unused]] auto const& that = this->template get<Entity::Struct>();
TRY(builder.append("Entity::Struct"));
break;}
case 1 /* Enum */: {
[[maybe_unused]] auto const& that = this->template get<Entity::Enum>();
TRY(builder.append("Entity::Enum"));
break;}
case 2 /* Namespace */: {
[[maybe_unused]] auto const& that = this->template get<Entity::Namespace>();
TRY(builder.append("Entity::Namespace"));
break;}
case 3 /* Function */: {
[[maybe_unused]] auto const& that = this->template get<Entity::Function>();
TRY(builder.append("Entity::Function"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("arrow: {}", that.arrow));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("indented: {}", that.indented));
}
TRY(builder.append(")"));
break;}
}
return builder.to_string();
}
formatter::Entity formatter::Entity::from_token(lexer::Token const& token) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<formatter::Entity, formatter::Entity>{
auto&& __jakt_match_variant = ((token));
switch(__jakt_match_variant.index()) {
case 94: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Struct>();
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Struct() } );
};/*case end*/
case 66: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Class>();
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Struct() } );
};/*case end*/
case 71: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Enum>();
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Enum() } );
};/*case end*/
case 85: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Namespace>();
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Namespace() } );
};/*case end*/
case 76: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comptime>();
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Function(false,false) } );
};/*case end*/
case 75: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Function>();
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Function(false,false) } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Struct() } );
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<String> formatter::ExpressionMode::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* OutsideExpression */: {
[[maybe_unused]] auto const& that = this->template get<ExpressionMode::OutsideExpression>();
TRY(builder.append("ExpressionMode::OutsideExpression"));
break;}
case 1 /* BeforeExpressions */: {
[[maybe_unused]] auto const& that = this->template get<ExpressionMode::BeforeExpressions>();
TRY(builder.append("ExpressionMode::BeforeExpressions"));
break;}
case 2 /* AtExpressionStart */: {
[[maybe_unused]] auto const& that = this->template get<ExpressionMode::AtExpressionStart>();
TRY(builder.append("ExpressionMode::AtExpressionStart"));
break;}
case 3 /* InExpression */: {
[[maybe_unused]] auto const& that = this->template get<ExpressionMode::InExpression>();
TRY(builder.append("ExpressionMode::InExpression"));
break;}
}
return builder.to_string();
}
}
} // namespace Jakt
