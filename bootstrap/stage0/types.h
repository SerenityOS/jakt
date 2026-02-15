#pragma once
#include <lib.h>
#include <AK/Format.h>
#include "ids.h"
#include "parser.h"
#include "compiler.h"
#include "utility.h"
#include "jakt__arguments.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace types {
struct GenericInferences;
struct SpecializedType;
struct ResolutionMixin;
class Scope;
struct ResolvedForallChunk;
struct TypeWithSkipList;
class Module;
class CheckedTrait;
struct LoadedModule;
struct CheckedNamespace;
class CheckedFunction;
class FunctionGenerics;
struct CheckedParameter;
struct FunctionGenericParameter;
class CheckedVariable;
struct CheckedVarDecl;
struct CheckedBlock;
struct FieldRecord;
class CheckedField;
struct CheckedStruct;
struct CheckedEnum;
struct CheckedGenericParameter;
struct CheckedEnumVariantBinding;
struct CheckedStringLiteral;
struct ClassInstanceRebind;
struct CheckedMatchCase;
struct OperatorTraitImplementation;
struct CheckedBinaryOperator;
struct ResolvedNamespace;
struct CheckedCall;
class CheckedProgram;
struct Value;
class TypecheckFunctions;
struct StructOrEnumId;

struct StructLikeId;

struct SafetyMode;

struct BuiltinType;

struct Type;

struct CheckedTraitRequirements;

struct MaybeResolvedScope;

struct CheckedVisibility;

struct CheckedCapture;

struct FunctionGenericParameterKind;

struct BlockControlFlow;

struct CheckedEnumVariant;

struct CheckedStatement;

struct NumberConstant;

struct CheckedNumericConstant;

struct StringLiteral;

struct CheckedTypeCast;

struct CheckedUnaryOperator;

struct CheckedMatchBody;

struct CheckedMatchPattern;

struct CheckedExpression;

struct ValueImpl;

struct NumericOrStringValue;

Jakt::ids::TypeId unknown_type_id();

Jakt::ids::TypeId void_type_id();

Jakt::ids::TypeId never_type_id();

Jakt::ids::TypeId builtin(Jakt::types::BuiltinType const builtin);

ErrorOr<ByteString> format_value_impl(ByteString const format_string, Jakt::types::Value const value, NonnullRefPtr<Jakt::types::CheckedProgram> const& program);

ErrorOr<ByteString> comptime_format_impl(ByteString const format_string, JaktInternal::ArraySlice<Jakt::types::Value> const arguments, NonnullRefPtr<Jakt::types::CheckedProgram> const& program);

}
namespace types {
struct StructOrEnumId {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::ids::StructId value;
} Struct;
struct {
Jakt::ids::EnumId value;
} Enum;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static StructOrEnumId Struct(Jakt::ids::StructId value);
[[nodiscard]] static StructOrEnumId Enum(Jakt::ids::EnumId value);
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
struct StructLikeId {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> generic_arguments;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::ids::StructId value;
} Struct;
struct {
Jakt::ids::EnumId value;
} Enum;
struct {
Jakt::ids::TraitId value;
} Trait;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static StructLikeId Struct(JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> generic_arguments, Jakt::ids::StructId value);
[[nodiscard]] static StructLikeId Enum(JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> generic_arguments, Jakt::ids::EnumId value);
[[nodiscard]] static StructLikeId Trait(JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> generic_arguments, Jakt::ids::TraitId value);
~StructLikeId();
StructLikeId& operator=(StructLikeId const &);
StructLikeId& operator=(StructLikeId &&);
StructLikeId(StructLikeId const&);
StructLikeId(StructLikeId &&);
private: void __jakt_destroy_variant();
public:
JaktInternal::DynamicArray<Jakt::ids::TypeId> generic_parameters(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const;
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters_as_checked(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const;
Jakt::ids::ScopeId scope_id(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const;
Jakt::ids::TypeId specialized_by(JaktInternal::DynamicArray<Jakt::ids::TypeId> const arguments, NonnullRefPtr<Jakt::types::CheckedProgram>& program, Jakt::ids::ModuleId const module_id, Jakt::parser::CheckedQualifiers const qualifiers) const;
static JaktInternal::Optional<Jakt::types::StructLikeId> from_type_id(Jakt::ids::TypeId const type_id, NonnullRefPtr<Jakt::types::CheckedProgram> const& program);
Jakt::ids::ScopeId associated_scope_id(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const;
private:
StructLikeId() {};
};
struct GenericInferences {
  public:
public: JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> values;public: void set(Jakt::ids::TypeId const key, Jakt::ids::TypeId const value);
public: void set_all(JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const keys, JaktInternal::DynamicArray<Jakt::ids::TypeId> const values);
public: JaktInternal::Optional<Jakt::ids::TypeId> get(Jakt::ids::TypeId const key) const;
public: Jakt::ids::TypeId map(Jakt::ids::TypeId const type) const;
public: ErrorOr<JaktInternal::DynamicArray<Jakt::ids::TypeId>> map(JaktInternal::DynamicArray<Jakt::ids::TypeId> const types) const;
public: JaktInternal::Optional<Jakt::ids::TypeId> find_and_map(ByteString const name, NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const;
public: JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> iterator() const;
public: JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> perform_checkpoint(bool const reset);
public: void restore(JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint);
public: void set_from(JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint);
public: ErrorOr<void> debug_description(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const;
public: GenericInferences(JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> a_values);

public: ByteString debug_description() const;
};struct SafetyMode {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
struct BuiltinType {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
size_t id() const;
ByteString constructor_name() const;
private:
BuiltinType() {};
};
struct Value {
  public:
public: NonnullRefPtr<typename Jakt::types::ValueImpl> impl;public: Jakt::utility::Span span;public: Jakt::types::Value copy() const;
public: ByteString type_name() const;
public: Jakt::types::Value cast(Jakt::types::Value const expected, Jakt::utility::Span const span) const;
public: Value(NonnullRefPtr<typename Jakt::types::ValueImpl> a_impl, Jakt::utility::Span a_span);

public: ByteString debug_description() const;
};struct Type: public RefCounted<Type> {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
Jakt::parser::CheckedQualifiers qualifiers;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations;
bool is_value;
} TypeVariable;
struct {
Jakt::ids::TypeId namespace_type;
ByteString name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> args;
} Dependent;
struct {
Jakt::ids::StructId id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> args;
} GenericInstance;
struct {
Jakt::ids::EnumId id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> args;
} GenericEnumInstance;
struct {
Jakt::ids::TraitId id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> args;
} GenericTraitInstance;
struct {
Jakt::ids::StructId value;
} Struct;
struct {
Jakt::ids::EnumId value;
} Enum;
struct {
Jakt::ids::TypeId value;
} RawPtr;
struct {
Jakt::ids::TraitId value;
} Trait;
struct {
Jakt::ids::TypeId value;
} Reference;
struct {
Jakt::ids::TypeId value;
} MutableReference;
struct {
JaktInternal::DynamicArray<Jakt::ids::TypeId> params;
bool can_throw;
Jakt::ids::TypeId return_type_id;
Jakt::ids::FunctionId pseudo_function_id;
} Function;
struct {
Jakt::types::Value value;
} Const;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NonnullRefPtr<Type> Void(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> Bool(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> U8(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> U16(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> U32(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> U64(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> I8(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> I16(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> I32(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> I64(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> F32(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> F64(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> Usize(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> JaktString(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> CChar(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> CInt(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> Unknown(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> Never(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> TypeVariable(Jakt::parser::CheckedQualifiers qualifiers, ByteString name, JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations, bool is_value);
[[nodiscard]] static NonnullRefPtr<Type> Dependent(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TypeId namespace_type, ByteString name, JaktInternal::DynamicArray<Jakt::ids::TypeId> args);
[[nodiscard]] static NonnullRefPtr<Type> GenericInstance(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::StructId id, JaktInternal::DynamicArray<Jakt::ids::TypeId> args);
[[nodiscard]] static NonnullRefPtr<Type> GenericEnumInstance(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::EnumId id, JaktInternal::DynamicArray<Jakt::ids::TypeId> args);
[[nodiscard]] static NonnullRefPtr<Type> GenericTraitInstance(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TraitId id, JaktInternal::DynamicArray<Jakt::ids::TypeId> args);
[[nodiscard]] static NonnullRefPtr<Type> Struct(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::StructId value);
[[nodiscard]] static NonnullRefPtr<Type> Enum(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::EnumId value);
[[nodiscard]] static NonnullRefPtr<Type> RawPtr(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TypeId value);
[[nodiscard]] static NonnullRefPtr<Type> Trait(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TraitId value);
[[nodiscard]] static NonnullRefPtr<Type> Reference(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TypeId value);
[[nodiscard]] static NonnullRefPtr<Type> MutableReference(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TypeId value);
[[nodiscard]] static NonnullRefPtr<Type> Function(Jakt::parser::CheckedQualifiers qualifiers, JaktInternal::DynamicArray<Jakt::ids::TypeId> params, bool can_throw, Jakt::ids::TypeId return_type_id, Jakt::ids::FunctionId pseudo_function_id);
[[nodiscard]] static NonnullRefPtr<Type> Self(Jakt::parser::CheckedQualifiers qualifiers);
[[nodiscard]] static NonnullRefPtr<Type> Const(Jakt::parser::CheckedQualifiers qualifiers, Jakt::types::Value value);
~Type();
Type& operator=(Type const &);
Type& operator=(Type &&);
Type(Type const&);
Type(Type &&);
private: void __jakt_destroy_variant();
public:
u32 hash() const;
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>> generic_parameters(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const;
bool is_boxed(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const;
bool is_concrete() const;
i64 specificity(NonnullRefPtr<Jakt::types::CheckedProgram> const program, i64 const base_specificity) const;
ByteString constructor_name() const;
bool equals(NonnullRefPtr<typename Jakt::types::Type> const rhs) const;
bool is_builtin() const;
bool is_integer() const;
bool is_floating() const;
bool is_numeric() const;
Jakt::types::BuiltinType as_builtin_type() const;
i64 get_bits() const;
bool is_signed() const;
i64 min() const;
u64 max() const;
Jakt::ids::TypeId flip_signedness() const;
private:
Type() {};
};
struct SpecializedType {
  public:
public: Jakt::ids::TypeId base_type_id;public: JaktInternal::DynamicArray<Jakt::ids::TypeId> arguments;public: Jakt::ids::TypeId type_id;public: SpecializedType(Jakt::ids::TypeId a_base_type_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> a_arguments, Jakt::ids::TypeId a_type_id);

public: ByteString debug_description() const;
};struct ResolutionMixin {
  public:
public: Jakt::ids::ScopeId scope_id;public: bool mixin_vars;public: bool mixin_bindings;public: bool mixin_structs;public: bool mixin_functions;public: bool mixin_enums;public: bool mixin_types;public: bool mixin_traits;public: bool mixin_imports;public: bool mixin_aliases;public: ResolutionMixin(Jakt::ids::ScopeId a_scope_id, bool a_mixin_vars, bool a_mixin_bindings, bool a_mixin_structs, bool a_mixin_functions, bool a_mixin_enums, bool a_mixin_types, bool a_mixin_traits, bool a_mixin_imports, bool a_mixin_aliases);

public: ByteString debug_description() const;
};class Scope :public RefCounted<Scope>, public Weakable<Scope> {
  public:
virtual ~Scope() = default;
public: JaktInternal::Optional<Jakt::ids::ScopeId> parent;public: bool can_throw;public: ByteString debug_name;public: bool is_block_scope;public: bool is_from_generated_code;public: JaktInternal::Optional<ByteString> namespace_name;public: JaktInternal::Optional<ByteString> module_namespace_name;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: JaktInternal::Dictionary<ByteString,Jakt::ids::VarId> vars;public: JaktInternal::Dictionary<ByteString,Jakt::types::Value> comptime_bindings;public: JaktInternal::Dictionary<ByteString,Jakt::ids::StructId> structs;public: JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> functions;public: JaktInternal::Dictionary<ByteString,Jakt::ids::EnumId> enums;public: JaktInternal::Dictionary<ByteString,Jakt::ids::TypeId> types;public: JaktInternal::Dictionary<ByteString,Jakt::ids::TraitId> traits;public: JaktInternal::Dictionary<ByteString,Jakt::ids::ModuleId> imports;public: JaktInternal::Dictionary<ByteString,Jakt::ids::ScopeId> aliases;public: JaktInternal::Optional<Jakt::ids::ScopeId> alias_scope;public: JaktInternal::DynamicArray<Jakt::ids::ScopeId> children;public: JaktInternal::Optional<ByteString> import_path_if_extern;public: JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>> alias_path;public: JaktInternal::DynamicArray<Jakt::parser::IncludeAction> after_extern_include;public: JaktInternal::DynamicArray<Jakt::parser::IncludeAction> before_extern_include;public: JaktInternal::DynamicArray<Jakt::types::ResolutionMixin> resolution_mixins;public: JaktInternal::Optional<Jakt::ids::TypeId> relevant_type_id;public: JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> resolved_forall_chunks;public: JaktInternal::Dictionary<ByteString,Jakt::types::SpecializedType> explicitly_specialized_types;public: JaktInternal::Optional<Jakt::parser::ExternalName> namespace_name_for_codegen() const;
public: protected:
explicit Scope(JaktInternal::Optional<Jakt::ids::ScopeId> a_parent, bool a_can_throw, ByteString a_debug_name, bool a_is_block_scope, bool a_is_from_generated_code, JaktInternal::Optional<ByteString> a_namespace_name, JaktInternal::Optional<ByteString> a_module_namespace_name, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Dictionary<ByteString,Jakt::ids::VarId> a_vars, JaktInternal::Dictionary<ByteString,Jakt::types::Value> a_comptime_bindings, JaktInternal::Dictionary<ByteString,Jakt::ids::StructId> a_structs, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> a_functions, JaktInternal::Dictionary<ByteString,Jakt::ids::EnumId> a_enums, JaktInternal::Dictionary<ByteString,Jakt::ids::TypeId> a_types, JaktInternal::Dictionary<ByteString,Jakt::ids::TraitId> a_traits, JaktInternal::Dictionary<ByteString,Jakt::ids::ModuleId> a_imports, JaktInternal::Dictionary<ByteString,Jakt::ids::ScopeId> a_aliases, JaktInternal::Optional<Jakt::ids::ScopeId> a_alias_scope, JaktInternal::DynamicArray<Jakt::ids::ScopeId> a_children, JaktInternal::Optional<ByteString> a_import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>> a_alias_path, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> a_after_extern_include, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> a_before_extern_include, JaktInternal::DynamicArray<Jakt::types::ResolutionMixin> a_resolution_mixins, JaktInternal::Optional<Jakt::ids::TypeId> a_relevant_type_id, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> a_resolved_forall_chunks, JaktInternal::Dictionary<ByteString,Jakt::types::SpecializedType> a_explicitly_specialized_types);
public:
static NonnullRefPtr<Scope> __jakt_create(JaktInternal::Optional<Jakt::ids::ScopeId> parent, bool can_throw, ByteString debug_name, bool is_block_scope, bool is_from_generated_code, JaktInternal::Optional<ByteString> namespace_name, JaktInternal::Optional<ByteString> module_namespace_name, JaktInternal::Optional<Jakt::parser::ExternalName> external_name, JaktInternal::Dictionary<ByteString,Jakt::ids::VarId> vars, JaktInternal::Dictionary<ByteString,Jakt::types::Value> comptime_bindings, JaktInternal::Dictionary<ByteString,Jakt::ids::StructId> structs, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> functions, JaktInternal::Dictionary<ByteString,Jakt::ids::EnumId> enums, JaktInternal::Dictionary<ByteString,Jakt::ids::TypeId> types, JaktInternal::Dictionary<ByteString,Jakt::ids::TraitId> traits, JaktInternal::Dictionary<ByteString,Jakt::ids::ModuleId> imports, JaktInternal::Dictionary<ByteString,Jakt::ids::ScopeId> aliases, JaktInternal::Optional<Jakt::ids::ScopeId> alias_scope, JaktInternal::DynamicArray<Jakt::ids::ScopeId> children, JaktInternal::Optional<ByteString> import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>> alias_path, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> after_extern_include, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> before_extern_include, JaktInternal::DynamicArray<Jakt::types::ResolutionMixin> resolution_mixins, JaktInternal::Optional<Jakt::ids::TypeId> relevant_type_id, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> resolved_forall_chunks, JaktInternal::Dictionary<ByteString,Jakt::types::SpecializedType> explicitly_specialized_types);

public: ByteString debug_description() const;
};struct ResolvedForallChunk {
  public:
public: JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> parameters;public: Jakt::parser::ParsedNamespace parsed_namespace;public: JaktInternal::DynamicArray<Jakt::ids::ScopeId> generated_scopes;public: ResolvedForallChunk(JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> a_parameters, Jakt::parser::ParsedNamespace a_parsed_namespace, JaktInternal::DynamicArray<Jakt::ids::ScopeId> a_generated_scopes);

public: ByteString debug_description() const;
};struct TypeWithSkipList {
  public:
public: NonnullRefPtr<typename Jakt::types::Type> type;public: u32 hash;public: JaktInternal::Optional<Jakt::ids::TypeId> next_with_same_hash;public: TypeWithSkipList(NonnullRefPtr<typename Jakt::types::Type> a_type, u32 a_hash, JaktInternal::Optional<Jakt::ids::TypeId> a_next_with_same_hash);

public: ByteString debug_description() const;
};class Module :public RefCounted<Module>, public Weakable<Module> {
  public:
virtual ~Module() = default;
public: Jakt::ids::ModuleId id;public: ByteString name;public: JaktInternal::DynamicArray<Jakt::types::TypeWithSkipList> types;public: JaktInternal::Dictionary<u32,Jakt::ids::TypeId> type_skip_list;public: ByteString resolved_import_path;public: bool is_root;public: JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>> functions;public: JaktInternal::DynamicArray<Jakt::types::CheckedStruct> structures;public: JaktInternal::DynamicArray<Jakt::types::CheckedEnum> enums;public: JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Scope>> scopes;public: JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedTrait>> traits;public: JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>> variables;public: JaktInternal::DynamicArray<Jakt::ids::ModuleId> imports;public: JaktInternal::Dictionary<size_t,Jakt::ids::StructId> builtin_implementation_structs;public: bool is_prelude() const;
public: void add_type(NonnullRefPtr<typename Jakt::types::Type> const type);
public: Jakt::ids::TypeId new_type_variable(JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const implemented_traits);
public: Jakt::ids::FunctionId next_function_id() const;
public: Jakt::ids::FunctionId add_function(NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function);
public: Jakt::ids::VarId add_variable(NonnullRefPtr<Jakt::types::CheckedVariable> const checked_variable);
public: protected:
explicit Module(Jakt::ids::ModuleId a_id, ByteString a_name, JaktInternal::DynamicArray<Jakt::types::TypeWithSkipList> a_types, JaktInternal::Dictionary<u32,Jakt::ids::TypeId> a_type_skip_list, ByteString a_resolved_import_path, bool a_is_root, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>> a_functions, JaktInternal::DynamicArray<Jakt::types::CheckedStruct> a_structures, JaktInternal::DynamicArray<Jakt::types::CheckedEnum> a_enums, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Scope>> a_scopes, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedTrait>> a_traits, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>> a_variables, JaktInternal::DynamicArray<Jakt::ids::ModuleId> a_imports, JaktInternal::Dictionary<size_t,Jakt::ids::StructId> a_builtin_implementation_structs);
public:
static NonnullRefPtr<Module> __jakt_create(Jakt::ids::ModuleId id, ByteString name, JaktInternal::DynamicArray<Jakt::types::TypeWithSkipList> types, JaktInternal::Dictionary<u32,Jakt::ids::TypeId> type_skip_list, ByteString resolved_import_path, bool is_root, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>> functions, JaktInternal::DynamicArray<Jakt::types::CheckedStruct> structures, JaktInternal::DynamicArray<Jakt::types::CheckedEnum> enums, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Scope>> scopes, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedTrait>> traits, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>> variables, JaktInternal::DynamicArray<Jakt::ids::ModuleId> imports, JaktInternal::Dictionary<size_t,Jakt::ids::StructId> builtin_implementation_structs);

public: ByteString debug_description() const;
};struct CheckedTraitRequirements {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> value;
} Methods;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> value;
} ComptimeExpression;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static CheckedTraitRequirements Nothing();
[[nodiscard]] static CheckedTraitRequirements Methods(JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> value);
[[nodiscard]] static CheckedTraitRequirements ComptimeExpression(NonnullRefPtr<typename Jakt::types::CheckedExpression> value);
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
class CheckedTrait :public RefCounted<CheckedTrait>, public Weakable<CheckedTrait> {
  public:
virtual ~CheckedTrait() = default;
public: ByteString name;public: Jakt::utility::Span name_span;public: Jakt::types::CheckedTraitRequirements requirements;public: JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters;public: Jakt::ids::ScopeId scope_id;public: protected:
explicit CheckedTrait(ByteString a_name, Jakt::utility::Span a_name_span, Jakt::types::CheckedTraitRequirements a_requirements, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> a_generic_parameters, Jakt::ids::ScopeId a_scope_id);
public:
static NonnullRefPtr<CheckedTrait> __jakt_create(ByteString name, Jakt::utility::Span name_span, Jakt::types::CheckedTraitRequirements requirements, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters, Jakt::ids::ScopeId scope_id);

public: ByteString debug_description() const;
};struct LoadedModule {
  public:
public: Jakt::ids::ModuleId module_id;public: Jakt::utility::FileId file_id;public: LoadedModule(Jakt::ids::ModuleId a_module_id, Jakt::utility::FileId a_file_id);

public: ByteString debug_description() const;
};struct CheckedNamespace {
  public:
public: ByteString name;public: Jakt::ids::ScopeId scope;public: CheckedNamespace(ByteString a_name, Jakt::ids::ScopeId a_scope);

public: ByteString debug_description() const;
};struct MaybeResolvedScope: public RefCounted<MaybeResolvedScope> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::ids::ScopeId value;
} Resolved;
struct {
NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> parent_scope;
ByteString relative_name;
} Unresolved;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NonnullRefPtr<MaybeResolvedScope> Resolved(Jakt::ids::ScopeId value);
[[nodiscard]] static NonnullRefPtr<MaybeResolvedScope> Unresolved(NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> parent_scope, ByteString relative_name);
~MaybeResolvedScope();
MaybeResolvedScope& operator=(MaybeResolvedScope const &);
MaybeResolvedScope& operator=(MaybeResolvedScope &&);
MaybeResolvedScope(MaybeResolvedScope const&);
MaybeResolvedScope(MaybeResolvedScope &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> try_resolve(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const;
private:
MaybeResolvedScope() {};
};
struct CheckedVisibility {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> scopes;
Jakt::utility::Span span;
} Restricted;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static CheckedVisibility Public();
[[nodiscard]] static CheckedVisibility Private();
[[nodiscard]] static CheckedVisibility Restricted(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> scopes, Jakt::utility::Span span);
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
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
Jakt::types::BlockControlFlow unify_with(Jakt::types::BlockControlFlow const second) const;
Jakt::types::BlockControlFlow branch_unify_with(Jakt::types::BlockControlFlow const second) const;
Jakt::types::BlockControlFlow updated(Jakt::types::BlockControlFlow const second) const;
Jakt::types::BlockControlFlow partial() const;
Jakt::types::BlockControlFlow definitive() const;
bool always_transfers_control() const;
bool never_returns() const;
bool always_returns() const;
bool may_return() const;
bool may_break() const;
bool is_reachable() const;
private:
BlockControlFlow() {};
};
struct CheckedBlock {
  public:
public: JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> statements;public: Jakt::ids::ScopeId scope_id;public: Jakt::types::BlockControlFlow control_flow;public: JaktInternal::Optional<Jakt::ids::TypeId> yielded_type;public: bool yielded_none;public: bool is_for_loop;public: CheckedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> a_statements, Jakt::ids::ScopeId a_scope_id, Jakt::types::BlockControlFlow a_control_flow, JaktInternal::Optional<Jakt::ids::TypeId> a_yielded_type, bool a_yielded_none, bool a_is_for_loop);

public: ByteString debug_description() const;
};class CheckedFunction :public RefCounted<CheckedFunction>, public Weakable<CheckedFunction> {
  public:
virtual ~CheckedFunction() = default;
public: ByteString name;public: Jakt::utility::Span name_span;public: Jakt::types::CheckedVisibility visibility;public: Jakt::ids::TypeId return_type_id;public: JaktInternal::Optional<Jakt::utility::Span> return_type_span;public: JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params;public: NonnullRefPtr<Jakt::types::FunctionGenerics> generics;public: Jakt::types::CheckedBlock block;public: bool can_throw;public: Jakt::parser::FunctionType type;public: Jakt::parser::FunctionLinkage linkage;public: Jakt::ids::ScopeId function_scope_id;public: JaktInternal::Optional<Jakt::ids::StructId> struct_id;public: bool is_instantiated;public: JaktInternal::Optional<Jakt::parser::ParsedFunction> parsed_function;public: bool is_comptime;public: bool is_virtual;public: bool is_override;public: bool is_unsafe;public: bool has_varargs;public: JaktInternal::Optional<size_t> specialization_index;public: JaktInternal::Optional<Jakt::ids::ScopeId> owner_scope;public: JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> owner_scope_generics;public: bool is_fully_checked;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: JaktInternal::Optional<ByteString> deprecated_message;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>>> stores_arguments;public: Jakt::parser::InlineState force_inline;public: bool is_raw_constructor;public: Jakt::parser::ExternalName name_for_codegen() const;
public: ErrorOr<void> map_types(Function<ErrorOr<Jakt::ids::TypeId>(Jakt::ids::TypeId)> const& map);
public: NonnullRefPtr<Jakt::types::CheckedFunction> copy() const;
public: bool signature_matches(NonnullRefPtr<Jakt::types::CheckedFunction> const other, bool const ignore_this) const;
public: bool is_static() const;
public: bool is_mutating() const;
public: void add_param(Jakt::types::CheckedParameter const checked_param);
public: void set_params(JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const checked_params);
public: bool is_specialized_for_types(JaktInternal::DynamicArray<Jakt::ids::TypeId> const types) const;
public: Jakt::parser::ParsedFunction to_parsed_function() const;
public: protected:
explicit CheckedFunction(ByteString a_name, Jakt::utility::Span a_name_span, Jakt::types::CheckedVisibility a_visibility, Jakt::ids::TypeId a_return_type_id, JaktInternal::Optional<Jakt::utility::Span> a_return_type_span, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> a_params, NonnullRefPtr<Jakt::types::FunctionGenerics> a_generics, Jakt::types::CheckedBlock a_block, bool a_can_throw, Jakt::parser::FunctionType a_type, Jakt::parser::FunctionLinkage a_linkage, Jakt::ids::ScopeId a_function_scope_id, JaktInternal::Optional<Jakt::ids::StructId> a_struct_id, bool a_is_instantiated, JaktInternal::Optional<Jakt::parser::ParsedFunction> a_parsed_function, bool a_is_comptime, bool a_is_virtual, bool a_is_override, bool a_is_unsafe, bool a_has_varargs, JaktInternal::Optional<size_t> a_specialization_index, JaktInternal::Optional<Jakt::ids::ScopeId> a_owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> a_owner_scope_generics, bool a_is_fully_checked, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Optional<ByteString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>>> a_stores_arguments, Jakt::parser::InlineState a_force_inline, bool a_is_raw_constructor);
public:
static NonnullRefPtr<CheckedFunction> __jakt_create(ByteString name, Jakt::utility::Span name_span, Jakt::types::CheckedVisibility visibility, Jakt::ids::TypeId return_type_id, JaktInternal::Optional<Jakt::utility::Span> return_type_span, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params, NonnullRefPtr<Jakt::types::FunctionGenerics> generics, Jakt::types::CheckedBlock block, bool can_throw, Jakt::parser::FunctionType type, Jakt::parser::FunctionLinkage linkage, Jakt::ids::ScopeId function_scope_id, JaktInternal::Optional<Jakt::ids::StructId> struct_id, bool is_instantiated, JaktInternal::Optional<Jakt::parser::ParsedFunction> parsed_function, bool is_comptime, bool is_virtual, bool is_override, bool is_unsafe, bool has_varargs, JaktInternal::Optional<size_t> specialization_index, JaktInternal::Optional<Jakt::ids::ScopeId> owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> owner_scope_generics, bool is_fully_checked, JaktInternal::Optional<Jakt::parser::ExternalName> external_name, JaktInternal::Optional<ByteString> deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>>> stores_arguments, Jakt::parser::InlineState force_inline, bool is_raw_constructor);

public: ByteString debug_description() const;
};class FunctionGenerics :public RefCounted<FunctionGenerics>, public Weakable<FunctionGenerics> {
  public:
virtual ~FunctionGenerics() = default;
public: Jakt::ids::ScopeId base_scope_id;public: JaktInternal::DynamicArray<Jakt::types::CheckedParameter> base_params;public: JaktInternal::DynamicArray<Jakt::types::FunctionGenericParameter> params;public: JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> specializations;public: bool is_specialized_for_types(JaktInternal::DynamicArray<Jakt::ids::TypeId> const types) const;
public: protected:
explicit FunctionGenerics(Jakt::ids::ScopeId a_base_scope_id, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> a_base_params, JaktInternal::DynamicArray<Jakt::types::FunctionGenericParameter> a_params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> a_specializations);
public:
static NonnullRefPtr<FunctionGenerics> __jakt_create(Jakt::ids::ScopeId base_scope_id, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> base_params, JaktInternal::DynamicArray<Jakt::types::FunctionGenericParameter> params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> specializations);

public: ByteString debug_description() const;
};struct CheckedParameter {
  public:
public: bool requires_label;public: NonnullRefPtr<Jakt::types::CheckedVariable> variable;public: JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> default_value_expression;public: ErrorOr<Jakt::types::CheckedParameter> map_types(Function<ErrorOr<Jakt::ids::TypeId>(Jakt::ids::TypeId)> const& map) const;
public: CheckedParameter(bool a_requires_label, NonnullRefPtr<Jakt::types::CheckedVariable> a_variable, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> a_default_value_expression);

public: ByteString debug_description() const;
};struct CheckedCapture {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
ByteString name;
Jakt::utility::Span span;
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
[[nodiscard]] static CheckedCapture ByValue(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static CheckedCapture ByReference(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static CheckedCapture ByMutableReference(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static CheckedCapture ByComptimeDependency(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static CheckedCapture AllByReference(ByteString name, Jakt::utility::Span span);
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
struct FunctionGenericParameterKind {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
struct CheckedGenericParameter {
  public:
public: Jakt::ids::TypeId type_id;public: JaktInternal::DynamicArray<Jakt::ids::TraitId> constraints;public: Jakt::utility::Span span;public: static Jakt::types::CheckedGenericParameter make(Jakt::ids::TypeId const type_id, Jakt::utility::Span const span);
public: CheckedGenericParameter(Jakt::ids::TypeId a_type_id, JaktInternal::DynamicArray<Jakt::ids::TraitId> a_constraints, Jakt::utility::Span a_span);

public: ByteString debug_description() const;
};struct FunctionGenericParameter {
  public:
public: Jakt::types::FunctionGenericParameterKind kind;public: Jakt::types::CheckedGenericParameter checked_parameter;public: Jakt::ids::TypeId type_id() const;
public: static Jakt::types::FunctionGenericParameter parameter(Jakt::ids::TypeId const type_id, Jakt::utility::Span const span);
public: FunctionGenericParameter(Jakt::types::FunctionGenericParameterKind a_kind, Jakt::types::CheckedGenericParameter a_checked_parameter);

public: ByteString debug_description() const;
};class CheckedVariable :public RefCounted<CheckedVariable>, public Weakable<CheckedVariable> {
  public:
virtual ~CheckedVariable() = default;
public: ByteString name;public: Jakt::ids::TypeId type_id;public: bool is_mutable;public: Jakt::utility::Span definition_span;public: JaktInternal::Optional<Jakt::utility::Span> type_span;public: Jakt::types::CheckedVisibility visibility;public: bool invisible_to_ide;public: JaktInternal::Optional<Jakt::ids::ScopeId> owner_scope;public: JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> owner_scope_generics;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: ErrorOr<NonnullRefPtr<Jakt::types::CheckedVariable>> map_types(Function<ErrorOr<Jakt::ids::TypeId>(Jakt::ids::TypeId)> const& map) const;
public: Jakt::parser::ExternalName name_for_codegen() const;
public: protected:
explicit CheckedVariable(ByteString a_name, Jakt::ids::TypeId a_type_id, bool a_is_mutable, Jakt::utility::Span a_definition_span, JaktInternal::Optional<Jakt::utility::Span> a_type_span, Jakt::types::CheckedVisibility a_visibility, bool a_invisible_to_ide, JaktInternal::Optional<Jakt::ids::ScopeId> a_owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> a_owner_scope_generics, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name);
public:
static NonnullRefPtr<CheckedVariable> __jakt_create(ByteString name, Jakt::ids::TypeId type_id, bool is_mutable, Jakt::utility::Span definition_span, JaktInternal::Optional<Jakt::utility::Span> type_span, Jakt::types::CheckedVisibility visibility, bool invisible_to_ide, JaktInternal::Optional<Jakt::ids::ScopeId> owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> owner_scope_generics, JaktInternal::Optional<Jakt::parser::ExternalName> external_name);

public: ByteString debug_description() const;
};struct CheckedVarDecl {
  public:
public: ByteString name;public: bool is_mutable;public: Jakt::utility::Span span;public: Jakt::ids::TypeId type_id;public: CheckedVarDecl(ByteString a_name, bool a_is_mutable, Jakt::utility::Span a_span, Jakt::ids::TypeId a_type_id);

public: ByteString debug_description() const;
};struct FieldRecord {
  public:
public: Jakt::ids::StructId struct_id;public: Jakt::ids::VarId field_id;public: FieldRecord(Jakt::ids::StructId a_struct_id, Jakt::ids::VarId a_field_id);

public: ByteString debug_description() const;
};class CheckedField :public RefCounted<CheckedField>, public Weakable<CheckedField> {
  public:
virtual ~CheckedField() = default;
public: Jakt::ids::VarId variable_id;public: JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> default_value_expression;public: JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> default_value_in_definition_scope;public: protected:
explicit CheckedField(Jakt::ids::VarId a_variable_id, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> a_default_value_expression, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> a_default_value_in_definition_scope);
public:
static NonnullRefPtr<CheckedField> __jakt_create(Jakt::ids::VarId variable_id, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> default_value_expression, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> default_value_in_definition_scope);

public: ByteString debug_description() const;
};struct CheckedStruct {
  public:
public: ByteString name;public: Jakt::utility::Span name_span;public: JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>> generic_parameter_defaults;public: JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> fields;public: Jakt::ids::ScopeId scope_id;public: Jakt::parser::DefinitionLinkage definition_linkage;public: JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> trait_implementations;public: Jakt::parser::RecordType record_type;public: Jakt::ids::TypeId type_id;public: JaktInternal::Optional<Jakt::ids::StructId> super_struct_id;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: JaktInternal::Optional<Jakt::ids::TypeId> implements_type;public: JaktInternal::Optional<ByteString> create_function_name;public: Jakt::parser::ExternalName name_for_codegen() const;
public: CheckedStruct(ByteString a_name, Jakt::utility::Span a_name_span, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> a_generic_parameters, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>> a_generic_parameter_defaults, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> a_fields, Jakt::ids::ScopeId a_scope_id, Jakt::parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> a_trait_implementations, Jakt::parser::RecordType a_record_type, Jakt::ids::TypeId a_type_id, JaktInternal::Optional<Jakt::ids::StructId> a_super_struct_id, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Optional<Jakt::ids::TypeId> a_implements_type, JaktInternal::Optional<ByteString> a_create_function_name);

public: ByteString debug_description() const;
};struct CheckedEnum {
  public:
public: ByteString name;public: Jakt::utility::Span name_span;public: JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters;public: JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariant> variants;public: JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> fields;public: Jakt::ids::ScopeId scope_id;public: Jakt::parser::DefinitionLinkage definition_linkage;public: JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> trait_implementations;public: Jakt::parser::RecordType record_type;public: Jakt::ids::TypeId underlying_type_id;public: Jakt::ids::TypeId type_id;public: bool is_boxed;public: CheckedEnum(ByteString a_name, Jakt::utility::Span a_name_span, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> a_generic_parameters, JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariant> a_variants, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> a_fields, Jakt::ids::ScopeId a_scope_id, Jakt::parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> a_trait_implementations, Jakt::parser::RecordType a_record_type, Jakt::ids::TypeId a_underlying_type_id, Jakt::ids::TypeId a_type_id, bool a_is_boxed);

public: ByteString debug_description() const;
};struct CheckedEnumVariant {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::ids::EnumId enum_id;
ByteString name;
Jakt::utility::Span span;
} Untyped;
struct {
Jakt::ids::EnumId enum_id;
ByteString name;
Jakt::ids::TypeId type_id;
Jakt::utility::Span span;
} Typed;
struct {
Jakt::ids::EnumId enum_id;
ByteString name;
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::utility::Span span;
} WithValue;
struct {
Jakt::ids::EnumId enum_id;
ByteString name;
JaktInternal::DynamicArray<Jakt::ids::VarId> fields;
Jakt::utility::Span span;
} StructLike;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static CheckedEnumVariant Untyped(Jakt::ids::EnumId enum_id, ByteString name, Jakt::utility::Span span);
[[nodiscard]] static CheckedEnumVariant Typed(Jakt::ids::EnumId enum_id, ByteString name, Jakt::ids::TypeId type_id, Jakt::utility::Span span);
[[nodiscard]] static CheckedEnumVariant WithValue(Jakt::ids::EnumId enum_id, ByteString name, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static CheckedEnumVariant StructLike(Jakt::ids::EnumId enum_id, ByteString name, JaktInternal::DynamicArray<Jakt::ids::VarId> fields, Jakt::utility::Span span);
~CheckedEnumVariant();
CheckedEnumVariant& operator=(CheckedEnumVariant const &);
CheckedEnumVariant& operator=(CheckedEnumVariant &&);
CheckedEnumVariant(CheckedEnumVariant const&);
CheckedEnumVariant(CheckedEnumVariant &&);
private: void __jakt_destroy_variant();
public:
bool equals(Jakt::types::CheckedEnumVariant const other) const;
Jakt::ids::EnumId enum_id() const;
Jakt::utility::Span span() const;
ByteString name() const;
private:
CheckedEnumVariant() {};
};
struct CheckedEnumVariantBinding {
  public:
public: JaktInternal::Optional<ByteString> name;public: ByteString binding;public: Jakt::ids::TypeId type_id;public: Jakt::utility::Span span;public: CheckedEnumVariantBinding(JaktInternal::Optional<ByteString> a_name, ByteString a_binding, Jakt::ids::TypeId a_type_id, Jakt::utility::Span a_span);

public: ByteString debug_description() const;
};struct CheckedStatement: public RefCounted<CheckedStatement> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::utility::Span span;
} Expression;
struct {
NonnullRefPtr<typename Jakt::types::CheckedStatement> statement;
Jakt::utility::Span span;
} Defer;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> vars;
NonnullRefPtr<typename Jakt::types::CheckedStatement> var_decl;
Jakt::utility::Span span;
} DestructuringDeclaration;
struct {
Jakt::ids::VarId var_id;
NonnullRefPtr<typename Jakt::types::CheckedExpression> init;
Jakt::utility::Span span;
} VarDecl;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> condition;
Jakt::types::CheckedBlock then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> else_statement;
Jakt::utility::Span span;
} If;
struct {
Jakt::types::CheckedBlock block;
Jakt::utility::Span span;
} Block;
struct {
Jakt::types::CheckedBlock block;
Jakt::utility::Span span;
} Loop;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> condition;
Jakt::types::CheckedBlock block;
Jakt::utility::Span span;
} While;
struct {
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> val;
JaktInternal::Optional<Jakt::utility::Span> span;
} Return;
struct {
Jakt::utility::Span value;
} Break;
struct {
Jakt::utility::Span value;
} Continue;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::utility::Span span;
} Throw;
struct {
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> expr;
Jakt::utility::Span span;
} Yield;
struct {
JaktInternal::DynamicArray<ByteString> lines;
Jakt::utility::Span span;
} InlineCpp;
struct {
Jakt::utility::Span value;
} Garbage;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Defer(NonnullRefPtr<typename Jakt::types::CheckedStatement> statement, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> DestructuringDeclaration(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> vars, NonnullRefPtr<typename Jakt::types::CheckedStatement> var_decl, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> VarDecl(Jakt::ids::VarId var_id, NonnullRefPtr<typename Jakt::types::CheckedExpression> init, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> If(NonnullRefPtr<typename Jakt::types::CheckedExpression> condition, Jakt::types::CheckedBlock then_block, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> else_statement, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Block(Jakt::types::CheckedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Loop(Jakt::types::CheckedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> While(NonnullRefPtr<typename Jakt::types::CheckedExpression> condition, Jakt::types::CheckedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Return(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> val, JaktInternal::Optional<Jakt::utility::Span> span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Break(Jakt::utility::Span value);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Continue(Jakt::utility::Span value);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Throw(NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Yield(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> InlineCpp(JaktInternal::DynamicArray<ByteString> lines, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedStatement> Garbage(Jakt::utility::Span value);
~CheckedStatement();
CheckedStatement& operator=(CheckedStatement const &);
CheckedStatement& operator=(CheckedStatement &&);
CheckedStatement(CheckedStatement const&);
CheckedStatement(CheckedStatement &&);
private: void __jakt_destroy_variant();
public:
JaktInternal::Optional<Jakt::utility::Span> span() const;
static JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> none();
static Jakt::types::BlockControlFlow maybe_control_flow(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const statement, Jakt::types::BlockControlFlow const other_branch);
Jakt::types::BlockControlFlow control_flow() const;
private:
CheckedStatement() {};
};
struct NumberConstant {
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
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
bool can_fit_number(Jakt::ids::TypeId const type_id, NonnullRefPtr<Jakt::types::CheckedProgram> const program) const;
size_t to_usize() const;
private:
NumberConstant() {};
};
struct CheckedNumericConstant {
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
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
JaktInternal::Optional<Jakt::types::NumberConstant> number_constant() const;
private:
CheckedNumericConstant() {};
};
struct StringLiteral {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString value;
} Static;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
public: Jakt::types::StringLiteral value;public: Jakt::ids::TypeId type_id;public: bool may_throw;public: ByteString to_string() const;
public: CheckedStringLiteral(Jakt::types::StringLiteral a_value, Jakt::ids::TypeId a_type_id, bool a_may_throw);

public: ByteString debug_description() const;
};struct CheckedTypeCast {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::ids::TypeId value;
} Fallible;
struct {
Jakt::ids::TypeId value;
} Infallible;
struct {
Jakt::ids::TypeId value;
} Identity;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static CheckedTypeCast Fallible(Jakt::ids::TypeId value);
[[nodiscard]] static CheckedTypeCast Infallible(Jakt::ids::TypeId value);
[[nodiscard]] static CheckedTypeCast Identity(Jakt::ids::TypeId value);
~CheckedTypeCast();
CheckedTypeCast& operator=(CheckedTypeCast const &);
CheckedTypeCast& operator=(CheckedTypeCast &&);
CheckedTypeCast(CheckedTypeCast const&);
CheckedTypeCast(CheckedTypeCast &&);
private: void __jakt_destroy_variant();
public:
Jakt::ids::TypeId type_id() const;
private:
CheckedTypeCast() {};
};
struct CheckedUnaryOperator {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::types::CheckedTypeCast value;
} TypeCast;
struct {
Jakt::ids::TypeId value;
} Is;
struct {
Jakt::types::CheckedEnumVariant enum_variant;
JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding> bindings;
Jakt::ids::TypeId type_id;
} IsEnumVariant;
struct {
Jakt::ids::TypeId value;
} Sizeof;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
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
[[nodiscard]] static CheckedUnaryOperator TypeCast(Jakt::types::CheckedTypeCast value);
[[nodiscard]] static CheckedUnaryOperator Is(Jakt::ids::TypeId value);
[[nodiscard]] static CheckedUnaryOperator IsEnumVariant(Jakt::types::CheckedEnumVariant enum_variant, JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding> bindings, Jakt::ids::TypeId type_id);
[[nodiscard]] static CheckedUnaryOperator IsSome();
[[nodiscard]] static CheckedUnaryOperator IsNone();
[[nodiscard]] static CheckedUnaryOperator Sizeof(Jakt::ids::TypeId value);
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
struct CheckedMatchBody {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> value;
} Expression;
struct {
Jakt::types::CheckedBlock value;
} Block;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static CheckedMatchBody Expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> value);
[[nodiscard]] static CheckedMatchBody Block(Jakt::types::CheckedBlock value);
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
struct ClassInstanceRebind {
  public:
public: ByteString name;public: Jakt::utility::Span name_span;public: bool is_mutable;public: bool is_reference;public: ClassInstanceRebind(ByteString a_name, Jakt::utility::Span a_name_span, bool a_is_mutable, bool a_is_reference);

public: ByteString debug_description() const;
};struct CheckedMatchCase {
  public:
public: JaktInternal::DynamicArray<Jakt::types::CheckedMatchPattern> patterns;public: Jakt::types::CheckedMatchBody body;public: JaktInternal::Dictionary<ByteString,Jakt::ids::VarId> bindings;public: CheckedMatchCase(JaktInternal::DynamicArray<Jakt::types::CheckedMatchPattern> a_patterns, Jakt::types::CheckedMatchBody a_body, JaktInternal::Dictionary<ByteString,Jakt::ids::VarId> a_bindings);

public: ByteString debug_description() const;
};struct CheckedMatchPattern {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Dictionary<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> defaults;
Jakt::utility::Span marker_span;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString name;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> args;
Jakt::ids::TypeId subject_type_id;
size_t index;
} EnumVariant;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expression;
} Expression;
struct {
Jakt::ids::TypeId type;
JaktInternal::Optional<Jakt::types::ClassInstanceRebind> rebind_name;
} ClassInstance;
struct {
bool has_arguments;
} CatchAll;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static CheckedMatchPattern EnumVariant(JaktInternal::Dictionary<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> defaults, Jakt::utility::Span marker_span, ByteString name, JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> args, Jakt::ids::TypeId subject_type_id, size_t index);
[[nodiscard]] static CheckedMatchPattern Expression(JaktInternal::Dictionary<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> defaults, Jakt::utility::Span marker_span, NonnullRefPtr<typename Jakt::types::CheckedExpression> expression);
[[nodiscard]] static CheckedMatchPattern ClassInstance(JaktInternal::Dictionary<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> defaults, Jakt::utility::Span marker_span, Jakt::ids::TypeId type, JaktInternal::Optional<Jakt::types::ClassInstanceRebind> rebind_name);
[[nodiscard]] static CheckedMatchPattern CatchAll(JaktInternal::Dictionary<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> defaults, Jakt::utility::Span marker_span, bool has_arguments);
~CheckedMatchPattern();
CheckedMatchPattern& operator=(CheckedMatchPattern const &);
CheckedMatchPattern& operator=(CheckedMatchPattern &&);
CheckedMatchPattern(CheckedMatchPattern const&);
CheckedMatchPattern(CheckedMatchPattern &&);
private: void __jakt_destroy_variant();
public:
private:
CheckedMatchPattern() {};
};
struct CheckedCall {
  public:
public: JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> namespace_;public: ByteString name;public: JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> args;public: JaktInternal::DynamicArray<Jakt::ids::TypeId> type_args;public: JaktInternal::Optional<Jakt::ids::FunctionId> function_id;public: Jakt::ids::TypeId return_type;public: bool callee_throws;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: Jakt::parser::InlineState force_inline;public: Jakt::parser::ExternalName name_for_codegen() const;
public: CheckedCall(JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> a_namespace_, ByteString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> a_args, JaktInternal::DynamicArray<Jakt::ids::TypeId> a_type_args, JaktInternal::Optional<Jakt::ids::FunctionId> a_function_id, Jakt::ids::TypeId a_return_type, bool a_callee_throws, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, Jakt::parser::InlineState a_force_inline);

public: ByteString debug_description() const;
};struct OperatorTraitImplementation {
  public:
public: Jakt::ids::TraitId trait_id;public: JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_generic_arguments;public: Jakt::types::CheckedCall call_expression;public: OperatorTraitImplementation(Jakt::ids::TraitId a_trait_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> a_trait_generic_arguments, Jakt::types::CheckedCall a_call_expression);

public: ByteString debug_description() const;
};struct CheckedBinaryOperator {
  public:
public: Jakt::parser::BinaryOperator op;public: JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> trait_implementation;public: CheckedBinaryOperator(Jakt::parser::BinaryOperator a_op, JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> a_trait_implementation);

public: ByteString debug_description() const;
};struct CheckedExpression: public RefCounted<CheckedExpression> {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
bool val;
Jakt::utility::Span span;
} Boolean;
struct {
Jakt::types::CheckedNumericConstant val;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} NumericConstant;
struct {
Jakt::types::CheckedStringLiteral val;
Jakt::utility::Span span;
} QuotedString;
struct {
ByteString val;
Jakt::utility::Span span;
} ByteConstant;
struct {
ByteString val;
Jakt::utility::Span span;
} CharacterConstant;
struct {
ByteString val;
Jakt::utility::Span span;
} CCharacterConstant;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::types::CheckedUnaryOperator op;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} UnaryOp;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> lhs;
Jakt::types::CheckedBinaryOperator op;
NonnullRefPtr<typename Jakt::types::CheckedExpression> rhs;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} BinaryOp;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} JaktTuple;
struct {
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> to;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} Range;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> repeat;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
Jakt::ids::TypeId inner_type_id;
} JaktArray;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
Jakt::ids::TypeId inner_type_id;
} JaktSet;
struct {
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> vals;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
Jakt::ids::TypeId key_type_id;
Jakt::ids::TypeId value_type_id;
} JaktDictionary;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> index;
JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> trait_implementation;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} IndexedExpression;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> index;
JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> trait_implementation;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} IndexedDictionary;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
size_t index;
Jakt::utility::Span span;
bool is_optional;
Jakt::ids::TypeId type_id;
} IndexedTuple;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
ByteString name;
JaktInternal::Optional<Jakt::ids::VarId> index;
Jakt::utility::Span span;
bool is_optional;
Jakt::ids::TypeId type_id;
} IndexedStruct;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
ByteString index;
Jakt::utility::Span span;
bool is_optional;
Jakt::ids::TypeId type_id;
} IndexedCommonEnumMember;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> index;
bool is_optional;
Jakt::utility::Span span;
} ComptimeIndex;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> match_cases;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
bool all_variants_constant;
} Match;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::types::CheckedEnumVariantBinding arg;
Jakt::types::CheckedEnumVariant enum_variant;
Jakt::utility::Span span;
} EnumVariantArg;
struct {
Jakt::types::CheckedCall call;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} Call;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::types::CheckedCall call;
Jakt::utility::Span span;
bool is_optional;
Jakt::ids::TypeId type_id;
} MethodCall;
struct {
JaktInternal::DynamicArray<Jakt::types::CheckedNamespace> namespaces;
NonnullRefPtr<Jakt::types::CheckedVariable> var;
Jakt::utility::Span span;
} NamespacedVar;
struct {
NonnullRefPtr<Jakt::types::CheckedVariable> var;
Jakt::utility::Span span;
} Var;
struct {
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} OptionalNone;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} OptionalSome;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} ForcedUnwrap;
struct {
Jakt::types::CheckedBlock block;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} Block;
struct {
JaktInternal::DynamicArray<Jakt::types::CheckedCapture> captures;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params;
bool can_throw;
Jakt::ids::TypeId return_type_id;
Jakt::types::CheckedBlock block;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id;
Jakt::ids::ScopeId scope_id;
} Function;
struct {
JaktInternal::DynamicArray<Jakt::types::CheckedCapture> captures;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params;
bool can_throw;
Jakt::ids::TypeId return_type_id;
Jakt::parser::ParsedBlock block;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id;
Jakt::ids::ScopeId scope_id;
} DependentFunction;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} Must;
struct {
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr;
JaktInternal::Optional<Jakt::types::CheckedBlock> catch_block;
JaktInternal::Optional<Jakt::utility::Span> catch_span;
JaktInternal::Optional<ByteString> catch_name;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
Jakt::ids::TypeId inner_type_id;
} Try;
struct {
NonnullRefPtr<typename Jakt::types::CheckedStatement> stmt;
Jakt::types::CheckedBlock catch_block;
ByteString error_name;
Jakt::utility::Span error_span;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} TryBlock;
struct {
Jakt::ids::TypeId type;
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} Reflect;
struct {
Jakt::utility::Span span;
Jakt::ids::TypeId type_id;
} Garbage;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Boolean(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, bool val, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> NumericConstant(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::types::CheckedNumericConstant val, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> QuotedString(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::types::CheckedStringLiteral val, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> ByteConstant(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, ByteString val, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> CharacterConstant(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, ByteString val, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> CCharacterConstant(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, ByteString val, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> UnaryOp(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::types::CheckedUnaryOperator op, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> BinaryOp(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> lhs, Jakt::types::CheckedBinaryOperator op, NonnullRefPtr<typename Jakt::types::CheckedExpression> rhs, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> JaktTuple(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Range(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> from, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> to, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> JaktArray(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> repeat, Jakt::utility::Span span, Jakt::ids::TypeId type_id, Jakt::ids::TypeId inner_type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> JaktSet(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals, Jakt::utility::Span span, Jakt::ids::TypeId type_id, Jakt::ids::TypeId inner_type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> JaktDictionary(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> vals, Jakt::utility::Span span, Jakt::ids::TypeId type_id, Jakt::ids::TypeId key_type_id, Jakt::ids::TypeId value_type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> IndexedExpression(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, NonnullRefPtr<typename Jakt::types::CheckedExpression> index, JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> trait_implementation, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> IndexedDictionary(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, NonnullRefPtr<typename Jakt::types::CheckedExpression> index, JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> trait_implementation, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> IndexedTuple(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, size_t index, Jakt::utility::Span span, bool is_optional, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> IndexedStruct(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, ByteString name, JaktInternal::Optional<Jakt::ids::VarId> index, Jakt::utility::Span span, bool is_optional, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> IndexedCommonEnumMember(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, ByteString index, Jakt::utility::Span span, bool is_optional, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> ComptimeIndex(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, NonnullRefPtr<typename Jakt::types::CheckedExpression> index, bool is_optional, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Match(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> match_cases, Jakt::utility::Span span, Jakt::ids::TypeId type_id, bool all_variants_constant);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> EnumVariantArg(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::types::CheckedEnumVariantBinding arg, Jakt::types::CheckedEnumVariant enum_variant, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Call(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::types::CheckedCall call, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> MethodCall(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::types::CheckedCall call, Jakt::utility::Span span, bool is_optional, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> NamespacedVar(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<Jakt::types::CheckedNamespace> namespaces, NonnullRefPtr<Jakt::types::CheckedVariable> var, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Var(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<Jakt::types::CheckedVariable> var, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> OptionalNone(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> OptionalSome(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> ForcedUnwrap(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Block(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::types::CheckedBlock block, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Function(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<Jakt::types::CheckedCapture> captures, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params, bool can_throw, Jakt::ids::TypeId return_type_id, Jakt::types::CheckedBlock block, Jakt::utility::Span span, Jakt::ids::TypeId type_id, JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id, Jakt::ids::ScopeId scope_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> DependentFunction(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<Jakt::types::CheckedCapture> captures, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params, bool can_throw, Jakt::ids::TypeId return_type_id, Jakt::parser::ParsedBlock block, Jakt::utility::Span span, Jakt::ids::TypeId type_id, JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id, Jakt::ids::ScopeId scope_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Must(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Try(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, JaktInternal::Optional<Jakt::types::CheckedBlock> catch_block, JaktInternal::Optional<Jakt::utility::Span> catch_span, JaktInternal::Optional<ByteString> catch_name, Jakt::utility::Span span, Jakt::ids::TypeId type_id, Jakt::ids::TypeId inner_type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> TryBlock(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedStatement> stmt, Jakt::types::CheckedBlock catch_block, ByteString error_name, Jakt::utility::Span error_span, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Reflect(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::ids::TypeId type, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<CheckedExpression> Garbage(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::utility::Span span, Jakt::ids::TypeId type_id);
~CheckedExpression();
CheckedExpression& operator=(CheckedExpression const &);
CheckedExpression& operator=(CheckedExpression &&);
CheckedExpression(CheckedExpression const&);
CheckedExpression(CheckedExpression &&);
private: void __jakt_destroy_variant();
public:
JaktInternal::Optional<Jakt::types::NumberConstant> to_number_constant(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const;
Jakt::utility::Span span() const;
bool is_mutable(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const;
bool can_throw() const;
Jakt::ids::TypeId type() const;
Jakt::types::BlockControlFlow control_flow() const;
private:
CheckedExpression() {};
};
struct ResolvedNamespace {
  public:
public: ByteString name;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> generic_parameters;public: Jakt::parser::ExternalName name_for_codegen() const;
public: ResolvedNamespace(ByteString a_name, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> a_generic_parameters);

public: ByteString debug_description() const;
};class CheckedProgram :public RefCounted<CheckedProgram>, public Weakable<CheckedProgram> {
  public:
virtual ~CheckedProgram() = default;
public: NonnullRefPtr<Jakt::compiler::Compiler> compiler;public: JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Module>> modules;public: JaktInternal::Dictionary<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> exports;public: JaktInternal::Dictionary<ByteString,Jakt::types::LoadedModule> loaded_modules;public: Jakt::ids::ModuleId create_module(ByteString const name, bool const is_root, JaktInternal::Optional<ByteString> const path);
public: ByteString debug_description_of(Jakt::ids::ScopeId const scope_id) const;
public: Jakt::ids::ScopeId create_scope(JaktInternal::Optional<Jakt::ids::ScopeId> const parent_scope_id, bool const can_throw, ByteString const debug_name, Jakt::ids::ModuleId const module_id, bool const for_block);
public: Jakt::ids::TypeId apply_qualifiers_to_type(Jakt::parser::CheckedQualifiers const qualifiers, Jakt::ids::TypeId const type_id);
public: Jakt::ids::StructId builtin_implementation_struct(Jakt::types::BuiltinType const builtin, Jakt::ids::ModuleId const for_module);
public: NonnullRefPtr<Jakt::types::Module> get_module(Jakt::ids::ModuleId const id) const;
public: NonnullRefPtr<Jakt::types::CheckedFunction> get_function(Jakt::ids::FunctionId const id) const;
public: NonnullRefPtr<Jakt::types::CheckedVariable> get_variable(Jakt::ids::VarId const id) const;
public: NonnullRefPtr<typename Jakt::types::Type> get_type(Jakt::ids::TypeId const id) const;
public: Jakt::types::CheckedEnum get_enum(Jakt::ids::EnumId const id) const;
public: Jakt::types::CheckedStruct get_struct(Jakt::ids::StructId const id) const;
public: NonnullRefPtr<Jakt::types::Scope> get_scope(Jakt::ids::ScopeId const id) const;
public: NonnullRefPtr<Jakt::types::CheckedTrait> get_trait(Jakt::ids::TraitId const id) const;
public: Jakt::ids::ScopeId prelude_scope_id() const;
public: Jakt::ids::ModuleId prelude_module_id() const;
public: void set_loaded_module(ByteString const module_name, Jakt::types::LoadedModule const loaded_module);
public: JaktInternal::Optional<Jakt::types::LoadedModule> get_loaded_module(ByteString const module_name) const;
public: void set_owner_scope_if_needed(Jakt::ids::ScopeId const parent_scope_id, JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set, Jakt::utility::Span const span);
public: void set_owner_scope_if_needed(Jakt::ids::ScopeId const parent_scope_id, Jakt::ids::VarId const var_id);
public: ErrorOr<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>>> find_var_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const var, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<Jakt::types::Value>> find_comptime_binding_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>> find_type_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::TypeId>> find_type_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::EnumId>> find_enum_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::TraitId>> find_trait_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: bool is_integer(Jakt::ids::TypeId const type_id) const;
public: bool is_floating(Jakt::ids::TypeId const type_id) const;
public: bool is_numeric(Jakt::ids::TypeId const type_id) const;
public: ErrorOr<bool> is_string(Jakt::ids::TypeId const type_id) const;
public: i64 get_bits(Jakt::ids::TypeId const type_id) const;
public: bool is_signed(Jakt::ids::TypeId const type_id) const;
private: ErrorOr<JaktInternal::Optional<bool>> for_each_scope_accessible_unqualified_from_scope_direct_chain(Jakt::ids::ScopeId const scope_id, Function<ErrorOr<typename Jakt::utility::IterationDecision<bool>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
private: ErrorOr<JaktInternal::Optional<bool>> for_each_scope_accessible_unqualified_from_scope_impl(Jakt::ids::ScopeId const scope_id, Function<ErrorOr<typename Jakt::utility::IterationDecision<bool>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::StructId>> find_struct_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<Jakt::ids::StructId> find_struct_in_prelude(ByteString const name) const;
public: ErrorOr<bool> is_scope_directly_accessible_from(Jakt::ids::ScopeId const check_scope_id, Jakt::ids::ScopeId const scope_id, bool const ignore_mixin_scopes) const;
public: ErrorOr<Jakt::types::StructOrEnumId> find_reflected_primitive(ByteString const primitive) const;
public: Jakt::ids::ScopeId find_type_scope_id(Jakt::ids::TypeId const type_id);
public: JaktInternal::Optional<Jakt::ids::ScopeId> find_namespace_in_immediate_children_of_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const treat_aliases_as_imports) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>> find_namespace_in_scope(Jakt::ids::ScopeId const scope_id, ByteString const name, bool const treat_aliases_as_imports, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> find_function_in_scope(Jakt::ids::ScopeId const parent_scope_id, ByteString const function_name, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> find_default_constructors_in_scope(Jakt::ids::ScopeId const parent_scope_id, ByteString const function_name, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> find_functions_with_name_in_scope(Jakt::ids::ScopeId const parent_scope_id, ByteString const function_name, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>> find_scoped_functions_with_name_in_scope(Jakt::ids::ScopeId const parent_scope_id, ByteString const function_name, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: ErrorOr<JaktInternal::Optional<Jakt::ids::StructId>> check_and_extract_weak_ptr(Jakt::ids::StructId const struct_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> const args) const;
public: ErrorOr<ByteString> type_name(Jakt::ids::TypeId const type_id, bool const debug_mode) const;
public: Jakt::ids::TypeId find_or_add_type_id(NonnullRefPtr<typename Jakt::types::Type> const type, Jakt::ids::ModuleId const module_id, bool const only_in_current_module);
public: ErrorOr<Jakt::ids::TypeId> substitute_typevars_in_type(Jakt::ids::TypeId const type_id, Jakt::types::GenericInferences const generic_inferences, Jakt::ids::ModuleId const module_id);
public: ErrorOr<Jakt::ids::TypeId> specialize_type_id(Jakt::ids::TypeId const type_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> const new_args, bool const replace_args, Jakt::ids::ModuleId const module_id);
private: ErrorOr<Jakt::ids::TypeId> substitute_typevars_in_type_helper(Jakt::ids::TypeId const type_id, Jakt::types::GenericInferences const generic_inferences, Jakt::ids::ModuleId const module_id);
public: template <typename T>
ErrorOr<JaktInternal::Optional<T>> for_each_scope_accessible_unqualified_from_scope(Jakt::ids::ScopeId const scope_id, Function<ErrorOr<typename Jakt::utility::IterationDecision<T>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback, bool const ignore_mixin_scopes, JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const;
public: public: public: public: public: public: public: public: public: public: protected:
explicit CheckedProgram(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Module>> a_modules, JaktInternal::Dictionary<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> a_exports, JaktInternal::Dictionary<ByteString,Jakt::types::LoadedModule> a_loaded_modules);
public:
static NonnullRefPtr<CheckedProgram> __jakt_create(NonnullRefPtr<Jakt::compiler::Compiler> compiler, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Module>> modules, JaktInternal::Dictionary<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> exports, JaktInternal::Dictionary<ByteString,Jakt::types::LoadedModule> loaded_modules);

public: ByteString debug_description() const;
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
JaktInternal::DynamicArray<Jakt::types::Value> fields;
Jakt::ids::StructId struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> constructor;
} Struct;
struct {
JaktInternal::DynamicArray<Jakt::types::Value> fields;
Jakt::ids::StructId struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> constructor;
} Class;
struct {
JaktInternal::DynamicArray<Jakt::types::Value> fields;
Jakt::ids::EnumId enum_id;
Jakt::ids::FunctionId constructor;
} Enum;
struct {
JaktInternal::DynamicArray<Jakt::types::Value> values;
Jakt::ids::TypeId type_id;
} JaktArray;
struct {
JaktInternal::DynamicArray<Jakt::types::Value> keys;
JaktInternal::DynamicArray<Jakt::types::Value> values;
Jakt::ids::TypeId type_id;
} JaktDictionary;
struct {
JaktInternal::DynamicArray<Jakt::types::Value> values;
Jakt::ids::TypeId type_id;
} JaktSet;
struct {
NonnullRefPtr<typename Jakt::types::ValueImpl> value;
} RawPtr;
struct {
Jakt::types::Value value;
} OptionalSome;
struct {
JaktInternal::DynamicArray<Jakt::types::Value> fields;
Jakt::ids::TypeId type_id;
} JaktTuple;
struct {
JaktInternal::Dictionary<ByteString,Jakt::types::Value> captures;
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>> params;
Jakt::ids::TypeId return_type_id;
Jakt::ids::TypeId type_id;
Jakt::types::CheckedBlock block;
bool can_throw;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> checked_params;
Jakt::ids::ScopeId scope_id;
JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id;
} Function;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NonnullRefPtr<ValueImpl> Void();
[[nodiscard]] static NonnullRefPtr<ValueImpl> Bool(bool value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> U8(u8 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> U16(u16 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> U32(u32 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> U64(u64 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> I8(i8 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> I16(i16 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> I32(i32 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> I64(i64 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> F32(f32 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> F64(f64 value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> USize(size_t value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> JaktString(ByteString value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> StringView(ByteString value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> CChar(char value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> CInt(int value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> Struct(JaktInternal::DynamicArray<Jakt::types::Value> fields, Jakt::ids::StructId struct_id, JaktInternal::Optional<Jakt::ids::FunctionId> constructor);
[[nodiscard]] static NonnullRefPtr<ValueImpl> Class(JaktInternal::DynamicArray<Jakt::types::Value> fields, Jakt::ids::StructId struct_id, JaktInternal::Optional<Jakt::ids::FunctionId> constructor);
[[nodiscard]] static NonnullRefPtr<ValueImpl> Enum(JaktInternal::DynamicArray<Jakt::types::Value> fields, Jakt::ids::EnumId enum_id, Jakt::ids::FunctionId constructor);
[[nodiscard]] static NonnullRefPtr<ValueImpl> JaktArray(JaktInternal::DynamicArray<Jakt::types::Value> values, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<ValueImpl> JaktDictionary(JaktInternal::DynamicArray<Jakt::types::Value> keys, JaktInternal::DynamicArray<Jakt::types::Value> values, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<ValueImpl> JaktSet(JaktInternal::DynamicArray<Jakt::types::Value> values, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<ValueImpl> RawPtr(NonnullRefPtr<typename Jakt::types::ValueImpl> value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> OptionalSome(Jakt::types::Value value);
[[nodiscard]] static NonnullRefPtr<ValueImpl> OptionalNone();
[[nodiscard]] static NonnullRefPtr<ValueImpl> JaktTuple(JaktInternal::DynamicArray<Jakt::types::Value> fields, Jakt::ids::TypeId type_id);
[[nodiscard]] static NonnullRefPtr<ValueImpl> Function(JaktInternal::Dictionary<ByteString,Jakt::types::Value> captures, JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>> params, Jakt::ids::TypeId return_type_id, Jakt::ids::TypeId type_id, Jakt::types::CheckedBlock block, bool can_throw, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> checked_params, Jakt::ids::ScopeId scope_id, JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id);
~ValueImpl();
ValueImpl& operator=(ValueImpl const &);
ValueImpl& operator=(ValueImpl &&);
ValueImpl(ValueImpl const&);
ValueImpl(ValueImpl &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<Jakt::ids::TypeId> type_id(NonnullRefPtr<Jakt::types::CheckedProgram>& program) const;
NonnullRefPtr<typename Jakt::types::ValueImpl> copy() const;
bool equals(NonnullRefPtr<typename Jakt::types::ValueImpl> const other) const;
private:
ValueImpl() {};
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
class TypecheckFunctions :public RefCounted<TypecheckFunctions>, public Weakable<TypecheckFunctions> {
  public:
virtual ~TypecheckFunctions() = default;
public: Function<ErrorOr<Jakt::types::CheckedBlock>(Jakt::parser::ParsedBlock, Jakt::ids::ScopeId, Jakt::types::SafetyMode, JaktInternal::Optional<Jakt::ids::TypeId>, JaktInternal::Optional<Jakt::ids::FunctionId>)> block;public: Function<ErrorOr<Jakt::ids::FunctionId>(NonnullRefPtr<Jakt::types::CheckedFunction>)> register_function;public: protected:
explicit TypecheckFunctions(Function<ErrorOr<Jakt::types::CheckedBlock>(Jakt::parser::ParsedBlock, Jakt::ids::ScopeId, Jakt::types::SafetyMode, JaktInternal::Optional<Jakt::ids::TypeId>, JaktInternal::Optional<Jakt::ids::FunctionId>)> a_block, Function<ErrorOr<Jakt::ids::FunctionId>(NonnullRefPtr<Jakt::types::CheckedFunction>)> a_register_function);
public:
static NonnullRefPtr<TypecheckFunctions> __jakt_create(Function<ErrorOr<Jakt::types::CheckedBlock>(Jakt::parser::ParsedBlock, Jakt::ids::ScopeId, Jakt::types::SafetyMode, JaktInternal::Optional<Jakt::ids::TypeId>, JaktInternal::Optional<Jakt::ids::FunctionId>)> block, Function<ErrorOr<Jakt::ids::FunctionId>(NonnullRefPtr<Jakt::types::CheckedFunction>)> register_function);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StructOrEnumId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StructOrEnumId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StructLikeId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StructLikeId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::GenericInferences> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::GenericInferences const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::SafetyMode> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::SafetyMode const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::BuiltinType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::BuiltinType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Value> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Value const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Type> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Type const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::SpecializedType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::SpecializedType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ResolutionMixin> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ResolutionMixin const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Scope> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Scope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ResolvedForallChunk> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ResolvedForallChunk const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::TypeWithSkipList> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::TypeWithSkipList const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::Module> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::Module const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTraitRequirements> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTraitRequirements const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTrait> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTrait const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::LoadedModule> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::LoadedModule const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::MaybeResolvedScope> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::MaybeResolvedScope const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVisibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVisibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::BlockControlFlow> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::BlockControlFlow const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedBlock> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedBlock const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedFunction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedFunction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenerics> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenerics const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedCapture> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedCapture const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenericParameterKind> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenericParameterKind const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FunctionGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FunctionGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVariable> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVariable const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedVarDecl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedVarDecl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::FieldRecord> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::FieldRecord const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedField> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedField const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStruct> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStruct const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnum> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnum const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedEnumVariantBinding> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedEnumVariantBinding const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStatement> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStatement const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::NumberConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::NumberConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedNumericConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedNumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::StringLiteral> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::StringLiteral const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedStringLiteral> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedStringLiteral const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedTypeCast> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedTypeCast const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedUnaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedUnaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedMatchBody> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedMatchBody const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ClassInstanceRebind> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ClassInstanceRebind const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedMatchCase> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedMatchCase const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedMatchPattern> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedMatchPattern const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedCall> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedCall const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::OperatorTraitImplementation> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::OperatorTraitImplementation const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedBinaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedBinaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedExpression> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedExpression const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ResolvedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ResolvedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::CheckedProgram> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::CheckedProgram const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::ValueImpl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::ValueImpl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::NumericOrStringValue> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::NumericOrStringValue const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::types::TypecheckFunctions> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::types::TypecheckFunctions const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
