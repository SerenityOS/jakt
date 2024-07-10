#pragma once
#include <lib.h>
#include "repl_backend__default.h"
#include "platform.h"
#include "typechecker.h"
#include "interpreter.h"
#include "types.h"
#include "ids.h"
#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__path.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace repl {
struct REPL;
ErrorOr<ByteString> serialize_unary_operation(Jakt::types::CheckedUnaryOperator const op, ByteString const expr);

ErrorOr<ByteString> serialize_ast_node(NonnullRefPtr<typename Jakt::types::CheckedExpression> const node);

}
namespace repl {
struct REPL {
  public:
public: NonnullRefPtr<Jakt::compiler::Compiler> compiler;public: Jakt::typechecker::Typechecker typechecker;public: Jakt::ids::ScopeId root_scope_id;public: NonnullRefPtr<Jakt::interpreter::InterpreterScope> root_interpreter_scope;public: Jakt::utility::FileId file_id;public: static ErrorOr<Jakt::repl::REPL> create(Jakt::jakt__path::Path const runtime_path, JaktInternal::Optional<ByteString> const target_triple, JaktInternal::Dictionary<ByteString,ByteString> const user_configuration);
public: ErrorOr<bool> handle_possible_error();
public: static JaktInternal::DynamicArray<u8> line_to_bytes(ByteString const line);
public: static bool check_parens(JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens);
public: ErrorOr<void> run();
public: REPL(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, Jakt::typechecker::Typechecker a_typechecker, Jakt::ids::ScopeId a_root_scope_id, NonnullRefPtr<Jakt::interpreter::InterpreterScope> a_root_interpreter_scope, Jakt::utility::FileId a_file_id);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl::REPL> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl::REPL const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
