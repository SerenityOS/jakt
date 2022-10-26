#pragma once
#include "__unified_forward.h"
#include "parser.h"
#include "typechecker.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace codegen {
struct LineSpan {
  public:
size_t start;size_t end;LineSpan(size_t a_start, size_t a_end);

ErrorOr<String> debug_description() const;
};namespace AllowedControlExits_Details {
struct Nothing {
};
struct JustReturn {
};
struct AtLoop {
};
}
struct AllowedControlExits : public Variant<AllowedControlExits_Details::Nothing, AllowedControlExits_Details::JustReturn, AllowedControlExits_Details::AtLoop> {
using Variant<AllowedControlExits_Details::Nothing, AllowedControlExits_Details::JustReturn, AllowedControlExits_Details::AtLoop>::Variant;
    using Nothing = AllowedControlExits_Details::Nothing;
    using JustReturn = AllowedControlExits_Details::JustReturn;
    using AtLoop = AllowedControlExits_Details::AtLoop;
ErrorOr<String> debug_description() const;
codegen::AllowedControlExits allow_return() const;
};
struct ControlFlowState {
  public:
codegen::AllowedControlExits allowed_exits;bool passes_through_match;bool passes_through_try;size_t match_nest_level;codegen::ControlFlowState enter_function() const;
codegen::ControlFlowState enter_loop() const;
static codegen::ControlFlowState no_control_flow();
bool is_match_nested() const;
String choose_control_flow_macro() const;
codegen::ControlFlowState enter_match() const;
ControlFlowState(codegen::AllowedControlExits a_allowed_exits, bool a_passes_through_match, bool a_passes_through_try, size_t a_match_nest_level);

ErrorOr<String> debug_description() const;
};struct CodegenDebugInfo {
  public:
NonnullRefPtr<compiler::Compiler> compiler;JaktInternal::Dictionary<size_t,JaktInternal::Array<codegen::LineSpan>> line_spans;bool statement_span_comments;ErrorOr<void> gather_line_spans();
ErrorOr<String> span_to_source_location(const utility::Span span);
CodegenDebugInfo(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Dictionary<size_t,JaktInternal::Array<codegen::LineSpan>> a_line_spans, bool a_statement_span_comments);

ErrorOr<String> debug_description() const;
};struct CodeGenerator {
  public:
NonnullRefPtr<compiler::Compiler> compiler;NonnullRefPtr<types::CheckedProgram> program;codegen::ControlFlowState control_flow_state;JaktInternal::Array<JaktInternal::Tuple<String,String>> entered_yieldable_blocks;String deferred_output;JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> current_function;bool inside_defer;codegen::CodegenDebugInfo debug_info;JaktInternal::Array<String> namespace_stack;size_t fresh_var_counter;size_t fresh_label_counter;ErrorOr<String> codegen_function(const NonnullRefPtr<types::CheckedFunction> function_, const bool as_method);
ErrorOr<String> codegen_generic_type_instance(const types::StructId id, const JaktInternal::Array<types::TypeId> args, const bool as_namespace) const;
ErrorOr<JaktInternal::Array<types::ModuleId>> topologically_sort_modules() const;
ErrorOr<String> codegen_debug_description_getter(const types::CheckedStruct struct_, const bool is_inline);
ErrorOr<String> codegen_unchecked_binary_op(const NonnullRefPtr<types::CheckedExpression> lhs, const NonnullRefPtr<types::CheckedExpression> rhs, const parser::BinaryOperator op, const types::TypeId type_id);
ErrorOr<String> codegen_namespace(const NonnullRefPtr<types::Scope> scope, const NonnullRefPtr<types::Module> current_module, const bool as_forward);
ErrorOr<JaktInternal::Dictionary<String,JaktInternal::Array<String>>> produce_codegen_dependency_graph(const NonnullRefPtr<types::Scope> scope) const;
ErrorOr<String> codegen_unchecked_binary_op_assignment(const NonnullRefPtr<types::CheckedExpression> lhs, const NonnullRefPtr<types::CheckedExpression> rhs, const parser::BinaryOperator op, const types::TypeId type_id);
ErrorOr<String> codegen_statement(const NonnullRefPtr<types::CheckedStatement> statement);
ErrorOr<String> codegen_enum(const types::CheckedEnum enum_);
ErrorOr<String> codegen_struct_type(const types::StructId id, const bool as_namespace) const;
ErrorOr<String> codegen_struct_predecl(const types::CheckedStruct struct_);
ErrorOr<String> codegen_generic_match(const NonnullRefPtr<types::CheckedExpression> expr, const JaktInternal::Array<types::CheckedMatchCase> cases, const types::TypeId return_type_id, const bool all_variants_constant);
ErrorOr<String> codegen_checked_binary_op(const NonnullRefPtr<types::CheckedExpression> lhs, const NonnullRefPtr<types::CheckedExpression> rhs, const parser::BinaryOperator op, const types::TypeId type_id);
ErrorOr<JaktInternal::Array<String>> extract_dependencies_from_enum(const types::EnumId enum_id, const JaktInternal::Dictionary<String,JaktInternal::Array<String>> dependency_graph, const bool top_level) const;
ErrorOr<String> codegen_expression(const NonnullRefPtr<types::CheckedExpression> expression);
ErrorOr<JaktInternal::Array<String>> extract_dependencies_from_struct(const types::StructId struct_id, const JaktInternal::Dictionary<String,JaktInternal::Array<String>> dependency_graph, const bool top_level, const JaktInternal::Array<types::TypeId> args) const;
ErrorOr<String> codegen_function_in_namespace(const NonnullRefPtr<types::CheckedFunction> function_, const JaktInternal::Optional<types::TypeId> containing_struct, const bool as_method);
ErrorOr<String> codegen_method_call(const NonnullRefPtr<types::CheckedExpression> expr, const types::CheckedCall call, const bool is_optional);
CodeGenerator(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, codegen::ControlFlowState a_control_flow_state, JaktInternal::Array<JaktInternal::Tuple<String,String>> a_entered_yieldable_blocks, String a_deferred_output, JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> a_current_function, bool a_inside_defer, codegen::CodegenDebugInfo a_debug_info, JaktInternal::Array<String> a_namespace_stack, size_t a_fresh_var_counter, size_t a_fresh_label_counter);

ErrorOr<String> codegen_struct(const types::CheckedStruct struct_);
ErrorOr<String> codegen_enum_predecl(const types::CheckedEnum enum_);
ErrorOr<String> codegen_binary_expression(const NonnullRefPtr<types::CheckedExpression> expression, const types::TypeId type_id, const NonnullRefPtr<types::CheckedExpression> lhs, const NonnullRefPtr<types::CheckedExpression> rhs, const parser::BinaryOperator op);
ErrorOr<String> codegen_namespace_predecl(const NonnullRefPtr<types::Scope> scope, const NonnullRefPtr<types::Module> current_module);
ErrorOr<String> current_error_handler() const;
ErrorOr<String> codegen_namespace_qualifier(const types::ScopeId scope_id) const;
ErrorOr<String> codegen_namespace_path(const types::CheckedCall call) const;
ErrorOr<String> codegen_type_possibly_as_namespace(const types::TypeId type_id, const bool as_namespace) const;
ErrorOr<JaktInternal::Array<String>> extract_dependencies_from(const types::TypeId type_id, const JaktInternal::Dictionary<String,JaktInternal::Array<String>> dependency_graph, const bool top_level) const;
ErrorOr<String> codegen_match_body(const types::CheckedMatchBody body, const types::TypeId return_type_id);
ErrorOr<String> codegen_function_predecl(const NonnullRefPtr<types::CheckedFunction> function_, const bool as_method);
ErrorOr<String> fresh_var();
ErrorOr<String> codegen_block(const types::CheckedBlock block);
ErrorOr<String> codegen_checked_binary_op_assignment(const NonnullRefPtr<types::CheckedExpression> lhs, const NonnullRefPtr<types::CheckedExpression> rhs, const parser::BinaryOperator op, const types::TypeId type_id);
ErrorOr<String> codegen_enum_type(const types::EnumId id, const bool as_namespace) const;
ErrorOr<String> codegen_constructor(const NonnullRefPtr<types::CheckedFunction> function_, const bool is_inline);
ErrorOr<String> codegen_enum_debug_description_getter(const types::CheckedEnum enum_, const bool is_inline);
ErrorOr<String> codegen_enum_match(const types::CheckedEnum enum_, const NonnullRefPtr<types::CheckedExpression> expr, const JaktInternal::Array<types::CheckedMatchCase> match_cases, const types::TypeId type_id, const bool all_variants_constant);
ErrorOr<String> codegen_match(const NonnullRefPtr<types::CheckedExpression> expr, const JaktInternal::Array<types::CheckedMatchCase> match_cases, const types::TypeId type_id, const bool all_variants_constant);
ErrorOr<String> codegen_function_return_type(const NonnullRefPtr<types::CheckedFunction> function_);
static ErrorOr<JaktInternal::Dictionary<String,JaktInternal::Tuple<String,String>>> generate(const NonnullRefPtr<compiler::Compiler> compiler, const NonnullRefPtr<types::CheckedProgram> program, const bool debug_info);
ErrorOr<String> codegen_call(const types::CheckedCall call);
ErrorOr<String> codegen_generic_enum_instance(const types::EnumId id, const JaktInternal::Array<types::TypeId> args, const bool as_namespace) const;
ErrorOr<String> codegen_function_generic_parameters(const NonnullRefPtr<types::CheckedFunction> function_);
ErrorOr<String> codegen_ak_formatter(const String name, const JaktInternal::Array<String> generic_parameter_names);
ErrorOr<String> codegen_constructor_predecl(const NonnullRefPtr<types::CheckedFunction> function_);
ErrorOr<String> codegen_type(const types::TypeId type_id) const;
ErrorOr<void> postorder_traversal(const String encoded_type_id, JaktInternal::Set<String> visited, const JaktInternal::Dictionary<String,JaktInternal::Array<String>> encoded_dependency_graph, JaktInternal::Array<types::TypeId> output) const;
ErrorOr<String> fresh_label();
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<codegen::LineSpan> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, codegen::LineSpan const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<codegen::AllowedControlExits> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, codegen::AllowedControlExits const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<codegen::ControlFlowState> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, codegen::ControlFlowState const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<codegen::CodegenDebugInfo> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, codegen::CodegenDebugInfo const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<codegen::CodeGenerator> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, codegen::CodeGenerator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
