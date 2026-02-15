#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "formatter.h"
#include "parser.h"
#include "utility.h"
namespace Jakt {
namespace formatter {
void bubble_sort(JaktInternal::DynamicArray<ByteString> values) {
{
i64 i = static_cast<i64>(0LL);
while (i < JaktInternal::checked_sub(infallible_integer_cast<i64>(values.size()),static_cast<i64>(1LL))){
i64 j = static_cast<i64>(0LL);
while (j < JaktInternal::checked_sub(JaktInternal::checked_sub(infallible_integer_cast<i64>(values.size()),i),static_cast<i64>(1LL))){
if (values[j] > values[JaktInternal::checked_add(j,static_cast<i64>(1LL))]){
ByteString const tmp = values[j];
values[j] = values[JaktInternal::checked_add(j,static_cast<i64>(1LL))];
values[JaktInternal::checked_add(j,static_cast<i64>(1LL))] = tmp;
}
++j;
}
++i;
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
{auto&& __jakt_match_variant = this->token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return __jakt_format(StringView::from_string_literal("Identifier: {}"sv),name);};/*case end*/
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
return __jakt_format(StringView::from_string_literal("Eol: {}"sv),comment.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }));};/*case end*/
case 56 /* Eof */:return ByteString::from_utf8_without_validation("Eof"sv);default:return this->token_text();}/*switch end*/
}
}
}

ErrorOr<ByteString> Jakt::formatter::FormattedToken::token_text() const {
{
{auto&& __jakt_match_variant = this->token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;ByteString const& quote = __jakt_match_value.quote;
JaktInternal::Optional<ByteString> const& prefix = __jakt_match_value.prefix;
return __jakt_format(StringView::from_string_literal("{}'{}'"sv),prefix.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }),quote);};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& quote = __jakt_match_value.quote;
return __jakt_format(StringView::from_string_literal("\"{}\""sv),quote);};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;Jakt::lexer::LiteralPrefix const& prefix = __jakt_match_value.prefix;
ByteString const& number = __jakt_match_value.number;
Jakt::lexer::LiteralSuffix const& suffix = __jakt_match_value.suffix;
return __jakt_format(StringView::from_string_literal("{}{}{}"sv),prefix.to_string(),number,suffix.to_string());};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return name;};/*case end*/
case 4 /* Semicolon */:return ByteString::from_utf8_without_validation(";"sv);case 5 /* Colon */:return ByteString::from_utf8_without_validation(":"sv);case 6 /* ColonColon */:return ByteString::from_utf8_without_validation("::"sv);case 7 /* LParen */:return ByteString::from_utf8_without_validation("("sv);case 8 /* RParen */:return ByteString::from_utf8_without_validation(")"sv);case 9 /* LCurly */:return ByteString::from_utf8_without_validation("{"sv);case 10 /* RCurly */:return ByteString::from_utf8_without_validation("}"sv);case 11 /* LSquare */:return ByteString::from_utf8_without_validation("["sv);case 12 /* RSquare */:return ByteString::from_utf8_without_validation("]"sv);case 13 /* PercentSign */:return ByteString::from_utf8_without_validation("%"sv);case 14 /* Plus */:return ByteString::from_utf8_without_validation("+"sv);case 15 /* Minus */:return ByteString::from_utf8_without_validation("-"sv);case 16 /* Equal */:return ByteString::from_utf8_without_validation("="sv);case 17 /* PlusEqual */:return ByteString::from_utf8_without_validation("+="sv);case 18 /* PlusPlus */:return ByteString::from_utf8_without_validation("++"sv);case 19 /* MinusEqual */:return ByteString::from_utf8_without_validation("-="sv);case 20 /* MinusMinus */:return ByteString::from_utf8_without_validation("--"sv);case 21 /* AsteriskEqual */:return ByteString::from_utf8_without_validation("*="sv);case 22 /* ForwardSlashEqual */:return ByteString::from_utf8_without_validation("/="sv);case 23 /* PercentSignEqual */:return ByteString::from_utf8_without_validation("%="sv);case 24 /* NotEqual */:return ByteString::from_utf8_without_validation("!="sv);case 25 /* DoubleEqual */:return ByteString::from_utf8_without_validation("=="sv);case 26 /* GreaterThan */:return ByteString::from_utf8_without_validation(">"sv);case 27 /* GreaterThanOrEqual */:return ByteString::from_utf8_without_validation(">="sv);case 28 /* LessThan */:return ByteString::from_utf8_without_validation("<"sv);case 29 /* LessThanOrEqual */:return ByteString::from_utf8_without_validation("<="sv);case 30 /* LeftArithmeticShift */:return ByteString::from_utf8_without_validation("<<<"sv);case 31 /* LeftShift */:return ByteString::from_utf8_without_validation("<<"sv);case 32 /* LeftShiftEqual */:return ByteString::from_utf8_without_validation("<<="sv);case 33 /* RightShift */:return ByteString::from_utf8_without_validation(">>"sv);case 34 /* RightArithmeticShift */:return ByteString::from_utf8_without_validation(">>>"sv);case 35 /* RightShiftEqual */:return ByteString::from_utf8_without_validation(">>="sv);case 36 /* Asterisk */:return ByteString::from_utf8_without_validation("*"sv);case 37 /* Ampersand */:return ByteString::from_utf8_without_validation("&"sv);case 38 /* AmpersandEqual */:return ByteString::from_utf8_without_validation("&="sv);case 39 /* AmpersandAmpersand */:return ByteString::from_utf8_without_validation("&&"sv);case 40 /* Pipe */:return ByteString::from_utf8_without_validation("|"sv);case 41 /* PipeEqual */:return ByteString::from_utf8_without_validation("|="sv);case 42 /* PipePipe */:return ByteString::from_utf8_without_validation("||"sv);case 43 /* Caret */:return ByteString::from_utf8_without_validation("^"sv);case 44 /* CaretEqual */:return ByteString::from_utf8_without_validation("^="sv);case 45 /* Dollar */:return ByteString::from_utf8_without_validation("$"sv);case 46 /* Tilde */:return ByteString::from_utf8_without_validation("~"sv);case 47 /* ForwardSlash */:return ByteString::from_utf8_without_validation("/"sv);case 48 /* ExclamationPoint */:return ByteString::from_utf8_without_validation("!"sv);case 49 /* QuestionMark */:return ByteString::from_utf8_without_validation("?"sv);case 50 /* QuestionMarkQuestionMark */:return ByteString::from_utf8_without_validation("??"sv);case 51 /* QuestionMarkQuestionMarkEqual */:return ByteString::from_utf8_without_validation("??="sv);case 52 /* Comma */:return ByteString::from_utf8_without_validation(","sv);case 53 /* Dot */:return ByteString::from_utf8_without_validation("."sv);case 54 /* DotDot */:return ByteString::from_utf8_without_validation(".."sv);case 55 /* Eol */:return ByteString::from_utf8_without_validation(""sv);case 56 /* Eof */:return ByteString::from_utf8_without_validation(""sv);case 57 /* FatArrow */:return ByteString::from_utf8_without_validation("=>"sv);case 58 /* Arrow */:return ByteString::from_utf8_without_validation("->"sv);case 59 /* And */:return ByteString::from_utf8_without_validation("and"sv);case 60 /* Anon */:return ByteString::from_utf8_without_validation("anon"sv);case 61 /* As */:return ByteString::from_utf8_without_validation("as"sv);case 62 /* Boxed */:return ByteString::from_utf8_without_validation("boxed"sv);case 63 /* Break */:return ByteString::from_utf8_without_validation("break"sv);case 64 /* Catch */:return ByteString::from_utf8_without_validation("catch"sv);case 65 /* Class */:return ByteString::from_utf8_without_validation("class"sv);case 66 /* Continue */:return ByteString::from_utf8_without_validation("continue"sv);case 67 /* Cpp */:return ByteString::from_utf8_without_validation("cpp"sv);case 68 /* Defer */:return ByteString::from_utf8_without_validation("defer"sv);case 69 /* Destructor */:return ByteString::from_utf8_without_validation("destructor"sv);case 70 /* Else */:return ByteString::from_utf8_without_validation("else"sv);case 71 /* Enum */:return ByteString::from_utf8_without_validation("enum"sv);case 72 /* Extern */:return ByteString::from_utf8_without_validation("extern"sv);case 73 /* Export */:return ByteString::from_utf8_without_validation("export"sv);case 74 /* False */:return ByteString::from_utf8_without_validation("false"sv);case 75 /* For */:return ByteString::from_utf8_without_validation("for"sv);case 76 /* Fn */:return ByteString::from_utf8_without_validation("fn"sv);case 77 /* Comptime */:return ByteString::from_utf8_without_validation("comptime"sv);case 78 /* If */:return ByteString::from_utf8_without_validation("if"sv);case 79 /* Import */:return ByteString::from_utf8_without_validation("import"sv);case 80 /* Relative */:return ByteString::from_utf8_without_validation("relative"sv);case 81 /* In */:return ByteString::from_utf8_without_validation("in"sv);case 82 /* Is */:return ByteString::from_utf8_without_validation("is"sv);case 83 /* Let */:return ByteString::from_utf8_without_validation("let"sv);case 84 /* Loop */:return ByteString::from_utf8_without_validation("loop"sv);case 85 /* Match */:return ByteString::from_utf8_without_validation("match"sv);case 87 /* Mut */:return ByteString::from_utf8_without_validation("mut"sv);case 88 /* Namespace */:return ByteString::from_utf8_without_validation("namespace"sv);case 89 /* Not */:return ByteString::from_utf8_without_validation("not"sv);case 90 /* Or */:return ByteString::from_utf8_without_validation("or"sv);case 92 /* Private */:return ByteString::from_utf8_without_validation("private"sv);case 93 /* Public */:return ByteString::from_utf8_without_validation("public"sv);case 94 /* Raw */:return ByteString::from_utf8_without_validation("raw"sv);case 96 /* Return */:return ByteString::from_utf8_without_validation("return"sv);case 97 /* Restricted */:return ByteString::from_utf8_without_validation("restricted"sv);case 98 /* Sizeof */:return ByteString::from_utf8_without_validation("sizeof"sv);case 99 /* Struct */:return ByteString::from_utf8_without_validation("struct"sv);case 100 /* This */:return ByteString::from_utf8_without_validation("this"sv);case 101 /* Throw */:return ByteString::from_utf8_without_validation("throw"sv);case 102 /* Throws */:return ByteString::from_utf8_without_validation("throws"sv);case 103 /* True */:return ByteString::from_utf8_without_validation("true"sv);case 104 /* Try */:return ByteString::from_utf8_without_validation("try"sv);case 105 /* Unsafe */:return ByteString::from_utf8_without_validation("unsafe"sv);case 107 /* Weak */:return ByteString::from_utf8_without_validation("weak"sv);case 108 /* While */:return ByteString::from_utf8_without_validation("while"sv);case 109 /* Yield */:return ByteString::from_utf8_without_validation("yield"sv);case 110 /* Guard */:return ByteString::from_utf8_without_validation("guard"sv);case 91 /* Override */:return ByteString::from_utf8_without_validation("override"sv);case 106 /* Virtual */:return ByteString::from_utf8_without_validation("virtual"sv);case 111 /* Implements */:return ByteString::from_utf8_without_validation("implements"sv);case 112 /* Requires */:return ByteString::from_utf8_without_validation("requires"sv);case 113 /* Trait */:return ByteString::from_utf8_without_validation("trait"sv);case 86 /* Must */:return ByteString::from_utf8_without_validation("must"sv);case 95 /* Reflect */:return ByteString::from_utf8_without_validation("reflect"sv);case 114 /* Garbage */:return ByteString::from_utf8_without_validation(""sv);default: VERIFY_NOT_REACHED();}/*switch end*/
}
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
JaktInternal::DynamicArray<u8> const old_file_contents = compiler->current_file_contents;
compiler->current_file_contents = source;
ScopeGuard __jakt_var_135([&] {
{
compiler->current_file_contents = old_file_contents;
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
return Jakt::formatter::FormattedToken(token,this->indent,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
}

Jakt::formatter::FormattedToken Jakt::formatter::Stage0::formatted_token(Jakt::lexer::Token const token,JaktInternal::DynamicArray<u8> const trailing_trivia,JaktInternal::DynamicArray<u8> const preceding_trivia) const {
{
return Jakt::formatter::FormattedToken(token,this->indent,trailing_trivia,preceding_trivia);
}
}

Jakt::lexer::Token Jakt::formatter::Stage0::peek(i64 const offset) const {
{
size_t const effective_index = [&]() -> size_t { auto __jakt_enum_value = offset;
if (__jakt_enum_value == static_cast<i64>(0LL)) {return this->index;}else {return infallible_integer_cast<size_t>(JaktInternal::checked_sub(JaktInternal::checked_add(infallible_integer_cast<i64>(this->index),offset),static_cast<i64>(1LL)));} 
}();
if (effective_index >= this->tokens.size()){
return Jakt::lexer::Token::Eof(this->tokens.last().value().span());
}
return this->tokens[effective_index];
}
}

bool Jakt::formatter::Stage0::line_has_indent() const {
{
i64 offset = static_cast<i64>(0LL);
for (;;){
Jakt::lexer::Token const token = this->peek(offset);
if (token.__jakt_init_index() == 9 /* LCurly */){
return true;
}
if ((token.__jakt_init_index() == 55 /* Eol */) || (token.__jakt_init_index() == 56 /* Eof */)){
break;
}
offset++;
}
return false;
}
}

Jakt::lexer::Token Jakt::formatter::Stage0::consume() {
{
return this->tokens[this->index++];
}
}

Jakt::formatter::State Jakt::formatter::Stage0::state() const {
{
return this->states.last().value();
}
}

ErrorOr<void> Jakt::formatter::Stage0::push_state(Jakt::formatter::State const state) {
{
this->states.push(state);
}
return {};
}

void Jakt::formatter::Stage0::pop_state() {
{
JaktInternal::Optional<Jakt::formatter::State> const dummy = this->states.pop();
}
}

ErrorOr<void> Jakt::formatter::Stage0::replace_state(Jakt::formatter::State const state) {
{
JaktInternal::Optional<Jakt::formatter::State> const dummy = this->states.pop();
this->states.push(state);
}
return {};
}

JaktInternal::DynamicArray<u8> Jakt::formatter::Stage0::to_array(ByteString const x) {
{
JaktInternal::DynamicArray<u8> res = DynamicArray<u8>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(x.length())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
res.push(x.byte_at(i));
}

}
}

return res;
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::formatted_peek() {
{
JaktInternal::DynamicArray<Jakt::formatter::State> const states_cache = this->states[JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}].to_array();
size_t const index_cache = this->index;
JaktInternal::Optional<Jakt::formatter::FormattedToken> const token = TRY((this->next_impl(true)));
this->index = index_cache;
this->states = states_cache;
return token;
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next() {
{
return this->next_impl(false);
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_extern_context(Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 99 /* Struct */:case 65 /* Class */:{
TRY((this->push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(token),!(token.__jakt_init_index() == 88 /* Namespace */),false,static_cast<size_t>(0ULL),true))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((token.__jakt_init_index() == 88 /* Namespace */) || (!(this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 28 /* LessThan */))){
trailing_trivia.push(static_cast<u8>(u8' '));
}
return this->formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_toplevel_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,bool const is_extern,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 72 /* Extern */:{
{auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 65 /* Class */:case 99 /* Struct */:{
TRY((this->push_state(Jakt::formatter::State::Extern())));
}
goto __jakt_label_191;default:{
}
goto __jakt_label_191;}/*switch end*/
}goto __jakt_label_191; __jakt_label_191:;;
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
{
if ((name == ByteString::from_utf8_without_validation("type"sv)) && (this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 3 /* Identifier */)){
TRY((this->push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(token),true,false,static_cast<size_t>(0ULL),is_extern))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 71 /* Enum */:case 65 /* Class */:case 99 /* Struct */:case 113 /* Trait */:case 76 /* Fn */:case 77 /* Comptime */:case 88 /* Namespace */:{
TRY((this->push_state(Jakt::formatter::State::EntityDeclaration(Jakt::formatter::Entity::from_token(token),!(token.__jakt_init_index() == 88 /* Namespace */),false,static_cast<size_t>(0ULL),is_extern))));
JaktInternal::DynamicArray<u8> trailing_trivia = DynamicArray<u8>::create_with({});
if ((token.__jakt_init_index() == 88 /* Namespace */) || (!(this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 28 /* LessThan */))){
trailing_trivia.push(static_cast<u8>(u8' '));
}
return this->formatted_token(token,trailing_trivia,DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 11 /* LSquare */:{
TRY((this->replace_state(Jakt::formatter::State::Toplevel(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),is_extern))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 12 /* RSquare */:{
if (open_squares == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::Toplevel(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),is_extern))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 7 /* LParen */:{
TRY((this->replace_state(Jakt::formatter::State::Toplevel(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,is_extern))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:{
if (open_parens == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::Toplevel(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,is_extern))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 9 /* LCurly */:{
TRY((this->replace_state(Jakt::formatter::State::Toplevel(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,is_extern))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 10 /* RCurly */:{
if (open_curlies == static_cast<size_t>(0ULL)){
this->pop_state();
this->index -= static_cast<size_t>(1ULL);
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::Toplevel(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,is_extern))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 5 /* Colon */:{
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 79 /* Import */:{
TRY((this->push_state(Jakt::formatter::State::Import(this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 72 /* Extern */))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 93 /* Public */:case 92 /* Private */:case 106 /* Virtual */:case 91 /* Override */:case 62 /* Boxed */:case 105 /* Unsafe */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 97 /* Restricted */:{
TRY((this->push_state(Jakt::formatter::State::RestrictionList())));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 16 /* Equal */:{
TRY((this->push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false,Jakt::formatter::ExpressionMode::AtExpressionStart(),static_cast<size_t>(0ULL)))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_import_context(bool const is_extern,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 72 /* Extern */:case 61 /* As */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 3 /* Identifier */:{
if ((!is_extern) && (this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 7 /* LParen */)){
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
if (this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 6 /* ColonColon */){
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
if ((!is_extern) && ((!(this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 9 /* LCurly */)) && (!(this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 61 /* As */)))){
this->pop_state();
}
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 7 /* LParen */:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));case 9 /* LCurly */:{
if (is_extern){
TRY((this->push_state(Jakt::formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern))));
}
else {
TRY((this->push_state(Jakt::formatter::State::ImportList(true))));
}

return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 10 /* RCurly */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:{
return this->formatted_token(token,[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}(),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 6 /* ColonColon */:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));default:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_implements_context(Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_import_list_context(bool const emitted_comma,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */:{
this->pop_state();
this->index--;
return this->next_impl(true);
}
case 52 /* Comma */:{
TRY((this->replace_state(Jakt::formatter::State::ImportList(true))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 55 /* Eol */:{
return this->next();
}
default:{
JaktInternal::DynamicArray<ByteString> collection = DynamicArray<ByteString>::create_with({});
ByteString output = ByteString::from_utf8_without_validation(""sv);
Jakt::utility::Span const span = token.span();
Jakt::lexer::Token local_token = token;
while (!(local_token.__jakt_init_index() == 10 /* RCurly */)){
Jakt::lexer::Token __jakt_tmp295 = local_token;
if (__jakt_tmp295.__jakt_init_index() == 3 /* Identifier */){
ByteString const name = __jakt_tmp295.as.Identifier.name;
collection.push(name);
}
local_token = this->consume();
}
Jakt::formatter::bubble_sort(collection);
bool first = true;
bool overflow = false;
size_t current_len = static_cast<size_t>(0ULL);
size_t const indent_amount = static_cast<size_t>(4ULL);
{
JaktInternal::ArrayIterator<ByteString> _magic = collection.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString item = _magic_value.value();
{
if (JaktInternal::checked_add(JaktInternal::checked_add(current_len,item.length()),static_cast<size_t>(2ULL)) > JaktInternal::checked_sub(static_cast<size_t>(120ULL),indent_amount)){
overflow = true;
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("\n"sv));
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(indent_amount)};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(" "sv));
}

}
}

current_len = indent_amount;
}
else if (!first){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(", "sv));
current_len += static_cast<size_t>(2ULL);
}
else {
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,item);
current_len += item.length();
}

}
}

if (overflow){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(indent_amount)};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
output = (ByteString::from_utf8_without_validation(" "sv) + output);
}

}
}

output = (ByteString::from_utf8_without_validation("\n"sv) + output);
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("\n"sv));
}
else {
output = ((ByteString::from_utf8_without_validation(" "sv) + output) + ByteString::from_utf8_without_validation(" "sv));
}

this->pop_state();
this->index--;
return this->formatted_token(Jakt::lexer::Token::Identifier(output,span),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_entity_declaration_context(Jakt::formatter::Entity const entity,bool const accept_generics,bool const has_generics,size_t const generic_nesting,bool const is_extern,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */:{
if (accept_generics){
TRY((this->replace_state(Jakt::formatter::State::EntityDeclaration(entity,accept_generics,true,JaktInternal::checked_add(generic_nesting,static_cast<size_t>(1ULL)),is_extern))));
}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 26 /* GreaterThan */:{
if (accept_generics){
if (generic_nesting > static_cast<size_t>(1ULL)){
TRY((this->replace_state(Jakt::formatter::State::EntityDeclaration(entity,accept_generics,has_generics,JaktInternal::checked_sub(generic_nesting,static_cast<size_t>(1ULL)),is_extern))));
}
else {
TRY((this->replace_state(Jakt::formatter::State::EntityDefinition(entity,is_extern))));
}

}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 3 /* Identifier */:{
if ((generic_nesting == static_cast<size_t>(0ULL)) && ((!(this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 28 /* LessThan */)) && (!has_generics))){
TRY((this->replace_state(Jakt::formatter::State::EntityDefinition(entity,is_extern))));
}
if (this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 111 /* Implements */){
TRY((this->push_state(Jakt::formatter::State::Implements())));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 10 /* RCurly */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 55 /* Eol */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 93 /* Public */:case 92 /* Private */:case 106 /* Virtual */:case 91 /* Override */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 97 /* Restricted */:{
TRY((this->push_state(Jakt::formatter::State::RestrictionList())));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 112 /* Requires */:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_entity_definition_context(Jakt::formatter::Entity const entity,bool const is_extern,i64& indent_change,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = entity;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */:case 0 /* Struct */:case 2 /* Namespace */:{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(-static_cast<i64>(1LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:case 9 /* LCurly */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}());
}
VERIFY_NOT_REACHED();
case 9 /* LCurly */:{
TRY((this->push_state(Jakt::formatter::State::Toplevel(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),is_extern))));
return this->formatted_token(token,[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:case 10 /* RCurly */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}(),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 5 /* Colon */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 16 /* Equal */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));case 3 /* Identifier */:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));default:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));}/*switch end*/
}case 3 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;bool const& arrow = __jakt_match_value.arrow;
bool const& indented = __jakt_match_value.indented;
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 57 /* FatArrow */:{
bool const next_is_eol = this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 55 /* Eol */;
TRY((this->replace_state(Jakt::formatter::State::EntityDefinition(Jakt::formatter::Entity::Function(true,next_is_eol),is_extern))));
if (next_is_eol){
if (!this->already_seen_enclosure_in_current_line){
this->already_seen_enclosure_in_current_line = true;
this->dedents_to_skip.push(static_cast<size_t>(0ULL));
}
indent_change += static_cast<i64>(1LL);
this->dedents_to_skip[JaktInternal::checked_sub(this->dedents_to_skip.size(),static_cast<size_t>(1ULL))] += static_cast<size_t>(1ULL);
}
size_t eols_allowed = static_cast<size_t>(0ULL);
if (next_is_eol){
eols_allowed = static_cast<size_t>(1ULL);
}
TRY((this->push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),eols_allowed,false,Jakt::formatter::ExpressionMode::BeforeExpressions(),static_cast<size_t>(0ULL)))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 58 /* Arrow */:{
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 7 /* LParen */:{
TRY((this->push_state(Jakt::formatter::State::ParameterList(static_cast<size_t>(0ULL)))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:return this->formatted_token(token,[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 102 /* Throws */:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});default:return DynamicArray<u8>::create_with({});}/*switch end*/
 
}(),DynamicArray<u8>::create_with({}));case 9 /* LCurly */:{
TRY((this->push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),JaktInternal::OptionalNone(),false,Jakt::formatter::ExpressionMode::OutsideExpression(),static_cast<size_t>(0ULL)))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 10 /* RCurly */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 55 /* Eol */:{
if (!arrow){
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
this->pop_state();
if (indented){
if (this->dedents_to_skip.last().value() == static_cast<size_t>(1ULL)){
if (this->dedents_to_skip.size() > static_cast<size_t>(1ULL)){
JaktInternal::Optional<size_t> const dummy = this->dedents_to_skip.pop();
}
indent_change -= static_cast<i64>(1LL);
}
else if (this->dedents_to_skip.last().value() > static_cast<size_t>(0ULL)){
this->dedents_to_skip[JaktInternal::checked_sub(this->dedents_to_skip.size(),static_cast<size_t>(1ULL))] -= static_cast<size_t>(1ULL);
}
}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_statement_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,size_t const arrow_indents,JaktInternal::Optional<size_t> const allow_eol,bool const inserted_comma,Jakt::formatter::ExpressionMode const expression_mode,size_t const dedents_on_open_curly,i64& indent_change,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 83 /* Let */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly))));
TRY((this->push_state(Jakt::formatter::State::VariableDeclaration(static_cast<size_t>(0ULL)))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 87 /* Mut */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
if (expression_mode.__jakt_init_index() == 0 /* OutsideExpression */){
TRY((this->push_state(Jakt::formatter::State::VariableDeclaration(static_cast<size_t>(0ULL)))));
}
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 85 /* Match */:case 75 /* For */:case 108 /* While */:case 78 /* If */:case 104 /* Try */:case 84 /* Loop */:case 110 /* Guard */:case 68 /* Defer */:{
size_t const added_indent = [&]() -> size_t { auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */:case 75 /* For */:case 108 /* While */:case 78 /* If */:case 110 /* Guard */:{
size_t indent = static_cast<size_t>(1ULL);
if (this->line_has_indent()){
indent = static_cast<size_t>(0ULL);
}
return indent;
}
VERIFY_NOT_REACHED();
default:return static_cast<size_t>(0ULL);}/*switch end*/
 
}();
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_add(dedents_on_open_curly,added_indent)))));
indent_change += infallible_integer_cast<i64>(added_indent);
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 64 /* Catch */:case 70 /* Else */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly))));
return this->formatted_token(token,[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:case 57 /* FatArrow */:case 7 /* LParen */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}(),[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(-static_cast<i64>(1LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:case 40 /* Pipe */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}());
}
VERIFY_NOT_REACHED();
case 55 /* Eol */:{
if ((expression_mode.__jakt_init_index() == 1 /* BeforeExpressions */) && (this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 55 /* Eol */)){
return this->next();
}
if (allow_eol.has_value() && ((allow_eol.value() == static_cast<size_t>(0ULL)) && (JaktInternal::checked_add(JaktInternal::checked_add(open_parens,open_curlies),open_squares) == static_cast<size_t>(0ULL)))){
this->pop_state();
this->index--;
return this->next_impl(true);
}
size_t new_arrow_indents = arrow_indents;
JaktInternal::Optional<size_t> new_allow_eol = allow_eol;
Jakt::formatter::ExpressionMode new_expression_mode = Jakt::formatter::ExpressionMode::OutsideExpression();
if (expression_mode.__jakt_init_index() == 1 /* BeforeExpressions */){
new_expression_mode = Jakt::formatter::ExpressionMode::BeforeExpressions();
}
else {
if (allow_eol.has_value() && (allow_eol.value() > static_cast<size_t>(0ULL))){
new_allow_eol = JaktInternal::checked_sub(allow_eol.value(),static_cast<size_t>(1ULL));
}
if (arrow_indents > static_cast<size_t>(0ULL)){
if (this->dedents_to_skip.last().value() == static_cast<size_t>(1ULL)){
if (this->dedents_to_skip.size() > static_cast<size_t>(1ULL)){
JaktInternal::Optional<size_t> const dummy = this->dedents_to_skip.pop();
}
indent_change -= static_cast<i64>(1LL);
}
else if (this->dedents_to_skip.last().value() > static_cast<size_t>(0ULL)){
this->dedents_to_skip[JaktInternal::checked_sub(this->dedents_to_skip.size(),static_cast<size_t>(1ULL))] -= static_cast<size_t>(1ULL);
}
new_arrow_indents--;
}
}

TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,new_arrow_indents,new_allow_eol,inserted_comma,new_expression_mode,dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 76 /* Fn */:{
TRY((this->push_state(Jakt::formatter::State::FunctionTypeContext(false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
{auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));default:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
VERIFY_NOT_REACHED();
case 96 /* Return */:case 101 /* Throw */:case 109 /* Yield */:{auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* Semicolon */:case 55 /* Eol */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::OutsideExpression(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
}/*switch end*/
}case 57 /* FatArrow */:{
bool const next_is_eol = this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 55 /* Eol */;
size_t new_arrow_indents = arrow_indents;
if (next_is_eol){
if (!this->already_seen_enclosure_in_current_line){
this->already_seen_enclosure_in_current_line = true;
this->dedents_to_skip.push(static_cast<size_t>(0ULL));
}
indent_change += static_cast<i64>(1LL);
this->dedents_to_skip[JaktInternal::checked_sub(this->dedents_to_skip.size(),static_cast<size_t>(1ULL))] += static_cast<size_t>(1ULL);
new_arrow_indents++;
}
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,new_arrow_indents,allow_eol,inserted_comma,[&]() -> Jakt::formatter::ExpressionMode { auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LCurly */:return Jakt::formatter::ExpressionMode::OutsideExpression();default:return Jakt::formatter::ExpressionMode::BeforeExpressions();}/*switch end*/
 
}(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 11 /* LSquare */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 12 /* RSquare */:{
if (open_squares == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 7 /* LParen */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:{
if (open_parens == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::StatementContext(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 9 /* LCurly */:{
size_t dedented = static_cast<size_t>(0ULL);
if (dedents_on_open_curly > static_cast<size_t>(0ULL)){
this->indent -= static_cast<size_t>(1ULL);
dedented = static_cast<size_t>(1ULL);
}
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),JaktInternal::checked_sub(dedents_on_open_curly,dedented)))));
return this->formatted_token(token,[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* AtExpressionStart */:case 1 /* BeforeExpressions */:return DynamicArray<u8>::create_with({});default:{auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:case 10 /* RCurly */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
}}/*switch end*/
 
}(),[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(-static_cast<i64>(1LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 70 /* Else */:case 104 /* Try */:case 64 /* Catch */:case 16 /* Equal */:case 57 /* FatArrow */:case 84 /* Loop */:case 68 /* Defer */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}());
}
VERIFY_NOT_REACHED();
case 10 /* RCurly */:{
if (open_curlies == static_cast<size_t>(0ULL)){
this->pop_state();
this->index -= static_cast<size_t>(1ULL);
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(-static_cast<i64>(1LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:case 9 /* LCurly */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}());
}
VERIFY_NOT_REACHED();
case 89 /* Not */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 98 /* Sizeof */:{
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 5 /* Colon */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
return this->formatted_token(token,[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}(),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 15 /* Minus */:case 36 /* Asterisk */:case 37 /* Ampersand */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
JaktInternal::DynamicArray<u8> const trivia = [&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = expression_mode;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* InExpression */:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});default:return DynamicArray<u8>::create_with({});}/*switch end*/
 
}();
return this->formatted_token(token,trivia,trivia);
}
VERIFY_NOT_REACHED();
case 13 /* PercentSign */:case 14 /* Plus */:case 16 /* Equal */:case 40 /* Pipe */:case 17 /* PlusEqual */:case 19 /* MinusEqual */:case 21 /* AsteriskEqual */:case 22 /* ForwardSlashEqual */:case 23 /* PercentSignEqual */:case 24 /* NotEqual */:case 25 /* DoubleEqual */:case 26 /* GreaterThan */:case 27 /* GreaterThanOrEqual */:case 28 /* LessThan */:case 29 /* LessThanOrEqual */:case 30 /* LeftArithmeticShift */:case 31 /* LeftShift */:case 33 /* RightShift */:case 32 /* LeftShiftEqual */:case 34 /* RightArithmeticShift */:case 35 /* RightShiftEqual */:case 38 /* AmpersandEqual */:case 41 /* PipeEqual */:case 43 /* Caret */:case 44 /* CaretEqual */:case 47 /* ForwardSlash */:case 50 /* QuestionMarkQuestionMark */:case 51 /* QuestionMarkQuestionMarkEqual */:case 59 /* And */:case 81 /* In */:case 90 /* Or */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 82 /* Is */:{
TRY((this->push_state(Jakt::formatter::State::MatchPattern(static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 61 /* As */:return this->formatted_token(token,[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 49 /* QuestionMark */:case 48 /* ExclamationPoint */:return DynamicArray<u8>::create_with({});default:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});}/*switch end*/
 
}(),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));case 49 /* QuestionMark */:case 48 /* ExclamationPoint */:{auto&& __jakt_match_variant = this->peek(-static_cast<i64>(1LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 61 /* As */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}case 3 /* Identifier */:case 2 /* Number */:{
if ((this->peek(-static_cast<i64>(1LL)).__jakt_init_index() == 3 /* Identifier */) && (!inserted_comma)){
this->index--;
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,true,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly))));
return this->formatted_token(Jakt::lexer::Token::Comma(token.span()),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,false,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly))));
if (this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 7 /* LParen */){
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
if (!(this->peek(static_cast<i64>(0LL)).__jakt_init_index() == 28 /* LessThan */)){
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
i64 open_angles = static_cast<i64>(1LL);
i64 lookahead_index = static_cast<i64>(2LL);
while (open_angles > static_cast<i64>(0LL)){
{auto&& __jakt_match_variant = this->peek(lookahead_index++);
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */:{
open_angles += static_cast<i64>(1LL);
}
goto __jakt_label_192;case 26 /* GreaterThan */:{
open_angles -= static_cast<i64>(1LL);
}
goto __jakt_label_192;case 55 /* Eol */:case 13 /* PercentSign */:case 14 /* Plus */:case 15 /* Minus */:case 16 /* Equal */:case 17 /* PlusEqual */:case 19 /* MinusEqual */:case 21 /* AsteriskEqual */:case 22 /* ForwardSlashEqual */:case 23 /* PercentSignEqual */:case 24 /* NotEqual */:case 25 /* DoubleEqual */:case 27 /* GreaterThanOrEqual */:case 29 /* LessThanOrEqual */:case 30 /* LeftArithmeticShift */:case 31 /* LeftShift */:case 33 /* RightShift */:case 32 /* LeftShiftEqual */:case 34 /* RightArithmeticShift */:case 35 /* RightShiftEqual */:case 36 /* Asterisk */:case 38 /* AmpersandEqual */:case 40 /* Pipe */:case 41 /* PipeEqual */:case 43 /* Caret */:case 44 /* CaretEqual */:case 47 /* ForwardSlash */:case 50 /* QuestionMarkQuestionMark */:case 51 /* QuestionMarkQuestionMarkEqual */:case 59 /* And */:case 81 /* In */:case 82 /* Is */:case 90 /* Or */:{
break;
}
goto __jakt_label_192;default:{
}
goto __jakt_label_192;}/*switch end*/
break;}goto __jakt_label_192; __jakt_label_192:;;
}
if ((open_angles == static_cast<i64>(0LL)) && (this->peek(lookahead_index).__jakt_init_index() == 7 /* LParen */)){
TRY((this->push_state(Jakt::formatter::State::GenericCallTypeParams(static_cast<size_t>(0ULL)))));
}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 4 /* Semicolon */:{
if (open_squares == static_cast<size_t>(0ULL)){
{auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */:return this->next();default:return this->formatted_token(Jakt::lexer::Token::Eol(JaktInternal::OptionalNone(),token.span()),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 94 /* Raw */:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::AtExpressionStart(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 95 /* Reflect */:{
TRY((this->replace_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return Jakt::formatter::FormattedToken(token,this->indent,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:{
TRY((this->replace_state(Jakt::formatter::State::StatementContext(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,Jakt::formatter::ExpressionMode::InExpression(),dedents_on_open_curly))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_generic_call_type_params_context(size_t const open_angles,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */:{
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 26 /* GreaterThan */:{
if (open_angles <= static_cast<size_t>(1ULL)){
this->pop_state();
}
else {
TRY((this->replace_state(Jakt::formatter::State::GenericCallTypeParams(JaktInternal::checked_sub(open_angles,static_cast<size_t>(1ULL))))));
}

return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:{
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_variable_declaration_context(size_t const open_parens,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Colon */:{
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 7 /* LParen */:{
TRY((this->replace_state(Jakt::formatter::State::VariableDeclaration(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL))))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:{
if (open_parens == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::VariableDeclaration(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL))))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 16 /* Equal */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_restriction_list_context(Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 52 /* Comma */:{
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_parameter_list_context(size_t const open_parens,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 60 /* Anon */:case 87 /* Mut */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 5 /* Colon */:{
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 16 /* Equal */:{
TRY((this->push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false,Jakt::formatter::ExpressionMode::AtExpressionStart(),static_cast<size_t>(0ULL)))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 7 /* LParen */:{
TRY((this->replace_state(Jakt::formatter::State::ParameterList(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL))))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:{
if (open_parens == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::ParameterList(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL))))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_type_context(size_t const open_parens,size_t const open_curlies,size_t const open_squares,size_t const open_angles,bool const seen_start,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Colon */:{
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 28 /* LessThan */:{
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,JaktInternal::checked_add(open_angles,static_cast<size_t>(1ULL)),seen_start))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 26 /* GreaterThan */:{
if (open_angles == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,JaktInternal::checked_sub(open_angles,static_cast<size_t>(1ULL)),seen_start))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 55 /* Eol */:{
if (JaktInternal::checked_add(JaktInternal::checked_add(JaktInternal::checked_add(open_parens,open_curlies),open_squares),open_angles) == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 11 /* LSquare */:{
if (seen_start){
this->index--;
this->pop_state();
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,JaktInternal::checked_add(open_squares,static_cast<size_t>(1ULL)),open_angles,true))));
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 12 /* RSquare */:{
if (open_squares == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,JaktInternal::checked_sub(open_squares,static_cast<size_t>(1ULL)),open_angles,seen_start))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 7 /* LParen */:{
if (seen_start){
this->index--;
this->pop_state();
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::TypeContext(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,open_angles,true))));
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:{
if (open_parens == static_cast<size_t>(0ULL)){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::TypeContext(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),open_curlies,open_squares,open_angles,seen_start))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 9 /* LCurly */:{
if (seen_start){
this->index--;
this->pop_state();
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,JaktInternal::checked_add(open_curlies,static_cast<size_t>(1ULL)),open_squares,open_angles,true))));
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 10 /* RCurly */:{
if (open_curlies == static_cast<size_t>(0ULL)){
this->pop_state();
this->index -= static_cast<size_t>(1ULL);
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,JaktInternal::checked_sub(open_curlies,static_cast<size_t>(1ULL)),open_squares,open_angles,seen_start))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 94 /* Raw */:case 87 /* Mut */:{
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 37 /* Ampersand */:{
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 76 /* Fn */:{
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true))));
TRY((this->push_state(Jakt::formatter::State::FunctionTypeContext(false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:{
if (JaktInternal::checked_add(open_angles,open_parens) == static_cast<size_t>(0ULL)){
this->index--;
this->pop_state();
return this->next_impl(true);
}
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 3 /* Identifier */:{
TRY((this->replace_state(Jakt::formatter::State::TypeContext(open_parens,open_curlies,open_squares,open_angles,true))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 107 /* Weak */:return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));case 16 /* Equal */:case 58 /* Arrow */:case 57 /* FatArrow */:{
this->pop_state();
this->index--;
return this->next_impl(true);
}
default:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_capture_list_context(Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */:{
this->pop_state();
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 52 /* Comma */:case 87 /* Mut */:{
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
default:{
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_function_type_context(bool const seen_final_type,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 57 /* FatArrow */:case 9 /* LCurly */:{
this->pop_state();
this->index--;
return this->next_impl(true);
}
case 58 /* Arrow */:{
if (seen_final_type){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::FunctionTypeContext(true))));
TRY((this->push_state(Jakt::formatter::State::TypeContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false))));
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
case 11 /* LSquare */:{
TRY((this->push_state(Jakt::formatter::State::CaptureList())));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 7 /* LParen */:{
if (seen_final_type){
this->pop_state();
this->index--;
return this->next_impl(true);
}
TRY((this->push_state(Jakt::formatter::State::ParameterList(static_cast<size_t>(0ULL)))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:{
if (seen_final_type){
this->pop_state();
this->index--;
return this->next_impl(true);
}
return this->formatted_token(token,[&]() -> JaktInternal::DynamicArray<u8> { auto&& __jakt_match_variant = this->peek(static_cast<i64>(0LL));
switch(__jakt_match_variant.__jakt_init_index()) {
case 102 /* Throws */:return DynamicArray<u8>::create_with({static_cast<u8>(u8' ')});default:return DynamicArray<u8>::create_with({});}/*switch end*/
 
}(),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 102 /* Throws */:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));default:{
if (seen_final_type){
this->pop_state();
this->index--;
return this->next_impl(true);
}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_in_match_pattern_context(size_t const open_parens,bool const allow_multiple,Jakt::lexer::Token const token) {
{
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */:{
TRY((this->replace_state(Jakt::formatter::State::MatchPattern(JaktInternal::checked_add(open_parens,static_cast<size_t>(1ULL)),allow_multiple))));
TRY((this->push_state(Jakt::formatter::State::StatementContext(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),false,Jakt::formatter::ExpressionMode::OutsideExpression(),static_cast<size_t>(0ULL)))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 8 /* RParen */:{
if (open_parens == static_cast<size_t>(0ULL)){
this->pop_state();
this->index -= static_cast<size_t>(1ULL);
return this->next_impl(true);
}
TRY((this->replace_state(Jakt::formatter::State::MatchPattern(JaktInternal::checked_sub(open_parens,static_cast<size_t>(1ULL)),allow_multiple))));
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 55 /* Eol */:{
if (!allow_multiple){
this->pop_state();
this->index -= static_cast<size_t>(1ULL);
return this->next_impl(true);
}
return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
}
VERIFY_NOT_REACHED();
case 3 /* Identifier */:return this->formatted_token(token,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));case 40 /* Pipe */:{
if (!allow_multiple){
this->pop_state();
this->index -= static_cast<size_t>(1ULL);
return this->next_impl(true);
}
return this->formatted_token(token,DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}),DynamicArray<u8>::create_with({static_cast<u8>(u8' ')}));
}
VERIFY_NOT_REACHED();
default:{
this->pop_state();
this->index -= static_cast<size_t>(1ULL);
return this->next_impl(true);
}
}/*switch end*/
}
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Stage0::next_impl(bool const reconsume) {
{
if (this->index >= this->tokens.size()){
return JaktInternal::OptionalNone();
}
if (this->states.is_empty() && (this->index < this->tokens.size())){
Jakt::abort();
}
Jakt::lexer::Token token = this->consume();
i64 indent_change = static_cast<i64>(0LL);
if (!reconsume){
if ((!this->already_seen_enclosure_in_current_line) && (((token.__jakt_init_index() == 7 /* LParen */) || (token.__jakt_init_index() == 9 /* LCurly */)) || (token.__jakt_init_index() == 11 /* LSquare */))){
this->already_seen_enclosure_in_current_line = true;
this->dedents_to_skip.push(static_cast<size_t>(0ULL));
indent_change = static_cast<i64>(1LL);
}
else if (token.__jakt_init_index() == 55 /* Eol */){
this->already_seen_enclosure_in_current_line = false;
}
if (((token.__jakt_init_index() == 7 /* LParen */) || (token.__jakt_init_index() == 9 /* LCurly */)) || (token.__jakt_init_index() == 11 /* LSquare */)){
this->dedents_to_skip[JaktInternal::checked_sub(this->dedents_to_skip.size(),static_cast<size_t>(1ULL))]++;
}
if (((token.__jakt_init_index() == 8 /* RParen */) || (token.__jakt_init_index() == 10 /* RCurly */)) || (token.__jakt_init_index() == 12 /* RSquare */)){
if (this->dedents_to_skip.last().value() == static_cast<size_t>(1ULL)){
if (this->dedents_to_skip.size() > static_cast<size_t>(1ULL)){
JaktInternal::Optional<size_t> const dummy = this->dedents_to_skip.pop();
}
this->indent -= static_cast<size_t>(1ULL);
this->already_seen_enclosure_in_current_line = false;
}
else if (this->dedents_to_skip.last().value() > static_cast<size_t>(0ULL)){
this->dedents_to_skip[JaktInternal::checked_sub(this->dedents_to_skip.size(),static_cast<size_t>(1ULL))] -= static_cast<size_t>(1ULL);
}
}
}
ScopeGuard __jakt_var_136([&] {
{
if (indent_change > static_cast<i64>(0LL)){
this->indent += infallible_integer_cast<size_t>(indent_change);
}
else if (indent_change < static_cast<i64>(0LL)){
this->indent -= infallible_integer_cast<size_t>(-indent_change);
}
}

});
if (this->debug){
warnln();
warnln(StringView::from_string_literal("Token: {} -- Indent: {}"sv),TRY((Jakt::formatter::FormattedToken(token,static_cast<size_t>(0ULL),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})).debug_text())),this->indent);
{
JaktInternal::ArrayIterator<Jakt::formatter::State> _magic = this->states.iterator();
for (;;){
JaktInternal::Optional<Jakt::formatter::State> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::formatter::State state = _magic_value.value();
{
warnln(StringView::from_string_literal("- State: {}"sv),state);
}

}
}

warnln();
}
{auto&& __jakt_match_variant = this->state();
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Toplevel */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Toplevel;size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
bool const& is_extern = __jakt_match_value.is_extern;
return this->next_in_toplevel_context(open_parens,open_curlies,open_squares,is_extern,token);};/*case end*/
case 1 /* Extern */:return this->next_in_extern_context(token);case 2 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;bool const& is_extern = __jakt_match_value.is_extern;
return this->next_in_import_context(is_extern,token);};/*case end*/
case 3 /* ImportList */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ImportList;bool const& emitted_comma = __jakt_match_value.emitted_comma;
return this->next_in_import_list_context(emitted_comma,token);};/*case end*/
case 5 /* Implements */:return this->next_in_implements_context(token);case 4 /* EntityDeclaration */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EntityDeclaration;Jakt::formatter::Entity const& entity = __jakt_match_value.entity;
bool const& accept_generics = __jakt_match_value.accept_generics;
bool const& has_generics = __jakt_match_value.has_generics;
size_t const& generic_nesting = __jakt_match_value.generic_nesting;
bool const& is_extern = __jakt_match_value.is_extern;
return this->next_in_entity_declaration_context(entity,accept_generics,has_generics,generic_nesting,is_extern,token);};/*case end*/
case 9 /* EntityDefinition */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EntityDefinition;Jakt::formatter::Entity const& entity = __jakt_match_value.entity;
bool const& is_extern = __jakt_match_value.is_extern;
return this->next_in_entity_definition_context(entity,is_extern,indent_change,token);};/*case end*/
case 10 /* StatementContext */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StatementContext;size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& arrow_indents = __jakt_match_value.arrow_indents;
JaktInternal::Optional<size_t> const& allow_eol = __jakt_match_value.allow_eol;
bool const& inserted_comma = __jakt_match_value.inserted_comma;
Jakt::formatter::ExpressionMode const& expression_mode = __jakt_match_value.expression_mode;
size_t const& dedents_on_open_curly = __jakt_match_value.dedents_on_open_curly;
return this->next_in_statement_context(open_parens,open_curlies,open_squares,arrow_indents,allow_eol,inserted_comma,expression_mode,dedents_on_open_curly,indent_change,token);};/*case end*/
case 13 /* GenericCallTypeParams */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericCallTypeParams;size_t const& open_angles = __jakt_match_value.open_angles;
return this->next_in_generic_call_type_params_context(open_angles,token);};/*case end*/
case 12 /* VariableDeclaration */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VariableDeclaration;size_t const& open_parens = __jakt_match_value.open_parens;
return this->next_in_variable_declaration_context(open_parens,token);};/*case end*/
case 8 /* RestrictionList */:return this->next_in_restriction_list_context(token);case 6 /* CaptureList */:return this->next_in_capture_list_context(token);case 7 /* ParameterList */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ParameterList;size_t const& open_parens = __jakt_match_value.open_parens;
return this->next_in_parameter_list_context(open_parens,token);};/*case end*/
case 14 /* TypeContext */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeContext;size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& open_angles = __jakt_match_value.open_angles;
bool const& seen_start = __jakt_match_value.seen_start;
return this->next_in_type_context(open_parens,open_curlies,open_squares,open_angles,seen_start,token);};/*case end*/
case 15 /* FunctionTypeContext */: {
auto&& __jakt_match_value = __jakt_match_variant.as.FunctionTypeContext;bool const& seen_final_type = __jakt_match_value.seen_final_type;
return this->next_in_function_type_context(seen_final_type,token);};/*case end*/
case 11 /* MatchPattern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MatchPattern;size_t const& open_parens = __jakt_match_value.open_parens;
bool const& allow_multiple = __jakt_match_value.allow_multiple;
return this->next_in_match_pattern_context(open_parens,allow_multiple,token);};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}
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
size_t length = token.preceding_trivia.size();
{auto&& __jakt_match_variant = token.token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
{
if (comment.has_value()){
u8 next_char = static_cast<u8>(u8' ');
if (comment.value().length() != static_cast<size_t>(0ULL)){
next_char = comment.value().byte_at(static_cast<size_t>(0ULL));
}
size_t const space = [&]() -> size_t { auto __jakt_enum_value = next_char;
if ((__jakt_enum_value == static_cast<u8>(u8' '))||(__jakt_enum_value == static_cast<u8>(u8'\t'))||(__jakt_enum_value == static_cast<u8>(u8'/'))) {return static_cast<size_t>(0ULL);}else {return static_cast<size_t>(1ULL);} 
}();
length += space;
length += comment.value().length();
}
}
goto __jakt_label_193;};/*case end*/
default:{
length += TRY((token.token_text())).length();
}
goto __jakt_label_193;}/*switch end*/
}goto __jakt_label_193; __jakt_label_193:;;
length += token.trailing_trivia.size();
return length;
}
}

void Jakt::formatter::Formatter::fixup_tokens_to_reflow() {
{
if (this->tokens_to_reflow.is_empty()){
return;
}
size_t i = static_cast<size_t>(0ULL);
size_t j = JaktInternal::checked_sub(this->tokens_to_reflow.size(),static_cast<size_t>(1ULL));
while (i < j){
Jakt::formatter::ReflowState const a = this->tokens_to_reflow[i];
this->tokens_to_reflow[i] = this->tokens_to_reflow[j];
this->tokens_to_reflow[j] = a;
i += static_cast<size_t>(1ULL);
j -= static_cast<size_t>(1ULL);
}
}
}

JaktInternal::DynamicArray<u8> Jakt::formatter::Formatter::to_array(ByteString const s) {
{
JaktInternal::DynamicArray<u8> result = DynamicArray<u8>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(s.length())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
result.push(s.byte_at(i));
}

}
}

return result;
}
}

void Jakt::formatter::Formatter::fixup_closing_enclosures(JaktInternal::DynamicArray<Jakt::formatter::ReflowState>& line) const {
{
if (line.is_empty()){
return;
}
line[static_cast<i64>(0LL)].token.preceding_trivia = DynamicArray<u8>::create_with({});
size_t enclosure_run_length = static_cast<size_t>(0ULL);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(JaktInternal::checked_sub(line.size(),static_cast<size_t>(1ULL))),static_cast<size_t>(static_cast<size_t>(0ULL))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
{auto&& __jakt_match_variant = line[i].token.token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */:case 10 /* RCurly */:case 12 /* RSquare */:{
enclosure_run_length += static_cast<size_t>(1ULL);
}
goto __jakt_label_194;default:{
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enclosure_run_length)};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t j = _magic_value.value();
{
line[JaktInternal::checked_sub(i,j)].token = Jakt::formatter::FormattedToken(line[JaktInternal::checked_sub(i,j)].token.token,line[JaktInternal::checked_sub(i,enclosure_run_length)].token.indent,line[JaktInternal::checked_sub(i,j)].token.trailing_trivia,line[JaktInternal::checked_sub(i,j)].token.preceding_trivia);
}

}
}

enclosure_run_length = static_cast<size_t>(0ULL);
}
goto __jakt_label_194;}/*switch end*/
break;}goto __jakt_label_194; __jakt_label_194:;;
}

}
}

{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enclosure_run_length)};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t j = _magic_value.value();
{
line[j].token = Jakt::formatter::FormattedToken(line[j].token.token,line[enclosure_run_length].token.indent,line[j].token.trailing_trivia,line[j].token.preceding_trivia);
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
return (state.__jakt_init_index() == 14 /* TypeContext */) || (state.__jakt_init_index() == 12 /* VariableDeclaration */);
}
}

ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> Jakt::formatter::Formatter::peek() {
{
JaktInternal::Optional<Jakt::formatter::ReflowState> reflown_token = JaktInternal::OptionalNone();
if (this->tokens_to_reflow.size() > static_cast<size_t>(0ULL)){
reflown_token = this->tokens_to_reflow[JaktInternal::checked_sub(this->tokens_to_reflow.size(),static_cast<size_t>(1ULL))];
}
return TRY((reflown_token.map([](auto&& _value) { return _value.token; }).try_value_or_lazy_evaluated_optional([&]() -> ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> { return TRY((this->token_provider.formatted_peek())); })));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>>> Jakt::formatter::Formatter::next() {
{
JaktInternal::Optional<Jakt::formatter::ReflowState> const reflown_token = this->tokens_to_reflow.pop();
JaktInternal::Optional<Jakt::formatter::FormattedToken> maybe_next_underlying_token = TRY((reflown_token.map([](auto&& _value) { return _value.token; }).try_value_or_lazy_evaluated_optional([&]() -> ErrorOr<JaktInternal::Optional<Jakt::formatter::FormattedToken>> { return TRY((this->token_provider.next())); })));
Jakt::formatter::State current_state = reflown_token.map([](auto&& _value) { return _value.state; }).value_or_lazy_evaluated([&] { return this->token_provider.state(); });
if (maybe_next_underlying_token.has_value()){
Jakt::lexer::Token next_underlying_token = maybe_next_underlying_token.value().token;
bool accepted_at_least_one_token = false;
while ((!(next_underlying_token.__jakt_init_index() == 56 /* Eof */)) && (!(next_underlying_token.__jakt_init_index() == 55 /* Eol */))){
size_t const projected_added_length = TRY((this->token_length(maybe_next_underlying_token.value())));
if (this->logical_break_indent.has_value()){
maybe_next_underlying_token.value().indent = this->logical_break_indent.value();
}
if ((this->in_condition_expr && (next_underlying_token.__jakt_init_index() == 9 /* LCurly */)) || (next_underlying_token.__jakt_init_index() == 70 /* Else */)){
this->in_condition_expr = false;
this->in_condition_expr_indented = false;
}
{auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */:case 9 /* LCurly */:case 11 /* LSquare */:{
accepted_at_least_one_token = true;
this->current_line.push(Jakt::formatter::ReflowState(maybe_next_underlying_token.value(),current_state,this->enclosures_to_ignore));
this->current_line_length += projected_added_length;
if (!Jakt::formatter::Formatter::should_ignore_state(current_state)){
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((this->peek()));
JaktInternal::Optional<Jakt::formatter::BreakablePoint> breakable_point = JaktInternal::OptionalNone();
if (next_token.has_value()){
i64 const a = static_cast<i64>(1LL);
breakable_point = [&]() -> JaktInternal::Optional<Jakt::formatter::BreakablePoint> { auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */:{auto&& __jakt_match_variant = next_token.value().token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */:return JaktInternal::OptionalNone();default:return Jakt::formatter::BreakablePoint::Paren(this->current_line.size(),this->current_line_length);}/*switch end*/
}case 9 /* LCurly */:{auto&& __jakt_match_variant = next_token.value().token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */:return JaktInternal::OptionalNone();default:return Jakt::formatter::BreakablePoint::Curly(this->current_line.size(),this->current_line_length);}/*switch end*/
}case 11 /* LSquare */:{auto&& __jakt_match_variant = next_token.value().token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */:return JaktInternal::OptionalNone();default:return Jakt::formatter::BreakablePoint::Square(this->current_line.size(),this->current_line_length);}/*switch end*/
}default:{
Jakt::abort();
}
}/*switch end*/
 
}();
}
else {
breakable_point = [&]() -> JaktInternal::Optional<Jakt::formatter::BreakablePoint> { auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */:return Jakt::formatter::BreakablePoint::Paren(this->current_line.size(),this->current_line_length);case 9 /* LCurly */:return Jakt::formatter::BreakablePoint::Curly(this->current_line.size(),this->current_line_length);case 11 /* LSquare */:return Jakt::formatter::BreakablePoint::Square(this->current_line.size(),this->current_line_length);default:{
Jakt::abort();
}
}/*switch end*/
 
}();
}

if (breakable_point.has_value()){
this->breakable_points_in_current_line.push(breakable_point.value());
}
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
this->replace_commas_in_enclosure.push(none);
}
else {
this->enclosures_to_ignore += static_cast<size_t>(1ULL);
}

}
goto __jakt_label_195;case 8 /* RParen */:case 10 /* RCurly */:case 12 /* RSquare */:{
bool ignore = false;
if (this->enclosures_to_ignore > static_cast<size_t>(0ULL)){
this->enclosures_to_ignore -= static_cast<size_t>(1ULL);
ignore = true;
}
if ((!ignore) && (!Jakt::formatter::Formatter::should_ignore_state(current_state))){
Jakt::lexer::Token const replacement = Jakt::formatter::collapse<Jakt::lexer::Token>(this->replace_commas_in_enclosure.pop()).value_or_lazy_evaluated([&] { return next_underlying_token; });
Jakt::formatter::FormattedToken const new_token = Jakt::formatter::FormattedToken(replacement,maybe_next_underlying_token.value().indent,maybe_next_underlying_token.value().trailing_trivia,maybe_next_underlying_token.value().preceding_trivia);
this->current_line.push(Jakt::formatter::ReflowState(new_token,current_state,this->enclosures_to_ignore));
this->current_line_length += TRY((this->token_length(new_token)));
if (replacement.__jakt_init_index() == 55 /* Eol */){
this->tokens_to_reflow.push(Jakt::formatter::ReflowState(maybe_next_underlying_token.value(),current_state,this->enclosures_to_ignore));
JaktInternal::Optional<Jakt::lexer::Token> const none = JaktInternal::OptionalNone();
this->replace_commas_in_enclosure.push(none);
break;
}
}
else {
this->current_line.push(Jakt::formatter::ReflowState(maybe_next_underlying_token.value(),current_state,this->enclosures_to_ignore));
this->current_line_length += TRY((this->token_length(maybe_next_underlying_token.value())));
}

accepted_at_least_one_token = true;
}
goto __jakt_label_195;case 52 /* Comma */:{
accepted_at_least_one_token = true;
if (!Jakt::formatter::Formatter::should_ignore_state(current_state)){
Jakt::lexer::Token const replacement = Jakt::formatter::collapse<Jakt::lexer::Token>(this->replace_commas_in_enclosure.last()).value_or_lazy_evaluated([&] { return next_underlying_token; });
Jakt::formatter::FormattedToken const new_token = Jakt::formatter::FormattedToken(replacement,maybe_next_underlying_token.value().indent,maybe_next_underlying_token.value().trailing_trivia,maybe_next_underlying_token.value().preceding_trivia);
this->current_line.push(Jakt::formatter::ReflowState(new_token,current_state,this->enclosures_to_ignore));
this->current_line_length += TRY((this->token_length(new_token)));
if (replacement.__jakt_init_index() == 55 /* Eol */){
break;
}
}
else {
this->current_line.push(Jakt::formatter::ReflowState(maybe_next_underlying_token.value(),current_state,this->enclosures_to_ignore));
this->current_line_length += TRY((this->token_length(maybe_next_underlying_token.value())));
}

}
goto __jakt_label_195;default:{
Jakt::lexer::Token const newline = Jakt::lexer::Token::Eol(JaktInternal::OptionalNone(),next_underlying_token.span());
{auto&& __jakt_match_variant = next_underlying_token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 85 /* Match */:case 75 /* For */:case 108 /* While */:case 78 /* If */:case 110 /* Guard */:{
this->in_condition_expr = true;
this->in_condition_expr_indented = false;
JaktInternal::Optional<Jakt::formatter::FormattedToken> const next_token = TRY((this->peek()));
if (next_token.has_value()){
if (next_token.value().indent > maybe_next_underlying_token.value().indent){
this->in_condition_expr_indented = true;
}
}
}
goto __jakt_label_196;default:{
}
goto __jakt_label_196;}/*switch end*/
break;}goto __jakt_label_196; __jakt_label_196:;;
if (this->logical_break_indent.has_value() && ((next_underlying_token.__jakt_init_index() == 59 /* And */) || (next_underlying_token.__jakt_init_index() == 90 /* Or */))){
this->current_line.push(Jakt::formatter::ReflowState(maybe_next_underlying_token.value(),current_state,this->enclosures_to_ignore));
this->current_line_length += TRY((this->token_length(maybe_next_underlying_token.value())));
Jakt::formatter::FormattedToken const new_token = Jakt::formatter::FormattedToken(newline,this->logical_break_indent.value(),DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({}));
this->current_line.push(Jakt::formatter::ReflowState(new_token,current_state,this->enclosures_to_ignore));
this->current_line_length += TRY((this->token_length(new_token)));
break;
}
size_t const real_line_length = JaktInternal::checked_add(JaktInternal::checked_add(this->current_line_length,projected_added_length),maybe_next_underlying_token.value().indent);
size_t const most_desirable_breaking_point_index = this->pick_breaking_point_index();
if (accepted_at_least_one_token && ((real_line_length > this->max_allowed_line_length) && ((!this->breakable_points_in_current_line.is_empty()) && ((this->breakable_points_in_current_line[most_desirable_breaking_point_index].point() < this->current_line.size()) && (!Jakt::formatter::Formatter::should_ignore_state(current_state)))))){
Jakt::formatter::BreakablePoint const breakable_point = this->breakable_points_in_current_line[most_desirable_breaking_point_index];
if (!this->replace_commas_in_enclosure.is_empty()){
this->replace_commas_in_enclosure[JaktInternal::checked_sub(this->replace_commas_in_enclosure.size(),static_cast<size_t>(1ULL))] = newline;
}
size_t const point = breakable_point.point();
if (breakable_point.__jakt_init_index() == 3 /* Logical */){
if (!this->logical_break_indent.has_value()){
this->logical_break_indent = this->current_line[point].token.indent;
if (!this->in_condition_expr_indented){
this->logical_break_indent.value() += static_cast<size_t>(1ULL);
}
}
}
this->tokens_to_reflow = this->current_line[JaktInternal::Range<size_t>{static_cast<size_t>(point),static_cast<size_t>(9223372036854775807LL)}].to_array();
this->tokens_to_reflow.push(Jakt::formatter::ReflowState(maybe_next_underlying_token.value(),current_state,this->enclosures_to_ignore));
this->fixup_tokens_to_reflow();
Jakt::formatter::State const final_state = this->current_line[point].state;
this->enclosures_to_ignore = this->current_line[point].enclosures_to_ignore;
this->current_line = this->current_line[JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(point)}].to_array();
this->current_line.push(Jakt::formatter::ReflowState(Jakt::formatter::FormattedToken(newline,maybe_next_underlying_token.value().indent,DynamicArray<u8>::create_with({}),DynamicArray<u8>::create_with({})),final_state,this->enclosures_to_ignore));
this->current_line_length = static_cast<size_t>(0ULL);
break;
}
accepted_at_least_one_token = true;
this->current_line.push(Jakt::formatter::ReflowState(maybe_next_underlying_token.value(),current_state,this->enclosures_to_ignore));
this->current_line_length += projected_added_length;
if (this->in_condition_expr && ((next_underlying_token.__jakt_init_index() == 59 /* And */) || (next_underlying_token.__jakt_init_index() == 90 /* Or */))){
this->breakable_points_in_current_line.push(Jakt::formatter::BreakablePoint::Logical(this->current_line.size(),this->current_line_length));
}
}
goto __jakt_label_195;}/*switch end*/
break;}goto __jakt_label_195; __jakt_label_195:;;
if (this->tokens_to_reflow.is_empty()){
maybe_next_underlying_token = TRY((this->token_provider.next()));
current_state = this->token_provider.state();
}
else {
JaktInternal::Optional<Jakt::formatter::ReflowState> const reflown_token = this->tokens_to_reflow.pop();
maybe_next_underlying_token = reflown_token.map([](auto&& _value) { return _value.token; });
current_state = reflown_token.map([](auto&& _value) { return _value.state; }).value_or_lazy_evaluated([&] { return current_state; });
}

if (!maybe_next_underlying_token.has_value()){
break;
}
next_underlying_token = maybe_next_underlying_token.value().token;
}
size_t const allowed_empty_lines_in_state = [&]() -> size_t { auto&& __jakt_match_variant = current_state;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* TypeContext */:case 3 /* ImportList */:case 7 /* ParameterList */:return static_cast<size_t>(0ULL);case 0 /* Toplevel */:return static_cast<size_t>(2ULL);default:return static_cast<size_t>(1ULL);}/*switch end*/
 
}();
JaktInternal::DynamicArray<Jakt::formatter::ReflowState> line = this->current_line;
this->current_line = DynamicArray<Jakt::formatter::ReflowState>::create_with({});
this->breakable_points_in_current_line = DynamicArray<Jakt::formatter::BreakablePoint>::create_with({});
this->current_line_length = static_cast<size_t>(0ULL);
this->enclosures_to_ignore = static_cast<size_t>(0ULL);
if (!this->in_condition_expr){
this->logical_break_indent = JaktInternal::OptionalNone();
}
if (line.is_empty() || (!(line.last().value().token.token.__jakt_init_index() == 55 /* Eol */))){
line.push(Jakt::formatter::ReflowState(maybe_next_underlying_token.value(),current_state,this->enclosures_to_ignore));
}
if (line.size() == static_cast<size_t>(1ULL)){
{auto&& __jakt_match_variant = line.last().value().token.token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
{
if ((this->empty_line_count >= allowed_empty_lines_in_state) && (!comment.has_value())){
return this->next();
}
if (comment.has_value()){
this->empty_line_count = static_cast<size_t>(0ULL);
}
else {
this->empty_line_count += static_cast<size_t>(1ULL);
}

}
goto __jakt_label_197;};/*case end*/
default:{
this->empty_line_count = static_cast<size_t>(0ULL);
}
goto __jakt_label_197;}/*switch end*/
}goto __jakt_label_197; __jakt_label_197:;;
}
else {
this->empty_line_count = static_cast<size_t>(0ULL);
}

if (line.size() > static_cast<size_t>(1ULL)){
line[JaktInternal::checked_sub(line.size(),static_cast<size_t>(2ULL))].token.trailing_trivia = DynamicArray<u8>::create_with({});
}
line[JaktInternal::checked_sub(line.size(),static_cast<size_t>(1ULL))].token.preceding_trivia = DynamicArray<u8>::create_with({});
line[JaktInternal::checked_sub(line.size(),static_cast<size_t>(1ULL))].token.trailing_trivia = DynamicArray<u8>::create_with({});
this->fixup_closing_enclosures(line);
JaktInternal::DynamicArray<Jakt::formatter::FormattedToken> result = DynamicArray<Jakt::formatter::FormattedToken>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::formatter::ReflowState> _magic = line.iterator();
for (;;){
JaktInternal::Optional<Jakt::formatter::ReflowState> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::formatter::ReflowState state = _magic_value.value();
{
result.push(state.token);
}

}
}

return result;
}
else {
if (this->current_line.is_empty()){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<Jakt::formatter::ReflowState> const line = this->current_line;
this->current_line = DynamicArray<Jakt::formatter::ReflowState>::create_with({});
this->breakable_points_in_current_line = DynamicArray<Jakt::formatter::BreakablePoint>::create_with({});
this->current_line_length = static_cast<size_t>(0ULL);
this->enclosures_to_ignore = static_cast<size_t>(0ULL);
this->in_condition_expr = false;
this->in_condition_expr_indented = false;
this->logical_break_indent = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<Jakt::formatter::FormattedToken> result = DynamicArray<Jakt::formatter::FormattedToken>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::formatter::ReflowState> _magic = line.iterator();
for (;;){
JaktInternal::Optional<Jakt::formatter::ReflowState> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::formatter::ReflowState state = _magic_value.value();
{
result.push(state.token);
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
{auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 99 /* Struct */:case 65 /* Class */:case 113 /* Trait */:return Jakt::formatter::Entity::Struct();case 71 /* Enum */:return Jakt::formatter::Entity::Enum();case 88 /* Namespace */:return Jakt::formatter::Entity::Namespace();case 77 /* Comptime */:case 76 /* Fn */:return Jakt::formatter::Entity::Function(false,false);default:return Jakt::formatter::Entity::Struct();}/*switch end*/
}
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
{auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Toplevel */:return ByteString::from_utf8_without_validation("toplevel"sv);case 1 /* Extern */:return ByteString::from_utf8_without_validation("extern"sv);case 2 /* Import */:return ByteString::from_utf8_without_validation("import"sv);case 3 /* ImportList */:return ByteString::from_utf8_without_validation("import list"sv);case 5 /* Implements */:return ByteString::from_utf8_without_validation("implements"sv);case 4 /* EntityDeclaration */:return ByteString::from_utf8_without_validation("entity declaration"sv);case 6 /* CaptureList */:return ByteString::from_utf8_without_validation("capture list"sv);case 7 /* ParameterList */:return ByteString::from_utf8_without_validation("parameter list"sv);case 8 /* RestrictionList */:return ByteString::from_utf8_without_validation("restriction list"sv);case 9 /* EntityDefinition */:return ByteString::from_utf8_without_validation("entity definition"sv);case 10 /* StatementContext */:return ByteString::from_utf8_without_validation("statement context"sv);case 11 /* MatchPattern */:return ByteString::from_utf8_without_validation("match pattern"sv);case 12 /* VariableDeclaration */:return ByteString::from_utf8_without_validation("variable declaration"sv);case 13 /* GenericCallTypeParams */:return ByteString::from_utf8_without_validation("generic call type params"sv);case 14 /* TypeContext */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeContext;size_t const& open_parens = __jakt_match_value.open_parens;
size_t const& open_curlies = __jakt_match_value.open_curlies;
size_t const& open_squares = __jakt_match_value.open_squares;
size_t const& open_angles = __jakt_match_value.open_angles;
bool const& seen_start = __jakt_match_value.seen_start;
return __jakt_format(StringView::from_string_literal("type context (p{} c{} s{} a{} s:{})"sv),open_parens,open_curlies,open_squares,open_angles,seen_start);};/*case end*/
case 15 /* FunctionTypeContext */:return ByteString::from_utf8_without_validation("function type context"sv);default: VERIFY_NOT_REACHED();}/*switch end*/
}
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
{auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Paren */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Paren;size_t const& point = __jakt_match_value.point;
return point;};/*case end*/
case 1 /* Curly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Curly;size_t const& point = __jakt_match_value.point;
return point;};/*case end*/
case 2 /* Square */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Square;size_t const& point = __jakt_match_value.point;
return point;};/*case end*/
case 3 /* Logical */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Logical;size_t const& point = __jakt_match_value.point;
return point;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

size_t Jakt::formatter::BreakablePoint::length() const {
{
{auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Paren */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Paren;size_t const& length = __jakt_match_value.length;
return length;};/*case end*/
case 1 /* Curly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Curly;size_t const& length = __jakt_match_value.length;
return length;};/*case end*/
case 2 /* Square */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Square;size_t const& length = __jakt_match_value.length;
return length;};/*case end*/
case 3 /* Logical */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Logical;size_t const& length = __jakt_match_value.length;
return length;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

}
} // namespace Jakt
