#pragma once
#include "__unified_forward.h"
#include "typechecker.h"
#include "interpreter.h"
#include "types.h"
#include "ids.h"
#include "parser.h"
#include "compiler.h"
#include "utility.h"
#include "jakt__path.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace codegen {
struct AllowedControlExits {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
public: codegen::AllowedControlExits allowed_exits;public: bool passes_through_try;public: bool directly_inside_match;public: bool indirectly_inside_match;public: static codegen::ControlFlowState no_control_flow();
public: codegen::ControlFlowState enter_function() const;
public: codegen::ControlFlowState enter_loop() const;
public: codegen::ControlFlowState enter_match() const;
public: ErrorOr<ByteString> apply_control_flow_macro(ByteString const x, ids::TypeId const func_return_type, bool const func_can_throw) const;
public: ControlFlowState(codegen::AllowedControlExits a_allowed_exits, bool a_passes_through_try, bool a_directly_inside_match, bool a_indirectly_inside_match);

public: ByteString debug_description() const;
};struct LineSpan {
  public:
public: size_t start;public: size_t end;public: LineSpan(size_t a_start, size_t a_end);

public: ByteString debug_description() const;
};struct CodegenDebugInfo {
  public:
public: NonnullRefPtr<compiler::Compiler> compiler;public: JaktInternal::Dictionary<size_t,JaktInternal::DynamicArray<codegen::LineSpan>> line_spans;public: bool statement_span_comments;public: ErrorOr<ByteString> span_to_source_location(utility::Span const span);
public: ErrorOr<void> gather_line_spans();
public: CodegenDebugInfo(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Dictionary<size_t,JaktInternal::DynamicArray<codegen::LineSpan>> a_line_spans, bool a_statement_span_comments);

public: ByteString debug_description() const;
};struct CodeGenerator {
  public:
public: NonnullRefPtr<compiler::Compiler> compiler;public: NonnullRefPtr<types::CheckedProgram> program;public: codegen::ControlFlowState control_flow_state;public: JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> entered_yieldable_blocks;public: ByteStringBuilder deferred_output;public: JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> current_function;public: bool inside_defer;public: codegen::CodegenDebugInfo debug_info;public: JaktInternal::DynamicArray<ByteString> namespace_stack;public: size_t fresh_var_counter;public: size_t fresh_label_counter;public: JaktInternal::Optional<ByteString> this_replacement;public: JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences;public: JaktInternal::Set<ids::ModuleId> used_modules;public: ByteString current_error_handler() const;
public: ByteString fresh_var();
public: ByteString fresh_label();
public: JaktInternal::DynamicArray<ids::ModuleId> topologically_sort_modules() const;
public: static ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> generate(NonnullRefPtr<compiler::Compiler> const compiler, NonnullRefPtr<types::CheckedProgram> const program, bool const debug_info);
public: static JaktInternal::DynamicArray<ids::ModuleId> get_topologically_sorted_modules(JaktInternal::DynamicArray<ids::ModuleId> const& all_sorted_modules, JaktInternal::Set<ids::ModuleId> const& dependencies);
public: ErrorOr<JaktInternal::DynamicArray<ids::ModuleId>> capturing_modules(JaktInternal::DynamicArray<ids::ModuleId> const& all_sorted_modules, NonnullRefPtr<types::Module> const module, Function<ErrorOr<void>(codegen::CodeGenerator&, NonnullRefPtr<types::Module>, ByteStringBuilder&)> const& gen, ByteStringBuilder& output);
public: ErrorOr<void> postorder_traversal(ids::TypeId const type_id, JaktInternal::Set<ids::TypeId> visited, JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph, JaktInternal::DynamicArray<ids::TypeId> output) const;
public: ErrorOr<JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>>> produce_codegen_dependency_graph(NonnullRefPtr<types::Scope> const scope) const;
public: JaktInternal::DynamicArray<ids::TypeId> extract_dependencies_from(ids::TypeId const type_id, JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph, bool const top_level) const;
public: JaktInternal::DynamicArray<ids::TypeId> extract_dependencies_from_enum(ids::EnumId const enum_id, JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph, bool const top_level) const;
public: JaktInternal::DynamicArray<ids::TypeId> extract_dependencies_from_struct(ids::StructId const struct_id, JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph, bool const top_level, JaktInternal::DynamicArray<ids::TypeId> const args) const;
public: bool is_full_respecialization(JaktInternal::DynamicArray<ids::TypeId> const type_args) const;
public: ErrorOr<void> codegen_namespace_specialization(ids::FunctionId const function_id, JaktInternal::Optional<ids::TypeId> const containing_struct, NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module, bool const define_pass, ByteStringBuilder& output);
public: ErrorOr<void> codegen_namespace_specializations(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module, ByteStringBuilder& output);
public: ErrorOr<void> codegen_namespace_forward(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module, ByteStringBuilder& output);
public: ErrorOr<void> codegen_namespace(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module, ByteStringBuilder& output);
public: ErrorOr<void> codegen_namespace_predecl(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::Module> const current_module, ByteStringBuilder& output);
public: ErrorOr<void> codegen_template_parameter_names(JaktInternal::DynamicArray<types::FunctionGenericParameter> const parameters, JaktInternal::DynamicArray<ByteString>& names, ByteStringBuilder& output);
public: ErrorOr<void> codegen_template_parameter_names(JaktInternal::DynamicArray<types::FunctionGenericParameter> const parameters, ByteStringBuilder& output);
public: ErrorOr<void> codegen_template_parameter_names(JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters, JaktInternal::DynamicArray<ByteString>& names, ByteStringBuilder& output);
public: ErrorOr<void> codegen_template_parameter_names(JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters, ByteStringBuilder& output);
public: ErrorOr<void> codegen_template_parameter_names(JaktInternal::DynamicArray<ids::TypeId> const parameters, JaktInternal::DynamicArray<ByteString>& names, ByteStringBuilder& output);
public: ErrorOr<void> codegen_function_generic_parameters(NonnullRefPtr<types::CheckedFunction> const function, ByteStringBuilder& output);
public: ErrorOr<void> codegen_function_predecl(NonnullRefPtr<types::CheckedFunction> const function, bool const as_method, bool const allow_generics, ByteStringBuilder& output);
public: ErrorOr<void> codegen_struct_predecl(types::CheckedStruct const struct_, ByteStringBuilder& output);
public: ErrorOr<void> codegen_struct(types::CheckedStruct const struct_, ByteStringBuilder& output);
public: ErrorOr<void> codegen_enum_predecl(types::CheckedEnum const enum_, ByteStringBuilder& output);
public: ErrorOr<void> codegen_enum(types::CheckedEnum const enum_, ByteStringBuilder& output);
public: static void codegen_enum_constructor_decl(ByteString const enum_name, ByteString const variant_name, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const variant_fields, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields, bool const is_inline, ByteString const ctor_result_type, ByteStringBuilder& output);
public: void codegen_for_enum_variants(types::CheckedEnum const& enum_, Function<ByteString(ByteString)> const& stmt_fmt, ByteString const index_expr, ByteStringBuilder& builder) const;
public: ByteString codegen_enum_assignment_body(types::CheckedEnum const enum_, bool const is_constructor, bool const use_move) const;
public: void codegen_enum_constructors(types::CheckedEnum const enum_, bool const is_inside_struct, JaktInternal::Optional<ByteString> const generic_parameter_list, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const variant_field_list, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields, ByteStringBuilder& output) const;
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>>> codegen_enum_field_lists(types::CheckedEnum const enum_);
public: JaktInternal::Optional<ByteString> destructor_name(ids::TypeId const id) const;
public: static ByteString enum_constructor_result_type(types::CheckedEnum const enum_, JaktInternal::Optional<ByteString> const generic_parameter_list);
public: void codegen_enum_destroy_variant(types::CheckedEnum const enum_, ByteStringBuilder& output) const;
public: void codegen_enum_destructor_body(types::CheckedEnum const enum_, ByteStringBuilder& output) const;
public: ErrorOr<void> codegen_debug_description_getter(types::CheckedStruct const struct_, bool const is_inline, ByteStringBuilder& output);
public: ErrorOr<void> codegen_enum_debug_description_getter(types::CheckedEnum const enum_, bool const is_inline, ByteStringBuilder& output);
public: void codegen_ak_formatter(ByteString const name, JaktInternal::DynamicArray<ByteString> const generic_parameter_names, ByteString const template_args, ByteStringBuilder& output);
public: ErrorOr<void> codegen_expression_and_deref_if_generic_and_needed(NonnullRefPtr<typename types::CheckedExpression> const expression, ByteStringBuilder& output);
public: ErrorOr<void> codegen_expression(NonnullRefPtr<typename types::CheckedExpression> const expression, ByteStringBuilder& output);
public: ErrorOr<void> codegen_match(NonnullRefPtr<typename types::CheckedExpression> const expr, JaktInternal::DynamicArray<types::CheckedMatchCase> const match_cases, ids::TypeId const type_id, bool const all_variants_constant, ByteStringBuilder& output);
public: ErrorOr<void> codegen_generic_match(NonnullRefPtr<typename types::CheckedExpression> const expr, JaktInternal::DynamicArray<types::CheckedMatchCase> const cases, ids::TypeId const return_type_id, ByteString const cpp_match_result_type, bool const all_variants_constant, ByteStringBuilder& output);
public: ErrorOr<void> codegen_enum_match(types::CheckedEnum const enum_, NonnullRefPtr<typename types::CheckedExpression> const expr, JaktInternal::DynamicArray<types::CheckedMatchCase> const match_cases, ids::TypeId const type_id, ByteString const cpp_match_result_type, bool const all_variants_constant, ByteStringBuilder& output);
public: ErrorOr<void> codegen_match_body(types::CheckedMatchBody const body, ids::TypeId const return_type_id, ByteStringBuilder& output);
public: ErrorOr<ByteString> codegen_function_return_type(NonnullRefPtr<types::CheckedFunction> const function);
public: ErrorOr<void> codegen_binary_expression(NonnullRefPtr<typename types::CheckedExpression> const expression, ids::TypeId const type_id, NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, types::CheckedBinaryOperator const op, ByteStringBuilder& output);
public: ErrorOr<void> codegen_unchecked_binary_op(NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, parser::BinaryOperator const op, ids::TypeId const type_id, ByteStringBuilder& output);
public: ErrorOr<void> codegen_checked_binary_op(NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, parser::BinaryOperator const op, ids::TypeId const type_id, ByteStringBuilder& output);
public: ErrorOr<void> codegen_unchecked_binary_op_assignment(NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, parser::BinaryOperator const op, ids::TypeId const type_id, ByteStringBuilder& output);
public: ErrorOr<void> codegen_checked_binary_op_assignment(NonnullRefPtr<typename types::CheckedExpression> const lhs, NonnullRefPtr<typename types::CheckedExpression> const rhs, parser::BinaryOperator const op, ids::TypeId const type_id, ByteStringBuilder& output);
public: ErrorOr<void> codegen_method_call(NonnullRefPtr<typename types::CheckedExpression> const expr, types::CheckedCall const call, bool const is_optional, ByteStringBuilder& output);
public: ErrorOr<void> codegen_call(types::CheckedCall const call, ByteStringBuilder& output);
public: ErrorOr<ByteString> codegen_namespace_path(types::CheckedCall const call);
public: ErrorOr<void> codegen_block(types::CheckedBlock const block, ByteStringBuilder& output);
public: ErrorOr<void> codegen_statement(NonnullRefPtr<typename types::CheckedStatement> const statement, ByteStringBuilder& output);
public: ErrorOr<ByteString> codegen_type(ids::TypeId const type_id);
public: ErrorOr<ByteString> codegen_type_possibly_as_namespace(ids::TypeId const type_id, bool const as_namespace);
public: ErrorOr<ByteString> codegen_generic_type_instance(ids::StructId const id, JaktInternal::DynamicArray<ids::TypeId> const args, bool const as_namespace);
public: ErrorOr<void> codegen_generic_enum_instance(ids::EnumId const id, JaktInternal::DynamicArray<ids::TypeId> const args, bool const as_namespace, ByteStringBuilder& output);
public: ErrorOr<ByteString> codegen_namespace_qualifier(ids::ScopeId const scope_id, bool const skip_current, JaktInternal::Optional<ByteString> const possible_constructor_name, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> const generic_mappings);
public: ids::TypeId map_type(ids::TypeId const type_id) const;
public: ErrorOr<void> codegen_function(NonnullRefPtr<types::CheckedFunction> const function, bool const as_method, ByteStringBuilder& output);
public: ErrorOr<ByteString> codegen_struct_type(ids::StructId const id, bool const as_namespace);
public: ErrorOr<ByteString> codegen_enum_type(ids::EnumId const id, bool const as_namespace);
public: ErrorOr<ByteString> codegen_destructor_predecl(types::CheckedStruct const& struct_);
public: ErrorOr<void> codegen_destructor(types::CheckedStruct const& struct_, NonnullRefPtr<types::CheckedFunction> const& function, bool const is_inline, ByteStringBuilder& output);
public: ErrorOr<void> codegen_constructor_predecl(NonnullRefPtr<types::CheckedFunction> const function, ByteStringBuilder& output);
public: ErrorOr<void> codegen_constructor(NonnullRefPtr<types::CheckedFunction> const function, bool const is_inline, ByteStringBuilder& output);
public: ErrorOr<void> codegen_function_in_namespace(NonnullRefPtr<types::CheckedFunction> const function, JaktInternal::Optional<ids::TypeId> const containing_struct, bool const as_method, bool const skip_template, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const explicit_generic_instantiation, ByteStringBuilder& output);
public: ErrorOr<void> codegen_lambda_block(bool const can_throw, types::CheckedBlock const block, ids::TypeId const return_type_id, ByteStringBuilder& output);
public: CodeGenerator(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, codegen::ControlFlowState a_control_flow_state, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> a_entered_yieldable_blocks, ByteStringBuilder a_deferred_output, JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> a_current_function, bool a_inside_defer, codegen::CodegenDebugInfo a_debug_info, JaktInternal::DynamicArray<ByteString> a_namespace_stack, size_t a_fresh_var_counter, size_t a_fresh_label_counter, JaktInternal::Optional<ByteString> a_this_replacement, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> a_generic_inferences, JaktInternal::Set<ids::ModuleId> a_used_modules);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::AllowedControlExits> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::AllowedControlExits const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::ControlFlowState> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::ControlFlowState const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::LineSpan> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::LineSpan const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::CodegenDebugInfo> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::CodegenDebugInfo const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::codegen::CodeGenerator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::codegen::CodeGenerator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
