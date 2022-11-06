#include "jakt__arguments.h"
namespace Jakt {
namespace jakt__arguments {
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

ErrorOr<String> jakt__arguments::ArgsParser::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("ArgsParser("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("args: "));TRY(builder.appendff("{}, ", args));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("removed_indices: "));TRY(builder.appendff("{}, ", removed_indices));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("definitely_positional_args: "));TRY(builder.appendff("{}", definitely_positional_args));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<jakt__arguments::ArgsParser> jakt__arguments::ArgsParser::from_args(JaktInternal::Array<String> const args) {
{
jakt__arguments::ArgsParser parser = jakt__arguments::ArgsParser(args,(TRY((Array<size_t>::create_with({})))),(TRY((Array<String>::create_with({})))));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<String> _magic = ((((parser).args)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String arg = (_magic_value.value());
{
if ((arg == String("--"))){
(((parser).definitely_positional_args) = TRY((((((((parser).args))[(JaktInternal::Range<size_t>{static_cast<size_t>((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))),static_cast<size_t>(((((parser).args)).size()))})])).to_array()))));
(((parser).args) = TRY((((((((parser).args))[(JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(i)})])).to_array()))));
break;
}
({auto& _jakt_ref = i;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}

}
}

return (parser);
}
}

ErrorOr<JaktInternal::Array<String>> jakt__arguments::ArgsParser::option_multiple(JaktInternal::Array<String> const names) {
{
JaktInternal::Array<String> result = (TRY((Array<String>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<String> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
if ((((((*this).args))[i]) == name)){
if ((((((*this).args)).size()) <= (JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))))){
warnln(String("The option '{}' requires a value, but none was supplied"),name);
return Error::from_errno(static_cast<i32>(200));
}
TRY((((((*this).removed_indices)).push(i))));
TRY((((((*this).removed_indices)).push((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))))));
TRY((((result).push(((((*this).args))[(JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))])))));
continue;
}
if (((((((*this).args))[i])).starts_with(name))){
TRY((((((*this).removed_indices)).push(i))));
TRY((((result).push(TRY((((((((*this).args))[i])).substring(((name).length()),(JaktInternal::checked_sub<size_t>(((((((*this).args))[i])).length()),((name).length())))))))))));
}
}

}
}

}

}
}

return (result);
}
}

ErrorOr<bool> jakt__arguments::ArgsParser::flag(JaktInternal::Array<String> const names) {
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<String> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
if ((((((*this).args))[i]) == name)){
TRY((((((*this).removed_indices)).push(i))));
return (true);
}
}

}
}

}

}
}

return (false);
}
}

jakt__arguments::ArgsParser::ArgsParser(JaktInternal::Array<String> a_args, JaktInternal::Array<size_t> a_removed_indices, JaktInternal::Array<String> a_definitely_positional_args) :args(a_args), removed_indices(a_removed_indices), definitely_positional_args(a_definitely_positional_args){}

ErrorOr<JaktInternal::Array<String>> jakt__arguments::ArgsParser::remaining_arguments() const {
{
JaktInternal::Array<String> remaining = (TRY((Array<String>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((*this).removed_indices)).contains(i))))){
TRY((((remaining).push(((((*this).args))[i])))));
}
}

}
}

{
JaktInternal::ArrayIterator<String> _magic = ((((*this).definitely_positional_args)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String arg = (_magic_value.value());
{
TRY((((remaining).push(arg))));
}

}
}

return (remaining);
}
}

ErrorOr<JaktInternal::Optional<String>> jakt__arguments::ArgsParser::option(JaktInternal::Array<String> const names) {
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<String> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
if ((((((*this).args))[i]) == name)){
if ((((((*this).args)).size()) <= (JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))))){
warnln(String("The option '{}' requires a value, but none was supplied"),name);
return Error::from_errno(static_cast<i32>(200));
}
TRY((((((*this).removed_indices)).push(i))));
TRY((((((*this).removed_indices)).push((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))))));
return (((((*this).args))[(JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))]));
}
if (((((((*this).args))[i])).starts_with(name))){
TRY((((((*this).removed_indices)).push(i))));
return (TRY((((((((*this).args))[i])).substring(((name).length()),(JaktInternal::checked_sub<size_t>(((((((*this).args))[i])).length()),((name).length()))))))));
}
}

}
}

}

}
}

return (JaktInternal::OptionalNone());
}
}

}
} // namespace Jakt
