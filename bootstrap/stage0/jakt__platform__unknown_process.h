#pragma once
#include <lib.h>
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace jakt__platform__unknown_process {
struct Process;
struct ExitPollResult;
ErrorOr<Jakt::jakt__platform__unknown_process::Process> start_background_process(JaktInternal::DynamicArray<ByteString> const args);

ErrorOr<JaktInternal::Optional<Jakt::jakt__platform__unknown_process::ExitPollResult>> poll_process_exit(Jakt::jakt__platform__unknown_process::Process const& process);

ErrorOr<Jakt::jakt__platform__unknown_process::ExitPollResult> wait_for_process(Jakt::jakt__platform__unknown_process::Process const& process);

ErrorOr<void> forcefully_kill_process(Jakt::jakt__platform__unknown_process::Process const& process);

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<size_t>,Jakt::jakt__platform__unknown_process::ExitPollResult>> wait_for_some_set_of_processes_that_at_least_includes(JaktInternal::Dictionary<size_t,Jakt::jakt__platform__unknown_process::Process> const& processes);

}
namespace jakt__platform__unknown_process {
struct Process {
  public:
public: Process();

public: ByteString debug_description() const;
};struct ExitPollResult {
  public:
public: i32 exit_code;public: Jakt::jakt__platform__unknown_process::Process process;public: ExitPollResult(i32 a_exit_code, Jakt::jakt__platform__unknown_process::Process a_process);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform__unknown_process::Process> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform__unknown_process::Process const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform__unknown_process::ExitPollResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform__unknown_process::ExitPollResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
