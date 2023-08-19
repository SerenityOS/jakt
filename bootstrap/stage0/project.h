#pragma once
#include "__unified_forward.h"
#include "jakt__platform.h"
#include "jakt__platform__unknown_fs.h"
#include "utility.h"
namespace Jakt {
namespace project {
struct Project {
  public:
public: DeprecatedString name;public: ErrorOr<void> create_template_cmake_lists(DeprecatedString const project_directory) const;
public: ErrorOr<void> populate() const;
public: ErrorOr<void> create_readme(DeprecatedString const project_directory) const;
public: ErrorOr<void> create_sample_jakt_files(DeprecatedString const project_directory) const;
public: Project(DeprecatedString a_name);

public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::project::Project> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::project::Project const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
