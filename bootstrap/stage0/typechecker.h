#pragma once
#include <lib.h>
#include "cpp_import__none.h"
#include "cpp_import__common.h"
#include "interpreter.h"
#include "types.h"
#include "ids.h"
#include "parser.h"
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform.h"
#include "jakt__arguments.h"
#include "jakt__prelude__operators.h"
namespace Jakt {
namespace typechecker {
struct TraitImplementationDescriptor;
struct ImportRestrictions;
template <typename K,typename V>struct InternalDictionaryProduct;
struct Typechecker;
struct AlreadyImplementedFor;
struct TraitImplCheck;
struct FunctionMatchResult;

struct TypeHint;

struct BreakContinueLegalityTracker;

struct ReturnLegalityTracker;

struct NumericOrStringValue;

ErrorOr<JaktInternal::Dictionary<ByteString,ByteString>> defines_from(JaktInternal::DynamicArray<Jakt::parser::IncludeAction> const actions);

ErrorOr<void> dump_scope(Jakt::ids::ScopeId const scope_id, NonnullRefPtr<Jakt::types::CheckedProgram> const& program, i64 const indent);

}
namespace typechecker {
struct FunctionMatchResult {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> args;
JaktInternal::Optional<Jakt::ids::TypeId> maybe_this_type_id;
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> used_generic_inferences;
i64 specificity;
} MatchSuccess;
struct {
JaktInternal::DynamicArray<Jakt::error::JaktError> errors;
} MatchError;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static FunctionMatchResult MatchSuccess(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> args, JaktInternal::Optional<Jakt::ids::TypeId> maybe_this_type_id, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> used_generic_inferences, i64 specificity);
[[nodiscard]] static FunctionMatchResult MatchError(JaktInternal::DynamicArray<Jakt::error::JaktError> errors);
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
struct TypeHint {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
Jakt::ids::TypeId type_id;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static TypeHint MustBe(Jakt::ids::TypeId type_id);
[[nodiscard]] static TypeHint CouldBe(Jakt::ids::TypeId type_id);
~TypeHint();
TypeHint& operator=(TypeHint const &);
TypeHint& operator=(TypeHint &&);
TypeHint(TypeHint const&);
TypeHint(TypeHint &&);
private: void __jakt_destroy_variant();
public:
private:
TypeHint() {};
};
struct TraitImplementationDescriptor {
  public:
public: Jakt::ids::TraitId trait_id;public: ByteString trait_name;public: JaktInternal::DynamicArray<Jakt::ids::TypeId> implemented_type_args;public: TraitImplementationDescriptor(Jakt::ids::TraitId a_trait_id, ByteString a_trait_name, JaktInternal::DynamicArray<Jakt::ids::TypeId> a_implemented_type_args);

public: ByteString debug_description() const;
};struct ImportRestrictions {
  public:
public: bool functions;public: bool structs;public: bool enums;public: bool types;public: bool traits;public: bool namespaces;public: static Jakt::typechecker::ImportRestrictions all();
public: ImportRestrictions(bool a_functions, bool a_structs, bool a_enums, bool a_types, bool a_traits, bool a_namespaces);

public: ByteString debug_description() const;
};struct BreakContinueLegalityTracker {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static BreakContinueLegalityTracker None();
[[nodiscard]] static BreakContinueLegalityTracker AnyLoop();
[[nodiscard]] static BreakContinueLegalityTracker Defer();
~BreakContinueLegalityTracker();
BreakContinueLegalityTracker& operator=(BreakContinueLegalityTracker const &);
BreakContinueLegalityTracker& operator=(BreakContinueLegalityTracker &&);
BreakContinueLegalityTracker(BreakContinueLegalityTracker const&);
BreakContinueLegalityTracker(BreakContinueLegalityTracker &&);
private: void __jakt_destroy_variant();
public:
private:
BreakContinueLegalityTracker() {};
};
struct ReturnLegalityTracker {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ReturnLegalityTracker None();
[[nodiscard]] static ReturnLegalityTracker Lambda();
[[nodiscard]] static ReturnLegalityTracker Defer();
~ReturnLegalityTracker();
ReturnLegalityTracker& operator=(ReturnLegalityTracker const &);
ReturnLegalityTracker& operator=(ReturnLegalityTracker &&);
ReturnLegalityTracker(ReturnLegalityTracker const&);
ReturnLegalityTracker(ReturnLegalityTracker &&);
private: void __jakt_destroy_variant();
public:
private:
ReturnLegalityTracker() {};
};
struct NumericOrStringValue {
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
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
template <typename K,typename V>struct InternalDictionaryProduct {
  public:
public: JaktInternal::Dictionary<K,JaktInternal::DynamicArray<V>> dict;public: JaktInternal::Dictionary<K,V> current;public: JaktInternal::Dictionary<K,size_t> current_index;public: bool done;public: JaktInternal::Optional<JaktInternal::Dictionary<K,V>> next() {
{
if (((*this).done)){
return JaktInternal::OptionalNone();
}
JaktInternal::Dictionary<K,V> next = Dictionary<K, V>::create_with_entries({});
{
JaktInternal::ArrayIterator<K> _magic = ((((((*this).dict)).keys())).iterator());
for (;;){
JaktInternal::Optional<K> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
K key = (_magic_value.value());
{
V const value = ((((((*this).dict))[key]))[((((*this).current_index))[key])]);
next.set(key, value);
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
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(JaktInternal::checked_add(index,static_cast<size_t>(1ULL)),((values).size()))){
((*this).current_index).set(key, JaktInternal::checked_add(index,static_cast<size_t>(1ULL)));
return next;
}
((*this).current_index).set(key, static_cast<size_t>(0ULL));
}

}
}

(((*this).done) = true);
return next;
}
}
public: InternalDictionaryProduct(JaktInternal::Dictionary<K,JaktInternal::DynamicArray<V>> a_dict, JaktInternal::Dictionary<K,V> a_current, JaktInternal::Dictionary<K,size_t> a_current_index, bool a_done): dict(move(a_dict)), current(move(a_current)), current_index(move(a_current_index)), done(move(a_done)){}

public: ByteString debug_description() const { auto builder = ByteStringBuilder::create();builder.append("InternalDictionaryProduct("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dict: {}, ", dict);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current: {}, ", current);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_index: {}, ", current_index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("done: {}", done);
}
builder.append(")"sv);return builder.to_string(); }
};struct Typechecker {
  public:
public: NonnullRefPtr<Jakt::compiler::Compiler> compiler;public: NonnullRefPtr<Jakt::types::CheckedProgram> program;public: Jakt::ids::ModuleId current_module_id;public: JaktInternal::Optional<Jakt::ids::TypeId> current_struct_type_id;public: JaktInternal::Optional<Jakt::ids::FunctionId> current_function_id;public: Jakt::typechecker::BreakContinueLegalityTracker break_continue_tracker;public: Jakt::typechecker::ReturnLegalityTracker return_tracker;public: bool ignore_errors;public: bool dump_type_hints;public: bool dump_try_hints;public: u64 lambda_count;public: Jakt::types::GenericInferences generic_inferences;public: JaktInternal::Optional<Jakt::ids::TypeId> self_type_id;public: ByteString root_module_name;public: bool in_comptime_function_call;public: bool had_an_error;public: JaktInternal::Dictionary<ByteString,Jakt::ids::ScopeId> cpp_import_cache;public: JaktInternal::Optional<Jakt::cpp_import__none::CppImportProcessor> cpp_import_processor;public: u64 temp_var_count;public: Jakt::types::CheckedBlock current_block;public: void set_self_type_id(Jakt::ids::TypeId const type_id);
public: ErrorOr<ByteString> type_name(Jakt::ids::TypeId const type_id, bool const debug_mode) const;
public: ErrorOr<void> dump_type_hint(Jakt::ids::TypeId const type_id, Jakt::utility::Span const span) const;
public: void dump_try_hint(Jakt::utility::Span const span) const;
public: static ErrorOr<Jakt::typechecker::Typechecker> typecheck(NonnullRefPtr<Jakt::compiler::Compiler> compiler, Jakt::parser::ParsedNamespace const parsed_namespace);
public: NonnullRefPtr<Jakt::types::CheckedFunction> get_function(Jakt::ids::FunctionId const id) const;
public: NonnullRefPtr<Jakt::types::CheckedVariable> get_variable(Jakt::ids::VarId const id) const;
public: NonnullRefPtr<Jakt::types::CheckedTrait> get_trait(Jakt::ids::TraitId const id) const;
public: NonnullRefPtr<typename Jakt::types::Type> get_type(Jakt::ids::TypeId const id) const;
public: Jakt::types::CheckedEnum get_enum(Jakt::ids::EnumId const id) const;
public: Jakt::types::CheckedStruct get_struct(Jakt::ids::StructId const id) const;
public: NonnullRefPtr<Jakt::types::Scope> get_scope(Jakt::ids::ScopeId const id) const;
public: ErrorOr<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>>> find_var_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const var, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope_id) const;
public: JaktInternal::Optional<Jakt::types::FieldRecord> lookup_struct_field(Jakt::ids::StructId const struct_id, ByteString const name) const;
public: ErrorOr<JaktInternal::Optional<Jakt::types::Value>> find_comptime_binding_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name) const;
public: Jakt::jakt__path::Path get_root_path() const;
public: Jakt::ids::ScopeId prelude_scope_id() const;
public: Jakt::ids::ScopeId root_scope_id() const;
public: NonnullRefPtr<Jakt::types::Module> current_module() const;
public: bool scope_can_access(Jakt::ids::ScopeId const accessor, Jakt::ids::ScopeId const accessee) const;
public: void error(ByteString const message, Jakt::utility::Span const span);
public: void error_with_hint(ByteString const message, Jakt::utility::Span const span, ByteString const hint, Jakt::utility::Span const hint_span);
public: bool is_integer(Jakt::ids::TypeId const type_id) const;
public: bool is_floating(Jakt::ids::TypeId const type_id) const;
public: bool is_numeric(Jakt::ids::TypeId const type_id) const;
public: Jakt::ids::ScopeId create_scope(JaktInternal::Optional<Jakt::ids::ScopeId> const parent_scope_id, bool const can_throw, ByteString const debug_name, bool const for_block);
public: Jakt::ids::ModuleId create_module(ByteString const name, bool const is_root, JaktInternal::Optional<ByteString> const path);
private: ErrorOr<JaktInternal::DynamicArray<u8>> get_prelude_contents() const;
public: ErrorOr<void> include_prelude();
public: ErrorOr<JaktInternal::Optional<Jakt::parser::ParsedNamespace>> lex_and_parse_file_contents(Jakt::utility::FileId const file_id);
public: ErrorOr<Jakt::ids::StructId> find_struct_in_prelude(ByteString const name) const;
public: ErrorOr<Jakt::ids::TypeId> prelude_struct_type_named(ByteString const name);
public: ErrorOr<Jakt::ids::TypeId> find_type_in_prelude(ByteString const name) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::TypeId>> unify(Jakt::ids::TypeId const lhs, Jakt::utility::Span const lhs_span, Jakt::ids::TypeId const rhs, Jakt::utility::Span const rhs_span);
public: ErrorOr<Jakt::ids::TypeId> unify_with_type(Jakt::ids::TypeId const found_type, JaktInternal::Optional<Jakt::ids::TypeId> const expected_type, Jakt::utility::Span const span);
public: Jakt::ids::TypeId find_or_add_type_id(NonnullRefPtr<typename Jakt::types::Type> const type);
public: ErrorOr<JaktInternal::Optional<Jakt::ids::TypeId>> find_type_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::TraitId>> find_trait_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name) const;
public: ErrorOr<JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor>> find_singular_trait_implementation(Jakt::ids::TypeId const type_id, ByteString const trait_name, Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics);
public: ErrorOr<JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor>> find_any_singular_trait_implementation(Jakt::ids::TypeId const type_id, JaktInternal::DynamicArray<ByteString> const trait_names, Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics);
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>> find_type_scope(Jakt::ids::ScopeId const scope_id, ByteString const name) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>> find_namespace_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const treat_aliases_as_imports, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<bool> add_struct_to_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, Jakt::ids::StructId const struct_id, Jakt::utility::Span const span);
public: bool add_enum_to_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, Jakt::ids::EnumId const enum_id, Jakt::utility::Span const span);
public: ErrorOr<bool> add_type_to_scope(Jakt::ids::ScopeId const scope_id, ByteString const type_name, Jakt::ids::TypeId const type_id, Jakt::utility::Span const span);
public: ErrorOr<bool> add_trait_to_scope(Jakt::ids::ScopeId const scope_id, ByteString const trait_name, Jakt::ids::TraitId const trait_id, Jakt::utility::Span const span);
public: bool add_function_to_scope(Jakt::ids::ScopeId const parent_scope_id, ByteString const name, JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set, Jakt::utility::Span const span);
public: bool add_var_to_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, Jakt::ids::VarId const var_id, Jakt::utility::Span const span);
public: bool add_comptime_binding_to_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, Jakt::types::Value const value, Jakt::utility::Span const span);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> find_functions_with_name_in_scope(Jakt::ids::ScopeId const parent_scope_id, ByteString const function_name, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope_id) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>> find_scoped_functions_with_name_in_scope(Jakt::ids::ScopeId const parent_scope_id, ByteString const function_name, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope_id) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> find_function_matching_signature_in_scope(Jakt::ids::ScopeId const parent_scope_id, Jakt::parser::ParsedFunction const prototype) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> find_function_matching_trait_implementation_in_scope(Jakt::ids::TypeId const self_type_id, Jakt::ids::ScopeId const parent_scope_id, ByteString const function_name, Jakt::typechecker::TraitImplementationDescriptor const& trait_descriptor);
public: ErrorOr<JaktInternal::Optional<Jakt::ids::StructId>> find_struct_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<Jakt::ids::TypeId> unwrap_type_id_from_optional_if_needed(Jakt::ids::TypeId const type_id) const;
public: ErrorOr<NonnullRefPtr<typename Jakt::types::Type>> unwrap_type_from_optional_if_needed(NonnullRefPtr<typename Jakt::types::Type> const type) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>>> get_type_ids_from_type_hint_if_struct_ids_match(Jakt::ids::TypeId const type_hint_id, Jakt::ids::StructId const expected_struct_id) const;
public: ErrorOr<void> typecheck_module(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id);
public: void collect_exports(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<Jakt::types::CheckedVisibility> typecheck_visibility(Jakt::parser::Visibility const visibility, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_namespace_fields(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> warn_about_unimplemented_nested_record(Jakt::parser::ParsedRecord const record);
public: ErrorOr<void> typecheck_struct_fields(Jakt::parser::ParsedRecord const record, Jakt::ids::StructId const struct_id);
public: ErrorOr<void> typecheck_module_import(Jakt::parser::ParsedModuleImport const import_, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<bool> find_and_import_name_from_scope(ByteString const from_name, Jakt::utility::Span const from_span, ByteString const to_name, Jakt::utility::Span const to_span, Jakt::ids::ScopeId const from_scope_id, Jakt::ids::ScopeId const into_scope_id, Jakt::typechecker::ImportRestrictions const allow);
public: ErrorOr<Jakt::ids::ScopeId> cache_or_process_cpp_import(Jakt::jakt__path::Path const import_path, Jakt::ids::ScopeId const scope_id, bool const is_c, JaktInternal::Dictionary<ByteString,ByteString> const defines);
public: ErrorOr<void> typecheck_extern_import(Jakt::parser::ParsedExternImport const import_, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_namespace_imports(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_auto_extern_imports(JaktInternal::DynamicArray<Jakt::parser::ParsedExternImport> const imports, auto const child_scope_id);
public: ErrorOr<void> typecheck_namespace_constructors(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_namespace_aliases(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id, Jakt::typechecker::ImportRestrictions const allow);
public: ErrorOr<void> typecheck_alias(Jakt::parser::ParsedAlias const alias, Jakt::ids::ScopeId const scope_id, Jakt::typechecker::ImportRestrictions const allow);
public: ErrorOr<void> typecheck_namespace_function_predecl(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<void> typecheck_namespace_predecl(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>>> typecheck_forall_chunk_parameters(JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> const chunk_parameters, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_namespace_methods_predecl(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<void> resolve_external_trait_implementations(Jakt::parser::ParsedExternalTraitImplementation const implementation, Jakt::ids::ScopeId const entity_scope_id, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>& trait_implementations, Jakt::ids::TypeId const for_type, Jakt::ids::ScopeId const scope_id, bool const default_pass);
public: ErrorOr<void> typecheck_trait_predecl(Jakt::parser::ParsedTrait const parsed_trait, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_trait(Jakt::parser::ParsedTrait const parsed_trait, Jakt::ids::TraitId const trait_id, Jakt::ids::ScopeId const scope_id, bool const comptime_pass);
public: ErrorOr<void> typecheck_enum_predecl_initial(Jakt::parser::ParsedRecord const parsed_record, size_t const enum_index, size_t const module_enum_len, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_enum_predecl(Jakt::parser::ParsedRecord const parsed_record, Jakt::ids::EnumId const enum_id, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_enum_methods_predecl(Jakt::parser::ParsedRecord const parsed_record, Jakt::ids::EnumId const enum_id, Jakt::ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: JaktInternal::DynamicArray<Jakt::ids::StructId> struct_inheritance_chain(Jakt::ids::StructId const struct_id) const;
public: bool struct_inherits_from(Jakt::ids::StructId const struct_id, Jakt::ids::StructId const super_struct_id, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::StructId>> const struct_inheritance_chain) const;
public: ErrorOr<void> typecheck_struct_constructor(Jakt::parser::ParsedRecord const parsed_record, Jakt::ids::StructId const struct_id, Jakt::ids::ScopeId const scope_id);
public: bool is_class(Jakt::ids::TypeId const type_id) const;
public: bool is_struct(Jakt::ids::TypeId const type_id) const;
public: ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> fill_trait_implementation_list(JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> const parsed_impl_list, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>& trait_implementations, Jakt::ids::ScopeId const scope_id, JaktInternal::Optional<Jakt::ids::ScopeId> const trait_name_scope_id_override);
public: ErrorOr<void> specialize_trait(Jakt::ids::TraitId const trait_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters);
public: ErrorOr<void> typecheck_struct_predecl(Jakt::parser::ParsedRecord const parsed_record, Jakt::ids::StructId const struct_id, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_struct_methods_predecl(Jakt::parser::ParsedRecord const parsed_record, Jakt::ids::StructId const struct_id, Jakt::ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<void> typecheck_struct_predecl_initial(Jakt::parser::ParsedRecord const parsed_record, size_t const struct_index, size_t const module_struct_len, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_entity_trait_implementations_predecl(Jakt::ids::ScopeId const scope_id, Jakt::ids::TypeId const type_id, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const trait_implementations, ByteString const name, Jakt::utility::Span const name_span);
public: ErrorOr<void> typecheck_entity_trait_implementations(Jakt::ids::ScopeId const scope_id, Jakt::ids::TypeId const type_id, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const trait_implementations, ByteString const name, Jakt::utility::Span const name_span);
public: ErrorOr<void> typecheck_namespace_trait_implementations_predecl(Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_namespace_trait_implementations(Jakt::ids::ScopeId const scope_id);
public: ErrorOr<void> typecheck_namespace_declarations(Jakt::parser::ParsedNamespace const parsed_namespace, Jakt::ids::ScopeId const scope_id, bool const comptime_pass, bool const generic_pass);
public: ErrorOr<void> typecheck_enum_constructor(Jakt::parser::ParsedRecord const parsed_record, Jakt::ids::EnumId const enum_id, Jakt::ids::ScopeId const parent_scope_id);
public: ErrorOr<void> typecheck_enum(Jakt::parser::ParsedRecord const record, Jakt::ids::EnumId const enum_id, Jakt::ids::ScopeId const parent_scope_id);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> cast_to_underlying(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, Jakt::ids::ScopeId const scope_id, NonnullRefPtr<typename Jakt::parser::ParsedType> const parsed_type);
public: ErrorOr<void> typecheck_struct(Jakt::parser::ParsedRecord const record, Jakt::ids::StructId const struct_id, Jakt::ids::ScopeId const parent_scope_id);
public: ErrorOr<void> typecheck_override(Jakt::parser::ParsedMethod const method, Jakt::ids::ScopeId const parent_scope_id, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>>> const all_virtuals);
public: ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> typecheck_method(Jakt::parser::ParsedFunction const func, Jakt::types::StructLikeId const parent_id);
public: ErrorOr<Jakt::types::CheckedParameter> typecheck_parameter(Jakt::parser::ParsedParameter const parameter, Jakt::ids::ScopeId const scope_id, bool const first, JaktInternal::Optional<Jakt::ids::TypeId> const this_arg_type_id, JaktInternal::Optional<Jakt::ids::ScopeId> const check_scope);
public: ErrorOr<void> fill_trait_requirements(JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> const names, JaktInternal::DynamicArray<Jakt::ids::TraitId>& trait_requirements, JaktInternal::DynamicArray<Jakt::ids::TypeId>& trait_implementations, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<Jakt::ids::FunctionId> typecheck_function_predecl(Jakt::parser::ParsedFunction const parsed_function, Jakt::ids::ScopeId const parent_scope_id, JaktInternal::Optional<Jakt::ids::TypeId> const this_arg_type_id, JaktInternal::Optional<NonnullRefPtr<Jakt::types::FunctionGenerics>> generics, JaktInternal::Optional<Jakt::types::ResolutionMixin> scope_mixin);
public: ErrorOr<void> check_that_type_doesnt_contain_reference(Jakt::ids::TypeId const type_id, Jakt::utility::Span const span);
public: bool type_contains_reference(Jakt::ids::TypeId const type_id);
public: ErrorOr<void> check_type_argument_requirements(Jakt::ids::TypeId const generic_argument, JaktInternal::DynamicArray<Jakt::ids::TraitId> const constraints, Jakt::utility::Span const arg_span, Jakt::ids::ScopeId const scope_id);
public: ErrorOr<Jakt::ids::FunctionId> typecheck_and_specialize_generic_function(Jakt::ids::FunctionId const function_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_arguments, Jakt::ids::ScopeId const parent_scope_id, JaktInternal::Optional<Jakt::ids::TypeId> const this_type_id, Jakt::types::GenericInferences const generic_substitutions, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> const type_args, Jakt::utility::Span const call_span, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>> const args);
public: ErrorOr<void> typecheck_jakt_main(Jakt::parser::ParsedFunction const parsed_function, Jakt::ids::ScopeId const parent_scope_id);
public: Jakt::ids::TypeId infer_function_return_type(Jakt::types::CheckedBlock const block) const;
public: ErrorOr<void> typecheck_function(Jakt::parser::ParsedFunction const parsed_function, Jakt::ids::ScopeId const parent_scope_id);
public: ErrorOr<Jakt::ids::TypeId> choose_broader_type_id(Jakt::ids::TypeId const original_type_id, Jakt::ids::TypeId const potential_type_id, Jakt::types::GenericInferences& generic_inferences, Jakt::utility::Span const span);
public: ErrorOr<bool> check_types_for_compat(Jakt::ids::TypeId const lhs_type_id, Jakt::typechecker::TypeHint const rhs_type_hint, Jakt::types::GenericInferences& generic_inferences, Jakt::utility::Span const span);
public: ErrorOr<bool> check_types_for_compat(Jakt::typechecker::TypeHint const lhs_type_hint, Jakt::ids::TypeId const rhs_type_id, Jakt::types::GenericInferences& generic_inferences, Jakt::utility::Span const span);
public: ErrorOr<bool> check_types_for_compat(Jakt::ids::TypeId const lhs_type_id, Jakt::ids::TypeId const rhs_type_id, Jakt::types::GenericInferences& generic_inferences, Jakt::utility::Span const span);
public: bool is_subclass_of(Jakt::ids::TypeId const ancestor_type_id, Jakt::ids::TypeId const child_type_id) const;
public: ErrorOr<Jakt::ids::TypeId> substitute_typevars_in_type(Jakt::ids::TypeId const type_id, Jakt::types::GenericInferences const generic_inferences);
public: ErrorOr<Jakt::types::CheckedBlock> typecheck_block(Jakt::parser::ParsedBlock const parsed_block, Jakt::ids::ScopeId const parent_scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const yield_type_hint);
public: ByteString debug_description_of(Jakt::ids::ScopeId const scope_id) const;
public: Jakt::parser::CheckedQualifiers typecheck_type_qualifiers(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> const qualifiers) const;
public: ErrorOr<Jakt::ids::TypeId> typecheck_typename(NonnullRefPtr<typename Jakt::parser::ParsedType> const parsed_type, Jakt::ids::ScopeId const scope_id, JaktInternal::Optional<ByteString> const name, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: Jakt::ids::TypeId with_qualifiers(Jakt::parser::CheckedQualifiers const qualifiers, Jakt::ids::TypeId const type_id);
public: ErrorOr<void> ensure_type_implements_trait(Jakt::ids::TypeId const type_id, ByteString const trait_name, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics, Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span);
public: ErrorOr<JaktInternal::Optional<Jakt::ids::TypeId>> find_explicitly_specialized_type_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, JaktInternal::DynamicArray<Jakt::ids::TypeId> const arguments, Jakt::utility::Span const span);
public: ErrorOr<Jakt::ids::TypeId> typecheck_generic_resolved_type(ByteString const name, JaktInternal::DynamicArray<Jakt::ids::TypeId> const checked_inner_types, Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_unary_operation(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr, Jakt::types::CheckedUnaryOperator const checked_op, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_unary_negate(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr, Jakt::utility::Span const span, Jakt::ids::TypeId const type_id);
public: ErrorOr<JaktInternal::Tuple<Jakt::types::CheckedBinaryOperator,Jakt::ids::TypeId>> typecheck_binary_operation(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_lhs, Jakt::parser::BinaryOperator const op, NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_rhs, Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_statement(NonnullRefPtr<typename Jakt::parser::ParsedStatement> const statement, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_yield(JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const expr, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: NonnullRefPtr<typename Jakt::types::CheckedStatement> typecheck_continue(Jakt::utility::Span const span);
public: NonnullRefPtr<typename Jakt::types::CheckedStatement> typecheck_break(Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_guard(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, Jakt::parser::ParsedBlock const else_block, Jakt::parser::ParsedBlock const remaining_code, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_for(ByteString const iterator_name, Jakt::utility::Span const name_span, bool const is_destructuring, NonnullRefPtr<typename Jakt::parser::ParsedExpression> const range, Jakt::parser::ParsedBlock const block, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>>> expand_context_for_bindings(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const condition, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const acc, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>& pre_condition, JaktInternal::Optional<Jakt::parser::ParsedBlock> const then_block, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const else_statement, Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span);
public: public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_if(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const condition, Jakt::parser::ParsedBlock const then_block, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const else_statement, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_destructuring_assignment(JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl> const vars, NonnullRefPtr<typename Jakt::parser::ParsedStatement> const var_decl, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter();
public: bool scope_lifetime_subsumes(JaktInternal::Optional<Jakt::ids::ScopeId> const larger, JaktInternal::Optional<Jakt::ids::ScopeId> const smaller) const;
public: JaktInternal::Optional<Jakt::ids::ScopeId> scope_lifetime_union(JaktInternal::Optional<Jakt::ids::ScopeId> const first, JaktInternal::Optional<Jakt::ids::ScopeId> const second) const;
public: ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> required_scope_id_in_hierarchy_for(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr, Jakt::ids::ScopeId const current_scope_id);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_var_decl(Jakt::parser::ParsedVarDecl const var, NonnullRefPtr<typename Jakt::parser::ParsedExpression> const init, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_while(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const condition, Jakt::parser::ParsedBlock const block, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_try_block(NonnullRefPtr<typename Jakt::parser::ParsedStatement> const stmt, ByteString const error_name, Jakt::utility::Span const error_span, Jakt::parser::ParsedBlock const catch_block, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_try(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, JaktInternal::Optional<Jakt::parser::ParsedBlock> const catch_block, JaktInternal::Optional<Jakt::utility::Span> const catch_span, JaktInternal::Optional<ByteString> const catch_name, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_throw(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_loop(Jakt::parser::ParsedBlock const parsed_block, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_defer(NonnullRefPtr<typename Jakt::parser::ParsedStatement> const statement, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_block_statement(Jakt::parser::ParsedBlock const parsed_block, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_inline_cpp(Jakt::parser::ParsedBlock const block, Jakt::utility::Span const span, Jakt::types::SafetyMode const safety_mode);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> typecheck_return(JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const expr, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> dereference_if_needed(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_expression_and_dereference_if_needed(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint, Jakt::utility::Span const span);
public: void map_generic_arguments(Jakt::ids::TypeId const type_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> const args);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_indexed_struct(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, ByteString const field_name, Jakt::ids::ScopeId const scope_id, bool const is_optional, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_indexed_tuple(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, size_t const index, Jakt::ids::ScopeId const scope_id, bool const is_optional, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_comptime_index(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, NonnullRefPtr<typename Jakt::parser::ParsedExpression> const index, Jakt::ids::ScopeId const scope_id, bool const is_optional, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span);
public: ErrorOr<void> check_member_access(Jakt::ids::ScopeId const accessor, Jakt::ids::ScopeId const accessee, NonnullRefPtr<Jakt::types::CheckedVariable> const member, Jakt::utility::Span const span);
public: ErrorOr<void> check_method_access(Jakt::ids::ScopeId const accessor, Jakt::ids::ScopeId const accessee, NonnullRefPtr<Jakt::types::CheckedFunction> const method, Jakt::utility::Span const span);
public: ErrorOr<bool> check_restricted_access(Jakt::ids::ScopeId const accessor, ByteString const accessee_kind, Jakt::ids::ScopeId const accessee, ByteString const name, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> const whitelist, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> infer_signed_int(i64 const val, Jakt::utility::Span const span, JaktInternal::Optional<Jakt::ids::TypeId> const type_hint_id);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> infer_unsigned_int(u64 const val, Jakt::utility::Span const span, JaktInternal::Optional<Jakt::ids::TypeId> const type_hint_id);
public: ErrorOr<Jakt::ids::TypeId> strip_optional_from_type(Jakt::ids::TypeId const type_id);
public: ErrorOr<Jakt::ids::TypeId> final_type_resolution_form(Jakt::ids::TypeId const type_id, Jakt::ids::ScopeId const scope_id) const;
public: ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>> struct_like_id_from_type_id(Jakt::ids::TypeId const type_id, Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span, bool const for_optional_chain, bool const treat_string_as_builtin);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_expression(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_must(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: ErrorOr<Jakt::types::CheckedUnaryOperator> typecheck_is_enum_variant(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr, NonnullRefPtr<typename Jakt::parser::ParsedType> const inner, JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const bindings, Jakt::ids::ScopeId const scope_id);
public: JaktInternal::Optional<Jakt::types::CheckedEnumVariant> get_enum_variant(Jakt::types::CheckedEnum const enum_, ByteString const variant_name);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding>>> typecheck_enum_variant_bindings(Jakt::types::CheckedEnumVariant const variant, JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const bindings, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_lambda(JaktInternal::DynamicArray<Jakt::parser::ParsedCapture> const captures, JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> const params, bool const can_throw, bool const is_fat_arrow, NonnullRefPtr<typename Jakt::parser::ParsedType> const return_type, Jakt::parser::ParsedBlock const block, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_namespaced_var_or_simple_enum_constructor_call(ByteString const name, JaktInternal::DynamicArray<ByteString> const namespace_, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_array(Jakt::ids::ScopeId const scope_id, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const values, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const fill_size, Jakt::utility::Span const span, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_set(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const values, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_generic_arguments_method_call(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr, Jakt::parser::ParsedCall const call, Jakt::ids::ScopeId const scope_id, Jakt::utility::Span const span, bool const is_optional, Jakt::types::SafetyMode const safety_mode);
public: ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::types::CheckedMatchCase,JaktInternal::Optional<Jakt::ids::TypeId>,bool>> typecheck_match_variant(Jakt::parser::ParsedMatchCase const case_, Jakt::ids::TypeId const subject_type_id, size_t const variant_index, JaktInternal::Optional<Jakt::ids::TypeId> const final_result_type, Jakt::types::CheckedEnumVariant const variant, JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const variant_arguments, JaktInternal::Dictionary<ByteString,Jakt::parser::ParsedPatternDefault> const default_bindings, Jakt::utility::Span const arguments_span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_match(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, JaktInternal::DynamicArray<Jakt::parser::ParsedMatchCase> const cases, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: ErrorOr<JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool>> typecheck_match_body(Jakt::parser::ParsedMatchBody const body, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, Jakt::types::GenericInferences& generic_inferences, JaktInternal::Optional<Jakt::ids::TypeId> const final_result_type, Jakt::utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_dictionary(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const values, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint);
public: ErrorOr<bool> is_scope_directly_accessible_from(Jakt::ids::ScopeId const scope_id, Jakt::ids::ScopeId const from_scope_id) const;
public: ErrorOr<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> resolve_call(Jakt::parser::ParsedCall const call, JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> namespaces, Jakt::utility::Span const span, Jakt::ids::ScopeId const scope_id, bool const must_be_enum_constructor);
public: ErrorOr<Jakt::typechecker::FunctionMatchResult> match_function_and_resolve_args(Jakt::parser::ParsedCall const call, Jakt::ids::ScopeId const caller_scope_id, Jakt::ids::FunctionId const candidate, Jakt::types::SafetyMode const safety_mode, Jakt::utility::Span const span, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const this_expr);
public: ErrorOr<ByteString> stringify_function_prototype(Jakt::ids::FunctionId const function_id);
public: ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> typecheck_call(Jakt::parser::ParsedCall const call, Jakt::ids::ScopeId const caller_scope_id, Jakt::utility::Span const span, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const this_expr, JaktInternal::Optional<Jakt::types::StructLikeId> const parent_id, Jakt::types::SafetyMode const safety_mode, JaktInternal::Optional<Jakt::typechecker::TypeHint> type_hint, bool const must_be_enum_constructor);
public: ErrorOr<void> check_implicit_constructor_argument_access(Jakt::ids::ScopeId const caller_scope_id, Jakt::parser::ParsedCall const call, Jakt::types::CheckedStruct const struct_);
public: ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>> resolve_default_params(JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const params, bool const has_varargs, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const args, Jakt::ids::ScopeId const scope_id, Jakt::types::SafetyMode const safety_mode, size_t const arg_offset, Jakt::utility::Span const span);
public: ErrorOr<Jakt::ids::TypeId> resolve_type_var(Jakt::ids::TypeId const type_var_type_id, Jakt::ids::ScopeId const scope_id) const;
public: bool validate_argument_label(Jakt::types::CheckedParameter const param, ByteString const label, Jakt::utility::Span const span, NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const default_value);
public: ByteString get_argument_name(JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const arg) const;
public: ErrorOr<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>> find_all_implementations_of_trait(Jakt::ids::TypeId const type_id, Jakt::ids::TraitId const trait_id, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics);
public: ErrorOr<bool> implements_trait(Jakt::ids::TypeId const type_id, Jakt::ids::TraitId const trait_id, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const generic_arguments);
public: ErrorOr<JaktInternal::Tuple<bool,JaktInternal::DynamicArray<Jakt::error::JaktError>>> signatures_match(Jakt::ids::TypeId const self_type_id, NonnullRefPtr<Jakt::types::CheckedFunction> const first, NonnullRefPtr<Jakt::types::CheckedFunction> const second);
private: ErrorOr<bool> signatures_match_impl(Jakt::ids::TypeId const self_type_id, NonnullRefPtr<Jakt::types::CheckedFunction> const first, NonnullRefPtr<Jakt::types::CheckedFunction> const second, Function<ErrorOr<bool>(Jakt::typechecker::Typechecker&, Jakt::ids::TypeId, Jakt::ids::TypeId)> const& types_match);
public: Typechecker(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, NonnullRefPtr<Jakt::types::CheckedProgram> a_program, Jakt::ids::ModuleId a_current_module_id, JaktInternal::Optional<Jakt::ids::TypeId> a_current_struct_type_id, JaktInternal::Optional<Jakt::ids::FunctionId> a_current_function_id, Jakt::typechecker::BreakContinueLegalityTracker a_break_continue_tracker, Jakt::typechecker::ReturnLegalityTracker a_return_tracker, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, Jakt::types::GenericInferences a_generic_inferences, JaktInternal::Optional<Jakt::ids::TypeId> a_self_type_id, ByteString a_root_module_name, bool a_in_comptime_function_call, bool a_had_an_error, JaktInternal::Dictionary<ByteString,Jakt::ids::ScopeId> a_cpp_import_cache, JaktInternal::Optional<Jakt::cpp_import__none::CppImportProcessor> a_cpp_import_processor, u64 a_temp_var_count, Jakt::types::CheckedBlock a_current_block);

public: ByteString debug_description() const;
};struct AlreadyImplementedFor {
  public:
public: ByteString trait_name;public: Jakt::utility::Span encounter_span;public: AlreadyImplementedFor(ByteString a_trait_name, Jakt::utility::Span a_encounter_span);

public: ByteString debug_description() const;
};struct TraitImplCheck {
  public:
public: JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> missing_methods;public: JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::error::JaktError>>>> unmatched_signatures;public: JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::utility::Span>> private_matching_methods;public: JaktInternal::Dictionary<ByteString,Jakt::typechecker::AlreadyImplementedFor> already_implemented_for;public: static Jakt::typechecker::TraitImplCheck make();
public: void ensure_capacity(size_t const count);
public: void register_trait(Jakt::ids::TypeId const trait_type_id, ByteString const trait_name, Jakt::types::CheckedTraitRequirements const requirements);
public: ErrorOr<void> throw_errors(Jakt::utility::Span const record_decl_span, Jakt::typechecker::Typechecker& typechecker);
public: ErrorOr<void> register_method(Jakt::ids::TypeId const self_type_id, ByteString const method_name, Jakt::ids::FunctionId const method_id, Jakt::typechecker::Typechecker& typechecker);
public: TraitImplCheck(JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> a_missing_methods, JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::error::JaktError>>>> a_unmatched_signatures, JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::utility::Span>> a_private_matching_methods, JaktInternal::Dictionary<ByteString,Jakt::typechecker::AlreadyImplementedFor> a_already_implemented_for);

public: ByteString debug_description() const;
};template <typename R,typename S>
Jakt::typechecker::InternalDictionaryProduct<R,S> create_internal_dictionary_product(JaktInternal::Dictionary<R,JaktInternal::DynamicArray<S>> const dict);
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::FunctionMatchResult> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::FunctionMatchResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::TypeHint> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::TypeHint const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::TraitImplementationDescriptor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::TraitImplementationDescriptor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::ImportRestrictions> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::ImportRestrictions const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::BreakContinueLegalityTracker> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::BreakContinueLegalityTracker const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::ReturnLegalityTracker> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::ReturnLegalityTracker const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::NumericOrStringValue> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::NumericOrStringValue const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<typename K,typename V>struct Jakt::Formatter<Jakt::typechecker::InternalDictionaryProduct<K, V>
> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::InternalDictionaryProduct<K, V>
 const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::Typechecker> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::Typechecker const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::AlreadyImplementedFor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::AlreadyImplementedFor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::typechecker::TraitImplCheck> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::typechecker::TraitImplCheck const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
