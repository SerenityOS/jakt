#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "error.h"
#include "jakt__arguments.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace error {
void print_error_json(ByteString const file_name,Jakt::error::JaktError const error) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, void>{
auto&& __jakt_match_variant = error;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Message */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Message;ByteString const& message = __jakt_match_value.message;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::error::display_message_with_span_json(Jakt::error::MessageSeverity::Error(),file_name,message,span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* MessageWithHint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MessageWithHint;ByteString const& message = __jakt_match_value.message;
Jakt::utility::Span const& span = __jakt_match_value.span;
ByteString const& hint = __jakt_match_value.hint;
Jakt::utility::Span const& hint_span = __jakt_match_value.hint_span;
{
Jakt::error::display_message_with_span_json(Jakt::error::MessageSeverity::Error(),file_name,message,span);
Jakt::error::display_message_with_span_json(Jakt::error::MessageSeverity::Hint(),file_name,hint,hint_span);
}
return JaktInternal::ExplicitValue<void>();
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

ErrorOr<void> print_error(ByteString const file_name,JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const file_contents,Jakt::error::JaktError const error) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = error;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Message */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Message;ByteString const& message = __jakt_match_value.message;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::error::display_message_with_span(Jakt::error::MessageSeverity::Error(),file_name,file_contents,message,span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* MessageWithHint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MessageWithHint;ByteString const& message = __jakt_match_value.message;
Jakt::utility::Span const& span = __jakt_match_value.span;
ByteString const& hint = __jakt_match_value.hint;
Jakt::utility::Span const& hint_span = __jakt_match_value.hint_span;
{
Jakt::error::display_message_with_span(Jakt::error::MessageSeverity::Error(),file_name,file_contents,message,span);
Jakt::error::display_message_with_span(Jakt::error::MessageSeverity::Hint(),file_name,file_contents,hint,hint_span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return {};
}

void display_message_with_span_json(Jakt::error::MessageSeverity const severity,ByteString const file_name,ByteString const message,Jakt::utility::Span const span) {
{
outln((StringView::from_string_literal("{{\"type\":\"diagnostic\",\"message\":\"{}\",\"severity\":\"{}\",\"file_id\":{},\"span\":{{\"start\":{},\"end\":{}}}}}"sv)),message,((severity).name()),((((span).file_id)).id),((span).start),((span).end));
}
}

void display_message_with_span(Jakt::error::MessageSeverity const severity,ByteString const file_name,JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const contents,ByteString const message,Jakt::utility::Span const span) {
{
warnln((StringView::from_string_literal("{}: {}"sv)),((severity).name()),message);
if ((!(((contents).has_value())))){
return;
}
JaktInternal::DynamicArray<u8> const file_contents = (contents.value());
JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,size_t>> const line_spans = Jakt::error::gather_line_spans(file_contents);
size_t line_index = static_cast<size_t>(0ULL);
size_t error_start_index = static_cast<size_t>(0ULL);
size_t largest_line_number = static_cast<size_t>(0ULL);
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(line_index,((line_spans).size()))){
if (([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((span).start),((((line_spans)[line_index])).template get<0>())) && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(((span).start),((((line_spans)[line_index])).template get<1>())))){
(error_start_index = line_index);
}
if (([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((span).end),((((line_spans)[line_index])).template get<0>())) && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(((span).end),((((line_spans)[line_index])).template get<1>())))){
(largest_line_number = JaktInternal::checked_add(line_index,static_cast<size_t>(2ULL)));
}
(++(line_index));
}
size_t const width = ((__jakt_format((StringView::from_string_literal("{}"sv)),largest_line_number)).length());
(line_index = error_start_index);
size_t const column_index = JaktInternal::checked_sub(((span).start),((((line_spans)[line_index])).template get<0>()));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_add(width,static_cast<size_t>(2ULL)))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t x = (_magic_value.value());
{
warn((StringView::from_string_literal("─"sv)));
}

}
}

warnln((StringView::from_string_literal("┬─ \u001b[33m{}:{}:{}\u001b[0m"sv)),file_name,JaktInternal::checked_add(line_index,static_cast<size_t>(1ULL)),JaktInternal::checked_add(column_index,static_cast<size_t>(1ULL)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(line_index,static_cast<size_t>(0ULL))){
Jakt::error::print_source_line(severity,file_contents,((line_spans)[JaktInternal::checked_sub(line_index,static_cast<size_t>(1ULL))]),span,line_index,largest_line_number);
}
while (([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(line_index,((line_spans).size())) && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((span).end),((((line_spans)[line_index])).template get<0>())))){
Jakt::error::print_source_line(severity,file_contents,((line_spans)[line_index]),span,JaktInternal::checked_add(line_index,static_cast<size_t>(1ULL)),largest_line_number);
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(((span).end),((((line_spans)[line_index])).template get<1>()))){
Jakt::error::print_underline(severity,width,((line_spans)[line_index]),span,JaktInternal::checked_add(line_index,static_cast<size_t>(1ULL)),largest_line_number);
break;
}
(++(line_index));
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_add(width,static_cast<size_t>(2ULL)))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t x = (_magic_value.value());
{
warn((StringView::from_string_literal(" "sv)));
}

}
}

warn((StringView::from_string_literal("│"sv)));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_sub(((span).end),((((line_spans)[line_index])).template get<0>())))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t x = (_magic_value.value());
{
warn((StringView::from_string_literal(" "sv)));
}

}
}

warnln((StringView::from_string_literal("\u001b[{}m╰─ {}\u001b[0m"sv)),((severity).ansi_color_code()),message);
(++(line_index));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(line_index,((line_spans).size()))){
Jakt::error::print_source_line(severity,file_contents,((line_spans)[line_index]),span,JaktInternal::checked_add(line_index,static_cast<size_t>(1ULL)),largest_line_number);
}
warn((StringView::from_string_literal("\u001b[0m"sv)));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_add(width,static_cast<size_t>(2ULL)))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t x = (_magic_value.value());
{
warn((StringView::from_string_literal("─"sv)));
}

}
}

warnln((StringView::from_string_literal("┴─"sv)));
}
}

void print_source_line(Jakt::error::MessageSeverity const severity,JaktInternal::DynamicArray<u8> const file_contents,JaktInternal::Tuple<size_t,size_t> const file_span,Jakt::utility::Span const error_span,size_t const line_number,size_t const largest_line_number) {
{
size_t index = ((file_span).template get<0>());
size_t const largest_width = ((__jakt_format((StringView::from_string_literal("{}"sv)),largest_line_number)).length());
size_t const current_width = ((__jakt_format((StringView::from_string_literal("{}"sv)),line_number)).length());
warn((StringView::from_string_literal(" {}"sv)),line_number);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_sub(largest_width,current_width))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t _ = (_magic_value.value());
{
warn((StringView::from_string_literal(" "sv)));
}

}
}

warn((StringView::from_string_literal(" │ "sv)));
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(index,((file_span).template get<1>()))){
u8 c = static_cast<u8>(u8' ');
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(index,((file_span).template get<1>()))){
(c = ((file_contents)[index]));
}
else if ((((((error_span).start)) == (((error_span).end))) && ((index) == (((error_span).start))))){
(c = static_cast<u8>(u8'_'));
}
if (((index) == (((error_span).start)))){
warn((StringView::from_string_literal("\u001b[{}m"sv)),((severity).ansi_color_code()));
}
if (((index) == (((error_span).end)))){
warn((StringView::from_string_literal("\u001b[0m"sv)));
}
warn((StringView::from_string_literal("{:c}"sv)),c);
(++(index));
}
warnln((StringView::from_string_literal(""sv)));
}
}

void print_underline(Jakt::error::MessageSeverity const severity,size_t const width,JaktInternal::Tuple<size_t,size_t> const file_span,Jakt::utility::Span const error_span,size_t const line_number,size_t const largest_line_number) {
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_add(width,static_cast<size_t>(2ULL)))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t x = (_magic_value.value());
{
warn((StringView::from_string_literal(" "sv)));
}

}
}

warn((StringView::from_string_literal("│ "sv)));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((file_span).template get<0>())),static_cast<size_t>(((file_span).template get<1>()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t index = (_magic_value.value());
{
if (((index) == (((error_span).start)))){
warn((StringView::from_string_literal("\u001b[{}m"sv)),((severity).ansi_color_code()));
}
if (((index) == (JaktInternal::checked_sub(((error_span).end),static_cast<size_t>(1ULL))))){
warn((StringView::from_string_literal("┬\u001b[0m"sv)));
}
else if (([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(index,((error_span).start)) && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(index,((error_span).end)))){
warn((StringView::from_string_literal("─"sv)));
}
else {
warn((StringView::from_string_literal(" "sv)));
}

}

}
}

warnln((StringView::from_string_literal(""sv)));
}
}

JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,size_t>> gather_line_spans(JaktInternal::DynamicArray<u8> const file_contents) {
{
size_t idx = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,size_t>> output = DynamicArray<JaktInternal::Tuple<size_t,size_t>>::create_with({});
size_t start = idx;
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(idx,((file_contents).size()))){
if (((((file_contents)[idx])) == (static_cast<u8>(u8'\n')))){
((output).push((Tuple{start, idx})));
(start = JaktInternal::checked_add(idx,static_cast<size_t>(1ULL)));
}
((idx) += (static_cast<size_t>(1ULL)));
}
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(start,idx)){
((output).push((Tuple{start, idx})));
}
return output;
}
}

ByteString Jakt::error::JaktError::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Message */: {
builder.append("JaktError::Message"sv);
[[maybe_unused]] auto const& that = this->as.Message;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("message: \"{}\", ", that.message);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* MessageWithHint */: {
builder.append("JaktError::MessageWithHint"sv);
[[maybe_unused]] auto const& that = this->as.MessageWithHint;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("message: \"{}\", ", that.message);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("hint: \"{}\", ", that.hint);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("hint_span: {}", that.hint_span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] JaktError JaktError::Message(ByteString message, Jakt::utility::Span span){
JaktError __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Message.message) (decltype(message))(move(message));
new (&__jakt_uninit_enum.as.Message.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] JaktError JaktError::MessageWithHint(ByteString message, Jakt::utility::Span span, ByteString hint, Jakt::utility::Span hint_span){
JaktError __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.MessageWithHint.message) (decltype(message))(move(message));
new (&__jakt_uninit_enum.as.MessageWithHint.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum.as.MessageWithHint.hint) (decltype(hint))(move(hint));
new (&__jakt_uninit_enum.as.MessageWithHint.hint_span) (decltype(hint_span))(move(hint_span));
return __jakt_uninit_enum;
}
JaktError& JaktError::operator=(JaktError const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Message */:
new (&this->as.Message.message) (decltype(this->as.Message.message))(rhs.as.Message.message);
new (&this->as.Message.span) (decltype(this->as.Message.span))(rhs.as.Message.span);
break;
case 1 /* MessageWithHint */:
new (&this->as.MessageWithHint.message) (decltype(this->as.MessageWithHint.message))(rhs.as.MessageWithHint.message);
new (&this->as.MessageWithHint.span) (decltype(this->as.MessageWithHint.span))(rhs.as.MessageWithHint.span);
new (&this->as.MessageWithHint.hint) (decltype(this->as.MessageWithHint.hint))(rhs.as.MessageWithHint.hint);
new (&this->as.MessageWithHint.hint_span) (decltype(this->as.MessageWithHint.hint_span))(rhs.as.MessageWithHint.hint_span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Message */:
this->as.Message.message = rhs.as.Message.message;
this->as.Message.span = rhs.as.Message.span;
break;
case 1 /* MessageWithHint */:
this->as.MessageWithHint.message = rhs.as.MessageWithHint.message;
this->as.MessageWithHint.span = rhs.as.MessageWithHint.span;
this->as.MessageWithHint.hint = rhs.as.MessageWithHint.hint;
this->as.MessageWithHint.hint_span = rhs.as.MessageWithHint.hint_span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
JaktError::JaktError(JaktError const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Message */:
new (&this->as.Message.message) (decltype(this->as.Message.message))(rhs.as.Message.message);
new (&this->as.Message.span) (decltype(this->as.Message.span))(rhs.as.Message.span);
break;
case 1 /* MessageWithHint */:
new (&this->as.MessageWithHint.message) (decltype(this->as.MessageWithHint.message))(rhs.as.MessageWithHint.message);
new (&this->as.MessageWithHint.span) (decltype(this->as.MessageWithHint.span))(rhs.as.MessageWithHint.span);
new (&this->as.MessageWithHint.hint) (decltype(this->as.MessageWithHint.hint))(rhs.as.MessageWithHint.hint);
new (&this->as.MessageWithHint.hint_span) (decltype(this->as.MessageWithHint.hint_span))(rhs.as.MessageWithHint.hint_span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
JaktError& JaktError::operator=(JaktError &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Message */:
new (&this->as.Message.message) (decltype(this->as.Message.message))(move(rhs.as.Message.message));
new (&this->as.Message.span) (decltype(this->as.Message.span))(move(rhs.as.Message.span));
break;
case 1 /* MessageWithHint */:
new (&this->as.MessageWithHint.message) (decltype(this->as.MessageWithHint.message))(move(rhs.as.MessageWithHint.message));
new (&this->as.MessageWithHint.span) (decltype(this->as.MessageWithHint.span))(move(rhs.as.MessageWithHint.span));
new (&this->as.MessageWithHint.hint) (decltype(this->as.MessageWithHint.hint))(move(rhs.as.MessageWithHint.hint));
new (&this->as.MessageWithHint.hint_span) (decltype(this->as.MessageWithHint.hint_span))(move(rhs.as.MessageWithHint.hint_span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Message */:
this->as.Message.message = move(rhs.as.Message.message);
this->as.Message.span = move(rhs.as.Message.span);
break;
case 1 /* MessageWithHint */:
this->as.MessageWithHint.message = move(rhs.as.MessageWithHint.message);
this->as.MessageWithHint.span = move(rhs.as.MessageWithHint.span);
this->as.MessageWithHint.hint = move(rhs.as.MessageWithHint.hint);
this->as.MessageWithHint.hint_span = move(rhs.as.MessageWithHint.hint_span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
JaktError::JaktError(JaktError &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Message */:
new (&this->as.Message.message) (decltype(this->as.Message.message))(move(rhs.as.Message.message));
new (&this->as.Message.span) (decltype(this->as.Message.span))(move(rhs.as.Message.span));
break;
case 1 /* MessageWithHint */:
new (&this->as.MessageWithHint.message) (decltype(this->as.MessageWithHint.message))(move(rhs.as.MessageWithHint.message));
new (&this->as.MessageWithHint.span) (decltype(this->as.MessageWithHint.span))(move(rhs.as.MessageWithHint.span));
new (&this->as.MessageWithHint.hint) (decltype(this->as.MessageWithHint.hint))(move(rhs.as.MessageWithHint.hint));
new (&this->as.MessageWithHint.hint_span) (decltype(this->as.MessageWithHint.hint_span))(move(rhs.as.MessageWithHint.hint_span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
JaktError::~JaktError(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void JaktError::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Message */:this->as.Message.message.~ByteString();
this->as.Message.span.~Span();
break;
case 1 /* MessageWithHint */:this->as.MessageWithHint.message.~ByteString();
this->as.MessageWithHint.span.~Span();
this->as.MessageWithHint.hint.~ByteString();
this->as.MessageWithHint.hint_span.~Span();
break;
}
}
Jakt::utility::Span Jakt::error::JaktError::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::utility::Span, Jakt::utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Message */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Message;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* MessageWithHint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MessageWithHint;Jakt::utility::Span const& span = __jakt_match_value.span;
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

ByteString Jakt::error::MessageSeverity::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Hint */: {
return ByteString("MessageSeverity::Hint"sv);
break;}
case 1 /* Error */: {
return ByteString("MessageSeverity::Error"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] MessageSeverity MessageSeverity::Hint(){
MessageSeverity __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] MessageSeverity MessageSeverity::Error(){
MessageSeverity __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
MessageSeverity& MessageSeverity::operator=(MessageSeverity const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Hint */:
break;
case 1 /* Error */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Hint */:
break;
case 1 /* Error */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
MessageSeverity::MessageSeverity(MessageSeverity const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Hint */:
break;
case 1 /* Error */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
MessageSeverity& MessageSeverity::operator=(MessageSeverity &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Hint */:
break;
case 1 /* Error */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Hint */:
break;
case 1 /* Error */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
MessageSeverity::MessageSeverity(MessageSeverity &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Hint */:
break;
case 1 /* Error */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
MessageSeverity::~MessageSeverity(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void MessageSeverity::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Hint */:break;
case 1 /* Error */:break;
}
}
ByteString Jakt::error::MessageSeverity::name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Hint */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Hint"sv)));
};/*case end*/
case 1 /* Error */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Error"sv)));
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

ByteString Jakt::error::MessageSeverity::ansi_color_code() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Hint */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("94"sv)));
};/*case end*/
case 1 /* Error */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("31"sv)));
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
