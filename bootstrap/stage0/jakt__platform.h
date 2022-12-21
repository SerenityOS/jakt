#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__platform {
struct Target {
  public:
DeprecatedString arch;DeprecatedString platform;DeprecatedString os;DeprecatedString abi;static ErrorOr<jakt__platform::Target> active();
Target(DeprecatedString a_arch, DeprecatedString a_platform, DeprecatedString a_os, DeprecatedString a_abi);

ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform::Target> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform::Target const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
