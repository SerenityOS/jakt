#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "utility.h"
#include "utility.h"
#include "jakt__path.h"
namespace Jakt {
namespace compiler {
class Compiler : public RefCounted<Compiler>, public Weakable<Compiler> {
  public:
virtual ~Compiler() = default;
JaktInternal::DynamicArray<jakt__path::Path> files;JaktInternal::Dictionary<DeprecatedString,utility::FileId> file_ids;JaktInternal::DynamicArray<error::JaktError> errors;JaktInternal::Optional<utility::FileId> current_file;JaktInternal::DynamicArray<u8> current_file_contents;bool dump_lexer;bool dump_parser;bool ignore_parser_errors;bool debug_print;jakt__path::Path std_include_path;JaktInternal::DynamicArray<DeprecatedString> include_paths;bool json_errors;bool dump_type_hints;bool dump_try_hints;bool optimize;JaktInternal::Optional<DeprecatedString> target_triple;JaktInternal::Dictionary<DeprecatedString,DeprecatedString> user_configuration;jakt__path::Path binary_dir;ErrorOr<void> load_prelude();
ErrorOr<JaktInternal::Optional<jakt__path::Path>> search_for_path(DeprecatedString const input_module_name) const;
void restore_file_state(JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> const state);
JaktInternal::Optional<jakt__path::Path> current_file_path() const;
JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> current_file_state() const;
ErrorOr<void> print_errors() const;
ErrorOr<void> dbg_println(DeprecatedString const message) const;
protected:
explicit Compiler(JaktInternal::DynamicArray<jakt__path::Path> a_files, JaktInternal::Dictionary<DeprecatedString,utility::FileId> a_file_ids, JaktInternal::DynamicArray<error::JaktError> a_errors, JaktInternal::Optional<utility::FileId> a_current_file, JaktInternal::DynamicArray<u8> a_current_file_contents, bool a_dump_lexer, bool a_dump_parser, bool a_ignore_parser_errors, bool a_debug_print, jakt__path::Path a_std_include_path, JaktInternal::DynamicArray<DeprecatedString> a_include_paths, bool a_json_errors, bool a_dump_type_hints, bool a_dump_try_hints, bool a_optimize, JaktInternal::Optional<DeprecatedString> a_target_triple, JaktInternal::Dictionary<DeprecatedString,DeprecatedString> a_user_configuration, jakt__path::Path a_binary_dir);
public:
static ErrorOr<NonnullRefPtr<Compiler>> __jakt_create(JaktInternal::DynamicArray<jakt__path::Path> files, JaktInternal::Dictionary<DeprecatedString,utility::FileId> file_ids, JaktInternal::DynamicArray<error::JaktError> errors, JaktInternal::Optional<utility::FileId> current_file, JaktInternal::DynamicArray<u8> current_file_contents, bool dump_lexer, bool dump_parser, bool ignore_parser_errors, bool debug_print, jakt__path::Path std_include_path, JaktInternal::DynamicArray<DeprecatedString> include_paths, bool json_errors, bool dump_type_hints, bool dump_try_hints, bool optimize, JaktInternal::Optional<DeprecatedString> target_triple, JaktInternal::Dictionary<DeprecatedString,DeprecatedString> user_configuration, jakt__path::Path binary_dir);

JaktInternal::Optional<utility::FileId> current_file_id() const;
ErrorOr<JaktInternal::Optional<jakt__path::Path>> find_in_search_paths(jakt__path::Path const path) const;
ErrorOr<JaktInternal::Optional<jakt__path::Path>> get_file_path(utility::FileId const file_id) const;
ErrorOr<utility::FileId> get_file_id_or_register(jakt__path::Path const file);
ErrorOr<bool> set_current_file(utility::FileId const file_id);
[[noreturn]] ErrorOr<void> panic(DeprecatedString const message) const;
ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::compiler::Compiler> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::compiler::Compiler const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
