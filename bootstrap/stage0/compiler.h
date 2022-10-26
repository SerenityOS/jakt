#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "utility.h"
#include "utility.h"
#include "path.h"
namespace Jakt {
namespace compiler {
class Compiler : public RefCounted<Compiler>, public Weakable<Compiler> {
  public:
virtual ~Compiler() = default;
JaktInternal::Array<path::Path> files;JaktInternal::Dictionary<String,utility::FileId> file_ids;JaktInternal::Array<error::JaktError> errors;JaktInternal::Optional<utility::FileId> current_file;JaktInternal::Array<u8> current_file_contents;bool dump_lexer;bool dump_parser;bool ignore_parser_errors;bool debug_print;path::Path std_include_path;JaktInternal::Array<String> include_paths;bool json_errors;bool dump_type_hints;bool dump_try_hints;bool optimize;JaktInternal::Optional<String> target_triple;ErrorOr<void> load_prelude();
ErrorOr<JaktInternal::Optional<path::Path>> get_file_path(const utility::FileId file_id) const;
bool set_current_file(const utility::FileId file_id);
ErrorOr<JaktInternal::Optional<path::Path>> search_for_path(const String input_module_name) const;
ErrorOr<utility::FileId> get_file_id_or_register(const path::Path file);
JaktInternal::Optional<utility::FileId> current_file_id() const;
protected:
explicit Compiler(JaktInternal::Array<path::Path>&& a_files, JaktInternal::Dictionary<String,utility::FileId>&& a_file_ids, JaktInternal::Array<error::JaktError>&& a_errors, JaktInternal::Optional<utility::FileId>&& a_current_file, JaktInternal::Array<u8>&& a_current_file_contents, bool&& a_dump_lexer, bool&& a_dump_parser, bool&& a_ignore_parser_errors, bool&& a_debug_print, path::Path&& a_std_include_path, JaktInternal::Array<String>&& a_include_paths, bool&& a_json_errors, bool&& a_dump_type_hints, bool&& a_dump_try_hints, bool&& a_optimize, JaktInternal::Optional<String>&& a_target_triple);
public:
static ErrorOr<NonnullRefPtr<Compiler>> create(JaktInternal::Array<path::Path> files, JaktInternal::Dictionary<String,utility::FileId> file_ids, JaktInternal::Array<error::JaktError> errors, JaktInternal::Optional<utility::FileId> current_file, JaktInternal::Array<u8> current_file_contents, bool dump_lexer, bool dump_parser, bool ignore_parser_errors, bool debug_print, path::Path std_include_path, JaktInternal::Array<String> include_paths, bool json_errors, bool dump_type_hints, bool dump_try_hints, bool optimize, JaktInternal::Optional<String> target_triple);

JaktInternal::Optional<path::Path> current_file_path() const;
[[noreturn]] ErrorOr<void> panic(const String message) const;
ErrorOr<void> print_errors() const;
void dbg_println(const String message) const;
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<compiler::Compiler> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, compiler::Compiler const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
