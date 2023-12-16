#include "jakt__platform__unknown_process.h"
namespace Jakt {
namespace jakt__platform__unknown_process {
ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<size_t>,jakt__platform__unknown_process::ExitPollResult>> wait_for_some_set_of_processes_that_at_least_includes(JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::Process> const& processes) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: wait_for_some_set_of_processes_that_at_least_includes {}"sv)),processes);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<jakt__platform__unknown_process::ExitPollResult> wait_for_process(jakt__platform__unknown_process::Process const& process) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: wait_for_process {}"sv)),process);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<jakt__platform__unknown_process::Process> start_background_process(JaktInternal::DynamicArray<ByteString> const args) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: start_background_process {}"sv)),args);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult>> poll_process_exit(jakt__platform__unknown_process::Process const& process) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: poll_process_exit {}"sv)),process);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<void> forcefully_kill_process(jakt__platform__unknown_process::Process const& process) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: forcefully_kill_process {}"sv)),process);
return Error::from_errno(static_cast<i32>(38));
}
return {};
}

ErrorOr<ByteString> jakt__platform__unknown_process::Process::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("Process("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
TRY(builder.append(")"sv));return builder.to_string(); }
jakt__platform__unknown_process::Process::Process(){}

ErrorOr<ByteString> jakt__platform__unknown_process::ExitPollResult::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("ExitPollResult("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("exit_code: {}, ", exit_code));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("process: {}", process));
}
TRY(builder.append(")"sv));return builder.to_string(); }
jakt__platform__unknown_process::ExitPollResult::ExitPollResult(i32 a_exit_code, jakt__platform__unknown_process::Process a_process): exit_code(move(a_exit_code)), process(move(a_process)){}

}
} // namespace Jakt
