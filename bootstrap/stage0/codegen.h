#pragma once
#include "__unified_forward.h"
#include "parser.h"
#include "typechecker.h"
#include "types.h"
#include "utility.h"
#include "compiler.h"
#include "interpreter.h"
namespace Jakt {
namespace codegen {
struct AllowedControlExits {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static AllowedControlExits Nothing();
[[nodiscard]] static AllowedControlExits JustReturn();
[[nodiscard]] static AllowedControlExits AtLoop();
~AllowedControlExits();
AllowedControlExits& operator=(AllowedControlExits const &);
AllowedControlExits& operator=(AllowedControlExits &&);
AllowedControlExits(AllowedControlExits const&);
AllowedControlExits(AllowedControlExits &&);
private: void __jakt_destroy_variant();
public:
codegen::AllowedControlExits allow_return() const;
private:
AllowedControlExits() {};
};
struct ControlFlowState {
  public:
public: codegen::AllowedControlExits allowed_exits;public: bool passes_through_match;public: bool passes_through_try;public: size_t match_nest_level;public: codegen::ControlFlowState enter_function() const;
public: static ErrorOr<DeprecatedString> nested_release_return_expr(ids::TypeId const func_return_type, bool const func_can_throw, DeprecatedString const cpp_match_result_type);
public: ErrorOr<DeprecatedString> apply_control_flow_macro(DeprecatedString const x, ids::TypeId const func_return_type, bool const func_can_throw, DeprecatedString const cpp_match_result_type) const;
public: codegen::ControlFlowState enter_loop() const;
public: static codegen::ControlFlowState no_control_flow();
public: bool is_match_nested() const;
public: codegen::ControlFlowState enter_match() const;
public: ControlFlowState(codegen::AllowedControlExits a_allowed_exits, bool a_passes_through_match, bool a_passes_through_try, size_t a_match_nest_level);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct CodegenDebugInfo {
  public:
public: NonnullRefPtr<compiler::Compiler> compiler;public: JaktInternal::Dictionary<size_t,JaktInternal::DynamicArray<codegen::LineSpan>> line_spans;public: bool statement_span_comments;public: ErrorOr<void> gather_line_spans();
public: ErrorOr<DeprecatedString> span_to_source_location(utility::Span const span);
public: CodegenDebugInfo(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Dictionary<size_t,JaktInternal::DynamicArray<codegen::LineSpan>> a_line_spans, bool a_statement_span_comments);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct CodeGenerator {
  public:
public: NonnullRefPtr<compiler::Compiler> compiler;public: NonnullRefPtr<types::CheckedProgram> program;public: codegen::ControlFlowState control_flow_state;public: JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> entered_yieldable_blocks;public: DeprecatedString deferred_output;public: JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> current_function;public: bool inside_defer;public: codegen::CodegenDebugInfo debug_info;public: JaktInternal::DynamicArray<DeprecatedString> namespace_stack;public: size_t fresh_var_counter;public: size_t fresh_label_counter;public: JaktInternal::Optional<DeprecatedString> this_replacement;public: static ErrorOr<JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<DeprecatedString,DeprecatedString>>> generate(NonnullRefPtr<compiler::Compiler> const compiler, NonnullRefPtr<types::CheckedProgram> const program, bool const debug_info);
public: ErrorOr<DeprecatedString> codegen_destructor(types::CheckedStruct const& struct_, NonnullRefPtr<types::CheckedFunction> const& function, bool const is_inline);
public: ErrorOr<DeprecatedString> codegen_unchecked_binary_op(NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, parser::BinaryOperator const op, ids::TypeId const type_id);
public: ErrorOr<DeprecatedString> codegen_namespace_qualifier(ids::ScopeId const scope_id, bool const skip_current, JaktInternal::Optional<DeprecatedString> const possible_constructor_name) const;
public: ErrorOr<DeprecatedString> codegen_checked_binary_op(NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, parser::BinaryOperator const op, ids::TypeId const type_id);
public: ErrorOr<DeprecatedString> codegen_constructor_predecl(NonnullRefPtr<types::CheckedFunction> const function);
public: bool is_full_respecialization(JaktInternal::DynamicArray<ids::TypeId> const type_args) const;
public: ErrorOr<JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>>> produce_codegen_dependency_graph(NonnullRefPtr<types::Scope> const scope) const;
public: ErrorOr<DeprecatedString> codegen_statement(NonnullRefPtr<typename types::CheckedStatement> const statement);
public: ErrorOr<DeprecatedString> codegen_function_generic_parameters(NonnullRefPtr<types::CheckedFunction> const function);
public: ErrorOr<DeprecatedString> codegen_function_predecl(NonnullRefPtr<types::CheckedFunction> const function, bool const as_method, bool const allow_generics);
public: static ErrorOr<DeprecatedString> enum_constructor_result_type(types::CheckedEnum const enum_, JaktInternal::Optional<DeprecatedString> const generic_parameter_list);
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,DeprecatedString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,DeprecatedString>>>>>> codegen_enum_field_lists(types::CheckedEnum const enum_);
public: ErrorOr<DeprecatedString> codegen_match_body(types::CheckedMatchBody const body, ids::TypeId const return_type_id);
public: ErrorOr<DeprecatedString> codegen_ak_formatter(DeprecatedString const name, JaktInternal::DynamicArray<DeprecatedString> const generic_parameter_names, DeprecatedString const template_args);
public: ErrorOr<DeprecatedString> codegen_template_parameter_names(JaktInternal::DynamicArray<types::FunctionGenericParameter> const parameters, JaktInternal::DynamicArray<DeprecatedString>& names);
public: ErrorOr<DeprecatedString> codegen_template_parameter_names(JaktInternal::DynamicArray<types::FunctionGenericParameter> const parameters);
public: ErrorOr<DeprecatedString> codegen_template_parameter_names(JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters, JaktInternal::DynamicArray<DeprecatedString>& names);
public: ErrorOr<DeprecatedString> codegen_template_parameter_names(JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters);
public: ErrorOr<DeprecatedString> codegen_template_parameter_names(JaktInternal::DynamicArray<ids::TypeId> const parameters, JaktInternal::DynamicArray<DeprecatedString>& names);
public: ErrorOr<DeprecatedString> codegen_method_call(NonnullRefPtr<typename types::CheckedExpression> const expr, types::CheckedCall const call, bool const is_optional);
public: ErrorOr<void> codegen_for_enum_variants(types::CheckedEnum const& enum_, Function<ErrorOr<DeprecatedString>(DeprecatedString)> const& stmt_fmt, DeprecatedString const index_expr, DeprecatedStringBuilder& output) const;
public: ErrorOr<DeprecatedString> fresh_label();
public: ErrorOr<DeprecatedString> fresh_var();
public: ErrorOr<DeprecatedString> codegen_call(types::CheckedCall const call);
public: ErrorOr<DeprecatedString> codegen_namespace_predecl(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module);
public: ErrorOr<JaktInternal::DynamicArray<ids::ModuleId>> topologically_sort_modules() const;
public: ErrorOr<DeprecatedString> codegen_block(types::CheckedBlock const block);
public: ErrorOr<DeprecatedString> codegen_generic_match(NonnullRefPtr<typename types::CheckedExpression> const expr, JaktInternal::DynamicArray<types::CheckedMatchCase> const cases, ids::TypeId const return_type_id, bool const all_variants_constant);
public: ErrorOr<DeprecatedString> codegen_debug_description_getter(types::CheckedStruct const struct_, bool const is_inline);
public: ErrorOr<DeprecatedString> codegen_lambda_block(bool const can_throw, types::CheckedBlock const block, ids::TypeId const return_type_id);
public: ErrorOr<DeprecatedString> codegen_match(NonnullRefPtr<typename types::CheckedExpression> const expr, JaktInternal::DynamicArray<types::CheckedMatchCase> const match_cases, ids::TypeId const type_id, bool const all_variants_constant);
public: ErrorOr<DeprecatedString> codegen_namespace_specializations(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module);
public: ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> extract_dependencies_from_struct(ids::StructId const struct_id, JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph, bool const top_level, JaktInternal::DynamicArray<ids::TypeId> const args) const;
public: ErrorOr<DeprecatedString> codegen_enum_type(ids::EnumId const id, bool const as_namespace) const;
public: ErrorOr<DeprecatedString> codegen_expression_and_deref_if_generic_and_needed(NonnullRefPtr<typename types::CheckedExpression> const expression);
public: ErrorOr<DeprecatedString> codegen_checked_binary_op_assignment(NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, parser::BinaryOperator const op, ids::TypeId const type_id);
public: ErrorOr<DeprecatedString> codegen_struct(types::CheckedStruct const struct_);
public: CodeGenerator(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, codegen::ControlFlowState a_control_flow_state, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> a_entered_yieldable_blocks, DeprecatedString a_deferred_output, JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> a_current_function, bool a_inside_defer, codegen::CodegenDebugInfo a_debug_info, JaktInternal::DynamicArray<DeprecatedString> a_namespace_stack, size_t a_fresh_var_counter, size_t a_fresh_label_counter, JaktInternal::Optional<DeprecatedString> a_this_replacement);

public: ErrorOr<DeprecatedString> codegen_function(NonnullRefPtr<types::CheckedFunction> const function, bool const as_method);
public: ErrorOr<DeprecatedString> codegen_generic_type_instance(ids::StructId const id, JaktInternal::DynamicArray<ids::TypeId> const args, bool const as_namespace);
public: ErrorOr<JaktInternal::Optional<DeprecatedString>> destructor_name(ids::TypeId const id) const;
public: ErrorOr<DeprecatedString> codegen_enum_debug_description_getter(types::CheckedEnum const enum_, bool const is_inline);
public: ErrorOr<DeprecatedString> codegen_expression(NonnullRefPtr<typename types::CheckedExpression> const expression);
public: ErrorOr<DeprecatedString> codegen_binary_expression(NonnullRefPtr<typename types::CheckedExpression> const expression, ids::TypeId const type_id, NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, types::CheckedBinaryOperator const op);
public: ErrorOr<DeprecatedString> current_error_handler() const;
public: ErrorOr<DeprecatedString> codegen_enum_match(types::CheckedEnum const enum_, NonnullRefPtr<typename types::CheckedExpression> const expr, JaktInternal::DynamicArray<types::CheckedMatchCase> const match_cases, ids::TypeId const type_id, bool const all_variants_constant);
public: ErrorOr<DeprecatedString> codegen_namespace_path(types::CheckedCall const call);
public: ErrorOr<DeprecatedString> codegen_enum_assignment_body(types::CheckedEnum const enum_, bool const is_constructor, bool const use_move) const;
public: ErrorOr<DeprecatedString> codegen_enum(types::CheckedEnum const enum_);
public: ErrorOr<DeprecatedString> codegen_struct_type(ids::StructId const id, bool const as_namespace) const;
public: ErrorOr<DeprecatedString> codegen_enum_predecl(types::CheckedEnum const enum_);
public: ErrorOr<void> postorder_traversal(ids::TypeId const type_id, JaktInternal::Set<ids::TypeId> visited, JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph, JaktInternal::DynamicArray<ids::TypeId> output) const;
public: ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> extract_dependencies_from_enum(ids::EnumId const enum_id, JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph, bool const top_level) const;
public: static ErrorOr<void> codegen_enum_constructor_decl(DeprecatedString const enum_name, DeprecatedString const variant_name, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> const variant_fields, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> const common_fields, bool const is_inline, DeprecatedString const ctor_result_type, DeprecatedString& output);
public: ErrorOr<DeprecatedString> codegen_generic_enum_instance(ids::EnumId const id, JaktInternal::DynamicArray<ids::TypeId> const args, bool const as_namespace);
public: ErrorOr<DeprecatedString> codegen_enum_constructors(types::CheckedEnum const enum_, bool const is_inside_struct, JaktInternal::Optional<DeprecatedString> const generic_parameter_list, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,DeprecatedString>>>> const variant_field_list, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> const common_fields) const;
public: ErrorOr<DeprecatedString> codegen_function_return_type(NonnullRefPtr<types::CheckedFunction> const function);
public: ErrorOr<DeprecatedString> codegen_function_in_namespace(NonnullRefPtr<types::CheckedFunction> const function, JaktInternal::Optional<ids::TypeId> const containing_struct, bool const as_method, bool const skip_template, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const explicit_generic_instantiation);
public: ErrorOr<void> codegen_enum_destroy_variant(types::CheckedEnum const enum_, DeprecatedString& output) const;
public: ErrorOr<DeprecatedString> codegen_type(ids::TypeId const type_id);
public: ErrorOr<JaktInternal::Optional<DeprecatedString>> codegen_namespace_specialization(ids::FunctionId const function_id, JaktInternal::Optional<ids::TypeId> const containing_struct, NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module, bool const define_pass);
public: ErrorOr<DeprecatedString> codegen_destructor_predecl(types::CheckedStruct const& struct_);
public: ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> extract_dependencies_from(ids::TypeId const type_id, JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph, bool const top_level) const;
public: ErrorOr<DeprecatedString> codegen_namespace(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module, bool const as_forward);
public: ErrorOr<DeprecatedString> codegen_unchecked_binary_op_assignment(NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, parser::BinaryOperator const op, ids::TypeId const type_id);
public: ErrorOr<DeprecatedString> codegen_constructor(NonnullRefPtr<types::CheckedFunction> const function, bool const is_inline);
public: ErrorOr<DeprecatedString> codegen_type_possibly_as_namespace(ids::TypeId const type_id, bool const as_namespace);
public: ErrorOr<void> codegen_enum_destructor_body(types::CheckedEnum const enum_, DeprecatedString& output) const;
public: ErrorOr<DeprecatedString> codegen_struct_predecl(types::CheckedStruct const struct_);
public: ErrorOr<DeprecatedString> debug_description() const;
};struct LineSpan {
  public:
public: size_t start;public: size_t end;public: LineSpan(size_t a_start, size_t a_end);

public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::AllowedControlExits> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::AllowedControlExits const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::ControlFlowState> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::ControlFlowState const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::CodegenDebugInfo> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::CodegenDebugInfo const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::CodeGenerator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::CodeGenerator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::LineSpan> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::LineSpan const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
