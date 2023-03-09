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
#include "jakt__libc__io.h"
namespace Jakt {
namespace repl {
struct REPL {
  public:
NonnullRefPtr<compiler::Compiler> compiler;typechecker::Typechecker typechecker;types::ScopeId root_scope_id;NonnullRefPtr<interpreter::InterpreterScope> root_interpreter_scope;utility::FileId file_id;static ErrorOr<repl::REPL> create(jakt__path::Path const runtime_path, JaktInternal::Optional<DeprecatedString> const target_triple);
ErrorOr<void> run();
REPL(NonnullRefPtr<compiler::Compiler> a_compiler, typechecker::Typechecker a_typechecker, types::ScopeId a_root_scope_id, NonnullRefPtr<interpreter::InterpreterScope> a_root_interpreter_scope, utility::FileId a_file_id);

ErrorOr<bool> handle_possible_error();
ErrorOr<DeprecatedString> debug_description() const;
};struct Editor {
  public:
FILE* standard_input_file;char* line_pointer;DeprecatedString prompt;static ErrorOr<repl::Editor> create(DeprecatedString const prompt);
Editor(FILE* a_standard_input_file, char* a_line_pointer, DeprecatedString a_prompt);

ErrorOr<repl::LineResult> get_line();
void destroy();
ErrorOr<DeprecatedString> debug_description() const;
};namespace LineResult_Details {
struct Line{
DeprecatedString value;
template<typename _MemberT0>
Line(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Eof {
};
}
struct LineResult : public Variant<LineResult_Details::Line, LineResult_Details::Eof> {
using Variant<LineResult_Details::Line, LineResult_Details::Eof>::Variant;
    using Line = LineResult_Details::Line;
    using Eof = LineResult_Details::Eof;
ErrorOr<DeprecatedString> debug_description() const;
};
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl::REPL> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl::REPL const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl::Editor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl::Editor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::repl::LineResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::repl::LineResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
