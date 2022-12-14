#include "os.h"
namespace Jakt {
namespace os {



ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> platform_import_names() {
{
os::Target const target = TRY((os::Target::Target::active()));
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

ErrorOr<DeprecatedString> os::Target::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Target("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("arch: "sv));TRY(builder.appendff("\"{}\", ", arch));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("platform: "sv));TRY(builder.appendff("\"{}\", ", platform));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("os: "sv));TRY(builder.appendff("\"{}\", ", os));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("abi: "sv));TRY(builder.appendff("\"{}\"", abi));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<os::Target> os::Target::active() {
{
DeprecatedString const triple = TRY((___jakt_get_target_triple_string()));
JaktInternal::DynamicArray<DeprecatedString> const parts = ((triple).split('-'));
if ((((parts).size()) != static_cast<size_t>(4ULL))){
warnln(Jakt::DeprecatedString("Invalid target triple '{}'"sv),triple);
return Error::from_errno(static_cast<i32>(22));
}
return (os::Target(((parts)[static_cast<i64>(0LL)]),((parts)[static_cast<i64>(1LL)]),((parts)[static_cast<i64>(2LL)]),((parts)[static_cast<i64>(3LL)])));
}
}

os::Target::Target(DeprecatedString a_arch, DeprecatedString a_platform, DeprecatedString a_os, DeprecatedString a_abi) :arch(a_arch), platform(a_platform), os(a_os), abi(a_abi){}

}
} // namespace Jakt
