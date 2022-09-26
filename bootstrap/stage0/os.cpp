#include "os.h"
namespace Jakt {
namespace os {



ErrorOr<JaktInternal::Array<String>> platform_import_names() {
{
const os::Target target = TRY((os::Target::active()));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<String>,ErrorOr<JaktInternal::Array<String>>>{
auto __jakt_enum_value = (((target).os));
if (__jakt_enum_value == String("windows")) {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<String>,ErrorOr<JaktInternal::Array<String>>>{
auto __jakt_enum_value = (((target).arch));
if (__jakt_enum_value == String("x86_64")) {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({String("win64"), String("windows")})))));
}
else if (__jakt_enum_value == String("i686")) {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({String("win32"), String("windows")})))));
}
else {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({String("windows")})))));
}
}()))
);
}
else if (__jakt_enum_value == String("darwin")) {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({String("darwin"), String("posix")})))));
}
else if (__jakt_enum_value == String("linux")) {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({((target).os), String("posix")})))));
}
else if (__jakt_enum_value == String("openbsd")) {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({((target).os), String("posix")})))));
}
else if (__jakt_enum_value == String("serenity")) {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({((target).os), String("posix")})))));
}
else {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({((target).os), String("unknown")})))));
}
}()))
);
}
}

ErrorOr<String> os::Target::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Target("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("arch: "));TRY(builder.appendff("\"{}\", ", arch));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("platform: "));TRY(builder.appendff("\"{}\", ", platform));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("os: "));TRY(builder.appendff("\"{}\", ", os));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("abi: "));TRY(builder.appendff("\"{}\"", abi));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<os::Target> os::Target::active() {
{
const String triple = ___jakt_get_target_triple_string();
const JaktInternal::Array<String> parts = TRY((((triple).split('-'))));
if ((((parts).size()) != static_cast<size_t>(4ULL))){
warnln(String("Invalid target triple '{}'"),triple);
return Error::from_errno(static_cast<i32>(22));
}
return (os::Target(((parts)[static_cast<i64>(0LL)]),((parts)[static_cast<i64>(1LL)]),((parts)[static_cast<i64>(2LL)]),((parts)[static_cast<i64>(3LL)])));
}
}

os::Target::Target(String a_arch, String a_platform, String a_os, String a_abi) :arch(a_arch), platform(a_platform), os(a_os), abi(a_abi){}

}
} // namespace Jakt
