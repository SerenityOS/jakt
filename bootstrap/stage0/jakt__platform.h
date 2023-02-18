#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__platform {
struct Target {
  public:
DeprecatedString arch;DeprecatedString platform;DeprecatedString os;DeprecatedString abi;Target(DeprecatedString a_arch, DeprecatedString a_platform, DeprecatedString a_os, DeprecatedString a_abi);

ErrorOr<size_t> int_alignment() const;
ErrorOr<size_t> pointer_size() const;
static ErrorOr<jakt__platform::Target> active();
ErrorOr<size_t> size_t_alignment() const;
ErrorOr<size_t> size_t_size() const;
ErrorOr<size_t> int_size() const;
ErrorOr<size_t> pointer_alignment() const;
ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform::Target> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform::Target const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
