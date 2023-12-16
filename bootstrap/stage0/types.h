#pragma once
#include "__unified_forward.h"
#include "parser.h"
#include "utility.h"
#include "compiler.h"
#include "ids.h"
namespace Jakt {
namespace types {
struct BlockControlFlow {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
bool might_break;
} AlwaysTransfersControl;
struct {
bool might_break;
} PartialAlwaysReturns;
struct {
bool might_break;
} PartialAlwaysTransfersControl;
struct {
bool might_break;
} PartialNeverReturns;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static BlockControlFlow AlwaysReturns();
[[nodiscard]] static BlockControlFlow AlwaysTransfersControl(bool might_break);
[[nodiscard]] static BlockControlFlow NeverReturns();
[[nodiscard]] static BlockControlFlow MayReturn();
[[nodiscard]] static BlockControlFlow PartialAlwaysReturns(bool might_break);
[[nodiscard]] static BlockControlFlow PartialAlwaysTransfersControl(bool might_break);
[[nodiscard]] static BlockControlFlow PartialNeverReturns(bool might_break);
~BlockControlFlow();
BlockControlFlow& operator=(BlockControlFlow const &);
BlockControlFlow& operator=(BlockControlFlow &&);
BlockControlFlow(BlockControlFlow const&);
BlockControlFlow(BlockControlFlow &&);
private: void __jakt_destroy_variant();
public:
types::BlockControlFlow updated(types::BlockControlFlow const second) const;
bool is_reachable() const;
bool always_returns() const;
bool always_transfers_control() const;
types::BlockControlFlow branch_unify_with(types::BlockControlFlow const second) const;
types::BlockControlFlow definitive() const;
types::BlockControlFlow partial() const;
bool may_break() const;
types::BlockControlFlow unify_with(types::BlockControlFlow const second) const;
bool may_return() const;
bool never_returns() const;
private:
BlockControlFlow() {};
};
struct CheckedBlock {
  public:
public: JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> statements;public: ids::ScopeId scope_id;public: types::BlockControlFlow control_flow;public: JaktInternal::Optional<ids::TypeId> yielded_type;public: bool yielded_none;public: CheckedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> a_statements, ids::ScopeId a_scope_id, types::BlockControlFlow a_control_flow, JaktInternal::Optional<ids::TypeId> a_yielded_type, bool a_yielded_none);

public: ErrorOr<ByteString> debug_description() const;
};struct BuiltinType {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static BuiltinType Void();
[[nodiscard]] static BuiltinType Bool();
[[nodiscard]] static BuiltinType U8();
[[nodiscard]] static BuiltinType U16();
[[nodiscard]] static BuiltinType U32();
[[nodiscard]] static BuiltinType U64();
[[nodiscard]] static BuiltinType I8();
[[nodiscard]] static BuiltinType I16();
[[nodiscard]] static BuiltinType I32();
[[nodiscard]] static BuiltinType I64();
[[nodiscard]] static BuiltinType F32();
[[nodiscard]] static BuiltinType F64();
[[nodiscard]] static BuiltinType Usize();
[[nodiscard]] static BuiltinType JaktString();
[[nodiscard]] static BuiltinType CChar();
[[nodiscard]] static BuiltinType CInt();
[[nodiscard]] static BuiltinType Unknown();
[[nodiscard]] static BuiltinType Never();
~BuiltinType();
BuiltinType& operator=(BuiltinType const &);
BuiltinType& operator=(BuiltinType &&);
BuiltinType(BuiltinType const&);
BuiltinType(BuiltinType &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<ByteString> constructor_name() const;
size_t id() const;
private:
BuiltinType() {};
};
struct CheckedVisibility {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> scopes;
utility::Span span;
} Restricted;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedVisibility Public();
[[nodiscard]] static CheckedVisibility Private();
[[nodiscard]] static CheckedVisibility Restricted(JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> scopes, utility::Span span);
~CheckedVisibility();
CheckedVisibility& operator=(CheckedVisibility const &);
CheckedVisibility& operator=(CheckedVisibility &&);
CheckedVisibility(CheckedVisibility const&);
CheckedVisibility(CheckedVisibility &&);
private: void __jakt_destroy_variant();
public:
private:
CheckedVisibility() {};
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
struct CheckedStruct {
  public:
public: ByteString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>> generic_parameter_defaults;public: JaktInternal::DynamicArray<types::CheckedField> fields;public: ids::ScopeId scope_id;public: parser::DefinitionLinkage definition_linkage;public: JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> trait_implementations;public: parser::RecordType record_type;public: ids::TypeId type_id;public: JaktInternal::Optional<ids::StructId> super_struct_id;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Optional<ids::TypeId> implements_type;public: CheckedStruct(ByteString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>> a_generic_parameter_defaults, JaktInternal::DynamicArray<types::CheckedField> a_fields, ids::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> a_trait_implementations, parser::RecordType a_record_type, ids::TypeId a_type_id, JaktInternal::Optional<ids::StructId> a_super_struct_id, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<ids::TypeId> a_implements_type);

public: parser::ExternalName name_for_codegen() const;
public: ErrorOr<ByteString> debug_description() const;
};struct CheckedNumericConstant {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
i8 value;
} I8;
struct {
i16 value;
} I16;
struct {
i32 value;
} I32;
struct {
i64 value;
} I64;
struct {
u8 value;
} U8;
struct {
u16 value;
} U16;
struct {
u32 value;
} U32;
struct {
u64 value;
} U64;
struct {
u64 value;
} USize;
struct {
f32 value;
} F32;
struct {
f64 value;
} F64;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedNumericConstant I8(i8 value);
[[nodiscard]] static CheckedNumericConstant I16(i16 value);
[[nodiscard]] static CheckedNumericConstant I32(i32 value);
[[nodiscard]] static CheckedNumericConstant I64(i64 value);
[[nodiscard]] static CheckedNumericConstant U8(u8 value);
[[nodiscard]] static CheckedNumericConstant U16(u16 value);
[[nodiscard]] static CheckedNumericConstant U32(u32 value);
[[nodiscard]] static CheckedNumericConstant U64(u64 value);
[[nodiscard]] static CheckedNumericConstant USize(u64 value);
[[nodiscard]] static CheckedNumericConstant F32(f32 value);
[[nodiscard]] static CheckedNumericConstant F64(f64 value);
~CheckedNumericConstant();
CheckedNumericConstant& operator=(CheckedNumericConstant const &);
CheckedNumericConstant& operator=(CheckedNumericConstant &&);
CheckedNumericConstant(CheckedNumericConstant const&);
CheckedNumericConstant(CheckedNumericConstant &&);
private: void __jakt_destroy_variant();
public:
JaktInternal::Optional<types::NumberConstant> number_constant() const;
private:
CheckedNumericConstant() {};
};
struct CheckedCall {
  public:
public: JaktInternal::DynamicArray<types::ResolvedNamespace> namespace_;public: ByteString name;public: JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> args;public: JaktInternal::DynamicArray<ids::TypeId> type_args;public: JaktInternal::Optional<ids::FunctionId> function_id;public: ids::TypeId return_type;public: bool callee_throws;public: JaktInternal::Optional<parser::ExternalName> external_name;public: parser::InlineState force_inline;public: CheckedCall(JaktInternal::DynamicArray<types::ResolvedNamespace> a_namespace_, ByteString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> a_args, JaktInternal::DynamicArray<ids::TypeId> a_type_args, JaktInternal::Optional<ids::FunctionId> a_function_id, ids::TypeId a_return_type, bool a_callee_throws, JaktInternal::Optional<parser::ExternalName> a_external_name, parser::InlineState a_force_inline);

public: parser::ExternalName name_for_codegen() const;
public: ErrorOr<ByteString> debug_description() const;
};struct OperatorTraitImplementation {
  public:
public: ids::TraitId trait_id;public: JaktInternal::DynamicArray<ids::TypeId> trait_generic_arguments;public: types::CheckedCall call_expression;public: OperatorTraitImplementation(ids::TraitId a_trait_id, JaktInternal::DynamicArray<ids::TypeId> a_trait_generic_arguments, types::CheckedCall a_call_expression);

public: ErrorOr<ByteString> debug_description() const;
};struct CheckedBinaryOperator {
  public:
public: parser::BinaryOperator op;public: JaktInternal::Optional<types::OperatorTraitImplementation> trait_implementation;public: CheckedBinaryOperator(parser::BinaryOperator a_op, JaktInternal::Optional<types::OperatorTraitImplementation> a_trait_implementation);

public: ErrorOr<ByteString> debug_description() const;
};struct StructLikeId {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
ids::StructId value;
} Struct;
struct {
ids::EnumId value;
} Enum;
struct {
ids::TraitId value;
} Trait;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static StructLikeId Struct(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments, ids::StructId value);
[[nodiscard]] static StructLikeId Enum(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments, ids::EnumId value);
[[nodiscard]] static StructLikeId Trait(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments, ids::TraitId value);
~StructLikeId();
StructLikeId& operator=(StructLikeId const &);
StructLikeId& operator=(StructLikeId &&);
StructLikeId(StructLikeId const&);
StructLikeId(StructLikeId &&);
private: void __jakt_destroy_variant();
public:
static ErrorOr<JaktInternal::Optional<types::StructLikeId>> from_type_id(ids::TypeId const type_id, NonnullRefPtr<types::CheckedProgram> const& program);
ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> generic_parameters(NonnullRefPtr<types::CheckedProgram> const& program) const;
ErrorOr<ids::ScopeId> associated_scope_id(NonnullRefPtr<types::CheckedProgram> const& program) const;
ErrorOr<JaktInternal::DynamicArray<types::CheckedGenericParameter>> generic_parameters_as_checked(NonnullRefPtr<types::CheckedProgram> const& program) const;
ErrorOr<ids::ScopeId> scope_id(NonnullRefPtr<types::CheckedProgram> const& program) const;
ErrorOr<ids::TypeId> specialized_by(JaktInternal::DynamicArray<ids::TypeId> const arguments, NonnullRefPtr<types::CheckedProgram>& program, ids::ModuleId const module_id, parser::CheckedQualifiers const qualifiers) const;
private:
StructLikeId() {};
};
class CheckedProgram :public RefCounted<CheckedProgram>, public Weakable<CheckedProgram> {
  public:
virtual ~CheckedProgram() = default;
public: NonnullRefPtr<compiler::Compiler> compiler;public: JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> modules;public: JaktInternal::Dictionary<ByteString,types::LoadedModule> loaded_modules;public: ErrorOr<ids::TypeId> substitute_typevars_in_type(ids::TypeId const type_id, types::GenericInferences const generic_inferences, ids::ModuleId const module_id);
public: ids::ModuleId prelude_module_id() const;
public: ErrorOr<JaktInternal::Optional<ids::ScopeId>> find_namespace_in_immediate_children_of_scope(ids::ScopeId const scope_id, ByteString const name, bool const treat_aliases_as_imports) const;
public: ErrorOr<ids::StructId> find_struct_in_prelude(ByteString const name) const;
public: ErrorOr<NonnullRefPtr<types::Scope>> get_scope(ids::ScopeId const id) const;
public: bool is_floating(ids::TypeId const type_id) const;
public: ErrorOr<JaktInternal::Optional<ids::FunctionId>> find_default_constructors_in_scope(ids::ScopeId const parent_scope_id, ByteString const function_name, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<ids::StructId>> find_struct_in_scope(ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<ids::TypeId>> find_type_in_scope(ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<void> set_loaded_module(ByteString const module_name, types::LoadedModule const loaded_module);
public: ErrorOr<ids::ScopeId> find_type_scope_id(ids::TypeId const type_id);
public: bool is_integer(ids::TypeId const type_id) const;
public: ErrorOr<ids::ScopeId> create_scope(JaktInternal::Optional<ids::ScopeId> const parent_scope_id, bool const can_throw, ByteString const debug_name, ids::ModuleId const module_id, bool const for_block);
public: NonnullRefPtr<types::Module> get_module(ids::ModuleId const id) const;
public: ErrorOr<ByteString> type_name(ids::TypeId const type_id, bool const debug_mode) const;
private: ErrorOr<JaktInternal::Optional<bool>> for_each_scope_accessible_unqualified_from_scope_impl(ids::ScopeId const scope_id, Function<ErrorOr<typename utility::IterationDecision<bool>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<bool> is_scope_directly_accessible_from(ids::ScopeId const check_scope_id, ids::ScopeId const scope_id, bool const ignore_mixin_scopes) const;
public: ErrorOr<ByteString> debug_description_of(ids::ScopeId const scope_id) const;
public: ErrorOr<bool> is_string(ids::TypeId const type_id) const;
public: ids::ScopeId prelude_scope_id() const;
public: NonnullRefPtr<types::CheckedTrait> get_trait(ids::TraitId const id) const;
public: NonnullRefPtr<types::CheckedVariable> get_variable(ids::VarId const id) const;
public: protected:
explicit CheckedProgram(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> a_modules, JaktInternal::Dictionary<ByteString,types::LoadedModule> a_loaded_modules);
public:
static ErrorOr<NonnullRefPtr<CheckedProgram>> __jakt_create(NonnullRefPtr<compiler::Compiler> compiler, JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> modules, JaktInternal::Dictionary<ByteString,types::LoadedModule> loaded_modules);

public: ErrorOr<ids::ModuleId> create_module(ByteString const name, bool const is_root, JaktInternal::Optional<ByteString> const path);
public: NonnullRefPtr<types::CheckedFunction> get_function(ids::FunctionId const id) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> find_type_scope(ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<ids::StructId> builtin_implementation_struct(types::BuiltinType const builtin, ids::ModuleId const for_module);
public: ErrorOr<JaktInternal::Optional<types::Value>> find_comptime_binding_in_scope(ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
private: ErrorOr<ids::TypeId> substitute_typevars_in_type_helper(ids::TypeId const type_id, types::GenericInferences const generic_inferences, ids::ModuleId const module_id);
private: ErrorOr<JaktInternal::Optional<bool>> for_each_scope_accessible_unqualified_from_scope_direct_chain(ids::ScopeId const scope_id, Function<ErrorOr<typename utility::IterationDecision<bool>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: i64 get_bits(ids::TypeId const type_id) const;
public: NonnullRefPtr<typename types::Type> get_type(ids::TypeId const id) const;
public: ErrorOr<ids::TypeId> find_or_add_type_id(NonnullRefPtr<typename types::Type> const type, ids::ModuleId const module_id, bool const only_in_current_module);
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>>> find_namespace_in_scope(ids::ScopeId const scope_id, ByteString const name, bool const treat_aliases_as_imports, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<void> set_owner_scope_if_needed(ids::ScopeId const parent_scope_id, JaktInternal::DynamicArray<ids::FunctionId> const overload_set, utility::Span const span);
public: ErrorOr<void> set_owner_scope_if_needed(ids::ScopeId const parent_scope_id, ids::VarId const var_id);
public: types::CheckedEnum get_enum(ids::EnumId const id) const;
public: ErrorOr<JaktInternal::Optional<ids::TraitId>> find_trait_in_scope(ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<ids::TypeId> apply_qualifiers_to_type(parser::CheckedQualifiers const qualifiers, ids::TypeId const type_id);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>>> find_functions_with_name_in_scope(ids::ScopeId const parent_scope_id, ByteString const function_name, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> find_var_in_scope(ids::ScopeId const scope_id, ByteString const var, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<ids::FunctionId>> find_function_in_scope(ids::ScopeId const parent_scope_id, ByteString const function_name, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: types::CheckedStruct get_struct(ids::StructId const id) const;
public: ErrorOr<JaktInternal::Optional<ids::StructId>> check_and_extract_weak_ptr(ids::StructId const struct_id, JaktInternal::DynamicArray<ids::TypeId> const args) const;
public: ErrorOr<JaktInternal::Optional<ids::EnumId>> find_enum_in_scope(ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: JaktInternal::Optional<types::LoadedModule> get_loaded_module(ByteString const module_name) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> find_scoped_functions_with_name_in_scope(ids::ScopeId const parent_scope_id, ByteString const function_name, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: bool is_signed(ids::TypeId const type_id) const;
public: bool is_numeric(ids::TypeId const type_id) const;
public: template <typename T>
ErrorOr<JaktInternal::Optional<T>> for_each_scope_accessible_unqualified_from_scope(ids::ScopeId const scope_id, Function<ErrorOr<typename utility::IterationDecision<T>>(ids::ScopeId, JaktInternal::Optional<ByteString>, bool)> const& callback, bool const ignore_mixin_scopes, JaktInternal::Optional<ids::ScopeId> const root_scope) const;
public: public: public: public: public: public: public: public: public: public: ErrorOr<types::StructOrEnumId> find_reflected_primitive(ByteString const primitive) const;
public: ErrorOr<ByteString> debug_description() const;
};struct CheckedField {
  public:
public: ids::VarId variable_id;public: JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>> default_value_expression;public: CheckedField(ids::VarId a_variable_id, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>> a_default_value_expression);

public: ErrorOr<ByteString> debug_description() const;
};struct CheckedEnumVariant {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ids::EnumId enum_id;
ByteString name;
utility::Span span;
} Untyped;
struct {
ids::EnumId enum_id;
ByteString name;
ids::TypeId type_id;
utility::Span span;
} Typed;
struct {
ids::EnumId enum_id;
ByteString name;
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
} WithValue;
struct {
ids::EnumId enum_id;
ByteString name;
JaktInternal::DynamicArray<ids::VarId> fields;
utility::Span span;
} StructLike;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedEnumVariant Untyped(ids::EnumId enum_id, ByteString name, utility::Span span);
[[nodiscard]] static CheckedEnumVariant Typed(ids::EnumId enum_id, ByteString name, ids::TypeId type_id, utility::Span span);
[[nodiscard]] static CheckedEnumVariant WithValue(ids::EnumId enum_id, ByteString name, NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span);
[[nodiscard]] static CheckedEnumVariant StructLike(ids::EnumId enum_id, ByteString name, JaktInternal::DynamicArray<ids::VarId> fields, utility::Span span);
~CheckedEnumVariant();
CheckedEnumVariant& operator=(CheckedEnumVariant const &);
CheckedEnumVariant& operator=(CheckedEnumVariant &&);
CheckedEnumVariant(CheckedEnumVariant const&);
CheckedEnumVariant(CheckedEnumVariant &&);
private: void __jakt_destroy_variant();
public:
ids::EnumId enum_id() const;
ByteString name() const;
bool equals(types::CheckedEnumVariant const other) const;
utility::Span span() const;
private:
CheckedEnumVariant() {};
};
struct CheckedTypeCast {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ids::TypeId value;
} Fallible;
struct {
ids::TypeId value;
} Infallible;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedTypeCast Fallible(ids::TypeId value);
[[nodiscard]] static CheckedTypeCast Infallible(ids::TypeId value);
~CheckedTypeCast();
CheckedTypeCast& operator=(CheckedTypeCast const &);
CheckedTypeCast& operator=(CheckedTypeCast &&);
CheckedTypeCast(CheckedTypeCast const&);
CheckedTypeCast(CheckedTypeCast &&);
private: void __jakt_destroy_variant();
public:
ids::TypeId type_id() const;
private:
CheckedTypeCast() {};
};
struct CheckedUnaryOperator {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
types::CheckedTypeCast value;
} TypeCast;
struct {
ids::TypeId value;
} Is;
struct {
types::CheckedEnumVariant enum_variant;
JaktInternal::DynamicArray<types::CheckedEnumVariantBinding> bindings;
ids::TypeId type_id;
} IsEnumVariant;
struct {
ids::TypeId value;
} Sizeof;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedUnaryOperator PreIncrement();
[[nodiscard]] static CheckedUnaryOperator PostIncrement();
[[nodiscard]] static CheckedUnaryOperator PreDecrement();
[[nodiscard]] static CheckedUnaryOperator PostDecrement();
[[nodiscard]] static CheckedUnaryOperator Negate();
[[nodiscard]] static CheckedUnaryOperator Dereference();
[[nodiscard]] static CheckedUnaryOperator RawAddress();
[[nodiscard]] static CheckedUnaryOperator Reference();
[[nodiscard]] static CheckedUnaryOperator MutableReference();
[[nodiscard]] static CheckedUnaryOperator LogicalNot();
[[nodiscard]] static CheckedUnaryOperator BitwiseNot();
[[nodiscard]] static CheckedUnaryOperator TypeCast(types::CheckedTypeCast value);
[[nodiscard]] static CheckedUnaryOperator Is(ids::TypeId value);
[[nodiscard]] static CheckedUnaryOperator IsEnumVariant(types::CheckedEnumVariant enum_variant, JaktInternal::DynamicArray<types::CheckedEnumVariantBinding> bindings, ids::TypeId type_id);
[[nodiscard]] static CheckedUnaryOperator IsSome();
[[nodiscard]] static CheckedUnaryOperator IsNone();
[[nodiscard]] static CheckedUnaryOperator Sizeof(ids::TypeId value);
~CheckedUnaryOperator();
CheckedUnaryOperator& operator=(CheckedUnaryOperator const &);
CheckedUnaryOperator& operator=(CheckedUnaryOperator &&);
CheckedUnaryOperator(CheckedUnaryOperator const&);
CheckedUnaryOperator(CheckedUnaryOperator &&);
private: void __jakt_destroy_variant();
public:
private:
CheckedUnaryOperator() {};
};
struct FunctionGenericParameterKind {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static FunctionGenericParameterKind InferenceGuide();
[[nodiscard]] static FunctionGenericParameterKind Parameter();
~FunctionGenericParameterKind();
FunctionGenericParameterKind& operator=(FunctionGenericParameterKind const &);
FunctionGenericParameterKind& operator=(FunctionGenericParameterKind &&);
FunctionGenericParameterKind(FunctionGenericParameterKind const&);
FunctionGenericParameterKind(FunctionGenericParameterKind &&);
private: void __jakt_destroy_variant();
public:
private:
FunctionGenericParameterKind() {};
};
struct LoadedModule {
  public:
public: ids::ModuleId module_id;public: utility::FileId file_id;public: LoadedModule(ids::ModuleId a_module_id, utility::FileId a_file_id);

public: ErrorOr<ByteString> debug_description() const;
};struct CheckedGenericParameter {
  public:
public: ids::TypeId type_id;public: JaktInternal::DynamicArray<ids::TraitId> constraints;public: utility::Span span;public: static ErrorOr<types::CheckedGenericParameter> make(ids::TypeId const type_id, utility::Span const span);
public: CheckedGenericParameter(ids::TypeId a_type_id, JaktInternal::DynamicArray<ids::TraitId> a_constraints, utility::Span a_span);

public: ErrorOr<ByteString> debug_description() const;
};struct ResolvedForallChunk {
  public:
public: JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> parameters;public: parser::ParsedNamespace parsed_namespace;public: JaktInternal::DynamicArray<ids::ScopeId> generated_scopes;public: ResolvedForallChunk(JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> a_parameters, parser::ParsedNamespace a_parsed_namespace, JaktInternal::DynamicArray<ids::ScopeId> a_generated_scopes);

public: ErrorOr<ByteString> debug_description() const;
};struct Value {
  public:
public: NonnullRefPtr<typename types::ValueImpl> impl;public: utility::Span span;public: ErrorOr<types::Value> copy() const;
public: ErrorOr<ByteString> type_name() const;
public: Value(NonnullRefPtr<typename types::ValueImpl> a_impl, utility::Span a_span);

public: ErrorOr<types::Value> cast(types::Value const expected, utility::Span const span) const;
public: ErrorOr<ByteString> debug_description() const;
};struct FieldRecord {
  public:
public: ids::StructId struct_id;public: ids::VarId field_id;public: FieldRecord(ids::StructId a_struct_id, ids::VarId a_field_id);

public: ErrorOr<ByteString> debug_description() const;
};struct Type: public RefCounted<Type> {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
parser::CheckedQualifiers qualifiers;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString name;
JaktInternal::DynamicArray<ids::TypeId> trait_implementations;
bool is_value;
} TypeVariable;
struct {
ids::TypeId namespace_type;
ByteString name;
} Dependent;
struct {
ids::StructId id;
JaktInternal::DynamicArray<ids::TypeId> args;
} GenericInstance;
struct {
ids::EnumId id;
JaktInternal::DynamicArray<ids::TypeId> args;
} GenericEnumInstance;
struct {
ids::TraitId id;
JaktInternal::DynamicArray<ids::TypeId> args;
} GenericTraitInstance;
struct {
ids::StructId id;
JaktInternal::DynamicArray<ids::TypeId> args;
} GenericResolvedType;
struct {
ids::StructId value;
} Struct;
struct {
ids::EnumId value;
} Enum;
struct {
ids::TypeId value;
} RawPtr;
struct {
ids::TraitId value;
} Trait;
struct {
ids::TypeId value;
} Reference;
struct {
ids::TypeId value;
} MutableReference;
struct {
JaktInternal::DynamicArray<ids::TypeId> params;
bool can_throw;
ids::TypeId return_type_id;
ids::FunctionId pseudo_function_id;
} Function;
struct {
types::Value value;
} Const;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Void(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Bool(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> U8(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> U16(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> U32(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> U64(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> I8(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> I16(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> I32(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> I64(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> F32(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> F64(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Usize(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> JaktString(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> CChar(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> CInt(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Unknown(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Never(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> TypeVariable(parser::CheckedQualifiers qualifiers, ByteString name, JaktInternal::DynamicArray<ids::TypeId> trait_implementations, bool is_value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Dependent(parser::CheckedQualifiers qualifiers, ids::TypeId namespace_type, ByteString name);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> GenericInstance(parser::CheckedQualifiers qualifiers, ids::StructId id, JaktInternal::DynamicArray<ids::TypeId> args);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> GenericEnumInstance(parser::CheckedQualifiers qualifiers, ids::EnumId id, JaktInternal::DynamicArray<ids::TypeId> args);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> GenericTraitInstance(parser::CheckedQualifiers qualifiers, ids::TraitId id, JaktInternal::DynamicArray<ids::TypeId> args);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> GenericResolvedType(parser::CheckedQualifiers qualifiers, ids::StructId id, JaktInternal::DynamicArray<ids::TypeId> args);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Struct(parser::CheckedQualifiers qualifiers, ids::StructId value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Enum(parser::CheckedQualifiers qualifiers, ids::EnumId value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> RawPtr(parser::CheckedQualifiers qualifiers, ids::TypeId value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Trait(parser::CheckedQualifiers qualifiers, ids::TraitId value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Reference(parser::CheckedQualifiers qualifiers, ids::TypeId value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> MutableReference(parser::CheckedQualifiers qualifiers, ids::TypeId value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Function(parser::CheckedQualifiers qualifiers, JaktInternal::DynamicArray<ids::TypeId> params, bool can_throw, ids::TypeId return_type_id, ids::FunctionId pseudo_function_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Self(parser::CheckedQualifiers qualifiers);
[[nodiscard]] static ErrorOr<NonnullRefPtr<Type>> Const(parser::CheckedQualifiers qualifiers, types::Value value);
~Type();
Type& operator=(Type const &);
Type& operator=(Type &&);
Type(Type const&);
Type(Type &&);
private: void __jakt_destroy_variant();
public:
u64 max() const;
bool equals(NonnullRefPtr<typename types::Type> const rhs) const;
JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>> generic_parameters(NonnullRefPtr<types::CheckedProgram> const program) const;
ErrorOr<ByteString> constructor_name() const;
bool is_concrete() const;
i64 get_bits() const;
i64 specificity(NonnullRefPtr<types::CheckedProgram> const program, i64 const base_specificity) const;
types::BuiltinType as_builtin_type() const;
bool is_builtin() const;
i64 min() const;
ErrorOr<ids::TypeId> flip_signedness() const;
bool is_boxed(NonnullRefPtr<types::CheckedProgram> const program) const;
bool is_signed() const;
private:
Type() {};
};
class Scope :public RefCounted<Scope>, public Weakable<Scope> {
  public:
virtual ~Scope() = default;
public: JaktInternal::Optional<ByteString> namespace_name;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Dictionary<ByteString,ids::VarId> vars;public: JaktInternal::Dictionary<ByteString,types::Value> comptime_bindings;public: JaktInternal::Dictionary<ByteString,ids::StructId> structs;public: JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> functions;public: JaktInternal::Dictionary<ByteString,ids::EnumId> enums;public: JaktInternal::Dictionary<ByteString,ids::TypeId> types;public: JaktInternal::Dictionary<ByteString,ids::TraitId> traits;public: JaktInternal::Dictionary<ByteString,ids::ModuleId> imports;public: JaktInternal::Dictionary<ByteString,ids::ScopeId> aliases;public: JaktInternal::Optional<ids::ScopeId> parent;public: JaktInternal::Optional<ids::ScopeId> alias_scope;public: JaktInternal::DynamicArray<ids::ScopeId> children;public: bool can_throw;public: JaktInternal::Optional<ByteString> import_path_if_extern;public: JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> alias_path;public: JaktInternal::DynamicArray<parser::IncludeAction> after_extern_include;public: JaktInternal::DynamicArray<parser::IncludeAction> before_extern_include;public: ByteString debug_name;public: JaktInternal::DynamicArray<ids::ScopeId> resolution_mixins;public: JaktInternal::Optional<ids::TypeId> relevant_type_id;public: bool is_block_scope;public: JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> resolved_forall_chunks;public: JaktInternal::Dictionary<ByteString,types::SpecializedType> explicitly_specialized_types;public: bool is_from_generated_code;public: protected:
explicit Scope(JaktInternal::Optional<ByteString> a_namespace_name, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Dictionary<ByteString,ids::VarId> a_vars, JaktInternal::Dictionary<ByteString,types::Value> a_comptime_bindings, JaktInternal::Dictionary<ByteString,ids::StructId> a_structs, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> a_functions, JaktInternal::Dictionary<ByteString,ids::EnumId> a_enums, JaktInternal::Dictionary<ByteString,ids::TypeId> a_types, JaktInternal::Dictionary<ByteString,ids::TraitId> a_traits, JaktInternal::Dictionary<ByteString,ids::ModuleId> a_imports, JaktInternal::Dictionary<ByteString,ids::ScopeId> a_aliases, JaktInternal::Optional<ids::ScopeId> a_parent, JaktInternal::Optional<ids::ScopeId> a_alias_scope, JaktInternal::DynamicArray<ids::ScopeId> a_children, bool a_can_throw, JaktInternal::Optional<ByteString> a_import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> a_alias_path, JaktInternal::DynamicArray<parser::IncludeAction> a_after_extern_include, JaktInternal::DynamicArray<parser::IncludeAction> a_before_extern_include, ByteString a_debug_name, JaktInternal::DynamicArray<ids::ScopeId> a_resolution_mixins, JaktInternal::Optional<ids::TypeId> a_relevant_type_id, bool a_is_block_scope, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> a_resolved_forall_chunks, JaktInternal::Dictionary<ByteString,types::SpecializedType> a_explicitly_specialized_types, bool a_is_from_generated_code);
public:
static ErrorOr<NonnullRefPtr<Scope>> __jakt_create(JaktInternal::Optional<ByteString> namespace_name, JaktInternal::Optional<parser::ExternalName> external_name, JaktInternal::Dictionary<ByteString,ids::VarId> vars, JaktInternal::Dictionary<ByteString,types::Value> comptime_bindings, JaktInternal::Dictionary<ByteString,ids::StructId> structs, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> functions, JaktInternal::Dictionary<ByteString,ids::EnumId> enums, JaktInternal::Dictionary<ByteString,ids::TypeId> types, JaktInternal::Dictionary<ByteString,ids::TraitId> traits, JaktInternal::Dictionary<ByteString,ids::ModuleId> imports, JaktInternal::Dictionary<ByteString,ids::ScopeId> aliases, JaktInternal::Optional<ids::ScopeId> parent, JaktInternal::Optional<ids::ScopeId> alias_scope, JaktInternal::DynamicArray<ids::ScopeId> children, bool can_throw, JaktInternal::Optional<ByteString> import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> alias_path, JaktInternal::DynamicArray<parser::IncludeAction> after_extern_include, JaktInternal::DynamicArray<parser::IncludeAction> before_extern_include, ByteString debug_name, JaktInternal::DynamicArray<ids::ScopeId> resolution_mixins, JaktInternal::Optional<ids::TypeId> relevant_type_id, bool is_block_scope, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> resolved_forall_chunks, JaktInternal::Dictionary<ByteString,types::SpecializedType> explicitly_specialized_types, bool is_from_generated_code);

public: JaktInternal::Optional<parser::ExternalName> namespace_name_for_codegen() const;
public: ErrorOr<ByteString> debug_description() const;
};struct ValueImpl: public RefCounted<ValueImpl> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
bool value;
} Bool;
struct {
u8 value;
} U8;
struct {
u16 value;
} U16;
struct {
u32 value;
} U32;
struct {
u64 value;
} U64;
struct {
i8 value;
} I8;
struct {
i16 value;
} I16;
struct {
i32 value;
} I32;
struct {
i64 value;
} I64;
struct {
f32 value;
} F32;
struct {
f64 value;
} F64;
struct {
size_t value;
} USize;
struct {
ByteString value;
} JaktString;
struct {
ByteString value;
} StringView;
struct {
char value;
} CChar;
struct {
int value;
} CInt;
struct {
JaktInternal::DynamicArray<types::Value> fields;
ids::StructId struct_id;
JaktInternal::Optional<ids::FunctionId> constructor;
} Struct;
struct {
JaktInternal::DynamicArray<types::Value> fields;
ids::StructId struct_id;
JaktInternal::Optional<ids::FunctionId> constructor;
} Class;
struct {
JaktInternal::DynamicArray<types::Value> fields;
ids::EnumId enum_id;
ids::FunctionId constructor;
} Enum;
struct {
JaktInternal::DynamicArray<types::Value> values;
ids::TypeId type_id;
} JaktArray;
struct {
JaktInternal::DynamicArray<types::Value> keys;
JaktInternal::DynamicArray<types::Value> values;
ids::TypeId type_id;
} JaktDictionary;
struct {
JaktInternal::DynamicArray<types::Value> values;
ids::TypeId type_id;
} JaktSet;
struct {
NonnullRefPtr<typename types::ValueImpl> value;
} RawPtr;
struct {
types::Value value;
} OptionalSome;
struct {
JaktInternal::DynamicArray<types::Value> fields;
ids::TypeId type_id;
} JaktTuple;
struct {
JaktInternal::Dictionary<ByteString,types::Value> captures;
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>> params;
ids::TypeId return_type_id;
ids::TypeId type_id;
types::CheckedBlock block;
bool can_throw;
JaktInternal::DynamicArray<types::CheckedParameter> checked_params;
ids::ScopeId scope_id;
JaktInternal::Optional<ids::FunctionId> pseudo_function_id;
} Function;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> Void();
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> Bool(bool value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> U8(u8 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> U16(u16 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> U32(u32 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> U64(u64 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> I8(i8 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> I16(i16 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> I32(i32 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> I64(i64 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> F32(f32 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> F64(f64 value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> USize(size_t value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> JaktString(ByteString value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> StringView(ByteString value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> CChar(char value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> CInt(int value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> Struct(JaktInternal::DynamicArray<types::Value> fields, ids::StructId struct_id, JaktInternal::Optional<ids::FunctionId> constructor);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> Class(JaktInternal::DynamicArray<types::Value> fields, ids::StructId struct_id, JaktInternal::Optional<ids::FunctionId> constructor);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> Enum(JaktInternal::DynamicArray<types::Value> fields, ids::EnumId enum_id, ids::FunctionId constructor);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> JaktArray(JaktInternal::DynamicArray<types::Value> values, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> JaktDictionary(JaktInternal::DynamicArray<types::Value> keys, JaktInternal::DynamicArray<types::Value> values, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> JaktSet(JaktInternal::DynamicArray<types::Value> values, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> RawPtr(NonnullRefPtr<typename types::ValueImpl> value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> OptionalSome(types::Value value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> OptionalNone();
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> JaktTuple(JaktInternal::DynamicArray<types::Value> fields, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ValueImpl>> Function(JaktInternal::Dictionary<ByteString,types::Value> captures, JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>> params, ids::TypeId return_type_id, ids::TypeId type_id, types::CheckedBlock block, bool can_throw, JaktInternal::DynamicArray<types::CheckedParameter> checked_params, ids::ScopeId scope_id, JaktInternal::Optional<ids::FunctionId> pseudo_function_id);
~ValueImpl();
ValueImpl& operator=(ValueImpl const &);
ValueImpl& operator=(ValueImpl &&);
ValueImpl(ValueImpl const&);
ValueImpl(ValueImpl &&);
private: void __jakt_destroy_variant();
public:
bool equals(NonnullRefPtr<typename types::ValueImpl> const other) const;
ErrorOr<ids::TypeId> type_id(NonnullRefPtr<types::CheckedProgram>& program) const;
ErrorOr<NonnullRefPtr<typename types::ValueImpl>> copy() const;
private:
ValueImpl() {};
};
struct StructOrEnumId {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ids::StructId value;
} Struct;
struct {
ids::EnumId value;
} Enum;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static StructOrEnumId Struct(ids::StructId value);
[[nodiscard]] static StructOrEnumId Enum(ids::EnumId value);
~StructOrEnumId();
StructOrEnumId& operator=(StructOrEnumId const &);
StructOrEnumId& operator=(StructOrEnumId &&);
StructOrEnumId(StructOrEnumId const&);
StructOrEnumId(StructOrEnumId &&);
private: void __jakt_destroy_variant();
public:
private:
StructOrEnumId() {};
};
struct CheckedStatement: public RefCounted<CheckedStatement> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
} Expression;
struct {
NonnullRefPtr<typename types::CheckedStatement> statement;
utility::Span span;
} Defer;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> vars;
NonnullRefPtr<typename types::CheckedStatement> var_decl;
utility::Span span;
} DestructuringAssignment;
struct {
ids::VarId var_id;
NonnullRefPtr<typename types::CheckedExpression> init;
utility::Span span;
} VarDecl;
struct {
NonnullRefPtr<typename types::CheckedExpression> condition;
types::CheckedBlock then_block;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> else_statement;
utility::Span span;
} If;
struct {
types::CheckedBlock block;
utility::Span span;
} Block;
struct {
types::CheckedBlock block;
utility::Span span;
} Loop;
struct {
NonnullRefPtr<typename types::CheckedExpression> condition;
types::CheckedBlock block;
utility::Span span;
} While;
struct {
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> val;
JaktInternal::Optional<utility::Span> span;
} Return;
struct {
utility::Span value;
} Break;
struct {
utility::Span value;
} Continue;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
} Throw;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
} Yield;
struct {
JaktInternal::DynamicArray<ByteString> lines;
utility::Span span;
} InlineCpp;
struct {
utility::Span value;
} Garbage;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Expression(NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Defer(NonnullRefPtr<typename types::CheckedStatement> statement, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> DestructuringAssignment(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> vars, NonnullRefPtr<typename types::CheckedStatement> var_decl, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> VarDecl(ids::VarId var_id, NonnullRefPtr<typename types::CheckedExpression> init, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> If(NonnullRefPtr<typename types::CheckedExpression> condition, types::CheckedBlock then_block, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> else_statement, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Block(types::CheckedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Loop(types::CheckedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> While(NonnullRefPtr<typename types::CheckedExpression> condition, types::CheckedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Return(JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> val, JaktInternal::Optional<utility::Span> span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Break(utility::Span value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Continue(utility::Span value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Throw(NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Yield(NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> InlineCpp(JaktInternal::DynamicArray<ByteString> lines, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedStatement>> Garbage(utility::Span value);
~CheckedStatement();
CheckedStatement& operator=(CheckedStatement const &);
CheckedStatement& operator=(CheckedStatement &&);
CheckedStatement(CheckedStatement const&);
CheckedStatement(CheckedStatement &&);
private: void __jakt_destroy_variant();
public:
JaktInternal::Optional<utility::Span> span() const;
static JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> none();
private:
CheckedStatement() {};
};
struct GenericInferences {
  public:
public: JaktInternal::Dictionary<ids::TypeId,ids::TypeId> values;public: ErrorOr<void> set_all(JaktInternal::DynamicArray<types::CheckedGenericParameter> const keys, JaktInternal::DynamicArray<ids::TypeId> const values);
public: ErrorOr<void> set_from(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const checkpoint);
public: ErrorOr<JaktInternal::Optional<ids::TypeId>> find_and_map(ByteString const name, NonnullRefPtr<types::CheckedProgram> const& program) const;
public: GenericInferences(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> a_values);

public: void restore(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const checkpoint);
public: ErrorOr<void> debug_description(NonnullRefPtr<types::CheckedProgram> const& program) const;
public: ids::TypeId map(ids::TypeId const type) const;
public: ErrorOr<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> perform_checkpoint(bool const reset);
public: JaktInternal::Optional<ids::TypeId> get(ids::TypeId const key) const;
public: JaktInternal::Dictionary<ids::TypeId,ids::TypeId> iterator() const;
public: ErrorOr<void> set(ids::TypeId const key, ids::TypeId const value);
public: ErrorOr<ByteString> debug_description() const;
};struct NumberConstant {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
i64 value;
} Signed;
struct {
u64 value;
} Unsigned;
struct {
f64 value;
} Floating;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static NumberConstant Signed(i64 value);
[[nodiscard]] static NumberConstant Unsigned(u64 value);
[[nodiscard]] static NumberConstant Floating(f64 value);
~NumberConstant();
NumberConstant& operator=(NumberConstant const &);
NumberConstant& operator=(NumberConstant &&);
NumberConstant(NumberConstant const&);
NumberConstant(NumberConstant &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<bool> can_fit_number(ids::TypeId const type_id, NonnullRefPtr<types::CheckedProgram> const program) const;
ErrorOr<size_t> to_usize() const;
private:
NumberConstant() {};
};
struct CheckedTraitRequirements {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::Dictionary<ByteString,ids::FunctionId> value;
} Methods;
struct {
NonnullRefPtr<typename types::CheckedExpression> value;
} ComptimeExpression;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedTraitRequirements Nothing();
[[nodiscard]] static CheckedTraitRequirements Methods(JaktInternal::Dictionary<ByteString,ids::FunctionId> value);
[[nodiscard]] static CheckedTraitRequirements ComptimeExpression(NonnullRefPtr<typename types::CheckedExpression> value);
~CheckedTraitRequirements();
CheckedTraitRequirements& operator=(CheckedTraitRequirements const &);
CheckedTraitRequirements& operator=(CheckedTraitRequirements &&);
CheckedTraitRequirements(CheckedTraitRequirements const&);
CheckedTraitRequirements(CheckedTraitRequirements &&);
private: void __jakt_destroy_variant();
public:
private:
CheckedTraitRequirements() {};
};
struct CheckedEnum {
  public:
public: ByteString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters;public: JaktInternal::DynamicArray<types::CheckedEnumVariant> variants;public: JaktInternal::DynamicArray<types::CheckedField> fields;public: ids::ScopeId scope_id;public: parser::DefinitionLinkage definition_linkage;public: JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> trait_implementations;public: parser::RecordType record_type;public: ids::TypeId underlying_type_id;public: ids::TypeId type_id;public: bool is_boxed;public: CheckedEnum(ByteString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, JaktInternal::DynamicArray<types::CheckedEnumVariant> a_variants, JaktInternal::DynamicArray<types::CheckedField> a_fields, ids::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> a_trait_implementations, parser::RecordType a_record_type, ids::TypeId a_underlying_type_id, ids::TypeId a_type_id, bool a_is_boxed);

public: ErrorOr<ByteString> debug_description() const;
};struct ClassInstanceRebind {
  public:
public: ByteString name;public: utility::Span name_span;public: bool is_mutable;public: bool is_reference;public: ClassInstanceRebind(ByteString a_name, utility::Span a_name_span, bool a_is_mutable, bool a_is_reference);

public: ErrorOr<ByteString> debug_description() const;
};struct StringLiteral {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString value;
} Static;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static StringLiteral Static(ByteString value);
~StringLiteral();
StringLiteral& operator=(StringLiteral const &);
StringLiteral& operator=(StringLiteral &&);
StringLiteral(StringLiteral const&);
StringLiteral(StringLiteral &&);
private: void __jakt_destroy_variant();
public:
ByteString to_string() const;
private:
StringLiteral() {};
};
struct CheckedStringLiteral {
  public:
public: types::StringLiteral value;public: ids::TypeId type_id;public: bool may_throw;public: ByteString to_string() const;
public: CheckedStringLiteral(types::StringLiteral a_value, ids::TypeId a_type_id, bool a_may_throw);

public: ErrorOr<ByteString> debug_description() const;
};struct FunctionGenericParameter {
  public:
public: types::FunctionGenericParameterKind kind;public: types::CheckedGenericParameter checked_parameter;public: static ErrorOr<types::FunctionGenericParameter> parameter(ids::TypeId const type_id, utility::Span const span);
public: ids::TypeId type_id() const;
public: FunctionGenericParameter(types::FunctionGenericParameterKind a_kind, types::CheckedGenericParameter a_checked_parameter);

public: ErrorOr<ByteString> debug_description() const;
};class CheckedTrait :public RefCounted<CheckedTrait>, public Weakable<CheckedTrait> {
  public:
virtual ~CheckedTrait() = default;
public: ByteString name;public: utility::Span name_span;public: types::CheckedTraitRequirements requirements;public: JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters;public: ids::ScopeId scope_id;public: protected:
explicit CheckedTrait(ByteString a_name, utility::Span a_name_span, types::CheckedTraitRequirements a_requirements, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, ids::ScopeId a_scope_id);
public:
static ErrorOr<NonnullRefPtr<CheckedTrait>> __jakt_create(ByteString name, utility::Span name_span, types::CheckedTraitRequirements requirements, JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters, ids::ScopeId scope_id);

public: ErrorOr<ByteString> debug_description() const;
};struct CheckedEnumVariantBinding {
  public:
public: JaktInternal::Optional<ByteString> name;public: ByteString binding;public: ids::TypeId type_id;public: utility::Span span;public: CheckedEnumVariantBinding(JaktInternal::Optional<ByteString> a_name, ByteString a_binding, ids::TypeId a_type_id, utility::Span a_span);

public: ErrorOr<ByteString> debug_description() const;
};struct CheckedExpression: public RefCounted<CheckedExpression> {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
bool val;
utility::Span span;
} Boolean;
struct {
types::CheckedNumericConstant val;
utility::Span span;
ids::TypeId type_id;
} NumericConstant;
struct {
types::CheckedStringLiteral val;
utility::Span span;
} QuotedString;
struct {
ByteString val;
utility::Span span;
} ByteConstant;
struct {
ByteString val;
utility::Span span;
} CharacterConstant;
struct {
ByteString val;
utility::Span span;
} CCharacterConstant;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
types::CheckedUnaryOperator op;
utility::Span span;
ids::TypeId type_id;
} UnaryOp;
struct {
NonnullRefPtr<typename types::CheckedExpression> lhs;
types::CheckedBinaryOperator op;
NonnullRefPtr<typename types::CheckedExpression> rhs;
utility::Span span;
ids::TypeId type_id;
} BinaryOp;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals;
utility::Span span;
ids::TypeId type_id;
} JaktTuple;
struct {
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> to;
utility::Span span;
ids::TypeId type_id;
} Range;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> repeat;
utility::Span span;
ids::TypeId type_id;
ids::TypeId inner_type_id;
} JaktArray;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals;
utility::Span span;
ids::TypeId type_id;
ids::TypeId inner_type_id;
} JaktSet;
struct {
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> vals;
utility::Span span;
ids::TypeId type_id;
ids::TypeId key_type_id;
ids::TypeId value_type_id;
} JaktDictionary;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
NonnullRefPtr<typename types::CheckedExpression> index;
utility::Span span;
ids::TypeId type_id;
} IndexedExpression;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
NonnullRefPtr<typename types::CheckedExpression> index;
utility::Span span;
ids::TypeId type_id;
} IndexedDictionary;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
size_t index;
utility::Span span;
bool is_optional;
ids::TypeId type_id;
} IndexedTuple;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
ByteString name;
JaktInternal::Optional<ids::VarId> index;
utility::Span span;
bool is_optional;
ids::TypeId type_id;
} IndexedStruct;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
ByteString index;
utility::Span span;
bool is_optional;
ids::TypeId type_id;
} IndexedCommonEnumMember;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
NonnullRefPtr<typename types::CheckedExpression> index;
bool is_optional;
utility::Span span;
} ComptimeIndex;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
JaktInternal::DynamicArray<types::CheckedMatchCase> match_cases;
utility::Span span;
ids::TypeId type_id;
bool all_variants_constant;
} Match;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
types::CheckedEnumVariantBinding arg;
types::CheckedEnumVariant enum_variant;
utility::Span span;
} EnumVariantArg;
struct {
types::CheckedCall call;
utility::Span span;
ids::TypeId type_id;
} Call;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
types::CheckedCall call;
utility::Span span;
bool is_optional;
ids::TypeId type_id;
} MethodCall;
struct {
JaktInternal::DynamicArray<types::CheckedNamespace> namespaces;
NonnullRefPtr<types::CheckedVariable> var;
utility::Span span;
} NamespacedVar;
struct {
NonnullRefPtr<types::CheckedVariable> var;
utility::Span span;
} Var;
struct {
utility::Span span;
ids::TypeId type_id;
} OptionalNone;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
ids::TypeId type_id;
} OptionalSome;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
utility::Span span;
ids::TypeId type_id;
} ForcedUnwrap;
struct {
types::CheckedBlock block;
utility::Span span;
ids::TypeId type_id;
} Block;
struct {
JaktInternal::DynamicArray<types::CheckedCapture> captures;
JaktInternal::DynamicArray<types::CheckedParameter> params;
bool can_throw;
ids::TypeId return_type_id;
types::CheckedBlock block;
utility::Span span;
ids::TypeId type_id;
JaktInternal::Optional<ids::FunctionId> pseudo_function_id;
ids::ScopeId scope_id;
} Function;
struct {
JaktInternal::DynamicArray<types::CheckedCapture> captures;
JaktInternal::DynamicArray<types::CheckedParameter> params;
bool can_throw;
ids::TypeId return_type_id;
parser::ParsedBlock block;
utility::Span span;
ids::TypeId type_id;
JaktInternal::Optional<ids::FunctionId> pseudo_function_id;
ids::ScopeId scope_id;
} DependentFunction;
struct {
NonnullRefPtr<typename types::CheckedExpression> expr;
JaktInternal::Optional<types::CheckedBlock> catch_block;
JaktInternal::Optional<utility::Span> catch_span;
JaktInternal::Optional<ByteString> catch_name;
utility::Span span;
ids::TypeId type_id;
ids::TypeId inner_type_id;
} Try;
struct {
NonnullRefPtr<typename types::CheckedStatement> stmt;
types::CheckedBlock catch_block;
ByteString error_name;
utility::Span error_span;
utility::Span span;
ids::TypeId type_id;
} TryBlock;
struct {
ids::TypeId type;
utility::Span span;
ids::TypeId type_id;
} Reflect;
struct {
utility::Span span;
ids::TypeId type_id;
} Garbage;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Boolean(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, bool val, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> NumericConstant(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, types::CheckedNumericConstant val, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> QuotedString(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, types::CheckedStringLiteral val, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> ByteConstant(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, ByteString val, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> CharacterConstant(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, ByteString val, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> CCharacterConstant(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, ByteString val, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> UnaryOp(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, types::CheckedUnaryOperator op, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> BinaryOp(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> lhs, types::CheckedBinaryOperator op, NonnullRefPtr<typename types::CheckedExpression> rhs, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> JaktTuple(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Range(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> from, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> to, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> JaktArray(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> repeat, utility::Span span, ids::TypeId type_id, ids::TypeId inner_type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> JaktSet(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals, utility::Span span, ids::TypeId type_id, ids::TypeId inner_type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> JaktDictionary(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> vals, utility::Span span, ids::TypeId type_id, ids::TypeId key_type_id, ids::TypeId value_type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> IndexedExpression(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, NonnullRefPtr<typename types::CheckedExpression> index, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> IndexedDictionary(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, NonnullRefPtr<typename types::CheckedExpression> index, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> IndexedTuple(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, size_t index, utility::Span span, bool is_optional, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> IndexedStruct(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, ByteString name, JaktInternal::Optional<ids::VarId> index, utility::Span span, bool is_optional, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> IndexedCommonEnumMember(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, ByteString index, utility::Span span, bool is_optional, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> ComptimeIndex(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, NonnullRefPtr<typename types::CheckedExpression> index, bool is_optional, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Match(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, JaktInternal::DynamicArray<types::CheckedMatchCase> match_cases, utility::Span span, ids::TypeId type_id, bool all_variants_constant);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> EnumVariantArg(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, types::CheckedEnumVariantBinding arg, types::CheckedEnumVariant enum_variant, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Call(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, types::CheckedCall call, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> MethodCall(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, types::CheckedCall call, utility::Span span, bool is_optional, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> NamespacedVar(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<types::CheckedNamespace> namespaces, NonnullRefPtr<types::CheckedVariable> var, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Var(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<types::CheckedVariable> var, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> OptionalNone(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> OptionalSome(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> ForcedUnwrap(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Block(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, types::CheckedBlock block, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Function(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<types::CheckedCapture> captures, JaktInternal::DynamicArray<types::CheckedParameter> params, bool can_throw, ids::TypeId return_type_id, types::CheckedBlock block, utility::Span span, ids::TypeId type_id, JaktInternal::Optional<ids::FunctionId> pseudo_function_id, ids::ScopeId scope_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> DependentFunction(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<types::CheckedCapture> captures, JaktInternal::DynamicArray<types::CheckedParameter> params, bool can_throw, ids::TypeId return_type_id, parser::ParsedBlock block, utility::Span span, ids::TypeId type_id, JaktInternal::Optional<ids::FunctionId> pseudo_function_id, ids::ScopeId scope_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Try(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, JaktInternal::Optional<types::CheckedBlock> catch_block, JaktInternal::Optional<utility::Span> catch_span, JaktInternal::Optional<ByteString> catch_name, utility::Span span, ids::TypeId type_id, ids::TypeId inner_type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> TryBlock(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedStatement> stmt, types::CheckedBlock catch_block, ByteString error_name, utility::Span error_span, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Reflect(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, ids::TypeId type, utility::Span span, ids::TypeId type_id);
[[nodiscard]] static ErrorOr<NonnullRefPtr<CheckedExpression>> Garbage(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, utility::Span span, ids::TypeId type_id);
~CheckedExpression();
CheckedExpression& operator=(CheckedExpression const &);
CheckedExpression& operator=(CheckedExpression &&);
CheckedExpression(CheckedExpression const&);
CheckedExpression(CheckedExpression &&);
private: void __jakt_destroy_variant();
public:
bool can_throw() const;
JaktInternal::Optional<types::NumberConstant> to_number_constant(NonnullRefPtr<types::CheckedProgram> const program) const;
utility::Span span() const;
ids::TypeId type() const;
ErrorOr<types::BlockControlFlow> control_flow() const;
bool is_mutable(NonnullRefPtr<types::CheckedProgram> const program) const;
private:
CheckedExpression() {};
};
struct CheckedParameter {
  public:
public: bool requires_label;public: NonnullRefPtr<types::CheckedVariable> variable;public: JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>> default_value_expression;public: ErrorOr<types::CheckedParameter> map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) const;
public: CheckedParameter(bool a_requires_label, NonnullRefPtr<types::CheckedVariable> a_variable, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>> a_default_value_expression);

public: ErrorOr<ByteString> debug_description() const;
};struct SafetyMode {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static SafetyMode Safe();
[[nodiscard]] static SafetyMode Unsafe();
~SafetyMode();
SafetyMode& operator=(SafetyMode const &);
SafetyMode& operator=(SafetyMode &&);
SafetyMode(SafetyMode const&);
SafetyMode(SafetyMode &&);
private: void __jakt_destroy_variant();
public:
private:
SafetyMode() {};
};
struct SpecializedType {
  public:
public: ids::TypeId base_type_id;public: JaktInternal::DynamicArray<ids::TypeId> arguments;public: ids::TypeId type_id;public: SpecializedType(ids::TypeId a_base_type_id, JaktInternal::DynamicArray<ids::TypeId> a_arguments, ids::TypeId a_type_id);

public: ErrorOr<ByteString> debug_description() const;
};class TypecheckFunctions :public RefCounted<TypecheckFunctions>, public Weakable<TypecheckFunctions> {
  public:
virtual ~TypecheckFunctions() = default;
public: Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>, JaktInternal::Optional<ids::FunctionId>)> block;public: Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> register_function;public: protected:
explicit TypecheckFunctions(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>, JaktInternal::Optional<ids::FunctionId>)> a_block, Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> a_register_function);
public:
static ErrorOr<NonnullRefPtr<TypecheckFunctions>> __jakt_create(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>, JaktInternal::Optional<ids::FunctionId>)> block, Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> register_function);

public: ErrorOr<ByteString> debug_description() const;
};class CheckedFunction :public RefCounted<CheckedFunction>, public Weakable<CheckedFunction> {
  public:
virtual ~CheckedFunction() = default;
public: ByteString name;public: utility::Span name_span;public: types::CheckedVisibility visibility;public: ids::TypeId return_type_id;public: JaktInternal::Optional<utility::Span> return_type_span;public: JaktInternal::DynamicArray<types::CheckedParameter> params;public: NonnullRefPtr<types::FunctionGenerics> generics;public: types::CheckedBlock block;public: bool can_throw;public: parser::FunctionType type;public: parser::FunctionLinkage linkage;public: ids::ScopeId function_scope_id;public: JaktInternal::Optional<ids::StructId> struct_id;public: bool is_instantiated;public: JaktInternal::Optional<parser::ParsedFunction> parsed_function;public: bool is_comptime;public: bool is_virtual;public: bool is_override;public: bool is_unsafe;public: bool has_varargs;public: JaktInternal::Optional<size_t> specialization_index;public: JaktInternal::Optional<ids::ScopeId> owner_scope;public: JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> owner_scope_generics;public: bool is_fully_checked;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Optional<ByteString> deprecated_message;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> stores_arguments;public: parser::InlineState force_inline;public: ErrorOr<void> map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map);
public: ErrorOr<bool> is_static() const;
public: ErrorOr<bool> is_mutating() const;
public: protected:
explicit CheckedFunction(ByteString a_name, utility::Span a_name_span, types::CheckedVisibility a_visibility, ids::TypeId a_return_type_id, JaktInternal::Optional<utility::Span> a_return_type_span, JaktInternal::DynamicArray<types::CheckedParameter> a_params, NonnullRefPtr<types::FunctionGenerics> a_generics, types::CheckedBlock a_block, bool a_can_throw, parser::FunctionType a_type, parser::FunctionLinkage a_linkage, ids::ScopeId a_function_scope_id, JaktInternal::Optional<ids::StructId> a_struct_id, bool a_is_instantiated, JaktInternal::Optional<parser::ParsedFunction> a_parsed_function, bool a_is_comptime, bool a_is_virtual, bool a_is_override, bool a_is_unsafe, bool a_has_varargs, JaktInternal::Optional<size_t> a_specialization_index, JaktInternal::Optional<ids::ScopeId> a_owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> a_owner_scope_generics, bool a_is_fully_checked, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<ByteString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> a_stores_arguments, parser::InlineState a_force_inline);
public:
static ErrorOr<NonnullRefPtr<CheckedFunction>> __jakt_create(ByteString name, utility::Span name_span, types::CheckedVisibility visibility, ids::TypeId return_type_id, JaktInternal::Optional<utility::Span> return_type_span, JaktInternal::DynamicArray<types::CheckedParameter> params, NonnullRefPtr<types::FunctionGenerics> generics, types::CheckedBlock block, bool can_throw, parser::FunctionType type, parser::FunctionLinkage linkage, ids::ScopeId function_scope_id, JaktInternal::Optional<ids::StructId> struct_id, bool is_instantiated, JaktInternal::Optional<parser::ParsedFunction> parsed_function, bool is_comptime, bool is_virtual, bool is_override, bool is_unsafe, bool has_varargs, JaktInternal::Optional<size_t> specialization_index, JaktInternal::Optional<ids::ScopeId> owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> owner_scope_generics, bool is_fully_checked, JaktInternal::Optional<parser::ExternalName> external_name, JaktInternal::Optional<ByteString> deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> stores_arguments, parser::InlineState force_inline);

public: ErrorOr<parser::ParsedFunction> to_parsed_function() const;
public: bool is_specialized_for_types(JaktInternal::DynamicArray<ids::TypeId> const types) const;
public: ErrorOr<NonnullRefPtr<types::CheckedFunction>> copy() const;
public: ErrorOr<bool> signature_matches(NonnullRefPtr<types::CheckedFunction> const other, bool const ignore_this) const;
public: parser::ExternalName name_for_codegen() const;
public: ErrorOr<void> add_param(types::CheckedParameter const checked_param);
public: ErrorOr<void> set_params(JaktInternal::DynamicArray<types::CheckedParameter> const checked_params);
public: ErrorOr<ByteString> debug_description() const;
};struct CheckedCapture {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
ByteString name;
utility::Span span;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedCapture ByValue(ByteString name, utility::Span span);
[[nodiscard]] static CheckedCapture ByReference(ByteString name, utility::Span span);
[[nodiscard]] static CheckedCapture ByMutableReference(ByteString name, utility::Span span);
[[nodiscard]] static CheckedCapture ByComptimeDependency(ByteString name, utility::Span span);
[[nodiscard]] static CheckedCapture AllByReference(ByteString name, utility::Span span);
~CheckedCapture();
CheckedCapture& operator=(CheckedCapture const &);
CheckedCapture& operator=(CheckedCapture &&);
CheckedCapture(CheckedCapture const&);
CheckedCapture(CheckedCapture &&);
private: void __jakt_destroy_variant();
public:
private:
CheckedCapture() {};
};
struct ResolvedNamespace {
  public:
public: ByteString name;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_parameters;public: ResolvedNamespace(ByteString a_name, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> a_generic_parameters);

public: parser::ExternalName name_for_codegen() const;
public: ErrorOr<ByteString> debug_description() const;
};struct MaybeResolvedScope: public RefCounted<MaybeResolvedScope> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ids::ScopeId value;
} Resolved;
struct {
NonnullRefPtr<typename types::MaybeResolvedScope> parent_scope;
ByteString relative_name;
} Unresolved;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static ErrorOr<NonnullRefPtr<MaybeResolvedScope>> Resolved(ids::ScopeId value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<MaybeResolvedScope>> Unresolved(NonnullRefPtr<typename types::MaybeResolvedScope> parent_scope, ByteString relative_name);
~MaybeResolvedScope();
MaybeResolvedScope& operator=(MaybeResolvedScope const &);
MaybeResolvedScope& operator=(MaybeResolvedScope &&);
MaybeResolvedScope(MaybeResolvedScope const&);
MaybeResolvedScope(MaybeResolvedScope &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<NonnullRefPtr<typename types::MaybeResolvedScope>> try_resolve(NonnullRefPtr<types::CheckedProgram> const program) const;
private:
MaybeResolvedScope() {};
};
class FunctionGenerics :public RefCounted<FunctionGenerics>, public Weakable<FunctionGenerics> {
  public:
virtual ~FunctionGenerics() = default;
public: ids::ScopeId base_scope_id;public: JaktInternal::DynamicArray<types::CheckedParameter> base_params;public: JaktInternal::DynamicArray<types::FunctionGenericParameter> params;public: JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> specializations;public: protected:
explicit FunctionGenerics(ids::ScopeId a_base_scope_id, JaktInternal::DynamicArray<types::CheckedParameter> a_base_params, JaktInternal::DynamicArray<types::FunctionGenericParameter> a_params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> a_specializations);
public:
static ErrorOr<NonnullRefPtr<FunctionGenerics>> __jakt_create(ids::ScopeId base_scope_id, JaktInternal::DynamicArray<types::CheckedParameter> base_params, JaktInternal::DynamicArray<types::FunctionGenericParameter> params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> specializations);

public: bool is_specialized_for_types(JaktInternal::DynamicArray<ids::TypeId> const types) const;
public: ErrorOr<ByteString> debug_description() const;
};class Module :public RefCounted<Module>, public Weakable<Module> {
  public:
virtual ~Module() = default;
public: ids::ModuleId id;public: ByteString name;public: JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> functions;public: JaktInternal::DynamicArray<types::CheckedStruct> structures;public: JaktInternal::DynamicArray<types::CheckedEnum> enums;public: JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> scopes;public: JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> types;public: JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> traits;public: JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> variables;public: JaktInternal::DynamicArray<ids::ModuleId> imports;public: ByteString resolved_import_path;public: JaktInternal::Dictionary<size_t,ids::StructId> builtin_implementation_structs;public: bool is_root;public: ids::FunctionId next_function_id() const;
public: ErrorOr<ids::FunctionId> add_function(NonnullRefPtr<types::CheckedFunction> const checked_function);
public: bool is_prelude() const;
public: protected:
explicit Module(ids::ModuleId a_id, ByteString a_name, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> a_functions, JaktInternal::DynamicArray<types::CheckedStruct> a_structures, JaktInternal::DynamicArray<types::CheckedEnum> a_enums, JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> a_scopes, JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> a_types, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> a_traits, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> a_variables, JaktInternal::DynamicArray<ids::ModuleId> a_imports, ByteString a_resolved_import_path, JaktInternal::Dictionary<size_t,ids::StructId> a_builtin_implementation_structs, bool a_is_root);
public:
static ErrorOr<NonnullRefPtr<Module>> __jakt_create(ids::ModuleId id, ByteString name, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> functions, JaktInternal::DynamicArray<types::CheckedStruct> structures, JaktInternal::DynamicArray<types::CheckedEnum> enums, JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> scopes, JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> types, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> traits, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> variables, JaktInternal::DynamicArray<ids::ModuleId> imports, ByteString resolved_import_path, JaktInternal::Dictionary<size_t,ids::StructId> builtin_implementation_structs, bool is_root);

public: ErrorOr<ids::VarId> add_variable(NonnullRefPtr<types::CheckedVariable> const checked_variable);
public: ErrorOr<ids::TypeId> new_type_variable(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const implemented_traits);
public: ErrorOr<ByteString> debug_description() const;
};class CheckedVariable :public RefCounted<CheckedVariable>, public Weakable<CheckedVariable> {
  public:
virtual ~CheckedVariable() = default;
public: ByteString name;public: ids::TypeId type_id;public: bool is_mutable;public: utility::Span definition_span;public: JaktInternal::Optional<utility::Span> type_span;public: types::CheckedVisibility visibility;public: JaktInternal::Optional<ids::ScopeId> owner_scope;public: JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> owner_scope_generics;public: JaktInternal::Optional<parser::ExternalName> external_name;public: ErrorOr<NonnullRefPtr<types::CheckedVariable>> map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) const;
public: parser::ExternalName name_for_codegen() const;
public: protected:
explicit CheckedVariable(ByteString a_name, ids::TypeId a_type_id, bool a_is_mutable, utility::Span a_definition_span, JaktInternal::Optional<utility::Span> a_type_span, types::CheckedVisibility a_visibility, JaktInternal::Optional<ids::ScopeId> a_owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> a_owner_scope_generics, JaktInternal::Optional<parser::ExternalName> a_external_name);
public:
static ErrorOr<NonnullRefPtr<CheckedVariable>> __jakt_create(ByteString name, ids::TypeId type_id, bool is_mutable, utility::Span definition_span, JaktInternal::Optional<utility::Span> type_span, types::CheckedVisibility visibility, JaktInternal::Optional<ids::ScopeId> owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> owner_scope_generics, JaktInternal::Optional<parser::ExternalName> external_name);

public: ErrorOr<ByteString> debug_description() const;
};struct CheckedNamespace {
  public:
public: ByteString name;public: ids::ScopeId scope;public: CheckedNamespace(ByteString a_name, ids::ScopeId a_scope);

public: ErrorOr<ByteString> debug_description() const;
};struct CheckedMatchBody {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename types::CheckedExpression> value;
} Expression;
struct {
types::CheckedBlock value;
} Block;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedMatchBody Expression(NonnullRefPtr<typename types::CheckedExpression> value);
[[nodiscard]] static CheckedMatchBody Block(types::CheckedBlock value);
~CheckedMatchBody();
CheckedMatchBody& operator=(CheckedMatchBody const &);
CheckedMatchBody& operator=(CheckedMatchBody &&);
CheckedMatchBody(CheckedMatchBody const&);
CheckedMatchBody(CheckedMatchBody &&);
private: void __jakt_destroy_variant();
public:
private:
CheckedMatchBody() {};
};
struct CheckedMatchCase {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString name;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> args;
ids::TypeId subject_type_id;
size_t index;
ids::ScopeId scope_id;
types::CheckedMatchBody body;
utility::Span marker_span;
} EnumVariant;
struct {
NonnullRefPtr<typename types::CheckedExpression> expression;
types::CheckedMatchBody body;
utility::Span marker_span;
} Expression;
struct {
ids::TypeId type;
types::CheckedMatchBody body;
JaktInternal::Optional<types::ClassInstanceRebind> rebind_name;
utility::Span marker_span;
} ClassInstance;
struct {
bool has_arguments;
types::CheckedMatchBody body;
utility::Span marker_span;
} CatchAll;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static CheckedMatchCase EnumVariant(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults, ByteString name, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> args, ids::TypeId subject_type_id, size_t index, ids::ScopeId scope_id, types::CheckedMatchBody body, utility::Span marker_span);
[[nodiscard]] static CheckedMatchCase Expression(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults, NonnullRefPtr<typename types::CheckedExpression> expression, types::CheckedMatchBody body, utility::Span marker_span);
[[nodiscard]] static CheckedMatchCase ClassInstance(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults, ids::TypeId type, types::CheckedMatchBody body, JaktInternal::Optional<types::ClassInstanceRebind> rebind_name, utility::Span marker_span);
[[nodiscard]] static CheckedMatchCase CatchAll(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults, bool has_arguments, types::CheckedMatchBody body, utility::Span marker_span);
~CheckedMatchCase();
CheckedMatchCase& operator=(CheckedMatchCase const &);
CheckedMatchCase& operator=(CheckedMatchCase &&);
CheckedMatchCase(CheckedMatchCase const&);
CheckedMatchCase(CheckedMatchCase &&);
private: void __jakt_destroy_variant();
public:
private:
CheckedMatchCase() {};
};
struct CheckedVarDecl {
  public:
public: ByteString name;public: bool is_mutable;public: utility::Span span;public: ids::TypeId type_id;public: CheckedVarDecl(ByteString a_name, bool a_is_mutable, utility::Span a_span, ids::TypeId a_type_id);

public: ErrorOr<ByteString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::BlockControlFlow> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::BlockControlFlow const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedBlock> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedBlock const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::BuiltinType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::BuiltinType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVisibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVisibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::NumericOrStringValue> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::NumericOrStringValue const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStruct> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStruct const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedNumericConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedNumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedCall> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedCall const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::OperatorTraitImplementation> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::OperatorTraitImplementation const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedBinaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedBinaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StructLikeId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StructLikeId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedProgram> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedProgram const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedField> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedField const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTypeCast> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTypeCast const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedUnaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedUnaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenericParameterKind> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenericParameterKind const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::LoadedModule> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::LoadedModule const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ResolvedForallChunk> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ResolvedForallChunk const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Value> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Value const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FieldRecord> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FieldRecord const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Type> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Type const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Scope> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Scope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ValueImpl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ValueImpl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StructOrEnumId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StructOrEnumId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStatement> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStatement const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::GenericInferences> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::GenericInferences const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::NumberConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::NumberConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTraitRequirements> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTraitRequirements const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnum> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnum const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ClassInstanceRebind> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ClassInstanceRebind const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StringLiteral> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StringLiteral const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStringLiteral> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStringLiteral const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTrait> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTrait const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnumVariantBinding> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnumVariantBinding const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedExpression> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedExpression const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::SafetyMode> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::SafetyMode const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::SpecializedType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::SpecializedType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::TypecheckFunctions> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::TypecheckFunctions const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedFunction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedFunction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedCapture> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedCapture const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ResolvedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ResolvedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::MaybeResolvedScope> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::MaybeResolvedScope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenerics> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenerics const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Module> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Module const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVariable> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVariable const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedMatchBody> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedMatchBody const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedMatchCase> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedMatchCase const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVarDecl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVarDecl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
