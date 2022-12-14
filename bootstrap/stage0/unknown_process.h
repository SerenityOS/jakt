#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace unknown_process {
struct Process {
  public:
Process();

ErrorOr<DeprecatedString> debug_description() const;
};struct ExitPollResult {
  public:
i32 exit_code;unknown_process::Process process;ExitPollResult(i32 a_exit_code, unknown_process::Process a_process);

ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::unknown_process::Process> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::unknown_process::Process const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::unknown_process::ExitPollResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::unknown_process::ExitPollResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
namespace Jakt {
} // namespace Jakt
