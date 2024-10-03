#pragma once
#include <lib.h>
#include "error.h"
#include "utility.h"
#include "jakt__file_iterator.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace compiler {
class Compiler;

}
namespace compiler {
class Compiler :public RefCounted<Compiler>, public Weakable<Compiler> {
  public:
virtual ~Compiler() = default;
public: JaktInternal::DynamicArray<Jakt::jakt__path::Path> files;public: JaktInternal::Dictionary<ByteString,Jakt::utility::FileId> file_ids;public: JaktInternal::DynamicArray<Jakt::error::JaktError> errors;public: JaktInternal::Optional<Jakt::utility::FileId> current_file;public: JaktInternal::DynamicArray<u8> current_file_contents;public: bool dump_lexer;public: bool dump_parser;public: bool ignore_parser_errors;public: bool debug_print;public: bool debug_print_cpp_import;public: Jakt::jakt__path::Path std_include_path;public: Jakt::jakt__path::Path prelude_path;public: JaktInternal::DynamicArray<ByteString> include_paths;public: bool json_errors;public: bool dump_type_hints;public: bool dump_try_hints;public: bool optimize;public: JaktInternal::Optional<ByteString> target_triple;public: JaktInternal::Dictionary<ByteString,ByteString> user_configuration;public: Jakt::jakt__path::Path binary_dir;public: Jakt::jakt__path::Path exports_dir;public: JaktInternal::Optional<Jakt::jakt__path::Path> assume_main_file_path;public: JaktInternal::Set<ByteString> files_used_in_build;public: [[noreturn]] void panic(ByteString const message) const;
public: ErrorOr<void> print_errors() const;
public: JaktInternal::Optional<Jakt::jakt__path::Path> get_file_path(Jakt::utility::FileId const file_id) const;
public: JaktInternal::Optional<Jakt::utility::FileId> current_file_id() const;
public: JaktInternal::Optional<Jakt::jakt__path::Path> current_file_path() const;
public: Jakt::utility::FileId get_file_id_or_register(Jakt::jakt__path::Path const file);
public: ErrorOr<bool> set_current_file(Jakt::utility::FileId const file_id);
public: JaktInternal::Tuple<JaktInternal::Optional<Jakt::utility::FileId>,JaktInternal::DynamicArray<u8>> current_file_state() const;
public: void restore_file_state(JaktInternal::Tuple<JaktInternal::Optional<Jakt::utility::FileId>,JaktInternal::DynamicArray<u8>> const state);
public: void dbg_println(ByteString const message) const;
public: ErrorOr<void> load_prelude();
public: ErrorOr<JaktInternal::Optional<Jakt::jakt__path::Path>> search_for_path(ByteString const input_module_name, bool const relative_import, size_t const parent_path_count) const;
public: ErrorOr<JaktInternal::Optional<Jakt::jakt__path::Path>> find_in_search_paths(Jakt::jakt__path::Path const path, bool const relative_import, size_t const parent_path_count) const;
public: protected:
explicit Compiler(JaktInternal::DynamicArray<Jakt::jakt__path::Path> a_files, JaktInternal::Dictionary<ByteString,Jakt::utility::FileId> a_file_ids, JaktInternal::DynamicArray<Jakt::error::JaktError> a_errors, JaktInternal::Optional<Jakt::utility::FileId> a_current_file, JaktInternal::DynamicArray<u8> a_current_file_contents, bool a_dump_lexer, bool a_dump_parser, bool a_ignore_parser_errors, bool a_debug_print, bool a_debug_print_cpp_import, Jakt::jakt__path::Path a_std_include_path, Jakt::jakt__path::Path a_prelude_path, JaktInternal::DynamicArray<ByteString> a_include_paths, bool a_json_errors, bool a_dump_type_hints, bool a_dump_try_hints, bool a_optimize, JaktInternal::Optional<ByteString> a_target_triple, JaktInternal::Dictionary<ByteString,ByteString> a_user_configuration, Jakt::jakt__path::Path a_binary_dir, Jakt::jakt__path::Path a_exports_dir, JaktInternal::Optional<Jakt::jakt__path::Path> a_assume_main_file_path, JaktInternal::Set<ByteString> a_files_used_in_build);
public:
static NonnullRefPtr<Compiler> __jakt_create(JaktInternal::DynamicArray<Jakt::jakt__path::Path> files, JaktInternal::Dictionary<ByteString,Jakt::utility::FileId> file_ids, JaktInternal::DynamicArray<Jakt::error::JaktError> errors, JaktInternal::Optional<Jakt::utility::FileId> current_file, JaktInternal::DynamicArray<u8> current_file_contents, bool dump_lexer, bool dump_parser, bool ignore_parser_errors, bool debug_print, bool debug_print_cpp_import, Jakt::jakt__path::Path std_include_path, Jakt::jakt__path::Path prelude_path, JaktInternal::DynamicArray<ByteString> include_paths, bool json_errors, bool dump_type_hints, bool dump_try_hints, bool optimize, JaktInternal::Optional<ByteString> target_triple, JaktInternal::Dictionary<ByteString,ByteString> user_configuration, Jakt::jakt__path::Path binary_dir, Jakt::jakt__path::Path exports_dir, JaktInternal::Optional<Jakt::jakt__path::Path> assume_main_file_path, JaktInternal::Set<ByteString> files_used_in_build);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::compiler::Compiler> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::compiler::Compiler const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
