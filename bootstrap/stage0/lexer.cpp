#include "lexer.h"
namespace Jakt {
namespace lexer {
ErrorOr<String> lexer::Lexer::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Lexer("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("index: "));TRY(builder.appendff("{}, ", index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("input: "));TRY(builder.appendff("{}, ", input));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("compiler: "));TRY(builder.appendff("{}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("comment_contents: "));TRY(builder.appendff("{}", comment_contents));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<lexer::Token> lexer::Lexer::lex_quoted_string(u8 const delimiter) {
{
size_t const start = ((*this).index);
(++(((*this).index)));
if (((*this).eof())){
TRY((((*this).error(String("unexpected eof"),((*this).span(start,start))))));
return ( lexer::Token { typename lexer::Token::Garbage(JaktInternal::OptionalNone(),((*this).span(start,start))) } );
}
bool escaped = false;
while (((!(((*this).eof()))) && (escaped || (((*this).peek()) != delimiter)))){
if (((((*this).peek()) == '\r') || (((*this).peek()) == '\n'))){
(++(((*this).index)));
continue;
}
if (((!(escaped)) && (((*this).peek()) == '\\'))){
(escaped = true);
}
else {
(escaped = false);
}

(++(((*this).index)));
}
String const str = TRY((((*this).substring((JaktInternal::checked_add<size_t>(start,static_cast<size_t>(1ULL))),((*this).index)))));
((((*this).index)++));
size_t const end = ((*this).index);
if ((delimiter == '\'')){
return ( lexer::Token { typename lexer::Token::SingleQuotedString(str,((*this).span(start,end))) } );
}
return ( lexer::Token { typename lexer::Token::QuotedString(str,((*this).span(start,end))) } );
}
}

ErrorOr<JaktInternal::Optional<lexer::Token>> lexer::Lexer::next() {
{
for (;;){
if ((((*this).index) == ((((*this).input)).size()))){
(++(((*this).index)));
return ( lexer::Token { typename lexer::Token::Eof(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),(JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL)))))) } );
}
if (((*this).eof())){
return (JaktInternal::OptionalNone());
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
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<lexer::Token>,ErrorOr<JaktInternal::Optional<lexer::Token>>>{
auto __jakt_enum_value = (((((*this).input))[((*this).index)]));
if (__jakt_enum_value == '(') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LParen(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == ')') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RParen(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '[') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LSquare(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == ']') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RSquare(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '{') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LCurly(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '}') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RCurly(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '<') {
return JaktInternal::ExplicitValue(((*this).lex_less_than()));
}
else if (__jakt_enum_value == '>') {
return JaktInternal::ExplicitValue(((*this).lex_greater_than()));
}
else if (__jakt_enum_value == '.') {
return JaktInternal::ExplicitValue(((*this).lex_dot()));
}
else if (__jakt_enum_value == ',') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Comma(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '~') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Tilde(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == ';') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Semicolon(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == ':') {
return JaktInternal::ExplicitValue(((*this).lex_colon()));
}
else if (__jakt_enum_value == '?') {
return JaktInternal::ExplicitValue(((*this).lex_question_mark()));
}
else if (__jakt_enum_value == '+') {
return JaktInternal::ExplicitValue(((*this).lex_plus()));
}
else if (__jakt_enum_value == '-') {
return JaktInternal::ExplicitValue(((*this).lex_minus()));
}
else if (__jakt_enum_value == '*') {
return JaktInternal::ExplicitValue(((*this).lex_asterisk()));
}
else if (__jakt_enum_value == '/') {
return JaktInternal::ExplicitValue(TRY((((*this).lex_forward_slash()))));
}
else if (__jakt_enum_value == '^') {
return JaktInternal::ExplicitValue(((*this).lex_caret()));
}
else if (__jakt_enum_value == '|') {
return JaktInternal::ExplicitValue(((*this).lex_pipe()));
}
else if (__jakt_enum_value == '%') {
return JaktInternal::ExplicitValue(((*this).lex_percent_sign()));
}
else if (__jakt_enum_value == '!') {
return JaktInternal::ExplicitValue(((*this).lex_exclamation_point()));
}
else if (__jakt_enum_value == '&') {
return JaktInternal::ExplicitValue(((*this).lex_ampersand()));
}
else if (__jakt_enum_value == '$') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Dollar(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue(((*this).lex_equals()));
}
else if (__jakt_enum_value == '\n') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Eol(TRY((((*this).consume_comment_contents()))),((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '\'') {
return JaktInternal::ExplicitValue(TRY((((*this).lex_quoted_string('\'')))));
}
else if (__jakt_enum_value == '\"') {
return JaktInternal::ExplicitValue(TRY((((*this).lex_quoted_string('"')))));
}
else if (__jakt_enum_value == 'b') {
return JaktInternal::ExplicitValue(TRY((((*this).lex_character_constant_or_name()))));
}
else if (__jakt_enum_value == 'c') {
return JaktInternal::ExplicitValue(TRY((((*this).lex_character_constant_or_name()))));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).lex_number_or_name()))));
}
}()))
);
}
}

ErrorOr<JaktInternal::Optional<String>> lexer::Lexer::consume_comment_contents() {
{
if ((!(((((*this).comment_contents)).has_value())))){
return (JaktInternal::OptionalNone());
}
JaktInternal::Array<u8> const contents = (((*this).comment_contents).value());
(((*this).comment_contents) = JaktInternal::OptionalNone());
StringBuilder builder = TRY((StringBuilder::create()));
{
JaktInternal::ArrayIterator<u8> _magic = ((contents).iterator());
for (;;){
JaktInternal::Optional<u8> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u8 c = (_magic_value.value());
{
TRY((((builder).append(c))));
}

}
}

return (TRY((((builder).to_string()))));
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_character_constant_or_name() {
{
if ((((*this).peek_ahead(static_cast<size_t>(1ULL))) != '\'')){
return (TRY((((*this).lex_number_or_name()))));
}
bool const is_byte = (((*this).peek()) == 'b');
if (is_byte){
((((*this).index)++));
}
size_t const start = ((*this).index);
((((*this).index)++));
bool escaped = false;
while (((!(((*this).eof()))) && (escaped || (((*this).peek()) != '\'')))){
if ((escaped && ((JaktInternal::checked_sub<size_t>(((*this).index),start)) > static_cast<size_t>(3ULL)))){
break;
}
else if (((JaktInternal::checked_sub<size_t>(((*this).index),start)) > static_cast<size_t>(2ULL))){
break;
}
if (((!(escaped)) && (((*this).peek()) == '\\'))){
(escaped = true);
}
((((*this).index)++));
}
if ((((*this).eof()) || (((*this).peek()) != '\''))){
TRY((((*this).error(String("Expected single quote"),((*this).span(start,start))))));
}
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
StringBuilder builder = TRY((StringBuilder::create()));
TRY((((builder).append(((((*this).input))[(JaktInternal::checked_add<size_t>(start,static_cast<size_t>(1ULL)))])))));
if (escaped){
TRY((((builder).append(((((*this).input))[(JaktInternal::checked_add<size_t>(start,static_cast<size_t>(2ULL)))])))));
}
String const quote = TRY((((builder).to_string())));
size_t const end = ((*this).index);
if (is_byte){
return ( lexer::Token { typename lexer::Token::SingleQuotedByteString(quote,((*this).span(start,end))) } );
}
return ( lexer::Token { typename lexer::Token::SingleQuotedString(quote,((*this).span(start,end))) } );
}
}

lexer::Token lexer::Lexer::lex_dot() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '.') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::DotDot(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Dot(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_forward_slash() {
{
size_t const start = ((((*this).index)++));
if ((((*this).peek()) == '=')){
return ( lexer::Token { typename lexer::Token::ForwardSlashEqual(((*this).span(start,(++(((*this).index)))))) } );
}
if ((((*this).peek()) != '/')){
return ( lexer::Token { typename lexer::Token::ForwardSlash(((*this).span(start,((*this).index)))) } );
}
if (((((*this).comment_contents)).has_value())){
((((*this).index)--));
return ( lexer::Token { typename lexer::Token::Eol(TRY((((*this).consume_comment_contents()))),((*this).span(start,((*this).index)))) } );
}
((((*this).index)++));
size_t const comment_start_index = ((*this).index);
while ((!(((*this).eof())))){
u8 const c = ((*this).peek());
((((*this).index)++));
if ((c == '\n')){
((((*this).index)--));
break;
}
}
(((*this).comment_contents) = TRY((((((((*this).input))[(JaktInternal::Range<size_t>{static_cast<size_t>(comment_start_index),static_cast<size_t>(((*this).index))})])).to_array()))));
return (TRY((((*this).next()))).value_or_lazy_evaluated([&] { return  lexer::Token { typename lexer::Token::Eof(((*this).span(((*this).index),((*this).index)))) } ; }));
}
}

lexer::Token lexer::Lexer::lex_question_mark() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '?') {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_2; {
((((*this).index)++));
__jakt_var_2 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::QuestionMarkQuestionMarkEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::QuestionMarkQuestionMark(((*this).span(start,((*this).index)))) } );
}
}()))
; goto __jakt_label_0;

}
__jakt_label_0:; __jakt_var_2.release_value(); }));
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::QuestionMark(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

u8 lexer::Lexer::peek_behind(size_t const steps) const {
{
if ((((*this).index) < steps)){
return (static_cast<u8>(0));
}
return (((((*this).input))[(JaktInternal::checked_sub<size_t>(((*this).index),steps))]));
}
}

u8 lexer::Lexer::peek_ahead(size_t const steps) const {
{
if (((JaktInternal::checked_add<size_t>(((*this).index),steps)) >= ((((*this).input)).size()))){
return (static_cast<u8>(0));
}
return (((((*this).input))[(JaktInternal::checked_add<size_t>(((*this).index),steps))]));
}
}

lexer::Token lexer::Lexer::lex_asterisk() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::AsteriskEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Asterisk(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

u8 lexer::Lexer::peek() const {
{
if (((*this).eof())){
return (static_cast<u8>(0));
}
return (((((*this).input))[((*this).index)]));
}
}

lexer::Token lexer::Lexer::lex_percent_sign() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PercentSignEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PercentSign(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_number_or_name() {
{
size_t const start = ((*this).index);
if (((*this).eof())){
TRY((((*this).error(String("unexpected eof"),((*this).span(start,start))))));
return ( lexer::Token { typename lexer::Token::Garbage(JaktInternal::OptionalNone(),((*this).span(start,start))) } );
}
if (utility::is_ascii_digit(((*this).peek()))){
return (TRY((((*this).lex_number()))));
}
else if ((utility::is_ascii_alpha(((*this).peek())) || (((*this).peek()) == '_'))){
StringBuilder string_builder = TRY((StringBuilder::create()));
while ((utility::is_ascii_alphanumeric(((*this).peek())) || (((*this).peek()) == '_'))){
u8 const value = ((((*this).input))[((*this).index)]);
(++(((*this).index)));
TRY((((string_builder).append(value))));
}
size_t const end = ((*this).index);
utility::Span const span = ((*this).span(start,end));
String const string = TRY((((string_builder).to_string())));
if ((((JaktInternal::checked_sub<size_t>(end,start)) >= static_cast<size_t>(6ULL)) && (TRY((((string).substring(static_cast<size_t>(0ULL),static_cast<size_t>(6ULL))))) == String("__jakt")))){
TRY((((*this).error(String("reserved identifier name"),span))));
}
return (lexer::Token::from_keyword_or_identifier(string,span));
}
u8 const unknown_char = ((((*this).input))[((*this).index)]);
size_t const end = (++(((*this).index)));
TRY((((*this).error(TRY((String::formatted(String("unknown character: {:c}"),unknown_char))),((*this).span(start,end))))));
return ( lexer::Token { typename lexer::Token::Garbage(TRY((String::formatted(String("{:c}"),unknown_char))),((*this).span(start,end))) } );
}
}

lexer::Token lexer::Lexer::lex_minus() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::MinusEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '-') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::MinusMinus(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '>') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Arrow(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Minus(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

bool lexer::Lexer::eof() const {
{
return ((((*this).index) >= ((((*this).input)).size())));
}
}

lexer::Token lexer::Lexer::lex_ampersand() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::AmpersandEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '&') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::AmpersandAmpersand(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Ampersand(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

utility::Span lexer::Lexer::span(size_t const start,size_t const end) const {
{
return (utility::Span((((((*this).compiler))->current_file).value()),start,end));
}
}

lexer::Token lexer::Lexer::lex_plus() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PlusEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '+') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PlusPlus(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Plus(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

lexer::Token lexer::Lexer::lex_exclamation_point() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::NotEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::ExclamationPoint(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

ErrorOr<lexer::LiteralSuffix> lexer::Lexer::consume_numeric_literal_suffix() {
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == 'u') {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == 'i') {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == 'f') {
{
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
return ( lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } );
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
if (((((*this).peek()) == 'u') && (((*this).peek_ahead(static_cast<size_t>(1ULL))) == 'z'))){
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(2ULL));});
return ( lexer::LiteralSuffix { typename lexer::LiteralSuffix::UZ() } );
}
size_t local_index = static_cast<size_t>(1ULL);
i64 width = static_cast<i64>(0LL);
while (utility::is_ascii_digit(((*this).peek_ahead(local_index)))){
if ((local_index > static_cast<size_t>(3ULL))){
return ( lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } );
}
u8 const value = ((((*this).input))[(JaktInternal::checked_add<size_t>(((*this).index),local_index))]);
(++(local_index));
i64 const digit = as_saturated<i64, u8>((JaktInternal::checked_sub<u8>(value,'0')));
(width = (JaktInternal::checked_add<i64>((JaktInternal::checked_mul<i64>(width,static_cast<i64>(10LL))),digit)));
}
lexer::LiteralSuffix const suffix = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == 'u') {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
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
}()))
);
}
else if (__jakt_enum_value == 'i') {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
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
}()))
);
}
else if (__jakt_enum_value == 'f') {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
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
}()))
);
}
else {
return JaktInternal::ExplicitValue( lexer::LiteralSuffix { typename lexer::LiteralSuffix::None() } );
}
}()))
;
if ((!(((suffix).index() == 0 /* None */)))){
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, local_index);});
}
return (suffix);
}
}

lexer::Token lexer::Lexer::lex_colon() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == ':') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::ColonColon(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Colon(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

lexer::Lexer::Lexer(size_t a_index, JaktInternal::Array<u8> a_input, NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Optional<JaktInternal::Array<u8>> a_comment_contents) :index(a_index), input(a_input), compiler(a_compiler), comment_contents(a_comment_contents){}

bool lexer::Lexer::valid_digit(lexer::LiteralPrefix const prefix,u8 const digit,bool const decimal_allowed) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = prefix;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralPrefix::Hexadecimal>();
return JaktInternal::ExplicitValue(utility::is_ascii_hexdigit(digit));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralPrefix::Octal>();
return JaktInternal::ExplicitValue(utility::is_ascii_octdigit(digit));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralPrefix::Binary>();
return JaktInternal::ExplicitValue(utility::is_ascii_binary(digit));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((utility::is_ascii_digit(digit) || (decimal_allowed && (digit == '.'))));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<void> lexer::Lexer::error(String const message,utility::Span const span) {
{
TRY((((((((*this).compiler))->errors)).push( error::JaktError { typename error::JaktError::Message(message,span) } ))));
}
return {};
}

ErrorOr<String> lexer::Lexer::substring(size_t const start,size_t const length) const {
{
StringBuilder builder = TRY((StringBuilder::create()));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(start),static_cast<size_t>(length)});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((builder).append(((((*this).input))[i])))));
}

}
}

return (TRY((((builder).to_string()))));
}
}

lexer::Token lexer::Lexer::lex_greater_than() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::GreaterThanOrEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '>') {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_3; {
((((*this).index)++));
__jakt_var_3 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '>') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RightArithmeticShift(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RightShiftEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::RightShift(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
; goto __jakt_label_1;

}
__jakt_label_1:; __jakt_var_3.release_value(); }));
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::GreaterThan(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

lexer::Token lexer::Lexer::lex_pipe() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PipeEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '|') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::PipePipe(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Pipe(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

lexer::Token lexer::Lexer::lex_caret() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::CaretEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Caret(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_number() {
{
size_t const start = ((*this).index);
bool floating = false;
lexer::LiteralPrefix prefix =  lexer::LiteralPrefix { typename lexer::LiteralPrefix::None() } ;
StringBuilder number = TRY((StringBuilder::create()));
if ((((*this).peek()) == '0')){
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<lexer::Token>>{
auto __jakt_enum_value = (((*this).peek_ahead(static_cast<size_t>(1ULL))));
if (__jakt_enum_value == 'x') {
{
(prefix =  lexer::LiteralPrefix { typename lexer::LiteralPrefix::Hexadecimal() } );
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(2ULL));});
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == 'o') {
{
(prefix =  lexer::LiteralPrefix { typename lexer::LiteralPrefix::Octal() } );
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(2ULL));});
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == 'b') {
{
(prefix =  lexer::LiteralPrefix { typename lexer::LiteralPrefix::Binary() } );
({auto& _jakt_ref = ((*this).index);_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(2ULL));});
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
}
while ((!(((*this).eof())))){
u8 const value = ((((*this).input))[((*this).index)]);
if ((!(((*this).valid_digit(prefix,value,true))))){
break;
}
if ((value == '.')){
if ((floating || (!(((*this).valid_digit(prefix,((*this).peek_ahead(static_cast<size_t>(1ULL))),false)))))){
break;
}
TRY((((number).append('.'))));
(floating = true);
((((*this).index)++));
continue;
}
TRY((((number).append(value))));
(++(((*this).index)));
if ((((*this).peek()) == '_')){
TRY((((number).append('_'))));
if (((*this).valid_digit(prefix,((*this).peek_ahead(static_cast<size_t>(1ULL))),true))){
(++(((*this).index)));
}
else {
break;
}

}
}
lexer::LiteralSuffix const suffix = TRY((((*this).consume_numeric_literal_suffix())));
return ( lexer::Token { typename lexer::Token::Number(prefix,TRY((((number).to_string()))),suffix,((*this).span(start,((*this).index)))) } );
}
}

lexer::Token lexer::Lexer::lex_less_than() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LessThanOrEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '<') {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_4; {
((((*this).index)++));
__jakt_var_4 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '<') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LeftArithmeticShift(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LeftShiftEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LeftShift(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
; goto __jakt_label_2;

}
__jakt_label_2:; __jakt_var_4.release_value(); }));
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::LessThan(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

lexer::Token lexer::Lexer::lex_equals() {
{
size_t const start = ((((*this).index)++));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == '=') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::DoubleEqual(((*this).span(start,(++(((*this).index)))))) } );
}
else if (__jakt_enum_value == '>') {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::FatArrow(((*this).span(start,(++(((*this).index)))))) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Equal(((*this).span((JaktInternal::checked_sub<size_t>(((*this).index),static_cast<size_t>(1ULL))),((*this).index)))) } );
}
}()))
);
}
}

ErrorOr<JaktInternal::Array<lexer::Token>> lexer::Lexer::lex(NonnullRefPtr<compiler::Compiler> const compiler) {
{
lexer::Lexer lexer = lexer::Lexer(static_cast<size_t>(0ULL),((compiler)->current_file_contents),compiler,JaktInternal::OptionalNone());
JaktInternal::Array<lexer::Token> tokens = (TRY((Array<lexer::Token>::create_with({}))));
{
lexer::Lexer _magic = lexer;
for (;;){
JaktInternal::Optional<lexer::Token> _magic_value = TRY((((_magic).next())));
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
TRY((((tokens).push(token))));
}

}
}

return (tokens);
}
}

ErrorOr<String> lexer::LiteralSuffix::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* None */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::None>();
TRY(builder.append("LiteralSuffix::None"));
break;}
case 1 /* UZ */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::UZ>();
TRY(builder.append("LiteralSuffix::UZ"));
break;}
case 2 /* U8 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::U8>();
TRY(builder.append("LiteralSuffix::U8"));
break;}
case 3 /* U16 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::U16>();
TRY(builder.append("LiteralSuffix::U16"));
break;}
case 4 /* U32 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::U32>();
TRY(builder.append("LiteralSuffix::U32"));
break;}
case 5 /* U64 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::U64>();
TRY(builder.append("LiteralSuffix::U64"));
break;}
case 6 /* I8 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::I8>();
TRY(builder.append("LiteralSuffix::I8"));
break;}
case 7 /* I16 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::I16>();
TRY(builder.append("LiteralSuffix::I16"));
break;}
case 8 /* I32 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::I32>();
TRY(builder.append("LiteralSuffix::I32"));
break;}
case 9 /* I64 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::I64>();
TRY(builder.append("LiteralSuffix::I64"));
break;}
case 10 /* F32 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::F32>();
TRY(builder.append("LiteralSuffix::F32"));
break;}
case 11 /* F64 */: {
[[maybe_unused]] auto const& that = this->template get<LiteralSuffix::F64>();
TRY(builder.append("LiteralSuffix::F64"));
break;}
}
return builder.to_string();
}
String lexer::LiteralSuffix::to_string() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, String>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::None>();
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::UZ>();
return JaktInternal::ExplicitValue(String("uz"));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::U8>();
return JaktInternal::ExplicitValue(String("u8"));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::U16>();
return JaktInternal::ExplicitValue(String("u16"));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::U32>();
return JaktInternal::ExplicitValue(String("u32"));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::U64>();
return JaktInternal::ExplicitValue(String("u64"));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::I8>();
return JaktInternal::ExplicitValue(String("i8"));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::I16>();
return JaktInternal::ExplicitValue(String("i16"));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::I32>();
return JaktInternal::ExplicitValue(String("i32"));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::I64>();
return JaktInternal::ExplicitValue(String("i64"));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::F32>();
return JaktInternal::ExplicitValue(String("f32"));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralSuffix::F64>();
return JaktInternal::ExplicitValue(String("f64"));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> lexer::Token::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* SingleQuotedString */: {
[[maybe_unused]] auto const& that = this->template get<Token::SingleQuotedString>();
TRY(builder.append("Token::SingleQuotedString"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("quote: \"{}\"", that.quote));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"));
break;}
case 1 /* SingleQuotedByteString */: {
[[maybe_unused]] auto const& that = this->template get<Token::SingleQuotedByteString>();
TRY(builder.append("Token::SingleQuotedByteString"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("quote: \"{}\"", that.quote));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"));
break;}
case 2 /* QuotedString */: {
[[maybe_unused]] auto const& that = this->template get<Token::QuotedString>();
TRY(builder.append("Token::QuotedString"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("quote: \"{}\"", that.quote));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"));
break;}
case 3 /* Number */: {
[[maybe_unused]] auto const& that = this->template get<Token::Number>();
TRY(builder.append("Token::Number"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("prefix: {}", that.prefix));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("number: \"{}\"", that.number));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("suffix: {}", that.suffix));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"));
break;}
case 4 /* Identifier */: {
[[maybe_unused]] auto const& that = this->template get<Token::Identifier>();
TRY(builder.append("Token::Identifier"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\"", that.name));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"));
break;}
case 5 /* Semicolon */: {
[[maybe_unused]] auto const& that = this->template get<Token::Semicolon>();
TRY(builder.append("Token::Semicolon"));
TRY(builder.appendff("({})", that.value));
break;}
case 6 /* Colon */: {
[[maybe_unused]] auto const& that = this->template get<Token::Colon>();
TRY(builder.append("Token::Colon"));
TRY(builder.appendff("({})", that.value));
break;}
case 7 /* ColonColon */: {
[[maybe_unused]] auto const& that = this->template get<Token::ColonColon>();
TRY(builder.append("Token::ColonColon"));
TRY(builder.appendff("({})", that.value));
break;}
case 8 /* LParen */: {
[[maybe_unused]] auto const& that = this->template get<Token::LParen>();
TRY(builder.append("Token::LParen"));
TRY(builder.appendff("({})", that.value));
break;}
case 9 /* RParen */: {
[[maybe_unused]] auto const& that = this->template get<Token::RParen>();
TRY(builder.append("Token::RParen"));
TRY(builder.appendff("({})", that.value));
break;}
case 10 /* LCurly */: {
[[maybe_unused]] auto const& that = this->template get<Token::LCurly>();
TRY(builder.append("Token::LCurly"));
TRY(builder.appendff("({})", that.value));
break;}
case 11 /* RCurly */: {
[[maybe_unused]] auto const& that = this->template get<Token::RCurly>();
TRY(builder.append("Token::RCurly"));
TRY(builder.appendff("({})", that.value));
break;}
case 12 /* LSquare */: {
[[maybe_unused]] auto const& that = this->template get<Token::LSquare>();
TRY(builder.append("Token::LSquare"));
TRY(builder.appendff("({})", that.value));
break;}
case 13 /* RSquare */: {
[[maybe_unused]] auto const& that = this->template get<Token::RSquare>();
TRY(builder.append("Token::RSquare"));
TRY(builder.appendff("({})", that.value));
break;}
case 14 /* PercentSign */: {
[[maybe_unused]] auto const& that = this->template get<Token::PercentSign>();
TRY(builder.append("Token::PercentSign"));
TRY(builder.appendff("({})", that.value));
break;}
case 15 /* Plus */: {
[[maybe_unused]] auto const& that = this->template get<Token::Plus>();
TRY(builder.append("Token::Plus"));
TRY(builder.appendff("({})", that.value));
break;}
case 16 /* Minus */: {
[[maybe_unused]] auto const& that = this->template get<Token::Minus>();
TRY(builder.append("Token::Minus"));
TRY(builder.appendff("({})", that.value));
break;}
case 17 /* Equal */: {
[[maybe_unused]] auto const& that = this->template get<Token::Equal>();
TRY(builder.append("Token::Equal"));
TRY(builder.appendff("({})", that.value));
break;}
case 18 /* PlusEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::PlusEqual>();
TRY(builder.append("Token::PlusEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 19 /* PlusPlus */: {
[[maybe_unused]] auto const& that = this->template get<Token::PlusPlus>();
TRY(builder.append("Token::PlusPlus"));
TRY(builder.appendff("({})", that.value));
break;}
case 20 /* MinusEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::MinusEqual>();
TRY(builder.append("Token::MinusEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 21 /* MinusMinus */: {
[[maybe_unused]] auto const& that = this->template get<Token::MinusMinus>();
TRY(builder.append("Token::MinusMinus"));
TRY(builder.appendff("({})", that.value));
break;}
case 22 /* AsteriskEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::AsteriskEqual>();
TRY(builder.append("Token::AsteriskEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 23 /* ForwardSlashEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::ForwardSlashEqual>();
TRY(builder.append("Token::ForwardSlashEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 24 /* PercentSignEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::PercentSignEqual>();
TRY(builder.append("Token::PercentSignEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 25 /* NotEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::NotEqual>();
TRY(builder.append("Token::NotEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 26 /* DoubleEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::DoubleEqual>();
TRY(builder.append("Token::DoubleEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 27 /* GreaterThan */: {
[[maybe_unused]] auto const& that = this->template get<Token::GreaterThan>();
TRY(builder.append("Token::GreaterThan"));
TRY(builder.appendff("({})", that.value));
break;}
case 28 /* GreaterThanOrEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::GreaterThanOrEqual>();
TRY(builder.append("Token::GreaterThanOrEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 29 /* LessThan */: {
[[maybe_unused]] auto const& that = this->template get<Token::LessThan>();
TRY(builder.append("Token::LessThan"));
TRY(builder.appendff("({})", that.value));
break;}
case 30 /* LessThanOrEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::LessThanOrEqual>();
TRY(builder.append("Token::LessThanOrEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 31 /* LeftArithmeticShift */: {
[[maybe_unused]] auto const& that = this->template get<Token::LeftArithmeticShift>();
TRY(builder.append("Token::LeftArithmeticShift"));
TRY(builder.appendff("({})", that.value));
break;}
case 32 /* LeftShift */: {
[[maybe_unused]] auto const& that = this->template get<Token::LeftShift>();
TRY(builder.append("Token::LeftShift"));
TRY(builder.appendff("({})", that.value));
break;}
case 33 /* LeftShiftEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::LeftShiftEqual>();
TRY(builder.append("Token::LeftShiftEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 34 /* RightShift */: {
[[maybe_unused]] auto const& that = this->template get<Token::RightShift>();
TRY(builder.append("Token::RightShift"));
TRY(builder.appendff("({})", that.value));
break;}
case 35 /* RightArithmeticShift */: {
[[maybe_unused]] auto const& that = this->template get<Token::RightArithmeticShift>();
TRY(builder.append("Token::RightArithmeticShift"));
TRY(builder.appendff("({})", that.value));
break;}
case 36 /* RightShiftEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::RightShiftEqual>();
TRY(builder.append("Token::RightShiftEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 37 /* Asterisk */: {
[[maybe_unused]] auto const& that = this->template get<Token::Asterisk>();
TRY(builder.append("Token::Asterisk"));
TRY(builder.appendff("({})", that.value));
break;}
case 38 /* Ampersand */: {
[[maybe_unused]] auto const& that = this->template get<Token::Ampersand>();
TRY(builder.append("Token::Ampersand"));
TRY(builder.appendff("({})", that.value));
break;}
case 39 /* AmpersandEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::AmpersandEqual>();
TRY(builder.append("Token::AmpersandEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 40 /* AmpersandAmpersand */: {
[[maybe_unused]] auto const& that = this->template get<Token::AmpersandAmpersand>();
TRY(builder.append("Token::AmpersandAmpersand"));
TRY(builder.appendff("({})", that.value));
break;}
case 41 /* Pipe */: {
[[maybe_unused]] auto const& that = this->template get<Token::Pipe>();
TRY(builder.append("Token::Pipe"));
TRY(builder.appendff("({})", that.value));
break;}
case 42 /* PipeEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::PipeEqual>();
TRY(builder.append("Token::PipeEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 43 /* PipePipe */: {
[[maybe_unused]] auto const& that = this->template get<Token::PipePipe>();
TRY(builder.append("Token::PipePipe"));
TRY(builder.appendff("({})", that.value));
break;}
case 44 /* Caret */: {
[[maybe_unused]] auto const& that = this->template get<Token::Caret>();
TRY(builder.append("Token::Caret"));
TRY(builder.appendff("({})", that.value));
break;}
case 45 /* CaretEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::CaretEqual>();
TRY(builder.append("Token::CaretEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 46 /* Dollar */: {
[[maybe_unused]] auto const& that = this->template get<Token::Dollar>();
TRY(builder.append("Token::Dollar"));
TRY(builder.appendff("({})", that.value));
break;}
case 47 /* Tilde */: {
[[maybe_unused]] auto const& that = this->template get<Token::Tilde>();
TRY(builder.append("Token::Tilde"));
TRY(builder.appendff("({})", that.value));
break;}
case 48 /* ForwardSlash */: {
[[maybe_unused]] auto const& that = this->template get<Token::ForwardSlash>();
TRY(builder.append("Token::ForwardSlash"));
TRY(builder.appendff("({})", that.value));
break;}
case 49 /* ExclamationPoint */: {
[[maybe_unused]] auto const& that = this->template get<Token::ExclamationPoint>();
TRY(builder.append("Token::ExclamationPoint"));
TRY(builder.appendff("({})", that.value));
break;}
case 50 /* QuestionMark */: {
[[maybe_unused]] auto const& that = this->template get<Token::QuestionMark>();
TRY(builder.append("Token::QuestionMark"));
TRY(builder.appendff("({})", that.value));
break;}
case 51 /* QuestionMarkQuestionMark */: {
[[maybe_unused]] auto const& that = this->template get<Token::QuestionMarkQuestionMark>();
TRY(builder.append("Token::QuestionMarkQuestionMark"));
TRY(builder.appendff("({})", that.value));
break;}
case 52 /* QuestionMarkQuestionMarkEqual */: {
[[maybe_unused]] auto const& that = this->template get<Token::QuestionMarkQuestionMarkEqual>();
TRY(builder.append("Token::QuestionMarkQuestionMarkEqual"));
TRY(builder.appendff("({})", that.value));
break;}
case 53 /* Comma */: {
[[maybe_unused]] auto const& that = this->template get<Token::Comma>();
TRY(builder.append("Token::Comma"));
TRY(builder.appendff("({})", that.value));
break;}
case 54 /* Dot */: {
[[maybe_unused]] auto const& that = this->template get<Token::Dot>();
TRY(builder.append("Token::Dot"));
TRY(builder.appendff("({})", that.value));
break;}
case 55 /* DotDot */: {
[[maybe_unused]] auto const& that = this->template get<Token::DotDot>();
TRY(builder.append("Token::DotDot"));
TRY(builder.appendff("({})", that.value));
break;}
case 56 /* Eol */: {
[[maybe_unused]] auto const& that = this->template get<Token::Eol>();
TRY(builder.append("Token::Eol"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("comment: {}", that.comment));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"));
break;}
case 57 /* Eof */: {
[[maybe_unused]] auto const& that = this->template get<Token::Eof>();
TRY(builder.append("Token::Eof"));
TRY(builder.appendff("({})", that.value));
break;}
case 58 /* FatArrow */: {
[[maybe_unused]] auto const& that = this->template get<Token::FatArrow>();
TRY(builder.append("Token::FatArrow"));
TRY(builder.appendff("({})", that.value));
break;}
case 59 /* Arrow */: {
[[maybe_unused]] auto const& that = this->template get<Token::Arrow>();
TRY(builder.append("Token::Arrow"));
TRY(builder.appendff("({})", that.value));
break;}
case 60 /* And */: {
[[maybe_unused]] auto const& that = this->template get<Token::And>();
TRY(builder.append("Token::And"));
TRY(builder.appendff("({})", that.value));
break;}
case 61 /* Anon */: {
[[maybe_unused]] auto const& that = this->template get<Token::Anon>();
TRY(builder.append("Token::Anon"));
TRY(builder.appendff("({})", that.value));
break;}
case 62 /* As */: {
[[maybe_unused]] auto const& that = this->template get<Token::As>();
TRY(builder.append("Token::As"));
TRY(builder.appendff("({})", that.value));
break;}
case 63 /* Boxed */: {
[[maybe_unused]] auto const& that = this->template get<Token::Boxed>();
TRY(builder.append("Token::Boxed"));
TRY(builder.appendff("({})", that.value));
break;}
case 64 /* Break */: {
[[maybe_unused]] auto const& that = this->template get<Token::Break>();
TRY(builder.append("Token::Break"));
TRY(builder.appendff("({})", that.value));
break;}
case 65 /* Catch */: {
[[maybe_unused]] auto const& that = this->template get<Token::Catch>();
TRY(builder.append("Token::Catch"));
TRY(builder.appendff("({})", that.value));
break;}
case 66 /* Class */: {
[[maybe_unused]] auto const& that = this->template get<Token::Class>();
TRY(builder.append("Token::Class"));
TRY(builder.appendff("({})", that.value));
break;}
case 67 /* Continue */: {
[[maybe_unused]] auto const& that = this->template get<Token::Continue>();
TRY(builder.append("Token::Continue"));
TRY(builder.appendff("({})", that.value));
break;}
case 68 /* Cpp */: {
[[maybe_unused]] auto const& that = this->template get<Token::Cpp>();
TRY(builder.append("Token::Cpp"));
TRY(builder.appendff("({})", that.value));
break;}
case 69 /* Defer */: {
[[maybe_unused]] auto const& that = this->template get<Token::Defer>();
TRY(builder.append("Token::Defer"));
TRY(builder.appendff("({})", that.value));
break;}
case 70 /* Else */: {
[[maybe_unused]] auto const& that = this->template get<Token::Else>();
TRY(builder.append("Token::Else"));
TRY(builder.appendff("({})", that.value));
break;}
case 71 /* Enum */: {
[[maybe_unused]] auto const& that = this->template get<Token::Enum>();
TRY(builder.append("Token::Enum"));
TRY(builder.appendff("({})", that.value));
break;}
case 72 /* Extern */: {
[[maybe_unused]] auto const& that = this->template get<Token::Extern>();
TRY(builder.append("Token::Extern"));
TRY(builder.appendff("({})", that.value));
break;}
case 73 /* False */: {
[[maybe_unused]] auto const& that = this->template get<Token::False>();
TRY(builder.append("Token::False"));
TRY(builder.appendff("({})", that.value));
break;}
case 74 /* For */: {
[[maybe_unused]] auto const& that = this->template get<Token::For>();
TRY(builder.append("Token::For"));
TRY(builder.appendff("({})", that.value));
break;}
case 75 /* Function */: {
[[maybe_unused]] auto const& that = this->template get<Token::Function>();
TRY(builder.append("Token::Function"));
TRY(builder.appendff("({})", that.value));
break;}
case 76 /* Comptime */: {
[[maybe_unused]] auto const& that = this->template get<Token::Comptime>();
TRY(builder.append("Token::Comptime"));
TRY(builder.appendff("({})", that.value));
break;}
case 77 /* If */: {
[[maybe_unused]] auto const& that = this->template get<Token::If>();
TRY(builder.append("Token::If"));
TRY(builder.appendff("({})", that.value));
break;}
case 78 /* Import */: {
[[maybe_unused]] auto const& that = this->template get<Token::Import>();
TRY(builder.append("Token::Import"));
TRY(builder.appendff("({})", that.value));
break;}
case 79 /* In */: {
[[maybe_unused]] auto const& that = this->template get<Token::In>();
TRY(builder.append("Token::In"));
TRY(builder.appendff("({})", that.value));
break;}
case 80 /* Is */: {
[[maybe_unused]] auto const& that = this->template get<Token::Is>();
TRY(builder.append("Token::Is"));
TRY(builder.appendff("({})", that.value));
break;}
case 81 /* Let */: {
[[maybe_unused]] auto const& that = this->template get<Token::Let>();
TRY(builder.append("Token::Let"));
TRY(builder.appendff("({})", that.value));
break;}
case 82 /* Loop */: {
[[maybe_unused]] auto const& that = this->template get<Token::Loop>();
TRY(builder.append("Token::Loop"));
TRY(builder.appendff("({})", that.value));
break;}
case 83 /* Match */: {
[[maybe_unused]] auto const& that = this->template get<Token::Match>();
TRY(builder.append("Token::Match"));
TRY(builder.appendff("({})", that.value));
break;}
case 84 /* Mut */: {
[[maybe_unused]] auto const& that = this->template get<Token::Mut>();
TRY(builder.append("Token::Mut"));
TRY(builder.appendff("({})", that.value));
break;}
case 85 /* Namespace */: {
[[maybe_unused]] auto const& that = this->template get<Token::Namespace>();
TRY(builder.append("Token::Namespace"));
TRY(builder.appendff("({})", that.value));
break;}
case 86 /* Not */: {
[[maybe_unused]] auto const& that = this->template get<Token::Not>();
TRY(builder.append("Token::Not"));
TRY(builder.appendff("({})", that.value));
break;}
case 87 /* Or */: {
[[maybe_unused]] auto const& that = this->template get<Token::Or>();
TRY(builder.append("Token::Or"));
TRY(builder.appendff("({})", that.value));
break;}
case 88 /* Override */: {
[[maybe_unused]] auto const& that = this->template get<Token::Override>();
TRY(builder.append("Token::Override"));
TRY(builder.appendff("({})", that.value));
break;}
case 89 /* Private */: {
[[maybe_unused]] auto const& that = this->template get<Token::Private>();
TRY(builder.append("Token::Private"));
TRY(builder.appendff("({})", that.value));
break;}
case 90 /* Public */: {
[[maybe_unused]] auto const& that = this->template get<Token::Public>();
TRY(builder.append("Token::Public"));
TRY(builder.appendff("({})", that.value));
break;}
case 91 /* Raw */: {
[[maybe_unused]] auto const& that = this->template get<Token::Raw>();
TRY(builder.append("Token::Raw"));
TRY(builder.appendff("({})", that.value));
break;}
case 92 /* Return */: {
[[maybe_unused]] auto const& that = this->template get<Token::Return>();
TRY(builder.append("Token::Return"));
TRY(builder.appendff("({})", that.value));
break;}
case 93 /* Restricted */: {
[[maybe_unused]] auto const& that = this->template get<Token::Restricted>();
TRY(builder.append("Token::Restricted"));
TRY(builder.appendff("({})", that.value));
break;}
case 94 /* Struct */: {
[[maybe_unused]] auto const& that = this->template get<Token::Struct>();
TRY(builder.append("Token::Struct"));
TRY(builder.appendff("({})", that.value));
break;}
case 95 /* This */: {
[[maybe_unused]] auto const& that = this->template get<Token::This>();
TRY(builder.append("Token::This"));
TRY(builder.appendff("({})", that.value));
break;}
case 96 /* Throw */: {
[[maybe_unused]] auto const& that = this->template get<Token::Throw>();
TRY(builder.append("Token::Throw"));
TRY(builder.appendff("({})", that.value));
break;}
case 97 /* Throws */: {
[[maybe_unused]] auto const& that = this->template get<Token::Throws>();
TRY(builder.append("Token::Throws"));
TRY(builder.appendff("({})", that.value));
break;}
case 98 /* True */: {
[[maybe_unused]] auto const& that = this->template get<Token::True>();
TRY(builder.append("Token::True"));
TRY(builder.appendff("({})", that.value));
break;}
case 99 /* Try */: {
[[maybe_unused]] auto const& that = this->template get<Token::Try>();
TRY(builder.append("Token::Try"));
TRY(builder.appendff("({})", that.value));
break;}
case 100 /* Unsafe */: {
[[maybe_unused]] auto const& that = this->template get<Token::Unsafe>();
TRY(builder.append("Token::Unsafe"));
TRY(builder.appendff("({})", that.value));
break;}
case 101 /* Virtual */: {
[[maybe_unused]] auto const& that = this->template get<Token::Virtual>();
TRY(builder.append("Token::Virtual"));
TRY(builder.appendff("({})", that.value));
break;}
case 102 /* Weak */: {
[[maybe_unused]] auto const& that = this->template get<Token::Weak>();
TRY(builder.append("Token::Weak"));
TRY(builder.appendff("({})", that.value));
break;}
case 103 /* While */: {
[[maybe_unused]] auto const& that = this->template get<Token::While>();
TRY(builder.append("Token::While"));
TRY(builder.appendff("({})", that.value));
break;}
case 104 /* Yield */: {
[[maybe_unused]] auto const& that = this->template get<Token::Yield>();
TRY(builder.append("Token::Yield"));
TRY(builder.appendff("({})", that.value));
break;}
case 105 /* Guard */: {
[[maybe_unused]] auto const& that = this->template get<Token::Guard>();
TRY(builder.append("Token::Guard"));
TRY(builder.appendff("({})", that.value));
break;}
case 106 /* Implements */: {
[[maybe_unused]] auto const& that = this->template get<Token::Implements>();
TRY(builder.append("Token::Implements"));
TRY(builder.appendff("({})", that.value));
break;}
case 107 /* Requires */: {
[[maybe_unused]] auto const& that = this->template get<Token::Requires>();
TRY(builder.append("Token::Requires"));
TRY(builder.appendff("({})", that.value));
break;}
case 108 /* Trait */: {
[[maybe_unused]] auto const& that = this->template get<Token::Trait>();
TRY(builder.append("Token::Trait"));
TRY(builder.appendff("({})", that.value));
break;}
case 109 /* Garbage */: {
[[maybe_unused]] auto const& that = this->template get<Token::Garbage>();
TRY(builder.append("Token::Garbage"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("consumed: {}", that.consumed));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"));
break;}
}
return builder.to_string();
}
lexer::Token lexer::Token::from_keyword_or_identifier(String const string,utility::Span const span) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (string);
if (__jakt_enum_value == String("and")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::And(span) } );
}
else if (__jakt_enum_value == String("anon")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Anon(span) } );
}
else if (__jakt_enum_value == String("as")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::As(span) } );
}
else if (__jakt_enum_value == String("boxed")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Boxed(span) } );
}
else if (__jakt_enum_value == String("break")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Break(span) } );
}
else if (__jakt_enum_value == String("catch")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Catch(span) } );
}
else if (__jakt_enum_value == String("class")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Class(span) } );
}
else if (__jakt_enum_value == String("continue")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Continue(span) } );
}
else if (__jakt_enum_value == String("cpp")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Cpp(span) } );
}
else if (__jakt_enum_value == String("defer")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Defer(span) } );
}
else if (__jakt_enum_value == String("else")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Else(span) } );
}
else if (__jakt_enum_value == String("enum")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Enum(span) } );
}
else if (__jakt_enum_value == String("extern")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Extern(span) } );
}
else if (__jakt_enum_value == String("false")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::False(span) } );
}
else if (__jakt_enum_value == String("for")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::For(span) } );
}
else if (__jakt_enum_value == String("function")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Function(span) } );
}
else if (__jakt_enum_value == String("comptime")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Comptime(span) } );
}
else if (__jakt_enum_value == String("if")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::If(span) } );
}
else if (__jakt_enum_value == String("import")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Import(span) } );
}
else if (__jakt_enum_value == String("in")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::In(span) } );
}
else if (__jakt_enum_value == String("is")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Is(span) } );
}
else if (__jakt_enum_value == String("let")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Let(span) } );
}
else if (__jakt_enum_value == String("loop")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Loop(span) } );
}
else if (__jakt_enum_value == String("match")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Match(span) } );
}
else if (__jakt_enum_value == String("mut")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Mut(span) } );
}
else if (__jakt_enum_value == String("namespace")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Namespace(span) } );
}
else if (__jakt_enum_value == String("not")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Not(span) } );
}
else if (__jakt_enum_value == String("or")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Or(span) } );
}
else if (__jakt_enum_value == String("override")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Override(span) } );
}
else if (__jakt_enum_value == String("private")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Private(span) } );
}
else if (__jakt_enum_value == String("public")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Public(span) } );
}
else if (__jakt_enum_value == String("raw")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Raw(span) } );
}
else if (__jakt_enum_value == String("return")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Return(span) } );
}
else if (__jakt_enum_value == String("restricted")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Restricted(span) } );
}
else if (__jakt_enum_value == String("struct")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Struct(span) } );
}
else if (__jakt_enum_value == String("this")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::This(span) } );
}
else if (__jakt_enum_value == String("throw")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Throw(span) } );
}
else if (__jakt_enum_value == String("throws")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Throws(span) } );
}
else if (__jakt_enum_value == String("true")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::True(span) } );
}
else if (__jakt_enum_value == String("try")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Try(span) } );
}
else if (__jakt_enum_value == String("unsafe")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Unsafe(span) } );
}
else if (__jakt_enum_value == String("virtual")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Virtual(span) } );
}
else if (__jakt_enum_value == String("weak")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Weak(span) } );
}
else if (__jakt_enum_value == String("while")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::While(span) } );
}
else if (__jakt_enum_value == String("yield")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Yield(span) } );
}
else if (__jakt_enum_value == String("guard")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Guard(span) } );
}
else if (__jakt_enum_value == String("requires")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Requires(span) } );
}
else if (__jakt_enum_value == String("implements")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Implements(span) } );
}
else if (__jakt_enum_value == String("trait")) {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Trait(span) } );
}
else {
return JaktInternal::ExplicitValue( lexer::Token { typename lexer::Token::Identifier(string,span) } );
}
}()))
);
}
}

utility::Span lexer::Token::span() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::SingleQuotedString>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::SingleQuotedByteString>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::QuotedString>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Number>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Identifier>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Semicolon>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Colon>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ColonColon>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LParen>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RParen>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LCurly>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RCurly>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LSquare>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RSquare>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSign>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Plus>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Minus>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Equal>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PlusPlus>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::MinusMinus>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AsteriskEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlashEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PercentSignEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::NotEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DoubleEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThan>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::GreaterThanOrEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThan>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LessThanOrEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftArithmeticShift>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShift>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 33: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::LeftShiftEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 34: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShift>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 35: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightArithmeticShift>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 36: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::RightShiftEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 37: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Asterisk>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 38: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Ampersand>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 39: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 40: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::AmpersandAmpersand>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 41: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Pipe>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 42: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipeEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 43: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::PipePipe>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 44: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Caret>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 45: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::CaretEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 46: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Dollar>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 47: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Tilde>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 48: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ForwardSlash>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 49: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::ExclamationPoint>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 50: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMark>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 51: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMark>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 52: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::QuestionMarkQuestionMarkEqual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 53: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Comma>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 54: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Dot>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 55: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::DotDot>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 57: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Eof>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 58: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::FatArrow>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 59: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Arrow>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 60: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::And>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 61: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Anon>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 62: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::As>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 63: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Boxed>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 64: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Break>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 65: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Catch>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 66: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Class>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 67: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Continue>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 68: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Cpp>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 69: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Defer>();
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
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Function>();
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
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Return>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 93: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Restricted>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 94: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Struct>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 95: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::This>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 96: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throw>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 97: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Throws>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 98: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::True>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 99: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Try>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 100: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Unsafe>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 101: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Virtual>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 102: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Weak>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 103: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::While>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 104: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Yield>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 105: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Guard>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 106: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Implements>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 107: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Requires>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 108: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::Token::Trait>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 109: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Garbage>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> lexer::LiteralPrefix::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* None */: {
[[maybe_unused]] auto const& that = this->template get<LiteralPrefix::None>();
TRY(builder.append("LiteralPrefix::None"));
break;}
case 1 /* Hexadecimal */: {
[[maybe_unused]] auto const& that = this->template get<LiteralPrefix::Hexadecimal>();
TRY(builder.append("LiteralPrefix::Hexadecimal"));
break;}
case 2 /* Octal */: {
[[maybe_unused]] auto const& that = this->template get<LiteralPrefix::Octal>();
TRY(builder.append("LiteralPrefix::Octal"));
break;}
case 3 /* Binary */: {
[[maybe_unused]] auto const& that = this->template get<LiteralPrefix::Binary>();
TRY(builder.append("LiteralPrefix::Binary"));
break;}
}
return builder.to_string();
}
String lexer::LiteralPrefix::to_string() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, String>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralPrefix::None>();
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralPrefix::Hexadecimal>();
return JaktInternal::ExplicitValue(String("0x"));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralPrefix::Octal>();
return JaktInternal::ExplicitValue(String("0o"));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::LiteralPrefix::Binary>();
return JaktInternal::ExplicitValue(String("0b"));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

}
} // namespace Jakt
