#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "lexer.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace lexer {
ByteString Jakt::lexer::Lexer::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Lexer("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("input: {}, ", input);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("comment_contents: {}, ", comment_contents);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("illegal_cpp_keywords: {}", illegal_cpp_keywords);
}
builder.append(")"sv);return builder.to_string(); }
JaktInternal::DynamicArray<Jakt::lexer::Token> Jakt::lexer::Lexer::lex(NonnullRefPtr<Jakt::compiler::Compiler> const compiler) {
{
JaktInternal::Set<ByteString> const illegal_cpp_keywords = Set<ByteString>::create_with_values({ByteString::from_utf8_without_validation("alignas"sv), ByteString::from_utf8_without_validation("alignof"sv), ByteString::from_utf8_without_validation("and_eq"sv), ByteString::from_utf8_without_validation("asm"sv), ByteString::from_utf8_without_validation("auto"sv), ByteString::from_utf8_without_validation("bitand"sv), ByteString::from_utf8_without_validation("bitor"sv), ByteString::from_utf8_without_validation("case"sv), ByteString::from_utf8_without_validation("char"sv), ByteString::from_utf8_without_validation("char8_t"sv), ByteString::from_utf8_without_validation("char16_t"sv), ByteString::from_utf8_without_validation("char32_t"sv), ByteString::from_utf8_without_validation("compl"sv), ByteString::from_utf8_without_validation("concept"sv), ByteString::from_utf8_without_validation("consteval"sv), ByteString::from_utf8_without_validation("constexpr"sv), ByteString::from_utf8_without_validation("constinit"sv), ByteString::from_utf8_without_validation("const_cast"sv), ByteString::from_utf8_without_validation("co_await"sv), ByteString::from_utf8_without_validation("co_return"sv), ByteString::from_utf8_without_validation("co_yield"sv), ByteString::from_utf8_without_validation("decltype"sv), ByteString::from_utf8_without_validation("delete"sv), ByteString::from_utf8_without_validation("do"sv), ByteString::from_utf8_without_validation("double"sv), ByteString::from_utf8_without_validation("dynamic_cast"sv), ByteString::from_utf8_without_validation("explicit"sv), ByteString::from_utf8_without_validation("float"sv), ByteString::from_utf8_without_validation("friend"sv), ByteString::from_utf8_without_validation("goto"sv), ByteString::from_utf8_without_validation("int"sv), ByteString::from_utf8_without_validation("long"sv), ByteString::from_utf8_without_validation("mutable"sv), ByteString::from_utf8_without_validation("new"sv), ByteString::from_utf8_without_validation("noexcept"sv), ByteString::from_utf8_without_validation("not_eq"sv), ByteString::from_utf8_without_validation("nullptr"sv), ByteString::from_utf8_without_validation("operator"sv), ByteString::from_utf8_without_validation("or_eq"sv), ByteString::from_utf8_without_validation("protected"sv), ByteString::from_utf8_without_validation("register"sv), ByteString::from_utf8_without_validation("reinterpret_cast"sv), ByteString::from_utf8_without_validation("short"sv), ByteString::from_utf8_without_validation("signed"sv), ByteString::from_utf8_without_validation("static"sv), ByteString::from_utf8_without_validation("static_assert"sv), ByteString::from_utf8_without_validation("static_cast"sv), ByteString::from_utf8_without_validation("switch"sv), ByteString::from_utf8_without_validation("template"sv), ByteString::from_utf8_without_validation("thread_local"sv), ByteString::from_utf8_without_validation("typedef"sv), ByteString::from_utf8_without_validation("typeid"sv), ByteString::from_utf8_without_validation("typename"sv), ByteString::from_utf8_without_validation("union"sv), ByteString::from_utf8_without_validation("unsigned"sv), ByteString::from_utf8_without_validation("using"sv), ByteString::from_utf8_without_validation("volatile"sv), ByteString::from_utf8_without_validation("wchar_t"sv), ByteString::from_utf8_without_validation("xor"sv), ByteString::from_utf8_without_validation("xor_eq"sv)});
Jakt::lexer::Lexer lexer = Jakt::lexer::Lexer(static_cast<size_t>(0ULL),compiler->current_file_contents,compiler,JaktInternal::OptionalNone(),illegal_cpp_keywords);
JaktInternal::DynamicArray<Jakt::lexer::Token> tokens = DynamicArray<Jakt::lexer::Token>::create_with({});
{
Jakt::lexer::Lexer _magic = lexer;
for (;;){
JaktInternal::Optional<Jakt::lexer::Token> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::lexer::Token token = _magic_value.value();
{
tokens.push(token);
}

}
}

return tokens;
}
}

void Jakt::lexer::Lexer::error(ByteString const message,Jakt::utility::Span const span) {
{
this->compiler->errors.push(Jakt::error::JaktError::Message(message,span));
}
}

Jakt::utility::Span Jakt::lexer::Lexer::span(size_t const start,size_t const end) const {
{
return Jakt::utility::Span(this->compiler->current_file.value(),start,end);
}
}

u8 Jakt::lexer::Lexer::peek() const {
{
if (this->eof()){
return static_cast<u8>(0);
}
return this->input[this->index];
}
}

u8 Jakt::lexer::Lexer::peek_ahead(size_t const steps) const {
{
if (JaktInternal::checked_add(this->index,steps) >= this->input.size()){
return static_cast<u8>(0);
}
return this->input[JaktInternal::checked_add(this->index,steps)];
}
}

u8 Jakt::lexer::Lexer::peek_behind(size_t const steps) const {
{
if (this->index < steps){
return static_cast<u8>(0);
}
return this->input[JaktInternal::checked_sub(this->index,steps)];
}
}

bool Jakt::lexer::Lexer::eof() const {
{
return this->index >= this->input.size();
}
}

ByteString Jakt::lexer::Lexer::substring(size_t const start,size_t const length) const {
{
ByteStringBuilder builder = ByteStringBuilder::create();
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(start),static_cast<size_t>(length)};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
builder.append(this->input[i]);
}

}
}

return builder.to_string();
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_character_constant_or_name() {
{
if (this->peek_ahead(static_cast<size_t>(1ULL)) != static_cast<u8>(u8'\'')){
return this->lex_number_or_name();
}
JaktInternal::Optional<ByteString> const prefix = [&]() -> JaktInternal::Optional<ByteString> { auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'b')) {return ByteString::from_utf8_without_validation("b"sv);}else if (__jakt_enum_value == static_cast<u8>(u8'c')) {return ByteString::from_utf8_without_validation("c"sv);}else {return JaktInternal::OptionalNone();} 
}();
if (prefix.has_value()){
this->index += static_cast<size_t>(1ULL);
}
size_t const start = this->index;
this->index++;
bool escaped = false;
while ((!this->eof()) && (escaped || (this->peek() != static_cast<u8>(u8'\'')))){
if (escaped && (JaktInternal::checked_sub(this->index,start) > static_cast<size_t>(3ULL))){
break;
}
else if (JaktInternal::checked_sub(this->index,start) > static_cast<size_t>(2ULL)){
break;
}
if ((!escaped) && (this->peek() == static_cast<u8>(u8'\\'))){
escaped = true;
}
this->index++;
}
if (this->eof() || (this->peek() != static_cast<u8>(u8'\''))){
this->error(ByteString::from_utf8_without_validation("Expected single quote"sv),this->span(start,start));
}
this->index += static_cast<size_t>(1ULL);
ByteStringBuilder builder = ByteStringBuilder::create();
builder.append(this->input[JaktInternal::checked_add(start,static_cast<size_t>(1ULL))]);
if (escaped){
builder.append(this->input[JaktInternal::checked_add(start,static_cast<size_t>(2ULL))]);
}
ByteString const quote = builder.to_string();
size_t const end = this->index;
return Jakt::lexer::Token::SingleQuotedString(quote,prefix,this->span(start,end));
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_number_or_name() {
{
size_t const start = this->index;
if (this->eof()){
this->error(ByteString::from_utf8_without_validation("unexpected eof"sv),this->span(start,start));
return Jakt::lexer::Token::Garbage(JaktInternal::OptionalNone(),this->span(start,start));
}
if (Jakt::utility::is_ascii_digit(this->peek())){
return this->lex_number();
}
else if (Jakt::utility::is_ascii_alpha(this->peek()) || (this->peek() == static_cast<u8>(u8'_'))){
ByteStringBuilder string_builder = ByteStringBuilder::create();
while (Jakt::utility::is_ascii_alphanumeric(this->peek()) || (this->peek() == static_cast<u8>(u8'_'))){
u8 const value = this->input[this->index];
++this->index;
string_builder.append(value);
}
size_t const end = this->index;
Jakt::utility::Span const span = this->span(start,end);
ByteString const string = string_builder.to_string();
if ((JaktInternal::checked_sub(end,start) >= static_cast<size_t>(6ULL)) && (string.substring(static_cast<size_t>(0ULL),static_cast<size_t>(6ULL)) == ByteString::from_utf8_without_validation("__jakt"sv))){
this->error(ByteString::from_utf8_without_validation("reserved identifier name"sv),span);
}
if (this->illegal_cpp_keywords.contains(string)){
this->error(ByteString::from_utf8_without_validation("C++ keywords are not allowed to be used as identifiers"sv),span);
}
return Jakt::lexer::Token::from_keyword_or_identifier(string,span);
}
u8 const unknown_char = this->input[this->index];
size_t const end = ++this->index;
this->error(__jakt_format(StringView::from_string_literal("unknown character: {:c}"sv),unknown_char),this->span(start,end));
return Jakt::lexer::Token::Garbage(__jakt_format(StringView::from_string_literal("{:c}"sv),unknown_char),this->span(start,end));
}
}

bool Jakt::lexer::Lexer::valid_digit(Jakt::lexer::LiteralPrefix const prefix,u8 const digit,bool const decimal_allowed) {
{
{auto&& __jakt_match_variant = prefix;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Hexadecimal */:return Jakt::utility::is_ascii_hexdigit(digit);case 2 /* Octal */:return Jakt::utility::is_ascii_octdigit(digit);case 3 /* Binary */:return Jakt::utility::is_ascii_binary(digit);default:return Jakt::utility::is_ascii_digit(digit) || (decimal_allowed && (digit == static_cast<u8>(u8'.')));}/*switch end*/
}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_number() {
{
size_t const start = this->index;
bool floating = false;
Jakt::lexer::LiteralPrefix prefix = Jakt::lexer::LiteralPrefix::None();
ByteStringBuilder number = ByteStringBuilder::create();
if (this->peek() == static_cast<u8>(u8'0')){
{auto __jakt_enum_value = this->peek_ahead(static_cast<size_t>(1ULL));
if (__jakt_enum_value == static_cast<u8>(u8'x')) {{
prefix = Jakt::lexer::LiteralPrefix::Hexadecimal();
this->index += static_cast<size_t>(2ULL);
}
goto __jakt_label_5;}else if (__jakt_enum_value == static_cast<u8>(u8'o')) {{
prefix = Jakt::lexer::LiteralPrefix::Octal();
this->index += static_cast<size_t>(2ULL);
}
goto __jakt_label_5;}else if (__jakt_enum_value == static_cast<u8>(u8'b')) {{
prefix = Jakt::lexer::LiteralPrefix::Binary();
this->index += static_cast<size_t>(2ULL);
}
goto __jakt_label_5;}else {{
}
goto __jakt_label_5;}}goto __jakt_label_5; __jakt_label_5:;;
}
while (!this->eof()){
u8 const value = this->input[this->index];
if (!this->valid_digit(prefix,value,true)){
break;
}
if (value == static_cast<u8>(u8'.')){
if (floating || (!this->valid_digit(prefix,this->peek_ahead(static_cast<size_t>(1ULL)),false))){
break;
}
number.append(static_cast<u8>(u8'.'));
floating = true;
this->index++;
continue;
}
number.append(value);
++this->index;
if (this->peek() == static_cast<u8>(u8'_')){
number.append(static_cast<u8>(u8'_'));
if (this->valid_digit(prefix,this->peek_ahead(static_cast<size_t>(1ULL)),true)){
++this->index;
}
else {
break;
}

}
}
Jakt::lexer::LiteralSuffix const suffix = this->consume_numeric_literal_suffix();
return Jakt::lexer::Token::Number(prefix,number.to_string(),suffix,this->span(start,this->index));
}
}

Jakt::lexer::LiteralSuffix Jakt::lexer::Lexer::consume_numeric_literal_suffix() {
{
{auto __jakt_enum_value = this->peek();
if ((__jakt_enum_value == static_cast<u8>(u8'u'))||(__jakt_enum_value == static_cast<u8>(u8'i'))||(__jakt_enum_value == static_cast<u8>(u8'f'))) {{
}
goto __jakt_label_6;}else {{
return Jakt::lexer::LiteralSuffix::None();
}
goto __jakt_label_6;}}goto __jakt_label_6; __jakt_label_6:;;
if ((this->peek() == static_cast<u8>(u8'u')) && (this->peek_ahead(static_cast<size_t>(1ULL)) == static_cast<u8>(u8'z'))){
this->index += static_cast<size_t>(2ULL);
return Jakt::lexer::LiteralSuffix::UZ();
}
size_t local_index = static_cast<size_t>(1ULL);
i64 width = static_cast<i64>(0LL);
while (Jakt::utility::is_ascii_digit(this->peek_ahead(local_index))){
if (local_index > static_cast<size_t>(3ULL)){
return Jakt::lexer::LiteralSuffix::None();
}
u8 const value = this->input[JaktInternal::checked_add(this->index,local_index)];
++local_index;
i64 const digit = Jakt::as_saturated<i64, u8>(JaktInternal::checked_sub(value,static_cast<u8>(u8'0')));
width = JaktInternal::checked_add(JaktInternal::checked_mul(width,static_cast<i64>(10LL)),digit);
}
Jakt::lexer::LiteralSuffix const suffix = [&]() -> Jakt::lexer::LiteralSuffix { auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'u')) {{auto __jakt_enum_value = width;
if (__jakt_enum_value == static_cast<i64>(8LL)) {return Jakt::lexer::LiteralSuffix::U8();}else if (__jakt_enum_value == static_cast<i64>(16LL)) {return Jakt::lexer::LiteralSuffix::U16();}else if (__jakt_enum_value == static_cast<i64>(32LL)) {return Jakt::lexer::LiteralSuffix::U32();}else if (__jakt_enum_value == static_cast<i64>(64LL)) {return Jakt::lexer::LiteralSuffix::U64();}else {return Jakt::lexer::LiteralSuffix::None();}}}else if (__jakt_enum_value == static_cast<u8>(u8'i')) {{auto __jakt_enum_value = width;
if (__jakt_enum_value == static_cast<i64>(8LL)) {return Jakt::lexer::LiteralSuffix::I8();}else if (__jakt_enum_value == static_cast<i64>(16LL)) {return Jakt::lexer::LiteralSuffix::I16();}else if (__jakt_enum_value == static_cast<i64>(32LL)) {return Jakt::lexer::LiteralSuffix::I32();}else if (__jakt_enum_value == static_cast<i64>(64LL)) {return Jakt::lexer::LiteralSuffix::I64();}else {return Jakt::lexer::LiteralSuffix::None();}}}else if (__jakt_enum_value == static_cast<u8>(u8'f')) {{auto __jakt_enum_value = width;
if (__jakt_enum_value == static_cast<i64>(32LL)) {return Jakt::lexer::LiteralSuffix::F32();}else if (__jakt_enum_value == static_cast<i64>(64LL)) {return Jakt::lexer::LiteralSuffix::F64();}else {return Jakt::lexer::LiteralSuffix::None();}}}else {return Jakt::lexer::LiteralSuffix::None();} 
}();
if (!(suffix.__jakt_init_index() == 0 /* None */)){
this->index += local_index;
}
return suffix;
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_quoted_string(u8 const delimiter) {
{
size_t const start = this->index;
++this->index;
if (this->eof()){
this->error(ByteString::from_utf8_without_validation("unexpected eof"sv),this->span(start,start));
return Jakt::lexer::Token::Garbage(JaktInternal::OptionalNone(),this->span(start,start));
}
bool escaped = false;
while ((!this->eof()) && (escaped || (this->peek() != delimiter))){
if ((this->peek() == static_cast<u8>(u8'\r')) || (this->peek() == static_cast<u8>(u8'\n'))){
++this->index;
continue;
}
if ((!escaped) && (this->peek() == static_cast<u8>(u8'\\'))){
escaped = true;
}
else {
escaped = false;
}

++this->index;
}
ByteString const str = this->substring(JaktInternal::checked_add(start,static_cast<size_t>(1ULL)),this->index);
this->index++;
size_t const end = this->index;
if (delimiter == static_cast<u8>(u8'\'')){
return Jakt::lexer::Token::SingleQuotedString(str,JaktInternal::OptionalNone(),this->span(start,end));
}
return Jakt::lexer::Token::QuotedString(str,this->span(start,end));
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_plus() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::PlusEqual(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'+')) {return Jakt::lexer::Token::PlusPlus(this->span(start,++this->index));}else {return Jakt::lexer::Token::Plus(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_minus() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::MinusEqual(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'-')) {return Jakt::lexer::Token::MinusMinus(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'>')) {return Jakt::lexer::Token::Arrow(this->span(start,++this->index));}else {return Jakt::lexer::Token::Minus(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_asterisk() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::AsteriskEqual(this->span(start,++this->index));}else {return Jakt::lexer::Token::Asterisk(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_forward_slash() {
{
size_t const start = this->index++;
if (this->peek() == static_cast<u8>(u8'=')){
return Jakt::lexer::Token::ForwardSlashEqual(this->span(start,++this->index));
}
if (this->peek() != static_cast<u8>(u8'/')){
return Jakt::lexer::Token::ForwardSlash(this->span(start,this->index));
}
if (this->comment_contents.has_value()){
this->index--;
return Jakt::lexer::Token::Eol(this->consume_comment_contents(),this->span(start,this->index));
}
this->index++;
size_t const comment_start_index = this->index;
while (!this->eof()){
u8 const c = this->peek();
this->index++;
if (c == static_cast<u8>(u8'\n')){
this->index--;
break;
}
}
this->comment_contents = this->input[JaktInternal::Range<size_t>{static_cast<size_t>(comment_start_index),static_cast<size_t>(this->index)}].to_array();
return this->next().value_or_lazy_evaluated([&] { return Jakt::lexer::Token::Eof(this->span(this->index,this->index)); });
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_caret() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::CaretEqual(this->span(start,++this->index));}else {return Jakt::lexer::Token::Caret(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_pipe() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::PipeEqual(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'|')) {return Jakt::lexer::Token::PipePipe(this->span(start,++this->index));}else {return Jakt::lexer::Token::Pipe(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_percent_sign() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::PercentSignEqual(this->span(start,++this->index));}else {return Jakt::lexer::Token::PercentSign(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_exclamation_point() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::NotEqual(this->span(start,++this->index));}else {return Jakt::lexer::Token::ExclamationPoint(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_ampersand() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::AmpersandEqual(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'&')) {return Jakt::lexer::Token::AmpersandAmpersand(this->span(start,++this->index));}else {return Jakt::lexer::Token::Ampersand(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_less_than() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::LessThanOrEqual(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'<')) {{
this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'<')) {return Jakt::lexer::Token::LeftArithmeticShift(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::LeftShiftEqual(this->span(start,++this->index));}else {return Jakt::lexer::Token::LeftShift(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
VERIFY_NOT_REACHED();
}else {return Jakt::lexer::Token::LessThan(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_greater_than() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::GreaterThanOrEqual(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'>')) {{
this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'>')) {return Jakt::lexer::Token::RightArithmeticShift(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::RightShiftEqual(this->span(start,++this->index));}else {return Jakt::lexer::Token::RightShift(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
VERIFY_NOT_REACHED();
}else {return Jakt::lexer::Token::GreaterThan(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_dot() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'.')) {return Jakt::lexer::Token::DotDot(this->span(start,++this->index));}else {return Jakt::lexer::Token::Dot(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_colon() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8':')) {return Jakt::lexer::Token::ColonColon(this->span(start,++this->index));}else {return Jakt::lexer::Token::Colon(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_question_mark() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'?')) {{
this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::QuestionMarkQuestionMarkEqual(this->span(start,++this->index));}else {return Jakt::lexer::Token::QuestionMarkQuestionMark(this->span(start,this->index));}}
}
VERIFY_NOT_REACHED();
}else {return Jakt::lexer::Token::QuestionMark(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

Jakt::lexer::Token Jakt::lexer::Lexer::lex_equals() {
{
size_t const start = this->index++;
{auto __jakt_enum_value = this->peek();
if (__jakt_enum_value == static_cast<u8>(u8'=')) {return Jakt::lexer::Token::DoubleEqual(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'>')) {return Jakt::lexer::Token::FatArrow(this->span(start,++this->index));}else {return Jakt::lexer::Token::Equal(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),this->index));}}
}
}

JaktInternal::Optional<ByteString> Jakt::lexer::Lexer::consume_comment_contents() {
{
if (!this->comment_contents.has_value()){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<u8> const contents = this->comment_contents.value();
this->comment_contents = JaktInternal::OptionalNone();
ByteStringBuilder builder = ByteStringBuilder::create();
{
JaktInternal::ArrayIterator<u8> _magic = contents.iterator();
for (;;){
JaktInternal::Optional<u8> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
u8 c = _magic_value.value();
{
builder.append(c);
}

}
}

return builder.to_string();
}
}

JaktInternal::Optional<Jakt::lexer::Token> Jakt::lexer::Lexer::next() {
{
for (;;){
if (this->index == this->input.size()){
++this->index;
return Jakt::lexer::Token::Eof(this->span(JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL)),JaktInternal::checked_sub(this->index,static_cast<size_t>(1ULL))));
}
if (this->eof()){
return JaktInternal::OptionalNone();
}
u8 const ch = this->peek();
if (Jakt::utility::is_whitespace(ch)){
this->index++;
}
else {
break;
}

}
size_t const start = this->index;
{auto __jakt_enum_value = this->input[this->index];
if (__jakt_enum_value == static_cast<u8>(u8'(')) {return Jakt::lexer::Token::LParen(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8')')) {return Jakt::lexer::Token::RParen(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'[')) {return Jakt::lexer::Token::LSquare(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8']')) {return Jakt::lexer::Token::RSquare(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'{')) {return Jakt::lexer::Token::LCurly(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'}')) {return Jakt::lexer::Token::RCurly(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'<')) {return this->lex_less_than();}else if (__jakt_enum_value == static_cast<u8>(u8'>')) {return this->lex_greater_than();}else if (__jakt_enum_value == static_cast<u8>(u8'.')) {return this->lex_dot();}else if (__jakt_enum_value == static_cast<u8>(u8',')) {return Jakt::lexer::Token::Comma(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'~')) {return Jakt::lexer::Token::Tilde(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8';')) {return Jakt::lexer::Token::Semicolon(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8':')) {return this->lex_colon();}else if (__jakt_enum_value == static_cast<u8>(u8'?')) {return this->lex_question_mark();}else if (__jakt_enum_value == static_cast<u8>(u8'+')) {return this->lex_plus();}else if (__jakt_enum_value == static_cast<u8>(u8'-')) {return this->lex_minus();}else if (__jakt_enum_value == static_cast<u8>(u8'*')) {return this->lex_asterisk();}else if (__jakt_enum_value == static_cast<u8>(u8'/')) {return this->lex_forward_slash();}else if (__jakt_enum_value == static_cast<u8>(u8'^')) {return this->lex_caret();}else if (__jakt_enum_value == static_cast<u8>(u8'|')) {return this->lex_pipe();}else if (__jakt_enum_value == static_cast<u8>(u8'%')) {return this->lex_percent_sign();}else if (__jakt_enum_value == static_cast<u8>(u8'!')) {return this->lex_exclamation_point();}else if (__jakt_enum_value == static_cast<u8>(u8'&')) {return this->lex_ampersand();}else if (__jakt_enum_value == static_cast<u8>(u8'$')) {return Jakt::lexer::Token::Dollar(this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'=')) {return this->lex_equals();}else if (__jakt_enum_value == static_cast<u8>(u8'\n')) {return Jakt::lexer::Token::Eol(this->consume_comment_contents(),this->span(start,++this->index));}else if (__jakt_enum_value == static_cast<u8>(u8'\'')) {return this->lex_quoted_string(static_cast<u8>(u8'\''));}else if (__jakt_enum_value == static_cast<u8>(u8'\"')) {return this->lex_quoted_string(static_cast<u8>(u8'"'));}else if (__jakt_enum_value == static_cast<u8>(u8'b')) {return this->lex_character_constant_or_name();}else if (__jakt_enum_value == static_cast<u8>(u8'c')) {return this->lex_character_constant_or_name();}else {return this->lex_number_or_name();}}
}
}

Jakt::lexer::Lexer::Lexer(size_t a_index, JaktInternal::DynamicArray<u8> a_input, NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> a_comment_contents, JaktInternal::Set<ByteString> a_illegal_cpp_keywords): index(move(a_index)), input(move(a_input)), compiler(move(a_compiler)), comment_contents(move(a_comment_contents)), illegal_cpp_keywords(move(a_illegal_cpp_keywords)){}

ByteString Jakt::lexer::Token::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* SingleQuotedString */: {
builder.append("Token::SingleQuotedString"sv);
[[maybe_unused]] auto const& that = this->as.SingleQuotedString;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("quote: \"{}\", ", that.quote);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("prefix: {}, ", that.prefix);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* QuotedString */: {
builder.append("Token::QuotedString"sv);
[[maybe_unused]] auto const& that = this->as.QuotedString;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("quote: \"{}\", ", that.quote);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 2 /* Number */: {
builder.append("Token::Number"sv);
[[maybe_unused]] auto const& that = this->as.Number;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("prefix: {}, ", that.prefix);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("number: \"{}\", ", that.number);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("suffix: {}, ", that.suffix);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 3 /* Identifier */: {
builder.append("Token::Identifier"sv);
[[maybe_unused]] auto const& that = this->as.Identifier;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 4 /* Semicolon */: {
builder.append("Token::Semicolon"sv);
[[maybe_unused]] auto const& that = this->as.Semicolon;
builder.appendff("({})", that.value);
break;}
case 5 /* Colon */: {
builder.append("Token::Colon"sv);
[[maybe_unused]] auto const& that = this->as.Colon;
builder.appendff("({})", that.value);
break;}
case 6 /* ColonColon */: {
builder.append("Token::ColonColon"sv);
[[maybe_unused]] auto const& that = this->as.ColonColon;
builder.appendff("({})", that.value);
break;}
case 7 /* LParen */: {
builder.append("Token::LParen"sv);
[[maybe_unused]] auto const& that = this->as.LParen;
builder.appendff("({})", that.value);
break;}
case 8 /* RParen */: {
builder.append("Token::RParen"sv);
[[maybe_unused]] auto const& that = this->as.RParen;
builder.appendff("({})", that.value);
break;}
case 9 /* LCurly */: {
builder.append("Token::LCurly"sv);
[[maybe_unused]] auto const& that = this->as.LCurly;
builder.appendff("({})", that.value);
break;}
case 10 /* RCurly */: {
builder.append("Token::RCurly"sv);
[[maybe_unused]] auto const& that = this->as.RCurly;
builder.appendff("({})", that.value);
break;}
case 11 /* LSquare */: {
builder.append("Token::LSquare"sv);
[[maybe_unused]] auto const& that = this->as.LSquare;
builder.appendff("({})", that.value);
break;}
case 12 /* RSquare */: {
builder.append("Token::RSquare"sv);
[[maybe_unused]] auto const& that = this->as.RSquare;
builder.appendff("({})", that.value);
break;}
case 13 /* PercentSign */: {
builder.append("Token::PercentSign"sv);
[[maybe_unused]] auto const& that = this->as.PercentSign;
builder.appendff("({})", that.value);
break;}
case 14 /* Plus */: {
builder.append("Token::Plus"sv);
[[maybe_unused]] auto const& that = this->as.Plus;
builder.appendff("({})", that.value);
break;}
case 15 /* Minus */: {
builder.append("Token::Minus"sv);
[[maybe_unused]] auto const& that = this->as.Minus;
builder.appendff("({})", that.value);
break;}
case 16 /* Equal */: {
builder.append("Token::Equal"sv);
[[maybe_unused]] auto const& that = this->as.Equal;
builder.appendff("({})", that.value);
break;}
case 17 /* PlusEqual */: {
builder.append("Token::PlusEqual"sv);
[[maybe_unused]] auto const& that = this->as.PlusEqual;
builder.appendff("({})", that.value);
break;}
case 18 /* PlusPlus */: {
builder.append("Token::PlusPlus"sv);
[[maybe_unused]] auto const& that = this->as.PlusPlus;
builder.appendff("({})", that.value);
break;}
case 19 /* MinusEqual */: {
builder.append("Token::MinusEqual"sv);
[[maybe_unused]] auto const& that = this->as.MinusEqual;
builder.appendff("({})", that.value);
break;}
case 20 /* MinusMinus */: {
builder.append("Token::MinusMinus"sv);
[[maybe_unused]] auto const& that = this->as.MinusMinus;
builder.appendff("({})", that.value);
break;}
case 21 /* AsteriskEqual */: {
builder.append("Token::AsteriskEqual"sv);
[[maybe_unused]] auto const& that = this->as.AsteriskEqual;
builder.appendff("({})", that.value);
break;}
case 22 /* ForwardSlashEqual */: {
builder.append("Token::ForwardSlashEqual"sv);
[[maybe_unused]] auto const& that = this->as.ForwardSlashEqual;
builder.appendff("({})", that.value);
break;}
case 23 /* PercentSignEqual */: {
builder.append("Token::PercentSignEqual"sv);
[[maybe_unused]] auto const& that = this->as.PercentSignEqual;
builder.appendff("({})", that.value);
break;}
case 24 /* NotEqual */: {
builder.append("Token::NotEqual"sv);
[[maybe_unused]] auto const& that = this->as.NotEqual;
builder.appendff("({})", that.value);
break;}
case 25 /* DoubleEqual */: {
builder.append("Token::DoubleEqual"sv);
[[maybe_unused]] auto const& that = this->as.DoubleEqual;
builder.appendff("({})", that.value);
break;}
case 26 /* GreaterThan */: {
builder.append("Token::GreaterThan"sv);
[[maybe_unused]] auto const& that = this->as.GreaterThan;
builder.appendff("({})", that.value);
break;}
case 27 /* GreaterThanOrEqual */: {
builder.append("Token::GreaterThanOrEqual"sv);
[[maybe_unused]] auto const& that = this->as.GreaterThanOrEqual;
builder.appendff("({})", that.value);
break;}
case 28 /* LessThan */: {
builder.append("Token::LessThan"sv);
[[maybe_unused]] auto const& that = this->as.LessThan;
builder.appendff("({})", that.value);
break;}
case 29 /* LessThanOrEqual */: {
builder.append("Token::LessThanOrEqual"sv);
[[maybe_unused]] auto const& that = this->as.LessThanOrEqual;
builder.appendff("({})", that.value);
break;}
case 30 /* LeftArithmeticShift */: {
builder.append("Token::LeftArithmeticShift"sv);
[[maybe_unused]] auto const& that = this->as.LeftArithmeticShift;
builder.appendff("({})", that.value);
break;}
case 31 /* LeftShift */: {
builder.append("Token::LeftShift"sv);
[[maybe_unused]] auto const& that = this->as.LeftShift;
builder.appendff("({})", that.value);
break;}
case 32 /* LeftShiftEqual */: {
builder.append("Token::LeftShiftEqual"sv);
[[maybe_unused]] auto const& that = this->as.LeftShiftEqual;
builder.appendff("({})", that.value);
break;}
case 33 /* RightShift */: {
builder.append("Token::RightShift"sv);
[[maybe_unused]] auto const& that = this->as.RightShift;
builder.appendff("({})", that.value);
break;}
case 34 /* RightArithmeticShift */: {
builder.append("Token::RightArithmeticShift"sv);
[[maybe_unused]] auto const& that = this->as.RightArithmeticShift;
builder.appendff("({})", that.value);
break;}
case 35 /* RightShiftEqual */: {
builder.append("Token::RightShiftEqual"sv);
[[maybe_unused]] auto const& that = this->as.RightShiftEqual;
builder.appendff("({})", that.value);
break;}
case 36 /* Asterisk */: {
builder.append("Token::Asterisk"sv);
[[maybe_unused]] auto const& that = this->as.Asterisk;
builder.appendff("({})", that.value);
break;}
case 37 /* Ampersand */: {
builder.append("Token::Ampersand"sv);
[[maybe_unused]] auto const& that = this->as.Ampersand;
builder.appendff("({})", that.value);
break;}
case 38 /* AmpersandEqual */: {
builder.append("Token::AmpersandEqual"sv);
[[maybe_unused]] auto const& that = this->as.AmpersandEqual;
builder.appendff("({})", that.value);
break;}
case 39 /* AmpersandAmpersand */: {
builder.append("Token::AmpersandAmpersand"sv);
[[maybe_unused]] auto const& that = this->as.AmpersandAmpersand;
builder.appendff("({})", that.value);
break;}
case 40 /* Pipe */: {
builder.append("Token::Pipe"sv);
[[maybe_unused]] auto const& that = this->as.Pipe;
builder.appendff("({})", that.value);
break;}
case 41 /* PipeEqual */: {
builder.append("Token::PipeEqual"sv);
[[maybe_unused]] auto const& that = this->as.PipeEqual;
builder.appendff("({})", that.value);
break;}
case 42 /* PipePipe */: {
builder.append("Token::PipePipe"sv);
[[maybe_unused]] auto const& that = this->as.PipePipe;
builder.appendff("({})", that.value);
break;}
case 43 /* Caret */: {
builder.append("Token::Caret"sv);
[[maybe_unused]] auto const& that = this->as.Caret;
builder.appendff("({})", that.value);
break;}
case 44 /* CaretEqual */: {
builder.append("Token::CaretEqual"sv);
[[maybe_unused]] auto const& that = this->as.CaretEqual;
builder.appendff("({})", that.value);
break;}
case 45 /* Dollar */: {
builder.append("Token::Dollar"sv);
[[maybe_unused]] auto const& that = this->as.Dollar;
builder.appendff("({})", that.value);
break;}
case 46 /* Tilde */: {
builder.append("Token::Tilde"sv);
[[maybe_unused]] auto const& that = this->as.Tilde;
builder.appendff("({})", that.value);
break;}
case 47 /* ForwardSlash */: {
builder.append("Token::ForwardSlash"sv);
[[maybe_unused]] auto const& that = this->as.ForwardSlash;
builder.appendff("({})", that.value);
break;}
case 48 /* ExclamationPoint */: {
builder.append("Token::ExclamationPoint"sv);
[[maybe_unused]] auto const& that = this->as.ExclamationPoint;
builder.appendff("({})", that.value);
break;}
case 49 /* QuestionMark */: {
builder.append("Token::QuestionMark"sv);
[[maybe_unused]] auto const& that = this->as.QuestionMark;
builder.appendff("({})", that.value);
break;}
case 50 /* QuestionMarkQuestionMark */: {
builder.append("Token::QuestionMarkQuestionMark"sv);
[[maybe_unused]] auto const& that = this->as.QuestionMarkQuestionMark;
builder.appendff("({})", that.value);
break;}
case 51 /* QuestionMarkQuestionMarkEqual */: {
builder.append("Token::QuestionMarkQuestionMarkEqual"sv);
[[maybe_unused]] auto const& that = this->as.QuestionMarkQuestionMarkEqual;
builder.appendff("({})", that.value);
break;}
case 52 /* Comma */: {
builder.append("Token::Comma"sv);
[[maybe_unused]] auto const& that = this->as.Comma;
builder.appendff("({})", that.value);
break;}
case 53 /* Dot */: {
builder.append("Token::Dot"sv);
[[maybe_unused]] auto const& that = this->as.Dot;
builder.appendff("({})", that.value);
break;}
case 54 /* DotDot */: {
builder.append("Token::DotDot"sv);
[[maybe_unused]] auto const& that = this->as.DotDot;
builder.appendff("({})", that.value);
break;}
case 55 /* Eol */: {
builder.append("Token::Eol"sv);
[[maybe_unused]] auto const& that = this->as.Eol;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("comment: {}, ", that.comment);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 56 /* Eof */: {
builder.append("Token::Eof"sv);
[[maybe_unused]] auto const& that = this->as.Eof;
builder.appendff("({})", that.value);
break;}
case 57 /* FatArrow */: {
builder.append("Token::FatArrow"sv);
[[maybe_unused]] auto const& that = this->as.FatArrow;
builder.appendff("({})", that.value);
break;}
case 58 /* Arrow */: {
builder.append("Token::Arrow"sv);
[[maybe_unused]] auto const& that = this->as.Arrow;
builder.appendff("({})", that.value);
break;}
case 59 /* And */: {
builder.append("Token::And"sv);
[[maybe_unused]] auto const& that = this->as.And;
builder.appendff("({})", that.value);
break;}
case 60 /* Anon */: {
builder.append("Token::Anon"sv);
[[maybe_unused]] auto const& that = this->as.Anon;
builder.appendff("({})", that.value);
break;}
case 61 /* As */: {
builder.append("Token::As"sv);
[[maybe_unused]] auto const& that = this->as.As;
builder.appendff("({})", that.value);
break;}
case 62 /* Boxed */: {
builder.append("Token::Boxed"sv);
[[maybe_unused]] auto const& that = this->as.Boxed;
builder.appendff("({})", that.value);
break;}
case 63 /* Break */: {
builder.append("Token::Break"sv);
[[maybe_unused]] auto const& that = this->as.Break;
builder.appendff("({})", that.value);
break;}
case 64 /* Catch */: {
builder.append("Token::Catch"sv);
[[maybe_unused]] auto const& that = this->as.Catch;
builder.appendff("({})", that.value);
break;}
case 65 /* Class */: {
builder.append("Token::Class"sv);
[[maybe_unused]] auto const& that = this->as.Class;
builder.appendff("({})", that.value);
break;}
case 66 /* Continue */: {
builder.append("Token::Continue"sv);
[[maybe_unused]] auto const& that = this->as.Continue;
builder.appendff("({})", that.value);
break;}
case 67 /* Cpp */: {
builder.append("Token::Cpp"sv);
[[maybe_unused]] auto const& that = this->as.Cpp;
builder.appendff("({})", that.value);
break;}
case 68 /* Defer */: {
builder.append("Token::Defer"sv);
[[maybe_unused]] auto const& that = this->as.Defer;
builder.appendff("({})", that.value);
break;}
case 69 /* Destructor */: {
builder.append("Token::Destructor"sv);
[[maybe_unused]] auto const& that = this->as.Destructor;
builder.appendff("({})", that.value);
break;}
case 70 /* Else */: {
builder.append("Token::Else"sv);
[[maybe_unused]] auto const& that = this->as.Else;
builder.appendff("({})", that.value);
break;}
case 71 /* Enum */: {
builder.append("Token::Enum"sv);
[[maybe_unused]] auto const& that = this->as.Enum;
builder.appendff("({})", that.value);
break;}
case 72 /* Extern */: {
builder.append("Token::Extern"sv);
[[maybe_unused]] auto const& that = this->as.Extern;
builder.appendff("({})", that.value);
break;}
case 73 /* Export */: {
builder.append("Token::Export"sv);
[[maybe_unused]] auto const& that = this->as.Export;
builder.appendff("({})", that.value);
break;}
case 74 /* False */: {
builder.append("Token::False"sv);
[[maybe_unused]] auto const& that = this->as.False;
builder.appendff("({})", that.value);
break;}
case 75 /* For */: {
builder.append("Token::For"sv);
[[maybe_unused]] auto const& that = this->as.For;
builder.appendff("({})", that.value);
break;}
case 76 /* Fn */: {
builder.append("Token::Fn"sv);
[[maybe_unused]] auto const& that = this->as.Fn;
builder.appendff("({})", that.value);
break;}
case 77 /* Comptime */: {
builder.append("Token::Comptime"sv);
[[maybe_unused]] auto const& that = this->as.Comptime;
builder.appendff("({})", that.value);
break;}
case 78 /* If */: {
builder.append("Token::If"sv);
[[maybe_unused]] auto const& that = this->as.If;
builder.appendff("({})", that.value);
break;}
case 79 /* Import */: {
builder.append("Token::Import"sv);
[[maybe_unused]] auto const& that = this->as.Import;
builder.appendff("({})", that.value);
break;}
case 80 /* Relative */: {
builder.append("Token::Relative"sv);
[[maybe_unused]] auto const& that = this->as.Relative;
builder.appendff("({})", that.value);
break;}
case 81 /* In */: {
builder.append("Token::In"sv);
[[maybe_unused]] auto const& that = this->as.In;
builder.appendff("({})", that.value);
break;}
case 82 /* Is */: {
builder.append("Token::Is"sv);
[[maybe_unused]] auto const& that = this->as.Is;
builder.appendff("({})", that.value);
break;}
case 83 /* Let */: {
builder.append("Token::Let"sv);
[[maybe_unused]] auto const& that = this->as.Let;
builder.appendff("({})", that.value);
break;}
case 84 /* Loop */: {
builder.append("Token::Loop"sv);
[[maybe_unused]] auto const& that = this->as.Loop;
builder.appendff("({})", that.value);
break;}
case 85 /* Match */: {
builder.append("Token::Match"sv);
[[maybe_unused]] auto const& that = this->as.Match;
builder.appendff("({})", that.value);
break;}
case 86 /* Must */: {
builder.append("Token::Must"sv);
[[maybe_unused]] auto const& that = this->as.Must;
builder.appendff("({})", that.value);
break;}
case 87 /* Mut */: {
builder.append("Token::Mut"sv);
[[maybe_unused]] auto const& that = this->as.Mut;
builder.appendff("({})", that.value);
break;}
case 88 /* Namespace */: {
builder.append("Token::Namespace"sv);
[[maybe_unused]] auto const& that = this->as.Namespace;
builder.appendff("({})", that.value);
break;}
case 89 /* Not */: {
builder.append("Token::Not"sv);
[[maybe_unused]] auto const& that = this->as.Not;
builder.appendff("({})", that.value);
break;}
case 90 /* Or */: {
builder.append("Token::Or"sv);
[[maybe_unused]] auto const& that = this->as.Or;
builder.appendff("({})", that.value);
break;}
case 91 /* Override */: {
builder.append("Token::Override"sv);
[[maybe_unused]] auto const& that = this->as.Override;
builder.appendff("({})", that.value);
break;}
case 92 /* Private */: {
builder.append("Token::Private"sv);
[[maybe_unused]] auto const& that = this->as.Private;
builder.appendff("({})", that.value);
break;}
case 93 /* Public */: {
builder.append("Token::Public"sv);
[[maybe_unused]] auto const& that = this->as.Public;
builder.appendff("({})", that.value);
break;}
case 94 /* Raw */: {
builder.append("Token::Raw"sv);
[[maybe_unused]] auto const& that = this->as.Raw;
builder.appendff("({})", that.value);
break;}
case 95 /* Reflect */: {
builder.append("Token::Reflect"sv);
[[maybe_unused]] auto const& that = this->as.Reflect;
builder.appendff("({})", that.value);
break;}
case 96 /* Return */: {
builder.append("Token::Return"sv);
[[maybe_unused]] auto const& that = this->as.Return;
builder.appendff("({})", that.value);
break;}
case 97 /* Restricted */: {
builder.append("Token::Restricted"sv);
[[maybe_unused]] auto const& that = this->as.Restricted;
builder.appendff("({})", that.value);
break;}
case 98 /* Sizeof */: {
builder.append("Token::Sizeof"sv);
[[maybe_unused]] auto const& that = this->as.Sizeof;
builder.appendff("({})", that.value);
break;}
case 99 /* Struct */: {
builder.append("Token::Struct"sv);
[[maybe_unused]] auto const& that = this->as.Struct;
builder.appendff("({})", that.value);
break;}
case 100 /* This */: {
builder.append("Token::This"sv);
[[maybe_unused]] auto const& that = this->as.This;
builder.appendff("({})", that.value);
break;}
case 101 /* Throw */: {
builder.append("Token::Throw"sv);
[[maybe_unused]] auto const& that = this->as.Throw;
builder.appendff("({})", that.value);
break;}
case 102 /* Throws */: {
builder.append("Token::Throws"sv);
[[maybe_unused]] auto const& that = this->as.Throws;
builder.appendff("({})", that.value);
break;}
case 103 /* True */: {
builder.append("Token::True"sv);
[[maybe_unused]] auto const& that = this->as.True;
builder.appendff("({})", that.value);
break;}
case 104 /* Try */: {
builder.append("Token::Try"sv);
[[maybe_unused]] auto const& that = this->as.Try;
builder.appendff("({})", that.value);
break;}
case 105 /* Unsafe */: {
builder.append("Token::Unsafe"sv);
[[maybe_unused]] auto const& that = this->as.Unsafe;
builder.appendff("({})", that.value);
break;}
case 106 /* Virtual */: {
builder.append("Token::Virtual"sv);
[[maybe_unused]] auto const& that = this->as.Virtual;
builder.appendff("({})", that.value);
break;}
case 107 /* Weak */: {
builder.append("Token::Weak"sv);
[[maybe_unused]] auto const& that = this->as.Weak;
builder.appendff("({})", that.value);
break;}
case 108 /* While */: {
builder.append("Token::While"sv);
[[maybe_unused]] auto const& that = this->as.While;
builder.appendff("({})", that.value);
break;}
case 109 /* Yield */: {
builder.append("Token::Yield"sv);
[[maybe_unused]] auto const& that = this->as.Yield;
builder.appendff("({})", that.value);
break;}
case 110 /* Guard */: {
builder.append("Token::Guard"sv);
[[maybe_unused]] auto const& that = this->as.Guard;
builder.appendff("({})", that.value);
break;}
case 111 /* Implements */: {
builder.append("Token::Implements"sv);
[[maybe_unused]] auto const& that = this->as.Implements;
builder.appendff("({})", that.value);
break;}
case 112 /* Requires */: {
builder.append("Token::Requires"sv);
[[maybe_unused]] auto const& that = this->as.Requires;
builder.appendff("({})", that.value);
break;}
case 113 /* Trait */: {
builder.append("Token::Trait"sv);
[[maybe_unused]] auto const& that = this->as.Trait;
builder.appendff("({})", that.value);
break;}
case 114 /* Garbage */: {
builder.append("Token::Garbage"sv);
[[maybe_unused]] auto const& that = this->as.Garbage;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("consumed: {}, ", that.consumed);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] Token Token::SingleQuotedString(ByteString quote, JaktInternal::Optional<ByteString> prefix, Jakt::utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.SingleQuotedString.quote) (decltype(quote))(move(quote));
new (&__jakt_uninit_enum.as.SingleQuotedString.prefix) (decltype(prefix))(move(prefix));
new (&__jakt_uninit_enum.as.SingleQuotedString.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::QuotedString(ByteString quote, Jakt::utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.QuotedString.quote) (decltype(quote))(move(quote));
new (&__jakt_uninit_enum.as.QuotedString.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Number(Jakt::lexer::LiteralPrefix prefix, ByteString number, Jakt::lexer::LiteralSuffix suffix, Jakt::utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Number.prefix) (decltype(prefix))(move(prefix));
new (&__jakt_uninit_enum.as.Number.number) (decltype(number))(move(number));
new (&__jakt_uninit_enum.as.Number.suffix) (decltype(suffix))(move(suffix));
new (&__jakt_uninit_enum.as.Number.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Identifier(ByteString name, Jakt::utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.Identifier.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Identifier.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Semicolon(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.as.Semicolon.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Colon(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
new (&__jakt_uninit_enum.as.Colon.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::ColonColon(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
new (&__jakt_uninit_enum.as.ColonColon.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LParen(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
new (&__jakt_uninit_enum.as.LParen.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RParen(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
new (&__jakt_uninit_enum.as.RParen.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LCurly(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
new (&__jakt_uninit_enum.as.LCurly.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RCurly(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
new (&__jakt_uninit_enum.as.RCurly.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LSquare(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
new (&__jakt_uninit_enum.as.LSquare.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RSquare(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
new (&__jakt_uninit_enum.as.RSquare.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PercentSign(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 14;
new (&__jakt_uninit_enum.as.PercentSign.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Plus(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 15;
new (&__jakt_uninit_enum.as.Plus.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Minus(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 16;
new (&__jakt_uninit_enum.as.Minus.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Equal(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 17;
new (&__jakt_uninit_enum.as.Equal.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PlusEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 18;
new (&__jakt_uninit_enum.as.PlusEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PlusPlus(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 19;
new (&__jakt_uninit_enum.as.PlusPlus.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::MinusEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 20;
new (&__jakt_uninit_enum.as.MinusEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::MinusMinus(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 21;
new (&__jakt_uninit_enum.as.MinusMinus.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::AsteriskEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 22;
new (&__jakt_uninit_enum.as.AsteriskEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::ForwardSlashEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 23;
new (&__jakt_uninit_enum.as.ForwardSlashEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PercentSignEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 24;
new (&__jakt_uninit_enum.as.PercentSignEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::NotEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 25;
new (&__jakt_uninit_enum.as.NotEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::DoubleEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 26;
new (&__jakt_uninit_enum.as.DoubleEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::GreaterThan(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 27;
new (&__jakt_uninit_enum.as.GreaterThan.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::GreaterThanOrEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 28;
new (&__jakt_uninit_enum.as.GreaterThanOrEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LessThan(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 29;
new (&__jakt_uninit_enum.as.LessThan.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LessThanOrEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 30;
new (&__jakt_uninit_enum.as.LessThanOrEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LeftArithmeticShift(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 31;
new (&__jakt_uninit_enum.as.LeftArithmeticShift.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LeftShift(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 32;
new (&__jakt_uninit_enum.as.LeftShift.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LeftShiftEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 33;
new (&__jakt_uninit_enum.as.LeftShiftEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RightShift(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 34;
new (&__jakt_uninit_enum.as.RightShift.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RightArithmeticShift(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 35;
new (&__jakt_uninit_enum.as.RightArithmeticShift.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RightShiftEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 36;
new (&__jakt_uninit_enum.as.RightShiftEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Asterisk(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 37;
new (&__jakt_uninit_enum.as.Asterisk.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Ampersand(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 38;
new (&__jakt_uninit_enum.as.Ampersand.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::AmpersandEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 39;
new (&__jakt_uninit_enum.as.AmpersandEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::AmpersandAmpersand(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 40;
new (&__jakt_uninit_enum.as.AmpersandAmpersand.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Pipe(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 41;
new (&__jakt_uninit_enum.as.Pipe.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PipeEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 42;
new (&__jakt_uninit_enum.as.PipeEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PipePipe(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 43;
new (&__jakt_uninit_enum.as.PipePipe.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Caret(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 44;
new (&__jakt_uninit_enum.as.Caret.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::CaretEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 45;
new (&__jakt_uninit_enum.as.CaretEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Dollar(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 46;
new (&__jakt_uninit_enum.as.Dollar.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Tilde(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 47;
new (&__jakt_uninit_enum.as.Tilde.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::ForwardSlash(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 48;
new (&__jakt_uninit_enum.as.ForwardSlash.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::ExclamationPoint(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 49;
new (&__jakt_uninit_enum.as.ExclamationPoint.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::QuestionMark(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 50;
new (&__jakt_uninit_enum.as.QuestionMark.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::QuestionMarkQuestionMark(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 51;
new (&__jakt_uninit_enum.as.QuestionMarkQuestionMark.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::QuestionMarkQuestionMarkEqual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 52;
new (&__jakt_uninit_enum.as.QuestionMarkQuestionMarkEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Comma(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 53;
new (&__jakt_uninit_enum.as.Comma.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Dot(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 54;
new (&__jakt_uninit_enum.as.Dot.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::DotDot(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 55;
new (&__jakt_uninit_enum.as.DotDot.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Eol(JaktInternal::Optional<ByteString> comment, Jakt::utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 56;
new (&__jakt_uninit_enum.as.Eol.comment) (decltype(comment))(move(comment));
new (&__jakt_uninit_enum.as.Eol.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Eof(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 57;
new (&__jakt_uninit_enum.as.Eof.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::FatArrow(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 58;
new (&__jakt_uninit_enum.as.FatArrow.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Arrow(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 59;
new (&__jakt_uninit_enum.as.Arrow.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::And(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 60;
new (&__jakt_uninit_enum.as.And.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Anon(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 61;
new (&__jakt_uninit_enum.as.Anon.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::As(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 62;
new (&__jakt_uninit_enum.as.As.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Boxed(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 63;
new (&__jakt_uninit_enum.as.Boxed.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Break(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 64;
new (&__jakt_uninit_enum.as.Break.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Catch(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 65;
new (&__jakt_uninit_enum.as.Catch.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Class(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 66;
new (&__jakt_uninit_enum.as.Class.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Continue(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 67;
new (&__jakt_uninit_enum.as.Continue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Cpp(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 68;
new (&__jakt_uninit_enum.as.Cpp.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Defer(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 69;
new (&__jakt_uninit_enum.as.Defer.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Destructor(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 70;
new (&__jakt_uninit_enum.as.Destructor.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Else(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 71;
new (&__jakt_uninit_enum.as.Else.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Enum(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 72;
new (&__jakt_uninit_enum.as.Enum.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Extern(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 73;
new (&__jakt_uninit_enum.as.Extern.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Export(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 74;
new (&__jakt_uninit_enum.as.Export.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::False(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 75;
new (&__jakt_uninit_enum.as.False.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::For(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 76;
new (&__jakt_uninit_enum.as.For.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Fn(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 77;
new (&__jakt_uninit_enum.as.Fn.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Comptime(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 78;
new (&__jakt_uninit_enum.as.Comptime.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::If(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 79;
new (&__jakt_uninit_enum.as.If.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Import(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 80;
new (&__jakt_uninit_enum.as.Import.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Relative(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 81;
new (&__jakt_uninit_enum.as.Relative.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::In(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 82;
new (&__jakt_uninit_enum.as.In.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Is(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 83;
new (&__jakt_uninit_enum.as.Is.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Let(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 84;
new (&__jakt_uninit_enum.as.Let.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Loop(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 85;
new (&__jakt_uninit_enum.as.Loop.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Match(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 86;
new (&__jakt_uninit_enum.as.Match.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Must(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 87;
new (&__jakt_uninit_enum.as.Must.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Mut(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 88;
new (&__jakt_uninit_enum.as.Mut.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Namespace(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 89;
new (&__jakt_uninit_enum.as.Namespace.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Not(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 90;
new (&__jakt_uninit_enum.as.Not.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Or(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 91;
new (&__jakt_uninit_enum.as.Or.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Override(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 92;
new (&__jakt_uninit_enum.as.Override.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Private(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 93;
new (&__jakt_uninit_enum.as.Private.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Public(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 94;
new (&__jakt_uninit_enum.as.Public.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Raw(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 95;
new (&__jakt_uninit_enum.as.Raw.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Reflect(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 96;
new (&__jakt_uninit_enum.as.Reflect.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Return(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 97;
new (&__jakt_uninit_enum.as.Return.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Restricted(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 98;
new (&__jakt_uninit_enum.as.Restricted.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Sizeof(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 99;
new (&__jakt_uninit_enum.as.Sizeof.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Struct(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 100;
new (&__jakt_uninit_enum.as.Struct.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::This(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 101;
new (&__jakt_uninit_enum.as.This.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Throw(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 102;
new (&__jakt_uninit_enum.as.Throw.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Throws(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 103;
new (&__jakt_uninit_enum.as.Throws.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::True(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 104;
new (&__jakt_uninit_enum.as.True.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Try(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 105;
new (&__jakt_uninit_enum.as.Try.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Unsafe(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 106;
new (&__jakt_uninit_enum.as.Unsafe.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Virtual(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 107;
new (&__jakt_uninit_enum.as.Virtual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Weak(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 108;
new (&__jakt_uninit_enum.as.Weak.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::While(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 109;
new (&__jakt_uninit_enum.as.While.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Yield(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 110;
new (&__jakt_uninit_enum.as.Yield.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Guard(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 111;
new (&__jakt_uninit_enum.as.Guard.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Implements(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 112;
new (&__jakt_uninit_enum.as.Implements.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Requires(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 113;
new (&__jakt_uninit_enum.as.Requires.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Trait(Jakt::utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 114;
new (&__jakt_uninit_enum.as.Trait.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Garbage(JaktInternal::Optional<ByteString> consumed, Jakt::utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 115;
new (&__jakt_uninit_enum.as.Garbage.consumed) (decltype(consumed))(move(consumed));
new (&__jakt_uninit_enum.as.Garbage.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
Token& Token::operator=(Token const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.quote) (decltype(this->as.SingleQuotedString.quote))(rhs.as.SingleQuotedString.quote);
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(rhs.as.SingleQuotedString.prefix);
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(rhs.as.SingleQuotedString.span);
break;
case 1 /* QuotedString */:
new (&this->as.QuotedString.quote) (decltype(this->as.QuotedString.quote))(rhs.as.QuotedString.quote);
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(rhs.as.QuotedString.span);
break;
case 2 /* Number */:
new (&this->as.Number.prefix) (decltype(this->as.Number.prefix))(rhs.as.Number.prefix);
new (&this->as.Number.number) (decltype(this->as.Number.number))(rhs.as.Number.number);
new (&this->as.Number.suffix) (decltype(this->as.Number.suffix))(rhs.as.Number.suffix);
new (&this->as.Number.span) (decltype(this->as.Number.span))(rhs.as.Number.span);
break;
case 3 /* Identifier */:
new (&this->as.Identifier.name) (decltype(this->as.Identifier.name))(rhs.as.Identifier.name);
new (&this->as.Identifier.span) (decltype(this->as.Identifier.span))(rhs.as.Identifier.span);
break;
case 4 /* Semicolon */:
new (&this->as.Semicolon.value) (decltype(this->as.Semicolon.value))(rhs.as.Semicolon.value);
break;
case 5 /* Colon */:
new (&this->as.Colon.value) (decltype(this->as.Colon.value))(rhs.as.Colon.value);
break;
case 6 /* ColonColon */:
new (&this->as.ColonColon.value) (decltype(this->as.ColonColon.value))(rhs.as.ColonColon.value);
break;
case 7 /* LParen */:
new (&this->as.LParen.value) (decltype(this->as.LParen.value))(rhs.as.LParen.value);
break;
case 8 /* RParen */:
new (&this->as.RParen.value) (decltype(this->as.RParen.value))(rhs.as.RParen.value);
break;
case 9 /* LCurly */:
new (&this->as.LCurly.value) (decltype(this->as.LCurly.value))(rhs.as.LCurly.value);
break;
case 10 /* RCurly */:
new (&this->as.RCurly.value) (decltype(this->as.RCurly.value))(rhs.as.RCurly.value);
break;
case 11 /* LSquare */:
new (&this->as.LSquare.value) (decltype(this->as.LSquare.value))(rhs.as.LSquare.value);
break;
case 12 /* RSquare */:
new (&this->as.RSquare.value) (decltype(this->as.RSquare.value))(rhs.as.RSquare.value);
break;
case 13 /* PercentSign */:
new (&this->as.PercentSign.value) (decltype(this->as.PercentSign.value))(rhs.as.PercentSign.value);
break;
case 14 /* Plus */:
new (&this->as.Plus.value) (decltype(this->as.Plus.value))(rhs.as.Plus.value);
break;
case 15 /* Minus */:
new (&this->as.Minus.value) (decltype(this->as.Minus.value))(rhs.as.Minus.value);
break;
case 16 /* Equal */:
new (&this->as.Equal.value) (decltype(this->as.Equal.value))(rhs.as.Equal.value);
break;
case 17 /* PlusEqual */:
new (&this->as.PlusEqual.value) (decltype(this->as.PlusEqual.value))(rhs.as.PlusEqual.value);
break;
case 18 /* PlusPlus */:
new (&this->as.PlusPlus.value) (decltype(this->as.PlusPlus.value))(rhs.as.PlusPlus.value);
break;
case 19 /* MinusEqual */:
new (&this->as.MinusEqual.value) (decltype(this->as.MinusEqual.value))(rhs.as.MinusEqual.value);
break;
case 20 /* MinusMinus */:
new (&this->as.MinusMinus.value) (decltype(this->as.MinusMinus.value))(rhs.as.MinusMinus.value);
break;
case 21 /* AsteriskEqual */:
new (&this->as.AsteriskEqual.value) (decltype(this->as.AsteriskEqual.value))(rhs.as.AsteriskEqual.value);
break;
case 22 /* ForwardSlashEqual */:
new (&this->as.ForwardSlashEqual.value) (decltype(this->as.ForwardSlashEqual.value))(rhs.as.ForwardSlashEqual.value);
break;
case 23 /* PercentSignEqual */:
new (&this->as.PercentSignEqual.value) (decltype(this->as.PercentSignEqual.value))(rhs.as.PercentSignEqual.value);
break;
case 24 /* NotEqual */:
new (&this->as.NotEqual.value) (decltype(this->as.NotEqual.value))(rhs.as.NotEqual.value);
break;
case 25 /* DoubleEqual */:
new (&this->as.DoubleEqual.value) (decltype(this->as.DoubleEqual.value))(rhs.as.DoubleEqual.value);
break;
case 26 /* GreaterThan */:
new (&this->as.GreaterThan.value) (decltype(this->as.GreaterThan.value))(rhs.as.GreaterThan.value);
break;
case 27 /* GreaterThanOrEqual */:
new (&this->as.GreaterThanOrEqual.value) (decltype(this->as.GreaterThanOrEqual.value))(rhs.as.GreaterThanOrEqual.value);
break;
case 28 /* LessThan */:
new (&this->as.LessThan.value) (decltype(this->as.LessThan.value))(rhs.as.LessThan.value);
break;
case 29 /* LessThanOrEqual */:
new (&this->as.LessThanOrEqual.value) (decltype(this->as.LessThanOrEqual.value))(rhs.as.LessThanOrEqual.value);
break;
case 30 /* LeftArithmeticShift */:
new (&this->as.LeftArithmeticShift.value) (decltype(this->as.LeftArithmeticShift.value))(rhs.as.LeftArithmeticShift.value);
break;
case 31 /* LeftShift */:
new (&this->as.LeftShift.value) (decltype(this->as.LeftShift.value))(rhs.as.LeftShift.value);
break;
case 32 /* LeftShiftEqual */:
new (&this->as.LeftShiftEqual.value) (decltype(this->as.LeftShiftEqual.value))(rhs.as.LeftShiftEqual.value);
break;
case 33 /* RightShift */:
new (&this->as.RightShift.value) (decltype(this->as.RightShift.value))(rhs.as.RightShift.value);
break;
case 34 /* RightArithmeticShift */:
new (&this->as.RightArithmeticShift.value) (decltype(this->as.RightArithmeticShift.value))(rhs.as.RightArithmeticShift.value);
break;
case 35 /* RightShiftEqual */:
new (&this->as.RightShiftEqual.value) (decltype(this->as.RightShiftEqual.value))(rhs.as.RightShiftEqual.value);
break;
case 36 /* Asterisk */:
new (&this->as.Asterisk.value) (decltype(this->as.Asterisk.value))(rhs.as.Asterisk.value);
break;
case 37 /* Ampersand */:
new (&this->as.Ampersand.value) (decltype(this->as.Ampersand.value))(rhs.as.Ampersand.value);
break;
case 38 /* AmpersandEqual */:
new (&this->as.AmpersandEqual.value) (decltype(this->as.AmpersandEqual.value))(rhs.as.AmpersandEqual.value);
break;
case 39 /* AmpersandAmpersand */:
new (&this->as.AmpersandAmpersand.value) (decltype(this->as.AmpersandAmpersand.value))(rhs.as.AmpersandAmpersand.value);
break;
case 40 /* Pipe */:
new (&this->as.Pipe.value) (decltype(this->as.Pipe.value))(rhs.as.Pipe.value);
break;
case 41 /* PipeEqual */:
new (&this->as.PipeEqual.value) (decltype(this->as.PipeEqual.value))(rhs.as.PipeEqual.value);
break;
case 42 /* PipePipe */:
new (&this->as.PipePipe.value) (decltype(this->as.PipePipe.value))(rhs.as.PipePipe.value);
break;
case 43 /* Caret */:
new (&this->as.Caret.value) (decltype(this->as.Caret.value))(rhs.as.Caret.value);
break;
case 44 /* CaretEqual */:
new (&this->as.CaretEqual.value) (decltype(this->as.CaretEqual.value))(rhs.as.CaretEqual.value);
break;
case 45 /* Dollar */:
new (&this->as.Dollar.value) (decltype(this->as.Dollar.value))(rhs.as.Dollar.value);
break;
case 46 /* Tilde */:
new (&this->as.Tilde.value) (decltype(this->as.Tilde.value))(rhs.as.Tilde.value);
break;
case 47 /* ForwardSlash */:
new (&this->as.ForwardSlash.value) (decltype(this->as.ForwardSlash.value))(rhs.as.ForwardSlash.value);
break;
case 48 /* ExclamationPoint */:
new (&this->as.ExclamationPoint.value) (decltype(this->as.ExclamationPoint.value))(rhs.as.ExclamationPoint.value);
break;
case 49 /* QuestionMark */:
new (&this->as.QuestionMark.value) (decltype(this->as.QuestionMark.value))(rhs.as.QuestionMark.value);
break;
case 50 /* QuestionMarkQuestionMark */:
new (&this->as.QuestionMarkQuestionMark.value) (decltype(this->as.QuestionMarkQuestionMark.value))(rhs.as.QuestionMarkQuestionMark.value);
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
new (&this->as.QuestionMarkQuestionMarkEqual.value) (decltype(this->as.QuestionMarkQuestionMarkEqual.value))(rhs.as.QuestionMarkQuestionMarkEqual.value);
break;
case 52 /* Comma */:
new (&this->as.Comma.value) (decltype(this->as.Comma.value))(rhs.as.Comma.value);
break;
case 53 /* Dot */:
new (&this->as.Dot.value) (decltype(this->as.Dot.value))(rhs.as.Dot.value);
break;
case 54 /* DotDot */:
new (&this->as.DotDot.value) (decltype(this->as.DotDot.value))(rhs.as.DotDot.value);
break;
case 55 /* Eol */:
new (&this->as.Eol.comment) (decltype(this->as.Eol.comment))(rhs.as.Eol.comment);
new (&this->as.Eol.span) (decltype(this->as.Eol.span))(rhs.as.Eol.span);
break;
case 56 /* Eof */:
new (&this->as.Eof.value) (decltype(this->as.Eof.value))(rhs.as.Eof.value);
break;
case 57 /* FatArrow */:
new (&this->as.FatArrow.value) (decltype(this->as.FatArrow.value))(rhs.as.FatArrow.value);
break;
case 58 /* Arrow */:
new (&this->as.Arrow.value) (decltype(this->as.Arrow.value))(rhs.as.Arrow.value);
break;
case 59 /* And */:
new (&this->as.And.value) (decltype(this->as.And.value))(rhs.as.And.value);
break;
case 60 /* Anon */:
new (&this->as.Anon.value) (decltype(this->as.Anon.value))(rhs.as.Anon.value);
break;
case 61 /* As */:
new (&this->as.As.value) (decltype(this->as.As.value))(rhs.as.As.value);
break;
case 62 /* Boxed */:
new (&this->as.Boxed.value) (decltype(this->as.Boxed.value))(rhs.as.Boxed.value);
break;
case 63 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(rhs.as.Break.value);
break;
case 64 /* Catch */:
new (&this->as.Catch.value) (decltype(this->as.Catch.value))(rhs.as.Catch.value);
break;
case 65 /* Class */:
new (&this->as.Class.value) (decltype(this->as.Class.value))(rhs.as.Class.value);
break;
case 66 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(rhs.as.Continue.value);
break;
case 67 /* Cpp */:
new (&this->as.Cpp.value) (decltype(this->as.Cpp.value))(rhs.as.Cpp.value);
break;
case 68 /* Defer */:
new (&this->as.Defer.value) (decltype(this->as.Defer.value))(rhs.as.Defer.value);
break;
case 69 /* Destructor */:
new (&this->as.Destructor.value) (decltype(this->as.Destructor.value))(rhs.as.Destructor.value);
break;
case 70 /* Else */:
new (&this->as.Else.value) (decltype(this->as.Else.value))(rhs.as.Else.value);
break;
case 71 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 72 /* Extern */:
new (&this->as.Extern.value) (decltype(this->as.Extern.value))(rhs.as.Extern.value);
break;
case 73 /* Export */:
new (&this->as.Export.value) (decltype(this->as.Export.value))(rhs.as.Export.value);
break;
case 74 /* False */:
new (&this->as.False.value) (decltype(this->as.False.value))(rhs.as.False.value);
break;
case 75 /* For */:
new (&this->as.For.value) (decltype(this->as.For.value))(rhs.as.For.value);
break;
case 76 /* Fn */:
new (&this->as.Fn.value) (decltype(this->as.Fn.value))(rhs.as.Fn.value);
break;
case 77 /* Comptime */:
new (&this->as.Comptime.value) (decltype(this->as.Comptime.value))(rhs.as.Comptime.value);
break;
case 78 /* If */:
new (&this->as.If.value) (decltype(this->as.If.value))(rhs.as.If.value);
break;
case 79 /* Import */:
new (&this->as.Import.value) (decltype(this->as.Import.value))(rhs.as.Import.value);
break;
case 80 /* Relative */:
new (&this->as.Relative.value) (decltype(this->as.Relative.value))(rhs.as.Relative.value);
break;
case 81 /* In */:
new (&this->as.In.value) (decltype(this->as.In.value))(rhs.as.In.value);
break;
case 82 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(rhs.as.Is.value);
break;
case 83 /* Let */:
new (&this->as.Let.value) (decltype(this->as.Let.value))(rhs.as.Let.value);
break;
case 84 /* Loop */:
new (&this->as.Loop.value) (decltype(this->as.Loop.value))(rhs.as.Loop.value);
break;
case 85 /* Match */:
new (&this->as.Match.value) (decltype(this->as.Match.value))(rhs.as.Match.value);
break;
case 86 /* Must */:
new (&this->as.Must.value) (decltype(this->as.Must.value))(rhs.as.Must.value);
break;
case 87 /* Mut */:
new (&this->as.Mut.value) (decltype(this->as.Mut.value))(rhs.as.Mut.value);
break;
case 88 /* Namespace */:
new (&this->as.Namespace.value) (decltype(this->as.Namespace.value))(rhs.as.Namespace.value);
break;
case 89 /* Not */:
new (&this->as.Not.value) (decltype(this->as.Not.value))(rhs.as.Not.value);
break;
case 90 /* Or */:
new (&this->as.Or.value) (decltype(this->as.Or.value))(rhs.as.Or.value);
break;
case 91 /* Override */:
new (&this->as.Override.value) (decltype(this->as.Override.value))(rhs.as.Override.value);
break;
case 92 /* Private */:
new (&this->as.Private.value) (decltype(this->as.Private.value))(rhs.as.Private.value);
break;
case 93 /* Public */:
new (&this->as.Public.value) (decltype(this->as.Public.value))(rhs.as.Public.value);
break;
case 94 /* Raw */:
new (&this->as.Raw.value) (decltype(this->as.Raw.value))(rhs.as.Raw.value);
break;
case 95 /* Reflect */:
new (&this->as.Reflect.value) (decltype(this->as.Reflect.value))(rhs.as.Reflect.value);
break;
case 96 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(rhs.as.Return.value);
break;
case 97 /* Restricted */:
new (&this->as.Restricted.value) (decltype(this->as.Restricted.value))(rhs.as.Restricted.value);
break;
case 98 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(rhs.as.Sizeof.value);
break;
case 99 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 100 /* This */:
new (&this->as.This.value) (decltype(this->as.This.value))(rhs.as.This.value);
break;
case 101 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(rhs.as.Throw.value);
break;
case 102 /* Throws */:
new (&this->as.Throws.value) (decltype(this->as.Throws.value))(rhs.as.Throws.value);
break;
case 103 /* True */:
new (&this->as.True.value) (decltype(this->as.True.value))(rhs.as.True.value);
break;
case 104 /* Try */:
new (&this->as.Try.value) (decltype(this->as.Try.value))(rhs.as.Try.value);
break;
case 105 /* Unsafe */:
new (&this->as.Unsafe.value) (decltype(this->as.Unsafe.value))(rhs.as.Unsafe.value);
break;
case 106 /* Virtual */:
new (&this->as.Virtual.value) (decltype(this->as.Virtual.value))(rhs.as.Virtual.value);
break;
case 107 /* Weak */:
new (&this->as.Weak.value) (decltype(this->as.Weak.value))(rhs.as.Weak.value);
break;
case 108 /* While */:
new (&this->as.While.value) (decltype(this->as.While.value))(rhs.as.While.value);
break;
case 109 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(rhs.as.Yield.value);
break;
case 110 /* Guard */:
new (&this->as.Guard.value) (decltype(this->as.Guard.value))(rhs.as.Guard.value);
break;
case 111 /* Implements */:
new (&this->as.Implements.value) (decltype(this->as.Implements.value))(rhs.as.Implements.value);
break;
case 112 /* Requires */:
new (&this->as.Requires.value) (decltype(this->as.Requires.value))(rhs.as.Requires.value);
break;
case 113 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
case 114 /* Garbage */:
new (&this->as.Garbage.consumed) (decltype(this->as.Garbage.consumed))(rhs.as.Garbage.consumed);
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(rhs.as.Garbage.span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
this->as.SingleQuotedString.quote = rhs.as.SingleQuotedString.quote;
this->as.SingleQuotedString.prefix = rhs.as.SingleQuotedString.prefix;
this->as.SingleQuotedString.span = rhs.as.SingleQuotedString.span;
break;
case 1 /* QuotedString */:
this->as.QuotedString.quote = rhs.as.QuotedString.quote;
this->as.QuotedString.span = rhs.as.QuotedString.span;
break;
case 2 /* Number */:
this->as.Number.prefix = rhs.as.Number.prefix;
this->as.Number.number = rhs.as.Number.number;
this->as.Number.suffix = rhs.as.Number.suffix;
this->as.Number.span = rhs.as.Number.span;
break;
case 3 /* Identifier */:
this->as.Identifier.name = rhs.as.Identifier.name;
this->as.Identifier.span = rhs.as.Identifier.span;
break;
case 4 /* Semicolon */:
this->as.Semicolon.value = rhs.as.Semicolon.value;
break;
case 5 /* Colon */:
this->as.Colon.value = rhs.as.Colon.value;
break;
case 6 /* ColonColon */:
this->as.ColonColon.value = rhs.as.ColonColon.value;
break;
case 7 /* LParen */:
this->as.LParen.value = rhs.as.LParen.value;
break;
case 8 /* RParen */:
this->as.RParen.value = rhs.as.RParen.value;
break;
case 9 /* LCurly */:
this->as.LCurly.value = rhs.as.LCurly.value;
break;
case 10 /* RCurly */:
this->as.RCurly.value = rhs.as.RCurly.value;
break;
case 11 /* LSquare */:
this->as.LSquare.value = rhs.as.LSquare.value;
break;
case 12 /* RSquare */:
this->as.RSquare.value = rhs.as.RSquare.value;
break;
case 13 /* PercentSign */:
this->as.PercentSign.value = rhs.as.PercentSign.value;
break;
case 14 /* Plus */:
this->as.Plus.value = rhs.as.Plus.value;
break;
case 15 /* Minus */:
this->as.Minus.value = rhs.as.Minus.value;
break;
case 16 /* Equal */:
this->as.Equal.value = rhs.as.Equal.value;
break;
case 17 /* PlusEqual */:
this->as.PlusEqual.value = rhs.as.PlusEqual.value;
break;
case 18 /* PlusPlus */:
this->as.PlusPlus.value = rhs.as.PlusPlus.value;
break;
case 19 /* MinusEqual */:
this->as.MinusEqual.value = rhs.as.MinusEqual.value;
break;
case 20 /* MinusMinus */:
this->as.MinusMinus.value = rhs.as.MinusMinus.value;
break;
case 21 /* AsteriskEqual */:
this->as.AsteriskEqual.value = rhs.as.AsteriskEqual.value;
break;
case 22 /* ForwardSlashEqual */:
this->as.ForwardSlashEqual.value = rhs.as.ForwardSlashEqual.value;
break;
case 23 /* PercentSignEqual */:
this->as.PercentSignEqual.value = rhs.as.PercentSignEqual.value;
break;
case 24 /* NotEqual */:
this->as.NotEqual.value = rhs.as.NotEqual.value;
break;
case 25 /* DoubleEqual */:
this->as.DoubleEqual.value = rhs.as.DoubleEqual.value;
break;
case 26 /* GreaterThan */:
this->as.GreaterThan.value = rhs.as.GreaterThan.value;
break;
case 27 /* GreaterThanOrEqual */:
this->as.GreaterThanOrEqual.value = rhs.as.GreaterThanOrEqual.value;
break;
case 28 /* LessThan */:
this->as.LessThan.value = rhs.as.LessThan.value;
break;
case 29 /* LessThanOrEqual */:
this->as.LessThanOrEqual.value = rhs.as.LessThanOrEqual.value;
break;
case 30 /* LeftArithmeticShift */:
this->as.LeftArithmeticShift.value = rhs.as.LeftArithmeticShift.value;
break;
case 31 /* LeftShift */:
this->as.LeftShift.value = rhs.as.LeftShift.value;
break;
case 32 /* LeftShiftEqual */:
this->as.LeftShiftEqual.value = rhs.as.LeftShiftEqual.value;
break;
case 33 /* RightShift */:
this->as.RightShift.value = rhs.as.RightShift.value;
break;
case 34 /* RightArithmeticShift */:
this->as.RightArithmeticShift.value = rhs.as.RightArithmeticShift.value;
break;
case 35 /* RightShiftEqual */:
this->as.RightShiftEqual.value = rhs.as.RightShiftEqual.value;
break;
case 36 /* Asterisk */:
this->as.Asterisk.value = rhs.as.Asterisk.value;
break;
case 37 /* Ampersand */:
this->as.Ampersand.value = rhs.as.Ampersand.value;
break;
case 38 /* AmpersandEqual */:
this->as.AmpersandEqual.value = rhs.as.AmpersandEqual.value;
break;
case 39 /* AmpersandAmpersand */:
this->as.AmpersandAmpersand.value = rhs.as.AmpersandAmpersand.value;
break;
case 40 /* Pipe */:
this->as.Pipe.value = rhs.as.Pipe.value;
break;
case 41 /* PipeEqual */:
this->as.PipeEqual.value = rhs.as.PipeEqual.value;
break;
case 42 /* PipePipe */:
this->as.PipePipe.value = rhs.as.PipePipe.value;
break;
case 43 /* Caret */:
this->as.Caret.value = rhs.as.Caret.value;
break;
case 44 /* CaretEqual */:
this->as.CaretEqual.value = rhs.as.CaretEqual.value;
break;
case 45 /* Dollar */:
this->as.Dollar.value = rhs.as.Dollar.value;
break;
case 46 /* Tilde */:
this->as.Tilde.value = rhs.as.Tilde.value;
break;
case 47 /* ForwardSlash */:
this->as.ForwardSlash.value = rhs.as.ForwardSlash.value;
break;
case 48 /* ExclamationPoint */:
this->as.ExclamationPoint.value = rhs.as.ExclamationPoint.value;
break;
case 49 /* QuestionMark */:
this->as.QuestionMark.value = rhs.as.QuestionMark.value;
break;
case 50 /* QuestionMarkQuestionMark */:
this->as.QuestionMarkQuestionMark.value = rhs.as.QuestionMarkQuestionMark.value;
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
this->as.QuestionMarkQuestionMarkEqual.value = rhs.as.QuestionMarkQuestionMarkEqual.value;
break;
case 52 /* Comma */:
this->as.Comma.value = rhs.as.Comma.value;
break;
case 53 /* Dot */:
this->as.Dot.value = rhs.as.Dot.value;
break;
case 54 /* DotDot */:
this->as.DotDot.value = rhs.as.DotDot.value;
break;
case 55 /* Eol */:
this->as.Eol.comment = rhs.as.Eol.comment;
this->as.Eol.span = rhs.as.Eol.span;
break;
case 56 /* Eof */:
this->as.Eof.value = rhs.as.Eof.value;
break;
case 57 /* FatArrow */:
this->as.FatArrow.value = rhs.as.FatArrow.value;
break;
case 58 /* Arrow */:
this->as.Arrow.value = rhs.as.Arrow.value;
break;
case 59 /* And */:
this->as.And.value = rhs.as.And.value;
break;
case 60 /* Anon */:
this->as.Anon.value = rhs.as.Anon.value;
break;
case 61 /* As */:
this->as.As.value = rhs.as.As.value;
break;
case 62 /* Boxed */:
this->as.Boxed.value = rhs.as.Boxed.value;
break;
case 63 /* Break */:
this->as.Break.value = rhs.as.Break.value;
break;
case 64 /* Catch */:
this->as.Catch.value = rhs.as.Catch.value;
break;
case 65 /* Class */:
this->as.Class.value = rhs.as.Class.value;
break;
case 66 /* Continue */:
this->as.Continue.value = rhs.as.Continue.value;
break;
case 67 /* Cpp */:
this->as.Cpp.value = rhs.as.Cpp.value;
break;
case 68 /* Defer */:
this->as.Defer.value = rhs.as.Defer.value;
break;
case 69 /* Destructor */:
this->as.Destructor.value = rhs.as.Destructor.value;
break;
case 70 /* Else */:
this->as.Else.value = rhs.as.Else.value;
break;
case 71 /* Enum */:
this->as.Enum.value = rhs.as.Enum.value;
break;
case 72 /* Extern */:
this->as.Extern.value = rhs.as.Extern.value;
break;
case 73 /* Export */:
this->as.Export.value = rhs.as.Export.value;
break;
case 74 /* False */:
this->as.False.value = rhs.as.False.value;
break;
case 75 /* For */:
this->as.For.value = rhs.as.For.value;
break;
case 76 /* Fn */:
this->as.Fn.value = rhs.as.Fn.value;
break;
case 77 /* Comptime */:
this->as.Comptime.value = rhs.as.Comptime.value;
break;
case 78 /* If */:
this->as.If.value = rhs.as.If.value;
break;
case 79 /* Import */:
this->as.Import.value = rhs.as.Import.value;
break;
case 80 /* Relative */:
this->as.Relative.value = rhs.as.Relative.value;
break;
case 81 /* In */:
this->as.In.value = rhs.as.In.value;
break;
case 82 /* Is */:
this->as.Is.value = rhs.as.Is.value;
break;
case 83 /* Let */:
this->as.Let.value = rhs.as.Let.value;
break;
case 84 /* Loop */:
this->as.Loop.value = rhs.as.Loop.value;
break;
case 85 /* Match */:
this->as.Match.value = rhs.as.Match.value;
break;
case 86 /* Must */:
this->as.Must.value = rhs.as.Must.value;
break;
case 87 /* Mut */:
this->as.Mut.value = rhs.as.Mut.value;
break;
case 88 /* Namespace */:
this->as.Namespace.value = rhs.as.Namespace.value;
break;
case 89 /* Not */:
this->as.Not.value = rhs.as.Not.value;
break;
case 90 /* Or */:
this->as.Or.value = rhs.as.Or.value;
break;
case 91 /* Override */:
this->as.Override.value = rhs.as.Override.value;
break;
case 92 /* Private */:
this->as.Private.value = rhs.as.Private.value;
break;
case 93 /* Public */:
this->as.Public.value = rhs.as.Public.value;
break;
case 94 /* Raw */:
this->as.Raw.value = rhs.as.Raw.value;
break;
case 95 /* Reflect */:
this->as.Reflect.value = rhs.as.Reflect.value;
break;
case 96 /* Return */:
this->as.Return.value = rhs.as.Return.value;
break;
case 97 /* Restricted */:
this->as.Restricted.value = rhs.as.Restricted.value;
break;
case 98 /* Sizeof */:
this->as.Sizeof.value = rhs.as.Sizeof.value;
break;
case 99 /* Struct */:
this->as.Struct.value = rhs.as.Struct.value;
break;
case 100 /* This */:
this->as.This.value = rhs.as.This.value;
break;
case 101 /* Throw */:
this->as.Throw.value = rhs.as.Throw.value;
break;
case 102 /* Throws */:
this->as.Throws.value = rhs.as.Throws.value;
break;
case 103 /* True */:
this->as.True.value = rhs.as.True.value;
break;
case 104 /* Try */:
this->as.Try.value = rhs.as.Try.value;
break;
case 105 /* Unsafe */:
this->as.Unsafe.value = rhs.as.Unsafe.value;
break;
case 106 /* Virtual */:
this->as.Virtual.value = rhs.as.Virtual.value;
break;
case 107 /* Weak */:
this->as.Weak.value = rhs.as.Weak.value;
break;
case 108 /* While */:
this->as.While.value = rhs.as.While.value;
break;
case 109 /* Yield */:
this->as.Yield.value = rhs.as.Yield.value;
break;
case 110 /* Guard */:
this->as.Guard.value = rhs.as.Guard.value;
break;
case 111 /* Implements */:
this->as.Implements.value = rhs.as.Implements.value;
break;
case 112 /* Requires */:
this->as.Requires.value = rhs.as.Requires.value;
break;
case 113 /* Trait */:
this->as.Trait.value = rhs.as.Trait.value;
break;
case 114 /* Garbage */:
this->as.Garbage.consumed = rhs.as.Garbage.consumed;
this->as.Garbage.span = rhs.as.Garbage.span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Token::Token(Token const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.quote) (decltype(this->as.SingleQuotedString.quote))(rhs.as.SingleQuotedString.quote);
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(rhs.as.SingleQuotedString.prefix);
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(rhs.as.SingleQuotedString.span);
break;
case 1 /* QuotedString */:
new (&this->as.QuotedString.quote) (decltype(this->as.QuotedString.quote))(rhs.as.QuotedString.quote);
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(rhs.as.QuotedString.span);
break;
case 2 /* Number */:
new (&this->as.Number.prefix) (decltype(this->as.Number.prefix))(rhs.as.Number.prefix);
new (&this->as.Number.number) (decltype(this->as.Number.number))(rhs.as.Number.number);
new (&this->as.Number.suffix) (decltype(this->as.Number.suffix))(rhs.as.Number.suffix);
new (&this->as.Number.span) (decltype(this->as.Number.span))(rhs.as.Number.span);
break;
case 3 /* Identifier */:
new (&this->as.Identifier.name) (decltype(this->as.Identifier.name))(rhs.as.Identifier.name);
new (&this->as.Identifier.span) (decltype(this->as.Identifier.span))(rhs.as.Identifier.span);
break;
case 4 /* Semicolon */:
new (&this->as.Semicolon.value) (decltype(this->as.Semicolon.value))(rhs.as.Semicolon.value);
break;
case 5 /* Colon */:
new (&this->as.Colon.value) (decltype(this->as.Colon.value))(rhs.as.Colon.value);
break;
case 6 /* ColonColon */:
new (&this->as.ColonColon.value) (decltype(this->as.ColonColon.value))(rhs.as.ColonColon.value);
break;
case 7 /* LParen */:
new (&this->as.LParen.value) (decltype(this->as.LParen.value))(rhs.as.LParen.value);
break;
case 8 /* RParen */:
new (&this->as.RParen.value) (decltype(this->as.RParen.value))(rhs.as.RParen.value);
break;
case 9 /* LCurly */:
new (&this->as.LCurly.value) (decltype(this->as.LCurly.value))(rhs.as.LCurly.value);
break;
case 10 /* RCurly */:
new (&this->as.RCurly.value) (decltype(this->as.RCurly.value))(rhs.as.RCurly.value);
break;
case 11 /* LSquare */:
new (&this->as.LSquare.value) (decltype(this->as.LSquare.value))(rhs.as.LSquare.value);
break;
case 12 /* RSquare */:
new (&this->as.RSquare.value) (decltype(this->as.RSquare.value))(rhs.as.RSquare.value);
break;
case 13 /* PercentSign */:
new (&this->as.PercentSign.value) (decltype(this->as.PercentSign.value))(rhs.as.PercentSign.value);
break;
case 14 /* Plus */:
new (&this->as.Plus.value) (decltype(this->as.Plus.value))(rhs.as.Plus.value);
break;
case 15 /* Minus */:
new (&this->as.Minus.value) (decltype(this->as.Minus.value))(rhs.as.Minus.value);
break;
case 16 /* Equal */:
new (&this->as.Equal.value) (decltype(this->as.Equal.value))(rhs.as.Equal.value);
break;
case 17 /* PlusEqual */:
new (&this->as.PlusEqual.value) (decltype(this->as.PlusEqual.value))(rhs.as.PlusEqual.value);
break;
case 18 /* PlusPlus */:
new (&this->as.PlusPlus.value) (decltype(this->as.PlusPlus.value))(rhs.as.PlusPlus.value);
break;
case 19 /* MinusEqual */:
new (&this->as.MinusEqual.value) (decltype(this->as.MinusEqual.value))(rhs.as.MinusEqual.value);
break;
case 20 /* MinusMinus */:
new (&this->as.MinusMinus.value) (decltype(this->as.MinusMinus.value))(rhs.as.MinusMinus.value);
break;
case 21 /* AsteriskEqual */:
new (&this->as.AsteriskEqual.value) (decltype(this->as.AsteriskEqual.value))(rhs.as.AsteriskEqual.value);
break;
case 22 /* ForwardSlashEqual */:
new (&this->as.ForwardSlashEqual.value) (decltype(this->as.ForwardSlashEqual.value))(rhs.as.ForwardSlashEqual.value);
break;
case 23 /* PercentSignEqual */:
new (&this->as.PercentSignEqual.value) (decltype(this->as.PercentSignEqual.value))(rhs.as.PercentSignEqual.value);
break;
case 24 /* NotEqual */:
new (&this->as.NotEqual.value) (decltype(this->as.NotEqual.value))(rhs.as.NotEqual.value);
break;
case 25 /* DoubleEqual */:
new (&this->as.DoubleEqual.value) (decltype(this->as.DoubleEqual.value))(rhs.as.DoubleEqual.value);
break;
case 26 /* GreaterThan */:
new (&this->as.GreaterThan.value) (decltype(this->as.GreaterThan.value))(rhs.as.GreaterThan.value);
break;
case 27 /* GreaterThanOrEqual */:
new (&this->as.GreaterThanOrEqual.value) (decltype(this->as.GreaterThanOrEqual.value))(rhs.as.GreaterThanOrEqual.value);
break;
case 28 /* LessThan */:
new (&this->as.LessThan.value) (decltype(this->as.LessThan.value))(rhs.as.LessThan.value);
break;
case 29 /* LessThanOrEqual */:
new (&this->as.LessThanOrEqual.value) (decltype(this->as.LessThanOrEqual.value))(rhs.as.LessThanOrEqual.value);
break;
case 30 /* LeftArithmeticShift */:
new (&this->as.LeftArithmeticShift.value) (decltype(this->as.LeftArithmeticShift.value))(rhs.as.LeftArithmeticShift.value);
break;
case 31 /* LeftShift */:
new (&this->as.LeftShift.value) (decltype(this->as.LeftShift.value))(rhs.as.LeftShift.value);
break;
case 32 /* LeftShiftEqual */:
new (&this->as.LeftShiftEqual.value) (decltype(this->as.LeftShiftEqual.value))(rhs.as.LeftShiftEqual.value);
break;
case 33 /* RightShift */:
new (&this->as.RightShift.value) (decltype(this->as.RightShift.value))(rhs.as.RightShift.value);
break;
case 34 /* RightArithmeticShift */:
new (&this->as.RightArithmeticShift.value) (decltype(this->as.RightArithmeticShift.value))(rhs.as.RightArithmeticShift.value);
break;
case 35 /* RightShiftEqual */:
new (&this->as.RightShiftEqual.value) (decltype(this->as.RightShiftEqual.value))(rhs.as.RightShiftEqual.value);
break;
case 36 /* Asterisk */:
new (&this->as.Asterisk.value) (decltype(this->as.Asterisk.value))(rhs.as.Asterisk.value);
break;
case 37 /* Ampersand */:
new (&this->as.Ampersand.value) (decltype(this->as.Ampersand.value))(rhs.as.Ampersand.value);
break;
case 38 /* AmpersandEqual */:
new (&this->as.AmpersandEqual.value) (decltype(this->as.AmpersandEqual.value))(rhs.as.AmpersandEqual.value);
break;
case 39 /* AmpersandAmpersand */:
new (&this->as.AmpersandAmpersand.value) (decltype(this->as.AmpersandAmpersand.value))(rhs.as.AmpersandAmpersand.value);
break;
case 40 /* Pipe */:
new (&this->as.Pipe.value) (decltype(this->as.Pipe.value))(rhs.as.Pipe.value);
break;
case 41 /* PipeEqual */:
new (&this->as.PipeEqual.value) (decltype(this->as.PipeEqual.value))(rhs.as.PipeEqual.value);
break;
case 42 /* PipePipe */:
new (&this->as.PipePipe.value) (decltype(this->as.PipePipe.value))(rhs.as.PipePipe.value);
break;
case 43 /* Caret */:
new (&this->as.Caret.value) (decltype(this->as.Caret.value))(rhs.as.Caret.value);
break;
case 44 /* CaretEqual */:
new (&this->as.CaretEqual.value) (decltype(this->as.CaretEqual.value))(rhs.as.CaretEqual.value);
break;
case 45 /* Dollar */:
new (&this->as.Dollar.value) (decltype(this->as.Dollar.value))(rhs.as.Dollar.value);
break;
case 46 /* Tilde */:
new (&this->as.Tilde.value) (decltype(this->as.Tilde.value))(rhs.as.Tilde.value);
break;
case 47 /* ForwardSlash */:
new (&this->as.ForwardSlash.value) (decltype(this->as.ForwardSlash.value))(rhs.as.ForwardSlash.value);
break;
case 48 /* ExclamationPoint */:
new (&this->as.ExclamationPoint.value) (decltype(this->as.ExclamationPoint.value))(rhs.as.ExclamationPoint.value);
break;
case 49 /* QuestionMark */:
new (&this->as.QuestionMark.value) (decltype(this->as.QuestionMark.value))(rhs.as.QuestionMark.value);
break;
case 50 /* QuestionMarkQuestionMark */:
new (&this->as.QuestionMarkQuestionMark.value) (decltype(this->as.QuestionMarkQuestionMark.value))(rhs.as.QuestionMarkQuestionMark.value);
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
new (&this->as.QuestionMarkQuestionMarkEqual.value) (decltype(this->as.QuestionMarkQuestionMarkEqual.value))(rhs.as.QuestionMarkQuestionMarkEqual.value);
break;
case 52 /* Comma */:
new (&this->as.Comma.value) (decltype(this->as.Comma.value))(rhs.as.Comma.value);
break;
case 53 /* Dot */:
new (&this->as.Dot.value) (decltype(this->as.Dot.value))(rhs.as.Dot.value);
break;
case 54 /* DotDot */:
new (&this->as.DotDot.value) (decltype(this->as.DotDot.value))(rhs.as.DotDot.value);
break;
case 55 /* Eol */:
new (&this->as.Eol.comment) (decltype(this->as.Eol.comment))(rhs.as.Eol.comment);
new (&this->as.Eol.span) (decltype(this->as.Eol.span))(rhs.as.Eol.span);
break;
case 56 /* Eof */:
new (&this->as.Eof.value) (decltype(this->as.Eof.value))(rhs.as.Eof.value);
break;
case 57 /* FatArrow */:
new (&this->as.FatArrow.value) (decltype(this->as.FatArrow.value))(rhs.as.FatArrow.value);
break;
case 58 /* Arrow */:
new (&this->as.Arrow.value) (decltype(this->as.Arrow.value))(rhs.as.Arrow.value);
break;
case 59 /* And */:
new (&this->as.And.value) (decltype(this->as.And.value))(rhs.as.And.value);
break;
case 60 /* Anon */:
new (&this->as.Anon.value) (decltype(this->as.Anon.value))(rhs.as.Anon.value);
break;
case 61 /* As */:
new (&this->as.As.value) (decltype(this->as.As.value))(rhs.as.As.value);
break;
case 62 /* Boxed */:
new (&this->as.Boxed.value) (decltype(this->as.Boxed.value))(rhs.as.Boxed.value);
break;
case 63 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(rhs.as.Break.value);
break;
case 64 /* Catch */:
new (&this->as.Catch.value) (decltype(this->as.Catch.value))(rhs.as.Catch.value);
break;
case 65 /* Class */:
new (&this->as.Class.value) (decltype(this->as.Class.value))(rhs.as.Class.value);
break;
case 66 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(rhs.as.Continue.value);
break;
case 67 /* Cpp */:
new (&this->as.Cpp.value) (decltype(this->as.Cpp.value))(rhs.as.Cpp.value);
break;
case 68 /* Defer */:
new (&this->as.Defer.value) (decltype(this->as.Defer.value))(rhs.as.Defer.value);
break;
case 69 /* Destructor */:
new (&this->as.Destructor.value) (decltype(this->as.Destructor.value))(rhs.as.Destructor.value);
break;
case 70 /* Else */:
new (&this->as.Else.value) (decltype(this->as.Else.value))(rhs.as.Else.value);
break;
case 71 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 72 /* Extern */:
new (&this->as.Extern.value) (decltype(this->as.Extern.value))(rhs.as.Extern.value);
break;
case 73 /* Export */:
new (&this->as.Export.value) (decltype(this->as.Export.value))(rhs.as.Export.value);
break;
case 74 /* False */:
new (&this->as.False.value) (decltype(this->as.False.value))(rhs.as.False.value);
break;
case 75 /* For */:
new (&this->as.For.value) (decltype(this->as.For.value))(rhs.as.For.value);
break;
case 76 /* Fn */:
new (&this->as.Fn.value) (decltype(this->as.Fn.value))(rhs.as.Fn.value);
break;
case 77 /* Comptime */:
new (&this->as.Comptime.value) (decltype(this->as.Comptime.value))(rhs.as.Comptime.value);
break;
case 78 /* If */:
new (&this->as.If.value) (decltype(this->as.If.value))(rhs.as.If.value);
break;
case 79 /* Import */:
new (&this->as.Import.value) (decltype(this->as.Import.value))(rhs.as.Import.value);
break;
case 80 /* Relative */:
new (&this->as.Relative.value) (decltype(this->as.Relative.value))(rhs.as.Relative.value);
break;
case 81 /* In */:
new (&this->as.In.value) (decltype(this->as.In.value))(rhs.as.In.value);
break;
case 82 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(rhs.as.Is.value);
break;
case 83 /* Let */:
new (&this->as.Let.value) (decltype(this->as.Let.value))(rhs.as.Let.value);
break;
case 84 /* Loop */:
new (&this->as.Loop.value) (decltype(this->as.Loop.value))(rhs.as.Loop.value);
break;
case 85 /* Match */:
new (&this->as.Match.value) (decltype(this->as.Match.value))(rhs.as.Match.value);
break;
case 86 /* Must */:
new (&this->as.Must.value) (decltype(this->as.Must.value))(rhs.as.Must.value);
break;
case 87 /* Mut */:
new (&this->as.Mut.value) (decltype(this->as.Mut.value))(rhs.as.Mut.value);
break;
case 88 /* Namespace */:
new (&this->as.Namespace.value) (decltype(this->as.Namespace.value))(rhs.as.Namespace.value);
break;
case 89 /* Not */:
new (&this->as.Not.value) (decltype(this->as.Not.value))(rhs.as.Not.value);
break;
case 90 /* Or */:
new (&this->as.Or.value) (decltype(this->as.Or.value))(rhs.as.Or.value);
break;
case 91 /* Override */:
new (&this->as.Override.value) (decltype(this->as.Override.value))(rhs.as.Override.value);
break;
case 92 /* Private */:
new (&this->as.Private.value) (decltype(this->as.Private.value))(rhs.as.Private.value);
break;
case 93 /* Public */:
new (&this->as.Public.value) (decltype(this->as.Public.value))(rhs.as.Public.value);
break;
case 94 /* Raw */:
new (&this->as.Raw.value) (decltype(this->as.Raw.value))(rhs.as.Raw.value);
break;
case 95 /* Reflect */:
new (&this->as.Reflect.value) (decltype(this->as.Reflect.value))(rhs.as.Reflect.value);
break;
case 96 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(rhs.as.Return.value);
break;
case 97 /* Restricted */:
new (&this->as.Restricted.value) (decltype(this->as.Restricted.value))(rhs.as.Restricted.value);
break;
case 98 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(rhs.as.Sizeof.value);
break;
case 99 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 100 /* This */:
new (&this->as.This.value) (decltype(this->as.This.value))(rhs.as.This.value);
break;
case 101 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(rhs.as.Throw.value);
break;
case 102 /* Throws */:
new (&this->as.Throws.value) (decltype(this->as.Throws.value))(rhs.as.Throws.value);
break;
case 103 /* True */:
new (&this->as.True.value) (decltype(this->as.True.value))(rhs.as.True.value);
break;
case 104 /* Try */:
new (&this->as.Try.value) (decltype(this->as.Try.value))(rhs.as.Try.value);
break;
case 105 /* Unsafe */:
new (&this->as.Unsafe.value) (decltype(this->as.Unsafe.value))(rhs.as.Unsafe.value);
break;
case 106 /* Virtual */:
new (&this->as.Virtual.value) (decltype(this->as.Virtual.value))(rhs.as.Virtual.value);
break;
case 107 /* Weak */:
new (&this->as.Weak.value) (decltype(this->as.Weak.value))(rhs.as.Weak.value);
break;
case 108 /* While */:
new (&this->as.While.value) (decltype(this->as.While.value))(rhs.as.While.value);
break;
case 109 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(rhs.as.Yield.value);
break;
case 110 /* Guard */:
new (&this->as.Guard.value) (decltype(this->as.Guard.value))(rhs.as.Guard.value);
break;
case 111 /* Implements */:
new (&this->as.Implements.value) (decltype(this->as.Implements.value))(rhs.as.Implements.value);
break;
case 112 /* Requires */:
new (&this->as.Requires.value) (decltype(this->as.Requires.value))(rhs.as.Requires.value);
break;
case 113 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
case 114 /* Garbage */:
new (&this->as.Garbage.consumed) (decltype(this->as.Garbage.consumed))(rhs.as.Garbage.consumed);
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(rhs.as.Garbage.span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Token& Token::operator=(Token &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.quote) (decltype(this->as.SingleQuotedString.quote))(move(rhs.as.SingleQuotedString.quote));
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(move(rhs.as.SingleQuotedString.prefix));
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(move(rhs.as.SingleQuotedString.span));
break;
case 1 /* QuotedString */:
new (&this->as.QuotedString.quote) (decltype(this->as.QuotedString.quote))(move(rhs.as.QuotedString.quote));
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(move(rhs.as.QuotedString.span));
break;
case 2 /* Number */:
new (&this->as.Number.prefix) (decltype(this->as.Number.prefix))(move(rhs.as.Number.prefix));
new (&this->as.Number.number) (decltype(this->as.Number.number))(move(rhs.as.Number.number));
new (&this->as.Number.suffix) (decltype(this->as.Number.suffix))(move(rhs.as.Number.suffix));
new (&this->as.Number.span) (decltype(this->as.Number.span))(move(rhs.as.Number.span));
break;
case 3 /* Identifier */:
new (&this->as.Identifier.name) (decltype(this->as.Identifier.name))(move(rhs.as.Identifier.name));
new (&this->as.Identifier.span) (decltype(this->as.Identifier.span))(move(rhs.as.Identifier.span));
break;
case 4 /* Semicolon */:
new (&this->as.Semicolon.value) (decltype(this->as.Semicolon.value))(move(rhs.as.Semicolon.value));
break;
case 5 /* Colon */:
new (&this->as.Colon.value) (decltype(this->as.Colon.value))(move(rhs.as.Colon.value));
break;
case 6 /* ColonColon */:
new (&this->as.ColonColon.value) (decltype(this->as.ColonColon.value))(move(rhs.as.ColonColon.value));
break;
case 7 /* LParen */:
new (&this->as.LParen.value) (decltype(this->as.LParen.value))(move(rhs.as.LParen.value));
break;
case 8 /* RParen */:
new (&this->as.RParen.value) (decltype(this->as.RParen.value))(move(rhs.as.RParen.value));
break;
case 9 /* LCurly */:
new (&this->as.LCurly.value) (decltype(this->as.LCurly.value))(move(rhs.as.LCurly.value));
break;
case 10 /* RCurly */:
new (&this->as.RCurly.value) (decltype(this->as.RCurly.value))(move(rhs.as.RCurly.value));
break;
case 11 /* LSquare */:
new (&this->as.LSquare.value) (decltype(this->as.LSquare.value))(move(rhs.as.LSquare.value));
break;
case 12 /* RSquare */:
new (&this->as.RSquare.value) (decltype(this->as.RSquare.value))(move(rhs.as.RSquare.value));
break;
case 13 /* PercentSign */:
new (&this->as.PercentSign.value) (decltype(this->as.PercentSign.value))(move(rhs.as.PercentSign.value));
break;
case 14 /* Plus */:
new (&this->as.Plus.value) (decltype(this->as.Plus.value))(move(rhs.as.Plus.value));
break;
case 15 /* Minus */:
new (&this->as.Minus.value) (decltype(this->as.Minus.value))(move(rhs.as.Minus.value));
break;
case 16 /* Equal */:
new (&this->as.Equal.value) (decltype(this->as.Equal.value))(move(rhs.as.Equal.value));
break;
case 17 /* PlusEqual */:
new (&this->as.PlusEqual.value) (decltype(this->as.PlusEqual.value))(move(rhs.as.PlusEqual.value));
break;
case 18 /* PlusPlus */:
new (&this->as.PlusPlus.value) (decltype(this->as.PlusPlus.value))(move(rhs.as.PlusPlus.value));
break;
case 19 /* MinusEqual */:
new (&this->as.MinusEqual.value) (decltype(this->as.MinusEqual.value))(move(rhs.as.MinusEqual.value));
break;
case 20 /* MinusMinus */:
new (&this->as.MinusMinus.value) (decltype(this->as.MinusMinus.value))(move(rhs.as.MinusMinus.value));
break;
case 21 /* AsteriskEqual */:
new (&this->as.AsteriskEqual.value) (decltype(this->as.AsteriskEqual.value))(move(rhs.as.AsteriskEqual.value));
break;
case 22 /* ForwardSlashEqual */:
new (&this->as.ForwardSlashEqual.value) (decltype(this->as.ForwardSlashEqual.value))(move(rhs.as.ForwardSlashEqual.value));
break;
case 23 /* PercentSignEqual */:
new (&this->as.PercentSignEqual.value) (decltype(this->as.PercentSignEqual.value))(move(rhs.as.PercentSignEqual.value));
break;
case 24 /* NotEqual */:
new (&this->as.NotEqual.value) (decltype(this->as.NotEqual.value))(move(rhs.as.NotEqual.value));
break;
case 25 /* DoubleEqual */:
new (&this->as.DoubleEqual.value) (decltype(this->as.DoubleEqual.value))(move(rhs.as.DoubleEqual.value));
break;
case 26 /* GreaterThan */:
new (&this->as.GreaterThan.value) (decltype(this->as.GreaterThan.value))(move(rhs.as.GreaterThan.value));
break;
case 27 /* GreaterThanOrEqual */:
new (&this->as.GreaterThanOrEqual.value) (decltype(this->as.GreaterThanOrEqual.value))(move(rhs.as.GreaterThanOrEqual.value));
break;
case 28 /* LessThan */:
new (&this->as.LessThan.value) (decltype(this->as.LessThan.value))(move(rhs.as.LessThan.value));
break;
case 29 /* LessThanOrEqual */:
new (&this->as.LessThanOrEqual.value) (decltype(this->as.LessThanOrEqual.value))(move(rhs.as.LessThanOrEqual.value));
break;
case 30 /* LeftArithmeticShift */:
new (&this->as.LeftArithmeticShift.value) (decltype(this->as.LeftArithmeticShift.value))(move(rhs.as.LeftArithmeticShift.value));
break;
case 31 /* LeftShift */:
new (&this->as.LeftShift.value) (decltype(this->as.LeftShift.value))(move(rhs.as.LeftShift.value));
break;
case 32 /* LeftShiftEqual */:
new (&this->as.LeftShiftEqual.value) (decltype(this->as.LeftShiftEqual.value))(move(rhs.as.LeftShiftEqual.value));
break;
case 33 /* RightShift */:
new (&this->as.RightShift.value) (decltype(this->as.RightShift.value))(move(rhs.as.RightShift.value));
break;
case 34 /* RightArithmeticShift */:
new (&this->as.RightArithmeticShift.value) (decltype(this->as.RightArithmeticShift.value))(move(rhs.as.RightArithmeticShift.value));
break;
case 35 /* RightShiftEqual */:
new (&this->as.RightShiftEqual.value) (decltype(this->as.RightShiftEqual.value))(move(rhs.as.RightShiftEqual.value));
break;
case 36 /* Asterisk */:
new (&this->as.Asterisk.value) (decltype(this->as.Asterisk.value))(move(rhs.as.Asterisk.value));
break;
case 37 /* Ampersand */:
new (&this->as.Ampersand.value) (decltype(this->as.Ampersand.value))(move(rhs.as.Ampersand.value));
break;
case 38 /* AmpersandEqual */:
new (&this->as.AmpersandEqual.value) (decltype(this->as.AmpersandEqual.value))(move(rhs.as.AmpersandEqual.value));
break;
case 39 /* AmpersandAmpersand */:
new (&this->as.AmpersandAmpersand.value) (decltype(this->as.AmpersandAmpersand.value))(move(rhs.as.AmpersandAmpersand.value));
break;
case 40 /* Pipe */:
new (&this->as.Pipe.value) (decltype(this->as.Pipe.value))(move(rhs.as.Pipe.value));
break;
case 41 /* PipeEqual */:
new (&this->as.PipeEqual.value) (decltype(this->as.PipeEqual.value))(move(rhs.as.PipeEqual.value));
break;
case 42 /* PipePipe */:
new (&this->as.PipePipe.value) (decltype(this->as.PipePipe.value))(move(rhs.as.PipePipe.value));
break;
case 43 /* Caret */:
new (&this->as.Caret.value) (decltype(this->as.Caret.value))(move(rhs.as.Caret.value));
break;
case 44 /* CaretEqual */:
new (&this->as.CaretEqual.value) (decltype(this->as.CaretEqual.value))(move(rhs.as.CaretEqual.value));
break;
case 45 /* Dollar */:
new (&this->as.Dollar.value) (decltype(this->as.Dollar.value))(move(rhs.as.Dollar.value));
break;
case 46 /* Tilde */:
new (&this->as.Tilde.value) (decltype(this->as.Tilde.value))(move(rhs.as.Tilde.value));
break;
case 47 /* ForwardSlash */:
new (&this->as.ForwardSlash.value) (decltype(this->as.ForwardSlash.value))(move(rhs.as.ForwardSlash.value));
break;
case 48 /* ExclamationPoint */:
new (&this->as.ExclamationPoint.value) (decltype(this->as.ExclamationPoint.value))(move(rhs.as.ExclamationPoint.value));
break;
case 49 /* QuestionMark */:
new (&this->as.QuestionMark.value) (decltype(this->as.QuestionMark.value))(move(rhs.as.QuestionMark.value));
break;
case 50 /* QuestionMarkQuestionMark */:
new (&this->as.QuestionMarkQuestionMark.value) (decltype(this->as.QuestionMarkQuestionMark.value))(move(rhs.as.QuestionMarkQuestionMark.value));
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
new (&this->as.QuestionMarkQuestionMarkEqual.value) (decltype(this->as.QuestionMarkQuestionMarkEqual.value))(move(rhs.as.QuestionMarkQuestionMarkEqual.value));
break;
case 52 /* Comma */:
new (&this->as.Comma.value) (decltype(this->as.Comma.value))(move(rhs.as.Comma.value));
break;
case 53 /* Dot */:
new (&this->as.Dot.value) (decltype(this->as.Dot.value))(move(rhs.as.Dot.value));
break;
case 54 /* DotDot */:
new (&this->as.DotDot.value) (decltype(this->as.DotDot.value))(move(rhs.as.DotDot.value));
break;
case 55 /* Eol */:
new (&this->as.Eol.comment) (decltype(this->as.Eol.comment))(move(rhs.as.Eol.comment));
new (&this->as.Eol.span) (decltype(this->as.Eol.span))(move(rhs.as.Eol.span));
break;
case 56 /* Eof */:
new (&this->as.Eof.value) (decltype(this->as.Eof.value))(move(rhs.as.Eof.value));
break;
case 57 /* FatArrow */:
new (&this->as.FatArrow.value) (decltype(this->as.FatArrow.value))(move(rhs.as.FatArrow.value));
break;
case 58 /* Arrow */:
new (&this->as.Arrow.value) (decltype(this->as.Arrow.value))(move(rhs.as.Arrow.value));
break;
case 59 /* And */:
new (&this->as.And.value) (decltype(this->as.And.value))(move(rhs.as.And.value));
break;
case 60 /* Anon */:
new (&this->as.Anon.value) (decltype(this->as.Anon.value))(move(rhs.as.Anon.value));
break;
case 61 /* As */:
new (&this->as.As.value) (decltype(this->as.As.value))(move(rhs.as.As.value));
break;
case 62 /* Boxed */:
new (&this->as.Boxed.value) (decltype(this->as.Boxed.value))(move(rhs.as.Boxed.value));
break;
case 63 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(move(rhs.as.Break.value));
break;
case 64 /* Catch */:
new (&this->as.Catch.value) (decltype(this->as.Catch.value))(move(rhs.as.Catch.value));
break;
case 65 /* Class */:
new (&this->as.Class.value) (decltype(this->as.Class.value))(move(rhs.as.Class.value));
break;
case 66 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(move(rhs.as.Continue.value));
break;
case 67 /* Cpp */:
new (&this->as.Cpp.value) (decltype(this->as.Cpp.value))(move(rhs.as.Cpp.value));
break;
case 68 /* Defer */:
new (&this->as.Defer.value) (decltype(this->as.Defer.value))(move(rhs.as.Defer.value));
break;
case 69 /* Destructor */:
new (&this->as.Destructor.value) (decltype(this->as.Destructor.value))(move(rhs.as.Destructor.value));
break;
case 70 /* Else */:
new (&this->as.Else.value) (decltype(this->as.Else.value))(move(rhs.as.Else.value));
break;
case 71 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 72 /* Extern */:
new (&this->as.Extern.value) (decltype(this->as.Extern.value))(move(rhs.as.Extern.value));
break;
case 73 /* Export */:
new (&this->as.Export.value) (decltype(this->as.Export.value))(move(rhs.as.Export.value));
break;
case 74 /* False */:
new (&this->as.False.value) (decltype(this->as.False.value))(move(rhs.as.False.value));
break;
case 75 /* For */:
new (&this->as.For.value) (decltype(this->as.For.value))(move(rhs.as.For.value));
break;
case 76 /* Fn */:
new (&this->as.Fn.value) (decltype(this->as.Fn.value))(move(rhs.as.Fn.value));
break;
case 77 /* Comptime */:
new (&this->as.Comptime.value) (decltype(this->as.Comptime.value))(move(rhs.as.Comptime.value));
break;
case 78 /* If */:
new (&this->as.If.value) (decltype(this->as.If.value))(move(rhs.as.If.value));
break;
case 79 /* Import */:
new (&this->as.Import.value) (decltype(this->as.Import.value))(move(rhs.as.Import.value));
break;
case 80 /* Relative */:
new (&this->as.Relative.value) (decltype(this->as.Relative.value))(move(rhs.as.Relative.value));
break;
case 81 /* In */:
new (&this->as.In.value) (decltype(this->as.In.value))(move(rhs.as.In.value));
break;
case 82 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(move(rhs.as.Is.value));
break;
case 83 /* Let */:
new (&this->as.Let.value) (decltype(this->as.Let.value))(move(rhs.as.Let.value));
break;
case 84 /* Loop */:
new (&this->as.Loop.value) (decltype(this->as.Loop.value))(move(rhs.as.Loop.value));
break;
case 85 /* Match */:
new (&this->as.Match.value) (decltype(this->as.Match.value))(move(rhs.as.Match.value));
break;
case 86 /* Must */:
new (&this->as.Must.value) (decltype(this->as.Must.value))(move(rhs.as.Must.value));
break;
case 87 /* Mut */:
new (&this->as.Mut.value) (decltype(this->as.Mut.value))(move(rhs.as.Mut.value));
break;
case 88 /* Namespace */:
new (&this->as.Namespace.value) (decltype(this->as.Namespace.value))(move(rhs.as.Namespace.value));
break;
case 89 /* Not */:
new (&this->as.Not.value) (decltype(this->as.Not.value))(move(rhs.as.Not.value));
break;
case 90 /* Or */:
new (&this->as.Or.value) (decltype(this->as.Or.value))(move(rhs.as.Or.value));
break;
case 91 /* Override */:
new (&this->as.Override.value) (decltype(this->as.Override.value))(move(rhs.as.Override.value));
break;
case 92 /* Private */:
new (&this->as.Private.value) (decltype(this->as.Private.value))(move(rhs.as.Private.value));
break;
case 93 /* Public */:
new (&this->as.Public.value) (decltype(this->as.Public.value))(move(rhs.as.Public.value));
break;
case 94 /* Raw */:
new (&this->as.Raw.value) (decltype(this->as.Raw.value))(move(rhs.as.Raw.value));
break;
case 95 /* Reflect */:
new (&this->as.Reflect.value) (decltype(this->as.Reflect.value))(move(rhs.as.Reflect.value));
break;
case 96 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(move(rhs.as.Return.value));
break;
case 97 /* Restricted */:
new (&this->as.Restricted.value) (decltype(this->as.Restricted.value))(move(rhs.as.Restricted.value));
break;
case 98 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(move(rhs.as.Sizeof.value));
break;
case 99 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 100 /* This */:
new (&this->as.This.value) (decltype(this->as.This.value))(move(rhs.as.This.value));
break;
case 101 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(move(rhs.as.Throw.value));
break;
case 102 /* Throws */:
new (&this->as.Throws.value) (decltype(this->as.Throws.value))(move(rhs.as.Throws.value));
break;
case 103 /* True */:
new (&this->as.True.value) (decltype(this->as.True.value))(move(rhs.as.True.value));
break;
case 104 /* Try */:
new (&this->as.Try.value) (decltype(this->as.Try.value))(move(rhs.as.Try.value));
break;
case 105 /* Unsafe */:
new (&this->as.Unsafe.value) (decltype(this->as.Unsafe.value))(move(rhs.as.Unsafe.value));
break;
case 106 /* Virtual */:
new (&this->as.Virtual.value) (decltype(this->as.Virtual.value))(move(rhs.as.Virtual.value));
break;
case 107 /* Weak */:
new (&this->as.Weak.value) (decltype(this->as.Weak.value))(move(rhs.as.Weak.value));
break;
case 108 /* While */:
new (&this->as.While.value) (decltype(this->as.While.value))(move(rhs.as.While.value));
break;
case 109 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(move(rhs.as.Yield.value));
break;
case 110 /* Guard */:
new (&this->as.Guard.value) (decltype(this->as.Guard.value))(move(rhs.as.Guard.value));
break;
case 111 /* Implements */:
new (&this->as.Implements.value) (decltype(this->as.Implements.value))(move(rhs.as.Implements.value));
break;
case 112 /* Requires */:
new (&this->as.Requires.value) (decltype(this->as.Requires.value))(move(rhs.as.Requires.value));
break;
case 113 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
case 114 /* Garbage */:
new (&this->as.Garbage.consumed) (decltype(this->as.Garbage.consumed))(move(rhs.as.Garbage.consumed));
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(move(rhs.as.Garbage.span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
this->as.SingleQuotedString.quote = move(rhs.as.SingleQuotedString.quote);
this->as.SingleQuotedString.prefix = move(rhs.as.SingleQuotedString.prefix);
this->as.SingleQuotedString.span = move(rhs.as.SingleQuotedString.span);
break;
case 1 /* QuotedString */:
this->as.QuotedString.quote = move(rhs.as.QuotedString.quote);
this->as.QuotedString.span = move(rhs.as.QuotedString.span);
break;
case 2 /* Number */:
this->as.Number.prefix = move(rhs.as.Number.prefix);
this->as.Number.number = move(rhs.as.Number.number);
this->as.Number.suffix = move(rhs.as.Number.suffix);
this->as.Number.span = move(rhs.as.Number.span);
break;
case 3 /* Identifier */:
this->as.Identifier.name = move(rhs.as.Identifier.name);
this->as.Identifier.span = move(rhs.as.Identifier.span);
break;
case 4 /* Semicolon */:
this->as.Semicolon.value = move(rhs.as.Semicolon.value);
break;
case 5 /* Colon */:
this->as.Colon.value = move(rhs.as.Colon.value);
break;
case 6 /* ColonColon */:
this->as.ColonColon.value = move(rhs.as.ColonColon.value);
break;
case 7 /* LParen */:
this->as.LParen.value = move(rhs.as.LParen.value);
break;
case 8 /* RParen */:
this->as.RParen.value = move(rhs.as.RParen.value);
break;
case 9 /* LCurly */:
this->as.LCurly.value = move(rhs.as.LCurly.value);
break;
case 10 /* RCurly */:
this->as.RCurly.value = move(rhs.as.RCurly.value);
break;
case 11 /* LSquare */:
this->as.LSquare.value = move(rhs.as.LSquare.value);
break;
case 12 /* RSquare */:
this->as.RSquare.value = move(rhs.as.RSquare.value);
break;
case 13 /* PercentSign */:
this->as.PercentSign.value = move(rhs.as.PercentSign.value);
break;
case 14 /* Plus */:
this->as.Plus.value = move(rhs.as.Plus.value);
break;
case 15 /* Minus */:
this->as.Minus.value = move(rhs.as.Minus.value);
break;
case 16 /* Equal */:
this->as.Equal.value = move(rhs.as.Equal.value);
break;
case 17 /* PlusEqual */:
this->as.PlusEqual.value = move(rhs.as.PlusEqual.value);
break;
case 18 /* PlusPlus */:
this->as.PlusPlus.value = move(rhs.as.PlusPlus.value);
break;
case 19 /* MinusEqual */:
this->as.MinusEqual.value = move(rhs.as.MinusEqual.value);
break;
case 20 /* MinusMinus */:
this->as.MinusMinus.value = move(rhs.as.MinusMinus.value);
break;
case 21 /* AsteriskEqual */:
this->as.AsteriskEqual.value = move(rhs.as.AsteriskEqual.value);
break;
case 22 /* ForwardSlashEqual */:
this->as.ForwardSlashEqual.value = move(rhs.as.ForwardSlashEqual.value);
break;
case 23 /* PercentSignEqual */:
this->as.PercentSignEqual.value = move(rhs.as.PercentSignEqual.value);
break;
case 24 /* NotEqual */:
this->as.NotEqual.value = move(rhs.as.NotEqual.value);
break;
case 25 /* DoubleEqual */:
this->as.DoubleEqual.value = move(rhs.as.DoubleEqual.value);
break;
case 26 /* GreaterThan */:
this->as.GreaterThan.value = move(rhs.as.GreaterThan.value);
break;
case 27 /* GreaterThanOrEqual */:
this->as.GreaterThanOrEqual.value = move(rhs.as.GreaterThanOrEqual.value);
break;
case 28 /* LessThan */:
this->as.LessThan.value = move(rhs.as.LessThan.value);
break;
case 29 /* LessThanOrEqual */:
this->as.LessThanOrEqual.value = move(rhs.as.LessThanOrEqual.value);
break;
case 30 /* LeftArithmeticShift */:
this->as.LeftArithmeticShift.value = move(rhs.as.LeftArithmeticShift.value);
break;
case 31 /* LeftShift */:
this->as.LeftShift.value = move(rhs.as.LeftShift.value);
break;
case 32 /* LeftShiftEqual */:
this->as.LeftShiftEqual.value = move(rhs.as.LeftShiftEqual.value);
break;
case 33 /* RightShift */:
this->as.RightShift.value = move(rhs.as.RightShift.value);
break;
case 34 /* RightArithmeticShift */:
this->as.RightArithmeticShift.value = move(rhs.as.RightArithmeticShift.value);
break;
case 35 /* RightShiftEqual */:
this->as.RightShiftEqual.value = move(rhs.as.RightShiftEqual.value);
break;
case 36 /* Asterisk */:
this->as.Asterisk.value = move(rhs.as.Asterisk.value);
break;
case 37 /* Ampersand */:
this->as.Ampersand.value = move(rhs.as.Ampersand.value);
break;
case 38 /* AmpersandEqual */:
this->as.AmpersandEqual.value = move(rhs.as.AmpersandEqual.value);
break;
case 39 /* AmpersandAmpersand */:
this->as.AmpersandAmpersand.value = move(rhs.as.AmpersandAmpersand.value);
break;
case 40 /* Pipe */:
this->as.Pipe.value = move(rhs.as.Pipe.value);
break;
case 41 /* PipeEqual */:
this->as.PipeEqual.value = move(rhs.as.PipeEqual.value);
break;
case 42 /* PipePipe */:
this->as.PipePipe.value = move(rhs.as.PipePipe.value);
break;
case 43 /* Caret */:
this->as.Caret.value = move(rhs.as.Caret.value);
break;
case 44 /* CaretEqual */:
this->as.CaretEqual.value = move(rhs.as.CaretEqual.value);
break;
case 45 /* Dollar */:
this->as.Dollar.value = move(rhs.as.Dollar.value);
break;
case 46 /* Tilde */:
this->as.Tilde.value = move(rhs.as.Tilde.value);
break;
case 47 /* ForwardSlash */:
this->as.ForwardSlash.value = move(rhs.as.ForwardSlash.value);
break;
case 48 /* ExclamationPoint */:
this->as.ExclamationPoint.value = move(rhs.as.ExclamationPoint.value);
break;
case 49 /* QuestionMark */:
this->as.QuestionMark.value = move(rhs.as.QuestionMark.value);
break;
case 50 /* QuestionMarkQuestionMark */:
this->as.QuestionMarkQuestionMark.value = move(rhs.as.QuestionMarkQuestionMark.value);
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
this->as.QuestionMarkQuestionMarkEqual.value = move(rhs.as.QuestionMarkQuestionMarkEqual.value);
break;
case 52 /* Comma */:
this->as.Comma.value = move(rhs.as.Comma.value);
break;
case 53 /* Dot */:
this->as.Dot.value = move(rhs.as.Dot.value);
break;
case 54 /* DotDot */:
this->as.DotDot.value = move(rhs.as.DotDot.value);
break;
case 55 /* Eol */:
this->as.Eol.comment = move(rhs.as.Eol.comment);
this->as.Eol.span = move(rhs.as.Eol.span);
break;
case 56 /* Eof */:
this->as.Eof.value = move(rhs.as.Eof.value);
break;
case 57 /* FatArrow */:
this->as.FatArrow.value = move(rhs.as.FatArrow.value);
break;
case 58 /* Arrow */:
this->as.Arrow.value = move(rhs.as.Arrow.value);
break;
case 59 /* And */:
this->as.And.value = move(rhs.as.And.value);
break;
case 60 /* Anon */:
this->as.Anon.value = move(rhs.as.Anon.value);
break;
case 61 /* As */:
this->as.As.value = move(rhs.as.As.value);
break;
case 62 /* Boxed */:
this->as.Boxed.value = move(rhs.as.Boxed.value);
break;
case 63 /* Break */:
this->as.Break.value = move(rhs.as.Break.value);
break;
case 64 /* Catch */:
this->as.Catch.value = move(rhs.as.Catch.value);
break;
case 65 /* Class */:
this->as.Class.value = move(rhs.as.Class.value);
break;
case 66 /* Continue */:
this->as.Continue.value = move(rhs.as.Continue.value);
break;
case 67 /* Cpp */:
this->as.Cpp.value = move(rhs.as.Cpp.value);
break;
case 68 /* Defer */:
this->as.Defer.value = move(rhs.as.Defer.value);
break;
case 69 /* Destructor */:
this->as.Destructor.value = move(rhs.as.Destructor.value);
break;
case 70 /* Else */:
this->as.Else.value = move(rhs.as.Else.value);
break;
case 71 /* Enum */:
this->as.Enum.value = move(rhs.as.Enum.value);
break;
case 72 /* Extern */:
this->as.Extern.value = move(rhs.as.Extern.value);
break;
case 73 /* Export */:
this->as.Export.value = move(rhs.as.Export.value);
break;
case 74 /* False */:
this->as.False.value = move(rhs.as.False.value);
break;
case 75 /* For */:
this->as.For.value = move(rhs.as.For.value);
break;
case 76 /* Fn */:
this->as.Fn.value = move(rhs.as.Fn.value);
break;
case 77 /* Comptime */:
this->as.Comptime.value = move(rhs.as.Comptime.value);
break;
case 78 /* If */:
this->as.If.value = move(rhs.as.If.value);
break;
case 79 /* Import */:
this->as.Import.value = move(rhs.as.Import.value);
break;
case 80 /* Relative */:
this->as.Relative.value = move(rhs.as.Relative.value);
break;
case 81 /* In */:
this->as.In.value = move(rhs.as.In.value);
break;
case 82 /* Is */:
this->as.Is.value = move(rhs.as.Is.value);
break;
case 83 /* Let */:
this->as.Let.value = move(rhs.as.Let.value);
break;
case 84 /* Loop */:
this->as.Loop.value = move(rhs.as.Loop.value);
break;
case 85 /* Match */:
this->as.Match.value = move(rhs.as.Match.value);
break;
case 86 /* Must */:
this->as.Must.value = move(rhs.as.Must.value);
break;
case 87 /* Mut */:
this->as.Mut.value = move(rhs.as.Mut.value);
break;
case 88 /* Namespace */:
this->as.Namespace.value = move(rhs.as.Namespace.value);
break;
case 89 /* Not */:
this->as.Not.value = move(rhs.as.Not.value);
break;
case 90 /* Or */:
this->as.Or.value = move(rhs.as.Or.value);
break;
case 91 /* Override */:
this->as.Override.value = move(rhs.as.Override.value);
break;
case 92 /* Private */:
this->as.Private.value = move(rhs.as.Private.value);
break;
case 93 /* Public */:
this->as.Public.value = move(rhs.as.Public.value);
break;
case 94 /* Raw */:
this->as.Raw.value = move(rhs.as.Raw.value);
break;
case 95 /* Reflect */:
this->as.Reflect.value = move(rhs.as.Reflect.value);
break;
case 96 /* Return */:
this->as.Return.value = move(rhs.as.Return.value);
break;
case 97 /* Restricted */:
this->as.Restricted.value = move(rhs.as.Restricted.value);
break;
case 98 /* Sizeof */:
this->as.Sizeof.value = move(rhs.as.Sizeof.value);
break;
case 99 /* Struct */:
this->as.Struct.value = move(rhs.as.Struct.value);
break;
case 100 /* This */:
this->as.This.value = move(rhs.as.This.value);
break;
case 101 /* Throw */:
this->as.Throw.value = move(rhs.as.Throw.value);
break;
case 102 /* Throws */:
this->as.Throws.value = move(rhs.as.Throws.value);
break;
case 103 /* True */:
this->as.True.value = move(rhs.as.True.value);
break;
case 104 /* Try */:
this->as.Try.value = move(rhs.as.Try.value);
break;
case 105 /* Unsafe */:
this->as.Unsafe.value = move(rhs.as.Unsafe.value);
break;
case 106 /* Virtual */:
this->as.Virtual.value = move(rhs.as.Virtual.value);
break;
case 107 /* Weak */:
this->as.Weak.value = move(rhs.as.Weak.value);
break;
case 108 /* While */:
this->as.While.value = move(rhs.as.While.value);
break;
case 109 /* Yield */:
this->as.Yield.value = move(rhs.as.Yield.value);
break;
case 110 /* Guard */:
this->as.Guard.value = move(rhs.as.Guard.value);
break;
case 111 /* Implements */:
this->as.Implements.value = move(rhs.as.Implements.value);
break;
case 112 /* Requires */:
this->as.Requires.value = move(rhs.as.Requires.value);
break;
case 113 /* Trait */:
this->as.Trait.value = move(rhs.as.Trait.value);
break;
case 114 /* Garbage */:
this->as.Garbage.consumed = move(rhs.as.Garbage.consumed);
this->as.Garbage.span = move(rhs.as.Garbage.span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Token::Token(Token &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.quote) (decltype(this->as.SingleQuotedString.quote))(move(rhs.as.SingleQuotedString.quote));
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(move(rhs.as.SingleQuotedString.prefix));
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(move(rhs.as.SingleQuotedString.span));
break;
case 1 /* QuotedString */:
new (&this->as.QuotedString.quote) (decltype(this->as.QuotedString.quote))(move(rhs.as.QuotedString.quote));
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(move(rhs.as.QuotedString.span));
break;
case 2 /* Number */:
new (&this->as.Number.prefix) (decltype(this->as.Number.prefix))(move(rhs.as.Number.prefix));
new (&this->as.Number.number) (decltype(this->as.Number.number))(move(rhs.as.Number.number));
new (&this->as.Number.suffix) (decltype(this->as.Number.suffix))(move(rhs.as.Number.suffix));
new (&this->as.Number.span) (decltype(this->as.Number.span))(move(rhs.as.Number.span));
break;
case 3 /* Identifier */:
new (&this->as.Identifier.name) (decltype(this->as.Identifier.name))(move(rhs.as.Identifier.name));
new (&this->as.Identifier.span) (decltype(this->as.Identifier.span))(move(rhs.as.Identifier.span));
break;
case 4 /* Semicolon */:
new (&this->as.Semicolon.value) (decltype(this->as.Semicolon.value))(move(rhs.as.Semicolon.value));
break;
case 5 /* Colon */:
new (&this->as.Colon.value) (decltype(this->as.Colon.value))(move(rhs.as.Colon.value));
break;
case 6 /* ColonColon */:
new (&this->as.ColonColon.value) (decltype(this->as.ColonColon.value))(move(rhs.as.ColonColon.value));
break;
case 7 /* LParen */:
new (&this->as.LParen.value) (decltype(this->as.LParen.value))(move(rhs.as.LParen.value));
break;
case 8 /* RParen */:
new (&this->as.RParen.value) (decltype(this->as.RParen.value))(move(rhs.as.RParen.value));
break;
case 9 /* LCurly */:
new (&this->as.LCurly.value) (decltype(this->as.LCurly.value))(move(rhs.as.LCurly.value));
break;
case 10 /* RCurly */:
new (&this->as.RCurly.value) (decltype(this->as.RCurly.value))(move(rhs.as.RCurly.value));
break;
case 11 /* LSquare */:
new (&this->as.LSquare.value) (decltype(this->as.LSquare.value))(move(rhs.as.LSquare.value));
break;
case 12 /* RSquare */:
new (&this->as.RSquare.value) (decltype(this->as.RSquare.value))(move(rhs.as.RSquare.value));
break;
case 13 /* PercentSign */:
new (&this->as.PercentSign.value) (decltype(this->as.PercentSign.value))(move(rhs.as.PercentSign.value));
break;
case 14 /* Plus */:
new (&this->as.Plus.value) (decltype(this->as.Plus.value))(move(rhs.as.Plus.value));
break;
case 15 /* Minus */:
new (&this->as.Minus.value) (decltype(this->as.Minus.value))(move(rhs.as.Minus.value));
break;
case 16 /* Equal */:
new (&this->as.Equal.value) (decltype(this->as.Equal.value))(move(rhs.as.Equal.value));
break;
case 17 /* PlusEqual */:
new (&this->as.PlusEqual.value) (decltype(this->as.PlusEqual.value))(move(rhs.as.PlusEqual.value));
break;
case 18 /* PlusPlus */:
new (&this->as.PlusPlus.value) (decltype(this->as.PlusPlus.value))(move(rhs.as.PlusPlus.value));
break;
case 19 /* MinusEqual */:
new (&this->as.MinusEqual.value) (decltype(this->as.MinusEqual.value))(move(rhs.as.MinusEqual.value));
break;
case 20 /* MinusMinus */:
new (&this->as.MinusMinus.value) (decltype(this->as.MinusMinus.value))(move(rhs.as.MinusMinus.value));
break;
case 21 /* AsteriskEqual */:
new (&this->as.AsteriskEqual.value) (decltype(this->as.AsteriskEqual.value))(move(rhs.as.AsteriskEqual.value));
break;
case 22 /* ForwardSlashEqual */:
new (&this->as.ForwardSlashEqual.value) (decltype(this->as.ForwardSlashEqual.value))(move(rhs.as.ForwardSlashEqual.value));
break;
case 23 /* PercentSignEqual */:
new (&this->as.PercentSignEqual.value) (decltype(this->as.PercentSignEqual.value))(move(rhs.as.PercentSignEqual.value));
break;
case 24 /* NotEqual */:
new (&this->as.NotEqual.value) (decltype(this->as.NotEqual.value))(move(rhs.as.NotEqual.value));
break;
case 25 /* DoubleEqual */:
new (&this->as.DoubleEqual.value) (decltype(this->as.DoubleEqual.value))(move(rhs.as.DoubleEqual.value));
break;
case 26 /* GreaterThan */:
new (&this->as.GreaterThan.value) (decltype(this->as.GreaterThan.value))(move(rhs.as.GreaterThan.value));
break;
case 27 /* GreaterThanOrEqual */:
new (&this->as.GreaterThanOrEqual.value) (decltype(this->as.GreaterThanOrEqual.value))(move(rhs.as.GreaterThanOrEqual.value));
break;
case 28 /* LessThan */:
new (&this->as.LessThan.value) (decltype(this->as.LessThan.value))(move(rhs.as.LessThan.value));
break;
case 29 /* LessThanOrEqual */:
new (&this->as.LessThanOrEqual.value) (decltype(this->as.LessThanOrEqual.value))(move(rhs.as.LessThanOrEqual.value));
break;
case 30 /* LeftArithmeticShift */:
new (&this->as.LeftArithmeticShift.value) (decltype(this->as.LeftArithmeticShift.value))(move(rhs.as.LeftArithmeticShift.value));
break;
case 31 /* LeftShift */:
new (&this->as.LeftShift.value) (decltype(this->as.LeftShift.value))(move(rhs.as.LeftShift.value));
break;
case 32 /* LeftShiftEqual */:
new (&this->as.LeftShiftEqual.value) (decltype(this->as.LeftShiftEqual.value))(move(rhs.as.LeftShiftEqual.value));
break;
case 33 /* RightShift */:
new (&this->as.RightShift.value) (decltype(this->as.RightShift.value))(move(rhs.as.RightShift.value));
break;
case 34 /* RightArithmeticShift */:
new (&this->as.RightArithmeticShift.value) (decltype(this->as.RightArithmeticShift.value))(move(rhs.as.RightArithmeticShift.value));
break;
case 35 /* RightShiftEqual */:
new (&this->as.RightShiftEqual.value) (decltype(this->as.RightShiftEqual.value))(move(rhs.as.RightShiftEqual.value));
break;
case 36 /* Asterisk */:
new (&this->as.Asterisk.value) (decltype(this->as.Asterisk.value))(move(rhs.as.Asterisk.value));
break;
case 37 /* Ampersand */:
new (&this->as.Ampersand.value) (decltype(this->as.Ampersand.value))(move(rhs.as.Ampersand.value));
break;
case 38 /* AmpersandEqual */:
new (&this->as.AmpersandEqual.value) (decltype(this->as.AmpersandEqual.value))(move(rhs.as.AmpersandEqual.value));
break;
case 39 /* AmpersandAmpersand */:
new (&this->as.AmpersandAmpersand.value) (decltype(this->as.AmpersandAmpersand.value))(move(rhs.as.AmpersandAmpersand.value));
break;
case 40 /* Pipe */:
new (&this->as.Pipe.value) (decltype(this->as.Pipe.value))(move(rhs.as.Pipe.value));
break;
case 41 /* PipeEqual */:
new (&this->as.PipeEqual.value) (decltype(this->as.PipeEqual.value))(move(rhs.as.PipeEqual.value));
break;
case 42 /* PipePipe */:
new (&this->as.PipePipe.value) (decltype(this->as.PipePipe.value))(move(rhs.as.PipePipe.value));
break;
case 43 /* Caret */:
new (&this->as.Caret.value) (decltype(this->as.Caret.value))(move(rhs.as.Caret.value));
break;
case 44 /* CaretEqual */:
new (&this->as.CaretEqual.value) (decltype(this->as.CaretEqual.value))(move(rhs.as.CaretEqual.value));
break;
case 45 /* Dollar */:
new (&this->as.Dollar.value) (decltype(this->as.Dollar.value))(move(rhs.as.Dollar.value));
break;
case 46 /* Tilde */:
new (&this->as.Tilde.value) (decltype(this->as.Tilde.value))(move(rhs.as.Tilde.value));
break;
case 47 /* ForwardSlash */:
new (&this->as.ForwardSlash.value) (decltype(this->as.ForwardSlash.value))(move(rhs.as.ForwardSlash.value));
break;
case 48 /* ExclamationPoint */:
new (&this->as.ExclamationPoint.value) (decltype(this->as.ExclamationPoint.value))(move(rhs.as.ExclamationPoint.value));
break;
case 49 /* QuestionMark */:
new (&this->as.QuestionMark.value) (decltype(this->as.QuestionMark.value))(move(rhs.as.QuestionMark.value));
break;
case 50 /* QuestionMarkQuestionMark */:
new (&this->as.QuestionMarkQuestionMark.value) (decltype(this->as.QuestionMarkQuestionMark.value))(move(rhs.as.QuestionMarkQuestionMark.value));
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
new (&this->as.QuestionMarkQuestionMarkEqual.value) (decltype(this->as.QuestionMarkQuestionMarkEqual.value))(move(rhs.as.QuestionMarkQuestionMarkEqual.value));
break;
case 52 /* Comma */:
new (&this->as.Comma.value) (decltype(this->as.Comma.value))(move(rhs.as.Comma.value));
break;
case 53 /* Dot */:
new (&this->as.Dot.value) (decltype(this->as.Dot.value))(move(rhs.as.Dot.value));
break;
case 54 /* DotDot */:
new (&this->as.DotDot.value) (decltype(this->as.DotDot.value))(move(rhs.as.DotDot.value));
break;
case 55 /* Eol */:
new (&this->as.Eol.comment) (decltype(this->as.Eol.comment))(move(rhs.as.Eol.comment));
new (&this->as.Eol.span) (decltype(this->as.Eol.span))(move(rhs.as.Eol.span));
break;
case 56 /* Eof */:
new (&this->as.Eof.value) (decltype(this->as.Eof.value))(move(rhs.as.Eof.value));
break;
case 57 /* FatArrow */:
new (&this->as.FatArrow.value) (decltype(this->as.FatArrow.value))(move(rhs.as.FatArrow.value));
break;
case 58 /* Arrow */:
new (&this->as.Arrow.value) (decltype(this->as.Arrow.value))(move(rhs.as.Arrow.value));
break;
case 59 /* And */:
new (&this->as.And.value) (decltype(this->as.And.value))(move(rhs.as.And.value));
break;
case 60 /* Anon */:
new (&this->as.Anon.value) (decltype(this->as.Anon.value))(move(rhs.as.Anon.value));
break;
case 61 /* As */:
new (&this->as.As.value) (decltype(this->as.As.value))(move(rhs.as.As.value));
break;
case 62 /* Boxed */:
new (&this->as.Boxed.value) (decltype(this->as.Boxed.value))(move(rhs.as.Boxed.value));
break;
case 63 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(move(rhs.as.Break.value));
break;
case 64 /* Catch */:
new (&this->as.Catch.value) (decltype(this->as.Catch.value))(move(rhs.as.Catch.value));
break;
case 65 /* Class */:
new (&this->as.Class.value) (decltype(this->as.Class.value))(move(rhs.as.Class.value));
break;
case 66 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(move(rhs.as.Continue.value));
break;
case 67 /* Cpp */:
new (&this->as.Cpp.value) (decltype(this->as.Cpp.value))(move(rhs.as.Cpp.value));
break;
case 68 /* Defer */:
new (&this->as.Defer.value) (decltype(this->as.Defer.value))(move(rhs.as.Defer.value));
break;
case 69 /* Destructor */:
new (&this->as.Destructor.value) (decltype(this->as.Destructor.value))(move(rhs.as.Destructor.value));
break;
case 70 /* Else */:
new (&this->as.Else.value) (decltype(this->as.Else.value))(move(rhs.as.Else.value));
break;
case 71 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 72 /* Extern */:
new (&this->as.Extern.value) (decltype(this->as.Extern.value))(move(rhs.as.Extern.value));
break;
case 73 /* Export */:
new (&this->as.Export.value) (decltype(this->as.Export.value))(move(rhs.as.Export.value));
break;
case 74 /* False */:
new (&this->as.False.value) (decltype(this->as.False.value))(move(rhs.as.False.value));
break;
case 75 /* For */:
new (&this->as.For.value) (decltype(this->as.For.value))(move(rhs.as.For.value));
break;
case 76 /* Fn */:
new (&this->as.Fn.value) (decltype(this->as.Fn.value))(move(rhs.as.Fn.value));
break;
case 77 /* Comptime */:
new (&this->as.Comptime.value) (decltype(this->as.Comptime.value))(move(rhs.as.Comptime.value));
break;
case 78 /* If */:
new (&this->as.If.value) (decltype(this->as.If.value))(move(rhs.as.If.value));
break;
case 79 /* Import */:
new (&this->as.Import.value) (decltype(this->as.Import.value))(move(rhs.as.Import.value));
break;
case 80 /* Relative */:
new (&this->as.Relative.value) (decltype(this->as.Relative.value))(move(rhs.as.Relative.value));
break;
case 81 /* In */:
new (&this->as.In.value) (decltype(this->as.In.value))(move(rhs.as.In.value));
break;
case 82 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(move(rhs.as.Is.value));
break;
case 83 /* Let */:
new (&this->as.Let.value) (decltype(this->as.Let.value))(move(rhs.as.Let.value));
break;
case 84 /* Loop */:
new (&this->as.Loop.value) (decltype(this->as.Loop.value))(move(rhs.as.Loop.value));
break;
case 85 /* Match */:
new (&this->as.Match.value) (decltype(this->as.Match.value))(move(rhs.as.Match.value));
break;
case 86 /* Must */:
new (&this->as.Must.value) (decltype(this->as.Must.value))(move(rhs.as.Must.value));
break;
case 87 /* Mut */:
new (&this->as.Mut.value) (decltype(this->as.Mut.value))(move(rhs.as.Mut.value));
break;
case 88 /* Namespace */:
new (&this->as.Namespace.value) (decltype(this->as.Namespace.value))(move(rhs.as.Namespace.value));
break;
case 89 /* Not */:
new (&this->as.Not.value) (decltype(this->as.Not.value))(move(rhs.as.Not.value));
break;
case 90 /* Or */:
new (&this->as.Or.value) (decltype(this->as.Or.value))(move(rhs.as.Or.value));
break;
case 91 /* Override */:
new (&this->as.Override.value) (decltype(this->as.Override.value))(move(rhs.as.Override.value));
break;
case 92 /* Private */:
new (&this->as.Private.value) (decltype(this->as.Private.value))(move(rhs.as.Private.value));
break;
case 93 /* Public */:
new (&this->as.Public.value) (decltype(this->as.Public.value))(move(rhs.as.Public.value));
break;
case 94 /* Raw */:
new (&this->as.Raw.value) (decltype(this->as.Raw.value))(move(rhs.as.Raw.value));
break;
case 95 /* Reflect */:
new (&this->as.Reflect.value) (decltype(this->as.Reflect.value))(move(rhs.as.Reflect.value));
break;
case 96 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(move(rhs.as.Return.value));
break;
case 97 /* Restricted */:
new (&this->as.Restricted.value) (decltype(this->as.Restricted.value))(move(rhs.as.Restricted.value));
break;
case 98 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(move(rhs.as.Sizeof.value));
break;
case 99 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 100 /* This */:
new (&this->as.This.value) (decltype(this->as.This.value))(move(rhs.as.This.value));
break;
case 101 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(move(rhs.as.Throw.value));
break;
case 102 /* Throws */:
new (&this->as.Throws.value) (decltype(this->as.Throws.value))(move(rhs.as.Throws.value));
break;
case 103 /* True */:
new (&this->as.True.value) (decltype(this->as.True.value))(move(rhs.as.True.value));
break;
case 104 /* Try */:
new (&this->as.Try.value) (decltype(this->as.Try.value))(move(rhs.as.Try.value));
break;
case 105 /* Unsafe */:
new (&this->as.Unsafe.value) (decltype(this->as.Unsafe.value))(move(rhs.as.Unsafe.value));
break;
case 106 /* Virtual */:
new (&this->as.Virtual.value) (decltype(this->as.Virtual.value))(move(rhs.as.Virtual.value));
break;
case 107 /* Weak */:
new (&this->as.Weak.value) (decltype(this->as.Weak.value))(move(rhs.as.Weak.value));
break;
case 108 /* While */:
new (&this->as.While.value) (decltype(this->as.While.value))(move(rhs.as.While.value));
break;
case 109 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(move(rhs.as.Yield.value));
break;
case 110 /* Guard */:
new (&this->as.Guard.value) (decltype(this->as.Guard.value))(move(rhs.as.Guard.value));
break;
case 111 /* Implements */:
new (&this->as.Implements.value) (decltype(this->as.Implements.value))(move(rhs.as.Implements.value));
break;
case 112 /* Requires */:
new (&this->as.Requires.value) (decltype(this->as.Requires.value))(move(rhs.as.Requires.value));
break;
case 113 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
case 114 /* Garbage */:
new (&this->as.Garbage.consumed) (decltype(this->as.Garbage.consumed))(move(rhs.as.Garbage.consumed));
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(move(rhs.as.Garbage.span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Token::~Token(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void Token::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* SingleQuotedString */:this->as.SingleQuotedString.quote.~ByteString();
this->as.SingleQuotedString.prefix.~Optional();
this->as.SingleQuotedString.span.~Span();
break;
case 1 /* QuotedString */:this->as.QuotedString.quote.~ByteString();
this->as.QuotedString.span.~Span();
break;
case 2 /* Number */:this->as.Number.prefix.~LiteralPrefix();
this->as.Number.number.~ByteString();
this->as.Number.suffix.~LiteralSuffix();
this->as.Number.span.~Span();
break;
case 3 /* Identifier */:this->as.Identifier.name.~ByteString();
this->as.Identifier.span.~Span();
break;
case 4 /* Semicolon */:this->as.Semicolon.value.~Span();
break;
case 5 /* Colon */:this->as.Colon.value.~Span();
break;
case 6 /* ColonColon */:this->as.ColonColon.value.~Span();
break;
case 7 /* LParen */:this->as.LParen.value.~Span();
break;
case 8 /* RParen */:this->as.RParen.value.~Span();
break;
case 9 /* LCurly */:this->as.LCurly.value.~Span();
break;
case 10 /* RCurly */:this->as.RCurly.value.~Span();
break;
case 11 /* LSquare */:this->as.LSquare.value.~Span();
break;
case 12 /* RSquare */:this->as.RSquare.value.~Span();
break;
case 13 /* PercentSign */:this->as.PercentSign.value.~Span();
break;
case 14 /* Plus */:this->as.Plus.value.~Span();
break;
case 15 /* Minus */:this->as.Minus.value.~Span();
break;
case 16 /* Equal */:this->as.Equal.value.~Span();
break;
case 17 /* PlusEqual */:this->as.PlusEqual.value.~Span();
break;
case 18 /* PlusPlus */:this->as.PlusPlus.value.~Span();
break;
case 19 /* MinusEqual */:this->as.MinusEqual.value.~Span();
break;
case 20 /* MinusMinus */:this->as.MinusMinus.value.~Span();
break;
case 21 /* AsteriskEqual */:this->as.AsteriskEqual.value.~Span();
break;
case 22 /* ForwardSlashEqual */:this->as.ForwardSlashEqual.value.~Span();
break;
case 23 /* PercentSignEqual */:this->as.PercentSignEqual.value.~Span();
break;
case 24 /* NotEqual */:this->as.NotEqual.value.~Span();
break;
case 25 /* DoubleEqual */:this->as.DoubleEqual.value.~Span();
break;
case 26 /* GreaterThan */:this->as.GreaterThan.value.~Span();
break;
case 27 /* GreaterThanOrEqual */:this->as.GreaterThanOrEqual.value.~Span();
break;
case 28 /* LessThan */:this->as.LessThan.value.~Span();
break;
case 29 /* LessThanOrEqual */:this->as.LessThanOrEqual.value.~Span();
break;
case 30 /* LeftArithmeticShift */:this->as.LeftArithmeticShift.value.~Span();
break;
case 31 /* LeftShift */:this->as.LeftShift.value.~Span();
break;
case 32 /* LeftShiftEqual */:this->as.LeftShiftEqual.value.~Span();
break;
case 33 /* RightShift */:this->as.RightShift.value.~Span();
break;
case 34 /* RightArithmeticShift */:this->as.RightArithmeticShift.value.~Span();
break;
case 35 /* RightShiftEqual */:this->as.RightShiftEqual.value.~Span();
break;
case 36 /* Asterisk */:this->as.Asterisk.value.~Span();
break;
case 37 /* Ampersand */:this->as.Ampersand.value.~Span();
break;
case 38 /* AmpersandEqual */:this->as.AmpersandEqual.value.~Span();
break;
case 39 /* AmpersandAmpersand */:this->as.AmpersandAmpersand.value.~Span();
break;
case 40 /* Pipe */:this->as.Pipe.value.~Span();
break;
case 41 /* PipeEqual */:this->as.PipeEqual.value.~Span();
break;
case 42 /* PipePipe */:this->as.PipePipe.value.~Span();
break;
case 43 /* Caret */:this->as.Caret.value.~Span();
break;
case 44 /* CaretEqual */:this->as.CaretEqual.value.~Span();
break;
case 45 /* Dollar */:this->as.Dollar.value.~Span();
break;
case 46 /* Tilde */:this->as.Tilde.value.~Span();
break;
case 47 /* ForwardSlash */:this->as.ForwardSlash.value.~Span();
break;
case 48 /* ExclamationPoint */:this->as.ExclamationPoint.value.~Span();
break;
case 49 /* QuestionMark */:this->as.QuestionMark.value.~Span();
break;
case 50 /* QuestionMarkQuestionMark */:this->as.QuestionMarkQuestionMark.value.~Span();
break;
case 51 /* QuestionMarkQuestionMarkEqual */:this->as.QuestionMarkQuestionMarkEqual.value.~Span();
break;
case 52 /* Comma */:this->as.Comma.value.~Span();
break;
case 53 /* Dot */:this->as.Dot.value.~Span();
break;
case 54 /* DotDot */:this->as.DotDot.value.~Span();
break;
case 55 /* Eol */:this->as.Eol.comment.~Optional();
this->as.Eol.span.~Span();
break;
case 56 /* Eof */:this->as.Eof.value.~Span();
break;
case 57 /* FatArrow */:this->as.FatArrow.value.~Span();
break;
case 58 /* Arrow */:this->as.Arrow.value.~Span();
break;
case 59 /* And */:this->as.And.value.~Span();
break;
case 60 /* Anon */:this->as.Anon.value.~Span();
break;
case 61 /* As */:this->as.As.value.~Span();
break;
case 62 /* Boxed */:this->as.Boxed.value.~Span();
break;
case 63 /* Break */:this->as.Break.value.~Span();
break;
case 64 /* Catch */:this->as.Catch.value.~Span();
break;
case 65 /* Class */:this->as.Class.value.~Span();
break;
case 66 /* Continue */:this->as.Continue.value.~Span();
break;
case 67 /* Cpp */:this->as.Cpp.value.~Span();
break;
case 68 /* Defer */:this->as.Defer.value.~Span();
break;
case 69 /* Destructor */:this->as.Destructor.value.~Span();
break;
case 70 /* Else */:this->as.Else.value.~Span();
break;
case 71 /* Enum */:this->as.Enum.value.~Span();
break;
case 72 /* Extern */:this->as.Extern.value.~Span();
break;
case 73 /* Export */:this->as.Export.value.~Span();
break;
case 74 /* False */:this->as.False.value.~Span();
break;
case 75 /* For */:this->as.For.value.~Span();
break;
case 76 /* Fn */:this->as.Fn.value.~Span();
break;
case 77 /* Comptime */:this->as.Comptime.value.~Span();
break;
case 78 /* If */:this->as.If.value.~Span();
break;
case 79 /* Import */:this->as.Import.value.~Span();
break;
case 80 /* Relative */:this->as.Relative.value.~Span();
break;
case 81 /* In */:this->as.In.value.~Span();
break;
case 82 /* Is */:this->as.Is.value.~Span();
break;
case 83 /* Let */:this->as.Let.value.~Span();
break;
case 84 /* Loop */:this->as.Loop.value.~Span();
break;
case 85 /* Match */:this->as.Match.value.~Span();
break;
case 86 /* Must */:this->as.Must.value.~Span();
break;
case 87 /* Mut */:this->as.Mut.value.~Span();
break;
case 88 /* Namespace */:this->as.Namespace.value.~Span();
break;
case 89 /* Not */:this->as.Not.value.~Span();
break;
case 90 /* Or */:this->as.Or.value.~Span();
break;
case 91 /* Override */:this->as.Override.value.~Span();
break;
case 92 /* Private */:this->as.Private.value.~Span();
break;
case 93 /* Public */:this->as.Public.value.~Span();
break;
case 94 /* Raw */:this->as.Raw.value.~Span();
break;
case 95 /* Reflect */:this->as.Reflect.value.~Span();
break;
case 96 /* Return */:this->as.Return.value.~Span();
break;
case 97 /* Restricted */:this->as.Restricted.value.~Span();
break;
case 98 /* Sizeof */:this->as.Sizeof.value.~Span();
break;
case 99 /* Struct */:this->as.Struct.value.~Span();
break;
case 100 /* This */:this->as.This.value.~Span();
break;
case 101 /* Throw */:this->as.Throw.value.~Span();
break;
case 102 /* Throws */:this->as.Throws.value.~Span();
break;
case 103 /* True */:this->as.True.value.~Span();
break;
case 104 /* Try */:this->as.Try.value.~Span();
break;
case 105 /* Unsafe */:this->as.Unsafe.value.~Span();
break;
case 106 /* Virtual */:this->as.Virtual.value.~Span();
break;
case 107 /* Weak */:this->as.Weak.value.~Span();
break;
case 108 /* While */:this->as.While.value.~Span();
break;
case 109 /* Yield */:this->as.Yield.value.~Span();
break;
case 110 /* Guard */:this->as.Guard.value.~Span();
break;
case 111 /* Implements */:this->as.Implements.value.~Span();
break;
case 112 /* Requires */:this->as.Requires.value.~Span();
break;
case 113 /* Trait */:this->as.Trait.value.~Span();
break;
case 114 /* Garbage */:this->as.Garbage.consumed.~Optional();
this->as.Garbage.span.~Span();
break;
}
}
Jakt::utility::Span Jakt::lexer::Token::span() const {
{
{auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;Jakt::utility::Span const& span = __jakt_match_value.span;
return span;};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;Jakt::utility::Span const& span = __jakt_match_value.span;
return span;};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;Jakt::utility::Span const& span = __jakt_match_value.span;
return span;};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;Jakt::utility::Span const& span = __jakt_match_value.span;
return span;};/*case end*/
case 4 /* Semicolon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Semicolon;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 5 /* Colon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Colon;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 6 /* ColonColon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ColonColon;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 7 /* LParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LParen;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 8 /* RParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RParen;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 9 /* LCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LCurly;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 10 /* RCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RCurly;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 11 /* LSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LSquare;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 12 /* RSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RSquare;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 13 /* PercentSign */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSign;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 14 /* Plus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Plus;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 15 /* Minus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Minus;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 16 /* Equal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Equal;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 17 /* PlusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 18 /* PlusPlus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusPlus;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 19 /* MinusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 20 /* MinusMinus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusMinus;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 21 /* AsteriskEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AsteriskEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 22 /* ForwardSlashEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlashEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 23 /* PercentSignEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSignEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 24 /* NotEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NotEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 25 /* DoubleEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DoubleEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 26 /* GreaterThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThan;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 27 /* GreaterThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThanOrEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 28 /* LessThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThan;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 29 /* LessThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThanOrEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 30 /* LeftArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftArithmeticShift;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 31 /* LeftShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShift;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 32 /* LeftShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShiftEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 33 /* RightShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShift;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 34 /* RightArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightArithmeticShift;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 35 /* RightShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShiftEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 36 /* Asterisk */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Asterisk;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 37 /* Ampersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Ampersand;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 38 /* AmpersandEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 39 /* AmpersandAmpersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandAmpersand;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 40 /* Pipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Pipe;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 41 /* PipeEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipeEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 42 /* PipePipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipePipe;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 43 /* Caret */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Caret;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 44 /* CaretEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CaretEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 45 /* Dollar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dollar;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 46 /* Tilde */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Tilde;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 47 /* ForwardSlash */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlash;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 48 /* ExclamationPoint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ExclamationPoint;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 49 /* QuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMark;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMark;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMarkEqual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 52 /* Comma */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comma;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 54 /* DotDot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DotDot;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;Jakt::utility::Span const& span = __jakt_match_value.span;
return span;};/*case end*/
case 56 /* Eof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eof;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 57 /* FatArrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.FatArrow;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 58 /* Arrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Arrow;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 59 /* And */: {
auto&& __jakt_match_value = __jakt_match_variant.as.And;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 60 /* Anon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Anon;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 61 /* As */: {
auto&& __jakt_match_value = __jakt_match_variant.as.As;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 62 /* Boxed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boxed;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 63 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 64 /* Catch */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Catch;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 65 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 66 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 67 /* Cpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Cpp;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 68 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 69 /* Destructor */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Destructor;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 70 /* Else */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Else;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 71 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 72 /* Extern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Extern;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 73 /* Export */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Export;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 74 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 75 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 76 /* Fn */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fn;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 77 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 78 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 79 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 80 /* Relative */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Relative;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 81 /* In */: {
auto&& __jakt_match_value = __jakt_match_variant.as.In;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 82 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 83 /* Let */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Let;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 84 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 85 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 86 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 87 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 88 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 89 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 90 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 91 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 92 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 93 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 94 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 95 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 96 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 97 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 98 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 99 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 100 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 101 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 102 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 103 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 104 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 105 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 106 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 107 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 108 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 109 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 110 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 111 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 112 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 113 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::utility::Span const& span = __jakt_match_value.value;
return span;};/*case end*/
case 114 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;Jakt::utility::Span const& span = __jakt_match_value.span;
return span;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

Jakt::lexer::Token Jakt::lexer::Token::from_keyword_or_identifier(ByteString const string,Jakt::utility::Span const span) {
{
{auto __jakt_enum_value = string;
if (__jakt_enum_value == ByteString::from_utf8_without_validation("and"sv)) {return Jakt::lexer::Token::And(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("anon"sv)) {return Jakt::lexer::Token::Anon(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("as"sv)) {return Jakt::lexer::Token::As(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("boxed"sv)) {return Jakt::lexer::Token::Boxed(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("break"sv)) {return Jakt::lexer::Token::Break(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("catch"sv)) {return Jakt::lexer::Token::Catch(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("class"sv)) {return Jakt::lexer::Token::Class(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("continue"sv)) {return Jakt::lexer::Token::Continue(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("cpp"sv)) {return Jakt::lexer::Token::Cpp(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("defer"sv)) {return Jakt::lexer::Token::Defer(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("destructor"sv)) {return Jakt::lexer::Token::Destructor(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("else"sv)) {return Jakt::lexer::Token::Else(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("enum"sv)) {return Jakt::lexer::Token::Enum(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("extern"sv)) {return Jakt::lexer::Token::Extern(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("export"sv)) {return Jakt::lexer::Token::Export(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("false"sv)) {return Jakt::lexer::Token::False(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("for"sv)) {return Jakt::lexer::Token::For(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("fn"sv)) {return Jakt::lexer::Token::Fn(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("comptime"sv)) {return Jakt::lexer::Token::Comptime(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("if"sv)) {return Jakt::lexer::Token::If(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("import"sv)) {return Jakt::lexer::Token::Import(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("relative"sv)) {return Jakt::lexer::Token::Relative(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("in"sv)) {return Jakt::lexer::Token::In(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("is"sv)) {return Jakt::lexer::Token::Is(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("let"sv)) {return Jakt::lexer::Token::Let(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("loop"sv)) {return Jakt::lexer::Token::Loop(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("match"sv)) {return Jakt::lexer::Token::Match(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("must"sv)) {return Jakt::lexer::Token::Must(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("mut"sv)) {return Jakt::lexer::Token::Mut(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("namespace"sv)) {return Jakt::lexer::Token::Namespace(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("not"sv)) {return Jakt::lexer::Token::Not(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("or"sv)) {return Jakt::lexer::Token::Or(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("override"sv)) {return Jakt::lexer::Token::Override(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("private"sv)) {return Jakt::lexer::Token::Private(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("public"sv)) {return Jakt::lexer::Token::Public(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("raw"sv)) {return Jakt::lexer::Token::Raw(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("reflect"sv)) {return Jakt::lexer::Token::Reflect(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("return"sv)) {return Jakt::lexer::Token::Return(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("restricted"sv)) {return Jakt::lexer::Token::Restricted(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("sizeof"sv)) {return Jakt::lexer::Token::Sizeof(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("struct"sv)) {return Jakt::lexer::Token::Struct(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("this"sv)) {return Jakt::lexer::Token::This(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("throw"sv)) {return Jakt::lexer::Token::Throw(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("throws"sv)) {return Jakt::lexer::Token::Throws(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("true"sv)) {return Jakt::lexer::Token::True(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("try"sv)) {return Jakt::lexer::Token::Try(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("unsafe"sv)) {return Jakt::lexer::Token::Unsafe(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("virtual"sv)) {return Jakt::lexer::Token::Virtual(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("weak"sv)) {return Jakt::lexer::Token::Weak(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("while"sv)) {return Jakt::lexer::Token::While(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("yield"sv)) {return Jakt::lexer::Token::Yield(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("guard"sv)) {return Jakt::lexer::Token::Guard(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("requires"sv)) {return Jakt::lexer::Token::Requires(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("implements"sv)) {return Jakt::lexer::Token::Implements(span);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("trait"sv)) {return Jakt::lexer::Token::Trait(span);}else {return Jakt::lexer::Token::Identifier(string,span);}}
}
}

ByteString Jakt::lexer::LiteralPrefix::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* None */: {
return ByteString("LiteralPrefix::None"sv);
break;}
case 1 /* Hexadecimal */: {
return ByteString("LiteralPrefix::Hexadecimal"sv);
break;}
case 2 /* Octal */: {
return ByteString("LiteralPrefix::Octal"sv);
break;}
case 3 /* Binary */: {
return ByteString("LiteralPrefix::Binary"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] LiteralPrefix LiteralPrefix::None(){
LiteralPrefix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralPrefix LiteralPrefix::Hexadecimal(){
LiteralPrefix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralPrefix LiteralPrefix::Octal(){
LiteralPrefix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralPrefix LiteralPrefix::Binary(){
LiteralPrefix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
LiteralPrefix& LiteralPrefix::operator=(LiteralPrefix const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LiteralPrefix::LiteralPrefix(LiteralPrefix const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
LiteralPrefix& LiteralPrefix::operator=(LiteralPrefix &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LiteralPrefix::LiteralPrefix(LiteralPrefix &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
LiteralPrefix::~LiteralPrefix(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void LiteralPrefix::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* None */:break;
case 1 /* Hexadecimal */:break;
case 2 /* Octal */:break;
case 3 /* Binary */:break;
}
}
ByteString Jakt::lexer::LiteralPrefix::to_string() const {
{
{auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* None */:return ByteString::from_utf8_without_validation(""sv);case 1 /* Hexadecimal */:return ByteString::from_utf8_without_validation("0x"sv);case 2 /* Octal */:return ByteString::from_utf8_without_validation("0o"sv);case 3 /* Binary */:return ByteString::from_utf8_without_validation("0b"sv);default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

ByteString Jakt::lexer::LiteralSuffix::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* None */: {
return ByteString("LiteralSuffix::None"sv);
break;}
case 1 /* UZ */: {
return ByteString("LiteralSuffix::UZ"sv);
break;}
case 2 /* U8 */: {
return ByteString("LiteralSuffix::U8"sv);
break;}
case 3 /* U16 */: {
return ByteString("LiteralSuffix::U16"sv);
break;}
case 4 /* U32 */: {
return ByteString("LiteralSuffix::U32"sv);
break;}
case 5 /* U64 */: {
return ByteString("LiteralSuffix::U64"sv);
break;}
case 6 /* I8 */: {
return ByteString("LiteralSuffix::I8"sv);
break;}
case 7 /* I16 */: {
return ByteString("LiteralSuffix::I16"sv);
break;}
case 8 /* I32 */: {
return ByteString("LiteralSuffix::I32"sv);
break;}
case 9 /* I64 */: {
return ByteString("LiteralSuffix::I64"sv);
break;}
case 10 /* F32 */: {
return ByteString("LiteralSuffix::F32"sv);
break;}
case 11 /* F64 */: {
return ByteString("LiteralSuffix::F64"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] LiteralSuffix LiteralSuffix::None(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::UZ(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::U8(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::U16(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::U32(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::U64(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::I8(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::I16(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::I32(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::I64(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::F32(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::F64(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
return __jakt_uninit_enum;
}
LiteralSuffix& LiteralSuffix::operator=(LiteralSuffix const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LiteralSuffix::LiteralSuffix(LiteralSuffix const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
LiteralSuffix& LiteralSuffix::operator=(LiteralSuffix &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LiteralSuffix::LiteralSuffix(LiteralSuffix &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
LiteralSuffix::~LiteralSuffix(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void LiteralSuffix::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* None */:break;
case 1 /* UZ */:break;
case 2 /* U8 */:break;
case 3 /* U16 */:break;
case 4 /* U32 */:break;
case 5 /* U64 */:break;
case 6 /* I8 */:break;
case 7 /* I16 */:break;
case 8 /* I32 */:break;
case 9 /* I64 */:break;
case 10 /* F32 */:break;
case 11 /* F64 */:break;
}
}
ByteString Jakt::lexer::LiteralSuffix::to_string() const {
{
{auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* None */:return ByteString::from_utf8_without_validation(""sv);case 1 /* UZ */:return ByteString::from_utf8_without_validation("uz"sv);case 2 /* U8 */:return ByteString::from_utf8_without_validation("u8"sv);case 3 /* U16 */:return ByteString::from_utf8_without_validation("u16"sv);case 4 /* U32 */:return ByteString::from_utf8_without_validation("u32"sv);case 5 /* U64 */:return ByteString::from_utf8_without_validation("u64"sv);case 6 /* I8 */:return ByteString::from_utf8_without_validation("i8"sv);case 7 /* I16 */:return ByteString::from_utf8_without_validation("i16"sv);case 8 /* I32 */:return ByteString::from_utf8_without_validation("i32"sv);case 9 /* I64 */:return ByteString::from_utf8_without_validation("i64"sv);case 10 /* F32 */:return ByteString::from_utf8_without_validation("f32"sv);case 11 /* F64 */:return ByteString::from_utf8_without_validation("f64"sv);default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

}
} // namespace Jakt
