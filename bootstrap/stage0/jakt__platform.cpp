#include "jakt__platform.h"
namespace Jakt {
namespace jakt__platform {



ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> add_to_each(JaktInternal::DynamicArray<DeprecatedString> const strings,DeprecatedString const prefix,DeprecatedString const suffix) {
{
JaktInternal::DynamicArray<DeprecatedString> output = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString str = (_magic_value.value());
{
TRY((((output).push(((prefix + str) + suffix)))));
}

}
}

return (output);
}
}

JaktInternal::Optional<size_t> last_namespace_separator(DeprecatedString const name) {
{
size_t i = (JaktInternal::checked_sub<size_t>(((name).length()),static_cast<size_t>(1ULL)));
while ((i >= static_cast<size_t>(2ULL))){
if (((((name).byte_at(i)) == ':') && (((name).byte_at((JaktInternal::checked_sub<size_t>(i,static_cast<size_t>(1ULL))))) == ':'))){
return ((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))));
}
((i--));
}
return (JaktInternal::OptionalNone());
}
}





ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> platform_import_names() {
{
jakt__platform::Target const target = TRY((jakt__platform::Target::active()));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<DeprecatedString>,ErrorOr<JaktInternal::DynamicArray<DeprecatedString>>>{
auto __jakt_enum_value = (((target).os));
if (__jakt_enum_value == Jakt::DeprecatedString("windows"sv)) {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<DeprecatedString>,ErrorOr<JaktInternal::DynamicArray<DeprecatedString>>>{
auto __jakt_enum_value = (((target).arch));
if (__jakt_enum_value == Jakt::DeprecatedString("x86_64"sv)) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({Jakt::DeprecatedString("win64"sv), Jakt::DeprecatedString("windows"sv)})))));
}
else if (__jakt_enum_value == Jakt::DeprecatedString("i686"sv)) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({Jakt::DeprecatedString("win32"sv), Jakt::DeprecatedString("windows"sv)})))));
}
else {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({Jakt::DeprecatedString("windows"sv)})))));
}
}()))
);
}
else if (__jakt_enum_value == Jakt::DeprecatedString("darwin"sv)) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({Jakt::DeprecatedString("darwin"sv), Jakt::DeprecatedString("posix"sv)})))));
}
else if (__jakt_enum_value == Jakt::DeprecatedString("linux"sv)) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), Jakt::DeprecatedString("posix"sv)})))));
}
else if (__jakt_enum_value == Jakt::DeprecatedString("openbsd"sv)) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), Jakt::DeprecatedString("posix"sv)})))));
}
else if (__jakt_enum_value == Jakt::DeprecatedString("serenity"sv)) {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), Jakt::DeprecatedString("posix"sv)})))));
}
else {
return JaktInternal::ExplicitValue((TRY((DynamicArray<DeprecatedString>::create_with({((target).os), Jakt::DeprecatedString("unknown"sv)})))));
}
}()))
);
}
}

ErrorOr<DeprecatedString> jakt__platform::Target::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Target("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("arch: "sv));TRY(builder.appendff("\"{}\", ", arch));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("platform: "sv));TRY(builder.appendff("\"{}\", ", platform));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("os: "sv));TRY(builder.appendff("\"{}\", ", os));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("abi: "sv));TRY(builder.appendff("\"{}\"", abi));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<jakt__platform::Target> jakt__platform::Target::active() {
{
DeprecatedString const triple = TRY((___jakt_get_target_triple_string()));
JaktInternal::DynamicArray<DeprecatedString> const parts = ((triple).split('-'));
if ((((parts).size()) != static_cast<size_t>(4ULL))){
warnln(Jakt::DeprecatedString("Invalid target triple '{}'"sv),triple);
return Error::from_errno(static_cast<i32>(22));
}
return (jakt__platform::Target(((parts)[static_cast<i64>(0LL)]),((parts)[static_cast<i64>(1LL)]),((parts)[static_cast<i64>(2LL)]),((parts)[static_cast<i64>(3LL)])));
}
}

jakt__platform::Target::Target(DeprecatedString a_arch, DeprecatedString a_platform, DeprecatedString a_os, DeprecatedString a_abi) :arch(a_arch), platform(a_platform), os(a_os), abi(a_abi){}

}
} // namespace Jakt
