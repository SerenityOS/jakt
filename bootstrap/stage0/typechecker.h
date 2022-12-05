#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "types.h"
#include "types.h"
#include "utility.h"
#include "path.h"
#include "compiler.h"
#include "interpreter.h"
namespace Jakt {
namespace typechecker {
struct AlreadyImplementedFor {
  public:
String trait_name;utility::Span encounter_span;AlreadyImplementedFor(String a_trait_name, utility::Span a_encounter_span);

ErrorOr<String> debug_description() const;
};struct TraitImplCheck {
  public:
JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,types::FunctionId>> missing_methods;JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,utility::Span>> unmatched_signatures;JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,utility::Span>> private_matching_methods;JaktInternal::Dictionary<String,typechecker::AlreadyImplementedFor> already_implemented_for;ErrorOr<void> ensure_capacity(size_t const count);
static ErrorOr<typechecker::TraitImplCheck> make();
TraitImplCheck(JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,types::FunctionId>> a_missing_methods, JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,utility::Span>> a_unmatched_signatures, JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,utility::Span>> a_private_matching_methods, JaktInternal::Dictionary<String,typechecker::AlreadyImplementedFor> a_already_implemented_for);

ErrorOr<void> register_trait(types::TraitId const trait_id, String const trait_name, JaktInternal::Dictionary<String,types::FunctionId> const trait_methods);
ErrorOr<void> register_method(types::TypeId const self_type_id, String const method_name, types::FunctionId const method_id, typechecker::Typechecker& typechecker);
ErrorOr<void> throw_errors(utility::Span const record_decl_span, typechecker::Typechecker& typechecker);
ErrorOr<String> debug_description() const;
};namespace FunctionMatchResult_Details {
struct MatchSuccess {
JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> args;
JaktInternal::Optional<types::TypeId> maybe_this_type_id;
JaktInternal::Dictionary<String,String> used_generic_inferences;
i64 specificity;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
MatchSuccess(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
args{ forward<_MemberT0>(member_0)},
maybe_this_type_id{ forward<_MemberT1>(member_1)},
used_generic_inferences{ forward<_MemberT2>(member_2)},
specificity{ forward<_MemberT3>(member_3)}
{}
};
struct MatchError {
JaktInternal::Array<error::JaktError> errors;
template<typename _MemberT0>
MatchError(_MemberT0&& member_0):
errors{ forward<_MemberT0>(member_0)}
{}
};
}
struct FunctionMatchResult : public Variant<FunctionMatchResult_Details::MatchSuccess, FunctionMatchResult_Details::MatchError> {
using Variant<FunctionMatchResult_Details::MatchSuccess, FunctionMatchResult_Details::MatchError>::Variant;
    using MatchSuccess = FunctionMatchResult_Details::MatchSuccess;
    using MatchError = FunctionMatchResult_Details::MatchError;
ErrorOr<String> debug_description() const;
};
struct Typechecker {
  public:
NonnullRefPtr<compiler::Compiler> compiler;NonnullRefPtr<types::CheckedProgram> program;types::ModuleId current_module_id;JaktInternal::Optional<types::TypeId> current_struct_type_id;JaktInternal::Optional<types::FunctionId> current_function_id;bool inside_defer;size_t checkidx;bool ignore_errors;bool dump_type_hints;bool dump_try_hints;u64 lambda_count;types::GenericInferences generic_inferences;bool is_floating(types::TypeId const type_id) const;
ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>>> typecheck_match_body(parser::ParsedMatchBody const body, types::ScopeId const scope_id, types::SafetyMode const safety_mode, types::GenericInferences& generic_inferences, JaktInternal::Optional<types::TypeId> const final_result_type, utility::Span const span);
ErrorOr<void> typecheck_namespace_predecl(parser::ParsedNamespace const parsed_namespace, types::ScopeId const scope_id);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_set(JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> const values, utility::Span const span, types::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const type_hint);
bool is_struct(types::TypeId const type_id) const;
bool is_integer(types::TypeId const type_id) const;
ErrorOr<void> dump_try_hint(utility::Span const span) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_call(parser::ParsedCall const call, types::ScopeId const caller_scope_id, utility::Span const span, JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const this_expr, JaktInternal::Optional<types::StructOrEnumId> const parent_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> type_hint, bool const must_be_enum_constructor);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_guard(NonnullRefPtr<parser::ParsedExpression> const expr, parser::ParsedBlock const else_block, parser::ParsedBlock const remaining_code, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<bool> add_comptime_binding_to_scope(types::ScopeId const scope_id, String const name, types::Value const value, utility::Span const span);
ErrorOr<bool> add_trait_to_scope(types::ScopeId const scope_id, String const trait_name, types::TraitId const trait_id, utility::Span const span);
ErrorOr<bool> signatures_match(types::TypeId const self_type_id, NonnullRefPtr<types::CheckedFunction> const first, NonnullRefPtr<types::CheckedFunction> const second);
ErrorOr<String> type_name(types::TypeId const type_id) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_namespaced_var_or_simple_enum_constructor_call(String const name, JaktInternal::Array<String> const namespace_, types::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const type_hint, utility::Span const span);
NonnullRefPtr<types::Module> current_module() const;
ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>>> typecheck_match_variant(parser::ParsedMatchCase const case_, types::TypeId const subject_type_id, size_t const variant_index, JaktInternal::Optional<types::TypeId> const final_result_type, types::CheckedEnumVariant const variant, JaktInternal::Array<parser::EnumVariantPatternArgument> const variant_arguments, JaktInternal::Dictionary<String,parser::ParsedPatternDefault> const default_bindings, utility::Span const arguments_span, types::ScopeId const scope_id, types::SafetyMode const safety_mode);
ErrorOr<void> error_with_hint(String const message, utility::Span const span, String const hint, utility::Span const hint_span);
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>>> find_type_scope(types::ScopeId const scope_id, String const name) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_indexed_tuple(NonnullRefPtr<parser::ParsedExpression> const expr, size_t const index, types::ScopeId const scope_id, bool const is_optional, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<types::TypeId> find_or_add_type_id(NonnullRefPtr<types::Type> const type);
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>>> find_namespace_in_scope(types::ScopeId const scope_id, String const name) const;
ErrorOr<types::TypeId> typecheck_typename(NonnullRefPtr<parser::ParsedType> const parsed_type, types::ScopeId const scope_id, JaktInternal::Optional<String> const name);
ErrorOr<void> typecheck_enum_predecl(parser::ParsedRecord const parsed_record, types::EnumId const enum_id, types::ScopeId const scope_id);
ErrorOr<types::ScopeId> create_scope(JaktInternal::Optional<types::ScopeId> const parent_scope_id, bool const can_throw, String const debug_name);
ErrorOr<JaktInternal::Optional<types::CheckedEnumVariant>> get_enum_variant(types::CheckedEnum const enum_, String const variant_name);
types::ScopeId root_scope_id() const;
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_loop(parser::ParsedBlock const parsed_block, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> typecheck_trait(parser::ParsedTrait const parsed_trait, types::TraitId const trait_id, types::ScopeId const scope_id);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_var_decl(parser::ParsedVarDecl const var, NonnullRefPtr<parser::ParsedExpression> const init, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_unary_operation(NonnullRefPtr<types::CheckedExpression> const checked_expr, types::CheckedUnaryOperator const checked_op, utility::Span const span, types::ScopeId const scope_id, types::SafetyMode const safety_mode);
ErrorOr<void> typecheck_module(parser::ParsedNamespace const parsed_namespace, types::ScopeId const scope_id);
ErrorOr<void> typecheck_namespace_declarations(parser::ParsedNamespace const parsed_namespace, types::ScopeId const scope_id);
ErrorOr<JaktInternal::Array<JaktInternal::Array<types::TypeId>>> find_all_implementations_of_trait(types::TypeId const type_id, types::TraitId const trait_id);
ErrorOr<types::TypeId> substitute_typevars_in_type(types::TypeId const type_id, types::GenericInferences const generic_inferences);
ErrorOr<types::StructId> find_struct_in_prelude(String const name) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> cast_to_underlying(NonnullRefPtr<parser::ParsedExpression> const expr, types::ScopeId const scope_id, NonnullRefPtr<parser::ParsedType> const parsed_type);
ErrorOr<void> typecheck_module_import(parser::ParsedModuleImport const import_, types::ScopeId const scope_id);
ErrorOr<types::TypeId> typecheck_binary_operation(NonnullRefPtr<types::CheckedExpression> const checked_lhs, parser::BinaryOperator const op, NonnullRefPtr<types::CheckedExpression> const checked_rhs, types::ScopeId const scope_id, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_dictionary(JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>>> const values, utility::Span const span, types::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const type_hint);
ErrorOr<void> typecheck_struct_default_fields(parser::ParsedRecord const parsed_record, types::StructId const struct_id, types::ScopeId const scope_id);
ErrorOr<bool> implements_trait(types::TypeId const type_id, types::TraitId const trait_id, JaktInternal::Optional<JaktInternal::Array<types::TypeId>> const generic_arguments);
ErrorOr<void> check_method_access(types::ScopeId const accessor, types::ScopeId const accessee, NonnullRefPtr<types::CheckedFunction> const method, utility::Span const span);
ErrorOr<types::CheckedBlock> typecheck_block(parser::ParsedBlock const parsed_block, types::ScopeId const parent_scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const yield_type_hint);
ErrorOr<JaktInternal::Optional<types::TypeId>> find_type_in_scope(types::ScopeId const scope_id, String const name) const;
ErrorOr<void> typecheck_function(parser::ParsedFunction const parsed_function, types::ScopeId const parent_scope_id);
ErrorOr<void> check_type_argument_requirements(types::TypeId const generic_argument, JaktInternal::Array<types::TraitId> const constraints, utility::Span const arg_span);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_inline_cpp(parser::ParsedBlock const block, utility::Span const span, types::SafetyMode const safety_mode);
ErrorOr<void> typecheck_struct_fields(parser::ParsedRecord const record, types::StructId const struct_id);
ErrorOr<bool> check_restricted_access(types::ScopeId const accessor, String const accessee_kind, types::ScopeId const accessee, String const name, JaktInternal::Array<NonnullRefPtr<types::MaybeResolvedScope>> const whitelist, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_throw(NonnullRefPtr<parser::ParsedExpression> const expr, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<JaktInternal::Array<types::StructId>> struct_inheritance_chain(types::StructId const struct_id) const;
ErrorOr<bool> add_function_to_scope(types::ScopeId const parent_scope_id, String const name, JaktInternal::Array<types::FunctionId> const overload_set, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_while(NonnullRefPtr<parser::ParsedExpression> const condition, parser::ParsedBlock const block, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_expression_and_dereference_if_needed(NonnullRefPtr<parser::ParsedExpression> const expr, types::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const type_hint, utility::Span const span);
ErrorOr<path::Path> get_root_path() const;
ErrorOr<bool> scope_can_access(types::ScopeId const accessor, types::ScopeId const accessee) const;
ErrorOr<void> typecheck_enum(parser::ParsedRecord const record, types::EnumId const enum_id, types::ScopeId const parent_scope_id);
ErrorOr<typechecker::FunctionMatchResult> match_function_and_resolve_args(parser::ParsedCall const call, types::ScopeId const caller_scope_id, types::FunctionId const candidate, types::SafetyMode const safety_mode, utility::Span const span, JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const this_expr);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_expression(NonnullRefPtr<parser::ParsedExpression> const expr, types::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const type_hint);
ErrorOr<void> dump_type_hint(types::TypeId const type_id, utility::Span const span) const;
Typechecker(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, types::ModuleId a_current_module_id, JaktInternal::Optional<types::TypeId> a_current_struct_type_id, JaktInternal::Optional<types::FunctionId> a_current_function_id, bool a_inside_defer, size_t a_checkidx, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, types::GenericInferences a_generic_inferences);

ErrorOr<void> typecheck_namespace_default_fields(parser::ParsedNamespace const parsed_namespace, types::ScopeId const scope_id);
bool is_subclass_of(types::TypeId const ancestor_type_id, types::TypeId const child_type_id) const;
ErrorOr<types::ModuleId> create_module(String const name, bool const is_root, JaktInternal::Optional<String> const path);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_defer(NonnullRefPtr<parser::ParsedStatement> const statement, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<JaktInternal::Optional<types::FieldRecord>> lookup_struct_field(types::StructId const struct_id, String const name) const;
ErrorOr<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>>> expand_context_for_bindings(NonnullRefPtr<parser::ParsedExpression> const condition, JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const acc, JaktInternal::Optional<parser::ParsedBlock> const then_block, JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const else_statement, utility::Span const span);
ErrorOr<JaktInternal::Optional<types::TypeId>> unify(types::TypeId const lhs, utility::Span const lhs_span, types::TypeId const rhs, utility::Span const rhs_span);
ErrorOr<types::TypeId> find_type_in_prelude(String const name) const;
bool is_numeric(types::TypeId const type_id) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_array(types::ScopeId const scope_id, JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> const values, JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const fill_size, utility::Span const span, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const type_hint);
ErrorOr<bool> add_var_to_scope(types::ScopeId const scope_id, String const name, types::VarId const var_id, utility::Span const span);
ErrorOr<NonnullRefPtr<types::Scope>> get_scope(types::ScopeId const id) const;
ErrorOr<bool> check_types_for_compat(types::TypeId const lhs_type_id, types::TypeId const rhs_type_id, types::GenericInferences& generic_inferences, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_lambda(JaktInternal::Array<parser::ParsedCapture> const captures, JaktInternal::Array<parser::ParsedParameter> const params, bool const can_throw, bool const is_fat_arrow, NonnullRefPtr<parser::ParsedType> const return_type, parser::ParsedBlock const block, utility::Span const span, types::ScopeId const scope_id, types::SafetyMode const safety_mode);
types::CheckedStruct get_struct(types::StructId const id) const;
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_try(NonnullRefPtr<parser::ParsedExpression> const expr, JaktInternal::Optional<parser::ParsedBlock> const catch_block, JaktInternal::Optional<String> const catch_name, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span, JaktInternal::Optional<types::TypeId> const type_hint);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_return(JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const expr, utility::Span const span, types::ScopeId const scope_id, types::SafetyMode const safety_mode);
ErrorOr<void> include_prelude();
ErrorOr<void> typecheck_namespace_fields(parser::ParsedNamespace const parsed_namespace, types::ScopeId const scope_id);
ErrorOr<void> typecheck_and_specialize_generic_function(types::FunctionId const function_id, JaktInternal::Array<types::TypeId> const generic_arguments, types::ScopeId const parent_scope_id, JaktInternal::Optional<types::TypeId> const this_type_id, types::GenericInferences const generic_substitutions, JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> const type_args, utility::Span const call_span);
ErrorOr<JaktInternal::Optional<parser::ParsedNamespace>> lex_and_parse_file_contents(utility::FileId const file_id);
types::BlockControlFlow statement_control_flow(NonnullRefPtr<types::CheckedStatement> const statement) const;
ErrorOr<void> fill_trait_implementation_list(JaktInternal::Array<parser::ParsedNameWithGenericParameters> const parsed_impl_list, JaktInternal::Dictionary<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>& trait_implementations, types::ScopeId const scope_id, JaktInternal::Optional<types::ScopeId> const trait_name_scope_id_override);
ErrorOr<void> specialize_trait(types::TraitId const trait_id, JaktInternal::Array<types::TypeId> const generic_parameters);
NonnullRefPtr<types::CheckedTrait> get_trait(types::TraitId const id) const;
NonnullRefPtr<types::CheckedFunction> get_function(types::FunctionId const id) const;
ErrorOr<void> typecheck_struct_predecl(parser::ParsedRecord const parsed_record, types::StructId const struct_id, types::ScopeId const scope_id);
ErrorOr<void> typecheck_enum_predecl_initial(parser::ParsedRecord const parsed_record, size_t const enum_index, size_t const module_enum_len, types::ScopeId const scope_id);
NonnullRefPtr<types::Type> get_type(types::TypeId const id) const;
ErrorOr<types::TypeId> resolve_type_var(types::TypeId const type_var_type_id, types::ScopeId const scope_id) const;
ErrorOr<JaktInternal::Optional<types::TraitId>> find_trait_in_scope(types::ScopeId const scope_id, String const name) const;
ErrorOr<void> typecheck_extern_import(parser::ParsedExternImport const import_, types::ScopeId const scope_id);
ErrorOr<void> check_member_access(types::ScopeId const accessor, types::ScopeId const accessee, types::CheckedVariable const member, utility::Span const span);
ErrorOr<JaktInternal::Optional<types::FunctionId>> typecheck_method(parser::ParsedFunction const func, types::StructOrEnumId const parent_id);
ErrorOr<void> error(String const message, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> infer_unsigned_int(u64 const val, utility::Span const span, JaktInternal::Optional<types::TypeId> const type_hint);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_unary_negate(NonnullRefPtr<types::CheckedExpression> const expr, utility::Span const span, types::TypeId const type_id);
ErrorOr<JaktInternal::Array<types::FunctionId>> resolve_call(parser::ParsedCall const call, JaktInternal::Array<types::ResolvedNamespace> namespaces, utility::Span const span, types::ScopeId const scope_id, bool const must_be_enum_constructor);
static ErrorOr<NonnullRefPtr<types::CheckedProgram>> typecheck(NonnullRefPtr<compiler::Compiler> compiler, parser::ParsedNamespace const parsed_namespace);
ErrorOr<bool> add_enum_to_scope(types::ScopeId const scope_id, String const name, types::EnumId const enum_id, utility::Span const span);
ErrorOr<JaktInternal::Optional<types::StructId>> find_struct_in_scope(types::ScopeId const scope_id, String const name) const;
ErrorOr<void> check_implicit_constructor_argument_access(types::ScopeId const caller_scope_id, parser::ParsedCall const call, types::CheckedStruct const struct_);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_block_statement(parser::ParsedBlock const parsed_block, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_if(NonnullRefPtr<parser::ParsedExpression> const condition, parser::ParsedBlock const then_block, JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const else_statement, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<types::TypeId> unify_with_type(types::TypeId const found_type, JaktInternal::Optional<types::TypeId> const expected_type, utility::Span const span);
ErrorOr<void> typecheck_trait_predecl(parser::ParsedTrait const parsed_trait, types::ScopeId const scope_id);
ErrorOr<types::CheckedVisibility> typecheck_visibility(parser::Visibility const visibility, types::ScopeId const scope_id);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_destructuring_assignment(JaktInternal::Array<parser::ParsedVarDecl> const vars, NonnullRefPtr<parser::ParsedStatement> const var_decl, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
types::ScopeId prelude_scope_id() const;
ErrorOr<bool> add_type_to_scope(types::ScopeId const scope_id, String const type_name, types::TypeId const type_id, utility::Span const span);
ErrorOr<JaktInternal::Optional<types::FunctionId>> find_function_matching_signature_in_scope(types::ScopeId const parent_scope_id, parser::ParsedFunction const prototype) const;
ErrorOr<void> map_generic_arguments(types::TypeId const type_id, JaktInternal::Array<types::TypeId> const args);
ErrorOr<bool> validate_argument_label(types::CheckedParameter const param, String const label, utility::Span const span, NonnullRefPtr<parser::ParsedExpression> const expr, JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const default_value);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> infer_signed_int(i64 const val, utility::Span const span, JaktInternal::Optional<types::TypeId> const type_hint);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_indexed_struct(NonnullRefPtr<parser::ParsedExpression> const expr, String const field_name, types::ScopeId const scope_id, bool const is_optional, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> typecheck_function_predecl(parser::ParsedFunction const parsed_function, types::ScopeId const parent_scope_id, JaktInternal::Optional<types::TypeId> const this_arg_type_id, JaktInternal::Optional<NonnullRefPtr<types::FunctionGenerics>> generics);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_try_block(NonnullRefPtr<parser::ParsedStatement> const stmt, String const error_name, utility::Span const error_span, parser::ParsedBlock const catch_block, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<types::CheckedUnaryOperator> typecheck_is_enum_variant(NonnullRefPtr<types::CheckedExpression> const checked_expr, NonnullRefPtr<parser::ParsedType> const inner, JaktInternal::Array<parser::EnumVariantPatternArgument> const bindings, types::ScopeId const scope_id);
types::CheckedVariable get_variable(types::VarId const id) const;
bool is_class(types::TypeId const type_id) const;
types::TypeId infer_function_return_type(types::CheckedBlock const block) const;
ErrorOr<JaktInternal::Optional<types::Value>> find_comptime_binding_in_scope(types::ScopeId const scope_id, String const name) const;
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_statement(NonnullRefPtr<parser::ParsedStatement> const statement, types::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const type_hint);
ErrorOr<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>>>> resolve_default_params(JaktInternal::Array<types::CheckedParameter> const params, JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> const args, types::ScopeId const scope_id, types::SafetyMode const safety_mode, size_t const arg_offset, utility::Span const span);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_generic_arguments_method_call(NonnullRefPtr<types::CheckedExpression> const checked_expr, parser::ParsedCall const call, types::ScopeId const scope_id, utility::Span const span, bool const is_optional, types::SafetyMode const safety_mode);
ErrorOr<void> check_that_type_doesnt_contain_reference(types::TypeId const type_id, utility::Span const span);
types::CheckedEnum get_enum(types::EnumId const id) const;
ErrorOr<void> typecheck_namespace_function_predecl(parser::ParsedNamespace const parsed_namespace, types::ScopeId const scope_id);
ErrorOr<void> typecheck_enum_constructor(parser::ParsedRecord const record, types::EnumId const enum_id, types::ScopeId const parent_scope_id);
ErrorOr<void> typecheck_struct_constructor(parser::ParsedRecord const parsed_record, types::StructId const struct_id, types::ScopeId const scope_id);
ErrorOr<types::CheckedParameter> typecheck_parameter(parser::ParsedParameter const parameter, types::ScopeId const scope_id, bool const first, JaktInternal::Optional<types::TypeId> const this_arg_type_id, JaktInternal::Optional<types::ScopeId> const check_scope);
ErrorOr<JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>>> typecheck_enum_variant_bindings(types::CheckedEnumVariant const variant, JaktInternal::Array<parser::EnumVariantPatternArgument> const bindings, utility::Span const span);
ErrorOr<void> typecheck_namespace_imports(parser::ParsedNamespace const parsed_namespace, types::ScopeId const scope_id);
ErrorOr<JaktInternal::Optional<JaktInternal::Array<types::FunctionId>>> find_functions_with_name_in_scope(types::ScopeId const parent_scope_id, String const function_name) const;
ErrorOr<JaktInternal::Optional<types::CheckedVariable>> find_var_in_scope(types::ScopeId const scope_id, String const var) const;
ErrorOr<void> typecheck_struct(parser::ParsedRecord const record, types::StructId const struct_id, types::ScopeId const parent_scope_id);
ErrorOr<void> typecheck_struct_predecl_initial(parser::ParsedRecord const parsed_record, size_t const struct_index, size_t const module_struct_len, types::ScopeId const scope_id);
ErrorOr<NonnullRefPtr<types::CheckedExpression>> typecheck_match(NonnullRefPtr<parser::ParsedExpression> const expr, JaktInternal::Array<parser::ParsedMatchCase> const cases, utility::Span const span, types::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<types::TypeId> const type_hint);
ErrorOr<types::TypeId> typecheck_generic_resolved_type(String const name, JaktInternal::Array<types::TypeId> const checked_inner_types, types::ScopeId const scope_id, utility::Span const span);
types::BlockControlFlow maybe_statement_control_flow(JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> const statement, types::BlockControlFlow const other_branch) const;
ErrorOr<void> typecheck_jakt_main(parser::ParsedFunction const parsed_function, types::ScopeId const parent_scope_id);
ErrorOr<NonnullRefPtr<types::CheckedStatement>> typecheck_for(String const iterator_name, utility::Span const name_span, NonnullRefPtr<parser::ParsedExpression> const range, parser::ParsedBlock const block, types::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> typecheck_namespace_constructors(parser::ParsedNamespace const parsed_namespace, types::ScopeId const scope_id);
ErrorOr<bool> add_struct_to_scope(types::ScopeId const scope_id, String const name, types::StructId const struct_id, utility::Span const span);
ErrorOr<void> fill_trait_requirements(JaktInternal::Array<parser::ParsedNameWithGenericParameters> const names, JaktInternal::Array<types::TraitId>& trait_requirements, types::ScopeId const scope_id);
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<typechecker::AlreadyImplementedFor> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, typechecker::AlreadyImplementedFor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<typechecker::TraitImplCheck> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, typechecker::TraitImplCheck const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<typechecker::FunctionMatchResult> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, typechecker::FunctionMatchResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<typechecker::Typechecker> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, typechecker::Typechecker const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
