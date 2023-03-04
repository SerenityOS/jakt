#include "utility.h"
namespace Jakt {
namespace utility {
ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> append_to_each(JaktInternal::DynamicArray<DeprecatedString> const strings,DeprecatedString const suffix) {
{
JaktInternal::DynamicArray<DeprecatedString> output = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString str = (_magic_value.value());
{
TRY((((output).push((str + suffix)))));
}

}
}

return (output);
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

bool is_ascii_digit(u8 const c) {
{
return (((c >= '0') && (c <= '9')));
}
}

bool is_ascii_alphanumeric(u8 const c) {
{
return ((utility::is_ascii_alpha(c) || utility::is_ascii_digit(c)));
}
}

DeprecatedString join(JaktInternal::DynamicArray<DeprecatedString> const strings,DeprecatedString const separator) {
{
DeprecatedString output = Jakt::DeprecatedString(""sv);
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString s = (_magic_value.value());
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

ErrorOr<void> write_to_file(DeprecatedString const data,DeprecatedString const output_filename) {
{
NonnullRefPtr<File> outfile = TRY((File::open_for_writing(output_filename)));
JaktInternal::DynamicArray<u8> bytes = (TRY((DynamicArray<u8>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((data).length()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((bytes).push(((data).byte_at(i))))));
}

}
}

TRY((((outfile)->write(bytes))));
}
return {};
}

bool is_ascii_octdigit(u8 const c) {
{
return (((c >= '0') && (c <= '7')));
}
}

void todo(DeprecatedString const message) {
{
warnln(Jakt::DeprecatedString("TODO: {}"sv),message);
abort();
}
}

ErrorOr<DeprecatedString> escape_for_quotes(DeprecatedString const s) {
{
DeprecatedStringBuilder builder = TRY((DeprecatedStringBuilder::create()));
{
DeprecatedStringCodePointIterator _magic = ((s).code_points());
for (;;){
JaktInternal::Optional<u32> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u32 cp = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<DeprecatedString>>{
auto __jakt_enum_value = (cp);
if (__jakt_enum_value == (infallible_integer_cast<u32>(('"')))) {
{
TRY((((builder).append_string(Jakt::DeprecatedString("\\\""sv)))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>(('\\')))) {
{
TRY((((builder).append_string(Jakt::DeprecatedString("\\\\"sv)))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>(('\n')))) {
{
TRY((((builder).append_string(Jakt::DeprecatedString("\\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((builder).append_code_point(cp))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
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

return (TRY((((builder).to_string()))));
}
}

bool is_ascii_hexdigit(u8 const c) {
{
return (((((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f'))) || ((c >= 'A') && (c <= 'F'))));
}
}

ErrorOr<DeprecatedString> interpret_escapes(DeprecatedString const s) {
{
DeprecatedStringBuilder builder = TRY((DeprecatedStringBuilder::create()));
bool in_escape = false;
{
DeprecatedStringCodePointIterator _magic = ((s).code_points());
for (;;){
JaktInternal::Optional<u32> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u32 cp = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<DeprecatedString>>{
auto __jakt_enum_value = (cp);
if (__jakt_enum_value == (infallible_integer_cast<u32>(('\\')))) {
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
else if (__jakt_enum_value == (infallible_integer_cast<u32>(('"')))) {
{
TRY((((builder).append_code_point(cp))));
(in_escape = false);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>(('\'')))) {
{
TRY((((builder).append_code_point(cp))));
(in_escape = false);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>(('n')))) {
{
if (in_escape){
TRY((((builder).append('\n'))));
(in_escape = false);
}
else {
TRY((((builder).append_code_point(cp))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((builder).append_code_point(cp))));
(in_escape = false);
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
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

return (TRY((((builder).to_string()))));
}
}

[[noreturn]] void panic(DeprecatedString const message) {
{
warnln(Jakt::DeprecatedString("internal error: {}"sv),message);
abort();
}
}

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> prepend_to_each(JaktInternal::DynamicArray<DeprecatedString> const strings,DeprecatedString const prefix) {
{
JaktInternal::DynamicArray<DeprecatedString> output = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString str = (_magic_value.value());
{
TRY((((output).push((prefix + str)))));
}

}
}

return (output);
}
}

bool is_ascii_binary(u8 const c) {
{
return (((c == '0') || (c == '1')));
}
}

ErrorOr<DeprecatedString> utility::Span::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Span("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("file_id: {}, ", file_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("start: {}, ", start));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("end: {}", end));
}
TRY(builder.append(")"sv));return builder.to_string(); }
bool utility::Span::contains(utility::Span const span) const {
{
return ((((((*this).file_id)).equals(((span).file_id))) && ((((span).start) >= ((*this).start)) && (((span).end) <= ((*this).end)))));
}
}

utility::Span::Span(utility::FileId a_file_id, size_t a_start, size_t a_end) :file_id(move(a_file_id)), start(move(a_start)), end(move(a_end)){}

bool utility::Span::is_in_offset_range(size_t const start,size_t const end) const {
{
return (((start <= ((*this).start)) && (end >= ((*this).end))));
}
}

ErrorOr<DeprecatedString> utility::FileId::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("FileId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
utility::FileId::FileId(size_t a_id) :id(move(a_id)){}

bool utility::FileId::equals(utility::FileId const rhs) const {
{
return ((((*this).id) == ((rhs).id)));
}
}

}
} // namespace Jakt
