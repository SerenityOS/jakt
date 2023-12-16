#pragma once
#include "__unified_forward.h"
#include "typechecker.h"
#include "parser.h"
#include "compiler.h"
#include "lexer.h"
#include "utility.h"
#include "error.h"
#include "interpreter.h"
#include "jakt__path.h"
#include "platform.h"
#include "repl_backend__default.h"
namespace Jakt {
namespace repl {
struct REPL {
  public:
public: NonnullRefPtr<compiler::Compiler> compiler;public: typechecker::Typechecker typechecker;public: ids::ScopeId root_scope_id;public: NonnullRefPtr<interpreter::InterpreterScope> root_interpreter_scope;public: utility::FileId file_id;public: static ErrorOr<repl::REPL> create(jakt__path::Path const runtime_path, JaktInternal::Optional<ByteString> const target_triple, JaktInternal::Dictionary<ByteString,ByteString> const user_configuration);
public: static ErrorOr<JaktInternal::DynamicArray<u8>> line_to_bytes(ByteString const line);
public: ErrorOr<void> run();
public: REPL(NonnullRefPtr<compiler::Compiler> a_compiler, typechecker::Typechecker a_typechecker, ids::ScopeId a_root_scope_id, NonnullRefPtr<interpreter::InterpreterScope> a_root_interpreter_scope, utility::FileId a_file_id);

public: ErrorOr<bool> handle_possible_error();
public: static bool check_parens(JaktInternal::DynamicArray<lexer::Token> const tokens);
public: ErrorOr<ByteString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl::REPL> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl::REPL const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
