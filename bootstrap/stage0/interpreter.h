#pragma once
#include "__unified_forward.h"
#include "types.h"
#include "utility.h"
#include "error.h"
#include "compiler.h"
namespace Jakt {
namespace interpreter {
class InterpreterScope : public RefCounted<InterpreterScope>, public Weakable<InterpreterScope> {
  public:
virtual ~InterpreterScope() = default;
JaktInternal::Dictionary<String,types::Value> bindings;JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent;JaktInternal::Dictionary<String,types::TypeId> type_bindings;JaktInternal::Array<interpreter::Deferred> defers;ErrorOr<void> defer_statement(const NonnullRefPtr<types::CheckedStatement> statement);
ErrorOr<void> perform_defers(NonnullRefPtr<interpreter::Interpreter> interpreter, const utility::Span span);
static ErrorOr<NonnullRefPtr<interpreter::InterpreterScope>> from_runtime_scope(const types::ScopeId scope_id, const NonnullRefPtr<types::CheckedProgram> program, const JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent);
ErrorOr<types::GenericInferences> type_map_for_substitution() const;
protected:
explicit InterpreterScope(JaktInternal::Dictionary<String,types::Value>&& a_bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>>&& a_parent, JaktInternal::Dictionary<String,types::TypeId>&& a_type_bindings, JaktInternal::Array<interpreter::Deferred>&& a_defers);
public:
static ErrorOr<NonnullRefPtr<InterpreterScope>> create(JaktInternal::Dictionary<String,types::Value> bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent, JaktInternal::Dictionary<String,types::TypeId> type_bindings, JaktInternal::Array<interpreter::Deferred> defers);

ErrorOr<types::TypeId> map_type(const types::TypeId id) const;
ErrorOr<void> set(const String name, const types::Value value);
static ErrorOr<NonnullRefPtr<interpreter::InterpreterScope>> create(const JaktInternal::Dictionary<String,types::Value> bindings, const JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent, const JaktInternal::Dictionary<String,types::TypeId> type_bindings);
ErrorOr<void> type_map_for_substitution_helper(JaktInternal::Dictionary<String,String>& map) const;
ErrorOr<types::Value> must_get(const String name) const;
ErrorOr<void> defer_expression(const NonnullRefPtr<types::CheckedExpression> expr);
ErrorOr<String> debug_description() const;
};namespace Deferred_Details {
struct Expression{
NonnullRefPtr<types::CheckedExpression> value;
template<typename... Args>
Expression(Args&&... args): value { forward<Args>(args)... } {}
};
struct Statement{
NonnullRefPtr<types::CheckedStatement> value;
template<typename... Args>
Statement(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct Deferred : public Variant<Deferred_Details::Expression, Deferred_Details::Statement> {
using Variant<Deferred_Details::Expression, Deferred_Details::Statement>::Variant;
    using Expression = Deferred_Details::Expression;
    using Statement = Deferred_Details::Statement;
ErrorOr<String> debug_description() const;
};
namespace ExecutionResult_Details {
struct Return{
types::Value value;
template<typename... Args>
Return(Args&&... args): value { forward<Args>(args)... } {}
};
struct Throw{
types::Value value;
template<typename... Args>
Throw(Args&&... args): value { forward<Args>(args)... } {}
};
}
struct ExecutionResult : public Variant<ExecutionResult_Details::Return, ExecutionResult_Details::Throw> {
using Variant<ExecutionResult_Details::Return, ExecutionResult_Details::Throw>::Variant;
    using Return = ExecutionResult_Details::Return;
    using Throw = ExecutionResult_Details::Throw;
ErrorOr<String> debug_description() const;
};
class Interpreter : public RefCounted<Interpreter>, public Weakable<Interpreter> {
  public:
virtual ~Interpreter() = default;
NonnullRefPtr<compiler::Compiler> compiler;NonnullRefPtr<types::CheckedProgram> program;JaktInternal::Array<utility::Span> spans;JaktInternal::Optional<types::FunctionId> current_function_id;ErrorOr<bool> get_prelude_function(const types::ScopeId scope_id) const;
ErrorOr<interpreter::StatementResult> call_prelude_function(const String prelude_function, const JaktInternal::Array<types::ResolvedNamespace> namespace_, const JaktInternal::Optional<types::Value> this_argument, const JaktInternal::Array<types::Value> arguments, const utility::Span call_span, const JaktInternal::Dictionary<String,types::TypeId> type_bindings);
ErrorOr<void> update_binding(const NonnullRefPtr<types::CheckedExpression> binding, NonnullRefPtr<interpreter::InterpreterScope> scope, const types::Value value, const utility::Span span);
ErrorOr<interpreter::StatementResult> execute_binary_operator(const types::Value lhs_value, const types::Value rhs_value, const parser::BinaryOperator op, const utility::Span span, const NonnullRefPtr<interpreter::InterpreterScope> scope);
protected:
explicit Interpreter(NonnullRefPtr<compiler::Compiler>&& a_compiler, NonnullRefPtr<types::CheckedProgram>&& a_program, JaktInternal::Array<utility::Span>&& a_spans, JaktInternal::Optional<types::FunctionId>&& a_current_function_id);
public:
static ErrorOr<NonnullRefPtr<Interpreter>> create(NonnullRefPtr<compiler::Compiler> compiler, NonnullRefPtr<types::CheckedProgram> program, JaktInternal::Array<utility::Span> spans, JaktInternal::Optional<types::FunctionId> current_function_id);

void leave_span();
ErrorOr<void> error(const String message, const utility::Span span);
ErrorOr<interpreter::StatementResult> execute_expression(const NonnullRefPtr<types::CheckedExpression> expr, NonnullRefPtr<interpreter::InterpreterScope> scope);
static ErrorOr<NonnullRefPtr<interpreter::Interpreter>> create(const NonnullRefPtr<compiler::Compiler> compiler, const NonnullRefPtr<types::CheckedProgram> program, const JaktInternal::Array<utility::Span> spans);
ErrorOr<interpreter::StatementResult> execute_expression_without_cast(const NonnullRefPtr<types::CheckedExpression> expr, NonnullRefPtr<interpreter::InterpreterScope> scope);
ErrorOr<interpreter::StatementResult> execute_statement(const NonnullRefPtr<types::CheckedStatement> statement, NonnullRefPtr<interpreter::InterpreterScope> scope, const utility::Span call_span);
ErrorOr<void> error_with_hint(const String message, const utility::Span span, const String hint_message, const utility::Span hint_span);
ErrorOr<interpreter::ExecutionResult> execute(const types::FunctionId function_to_run_id, JaktInternal::Optional<JaktInternal::Array<types::ResolvedNamespace>> namespace_, const JaktInternal::Optional<types::Value> this_argument, const JaktInternal::Array<types::Value> arguments, const utility::Span call_span, const JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> invocation_scope);
ErrorOr<void> enter_span(const utility::Span span);
ErrorOr<interpreter::StatementResult> execute_block(const types::CheckedBlock block, NonnullRefPtr<interpreter::InterpreterScope> scope, const utility::Span call_span);
ErrorOr<types::TypeId> find_or_add_type_id(const NonnullRefPtr<types::Type> type);
ErrorOr<String> debug_description() const;
};enum class InterpretError: i32 {
CallToExternalFunction = (infallible_integer_cast<i32>((static_cast<i32>(42)))),
MismatchingArguments = (infallible_integer_cast<i32>((static_cast<u64>(43ULL)))),
InvalidThisArgument = (infallible_integer_cast<i32>((static_cast<u64>(44ULL)))),
InvalidType = (infallible_integer_cast<i32>((static_cast<u64>(45ULL)))),
UnknownVariable = (infallible_integer_cast<i32>((static_cast<u64>(46ULL)))),
Unimplemented = (infallible_integer_cast<i32>((static_cast<u64>(47ULL)))),
};
namespace StatementResult_Details {
struct Return{
types::Value value;
template<typename... Args>
Return(Args&&... args): value { forward<Args>(args)... } {}
};
struct Throw{
types::Value value;
template<typename... Args>
Throw(Args&&... args): value { forward<Args>(args)... } {}
};
struct Yield{
types::Value value;
template<typename... Args>
Yield(Args&&... args): value { forward<Args>(args)... } {}
};
struct Continue {};
struct Break {};
struct JustValue{
types::Value value;
template<typename... Args>
JustValue(Args&&... args): value { forward<Args>(args)... } {}
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
}
template<>struct Formatter<interpreter::InterpreterScope> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::InterpreterScope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<interpreter::Deferred> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::Deferred const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<interpreter::ExecutionResult> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::ExecutionResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<interpreter::Interpreter> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::Interpreter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<interpreter::StatementResult> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, interpreter::StatementResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
