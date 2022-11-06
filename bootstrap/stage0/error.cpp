#include "error.h"
namespace Jakt {
namespace error {
ErrorOr<void> print_error_json(String const file_name,error::JaktError const error) {
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = error;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<error::JaktError::Message>();String const& message = __jakt_match_value.message;
utility::Span const& span = __jakt_match_value.span;
{
TRY((error::display_message_with_span_json( error::MessageSeverity { typename error::MessageSeverity::Error() } ,file_name,message,span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<error::JaktError::MessageWithHint>();String const& message = __jakt_match_value.message;
utility::Span const& span = __jakt_match_value.span;
String const& hint = __jakt_match_value.hint;
utility::Span const& hint_span = __jakt_match_value.hint_span;
{
TRY((error::display_message_with_span_json( error::MessageSeverity { typename error::MessageSeverity::Error() } ,file_name,message,span)));
TRY((error::display_message_with_span_json( error::MessageSeverity { typename error::MessageSeverity::Hint() } ,file_name,hint,hint_span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}
return {};
}

ErrorOr<JaktInternal::Array<JaktInternal::Tuple<size_t,size_t>>> gather_line_spans(JaktInternal::Array<u8> const file_contents) {
{
size_t idx = static_cast<size_t>(0ULL);
JaktInternal::Array<JaktInternal::Tuple<size_t,size_t>> output = (TRY((Array<JaktInternal::Tuple<size_t,size_t>>::create_with({}))));
size_t start = idx;
while ((idx < ((file_contents).size()))){
if ((((file_contents)[idx]) == '\n')){
TRY((((output).push((Tuple{start, idx})))));
(start = (JaktInternal::checked_add<size_t>(idx,static_cast<size_t>(1ULL))));
}
({auto& _jakt_ref = idx;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
if ((start < idx)){
TRY((((output).push((Tuple{start, idx})))));
}
return (output);
}
}

ErrorOr<void> display_message_with_span(error::MessageSeverity const severity,String const file_name,JaktInternal::Optional<JaktInternal::Array<u8>> const contents,String const message,utility::Span const span) {
{
warnln(String("{}: {}"),TRY((((severity).name()))),message);
if ((!(((contents).has_value())))){
return {};
}
JaktInternal::Array<u8> const file_contents = (contents.value());
JaktInternal::Array<JaktInternal::Tuple<size_t,size_t>> const line_spans = TRY((error::gather_line_spans(file_contents)));
size_t line_index = static_cast<size_t>(1ULL);
size_t largest_line_number = static_cast<size_t>(0ULL);
while ((line_index < ((line_spans).size()))){
if (((((span).start) >= ((((line_spans)[line_index])).get<0>())) && (((span).start) <= ((((line_spans)[line_index])).get<1>())))){
(largest_line_number = (JaktInternal::checked_add<size_t>(line_index,static_cast<size_t>(2ULL))));
}
(++(line_index));
}
size_t const width = ((TRY((String::formatted(String("{}"),largest_line_number)))).length());
(line_index = static_cast<size_t>(1ULL));
while ((line_index < ((line_spans).size()))){
if (((((span).start) >= ((((line_spans)[line_index])).get<0>())) && (((span).start) <= ((((line_spans)[line_index])).get<1>())))){
size_t const column_index = (JaktInternal::checked_sub<size_t>(((span).start),((((line_spans)[line_index])).get<0>())));
warnln(String("----- \u001b[33m{}:{}:{}\u001b[0m"),file_name,(JaktInternal::checked_add<size_t>(line_index,static_cast<size_t>(1ULL))),(JaktInternal::checked_add<size_t>(column_index,static_cast<size_t>(1ULL))));
if ((line_index > static_cast<size_t>(0ULL))){
TRY((error::print_source_line(severity,file_contents,((line_spans)[(JaktInternal::checked_sub<size_t>(line_index,static_cast<size_t>(1ULL)))]),span,line_index,largest_line_number)));
}
TRY((error::print_source_line(severity,file_contents,((line_spans)[line_index]),span,(JaktInternal::checked_add<size_t>(line_index,static_cast<size_t>(1ULL))),largest_line_number)));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>((JaktInternal::checked_add<size_t>((JaktInternal::checked_add<size_t>((JaktInternal::checked_sub<size_t>(((span).start),((((line_spans)[line_index])).get<0>()))),width)),static_cast<size_t>(4ULL))))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t x = (_magic_value.value());
{
warn(String(" "));
}

}
}

warnln(String("\u001b[{}m^- {}\u001b[0m"),TRY((((severity).ansi_color_code()))),message);
while (((line_index < ((line_spans).size())) && (((span).end) > ((((line_spans)[line_index])).get<0>())))){
(++(line_index));
if ((line_index >= ((line_spans).size()))){
break;
}
TRY((error::print_source_line(severity,file_contents,((line_spans)[line_index]),span,(JaktInternal::checked_add<size_t>(line_index,static_cast<size_t>(1ULL))),largest_line_number)));
break;
}
}
else {
(++(line_index));
}

}
warnln(String("\u001b[0m-----"));
}
return {};
}

ErrorOr<void> print_source_line(error::MessageSeverity const severity,JaktInternal::Array<u8> const file_contents,JaktInternal::Tuple<size_t,size_t> const file_span,utility::Span const error_span,size_t const line_number,size_t const largest_line_number) {
{
size_t index = ((file_span).get<0>());
size_t const largest_width = ((TRY((String::formatted(String("{}"),largest_line_number)))).length());
size_t const current_width = ((TRY((String::formatted(String("{}"),line_number)))).length());
warn(String(" {}"),line_number);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>((JaktInternal::checked_sub<size_t>(largest_width,current_width)))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t _ = (_magic_value.value());
{
warn(String(" "));
}

}
}

warn(String(" | "));
while ((index <= ((file_span).get<1>()))){
u8 c = ' ';
if ((index < ((file_span).get<1>()))){
(c = ((file_contents)[index]));
}
else if (((((error_span).start) == ((error_span).end)) && (index == ((error_span).start)))){
(c = '_');
}
if ((index == ((error_span).start))){
warn(String("\u001b[{}m"),TRY((((severity).ansi_color_code()))));
}
if ((index == ((error_span).end))){
warn(String("\u001b[0m"));
}
warn(String("{:c}"),c);
(++(index));
}
warnln(String(""));
}
return {};
}

ErrorOr<void> display_message_with_span_json(error::MessageSeverity const severity,String const file_name,String const message,utility::Span const span) {
{
outln(String("{{\"type\":\"diagnostic\",\"message\":\"{}\",\"severity\":\"{}\",\"file_id\":{},\"span\":{{\"start\":{},\"end\":{}}}}}"),message,TRY((((severity).name()))),((((span).file_id)).id),((span).start),((span).end));
}
return {};
}

ErrorOr<void> print_error(String const file_name,JaktInternal::Optional<JaktInternal::Array<u8>> const file_contents,error::JaktError const error) {
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = error;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<error::JaktError::Message>();String const& message = __jakt_match_value.message;
utility::Span const& span = __jakt_match_value.span;
{
TRY((error::display_message_with_span( error::MessageSeverity { typename error::MessageSeverity::Error() } ,file_name,file_contents,message,span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<error::JaktError::MessageWithHint>();String const& message = __jakt_match_value.message;
utility::Span const& span = __jakt_match_value.span;
String const& hint = __jakt_match_value.hint;
utility::Span const& hint_span = __jakt_match_value.hint_span;
{
TRY((error::display_message_with_span( error::MessageSeverity { typename error::MessageSeverity::Error() } ,file_name,file_contents,message,span)));
TRY((error::display_message_with_span( error::MessageSeverity { typename error::MessageSeverity::Hint() } ,file_name,file_contents,hint,hint_span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}
return {};
}

ErrorOr<String> error::JaktError::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Message */: {
[[maybe_unused]] auto const& that = this->template get<JaktError::Message>();
TRY(builder.append("JaktError::Message"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("message: \"{}\"", that.message));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"));
break;}
case 1 /* MessageWithHint */: {
[[maybe_unused]] auto const& that = this->template get<JaktError::MessageWithHint>();
TRY(builder.append("JaktError::MessageWithHint"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("message: \"{}\"", that.message));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("hint: \"{}\"", that.hint));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("hint_span: {}", that.hint_span));
}
TRY(builder.append(")"));
break;}
}
return builder.to_string();
}
utility::Span error::JaktError::span() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<error::JaktError::Message>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<error::JaktError::MessageWithHint>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> error::MessageSeverity::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Hint */: {
[[maybe_unused]] auto const& that = this->template get<MessageSeverity::Hint>();
TRY(builder.append("MessageSeverity::Hint"));
break;}
case 1 /* Error */: {
[[maybe_unused]] auto const& that = this->template get<MessageSeverity::Error>();
TRY(builder.append("MessageSeverity::Error"));
break;}
}
return builder.to_string();
}
ErrorOr<String> error::MessageSeverity::ansi_color_code() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename error::MessageSeverity::Hint>();
return JaktInternal::ExplicitValue(String("94"));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename error::MessageSeverity::Error>();
return JaktInternal::ExplicitValue(String("31"));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> error::MessageSeverity::name() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename error::MessageSeverity::Hint>();
return JaktInternal::ExplicitValue(String("Hint"));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename error::MessageSeverity::Error>();
return JaktInternal::ExplicitValue(String("Error"));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

}
} // namespace Jakt
