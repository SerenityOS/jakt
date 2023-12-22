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
enum class InterpretError : i32 {
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
struct Deferred {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename types::CheckedExpression> value;
} Expression;
struct {
NonnullRefPtr<typename types::CheckedStatement> value;
} Statement;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static Deferred Expression(NonnullRefPtr<typename types::CheckedExpression> value);
[[nodiscard]] static Deferred Statement(NonnullRefPtr<typename types::CheckedStatement> value);
~Deferred();
Deferred& operator=(Deferred const &);
Deferred& operator=(Deferred &&);
Deferred(Deferred const&);
Deferred(Deferred &&);
private: void __jakt_destroy_variant();
public:
private:
Deferred() {};
};
class InterpreterScope :public RefCounted<InterpreterScope>, public Weakable<InterpreterScope> {
  public:
virtual ~InterpreterScope() = default;
public: JaktInternal::Dictionary<ByteString,types::Value> bindings;public: JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent;public: JaktInternal::Dictionary<ids::TypeId,ids::TypeId> type_bindings;public: JaktInternal::DynamicArray<interpreter::Deferred> defers;public: static NonnullRefPtr<interpreter::InterpreterScope> create(JaktInternal::Dictionary<ByteString,types::Value> const bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const parent, JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const type_bindings);
public: static NonnullRefPtr<interpreter::InterpreterScope> from_runtime_scope(ids::ScopeId const scope_id, NonnullRefPtr<types::CheckedProgram> const program, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const parent);
public: ErrorOr<types::Value> must_get(ByteString const name) const;
public: ErrorOr<void> set(ByteString const name, types::Value const value);
public: JaktInternal::Dictionary<ByteString,types::Value> all_bindings() const;
public: ids::TypeId map_type(ids::TypeId const id) const;
private: void type_map_for_substitution_helper(JaktInternal::Dictionary<ids::TypeId,ids::TypeId>& map) const;
public: types::GenericInferences type_map_for_substitution() const;
public: ErrorOr<void> perform_defers(NonnullRefPtr<interpreter::Interpreter> interpreter, utility::Span const span);
public: void defer_expression(NonnullRefPtr<typename types::CheckedExpression> const expr);
public: void defer_statement(NonnullRefPtr<typename types::CheckedStatement> const statement);
public: protected:
explicit InterpreterScope(JaktInternal::Dictionary<ByteString,types::Value> a_bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> a_parent, JaktInternal::Dictionary<ids::TypeId,ids::TypeId> a_type_bindings, JaktInternal::DynamicArray<interpreter::Deferred> a_defers);
public:
static NonnullRefPtr<InterpreterScope> __jakt_create(JaktInternal::Dictionary<ByteString,types::Value> bindings, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> parent, JaktInternal::Dictionary<ids::TypeId,ids::TypeId> type_bindings, JaktInternal::DynamicArray<interpreter::Deferred> defers);

public: ByteString debug_description() const;
};struct ExecutionResult {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
types::Value value;
} Return;
struct {
types::Value value;
} Throw;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ExecutionResult Return(types::Value value);
[[nodiscard]] static ExecutionResult Throw(types::Value value);
~ExecutionResult();
ExecutionResult& operator=(ExecutionResult const &);
ExecutionResult& operator=(ExecutionResult &&);
ExecutionResult(ExecutionResult const&);
ExecutionResult(ExecutionResult &&);
private: void __jakt_destroy_variant();
public:
private:
ExecutionResult() {};
};
struct StatementResult {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
types::Value value;
} Return;
struct {
types::Value value;
} Throw;
struct {
types::Value value;
} Yield;
struct {
types::Value value;
} JustValue;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static StatementResult Return(types::Value value);
[[nodiscard]] static StatementResult Throw(types::Value value);
[[nodiscard]] static StatementResult Yield(types::Value value);
[[nodiscard]] static StatementResult Continue();
[[nodiscard]] static StatementResult Break();
[[nodiscard]] static StatementResult JustValue(types::Value value);
~StatementResult();
StatementResult& operator=(StatementResult const &);
StatementResult& operator=(StatementResult &&);
StatementResult(StatementResult const&);
StatementResult(StatementResult &&);
private: void __jakt_destroy_variant();
public:
private:
StatementResult() {};
};
class Interpreter :public RefCounted<Interpreter>, public Weakable<Interpreter> {
  public:
virtual ~Interpreter() = default;
public: NonnullRefPtr<compiler::Compiler> compiler;public: NonnullRefPtr<types::CheckedProgram> program;public: JaktInternal::DynamicArray<utility::Span> spans;public: JaktInternal::Dictionary<ids::TypeId,types::Value> reflected_type_cache;public: JaktInternal::Set<ids::TypeId> seen_reflected_types;public: JaktInternal::Optional<ids::FunctionId> current_function_id;public: NonnullRefPtr<types::TypecheckFunctions> typecheck_functions;public: static NonnullRefPtr<interpreter::Interpreter> create(NonnullRefPtr<compiler::Compiler> const compiler, NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<types::TypecheckFunctions> const typecheck_functions, JaktInternal::DynamicArray<utility::Span> const spans);
public: void enter_span(utility::Span const span);
public: void leave_span();
public: ErrorOr<types::CheckedBlock> perform_final_interpretation_pass(types::CheckedBlock const block, JaktInternal::Optional<ids::ScopeId> const runtime_scope, NonnullRefPtr<interpreter::InterpreterScope> const scope, JaktInternal::Optional<ids::FunctionId> const function_id);
public: ErrorOr<types::CheckedBlock> perform_final_interpretation_pass(parser::ParsedBlock const block, ids::ScopeId const runtime_scope, NonnullRefPtr<interpreter::InterpreterScope> const scope, JaktInternal::Optional<ids::FunctionId> const function_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> perform_final_interpretation_pass(NonnullRefPtr<typename types::CheckedStatement> const statement, NonnullRefPtr<interpreter::InterpreterScope> const scope, JaktInternal::Optional<ids::FunctionId> const function_id);
private: ErrorOr<types::CheckedBlock> typecheck_block(parser::ParsedBlock const block, ids::ScopeId const scope, JaktInternal::Optional<ids::FunctionId> const function_id);
private: static ErrorOr<types::CheckedBlock> invoke_typecheck_block(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>, JaktInternal::Optional<ids::FunctionId>)> const& function, parser::ParsedBlock const block, ids::ScopeId const parent_scope_id, JaktInternal::Optional<ids::FunctionId> const function_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> perform_final_interpretation_expr_pass(NonnullRefPtr<typename types::CheckedExpression> const expr, NonnullRefPtr<interpreter::InterpreterScope> const scope, JaktInternal::Optional<ids::FunctionId> const function_id);
public: bool get_prelude_function(ids::ScopeId const scope_id) const;
public: ids::TypeId find_or_add_type_id(NonnullRefPtr<typename types::Type> const type);
public: ErrorOr<interpreter::StatementResult> call_prelude_function(ByteString const prelude_function, JaktInternal::DynamicArray<types::ResolvedNamespace> const namespace_, JaktInternal::Optional<types::Value> const this_argument, JaktInternal::DynamicArray<types::Value> const arguments, utility::Span const call_span, JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const type_bindings);
public: ErrorOr<interpreter::ExecutionResult> execute(ids::FunctionId const function_to_run_id, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> namespace_, JaktInternal::Optional<types::Value> const this_argument, JaktInternal::DynamicArray<types::Value> const arguments, utility::Span const call_span, JaktInternal::Optional<NonnullRefPtr<interpreter::InterpreterScope>> const invocation_scope);
public: ErrorOr<interpreter::StatementResult> execute_statement(NonnullRefPtr<typename types::CheckedStatement> const statement, NonnullRefPtr<interpreter::InterpreterScope> scope, utility::Span const call_span);
public: ErrorOr<interpreter::StatementResult> execute_block(types::CheckedBlock const block, NonnullRefPtr<interpreter::InterpreterScope> scope, utility::Span const call_span);
public: ErrorOr<void> error(ByteString const message, utility::Span const span);
public: ErrorOr<void> error_with_hint(ByteString const message, utility::Span const span, ByteString const hint_message, utility::Span const hint_span);
public: ErrorOr<interpreter::StatementResult> execute_binary_operator(types::Value const lhs_value, types::Value const rhs_value, parser::BinaryOperator const op, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
public: ErrorOr<void> update_binding(NonnullRefPtr<typename types::CheckedExpression> const binding, NonnullRefPtr<interpreter::InterpreterScope> scope, types::Value const value, utility::Span const span);
public: ErrorOr<interpreter::StatementResult> execute_expression(NonnullRefPtr<typename types::CheckedExpression> const expr, NonnullRefPtr<interpreter::InterpreterScope> scope);
public: ErrorOr<interpreter::StatementResult> execute_expression_without_cast(NonnullRefPtr<typename types::CheckedExpression> const expr, NonnullRefPtr<interpreter::InterpreterScope> scope);
public: ErrorOr<ids::TypeId> array_type_of_struct(ids::StructId const struct_id);
public: ErrorOr<types::Value> array_value_of_type(JaktInternal::DynamicArray<types::Value> const values, ids::TypeId const type, utility::Span const span);
public: ErrorOr<ids::TypeId> tuple_type(JaktInternal::DynamicArray<ids::TypeId> const members);
public: ErrorOr<types::Value> tuple_value(JaktInternal::DynamicArray<types::Value> const members, ids::TypeId const type, utility::Span const span);
public: ErrorOr<types::Value> bool_value(bool const value, utility::Span const span);
public: ErrorOr<types::Value> error_value(ByteString const string, utility::Span const span);
public: ErrorOr<ids::TypeId> string_type();
public: ErrorOr<types::Value> string_value(ByteString const string, utility::Span const span);
public: ErrorOr<ByteString> string_from_value(types::Value const value);
public: ErrorOr<types::Value> reflect_methods(ids::ScopeId const scope_id, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const interpreter_scope);
public: ErrorOr<JaktInternal::DynamicArray<types::Value>> reflect_fields(JaktInternal::DynamicArray<ids::VarId> const fields, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
public: ErrorOr<JaktInternal::DynamicArray<types::Value>> reflect_sum_enum_variants(types::CheckedEnum const subject_enum, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
public: ErrorOr<types::Value> reflect_type(ids::TypeId const type_id, utility::Span const span, NonnullRefPtr<interpreter::InterpreterScope> const scope);
public: protected:
explicit Interpreter(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, JaktInternal::DynamicArray<utility::Span> a_spans, JaktInternal::Dictionary<ids::TypeId,types::Value> a_reflected_type_cache, JaktInternal::Set<ids::TypeId> a_seen_reflected_types, JaktInternal::Optional<ids::FunctionId> a_current_function_id, NonnullRefPtr<types::TypecheckFunctions> a_typecheck_functions);
public:
static NonnullRefPtr<Interpreter> __jakt_create(NonnullRefPtr<compiler::Compiler> compiler, NonnullRefPtr<types::CheckedProgram> program, JaktInternal::DynamicArray<utility::Span> spans, JaktInternal::Dictionary<ids::TypeId,types::Value> reflected_type_cache, JaktInternal::Set<ids::TypeId> seen_reflected_types, JaktInternal::Optional<ids::FunctionId> current_function_id, NonnullRefPtr<types::TypecheckFunctions> typecheck_functions);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::Deferred> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::Deferred const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::InterpreterScope> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::InterpreterScope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::ExecutionResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::ExecutionResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::StatementResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::StatementResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::interpreter::Interpreter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::interpreter::Interpreter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
