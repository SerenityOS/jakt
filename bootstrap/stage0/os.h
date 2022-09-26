#pragma once
#include "__unified_forward.h"
#include "utility.h"
namespace Jakt {
namespace os {
struct Target {
  public:
String arch;String platform;String os;String abi;static ErrorOr<os::Target> active();
Target(String a_arch, String a_platform, String a_os, String a_abi);

ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<os::Target> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, os::Target const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
