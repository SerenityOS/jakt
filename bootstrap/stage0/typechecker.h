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
#include "cpp_import__common.h"
#include "cpp_import__none.h"
#include "jakt__platform.h"
#include "jakt__platform__unknown_fs.h"
namespace Jakt {
namespace typechecker {
struct TraitImplementationDescriptor {
  public:
public: ids::TraitId trait_id;public: ByteString trait_name;public: JaktInternal::DynamicArray<ids::TypeId> implemented_type_args;public: TraitImplementationDescriptor(ids::TraitId a_trait_id, ByteString a_trait_name, JaktInternal::DynamicArray<ids::TypeId> a_implemented_type_args);

public: ErrorOr<ByteString> debug_description() const;
};struct AlreadyImplementedFor {
  public:
public: ByteString trait_name;public: utility::Span encounter_span;public: AlreadyImplementedFor(ByteString a_trait_name, utility::Span a_encounter_span);

public: ErrorOr<ByteString> debug_description() const;
};struct FunctionMatchResult {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> args;
JaktInternal::Optional<ids::TypeId> maybe_this_type_id;
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> used_generic_inferences;
i64 specificity;
} MatchSuccess;
struct {
JaktInternal::DynamicArray<error::JaktError> errors;
} MatchError;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static FunctionMatchResult MatchSuccess(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> args, JaktInternal::Optional<ids::TypeId> maybe_this_type_id, JaktInternal::Dictionary<ids::TypeId,ids::TypeId> used_generic_inferences, i64 specificity);
[[nodiscard]] static FunctionMatchResult MatchError(JaktInternal::DynamicArray<error::JaktError> errors);
~FunctionMatchResult();
FunctionMatchResult& operator=(FunctionMatchResult const &);
FunctionMatchResult& operator=(FunctionMatchResult &&);
FunctionMatchResult(FunctionMatchResult const&);
FunctionMatchResult(FunctionMatchResult &&);
private: void __jakt_destroy_variant();
public:
private:
FunctionMatchResult() {};
};
struct ImportRestrictions {
  public:
public: bool functions;public: bool structs;public: bool enums;public: bool types;public: bool traits;public: bool namespaces;public: ImportRestrictions(bool a_functions, bool a_structs, bool a_enums, bool a_types, bool a_traits, bool a_namespaces);

public: static typechecker::ImportRestrictions all();
public: ErrorOr<ByteString> debug_description() const;
};template <typename K,typename V>struct InternalDictionaryProduct {
  public:
public: JaktInternal::Dictionary<K,JaktInternal::DynamicArray<V>> dict;public: JaktInternal::Dictionary<K,V> current;public: JaktInternal::Dictionary<K,size_t> current_index;public: bool done;public: ErrorOr<JaktInternal::Optional<JaktInternal::Dictionary<K,V>>> next() {
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
public: InternalDictionaryProduct(JaktInternal::Dictionary<K,JaktInternal::DynamicArray<V>> a_dict, JaktInternal::Dictionary<K,V> a_current, JaktInternal::Dictionary<K,size_t> a_current_index, bool a_done): dict(move(a_dict)), current(move(a_current)), current_index(move(a_current_index)), done(move(a_done)){}

public: ErrorOr<ByteString> debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("InternalDictionaryProduct("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("dict: {}, ", dict));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current: {}, ", current));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_index: {}, ", current_index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("done: {}", done));
}
TRY(builder.append(")"sv));return builder.to_string(); }
};struct NumericOrStringValue {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString value;
} StringValue;
struct {
i64 value;
} SignedNumericValue;
struct {
u64 value;
} UnsignedNumericValue;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static NumericOrStringValue StringValue(ByteString value);
[[nodiscard]] static NumericOrStringValue SignedNumericValue(i64 value);
[[nodiscard]] static NumericOrStringValue UnsignedNumericValue(u64 value);
~NumericOrStringValue();
NumericOrStringValue& operator=(NumericOrStringValue const &);
NumericOrStringValue& operator=(NumericOrStringValue &&);
NumericOrStringValue(NumericOrStringValue const&);
NumericOrStringValue(NumericOrStringValue &&);
private: void __jakt_destroy_variant();
public:
private:
NumericOrStringValue() {};
};
struct Typechecker {
  public:
public: NonnullRefPtr<compiler::Compiler> compiler;public: NonnullRefPtr<types::CheckedProgram> program;public: ids::ModuleId current_module_id;public: JaktInternal::Optional<ids::TypeId> current_struct_type_id;public: JaktInternal::Optional<ids::FunctionId> current_function_id;public: bool inside_defer;public: size_t checkidx;public: bool ignore_errors;public: bool dump_type_hints;public: bool dump_try_hints;public: u64 lambda_count;public: types::GenericInferences generic_inferences;public: JaktInternal::Optional<ids::TypeId> self_type_id;public: ByteString root_module_name;public: bool in_comptime_function_call;public: bool had_an_error;public: JaktInternal::Dictionary<ByteString,ids::ScopeId> cpp_import_cache;public: JaktInternal::Optional<cpp_import__none::CppImportProcessor> cpp_import_processor;public: ErrorOr<void> typecheck_struct_predecl_initial(parser::ParsedRecord const parsed_record, size_t const struct_index, size_t const module_struct_len, ids::ScopeId const scope_id);
public: ErrorOr<void> ensure_type_implements_trait(ids::TypeId const type_id, ByteString const trait_name, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const filter_for_generics, ids::ScopeId const scope_id, utility::Span const span);
public: ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<ids::TypeId>>> typecheck_match_body(parser::ParsedMatchBody const body, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, types::GenericInferences& generic_inferences, JaktInternal::Optional<ids::TypeId> const final_result_type, utility::Span const span);
public: ErrorOr<ByteString> type_name(ids::TypeId const type_id, bool const debug_mode) const;
public: ErrorOr<ids::ScopeId> create_scope(JaktInternal::Optional<ids::ScopeId> const parent_scope_id, bool const can_throw, ByteString const debug_name, bool const for_block);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_return(JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const expr, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode);
public: NonnullRefPtr<types::CheckedTrait> get_trait(ids::TraitId const id) const;
public: ErrorOr<void> typecheck_namespace_function_predecl(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_set(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const values, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ErrorOr<void> typecheck_struct_methods_predecl(parser::ParsedRecord const parsed_record, ids::StructId const struct_id, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>>> find_functions_with_name_in_scope(ids::ScopeId const parent_scope_id, ByteString const function_name, JaktInternal::Optional<ids::ScopeId> const root_scope_id) const;
public: bool is_class(ids::TypeId const type_id) const;
public: ErrorOr<types::CheckedVisibility> typecheck_visibility(parser::Visibility const visibility, ids::ScopeId const scope_id);
public: ErrorOr<JaktInternal::Optional<types::Value>> find_comptime_binding_in_scope(ids::ScopeId const scope_id, ByteString const name) const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_try_block(NonnullRefPtr<typename parser::ParsedStatement> const stmt, ByteString const error_name, utility::Span const error_span, parser::ParsedBlock const catch_block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<void> typecheck_trait(parser::ParsedTrait const parsed_trait, ids::TraitId const trait_id, ids::ScopeId const scope_id, bool const comptime_pass);
public: ErrorOr<void> typecheck_enum_constructor(parser::ParsedRecord const parsed_record, ids::EnumId const enum_id, ids::ScopeId const parent_scope_id);
public: ErrorOr<typechecker::FunctionMatchResult> match_function_and_resolve_args(parser::ParsedCall const call, ids::ScopeId const caller_scope_id, ids::FunctionId const candidate, types::SafetyMode const safety_mode, utility::Span const span, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const this_expr);
public: ErrorOr<ids::TypeId> unify_with_type(ids::TypeId const found_type, JaktInternal::Optional<ids::TypeId> const expected_type, utility::Span const span);
public: ErrorOr<ids::StructId> find_struct_in_prelude(ByteString const name) const;
public: bool is_numeric(ids::TypeId const type_id) const;
public: ErrorOr<ByteString> debug_description_of(ids::ScopeId const scope_id) const;
public: types::CheckedStruct get_struct(ids::StructId const id) const;
public: types::CheckedEnum get_enum(ids::EnumId const id) const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> dereference_if_needed(NonnullRefPtr<typename types::CheckedExpression> const checked_expr, utility::Span const span);
public: ErrorOr<void> dump_type_hint(ids::TypeId const type_id, utility::Span const span) const;
public: ErrorOr<void> typecheck_entity_trait_implementations(ids::ScopeId const scope_id, ids::TypeId const type_id, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> const trait_implementations, ByteString const name, utility::Span const name_span);
public: ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> fill_trait_implementation_list(JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> const parsed_impl_list, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>>& trait_implementations, ids::ScopeId const scope_id, JaktInternal::Optional<ids::ScopeId> const trait_name_scope_id_override);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_statement(NonnullRefPtr<typename parser::ParsedStatement> const statement, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_unary_negate(NonnullRefPtr<typename types::CheckedExpression> const expr, utility::Span const span, ids::TypeId const type_id);
public: ErrorOr<void> typecheck_function(parser::ParsedFunction const parsed_function, ids::ScopeId const parent_scope_id);
public: ErrorOr<void> typecheck_namespace_declarations(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<void> typecheck_struct_constructor(parser::ParsedRecord const parsed_record, ids::StructId const struct_id, ids::ScopeId const scope_id);
public: ErrorOr<ids::TypeId> resolve_type_var(ids::TypeId const type_var_type_id, ids::ScopeId const scope_id) const;
public: ErrorOr<void> check_type_argument_requirements(ids::TypeId const generic_argument, JaktInternal::DynamicArray<ids::TraitId> const constraints, utility::Span const arg_span);
public: ErrorOr<ByteString> stringify_function_prototype(ids::FunctionId const function_id);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>>> get_type_ids_from_type_hint_if_struct_ids_match(JaktInternal::Optional<ids::TypeId> const type_hint, ids::StructId const expected_struct_id) const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_generic_arguments_method_call(NonnullRefPtr<typename types::CheckedExpression> const checked_expr, parser::ParsedCall const call, ids::ScopeId const scope_id, utility::Span const span, bool const is_optional, types::SafetyMode const safety_mode);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_loop(parser::ParsedBlock const parsed_block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<NonnullRefPtr<types::Scope>> get_scope(ids::ScopeId const id) const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_indexed_tuple(NonnullRefPtr<typename parser::ParsedExpression> const expr, size_t const index, ids::ScopeId const scope_id, bool const is_optional, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>>> typecheck_forall_chunk_parameters(JaktInternal::DynamicArray<parser::ParsedGenericParameter> const chunk_parameters, ids::ScopeId const scope_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_while(NonnullRefPtr<typename parser::ParsedExpression> const condition, parser::ParsedBlock const block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<ids::TypeId> prelude_struct_type_named(ByteString const name);
public: ErrorOr<void> typecheck_alias(parser::ParsedAlias const alias, ids::ScopeId const scope_id, typechecker::ImportRestrictions const allow);
public: ErrorOr<types::CheckedUnaryOperator> typecheck_is_enum_variant(NonnullRefPtr<typename types::CheckedExpression> const checked_expr, NonnullRefPtr<typename parser::ParsedType> const inner, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const bindings, ids::ScopeId const scope_id);
public: ErrorOr<bool> add_var_to_scope(ids::ScopeId const scope_id, ByteString const name, ids::VarId const var_id, utility::Span const span);
public: ErrorOr<bool> add_comptime_binding_to_scope(ids::ScopeId const scope_id, ByteString const name, types::Value const value, utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_match(NonnullRefPtr<typename parser::ParsedExpression> const expr, JaktInternal::DynamicArray<parser::ParsedMatchCase> const cases, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ErrorOr<void> map_generic_arguments(ids::TypeId const type_id, JaktInternal::DynamicArray<ids::TypeId> const args);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_throw(NonnullRefPtr<typename parser::ParsedExpression> const expr, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<void> fill_trait_requirements(JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> const names, JaktInternal::DynamicArray<ids::TraitId>& trait_requirements, JaktInternal::DynamicArray<ids::TypeId>& trait_implementations, ids::ScopeId const scope_id);
public: ErrorOr<bool> struct_inherits_from(ids::StructId const struct_id, ids::StructId const super_struct_id, JaktInternal::Optional<JaktInternal::DynamicArray<ids::StructId>> const struct_inheritance_chain) const;
public: ErrorOr<JaktInternal::Optional<ids::FunctionId>> find_function_matching_trait_implementation_in_scope(ids::TypeId const self_type_id, ids::ScopeId const parent_scope_id, ByteString const function_name, typechecker::TraitImplementationDescriptor const& trait_descriptor);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_dictionary(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> const values, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ErrorOr<types::CheckedBlock> typecheck_block(parser::ParsedBlock const parsed_block, ids::ScopeId const parent_scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const yield_type_hint);
public: ErrorOr<void> typecheck_jakt_main(parser::ParsedFunction const parsed_function, ids::ScopeId const parent_scope_id);
public: ErrorOr<JaktInternal::Tuple<types::CheckedBinaryOperator,ids::TypeId>> typecheck_binary_operation(NonnullRefPtr<typename types::CheckedExpression> const checked_lhs, parser::BinaryOperator const op, NonnullRefPtr<typename types::CheckedExpression> const checked_rhs, ids::ScopeId const scope_id, utility::Span const span);
public: ErrorOr<void> typecheck_enum_predecl_initial(parser::ParsedRecord const parsed_record, size_t const enum_index, size_t const module_enum_len, ids::ScopeId const scope_id);
public: ErrorOr<ids::TypeId> typecheck_generic_resolved_type(ByteString const name, JaktInternal::DynamicArray<ids::TypeId> const checked_inner_types, ids::ScopeId const scope_id, utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_comptime_index(NonnullRefPtr<typename parser::ParsedExpression> const expr, NonnullRefPtr<typename parser::ParsedExpression> const index, ids::ScopeId const scope_id, bool const is_optional, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<ids::ScopeId> cache_or_process_cpp_import(jakt__path::Path const import_path, ids::ScopeId const scope_id, bool const is_c, JaktInternal::Dictionary<ByteString,ByteString> const defines);
public: ErrorOr<void> typecheck_namespace_fields(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
public: Typechecker(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, ids::ModuleId a_current_module_id, JaktInternal::Optional<ids::TypeId> a_current_struct_type_id, JaktInternal::Optional<ids::FunctionId> a_current_function_id, bool a_inside_defer, size_t a_checkidx, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, types::GenericInferences a_generic_inferences, JaktInternal::Optional<ids::TypeId> a_self_type_id, ByteString a_root_module_name, bool a_in_comptime_function_call, bool a_had_an_error, JaktInternal::Dictionary<ByteString,ids::ScopeId> a_cpp_import_cache, JaktInternal::Optional<cpp_import__none::CppImportProcessor> a_cpp_import_processor);

public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> cast_to_underlying(NonnullRefPtr<typename parser::ParsedExpression> const expr, ids::ScopeId const scope_id, NonnullRefPtr<typename parser::ParsedType> const parsed_type);
public: ErrorOr<ids::TypeId> substitute_typevars_in_type(ids::TypeId const type_id, types::GenericInferences const generic_inferences);
public: ErrorOr<ByteString> get_argument_name(JaktInternal::Tuple<ByteString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> const arg) const;
public: ErrorOr<ids::TypeId> with_qualifiers(parser::CheckedQualifiers const qualifiers, ids::TypeId const type_id);
public: ErrorOr<ids::FunctionId> typecheck_and_specialize_generic_function(ids::FunctionId const function_id, JaktInternal::DynamicArray<ids::TypeId> const generic_arguments, ids::ScopeId const parent_scope_id, JaktInternal::Optional<ids::TypeId> const this_type_id, types::GenericInferences const generic_substitutions, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const type_args, utility::Span const call_span, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>>> const args);
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> find_type_scope(ids::ScopeId const scope_id, ByteString const name) const;
public: NonnullRefPtr<types::CheckedFunction> get_function(ids::FunctionId const id) const;
public: ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<ids::ScopeId>,NonnullRefPtr<typename types::CheckedExpression>>> required_scope_id_in_hierarchy_for(NonnullRefPtr<typename types::CheckedExpression> const expr, ids::ScopeId const current_scope_id);
public: ErrorOr<JaktInternal::Optional<typechecker::TraitImplementationDescriptor>> find_any_singular_trait_implementation(ids::TypeId const type_id, JaktInternal::DynamicArray<ByteString> const trait_names, ids::ScopeId const scope_id, utility::Span const span, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const filter_for_generics);
public: ErrorOr<void> specialize_trait(ids::TraitId const trait_id, JaktInternal::DynamicArray<ids::TypeId> const generic_parameters);
public: ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,types::CheckedMatchCase,JaktInternal::Optional<ids::TypeId>>> typecheck_match_variant(parser::ParsedMatchCase const case_, ids::TypeId const subject_type_id, size_t const variant_index, JaktInternal::Optional<ids::TypeId> const final_result_type, types::CheckedEnumVariant const variant, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const variant_arguments, JaktInternal::Dictionary<ByteString,parser::ParsedPatternDefault> const default_bindings, utility::Span const arguments_span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode);
public: ErrorOr<void> include_prelude();
public: ErrorOr<ids::ModuleId> create_module(ByteString const name, bool const is_root, JaktInternal::Optional<ByteString> const path);
public: ids::ScopeId prelude_scope_id() const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_namespaced_var_or_simple_enum_constructor_call(ByteString const name, JaktInternal::DynamicArray<ByteString> const namespace_, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint, utility::Span const span);
public: ErrorOr<void> typecheck_struct_predecl(parser::ParsedRecord const parsed_record, ids::StructId const struct_id, ids::ScopeId const scope_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_unary_operation(NonnullRefPtr<typename types::CheckedExpression> const checked_expr, types::CheckedUnaryOperator const checked_op, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode);
public: ErrorOr<void> warn_about_unimplemented_nested_record(parser::ParsedRecord const record);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> infer_unsigned_int(u64 const val, utility::Span const span, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ErrorOr<ids::TypeId> strip_optional_from_type(ids::TypeId const type_id);
public: ErrorOr<JaktInternal::Optional<types::FieldRecord>> lookup_struct_field(ids::StructId const struct_id, ByteString const name) const;
public: ErrorOr<types::CheckedParameter> typecheck_parameter(parser::ParsedParameter const parameter, ids::ScopeId const scope_id, bool const first, JaktInternal::Optional<ids::TypeId> const this_arg_type_id, JaktInternal::Optional<ids::ScopeId> const check_scope);
public: ErrorOr<types::BlockControlFlow> maybe_statement_control_flow(JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const statement, types::BlockControlFlow const other_branch) const;
public: ErrorOr<JaktInternal::Optional<ids::TypeId>> unify(ids::TypeId const lhs, utility::Span const lhs_span, ids::TypeId const rhs, utility::Span const rhs_span);
public: bool is_floating(ids::TypeId const type_id) const;
public: ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> find_var_in_scope(ids::ScopeId const scope_id, ByteString const var, JaktInternal::Optional<ids::ScopeId> const root_scope_id) const;
public: ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<types::StructLikeId>,bool>> struct_like_id_from_type_id(ids::TypeId const type_id, ids::ScopeId const scope_id, utility::Span const span, bool const for_optional_chain, bool const treat_string_as_builtin);
public: ErrorOr<ids::TypeId> find_type_in_prelude(ByteString const name) const;
public: ErrorOr<bool> add_type_to_scope(ids::ScopeId const scope_id, ByteString const type_name, ids::TypeId const type_id, utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> infer_signed_int(i64 const val, utility::Span const span, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ErrorOr<void> typecheck_namespace_aliases(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id, typechecker::ImportRestrictions const allow);
public: ErrorOr<bool> add_struct_to_scope(ids::ScopeId const scope_id, ByteString const name, ids::StructId const struct_id, utility::Span const span);
public: ErrorOr<void> error(ByteString const message, utility::Span const span);
public: ErrorOr<bool> check_restricted_access(ids::ScopeId const accessor, ByteString const accessee_kind, ids::ScopeId const accessee, ByteString const name, JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> const whitelist, utility::Span const span);
public: ErrorOr<bool> check_types_for_compat(ids::TypeId const lhs_type_id, ids::TypeId const rhs_type_id, types::GenericInferences& generic_inferences, utility::Span const span);
public: ErrorOr<void> typecheck_enum_predecl(parser::ParsedRecord const parsed_record, ids::EnumId const enum_id, ids::ScopeId const scope_id);
private: ErrorOr<bool> signatures_match_impl(ids::TypeId const self_type_id, NonnullRefPtr<types::CheckedFunction> const first, NonnullRefPtr<types::CheckedFunction> const second, Function<ErrorOr<bool>(typechecker::Typechecker&, ids::TypeId, ids::TypeId)> const& types_match);
public: ErrorOr<void> check_member_access(ids::ScopeId const accessor, ids::ScopeId const accessee, NonnullRefPtr<types::CheckedVariable> const member, utility::Span const span);
public: bool is_integer(ids::TypeId const type_id) const;
public: ErrorOr<JaktInternal::Tuple<bool,JaktInternal::DynamicArray<error::JaktError>>> signatures_match(ids::TypeId const self_type_id, NonnullRefPtr<types::CheckedFunction> const first, NonnullRefPtr<types::CheckedFunction> const second);
public: ErrorOr<NonnullRefPtr<typename types::Type>> unwrap_type_from_optional_if_needed(NonnullRefPtr<typename types::Type> const type) const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_guard(NonnullRefPtr<typename parser::ParsedExpression> const expr, parser::ParsedBlock const else_block, parser::ParsedBlock const remaining_code, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: NonnullRefPtr<typename types::Type> get_type(ids::TypeId const id) const;
public: ErrorOr<void> typecheck_namespace_trait_implementations_predecl(ids::ScopeId const scope_id);
public: ErrorOr<bool> add_trait_to_scope(ids::ScopeId const scope_id, ByteString const trait_name, ids::TraitId const trait_id, utility::Span const span);
public: ErrorOr<JaktInternal::Optional<ids::ScopeId>> scope_lifetime_union(JaktInternal::Optional<ids::ScopeId> const first, JaktInternal::Optional<ids::ScopeId> const second) const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_destructuring_assignment(JaktInternal::DynamicArray<parser::ParsedVarDecl> const vars, NonnullRefPtr<typename parser::ParsedStatement> const var_decl, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<bool> is_scope_directly_accessible_from(ids::ScopeId const scope_id, ids::ScopeId const from_scope_id) const;
public: ErrorOr<void> typecheck_namespace_constructors(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_block_statement(parser::ParsedBlock const parsed_block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<ids::FunctionId> typecheck_function_predecl(parser::ParsedFunction const parsed_function, ids::ScopeId const parent_scope_id, JaktInternal::Optional<ids::TypeId> const this_arg_type_id, JaktInternal::Optional<NonnullRefPtr<types::FunctionGenerics>> generics, JaktInternal::Optional<ids::ScopeId> scope_mixin);
public: ErrorOr<ids::TypeId> find_or_add_type_id(NonnullRefPtr<typename types::Type> const type);
public: static ErrorOr<typechecker::Typechecker> typecheck(NonnullRefPtr<compiler::Compiler> compiler, parser::ParsedNamespace const parsed_namespace);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedEnumVariantBinding>>> typecheck_enum_variant_bindings(types::CheckedEnumVariant const variant, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const bindings, utility::Span const span);
public: ErrorOr<void> typecheck_struct(parser::ParsedRecord const record, ids::StructId const struct_id, ids::ScopeId const parent_scope_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_lambda(JaktInternal::DynamicArray<parser::ParsedCapture> const captures, JaktInternal::DynamicArray<parser::ParsedParameter> const params, bool const can_throw, bool const is_fat_arrow, NonnullRefPtr<typename parser::ParsedType> const return_type, parser::ParsedBlock const block, utility::Span const span, ids::ScopeId const scope_id, types::SafetyMode const safety_mode);
public: NonnullRefPtr<types::CheckedVariable> get_variable(ids::VarId const id) const;
public: ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span,NonnullRefPtr<typename types::CheckedExpression>>>> resolve_default_params(JaktInternal::DynamicArray<types::CheckedParameter> const params, bool const has_varargs, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const args, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, size_t const arg_offset, utility::Span const span);
public: ErrorOr<JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>>> find_all_implementations_of_trait(ids::TypeId const type_id, ids::TraitId const trait_id, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const filter_for_generics);
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>>> find_namespace_in_scope(ids::ScopeId const scope_id, ByteString const name, bool const treat_aliases_as_imports, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<void> typecheck_struct_fields(parser::ParsedRecord const record, ids::StructId const struct_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_call(parser::ParsedCall const call, ids::ScopeId const caller_scope_id, utility::Span const span, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const this_expr, JaktInternal::Optional<types::StructLikeId> const parent_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> type_hint, bool const must_be_enum_constructor);
public: ErrorOr<JaktInternal::DynamicArray<ids::FunctionId>> resolve_call(parser::ParsedCall const call, JaktInternal::DynamicArray<types::ResolvedNamespace> namespaces, utility::Span const span, ids::ScopeId const scope_id, bool const must_be_enum_constructor);
public: ErrorOr<void> typecheck_auto_extern_imports(JaktInternal::DynamicArray<parser::ParsedExternImport> const imports, auto const child_scope_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_if(NonnullRefPtr<typename parser::ParsedExpression> const condition, parser::ParsedBlock const then_block, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const else_statement, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<void> check_implicit_constructor_argument_access(ids::ScopeId const caller_scope_id, parser::ParsedCall const call, types::CheckedStruct const struct_);
public: ErrorOr<JaktInternal::Optional<ids::TypeId>> find_explicitly_specialized_type_in_scope(ids::ScopeId const scope_id, ByteString const name, JaktInternal::DynamicArray<ids::TypeId> const arguments, utility::Span const span);
private: public: ErrorOr<void> typecheck_enum(parser::ParsedRecord const record, ids::EnumId const enum_id, ids::ScopeId const parent_scope_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_expression_and_dereference_if_needed(NonnullRefPtr<typename parser::ParsedExpression> const expr, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint, utility::Span const span);
public: ErrorOr<JaktInternal::Optional<ids::TypeId>> find_type_in_scope(ids::ScopeId const scope_id, ByteString const name) const;
public: ErrorOr<void> set_self_type_id(ids::TypeId const type_id);
public: ErrorOr<JaktInternal::Optional<types::CheckedEnumVariant>> get_enum_variant(types::CheckedEnum const enum_, ByteString const variant_name);
public: ErrorOr<bool> scope_can_access(ids::ScopeId const accessor, ids::ScopeId const accessee) const;
public: ErrorOr<JaktInternal::DynamicArray<ids::StructId>> struct_inheritance_chain(ids::StructId const struct_id) const;
public: ErrorOr<bool> type_contains_reference(ids::TypeId const type_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_for(ByteString const iterator_name, utility::Span const name_span, bool const is_destructuring, NonnullRefPtr<typename parser::ParsedExpression> const range, parser::ParsedBlock const block, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<JaktInternal::Optional<ids::FunctionId>> find_function_matching_signature_in_scope(ids::ScopeId const parent_scope_id, parser::ParsedFunction const prototype) const;
public: ErrorOr<void> resolve_external_trait_implementations(parser::ParsedExternalTraitImplementation const implementation, ids::ScopeId const entity_scope_id, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>>& trait_implementations, ids::TypeId const for_type, ids::ScopeId const scope_id, bool const default_pass);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_array(ids::ScopeId const scope_id, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const values, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const fill_size, utility::Span const span, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ErrorOr<void> typecheck_entity_trait_implementations_predecl(ids::ScopeId const scope_id, ids::TypeId const type_id, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> const trait_implementations, ByteString const name, utility::Span const name_span);
public: ErrorOr<void> typecheck_trait_predecl(parser::ParsedTrait const parsed_trait, ids::ScopeId const scope_id);
public: ErrorOr<bool> implements_trait(ids::TypeId const type_id, ids::TraitId const trait_id, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const generic_arguments);
public: ErrorOr<void> typecheck_module_import(parser::ParsedModuleImport const import_, ids::ScopeId const scope_id);
public: ErrorOr<JaktInternal::Optional<ids::FunctionId>> typecheck_method(parser::ParsedFunction const func, types::StructLikeId const parent_id);
public: ErrorOr<void> typecheck_extern_import(parser::ParsedExternImport const import_, ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_override(parser::ParsedMethod const method, ids::ScopeId const parent_scope_id, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>>> const all_virtuals);
public: ErrorOr<types::BlockControlFlow> statement_control_flow(NonnullRefPtr<typename types::CheckedStatement> const statement) const;
public: ErrorOr<JaktInternal::Optional<ids::StructId>> find_struct_in_scope(ids::ScopeId const scope_id, ByteString const name, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<void> check_that_type_doesnt_contain_reference(ids::TypeId const type_id, utility::Span const span);
public: ErrorOr<JaktInternal::Optional<parser::ParsedNamespace>> lex_and_parse_file_contents(utility::FileId const file_id);
public: ErrorOr<bool> find_and_import_name_from_scope(ByteString const from_name, utility::Span const from_span, ByteString const to_name, utility::Span const to_span, ids::ScopeId const from_scope_id, ids::ScopeId const into_scope_id, typechecker::ImportRestrictions const allow);
public: parser::CheckedQualifiers typecheck_type_qualifiers(JaktInternal::Optional<parser::ParsedTypeQualifiers> const qualifiers) const;
public: ErrorOr<bool> validate_argument_label(types::CheckedParameter const param, ByteString const label, utility::Span const span, NonnullRefPtr<typename parser::ParsedExpression> const expr, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const default_value);
public: ErrorOr<bool> add_enum_to_scope(ids::ScopeId const scope_id, ByteString const name, ids::EnumId const enum_id, utility::Span const span);
public: ErrorOr<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>>> expand_context_for_bindings(NonnullRefPtr<typename parser::ParsedExpression> const condition, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const acc, JaktInternal::Optional<parser::ParsedBlock> const then_block, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const else_statement, ids::ScopeId const scope_id, utility::Span const span);
public: ErrorOr<JaktInternal::Optional<ids::TraitId>> find_trait_in_scope(ids::ScopeId const scope_id, ByteString const name) const;
public: NonnullRefPtr<types::Module> current_module() const;
public: ids::ScopeId root_scope_id() const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_defer(NonnullRefPtr<typename parser::ParsedStatement> const statement, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<bool> add_function_to_scope(ids::ScopeId const parent_scope_id, ByteString const name, JaktInternal::DynamicArray<ids::FunctionId> const overload_set, utility::Span const span);
public: ErrorOr<void> check_method_access(ids::ScopeId const accessor, ids::ScopeId const accessee, NonnullRefPtr<types::CheckedFunction> const method, utility::Span const span);
public: ErrorOr<ids::TypeId> final_type_resolution_form(ids::TypeId const type_id, ids::ScopeId const scope_id) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> find_scoped_functions_with_name_in_scope(ids::ScopeId const parent_scope_id, ByteString const function_name, JaktInternal::Optional<ids::ScopeId> const root_scope_id) const;
public: ErrorOr<NonnullRefPtr<interpreter::Interpreter>> interpreter();
public: ErrorOr<void> typecheck_enum_methods_predecl(parser::ParsedRecord const parsed_record, ids::EnumId const enum_id, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<void> dump_try_hint(utility::Span const span) const;
public: ErrorOr<void> typecheck_namespace_methods_predecl(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<void> typecheck_module(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
public: ErrorOr<void> error_with_hint(ByteString const message, utility::Span const span, ByteString const hint, utility::Span const hint_span);
public: bool is_subclass_of(ids::TypeId const ancestor_type_id, ids::TypeId const child_type_id) const;
public: ErrorOr<void> typecheck_namespace_predecl(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_var_decl(parser::ParsedVarDecl const var, NonnullRefPtr<typename parser::ParsedExpression> const init, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typecheck_inline_cpp(parser::ParsedBlock const block, utility::Span const span, types::SafetyMode const safety_mode);
public: bool is_struct(ids::TypeId const type_id) const;
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_expression(NonnullRefPtr<typename parser::ParsedExpression> const expr, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_indexed_struct(NonnullRefPtr<typename parser::ParsedExpression> const expr, ByteString const field_name, ids::ScopeId const scope_id, bool const is_optional, types::SafetyMode const safety_mode, utility::Span const span);
public: ErrorOr<void> typecheck_namespace_imports(parser::ParsedNamespace const parsed_namespace, ids::ScopeId const scope_id);
public: ErrorOr<jakt__path::Path> get_root_path() const;
public: ErrorOr<void> typecheck_namespace_trait_implementations(ids::ScopeId const scope_id);
public: ErrorOr<JaktInternal::Optional<typechecker::TraitImplementationDescriptor>> find_singular_trait_implementation(ids::TypeId const type_id, ByteString const trait_name, ids::ScopeId const scope_id, utility::Span const span, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const filter_for_generics);
public: ErrorOr<ids::TypeId> typecheck_typename(NonnullRefPtr<typename parser::ParsedType> const parsed_type, ids::ScopeId const scope_id, JaktInternal::Optional<ByteString> const name);
public: ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typecheck_try(NonnullRefPtr<typename parser::ParsedExpression> const expr, JaktInternal::Optional<parser::ParsedBlock> const catch_block, JaktInternal::Optional<utility::Span> const catch_span, JaktInternal::Optional<ByteString> const catch_name, ids::ScopeId const scope_id, types::SafetyMode const safety_mode, utility::Span const span, JaktInternal::Optional<ids::TypeId> const type_hint);
public: ids::TypeId infer_function_return_type(types::CheckedBlock const block) const;
public: ErrorOr<bool> scope_lifetime_subsumes(JaktInternal::Optional<ids::ScopeId> const larger, JaktInternal::Optional<ids::ScopeId> const smaller) const;
public: ErrorOr<ByteString> debug_description() const;
};struct TraitImplCheck {
  public:
public: JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<ByteString,ids::FunctionId>> missing_methods;public: JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<utility::Span,JaktInternal::DynamicArray<error::JaktError>>>> unmatched_signatures;public: JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<ByteString,utility::Span>> private_matching_methods;public: JaktInternal::Dictionary<ByteString,typechecker::AlreadyImplementedFor> already_implemented_for;public: ErrorOr<void> throw_errors(utility::Span const record_decl_span, typechecker::Typechecker& typechecker);
public: ErrorOr<void> ensure_capacity(size_t const count);
public: ErrorOr<void> register_method(ids::TypeId const self_type_id, ByteString const method_name, ids::FunctionId const method_id, typechecker::Typechecker& typechecker);
public: static ErrorOr<typechecker::TraitImplCheck> make();
public: TraitImplCheck(JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<ByteString,ids::FunctionId>> a_missing_methods, JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<utility::Span,JaktInternal::DynamicArray<error::JaktError>>>> a_unmatched_signatures, JaktInternal::Dictionary<ids::TypeId,JaktInternal::Dictionary<ByteString,utility::Span>> a_private_matching_methods, JaktInternal::Dictionary<ByteString,typechecker::AlreadyImplementedFor> a_already_implemented_for);

public: ErrorOr<void> register_trait(ids::TypeId const trait_type_id, ByteString const trait_name, types::CheckedTraitRequirements const requirements);
public: ErrorOr<ByteString> debug_description() const;
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
template<>struct Jakt::Formatter<Jakt::typechecker::AlreadyImplementedFor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::AlreadyImplementedFor const& value) {
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
template<typename K,typename V>struct Jakt::Formatter<Jakt::typechecker::InternalDictionaryProduct<K, V>
> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::InternalDictionaryProduct<K, V>
 const& value) {
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
template<>struct Jakt::Formatter<Jakt::typechecker::Typechecker> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::Typechecker const& value) {
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
