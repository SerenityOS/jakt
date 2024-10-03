#pragma once
#include <lib.h>
#include "types.h"
#include "ids.h"
#include "parser.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__platform.h"
namespace Jakt {
namespace interpreter {
class InterpreterScope;
class Interpreter;
enum class InterpretError: i32;
struct Deferred;

struct ExecutionResult;

struct StatementResult;

ErrorOr<size_t> align_of_impl(Jakt::ids::TypeId const type_id, NonnullRefPtr<Jakt::interpreter::Interpreter> const interpreter);

ErrorOr<size_t> size_of_impl(Jakt::ids::TypeId const type_id, NonnullRefPtr<Jakt::interpreter::Interpreter> const interpreter);

ErrorOr<Jakt::types::Value> cast_value_to_type(Jakt::types::Value const this_value, Jakt::ids::TypeId const type_id, NonnullRefPtr<Jakt::interpreter::Interpreter> const interpreter, bool const saturating);

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> value_to_checked_expression(Jakt::types::Value const this_value, NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter);

}
namespace interpreter {
enum class InterpretError : i32 {
CallToExternalFunction = static_cast<i32>(static_cast<i32>(42)),
MismatchingArguments = static_cast<i32>(static_cast<i32>(43)),
InvalidThisArgument = static_cast<i32>(static_cast<i32>(44)),
InvalidOperation = static_cast<i32>(static_cast<i32>(45)),
InvalidType = static_cast<i32>(static_cast<i32>(46)),
UnknownVariable = static_cast<i32>(static_cast<i32>(47)),
Unimplemented = static_cast<i32>(static_cast<i32>(48)),
UnwrapOptionalNone = static_cast<i32>(static_cast<i32>(49)),
InvalidCharacterConstant = static_cast<i32>(static_cast<i32>(50)),
};
struct Deferred {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> value;
} Expression;
struct {
NonnullRefPtr<typename Jakt::types::CheckedStatement> value;
} Statement;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static Deferred Expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> value);
[[nodiscard]] static Deferred Statement(NonnullRefPtr<typename Jakt::types::CheckedStatement> value);
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
public: JaktInternal::Dictionary<ByteString,Jakt::types::Value> bindings;public: JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> parent;public: JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> type_bindings;public: JaktInternal::DynamicArray<Jakt::interpreter::Deferred> defers;private: NonnullRefPtr<Jakt::compiler::Compiler> compiler;public: JaktInternal::Optional<Jakt::ids::ScopeId> runtime_scope_id;public: static NonnullRefPtr<Jakt::interpreter::InterpreterScope> create(JaktInternal::Dictionary<ByteString,Jakt::types::Value> const bindings, JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> const parent, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const type_bindings, NonnullRefPtr<Jakt::compiler::Compiler> const compiler, JaktInternal::Optional<Jakt::ids::ScopeId> const runtime_scope_id);
public: static NonnullRefPtr<Jakt::interpreter::InterpreterScope> from_runtime_scope(Jakt::ids::ScopeId const scope_id, NonnullRefPtr<Jakt::types::CheckedProgram> const program, JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> const parent);
public: ErrorOr<Jakt::types::Value> must_get(ByteString const name) const;
public: ErrorOr<void> set(ByteString const name, Jakt::types::Value const value);
public: JaktInternal::Dictionary<ByteString,Jakt::types::Value> all_bindings() const;
public: Jakt::ids::TypeId map_type(Jakt::ids::TypeId const id) const;
private: void type_map_for_substitution_helper(JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>& map) const;
public: Jakt::types::GenericInferences type_map_for_substitution() const;
public: ErrorOr<void> perform_defers(NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter, Jakt::utility::Span const span);
public: void defer_expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr);
public: void defer_statement(NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement);
public: protected:
explicit InterpreterScope(JaktInternal::Dictionary<ByteString,Jakt::types::Value> a_bindings, JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> a_parent, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> a_type_bindings, JaktInternal::DynamicArray<Jakt::interpreter::Deferred> a_defers, NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, JaktInternal::Optional<Jakt::ids::ScopeId> a_runtime_scope_id);
public:
static NonnullRefPtr<InterpreterScope> __jakt_create(JaktInternal::Dictionary<ByteString,Jakt::types::Value> bindings, JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> parent, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> type_bindings, JaktInternal::DynamicArray<Jakt::interpreter::Deferred> defers, NonnullRefPtr<Jakt::compiler::Compiler> compiler, JaktInternal::Optional<Jakt::ids::ScopeId> runtime_scope_id);

public: ByteString debug_description() const;
};struct ExecutionResult {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::types::Value value;
} Return;
struct {
Jakt::types::Value value;
} Throw;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ExecutionResult Return(Jakt::types::Value value);
[[nodiscard]] static ExecutionResult Throw(Jakt::types::Value value);
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
Jakt::types::Value value;
} Return;
struct {
Jakt::types::Value value;
} Throw;
struct {
Jakt::types::Value value;
} Yield;
struct {
Jakt::types::Value value;
} JustValue;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static StatementResult Return(Jakt::types::Value value);
[[nodiscard]] static StatementResult Throw(Jakt::types::Value value);
[[nodiscard]] static StatementResult Yield(Jakt::types::Value value);
[[nodiscard]] static StatementResult Continue();
[[nodiscard]] static StatementResult Break();
[[nodiscard]] static StatementResult JustValue(Jakt::types::Value value);
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
public: NonnullRefPtr<Jakt::compiler::Compiler> compiler;public: NonnullRefPtr<Jakt::types::CheckedProgram> program;public: JaktInternal::DynamicArray<Jakt::utility::Span> spans;public: JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::types::Value> reflected_type_cache;public: JaktInternal::Set<Jakt::ids::TypeId> seen_reflected_types;public: JaktInternal::Optional<Jakt::ids::FunctionId> current_function_id;public: NonnullRefPtr<Jakt::types::TypecheckFunctions> typecheck_functions;public: static NonnullRefPtr<Jakt::interpreter::Interpreter> create(NonnullRefPtr<Jakt::compiler::Compiler> const compiler, NonnullRefPtr<Jakt::types::CheckedProgram> const program, NonnullRefPtr<Jakt::types::TypecheckFunctions> const typecheck_functions, JaktInternal::DynamicArray<Jakt::utility::Span> const spans);
public: void enter_span(Jakt::utility::Span const span);
public: void leave_span();
public: ErrorOr<Jakt::types::CheckedBlock> perform_final_interpretation_pass(Jakt::types::CheckedBlock const block, JaktInternal::Optional<Jakt::ids::ScopeId> const runtime_scope, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope, JaktInternal::Optional<Jakt::ids::FunctionId> const function_id);
public: ErrorOr<Jakt::types::CheckedBlock> perform_final_interpretation_pass(Jakt::parser::ParsedBlock const block, Jakt::ids::ScopeId const runtime_scope, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope, JaktInternal::Optional<Jakt::ids::FunctionId> const function_id);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> perform_final_interpretation_pass(NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope, JaktInternal::Optional<Jakt::ids::FunctionId> const function_id);
private: ErrorOr<Jakt::types::CheckedBlock> typecheck_block(Jakt::parser::ParsedBlock const block, Jakt::ids::ScopeId const scope, JaktInternal::Optional<Jakt::ids::FunctionId> const function_id);
private: static ErrorOr<Jakt::types::CheckedBlock> invoke_typecheck_block(Function<ErrorOr<Jakt::types::CheckedBlock>(Jakt::parser::ParsedBlock, Jakt::ids::ScopeId, Jakt::types::SafetyMode, JaktInternal::Optional<Jakt::ids::TypeId>, JaktInternal::Optional<Jakt::ids::FunctionId>)> const& function, Jakt::parser::ParsedBlock const block, Jakt::ids::ScopeId const parent_scope_id, JaktInternal::Optional<Jakt::ids::FunctionId> const function_id);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> perform_final_interpretation_expr_pass(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope, JaktInternal::Optional<Jakt::ids::FunctionId> const function_id);
public: bool get_prelude_function(Jakt::ids::ScopeId const scope_id) const;
public: Jakt::ids::TypeId find_or_add_type_id(NonnullRefPtr<typename Jakt::types::Type> const type);
public: ErrorOr<Jakt::interpreter::StatementResult> call_prelude_function(ByteString const prelude_function, JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> const namespace_, JaktInternal::Optional<Jakt::types::Value> const this_argument, JaktInternal::DynamicArray<Jakt::types::Value> const arguments, Jakt::utility::Span const call_span, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const type_bindings, JaktInternal::Optional<Jakt::ids::ScopeId> const runtime_scope_id);
private: ErrorOr<Jakt::interpreter::StatementResult> call_compiler_interface_function(NonnullRefPtr<Jakt::types::CheckedFunction> const function, JaktInternal::DynamicArray<Jakt::types::Value> const arguments, Jakt::utility::Span const call_span, JaktInternal::Optional<Jakt::ids::ScopeId> const scope_id);
public: ErrorOr<Jakt::interpreter::ExecutionResult> execute(Jakt::ids::FunctionId const function_to_run_id, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>> namespace_, JaktInternal::Optional<Jakt::types::Value> const this_argument, JaktInternal::DynamicArray<Jakt::types::Value> const arguments, Jakt::utility::Span const call_span, JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> const invocation_scope, bool const is_main);
public: ErrorOr<Jakt::interpreter::StatementResult> execute_statement(NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement, NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope, Jakt::utility::Span const call_span);
public: ErrorOr<Jakt::interpreter::StatementResult> execute_block(Jakt::types::CheckedBlock const block, NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope, Jakt::utility::Span const call_span);
public: ErrorOr<void> error(ByteString const message, Jakt::utility::Span const span);
public: ErrorOr<void> error_with_hint(ByteString const message, Jakt::utility::Span const span, ByteString const hint_message, Jakt::utility::Span const hint_span);
public: ErrorOr<Jakt::interpreter::StatementResult> execute_binary_operator(Jakt::types::Value const lhs_value, Jakt::types::Value const rhs_value, Jakt::parser::BinaryOperator const op, Jakt::utility::Span const span, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope);
public: ErrorOr<void> update_binding(NonnullRefPtr<typename Jakt::types::CheckedExpression> const binding, NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope, Jakt::types::Value const value, Jakt::utility::Span const span);
public: ErrorOr<Jakt::interpreter::StatementResult> execute_expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr, NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope);
public: ErrorOr<Jakt::interpreter::StatementResult> execute_expression_without_cast(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr, NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope);
public: ErrorOr<Jakt::ids::TypeId> array_type_of_struct(Jakt::ids::StructId const struct_id);
public: ErrorOr<Jakt::types::Value> array_value_of_type(JaktInternal::DynamicArray<Jakt::types::Value> const values, Jakt::ids::TypeId const type, Jakt::utility::Span const span);
public: ErrorOr<Jakt::ids::TypeId> tuple_type(JaktInternal::DynamicArray<Jakt::ids::TypeId> const members);
public: ErrorOr<Jakt::types::Value> tuple_value(JaktInternal::DynamicArray<Jakt::types::Value> const members, Jakt::ids::TypeId const type, Jakt::utility::Span const span);
public: ErrorOr<Jakt::types::Value> bool_value(bool const value, Jakt::utility::Span const span);
public: ErrorOr<Jakt::types::Value> error_value(ByteString const string, Jakt::utility::Span const span);
public: ErrorOr<Jakt::ids::TypeId> string_type();
public: ErrorOr<Jakt::types::Value> string_value(ByteString const string, Jakt::utility::Span const span);
public: ErrorOr<ByteString> string_from_value(Jakt::types::Value const value);
public: ErrorOr<Jakt::types::Value> reflect_methods(Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const interpreter_scope);
public: ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>> reflect_fields(JaktInternal::DynamicArray<Jakt::ids::VarId> const fields, Jakt::utility::Span const span, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope);
public: ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>> reflect_value_enum_variants(Jakt::types::CheckedEnum const subject_enum, Jakt::utility::Span const span, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope);
public: ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>> reflect_sum_enum_variants(Jakt::types::CheckedEnum const subject_enum, Jakt::utility::Span const span, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope);
public: ErrorOr<Jakt::types::Value> reflect_type(Jakt::ids::TypeId const type_id, Jakt::utility::Span const span, NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope);
public: protected:
explicit Interpreter(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, NonnullRefPtr<Jakt::types::CheckedProgram> a_program, JaktInternal::DynamicArray<Jakt::utility::Span> a_spans, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::types::Value> a_reflected_type_cache, JaktInternal::Set<Jakt::ids::TypeId> a_seen_reflected_types, JaktInternal::Optional<Jakt::ids::FunctionId> a_current_function_id, NonnullRefPtr<Jakt::types::TypecheckFunctions> a_typecheck_functions);
public:
static NonnullRefPtr<Interpreter> __jakt_create(NonnullRefPtr<Jakt::compiler::Compiler> compiler, NonnullRefPtr<Jakt::types::CheckedProgram> program, JaktInternal::DynamicArray<Jakt::utility::Span> spans, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::types::Value> reflected_type_cache, JaktInternal::Set<Jakt::ids::TypeId> seen_reflected_types, JaktInternal::Optional<Jakt::ids::FunctionId> current_function_id, NonnullRefPtr<Jakt::types::TypecheckFunctions> typecheck_functions);

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
