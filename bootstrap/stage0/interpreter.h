#pragma once
#include "__unified_forward.h"
#include "types.h"
#include "parser.h"
#include "utility.h"
#include "error.h"
#include "compiler.h"
#include "jakt__platform.h"
namespace Jakt {
namespace interpreter {
enum class InterpretError: i32 {
CallToExternalFunction = (infallible_integer_cast<i32>((static_cast<i32>(42)))),
MismatchingArguments = (infallible_integer_cast<i32>((static_cast<u64>(43ULL)))),
InvalidThisArgument = (infallible_integer_cast<i32>((static_cast<u64>(44ULL)))),
InvalidOperation = (infallible_integer_cast<i32>((static_cast<u64>(45ULL)))),
InvalidType = (infallible_integer_cast<i32>((static_cast<u64>(46ULL)))),
UnknownVariable = (infallible_integer_cast<i32>((static_cast<u64>(47ULL)))),
Unimplemented = (infallible_integer_cast<i32>((static_cast<u64>(48ULL)))),
UnwrapOptionalNone = (infallible_integer_cast<i32>((static_cast<u64>(49ULL)))),
InvalidCharacterConstant = (infallible_integer_cast<i32>((static_cast<u64>(50ULL)))),
};
class Interpreter : public RefCounted<Interpreter>, public Weakable<Interpreter> {
  public:
virtual ~Interpreter() = default;
NonnullRefPtr<compiler::Compiler> compiler;NonnullRefPtr<types::CheckedProgram> program;JaktInternal::DynamicArray<utility::Span> spans;JaktInternal::Dictionary<DeprecatedString,types::Value> reflected_type_cache;JaktInternal::Set<DeprecatedString> seen_reflected_types;JaktInternal::Optional<types::FunctionId> current_function_id;NonnullRefPtr<types::TypecheckFunctions> typecheck_functions;ErrorOr<DeprecatedString> string_from_value(types::Value const value);
ErrorOr<void> update_binding(NonnullRefPtr<typename types::CheckedExpression> const binding, NonnullRefPtr<interpreter::InterpreterScope> scope, types::Value const value, utility::Span const span);
protected:
explicit Interpreter(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, JaktInternal::DynamicArray<utility::Span> a_spans, JaktInternal::Dictionary<DeprecatedString,types::Value> a_reflected_type_cache, JaktInternal::Set<DeprecatedString> a_seen_reflected_types, JaktInternal::Optional<types::FunctionId> a_current_function_id, NonnullRefPtr<types::TypecheckFunctions> a_typecheck_functions);
public:
static ErrorOr<NonnullRefPtr<Interpreter>> __jakt_create(NonnullRefPtr<compiler::Compiler> compiler, NonnullRefPtr<types::CheckedProgram> program, JaktInternal::DynamicArray<utility::Span> spans, JaktInternal::Dictionary<DeprecatedString,types::Value> reflected_type_cache, JaktInternal::Set<DeprecatedString> seen_reflected_types, JaktInternal::Optional<types::FunctionId> current_function_id, NonnullRefPtr<types::TypecheckFunctions> typecheck_functions);

ErrorOr<types::CheckedBlock> typecheck_block(parser::ParsedBlock const block, types::ScopeId const scope);
ErrorOr<types::Value> reflect_methods(types::ScopeId const scope_id, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const interpreter_scope);
ErrorOr<types::Value> bool_value(bool const value, utility::Span const span);
ErrorOr<types::Value> string_value(DeprecatedString const string, utility::Span const span);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> perform_final_interpretation_expr_pass(NonnullRefPtr<typename types::CheckedExpression> const expr, NonnullRefPtr<interpreter::InterpreterScope> const scope);
ErrorOr<types::CheckedBlock> perform_final_interpretation_pass(types::CheckedBlock const block, JaktInternal::Optional<types::ScopeId> const runtime_scope, NonnullRefPtr<interpreter::InterpreterScope> const scope);
ErrorOr<types::CheckedBlock> perform_final_interpretation_pass(parser::ParsedBlock const block, types::ScopeId const runtime_scope, NonnullRefPtr<interpreter::InterpreterScope> const scope);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> perform_final_interpretation_pass(NonnullRefPtr<typename types::CheckedStatement> const statement, NonnullRefPtr<interpreter::InterpreterScope> const scope);
ErrorOr<types::Value> array_value_of_type(JaktInternal::DynamicArray<types::Value> const values, types::TypeId const type, utility::Span const span);
ErrorOr<types::TypeId> string_type();
ErrorOr<void> error_with_hint(DeprecatedString const message, utility::Span const span, DeprecatedString const hint_message, utility::Span const hint_span);
ErrorOr<interpreter::StatementResult> call_prelude_function(DeprecatedString const prelude_function, JaktInternal::DynamicArray<types::ResolvedNamespace> const namespace_, JaktInternal::Optional<types::Value> const this_argument, JaktInternal::DynamicArray<types::Value> const arguments, utility::Span const call_span, JaktInternal::Dictionary<DeprecatedString,types::TypeId> const type_bindings);
ErrorOr<void> enter_span(utility::Span const span);
ErrorOr<bool> get_prelude_function(types::ScopeId const scope_id) const;
ErrorOr<types::TypeId> find_or_add_type_id(NonnullRefPtr<typename types::Type> const type);
ErrorOr<interpreter::StatementResult> execute_expression_without_cast(NonnullRefPtr<typename types::CheckedExpression> const expr, NonnullRefPtr<interpreter::InterpreterScope> scope);
ErrorOr<interpreter::StatementResult> execute_expression(NonnullRefPtr<typename types::CheckedExpression> const expr, NonnullRefPtr<interpreter::InterpreterScope> scope);
ErrorOr<interpreter::StatementResult> execute_binary_operator(types::Value const lhs_value, types::Value const rhs_value, parser::BinaryOperator const op, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
ErrorOr<types::TypeId> array_type_of_struct(types::StructId const struct_id);
void leave_span();
ErrorOr<JaktInternal::DynamicArray<types::Value>> reflect_fields(JaktInternal::DynamicArray<types::VarId> const fields, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
ErrorOr<types::Value> tuple_value(JaktInternal::DynamicArray<types::Value> const members, types::TypeId const type, utility::Span const span);
ErrorOr<void> error(DeprecatedString const message, utility::Span const span);
static ErrorOr<NonnullRefPtr<interpreter::Interpreter>> create(NonnullRefPtr<compiler::Compiler> const compiler, NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<types::TypecheckFunctions> const typecheck_functions, JaktInternal::DynamicArray<utility::Span> const spans);
ErrorOr<interpreter::StatementResult> execute_statement(NonnullRefPtr<typename types::CheckedStatement> const statement, NonnullRefPtr<interpreter::InterpreterScope> scope, utility::Span const call_span);
ErrorOr<JaktInternal::DynamicArray<types::Value>> reflect_sum_enum_variants(types::CheckedEnum const subject_enum, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
ErrorOr<interpreter::ExecutionResult> execute(types::FunctionId const function_to_run_id, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> namespace_, JaktInternal::Optional<types::Value> const this_argument, JaktInternal::DynamicArray<types::Value> const arguments, utility::Span const call_span, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const invocation_scope);
static ErrorOr<types::CheckedBlock> invoke_typecheck_block(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, types::ScopeId, types::SafetyMode, JaktInternal::Optional<types::TypeId>)> const& function, parser::ParsedBlock const block, types::ScopeId const parent_scope_id);
ErrorOr<types::TypeId> tuple_type(JaktInternal::DynamicArray<types::TypeId> const members);
ErrorOr<interpreter::StatementResult> execute_block(types::CheckedBlock const block, NonnullRefPtr<interpreter::InterpreterScope> scope, utility::Span const call_span);
ErrorOr<types::Value> reflect_type(types::TypeId const type_id, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
ErrorOr<DeprecatedString> debug_description() const;
};namespace StatementResult_Details {
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
ErrorOr<DeprecatedString> debug_description() const;
};
class InterpreterScope : public RefCounted<InterpreterScope>, public Weakable<InterpreterScope> {
  public:
virtual ~InterpreterScope() = default;
JaktInternal::Dictionary<DeprecatedString,types::Value> bindings;JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent;JaktInternal::Dictionary<DeprecatedString,types::TypeId> type_bindings;JaktInternal::DynamicArray<interpreter::Deferred> defers;ErrorOr<void> set(DeprecatedString const name, types::Value const value);
static ErrorOr<NonnullRefPtr<interpreter::InterpreterScope>> create(JaktInternal::Dictionary<DeprecatedString,types::Value> const bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const parent, JaktInternal::Dictionary<DeprecatedString,types::TypeId> const type_bindings);
ErrorOr<void> defer_statement(NonnullRefPtr<typename types::CheckedStatement> const statement);
ErrorOr<void> perform_defers(NonnullRefPtr<interpreter::Interpreter> interpreter, utility::Span const span);
static ErrorOr<NonnullRefPtr<interpreter::InterpreterScope>> from_runtime_scope(types::ScopeId const scope_id, NonnullRefPtr<types::CheckedProgram> const program, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const parent);
ErrorOr<JaktInternal::Dictionary<DeprecatedString,types::Value>> all_bindings() const;
ErrorOr<void> type_map_for_substitution_helper(JaktInternal::Dictionary<DeprecatedString,DeprecatedString>& map) const;
ErrorOr<types::GenericInferences> type_map_for_substitution() const;
protected:
explicit InterpreterScope(JaktInternal::Dictionary<DeprecatedString,types::Value> a_bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> a_parent, JaktInternal::Dictionary<DeprecatedString,types::TypeId> a_type_bindings, JaktInternal::DynamicArray<interpreter::Deferred> a_defers);
public:
static ErrorOr<NonnullRefPtr<InterpreterScope>> __jakt_create(JaktInternal::Dictionary<DeprecatedString,types::Value> bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent, JaktInternal::Dictionary<DeprecatedString,types::TypeId> type_bindings, JaktInternal::DynamicArray<interpreter::Deferred> defers);

ErrorOr<void> defer_expression(NonnullRefPtr<typename types::CheckedExpression> const expr);
ErrorOr<types::Value> must_get(DeprecatedString const name) const;
ErrorOr<types::TypeId> map_type(types::TypeId const id) const;
ErrorOr<DeprecatedString> debug_description() const;
};namespace Deferred_Details {
struct Expression{
NonnullRefPtr<typename types::CheckedExpression> value;
template<typename _MemberT0>
Expression(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Statement{
NonnullRefPtr<typename types::CheckedStatement> value;
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
ErrorOr<DeprecatedString> debug_description() const;
};
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
ErrorOr<DeprecatedString> debug_description() const;
};
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::Interpreter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::Interpreter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::StatementResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::StatementResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::InterpreterScope> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::InterpreterScope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::Deferred> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::Deferred const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::ExecutionResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::ExecutionResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
