#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "formatter.h"
#include "parser.h"
#include "utility.h"
#include "jakt__prelude__operators.h"
namespace Jakt {
namespace formatter {
void bubble_sort(JaktInternal::DynamicArray<ByteString> values) {
{
i64 i = static_cast<i64>(0LL);
while ([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,JaktInternal::checked_sub((infallible_integer_cast<i64>((((values).size())))),static_cast<i64>(1LL)))){
i64 j = static_cast<i64>(0LL);
while ([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(j,JaktInternal::checked_sub(JaktInternal::checked_sub((infallible_integer_cast<i64>((((values).size())))),i),static_cast<i64>(1LL)))){
if (((((values)[j])) > (((values)[JaktInternal::checked_add(j,static_cast<i64>(1LL))])))){
ByteString const tmp = ((values)[j]);
(((values)[j]) = ((values)[JaktInternal::checked_add(j,static_cast<i64>(1LL))]));
(((values)[JaktInternal::checked_add(j,static_cast<i64>(1LL))]) = tmp);
}
(++(j));
}
(++(i));
}
}
}

ByteString Jakt::formatter::FormattedToken::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FormattedToken("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("token: {}, ", token);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("indent: {}, ", indent);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trailing_trivia: {}, ", trailing_trivia);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("preceding_trivia: {}", preceding_trivia);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<ByteString> Jakt::formatter::FormattedToken::debug_text() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((*this).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("Identifier: {}"sv)),name));
};/*case end*/
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("Eol: {}"sv)),comment.value_or_lazy_evaluated([&] { return (ByteString::from_utf8_without_validation(""sv)); })));
};/*case end*/
case 56 /* Eof */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Eof"sv)));
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

ErrorOr<ByteString> Jakt::formatter::FormattedToken::token_text() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((*this).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;ByteString const& quote = __jakt_match_value.quote;
JaktInternal::Optional<ByteString> const& prefix = __jakt_match_value.prefix;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}'{}'"sv)),prefix.value_or_lazy_evaluated([&] { return (ByteString::from_utf8_without_validation(""sv)); }),quote));
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("\"{}\""sv)),quote));
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;Jakt::lexer::LiteralPrefix const& prefix = __jakt_match_value.prefix;
ByteString const& number = __jakt_match_value.number;
Jakt::lexer::LiteralSuffix const& suffix = __jakt_match_value.suffix;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}{}{}"sv)),((prefix).to_string()),number,((suffix).to_string())));
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 4 /* Semicolon */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(";"sv)));
};/*case end*/
case 5 /* Colon */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(":"sv)));
};/*case end*/
case 6 /* ColonColon */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("::"sv)));
};/*case end*/
case 7 /* LParen */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("("sv)));
};/*case end*/
case 8 /* RParen */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(")"sv)));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("{"sv)));
};/*case end*/
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("}"sv)));
};/*case end*/
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("["sv)));
};/*case end*/
case 12 /* RSquare */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("]"sv)));
};/*case end*/
case 13 /* PercentSign */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("%"sv)));
};/*case end*/
case 14 /* Plus */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("+"sv)));
};/*case end*/
case 15 /* Minus */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("-"sv)));
};/*case end*/
case 16 /* Equal */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("="sv)));
};/*case end*/
case 17 /* PlusEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("+="sv)));
};/*case end*/
case 18 /* PlusPlus */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("++"sv)));
};/*case end*/
case 19 /* MinusEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("-="sv)));
};/*case end*/
case 20 /* MinusMinus */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("--"sv)));
};/*case end*/
case 21 /* AsteriskEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("*="sv)));
};/*case end*/
case 22 /* ForwardSlashEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("/="sv)));
};/*case end*/
case 23 /* PercentSignEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("%="sv)));
};/*case end*/
case 24 /* NotEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("!="sv)));
};/*case end*/
case 25 /* DoubleEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("=="sv)));
};/*case end*/
case 26 /* GreaterThan */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(">"sv)));
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(">="sv)));
};/*case end*/
case 28 /* LessThan */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("<"sv)));
};/*case end*/
case 29 /* LessThanOrEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("<="sv)));
};/*case end*/
case 30 /* LeftArithmeticShift */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("<<<"sv)));
};/*case end*/
case 31 /* LeftShift */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("<<"sv)));
};/*case end*/
case 32 /* LeftShiftEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("<<="sv)));
};/*case end*/
case 33 /* RightShift */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(">>"sv)));
};/*case end*/
case 34 /* RightArithmeticShift */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(">>>"sv)));
};/*case end*/
case 35 /* RightShiftEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(">>="sv)));
};/*case end*/
case 36 /* Asterisk */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("*"sv)));
};/*case end*/
case 37 /* Ampersand */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("&"sv)));
};/*case end*/
case 38 /* AmpersandEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("&="sv)));
};/*case end*/
case 39 /* AmpersandAmpersand */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("&&"sv)));
};/*case end*/
case 40 /* Pipe */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("|"sv)));
};/*case end*/
case 41 /* PipeEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("|="sv)));
};/*case end*/
case 42 /* PipePipe */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("||"sv)));
};/*case end*/
case 43 /* Caret */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("^"sv)));
};/*case end*/
case 44 /* CaretEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("^="sv)));
};/*case end*/
case 45 /* Dollar */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("$"sv)));
};/*case end*/
case 46 /* Tilde */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("~"sv)));
};/*case end*/
case 47 /* ForwardSlash */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("/"sv)));
};/*case end*/
case 48 /* ExclamationPoint */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("!"sv)));
};/*case end*/
case 49 /* QuestionMark */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("?"sv)));
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("??"sv)));
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("??="sv)));
};/*case end*/
case 52 /* Comma */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(","sv)));
};/*case end*/
case 53 /* Dot */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("."sv)));
};/*case end*/
case 54 /* DotDot */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(".."sv)));
};/*case end*/
case 55 /* Eol */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
};/*case end*/
case 56 /* Eof */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
};/*case end*/
case 57 /* FatArrow */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("=>"sv)));
};/*case end*/
case 58 /* Arrow */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("->"sv)));
};/*case end*/
case 59 /* And */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("and"sv)));
};/*case end*/
case 60 /* Anon */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("anon"sv)));
};/*case end*/
case 61 /* As */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("as"sv)));
};/*case end*/
case 62 /* Boxed */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("boxed"sv)));
};/*case end*/
case 63 /* Break */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("break"sv)));
};/*case end*/
case 64 /* Catch */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("catch"sv)));
};/*case end*/
case 65 /* Class */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("class"sv)));
};/*case end*/
case 66 /* Continue */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("continue"sv)));
};/*case end*/
case 67 /* Cpp */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("cpp"sv)));
};/*case end*/
case 68 /* Defer */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("defer"sv)));
};/*case end*/
case 69 /* Destructor */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("destructor"sv)));
};/*case end*/
case 70 /* Else */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("else"sv)));
};/*case end*/
case 71 /* Enum */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("enum"sv)));
};/*case end*/
case 72 /* Extern */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("extern"sv)));
};/*case end*/
case 73 /* Export */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("export"sv)));
};/*case end*/
case 74 /* False */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("false"sv)));
};/*case end*/
case 75 /* For */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("for"sv)));
};/*case end*/
case 76 /* Fn */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("fn"sv)));
};/*case end*/
case 77 /* Comptime */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("comptime"sv)));
};/*case end*/
case 78 /* If */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("if"sv)));
};/*case end*/
case 79 /* Import */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("import"sv)));
};/*case end*/
case 80 /* Relative */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("relative"sv)));
};/*case end*/
case 81 /* In */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("in"sv)));
};/*case end*/
case 82 /* Is */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("is"sv)));
};/*case end*/
case 83 /* Let */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("let"sv)));
};/*case end*/
case 84 /* Loop */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("loop"sv)));
};/*case end*/
case 85 /* Match */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("match"sv)));
};/*case end*/
case 87 /* Mut */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("mut"sv)));
};/*case end*/
case 88 /* Namespace */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("namespace"sv)));
};/*case end*/
case 89 /* Not */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("not"sv)));
};/*case end*/
case 90 /* Or */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("or"sv)));
};/*case end*/
case 92 /* Private */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("private"sv)));
};/*case end*/
case 93 /* Public */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("public"sv)));
};/*case end*/
case 94 /* Raw */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("raw"sv)));
};/*case end*/
case 96 /* Return */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("return"sv)));
};/*case end*/
case 97 /* Restricted */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("restricted"sv)));
};/*case end*/
case 98 /* Sizeof */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("sizeof"sv)));
};/*case end*/
case 99 /* Struct */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("struct"sv)));
};/*case end*/
case 100 /* This */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("this"sv)));
};/*case end*/
case 101 /* Throw */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("throw"sv)));
};/*case end*/
case 102 /* Throws */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("throws"sv)));
};/*case end*/
case 103 /* True */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("true"sv)));
};/*case end*/
case 104 /* Try */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("try"sv)));
};/*case end*/
case 105 /* Unsafe */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("unsafe"sv)));
};/*case end*/
case 107 /* Weak */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("weak"sv)));
};/*case end*/
case 108 /* While */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("while"sv)));
};/*case end*/
case 109 /* Yield */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("yield"sv)));
};/*case end*/
case 110 /* Guard */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("guard"sv)));
};/*case end*/
case 91 /* Override */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("override"sv)));
};/*case end*/
case 106 /* Virtual */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("virtual"sv)));
};/*case end*/
case 111 /* Implements */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("implements"sv)));
};/*case end*/
case 112 /* Requires */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("requires"sv)));
};/*case end*/
case 113 /* Trait */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("trait"sv)));
};/*case end*/
case 86 /* Must */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("must"sv)));
};/*case end*/
case 95 /* Reflect */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("reflect"sv)));
};/*case end*/
case 114 /* Garbage */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
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

Jakt::formatter::FormattedToken::FormattedToken(Jakt::lexer::Token a_token, size_t a_indent, JaktInternal::DynamicArray<u8> a_trailing_trivia, JaktInternal::DynamicArray<u8> a_preceding_trivia): token(move(a_token)), indent(move(a_indent)), trailing_trivia(move(a_trailing_trivia)), preceding_trivia(move(a_preceding_trivia)){}

ByteString Jakt::formatter::Stage0::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Stage0("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("tokens: {}, ", tokens);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("states: {}, ", states);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("indent: {}, ", indent);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("already_seen_enclosure_in_current_line: {}, ", already_seen_enclosure_in_current_line);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dedents_to_skip: {}, ", dedents_to_skip);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("debug: {}", debug);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<Jakt::formatter::Stage0> Jakt::formatter::Stage0::create(NonnullRefPtr<Jakt::compiler::Compiler> compiler,JaktInternal::DynamicArray<u8> const source,bool const debug) {
{
JaktInternal::DynamicArray<u8> const old_file_contents = ((compiler)->current_file_contents);
(((compiler)->current_file_contents) = source);
ScopeGuard __jakt_var_115([&] {
{
(((compiler)->current_file_contents) = old_file_contents);
}

});
JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens = Jakt::lexer::Lexer::lex(compiler);
return Jakt::formatter::Stage0(tokens,static_cast<size_t>(0ULL),DynamicArray<Jakt::formatter::State>::create_with({Jakt::formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)}),static_cast<size_t>(0ULL),false,DynamicArray<size_t>::create_with({static_cast<size_t>(0ULL)}),debug);
}
}

ErrorOr<Jakt::formatter::Stage0> Jakt::formatter::Stage0::for_tokens(JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens,bool const debug) {
{
return Jakt::formatter::Stage0(tokens,static_cast<size_t>(0ULL),DynamicArray<Jakt::formatter::State>::create_with({Jakt::formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)}),static_cast<size_t>(0ULL),false,DynamicArray<size_t>::create_with({static_cast<size_t>(0ULL)}),debug);
}
}

ErrorOr<Jakt::formatter::FormattedToken> Jakt::formatter::Stage0::formatted_token(Jakt::lexer::Token const token) const {
{
return Jakt::formatter::FormattedToken(token,((*this).indent),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
}

Jakt::formatter::FormattedToken Jakt::formatter::Stage0::formatted_token(Jakt::lexer::Token const token,JaktInternal::DynamicArray<u8> const trailing_trivia,JaktInternal::DynamicArray<u8> const preceding_trivia) const {
{
return Jakt::formatter::FormattedToken(token,((*this).indent),trailing_trivia,preceding_trivia);
}
}

Jakt::lexer::Token Jakt::formatter::Stage0::peek(i64 const offset) const {
{
size_t const effective_index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,Jakt::lexer::Token> {
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
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(effective_index,((((*this).tokens)).size()))){
return Jakt::lexer::Token::Eof((((((((*this).tokens)).last()).value())).span()));
}
return ((((*this).tokens))[effective_index]);
}
}

bool Jakt::formatter::Stage0::line_has_indent() const {
{
i64 offset = static_cast<i64>(0LL);
for (;;){
Jakt::lexer::Token const token = ((*this).peek(offset));
if (((token).__jakt_init_index() == 9 /* LCurly */)){
return true;
}
if ((((token).__jakt_init_index() == 55 /* Eol */) || ((token).__jakt_init_index() == 56 /* Eof */))){
break;
}
((offset++));
}
return false;
}
}

Jakt::lexer::Token Jakt::formatter::Stage0::consume() {
{
return ((((*this).tokens))[((((*this).index)++))]);
}
}

Jakt::formatter::State Jakt::formatter::Stage0::state() const {
{
return (((((*this).states)).last()).value());
}
}

ErrorOr<void> Jakt::formatter::Stage0::push_state(Jakt::formatter::State const state) {
{
((((*this).states)).push(state));
}
return {};
}

void Jakt::formatter::Stage0::pop_state() {
{
JaktInternal::Optional<Jakt::formatter::State> const dummy = ((((*this).states)).pop());
}
}

ErrorOr<void> Jakt::formatter::Stage0::replace_state(Jakt::formatter::State const state) {
{
JaktInternal::Optional<Jakt::formatter::State> const dummy = ((((*this).states)).pop());
((((*this).states)).push(state));
}
return {};
}

JaktInternal::DynamicArray<u8> Jakt::formatter::Stage0::to_array(ByteString const x) {
{
JaktInternal::DynamicArray<u8> res = DynamicArray<u8>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((x).length()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((res).push(((x).byte_at(i))));
}

}
}

return res;
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::formatted_peek() {
{
JaktInternal::DynamicArray<Jakt::formatter::State> const states_cache = ((((((*this).states))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})])).to_array());
size_t const index_cache = ((*this).index);
JaktInternal::Optional<Jakt::formatter::FormattedToken> const token = TRY((((*this).next_impl(true))));
(((*this).index) = index_cache);
(((*this).states) = states_cache);
return token;
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next() {
{
return ((((*this).next_impl(false))));
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_extern_context(Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 99 /* Struct */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),true)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 65 /* Class */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),true)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_toplevel_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,bool const is_extern,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 72 /* Extern */: {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 65 /* Class */: {
{
TRY((((*this).push_state(Jakt::formatter::State::Extern()))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* Struct */: {
{
TRY((((*this).push_state(Jakt::formatter::State::Extern()))));
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
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
{
if ((((name) == ((ByteString::from_utf8_without_validation("type"sv)))) && ((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 3 /* Identifier */))){
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),true,false,static_cast<size_t>(0ULL),is_extern)))));
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({})));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 71 /* Enum */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 65 /* Class */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 99 /* Struct */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 113 /* Trait */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 76 /* Fn */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 77 /* Comptime */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 88 /* Namespace */: {
{
TRY((((*this).push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(((token))),(!(((token).__jakt_init_index() == 88 /* Namespace */))),false,static_cast<size_t>(0ULL),is_extern)))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((((token).__jakt_init_index() == 88 /* Namespace */) || (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))))){
((trailing_trivia).push(static_cast<u8>(u8' ')));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* LSquare */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::Toplevel(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* RSquare */: {
{
if (((open_squares) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::Toplevel(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* LParen */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::Toplevel(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
{
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::Toplevel(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* LCurly */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::Toplevel(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* RCurly */: {
{
if (((open_curlies) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::Toplevel(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* Colon */: {
{
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 79 /* Import */: {
{
TRY((((*this).push_state(Jakt::formatter::State::Import(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 72 /* Extern */))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 93 /* Public */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 92 /* Private */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 106 /* Virtual */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 91 /* Override */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 62 /* Boxed */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 105 /* Unsafe */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 97 /* Restricted */: {
{
TRY((((*this).push_state(Jakt::formatter::State::RestrictionList()))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 16 /* Equal */: {
{
TRY((((*this).push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false,Jakt::formatter::ExpressionMode::AtExpressionStart(),static_cast<size_t>(0ULL))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_import_context(bool const is_extern,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 72 /* Extern */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 61 /* As */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 3 /* Identifier */: {
{
if (((!(is_extern)) && ((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 7 /* LParen */))){
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})));
}
if (((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 6 /* ColonColon */)){
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})));
}
if (((!(is_extern)) && ((!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 9 /* LCurly */))) && (!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 61 /* As */)))))){
((*this).pop_state());
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 9 /* LCurly */: {
{
if (is_extern){
TRY((((*this).push_state(Jakt::formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern)))));
}
else {
TRY((((*this).push_state(Jakt::formatter::State::ImportList(true)))));
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* RCurly */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
{
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* ColonColon */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_implements_context(Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_import_list_context(bool const emitted_comma,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
};/*case end*/
case 52 /* Comma */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::ImportList(true)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
return ((((*this).next())));
}
};/*case end*/
default: {
{
JaktInternal::DynamicArray<ByteString> collection = DynamicArray<ByteString>::create_with({});
ByteString output = (ByteString::from_utf8_without_validation(""sv));
Jakt::utility::Span const span = ((token).span());
Jakt::lexer::Token local_token = token;
while ((!(((local_token).__jakt_init_index() == 10 /* RCurly */)))){
if (((local_token).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (local_token).as.Identifier.name;
((collection).push(name));
}
(local_token = ((*this).consume()));
}
Jakt::formatter::bubble_sort(collection);
bool first = true;
bool overflow = false;
size_t current_len = static_cast<size_t>(0ULL);
size_t const indent_amount = static_cast<size_t>(4ULL);
{
JaktInternal::ArrayIterator<ByteString> _magic = ((collection).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString item = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(JaktInternal::checked_add(JaktInternal::checked_add(current_len,((item).length())),static_cast<size_t>(2ULL)),JaktInternal::checked_sub(static_cast<size_t>(120ULL),indent_amount))){
(overflow = true);
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("\n"sv)));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(indent_amount)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(" "sv)));
}

}
}

(current_len = indent_amount);
}
else if ((!(first))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
((current_len) += (static_cast<size_t>(2ULL)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,item);
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
(output = (((ByteString::from_utf8_without_validation(" "sv))) + (output)));
}

}
}

(output = (((ByteString::from_utf8_without_validation("\n"sv))) + (output)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("\n"sv)));
}
else {
(output = (((((ByteString::from_utf8_without_validation(" "sv))) + (output))) + ((ByteString::from_utf8_without_validation(" "sv)))));
}

((*this).pop_state());
((((*this).index)--));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(Jakt::lexer::Token::Identifier(output,span),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_entity_declaration_context(Jakt::formatter::Entity const entity,bool const accept_generics,bool const has_generics,size_t const generic_nesting,bool const is_extern,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */: {
{
if (accept_generics){
TRY((((*this).replace_state(Jakt::formatter::State::EntityDeclaration(entity,accept_generics,true,JaktInternal::checked_add(generic_nesting,static_cast<size_t>(1ULL)),is_extern)))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* GreaterThan */: {
{
if (accept_generics){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(generic_nesting,static_cast<size_t>(1ULL))){
TRY((((*this).replace_state(Jakt::formatter::State::EntityDeclaration(entity,accept_generics,has_generics,JaktInternal::checked_sub(generic_nesting,static_cast<size_t>(1ULL)),is_extern)))));
}
else {
TRY((((*this).replace_state(Jakt::formatter::State::EntityDefinition(entity,is_extern)))));
}

}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* Identifier */: {
{
if ((((generic_nesting) == (static_cast<size_t>(0ULL))) && ((!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */))) && (!(has_generics))))){
TRY((((*this).replace_state(Jakt::formatter::State::EntityDefinition(entity,is_extern)))));
}
if (((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 111 /* Implements */)){
TRY((((*this).push_state(Jakt::formatter::State::Implements()))));
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({})));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 10 /* RCurly */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 93 /* Public */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 92 /* Private */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 106 /* Virtual */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 91 /* Override */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 97 /* Restricted */: {
{
TRY((((*this).push_state(Jakt::formatter::State::RestrictionList()))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 112 /* Requires */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_entity_definition_context(Jakt::formatter::Entity const entity,bool const is_extern,i64& indent_change,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = entity;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* LCurly */: {
{
TRY((((*this).push_state(Jakt::formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* Colon */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 16 /* Equal */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
};/*case end*/
case 3 /* Identifier */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 0 /* Struct */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* LCurly */: {
{
TRY((((*this).push_state(Jakt::formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* Colon */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 16 /* Equal */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
};/*case end*/
case 3 /* Identifier */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 2 /* Namespace */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* LCurly */: {
{
TRY((((*this).push_state(Jakt::formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* Colon */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 16 /* Equal */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
};/*case end*/
case 3 /* Identifier */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;bool const& arrow = __jakt_match_value.arrow;
bool const& indented = __jakt_match_value.indented;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 57 /* FatArrow */: {
{
bool const next_is_eol = ((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 55 /* Eol */);
TRY((((*this).replace_state(Jakt::formatter::State::EntityDefinition(Jakt::formatter::Entity::Function(true,next_is_eol),is_extern)))));
if (next_is_eol){
if ((!(((*this).already_seen_enclosure_in_current_line)))){
(((*this).already_seen_enclosure_in_current_line) = true);
((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)));
}
((((indent_change))) += (static_cast<i64>(1LL)));
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])) += (static_cast<size_t>(1ULL)));
}
size_t eols_allowed = static_cast<size_t>(0ULL);
if (next_is_eol){
(eols_allowed = static_cast<size_t>(1ULL));
}
TRY((((*this).push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),eols_allowed,false,Jakt::formatter::ExpressionMode::BeforeExpressions(),static_cast<size_t>(0ULL))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 58 /* Arrow */: {
{
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* LParen */: {
{
TRY((((*this).push_state(Jakt::formatter::State::ParameterList(static_cast<size_t>(0ULL))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 102 /* Throws */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 9 /* LCurly */: {
{
TRY((((*this).push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),JaktInternal::OptionalNone(),false,Jakt::formatter::ExpressionMode::OutsideExpression(),static_cast<size_t>(0ULL))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* RCurly */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
if ((!(arrow))){
((*this).pop_state());
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})));
}
((*this).pop_state());
if (indented){
if ((((((((*this).dedents_to_skip)).last()).value())) == (static_cast<size_t>(1ULL)))){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
else if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((((*this).dedents_to_skip)).last()).value()),static_cast<size_t>(0ULL))){
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])) -= (static_cast<size_t>(1ULL)));
}
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_statement_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,size_t const arrow_indents,JaktInternal::Optional<size_t> const allow_eol,bool const inserted_comma,Jakt::formatter::ExpressionMode const expression_mode,size_t const dedents_on_open_curly,i64& indent_change,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 83 /* Let */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
TRY((((*this).push_state(Jakt::formatter::State::VariableDeclaration(static_cast<size_t>(0ULL))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 87 /* Mut */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
if (((expression_mode).__jakt_init_index() == 0 /* OutsideExpression */)){
TRY((((*this).push_state(Jakt::formatter::State::VariableDeclaration(static_cast<size_t>(0ULL))))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 85 /* Match */: {
{
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
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
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent))))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
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
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent))))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
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
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent))))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
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
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent))))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 104 /* Try */: {
{
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
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
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent))))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 84 /* Loop */: {
{
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
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
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent))))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
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
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent))))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 68 /* Defer */: {
{
size_t const added_indent = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 75 /* For */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 108 /* While */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 78 /* If */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 110 /* Guard */: {
{
size_t indent = static_cast<size_t>(1ULL);
if (((*this).line_has_indent())){
(indent = static_cast<size_t>(0ULL));
}
return JaktInternal::ExplicitValue<size_t>(indent);
}
VERIFY_NOT_REACHED();
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
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent))))));
((((indent_change))) += ((infallible_integer_cast<i64>((added_indent)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 64 /* Catch */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 57 /* FatArrow */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 40 /* Pipe */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 70 /* Else */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 57 /* FatArrow */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 40 /* Pipe */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
if ((((expression_mode).__jakt_init_index() == 1 /* BeforeExpressions */) && ((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 55 /* Eol */))){
return ((((*this).next())));
}
if ((((allow_eol).has_value()) && ((((allow_eol.value())) == (static_cast<size_t>(0ULL))) && ((JaktInternal::checked_add(JaktInternal::checked_add(open_parens,open_curlies),open_squares)) == (static_cast<size_t>(0ULL)))))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
size_t new_arrow_indents = arrow_indents;
JaktInternal::Optional<size_t> new_allow_eol = allow_eol;
Jakt::formatter::ExpressionMode new_expression_mode = Jakt::formatter::ExpressionMode::OutsideExpression();
if (((expression_mode).__jakt_init_index() == 1 /* BeforeExpressions */)){
(new_expression_mode = Jakt::formatter::ExpressionMode::BeforeExpressions());
}
else {
if ((((allow_eol).has_value()) && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((allow_eol.value()),static_cast<size_t>(0ULL)))){
(new_allow_eol = JaktInternal::checked_sub((allow_eol.value()),static_cast<size_t>(1ULL)));
}
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(arrow_indents,static_cast<size_t>(0ULL))){
if ((((((((*this).dedents_to_skip)).last()).value())) == (static_cast<size_t>(1ULL)))){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
else if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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

TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,new_arrow_indents,new_allow_eol,inserted_comma,new_expression_mode,dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 76 /* Fn */: {
{
TRY((((*this).push_state(Jakt::formatter::State::FunctionTypeContext(false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 96 /* Return */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* Semicolon */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 101 /* Throw */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* Semicolon */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 109 /* Yield */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* Semicolon */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 57 /* FatArrow */: {
{
bool const next_is_eol = ((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 55 /* Eol */);
size_t new_arrow_indents = arrow_indents;
if (next_is_eol){
if ((!(((*this).already_seen_enclosure_in_current_line)))){
(((*this).already_seen_enclosure_in_current_line) = true);
((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)));
}
((((indent_change))) += (static_cast<i64>(1LL)));
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])) += (static_cast<size_t>(1ULL)));
((new_arrow_indents++));
}
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,new_arrow_indents,allow_eol,inserted_comma,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::formatter::ExpressionMode, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(Jakt::formatter::ExpressionMode::OutsideExpression());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::ExpressionMode::BeforeExpressions());
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* LSquare */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* RSquare */: {
{
if (((open_squares) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* LParen */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
{
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* LCurly */: {
{
size_t dedented = static_cast<size_t>(0ULL);
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(dedents_on_open_curly,static_cast<size_t>(0ULL))){
((((*this).indent)) -= (static_cast<size_t>(1ULL)));
(dedented = static_cast<size_t>(1ULL));
}
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_sub(dedents_on_open_curly,dedented))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* AtExpressionStart */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 1 /* BeforeExpressions */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 70 /* Else */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 104 /* Try */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 64 /* Catch */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 16 /* Equal */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 57 /* FatArrow */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 84 /* Loop */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 68 /* Defer */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* RCurly */: {
{
if (((open_curlies) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 89 /* Not */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 98 /* Sizeof */: {
{
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* Colon */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 15 /* Minus */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
JaktInternal::DynamicArray<u8> const trivia = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* InExpression */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trivia,trivia)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 36 /* Asterisk */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
JaktInternal::DynamicArray<u8> const trivia = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* InExpression */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trivia,trivia)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 37 /* Ampersand */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
JaktInternal::DynamicArray<u8> const trivia = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* InExpression */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,trivia,trivia)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 13 /* PercentSign */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 14 /* Plus */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* Equal */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 40 /* Pipe */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 17 /* PlusEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 19 /* MinusEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* AsteriskEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* ForwardSlashEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 23 /* PercentSignEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* NotEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* DoubleEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* GreaterThan */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 28 /* LessThan */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 29 /* LessThanOrEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 30 /* LeftArithmeticShift */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 31 /* LeftShift */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 33 /* RightShift */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 32 /* LeftShiftEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 34 /* RightArithmeticShift */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 35 /* RightShiftEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 38 /* AmpersandEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 41 /* PipeEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 43 /* Caret */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 44 /* CaretEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 47 /* ForwardSlash */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 59 /* And */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 81 /* In */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 90 /* Or */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 82 /* Is */: {
{
TRY((((*this).push_state(Jakt::formatter::State::MatchPattern(static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 61 /* As */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 49 /* QuestionMark */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
case 48 /* ExclamationPoint */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
};/*case end*/
case 49 /* QuestionMark */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 61 /* As */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 48 /* ExclamationPoint */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek((-(static_cast<i64>(1LL)))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 61 /* As */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* Identifier */: {
{
if ((((((*this).peek((-(static_cast<i64>(1LL)))))).__jakt_init_index() == 3 /* Identifier */) && (!(inserted_comma)))){
((((*this).index)--));
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,true,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly)))));
return ((*this).formatted_token(Jakt::lexer::Token::Comma(((token).span())),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({})));
}
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,false,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly)))));
if (((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 7 /* LParen */)){
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})));
}
if ((!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */)))){
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})));
}
i64 open_angles = static_cast<i64>(1LL);
i64 lookahead_index = static_cast<i64>(2LL);
while ([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(open_angles,static_cast<i64>(0LL))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(((lookahead_index++))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */: {
{
((open_angles) += (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* GreaterThan */: {
{
((open_angles) -= (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* PercentSign */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* Plus */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15 /* Minus */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* Equal */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* PlusEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* MinusEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* AsteriskEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* ForwardSlashEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* PercentSignEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* NotEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* DoubleEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* LessThanOrEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* LeftArithmeticShift */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31 /* LeftShift */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32 /* LeftShiftEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34 /* RightArithmeticShift */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35 /* RightShiftEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36 /* Asterisk */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 38 /* AmpersandEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40 /* Pipe */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41 /* PipeEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 43 /* Caret */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44 /* CaretEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 47 /* ForwardSlash */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59 /* And */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 81 /* In */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 82 /* Is */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Or */: {
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
if ((((open_angles) == (static_cast<i64>(0LL))) && ((((*this).peek(lookahead_index))).__jakt_init_index() == 7 /* LParen */))){
TRY((((*this).push_state(Jakt::formatter::State::GenericCallTypeParams(static_cast<size_t>(0ULL))))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* Number */: {
{
if ((((((*this).peek((-(static_cast<i64>(1LL)))))).__jakt_init_index() == 3 /* Identifier */) && (!(inserted_comma)))){
((((*this).index)--));
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,true,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly)))));
return ((*this).formatted_token(Jakt::lexer::Token::Comma(((token).span())),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({})));
}
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,false,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly)))));
if (((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 7 /* LParen */)){
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})));
}
if ((!(((((*this).peek(static_cast<i64>(0LL)))).__jakt_init_index() == 28 /* LessThan */)))){
return ((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})));
}
i64 open_angles = static_cast<i64>(1LL);
i64 lookahead_index = static_cast<i64>(2LL);
while ([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(open_angles,static_cast<i64>(0LL))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(((lookahead_index++))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */: {
{
((open_angles) += (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* GreaterThan */: {
{
((open_angles) -= (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* PercentSign */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* Plus */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15 /* Minus */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* Equal */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* PlusEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* MinusEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* AsteriskEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* ForwardSlashEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* PercentSignEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* NotEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* DoubleEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* LessThanOrEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* LeftArithmeticShift */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31 /* LeftShift */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32 /* LeftShiftEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34 /* RightArithmeticShift */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35 /* RightShiftEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36 /* Asterisk */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 38 /* AmpersandEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40 /* Pipe */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41 /* PipeEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 43 /* Caret */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44 /* CaretEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 47 /* ForwardSlash */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59 /* And */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 81 /* In */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 82 /* Is */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Or */: {
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
if ((((open_angles) == (static_cast<i64>(0LL))) && ((((*this).peek(lookahead_index))).__jakt_init_index() == 7 /* LParen */))){
TRY((((*this).push_state(Jakt::formatter::State::GenericCallTypeParams(static_cast<size_t>(0ULL))))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* Semicolon */: {
{
if (((open_squares) == (static_cast<size_t>(0ULL)))){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(TRY((((*this).next()))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(Jakt::lexer::Token::Eol(JaktInternal::OptionalNone(),((token).span())),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 94 /* Raw */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 95 /* Reflect */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(Jakt::formatter::FormattedToken(token,((*this).indent),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({})));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_generic_call_type_params_context(size_t const open_angles,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */: {
{
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* GreaterThan */: {
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(open_angles,static_cast<size_t>(1ULL))){
((*this).pop_state());
}
else {
TRY((((*this).replace_state(Jakt::formatter::State::GenericCallTypeParams(JaktInternal::checked_sub(open_angles,static_cast<size_t>(1ULL)))))));
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
{
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_variable_declaration_context(size_t const open_parens,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Colon */: {
{
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* LParen */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::VariableDeclaration(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
{
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::VariableDeclaration(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* Equal */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_restriction_list_context(Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 52 /* Comma */: {
{
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_parameter_list_context(size_t const open_parens,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 60 /* Anon */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 87 /* Mut */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 5 /* Colon */: {
{
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 16 /* Equal */: {
{
TRY((((*this).push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false,Jakt::formatter::ExpressionMode::AtExpressionStart(),static_cast<size_t>(0ULL))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* LParen */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::ParameterList(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
{
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::ParameterList(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_type_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,size_t const open_angles,bool const seen_start,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Colon */: {
{
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 28 /* LessThan */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,JaktInternal::checked_add(open_angles,static_cast<size_t>(1ULL)),seen_start)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* GreaterThan */: {
{
if (((open_angles) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,JaktInternal::checked_sub(open_angles,static_cast<size_t>(1ULL)),seen_start)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
if (((JaktInternal::checked_add(JaktInternal::checked_add(JaktInternal::checked_add(open_parens,open_curlies),open_squares),open_angles)) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* LSquare */: {
{
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),open_angles,true)))));
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* RSquare */: {
{
if (((open_squares) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),open_angles,seen_start)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* LParen */: {
{
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,open_angles,true)))));
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
{
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,open_angles,seen_start)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* LCurly */: {
{
if (seen_start){
((((*this).index)--));
((*this).pop_state());
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,open_angles,true)))));
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* RCurly */: {
{
if (((open_curlies) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,open_angles,seen_start)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 94 /* Raw */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 87 /* Mut */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 37 /* Ampersand */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 76 /* Fn */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true)))));
TRY((((*this).push_state(Jakt::formatter::State::FunctionTypeContext(false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
{
if (((JaktInternal::checked_add(open_angles,open_parens)) == (static_cast<size_t>(0ULL)))){
((((*this).index)--));
((*this).pop_state());
return ((((*this).next_impl(true))));
}
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* Identifier */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 107 /* Weak */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 16 /* Equal */: {
{
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
};/*case end*/
case 58 /* Arrow */: {
{
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
};/*case end*/
case 57 /* FatArrow */: {
{
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_capture_list_context(Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
{
((*this).pop_state());
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 52 /* Comma */: {
{
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 87 /* Mut */: {
{
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_function_type_context(bool const seen_final_type,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 57 /* FatArrow */: {
{
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
};/*case end*/
case 9 /* LCurly */: {
{
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
};/*case end*/
case 58 /* Arrow */: {
{
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::FunctionTypeContext(true)))));
TRY((((*this).push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* LSquare */: {
{
TRY((((*this).push_state(Jakt::formatter::State::CaptureList()))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* LParen */: {
{
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
TRY((((*this).push_state(Jakt::formatter::State::ParameterList(static_cast<size_t>(0ULL))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
{
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<u8>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 102 /* Throws */: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<u8>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 102 /* Throws */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
default: {
{
if (seen_final_type){
((*this).pop_state());
((((*this).index)--));
return ((((*this).next_impl(true))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_match_pattern_context(size_t const open_parens,bool const allow_multiple,Jakt::lexer::Token const token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
{
TRY((((*this).replace_state(Jakt::formatter::State::MatchPattern(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),allow_multiple)))));
TRY((((*this).push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false,Jakt::formatter::ExpressionMode::OutsideExpression(),static_cast<size_t>(0ULL))))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* RParen */: {
{
if (((open_parens) == (static_cast<size_t>(0ULL)))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return ((((*this).next_impl(true))));
}
TRY((((*this).replace_state(Jakt::formatter::State::MatchPattern(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),allow_multiple)))));
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 55 /* Eol */: {
{
if ((!(allow_multiple))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return ((((*this).next_impl(true))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* Identifier */: {
return JaktInternal::ExplicitValue(((*this).formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))));
};/*case end*/
case 40 /* Pipe */: {
{
if ((!(allow_multiple))){
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return ((((*this).next_impl(true))));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::formatter::FormattedToken>>(((*this).formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
((*this).pop_state());
((((*this).index)) -= (static_cast<size_t>(1ULL)));
return ((((*this).next_impl(true))));
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

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_impl(bool const reconsume) {
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((*this).index),((((*this).tokens)).size()))){
return JaktInternal::OptionalNone();
}
if ((((((*this).states)).is_empty()) && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((*this).index),((((*this).tokens)).size())))){
Jakt::abort();
}
Jakt::lexer::Token token = ((*this).consume());
i64 indent_change = static_cast<i64>(0LL);
if ((!(reconsume))){
if (((!(((*this).already_seen_enclosure_in_current_line))) && ((((token).__jakt_init_index() == 7 /* LParen */) || ((token).__jakt_init_index() == 9 /* LCurly */)) || ((token).__jakt_init_index() == 11 /* LSquare */)))){
(((*this).already_seen_enclosure_in_current_line) = true);
((((*this).dedents_to_skip)).push(static_cast<size_t>(0ULL)));
(indent_change = static_cast<i64>(1LL));
}
else if (((token).__jakt_init_index() == 55 /* Eol */)){
(((*this).already_seen_enclosure_in_current_line) = false);
}
if (((((token).__jakt_init_index() == 7 /* LParen */) || ((token).__jakt_init_index() == 9 /* LCurly */)) || ((token).__jakt_init_index() == 11 /* LSquare */))){
((((((*this).dedents_to_skip))[JaktInternal::checked_sub(((((*this).dedents_to_skip)).size()),static_cast<size_t>(1ULL))])++));
}
if (((((token).__jakt_init_index() == 8 /* RParen */) || ((token).__jakt_init_index() == 10 /* RCurly */)) || ((token).__jakt_init_index() == 12 /* RSquare */))){
if ((((((((*this).dedents_to_skip)).last()).value())) == (static_cast<size_t>(1ULL)))){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
else if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
ScopeGuard __jakt_var_116([&] {
{
if ([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(indent_change,static_cast<i64>(0LL))){
((((*this).indent)) += ((infallible_integer_cast<size_t>((indent_change)))));
}
else if ([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
warnln((StringView::from_string_literal("Token: {} -- Indent: {}"sv)),TRY((((Jakt::formatter::FormattedToken(token,static_cast<size_t>(0ULL),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}))).debug_text()))),((*this).indent));
{
JaktInternal::ArrayIterator<Jakt::formatter::State> _magic = ((((*this).states)).iterator());
for (;;){
JaktInternal::Optional<Jakt::formatter::State> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::formatter::State state = (_magic_value.value());
{
warnln((StringView::from_string_literal("- State: {}"sv)),state);
}

}
}

warnln();
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::FormattedToken>, ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>>>{
auto&& __jakt_match_variant = ((*this).state());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Toplevel */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Toplevel;size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_toplevel_context(open_parens,open_curlies,open_squares,is_extern,token)))));
};/*case end*/
case 1 /* Extern */: {
return JaktInternal::ExplicitValue(TRY((((*this).next_in_extern_context(token)))));
};/*case end*/
case 2 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_import_context(is_extern,token)))));
};/*case end*/
case 3 /* ImportList */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ImportList;bool const& emitted_comma = __jakt_match_value.emitted_comma;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_import_list_context(emitted_comma,token)))));
};/*case end*/
case 5 /* Implements */: {
return JaktInternal::ExplicitValue(TRY((((*this).next_in_implements_context(token)))));
};/*case end*/
case 4 /* EntityDeclaration */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EntityDeclaration;Jakt::formatter::Entity const& entity = __jakt_match_value.entity;
bool const& accept_generics = __jakt_match_value.accept_generics;
bool const& has_generics = __jakt_match_value.has_generics;
size_t const& generic_nesting = __jakt_match_value.generic_nesting;
bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_entity_declaration_context(entity,accept_generics,has_generics,generic_nesting,is_extern,token)))));
};/*case end*/
case 9 /* EntityDefinition */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EntityDefinition;Jakt::formatter::Entity const& entity = __jakt_match_value.entity;
bool const& is_extern = __jakt_match_value.is_extern;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_entity_definition_context(entity,is_extern,((indent_change)),token)))));
};/*case end*/
case 10 /* StatementContext */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StatementContext;size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& arrow_indents = __jakt_match_value.arrow_indents;
JaktInternal::Optional<size_t> const& allow_eol = __jakt_match_value.allow_eol;
bool const& inserted_comma = __jakt_match_value.inserted_comma;
Jakt::formatter::ExpressionMode const& expression_mode = __jakt_match_value.expression_mode;
size_t const& dedents_on_open_curly = __jakt_match_value.dedents_on_open_curly;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_statement_context(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,expression_mode,dedents_on_open_curly,((indent_change)),token)))));
};/*case end*/
case 13 /* GenericCallTypeParams */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericCallTypeParams;size_t const& open_angles = __jakt_match_value.open_angles;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_generic_call_type_params_context(open_angles,token)))));
};/*case end*/
case 12 /* VariableDeclaration */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VariableDeclaration;size_t const& open_parens = __jakt_match_value.open_parens;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_variable_declaration_context(open_parens,token)))));
};/*case end*/
case 8 /* RestrictionList */: {
return JaktInternal::ExplicitValue(TRY((((*this).next_in_restriction_list_context(token)))));
};/*case end*/
case 6 /* CaptureList */: {
return JaktInternal::ExplicitValue(TRY((((*this).next_in_capture_list_context(token)))));
};/*case end*/
case 7 /* ParameterList */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ParameterList;size_t const& open_parens = __jakt_match_value.open_parens;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_parameter_list_context(open_parens,token)))));
};/*case end*/
case 14 /* TypeContext */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeContext;size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& open_angles = __jakt_match_value.open_angles;
bool const& seen_start = __jakt_match_value.seen_start;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_type_context(open_parens,open_curlies,open_squares,open_angles,seen_start,token)))));
};/*case end*/
case 15 /* FunctionTypeContext */: {
auto&& __jakt_match_value = __jakt_match_variant.as.FunctionTypeContext;bool const& seen_final_type = __jakt_match_value.seen_final_type;
return JaktInternal::ExplicitValue(TRY((((*this).next_in_function_type_context(seen_final_type,token)))));
};/*case end*/
case 11 /* MatchPattern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MatchPattern;size_t const& open_parens = __jakt_match_value.open_parens;
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

Jakt::formatter::Stage0::Stage0(JaktInternal::DynamicArray<Jakt::lexer::Token> a_tokens, size_t a_index, JaktInternal::DynamicArray<Jakt::formatter::State> a_states, size_t a_indent, bool a_already_seen_enclosure_in_current_line, JaktInternal::DynamicArray<size_t> a_dedents_to_skip, bool a_debug): tokens(move(a_tokens)), index(move(a_index)), states(move(a_states)), indent(move(a_indent)), already_seen_enclosure_in_current_line(move(a_already_seen_enclosure_in_current_line)), dedents_to_skip(move(a_dedents_to_skip)), debug(move(a_debug)){}

ByteString Jakt::formatter::ReflowState::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ReflowState("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("token: {}, ", token);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("state: {}, ", state);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enclosures_to_ignore: {}", enclosures_to_ignore);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::formatter::ReflowState::ReflowState(Jakt::formatter::FormattedToken a_token, Jakt::formatter::State a_state, size_t a_enclosures_to_ignore): token(move(a_token)), state(move(a_state)), enclosures_to_ignore(move(a_enclosures_to_ignore)){}

ByteString Jakt::formatter::Formatter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Formatter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("token_provider: {}, ", token_provider);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("max_allowed_line_length: {}, ", max_allowed_line_length);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_line: {}, ", current_line);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_line_length: {}, ", current_line_length);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("breakable_points_in_current_line: {}, ", breakable_points_in_current_line);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("tokens_to_reflow: {}, ", tokens_to_reflow);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("replace_commas_in_enclosure: {}, ", replace_commas_in_enclosure);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enclosures_to_ignore: {}, ", enclosures_to_ignore);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("in_condition_expr: {}, ", in_condition_expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("in_condition_expr_indented: {}, ", in_condition_expr_indented);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("logical_break_indent: {}, ", logical_break_indent);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("empty_line_count: {}", empty_line_count);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<Jakt::formatter::Formatter> Jakt::formatter::Formatter::for_tokens(JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens,bool const debug,size_t const max_allowed_line_length) {
{
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
return Jakt::formatter::Formatter(TRY((Jakt::formatter::Stage0::for_tokens(tokens,debug))),max_allowed_line_length,DynamicArray<Jakt::formatter::ReflowState>::create_with({}),static_cast<size_t>(0ULL),DynamicArray<Jakt::formatter::BreakablePoint>::create_with({}),DynamicArray<Jakt::formatter::ReflowState>::create_with({}),DynamicArray<JaktInternal::Optional<Jakt::lexer::Token>>::create_with({}),static_cast<size_t>(0ULL),false,false,JaktInternal::OptionalNone(),static_cast<size_t>(0ULL));
}
}

ErrorOr<size_t> Jakt::formatter::Formatter::token_length(Jakt::formatter::FormattedToken const token) const {
{
size_t length = ((((token).preceding_trivia)).size());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<size_t>>{
auto&& __jakt_match_variant = ((token).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
{
if (((comment).has_value())){
u8 next_char = static_cast<u8>(u8' ');
if ((((((comment.value())).length())) != (static_cast<size_t>(0ULL)))){
(next_char = (((comment.value())).byte_at(static_cast<size_t>(0ULL))));
}
size_t const space = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>> {
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

void Jakt::formatter::Formatter::fixup_tokens_to_reflow() {
{
if (((((*this).tokens_to_reflow)).is_empty())){
return;
}
size_t i = static_cast<size_t>(0ULL);
size_t j = JaktInternal::checked_sub(((((*this).tokens_to_reflow)).size()),static_cast<size_t>(1ULL));
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,j)){
Jakt::formatter::ReflowState const a = ((((*this).tokens_to_reflow))[i]);
(((((*this).tokens_to_reflow))[i]) = ((((*this).tokens_to_reflow))[j]));
(((((*this).tokens_to_reflow))[j]) = a);
((i) += (static_cast<size_t>(1ULL)));
((j) -= (static_cast<size_t>(1ULL)));
}
}
}

JaktInternal::DynamicArray<u8> Jakt::formatter::Formatter::to_array(ByteString const s) {
{
JaktInternal::DynamicArray<u8> result = DynamicArray<u8>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((s).length()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((result).push(((s).byte_at(i))));
}

}
}

return result;
}
}

void Jakt::formatter::Formatter::fixup_closing_enclosures(JaktInternal::DynamicArray<Jakt::formatter::ReflowState>& line) const {
{
if (((((line))).is_empty())){
return;
}
(((((((((line)))[static_cast<i64>(0LL)])).token)).preceding_trivia) = DynamicArray<u8>::create_with({}));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, void>{
auto&& __jakt_match_variant = ((((((((line)))[i])).token)).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
{
((enclosure_run_length) += (static_cast<size_t>(1ULL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
{
((enclosure_run_length) += (static_cast<size_t>(1ULL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* RSquare */: {
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
(((((((line)))[JaktInternal::checked_sub(i,j)])).token) = Jakt::formatter::FormattedToken(((((((((line)))[JaktInternal::checked_sub(i,j)])).token)).token),((((((((line)))[JaktInternal::checked_sub(i,enclosure_run_length)])).token)).indent),((((((((line)))[JaktInternal::checked_sub(i,j)])).token)).trailing_trivia),((((((((line)))[JaktInternal::checked_sub(i,j)])).token)).preceding_trivia)));
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
(((((((line)))[j])).token) = Jakt::formatter::FormattedToken(((((((((line)))[j])).token)).token),((((((((line)))[enclosure_run_length])).token)).indent),((((((((line)))[j])).token)).trailing_trivia),((((((((line)))[j])).token)).preceding_trivia)));
}

}
}

}
}

size_t Jakt::formatter::Formatter::pick_breaking_point_index() const {
{
return static_cast<size_t>(0ULL);
}
}

bool Jakt::formatter::Formatter::should_ignore_state(Jakt::formatter::State const state) {
{
return (((state).__jakt_init_index() == 14 /* TypeContext */) || ((state).__jakt_init_index() == 12 /* VariableDeclaration */));
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Formatter::peek() {
{
JaktInternal::Optional<Jakt::formatter::ReflowState> reflown_token = JaktInternal::OptionalNone();
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((*this).tokens_to_reflow)).size()),static_cast<size_t>(0ULL))){
(reflown_token = ((((*this).tokens_to_reflow))[JaktInternal::checked_sub(((((*this).tokens_to_reflow)).size()),static_cast<size_t>(1ULL))]));
}
return TRY((((reflown_token).map([](auto& _value) { return _value.token; })).try_value_or_lazy_evaluated_optional([&]() -> ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> { return TRY((((((*this).token_provider)).formatted_peek()))); })));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>> Jakt::formatter::Formatter::next() {
{
JaktInternal::Optional<Jakt::formatter::ReflowState> const reflown_token = ((((*this).tokens_to_reflow)).pop());
JaktInternal::Optional<Jakt::formatter::FormattedToken> maybe_next_underlying_token = TRY((((reflown_token).map([](auto& _value) { return _value.token; })).try_value_or_lazy_evaluated_optional([&]() -> ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> { return TRY((((((*this).token_provider)).next()))); })));
Jakt::formatter::State current_state = ((reflown_token).map([](auto& _value) { return _value.state; })).value_or_lazy_evaluated([&] { return ((((*this).token_provider)).state()); });
if (((maybe_next_underlying_token).has_value())){
Jakt::lexer::Token next_underlying_token = (((maybe_next_underlying_token.value())).token);
bool accepted_at_least_one_token = false;
while (((!(((next_underlying_token).__jakt_init_index() == 56 /* Eof */))) && (!(((next_underlying_token).__jakt_init_index() == 55 /* Eol */))))){
size_t const projected_added_length = TRY((((*this).token_length((maybe_next_underlying_token.value())))));
if (((((*this).logical_break_indent)).has_value())){
((((maybe_next_underlying_token.value())).indent) = (((*this).logical_break_indent).value()));
}
if (((((*this).in_condition_expr) && ((next_underlying_token).__jakt_init_index() == 9 /* LCurly */)) || ((next_underlying_token).__jakt_init_index() == 70 /* Else */))){
(((*this).in_condition_expr) = false);
(((*this).in_condition_expr_indented) = false);
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
{
(accepted_at_least_one_token = true);
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (projected_added_length));
if ((!(Jakt::formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<Jakt::formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)));
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
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)));
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
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)));
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
Jakt::abort();
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
default: {
{
Jakt::abort();
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
((((*this).breakable_points_in_current_line)).push((breakable_point.value())));
}
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
((((*this).replace_commas_in_enclosure)).push(none));
}
else {
((((*this).enclosures_to_ignore)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
{
(accepted_at_least_one_token = true);
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (projected_added_length));
if ((!(Jakt::formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<Jakt::formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)));
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
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)));
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
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)));
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
Jakt::abort();
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
default: {
{
Jakt::abort();
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
((((*this).breakable_points_in_current_line)).push((breakable_point.value())));
}
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
((((*this).replace_commas_in_enclosure)).push(none));
}
else {
((((*this).enclosures_to_ignore)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
{
(accepted_at_least_one_token = true);
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (projected_added_length));
if ((!(Jakt::formatter::Formatter::should_ignore_state(current_state)))){
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((((*this).peek())));
JaktInternal::Optional<Jakt::formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (((next_token).has_value())){
i64 const a = static_cast<i64>(1LL);
(breakable_point = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)));
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
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)));
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
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((next_token.value())).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)));
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
Jakt::abort();
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::formatter::BreakablePoint>, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Paren(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Curly(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(Jakt::formatter::BreakablePoint::Square(((((*this).current_line)).size()),((*this).current_line_length)));
};/*case end*/
default: {
{
Jakt::abort();
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
((((*this).breakable_points_in_current_line)).push((breakable_point.value())));
}
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
((((*this).replace_commas_in_enclosure)).push(none));
}
else {
((((*this).enclosures_to_ignore)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
{
bool ignore = false;
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((*this).enclosures_to_ignore),static_cast<size_t>(0ULL))){
((((*this).enclosures_to_ignore)) -= (static_cast<size_t>(1ULL)));
(ignore = true);
}
if (((!(ignore)) && (!(Jakt::formatter::Formatter::should_ignore_state(current_state))))){
Jakt::lexer::Token const replacement = Jakt::formatter::collapse<Jakt::lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
Jakt::formatter::FormattedToken const new_token = Jakt::formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
((((*this).current_line)).push(Jakt::formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
if (((replacement).__jakt_init_index() == 55 /* Eol */)){
((((*this).tokens_to_reflow)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
((((*this).replace_commas_in_enclosure)).push(none));
return JaktInternal::LoopBreak{};
}
}
else {
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
{
bool ignore = false;
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((*this).enclosures_to_ignore),static_cast<size_t>(0ULL))){
((((*this).enclosures_to_ignore)) -= (static_cast<size_t>(1ULL)));
(ignore = true);
}
if (((!(ignore)) && (!(Jakt::formatter::Formatter::should_ignore_state(current_state))))){
Jakt::lexer::Token const replacement = Jakt::formatter::collapse<Jakt::lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
Jakt::formatter::FormattedToken const new_token = Jakt::formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
((((*this).current_line)).push(Jakt::formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
if (((replacement).__jakt_init_index() == 55 /* Eol */)){
((((*this).tokens_to_reflow)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
((((*this).replace_commas_in_enclosure)).push(none));
return JaktInternal::LoopBreak{};
}
}
else {
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* RSquare */: {
{
bool ignore = false;
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((*this).enclosures_to_ignore),static_cast<size_t>(0ULL))){
((((*this).enclosures_to_ignore)) -= (static_cast<size_t>(1ULL)));
(ignore = true);
}
if (((!(ignore)) && (!(Jakt::formatter::Formatter::should_ignore_state(current_state))))){
Jakt::lexer::Token const replacement = Jakt::formatter::collapse<Jakt::lexer::Token>(((((*this).replace_commas_in_enclosure)).pop())).value_or_lazy_evaluated([&] { return next_underlying_token; });
Jakt::formatter::FormattedToken const new_token = Jakt::formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
((((*this).current_line)).push(Jakt::formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
if (((replacement).__jakt_init_index() == 55 /* Eol */)){
((((*this).tokens_to_reflow)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
((((*this).replace_commas_in_enclosure)).push(none));
return JaktInternal::LoopBreak{};
}
}
else {
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
}

(accepted_at_least_one_token = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
(accepted_at_least_one_token = true);
if ((!(Jakt::formatter::Formatter::should_ignore_state(current_state)))){
Jakt::lexer::Token const replacement = Jakt::formatter::collapse<Jakt::lexer::Token>(((((*this).replace_commas_in_enclosure)).last())).value_or_lazy_evaluated([&] { return next_underlying_token; });
Jakt::formatter::FormattedToken const new_token = Jakt::formatter::FormattedToken(replacement,(((maybe_next_underlying_token.value())).indent),(((maybe_next_underlying_token.value())).trailing_trivia),(((maybe_next_underlying_token.value())).preceding_trivia));
((((*this).current_line)).push(Jakt::formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
if (((replacement).__jakt_init_index() == 55 /* Eol */)){
return JaktInternal::LoopBreak{};
}
}
else {
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
Jakt::lexer::Token const newline = Jakt::lexer::Token::Eol(JaktInternal::OptionalNone(),((next_underlying_token).span()));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
case 75 /* For */: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
case 108 /* While */: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
case 78 /* If */: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
case 110 /* Guard */: {
{
(((*this).in_condition_expr) = true);
(((*this).in_condition_expr_indented) = false);
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((((*this).peek())));
if (((next_token).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
if ((((((*this).logical_break_indent)).has_value()) && (((next_underlying_token).__jakt_init_index() == 59 /* And */) || ((next_underlying_token).__jakt_init_index() == 90 /* Or */)))){
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length((maybe_next_underlying_token.value())))))));
Jakt::formatter::FormattedToken const new_token = Jakt::formatter::FormattedToken(newline,(((*this).logical_break_indent).value()),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
((((*this).current_line)).push(Jakt::formatter::ReflowState(new_token,current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (TRY((((*this).token_length(new_token))))));
return JaktInternal::LoopBreak{};
}
size_t const real_line_length = JaktInternal::checked_add(JaktInternal::checked_add(((*this).current_line_length),projected_added_length),(((maybe_next_underlying_token.value())).indent));
size_t const most_desirable_breaking_point_index = ((*this).pick_breaking_point_index());
if ((accepted_at_least_one_token && ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(real_line_length,((*this).max_allowed_line_length)) && ((!(((((*this).breakable_points_in_current_line)).is_empty()))) && ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((((((*this).breakable_points_in_current_line))[most_desirable_breaking_point_index])).point()),((((*this).current_line)).size())) && (!(Jakt::formatter::Formatter::should_ignore_state(current_state)))))))){
Jakt::formatter::BreakablePoint const breakable_point = ((((*this).breakable_points_in_current_line))[most_desirable_breaking_point_index]);
if ((!(((((*this).replace_commas_in_enclosure)).is_empty())))){
(((((*this).replace_commas_in_enclosure))[JaktInternal::checked_sub(((((*this).replace_commas_in_enclosure)).size()),static_cast<size_t>(1ULL))]) = newline);
}
size_t const point = ((breakable_point).point());
if (((breakable_point).__jakt_init_index() == 3 /* Logical */)){
if ((!(((((*this).logical_break_indent)).has_value())))){
(((*this).logical_break_indent) = ((((((((*this).current_line))[point])).token)).indent));
if ((!(((*this).in_condition_expr_indented)))){
(((((*this).logical_break_indent).value())) += (static_cast<size_t>(1ULL)));
}
}
}
(((*this).tokens_to_reflow) = ((((((*this).current_line))[(JaktInternal::Range<size_t>{static_cast<size_t>(point),static_cast<size_t>(9223372036854775807LL)})])).to_array()));
((((*this).tokens_to_reflow)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((*this).fixup_tokens_to_reflow());
Jakt::formatter::State const final_state = ((((((*this).current_line))[point])).state);
(((*this).enclosures_to_ignore) = ((((((*this).current_line))[point])).enclosures_to_ignore));
(((*this).current_line) = ((((((*this).current_line))[(JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(point)})])).to_array()));
((((*this).current_line)).push(Jakt::formatter::ReflowState(Jakt::formatter::FormattedToken(newline,(((maybe_next_underlying_token.value())).indent),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})),final_state,((*this).enclosures_to_ignore))));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
return JaktInternal::LoopBreak{};
}
(accepted_at_least_one_token = true);
((((*this).current_line)).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
((((*this).current_line_length)) += (projected_added_length));
if ((((*this).in_condition_expr) && (((next_underlying_token).__jakt_init_index() == 59 /* And */) || ((next_underlying_token).__jakt_init_index() == 90 /* Or */)))){
((((*this).breakable_points_in_current_line)).push(Jakt::formatter::BreakablePoint::Logical(((((*this).current_line)).size()),((*this).current_line_length))));
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
JaktInternal::Optional<Jakt::formatter::ReflowState> const reflown_token = ((((*this).tokens_to_reflow)).pop());
(maybe_next_underlying_token = ((reflown_token).map([](auto& _value) { return _value.token; })));
(current_state = ((reflown_token).map([](auto& _value) { return _value.state; })).value_or_lazy_evaluated([&] { return current_state; }));
}

if ((!(((maybe_next_underlying_token).has_value())))){
break;
}
(next_underlying_token = (((maybe_next_underlying_token.value())).token));
}
size_t const allowed_empty_lines_in_state = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = current_state;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* TypeContext */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* ImportList */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 7 /* ParameterList */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 0 /* Toplevel */: {
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
JaktInternal::DynamicArray<Jakt::formatter::ReflowState> line = ((*this).current_line);
(((*this).current_line) = DynamicArray<Jakt::formatter::ReflowState>::create_with({}));
(((*this).breakable_points_in_current_line) = DynamicArray<Jakt::formatter::BreakablePoint>::create_with({}));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
(((*this).enclosures_to_ignore) = static_cast<size_t>(0ULL));
if ((!(((*this).in_condition_expr)))){
(((*this).logical_break_indent) = JaktInternal::OptionalNone());
}
if ((((line).is_empty()) || (!((((((((((line).last()).value())).token)).token)).__jakt_init_index() == 55 /* Eol */))))){
((line).push(Jakt::formatter::ReflowState((maybe_next_underlying_token.value()),current_state,((*this).enclosures_to_ignore))));
}
if (((((line).size())) == (static_cast<size_t>(1ULL)))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>>>{
auto&& __jakt_match_variant = (((((((line).last()).value())).token)).token);
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
{
if (([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((*this).empty_line_count),allowed_empty_lines_in_state) && (!(((comment).has_value()))))){
return ((((*this).next())));
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

if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((line).size()),static_cast<size_t>(1ULL))){
(((((((line)[JaktInternal::checked_sub(((line).size()),static_cast<size_t>(2ULL))])).token)).trailing_trivia) = DynamicArray<u8>::create_with({}));
}
(((((((line)[JaktInternal::checked_sub(((line).size()),static_cast<size_t>(1ULL))])).token)).preceding_trivia) = DynamicArray<u8>::create_with({}));
(((((((line)[JaktInternal::checked_sub(((line).size()),static_cast<size_t>(1ULL))])).token)).trailing_trivia) = DynamicArray<u8>::create_with({}));
((*this).fixup_closing_enclosures(((line))));
JaktInternal::DynamicArray<Jakt::formatter::FormattedToken> result = DynamicArray<Jakt::formatter::FormattedToken>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::formatter::ReflowState> _magic = ((line).iterator());
for (;;){
JaktInternal::Optional<Jakt::formatter::ReflowState> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::formatter::ReflowState state = (_magic_value.value());
{
((result).push(((state).token)));
}

}
}

return result;
}
else {
if (((((*this).current_line)).is_empty())){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<Jakt::formatter::ReflowState> const line = ((*this).current_line);
(((*this).current_line) = DynamicArray<Jakt::formatter::ReflowState>::create_with({}));
(((*this).breakable_points_in_current_line) = DynamicArray<Jakt::formatter::BreakablePoint>::create_with({}));
(((*this).current_line_length) = static_cast<size_t>(0ULL));
(((*this).enclosures_to_ignore) = static_cast<size_t>(0ULL));
(((*this).in_condition_expr) = false);
(((*this).in_condition_expr_indented) = false);
(((*this).logical_break_indent) = JaktInternal::OptionalNone());
JaktInternal::DynamicArray<Jakt::formatter::FormattedToken> result = DynamicArray<Jakt::formatter::FormattedToken>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::formatter::ReflowState> _magic = ((line).iterator());
for (;;){
JaktInternal::Optional<Jakt::formatter::ReflowState> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::formatter::ReflowState state = (_magic_value.value());
{
((result).push(((state).token)));
}

}
}

return result;
}

}
}

Jakt::formatter::Formatter::Formatter(Jakt::formatter::Stage0 a_token_provider, size_t a_max_allowed_line_length, JaktInternal::DynamicArray<Jakt::formatter::ReflowState> a_current_line, size_t a_current_line_length, JaktInternal::DynamicArray<Jakt::formatter::BreakablePoint> a_breakable_points_in_current_line, JaktInternal::DynamicArray<Jakt::formatter::ReflowState> a_tokens_to_reflow, JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::lexer::Token>> a_replace_commas_in_enclosure, size_t a_enclosures_to_ignore, bool a_in_condition_expr, bool a_in_condition_expr_indented, JaktInternal::Optional<size_t> a_logical_break_indent, size_t a_empty_line_count): token_provider(move(a_token_provider)), max_allowed_line_length(move(a_max_allowed_line_length)), current_line(move(a_current_line)), current_line_length(move(a_current_line_length)), breakable_points_in_current_line(move(a_breakable_points_in_current_line)), tokens_to_reflow(move(a_tokens_to_reflow)), replace_commas_in_enclosure(move(a_replace_commas_in_enclosure)), enclosures_to_ignore(move(a_enclosures_to_ignore)), in_condition_expr(move(a_in_condition_expr)), in_condition_expr_indented(move(a_in_condition_expr_indented)), logical_break_indent(move(a_logical_break_indent)), empty_line_count(move(a_empty_line_count)){}

ByteString Jakt::formatter::Entity::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Struct */: {
return ByteString("Entity::Struct"sv);
break;}
case 1 /* Enum */: {
return ByteString("Entity::Enum"sv);
break;}
case 2 /* Namespace */: {
return ByteString("Entity::Namespace"sv);
break;}
case 3 /* Function */: {
builder.append("Entity::Function"sv);
[[maybe_unused]] auto const& that = this->as.Function;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arrow: {}, ", that.arrow);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("indented: {}", that.indented);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] Entity Entity::Struct(){
Entity __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] Entity Entity::Enum(){
Entity __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] Entity Entity::Namespace(){
Entity __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] Entity Entity::Function(bool arrow, bool indented){
Entity __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.Function.arrow) (decltype(arrow))(move(arrow));
new (&__jakt_uninit_enum.as.Function.indented) (decltype(indented))(move(indented));
return __jakt_uninit_enum;
}
Entity& Entity::operator=(Entity const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
break;
case 1 /* Enum */:
break;
case 2 /* Namespace */:
break;
case 3 /* Function */:
new (&this->as.Function.arrow) (decltype(this->as.Function.arrow))(rhs.as.Function.arrow);
new (&this->as.Function.indented) (decltype(this->as.Function.indented))(rhs.as.Function.indented);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
break;
case 1 /* Enum */:
break;
case 2 /* Namespace */:
break;
case 3 /* Function */:
this->as.Function.arrow = rhs.as.Function.arrow;
this->as.Function.indented = rhs.as.Function.indented;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Entity::Entity(Entity const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
break;
case 1 /* Enum */:
break;
case 2 /* Namespace */:
break;
case 3 /* Function */:
new (&this->as.Function.arrow) (decltype(this->as.Function.arrow))(rhs.as.Function.arrow);
new (&this->as.Function.indented) (decltype(this->as.Function.indented))(rhs.as.Function.indented);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Entity& Entity::operator=(Entity &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
break;
case 1 /* Enum */:
break;
case 2 /* Namespace */:
break;
case 3 /* Function */:
new (&this->as.Function.arrow) (decltype(this->as.Function.arrow))(move(rhs.as.Function.arrow));
new (&this->as.Function.indented) (decltype(this->as.Function.indented))(move(rhs.as.Function.indented));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
break;
case 1 /* Enum */:
break;
case 2 /* Namespace */:
break;
case 3 /* Function */:
this->as.Function.arrow = move(rhs.as.Function.arrow);
this->as.Function.indented = move(rhs.as.Function.indented);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Entity::Entity(Entity &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
break;
case 1 /* Enum */:
break;
case 2 /* Namespace */:
break;
case 3 /* Function */:
new (&this->as.Function.arrow) (decltype(this->as.Function.arrow))(move(rhs.as.Function.arrow));
new (&this->as.Function.indented) (decltype(this->as.Function.indented))(move(rhs.as.Function.indented));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Entity::~Entity(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void Entity::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Struct */:break;
case 1 /* Enum */:break;
case 2 /* Namespace */:break;
case 3 /* Function */:break;
}
}
Jakt::formatter::Entity Jakt::formatter::Entity::from_token(Jakt::lexer::Token const& token) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::formatter::Entity, Jakt::formatter::Entity>{
auto&& __jakt_match_variant = ((token));
switch(__jakt_match_variant.__jakt_init_index()) {
case 99 /* Struct */: {
return JaktInternal::ExplicitValue(Jakt::formatter::Entity::Struct());
};/*case end*/
case 65 /* Class */: {
return JaktInternal::ExplicitValue(Jakt::formatter::Entity::Struct());
};/*case end*/
case 113 /* Trait */: {
return JaktInternal::ExplicitValue(Jakt::formatter::Entity::Struct());
};/*case end*/
case 71 /* Enum */: {
return JaktInternal::ExplicitValue(Jakt::formatter::Entity::Enum());
};/*case end*/
case 88 /* Namespace */: {
return JaktInternal::ExplicitValue(Jakt::formatter::Entity::Namespace());
};/*case end*/
case 77 /* Comptime */: {
return JaktInternal::ExplicitValue(Jakt::formatter::Entity::Function(false,false));
};/*case end*/
case 76 /* Fn */: {
return JaktInternal::ExplicitValue(Jakt::formatter::Entity::Function(false,false));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::formatter::Entity::Struct());
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

ByteString Jakt::formatter::ExpressionMode::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* OutsideExpression */: {
return ByteString("ExpressionMode::OutsideExpression"sv);
break;}
case 1 /* BeforeExpressions */: {
return ByteString("ExpressionMode::BeforeExpressions"sv);
break;}
case 2 /* AtExpressionStart */: {
return ByteString("ExpressionMode::AtExpressionStart"sv);
break;}
case 3 /* InExpression */: {
return ByteString("ExpressionMode::InExpression"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] ExpressionMode ExpressionMode::OutsideExpression(){
ExpressionMode __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] ExpressionMode ExpressionMode::BeforeExpressions(){
ExpressionMode __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] ExpressionMode ExpressionMode::AtExpressionStart(){
ExpressionMode __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] ExpressionMode ExpressionMode::InExpression(){
ExpressionMode __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
ExpressionMode& ExpressionMode::operator=(ExpressionMode const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* OutsideExpression */:
break;
case 1 /* BeforeExpressions */:
break;
case 2 /* AtExpressionStart */:
break;
case 3 /* InExpression */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* OutsideExpression */:
break;
case 1 /* BeforeExpressions */:
break;
case 2 /* AtExpressionStart */:
break;
case 3 /* InExpression */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ExpressionMode::ExpressionMode(ExpressionMode const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* OutsideExpression */:
break;
case 1 /* BeforeExpressions */:
break;
case 2 /* AtExpressionStart */:
break;
case 3 /* InExpression */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ExpressionMode& ExpressionMode::operator=(ExpressionMode &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* OutsideExpression */:
break;
case 1 /* BeforeExpressions */:
break;
case 2 /* AtExpressionStart */:
break;
case 3 /* InExpression */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* OutsideExpression */:
break;
case 1 /* BeforeExpressions */:
break;
case 2 /* AtExpressionStart */:
break;
case 3 /* InExpression */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ExpressionMode::ExpressionMode(ExpressionMode &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* OutsideExpression */:
break;
case 1 /* BeforeExpressions */:
break;
case 2 /* AtExpressionStart */:
break;
case 3 /* InExpression */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ExpressionMode::~ExpressionMode(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ExpressionMode::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* OutsideExpression */:break;
case 1 /* BeforeExpressions */:break;
case 2 /* AtExpressionStart */:break;
case 3 /* InExpression */:break;
}
}
ByteString Jakt::formatter::State::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Toplevel */: {
builder.append("State::Toplevel"sv);
[[maybe_unused]] auto const& that = this->as.Toplevel;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_parens: {}, ", that.open_parens);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_curlies: {}, ", that.open_curlies);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_squares: {}, ", that.open_squares);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_extern: {}", that.is_extern);
}
builder.append(")"sv);
break;}
case 1 /* Extern */: {
return ByteString("State::Extern"sv);
break;}
case 2 /* Import */: {
builder.append("State::Import"sv);
[[maybe_unused]] auto const& that = this->as.Import;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_extern: {}", that.is_extern);
}
builder.append(")"sv);
break;}
case 3 /* ImportList */: {
builder.append("State::ImportList"sv);
[[maybe_unused]] auto const& that = this->as.ImportList;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("emitted_comma: {}", that.emitted_comma);
}
builder.append(")"sv);
break;}
case 4 /* EntityDeclaration */: {
builder.append("State::EntityDeclaration"sv);
[[maybe_unused]] auto const& that = this->as.EntityDeclaration;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("entity: {}, ", that.entity);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("accept_generics: {}, ", that.accept_generics);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("has_generics: {}, ", that.has_generics);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_nesting: {}, ", that.generic_nesting);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_extern: {}", that.is_extern);
}
builder.append(")"sv);
break;}
case 5 /* Implements */: {
return ByteString("State::Implements"sv);
break;}
case 6 /* CaptureList */: {
return ByteString("State::CaptureList"sv);
break;}
case 7 /* ParameterList */: {
builder.append("State::ParameterList"sv);
[[maybe_unused]] auto const& that = this->as.ParameterList;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_parens: {}", that.open_parens);
}
builder.append(")"sv);
break;}
case 8 /* RestrictionList */: {
return ByteString("State::RestrictionList"sv);
break;}
case 9 /* EntityDefinition */: {
builder.append("State::EntityDefinition"sv);
[[maybe_unused]] auto const& that = this->as.EntityDefinition;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("entity: {}, ", that.entity);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_extern: {}", that.is_extern);
}
builder.append(")"sv);
break;}
case 10 /* StatementContext */: {
builder.append("State::StatementContext"sv);
[[maybe_unused]] auto const& that = this->as.StatementContext;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_parens: {}, ", that.open_parens);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_curlies: {}, ", that.open_curlies);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_squares: {}, ", that.open_squares);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arrow_indents: {}, ", that.arrow_indents);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("allow_eol: {}, ", that.allow_eol);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inserted_comma: {}, ", that.inserted_comma);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expression_mode: {}, ", that.expression_mode);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dedents_on_open_curly: {}", that.dedents_on_open_curly);
}
builder.append(")"sv);
break;}
case 11 /* MatchPattern */: {
builder.append("State::MatchPattern"sv);
[[maybe_unused]] auto const& that = this->as.MatchPattern;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_parens: {}, ", that.open_parens);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("allow_multiple: {}", that.allow_multiple);
}
builder.append(")"sv);
break;}
case 12 /* VariableDeclaration */: {
builder.append("State::VariableDeclaration"sv);
[[maybe_unused]] auto const& that = this->as.VariableDeclaration;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_parens: {}", that.open_parens);
}
builder.append(")"sv);
break;}
case 13 /* GenericCallTypeParams */: {
builder.append("State::GenericCallTypeParams"sv);
[[maybe_unused]] auto const& that = this->as.GenericCallTypeParams;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_angles: {}", that.open_angles);
}
builder.append(")"sv);
break;}
case 14 /* TypeContext */: {
builder.append("State::TypeContext"sv);
[[maybe_unused]] auto const& that = this->as.TypeContext;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_parens: {}, ", that.open_parens);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_curlies: {}, ", that.open_curlies);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_squares: {}, ", that.open_squares);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("open_angles: {}, ", that.open_angles);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("seen_start: {}", that.seen_start);
}
builder.append(")"sv);
break;}
case 15 /* FunctionTypeContext */: {
builder.append("State::FunctionTypeContext"sv);
[[maybe_unused]] auto const& that = this->as.FunctionTypeContext;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("seen_final_type: {}", that.seen_final_type);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] State State::Toplevel(size_t open_parens, size_t open_curlies, size_t open_squares, bool is_extern){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Toplevel.open_parens) (decltype(open_parens))(move(open_parens));
new (&__jakt_uninit_enum.as.Toplevel.open_curlies) (decltype(open_curlies))(move(open_curlies));
new (&__jakt_uninit_enum.as.Toplevel.open_squares) (decltype(open_squares))(move(open_squares));
new (&__jakt_uninit_enum.as.Toplevel.is_extern) (decltype(is_extern))(move(is_extern));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::Extern(){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] State State::Import(bool is_extern){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Import.is_extern) (decltype(is_extern))(move(is_extern));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::ImportList(bool emitted_comma){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.ImportList.emitted_comma) (decltype(emitted_comma))(move(emitted_comma));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::EntityDeclaration(Jakt::formatter::Entity entity, bool accept_generics, bool has_generics, size_t generic_nesting, bool is_extern){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.as.EntityDeclaration.entity) (decltype(entity))(move(entity));
new (&__jakt_uninit_enum.as.EntityDeclaration.accept_generics) (decltype(accept_generics))(move(accept_generics));
new (&__jakt_uninit_enum.as.EntityDeclaration.has_generics) (decltype(has_generics))(move(has_generics));
new (&__jakt_uninit_enum.as.EntityDeclaration.generic_nesting) (decltype(generic_nesting))(move(generic_nesting));
new (&__jakt_uninit_enum.as.EntityDeclaration.is_extern) (decltype(is_extern))(move(is_extern));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::Implements(){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] State State::CaptureList(){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
[[nodiscard]] State State::ParameterList(size_t open_parens){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
new (&__jakt_uninit_enum.as.ParameterList.open_parens) (decltype(open_parens))(move(open_parens));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::RestrictionList(){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
return __jakt_uninit_enum;
}
[[nodiscard]] State State::EntityDefinition(Jakt::formatter::Entity entity, bool is_extern){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
new (&__jakt_uninit_enum.as.EntityDefinition.entity) (decltype(entity))(move(entity));
new (&__jakt_uninit_enum.as.EntityDefinition.is_extern) (decltype(is_extern))(move(is_extern));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::StatementContext(size_t open_parens, size_t open_curlies, size_t open_squares, size_t arrow_indents, JaktInternal::Optional<size_t> allow_eol, bool inserted_comma, Jakt::formatter::ExpressionMode expression_mode, size_t dedents_on_open_curly){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
new (&__jakt_uninit_enum.as.StatementContext.open_parens) (decltype(open_parens))(move(open_parens));
new (&__jakt_uninit_enum.as.StatementContext.open_curlies) (decltype(open_curlies))(move(open_curlies));
new (&__jakt_uninit_enum.as.StatementContext.open_squares) (decltype(open_squares))(move(open_squares));
new (&__jakt_uninit_enum.as.StatementContext.arrow_indents) (decltype(arrow_indents))(move(arrow_indents));
new (&__jakt_uninit_enum.as.StatementContext.allow_eol) (decltype(allow_eol))(move(allow_eol));
new (&__jakt_uninit_enum.as.StatementContext.inserted_comma) (decltype(inserted_comma))(move(inserted_comma));
new (&__jakt_uninit_enum.as.StatementContext.expression_mode) (decltype(expression_mode))(move(expression_mode));
new (&__jakt_uninit_enum.as.StatementContext.dedents_on_open_curly) (decltype(dedents_on_open_curly))(move(dedents_on_open_curly));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::MatchPattern(size_t open_parens, bool allow_multiple){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
new (&__jakt_uninit_enum.as.MatchPattern.open_parens) (decltype(open_parens))(move(open_parens));
new (&__jakt_uninit_enum.as.MatchPattern.allow_multiple) (decltype(allow_multiple))(move(allow_multiple));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::VariableDeclaration(size_t open_parens){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
new (&__jakt_uninit_enum.as.VariableDeclaration.open_parens) (decltype(open_parens))(move(open_parens));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::GenericCallTypeParams(size_t open_angles){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 14;
new (&__jakt_uninit_enum.as.GenericCallTypeParams.open_angles) (decltype(open_angles))(move(open_angles));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::TypeContext(size_t open_parens, size_t open_curlies, size_t open_squares, size_t open_angles, bool seen_start){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 15;
new (&__jakt_uninit_enum.as.TypeContext.open_parens) (decltype(open_parens))(move(open_parens));
new (&__jakt_uninit_enum.as.TypeContext.open_curlies) (decltype(open_curlies))(move(open_curlies));
new (&__jakt_uninit_enum.as.TypeContext.open_squares) (decltype(open_squares))(move(open_squares));
new (&__jakt_uninit_enum.as.TypeContext.open_angles) (decltype(open_angles))(move(open_angles));
new (&__jakt_uninit_enum.as.TypeContext.seen_start) (decltype(seen_start))(move(seen_start));
return __jakt_uninit_enum;
}
[[nodiscard]] State State::FunctionTypeContext(bool seen_final_type){
State __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 16;
new (&__jakt_uninit_enum.as.FunctionTypeContext.seen_final_type) (decltype(seen_final_type))(move(seen_final_type));
return __jakt_uninit_enum;
}
State& State::operator=(State const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Toplevel */:
new (&this->as.Toplevel.open_parens) (decltype(this->as.Toplevel.open_parens))(rhs.as.Toplevel.open_parens);
new (&this->as.Toplevel.open_curlies) (decltype(this->as.Toplevel.open_curlies))(rhs.as.Toplevel.open_curlies);
new (&this->as.Toplevel.open_squares) (decltype(this->as.Toplevel.open_squares))(rhs.as.Toplevel.open_squares);
new (&this->as.Toplevel.is_extern) (decltype(this->as.Toplevel.is_extern))(rhs.as.Toplevel.is_extern);
break;
case 1 /* Extern */:
break;
case 2 /* Import */:
new (&this->as.Import.is_extern) (decltype(this->as.Import.is_extern))(rhs.as.Import.is_extern);
break;
case 3 /* ImportList */:
new (&this->as.ImportList.emitted_comma) (decltype(this->as.ImportList.emitted_comma))(rhs.as.ImportList.emitted_comma);
break;
case 4 /* EntityDeclaration */:
new (&this->as.EntityDeclaration.entity) (decltype(this->as.EntityDeclaration.entity))(rhs.as.EntityDeclaration.entity);
new (&this->as.EntityDeclaration.accept_generics) (decltype(this->as.EntityDeclaration.accept_generics))(rhs.as.EntityDeclaration.accept_generics);
new (&this->as.EntityDeclaration.has_generics) (decltype(this->as.EntityDeclaration.has_generics))(rhs.as.EntityDeclaration.has_generics);
new (&this->as.EntityDeclaration.generic_nesting) (decltype(this->as.EntityDeclaration.generic_nesting))(rhs.as.EntityDeclaration.generic_nesting);
new (&this->as.EntityDeclaration.is_extern) (decltype(this->as.EntityDeclaration.is_extern))(rhs.as.EntityDeclaration.is_extern);
break;
case 5 /* Implements */:
break;
case 6 /* CaptureList */:
break;
case 7 /* ParameterList */:
new (&this->as.ParameterList.open_parens) (decltype(this->as.ParameterList.open_parens))(rhs.as.ParameterList.open_parens);
break;
case 8 /* RestrictionList */:
break;
case 9 /* EntityDefinition */:
new (&this->as.EntityDefinition.entity) (decltype(this->as.EntityDefinition.entity))(rhs.as.EntityDefinition.entity);
new (&this->as.EntityDefinition.is_extern) (decltype(this->as.EntityDefinition.is_extern))(rhs.as.EntityDefinition.is_extern);
break;
case 10 /* StatementContext */:
new (&this->as.StatementContext.open_parens) (decltype(this->as.StatementContext.open_parens))(rhs.as.StatementContext.open_parens);
new (&this->as.StatementContext.open_curlies) (decltype(this->as.StatementContext.open_curlies))(rhs.as.StatementContext.open_curlies);
new (&this->as.StatementContext.open_squares) (decltype(this->as.StatementContext.open_squares))(rhs.as.StatementContext.open_squares);
new (&this->as.StatementContext.arrow_indents) (decltype(this->as.StatementContext.arrow_indents))(rhs.as.StatementContext.arrow_indents);
new (&this->as.StatementContext.allow_eol) (decltype(this->as.StatementContext.allow_eol))(rhs.as.StatementContext.allow_eol);
new (&this->as.StatementContext.inserted_comma) (decltype(this->as.StatementContext.inserted_comma))(rhs.as.StatementContext.inserted_comma);
new (&this->as.StatementContext.expression_mode) (decltype(this->as.StatementContext.expression_mode))(rhs.as.StatementContext.expression_mode);
new (&this->as.StatementContext.dedents_on_open_curly) (decltype(this->as.StatementContext.dedents_on_open_curly))(rhs.as.StatementContext.dedents_on_open_curly);
break;
case 11 /* MatchPattern */:
new (&this->as.MatchPattern.open_parens) (decltype(this->as.MatchPattern.open_parens))(rhs.as.MatchPattern.open_parens);
new (&this->as.MatchPattern.allow_multiple) (decltype(this->as.MatchPattern.allow_multiple))(rhs.as.MatchPattern.allow_multiple);
break;
case 12 /* VariableDeclaration */:
new (&this->as.VariableDeclaration.open_parens) (decltype(this->as.VariableDeclaration.open_parens))(rhs.as.VariableDeclaration.open_parens);
break;
case 13 /* GenericCallTypeParams */:
new (&this->as.GenericCallTypeParams.open_angles) (decltype(this->as.GenericCallTypeParams.open_angles))(rhs.as.GenericCallTypeParams.open_angles);
break;
case 14 /* TypeContext */:
new (&this->as.TypeContext.open_parens) (decltype(this->as.TypeContext.open_parens))(rhs.as.TypeContext.open_parens);
new (&this->as.TypeContext.open_curlies) (decltype(this->as.TypeContext.open_curlies))(rhs.as.TypeContext.open_curlies);
new (&this->as.TypeContext.open_squares) (decltype(this->as.TypeContext.open_squares))(rhs.as.TypeContext.open_squares);
new (&this->as.TypeContext.open_angles) (decltype(this->as.TypeContext.open_angles))(rhs.as.TypeContext.open_angles);
new (&this->as.TypeContext.seen_start) (decltype(this->as.TypeContext.seen_start))(rhs.as.TypeContext.seen_start);
break;
case 15 /* FunctionTypeContext */:
new (&this->as.FunctionTypeContext.seen_final_type) (decltype(this->as.FunctionTypeContext.seen_final_type))(rhs.as.FunctionTypeContext.seen_final_type);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Toplevel */:
this->as.Toplevel.open_parens = rhs.as.Toplevel.open_parens;
this->as.Toplevel.open_curlies = rhs.as.Toplevel.open_curlies;
this->as.Toplevel.open_squares = rhs.as.Toplevel.open_squares;
this->as.Toplevel.is_extern = rhs.as.Toplevel.is_extern;
break;
case 1 /* Extern */:
break;
case 2 /* Import */:
this->as.Import.is_extern = rhs.as.Import.is_extern;
break;
case 3 /* ImportList */:
this->as.ImportList.emitted_comma = rhs.as.ImportList.emitted_comma;
break;
case 4 /* EntityDeclaration */:
this->as.EntityDeclaration.entity = rhs.as.EntityDeclaration.entity;
this->as.EntityDeclaration.accept_generics = rhs.as.EntityDeclaration.accept_generics;
this->as.EntityDeclaration.has_generics = rhs.as.EntityDeclaration.has_generics;
this->as.EntityDeclaration.generic_nesting = rhs.as.EntityDeclaration.generic_nesting;
this->as.EntityDeclaration.is_extern = rhs.as.EntityDeclaration.is_extern;
break;
case 5 /* Implements */:
break;
case 6 /* CaptureList */:
break;
case 7 /* ParameterList */:
this->as.ParameterList.open_parens = rhs.as.ParameterList.open_parens;
break;
case 8 /* RestrictionList */:
break;
case 9 /* EntityDefinition */:
this->as.EntityDefinition.entity = rhs.as.EntityDefinition.entity;
this->as.EntityDefinition.is_extern = rhs.as.EntityDefinition.is_extern;
break;
case 10 /* StatementContext */:
this->as.StatementContext.open_parens = rhs.as.StatementContext.open_parens;
this->as.StatementContext.open_curlies = rhs.as.StatementContext.open_curlies;
this->as.StatementContext.open_squares = rhs.as.StatementContext.open_squares;
this->as.StatementContext.arrow_indents = rhs.as.StatementContext.arrow_indents;
this->as.StatementContext.allow_eol = rhs.as.StatementContext.allow_eol;
this->as.StatementContext.inserted_comma = rhs.as.StatementContext.inserted_comma;
this->as.StatementContext.expression_mode = rhs.as.StatementContext.expression_mode;
this->as.StatementContext.dedents_on_open_curly = rhs.as.StatementContext.dedents_on_open_curly;
break;
case 11 /* MatchPattern */:
this->as.MatchPattern.open_parens = rhs.as.MatchPattern.open_parens;
this->as.MatchPattern.allow_multiple = rhs.as.MatchPattern.allow_multiple;
break;
case 12 /* VariableDeclaration */:
this->as.VariableDeclaration.open_parens = rhs.as.VariableDeclaration.open_parens;
break;
case 13 /* GenericCallTypeParams */:
this->as.GenericCallTypeParams.open_angles = rhs.as.GenericCallTypeParams.open_angles;
break;
case 14 /* TypeContext */:
this->as.TypeContext.open_parens = rhs.as.TypeContext.open_parens;
this->as.TypeContext.open_curlies = rhs.as.TypeContext.open_curlies;
this->as.TypeContext.open_squares = rhs.as.TypeContext.open_squares;
this->as.TypeContext.open_angles = rhs.as.TypeContext.open_angles;
this->as.TypeContext.seen_start = rhs.as.TypeContext.seen_start;
break;
case 15 /* FunctionTypeContext */:
this->as.FunctionTypeContext.seen_final_type = rhs.as.FunctionTypeContext.seen_final_type;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
State::State(State const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Toplevel */:
new (&this->as.Toplevel.open_parens) (decltype(this->as.Toplevel.open_parens))(rhs.as.Toplevel.open_parens);
new (&this->as.Toplevel.open_curlies) (decltype(this->as.Toplevel.open_curlies))(rhs.as.Toplevel.open_curlies);
new (&this->as.Toplevel.open_squares) (decltype(this->as.Toplevel.open_squares))(rhs.as.Toplevel.open_squares);
new (&this->as.Toplevel.is_extern) (decltype(this->as.Toplevel.is_extern))(rhs.as.Toplevel.is_extern);
break;
case 1 /* Extern */:
break;
case 2 /* Import */:
new (&this->as.Import.is_extern) (decltype(this->as.Import.is_extern))(rhs.as.Import.is_extern);
break;
case 3 /* ImportList */:
new (&this->as.ImportList.emitted_comma) (decltype(this->as.ImportList.emitted_comma))(rhs.as.ImportList.emitted_comma);
break;
case 4 /* EntityDeclaration */:
new (&this->as.EntityDeclaration.entity) (decltype(this->as.EntityDeclaration.entity))(rhs.as.EntityDeclaration.entity);
new (&this->as.EntityDeclaration.accept_generics) (decltype(this->as.EntityDeclaration.accept_generics))(rhs.as.EntityDeclaration.accept_generics);
new (&this->as.EntityDeclaration.has_generics) (decltype(this->as.EntityDeclaration.has_generics))(rhs.as.EntityDeclaration.has_generics);
new (&this->as.EntityDeclaration.generic_nesting) (decltype(this->as.EntityDeclaration.generic_nesting))(rhs.as.EntityDeclaration.generic_nesting);
new (&this->as.EntityDeclaration.is_extern) (decltype(this->as.EntityDeclaration.is_extern))(rhs.as.EntityDeclaration.is_extern);
break;
case 5 /* Implements */:
break;
case 6 /* CaptureList */:
break;
case 7 /* ParameterList */:
new (&this->as.ParameterList.open_parens) (decltype(this->as.ParameterList.open_parens))(rhs.as.ParameterList.open_parens);
break;
case 8 /* RestrictionList */:
break;
case 9 /* EntityDefinition */:
new (&this->as.EntityDefinition.entity) (decltype(this->as.EntityDefinition.entity))(rhs.as.EntityDefinition.entity);
new (&this->as.EntityDefinition.is_extern) (decltype(this->as.EntityDefinition.is_extern))(rhs.as.EntityDefinition.is_extern);
break;
case 10 /* StatementContext */:
new (&this->as.StatementContext.open_parens) (decltype(this->as.StatementContext.open_parens))(rhs.as.StatementContext.open_parens);
new (&this->as.StatementContext.open_curlies) (decltype(this->as.StatementContext.open_curlies))(rhs.as.StatementContext.open_curlies);
new (&this->as.StatementContext.open_squares) (decltype(this->as.StatementContext.open_squares))(rhs.as.StatementContext.open_squares);
new (&this->as.StatementContext.arrow_indents) (decltype(this->as.StatementContext.arrow_indents))(rhs.as.StatementContext.arrow_indents);
new (&this->as.StatementContext.allow_eol) (decltype(this->as.StatementContext.allow_eol))(rhs.as.StatementContext.allow_eol);
new (&this->as.StatementContext.inserted_comma) (decltype(this->as.StatementContext.inserted_comma))(rhs.as.StatementContext.inserted_comma);
new (&this->as.StatementContext.expression_mode) (decltype(this->as.StatementContext.expression_mode))(rhs.as.StatementContext.expression_mode);
new (&this->as.StatementContext.dedents_on_open_curly) (decltype(this->as.StatementContext.dedents_on_open_curly))(rhs.as.StatementContext.dedents_on_open_curly);
break;
case 11 /* MatchPattern */:
new (&this->as.MatchPattern.open_parens) (decltype(this->as.MatchPattern.open_parens))(rhs.as.MatchPattern.open_parens);
new (&this->as.MatchPattern.allow_multiple) (decltype(this->as.MatchPattern.allow_multiple))(rhs.as.MatchPattern.allow_multiple);
break;
case 12 /* VariableDeclaration */:
new (&this->as.VariableDeclaration.open_parens) (decltype(this->as.VariableDeclaration.open_parens))(rhs.as.VariableDeclaration.open_parens);
break;
case 13 /* GenericCallTypeParams */:
new (&this->as.GenericCallTypeParams.open_angles) (decltype(this->as.GenericCallTypeParams.open_angles))(rhs.as.GenericCallTypeParams.open_angles);
break;
case 14 /* TypeContext */:
new (&this->as.TypeContext.open_parens) (decltype(this->as.TypeContext.open_parens))(rhs.as.TypeContext.open_parens);
new (&this->as.TypeContext.open_curlies) (decltype(this->as.TypeContext.open_curlies))(rhs.as.TypeContext.open_curlies);
new (&this->as.TypeContext.open_squares) (decltype(this->as.TypeContext.open_squares))(rhs.as.TypeContext.open_squares);
new (&this->as.TypeContext.open_angles) (decltype(this->as.TypeContext.open_angles))(rhs.as.TypeContext.open_angles);
new (&this->as.TypeContext.seen_start) (decltype(this->as.TypeContext.seen_start))(rhs.as.TypeContext.seen_start);
break;
case 15 /* FunctionTypeContext */:
new (&this->as.FunctionTypeContext.seen_final_type) (decltype(this->as.FunctionTypeContext.seen_final_type))(rhs.as.FunctionTypeContext.seen_final_type);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
State& State::operator=(State &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Toplevel */:
new (&this->as.Toplevel.open_parens) (decltype(this->as.Toplevel.open_parens))(move(rhs.as.Toplevel.open_parens));
new (&this->as.Toplevel.open_curlies) (decltype(this->as.Toplevel.open_curlies))(move(rhs.as.Toplevel.open_curlies));
new (&this->as.Toplevel.open_squares) (decltype(this->as.Toplevel.open_squares))(move(rhs.as.Toplevel.open_squares));
new (&this->as.Toplevel.is_extern) (decltype(this->as.Toplevel.is_extern))(move(rhs.as.Toplevel.is_extern));
break;
case 1 /* Extern */:
break;
case 2 /* Import */:
new (&this->as.Import.is_extern) (decltype(this->as.Import.is_extern))(move(rhs.as.Import.is_extern));
break;
case 3 /* ImportList */:
new (&this->as.ImportList.emitted_comma) (decltype(this->as.ImportList.emitted_comma))(move(rhs.as.ImportList.emitted_comma));
break;
case 4 /* EntityDeclaration */:
new (&this->as.EntityDeclaration.entity) (decltype(this->as.EntityDeclaration.entity))(move(rhs.as.EntityDeclaration.entity));
new (&this->as.EntityDeclaration.accept_generics) (decltype(this->as.EntityDeclaration.accept_generics))(move(rhs.as.EntityDeclaration.accept_generics));
new (&this->as.EntityDeclaration.has_generics) (decltype(this->as.EntityDeclaration.has_generics))(move(rhs.as.EntityDeclaration.has_generics));
new (&this->as.EntityDeclaration.generic_nesting) (decltype(this->as.EntityDeclaration.generic_nesting))(move(rhs.as.EntityDeclaration.generic_nesting));
new (&this->as.EntityDeclaration.is_extern) (decltype(this->as.EntityDeclaration.is_extern))(move(rhs.as.EntityDeclaration.is_extern));
break;
case 5 /* Implements */:
break;
case 6 /* CaptureList */:
break;
case 7 /* ParameterList */:
new (&this->as.ParameterList.open_parens) (decltype(this->as.ParameterList.open_parens))(move(rhs.as.ParameterList.open_parens));
break;
case 8 /* RestrictionList */:
break;
case 9 /* EntityDefinition */:
new (&this->as.EntityDefinition.entity) (decltype(this->as.EntityDefinition.entity))(move(rhs.as.EntityDefinition.entity));
new (&this->as.EntityDefinition.is_extern) (decltype(this->as.EntityDefinition.is_extern))(move(rhs.as.EntityDefinition.is_extern));
break;
case 10 /* StatementContext */:
new (&this->as.StatementContext.open_parens) (decltype(this->as.StatementContext.open_parens))(move(rhs.as.StatementContext.open_parens));
new (&this->as.StatementContext.open_curlies) (decltype(this->as.StatementContext.open_curlies))(move(rhs.as.StatementContext.open_curlies));
new (&this->as.StatementContext.open_squares) (decltype(this->as.StatementContext.open_squares))(move(rhs.as.StatementContext.open_squares));
new (&this->as.StatementContext.arrow_indents) (decltype(this->as.StatementContext.arrow_indents))(move(rhs.as.StatementContext.arrow_indents));
new (&this->as.StatementContext.allow_eol) (decltype(this->as.StatementContext.allow_eol))(move(rhs.as.StatementContext.allow_eol));
new (&this->as.StatementContext.inserted_comma) (decltype(this->as.StatementContext.inserted_comma))(move(rhs.as.StatementContext.inserted_comma));
new (&this->as.StatementContext.expression_mode) (decltype(this->as.StatementContext.expression_mode))(move(rhs.as.StatementContext.expression_mode));
new (&this->as.StatementContext.dedents_on_open_curly) (decltype(this->as.StatementContext.dedents_on_open_curly))(move(rhs.as.StatementContext.dedents_on_open_curly));
break;
case 11 /* MatchPattern */:
new (&this->as.MatchPattern.open_parens) (decltype(this->as.MatchPattern.open_parens))(move(rhs.as.MatchPattern.open_parens));
new (&this->as.MatchPattern.allow_multiple) (decltype(this->as.MatchPattern.allow_multiple))(move(rhs.as.MatchPattern.allow_multiple));
break;
case 12 /* VariableDeclaration */:
new (&this->as.VariableDeclaration.open_parens) (decltype(this->as.VariableDeclaration.open_parens))(move(rhs.as.VariableDeclaration.open_parens));
break;
case 13 /* GenericCallTypeParams */:
new (&this->as.GenericCallTypeParams.open_angles) (decltype(this->as.GenericCallTypeParams.open_angles))(move(rhs.as.GenericCallTypeParams.open_angles));
break;
case 14 /* TypeContext */:
new (&this->as.TypeContext.open_parens) (decltype(this->as.TypeContext.open_parens))(move(rhs.as.TypeContext.open_parens));
new (&this->as.TypeContext.open_curlies) (decltype(this->as.TypeContext.open_curlies))(move(rhs.as.TypeContext.open_curlies));
new (&this->as.TypeContext.open_squares) (decltype(this->as.TypeContext.open_squares))(move(rhs.as.TypeContext.open_squares));
new (&this->as.TypeContext.open_angles) (decltype(this->as.TypeContext.open_angles))(move(rhs.as.TypeContext.open_angles));
new (&this->as.TypeContext.seen_start) (decltype(this->as.TypeContext.seen_start))(move(rhs.as.TypeContext.seen_start));
break;
case 15 /* FunctionTypeContext */:
new (&this->as.FunctionTypeContext.seen_final_type) (decltype(this->as.FunctionTypeContext.seen_final_type))(move(rhs.as.FunctionTypeContext.seen_final_type));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Toplevel */:
this->as.Toplevel.open_parens = move(rhs.as.Toplevel.open_parens);
this->as.Toplevel.open_curlies = move(rhs.as.Toplevel.open_curlies);
this->as.Toplevel.open_squares = move(rhs.as.Toplevel.open_squares);
this->as.Toplevel.is_extern = move(rhs.as.Toplevel.is_extern);
break;
case 1 /* Extern */:
break;
case 2 /* Import */:
this->as.Import.is_extern = move(rhs.as.Import.is_extern);
break;
case 3 /* ImportList */:
this->as.ImportList.emitted_comma = move(rhs.as.ImportList.emitted_comma);
break;
case 4 /* EntityDeclaration */:
this->as.EntityDeclaration.entity = move(rhs.as.EntityDeclaration.entity);
this->as.EntityDeclaration.accept_generics = move(rhs.as.EntityDeclaration.accept_generics);
this->as.EntityDeclaration.has_generics = move(rhs.as.EntityDeclaration.has_generics);
this->as.EntityDeclaration.generic_nesting = move(rhs.as.EntityDeclaration.generic_nesting);
this->as.EntityDeclaration.is_extern = move(rhs.as.EntityDeclaration.is_extern);
break;
case 5 /* Implements */:
break;
case 6 /* CaptureList */:
break;
case 7 /* ParameterList */:
this->as.ParameterList.open_parens = move(rhs.as.ParameterList.open_parens);
break;
case 8 /* RestrictionList */:
break;
case 9 /* EntityDefinition */:
this->as.EntityDefinition.entity = move(rhs.as.EntityDefinition.entity);
this->as.EntityDefinition.is_extern = move(rhs.as.EntityDefinition.is_extern);
break;
case 10 /* StatementContext */:
this->as.StatementContext.open_parens = move(rhs.as.StatementContext.open_parens);
this->as.StatementContext.open_curlies = move(rhs.as.StatementContext.open_curlies);
this->as.StatementContext.open_squares = move(rhs.as.StatementContext.open_squares);
this->as.StatementContext.arrow_indents = move(rhs.as.StatementContext.arrow_indents);
this->as.StatementContext.allow_eol = move(rhs.as.StatementContext.allow_eol);
this->as.StatementContext.inserted_comma = move(rhs.as.StatementContext.inserted_comma);
this->as.StatementContext.expression_mode = move(rhs.as.StatementContext.expression_mode);
this->as.StatementContext.dedents_on_open_curly = move(rhs.as.StatementContext.dedents_on_open_curly);
break;
case 11 /* MatchPattern */:
this->as.MatchPattern.open_parens = move(rhs.as.MatchPattern.open_parens);
this->as.MatchPattern.allow_multiple = move(rhs.as.MatchPattern.allow_multiple);
break;
case 12 /* VariableDeclaration */:
this->as.VariableDeclaration.open_parens = move(rhs.as.VariableDeclaration.open_parens);
break;
case 13 /* GenericCallTypeParams */:
this->as.GenericCallTypeParams.open_angles = move(rhs.as.GenericCallTypeParams.open_angles);
break;
case 14 /* TypeContext */:
this->as.TypeContext.open_parens = move(rhs.as.TypeContext.open_parens);
this->as.TypeContext.open_curlies = move(rhs.as.TypeContext.open_curlies);
this->as.TypeContext.open_squares = move(rhs.as.TypeContext.open_squares);
this->as.TypeContext.open_angles = move(rhs.as.TypeContext.open_angles);
this->as.TypeContext.seen_start = move(rhs.as.TypeContext.seen_start);
break;
case 15 /* FunctionTypeContext */:
this->as.FunctionTypeContext.seen_final_type = move(rhs.as.FunctionTypeContext.seen_final_type);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
State::State(State &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Toplevel */:
new (&this->as.Toplevel.open_parens) (decltype(this->as.Toplevel.open_parens))(move(rhs.as.Toplevel.open_parens));
new (&this->as.Toplevel.open_curlies) (decltype(this->as.Toplevel.open_curlies))(move(rhs.as.Toplevel.open_curlies));
new (&this->as.Toplevel.open_squares) (decltype(this->as.Toplevel.open_squares))(move(rhs.as.Toplevel.open_squares));
new (&this->as.Toplevel.is_extern) (decltype(this->as.Toplevel.is_extern))(move(rhs.as.Toplevel.is_extern));
break;
case 1 /* Extern */:
break;
case 2 /* Import */:
new (&this->as.Import.is_extern) (decltype(this->as.Import.is_extern))(move(rhs.as.Import.is_extern));
break;
case 3 /* ImportList */:
new (&this->as.ImportList.emitted_comma) (decltype(this->as.ImportList.emitted_comma))(move(rhs.as.ImportList.emitted_comma));
break;
case 4 /* EntityDeclaration */:
new (&this->as.EntityDeclaration.entity) (decltype(this->as.EntityDeclaration.entity))(move(rhs.as.EntityDeclaration.entity));
new (&this->as.EntityDeclaration.accept_generics) (decltype(this->as.EntityDeclaration.accept_generics))(move(rhs.as.EntityDeclaration.accept_generics));
new (&this->as.EntityDeclaration.has_generics) (decltype(this->as.EntityDeclaration.has_generics))(move(rhs.as.EntityDeclaration.has_generics));
new (&this->as.EntityDeclaration.generic_nesting) (decltype(this->as.EntityDeclaration.generic_nesting))(move(rhs.as.EntityDeclaration.generic_nesting));
new (&this->as.EntityDeclaration.is_extern) (decltype(this->as.EntityDeclaration.is_extern))(move(rhs.as.EntityDeclaration.is_extern));
break;
case 5 /* Implements */:
break;
case 6 /* CaptureList */:
break;
case 7 /* ParameterList */:
new (&this->as.ParameterList.open_parens) (decltype(this->as.ParameterList.open_parens))(move(rhs.as.ParameterList.open_parens));
break;
case 8 /* RestrictionList */:
break;
case 9 /* EntityDefinition */:
new (&this->as.EntityDefinition.entity) (decltype(this->as.EntityDefinition.entity))(move(rhs.as.EntityDefinition.entity));
new (&this->as.EntityDefinition.is_extern) (decltype(this->as.EntityDefinition.is_extern))(move(rhs.as.EntityDefinition.is_extern));
break;
case 10 /* StatementContext */:
new (&this->as.StatementContext.open_parens) (decltype(this->as.StatementContext.open_parens))(move(rhs.as.StatementContext.open_parens));
new (&this->as.StatementContext.open_curlies) (decltype(this->as.StatementContext.open_curlies))(move(rhs.as.StatementContext.open_curlies));
new (&this->as.StatementContext.open_squares) (decltype(this->as.StatementContext.open_squares))(move(rhs.as.StatementContext.open_squares));
new (&this->as.StatementContext.arrow_indents) (decltype(this->as.StatementContext.arrow_indents))(move(rhs.as.StatementContext.arrow_indents));
new (&this->as.StatementContext.allow_eol) (decltype(this->as.StatementContext.allow_eol))(move(rhs.as.StatementContext.allow_eol));
new (&this->as.StatementContext.inserted_comma) (decltype(this->as.StatementContext.inserted_comma))(move(rhs.as.StatementContext.inserted_comma));
new (&this->as.StatementContext.expression_mode) (decltype(this->as.StatementContext.expression_mode))(move(rhs.as.StatementContext.expression_mode));
new (&this->as.StatementContext.dedents_on_open_curly) (decltype(this->as.StatementContext.dedents_on_open_curly))(move(rhs.as.StatementContext.dedents_on_open_curly));
break;
case 11 /* MatchPattern */:
new (&this->as.MatchPattern.open_parens) (decltype(this->as.MatchPattern.open_parens))(move(rhs.as.MatchPattern.open_parens));
new (&this->as.MatchPattern.allow_multiple) (decltype(this->as.MatchPattern.allow_multiple))(move(rhs.as.MatchPattern.allow_multiple));
break;
case 12 /* VariableDeclaration */:
new (&this->as.VariableDeclaration.open_parens) (decltype(this->as.VariableDeclaration.open_parens))(move(rhs.as.VariableDeclaration.open_parens));
break;
case 13 /* GenericCallTypeParams */:
new (&this->as.GenericCallTypeParams.open_angles) (decltype(this->as.GenericCallTypeParams.open_angles))(move(rhs.as.GenericCallTypeParams.open_angles));
break;
case 14 /* TypeContext */:
new (&this->as.TypeContext.open_parens) (decltype(this->as.TypeContext.open_parens))(move(rhs.as.TypeContext.open_parens));
new (&this->as.TypeContext.open_curlies) (decltype(this->as.TypeContext.open_curlies))(move(rhs.as.TypeContext.open_curlies));
new (&this->as.TypeContext.open_squares) (decltype(this->as.TypeContext.open_squares))(move(rhs.as.TypeContext.open_squares));
new (&this->as.TypeContext.open_angles) (decltype(this->as.TypeContext.open_angles))(move(rhs.as.TypeContext.open_angles));
new (&this->as.TypeContext.seen_start) (decltype(this->as.TypeContext.seen_start))(move(rhs.as.TypeContext.seen_start));
break;
case 15 /* FunctionTypeContext */:
new (&this->as.FunctionTypeContext.seen_final_type) (decltype(this->as.FunctionTypeContext.seen_final_type))(move(rhs.as.FunctionTypeContext.seen_final_type));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
State::~State(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void State::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Toplevel */:break;
case 1 /* Extern */:break;
case 2 /* Import */:break;
case 3 /* ImportList */:break;
case 4 /* EntityDeclaration */:this->as.EntityDeclaration.entity.~Entity();
break;
case 5 /* Implements */:break;
case 6 /* CaptureList */:break;
case 7 /* ParameterList */:break;
case 8 /* RestrictionList */:break;
case 9 /* EntityDefinition */:this->as.EntityDefinition.entity.~Entity();
break;
case 10 /* StatementContext */:this->as.StatementContext.allow_eol.~Optional();
this->as.StatementContext.expression_mode.~ExpressionMode();
break;
case 11 /* MatchPattern */:break;
case 12 /* VariableDeclaration */:break;
case 13 /* GenericCallTypeParams */:break;
case 14 /* TypeContext */:break;
case 15 /* FunctionTypeContext */:break;
}
}
ByteString Jakt::formatter::State::name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Toplevel */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("toplevel"sv)));
};/*case end*/
case 1 /* Extern */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("extern"sv)));
};/*case end*/
case 2 /* Import */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("import"sv)));
};/*case end*/
case 3 /* ImportList */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("import list"sv)));
};/*case end*/
case 5 /* Implements */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("implements"sv)));
};/*case end*/
case 4 /* EntityDeclaration */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("entity declaration"sv)));
};/*case end*/
case 6 /* CaptureList */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("capture list"sv)));
};/*case end*/
case 7 /* ParameterList */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("parameter list"sv)));
};/*case end*/
case 8 /* RestrictionList */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("restriction list"sv)));
};/*case end*/
case 9 /* EntityDefinition */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("entity definition"sv)));
};/*case end*/
case 10 /* StatementContext */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("statement context"sv)));
};/*case end*/
case 11 /* MatchPattern */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("match pattern"sv)));
};/*case end*/
case 12 /* VariableDeclaration */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("variable declaration"sv)));
};/*case end*/
case 13 /* GenericCallTypeParams */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("generic call type params"sv)));
};/*case end*/
case 14 /* TypeContext */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeContext;size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& open_angles = __jakt_match_value.open_angles;
bool const& seen_start = __jakt_match_value.seen_start;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("type context (p{} c{} s{} a{} s:{})"sv)),open_parens,open_curlies,open_squares,open_angles,seen_start));
};/*case end*/
case 15 /* FunctionTypeContext */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("function type context"sv)));
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

ByteString Jakt::formatter::BreakablePoint::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Paren */: {
builder.append("BreakablePoint::Paren"sv);
[[maybe_unused]] auto const& that = this->as.Paren;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("point: {}, ", that.point);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("length: {}", that.length);
}
builder.append(")"sv);
break;}
case 1 /* Curly */: {
builder.append("BreakablePoint::Curly"sv);
[[maybe_unused]] auto const& that = this->as.Curly;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("point: {}, ", that.point);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("length: {}", that.length);
}
builder.append(")"sv);
break;}
case 2 /* Square */: {
builder.append("BreakablePoint::Square"sv);
[[maybe_unused]] auto const& that = this->as.Square;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("point: {}, ", that.point);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("length: {}", that.length);
}
builder.append(")"sv);
break;}
case 3 /* Logical */: {
builder.append("BreakablePoint::Logical"sv);
[[maybe_unused]] auto const& that = this->as.Logical;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("point: {}, ", that.point);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("length: {}", that.length);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] BreakablePoint BreakablePoint::Paren(size_t point, size_t length){
BreakablePoint __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Paren.point) (decltype(point))(move(point));
new (&__jakt_uninit_enum.as.Paren.length) (decltype(length))(move(length));
return __jakt_uninit_enum;
}
[[nodiscard]] BreakablePoint BreakablePoint::Curly(size_t point, size_t length){
BreakablePoint __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Curly.point) (decltype(point))(move(point));
new (&__jakt_uninit_enum.as.Curly.length) (decltype(length))(move(length));
return __jakt_uninit_enum;
}
[[nodiscard]] BreakablePoint BreakablePoint::Square(size_t point, size_t length){
BreakablePoint __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Square.point) (decltype(point))(move(point));
new (&__jakt_uninit_enum.as.Square.length) (decltype(length))(move(length));
return __jakt_uninit_enum;
}
[[nodiscard]] BreakablePoint BreakablePoint::Logical(size_t point, size_t length){
BreakablePoint __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.Logical.point) (decltype(point))(move(point));
new (&__jakt_uninit_enum.as.Logical.length) (decltype(length))(move(length));
return __jakt_uninit_enum;
}
BreakablePoint& BreakablePoint::operator=(BreakablePoint const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Paren */:
new (&this->as.Paren.point) (decltype(this->as.Paren.point))(rhs.as.Paren.point);
new (&this->as.Paren.length) (decltype(this->as.Paren.length))(rhs.as.Paren.length);
break;
case 1 /* Curly */:
new (&this->as.Curly.point) (decltype(this->as.Curly.point))(rhs.as.Curly.point);
new (&this->as.Curly.length) (decltype(this->as.Curly.length))(rhs.as.Curly.length);
break;
case 2 /* Square */:
new (&this->as.Square.point) (decltype(this->as.Square.point))(rhs.as.Square.point);
new (&this->as.Square.length) (decltype(this->as.Square.length))(rhs.as.Square.length);
break;
case 3 /* Logical */:
new (&this->as.Logical.point) (decltype(this->as.Logical.point))(rhs.as.Logical.point);
new (&this->as.Logical.length) (decltype(this->as.Logical.length))(rhs.as.Logical.length);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Paren */:
this->as.Paren.point = rhs.as.Paren.point;
this->as.Paren.length = rhs.as.Paren.length;
break;
case 1 /* Curly */:
this->as.Curly.point = rhs.as.Curly.point;
this->as.Curly.length = rhs.as.Curly.length;
break;
case 2 /* Square */:
this->as.Square.point = rhs.as.Square.point;
this->as.Square.length = rhs.as.Square.length;
break;
case 3 /* Logical */:
this->as.Logical.point = rhs.as.Logical.point;
this->as.Logical.length = rhs.as.Logical.length;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BreakablePoint::BreakablePoint(BreakablePoint const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Paren */:
new (&this->as.Paren.point) (decltype(this->as.Paren.point))(rhs.as.Paren.point);
new (&this->as.Paren.length) (decltype(this->as.Paren.length))(rhs.as.Paren.length);
break;
case 1 /* Curly */:
new (&this->as.Curly.point) (decltype(this->as.Curly.point))(rhs.as.Curly.point);
new (&this->as.Curly.length) (decltype(this->as.Curly.length))(rhs.as.Curly.length);
break;
case 2 /* Square */:
new (&this->as.Square.point) (decltype(this->as.Square.point))(rhs.as.Square.point);
new (&this->as.Square.length) (decltype(this->as.Square.length))(rhs.as.Square.length);
break;
case 3 /* Logical */:
new (&this->as.Logical.point) (decltype(this->as.Logical.point))(rhs.as.Logical.point);
new (&this->as.Logical.length) (decltype(this->as.Logical.length))(rhs.as.Logical.length);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
BreakablePoint& BreakablePoint::operator=(BreakablePoint &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Paren */:
new (&this->as.Paren.point) (decltype(this->as.Paren.point))(move(rhs.as.Paren.point));
new (&this->as.Paren.length) (decltype(this->as.Paren.length))(move(rhs.as.Paren.length));
break;
case 1 /* Curly */:
new (&this->as.Curly.point) (decltype(this->as.Curly.point))(move(rhs.as.Curly.point));
new (&this->as.Curly.length) (decltype(this->as.Curly.length))(move(rhs.as.Curly.length));
break;
case 2 /* Square */:
new (&this->as.Square.point) (decltype(this->as.Square.point))(move(rhs.as.Square.point));
new (&this->as.Square.length) (decltype(this->as.Square.length))(move(rhs.as.Square.length));
break;
case 3 /* Logical */:
new (&this->as.Logical.point) (decltype(this->as.Logical.point))(move(rhs.as.Logical.point));
new (&this->as.Logical.length) (decltype(this->as.Logical.length))(move(rhs.as.Logical.length));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Paren */:
this->as.Paren.point = move(rhs.as.Paren.point);
this->as.Paren.length = move(rhs.as.Paren.length);
break;
case 1 /* Curly */:
this->as.Curly.point = move(rhs.as.Curly.point);
this->as.Curly.length = move(rhs.as.Curly.length);
break;
case 2 /* Square */:
this->as.Square.point = move(rhs.as.Square.point);
this->as.Square.length = move(rhs.as.Square.length);
break;
case 3 /* Logical */:
this->as.Logical.point = move(rhs.as.Logical.point);
this->as.Logical.length = move(rhs.as.Logical.length);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BreakablePoint::BreakablePoint(BreakablePoint &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Paren */:
new (&this->as.Paren.point) (decltype(this->as.Paren.point))(move(rhs.as.Paren.point));
new (&this->as.Paren.length) (decltype(this->as.Paren.length))(move(rhs.as.Paren.length));
break;
case 1 /* Curly */:
new (&this->as.Curly.point) (decltype(this->as.Curly.point))(move(rhs.as.Curly.point));
new (&this->as.Curly.length) (decltype(this->as.Curly.length))(move(rhs.as.Curly.length));
break;
case 2 /* Square */:
new (&this->as.Square.point) (decltype(this->as.Square.point))(move(rhs.as.Square.point));
new (&this->as.Square.length) (decltype(this->as.Square.length))(move(rhs.as.Square.length));
break;
case 3 /* Logical */:
new (&this->as.Logical.point) (decltype(this->as.Logical.point))(move(rhs.as.Logical.point));
new (&this->as.Logical.length) (decltype(this->as.Logical.length))(move(rhs.as.Logical.length));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
BreakablePoint::~BreakablePoint(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void BreakablePoint::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Paren */:break;
case 1 /* Curly */:break;
case 2 /* Square */:break;
case 3 /* Logical */:break;
}
}
size_t Jakt::formatter::BreakablePoint::point() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Paren */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Paren;size_t const& point = __jakt_match_value.point;
return JaktInternal::ExplicitValue(point);
};/*case end*/
case 1 /* Curly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Curly;size_t const& point = __jakt_match_value.point;
return JaktInternal::ExplicitValue(point);
};/*case end*/
case 2 /* Square */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Square;size_t const& point = __jakt_match_value.point;
return JaktInternal::ExplicitValue(point);
};/*case end*/
case 3 /* Logical */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Logical;size_t const& point = __jakt_match_value.point;
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

size_t Jakt::formatter::BreakablePoint::length() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Paren */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Paren;size_t const& length = __jakt_match_value.length;
return JaktInternal::ExplicitValue(length);
};/*case end*/
case 1 /* Curly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Curly;size_t const& length = __jakt_match_value.length;
return JaktInternal::ExplicitValue(length);
};/*case end*/
case 2 /* Square */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Square;size_t const& length = __jakt_match_value.length;
return JaktInternal::ExplicitValue(length);
};/*case end*/
case 3 /* Logical */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Logical;size_t const& length = __jakt_match_value.length;
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

}
} // namespace Jakt
