#pragma once
#include "__unified_forward.h"
#include "jakt__platform__unknown_process.h"
#include "jakt__path.h"
#include "jakt__platform.h"
namespace Jakt {
namespace build {
struct ParallelExecutionPool {
  public:
public: JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::Process> pids;public: JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::ExitPollResult> completed;public: size_t pid_index;public: size_t max_concurrent;public: static build::ParallelExecutionPool create(size_t const max_concurrent);
public: ErrorOr<size_t> run(JaktInternal::DynamicArray<ByteString> const args);
public: JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult> status(size_t const id) const;
public: ErrorOr<void> wait_for_any_job_to_complete();
public: ErrorOr<void> wait_for_all_jobs_to_complete();
public: ErrorOr<void> kill_all();
public: ParallelExecutionPool(JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::Process> a_pids, JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::ExitPollResult> a_completed, size_t a_pid_index, size_t a_max_concurrent);

public: ByteString debug_description() const;
};struct Builder {
  public:
public: JaktInternal::DynamicArray<ByteString> linked_files;public: JaktInternal::DynamicArray<ByteString> files_to_compile;public: build::ParallelExecutionPool pool;public: static ErrorOr<build::Builder> for_building(JaktInternal::DynamicArray<ByteString> const files, size_t const max_concurrent);
public: ErrorOr<void> build_all(jakt__path::Path const binary_dir, Function<ErrorOr<JaktInternal::DynamicArray<ByteString>>(ByteString, ByteString)> const& compiler_invocation);
public: ErrorOr<void> link_into_archive(ByteString const archiver, ByteString const archive_filename, JaktInternal::DynamicArray<ByteString> const extra_arguments);
public: ErrorOr<void> link_into_executable(ByteString const cxx_compiler_path, ByteString const output_filename, JaktInternal::DynamicArray<ByteString> const extra_arguments);
public: Builder(JaktInternal::DynamicArray<ByteString> a_linked_files, JaktInternal::DynamicArray<ByteString> a_files_to_compile, build::ParallelExecutionPool a_pool);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::build::ParallelExecutionPool> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::build::ParallelExecutionPool const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::build::Builder> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::build::Builder const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
