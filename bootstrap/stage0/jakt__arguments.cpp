#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "jakt__arguments.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace jakt__arguments {
ByteString Jakt::jakt__arguments::ArgsParser::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ArgsParser("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}, ", args);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("removed_indices: {}, ", removed_indices);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("definitely_positional_args: {}", definitely_positional_args);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<bool> Jakt::jakt__arguments::ArgsParser::flag(JaktInternal::DynamicArray<ByteString> const names) {
{
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(this->args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
{
JaktInternal::ArrayIterator<ByteString> _magic = names.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString name = _magic_value.value();
{
if (this->args.operator[](i) == name){
this->removed_indices.push(i);
return true;
}
}

}
}

}

}
}

return false;
}
}

ErrorOr<JaktInternal::Optional<ByteString>> Jakt::jakt__arguments::ArgsParser::option(JaktInternal::DynamicArray<ByteString> const names) {
{
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(this->args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
{
JaktInternal::ArrayIterator<ByteString> _magic = names.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString name = _magic_value.value();
{
if (this->args.operator[](i) == name){
if (this->args.size() <= JaktInternal::checked_add(i,static_cast<size_t>(1ULL))){
warnln(StringView::from_string_literal("The option '{}' requires a value, but none was supplied"sv),name);
return Error::from_errno(static_cast<i32>(200));
}
this->removed_indices.push(i);
this->removed_indices.push(JaktInternal::checked_add(i,static_cast<size_t>(1ULL)));
return this->args.operator[](JaktInternal::checked_add(i,static_cast<size_t>(1ULL)));
}
if (this->args.operator[](i).starts_with(name)){
this->removed_indices.push(i);
return this->args.operator[](i).substring(name.length(),JaktInternal::checked_sub(this->args.operator[](i).length(),name.length()));
}
}

}
}

}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::DynamicArray<ByteString>> Jakt::jakt__arguments::ArgsParser::option_multiple(JaktInternal::DynamicArray<ByteString> const names) {
{
JaktInternal::DynamicArray<ByteString> result = DynamicArray<ByteString>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(this->args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
{
JaktInternal::ArrayIterator<ByteString> _magic = names.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString name = _magic_value.value();
{
if (this->args.operator[](i) == name){
if (this->args.size() <= JaktInternal::checked_add(i,static_cast<size_t>(1ULL))){
warnln(StringView::from_string_literal("The option '{}' requires a value, but none was supplied"sv),name);
return Error::from_errno(static_cast<i32>(200));
}
this->removed_indices.push(i);
this->removed_indices.push(JaktInternal::checked_add(i,static_cast<size_t>(1ULL)));
result.push(this->args.operator[](JaktInternal::checked_add(i,static_cast<size_t>(1ULL))));
continue;
}
if (this->args.operator[](i).starts_with(name)){
this->removed_indices.push(i);
result.push(this->args.operator[](i).substring(name.length(),JaktInternal::checked_sub(this->args.operator[](i).length(),name.length())));
}
}

}
}

}

}
}

return result;
}
}

Jakt::jakt__arguments::ArgsParser Jakt::jakt__arguments::ArgsParser::from_args(JaktInternal::DynamicArray<ByteString> const args) {
{
Jakt::jakt__arguments::ArgsParser parser = Jakt::jakt__arguments::ArgsParser(args,DynamicArray<size_t>::create_with({}),DynamicArray<ByteString>::create_with({}));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ByteString> _magic = parser.args.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString arg = _magic_value.value();
{
if (arg == ByteString::from_utf8_without_validation("--"sv)){
parser.definitely_positional_args = parser.args.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(JaktInternal::checked_add(i,static_cast<size_t>(1ULL))),static_cast<size_t>(parser.args.size())}).to_array();
parser.args = parser.args.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(i)}).to_array();
break;
}
i += static_cast<size_t>(1ULL);
}

}
}

return parser;
}
}

JaktInternal::DynamicArray<ByteString> Jakt::jakt__arguments::ArgsParser::remaining_arguments() const {
{
JaktInternal::DynamicArray<ByteString> remaining = DynamicArray<ByteString>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(this->args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (!this->removed_indices.contains(i)){
remaining.push(this->args.operator[](i));
}
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = this->definitely_positional_args.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString arg = _magic_value.value();
{
remaining.push(arg);
}

}
}

return remaining;
}
}

Jakt::jakt__arguments::ArgsParser::ArgsParser(JaktInternal::DynamicArray<ByteString> a_args, JaktInternal::DynamicArray<size_t> a_removed_indices, JaktInternal::DynamicArray<ByteString> a_definitely_positional_args): args(move(a_args)), removed_indices(move(a_removed_indices)), definitely_positional_args(move(a_definitely_positional_args)){}

}
} // namespace Jakt
