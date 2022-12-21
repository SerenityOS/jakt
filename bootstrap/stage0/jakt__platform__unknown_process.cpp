#include "jakt__platform__unknown_process.h"
namespace Jakt {
namespace jakt__platform__unknown_process {
ErrorOr<jakt__platform__unknown_process::Process> start_background_process(JaktInternal::DynamicArray<DeprecatedString> const args) {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: start_background_process {}"sv),args);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<size_t>,jakt__platform__unknown_process::ExitPollResult>> wait_for_some_set_of_processes_that_at_least_includes(JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::Process> const& processes) {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: wait_for_some_set_of_processes_that_at_least_includes {}"sv),processes);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<jakt__platform__unknown_process::ExitPollResult> wait_for_process(jakt__platform__unknown_process::Process const& process) {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: wait_for_process {}"sv),process);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<void> forcefully_kill_process(jakt__platform__unknown_process::Process const& process) {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: forcefully_kill_process {}"sv),process);
return Error::from_errno(static_cast<i32>(38));
}
return {};
}

ErrorOr<JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult>> poll_process_exit(jakt__platform__unknown_process::Process const& process) {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: poll_process_exit {}"sv),process);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<DeprecatedString> jakt__platform__unknown_process::Process::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Process("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
TRY(builder.append(")"sv));return builder.to_string(); }
jakt__platform__unknown_process::Process::Process() {}

ErrorOr<DeprecatedString> jakt__platform__unknown_process::ExitPollResult::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("ExitPollResult("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("exit_code: "sv));TRY(builder.appendff("{}, ", exit_code));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("process: "sv));TRY(builder.appendff("{}", process));
}
TRY(builder.append(")"sv));return builder.to_string(); }
jakt__platform__unknown_process::ExitPollResult::ExitPollResult(i32 a_exit_code, jakt__platform__unknown_process::Process a_process) :exit_code(a_exit_code), process(a_process){}

}
} // namespace Jakt
