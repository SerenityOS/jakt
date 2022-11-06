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
ErrorOr<String> span_to_source_location(utility::Span const span);
CodegenDebugInfo(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Dictionary<size_t,JaktInternal::Array<codegen::LineSpan>> a_line_spans, bool a_statement_span_comments);

ErrorOr<String> debug_description() const;
};struct CodeGenerator {
  public:
NonnullRefPtr<compiler::Compiler> compiler;NonnullRefPtr<types::CheckedProgram> program;codegen::ControlFlowState control_flow_state;JaktInternal::Array<JaktInternal::Tuple<String,String>> entered_yieldable_blocks;String deferred_output;JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> current_function;bool inside_defer;codegen::CodegenDebugInfo debug_info;JaktInternal::Array<String> namespace_stack;size_t fresh_var_counter;size_t fresh_label_counter;ErrorOr<String> codegen_function(NonnullRefPtr<types::CheckedFunction> const function_, bool const as_method);
ErrorOr<String> codegen_generic_type_instance(types::StructId const id, JaktInternal::Array<types::TypeId> const args, bool const as_namespace) const;
ErrorOr<JaktInternal::Array<types::ModuleId>> topologically_sort_modules() const;
ErrorOr<String> codegen_debug_description_getter(types::CheckedStruct const struct_, bool const is_inline);
ErrorOr<String> codegen_expression_and_deref_if_generic_and_needed(NonnullRefPtr<types::CheckedExpression> const expression);
ErrorOr<String> codegen_namespace(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module, bool const as_forward);
ErrorOr<String> codegen_unchecked_binary_op(NonnullRefPtr<types::CheckedExpression> const lhs, NonnullRefPtr<types::CheckedExpression> const rhs, parser::BinaryOperator const op, types::TypeId const type_id);
ErrorOr<JaktInternal::Dictionary<String,JaktInternal::Array<String>>> produce_codegen_dependency_graph(NonnullRefPtr<types::Scope> const scope) const;
ErrorOr<String> codegen_unchecked_binary_op_assignment(NonnullRefPtr<types::CheckedExpression> const lhs, NonnullRefPtr<types::CheckedExpression> const rhs, parser::BinaryOperator const op, types::TypeId const type_id);
ErrorOr<String> codegen_statement(NonnullRefPtr<types::CheckedStatement> const statement);
ErrorOr<String> codegen_enum(types::CheckedEnum const enum_);
ErrorOr<String> codegen_struct_type(types::StructId const id, bool const as_namespace) const;
ErrorOr<String> codegen_struct_predecl(types::CheckedStruct const struct_);
ErrorOr<String> codegen_generic_match(NonnullRefPtr<types::CheckedExpression> const expr, JaktInternal::Array<types::CheckedMatchCase> const cases, types::TypeId const return_type_id, bool const all_variants_constant);
ErrorOr<String> codegen_checked_binary_op(NonnullRefPtr<types::CheckedExpression> const lhs, NonnullRefPtr<types::CheckedExpression> const rhs, parser::BinaryOperator const op, types::TypeId const type_id);
ErrorOr<JaktInternal::Array<String>> extract_dependencies_from_enum(types::EnumId const enum_id, JaktInternal::Dictionary<String,JaktInternal::Array<String>> const dependency_graph, bool const top_level) const;
ErrorOr<String> codegen_expression(NonnullRefPtr<types::CheckedExpression> const expression);
ErrorOr<JaktInternal::Array<String>> extract_dependencies_from_struct(types::StructId const struct_id, JaktInternal::Dictionary<String,JaktInternal::Array<String>> const dependency_graph, bool const top_level, JaktInternal::Array<types::TypeId> const args) const;
ErrorOr<String> codegen_function_in_namespace(NonnullRefPtr<types::CheckedFunction> const function_, JaktInternal::Optional<types::TypeId> const containing_struct, bool const as_method);
ErrorOr<String> codegen_method_call(NonnullRefPtr<types::CheckedExpression> const expr, types::CheckedCall const call, bool const is_optional);
CodeGenerator(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, codegen::ControlFlowState a_control_flow_state, JaktInternal::Array<JaktInternal::Tuple<String,String>> a_entered_yieldable_blocks, String a_deferred_output, JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> a_current_function, bool a_inside_defer, codegen::CodegenDebugInfo a_debug_info, JaktInternal::Array<String> a_namespace_stack, size_t a_fresh_var_counter, size_t a_fresh_label_counter);

ErrorOr<String> codegen_struct(types::CheckedStruct const struct_);
ErrorOr<String> codegen_enum_predecl(types::CheckedEnum const enum_);
ErrorOr<String> codegen_binary_expression(NonnullRefPtr<types::CheckedExpression> const expression, types::TypeId const type_id, NonnullRefPtr<types::CheckedExpression> const lhs, NonnullRefPtr<types::CheckedExpression> const rhs, parser::BinaryOperator const op);
ErrorOr<String> codegen_namespace_predecl(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module);
ErrorOr<String> current_error_handler() const;
ErrorOr<String> codegen_namespace_qualifier(types::ScopeId const scope_id) const;
ErrorOr<String> codegen_namespace_path(types::CheckedCall const call) const;
ErrorOr<String> codegen_type_possibly_as_namespace(types::TypeId const type_id, bool const as_namespace) const;
ErrorOr<JaktInternal::Array<String>> extract_dependencies_from(types::TypeId const type_id, JaktInternal::Dictionary<String,JaktInternal::Array<String>> const dependency_graph, bool const top_level) const;
ErrorOr<String> codegen_match_body(types::CheckedMatchBody const body, types::TypeId const return_type_id);
ErrorOr<String> codegen_function_predecl(NonnullRefPtr<types::CheckedFunction> const function_, bool const as_method);
ErrorOr<String> fresh_var();
ErrorOr<String> codegen_block(types::CheckedBlock const block);
ErrorOr<String> codegen_checked_binary_op_assignment(NonnullRefPtr<types::CheckedExpression> const lhs, NonnullRefPtr<types::CheckedExpression> const rhs, parser::BinaryOperator const op, types::TypeId const type_id);
ErrorOr<String> codegen_enum_type(types::EnumId const id, bool const as_namespace) const;
ErrorOr<String> codegen_constructor(NonnullRefPtr<types::CheckedFunction> const function_, bool const is_inline);
ErrorOr<String> codegen_enum_debug_description_getter(types::CheckedEnum const enum_, bool const is_inline);
ErrorOr<String> codegen_enum_match(types::CheckedEnum const enum_, NonnullRefPtr<types::CheckedExpression> const expr, JaktInternal::Array<types::CheckedMatchCase> const match_cases, types::TypeId const type_id, bool const all_variants_constant);
ErrorOr<String> codegen_match(NonnullRefPtr<types::CheckedExpression> const expr, JaktInternal::Array<types::CheckedMatchCase> const match_cases, types::TypeId const type_id, bool const all_variants_constant);
ErrorOr<String> codegen_function_return_type(NonnullRefPtr<types::CheckedFunction> const function_);
static ErrorOr<JaktInternal::Dictionary<String,JaktInternal::Tuple<String,String>>> generate(NonnullRefPtr<compiler::Compiler> const compiler, NonnullRefPtr<types::CheckedProgram> const program, bool const debug_info);
ErrorOr<String> codegen_call(types::CheckedCall const call);
ErrorOr<String> codegen_generic_enum_instance(types::EnumId const id, JaktInternal::Array<types::TypeId> const args, bool const as_namespace) const;
ErrorOr<String> codegen_function_generic_parameters(NonnullRefPtr<types::CheckedFunction> const function_);
ErrorOr<String> codegen_ak_formatter(String const name, JaktInternal::Array<String> const generic_parameter_names);
ErrorOr<String> codegen_constructor_predecl(NonnullRefPtr<types::CheckedFunction> const function_);
ErrorOr<String> codegen_type(types::TypeId const type_id) const;
ErrorOr<void> postorder_traversal(String const encoded_type_id, JaktInternal::Set<String> visited, JaktInternal::Dictionary<String,JaktInternal::Array<String>> const encoded_dependency_graph, JaktInternal::Array<types::TypeId> output) const;
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
