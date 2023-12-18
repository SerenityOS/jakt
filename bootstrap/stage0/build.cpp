#include "build.h"
namespace Jakt {
namespace build {
ErrorOr<ByteString> build::Builder::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("Builder("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("linked_files: {}, ", linked_files));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("files_to_compile: {}, ", files_to_compile));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("pool: {}", pool));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> build::Builder::link_into_executable(ByteString const cxx_compiler_path,ByteString const output_filename,JaktInternal::DynamicArray<ByteString> const extra_arguments) {
{
JaktInternal::DynamicArray<ByteString> args = (TRY((DynamicArray<ByteString>::create_with({cxx_compiler_path, (ByteString::must_from_utf8("-o"sv)), output_filename}))));
{
JaktInternal::ArrayIterator<ByteString> _magic = ((((*this).linked_files)).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString file = (_magic_value.value());
{
TRY((((args).push(file))));
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = ((extra_arguments).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString arg = (_magic_value.value());
{
TRY((((args).push(arg))));
}

}
}

size_t const id = TRY((((((*this).pool)).run(args))));
TRY((((((*this).pool)).wait_for_all_jobs_to_complete())));
if ((((((((((*this).pool)).status(id)).value())).exit_code)) != (static_cast<i32>(0)))){
warnln((StringView::from_string_literal("Error: Linking failed"sv)));
return Error::from_errno(static_cast<i32>(1));
}
}
return {};
}

ErrorOr<build::Builder> build::Builder::for_building(JaktInternal::DynamicArray<ByteString> const files,size_t const max_concurrent) {
{
return build::Builder((TRY((DynamicArray<ByteString>::create_with({})))),files,TRY((build::ParallelExecutionPool::create(max_concurrent))));
}
}

ErrorOr<void> build::Builder::link_into_archive(ByteString const archiver,ByteString const archive_filename,JaktInternal::DynamicArray<ByteString> const extra_arguments) {
{
JaktInternal::DynamicArray<ByteString> args = (TRY((DynamicArray<ByteString>::create_with({archiver, ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<void>>{
auto __jakt_enum_value = (((extra_arguments).size()));
if (__jakt_enum_value == static_cast<size_t>(0ULL)) {
return JaktInternal::ExplicitValue((ByteString::must_from_utf8("cr"sv)));
}
else {
return JaktInternal::ExplicitValue((ByteString::must_from_utf8("crT"sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}), archive_filename}))));
{
JaktInternal::ArrayIterator<ByteString> _magic = ((((*this).linked_files)).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString file = (_magic_value.value());
{
TRY((((args).push(file))));
}

}
}

TRY((((args).push_values(((extra_arguments))))));
size_t const id = TRY((((((*this).pool)).run(args))));
TRY((((((*this).pool)).wait_for_all_jobs_to_complete())));
if ((((((((((*this).pool)).status(id)).value())).exit_code)) != (static_cast<i32>(0)))){
warnln((StringView::from_string_literal("Error: Linking failed"sv)));
return Error::from_errno(static_cast<i32>(1));
}
}
return {};
}

build::Builder::Builder(JaktInternal::DynamicArray<ByteString> a_linked_files, JaktInternal::DynamicArray<ByteString> a_files_to_compile, build::ParallelExecutionPool a_pool): linked_files(move(a_linked_files)), files_to_compile(move(a_files_to_compile)), pool(move(a_pool)){}

ErrorOr<void> build::Builder::build_all(jakt__path::Path const binary_dir,Function<ErrorOr<JaktInternal::DynamicArray<ByteString>>(ByteString, ByteString)> const& compiler_invocation) {
{
JaktInternal::Set<size_t> ids = (TRY((Set<size_t>::create_with_values({}))));
{
JaktInternal::ArrayIterator<ByteString> _magic = ((((*this).files_to_compile)).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString file_name = (_magic_value.value());
{
{
JaktInternal::DictionaryIterator<size_t,jakt__platform__unknown_process::ExitPollResult> _magic = ((((((*this).pool)).completed)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult> id__exit_result__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult> const jakt__id__exit_result__ = id__exit_result__;
size_t const id = ((jakt__id__exit_result__).template get<0>());
jakt__platform__unknown_process::ExitPollResult const exit_result = ((jakt__id__exit_result__).template get<1>());

if (((((exit_result).exit_code)) != (static_cast<i32>(0)))){
warnln((StringView::from_string_literal("Error: Compilation failed"sv)));
TRY((((((*this).pool)).kill_all())));
return Error::from_errno(static_cast<i32>(1));
}
}

}
}

ByteString const built_object = ((TRY((((binary_dir).join(((TRY((((TRY((jakt__path::Path::from_string(file_name)))).replace_extension((ByteString::must_from_utf8("o"sv))))))).to_string())))))).to_string());
TRY((((((*this).linked_files)).push(built_object))));
JaktInternal::DynamicArray<ByteString> const args = TRY((compiler_invocation(((TRY((((binary_dir).join(file_name))))).to_string()),built_object)));
size_t const id = TRY((((((*this).pool)).run(args))));
TRY((((ids).add(id))));
warnln((StringView::from_string_literal("{:c}[2LBuilding: {}/{} ({})"sv)),static_cast<i64>(27LL),((ids).size()),((((*this).files_to_compile)).size()),file_name);
}

}
}

TRY((((((*this).pool)).wait_for_all_jobs_to_complete())));
{
JaktInternal::DictionaryIterator<size_t,jakt__platform__unknown_process::ExitPollResult> _magic = ((((((*this).pool)).completed)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult> id__exit_result__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult> const jakt__id__exit_result__ = id__exit_result__;
size_t const id = ((jakt__id__exit_result__).template get<0>());
jakt__platform__unknown_process::ExitPollResult const exit_result = ((jakt__id__exit_result__).template get<1>());

if (((((exit_result).exit_code)) != (static_cast<i32>(0)))){
warnln((StringView::from_string_literal("Error: Compilation failed"sv)));
return Error::from_errno(static_cast<i32>(1));
}
}

}
}

(((*this).files_to_compile) = (TRY((DynamicArray<ByteString>::create_with({})))));
}
return {};
}

ErrorOr<ByteString> build::ParallelExecutionPool::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("ParallelExecutionPool("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("pids: {}, ", pids));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("completed: {}, ", completed));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("pid_index: {}, ", pid_index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("max_concurrent: {}", max_concurrent));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<build::ParallelExecutionPool> build::ParallelExecutionPool::create(size_t const max_concurrent) {
{
return build::ParallelExecutionPool((TRY((Dictionary<size_t, jakt__platform__unknown_process::Process>::create_with_entries({})))),(TRY((Dictionary<size_t, jakt__platform__unknown_process::ExitPollResult>::create_with_entries({})))),static_cast<size_t>(0ULL),max_concurrent);
}
}

JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult> build::ParallelExecutionPool::status(size_t const id) const {
{
if (((((*this).completed)).contains(id))){
return ((((*this).completed))[id]);
}
return JaktInternal::OptionalNone();
}
}

build::ParallelExecutionPool::ParallelExecutionPool(JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::Process> a_pids, JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::ExitPollResult> a_completed, size_t a_pid_index, size_t a_max_concurrent): pids(move(a_pids)), completed(move(a_completed)), pid_index(move(a_pid_index)), max_concurrent(move(a_max_concurrent)){}

ErrorOr<void> build::ParallelExecutionPool::wait_for_any_job_to_complete() {
{
JaktInternal::Tuple<JaktInternal::Optional<size_t>,jakt__platform__unknown_process::ExitPollResult> const finished_pid_finished_status_ = TRY((jakt__platform__unknown_process::wait_for_some_set_of_processes_that_at_least_includes(((((*this).pids))))));
JaktInternal::Optional<size_t> const finished_pid = ((finished_pid_finished_status_).template get<0>());
jakt__platform__unknown_process::ExitPollResult const finished_status = ((finished_pid_finished_status_).template get<1>());

JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::ExitPollResult> pids_to_remove = (TRY((Dictionary<size_t, jakt__platform__unknown_process::ExitPollResult>::create_with_entries({}))));
if (((finished_pid).has_value())){
TRY((((pids_to_remove).set((finished_pid.value()),finished_status))));
}
{
JaktInternal::DictionaryIterator<size_t,jakt__platform__unknown_process::Process> _magic = ((((*this).pids)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,jakt__platform__unknown_process::Process>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::Process> index__process__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::Process> const jakt__index__process__ = index__process__;
size_t const index = ((jakt__index__process__).template get<0>());
jakt__platform__unknown_process::Process const process = ((jakt__index__process__).template get<1>());

JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult> const status = ({ Optional<JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult>> __jakt_var_0;
auto __jakt_var_1 = [&]() -> ErrorOr<JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult>> { return TRY((jakt__platform__unknown_process::poll_process_exit(((process))))); }();
if (__jakt_var_1.is_error()) {{
TRY((((pids_to_remove).set(index,finished_status))));
continue;
}
} else {__jakt_var_0 = __jakt_var_1.release_value();
}
__jakt_var_0.release_value(); });
if (((status).has_value())){
TRY((((pids_to_remove).set(index,(status.value())))));
}
}

}
}

{
JaktInternal::DictionaryIterator<size_t,jakt__platform__unknown_process::ExitPollResult> _magic = ((pids_to_remove).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult> index__status__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::ExitPollResult> const jakt__index__status__ = index__status__;
size_t const index = ((jakt__index__status__).template get<0>());
jakt__platform__unknown_process::ExitPollResult const status = ((jakt__index__status__).template get<1>());

((((*this).pids)).remove(index));
TRY((((((*this).completed)).set(index,status))));
}

}
}

}
return {};
}

ErrorOr<size_t> build::ParallelExecutionPool::run(JaktInternal::DynamicArray<ByteString> const args) {
{
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((((*this).pids)).size()),((*this).max_concurrent))){
TRY((((*this).wait_for_any_job_to_complete())));
}
jakt__platform__unknown_process::Process const process = TRY((jakt__platform__unknown_process::start_background_process(args)));
size_t const id = ((((*this).pid_index)++));
TRY((((((*this).pids)).set(id,process))));
return id;
}
}

ErrorOr<void> build::ParallelExecutionPool::kill_all() {
{
{
JaktInternal::DictionaryIterator<size_t,jakt__platform__unknown_process::Process> _magic = ((((*this).pids)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,jakt__platform__unknown_process::Process>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::Process> ___process__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,jakt__platform__unknown_process::Process> const jakt_____process__ = ___process__;
size_t const _ = ((jakt_____process__).template get<0>());
jakt__platform__unknown_process::Process const process = ((jakt_____process__).template get<1>());

TRY((jakt__platform__unknown_process::forcefully_kill_process(((process)))));
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
