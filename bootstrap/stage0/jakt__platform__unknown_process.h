#pragma once
#include "__unified_forward.h"
namespace Jakt {
namespace jakt__platform__unknown_process {
struct Process {
  public:
public: Process();

public: ErrorOr<ByteString> debug_description() const;
};struct ExitPollResult {
  public:
public: i32 exit_code;public: jakt__platform__unknown_process::Process process;public: ExitPollResult(i32 a_exit_code, jakt__platform__unknown_process::Process a_process);

public: ErrorOr<ByteString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform__unknown_process::Process> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform__unknown_process::Process const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform__unknown_process::ExitPollResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform__unknown_process::ExitPollResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
