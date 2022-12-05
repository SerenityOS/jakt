#include "build.h"
namespace Jakt {
namespace build {
ErrorOr<String> build::Builder::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Builder("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("linked_files: "));TRY(builder.appendff("{}, ", linked_files));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("files_to_compile: "));TRY(builder.appendff("{}, ", files_to_compile));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("pool: "));TRY(builder.appendff("{}", pool));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<void> build::Builder::link_into_archive(String const archiver,String const archive_filename) {
{
JaktInternal::Array<String> args = (TRY((Array<String>::create_with({archiver, Jakt::String("cr"), archive_filename}))));
{
JaktInternal::ArrayIterator<String> _magic = ((((*this).linked_files)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String file = (_magic_value.value());
{
TRY((((args).push(file))));
}

}
}

size_t const id = TRY((((((*this).pool)).run(args))));
TRY((((((*this).pool)).wait_for_all_jobs_to_complete())));
if (((((((((*this).pool)).status(id)).value())).exit_code) != static_cast<i32>(0))){
warnln(Jakt::String("Error: Linking failed"));
return Error::from_errno(static_cast<i32>(1));
}
}
return {};
}

build::Builder::Builder(JaktInternal::Array<String> a_linked_files, JaktInternal::Array<String> a_files_to_compile, build::ParallelExecutionPool a_pool) :linked_files(a_linked_files), files_to_compile(a_files_to_compile), pool(a_pool){}

ErrorOr<void> build::Builder::link_into_executable(String const cxx_compiler_path,String const output_filename,JaktInternal::Array<String> const extra_arguments) {
{
JaktInternal::Array<String> args = (TRY((Array<String>::create_with({cxx_compiler_path, Jakt::String("-o"), output_filename}))));
{
JaktInternal::ArrayIterator<String> _magic = ((((*this).linked_files)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String file = (_magic_value.value());
{
TRY((((args).push(file))));
}

}
}

{
JaktInternal::ArrayIterator<String> _magic = ((extra_arguments).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String arg = (_magic_value.value());
{
TRY((((args).push(arg))));
}

}
}

size_t const id = TRY((((((*this).pool)).run(args))));
TRY((((((*this).pool)).wait_for_all_jobs_to_complete())));
if (((((((((*this).pool)).status(id)).value())).exit_code) != static_cast<i32>(0))){
warnln(Jakt::String("Error: Linking failed"));
return Error::from_errno(static_cast<i32>(1));
}
}
return {};
}

ErrorOr<build::Builder> build::Builder::for_building(JaktInternal::Array<String> const files,size_t const max_concurrent) {
{
return (build::Builder((TRY((Array<String>::create_with({})))),files,TRY((build::ParallelExecutionPool::ParallelExecutionPool::create(max_concurrent)))));
}
}

ErrorOr<void> build::Builder::build_all(path::Path const binary_dir,Function<ErrorOr<JaktInternal::Array<String>>(String, String)> const& compiler_invocation) {
{
JaktInternal::Set<size_t> ids = (TRY((Set<size_t>::create_with_values({}))));
{
JaktInternal::ArrayIterator<String> _magic = ((((*this).files_to_compile)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String file_name = (_magic_value.value());
{
{
JaktInternal::DictionaryIterator<size_t,unknown_process::ExitPollResult> _magic = ((((((*this).pool)).completed)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,unknown_process::ExitPollResult>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,unknown_process::ExitPollResult> id__exit_result__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,unknown_process::ExitPollResult> const jakt__id__exit_result__ = id__exit_result__;
size_t const id = ((jakt__id__exit_result__).template get<0>());
unknown_process::ExitPollResult const exit_result = ((jakt__id__exit_result__).template get<1>());

if ((((exit_result).exit_code) != static_cast<i32>(0))){
warnln(Jakt::String("Error: Compilation failed"));
TRY((((((*this).pool)).kill_all())));
return Error::from_errno(static_cast<i32>(1));
}
}

}
}

String const built_object = ((TRY((((binary_dir).join(((TRY((((TRY((path::Path::Path::from_string(file_name)))).replace_extension(Jakt::String("o")))))).to_string())))))).to_string());
TRY((((((*this).linked_files)).push(built_object))));
size_t const id = TRY((((((*this).pool)).run(TRY((compiler_invocation(((TRY((((binary_dir).join(file_name))))).to_string()),built_object)))))));
TRY((((ids).add(id))));
warnln(Jakt::String("{:c}[2LBuilding: {}/{}"),static_cast<i64>(27LL),((ids).size()),((((*this).files_to_compile)).size()));
}

}
}

TRY((((((*this).pool)).wait_for_all_jobs_to_complete())));
{
JaktInternal::DictionaryIterator<size_t,unknown_process::ExitPollResult> _magic = ((((((*this).pool)).completed)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,unknown_process::ExitPollResult>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,unknown_process::ExitPollResult> id__exit_result__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,unknown_process::ExitPollResult> const jakt__id__exit_result__ = id__exit_result__;
size_t const id = ((jakt__id__exit_result__).template get<0>());
unknown_process::ExitPollResult const exit_result = ((jakt__id__exit_result__).template get<1>());

if ((((exit_result).exit_code) != static_cast<i32>(0))){
warnln(Jakt::String("Error: Compilation failed"));
return Error::from_errno(static_cast<i32>(1));
}
}

}
}

(((*this).files_to_compile) = (TRY((Array<String>::create_with({})))));
}
return {};
}

ErrorOr<String> build::ParallelExecutionPool::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("ParallelExecutionPool("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("pids: "));TRY(builder.appendff("{}, ", pids));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("completed: "));TRY(builder.appendff("{}, ", completed));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("pid_index: "));TRY(builder.appendff("{}, ", pid_index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("max_concurrent: "));TRY(builder.appendff("{}", max_concurrent));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<build::ParallelExecutionPool> build::ParallelExecutionPool::create(size_t const max_concurrent) {
{
return (build::ParallelExecutionPool((TRY((Dictionary<size_t, unknown_process::Process>::create_with_entries({})))),(TRY((Dictionary<size_t, unknown_process::ExitPollResult>::create_with_entries({})))),static_cast<size_t>(0ULL),max_concurrent));
}
}

JaktInternal::Optional<unknown_process::ExitPollResult> build::ParallelExecutionPool::status(size_t const id) const {
{
if (((((*this).completed)).contains(id))){
return (((((*this).completed))[id]));
}
return (JaktInternal::OptionalNone());
}
}

build::ParallelExecutionPool::ParallelExecutionPool(JaktInternal::Dictionary<size_t,unknown_process::Process> a_pids, JaktInternal::Dictionary<size_t,unknown_process::ExitPollResult> a_completed, size_t a_pid_index, size_t a_max_concurrent) :pids(a_pids), completed(a_completed), pid_index(a_pid_index), max_concurrent(a_max_concurrent){}

ErrorOr<void> build::ParallelExecutionPool::wait_for_any_job_to_complete() {
{
JaktInternal::Tuple<JaktInternal::Optional<size_t>,unknown_process::ExitPollResult> const finished_pid_finished_status_ = TRY((unknown_process::wait_for_some_set_of_processes_that_at_least_includes(((((*this).pids))))));
JaktInternal::Optional<size_t> const finished_pid = ((finished_pid_finished_status_).template get<0>());
unknown_process::ExitPollResult const finished_status = ((finished_pid_finished_status_).template get<1>());

JaktInternal::Dictionary<size_t,unknown_process::ExitPollResult> pids_to_remove = (TRY((Dictionary<size_t, unknown_process::ExitPollResult>::create_with_entries({}))));
if (((finished_pid).has_value())){
TRY((((pids_to_remove).set((finished_pid.value()),finished_status))));
}
{
JaktInternal::DictionaryIterator<size_t,unknown_process::Process> _magic = ((((*this).pids)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,unknown_process::Process>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,unknown_process::Process> index__process__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,unknown_process::Process> const jakt__index__process__ = index__process__;
size_t const index = ((jakt__index__process__).template get<0>());
unknown_process::Process const process = ((jakt__index__process__).template get<1>());

JaktInternal::Optional<unknown_process::ExitPollResult> const status = ({ Optional<JaktInternal::Optional<unknown_process::ExitPollResult>> __jakt_var_722;
auto __jakt_var_723 = [&]() -> ErrorOr<JaktInternal::Optional<unknown_process::ExitPollResult>> { return TRY((unknown_process::poll_process_exit(((process))))); }();
if (__jakt_var_723.is_error()) {{
TRY((((pids_to_remove).set(index,finished_status))));
continue;
}
} else {__jakt_var_722 = __jakt_var_723.release_value();
}
__jakt_var_722.release_value(); });
if (((status).has_value())){
TRY((((pids_to_remove).set(index,(status.value())))));
}
}

}
}

{
JaktInternal::DictionaryIterator<size_t,unknown_process::ExitPollResult> _magic = ((pids_to_remove).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,unknown_process::ExitPollResult>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,unknown_process::ExitPollResult> index__status__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,unknown_process::ExitPollResult> const jakt__index__status__ = index__status__;
size_t const index = ((jakt__index__status__).template get<0>());
unknown_process::ExitPollResult const status = ((jakt__index__status__).template get<1>());

((((*this).pids)).remove(index));
TRY((((((*this).completed)).set(index,status))));
}

}
}

}
return {};
}

ErrorOr<size_t> build::ParallelExecutionPool::run(JaktInternal::Array<String> const args) {
{
if ((((((*this).pids)).size()) >= ((*this).max_concurrent))){
TRY((((*this).wait_for_any_job_to_complete())));
}
unknown_process::Process const process = TRY((unknown_process::start_background_process(args)));
size_t const id = ((((*this).pid_index)++));
TRY((((((*this).pids)).set(id,process))));
return (id);
}
}

ErrorOr<void> build::ParallelExecutionPool::kill_all() {
{
{
JaktInternal::DictionaryIterator<size_t,unknown_process::Process> _magic = ((((*this).pids)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,unknown_process::Process>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,unknown_process::Process> ___process__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,unknown_process::Process> const jakt_____process__ = ___process__;
size_t const _ = ((jakt_____process__).template get<0>());
unknown_process::Process const process = ((jakt_____process__).template get<1>());

TRY((unknown_process::forcefully_kill_process(((process)))));
}

}
}

}
return {};
}

ErrorOr<void> build::ParallelExecutionPool::wait_for_all_jobs_to_complete() {
{
while ((!(((((*this).pids)).is_empty())))){
TRY((((*this).wait_for_any_job_to_complete())));
}
}
return {};
}

}
} // namespace Jakt
