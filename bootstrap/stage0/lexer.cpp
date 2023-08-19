#include "lexer.h"
namespace Jakt {
namespace lexer {
ErrorOr<DeprecatedString> lexer::Lexer::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Lexer("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("index: {}, ", index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("input: {}, ", input));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("compiler: {}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("comment_contents: {}, ", comment_contents));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("illegal_cpp_keywords: {}", illegal_cpp_keywords));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<DeprecatedString>> lexer::Lexer::consume_comment_contents() {
{
if ((!(((((*this).comment_contents)).has_value())))){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<u8> const contents = (((*this).comment_contents).value());
(((*this).comment_contents) = JaktInternal::OptionalNone());
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
{
JaktInternal::ArrayIterator<u8> _magic = ((contents).iterator());
for (;;){
JaktInternal::Optional<u8> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u8 c = (_magic_value.value());
{
TRY((((builder).append(c))));
}

}
}

return TRY((((builder).to_string())));
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_quoted_string(u8 const delimiter) {
{
size_t const start = ((*this).index);
(++(((*this).index)));
if (((*this).eof())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("unexpected eof"sv)),((*this).span(start,start))))));
return  lexer::Token { typename lexer::Token::Garbage(JaktInternal::OptionalNone(),((*this).span(start,start))) } ;
}
bool escaped = false;
while (((!(((*this).eof()))) && (escaped || ((((*this).peek())) != (delimiter))))){
if ((((((*this).peek())) == (static_cast<u8>(u8'\r'))) || ((((*this).peek())) == (static_cast<u8>(u8'\n'))))){
(++(((*this).index)));
continue;
}
if (((!(escaped)) && ((((*this).peek())) == (static_cast<u8>(u8'\\'))))){
(escaped = true);
}
else {
(escaped = false);
}

(++(((*this).index)));
}
DeprecatedString const str = TRY((((*this).substring(JaktInternal::checked_add(start,static_cast<size_t>(1ULL)),((*this).index)))));
((((*this).index)++));
size_t const end = ((*this).index);
if (((delimiter) == (static_cast<u8>(u8'\'')))){
return  lexer::Token { typename lexer::Token::SingleQuotedString(str,JaktInternal::OptionalNone(),((*this).span(start,end))) } ;
}
return  lexer::Token { typename lexer::Token::QuotedString(str,((*this).span(start,end))) } ;
}
}

ErrorOr<JaktInternal::Optional<lexer::Token>> lexer::Lexer::next() {
{
for (;;){
if (((((*this).index)) == (((((*this).input)).size())))){
(++(((*this).index)));
return  lexer::Token { typename lexer::Token::Eof(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL))))) } ;
}
if (((*this).eof())){
return JaktInternal::OptionalNone();
}
u8 const ch = ((*this).peek());
if (utility::is_whitespace(ch)){
((((*this).index)++));
}
else {
break;
}

}
size_t const start = ((*this).index);
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<lexer::Token>,ErrorOr<JaktInternal::Optional<lexer::Token>>>{
auto __jakt_enum_value = (((((*this).input))[((*this).index)]));
if (__jakt_enum_value == static_cast<u8>(u8'(')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LParen(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8')')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RParen(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'[')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LSquare(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8']')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RSquare(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'{')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LCurly(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'}')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RCurly(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'<')) {
return JaktInternal::ExplicitValue(((*this).lex_less_than()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue(((*this).lex_greater_than()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'.')) {
return JaktInternal::ExplicitValue(((*this).lex_dot()));
}
else if (__jakt_enum_value == static_cast<u8>(u8',')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Comma(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'~')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Tilde(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8';')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Semicolon(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8':')) {
return JaktInternal::ExplicitValue(((*this).lex_colon()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'?')) {
return JaktInternal::ExplicitValue(((*this).lex_question_mark()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'+')) {
return JaktInternal::ExplicitValue(((*this).lex_plus()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'-')) {
return JaktInternal::ExplicitValue(((*this).lex_minus()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'*')) {
return JaktInternal::ExplicitValue(((*this).lex_asterisk()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'/')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_forward_slash()))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'^')) {
return JaktInternal::ExplicitValue(((*this).lex_caret()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'|')) {
return JaktInternal::ExplicitValue(((*this).lex_pipe()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'%')) {
return JaktInternal::ExplicitValue(((*this).lex_percent_sign()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'!')) {
return JaktInternal::ExplicitValue(((*this).lex_exclamation_point()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'&')) {
return JaktInternal::ExplicitValue(((*this).lex_ampersand()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'$')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Dollar(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(((*this).lex_equals()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'\n')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Eol(TRY((((*this).consume_comment_contents()))),((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'\'')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_quoted_string(static_cast<u8>(u8'\''))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'\"')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_quoted_string(static_cast<u8>(u8'"'))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'b')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_character_constant_or_name()))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'c')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_character_constant_or_name()))));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).lex_number_or_name()))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_character_constant_or_name() {
{
if (((((*this).peek_ahead(static_cast<size_t>(1ULL)))) != (static_cast<u8>(u8'\'')))){
return TRY((((*this).lex_number_or_name())));
}
JaktInternal::Optional<DeprecatedString> const prefix = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<DeprecatedString>,ErrorOr<lexer::Token>>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'b')) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("b"sv)));
}
else if (__jakt_enum_value == static_cast<u8>(u8'c')) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("c"sv)));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((prefix).has_value())){
((((*this).index)) += (static_cast<size_t>(1ULL)));
}
size_t const start = ((*this).index);
((((*this).index)++));
bool escaped = false;
while (((!(((*this).eof()))) && (escaped || ((((*this).peek())) != (static_cast<u8>(u8'\'')))))){
if ((escaped && [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(JaktInternal::checked_sub(((*this).index),start),static_cast<size_t>(3ULL)))){
break;
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
(JaktInternal::checked_sub(((*this).index),start),static_cast<size_t>(2ULL))){
break;
}
if (((!(escaped)) && ((((*this).peek())) == (static_cast<u8>(u8'\\'))))){
(escaped = true);
}
((((*this).index)++));
}
if ((((*this).eof()) || ((((*this).peek())) != (static_cast<u8>(u8'\''))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Expected single quote"sv)),((*this).span(start,start))))));
}
((((*this).index)) += (static_cast<size_t>(1ULL)));
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
TRY((((builder).append(((((*this).input))[JaktInternal::checked_add(start,static_cast<size_t>(1ULL))])))));
if (escaped){
TRY((((builder).append(((((*this).input))[JaktInternal::checked_add(start,static_cast<size_t>(2ULL))])))));
}
DeprecatedString const quote = TRY((((builder).to_string())));
size_t const end = ((*this).index);
return  lexer::Token { typename lexer::Token::SingleQuotedString(quote,prefix,((*this).span(start,end))) } ;
}
}

lexer::Token lexer::Lexer::lex_dot() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'.')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::DotDot(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Dot(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_question_mark() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'?')) {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_4; {
((((*this).index)++));
__jakt_var_4 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::QuestionMarkQuestionMarkEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::QuestionMarkQuestionMark(((*this).span(start,((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_0;

}
__jakt_label_0:; __jakt_var_4.release_value(); }));
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::QuestionMark(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_forward_slash() {
{
size_t const start = ((((*this).index)++));
if (((((*this).peek())) == (static_cast<u8>(u8'=')))){
return  lexer::Token { typename lexer::Token::ForwardSlashEqual(((*this).span(start,(++(((*this).index)))))) } ;
}
if (((((*this).peek())) != (static_cast<u8>(u8'/')))){
return  lexer::Token { typename lexer::Token::ForwardSlash(((*this).span(start,((*this).index)))) } ;
}
if (((((*this).comment_contents)).has_value())){
((((*this).index)--));
return  lexer::Token { typename lexer::Token::Eol(TRY((((*this).consume_comment_contents()))),((*this).span(start,((*this).index)))) } ;
}
((((*this).index)++));
size_t const comment_start_index = ((*this).index);
while ((!(((*this).eof())))){
u8 const c = ((*this).peek());
((((*this).index)++));
if (((c) == (static_cast<u8>(u8'\n')))){
((((*this).index)--));
break;
}
}
(((*this).comment_contents) = TRY((((((((*this).input))[(JaktInternal::Range<size_t>{static_cast<size_t>(comment_start_index),static_cast<size_t>(((*this).index))})])).to_array()))));
return TRY((((*this).next()))).value_or_lazy_evaluated([&] { return  lexer::Token { typename lexer::Token::Eof(((*this).span(((*this).index),((*this).index)))) } ; });
}
}

u8 lexer::Lexer::peek_behind(size_t const steps) const {
{
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((*this).index),steps)){
return static_cast<u8>(0);
}
return ((((*this).input))[JaktInternal::checked_sub(((*this).index),steps)]);
}
}

u8 lexer::Lexer::peek_ahead(size_t const steps) const {
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
(JaktInternal::checked_add(((*this).index),steps),((((*this).input)).size()))){
return static_cast<u8>(0);
}
return ((((*this).input))[JaktInternal::checked_add(((*this).index),steps)]);
}
}

lexer::Token lexer::Lexer::lex_asterisk() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::AsteriskEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Asterisk(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_minus() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::MinusEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'-')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::MinusMinus(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Arrow(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Minus(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

u8 lexer::Lexer::peek() const {
{
if (((*this).eof())){
return static_cast<u8>(0);
}
return ((((*this).input))[((*this).index)]);
}
}

lexer::Token lexer::Lexer::lex_percent_sign() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PercentSignEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PercentSign(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_number_or_name() {
{
size_t const start = ((*this).index);
if (((*this).eof())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("unexpected eof"sv)),((*this).span(start,start))))));
return  lexer::Token { typename lexer::Token::Garbage(JaktInternal::OptionalNone(),((*this).span(start,start))) } ;
}
if (utility::is_ascii_digit(((*this).peek()))){
return TRY((((*this).lex_number())));
}
else if ((utility::is_ascii_alpha(((*this).peek())) || ((((*this).peek())) == (static_cast<u8>(u8'_'))))){
DeprecatedStringBuilder string_builder = DeprecatedStringBuilder::create();
while ((utility::is_ascii_alphanumeric(((*this).peek())) || ((((*this).peek())) == (static_cast<u8>(u8'_'))))){
u8 const value = ((((*this).input))[((*this).index)]);
(++(((*this).index)));
TRY((((string_builder).append(value))));
}
size_t const end = ((*this).index);
utility::Span const span = ((*this).span(start,end));
DeprecatedString const string = TRY((((string_builder).to_string())));
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
(JaktInternal::checked_sub(end,start),static_cast<size_t>(6ULL)) && ((((string).substring(static_cast<size_t>(0ULL),static_cast<size_t>(6ULL)))) == (TRY(DeprecatedString::from_utf8("__jakt"sv)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("reserved identifier name"sv)),span))));
}
if (((((*this).illegal_cpp_keywords)).contains(string))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("C++ keywords are not allowed to be used as identifiers"sv)),span))));
}
return TRY((lexer::Token::from_keyword_or_identifier(string,span)));
}
u8 const unknown_char = ((((*this).input))[((*this).index)]);
size_t const end = (++(((*this).index)));
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown character: {:c}"sv)),unknown_char))),((*this).span(start,end))))));
return  lexer::Token { typename lexer::Token::Garbage(TRY((__jakt_format((StringView::from_string_literal("{:c}"sv)),unknown_char))),((*this).span(start,end))) } ;
}
}

lexer::Token lexer::Lexer::lex_less_than() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LessThanOrEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'<')) {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_5; {
((((*this).index)++));
__jakt_var_5 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'<')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LeftArithmeticShift(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LeftShiftEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LeftShift(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_1;

}
__jakt_label_1:; __jakt_var_5.release_value(); }));
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LessThan(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool lexer::Lexer::eof() const {
{
return [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((*this).index),((((*this).input)).size()));
}
}

lexer::Lexer::Lexer(size_t a_index, JaktInternal::DynamicArray<u8> a_input, NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> a_comment_contents, JaktInternal::Set<DeprecatedString> a_illegal_cpp_keywords) :index(move(a_index)), input(move(a_input)), compiler(move(a_compiler)), comment_contents(move(a_comment_contents)), illegal_cpp_keywords(move(a_illegal_cpp_keywords)){}

lexer::Token lexer::Lexer::lex_ampersand() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::AmpersandEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'&')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::AmpersandAmpersand(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Ampersand(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

utility::Span lexer::Lexer::span(size_t const start,size_t const end) const {
{
return utility::Span((((((*this).compiler))->current_file).value()),start,end);
}
}

lexer::Token lexer::Lexer::lex_plus() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PlusEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'+')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PlusPlus(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Plus(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_exclamation_point() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::NotEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::ExclamationPoint(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::LiteralSuffix> lexer::Lexer::consume_numeric_literal_suffix() {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'u')) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u8>(u8'i')) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u8>(u8'f')) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
return  lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } ;
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((((((*this).peek())) == (static_cast<u8>(u8'u'))) && ((((*this).peek_ahead(static_cast<size_t>(1ULL)))) == (static_cast<u8>(u8'z'))))){
((((*this).index)) += (static_cast<size_t>(2ULL)));
return  lexer::LiteralSuffix { typename lexer::LiteralSuffix::UZ() } ;
}
size_t local_index = static_cast<size_t>(1ULL);
i64 width = static_cast<i64>(0LL);
while (utility::is_ascii_digit(((*this).peek_ahead(local_index)))){
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
(local_index,static_cast<size_t>(3ULL))){
return  lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } ;
}
u8 const value = ((((*this).input))[JaktInternal::checked_add(((*this).index),local_index)]);
(++(local_index));
i64 const digit = as_saturated<i64, u8>(JaktInternal::checked_sub(value,static_cast<u8>(u8'0')));
(width = JaktInternal::checked_add(JaktInternal::checked_mul(width,static_cast<i64>(10LL)),digit));
}
lexer::LiteralSuffix const suffix = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'u')) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (width);
if (__jakt_enum_value == static_cast<i64>(8LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::U8() } );
}
else if (__jakt_enum_value == static_cast<i64>(16LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::U16() } );
}
else if (__jakt_enum_value == static_cast<i64>(32LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::U32() } );
}
else if (__jakt_enum_value == static_cast<i64>(64LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::U64() } );
}
else {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == static_cast<u8>(u8'i')) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (width);
if (__jakt_enum_value == static_cast<i64>(8LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::I8() } );
}
else if (__jakt_enum_value == static_cast<i64>(16LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::I16() } );
}
else if (__jakt_enum_value == static_cast<i64>(32LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::I32() } );
}
else if (__jakt_enum_value == static_cast<i64>(64LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::I64() } );
}
else {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == static_cast<u8>(u8'f')) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (width);
if (__jakt_enum_value == static_cast<i64>(32LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::F32() } );
}
else if (__jakt_enum_value == static_cast<i64>(64LL)) {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::F64() } );
}
else {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((!(((suffix).index() == 0 /* None */)))){
((((*this).index)) += (local_index));
}
return suffix;
}
}

lexer::Token lexer::Lexer::lex_colon() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8':')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::ColonColon(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Colon(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool lexer::Lexer::valid_digit(lexer::LiteralPrefix const prefix,u8 const digit,bool const decimal_allowed) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = prefix;
switch(__jakt_match_variant.index()) {
case 1: {
return JaktInternal::ExplicitValue(utility::is_ascii_hexdigit(digit));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(utility::is_ascii_octdigit(digit));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(utility::is_ascii_binary(digit));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((utility::is_ascii_digit(digit) || (decimal_allowed && ((digit) == (static_cast<u8>(u8'.'))))));
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

ErrorOr<void> lexer::Lexer::error(DeprecatedString const message,utility::Span const span) {
{
TRY((((((((*this).compiler))->errors)).push( error::JaktError { typename error::JaktError::Message(message,span) } ))));
}
return {};
}

lexer::Token lexer::Lexer::lex_equals() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::DoubleEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::FatArrow(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Equal(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> lexer::Lexer::substring(size_t const start,size_t const length) const {
{
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(start),static_cast<size_t>(length)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((builder).append(((((*this).input))[i])))));
}

}
}

return TRY((((builder).to_string())));
}
}

lexer::Token lexer::Lexer::lex_greater_than() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::GreaterThanOrEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_6; {
((((*this).index)++));
__jakt_var_6 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RightArithmeticShift(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RightShiftEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RightShift(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_2;

}
__jakt_label_2:; __jakt_var_6.release_value(); }));
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::GreaterThan(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_pipe() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PipeEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == static_cast<u8>(u8'|')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PipePipe(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Pipe(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_caret() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::CaretEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Caret(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_number() {
{
size_t const start = ((*this).index);
bool floating = false;
lexer::LiteralPrefix prefix =  lexer::LiteralPrefix { typename lexer::LiteralPrefix::None() } ;
DeprecatedStringBuilder number = DeprecatedStringBuilder::create();
if (((((*this).peek())) == (static_cast<u8>(u8'0')))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<lexer::Token>>{
auto __jakt_enum_value = (((*this).peek_ahead(static_cast<size_t>(1ULL))));
if (__jakt_enum_value == static_cast<u8>(u8'x')) {
{
(prefix =  lexer::LiteralPrefix { typename lexer::LiteralPrefix::Hexadecimal() } );
((((*this).index)) += (static_cast<size_t>(2ULL)));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u8>(u8'o')) {
{
(prefix =  lexer::LiteralPrefix { typename lexer::LiteralPrefix::Octal() } );
((((*this).index)) += (static_cast<size_t>(2ULL)));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u8>(u8'b')) {
{
(prefix =  lexer::LiteralPrefix { typename lexer::LiteralPrefix::Binary() } );
((((*this).index)) += (static_cast<size_t>(2ULL)));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
while ((!(((*this).eof())))){
u8 const value = ((((*this).input))[((*this).index)]);
if ((!(((*this).valid_digit(prefix,value,true))))){
break;
}
if (((value) == (static_cast<u8>(u8'.')))){
if ((floating || (!(((*this).valid_digit(prefix,((*this).peek_ahead(static_cast<size_t>(1ULL))),false)))))){
break;
}
TRY((((number).append(static_cast<u8>(u8'.')))));
(floating = true);
((((*this).index)++));
continue;
}
TRY((((number).append(value))));
(++(((*this).index)));
if (((((*this).peek())) == (static_cast<u8>(u8'_')))){
TRY((((number).append(static_cast<u8>(u8'_')))));
if (((*this).valid_digit(prefix,((*this).peek_ahead(static_cast<size_t>(1ULL))),true))){
(++(((*this).index)));
}
else {
break;
}

}
}
lexer::LiteralSuffix const suffix = TRY((((*this).consume_numeric_literal_suffix())));
return  lexer::Token { typename lexer::Token::Number(prefix,TRY((((number).to_string()))),suffix,((*this).span(start,((*this).index)))) } ;
}
}

ErrorOr<JaktInternal::DynamicArray<lexer::Token>> lexer::Lexer::lex(NonnullRefPtr<compiler::Compiler> const compiler) {
{
JaktInternal::Set<DeprecatedString> const illegal_cpp_keywords = (TRY((Set<DeprecatedString>::create_with_values({TRY(DeprecatedString::from_utf8("alignas"sv)), TRY(DeprecatedString::from_utf8("alignof"sv)), TRY(DeprecatedString::from_utf8("and_eq"sv)), TRY(DeprecatedString::from_utf8("asm"sv)), TRY(DeprecatedString::from_utf8("auto"sv)), TRY(DeprecatedString::from_utf8("bitand"sv)), TRY(DeprecatedString::from_utf8("bitor"sv)), TRY(DeprecatedString::from_utf8("case"sv)), TRY(DeprecatedString::from_utf8("char"sv)), TRY(DeprecatedString::from_utf8("char8_t"sv)), TRY(DeprecatedString::from_utf8("char16_t"sv)), TRY(DeprecatedString::from_utf8("char32_t"sv)), TRY(DeprecatedString::from_utf8("compl"sv)), TRY(DeprecatedString::from_utf8("concept"sv)), TRY(DeprecatedString::from_utf8("consteval"sv)), TRY(DeprecatedString::from_utf8("constexpr"sv)), TRY(DeprecatedString::from_utf8("constinit"sv)), TRY(DeprecatedString::from_utf8("const_cast"sv)), TRY(DeprecatedString::from_utf8("co_await"sv)), TRY(DeprecatedString::from_utf8("co_return"sv)), TRY(DeprecatedString::from_utf8("co_yield"sv)), TRY(DeprecatedString::from_utf8("decltype"sv)), TRY(DeprecatedString::from_utf8("delete"sv)), TRY(DeprecatedString::from_utf8("do"sv)), TRY(DeprecatedString::from_utf8("double"sv)), TRY(DeprecatedString::from_utf8("dynamic_cast"sv)), TRY(DeprecatedString::from_utf8("explicit"sv)), TRY(DeprecatedString::from_utf8("export"sv)), TRY(DeprecatedString::from_utf8("float"sv)), TRY(DeprecatedString::from_utf8("friend"sv)), TRY(DeprecatedString::from_utf8("goto"sv)), TRY(DeprecatedString::from_utf8("int"sv)), TRY(DeprecatedString::from_utf8("long"sv)), TRY(DeprecatedString::from_utf8("mutable"sv)), TRY(DeprecatedString::from_utf8("new"sv)), TRY(DeprecatedString::from_utf8("noexcept"sv)), TRY(DeprecatedString::from_utf8("not_eq"sv)), TRY(DeprecatedString::from_utf8("nullptr"sv)), TRY(DeprecatedString::from_utf8("operator"sv)), TRY(DeprecatedString::from_utf8("or_eq"sv)), TRY(DeprecatedString::from_utf8("protected"sv)), TRY(DeprecatedString::from_utf8("register"sv)), TRY(DeprecatedString::from_utf8("reinterpret_cast"sv)), TRY(DeprecatedString::from_utf8("short"sv)), TRY(DeprecatedString::from_utf8("signed"sv)), TRY(DeprecatedString::from_utf8("static"sv)), TRY(DeprecatedString::from_utf8("static_assert"sv)), TRY(DeprecatedString::from_utf8("static_cast"sv)), TRY(DeprecatedString::from_utf8("switch"sv)), TRY(DeprecatedString::from_utf8("template"sv)), TRY(DeprecatedString::from_utf8("thread_local"sv)), TRY(DeprecatedString::from_utf8("typedef"sv)), TRY(DeprecatedString::from_utf8("typeid"sv)), TRY(DeprecatedString::from_utf8("typename"sv)), TRY(DeprecatedString::from_utf8("union"sv)), TRY(DeprecatedString::from_utf8("unsigned"sv)), TRY(DeprecatedString::from_utf8("using"sv)), TRY(DeprecatedString::from_utf8("volatile"sv)), TRY(DeprecatedString::from_utf8("wchar_t"sv)), TRY(DeprecatedString::from_utf8("xor"sv)), TRY(DeprecatedString::from_utf8("xor_eq"sv))}))));
lexer::Lexer lexer = lexer::Lexer(static_cast<size_t>(0ULL),((compiler)->current_file_contents),compiler,JaktInternal::OptionalNone(),illegal_cpp_keywords);
JaktInternal::DynamicArray<lexer::Token> tokens = (TRY((DynamicArray<lexer::Token>::create_with({}))));
{
lexer::Lexer _magic = lexer;
for (;;){
JaktInternal::Optional<lexer::Token> const _magic_value = TRY((((_magic).next())));
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
TRY((((tokens).push(token))));
}

}
}

return tokens;
}
}

ErrorOr<DeprecatedString> lexer::LiteralSuffix::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* None */: {
return DeprecatedString("LiteralSuffix::None"sv);
break;}
case 1 /* UZ */: {
return DeprecatedString("LiteralSuffix::UZ"sv);
break;}
case 2 /* U8 */: {
return DeprecatedString("LiteralSuffix::U8"sv);
break;}
case 3 /* U16 */: {
return DeprecatedString("LiteralSuffix::U16"sv);
break;}
case 4 /* U32 */: {
return DeprecatedString("LiteralSuffix::U32"sv);
break;}
case 5 /* U64 */: {
return DeprecatedString("LiteralSuffix::U64"sv);
break;}
case 6 /* I8 */: {
return DeprecatedString("LiteralSuffix::I8"sv);
break;}
case 7 /* I16 */: {
return DeprecatedString("LiteralSuffix::I16"sv);
break;}
case 8 /* I32 */: {
return DeprecatedString("LiteralSuffix::I32"sv);
break;}
case 9 /* I64 */: {
return DeprecatedString("LiteralSuffix::I64"sv);
break;}
case 10 /* F32 */: {
return DeprecatedString("LiteralSuffix::F32"sv);
break;}
case 11 /* F64 */: {
return DeprecatedString("LiteralSuffix::F64"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> lexer::LiteralSuffix::to_string() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("uz"sv)));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u8"sv)));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u16"sv)));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u32"sv)));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u64"sv)));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i8"sv)));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i16"sv)));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i32"sv)));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i64"sv)));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("f32"sv)));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("f64"sv)));
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

ErrorOr<DeprecatedString> lexer::Token::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* SingleQuotedString */: {
TRY(builder.append("Token::SingleQuotedString"sv));
[[maybe_unused]] auto const& that = this->template get<Token::SingleQuotedString>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("quote: \"{}\", ", that.quote));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("prefix: {}, ", that.prefix));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 1 /* QuotedString */: {
TRY(builder.append("Token::QuotedString"sv));
[[maybe_unused]] auto const& that = this->template get<Token::QuotedString>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("quote: \"{}\", ", that.quote));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 2 /* Number */: {
TRY(builder.append("Token::Number"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Number>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("prefix: {}, ", that.prefix));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("number: \"{}\", ", that.number));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("suffix: {}, ", that.suffix));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 3 /* Identifier */: {
TRY(builder.append("Token::Identifier"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Identifier>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 4 /* Semicolon */: {
TRY(builder.append("Token::Semicolon"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Semicolon>();
TRY(builder.appendff("({})", that.value));
break;}
case 5 /* Colon */: {
TRY(builder.append("Token::Colon"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Colon>();
TRY(builder.appendff("({})", that.value));
break;}
case 6 /* ColonColon */: {
TRY(builder.append("Token::ColonColon"sv));
[[maybe_unused]] auto const& that = this->template get<Token::ColonColon>();
TRY(builder.appendff("({})", that.value));
break;}
case 7 /* LParen */: {
TRY(builder.append("Token::LParen"sv));
[[maybe_unused]] auto const& that = this->template get<Token::LParen>();
TRY(builder.appendff("({})", that.value));
break;}
case 8 /* RParen */: {
TRY(builder.append("Token::RParen"sv));
[[maybe_unused]] auto const& that = this->template get<Token::RParen>();
TRY(builder.appendff("({})", that.value));
break;}
case 9 /* LCurly */: {
TRY(builder.append("Token::LCurly"sv));
[[maybe_unused]] auto const& that = this->template get<Token::LCurly>();
TRY(builder.appendff("({})", that.value));
break;}
case 10 /* RCurly */: {
TRY(builder.append("Token::RCurly"sv));
[[maybe_unused]] auto const& that = this->template get<Token::RCurly>();
TRY(builder.appendff("({})", that.value));
break;}
case 11 /* LSquare */: {
TRY(builder.append("Token::LSquare"sv));
[[maybe_unused]] auto const& that = this->template get<Token::LSquare>();
TRY(builder.appendff("({})", that.value));
break;}
case 12 /* RSquare */: {
TRY(builder.append("Token::RSquare"sv));
[[maybe_unused]] auto const& that = this->template get<Token::RSquare>();
TRY(builder.appendff("({})", that.value));
break;}
case 13 /* PercentSign */: {
TRY(builder.append("Token::PercentSign"sv));
[[maybe_unused]] auto const& that = this->template get<Token::PercentSign>();
TRY(builder.appendff("({})", that.value));
break;}
case 14 /* Plus */: {
TRY(builder.append("Token::Plus"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Plus>();
TRY(builder.appendff("({})", that.value));
break;}
case 15 /* Minus */: {
TRY(builder.append("Token::Minus"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Minus>();
TRY(builder.appendff("({})", that.value));
break;}
case 16 /* Equal */: {
TRY(builder.append("Token::Equal"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Equal>();
TRY(builder.appendff("({})", that.value));
break;}
case 17 /* PlusEqual */: {
TRY(builder.append("Token::PlusEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::PlusEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 18 /* PlusPlus */: {
TRY(builder.append("Token::PlusPlus"sv));
[[maybe_unused]] auto const& that = this->template get<Token::PlusPlus>();
TRY(builder.appendff("({})", that.value));
break;}
case 19 /* MinusEqual */: {
TRY(builder.append("Token::MinusEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::MinusEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 20 /* MinusMinus */: {
TRY(builder.append("Token::MinusMinus"sv));
[[maybe_unused]] auto const& that = this->template get<Token::MinusMinus>();
TRY(builder.appendff("({})", that.value));
break;}
case 21 /* AsteriskEqual */: {
TRY(builder.append("Token::AsteriskEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::AsteriskEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 22 /* ForwardSlashEqual */: {
TRY(builder.append("Token::ForwardSlashEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::ForwardSlashEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 23 /* PercentSignEqual */: {
TRY(builder.append("Token::PercentSignEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::PercentSignEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 24 /* NotEqual */: {
TRY(builder.append("Token::NotEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::NotEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 25 /* DoubleEqual */: {
TRY(builder.append("Token::DoubleEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::DoubleEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 26 /* GreaterThan */: {
TRY(builder.append("Token::GreaterThan"sv));
[[maybe_unused]] auto const& that = this->template get<Token::GreaterThan>();
TRY(builder.appendff("({})", that.value));
break;}
case 27 /* GreaterThanOrEqual */: {
TRY(builder.append("Token::GreaterThanOrEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::GreaterThanOrEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 28 /* LessThan */: {
TRY(builder.append("Token::LessThan"sv));
[[maybe_unused]] auto const& that = this->template get<Token::LessThan>();
TRY(builder.appendff("({})", that.value));
break;}
case 29 /* LessThanOrEqual */: {
TRY(builder.append("Token::LessThanOrEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::LessThanOrEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 30 /* LeftArithmeticShift */: {
TRY(builder.append("Token::LeftArithmeticShift"sv));
[[maybe_unused]] auto const& that = this->template get<Token::LeftArithmeticShift>();
TRY(builder.appendff("({})", that.value));
break;}
case 31 /* LeftShift */: {
TRY(builder.append("Token::LeftShift"sv));
[[maybe_unused]] auto const& that = this->template get<Token::LeftShift>();
TRY(builder.appendff("({})", that.value));
break;}
case 32 /* LeftShiftEqual */: {
TRY(builder.append("Token::LeftShiftEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::LeftShiftEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 33 /* RightShift */: {
TRY(builder.append("Token::RightShift"sv));
[[maybe_unused]] auto const& that = this->template get<Token::RightShift>();
TRY(builder.appendff("({})", that.value));
break;}
case 34 /* RightArithmeticShift */: {
TRY(builder.append("Token::RightArithmeticShift"sv));
[[maybe_unused]] auto const& that = this->template get<Token::RightArithmeticShift>();
TRY(builder.appendff("({})", that.value));
break;}
case 35 /* RightShiftEqual */: {
TRY(builder.append("Token::RightShiftEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::RightShiftEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 36 /* Asterisk */: {
TRY(builder.append("Token::Asterisk"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Asterisk>();
TRY(builder.appendff("({})", that.value));
break;}
case 37 /* Ampersand */: {
TRY(builder.append("Token::Ampersand"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Ampersand>();
TRY(builder.appendff("({})", that.value));
break;}
case 38 /* AmpersandEqual */: {
TRY(builder.append("Token::AmpersandEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::AmpersandEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 39 /* AmpersandAmpersand */: {
TRY(builder.append("Token::AmpersandAmpersand"sv));
[[maybe_unused]] auto const& that = this->template get<Token::AmpersandAmpersand>();
TRY(builder.appendff("({})", that.value));
break;}
case 40 /* Pipe */: {
TRY(builder.append("Token::Pipe"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Pipe>();
TRY(builder.appendff("({})", that.value));
break;}
case 41 /* PipeEqual */: {
TRY(builder.append("Token::PipeEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::PipeEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 42 /* PipePipe */: {
TRY(builder.append("Token::PipePipe"sv));
[[maybe_unused]] auto const& that = this->template get<Token::PipePipe>();
TRY(builder.appendff("({})", that.value));
break;}
case 43 /* Caret */: {
TRY(builder.append("Token::Caret"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Caret>();
TRY(builder.appendff("({})", that.value));
break;}
case 44 /* CaretEqual */: {
TRY(builder.append("Token::CaretEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::CaretEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 45 /* Dollar */: {
TRY(builder.append("Token::Dollar"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Dollar>();
TRY(builder.appendff("({})", that.value));
break;}
case 46 /* Tilde */: {
TRY(builder.append("Token::Tilde"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Tilde>();
TRY(builder.appendff("({})", that.value));
break;}
case 47 /* ForwardSlash */: {
TRY(builder.append("Token::ForwardSlash"sv));
[[maybe_unused]] auto const& that = this->template get<Token::ForwardSlash>();
TRY(builder.appendff("({})", that.value));
break;}
case 48 /* ExclamationPoint */: {
TRY(builder.append("Token::ExclamationPoint"sv));
[[maybe_unused]] auto const& that = this->template get<Token::ExclamationPoint>();
TRY(builder.appendff("({})", that.value));
break;}
case 49 /* QuestionMark */: {
TRY(builder.append("Token::QuestionMark"sv));
[[maybe_unused]] auto const& that = this->template get<Token::QuestionMark>();
TRY(builder.appendff("({})", that.value));
break;}
case 50 /* QuestionMarkQuestionMark */: {
TRY(builder.append("Token::QuestionMarkQuestionMark"sv));
[[maybe_unused]] auto const& that = this->template get<Token::QuestionMarkQuestionMark>();
TRY(builder.appendff("({})", that.value));
break;}
case 51 /* QuestionMarkQuestionMarkEqual */: {
TRY(builder.append("Token::QuestionMarkQuestionMarkEqual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::QuestionMarkQuestionMarkEqual>();
TRY(builder.appendff("({})", that.value));
break;}
case 52 /* Comma */: {
TRY(builder.append("Token::Comma"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Comma>();
TRY(builder.appendff("({})", that.value));
break;}
case 53 /* Dot */: {
TRY(builder.append("Token::Dot"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Dot>();
TRY(builder.appendff("({})", that.value));
break;}
case 54 /* DotDot */: {
TRY(builder.append("Token::DotDot"sv));
[[maybe_unused]] auto const& that = this->template get<Token::DotDot>();
TRY(builder.appendff("({})", that.value));
break;}
case 55 /* Eol */: {
TRY(builder.append("Token::Eol"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Eol>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("comment: {}, ", that.comment));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 56 /* Eof */: {
TRY(builder.append("Token::Eof"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Eof>();
TRY(builder.appendff("({})", that.value));
break;}
case 57 /* FatArrow */: {
TRY(builder.append("Token::FatArrow"sv));
[[maybe_unused]] auto const& that = this->template get<Token::FatArrow>();
TRY(builder.appendff("({})", that.value));
break;}
case 58 /* Arrow */: {
TRY(builder.append("Token::Arrow"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Arrow>();
TRY(builder.appendff("({})", that.value));
break;}
case 59 /* And */: {
TRY(builder.append("Token::And"sv));
[[maybe_unused]] auto const& that = this->template get<Token::And>();
TRY(builder.appendff("({})", that.value));
break;}
case 60 /* Anon */: {
TRY(builder.append("Token::Anon"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Anon>();
TRY(builder.appendff("({})", that.value));
break;}
case 61 /* As */: {
TRY(builder.append("Token::As"sv));
[[maybe_unused]] auto const& that = this->template get<Token::As>();
TRY(builder.appendff("({})", that.value));
break;}
case 62 /* Boxed */: {
TRY(builder.append("Token::Boxed"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Boxed>();
TRY(builder.appendff("({})", that.value));
break;}
case 63 /* Break */: {
TRY(builder.append("Token::Break"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Break>();
TRY(builder.appendff("({})", that.value));
break;}
case 64 /* Catch */: {
TRY(builder.append("Token::Catch"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Catch>();
TRY(builder.appendff("({})", that.value));
break;}
case 65 /* Class */: {
TRY(builder.append("Token::Class"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Class>();
TRY(builder.appendff("({})", that.value));
break;}
case 66 /* Continue */: {
TRY(builder.append("Token::Continue"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Continue>();
TRY(builder.appendff("({})", that.value));
break;}
case 67 /* Cpp */: {
TRY(builder.append("Token::Cpp"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Cpp>();
TRY(builder.appendff("({})", that.value));
break;}
case 68 /* Defer */: {
TRY(builder.append("Token::Defer"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Defer>();
TRY(builder.appendff("({})", that.value));
break;}
case 69 /* Destructor */: {
TRY(builder.append("Token::Destructor"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Destructor>();
TRY(builder.appendff("({})", that.value));
break;}
case 70 /* Else */: {
TRY(builder.append("Token::Else"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Else>();
TRY(builder.appendff("({})", that.value));
break;}
case 71 /* Enum */: {
TRY(builder.append("Token::Enum"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Enum>();
TRY(builder.appendff("({})", that.value));
break;}
case 72 /* Extern */: {
TRY(builder.append("Token::Extern"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Extern>();
TRY(builder.appendff("({})", that.value));
break;}
case 73 /* False */: {
TRY(builder.append("Token::False"sv));
[[maybe_unused]] auto const& that = this->template get<Token::False>();
TRY(builder.appendff("({})", that.value));
break;}
case 74 /* For */: {
TRY(builder.append("Token::For"sv));
[[maybe_unused]] auto const& that = this->template get<Token::For>();
TRY(builder.appendff("({})", that.value));
break;}
case 75 /* Fn */: {
TRY(builder.append("Token::Fn"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Fn>();
TRY(builder.appendff("({})", that.value));
break;}
case 76 /* Comptime */: {
TRY(builder.append("Token::Comptime"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Comptime>();
TRY(builder.appendff("({})", that.value));
break;}
case 77 /* If */: {
TRY(builder.append("Token::If"sv));
[[maybe_unused]] auto const& that = this->template get<Token::If>();
TRY(builder.appendff("({})", that.value));
break;}
case 78 /* Import */: {
TRY(builder.append("Token::Import"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Import>();
TRY(builder.appendff("({})", that.value));
break;}
case 79 /* In */: {
TRY(builder.append("Token::In"sv));
[[maybe_unused]] auto const& that = this->template get<Token::In>();
TRY(builder.appendff("({})", that.value));
break;}
case 80 /* Is */: {
TRY(builder.append("Token::Is"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Is>();
TRY(builder.appendff("({})", that.value));
break;}
case 81 /* Let */: {
TRY(builder.append("Token::Let"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Let>();
TRY(builder.appendff("({})", that.value));
break;}
case 82 /* Loop */: {
TRY(builder.append("Token::Loop"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Loop>();
TRY(builder.appendff("({})", that.value));
break;}
case 83 /* Match */: {
TRY(builder.append("Token::Match"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Match>();
TRY(builder.appendff("({})", that.value));
break;}
case 84 /* Mut */: {
TRY(builder.append("Token::Mut"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Mut>();
TRY(builder.appendff("({})", that.value));
break;}
case 85 /* Namespace */: {
TRY(builder.append("Token::Namespace"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Namespace>();
TRY(builder.appendff("({})", that.value));
break;}
case 86 /* Not */: {
TRY(builder.append("Token::Not"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Not>();
TRY(builder.appendff("({})", that.value));
break;}
case 87 /* Or */: {
TRY(builder.append("Token::Or"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Or>();
TRY(builder.appendff("({})", that.value));
break;}
case 88 /* Override */: {
TRY(builder.append("Token::Override"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Override>();
TRY(builder.appendff("({})", that.value));
break;}
case 89 /* Private */: {
TRY(builder.append("Token::Private"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Private>();
TRY(builder.appendff("({})", that.value));
break;}
case 90 /* Public */: {
TRY(builder.append("Token::Public"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Public>();
TRY(builder.appendff("({})", that.value));
break;}
case 91 /* Raw */: {
TRY(builder.append("Token::Raw"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Raw>();
TRY(builder.appendff("({})", that.value));
break;}
case 92 /* Reflect */: {
TRY(builder.append("Token::Reflect"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Reflect>();
TRY(builder.appendff("({})", that.value));
break;}
case 93 /* Return */: {
TRY(builder.append("Token::Return"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Return>();
TRY(builder.appendff("({})", that.value));
break;}
case 94 /* Restricted */: {
TRY(builder.append("Token::Restricted"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Restricted>();
TRY(builder.appendff("({})", that.value));
break;}
case 95 /* Sizeof */: {
TRY(builder.append("Token::Sizeof"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Sizeof>();
TRY(builder.appendff("({})", that.value));
break;}
case 96 /* Struct */: {
TRY(builder.append("Token::Struct"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Struct>();
TRY(builder.appendff("({})", that.value));
break;}
case 97 /* This */: {
TRY(builder.append("Token::This"sv));
[[maybe_unused]] auto const& that = this->template get<Token::This>();
TRY(builder.appendff("({})", that.value));
break;}
case 98 /* Throw */: {
TRY(builder.append("Token::Throw"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Throw>();
TRY(builder.appendff("({})", that.value));
break;}
case 99 /* Throws */: {
TRY(builder.append("Token::Throws"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Throws>();
TRY(builder.appendff("({})", that.value));
break;}
case 100 /* True */: {
TRY(builder.append("Token::True"sv));
[[maybe_unused]] auto const& that = this->template get<Token::True>();
TRY(builder.appendff("({})", that.value));
break;}
case 101 /* Try */: {
TRY(builder.append("Token::Try"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Try>();
TRY(builder.appendff("({})", that.value));
break;}
case 102 /* Unsafe */: {
TRY(builder.append("Token::Unsafe"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Unsafe>();
TRY(builder.appendff("({})", that.value));
break;}
case 103 /* Virtual */: {
TRY(builder.append("Token::Virtual"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Virtual>();
TRY(builder.appendff("({})", that.value));
break;}
case 104 /* Weak */: {
TRY(builder.append("Token::Weak"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Weak>();
TRY(builder.appendff("({})", that.value));
break;}
case 105 /* While */: {
TRY(builder.append("Token::While"sv));
[[maybe_unused]] auto const& that = this->template get<Token::While>();
TRY(builder.appendff("({})", that.value));
break;}
case 106 /* Yield */: {
TRY(builder.append("Token::Yield"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Yield>();
TRY(builder.appendff("({})", that.value));
break;}
case 107 /* Guard */: {
TRY(builder.append("Token::Guard"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Guard>();
TRY(builder.appendff("({})", that.value));
break;}
case 108 /* Implements */: {
TRY(builder.append("Token::Implements"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Implements>();
TRY(builder.appendff("({})", that.value));
break;}
case 109 /* Requires */: {
TRY(builder.append("Token::Requires"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Requires>();
TRY(builder.appendff("({})", that.value));
break;}
case 110 /* Trait */: {
TRY(builder.append("Token::Trait"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Trait>();
TRY(builder.appendff("({})", that.value));
break;}
case 111 /* Garbage */: {
TRY(builder.append("Token::Garbage"sv));
[[maybe_unused]] auto const& that = this->template get<Token::Garbage>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("consumed: {}, ", that.consumed));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
ErrorOr<lexer::Token> lexer::Token::from_keyword_or_identifier(DeprecatedString const string,utility::Span const span) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,ErrorOr<lexer::Token>>{
auto __jakt_enum_value = (string);
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("and"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::And(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("anon"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Anon(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("as"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::As(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("boxed"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Boxed(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("break"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Break(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("catch"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Catch(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("class"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Class(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("continue"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Continue(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("cpp"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Cpp(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("defer"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Defer(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("destructor"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Destructor(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("else"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Else(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("enum"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Enum(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("extern"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Extern(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("false"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::False(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("for"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::For(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("fn"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Fn(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("comptime"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Comptime(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("if"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::If(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("import"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Import(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("in"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::In(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("is"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Is(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("let"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Let(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("loop"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Loop(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("match"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Match(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("mut"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Mut(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("namespace"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Namespace(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("not"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Not(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("or"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Or(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("override"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Override(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("private"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Private(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("public"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Public(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("raw"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Raw(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("reflect"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Reflect(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("return"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Return(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("restricted"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Restricted(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("sizeof"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Sizeof(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("struct"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Struct(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("this"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::This(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("throw"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Throw(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("throws"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Throws(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("true"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::True(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("try"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Try(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("unsafe"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Unsafe(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("virtual"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Virtual(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("weak"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Weak(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("while"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::While(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("yield"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Yield(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("guard"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Guard(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("requires"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Requires(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("implements"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Implements(span) } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("trait"sv))) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Trait(span) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Identifier(string,span) } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

utility::Span lexer::Token::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::SingleQuotedString>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::QuotedString>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Number>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Semicolon>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ColonColon>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSign>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Plus>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Minus>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusPlus>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusMinus>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AsteriskEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlashEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSignEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::NotEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DoubleEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThanOrEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThanOrEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftArithmeticShift>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShift>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShiftEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 33: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShift>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 34: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightArithmeticShift>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 35: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShiftEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 36: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Asterisk>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 37: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Ampersand>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 38: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 39: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandAmpersand>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 40: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipeEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 42: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipePipe>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 43: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Caret>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 44: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::CaretEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 45: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Dollar>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 46: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Tilde>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 47: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlash>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 48: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ExclamationPoint>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 49: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMark>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 50: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMark>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 51: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMarkEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 52: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Dot>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 54: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DotDot>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 55: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Eof>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 57: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Arrow>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 59: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::And>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 60: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Anon>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 61: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::As>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 62: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Boxed>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 63: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Break>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 64: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Catch>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 65: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Class>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 66: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Continue>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 67: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Cpp>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 68: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Defer>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 69: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Destructor>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 70: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Else>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 71: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Enum>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 72: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Extern>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 73: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::False>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 74: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::For>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 75: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Fn>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 76: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comptime>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 77: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::If>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 78: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Import>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 79: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::In>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 80: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Is>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 81: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Let>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 82: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Loop>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 83: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Match>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 84: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Mut>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 85: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Namespace>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 86: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Not>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 87: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Or>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 88: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Override>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 89: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Private>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 90: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Public>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 91: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Raw>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 92: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Reflect>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 93: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Return>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 94: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Restricted>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 95: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Sizeof>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 96: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Struct>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 97: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::This>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 98: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throw>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 99: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throws>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 100: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::True>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 101: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Try>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 102: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Unsafe>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Virtual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 104: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Weak>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 106: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Yield>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 107: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 108: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Implements>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 109: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Requires>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 110: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Trait>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 111: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Garbage>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
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

ErrorOr<DeprecatedString> lexer::LiteralPrefix::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* None */: {
return DeprecatedString("LiteralPrefix::None"sv);
break;}
case 1 /* Hexadecimal */: {
return DeprecatedString("LiteralPrefix::Hexadecimal"sv);
break;}
case 2 /* Octal */: {
return DeprecatedString("LiteralPrefix::Octal"sv);
break;}
case 3 /* Binary */: {
return DeprecatedString("LiteralPrefix::Binary"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> lexer::LiteralPrefix::to_string() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("0x"sv)));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("0o"sv)));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("0b"sv)));
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
