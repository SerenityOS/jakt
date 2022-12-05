#include "unknown_process.h"
namespace Jakt {
namespace unknown_process {
ErrorOr<unknown_process::Process> start_background_process(JaktInternal::Array<String> const args) {
{
warnln(Jakt::String("NOT IMPLEMENTED: start_background_process {}"),args);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<size_t>,unknown_process::ExitPollResult>> wait_for_some_set_of_processes_that_at_least_includes(JaktInternal::Dictionary<size_t,unknown_process::Process> const& processes) {
{
warnln(Jakt::String("NOT IMPLEMENTED: wait_for_some_set_of_processes_that_at_least_includes {}"),processes);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<unknown_process::ExitPollResult> wait_for_process(unknown_process::Process const& process) {
{
warnln(Jakt::String("NOT IMPLEMENTED: wait_for_process {}"),process);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<void> forcefully_kill_process(unknown_process::Process const& process) {
{
warnln(Jakt::String("NOT IMPLEMENTED: forcefully_kill_process {}"),process);
return Error::from_errno(static_cast<i32>(38));
}
return {};
}

ErrorOr<JaktInternal::Optional<unknown_process::ExitPollResult>> poll_process_exit(unknown_process::Process const& process) {
{
warnln(Jakt::String("NOT IMPLEMENTED: poll_process_exit {}"),process);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<String> unknown_process::Process::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Process("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
TRY(builder.append(")"));return builder.to_string(); }
unknown_process::Process::Process() {}

ErrorOr<String> unknown_process::ExitPollResult::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("ExitPollResult("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("exit_code: "));TRY(builder.appendff("{}, ", exit_code));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("process: "));TRY(builder.appendff("{}", process));
}
TRY(builder.append(")"));return builder.to_string(); }
unknown_process::ExitPollResult::ExitPollResult(i32 a_exit_code, unknown_process::Process a_process) :exit_code(a_exit_code), process(a_process){}

}
} // namespace Jakt
