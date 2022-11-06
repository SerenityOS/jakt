#pragma once
#include "__unified_forward.h"
#include "types.h"
#include "utility.h"
#include "error.h"
#include "compiler.h"
namespace Jakt {
namespace interpreter {
namespace ExecutionResult_Details {
struct Return{
types::Value value;
template<typename _MemberT0>
Return(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Throw{
types::Value value;
template<typename _MemberT0>
Throw(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct ExecutionResult : public Variant<ExecutionResult_Details::Return, ExecutionResult_Details::Throw> {
using Variant<ExecutionResult_Details::Return, ExecutionResult_Details::Throw>::Variant;
    using Return = ExecutionResult_Details::Return;
    using Throw = ExecutionResult_Details::Throw;
ErrorOr<String> debug_description() const;
};
enum class InterpretError: i32 {
CallToExternalFunction = (infallible_integer_cast<i32>((static_cast<i32>(42)))),
MismatchingArguments = (infallible_integer_cast<i32>((static_cast<u64>(43ULL)))),
InvalidThisArgument = (infallible_integer_cast<i32>((static_cast<u64>(44ULL)))),
InvalidType = (infallible_integer_cast<i32>((static_cast<u64>(45ULL)))),
UnknownVariable = (infallible_integer_cast<i32>((static_cast<u64>(46ULL)))),
Unimplemented = (infallible_integer_cast<i32>((static_cast<u64>(47ULL)))),
UnwrapOptionalNone = (infallible_integer_cast<i32>((static_cast<u64>(48ULL)))),
};
namespace Deferred_Details {
struct Expression{
NonnullRefPtr<types::CheckedExpression> value;
template<typename _MemberT0>
Expression(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Statement{
NonnullRefPtr<types::CheckedStatement> value;
template<typename _MemberT0>
Statement(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct Deferred : public Variant<Deferred_Details::Expression, Deferred_Details::Statement> {
using Variant<Deferred_Details::Expression, Deferred_Details::Statement>::Variant;
    using Expression = Deferred_Details::Expression;
    using Statement = Deferred_Details::Statement;
ErrorOr<String> debug_description() const;
};
namespace StatementResult_Details {
struct Return{
types::Value value;
template<typename _MemberT0>
Return(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Throw{
types::Value value;
template<typename _MemberT0>
Throw(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Yield{
types::Value value;
template<typename _MemberT0>
Yield(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Continue {
};
struct Break {
};
struct JustValue{
types::Value value;
template<typename _MemberT0>
JustValue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct StatementResult : public Variant<StatementResult_Details::Return, StatementResult_Details::Throw, StatementResult_Details::Yield, StatementResult_Details::Continue, StatementResult_Details::Break, StatementResult_Details::JustValue> {
using Variant<StatementResult_Details::Return, StatementResult_Details::Throw, StatementResult_Details::Yield, StatementResult_Details::Continue, StatementResult_Details::Break, StatementResult_Details::JustValue>::Variant;
    using Return = StatementResult_Details::Return;
    using Throw = StatementResult_Details::Throw;
    using Yield = StatementResult_Details::Yield;
    using Continue = StatementResult_Details::Continue;
    using Break = StatementResult_Details::Break;
    using JustValue = StatementResult_Details::JustValue;
ErrorOr<String> debug_description() const;
};
class InterpreterScope : public RefCounted<InterpreterScope>, public Weakable<InterpreterScope> {
  public:
virtual ~InterpreterScope() = default;
JaktInternal::Dictionary<String,types::Value> bindings;JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent;JaktInternal::Dictionary<String,types::TypeId> type_bindings;JaktInternal::Array<interpreter::Deferred> defers;ErrorOr<void> defer_statement(NonnullRefPtr<types::CheckedStatement> const statement);
ErrorOr<void> perform_defers(NonnullRefPtr<interpreter::Interpreter> interpreter, utility::Span const span);
static ErrorOr<NonnullRefPtr<interpreter::InterpreterScope>> from_runtime_scope(types::ScopeId const scope_id, NonnullRefPtr<types::CheckedProgram> const program, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const parent);
ErrorOr<types::GenericInferences> type_map_for_substitution() const;
protected:
explicit InterpreterScope(JaktInternal::Dictionary<String,types::Value>&& a_bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>>&& a_parent, JaktInternal::Dictionary<String,types::TypeId>&& a_type_bindings, JaktInternal::Array<interpreter::Deferred>&& a_defers);
public:
static ErrorOr<NonnullRefPtr<InterpreterScope>> create(JaktInternal::Dictionary<String,types::Value> bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent, JaktInternal::Dictionary<String,types::TypeId> type_bindings, JaktInternal::Array<interpreter::Deferred> defers);

ErrorOr<types::TypeId> map_type(types::TypeId const id) const;
ErrorOr<void> set(String const name, types::Value const value);
static ErrorOr<NonnullRefPtr<interpreter::InterpreterScope>> create(JaktInternal::Dictionary<String,types::Value> const bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const parent, JaktInternal::Dictionary<String,types::TypeId> const type_bindings);
ErrorOr<void> type_map_for_substitution_helper(JaktInternal::Dictionary<String,String>& map) const;
ErrorOr<types::Value> must_get(String const name) const;
ErrorOr<void> defer_expression(NonnullRefPtr<types::CheckedExpression> const expr);
ErrorOr<String> debug_description() const;
};class Interpreter : public RefCounted<Interpreter>, public Weakable<Interpreter> {
  public:
virtual ~Interpreter() = default;
NonnullRefPtr<compiler::Compiler> compiler;NonnullRefPtr<types::CheckedProgram> program;JaktInternal::Array<utility::Span> spans;JaktInternal::Optional<types::FunctionId> current_function_id;ErrorOr<bool> get_prelude_function(types::ScopeId const scope_id) const;
ErrorOr<interpreter::StatementResult> call_prelude_function(String const prelude_function, JaktInternal::Array<types::ResolvedNamespace> const namespace_, JaktInternal::Optional<types::Value> const this_argument, JaktInternal::Array<types::Value> const arguments, utility::Span const call_span, JaktInternal::Dictionary<String,types::TypeId> const type_bindings);
ErrorOr<void> update_binding(NonnullRefPtr<types::CheckedExpression> const binding, NonnullRefPtr<interpreter::InterpreterScope> scope, types::Value const value, utility::Span const span);
ErrorOr<interpreter::StatementResult> execute_binary_operator(types::Value const lhs_value, types::Value const rhs_value, parser::BinaryOperator const op, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
protected:
explicit Interpreter(NonnullRefPtr<compiler::Compiler>&& a_compiler, NonnullRefPtr<types::CheckedProgram>&& a_program, JaktInternal::Array<utility::Span>&& a_spans, JaktInternal::Optional<types::FunctionId>&& a_current_function_id);
public:
static ErrorOr<NonnullRefPtr<Interpreter>> create(NonnullRefPtr<compiler::Compiler> compiler, NonnullRefPtr<types::CheckedProgram> program, JaktInternal::Array<utility::Span> spans, JaktInternal::Optional<types::FunctionId> current_function_id);

void leave_span();
ErrorOr<void> error(String const message, utility::Span const span);
ErrorOr<interpreter::StatementResult> execute_expression(NonnullRefPtr<types::CheckedExpression> const expr, NonnullRefPtr<interpreter::InterpreterScope> scope);
static ErrorOr<NonnullRefPtr<interpreter::Interpreter>> create(NonnullRefPtr<compiler::Compiler> const compiler, NonnullRefPtr<types::CheckedProgram> const program, JaktInternal::Array<utility::Span> const spans);
ErrorOr<interpreter::StatementResult> execute_expression_without_cast(NonnullRefPtr<types::CheckedExpression> const expr, NonnullRefPtr<interpreter::InterpreterScope> scope);
ErrorOr<interpreter::StatementResult> execute_statement(NonnullRefPtr<types::CheckedStatement> const statement, NonnullRefPtr<interpreter::InterpreterScope> scope, utility::Span const call_span);
ErrorOr<void> error_with_hint(String const message, utility::Span const span, String const hint_message, utility::Span const hint_span);
ErrorOr<interpreter::ExecutionResult> execute(types::FunctionId const function_to_run_id, JaktInternal::Optional<JaktInternal::Array<types::ResolvedNamespace>> namespace_, JaktInternal::Optional<types::Value> const this_argument, JaktInternal::Array<types::Value> const arguments, utility::Span const call_span, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const invocation_scope);
ErrorOr<void> enter_span(utility::Span const span);
ErrorOr<interpreter::StatementResult> execute_block(types::CheckedBlock const block, NonnullRefPtr<interpreter::InterpreterScope> scope, utility::Span const call_span);
ErrorOr<types::TypeId> find_or_add_type_id(NonnullRefPtr<types::Type> const type);
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<interpreter::ExecutionResult> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::ExecutionResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<interpreter::Deferred> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::Deferred const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<interpreter::StatementResult> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::StatementResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<interpreter::InterpreterScope> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::InterpreterScope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<interpreter::Interpreter> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::Interpreter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
