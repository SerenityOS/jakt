#pragma once
#include "__unified_forward.h"
#include <stdio.h>
#include "typechecker.h"
#include "compiler.h"
#include "lexer.h"
#include "parser.h"
#include "utility.h"
#include "error.h"
#include "interpreter.h"
namespace Jakt {
namespace repl {
namespace LineResult_Details {
struct Line{
String value;
template<typename... Args>
Line(Args&&... args): value { forward<Args>(args)... } {}
};
struct Eof {};
}
struct LineResult : public Variant<LineResult_Details::Line, LineResult_Details::Eof> {
using Variant<LineResult_Details::Line, LineResult_Details::Eof>::Variant;
    using Line = LineResult_Details::Line;
    using Eof = LineResult_Details::Eof;
ErrorOr<String> debug_description() const;
};
struct REPL {
  public:
NonnullRefPtr<compiler::Compiler> compiler;typechecker::Typechecker typechecker;types::ScopeId root_scope_id;NonnullRefPtr<interpreter::InterpreterScope> root_interpreter_scope;utility::FileId file_id;static ErrorOr<repl::REPL> create(const JaktInternal::Optional<String> target_triple);
ErrorOr<void> run();
REPL(NonnullRefPtr<compiler::Compiler> a_compiler, typechecker::Typechecker a_typechecker, types::ScopeId a_root_scope_id, NonnullRefPtr<interpreter::InterpreterScope> a_root_interpreter_scope, utility::FileId a_file_id);

ErrorOr<bool> handle_possible_error();
ErrorOr<String> debug_description() const;
};struct Editor {
  public:
FILE* standard_input_file;char* line_pointer;String prompt;static ErrorOr<repl::Editor> create(const String prompt);
void destroy();
Editor(FILE* a_standard_input_file, char* a_line_pointer, String a_prompt);

ErrorOr<repl::LineResult> get_line();
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<repl::LineResult> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, repl::LineResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<repl::REPL> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, repl::REPL const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<repl::Editor> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, repl::Editor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
