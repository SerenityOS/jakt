#pragma once
#include "__unified_forward.h"
#include "os.h"
#include "unknown_fs.h"
#include "utility.h"
namespace Jakt {
namespace project {
struct Project {
  public:
String name;ErrorOr<void> populate() const;
ErrorOr<void> create_readme(String const project_directory) const;
Project(String a_name);

ErrorOr<void> create_template_cmake_lists(String const project_directory) const;
ErrorOr<void> create_sample_jakt_files(String const project_directory) const;
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<project::Project> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, project::Project const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
