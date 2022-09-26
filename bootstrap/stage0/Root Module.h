#pragma once
#include "__unified_forward.h"
#include "compiler.h"
#include "codegen.h"
#include "error.h"
#include "formatter.h"
#include "utility.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "typechecker.h"
#include "types.h"
#include "repl.h"
#include "ide.h"
#include "os.h"
#include "unknown_process.h"
#include "unknown_fs.h"
namespace Jakt {
struct FormatRange {
  public:
size_t start;size_t end;FormatRange(size_t a_start, size_t a_end);

ErrorOr<String> debug_description() const;
};struct ParallelExecutionPool {
  public:
JaktInternal::Dictionary<size_t,unknown_process::Process> pids;JaktInternal::Dictionary<size_t,unknown_process::ExitPollResult> completed;size_t pid_index;size_t max_concurrent;static ErrorOr<ParallelExecutionPool> create(const size_t max_concurrent);
JaktInternal::Optional<unknown_process::ExitPollResult> status(const size_t id) const;
ParallelExecutionPool(JaktInternal::Dictionary<size_t,unknown_process::Process> a_pids, JaktInternal::Dictionary<size_t,unknown_process::ExitPollResult> a_completed, size_t a_pid_index, size_t a_max_concurrent);

ErrorOr<void> wait_for_any_job_to_complete();
ErrorOr<size_t> run(const JaktInternal::Array<String> args);
ErrorOr<void> kill_all();
ErrorOr<void> wait_for_all_jobs_to_complete();
ErrorOr<String> debug_description() const;
};template <typename T>
ErrorOr<T> value_or_throw(const JaktInternal::Optional<T> maybe) {
{
if (((maybe).has_value())){
return ((maybe.value()));
}
return Error::from_errno(static_cast<i32>(1));
}
}

template<>struct Formatter<FormatRange> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, FormatRange const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<ParallelExecutionPool> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, ParallelExecutionPool const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
