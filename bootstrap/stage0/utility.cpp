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
TRY((((output).push(TRY((((str) + (suffix))))))));
}

}
}

return output;
}
}

bool is_ascii_alpha(u8 const c) {
{
return (([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(c,static_cast<u8>(u8'a')) && [](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(c,static_cast<u8>(u8'z'))) || ([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(c,static_cast<u8>(u8'A')) && [](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(c,static_cast<u8>(u8'Z'))));
}
}

bool is_whitespace(u8 const byte) {
{
return ((((byte) == (static_cast<u8>(u8' '))) || ((byte) == (static_cast<u8>(u8'\t')))) || ((byte) == (static_cast<u8>(u8'\r'))));
}
}

bool is_ascii_digit(u8 const c) {
{
return ([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(c,static_cast<u8>(u8'0')) && [](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(c,static_cast<u8>(u8'9')));
}
}

bool is_ascii_alphanumeric(u8 const c) {
{
return (utility::is_ascii_alpha(c) || utility::is_ascii_digit(c));
}
}

ErrorOr<DeprecatedString> join(JaktInternal::DynamicArray<DeprecatedString> const strings,DeprecatedString const separator) {
{
DeprecatedString output = TRY(DeprecatedString::from_utf8(""sv));
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
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,s)));
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
(i,JaktInternal::checked_sub(((strings).size()),static_cast<size_t>(1ULL)))){
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,separator)));
}
((i++));
}

}
}

return output;
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
return ([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(c,static_cast<u8>(u8'0')) && [](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(c,static_cast<u8>(u8'7')));
}
}

[[noreturn]] void todo(DeprecatedString const message) {
{
warnln((StringView::from_string_literal("TODO: {}"sv)),message);
abort();
}
}

ErrorOr<DeprecatedString> escape_for_quotes(DeprecatedString const s) {
{
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
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
if (__jakt_enum_value == (infallible_integer_cast<u32>((static_cast<u8>(u8'"'))))) {
{
TRY((((builder).append_string(TRY(DeprecatedString::from_utf8("\\\""sv))))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>((static_cast<u8>(u8'\\'))))) {
{
TRY((((builder).append_string(TRY(DeprecatedString::from_utf8("\\\\"sv))))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>((static_cast<u8>(u8'\n'))))) {
{
TRY((((builder).append_string(TRY(DeprecatedString::from_utf8("\\n"sv))))));
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

return TRY((((builder).to_string())));
}
}

bool is_ascii_hexdigit(u8 const c) {
{
return ((([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(c,static_cast<u8>(u8'0')) && [](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(c,static_cast<u8>(u8'9'))) || ([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(c,static_cast<u8>(u8'a')) && [](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(c,static_cast<u8>(u8'f')))) || ([](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(c,static_cast<u8>(u8'A')) && [](u8 const& self, u8 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(c,static_cast<u8>(u8'F'))));
}
}

ErrorOr<DeprecatedString> interpret_escapes(DeprecatedString const s) {
{
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
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
if (__jakt_enum_value == (infallible_integer_cast<u32>((static_cast<u8>(u8'\\'))))) {
{
if (in_escape){
TRY((((builder).append(static_cast<u8>(u8'\\')))));
(in_escape = false);
}
else {
(in_escape = true);
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>((static_cast<u8>(u8'"'))))) {
{
TRY((((builder).append_code_point(cp))));
(in_escape = false);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>((static_cast<u8>(u8'\''))))) {
{
TRY((((builder).append_code_point(cp))));
(in_escape = false);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == (infallible_integer_cast<u32>((static_cast<u8>(u8'n'))))) {
{
if (in_escape){
TRY((((builder).append(static_cast<u8>(u8'\n')))));
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

return TRY((((builder).to_string())));
}
}

[[noreturn]] void panic(DeprecatedString const message) {
{
warnln((StringView::from_string_literal("internal error: {}"sv)),message);
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
TRY((((output).push(TRY((((prefix) + (str))))))));
}

}
}

return output;
}
}

bool is_ascii_binary(u8 const c) {
{
return (((c) == (static_cast<u8>(u8'0'))) || ((c) == (static_cast<u8>(u8'1'))));
}
}

ErrorOr<DeprecatedString> utility::Span::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Span("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("file_id: {}, ", file_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("start: {}, ", start));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("end: {}", end));
}
TRY(builder.append(")"sv));return builder.to_string(); }
bool utility::Span::contains(utility::Span const span) const {
{
return (((((*this).file_id)).equals(((span).file_id))) && ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((span).start),((*this).start)) && [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(((span).end),((*this).end))));
}
}

utility::Span::Span(utility::FileId a_file_id, size_t a_start, size_t a_end) :file_id(move(a_file_id)), start(move(a_start)), end(move(a_end)){}

bool utility::Span::is_in_offset_range(size_t const start,size_t const end) const {
{
return ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(start,((*this).start)) && [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(end,((*this).end)));
}
}

ErrorOr<DeprecatedString> utility::FileId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("FileId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
utility::FileId::FileId(size_t a_id) :id(move(a_id)){}

bool utility::FileId::equals(utility::FileId const rhs) const {
{
return ((((*this).id)) == (((rhs).id)));
}
}

}
} // namespace Jakt
