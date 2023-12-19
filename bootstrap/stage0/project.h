#pragma once
#include "__unified_forward.h"
#include "jakt__platform.h"
#include "jakt__platform__unknown_fs.h"
#include "utility.h"
namespace Jakt {
namespace project {
struct Project {
  public:
public: ByteString name;public: ErrorOr<void> populate() const;
public: ErrorOr<void> create_template_cmake_lists(ByteString const project_directory) const;
public: ErrorOr<void> create_sample_jakt_files(ByteString const project_directory) const;
public: ErrorOr<void> create_readme(ByteString const project_directory) const;
public: Project(ByteString a_name);

public: ErrorOr<ByteString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::project::Project> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::project::Project const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
