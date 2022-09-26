#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace unknown_process {
struct Process {
  public:
Process();

ErrorOr<String> debug_description() const;
};struct ExitPollResult {
  public:
i32 exit_code;unknown_process::Process process;ExitPollResult(i32 a_exit_code, unknown_process::Process a_process);

ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<unknown_process::Process> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, unknown_process::Process const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<unknown_process::ExitPollResult> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, unknown_process::ExitPollResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
