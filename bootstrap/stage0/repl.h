#pragma once
#include "__unified_forward.h"
#include "typechecker.h"
#include "compiler.h"
#include "lexer.h"
#include "parser.h"
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
NonnullRefPtr<compiler::Compiler> compiler;typechecker::Typechecker typechecker;types::ScopeId root_scope_id;NonnullRefPtr<interpreter::InterpreterScope> root_interpreter_scope;utility::FileId file_id;static ErrorOr<repl::REPL> create(jakt__path::Path const runtime_path, JaktInternal::Optional<DeprecatedString> const target_triple, JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const user_configuration);
ErrorOr<void> run();
REPL(NonnullRefPtr<compiler::Compiler> a_compiler, typechecker::Typechecker a_typechecker, types::ScopeId a_root_scope_id, NonnullRefPtr<interpreter::InterpreterScope> a_root_interpreter_scope, utility::FileId a_file_id);

ErrorOr<bool> handle_possible_error();
ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl::REPL> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl::REPL const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
