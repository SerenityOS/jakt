#include "utility.h"
namespace Jakt {
namespace utility {
bool is_ascii_binary(u8 const c) {
{
return (((c == '0') || (c == '1')));
}
}

bool is_ascii_alpha(u8 const c) {
{
return ((((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))));
}
}

bool is_whitespace(u8 const byte) {
{
return ((((byte == ' ') || (byte == '\t')) || (byte == '\r')));
}
}

ErrorOr<JaktInternal::Array<String>> prepend_to_each(JaktInternal::Array<String> const strings,String const prefix) {
{
JaktInternal::Array<String> output = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<String> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String str = (_magic_value.value());
{
TRY((((output).push((prefix + str)))));
}

}
}

return (output);
}
}

bool is_ascii_digit(u8 const c) {
{
return (((c >= '0') && (c <= '9')));
}
}

void todo(String const message) {
{
warnln(String("TODO: {}"),message);
abort();
}
}

bool is_ascii_alphanumeric(u8 const c) {
{
return ((utility::is_ascii_alpha(c) || utility::is_ascii_digit(c)));
}
}

ErrorOr<String> interpret_escapes(String const s) {
{
StringBuilder builder = TRY((StringBuilder::create()));
bool in_escape = false;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((s).length()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
u8 const c = ((s).byte_at(i));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<String>>{
auto __jakt_enum_value = (c);
if (__jakt_enum_value == '\\') {
{
if (in_escape){
TRY((((builder).append('\\'))));
(in_escape = false);
}
else {
(in_escape = true);
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == '"') {
{
if (in_escape){
TRY((((builder).append(c))));
(in_escape = false);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == '\'') {
{
if (in_escape){
TRY((((builder).append(c))));
(in_escape = false);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == 'n') {
{
if (in_escape){
TRY((((builder).append('\n'))));
(in_escape = false);
}
else {
TRY((((builder).append(c))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((builder).append(c))));
(in_escape = false);
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
}

}
}

return (TRY((((builder).to_string()))));
}
}

ErrorOr<JaktInternal::Array<String>> append_to_each(JaktInternal::Array<String> const strings,String const suffix) {
{
JaktInternal::Array<String> output = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<String> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String str = (_magic_value.value());
{
TRY((((output).push((str + suffix)))));
}

}
}

return (output);
}
}

String join(JaktInternal::Array<String> const strings,String const separator) {
{
String output = String("");
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<String> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String s = (_magic_value.value());
{
(output += s);
if ((i < (JaktInternal::checked_sub<size_t>(((strings).size()),static_cast<size_t>(1ULL))))){
(output += separator);
}
((i++));
}

}
}

return (output);
}
}

bool is_ascii_octdigit(u8 const c) {
{
return (((c >= '0') && (c <= '7')));
}
}

bool is_ascii_hexdigit(u8 const c) {
{
return (((((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f'))) || ((c >= 'A') && (c <= 'F'))));
}
}

[[noreturn]] void panic(String const message) {
{
warnln(String("internal error: {}"),message);
abort();
}
}

ErrorOr<String> escape_for_quotes(String const s) {
{
StringBuilder builder = TRY((StringBuilder::create()));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((s).length()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
u8 const c = ((s).byte_at(i));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<String>>{
auto __jakt_enum_value = (c);
if (__jakt_enum_value == '"') {
{
TRY((((builder).append_string(String("\\\"")))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == '\\') {
{
TRY((((builder).append_string(String("\\\\")))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == '\n') {
{
TRY((((builder).append_string(String("\\n")))));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((builder).append(c))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
}

}
}

return (TRY((((builder).to_string()))));
}
}

ErrorOr<String> utility::Span::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Span("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("file_id: "));TRY(builder.appendff("{}, ", file_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("start: "));TRY(builder.appendff("{}, ", start));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("end: "));TRY(builder.appendff("{}", end));
}
TRY(builder.append(")"));return builder.to_string(); }
bool utility::Span::contains(utility::Span const span) const {
{
return ((((((*this).file_id)).equals(((span).file_id))) && ((((span).start) >= ((*this).start)) && (((span).end) <= ((*this).end)))));
}
}

bool utility::Span::is_in_offset_range(size_t const start,size_t const end) const {
{
return (((start <= ((*this).start)) && (end >= ((*this).end))));
}
}

utility::Span::Span(utility::FileId a_file_id, size_t a_start, size_t a_end) :file_id(a_file_id), start(a_start), end(a_end){}

ErrorOr<String> utility::FileId::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("FileId("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("id: "));TRY(builder.appendff("{}", id));
}
TRY(builder.append(")"));return builder.to_string(); }
bool utility::FileId::equals(utility::FileId const rhs) const {
{
return ((((*this).id) == ((rhs).id)));
}
}

utility::FileId::FileId(size_t a_id) :id(a_id){}

}
} // namespace Jakt
