#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "utility.h"
#include "utility.h"
#include "jakt__path.h"
namespace Jakt {
namespace compiler {
class Compiler :public RefCounted<Compiler>, public Weakable<Compiler> {
  public:
virtual ~Compiler() = default;
public: JaktInternal::DynamicArray<jakt__path::Path> files;public: JaktInternal::Dictionary<DeprecatedString,utility::FileId> file_ids;public: JaktInternal::DynamicArray<error::JaktError> errors;public: JaktInternal::Optional<utility::FileId> current_file;public: JaktInternal::DynamicArray<u8> current_file_contents;public: bool dump_lexer;public: bool dump_parser;public: bool ignore_parser_errors;public: bool debug_print;public: jakt__path::Path std_include_path;public: JaktInternal::DynamicArray<DeprecatedString> include_paths;public: bool json_errors;public: bool dump_type_hints;public: bool dump_try_hints;public: bool optimize;public: JaktInternal::Optional<DeprecatedString> target_triple;public: JaktInternal::Dictionary<DeprecatedString,DeprecatedString> user_configuration;public: jakt__path::Path binary_dir;public: ErrorOr<void> load_prelude();
public: ErrorOr<JaktInternal::Optional<jakt__path::Path>> search_for_path(DeprecatedString const input_module_name) const;
public: void restore_file_state(JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> const state);
public: JaktInternal::Optional<jakt__path::Path> current_file_path() const;
public: JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> current_file_state() const;
public: ErrorOr<void> print_errors() const;
public: ErrorOr<void> dbg_println(DeprecatedString const message) const;
public: protected:
explicit Compiler(JaktInternal::DynamicArray<jakt__path::Path> a_files, JaktInternal::Dictionary<DeprecatedString,utility::FileId> a_file_ids, JaktInternal::DynamicArray<error::JaktError> a_errors, JaktInternal::Optional<utility::FileId> a_current_file, JaktInternal::DynamicArray<u8> a_current_file_contents, bool a_dump_lexer, bool a_dump_parser, bool a_ignore_parser_errors, bool a_debug_print, jakt__path::Path a_std_include_path, JaktInternal::DynamicArray<DeprecatedString> a_include_paths, bool a_json_errors, bool a_dump_type_hints, bool a_dump_try_hints, bool a_optimize, JaktInternal::Optional<DeprecatedString> a_target_triple, JaktInternal::Dictionary<DeprecatedString,DeprecatedString> a_user_configuration, jakt__path::Path a_binary_dir);
public:
static ErrorOr<NonnullRefPtr<Compiler>> __jakt_create(JaktInternal::DynamicArray<jakt__path::Path> files, JaktInternal::Dictionary<DeprecatedString,utility::FileId> file_ids, JaktInternal::DynamicArray<error::JaktError> errors, JaktInternal::Optional<utility::FileId> current_file, JaktInternal::DynamicArray<u8> current_file_contents, bool dump_lexer, bool dump_parser, bool ignore_parser_errors, bool debug_print, jakt__path::Path std_include_path, JaktInternal::DynamicArray<DeprecatedString> include_paths, bool json_errors, bool dump_type_hints, bool dump_try_hints, bool optimize, JaktInternal::Optional<DeprecatedString> target_triple, JaktInternal::Dictionary<DeprecatedString,DeprecatedString> user_configuration, jakt__path::Path binary_dir);

public: JaktInternal::Optional<utility::FileId> current_file_id() const;
public: ErrorOr<JaktInternal::Optional<jakt__path::Path>> find_in_search_paths(jakt__path::Path const path) const;
public: ErrorOr<JaktInternal::Optional<jakt__path::Path>> get_file_path(utility::FileId const file_id) const;
public: ErrorOr<utility::FileId> get_file_id_or_register(jakt__path::Path const file);
public: ErrorOr<bool> set_current_file(utility::FileId const file_id);
public: [[noreturn]] ErrorOr<void> panic(DeprecatedString const message) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::compiler::Compiler> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::compiler::Compiler const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
