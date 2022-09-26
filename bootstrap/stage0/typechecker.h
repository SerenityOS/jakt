#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "types.h"
#include "types.h"
#include "utility.h"
#include "compiler.h"
#include "interpreter.h"
namespace Jakt {
namespace typechecker {
struct Typechecker {
  public:
NonnullRefPtr<compiler::Compiler> compiler;NonnullRefPtr<types::CheckedProgram> program;types::ModuleId current_module_id;JaktInternal::Optional<types::TypeId> current_struct_type_id;JaktInternal::Optional<types::FunctionId> current_function_id;bool inside_defer;size_t checkidx;bool ignore_errors;bool dump_type_hints;bool dump_try_hints;u64 lambda_count;types::GenericInferences generic_inferences;bool is_floating(const types::TypeId type_id) const;
ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>>> typecheck_match_body(const parser::ParsedMatchBody body, const types::ScopeId scope_id, const types::SafetyMode safety_mode, types::GenericInferences& generic_inferences, const JaktInternal::Optional<types::TypeId> final_result_type, const utility::Span span);
ErrorOr<void> typecheck_namespace_predecl(const parser::ParsedNamespace parsed_namespace, const types::ScopeId scope_id);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_set(const JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> values, const utility::Span span, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> type_hint);
bool is_struct(const types::TypeId type_id) const;
bool is_integer(const types::TypeId type_id) const;
ErrorOr<void> dump_try_hint(const utility::Span span) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_call(const parser::ParsedCall call, const types::ScopeId caller_scope_id, const utility::Span span, const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> this_expr, const JaktInternal::Optional<types::StructOrEnumId> parent_id, const types::SafetyMode safety_mode, JaktInternal::Optional<types::TypeId> type_hint, const bool must_be_enum_constructor);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_guard(const NonnullRefPtr<parser::ParsedExpression> expr, const parser::ParsedBlock else_block, const parser::ParsedBlock remaining_code, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<bool> add_comptime_binding_to_scope(const types::ScopeId scope_id, const String name, const types::Value value, const utility::Span span);
ErrorOr<types::CheckedVisibility> typecheck_visibility(const parser::Visibility visibility, const types::ScopeId scope_id);
ErrorOr<String> type_name(const types::TypeId type_id) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_namespaced_var_or_simple_enum_constructor_call(const String name, const JaktInternal::Array<String> namespace_, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> type_hint, const utility::Span span);
NonnullRefPtr<types::Module> current_module() const;
ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>>> typecheck_match_variant(const parser::ParsedMatchCase case_, const types::TypeId subject_type_id, const size_t variant_index, const JaktInternal::Optional<types::TypeId> final_result_type, const types::CheckedEnumVariant variant, const JaktInternal::Array<parser::EnumVariantPatternArgument> variant_arguments, const utility::Span arguments_span, const types::ScopeId scope_id, const types::SafetyMode safety_mode);
ErrorOr<void> error_with_hint(const String message, const utility::Span span, const String hint, const utility::Span hint_span);
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>>> find_type_scope(const types::ScopeId scope_id, const String name) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_indexed_tuple(const NonnullRefPtr<parser::ParsedExpression> expr, const size_t index, const types::ScopeId scope_id, const bool is_optional, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<types::TypeId> find_or_add_type_id(const NonnullRefPtr<types::Type> type);
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>>> find_namespace_in_scope(const types::ScopeId scope_id, const String name) const;
ErrorOr<types::TypeId> typecheck_typename(const NonnullRefPtr<parser::ParsedType> parsed_type, const types::ScopeId scope_id, const JaktInternal::Optional<String> name);
ErrorOr<void> typecheck_enum_predecl(const parser::ParsedRecord parsed_record, const types::EnumId enum_id, const types::ScopeId scope_id);
ErrorOr<JaktInternal::Optional<types::CheckedEnumVariant>> get_enum_variant(const types::CheckedEnum enum_, const String variant_name);
types::ScopeId root_scope_id() const;
ErrorOr<JaktInternal::Optional<types::FunctionId>> find_function_in_scope(const types::ScopeId parent_scope_id, const String function_name) const;
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_loop(const parser::ParsedBlock parsed_block, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_defer(const NonnullRefPtr<parser::ParsedStatement> statement, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<void> error(const String message, const utility::Span span);
ErrorOr<void> typecheck_module(const parser::ParsedNamespace parsed_namespace, const types::ScopeId scope_id);
ErrorOr<void> typecheck_namespace_declarations(const parser::ParsedNamespace parsed_namespace, const types::ScopeId scope_id);
ErrorOr<types::TypeId> substitute_typevars_in_type(const types::TypeId type_id, const types::GenericInferences generic_inferences);
ErrorOr<types::StructId> find_struct_in_prelude(const String name) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> cast_to_underlying(const NonnullRefPtr<parser::ParsedExpression> expr, const types::ScopeId scope_id, const NonnullRefPtr<parser::ParsedType> parsed_type);
ErrorOr<void> typecheck_module_import(const parser::ParsedModuleImport import_, const types::ScopeId scope_id);
ErrorOr<types::TypeId> typecheck_binary_operation(const NonnullRefPtr<types::CheckedExpression> checked_lhs, const parser::BinaryOperator op, const NonnullRefPtr<types::CheckedExpression> checked_rhs, const types::ScopeId scope_id, const utility::Span span);
ErrorOr<JaktInternal::Optional<types::StructId>> find_struct_in_scope(const types::ScopeId scope_id, const String name) const;
ErrorOr<void> check_method_access(const types::ScopeId accessor, const types::ScopeId accessee, const NonnullRefPtr<types::CheckedFunction> method, const utility::Span span);
ErrorOr<types::CheckedBlock> typecheck_block(const parser::ParsedBlock parsed_block, const types::ScopeId parent_scope_id, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> yield_type_hint);
ErrorOr<JaktInternal::Optional<types::TypeId>> find_type_in_scope(const types::ScopeId scope_id, const String name) const;
ErrorOr<void> typecheck_function(const parser::ParsedFunction parsed_function, const types::ScopeId parent_scope_id);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_inline_cpp(const parser::ParsedBlock block, const utility::Span span, const types::SafetyMode safety_mode);
ErrorOr<bool> check_restricted_access(const types::ScopeId accessor, const String accessee_kind, const types::ScopeId accessee, const String name, const JaktInternal::Array<NonnullRefPtr<types::MaybeResolvedScope>> whitelist, const utility::Span span);
ErrorOr<JaktInternal::Array<types::StructId>> struct_inheritance_chain(const types::StructId struct_id) const;
ErrorOr<bool> add_function_to_scope(const types::ScopeId parent_scope_id, const String name, const types::FunctionId function_id, const utility::Span span);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_while(const NonnullRefPtr<parser::ParsedExpression> condition, const parser::ParsedBlock block, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_expression_and_dereference_if_needed(const NonnullRefPtr<parser::ParsedExpression> expr, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> type_hint, const utility::Span span);
ErrorOr<NonnullRefPtr<utility::FilePath>> get_root_path() const;
ErrorOr<bool> scope_can_access(const types::ScopeId accessor, const types::ScopeId accessee) const;
ErrorOr<void> typecheck_struct_fields(const parser::ParsedRecord record, const types::StructId struct_id);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_expression(const NonnullRefPtr<parser::ParsedExpression> expr, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> type_hint);
ErrorOr<void> dump_type_hint(const types::TypeId type_id, const utility::Span span) const;
Typechecker(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, types::ModuleId a_current_module_id, JaktInternal::Optional<types::TypeId> a_current_struct_type_id, JaktInternal::Optional<types::FunctionId> a_current_function_id, bool a_inside_defer, size_t a_checkidx, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, types::GenericInferences a_generic_inferences);

bool is_subclass_of(const types::TypeId ancestor_type_id, const types::TypeId child_type_id) const;
ErrorOr<types::ModuleId> create_module(const String name, const bool is_root, const JaktInternal::Optional<String> path);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_block_statement(const parser::ParsedBlock parsed_block, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<JaktInternal::Optional<types::FieldRecord>> lookup_struct_field(const types::StructId struct_id, const String name) const;
ErrorOr<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,parser::ParsedBlock,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>>> expand_context_for_bindings(const NonnullRefPtr<parser::ParsedExpression> condition, const JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> acc, const parser::ParsedBlock then_block, const JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> else_statement, const utility::Span span);
ErrorOr<JaktInternal::Optional<types::TypeId>> unify(const types::TypeId lhs, const utility::Span lhs_span, const types::TypeId rhs, const utility::Span rhs_span);
ErrorOr<types::TypeId> find_type_in_prelude(const String name) const;
bool is_numeric(const types::TypeId type_id) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_array(const types::ScopeId scope_id, const JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> values, const JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> fill_size, const utility::Span span, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> type_hint);
ErrorOr<bool> add_var_to_scope(const types::ScopeId scope_id, const String name, const types::VarId var_id, const utility::Span span);
ErrorOr<NonnullRefPtr<types::Scope>> get_scope(const types::ScopeId id) const;
ErrorOr<bool> check_types_for_compat(const types::TypeId lhs_type_id, const types::TypeId rhs_type_id, types::GenericInferences& generic_inferences, const utility::Span span);
ErrorOr<JaktInternal::Optional<types::CheckedVariable>> find_var_in_scope(const types::ScopeId scope_id, const String var) const;
types::CheckedStruct get_struct(const types::StructId id) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_lambda(const JaktInternal::Array<parser::ParsedCapture> captures, const JaktInternal::Array<parser::ParsedParameter> params, const bool can_throw, const NonnullRefPtr<parser::ParsedType> return_type, const parser::ParsedBlock block, const utility::Span span, const types::ScopeId scope_id, const types::SafetyMode safety_mode);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_try(const NonnullRefPtr<parser::ParsedExpression> expr, const JaktInternal::Optional<parser::ParsedBlock> catch_block, const JaktInternal::Optional<String> catch_name, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span, const JaktInternal::Optional<types::TypeId> type_hint);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_return(const JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> expr, const utility::Span span, const types::ScopeId scope_id, const types::SafetyMode safety_mode);
ErrorOr<void> include_prelude();
ErrorOr<void> typecheck_namespace_fields(const parser::ParsedNamespace parsed_namespace, const types::ScopeId scope_id);
ErrorOr<void> typecheck_and_specialize_generic_function(const types::FunctionId function_id, const JaktInternal::Array<types::TypeId> generic_arguments, const types::ScopeId parent_scope_id, const JaktInternal::Optional<types::TypeId> this_type_id, const types::GenericInferences generic_substitutions);
ErrorOr<JaktInternal::Optional<parser::ParsedNamespace>> lex_and_parse_file_contents(const utility::FileId file_id);
types::BlockControlFlow statement_control_flow(const NonnullRefPtr<types::CheckedStatement> statement) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_unary_operation(const NonnullRefPtr<types::CheckedExpression> checked_expr, const types::CheckedUnaryOperator checked_op, const utility::Span span, const types::ScopeId scope_id, const types::SafetyMode safety_mode);
ErrorOr<types::TypeId> resolve_type_var(const types::TypeId type_var_type_id, const types::ScopeId scope_id) const;
NonnullRefPtr<types::CheckedFunction> get_function(const types::FunctionId id) const;
ErrorOr<void> typecheck_struct_predecl(const parser::ParsedRecord parsed_record, const types::StructId struct_id, const types::ScopeId scope_id);
ErrorOr<void> typecheck_enum_predecl_initial(const parser::ParsedRecord parsed_record, const size_t enum_index, const size_t module_enum_len, const types::ScopeId scope_id);
NonnullRefPtr<types::Type> get_type(const types::TypeId id) const;
ErrorOr<void> typecheck_extern_import(const parser::ParsedExternImport import_, const types::ScopeId scope_id);
ErrorOr<void> check_member_access(const types::ScopeId accessor, const types::ScopeId accessee, const types::CheckedVariable member, const utility::Span span);
ErrorOr<void> typecheck_method(const parser::ParsedFunction func, const types::StructOrEnumId parent_id);
ErrorOr<bool> add_struct_to_scope(const types::ScopeId scope_id, const String name, const types::StructId struct_id, const utility::Span span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> infer_unsigned_int(const u64 val, const utility::Span span, const JaktInternal::Optional<types::TypeId> type_hint);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_unary_negate(const NonnullRefPtr<types::CheckedExpression> expr, const utility::Span span, const types::TypeId type_id);
ErrorOr<JaktInternal::Optional<types::FunctionId>> resolve_call(const parser::ParsedCall call, JaktInternal::Array<types::ResolvedNamespace> namespaces, const utility::Span span, const types::ScopeId scope_id, const bool must_be_enum_constructor, const bool ignore_errors);
static ErrorOr<NonnullRefPtr<types::CheckedProgram>> typecheck(NonnullRefPtr<compiler::Compiler> compiler, const parser::ParsedNamespace parsed_namespace);
ErrorOr<bool> add_enum_to_scope(const types::ScopeId scope_id, const String name, const types::EnumId enum_id, const utility::Span span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_dictionary(const JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>>> values, const utility::Span span, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> type_hint);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_if(const NonnullRefPtr<parser::ParsedExpression> condition, const parser::ParsedBlock then_block, const JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> else_statement, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<types::TypeId> unify_with_type(const types::TypeId found_type, const JaktInternal::Optional<types::TypeId> expected_type, const utility::Span span);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_throw(const NonnullRefPtr<parser::ParsedExpression> expr, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_destructuring_assignment(const JaktInternal::Array<parser::ParsedVarDecl> vars, const NonnullRefPtr<parser::ParsedStatement> var_decl, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
types::ScopeId prelude_scope_id() const;
ErrorOr<bool> add_type_to_scope(const types::ScopeId scope_id, const String type_name, const types::TypeId type_id, const utility::Span span);
ErrorOr<types::ScopeId> create_scope(const JaktInternal::Optional<types::ScopeId> parent_scope_id, const bool can_throw, const String debug_name);
ErrorOr<bool> validate_argument_label(const types::CheckedParameter param, const String label, const utility::Span span, const NonnullRefPtr<parser::ParsedExpression> expr, const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> default_value);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> infer_signed_int(const i64 val, const utility::Span span, const JaktInternal::Optional<types::TypeId> type_hint);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_indexed_struct(const NonnullRefPtr<parser::ParsedExpression> expr, const String field, const types::ScopeId scope_id, const bool is_optional, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<void> typecheck_function_predecl(const parser::ParsedFunction parsed_function, const types::ScopeId parent_scope_id, const JaktInternal::Optional<types::TypeId> this_arg_type_id, JaktInternal::Optional<NonnullRefPtr<types::FunctionGenerics>> generics);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_try_block(const NonnullRefPtr<parser::ParsedStatement> stmt, const String error_name, const utility::Span error_span, const parser::ParsedBlock catch_block, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<types::CheckedUnaryOperator> typecheck_is_enum_variant(const NonnullRefPtr<types::CheckedExpression> checked_expr, const NonnullRefPtr<parser::ParsedType> inner, const JaktInternal::Array<parser::EnumVariantPatternArgument> bindings, const types::ScopeId scope_id);
types::CheckedVariable get_variable(const types::VarId id) const;
bool is_class(const types::TypeId type_id) const;
types::TypeId infer_function_return_type(const types::CheckedBlock block) const;
ErrorOr<JaktInternal::Optional<types::Value>> find_comptime_binding_in_scope(const types::ScopeId scope_id, const String name) const;
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_statement(const NonnullRefPtr<parser::ParsedStatement> statement, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> type_hint);
ErrorOr<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>>>> resolve_default_params(const JaktInternal::Array<types::CheckedParameter> params, const JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> args, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const size_t arg_offset, const utility::Span span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_generic_arguments_method_call(const NonnullRefPtr<types::CheckedExpression> checked_expr, const parser::ParsedCall call, const types::ScopeId scope_id, const utility::Span span, const bool is_optional, const types::SafetyMode safety_mode);
ErrorOr<void> check_that_type_doesnt_contain_reference(const types::TypeId type_id, const utility::Span span);
types::CheckedEnum get_enum(const types::EnumId id) const;
ErrorOr<void> typecheck_namespace_function_predecl(const parser::ParsedNamespace parsed_namespace, const types::ScopeId scope_id);
ErrorOr<void> typecheck_enum_constructor(const parser::ParsedRecord record, const types::EnumId enum_id, const types::ScopeId parent_scope_id);
ErrorOr<void> typecheck_struct_constructor(const parser::ParsedRecord parsed_record, const types::StructId struct_id, const types::ScopeId scope_id);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_var_decl(const parser::ParsedVarDecl var, const NonnullRefPtr<parser::ParsedExpression> init, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>>> typecheck_enum_variant_bindings(const types::CheckedEnumVariant variant, const JaktInternal::Array<parser::EnumVariantPatternArgument> bindings, const utility::Span span);
ErrorOr<void> typecheck_namespace_imports(const parser::ParsedNamespace parsed_namespace, const types::ScopeId scope_id);
ErrorOr<void> typecheck_enum(const parser::ParsedRecord record, const types::EnumId enum_id, const types::ScopeId parent_scope_id);
ErrorOr<types::CheckedParameter> typecheck_parameter(const parser::ParsedParameter parameter, const types::ScopeId scope_id, const bool first, const JaktInternal::Optional<types::TypeId> this_arg_type_id, const JaktInternal::Optional<types::ScopeId> check_scope);
ErrorOr<void> typecheck_struct(const parser::ParsedRecord record, const types::StructId struct_id, const types::ScopeId parent_scope_id);
ErrorOr<void> typecheck_struct_predecl_initial(const parser::ParsedRecord parsed_record, const size_t struct_index, const size_t module_struct_len, const types::ScopeId scope_id);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_match(const NonnullRefPtr<parser::ParsedExpression> expr, const JaktInternal::Array<parser::ParsedMatchCase> cases, const utility::Span span, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const JaktInternal::Optional<types::TypeId> type_hint);
ErrorOr<types::TypeId> typecheck_generic_resolved_type(const String name, const JaktInternal::Array<types::TypeId> checked_inner_types, const types::ScopeId scope_id, const utility::Span span);
types::BlockControlFlow maybe_statement_control_flow(const JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> statement, const types::BlockControlFlow other_branch) const;
ErrorOr<void> typecheck_jakt_main(const parser::ParsedFunction parsed_function);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_for(const String iterator_name, const utility::Span name_span, const NonnullRefPtr<parser::ParsedExpression> range, const parser::ParsedBlock block, const types::ScopeId scope_id, const types::SafetyMode safety_mode, const utility::Span span);
ErrorOr<void> typecheck_namespace_constructors(const parser::ParsedNamespace parsed_namespace, const types::ScopeId scope_id);
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<typechecker::Typechecker> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, typechecker::Typechecker const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
