#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "types.h"
#include "types.h"
#include "utility.h"
#include "jakt__path.h"
#include "compiler.h"
#include "interpreter.h"
namespace Jakt {
namespace typechecker {
struct TraitImplementationDescriptor {
  public:
ids::TraitId trait_id;DeprecatedString trait_name;JaktInternal::DynamicArray<ids::TypeId> implemented_type_args;TraitImplementationDescriptor(ids::TraitId a_trait_id, DeprecatedString a_trait_name, JaktInternal::DynamicArray<ids::TypeId> a_implemented_type_args);

ErrorOr<DeprecatedString> debug_description() const;
};struct TraitImplCheck {
  public:
JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<DeprecatedString,ids::FunctionId>> missing_methods;JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<DeprecatedString,utility::Span>> unmatched_signatures;JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<DeprecatedString,utility::Span>> private_matching_methods;JaktInternal::Dictionary<DeprecatedString,typechecker::AlreadyImplementedFor> already_implemented_for;ErrorOr<void> throw_errors(utility::Span const record_decl_span, typechecker::Typechecker& typechecker);
ErrorOr<void> ensure_capacity(size_t const count);
ErrorOr<void> register_method(ids::TypeId const self_type_id, DeprecatedString const method_name, ids::FunctionId const method_id, typechecker::Typechecker& typechecker);
static ErrorOr<typechecker::TraitImplCheck> make();
TraitImplCheck(JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<DeprecatedString,ids::FunctionId>> a_missing_methods, JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<DeprecatedString,utility::Span>> a_unmatched_signatures, JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<DeprecatedString,utility::Span>> a_private_matching_methods, JaktInternal::Dictionary<DeprecatedString,typechecker::AlreadyImplementedFor> a_already_implemented_for);

ErrorOr<void> register_trait(ids::TypeId const trait_type_id, DeprecatedString const trait_name, types::CheckedTraitRequirements const requirements);
ErrorOr<DeprecatedString> debug_description() const;
};namespace NumericOrStringValue_Details {
struct StringValue{
DeprecatedString value;
template<typename _MemberT0>
StringValue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct SignedNumericValue{
i64 value;
template<typename _MemberT0>
SignedNumericValue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct UnsignedNumericValue{
u64 value;
template<typename _MemberT0>
UnsignedNumericValue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct NumericOrStringValue : public Variant<NumericOrStringValue_Details::StringValue, NumericOrStringValue_Details::SignedNumericValue, NumericOrStringValue_Details::UnsignedNumericValue> {
using Variant<NumericOrStringValue_Details::StringValue, NumericOrStringValue_Details::SignedNumericValue, NumericOrStringValue_Details::UnsignedNumericValue>::Variant;
    using StringValue = NumericOrStringValue_Details::StringValue;
    using SignedNumericValue = NumericOrStringValue_Details::SignedNumericValue;
    using UnsignedNumericValue = NumericOrStringValue_Details::UnsignedNumericValue;
ErrorOr<DeprecatedString> debug_description() const;
};
template <typename K, typename V>struct InternalDictionaryProduct {
  public:
JaktInternal::Dictionary<K,JaktInternal::DynamicArray<V>> dict;JaktInternal::Dictionary<K,V> current;JaktInternal::Dictionary<K,size_t> current_index;bool done;ErrorOr<JaktInternal::Optional<JaktInternal::Dictionary<K,V>>> next() {
{
if (((*this).done)){
return JaktInternal::OptionalNone();
}
JaktInternal::Dictionary<K,V> next = (TRY((Dictionary<K, V>::create_with_entries({}))));
{
JaktInternal::ArrayIterator<K> _magic = ((TRY((((((*this).dict)).keys())))).iterator());
for (;;){
JaktInternal::Optional<K> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
K key = (_magic_value.value());
{
V const value = ((((((*this).dict))[key]))[((((*this).current_index))[key])]);
TRY(next.set(key, value));
}

}
}

(((*this).current) = next);
{
JaktInternal::DictionaryIterator<K,JaktInternal::DynamicArray<V>> _magic = ((((*this).dict)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<K,JaktInternal::DynamicArray<V>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<K,JaktInternal::DynamicArray<V>> key__values__ = (_magic_value.value());
{
JaktInternal::Tuple<K,JaktInternal::DynamicArray<V>> const jakt__key__values__ = key__values__;
K const key = ((jakt__key__values__).template get<0>());
JaktInternal::DynamicArray<V> const values = ((jakt__key__values__).template get<1>());

size_t const index = ((((*this).current_index))[key]);
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(JaktInternal::checked_add(index,static_cast<size_t>(1ULL)),((values).size()))){
TRY(((*this).current_index).set(key, JaktInternal::checked_add(index,static_cast<size_t>(1ULL))));
return next;
}
TRY(((*this).current_index).set(key, static_cast<size_t>(0ULL)));
}

}
}

(((*this).done) = true);
return next;
}
}
InternalDictionaryProduct(JaktInternal::Dictionary<K,JaktInternal::DynamicArray<V>> a_dict, JaktInternal::Dictionary<K,V> a_current, JaktInternal::Dictionary<K,size_t> a_current_index, bool a_done) :dict(move(a_dict)), current(move(a_current)), current_index(move(a_current_index)), done(move(a_done)){}

ErrorOr<DeprecatedString> debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("InternalDictionaryProduct("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("dict: {}, ", dict));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current: {}, ", current));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_index: {}, ", current_index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("done: {}", done));
}
TRY(builder.append(")"sv));return builder.to_string(); }
};namespace FunctionMatchResult_Details {
struct MatchSuccess {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> args;
JaktInternal::Optional<ids::TypeId> maybe_this_type_id;
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> used_generic_inferences;
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
JaktInternal::DynamicArray<error::JaktError> errors;
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
ErrorOr<DeprecatedString> debug_description() const;
};
struct ImportRestrictions {
  public:
bool functions;bool structs;bool enums;bool types;bool traits;bool namespaces;ImportRestrictions(bool a_functions, bool a_structs, bool a_enums, bool a_types, bool a_traits, bool a_namespaces);

static typechecker::ImportRestrictions all();
ErrorOr<DeprecatedString> debug_description() const;
};struct AlreadyImplementedFor {
  public:
DeprecatedString trait_name;utility::Span encounter_span;AlreadyImplementedFor(DeprecatedString a_trait_name, utility::Span a_encounter_span);

ErrorOr<DeprecatedString> debug_description() const;
};struct Typechecker {
  public:
NonnullRefPtr<compiler::Compiler> compiler;NonnullRefPtr<types::CheckedProgram> program;ids::ModuleId current_module_id;JaktInternal::Optional<ids::TypeId> current_struct_type_id;JaktInternal::Optional<ids::FunctionId> current_function_id;bool inside_defer;size_t checkidx;bool ignore_errors;bool dump_type_hints;bool dump_try_hints;u64 lambda_count;types::GenericInferences generic_inferences;JaktInternal::Optional<ids::TypeId> self_type_id;DeprecatedString root_module_name;bool in_comptime_function_call;bool had_an_error;ErrorOr<void> typecheck_struct_predecl_initial(parser::ParsedRecord const parsed_record, size_t const struct_index, size_t const module_struct_len, ids::ScopeId const scope_id);
ErrorOr<void> ensure_type_implements_trait(ids::TypeId const type_id, DeprecatedString const trait_name, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const filter_for_generics, ids::ScopeId const scope_id, utility::Span const span);
ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<ids::TypeId>>> typecheck_match_body(parser::ParsedMatchBody const body, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, types::GenericInferences& generic_inferences, JaktInternal::Optional<ids::TypeId> const final_result_type, utility::Span const span);
ErrorOr<DeprecatedString> type_name(ids::TypeId const type_id, bool const debug_mode) const;
ErrorOr<ids::ScopeId> create_scope(JaktInternal::Optional<ids::ScopeId> const parent_scope_id, bool const can_throw, DeprecatedString const debug_name, bool const for_block);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_return(JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const expr, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode);
NonnullRefPtr<types::CheckedTrait> get_trait(ids::TraitId const id) const;
ErrorOr<void> typecheck_namespace_function_predecl(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_set(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const values, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
ErrorOr<void> typecheck_struct_methods_predecl(parser::ParsedRecord const parsed_record, ids::StructId const struct_id, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>>> find_functions_with_name_in_scope(ids::ScopeId const parent_scope_id, DeprecatedString const function_name) const;
bool is_class(ids::TypeId const type_id) const;
ErrorOr<types::CheckedVisibility> typecheck_visibility(parser::Visibility const visibility, ids::ScopeId const scope_id);
ErrorOr<JaktInternal::Optional<types::Value>> find_comptime_binding_in_scope(ids::ScopeId const scope_id, DeprecatedString const name) const;
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_try_block(NonnullRefPtr<typename parser::ParsedStatement> const stmt, DeprecatedString const error_name, utility::Span const error_span, parser::ParsedBlock const catch_block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> typecheck_trait(parser::ParsedTrait const parsed_trait, ids::TraitId const trait_id, ids::ScopeId const scope_id, bool const comptime_pass);
ErrorOr<void> typecheck_enum_constructor(parser::ParsedRecord const parsed_record, ids::EnumId const enum_id, ids::ScopeId const parent_scope_id);
ErrorOr<typechecker::FunctionMatchResult> match_function_and_resolve_args(parser::ParsedCall const call, ids::ScopeId const caller_scope_id, ids::FunctionId const candidate, types::SafetyMode const safety_mode, utility::Span const span, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const this_expr);
ErrorOr<ids::TypeId> unify_with_type(ids::TypeId const found_type, JaktInternal::Optional<ids::TypeId> const expected_type, utility::Span const span);
ErrorOr<ids::StructId> find_struct_in_prelude(DeprecatedString const name) const;
bool is_numeric(ids::TypeId const type_id) const;
ErrorOr<DeprecatedString> debug_description_of(ids::ScopeId const scope_id) const;
types::CheckedStruct get_struct(ids::StructId const id) const;
types::CheckedEnum get_enum(ids::EnumId const id) const;
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> dereference_if_needed(NonnullRefPtr<typename types::CheckedExpression> const checked_expr, utility::Span const span);
ErrorOr<void> dump_type_hint(ids::TypeId const type_id, utility::Span const span) const;
ErrorOr<void> typecheck_entity_trait_implementations(ids::ScopeId const scope_id, ids::TypeId const type_id, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> const trait_implementations, DeprecatedString const name, utility::Span const name_span);
ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> fill_trait_implementation_list(JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> const parsed_impl_list, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>>& trait_implementations, ids::ScopeId const scope_id, JaktInternal::Optional<ids::ScopeId> const trait_name_scope_id_override);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_statement(NonnullRefPtr<typename parser::ParsedStatement> const statement, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_unary_negate(NonnullRefPtr<typename types::CheckedExpression> const expr, utility::Span const span, ids::TypeId const type_id);
ErrorOr<void> typecheck_function(parser::ParsedFunction const parsed_function, ids::ScopeId const parent_scope_id);
ErrorOr<void> typecheck_namespace_declarations(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
ErrorOr<void> typecheck_struct_constructor(parser::ParsedRecord const parsed_record, ids::StructId const struct_id, ids::ScopeId const scope_id);
ErrorOr<ids::TypeId> resolve_type_var(ids::TypeId const type_var_type_id, ids::ScopeId const scope_id) const;
ErrorOr<void> check_type_argument_requirements(ids::TypeId const generic_argument, JaktInternal::DynamicArray<ids::TraitId> const constraints, utility::Span const arg_span);
ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>>> get_type_ids_from_type_hint_if_struct_ids_match(JaktInternal::Optional<ids::TypeId> const type_hint, ids::StructId const expected_struct_id) const;
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_generic_arguments_method_call(NonnullRefPtr<typename types::CheckedExpression> const checked_expr, parser::ParsedCall const call, ids::ScopeId const scope_id, utility::Span const span, bool const is_optional, types::SafetyMode const safety_mode);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_loop(parser::ParsedBlock const parsed_block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<NonnullRefPtr<types::Scope>> get_scope(ids::ScopeId const id) const;
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_indexed_tuple(NonnullRefPtr<typename parser::ParsedExpression> const expr, size_t const index, ids::ScopeId const scope_id, bool const is_optional, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>>> typecheck_forall_chunk_parameters(JaktInternal::DynamicArray<parser::ParsedGenericParameter> const chunk_parameters, ids::ScopeId const scope_id);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_while(NonnullRefPtr<typename parser::ParsedExpression> const condition, parser::ParsedBlock const block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<ids::TypeId> prelude_struct_type_named(DeprecatedString const name);
ErrorOr<void> typecheck_alias(parser::ParsedAlias const alias, ids::ScopeId const scope_id, typechecker::ImportRestrictions const allow);
ErrorOr<types::CheckedUnaryOperator> typecheck_is_enum_variant(NonnullRefPtr<typename types::CheckedExpression> const checked_expr, NonnullRefPtr<typename parser::ParsedType> const inner, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const bindings, ids::ScopeId const scope_id);
ErrorOr<bool> add_var_to_scope(ids::ScopeId const scope_id, DeprecatedString const name, ids::VarId const var_id, utility::Span const span);
ErrorOr<bool> add_comptime_binding_to_scope(ids::ScopeId const scope_id, DeprecatedString const name, types::Value const value, utility::Span const span);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_match(NonnullRefPtr<typename parser::ParsedExpression> const expr, JaktInternal::DynamicArray<parser::ParsedMatchCase> const cases, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
ErrorOr<void> map_generic_arguments(ids::TypeId const type_id, JaktInternal::DynamicArray<ids::TypeId> const args);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_throw(NonnullRefPtr<typename parser::ParsedExpression> const expr, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> fill_trait_requirements(JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> const names, JaktInternal::DynamicArray<ids::TraitId>& trait_requirements, JaktInternal::DynamicArray<ids::TypeId>& trait_implementations, ids::ScopeId const scope_id);
ErrorOr<bool> struct_inherits_from(ids::StructId const struct_id, ids::StructId const super_struct_id, JaktInternal::Optional<JaktInternal::DynamicArray<ids::StructId>> const struct_inheritance_chain) const;
ErrorOr<JaktInternal::Optional<ids::FunctionId>> find_function_matching_trait_implementation_in_scope(ids::TypeId const self_type_id, ids::ScopeId const parent_scope_id, DeprecatedString const function_name, typechecker::TraitImplementationDescriptor const& trait_descriptor);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_dictionary(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> const values, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
ErrorOr<types::CheckedBlock> typecheck_block(parser::ParsedBlock const parsed_block, ids::ScopeId const parent_scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const yield_type_hint);
ErrorOr<void> typecheck_namespace_default_fields(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
ErrorOr<void> typecheck_jakt_main(parser::ParsedFunction const parsed_function, ids::ScopeId const parent_scope_id);
ErrorOr<JaktInternal::Tuple<types::CheckedBinaryOperator,ids::TypeId>> typecheck_binary_operation(NonnullRefPtr<typename types::CheckedExpression> const checked_lhs, parser::BinaryOperator const op, NonnullRefPtr<typename types::CheckedExpression> const checked_rhs, ids::ScopeId const scope_id, utility::Span const span);
ErrorOr<void> typecheck_enum_predecl_initial(parser::ParsedRecord const parsed_record, size_t const enum_index, size_t const module_enum_len, ids::ScopeId const scope_id);
ErrorOr<ids::TypeId> typecheck_generic_resolved_type(DeprecatedString const name, JaktInternal::DynamicArray<ids::TypeId> const checked_inner_types, ids::ScopeId const scope_id, utility::Span const span);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_comptime_index(NonnullRefPtr<typename parser::ParsedExpression> const expr, NonnullRefPtr<typename parser::ParsedExpression> const index, ids::ScopeId const scope_id, bool const is_optional, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> typecheck_namespace_fields(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
Typechecker(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, ids::ModuleId a_current_module_id, JaktInternal::Optional<ids::TypeId> a_current_struct_type_id, JaktInternal::Optional<ids::FunctionId> a_current_function_id, bool a_inside_defer, size_t a_checkidx, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, types::GenericInferences a_generic_inferences, JaktInternal::Optional<ids::TypeId> a_self_type_id, DeprecatedString a_root_module_name, bool a_in_comptime_function_call, bool a_had_an_error);

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> cast_to_underlying(NonnullRefPtr<typename parser::ParsedExpression> const expr, ids::ScopeId const scope_id, NonnullRefPtr<typename parser::ParsedType> const parsed_type);
ErrorOr<ids::TypeId> substitute_typevars_in_type(ids::TypeId const type_id, types::GenericInferences const generic_inferences);
ErrorOr<DeprecatedString> get_argument_name(JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> const arg) const;
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> find_type_scope(ids::ScopeId const scope_id, DeprecatedString const name) const;
ErrorOr<ids::FunctionId> typecheck_and_specialize_generic_function(ids::FunctionId const function_id, JaktInternal::DynamicArray<ids::TypeId> const generic_arguments, ids::ScopeId const parent_scope_id, JaktInternal::Optional<ids::TypeId> const this_type_id, types::GenericInferences const generic_substitutions, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const type_args, utility::Span const call_span, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>>> const args);
NonnullRefPtr<types::CheckedFunction> get_function(ids::FunctionId const id) const;
ErrorOr<JaktInternal::Optional<ids::ScopeId>> required_scope_id_in_hierarchy_for(NonnullRefPtr<typename types::CheckedExpression> const expr, ids::ScopeId const current_scope_id);
ErrorOr<JaktInternal::Optional<typechecker::TraitImplementationDescriptor>> find_any_singular_trait_implementation(ids::TypeId const type_id, JaktInternal::DynamicArray<DeprecatedString> const trait_names, ids::ScopeId const scope_id, utility::Span const span, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const filter_for_generics);
ErrorOr<void> specialize_trait(ids::TraitId const trait_id, JaktInternal::DynamicArray<ids::TypeId> const generic_parameters);
ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,types::CheckedMatchCase,JaktInternal::Optional<ids::TypeId>>> typecheck_match_variant(parser::ParsedMatchCase const case_, ids::TypeId const subject_type_id, size_t const variant_index, JaktInternal::Optional<ids::TypeId> const final_result_type, types::CheckedEnumVariant const variant, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const variant_arguments, JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> const default_bindings, utility::Span const arguments_span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode);
ErrorOr<void> include_prelude();
ErrorOr<ids::ModuleId> create_module(DeprecatedString const name, bool const is_root, JaktInternal::Optional<DeprecatedString> const path);
ids::ScopeId prelude_scope_id() const;
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_namespaced_var_or_simple_enum_constructor_call(DeprecatedString const name, JaktInternal::DynamicArray<DeprecatedString> const namespace_, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint, utility::Span const span);
ErrorOr<void> typecheck_struct_predecl(parser::ParsedRecord const parsed_record, ids::StructId const struct_id, ids::ScopeId const scope_id);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_unary_operation(NonnullRefPtr<typename types::CheckedExpression> const checked_expr, types::CheckedUnaryOperator const checked_op, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> infer_unsigned_int(u64 const val, utility::Span const span, JaktInternal::Optional<ids::TypeId> const type_hint);
ErrorOr<ids::TypeId> strip_optional_from_type(ids::TypeId const type_id);
ErrorOr<JaktInternal::Optional<types::FieldRecord>> lookup_struct_field(ids::StructId const struct_id, DeprecatedString const name) const;
ErrorOr<types::CheckedParameter> typecheck_parameter(parser::ParsedParameter const parameter, ids::ScopeId const scope_id, bool const first, JaktInternal::Optional<ids::TypeId> const this_arg_type_id, JaktInternal::Optional<ids::ScopeId> const check_scope);
ErrorOr<JaktInternal::Optional<ids::TypeId>> unify(ids::TypeId const lhs, utility::Span const lhs_span, ids::TypeId const rhs, utility::Span const rhs_span);
ErrorOr<types::BlockControlFlow> maybe_statement_control_flow(JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const statement, types::BlockControlFlow const other_branch) const;
bool is_floating(ids::TypeId const type_id) const;
ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> find_var_in_scope(ids::ScopeId const scope_id, DeprecatedString const var) const;
ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<types::StructLikeId>,bool>> struct_like_id_from_type_id(ids::TypeId const type_id, ids::ScopeId const scope_id, utility::Span const span, bool const for_optional_chain, bool const treat_string_as_builtin);
ErrorOr<void> set_owner_scope_if_needed(ids::ScopeId const parent_scope_id, JaktInternal::DynamicArray<ids::FunctionId> const overload_set);
ErrorOr<void> set_owner_scope_if_needed(ids::ScopeId const parent_scope_id, ids::VarId const var_id);
ErrorOr<ids::TypeId> find_type_in_prelude(DeprecatedString const name) const;
ErrorOr<bool> add_type_to_scope(ids::ScopeId const scope_id, DeprecatedString const type_name, ids::TypeId const type_id, utility::Span const span);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> infer_signed_int(i64 const val, utility::Span const span, JaktInternal::Optional<ids::TypeId> const type_hint);
ErrorOr<void> typecheck_namespace_aliases(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id, typechecker::ImportRestrictions const allow);
ErrorOr<bool> add_struct_to_scope(ids::ScopeId const scope_id, DeprecatedString const name, ids::StructId const struct_id, utility::Span const span);
ErrorOr<void> error(DeprecatedString const message, utility::Span const span);
ErrorOr<bool> check_restricted_access(ids::ScopeId const accessor, DeprecatedString const accessee_kind, ids::ScopeId const accessee, DeprecatedString const name, JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> const whitelist, utility::Span const span);
ErrorOr<bool> check_types_for_compat(ids::TypeId const lhs_type_id, ids::TypeId const rhs_type_id, types::GenericInferences& generic_inferences, utility::Span const span);
ErrorOr<void> typecheck_enum_predecl(parser::ParsedRecord const parsed_record, ids::EnumId const enum_id, ids::ScopeId const scope_id);
ErrorOr<void> check_member_access(ids::ScopeId const accessor, ids::ScopeId const accessee, NonnullRefPtr<types::CheckedVariable> const member, utility::Span const span);
bool is_integer(ids::TypeId const type_id) const;
ErrorOr<bool> signatures_match(ids::TypeId const self_type_id, NonnullRefPtr<types::CheckedFunction> const first, NonnullRefPtr<types::CheckedFunction> const second);
ErrorOr<NonnullRefPtr<typename types::Type>> unwrap_type_from_optional_if_needed(NonnullRefPtr<typename types::Type> const type) const;
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_guard(NonnullRefPtr<typename parser::ParsedExpression> const expr, parser::ParsedBlock const else_block, parser::ParsedBlock const remaining_code, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
NonnullRefPtr<typename types::Type> get_type(ids::TypeId const id) const;
ErrorOr<void> typecheck_namespace_trait_implementations_predecl(ids::ScopeId const scope_id);
ErrorOr<bool> add_trait_to_scope(ids::ScopeId const scope_id, DeprecatedString const trait_name, ids::TraitId const trait_id, utility::Span const span);
ErrorOr<JaktInternal::Optional<ids::ScopeId>> scope_lifetime_union(JaktInternal::Optional<ids::ScopeId> const first, JaktInternal::Optional<ids::ScopeId> const second) const;
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_destructuring_assignment(JaktInternal::DynamicArray<parser::ParsedVarDecl> const vars, NonnullRefPtr<typename parser::ParsedStatement> const var_decl, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<bool> is_scope_directly_accessible_from(ids::ScopeId const scope_id, ids::ScopeId const from_scope_id) const;
ErrorOr<void> typecheck_struct_default_fields(parser::ParsedRecord const parsed_record, ids::StructId const struct_id, ids::ScopeId const scope_id);
ErrorOr<void> typecheck_namespace_constructors(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_block_statement(parser::ParsedBlock const parsed_block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<ids::FunctionId> typecheck_function_predecl(parser::ParsedFunction const parsed_function, ids::ScopeId const parent_scope_id, JaktInternal::Optional<ids::TypeId> const this_arg_type_id, JaktInternal::Optional<NonnullRefPtr<types::FunctionGenerics>> generics, JaktInternal::Optional<ids::ScopeId> scope_mixin);
ErrorOr<ids::TypeId> find_or_add_type_id(NonnullRefPtr<typename types::Type> const type);
static ErrorOr<typechecker::Typechecker> typecheck(NonnullRefPtr<compiler::Compiler> compiler, parser::ParsedNamespace const parsed_namespace);
ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedEnumVariantBinding>>> typecheck_enum_variant_bindings(types::CheckedEnumVariant const variant, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const bindings, utility::Span const span);
ErrorOr<void> typecheck_struct(parser::ParsedRecord const record, ids::StructId const struct_id, ids::ScopeId const parent_scope_id);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_lambda(JaktInternal::DynamicArray<parser::ParsedCapture> const captures, JaktInternal::DynamicArray<parser::ParsedParameter> const params, bool const can_throw, bool const is_fat_arrow, NonnullRefPtr<typename parser::ParsedType> const return_type, parser::ParsedBlock const block, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode);
NonnullRefPtr<types::CheckedVariable> get_variable(ids::VarId const id) const;
ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename types::CheckedExpression>>>> resolve_default_params(JaktInternal::DynamicArray<types::CheckedParameter> const params, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const args, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, size_t const arg_offset, utility::Span const span);
ErrorOr<JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>>> find_all_implementations_of_trait(ids::TypeId const type_id, ids::TraitId const trait_id, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const filter_for_generics);
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>>> find_namespace_in_scope(ids::ScopeId const scope_id, DeprecatedString const name, bool const treat_aliases_as_imports) const;
ErrorOr<void> typecheck_struct_fields(parser::ParsedRecord const record, ids::StructId const struct_id);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_call(parser::ParsedCall const call, ids::ScopeId const caller_scope_id, utility::Span const span, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const this_expr, JaktInternal::Optional<types::StructLikeId> const parent_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> type_hint, bool const must_be_enum_constructor);
ErrorOr<JaktInternal::DynamicArray<ids::FunctionId>> resolve_call(parser::ParsedCall const call, JaktInternal::DynamicArray<types::ResolvedNamespace> namespaces, utility::Span const span, ids::ScopeId const scope_id, bool const must_be_enum_constructor);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_if(NonnullRefPtr<typename parser::ParsedExpression> const condition, parser::ParsedBlock const then_block, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const else_statement, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> check_implicit_constructor_argument_access(ids::ScopeId const caller_scope_id, parser::ParsedCall const call, types::CheckedStruct const struct_);
ErrorOr<void> typecheck_enum(parser::ParsedRecord const record, ids::EnumId const enum_id, ids::ScopeId const parent_scope_id);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_expression_and_dereference_if_needed(NonnullRefPtr<typename parser::ParsedExpression> const expr, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint, utility::Span const span);
ErrorOr<JaktInternal::Optional<ids::TypeId>> find_type_in_scope(ids::ScopeId const scope_id, DeprecatedString const name) const;
ErrorOr<void> set_self_type_id(ids::TypeId const type_id);
ErrorOr<JaktInternal::Optional<types::CheckedEnumVariant>> get_enum_variant(types::CheckedEnum const enum_, DeprecatedString const variant_name);
ErrorOr<bool> scope_can_access(ids::ScopeId const accessor, ids::ScopeId const accessee) const;
ErrorOr<JaktInternal::DynamicArray<ids::StructId>> struct_inheritance_chain(ids::StructId const struct_id) const;
ErrorOr<bool> type_contains_reference(ids::TypeId const type_id);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_for(DeprecatedString const iterator_name, utility::Span const name_span, bool const is_destructuring, NonnullRefPtr<typename parser::ParsedExpression> const range, parser::ParsedBlock const block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> resolve_external_trait_implementations(parser::ParsedExternalTraitImplementation const implementation, ids::ScopeId const entity_scope_id, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>>& trait_implementations, ids::TypeId const for_type, ids::ScopeId const scope_id, bool const default_pass);
ErrorOr<JaktInternal::Optional<ids::FunctionId>> find_function_matching_signature_in_scope(ids::ScopeId const parent_scope_id, parser::ParsedFunction const prototype) const;
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_array(ids::ScopeId const scope_id, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const values, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const fill_size, utility::Span const span, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
ErrorOr<void> typecheck_entity_trait_implementations_predecl(ids::ScopeId const scope_id, ids::TypeId const type_id, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> const trait_implementations, DeprecatedString const name, utility::Span const name_span);
ErrorOr<void> typecheck_trait_predecl(parser::ParsedTrait const parsed_trait, ids::ScopeId const scope_id);
ErrorOr<bool> implements_trait(ids::TypeId const type_id, ids::TraitId const trait_id, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const generic_arguments);
ErrorOr<void> typecheck_module_import(parser::ParsedModuleImport const import_, ids::ScopeId const scope_id);
ErrorOr<JaktInternal::Optional<ids::FunctionId>> typecheck_method(parser::ParsedFunction const func, types::StructLikeId const parent_id);
ErrorOr<void> typecheck_extern_import(parser::ParsedExternImport const import_, ids::ScopeId const scope_id);
ErrorOr<void> typecheck_override(parser::ParsedMethod const method, ids::ScopeId const parent_scope_id, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>>> const all_virtuals);
ErrorOr<types::BlockControlFlow> statement_control_flow(NonnullRefPtr<typename types::CheckedStatement> const statement) const;
ErrorOr<JaktInternal::Optional<ids::StructId>> find_struct_in_scope(ids::ScopeId const scope_id, DeprecatedString const name) const;
ErrorOr<void> check_that_type_doesnt_contain_reference(ids::TypeId const type_id, utility::Span const span);
ErrorOr<JaktInternal::Optional<parser::ParsedNamespace>> lex_and_parse_file_contents(utility::FileId const file_id);
ErrorOr<bool> find_and_import_name_from_scope(DeprecatedString const from_name, utility::Span const from_span, DeprecatedString const to_name, utility::Span const to_span, ids::ScopeId const from_scope_id, ids::ScopeId const into_scope_id, typechecker::ImportRestrictions const allow);
ErrorOr<bool> validate_argument_label(types::CheckedParameter const param, DeprecatedString const label, utility::Span const span, NonnullRefPtr<typename parser::ParsedExpression> const expr, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const default_value);
ErrorOr<bool> add_enum_to_scope(ids::ScopeId const scope_id, DeprecatedString const name, ids::EnumId const enum_id, utility::Span const span);
ErrorOr<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>>> expand_context_for_bindings(NonnullRefPtr<typename parser::ParsedExpression> const condition, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const acc, JaktInternal::Optional<parser::ParsedBlock> const then_block, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const else_statement, ids::ScopeId const scope_id, utility::Span const span);
ErrorOr<JaktInternal::Optional<ids::TraitId>> find_trait_in_scope(ids::ScopeId const scope_id, DeprecatedString const name) const;
NonnullRefPtr<types::Module> current_module() const;
ids::ScopeId root_scope_id() const;
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_defer(NonnullRefPtr<typename parser::ParsedStatement> const statement, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<bool> add_function_to_scope(ids::ScopeId const parent_scope_id, DeprecatedString const name, JaktInternal::DynamicArray<ids::FunctionId> const overload_set, utility::Span const span);
ErrorOr<void> check_method_access(ids::ScopeId const accessor, ids::ScopeId const accessee, NonnullRefPtr<types::CheckedFunction> const method, utility::Span const span);
ErrorOr<ids::TypeId> final_type_resolution_form(ids::TypeId const type_id, ids::ScopeId const scope_id) const;
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> find_scoped_functions_with_name_in_scope(ids::ScopeId const parent_scope_id, DeprecatedString const function_name) const;
ErrorOr<NonnullRefPtr<interpreter::Interpreter>> interpreter();
ErrorOr<void> typecheck_enum_methods_predecl(parser::ParsedRecord const parsed_record, ids::EnumId const enum_id, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
ErrorOr<void> dump_try_hint(utility::Span const span) const;
ErrorOr<void> typecheck_namespace_methods_predecl(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
ErrorOr<void> typecheck_module(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
ErrorOr<void> error_with_hint(DeprecatedString const message, utility::Span const span, DeprecatedString const hint, utility::Span const hint_span);
bool is_subclass_of(ids::TypeId const ancestor_type_id, ids::TypeId const child_type_id) const;
ErrorOr<void> typecheck_namespace_predecl(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_var_decl(parser::ParsedVarDecl const var, NonnullRefPtr<typename parser::ParsedExpression> const init, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_inline_cpp(parser::ParsedBlock const block, utility::Span const span, types::SafetyMode const safety_mode);
bool is_struct(ids::TypeId const type_id) const;
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_expression(NonnullRefPtr<typename parser::ParsedExpression> const expr, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_indexed_struct(NonnullRefPtr<typename parser::ParsedExpression> const expr, DeprecatedString const field_name, ids::ScopeId const scope_id, bool const is_optional, types::SafetyMode const safety_mode, utility::Span const span);
ErrorOr<void> typecheck_namespace_imports(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
ErrorOr<jakt__path::Path> get_root_path() const;
ErrorOr<void> typecheck_namespace_trait_implementations(ids::ScopeId const scope_id);
ErrorOr<JaktInternal::Optional<typechecker::TraitImplementationDescriptor>> find_singular_trait_implementation(ids::TypeId const type_id, DeprecatedString const trait_name, ids::ScopeId const scope_id, utility::Span const span, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const filter_for_generics);
ErrorOr<ids::TypeId> typecheck_typename(NonnullRefPtr<typename parser::ParsedType> const parsed_type, ids::ScopeId const scope_id, JaktInternal::Optional<DeprecatedString> const name);
ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_try(NonnullRefPtr<typename parser::ParsedExpression> const expr, JaktInternal::Optional<parser::ParsedBlock> const catch_block, JaktInternal::Optional<DeprecatedString> const catch_name, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span, JaktInternal::Optional<ids::TypeId> const type_hint);
ids::TypeId infer_function_return_type(types::CheckedBlock const block) const;
ErrorOr<bool> scope_lifetime_subsumes(JaktInternal::Optional<ids::ScopeId> const larger, JaktInternal::Optional<ids::ScopeId> const smaller) const;
ErrorOr<DeprecatedString> debug_description() const;
};template <typename R,typename S>
ErrorOr<typechecker::InternalDictionaryProduct<R,S>> create_internal_dictionary_product(JaktInternal::Dictionary<R,JaktInternal::DynamicArray<S>> const dict);
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::TraitImplementationDescriptor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::TraitImplementationDescriptor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::TraitImplCheck> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::TraitImplCheck const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::NumericOrStringValue> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::NumericOrStringValue const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<typename K, typename V>struct Jakt::Formatter<Jakt::typechecker::InternalDictionaryProduct<K, V>
> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::InternalDictionaryProduct<K, V>
 const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::FunctionMatchResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::FunctionMatchResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::ImportRestrictions> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::ImportRestrictions const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::AlreadyImplementedFor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::AlreadyImplementedFor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::Typechecker> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::Typechecker const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
