#include "jakt__arguments.h"
namespace Jakt {
namespace jakt__arguments {
ErrorOr<DeprecatedString> jakt__arguments::ArgsParser::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("ArgsParser("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("args: "sv));TRY(builder.appendff("{}, ", args));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("removed_indices: "sv));TRY(builder.appendff("{}, ", removed_indices));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("definitely_positional_args: "sv));TRY(builder.appendff("{}", definitely_positional_args));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<jakt__arguments::ArgsParser> jakt__arguments::ArgsParser::from_args(JaktInternal::DynamicArray<DeprecatedString> const args) {
{
jakt__arguments::ArgsParser parser = jakt__arguments::ArgsParser(args,(TRY((DynamicArray<size_t>::create_with({})))),(TRY((DynamicArray<DeprecatedString>::create_with({})))));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((((parser).args)).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString arg = (_magic_value.value());
{
if ((arg == Jakt::DeprecatedString("--"sv))){
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

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> jakt__arguments::ArgsParser::option_multiple(JaktInternal::DynamicArray<DeprecatedString> const names) {
{
JaktInternal::DynamicArray<DeprecatedString> result = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
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
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString name = (_magic_value.value());
{
if ((((((*this).args))[i]) == name)){
if ((((((*this).args)).size()) <= (JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))))){
warnln(Jakt::DeprecatedString("The option '{}' requires a value, but none was supplied"sv),name);
return Error::from_errno(static_cast<i32>(200));
}
TRY((((((*this).removed_indices)).push(i))));
TRY((((((*this).removed_indices)).push((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))))));
TRY((((result).push(((((*this).args))[(JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))])))));
continue;
}
if (((((((*this).args))[i])).starts_with(name))){
TRY((((((*this).removed_indices)).push(i))));
TRY((((result).push(((((((*this).args))[i])).substring(((name).length()),(JaktInternal::checked_sub<size_t>(((((((*this).args))[i])).length()),((name).length())))))))));
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

ErrorOr<bool> jakt__arguments::ArgsParser::flag(JaktInternal::DynamicArray<DeprecatedString> const names) {
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
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString name = (_magic_value.value());
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

jakt__arguments::ArgsParser::ArgsParser(JaktInternal::DynamicArray<DeprecatedString> a_args, JaktInternal::DynamicArray<size_t> a_removed_indices, JaktInternal::DynamicArray<DeprecatedString> a_definitely_positional_args) :args(a_args), removed_indices(a_removed_indices), definitely_positional_args(a_definitely_positional_args){}

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> jakt__arguments::ArgsParser::remaining_arguments() const {
{
JaktInternal::DynamicArray<DeprecatedString> remaining = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
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
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((((*this).definitely_positional_args)).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString arg = (_magic_value.value());
{
TRY((((remaining).push(arg))));
}

}
}

return (remaining);
}
}

ErrorOr<JaktInternal::Optional<DeprecatedString>> jakt__arguments::ArgsParser::option(JaktInternal::DynamicArray<DeprecatedString> const names) {
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
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString name = (_magic_value.value());
{
if ((((((*this).args))[i]) == name)){
if ((((((*this).args)).size()) <= (JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))))){
warnln(Jakt::DeprecatedString("The option '{}' requires a value, but none was supplied"sv),name);
return Error::from_errno(static_cast<i32>(200));
}
TRY((((((*this).removed_indices)).push(i))));
TRY((((((*this).removed_indices)).push((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))))));
return (((((*this).args))[(JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))]));
}
if (((((((*this).args))[i])).starts_with(name))){
TRY((((((*this).removed_indices)).push(i))));
return (((((((*this).args))[i])).substring(((name).length()),(JaktInternal::checked_sub<size_t>(((((((*this).args))[i])).length()),((name).length()))))));
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
