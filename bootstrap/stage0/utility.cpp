#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "utility.h"
#include "jakt__arguments.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace utility {
[[noreturn]] void panic(ByteString const message) {
{
warnln(StringView::from_string_literal("internal error: {}"sv),message);
Jakt::abort();
}
}

[[noreturn]] void todo(ByteString const message) {
{
warnln(StringView::from_string_literal("TODO: {}"sv),message);
Jakt::abort();
}
}

ByteString to_string(JaktInternal::DynamicArray<u8> const bytes) {
{
ByteStringBuilder builder = ByteStringBuilder::create();
{
JaktInternal::ArrayIterator<u8> _magic = bytes.iterator();
for (;;){
JaktInternal::Optional<u8> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
u8 byte = _magic_value.value();
{
builder.append(byte);
}

}
}

return builder.to_string();
}
}

ByteString join(JaktInternal::DynamicArray<ByteString> const strings,ByteString const separator) {
{
ByteStringBuilder output = ByteStringBuilder::create();
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ByteString> _magic = strings.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString s = _magic_value.value();
{
output.append(s);
if (i < JaktInternal::checked_sub(strings.size(),static_cast<size_t>(1ULL))){
output.append(separator);
}
i++;
}

}
}

return output.to_string();
}
}

JaktInternal::DynamicArray<ByteString> prepend_to_each(JaktInternal::DynamicArray<ByteString> const strings,ByteString const prefix) {
{
JaktInternal::DynamicArray<ByteString> output = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = strings.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString str = _magic_value.value();
{
output.push(prefix + str);
}

}
}

return output;
}
}

JaktInternal::DynamicArray<ByteString> append_to_each(JaktInternal::DynamicArray<ByteString> const strings,ByteString const suffix) {
{
JaktInternal::DynamicArray<ByteString> output = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = strings.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString str = _magic_value.value();
{
output.push(str + suffix);
}

}
}

return output;
}
}

ErrorOr<void> write_to_file(ByteString const data,ByteString const output_filename) {
{
NonnullRefPtr<File> outfile = TRY((File::open_for_writing(output_filename)));
JaktInternal::DynamicArray<u8> bytes = DynamicArray<u8>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(data.length())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
bytes.push(data.byte_at(i));
}

}
}

TRY((outfile->write(bytes)));
}
return {};
}

ByteString escape_for_quotes(ByteString const s) {
{
ByteStringBuilder builder = ByteStringBuilder::create();
{
DeprecatedStringCodePointIterator _magic = s.code_points();
for (;;){
JaktInternal::Optional<u32> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
u32 cp = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ByteString> {
auto __jakt_enum_value = (cp);
if (__jakt_enum_value == infallible_integer_cast<u32>(static_cast<u8>(u8'"'))) {{
builder.append(StringView::from_string_literal("\\\""sv));
}
return JaktInternal::ExplicitValue<void>();
}else if (__jakt_enum_value == infallible_integer_cast<u32>(static_cast<u8>(u8'\\'))) {{
builder.append(StringView::from_string_literal("\\\\"sv));
}
return JaktInternal::ExplicitValue<void>();
}else if (__jakt_enum_value == infallible_integer_cast<u32>(static_cast<u8>(u8'\n'))) {{
builder.append(StringView::from_string_literal("\\n"sv));
}
return JaktInternal::ExplicitValue<void>();
}else {{
builder.append_code_point(cp);
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
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

return builder.to_string();
}
}

ByteString interpret_escapes(ByteString const s) {
{
ByteStringBuilder builder = ByteStringBuilder::create();
bool in_escape = false;
{
DeprecatedStringCodePointIterator _magic = s.code_points();
for (;;){
JaktInternal::Optional<u32> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
u32 cp = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ByteString> {
auto __jakt_enum_value = (cp);
if (__jakt_enum_value == infallible_integer_cast<u32>(static_cast<u8>(u8'\\'))) {{
if (in_escape){
builder.append(static_cast<u8>(u8'\\'));
in_escape = false;
}
else {
in_escape = true;
}

}
return JaktInternal::ExplicitValue<void>();
}else if ((__jakt_enum_value == infallible_integer_cast<u32>(static_cast<u8>(u8'"')))||(__jakt_enum_value == infallible_integer_cast<u32>(static_cast<u8>(u8'\'')))) {{
builder.append_code_point(cp);
in_escape = false;
}
return JaktInternal::ExplicitValue<void>();
}else if (__jakt_enum_value == infallible_integer_cast<u32>(static_cast<u8>(u8'n'))) {{
if (in_escape){
builder.append(static_cast<u8>(u8'\n'));
in_escape = false;
}
else {
builder.append_code_point(cp);
}

}
return JaktInternal::ExplicitValue<void>();
}else {{
builder.append_code_point(cp);
in_escape = false;
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
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

return builder.to_string();
}
}

bool is_ascii_alpha(u8 const c) {
{
return ((c >= static_cast<u8>(u8'a')) && (c <= static_cast<u8>(u8'z'))) || ((c >= static_cast<u8>(u8'A')) && (c <= static_cast<u8>(u8'Z')));
}
}

bool is_ascii_digit(u8 const c) {
{
return (c >= static_cast<u8>(u8'0')) && (c <= static_cast<u8>(u8'9'));
}
}

bool is_ascii_hexdigit(u8 const c) {
{
return (((c >= static_cast<u8>(u8'0')) && (c <= static_cast<u8>(u8'9'))) || ((c >= static_cast<u8>(u8'a')) && (c <= static_cast<u8>(u8'f')))) || ((c >= static_cast<u8>(u8'A')) && (c <= static_cast<u8>(u8'F')));
}
}

bool is_ascii_octdigit(u8 const c) {
{
return (c >= static_cast<u8>(u8'0')) && (c <= static_cast<u8>(u8'7'));
}
}

bool is_ascii_binary(u8 const c) {
{
return (c == static_cast<u8>(u8'0')) || (c == static_cast<u8>(u8'1'));
}
}

bool is_ascii_alphanumeric(u8 const c) {
{
return Jakt::utility::is_ascii_alpha(c) || Jakt::utility::is_ascii_digit(c);
}
}

bool is_whitespace(u8 const byte) {
{
return ((byte == static_cast<u8>(u8' ')) || (byte == static_cast<u8>(u8'\t'))) || (byte == static_cast<u8>(u8'\r'));
}
}

ByteString Jakt::utility::Span::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Span("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("file_id: {}, ", file_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("start: {}, ", start);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("end: {}", end);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::utility::Span Jakt::utility::Span::first(Jakt::utility::Span const a,Jakt::utility::Span const b) {
{
if (a.start < b.start){
return a;
}
if (b.start < a.start){
return b;
}
if (a.end < b.end){
return a;
}
return b;
}
}

Jakt::utility::Span Jakt::utility::Span::last(Jakt::utility::Span const a,Jakt::utility::Span const b) {
{
if (a.start > b.start){
return a;
}
if (b.start > a.start){
return b;
}
if (a.end > b.end){
return a;
}
return b;
}
}

bool Jakt::utility::Span::contains(Jakt::utility::Span const span) const {
{
return this->file_id.equals(span.file_id) && ((span.start >= this->start) && (span.end <= this->end));
}
}

bool Jakt::utility::Span::is_in_offset_range(size_t const start,size_t const end) const {
{
return (start <= this->start) && (end >= this->end);
}
}

Jakt::utility::Span::Span(Jakt::utility::FileId a_file_id, size_t a_start, size_t a_end): file_id(move(a_file_id)), start(move(a_start)), end(move(a_end)){}

ByteString Jakt::utility::FileId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FileId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
bool Jakt::utility::FileId::equals(Jakt::utility::FileId const rhs) const {
{
return this->id == rhs.id;
}
}

Jakt::utility::FileId::FileId(size_t a_id): id(move(a_id)){}

}
} // namespace Jakt
