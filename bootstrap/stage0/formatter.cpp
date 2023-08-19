#include "formatter.h"
namespace Jakt {
namespace formatter {
void bubble_sort(JaktInternal::DynamicArray<DeprecatedString> values) {
{
i64 i = static_cast<i64>(0LL);
while ([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,JaktInternal::checked_sub((infallible_integer_cast<i64>((((values).size())))),static_cast<i64>(1LL)))){
i64 j = static_cast<i64>(0LL);
while ([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(j,JaktInternal::checked_sub(JaktInternal::checked_sub((infallible_integer_cast<i64>((((values).size())))),i),static_cast<i64>(1LL)))){
if (((((values)[j])) > (((values)[JaktInternal::checked_add(j,static_cast<i64>(1LL))])))){
DeprecatedString const tmp = ((values)[j]);
(((values)[j]) = ((values)[JaktInternal::checked_add(j,static_cast<i64>(1LL))]));
(((values)[JaktInternal::checked_add(j,static_cast<i64>(1LL))]) = tmp);
}
(++(j));
}
(++(i));
}
}
}

ErrorOr<DeprecatedString> formatter::FormattedToken::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("FormattedToken("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("token: {}, ", token));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("indent: {}, ", indent));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trailing_trivia: {}, ", trailing_trivia));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("preceding_trivia: {}", preceding_trivia));
}
TRY(builder.append(")"sv));return builder.to_string(); }
formatter::FormattedToken::FormattedToken(lexer::Token a_token, size_t a_indent, JaktInternal::DynamicArray<u8> a_trailing_trivia, JaktInternal::DynamicArray<u8> a_preceding_trivia) :token(move(a_token)), indent(move(a_indent)), trailing_trivia(move(a_trailing_trivia)), preceding_trivia(move(a_preceding_trivia)){}

ErrorOr<DeprecatedString> formatter::FormattedToken::token_text() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = ((*this).token);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::SingleQuotedString>();DeprecatedString const& quote = __jakt_match_value.quote;
JaktInternal::Optional<DeprecatedString> const& prefix = __jakt_match_value.prefix;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}'{}'"sv)),TRY((prefix.try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))),quote))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::QuotedString>();DeprecatedString const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("\"{}\""sv)),quote))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Number>();lexer::LiteralPrefix const& prefix = __jakt_match_value.prefix;
DeprecatedString const& number = __jakt_match_value.number;
lexer::LiteralSuffix const& suffix = __jakt_match_value.suffix;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}{}{}"sv)),TRY((((prefix).to_string()))),number,TRY((((suffix).to_string())))))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(";"sv)));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(":"sv)));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("::"sv)));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("("sv)));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(")"sv)));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("{"sv)));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("}"sv)));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("["sv)));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("]"sv)));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("%"sv)));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("+"sv)));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("-"sv)));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("="sv)));
};/*case end*/
case 17: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("+="sv)));
};/*case end*/
case 18: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("++"sv)));
};/*case end*/
case 19: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("-="sv)));
};/*case end*/
case 20: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("--"sv)));
};/*case end*/
case 21: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("*="sv)));
};/*case end*/
case 22: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("/="sv)));
};/*case end*/
case 23: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("%="sv)));
};/*case end*/
case 24: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("!="sv)));
};/*case end*/
case 25: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("=="sv)));
};/*case end*/
case 26: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(">"sv)));
};/*case end*/
case 27: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(">="sv)));
};/*case end*/
case 28: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("<"sv)));
};/*case end*/
case 29: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("<="sv)));
};/*case end*/
case 30: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("<<<"sv)));
};/*case end*/
case 31: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("<<"sv)));
};/*case end*/
case 32: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("<<="sv)));
};/*case end*/
case 33: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(">>"sv)));
};/*case end*/
case 34: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(">>>"sv)));
};/*case end*/
case 35: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(">>="sv)));
};/*case end*/
case 36: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("*"sv)));
};/*case end*/
case 37: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("&"sv)));
};/*case end*/
case 38: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("&="sv)));
};/*case end*/
case 39: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("&&"sv)));
};/*case end*/
case 40: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("|"sv)));
};/*case end*/
case 41: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("|="sv)));
};/*case end*/
case 42: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("||"sv)));
};/*case end*/
case 43: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("^"sv)));
};/*case end*/
case 44: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("^="sv)));
};/*case end*/
case 45: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("$"sv)));
};/*case end*/
case 46: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("~"sv)));
};/*case end*/
case 47: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("/"sv)));
};/*case end*/
case 48: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("!"sv)));
};/*case end*/
case 49: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("?"sv)));
};/*case end*/
case 50: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("??"sv)));
};/*case end*/
case 51: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("??="sv)));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(","sv)));
};/*case end*/
case 53: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("."sv)));
};/*case end*/
case 54: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(".."sv)));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
};/*case end*/
case 56: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
};/*case end*/
case 57: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("=>"sv)));
};/*case end*/
case 58: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("->"sv)));
};/*case end*/
case 59: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("and"sv)));
};/*case end*/
case 60: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("anon"sv)));
};/*case end*/
case 61: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("as"sv)));
};/*case end*/
case 62: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("boxed"sv)));
};/*case end*/
case 63: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("break"sv)));
};/*case end*/
case 64: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("catch"sv)));
};/*case end*/
case 65: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("class"sv)));
};/*case end*/
case 66: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("continue"sv)));
};/*case end*/
case 67: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("cpp"sv)));
};/*case end*/
case 68: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("defer"sv)));
};/*case end*/
case 69: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("destructor"sv)));
};/*case end*/
case 70: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("else"sv)));
};/*case end*/
case 71: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("enum"sv)));
};/*case end*/
case 72: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("extern"sv)));
};/*case end*/
case 73: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("false"sv)));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("for"sv)));
};/*case end*/
case 75: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("fn"sv)));
};/*case end*/
case 76: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("comptime"sv)));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("if"sv)));
};/*case end*/
case 78: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("import"sv)));
};/*case end*/
case 79: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("in"sv)));
};/*case end*/
case 80: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("is"sv)));
};/*case end*/
case 81: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("let"sv)));
};/*case end*/
case 82: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("loop"sv)));
};/*case end*/
case 83: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("match"sv)));
};/*case end*/
case 84: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("mut"sv)));
};/*case end*/
case 85: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("namespace"sv)));
};/*case end*/
case 86: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("not"sv)));
};/*case end*/
case 87: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("or"sv)));
};/*case end*/
case 89: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("private"sv)));
};/*case end*/
case 90: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("public"sv)));
};/*case end*/
case 91: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("raw"sv)));
};/*case end*/
case 93: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("return"sv)));
};/*case end*/
case 94: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("restricted"sv)));
};/*case end*/
case 95: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("sizeof"sv)));
};/*case end*/
case 96: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("struct"sv)));
};/*case end*/
case 97: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("this"sv)));
};/*case end*/
case 98: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("throw"sv)));
};/*case end*/
case 99: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("throws"sv)));
};/*case end*/
case 100: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("true"sv)));
};/*case end*/
case 101: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("try"sv)));
};/*case end*/
case 102: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("unsafe"sv)));
};/*case end*/
case 104: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("weak"sv)));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("while"sv)));
};/*case end*/
case 106: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("yield"sv)));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("guard"sv)));
};/*case end*/
case 88: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("override"sv)));
};/*case end*/
case 103: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("virtual"sv)));
};/*case end*/
case 108: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("implements"sv)));
};/*case end*/
case 109: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("requires"sv)));
};/*case end*/
case 110: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("trait"sv)));
};/*case end*/
case 92: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("reflect"sv)));
};/*case end*/
case 111: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> formatter::FormattedToken::debug_text() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = ((*this).token);
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("Identifier: {}"sv)),name))));
};/*case end*/
case 55: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();JaktInternal::Optional<DeprecatedString> const& comment = __jakt_match_value.comment;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("Eol: {}"sv)),TRY((comment.try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); })))))));
};/*case end*/
case 56: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Eof"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).token_text()))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> formatter::ReflowState::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("ReflowState("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("token: {}, ", token));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("state: {}, ", state));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("enclosures_to_ignore: {}", enclosures_to_ignore));
}
TRY(builder.append(")"sv));return builder.to_string(); }
formatter::ReflowState::ReflowState(formatter::FormattedToken a_token, formatter::State a_state, size_t a_enclosures_to_ignore) :token(move(a_token)), state(move(a_state)), enclosures_to_ignore(move(a_enclosures_to_ignore)){}

ErrorOr<DeprecatedString> formatter::Formatter::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Formatter("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("token_provider: {}, ", token_provider));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_line: {}, ", current_line));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_line_length: {}, ", current_line_length));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("max_allowed_line_length: {}, ", max_allowed_line_length));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("breakable_points_in_current_line: {}, ", breakable_points_in_current_line));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("tokens_to_reflow: {}, ", tokens_to_reflow));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("replace_commas_in_enclosure: {}, ", replace_commas_in_enclosure));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("enclosures_to_ignore: {}, ", enclosures_to_ignore));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("in_condition_expr: {}, ", in_condition_expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("in_condition_expr_indented: {}, ", in_condition_expr_indented));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("logical_break_indent: {}, ", logical_break_indent));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("empty_line_count: {}", empty_line_count));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>> formatter::Formatter::next() {
{
JaktInternal::Optional<formatter::ReflowState> const reflown_token = ((((*this).tokens_to_reflow)).pop());
JaktInternal::Optional<formatter::FormattedToken> maybe_next_underlying_token = TRY((((reflown_token).map([](auto& _value) { return _value.token; })).try_value_or_lazy_evaluated_optional([&]() -> ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> { return TRY((((((*this).token_provider)).next()))); })));
formatter::State current_state = ((reflown_token).map([](auto& _value) { return _value.state; })).value_or_lazy_evaluated([&] { return ((((*this).token_provider)).state()); });
if (((maybe_next_underlying_token).has_value())){
lexer::Token next_underlying_token = (((maybe_next_underlying_token.value())).token);
bool accepted_at_least_one_token = false;
while (((!(((next_underlying_token).index() == 56 /* Eof */))) && (!(((next_underlying_token).index() == 55 /* Eol */))))){
size_t const projected_added_length = TRY((((*this).token_length((maybe_next_underlying_token.value())))));
if (((((*this).logical_break_indent)).has_value())){
((((maybe_next_underlying_token.value())).indent) = (((*this).logical_break_indent).value()));
}
if (((((*this).in_condition_expr) && ((next_underlying_token).index() == 9 /* LCurly */)) || ((next_underlying_token).index() == 70 /* Else */))){
(((*this).in_condition_expr) = false);
(((*this).in_condition_expr_indented) = false);
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 7: {
{
(accepted_at_least_one_token = true);
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (projected_added_length));
if ((!(formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 7: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 8: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 10: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 12: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
}
else {
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 7: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
}

if (((breakable_point).has_value())){
TRY((((((*this).breakable_points_in_current_line)).push((breakable_point.value())))));
}
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
}
else {
((((*this).enclosures_to_ignore)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9: {
{
(accepted_at_least_one_token = true);
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (projected_added_length));
if ((!(formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 7: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 8: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 10: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 12: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
}
else {
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 7: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
}

if (((breakable_point).has_value())){
TRY((((((*this).breakable_points_in_current_line)).push((breakable_point.value())))));
}
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
}
else {
((((*this).enclosures_to_ignore)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
{
(accepted_at_least_one_token = true);
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (projected_added_length));
if ((!(formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 7: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 8: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 10: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.index()) {
case 12: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
}
else {
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 7: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue( formatter::BreakablePoint { typename formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)) } );
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
}

if (((breakable_point).has_value())){
TRY((((((*this).breakable_points_in_current_line)).push((breakable_point.value())))));
}
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
}
else {
((((*this).enclosures_to_ignore)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8: {
{
bool ignore = false;
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((*this).enclosures_to_ignore),static_cast<size_t>(0ULL))){
((((*this).enclosures_to_ignore)) -= (static_cast<size_t>(1ULL)));
(ignore = true);
}
if (((!(ignore)) && (!(formatter::Formatter::should_ignore_state(current_state))))){
lexer::Token const replacement = formatter::collapse<lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
formatter::FormattedToken const new_token = formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
if (((replacement).index() == 55 /* Eol */)){
TRY((((((*this).tokens_to_reflow)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
return JaktInternal::LoopBreak{};
}
}
else {
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10: {
{
bool ignore = false;
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((*this).enclosures_to_ignore),static_cast<size_t>(0ULL))){
((((*this).enclosures_to_ignore)) -= (static_cast<size_t>(1ULL)));
(ignore = true);
}
if (((!(ignore)) && (!(formatter::Formatter::should_ignore_state(current_state))))){
lexer::Token const replacement = formatter::collapse<lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
formatter::FormattedToken const new_token = formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
if (((replacement).index() == 55 /* Eol */)){
TRY((((((*this).tokens_to_reflow)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
return JaktInternal::LoopBreak{};
}
}
else {
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12: {
{
bool ignore = false;
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((*this).enclosures_to_ignore),static_cast<size_t>(0ULL))){
((((*this).enclosures_to_ignore)) -= (static_cast<size_t>(1ULL)));
(ignore = true);
}
if (((!(ignore)) && (!(formatter::Formatter::should_ignore_state(current_state))))){
lexer::Token const replacement = formatter::collapse<lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
formatter::FormattedToken const new_token = formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
if (((replacement).index() == 55 /* Eol */)){
TRY((((((*this).tokens_to_reflow)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
TRY((((((*this).replace_commas_in_enclosure)).push(none))));
return JaktInternal::LoopBreak{};
}
}
else {
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52: {
{
(accepted_at_least_one_token = true);
if ((!(formatter::Formatter::should_ignore_state(current_state)))){
lexer::Token const replacement = formatter::collapse<lexer::Token>(((((*this).replace_commas_in_enclosure)).last())).value_or_lazy_evaluated([&] { return next_underlying_token; });
formatter::FormattedToken const new_token = formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
if (((replacement).index() == 55 /* Eol */)){
return JaktInternal::LoopBreak{};
}
}
else {
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
lexer::Token const newline =  lexer::Token { typename lexer::Token::Eol(JaktInternal::OptionalNone(),((next_underlying_token).span())) } ;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.index()) {
case 83: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((next_token.value())).indent),(((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 74: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((next_token.value())).indent),(((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((next_token.value())).indent),(((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 77: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((next_token.value())).indent),(((maybe_next_underlying_token.value())).indent))){
(((*this).in_condition_expr_indented) = true);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 107: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((next_token.value())).indent),(((maybe_next_underlying_token.value())).indent))){
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
if ((((((*this).logical_break_indent)).has_value()) && (((next_underlying_token).index() == 59 /* And */) || ((next_underlying_token).index() == 87 /* Or */)))){
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
formatter::FormattedToken const new_token = formatter::FormattedToken(newline,(((*this).logical_break_indent).value()),(TRY((DynamicArray<u8>::create_with({})))),(TRY((DynamicArray<u8>::create_with({})))));
TRY((((((*this).current_line)).push(formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
return JaktInternal::LoopBreak{};
}
size_t const real_line_length = JaktInternal::checked_add(JaktInternal::checked_add(((*this).current_line_length),projected_added_length),(((maybe_next_underlying_token.value())).indent));
size_t const most_desirable_breaking_point_index = ((*this).pick_breaking_point_index());
if ((accepted_at_least_one_token && ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(real_line_length,((*this).max_allowed_line_length)) && ((!(((((*this).breakable_points_in_current_line)).is_empty()))) && ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((((((*this).breakable_points_in_current_line))[most_desirable_breaking_point_index])).point()),((((*this).current_line)).size())) && (!(formatter::Formatter::should_ignore_state(current_state)))))))){
formatter::BreakablePoint const breakable_point = ((((*this).breakable_points_in_current_line))[most_desirable_breaking_point_index]);
if ((!(((((*this).replace_commas_in_enclosure)).is_empty())))){
(((((*this).replace_commas_in_enclosure))[JaktInternal::checked_sub(((((*this).replace_commas_in_enclosure)).size()),static_cast<size_t>(1ULL))]) = newline);
}
size_t const point = ((breakable_point).point());
if (((breakable_point).index() == 3 /* Logical */)){
if ((!(((((*this).logical_break_indent)).has_value())))){
(((*this).logical_break_indent) = ((((((((*this).current_line))[point])).token)).indent));
if ((!(((*this).in_condition_expr_indented)))){
(((((*this).logical_break_indent).value())) += (static_cast<size_t>(1ULL)));
}
}
}
(((*this).tokens_to_reflow) = TRY((((((((*this).current_line))[(JaktInternal::Range<size_t>{static_cast<size_t>(point),static_cast<size_t>(9223372036854775807LL)})])).to_array()))));
TRY((((((*this).tokens_to_reflow)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
TRY((((*this).fixup_tokens_to_reflow())));
formatter::State const final_state = ((((((*this).current_line))[point])).state);
(((*this).enclosures_to_ignore) = ((((((*this).current_line))[point])).enclosures_to_ignore));
(((*this).current_line) = TRY((((((((*this).current_line))[(JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(point)})])).to_array()))));
TRY((((((*this).current_line)).push(formatter::ReflowState(formatter::FormattedToken(newline,(((maybe_next_underlying_token.value())).indent),(TRY((DynamicArray<u8>::create_with({})))),(TRY((DynamicArray<u8>::create_with({}))))),final_state,((*this).enclosures_to_ignore))))));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
return JaktInternal::LoopBreak{};
}
(accepted_at_least_one_token = true);
TRY((((((*this).current_line)).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
((((*this).current_line_length)) += (projected_added_length));
if ((((*this).in_condition_expr) && (((next_underlying_token).index() == 59 /* And */) || ((next_underlying_token).index() == 87 /* Or */)))){
TRY((((((*this).breakable_points_in_current_line)).push( formatter::BreakablePoint { typename formatter::BreakablePoint::Logical(((((*this).current_line)).size()),((*this).current_line_length)) } ))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
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
size_t const allowed_empty_lines_in_state = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = current_state;
switch(__jakt_match_variant.index()) {
case 14: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<formatter::ReflowState> line = ((*this).current_line);
(((*this).current_line) = (TRY((DynamicArray<formatter::ReflowState>::create_with({})))));
(((*this).breakable_points_in_current_line) = (TRY((DynamicArray<formatter::BreakablePoint>::create_with({})))));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
(((*this).enclosures_to_ignore) = static_cast<size_t>(0ULL));
if ((!(((*this).in_condition_expr)))){
(((*this).logical_break_indent) = JaktInternal::OptionalNone());
}
if ((((line).is_empty()) || (!((((((((((line).last()).value())).token)).token)).index() == 55 /* Eol */))))){
TRY((((line).push(formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))))));
}
if (((((line).size())) == (static_cast<size_t>(1ULL)))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((((((line).last()).value())).token)).token);
switch(__jakt_match_variant.index()) {
case 55: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();JaktInternal::Optional<DeprecatedString> const& comment = __jakt_match_value.comment;
{
if (([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((*this).empty_line_count),allowed_empty_lines_in_state) && (!(((comment).has_value()))))){
return TRY((((*this).next())));
}
if (((comment).has_value())){
(((*this).empty_line_count) = static_cast<size_t>(0ULL));
}
else {
((((*this).empty_line_count)) += (static_cast<size_t>(1ULL)));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
else {
(((*this).empty_line_count) = static_cast<size_t>(0ULL));
}

if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((line).size()),static_cast<size_t>(1ULL))){
(((((((line)[JaktInternal::checked_sub(((line).size()),static_cast<size_t>(2ULL))])).token)).trailing_trivia) = (TRY((DynamicArray<u8>::create_with({})))));
}
(((((((line)[JaktInternal::checked_sub(((line).size()),static_cast<size_t>(1ULL))])).token)).preceding_trivia) = (TRY((DynamicArray<u8>::create_with({})))));
(((((((line)[JaktInternal::checked_sub(((line).size()),static_cast<size_t>(1ULL))])).token)).trailing_trivia) = (TRY((DynamicArray<u8>::create_with({})))));
TRY((((*this).fixup_closing_enclosures(((line))))));
JaktInternal::DynamicArray<formatter::FormattedToken> result = (TRY((DynamicArray<formatter::FormattedToken>::create_with({}))));
{
JaktInternal::ArrayIterator<formatter::ReflowState> _magic = ((line).iterator());
for (;;){
JaktInternal::Optional<formatter::ReflowState> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
formatter::ReflowState state = (_magic_value.value());
{
TRY((((result).push(((state).token)))));
}

}
}

return result;
}
else {
if (((((*this).current_line)).is_empty())){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<formatter::ReflowState> const line = ((*this).current_line);
(((*this).current_line) = (TRY((DynamicArray<formatter::ReflowState>::create_with({})))));
(((*this).breakable_points_in_current_line) = (TRY((DynamicArray<formatter::BreakablePoint>::create_with({})))));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
(((*this).enclosures_to_ignore) = static_cast<size_t>(0ULL));
(((*this).in_condition_expr) = false);
(((*this).in_condition_expr_indented) = false);
(((*this).logical_break_indent) = JaktInternal::OptionalNone());
JaktInternal::DynamicArray<formatter::FormattedToken> result = (TRY((DynamicArray<formatter::FormattedToken>::create_with({}))));
{
JaktInternal::ArrayIterator<formatter::ReflowState> _magic = ((line).iterator());
for (;;){
JaktInternal::Optional<formatter::ReflowState> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
formatter::ReflowState state = (_magic_value.value());
{
TRY((((result).push(((state).token)))));
}

}
}

return result;
}

}
}

bool formatter::Formatter::should_ignore_state(formatter::State const state) {
{
return (((state).index() == 14 /* TypeContext */) || ((state).index() == 12 /* VariableDeclaration */));
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Formatter::peek() {
{
JaktInternal::Optional<formatter::ReflowState> reflown_token = JaktInternal::OptionalNone();
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((*this).tokens_to_reflow)).size()),static_cast<size_t>(0ULL))){
(reflown_token = ((((*this).tokens_to_reflow))[JaktInternal::checked_sub(((((*this).tokens_to_reflow)).size()),static_cast<size_t>(1ULL))]));
}
return TRY((((reflown_token).map([](auto& _value) { return _value.token; })).try_value_or_lazy_evaluated_optional([&]() -> ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> { return TRY((((((*this).token_provider)).formatted_peek()))); })));
}
}

ErrorOr<formatter::Formatter> formatter::Formatter::for_tokens(JaktInternal::DynamicArray<lexer::Token> const tokens,bool const debug,size_t const max_allowed_line_length) {
{
JaktInternal::Optional<lexer::Token> const none = JaktInternal::OptionalNone();
return formatter::Formatter(TRY((formatter::Stage0::for_tokens(tokens,debug))),(TRY((DynamicArray<formatter::ReflowState>::create_with({})))),static_cast<size_t>(0ULL),max_allowed_line_length,(TRY((DynamicArray<formatter::BreakablePoint>::create_with({})))),(TRY((DynamicArray<formatter::ReflowState>::create_with({})))),(TRY((DynamicArray<JaktInternal::Optional<lexer::Token>>::create_with({none})))),static_cast<size_t>(0ULL),false,false,JaktInternal::OptionalNone(),static_cast<size_t>(0ULL));
}
}

ErrorOr<JaktInternal::DynamicArray<u8>> formatter::Formatter::to_array(DeprecatedString const s) {
{
JaktInternal::DynamicArray<u8> result = (TRY((DynamicArray<u8>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((s).length()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((result).push(((s).byte_at(i))))));
}

}
}

return result;
}
}

ErrorOr<void> formatter::Formatter::fixup_tokens_to_reflow() {
{
if (((((*this).tokens_to_reflow)).is_empty())){
return {};
}
size_t i = static_cast<size_t>(0ULL);
size_t j = JaktInternal::checked_sub(((((*this).tokens_to_reflow)).size()),static_cast<size_t>(1ULL));
while ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,j)){
formatter::ReflowState const a = ((((*this).tokens_to_reflow))[i]);
(((((*this).tokens_to_reflow))[i]) = ((((*this).tokens_to_reflow))[j]));
(((((*this).tokens_to_reflow))[j]) = a);
((i) += (static_cast<size_t>(1ULL)));
((j) -= (static_cast<size_t>(1ULL)));
}
}
return {};
}

formatter::Formatter::Formatter(formatter::Stage0 a_token_provider, JaktInternal::DynamicArray<formatter::ReflowState> a_current_line, size_t a_current_line_length, size_t a_max_allowed_line_length, JaktInternal::DynamicArray<formatter::BreakablePoint> a_breakable_points_in_current_line, JaktInternal::DynamicArray<formatter::ReflowState> a_tokens_to_reflow, JaktInternal::DynamicArray<JaktInternal::Optional<lexer::Token>> a_replace_commas_in_enclosure, size_t a_enclosures_to_ignore, bool a_in_condition_expr, bool a_in_condition_expr_indented, JaktInternal::Optional<size_t> a_logical_break_indent, size_t a_empty_line_count) :token_provider(move(a_token_provider)), current_line(move(a_current_line)), current_line_length(move(a_current_line_length)), max_allowed_line_length(move(a_max_allowed_line_length)), breakable_points_in_current_line(move(a_breakable_points_in_current_line)), tokens_to_reflow(move(a_tokens_to_reflow)), replace_commas_in_enclosure(move(a_replace_commas_in_enclosure)), enclosures_to_ignore(move(a_enclosures_to_ignore)), in_condition_expr(move(a_in_condition_expr)), in_condition_expr_indented(move(a_in_condition_expr_indented)), logical_break_indent(move(a_logical_break_indent)), empty_line_count(move(a_empty_line_count)){}

ErrorOr<size_t> formatter::Formatter::token_length(formatter::FormattedToken const token) const {
{
size_t length = ((((token).preceding_trivia)).size());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<size_t>>{
auto&& __jakt_match_variant = ((token).token);
switch(__jakt_match_variant.index()) {
case 55: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();JaktInternal::Optional<DeprecatedString> const& comment = __jakt_match_value.comment;
{
if (((comment).has_value())){
u8 next_char = static_cast<u8>(u8' ');
if ((((((comment.value())).length())) != (static_cast<size_t>(0ULL)))){
(next_char = (((comment.value())).byte_at(static_cast<size_t>(0ULL))));
}
size_t const space = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>>{
auto __jakt_enum_value = (next_char);
if (__jakt_enum_value == static_cast<u8>(u8' ')) {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
}
else if (__jakt_enum_value == static_cast<u8>(u8'\t')) {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
}
else if (__jakt_enum_value == static_cast<u8>(u8'/')) {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
}
else {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((length) += (space));
((length) += ((((comment.value())).length())));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((length) += (((TRY((((token).token_text())))).length())));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((length) += (((((token).trailing_trivia)).size())));
return length;
}
}

ErrorOr<void> formatter::Formatter::fixup_closing_enclosures(JaktInternal::DynamicArray<formatter::ReflowState>& line) const {
{
if (((((line))).is_empty())){
return {};
}
(((((((((line)))[static_cast<i64>(0LL)])).token)).preceding_trivia) = (TRY((DynamicArray<u8>::create_with({})))));
size_t enclosure_run_length = static_cast<size_t>(0ULL);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(JaktInternal::checked_sub(((((line))).size()),static_cast<size_t>(1ULL))),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((((((((line)))[i])).token)).token);
switch(__jakt_match_variant.index()) {
case 8: {
{
((enclosure_run_length) += (static_cast<size_t>(1ULL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10: {
{
((enclosure_run_length) += (static_cast<size_t>(1ULL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12: {
{
((enclosure_run_length) += (static_cast<size_t>(1ULL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enclosure_run_length)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t j = (_magic_value.value());
{
(((((((line)))[JaktInternal::checked_sub(i,j)])).token) = formatter::FormattedToken(((((((((line)))[JaktInternal::checked_sub(i,j)])).token)).token),((((((((line)))[JaktInternal::checked_sub(i,enclosure_run_length)])).token)).indent),((((((((line)))[JaktInternal::checked_sub(i,j)])).token)).trailing_trivia),((((((((line)))[JaktInternal::checked_sub(i,j)])).token)).preceding_trivia)));
}

}
}

(enclosure_run_length = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enclosure_run_length)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
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
return static_cast<size_t>(0ULL);
}
}

ErrorOr<DeprecatedString> formatter::Stage0::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Stage0("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("tokens: {}, ", tokens));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("index: {}, ", index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("states: {}, ", states));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("indent: {}, ", indent));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("already_seen_enclosure_in_current_line: {}, ", already_seen_enclosure_in_current_line));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("dedents_to_skip: {}, ", dedents_to_skip));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("debug: {}", debug));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_implements_context(lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_636; {
((*this).pop_state());
__jakt_var_636 = TRY((((*this).formatted_token(token)))); goto __jakt_label_532;

}
__jakt_label_532:; __jakt_var_636.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next() {
{
return TRY((((*this).next_impl(false))));
}
}

ErrorOr<void> formatter::Stage0::push_state(formatter::State const state) {
{
TRY((((((*this).states)).push(state))));
}
return {};
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_import_context(bool const is_extern,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 72: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 61: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_637; {
if (((!(is_extern)) && ((((*this).peek(static_cast<i64>(0LL)))).index() == 7 /* LParen */))){
return TRY((((*this).formatted_token(token))));
}
if (((((*this).peek(static_cast<i64>(0LL)))).index() == 6 /* ColonColon */)){
return TRY((((*this).formatted_token(token))));
}
if (((!(is_extern)) && ((!(((((*this).peek(static_cast<i64>(0LL)))).index() == 9 /* LCurly */))) && (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 61 /* As */)))))){
((*this).pop_state());
}
__jakt_var_637 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_533;

}
__jakt_label_533:; __jakt_var_637.release_value(); }));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_638; {
if (is_extern){
TRY((((*this).push_state( formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern) } ))));
}
else {
TRY((((*this).push_state( formatter::State { typename formatter::State::ImportList(true) } ))));
}

__jakt_var_638 = TRY((((*this).formatted_token(token)))); goto __jakt_label_534;

}
__jakt_label_534:; __jakt_var_638.release_value(); }));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_639; {
((*this).pop_state());
__jakt_var_639 = TRY((((*this).formatted_token(token)))); goto __jakt_label_535;

}
__jakt_label_535:; __jakt_var_639.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_640; {
__jakt_var_640 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_536;

}
__jakt_label_536:; __jakt_var_640.release_value(); }));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_toplevel_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,bool const is_extern,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 72: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_641; {
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 65: {
{
TRY((((*this).push_state( formatter::State { typename formatter::State::Extern() } ))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96: {
{
TRY((((*this).push_state( formatter::State { typename formatter::State::Extern() } ))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_641 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_537;

}
__jakt_label_537:; __jakt_var_641.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_642; {
if ((((name) == (TRY(DeprecatedString::from_utf8("type"sv)))) && ((((*this).peek(static_cast<i64>(0LL)))).index() == 3 /* Identifier */))){
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),true,false,static_cast<size_t>(0ULL),is_extern) } ))));
return TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({}))))))));
}
__jakt_var_642 = TRY((((*this).formatted_token(token)))); goto __jakt_label_538;

}
__jakt_label_538:; __jakt_var_642.release_value(); }));
};/*case end*/
case 71: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_643; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_643 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_539;

}
__jakt_label_539:; __jakt_var_643.release_value(); }));
};/*case end*/
case 65: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_644; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_644 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_540;

}
__jakt_label_540:; __jakt_var_644.release_value(); }));
};/*case end*/
case 96: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_645; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_645 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_541;

}
__jakt_label_541:; __jakt_var_645.release_value(); }));
};/*case end*/
case 110: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_646; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_646 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_542;

}
__jakt_label_542:; __jakt_var_646.release_value(); }));
};/*case end*/
case 75: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_647; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_647 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_543;

}
__jakt_label_543:; __jakt_var_647.release_value(); }));
};/*case end*/
case 76: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_648; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_648 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_544;

}
__jakt_label_544:; __jakt_var_648.release_value(); }));
};/*case end*/
case 85: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_649; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_649 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_545;

}
__jakt_label_545:; __jakt_var_649.release_value(); }));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_650; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),is_extern) } ))));
__jakt_var_650 = TRY((((*this).formatted_token(token)))); goto __jakt_label_546;

}
__jakt_label_546:; __jakt_var_650.release_value(); }));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_651; {
if (((open_squares) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),is_extern) } ))));
__jakt_var_651 = TRY((((*this).formatted_token(token)))); goto __jakt_label_547;

}
__jakt_label_547:; __jakt_var_651.release_value(); }));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_652; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,is_extern) } ))));
__jakt_var_652 = TRY((((*this).formatted_token(token)))); goto __jakt_label_548;

}
__jakt_label_548:; __jakt_var_652.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_653; {
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,is_extern) } ))));
__jakt_var_653 = TRY((((*this).formatted_token(token)))); goto __jakt_label_549;

}
__jakt_label_549:; __jakt_var_653.release_value(); }));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_654; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,is_extern) } ))));
__jakt_var_654 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_550;

}
__jakt_label_550:; __jakt_var_654.release_value(); }));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_655; {
if (((open_curlies) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::Toplevel(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,is_extern) } ))));
__jakt_var_655 = TRY((((*this).formatted_token(token)))); goto __jakt_label_551;

}
__jakt_label_551:; __jakt_var_655.release_value(); }));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_656; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_656 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_552;

}
__jakt_label_552:; __jakt_var_656.release_value(); }));
};/*case end*/
case 78: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_657; {
TRY((((*this).push_state( formatter::State { typename formatter::State::Import(((((*this).peek(static_cast<i64>(0LL)))).index() == 72 /* Extern */)) } ))));
__jakt_var_657 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_553;

}
__jakt_label_553:; __jakt_var_657.release_value(); }));
};/*case end*/
case 90: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 89: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 103: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 88: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 62: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 102: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 94: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_658; {
TRY((((*this).push_state( formatter::State { typename formatter::State::RestrictionList() } ))));
__jakt_var_658 = TRY((((*this).formatted_token(token)))); goto __jakt_label_554;

}
__jakt_label_554:; __jakt_var_658.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_659; {
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_659 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_555;

}
__jakt_label_555:; __jakt_var_659.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_entity_declaration_context(formatter::Entity const entity,bool const accept_generics,bool const has_generics,size_t const generic_nesting,bool const is_extern,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 28: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_660; {
if (accept_generics){
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDeclaration(entity,accept_generics,true,JaktInternal::checked_add(generic_nesting,static_cast<size_t>(1ULL)),is_extern) } ))));
}
__jakt_var_660 = TRY((((*this).formatted_token(token)))); goto __jakt_label_556;

}
__jakt_label_556:; __jakt_var_660.release_value(); }));
};/*case end*/
case 26: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_661; {
if (accept_generics){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(generic_nesting,static_cast<size_t>(1ULL))){
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDeclaration(entity,accept_generics,has_generics,JaktInternal::checked_sub(generic_nesting,static_cast<size_t>(1ULL)),is_extern) } ))));
}
else {
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDefinition(entity,is_extern) } ))));
}

}
__jakt_var_661 = TRY((((*this).formatted_token(token)))); goto __jakt_label_557;

}
__jakt_label_557:; __jakt_var_661.release_value(); }));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_662; {
if ((((generic_nesting) == (static_cast<size_t>(0ULL))) && ((!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))) && (!(has_generics))))){
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDefinition(entity,is_extern) } ))));
}
if (((((*this).peek(static_cast<i64>(0LL)))).index() == 108 /* Implements */)){
TRY((((*this).push_state( formatter::State { typename formatter::State::Implements() } ))));
return TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({}))))))));
}
__jakt_var_662 = TRY((((*this).formatted_token(token)))); goto __jakt_label_558;

}
__jakt_label_558:; __jakt_var_662.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_663; {
((*this).pop_state());
__jakt_var_663 = TRY((((*this).formatted_token(token)))); goto __jakt_label_559;

}
__jakt_label_559:; __jakt_var_663.release_value(); }));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_664; {
((*this).pop_state());
__jakt_var_664 = TRY((((*this).formatted_token(token)))); goto __jakt_label_560;

}
__jakt_label_560:; __jakt_var_664.release_value(); }));
};/*case end*/
case 90: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 89: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 103: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 88: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 94: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_665; {
TRY((((*this).push_state( formatter::State { typename formatter::State::RestrictionList() } ))));
__jakt_var_665 = TRY((((*this).formatted_token(token)))); goto __jakt_label_561;

}
__jakt_label_561:; __jakt_var_665.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token formatter::Stage0::consume() {
{
return ((((*this).tokens))[((((*this).index)++))]);
}
}

bool formatter::Stage0::line_has_indent() const {
{
i64 offset = static_cast<i64>(0LL);
for (;;){
lexer::Token const token = ((*this).peek(offset));
if (((token).index() == 9 /* LCurly */)){
return true;
}
if ((((token).index() == 55 /* Eol */) || ((token).index() == 56 /* Eof */))){
break;
}
((offset++));
}
return false;
}
}

ErrorOr<JaktInternal::DynamicArray<u8>> formatter::Stage0::to_array(DeprecatedString const x) {
{
JaktInternal::DynamicArray<u8> res = (TRY((DynamicArray<u8>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((x).length()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((res).push(((x).byte_at(i))))));
}

}
}

return res;
}
}

ErrorOr<formatter::Stage0> formatter::Stage0::create(NonnullRefPtr<compiler::Compiler> compiler,JaktInternal::DynamicArray<u8> const source,bool const debug) {
{
JaktInternal::DynamicArray<u8> const old_file_contents = ((compiler)->current_file_contents);
(((compiler)->current_file_contents) = source);
ScopeGuard __jakt_var_666([&] {
{
(((compiler)->current_file_contents) = old_file_contents);
}

});
JaktInternal::DynamicArray<lexer::Token> const tokens = TRY((lexer::Lexer::lex(compiler)));
return formatter::Stage0(tokens,static_cast<size_t>(0ULL),(TRY((DynamicArray<formatter::State>::create_with({ formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } })))),static_cast<size_t>(0ULL),false,(TRY((DynamicArray<size_t>::create_with({static_cast<size_t>(0ULL)})))),debug);
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_parameter_list_context(size_t const open_parens,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 60: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 84: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_667; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_667 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_562;

}
__jakt_label_562:; __jakt_var_667.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_668; {
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_668 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_563;

}
__jakt_label_563:; __jakt_var_668.release_value(); }));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_669; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::ParameterList(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL))) } ))));
__jakt_var_669 = TRY((((*this).formatted_token(token)))); goto __jakt_label_564;

}
__jakt_label_564:; __jakt_var_669.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_670; {
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::ParameterList(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL))) } ))));
__jakt_var_670 = TRY((((*this).formatted_token(token)))); goto __jakt_label_565;

}
__jakt_label_565:; __jakt_var_670.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_capture_list_context(lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 12: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_671; {
((*this).pop_state());
__jakt_var_671 = TRY((((*this).formatted_token(token)))); goto __jakt_label_566;

}
__jakt_label_566:; __jakt_var_671.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_672; {
__jakt_var_672 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_567;

}
__jakt_label_567:; __jakt_var_672.release_value(); }));
};/*case end*/
case 84: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_673; {
__jakt_var_673 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_568;

}
__jakt_label_568:; __jakt_var_673.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_674; {
__jakt_var_674 = TRY((((*this).formatted_token(token)))); goto __jakt_label_569;

}
__jakt_label_569:; __jakt_var_674.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_impl(bool const reconsume) {
{
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((*this).index),((((*this).tokens)).size()))){
return JaktInternal::OptionalNone();
}
if ((((((*this).states)).is_empty()) && [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((*this).index),((((*this).tokens)).size())))){
abort();
}
lexer::Token token = ((*this).consume());
i64 indent_change = static_cast<i64>(0LL);
if ((!(reconsume))){
if (((!(((*this).already_seen_enclosure_in_current_line))) && ((((token).index() == 7 /* LParen */) || ((token).index() == 9 /* LCurly */)) || ((token).index() == 11 /* LSquare */)))){
(((*this).already_seen_enclosure_in_current_line) = true);
TRY((((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)))));
(indent_change = static_cast<i64>(1LL));
}
else if (((token).index() == 55 /* Eol */)){
(((*this).already_seen_enclosure_in_current_line) = false);
}
if (((((token).index() == 7 /* LParen */) || ((token).index() == 9 /* LCurly */)) || ((token).index() == 11 /* LSquare */))){
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])++));
}
if (((((token).index() == 8 /* RParen */) || ((token).index() == 10 /* RCurly */)) || ((token).index() == 12 /* RSquare */))){
if ((((((((*this).dedents_to_skip)).last()).value())) == (static_cast<size_t>(1ULL)))){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))){
JaktInternal::Optional<size_t> const dummy = ((((*this).dedents_to_skip)).pop());
}
((((*this).indent)) -= (static_cast<size_t>(1ULL)));
(((*this).already_seen_enclosure_in_current_line) = false);
}
else if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((((*this).dedents_to_skip)).last()).value()),static_cast<size_t>(0ULL))){
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])) -= (static_cast<size_t>(1ULL)));
}
}
}
ScopeGuard __jakt_var_675([&] {
{
if ([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(indent_change,static_cast<i64>(0LL))){
((((*this).indent)) += ((infallible_integer_cast<size_t>((indent_change)))));
}
else if ([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(indent_change,static_cast<i64>(0LL))){
((((*this).indent)) -= ((infallible_integer_cast<size_t>(((-(indent_change)))))));
}
}

});
if (((*this).debug)){
warnln();
warnln((StringView::from_string_literal("Token: {} -- Indent: {}"sv)),TRY((((formatter::FormattedToken(token,static_cast<size_t>(0ULL),(TRY((DynamicArray<u8>::create_with({})))),(TRY((DynamicArray<u8>::create_with({})))))).debug_text()))),((*this).indent));
{
JaktInternal::ArrayIterator<formatter::State> _magic = ((((*this).states)).iterator());
for (;;){
JaktInternal::Optional<formatter::State> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
formatter::State state = (_magic_value.value());
{
warnln((StringView::from_string_literal("- State: {}"sv)),state);
}

}
}

warnln();
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).state());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::Toplevel>();size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_toplevel_context(open_parens,open_curlies,open_squares,is_extern,token)))));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY((((*this).next_in_extern_context(token)))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::Import>();bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_import_context(is_extern,token)))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::ImportList>();bool const& emitted_comma = __jakt_match_value.emitted_comma;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_import_list_context(emitted_comma,token)))));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY((((*this).next_in_implements_context(token)))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::EntityDeclaration>();formatter::Entity const& entity = __jakt_match_value.entity;
bool const& accept_generics = __jakt_match_value.accept_generics;
bool const& has_generics = __jakt_match_value.has_generics;
size_t const& generic_nesting = __jakt_match_value.generic_nesting;
bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_entity_declaration_context(entity,accept_generics,has_generics,generic_nesting,is_extern,token)))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::EntityDefinition>();formatter::Entity const& entity = __jakt_match_value.entity;
bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_entity_definition_context(entity,is_extern,((indent_change)),token)))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::StatementContext>();size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& arrow_indents = __jakt_match_value.arrow_indents;
JaktInternal::Optional<size_t> const& allow_eol = __jakt_match_value.allow_eol;
bool const& inserted_comma = __jakt_match_value.inserted_comma;
formatter::ExpressionMode const& expression_mode = __jakt_match_value.expression_mode;
size_t const& dedents_on_open_curly = __jakt_match_value.dedents_on_open_curly;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_statement_context(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,expression_mode,dedents_on_open_curly,((indent_change)),token)))));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::GenericCallTypeParams>();size_t const& open_angles = __jakt_match_value.open_angles;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_generic_call_type_params_context(open_angles,token)))));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::VariableDeclaration>();size_t const& open_parens = __jakt_match_value.open_parens;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_variable_declaration_context(open_parens,token)))));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY((((*this).next_in_restriction_list_context(token)))));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY((((*this).next_in_capture_list_context(token)))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::ParameterList>();size_t const& open_parens = __jakt_match_value.open_parens;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_parameter_list_context(open_parens,token)))));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::TypeContext>();size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& open_angles = __jakt_match_value.open_angles;
bool const& seen_start = __jakt_match_value.seen_start;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_type_context(open_parens,open_curlies,open_squares,open_angles,seen_start,token)))));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::FunctionTypeContext>();bool const& seen_final_type = __jakt_match_value.seen_final_type;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_function_type_context(seen_final_type,token)))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::MatchPattern>();size_t const& open_parens = __jakt_match_value.open_parens;
bool const& allow_multiple = __jakt_match_value.allow_multiple;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_match_pattern_context(open_parens,allow_multiple,token)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_statement_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,size_t const arrow_indents,JaktInternal::Optional<size_t> const allow_eol,bool const inserted_comma,formatter::ExpressionMode const expression_mode,size_t const dedents_on_open_curly,i64& indent_change,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 81: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_676; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::VariableDeclaration(static_cast<size_t>(0ULL)) } ))));
__jakt_var_676 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_570;

}
__jakt_label_570:; __jakt_var_676.release_value(); }));
};/*case end*/
case 84: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_677; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
if (((expression_mode).index() == 0 /* OutsideExpression */)){
TRY((((*this).push_state( formatter::State { typename formatter::State::VariableDeclaration(static_cast<size_t>(0ULL)) } ))));
}
__jakt_var_677 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_571;

}
__jakt_label_571:; __jakt_var_677.release_value(); }));
};/*case end*/
case 83: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_678; {
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_679; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_679 = indent; goto __jakt_label_573;

}
__jakt_label_573:; __jakt_var_679.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_680; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_680 = indent; goto __jakt_label_574;

}
__jakt_label_574:; __jakt_var_680.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_681; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_681 = indent; goto __jakt_label_575;

}
__jakt_label_575:; __jakt_var_681.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_682; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_682 = indent; goto __jakt_label_576;

}
__jakt_label_576:; __jakt_var_682.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_683; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_683 = indent; goto __jakt_label_577;

}
__jakt_label_577:; __jakt_var_683.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_add(dedents_on_open_curly,added_indent)) } ))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
__jakt_var_678 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_572;

}
__jakt_label_572:; __jakt_var_678.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_684; {
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_685; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_685 = indent; goto __jakt_label_579;

}
__jakt_label_579:; __jakt_var_685.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_686; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_686 = indent; goto __jakt_label_580;

}
__jakt_label_580:; __jakt_var_686.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_687; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_687 = indent; goto __jakt_label_581;

}
__jakt_label_581:; __jakt_var_687.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_688; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_688 = indent; goto __jakt_label_582;

}
__jakt_label_582:; __jakt_var_688.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_689; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_689 = indent; goto __jakt_label_583;

}
__jakt_label_583:; __jakt_var_689.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_add(dedents_on_open_curly,added_indent)) } ))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
__jakt_var_684 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_578;

}
__jakt_label_578:; __jakt_var_684.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_690; {
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_691; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_691 = indent; goto __jakt_label_585;

}
__jakt_label_585:; __jakt_var_691.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_692; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_692 = indent; goto __jakt_label_586;

}
__jakt_label_586:; __jakt_var_692.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_693; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_693 = indent; goto __jakt_label_587;

}
__jakt_label_587:; __jakt_var_693.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_694; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_694 = indent; goto __jakt_label_588;

}
__jakt_label_588:; __jakt_var_694.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_695; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_695 = indent; goto __jakt_label_589;

}
__jakt_label_589:; __jakt_var_695.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_add(dedents_on_open_curly,added_indent)) } ))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
__jakt_var_690 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_584;

}
__jakt_label_584:; __jakt_var_690.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_696; {
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_697; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_697 = indent; goto __jakt_label_591;

}
__jakt_label_591:; __jakt_var_697.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_698; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_698 = indent; goto __jakt_label_592;

}
__jakt_label_592:; __jakt_var_698.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_699; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_699 = indent; goto __jakt_label_593;

}
__jakt_label_593:; __jakt_var_699.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_700; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_700 = indent; goto __jakt_label_594;

}
__jakt_label_594:; __jakt_var_700.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_701; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_701 = indent; goto __jakt_label_595;

}
__jakt_label_595:; __jakt_var_701.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_add(dedents_on_open_curly,added_indent)) } ))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
__jakt_var_696 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_590;

}
__jakt_label_590:; __jakt_var_696.release_value(); }));
};/*case end*/
case 101: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_702; {
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_703; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_703 = indent; goto __jakt_label_597;

}
__jakt_label_597:; __jakt_var_703.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_704; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_704 = indent; goto __jakt_label_598;

}
__jakt_label_598:; __jakt_var_704.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_705; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_705 = indent; goto __jakt_label_599;

}
__jakt_label_599:; __jakt_var_705.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_706; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_706 = indent; goto __jakt_label_600;

}
__jakt_label_600:; __jakt_var_706.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_707; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_707 = indent; goto __jakt_label_601;

}
__jakt_label_601:; __jakt_var_707.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_add(dedents_on_open_curly,added_indent)) } ))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
__jakt_var_702 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_596;

}
__jakt_label_596:; __jakt_var_702.release_value(); }));
};/*case end*/
case 82: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_708; {
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_709; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_709 = indent; goto __jakt_label_603;

}
__jakt_label_603:; __jakt_var_709.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_710; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_710 = indent; goto __jakt_label_604;

}
__jakt_label_604:; __jakt_var_710.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_711; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_711 = indent; goto __jakt_label_605;

}
__jakt_label_605:; __jakt_var_711.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_712; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_712 = indent; goto __jakt_label_606;

}
__jakt_label_606:; __jakt_var_712.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_713; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_713 = indent; goto __jakt_label_607;

}
__jakt_label_607:; __jakt_var_713.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_add(dedents_on_open_curly,added_indent)) } ))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
__jakt_var_708 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_602;

}
__jakt_label_602:; __jakt_var_708.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_714; {
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_715; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_715 = indent; goto __jakt_label_609;

}
__jakt_label_609:; __jakt_var_715.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_716; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_716 = indent; goto __jakt_label_610;

}
__jakt_label_610:; __jakt_var_716.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_717; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_717 = indent; goto __jakt_label_611;

}
__jakt_label_611:; __jakt_var_717.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_718; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_718 = indent; goto __jakt_label_612;

}
__jakt_label_612:; __jakt_var_718.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_719; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_719 = indent; goto __jakt_label_613;

}
__jakt_label_613:; __jakt_var_719.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_add(dedents_on_open_curly,added_indent)) } ))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
__jakt_var_714 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_608;

}
__jakt_label_608:; __jakt_var_714.release_value(); }));
};/*case end*/
case 68: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_720; {
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 83: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_721; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_721 = indent; goto __jakt_label_615;

}
__jakt_label_615:; __jakt_var_721.release_value(); }));
};/*case end*/
case 74: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_722; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_722 = indent; goto __jakt_label_616;

}
__jakt_label_616:; __jakt_var_722.release_value(); }));
};/*case end*/
case 105: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_723; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_723 = indent; goto __jakt_label_617;

}
__jakt_label_617:; __jakt_var_723.release_value(); }));
};/*case end*/
case 77: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_724; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_724 = indent; goto __jakt_label_618;

}
__jakt_label_618:; __jakt_var_724.release_value(); }));
};/*case end*/
case 107: {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_725; {
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
__jakt_var_725 = indent; goto __jakt_label_619;

}
__jakt_label_619:; __jakt_var_725.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_add(dedents_on_open_curly,added_indent)) } ))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
__jakt_var_720 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_614;

}
__jakt_label_614:; __jakt_var_720.release_value(); }));
};/*case end*/
case 64: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_726; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_726 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 57: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 40: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))))); goto __jakt_label_620;

}
__jakt_label_620:; __jakt_var_726.release_value(); }));
};/*case end*/
case 70: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_727; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_727 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 57: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 40: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))))); goto __jakt_label_621;

}
__jakt_label_621:; __jakt_var_727.release_value(); }));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_728; {
if ((((expression_mode).index() == 1 /* BeforeExpressions */) && ((((*this).peek(static_cast<i64>(0LL)))).index() == 55 /* Eol */))){
return TRY((((*this).next())));
}
if ((((allow_eol).has_value()) && ((((allow_eol.value())) == (static_cast<size_t>(0ULL))) && ((JaktInternal::checked_add(JaktInternal::checked_add(open_parens,open_curlies),open_squares)) == (static_cast<size_t>(0ULL)))))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
size_t new_arrow_indents = arrow_indents;
JaktInternal::Optional<size_t> new_allow_eol = allow_eol;
formatter::ExpressionMode new_expression_mode =  formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ;
if (((expression_mode).index() == 1 /* BeforeExpressions */)){
(new_expression_mode =  formatter::ExpressionMode { typename formatter::ExpressionMode::BeforeExpressions() } );
}
else {
if ((((allow_eol).has_value()) && [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((allow_eol.value()),static_cast<size_t>(0ULL)))){
(new_allow_eol = JaktInternal::checked_sub((allow_eol.value()),static_cast<size_t>(1ULL)));
}
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(arrow_indents,static_cast<size_t>(0ULL))){
if ((((((((*this).dedents_to_skip)).last()).value())) == (static_cast<size_t>(1ULL)))){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))){
JaktInternal::Optional<size_t> const dummy = ((((*this).dedents_to_skip)).pop());
}
((((indent_change))) -= (static_cast<i64>(1LL)));
}
else if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((((*this).dedents_to_skip)).last()).value()),static_cast<size_t>(0ULL))){
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])) -= (static_cast<size_t>(1ULL)));
}
((new_arrow_indents--));
}
}

TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,new_arrow_indents,new_allow_eol,inserted_comma,new_expression_mode,dedents_on_open_curly) } ))));
__jakt_var_728 = TRY((((*this).formatted_token(token)))); goto __jakt_label_622;

}
__jakt_label_622:; __jakt_var_728.release_value(); }));
};/*case end*/
case 75: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_729; {
TRY((((*this).push_state( formatter::State { typename formatter::State::FunctionTypeContext(false) } ))));
__jakt_var_729 = TRY((((*this).formatted_token(token)))); goto __jakt_label_623;

}
__jakt_label_623:; __jakt_var_729.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<formatter::FormattedToken>> __jakt_var_730; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_730 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_624;

}
__jakt_label_624:; __jakt_var_730.release_value(); }));
};/*case end*/
case 93: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 4: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_731; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_731 = TRY((((*this).formatted_token(token)))); goto __jakt_label_625;

}
__jakt_label_625:; __jakt_var_731.release_value(); }));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_732; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_732 = TRY((((*this).formatted_token(token)))); goto __jakt_label_626;

}
__jakt_label_626:; __jakt_var_732.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_733; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_733 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_627;

}
__jakt_label_627:; __jakt_var_733.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 98: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 4: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_734; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_734 = TRY((((*this).formatted_token(token)))); goto __jakt_label_628;

}
__jakt_label_628:; __jakt_var_734.release_value(); }));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_735; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_735 = TRY((((*this).formatted_token(token)))); goto __jakt_label_629;

}
__jakt_label_629:; __jakt_var_735.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_736; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_736 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_630;

}
__jakt_label_630:; __jakt_var_736.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 106: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 4: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_737; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_737 = TRY((((*this).formatted_token(token)))); goto __jakt_label_631;

}
__jakt_label_631:; __jakt_var_737.release_value(); }));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_738; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_738 = TRY((((*this).formatted_token(token)))); goto __jakt_label_632;

}
__jakt_label_632:; __jakt_var_738.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_739; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_739 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_633;

}
__jakt_label_633:; __jakt_var_739.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 57: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_740; {
bool const next_is_eol = ((((*this).peek(static_cast<i64>(0LL)))).index() == 55 /* Eol */);
size_t new_arrow_indents = arrow_indents;
if (next_is_eol){
if ((!(((*this).already_seen_enclosure_in_current_line)))){
(((*this).already_seen_enclosure_in_current_line) = true);
TRY((((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)))));
}
((((indent_change))) += (static_cast<i64>(1LL)));
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])) += (static_cast<size_t>(1ULL)));
((new_arrow_indents++));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,new_arrow_indents,allow_eol,inserted_comma,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<formatter::ExpressionMode, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 9: {
return JaktInternal::ExplicitValue( formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::ExpressionMode { typename formatter::ExpressionMode::BeforeExpressions() } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),dedents_on_open_curly) } ))));
__jakt_var_740 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_634;

}
__jakt_label_634:; __jakt_var_740.release_value(); }));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_741; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_741 = TRY((((*this).formatted_token(token)))); goto __jakt_label_635;

}
__jakt_label_635:; __jakt_var_741.release_value(); }));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_742; {
if (((open_squares) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_742 = TRY((((*this).formatted_token(token)))); goto __jakt_label_636;

}
__jakt_label_636:; __jakt_var_742.release_value(); }));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_743; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_743 = TRY((((*this).formatted_token(token)))); goto __jakt_label_637;

}
__jakt_label_637:; __jakt_var_743.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_744; {
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_744 = TRY((((*this).formatted_token(token)))); goto __jakt_label_638;

}
__jakt_label_638:; __jakt_var_744.release_value(); }));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_745; {
size_t dedented = static_cast<size_t>(0ULL);
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(dedents_on_open_curly,static_cast<size_t>(0ULL))){
((((*this).indent)) -= (static_cast<size_t>(1ULL)));
(dedented = static_cast<size_t>(1ULL));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,JaktInternal::checked_sub(dedents_on_open_curly,dedented)) } ))));
__jakt_var_745 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 70: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 101: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 64: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 57: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 82: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 68: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))))); goto __jakt_label_639;

}
__jakt_label_639:; __jakt_var_745.release_value(); }));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_746; {
if (((open_curlies) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_746 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({})))),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))))); goto __jakt_label_640;

}
__jakt_label_640:; __jakt_var_746.release_value(); }));
};/*case end*/
case 86: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_747; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_747 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_641;

}
__jakt_label_641:; __jakt_var_747.release_value(); }));
};/*case end*/
case 95: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_748; {
__jakt_var_748 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_642;

}
__jakt_label_642:; __jakt_var_748.release_value(); }));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_749; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_749 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 12: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_643;

}
__jakt_label_643:; __jakt_var_749.release_value(); }));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_750; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
JaktInternal::DynamicArray<u8> const trivia = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.index()) {
case 3: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_750 = TRY((((*this).formatted_token(token,trivia,trivia)))); goto __jakt_label_644;

}
__jakt_label_644:; __jakt_var_750.release_value(); }));
};/*case end*/
case 36: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_751; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
JaktInternal::DynamicArray<u8> const trivia = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.index()) {
case 3: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_751 = TRY((((*this).formatted_token(token,trivia,trivia)))); goto __jakt_label_645;

}
__jakt_label_645:; __jakt_var_751.release_value(); }));
};/*case end*/
case 37: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_752; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
JaktInternal::DynamicArray<u8> const trivia = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.index()) {
case 3: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_752 = TRY((((*this).formatted_token(token,trivia,trivia)))); goto __jakt_label_646;

}
__jakt_label_646:; __jakt_var_752.release_value(); }));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_753; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_753 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_647;

}
__jakt_label_647:; __jakt_var_753.release_value(); }));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_754; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_754 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_648;

}
__jakt_label_648:; __jakt_var_754.release_value(); }));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_755; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_755 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_649;

}
__jakt_label_649:; __jakt_var_755.release_value(); }));
};/*case end*/
case 40: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_756; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_756 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_650;

}
__jakt_label_650:; __jakt_var_756.release_value(); }));
};/*case end*/
case 17: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_757; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_757 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_651;

}
__jakt_label_651:; __jakt_var_757.release_value(); }));
};/*case end*/
case 19: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_758; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_758 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_652;

}
__jakt_label_652:; __jakt_var_758.release_value(); }));
};/*case end*/
case 21: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_759; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_759 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_653;

}
__jakt_label_653:; __jakt_var_759.release_value(); }));
};/*case end*/
case 22: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_760; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_760 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_654;

}
__jakt_label_654:; __jakt_var_760.release_value(); }));
};/*case end*/
case 23: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_761; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_761 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_655;

}
__jakt_label_655:; __jakt_var_761.release_value(); }));
};/*case end*/
case 24: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_762; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_762 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_656;

}
__jakt_label_656:; __jakt_var_762.release_value(); }));
};/*case end*/
case 25: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_763; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_763 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_657;

}
__jakt_label_657:; __jakt_var_763.release_value(); }));
};/*case end*/
case 26: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_764; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_764 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_658;

}
__jakt_label_658:; __jakt_var_764.release_value(); }));
};/*case end*/
case 27: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_765; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_765 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_659;

}
__jakt_label_659:; __jakt_var_765.release_value(); }));
};/*case end*/
case 28: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_766; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_766 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_660;

}
__jakt_label_660:; __jakt_var_766.release_value(); }));
};/*case end*/
case 29: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_767; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_767 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_661;

}
__jakt_label_661:; __jakt_var_767.release_value(); }));
};/*case end*/
case 30: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_768; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_768 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_662;

}
__jakt_label_662:; __jakt_var_768.release_value(); }));
};/*case end*/
case 31: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_769; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_769 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_663;

}
__jakt_label_663:; __jakt_var_769.release_value(); }));
};/*case end*/
case 33: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_770; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_770 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_664;

}
__jakt_label_664:; __jakt_var_770.release_value(); }));
};/*case end*/
case 32: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_771; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_771 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_665;

}
__jakt_label_665:; __jakt_var_771.release_value(); }));
};/*case end*/
case 34: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_772; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_772 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_666;

}
__jakt_label_666:; __jakt_var_772.release_value(); }));
};/*case end*/
case 35: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_773; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_773 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_667;

}
__jakt_label_667:; __jakt_var_773.release_value(); }));
};/*case end*/
case 38: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_774; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_774 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_668;

}
__jakt_label_668:; __jakt_var_774.release_value(); }));
};/*case end*/
case 41: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_775; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_775 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_669;

}
__jakt_label_669:; __jakt_var_775.release_value(); }));
};/*case end*/
case 43: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_776; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_776 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_670;

}
__jakt_label_670:; __jakt_var_776.release_value(); }));
};/*case end*/
case 44: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_777; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_777 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_671;

}
__jakt_label_671:; __jakt_var_777.release_value(); }));
};/*case end*/
case 47: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_778; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_778 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_672;

}
__jakt_label_672:; __jakt_var_778.release_value(); }));
};/*case end*/
case 50: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_779; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_779 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_673;

}
__jakt_label_673:; __jakt_var_779.release_value(); }));
};/*case end*/
case 51: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_780; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_780 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_674;

}
__jakt_label_674:; __jakt_var_780.release_value(); }));
};/*case end*/
case 59: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_781; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_781 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_675;

}
__jakt_label_675:; __jakt_var_781.release_value(); }));
};/*case end*/
case 79: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_782; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_782 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_676;

}
__jakt_label_676:; __jakt_var_782.release_value(); }));
};/*case end*/
case 87: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_783; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_783 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_677;

}
__jakt_label_677:; __jakt_var_783.release_value(); }));
};/*case end*/
case 80: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_784; {
TRY((((*this).push_state( formatter::State { typename formatter::State::MatchPattern(static_cast<size_t>(0ULL),false) } ))));
__jakt_var_784 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_678;

}
__jakt_label_678:; __jakt_var_784.release_value(); }));
};/*case end*/
case 61: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 49: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 48: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))));
};/*case end*/
case 49: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 61: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 48: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 61: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_785; {
if ((((((*this).peek((-(static_cast<i64>(1LL)))))).index() == 3 /* Identifier */) && (!(inserted_comma)))){
((((*this).index)--));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,true, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
return TRY((((*this).formatted_token( lexer::Token { typename lexer::Token::Comma(((token).span())) } ,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({}))))))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,false, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
if (((((*this).peek(static_cast<i64>(0LL)))).index() == 7 /* LParen */)){
return TRY((((*this).formatted_token(token))));
}
if ((!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */)))){
return TRY((((*this).formatted_token(token))));
}
i64 open_angles = static_cast<i64>(1LL);
i64 lookahead_index = static_cast<i64>(2LL);
while ([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(open_angles,static_cast<i64>(0LL))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(((lookahead_index++))));
switch(__jakt_match_variant.index()) {
case 28: {
{
((open_angles) += (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
{
((open_angles) -= (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 38: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 43: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 47: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 50: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87: {
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}
if ((((open_angles) == (static_cast<i64>(0LL))) && ((((*this).peek(lookahead_index))).index() == 7 /* LParen */))){
TRY((((*this).push_state( formatter::State { typename formatter::State::GenericCallTypeParams(static_cast<size_t>(0ULL)) } ))));
}
__jakt_var_785 = TRY((((*this).formatted_token(token)))); goto __jakt_label_679;

}
__jakt_label_679:; __jakt_var_785.release_value(); }));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_786; {
if ((((((*this).peek((-(static_cast<i64>(1LL)))))).index() == 3 /* Identifier */) && (!(inserted_comma)))){
((((*this).index)--));
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,true, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
return TRY((((*this).formatted_token( lexer::Token { typename lexer::Token::Comma(((token).span())) } ,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({}))))))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,false, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
if (((((*this).peek(static_cast<i64>(0LL)))).index() == 7 /* LParen */)){
return TRY((((*this).formatted_token(token))));
}
if ((!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */)))){
return TRY((((*this).formatted_token(token))));
}
i64 open_angles = static_cast<i64>(1LL);
i64 lookahead_index = static_cast<i64>(2LL);
while ([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(open_angles,static_cast<i64>(0LL))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(((lookahead_index++))));
switch(__jakt_match_variant.index()) {
case 28: {
{
((open_angles) += (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
{
((open_angles) -= (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 38: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 43: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 47: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 50: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87: {
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}
if ((((open_angles) == (static_cast<i64>(0LL))) && ((((*this).peek(lookahead_index))).index() == 7 /* LParen */))){
TRY((((*this).push_state( formatter::State { typename formatter::State::GenericCallTypeParams(static_cast<size_t>(0ULL)) } ))));
}
__jakt_var_786 = TRY((((*this).formatted_token(token)))); goto __jakt_label_680;

}
__jakt_label_680:; __jakt_var_786.release_value(); }));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_787; {
if (((open_squares) == (static_cast<size_t>(0ULL)))){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue(TRY((((*this).next()))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token( lexer::Token { typename lexer::Token::Eol(JaktInternal::OptionalNone(),((token).span())) } )))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
__jakt_var_787 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_681;

}
__jakt_label_681:; __jakt_var_787.release_value(); }));
};/*case end*/
case 91: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_788; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::AtExpressionStart() } ,dedents_on_open_curly) } ))));
__jakt_var_788 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_682;

}
__jakt_label_682:; __jakt_var_788.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_789; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma, formatter::ExpressionMode { typename formatter::ExpressionMode::InExpression() } ,dedents_on_open_curly) } ))));
__jakt_var_789 = TRY((((*this).formatted_token(token)))); goto __jakt_label_683;

}
__jakt_label_683:; __jakt_var_789.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_generic_call_type_params_context(size_t const open_angles,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 28: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_790; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_790 = TRY((((*this).formatted_token(token)))); goto __jakt_label_684;

}
__jakt_label_684:; __jakt_var_790.release_value(); }));
};/*case end*/
case 26: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_791; {
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(open_angles,static_cast<size_t>(1ULL))){
((*this).pop_state());
}
else {
TRY((((*this).replace_state( formatter::State { typename formatter::State::GenericCallTypeParams(JaktInternal::checked_sub(open_angles,static_cast<size_t>(1ULL))) } ))));
}

__jakt_var_791 = TRY((((*this).formatted_token(token)))); goto __jakt_label_685;

}
__jakt_label_685:; __jakt_var_791.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_792; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_792 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_686;

}
__jakt_label_686:; __jakt_var_792.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_restriction_list_context(lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 52: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_793; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_793 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_687;

}
__jakt_label_687:; __jakt_var_793.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_794; {
((*this).pop_state());
__jakt_var_794 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_688;

}
__jakt_label_688:; __jakt_var_794.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<formatter::FormattedToken> formatter::Stage0::formatted_token(lexer::Token const token) const {
{
return formatter::FormattedToken(token,((*this).indent),(TRY((DynamicArray<u8>::create_with({})))),(TRY((DynamicArray<u8>::create_with({})))));
}
}

ErrorOr<formatter::FormattedToken> formatter::Stage0::formatted_token(lexer::Token const token,JaktInternal::DynamicArray<u8> const trailing_trivia,JaktInternal::DynamicArray<u8> const preceding_trivia) const {
{
return formatter::FormattedToken(token,((*this).indent),trailing_trivia,preceding_trivia);
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::formatted_peek() {
{
JaktInternal::DynamicArray<formatter::State> const states_cache = TRY((((((((*this).states))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})])).to_array())));
size_t const index_cache = ((*this).index);
JaktInternal::Optional<formatter::FormattedToken> const token = TRY((((*this).next_impl(true))));
(((*this).index) = index_cache);
(((*this).states) = states_cache);
return token;
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_type_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,size_t const open_angles,bool const seen_start,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 5: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_795; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_795 = TRY((((*this).formatted_token(token)))); goto __jakt_label_689;

}
__jakt_label_689:; __jakt_var_795.release_value(); }));
};/*case end*/
case 28: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_796; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,JaktInternal::checked_add(open_angles,static_cast<size_t>(1ULL)),seen_start) } ))));
__jakt_var_796 = TRY((((*this).formatted_token(token)))); goto __jakt_label_690;

}
__jakt_label_690:; __jakt_var_796.release_value(); }));
};/*case end*/
case 26: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_797; {
if (((open_angles) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,JaktInternal::checked_sub(open_angles,static_cast<size_t>(1ULL)),seen_start) } ))));
__jakt_var_797 = TRY((((*this).formatted_token(token)))); goto __jakt_label_691;

}
__jakt_label_691:; __jakt_var_797.release_value(); }));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_798; {
if (((JaktInternal::checked_add(JaktInternal::checked_add(JaktInternal::checked_add(open_parens,open_curlies),open_squares),open_angles)) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
__jakt_var_798 = TRY((((*this).formatted_token(token)))); goto __jakt_label_692;

}
__jakt_label_692:; __jakt_var_798.release_value(); }));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_799; {
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),open_angles,true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_799 = TRY((((*this).formatted_token(token)))); goto __jakt_label_693;

}
__jakt_label_693:; __jakt_var_799.release_value(); }));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_800; {
if (((open_squares) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),open_angles,seen_start) } ))));
__jakt_var_800 = TRY((((*this).formatted_token(token)))); goto __jakt_label_694;

}
__jakt_label_694:; __jakt_var_800.release_value(); }));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_801; {
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,open_angles,true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_801 = TRY((((*this).formatted_token(token)))); goto __jakt_label_695;

}
__jakt_label_695:; __jakt_var_801.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_802; {
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,open_angles,seen_start) } ))));
__jakt_var_802 = TRY((((*this).formatted_token(token)))); goto __jakt_label_696;

}
__jakt_label_696:; __jakt_var_802.release_value(); }));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_803; {
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,open_angles,true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_803 = TRY((((*this).formatted_token(token)))); goto __jakt_label_697;

}
__jakt_label_697:; __jakt_var_803.release_value(); }));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_804; {
if (((open_curlies) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,open_angles,seen_start) } ))));
__jakt_var_804 = TRY((((*this).formatted_token(token)))); goto __jakt_label_698;

}
__jakt_label_698:; __jakt_var_804.release_value(); }));
};/*case end*/
case 91: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_805; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
__jakt_var_805 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_699;

}
__jakt_label_699:; __jakt_var_805.release_value(); }));
};/*case end*/
case 84: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_806; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
__jakt_var_806 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_700;

}
__jakt_label_700:; __jakt_var_806.release_value(); }));
};/*case end*/
case 37: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_807; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
__jakt_var_807 = TRY((((*this).formatted_token(token)))); goto __jakt_label_701;

}
__jakt_label_701:; __jakt_var_807.release_value(); }));
};/*case end*/
case 75: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_808; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::FunctionTypeContext(false) } ))));
__jakt_var_808 = TRY((((*this).formatted_token(token)))); goto __jakt_label_702;

}
__jakt_label_702:; __jakt_var_808.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_809; {
if (((JaktInternal::checked_add(open_angles,open_parens)) == (static_cast<size_t>(0ULL)))){
((((*this).index)--));
((*this).pop_state());
return TRY((((*this).next_impl(true))));
}
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_809 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_703;

}
__jakt_label_703:; __jakt_var_809.release_value(); }));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_810; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true) } ))));
__jakt_var_810 = TRY((((*this).formatted_token(token)))); goto __jakt_label_704;

}
__jakt_label_704:; __jakt_var_810.release_value(); }));
};/*case end*/
case 104: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 16: {
{
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
};/*case end*/
case 58: {
{
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
};/*case end*/
case 57: {
{
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

formatter::Stage0::Stage0(JaktInternal::DynamicArray<lexer::Token> a_tokens, size_t a_index, JaktInternal::DynamicArray<formatter::State> a_states, size_t a_indent, bool a_already_seen_enclosure_in_current_line, JaktInternal::DynamicArray<size_t> a_dedents_to_skip, bool a_debug) :tokens(move(a_tokens)), index(move(a_index)), states(move(a_states)), indent(move(a_indent)), already_seen_enclosure_in_current_line(move(a_already_seen_enclosure_in_current_line)), dedents_to_skip(move(a_dedents_to_skip)), debug(move(a_debug)){}

formatter::State formatter::Stage0::state() const {
{
return (((((*this).states)).last()).value());
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_entity_definition_context(formatter::Entity const entity,bool const is_extern,i64& indent_change,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = entity;
switch(__jakt_match_variant.index()) {
case 1: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_811; {
((*this).pop_state());
__jakt_var_811 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({})))),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))))); goto __jakt_label_705;

}
__jakt_label_705:; __jakt_var_811.release_value(); }));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_812; {
TRY((((*this).push_state( formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern) } ))));
__jakt_var_812 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_706;

}
__jakt_label_706:; __jakt_var_812.release_value(); }));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_813; {
((*this).pop_state());
__jakt_var_813 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({})))),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))))); goto __jakt_label_707;

}
__jakt_label_707:; __jakt_var_813.release_value(); }));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_814; {
TRY((((*this).push_state( formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern) } ))));
__jakt_var_814 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_708;

}
__jakt_label_708:; __jakt_var_814.release_value(); }));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_815; {
((*this).pop_state());
__jakt_var_815 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({})))),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))))); goto __jakt_label_709;

}
__jakt_label_709:; __jakt_var_815.release_value(); }));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_816; {
TRY((((*this).push_state( formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern) } ))));
__jakt_var_816 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 55: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_710;

}
__jakt_label_710:; __jakt_var_816.release_value(); }));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::Entity::Function>();bool const& arrow = __jakt_match_value.arrow;
bool const& indented = __jakt_match_value.indented;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 57: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_817; {
bool const next_is_eol = ((((*this).peek(static_cast<i64>(0LL)))).index() == 55 /* Eol */);
TRY((((*this).replace_state( formatter::State { typename formatter::State::EntityDefinition( formatter::Entity { typename formatter::Entity::Function(true,next_is_eol) } ,is_extern) } ))));
if (next_is_eol){
if ((!(((*this).already_seen_enclosure_in_current_line)))){
(((*this).already_seen_enclosure_in_current_line) = true);
TRY((((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)))));
}
((((indent_change))) += (static_cast<i64>(1LL)));
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])) += (static_cast<size_t>(1ULL)));
}
size_t eols_allowed = static_cast<size_t>(0ULL);
if (next_is_eol){
(eols_allowed = static_cast<size_t>(1ULL));
}
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),eols_allowed,false, formatter::ExpressionMode { typename formatter::ExpressionMode::BeforeExpressions() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_817 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_711;

}
__jakt_label_711:; __jakt_var_817.release_value(); }));
};/*case end*/
case 58: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_818; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_818 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_712;

}
__jakt_label_712:; __jakt_var_818.release_value(); }));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_819; {
TRY((((*this).push_state( formatter::State { typename formatter::State::ParameterList(static_cast<size_t>(0ULL)) } ))));
__jakt_var_819 = TRY((((*this).formatted_token(token)))); goto __jakt_label_713;

}
__jakt_label_713:; __jakt_var_819.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 99: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_820; {
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),JaktInternal::OptionalNone(),false, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_820 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_714;

}
__jakt_label_714:; __jakt_var_820.release_value(); }));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_821; {
((*this).pop_state());
__jakt_var_821 = TRY((((*this).formatted_token(token)))); goto __jakt_label_715;

}
__jakt_label_715:; __jakt_var_821.release_value(); }));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_822; {
if ((!(arrow))){
((*this).pop_state());
return TRY((((*this).formatted_token(token))));
}
((*this).pop_state());
if (indented){
if ((((((((*this).dedents_to_skip)).last()).value())) == (static_cast<size_t>(1ULL)))){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))){
JaktInternal::Optional<size_t> const dummy = ((((*this).dedents_to_skip)).pop());
}
((((indent_change))) -= (static_cast<i64>(1LL)));
}
else if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((((*this).dedents_to_skip)).last()).value()),static_cast<size_t>(0ULL))){
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])) -= (static_cast<size_t>(1ULL)));
}
}
__jakt_var_822 = TRY((((*this).formatted_token(token)))); goto __jakt_label_716;

}
__jakt_label_716:; __jakt_var_822.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_extern_context(lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 96: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_823; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),true) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_823 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_717;

}
__jakt_label_717:; __jakt_var_823.release_value(); }));
};/*case end*/
case 65: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_824; {
TRY((((*this).push_state( formatter::State { typename formatter::State::EntityDeclaration(formatter::Entity::from_token(((token))),(!(((token).index() == 85 /* Namespace */))),false,static_cast<size_t>(0ULL),true) } ))));
JaktInternal::DynamicArray<u8> trailing_trivia = (TRY((DynamicArray<u8>::create_with({}))));
if ((((token).index() == 85 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).index() == 28 /* LessThan */))))){
TRY((((trailing_trivia).push(static_cast<u8>(u8' ')))));
}
__jakt_var_824 = TRY((((*this).formatted_token(token,trailing_trivia,(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_718;

}
__jakt_label_718:; __jakt_var_824.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_825; {
((*this).pop_state());
__jakt_var_825 = TRY((((*this).formatted_token(token)))); goto __jakt_label_719;

}
__jakt_label_719:; __jakt_var_825.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_function_type_context(bool const seen_final_type,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 57: {
{
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
};/*case end*/
case 9: {
{
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
};/*case end*/
case 58: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_826; {
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::FunctionTypeContext(true) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_826 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_720;

}
__jakt_label_720:; __jakt_var_826.release_value(); }));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_827; {
TRY((((*this).push_state( formatter::State { typename formatter::State::CaptureList() } ))));
__jakt_var_827 = TRY((((*this).formatted_token(token)))); goto __jakt_label_721;

}
__jakt_label_721:; __jakt_var_827.release_value(); }));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_828; {
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).push_state( formatter::State { typename formatter::State::ParameterList(static_cast<size_t>(0ULL)) } ))));
__jakt_var_828 = TRY((((*this).formatted_token(token)))); goto __jakt_label_722;

}
__jakt_label_722:; __jakt_var_828.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_829; {
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
__jakt_var_829 = TRY((((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.index()) {
case 99: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<u8>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_723;

}
__jakt_label_723:; __jakt_var_829.release_value(); }));
};/*case end*/
case 99: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_830; {
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
__jakt_var_830 = TRY((((*this).formatted_token(token)))); goto __jakt_label_724;

}
__jakt_label_724:; __jakt_var_830.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

void formatter::Stage0::pop_state() {
{
JaktInternal::Optional<formatter::State> const dummy = ((((*this).states)).pop());
}
}

lexer::Token formatter::Stage0::peek(i64 const offset) const {
{
size_t const effective_index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,lexer::Token>{
auto __jakt_enum_value = (offset);
if (__jakt_enum_value == static_cast<i64>(0LL)) {
return JaktInternal::ExplicitValue(((*this).index));
}
else {
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((JaktInternal::checked_sub(JaktInternal::checked_add((infallible_integer_cast<i64>((((*this).index)))),offset),static_cast<i64>(1LL))))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(effective_index,((((*this).tokens)).size()))){
return  lexer::Token { typename lexer::Token::Eof((((((((*this).tokens)).last()).value())).span())) } ;
}
return ((((*this).tokens))[effective_index]);
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_match_pattern_context(size_t const open_parens,bool const allow_multiple,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 7: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_831; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::MatchPattern(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),allow_multiple) } ))));
TRY((((*this).push_state( formatter::State { typename formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false, formatter::ExpressionMode { typename formatter::ExpressionMode::OutsideExpression() } ,static_cast<size_t>(0ULL)) } ))));
__jakt_var_831 = TRY((((*this).formatted_token(token)))); goto __jakt_label_725;

}
__jakt_label_725:; __jakt_var_831.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_832; {
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::MatchPattern(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),allow_multiple) } ))));
__jakt_var_832 = TRY((((*this).formatted_token(token)))); goto __jakt_label_726;

}
__jakt_label_726:; __jakt_var_832.release_value(); }));
};/*case end*/
case 55: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_833; {
if ((!(allow_multiple))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return TRY((((*this).next_impl(true))));
}
__jakt_var_833 = TRY((((*this).formatted_token(token)))); goto __jakt_label_727;

}
__jakt_label_727:; __jakt_var_833.release_value(); }));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
case 40: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_834; {
if ((!(allow_multiple))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return TRY((((*this).next_impl(true))));
}
__jakt_var_834 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_728;

}
__jakt_label_728:; __jakt_var_834.release_value(); }));
};/*case end*/
default: {
{
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return TRY((((*this).next_impl(true))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_import_list_context(bool const emitted_comma,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 10: {
{
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_835; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::ImportList(true) } ))));
__jakt_var_835 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_729;

}
__jakt_label_729:; __jakt_var_835.release_value(); }));
};/*case end*/
case 55: {
{
return TRY((((*this).next())));
}
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_836; {
JaktInternal::DynamicArray<DeprecatedString> collection = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
DeprecatedString output = TRY(DeprecatedString::from_utf8(""sv));
utility::Span const span = ((token).span());
lexer::Token local_token = token;
while ((!(((local_token).index() == 10 /* RCurly */)))){
if (((local_token).index() == 3 /* Identifier */)){
DeprecatedString const name = ((local_token).get<lexer::Token::Identifier>()).name;
TRY((((collection).push(name))));
}
(local_token = ((*this).consume()));
}
formatter::bubble_sort(collection);
bool first = true;
bool overflow = false;
size_t current_len = static_cast<size_t>(0ULL);
size_t const indent_amount = static_cast<size_t>(4ULL);
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((collection).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString item = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(JaktInternal::checked_add(JaktInternal::checked_add(current_len,((item).length())),static_cast<size_t>(2ULL)),JaktInternal::checked_sub(static_cast<size_t>(120ULL),indent_amount))){
(overflow = true);
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8("\n"sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(indent_amount)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(" "sv)))));
}

}
}

(current_len = indent_amount);
}
else if ((!(first))){
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(", "sv)))));
((current_len) += (static_cast<size_t>(2ULL)));
}
else {
(first = false);
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,item)));
((current_len) += (((item).length())));
}

}
}

if (overflow){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(indent_amount)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output = TRY((((TRY(DeprecatedString::from_utf8(" "sv))) + (output)))));
}

}
}

(output = TRY((((TRY(DeprecatedString::from_utf8("\n"sv))) + (output)))));
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8("\n"sv)))));
}
else {
(output = TRY((((TRY((((TRY(DeprecatedString::from_utf8(" "sv))) + (output))))) + (TRY(DeprecatedString::from_utf8(" "sv)))))));
}

((*this).pop_state());
((((*this).index)--));
__jakt_var_836 = TRY((((*this).formatted_token( lexer::Token { typename lexer::Token::Identifier(output,span) } )))); goto __jakt_label_730;

}
__jakt_label_730:; __jakt_var_836.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<void> formatter::Stage0::replace_state(formatter::State const state) {
{
JaktInternal::Optional<formatter::State> const dummy = ((((*this).states)).pop());
TRY((((((*this).states)).push(state))));
}
return {};
}

ErrorOr<JaktInternal::Optional<formatter::FormattedToken>> formatter::Stage0::next_in_variable_declaration_context(size_t const open_parens,lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.index()) {
case 5: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_837; {
TRY((((*this).push_state( formatter::State { typename formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } ))));
__jakt_var_837 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))); goto __jakt_label_731;

}
__jakt_label_731:; __jakt_var_837.release_value(); }));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_838; {
TRY((((*this).replace_state( formatter::State { typename formatter::State::VariableDeclaration(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL))) } ))));
__jakt_var_838 = TRY((((*this).formatted_token(token)))); goto __jakt_label_732;

}
__jakt_label_732:; __jakt_var_838.release_value(); }));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_839; {
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return TRY((((*this).next_impl(true))));
}
TRY((((*this).replace_state( formatter::State { typename formatter::State::VariableDeclaration(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL))) } ))));
__jakt_var_839 = TRY((((*this).formatted_token(token)))); goto __jakt_label_733;

}
__jakt_label_733:; __jakt_var_839.release_value(); }));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(({ Optional<formatter::FormattedToken> __jakt_var_840; {
((*this).pop_state());
__jakt_var_840 = TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))))))); goto __jakt_label_734;

}
__jakt_label_734:; __jakt_var_840.release_value(); }));
};/*case end*/
case 52: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token,(TRY((DynamicArray<u8>::create_with({static_cast<u8>(u8' ')})))),(TRY((DynamicArray<u8>::create_with({})))))))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).formatted_token(token)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<formatter::Stage0> formatter::Stage0::for_tokens(JaktInternal::DynamicArray<lexer::Token> const tokens,bool const debug) {
{
return formatter::Stage0(tokens,static_cast<size_t>(0ULL),(TRY((DynamicArray<formatter::State>::create_with({ formatter::State { typename formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false) } })))),static_cast<size_t>(0ULL),false,(TRY((DynamicArray<size_t>::create_with({static_cast<size_t>(0ULL)})))),debug);
}
}

ErrorOr<DeprecatedString> formatter::State::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Toplevel */: {
TRY(builder.append("State::Toplevel"sv));
[[maybe_unused]] auto const& that = this->template get<State::Toplevel>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}, ", that.open_parens));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_curlies: {}, ", that.open_curlies));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_squares: {}, ", that.open_squares));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_extern: {}", that.is_extern));
}
TRY(builder.append(")"sv));
break;}
case 1 /* Extern */: {
return DeprecatedString("State::Extern"sv);
break;}
case 2 /* Import */: {
TRY(builder.append("State::Import"sv));
[[maybe_unused]] auto const& that = this->template get<State::Import>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_extern: {}", that.is_extern));
}
TRY(builder.append(")"sv));
break;}
case 3 /* ImportList */: {
TRY(builder.append("State::ImportList"sv));
[[maybe_unused]] auto const& that = this->template get<State::ImportList>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("emitted_comma: {}", that.emitted_comma));
}
TRY(builder.append(")"sv));
break;}
case 4 /* EntityDeclaration */: {
TRY(builder.append("State::EntityDeclaration"sv));
[[maybe_unused]] auto const& that = this->template get<State::EntityDeclaration>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("entity: {}, ", that.entity));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("accept_generics: {}, ", that.accept_generics));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("has_generics: {}, ", that.has_generics));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("generic_nesting: {}, ", that.generic_nesting));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_extern: {}", that.is_extern));
}
TRY(builder.append(")"sv));
break;}
case 5 /* Implements */: {
return DeprecatedString("State::Implements"sv);
break;}
case 6 /* CaptureList */: {
return DeprecatedString("State::CaptureList"sv);
break;}
case 7 /* ParameterList */: {
TRY(builder.append("State::ParameterList"sv));
[[maybe_unused]] auto const& that = this->template get<State::ParameterList>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}", that.open_parens));
}
TRY(builder.append(")"sv));
break;}
case 8 /* RestrictionList */: {
return DeprecatedString("State::RestrictionList"sv);
break;}
case 9 /* EntityDefinition */: {
TRY(builder.append("State::EntityDefinition"sv));
[[maybe_unused]] auto const& that = this->template get<State::EntityDefinition>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("entity: {}, ", that.entity));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_extern: {}", that.is_extern));
}
TRY(builder.append(")"sv));
break;}
case 10 /* StatementContext */: {
TRY(builder.append("State::StatementContext"sv));
[[maybe_unused]] auto const& that = this->template get<State::StatementContext>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}, ", that.open_parens));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_curlies: {}, ", that.open_curlies));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_squares: {}, ", that.open_squares));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("arrow_indents: {}, ", that.arrow_indents));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("allow_eol: {}, ", that.allow_eol));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("inserted_comma: {}, ", that.inserted_comma));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expression_mode: {}, ", that.expression_mode));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("dedents_on_open_curly: {}", that.dedents_on_open_curly));
}
TRY(builder.append(")"sv));
break;}
case 11 /* MatchPattern */: {
TRY(builder.append("State::MatchPattern"sv));
[[maybe_unused]] auto const& that = this->template get<State::MatchPattern>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}, ", that.open_parens));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("allow_multiple: {}", that.allow_multiple));
}
TRY(builder.append(")"sv));
break;}
case 12 /* VariableDeclaration */: {
TRY(builder.append("State::VariableDeclaration"sv));
[[maybe_unused]] auto const& that = this->template get<State::VariableDeclaration>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}", that.open_parens));
}
TRY(builder.append(")"sv));
break;}
case 13 /* GenericCallTypeParams */: {
TRY(builder.append("State::GenericCallTypeParams"sv));
[[maybe_unused]] auto const& that = this->template get<State::GenericCallTypeParams>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_angles: {}", that.open_angles));
}
TRY(builder.append(")"sv));
break;}
case 14 /* TypeContext */: {
TRY(builder.append("State::TypeContext"sv));
[[maybe_unused]] auto const& that = this->template get<State::TypeContext>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_parens: {}, ", that.open_parens));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_curlies: {}, ", that.open_curlies));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_squares: {}, ", that.open_squares));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("open_angles: {}, ", that.open_angles));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("seen_start: {}", that.seen_start));
}
TRY(builder.append(")"sv));
break;}
case 15 /* FunctionTypeContext */: {
TRY(builder.append("State::FunctionTypeContext"sv));
[[maybe_unused]] auto const& that = this->template get<State::FunctionTypeContext>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("seen_final_type: {}", that.seen_final_type));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> formatter::State::name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("toplevel"sv)));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("extern"sv)));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("import"sv)));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("import list"sv)));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("implements"sv)));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("entity declaration"sv)));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("capture list"sv)));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("parameter list"sv)));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("restriction list"sv)));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("entity definition"sv)));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("statement context"sv)));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("match pattern"sv)));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("variable declaration"sv)));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("generic call type params"sv)));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<formatter::State::TypeContext>();size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& open_angles = __jakt_match_value.open_angles;
bool const& seen_start = __jakt_match_value.seen_start;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("type context (p{} c{} s{} a{} s:{})"sv)),open_parens,open_curlies,open_squares,open_angles,seen_start))));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("function type context"sv)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> formatter::ExpressionMode::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* OutsideExpression */: {
return DeprecatedString("ExpressionMode::OutsideExpression"sv);
break;}
case 1 /* BeforeExpressions */: {
return DeprecatedString("ExpressionMode::BeforeExpressions"sv);
break;}
case 2 /* AtExpressionStart */: {
return DeprecatedString("ExpressionMode::AtExpressionStart"sv);
break;}
case 3 /* InExpression */: {
return DeprecatedString("ExpressionMode::InExpression"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> formatter::BreakablePoint::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Paren */: {
TRY(builder.append("BreakablePoint::Paren"sv));
[[maybe_unused]] auto const& that = this->template get<BreakablePoint::Paren>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("point: {}, ", that.point));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("length: {}", that.length));
}
TRY(builder.append(")"sv));
break;}
case 1 /* Curly */: {
TRY(builder.append("BreakablePoint::Curly"sv));
[[maybe_unused]] auto const& that = this->template get<BreakablePoint::Curly>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("point: {}, ", that.point));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("length: {}", that.length));
}
TRY(builder.append(")"sv));
break;}
case 2 /* Square */: {
TRY(builder.append("BreakablePoint::Square"sv));
[[maybe_unused]] auto const& that = this->template get<BreakablePoint::Square>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("point: {}, ", that.point));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("length: {}", that.length));
}
TRY(builder.append(")"sv));
break;}
case 3 /* Logical */: {
TRY(builder.append("BreakablePoint::Logical"sv));
[[maybe_unused]] auto const& that = this->template get<BreakablePoint::Logical>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("point: {}, ", that.point));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("length: {}", that.length));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
size_t formatter::BreakablePoint::length() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

size_t formatter::BreakablePoint::point() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> formatter::Entity::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Struct */: {
return DeprecatedString("Entity::Struct"sv);
break;}
case 1 /* Enum */: {
return DeprecatedString("Entity::Enum"sv);
break;}
case 2 /* Namespace */: {
return DeprecatedString("Entity::Namespace"sv);
break;}
case 3 /* Function */: {
TRY(builder.append("Entity::Function"sv));
[[maybe_unused]] auto const& that = this->template get<Entity::Function>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("arrow: {}, ", that.arrow));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("indented: {}", that.indented));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
formatter::Entity formatter::Entity::from_token(lexer::Token const& token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<formatter::Entity, formatter::Entity>{
auto&& __jakt_match_variant = ((token));
switch(__jakt_match_variant.index()) {
case 96: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Struct() } );
};/*case end*/
case 65: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Struct() } );
};/*case end*/
case 110: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Struct() } );
};/*case end*/
case 71: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Enum() } );
};/*case end*/
case 85: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Namespace() } );
};/*case end*/
case 76: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Function(false,false) } );
};/*case end*/
case 75: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Function(false,false) } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( formatter::Entity { typename formatter::Entity::Struct() } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

}
} // namespace Jakt
