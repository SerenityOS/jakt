#pragma once
#include <lib.h>
#include "lexer.h"
#include "compiler.h"
#include "error.h"
#include "utility.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace parser {
struct ParsedFunctionParameters;
struct ParsedExport;
struct ParsedModuleImport;
struct ParsedExternImport;
struct ParsedAlias;
struct ParsedNamespace;
struct ValueEnumVariant;
struct SumEnumVariant;
struct ParsedRecord;
struct ParsedFunction;
struct ParsedParameter;
struct ParsedName;
struct ParsedNameWithGenericParameters;
struct ParsedGenericParameter;
struct ParsedTrait;
struct ParsedExternalTraitImplementation;
struct ParsedBlock;
struct EnumVariantPatternArgument;
struct ParsedPatternDefault;
struct ParsedMatchCase;
struct ParsedVarDecl;
struct ParsedVarDeclTuple;
struct ParsedField;
struct ParsedMethod;
struct ParsedVariable;
struct ParsedCall;
struct ParsedTypeQualifiers;
struct CheckedQualifiers;
struct VisibilityRestriction;
struct ParsedAttributeArgument;
struct ParsedAttribute;
struct Parser;
struct ExternalName;

struct NumericConstant;

struct DefinitionLinkage;

struct ImportName;

struct ImportList;

struct IncludeAction;

struct RecordType;

struct FunctionType;

struct ArgumentStoreLevel;

struct InlineState;

struct ParsedTraitRequirements;

struct ParsedStatement;

struct BinaryOperator;

struct TypeCast;

struct UnaryOperator;

struct ParsedMatchPattern;

struct ParsedMatchBody;

struct ParsedCapture;

struct ParsedExpression;

struct ParsedType;

struct FunctionLinkage;

struct Visibility;

f32 f64_to_f32(f64 const number);

Jakt::utility::Span merge_spans(Jakt::utility::Span const start, Jakt::utility::Span const end);

}
namespace parser {
struct ParsedFunctionParameters {
  public:
public: JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> parameters;public: bool has_varargs;public: ParsedFunctionParameters(JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> a_parameters, bool a_has_varargs);

public: ByteString debug_description() const;
};struct ExternalName {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString value;
} Plain;
struct {
ByteString value;
} PreprocessorName;
struct {
ByteString name;
bool is_prefix;
} Operator;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ExternalName Plain(ByteString value);
[[nodiscard]] static ExternalName PreprocessorName(ByteString value);
[[nodiscard]] static ExternalName Operator(ByteString name, bool is_prefix);
~ExternalName();
ExternalName& operator=(ExternalName const &);
ExternalName& operator=(ExternalName &&);
ExternalName(ExternalName const&);
ExternalName(ExternalName &&);
private: void __jakt_destroy_variant();
public:
ByteString as_name_for_definition() const;
ByteString as_name_for_use() const;
bool is_prefix() const;
bool is_scopable() const;
private:
ExternalName() {};
};
struct NumericConstant {
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
struct {
i64 value;
} UnknownSigned;
struct {
u64 value;
} UnknownUnsigned;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NumericConstant I8(i8 value);
[[nodiscard]] static NumericConstant I16(i16 value);
[[nodiscard]] static NumericConstant I32(i32 value);
[[nodiscard]] static NumericConstant I64(i64 value);
[[nodiscard]] static NumericConstant U8(u8 value);
[[nodiscard]] static NumericConstant U16(u16 value);
[[nodiscard]] static NumericConstant U32(u32 value);
[[nodiscard]] static NumericConstant U64(u64 value);
[[nodiscard]] static NumericConstant USize(u64 value);
[[nodiscard]] static NumericConstant F32(f32 value);
[[nodiscard]] static NumericConstant F64(f64 value);
[[nodiscard]] static NumericConstant UnknownSigned(i64 value);
[[nodiscard]] static NumericConstant UnknownUnsigned(u64 value);
~NumericConstant();
NumericConstant& operator=(NumericConstant const &);
NumericConstant& operator=(NumericConstant &&);
NumericConstant(NumericConstant const&);
NumericConstant(NumericConstant &&);
private: void __jakt_destroy_variant();
public:
size_t to_usize() const;
private:
NumericConstant() {};
};
struct DefinitionLinkage {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static DefinitionLinkage Internal();
[[nodiscard]] static DefinitionLinkage External();
~DefinitionLinkage();
DefinitionLinkage& operator=(DefinitionLinkage const &);
DefinitionLinkage& operator=(DefinitionLinkage &&);
DefinitionLinkage(DefinitionLinkage const&);
DefinitionLinkage(DefinitionLinkage &&);
private: void __jakt_destroy_variant();
public:
private:
DefinitionLinkage() {};
};
struct ImportName {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString name;
Jakt::utility::Span span;
} Literal;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expression;
} Comptime;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ImportName Literal(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static ImportName Comptime(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expression);
~ImportName();
ImportName& operator=(ImportName const &);
ImportName& operator=(ImportName &&);
ImportName(ImportName const&);
ImportName(ImportName &&);
private: void __jakt_destroy_variant();
public:
bool equals(Jakt::parser::ImportName const other) const;
ByteString literal_name() const;
Jakt::utility::Span span() const;
private:
ImportName() {};
};
struct ParsedName {
  public:
public: ByteString name;public: Jakt::utility::Span span;public: ParsedName(ByteString a_name, Jakt::utility::Span a_span);

public: ByteString debug_description() const;
};struct ParsedExport {
  public:
public: Jakt::parser::ParsedName file;public: JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::parser::ParsedName>> names;public: ParsedExport(Jakt::parser::ParsedName a_file, JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::parser::ParsedName>> a_names);

public: ByteString debug_description() const;
};struct ImportList {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<Jakt::parser::ImportName> value;
} List;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ImportList List(JaktInternal::DynamicArray<Jakt::parser::ImportName> value);
[[nodiscard]] static ImportList All();
~ImportList();
ImportList& operator=(ImportList const &);
ImportList& operator=(ImportList &&);
ImportList(ImportList const&);
ImportList(ImportList &&);
private: void __jakt_destroy_variant();
public:
bool is_empty() const;
void add(Jakt::parser::ImportName const name);
private:
ImportList() {};
};
struct ParsedModuleImport {
  public:
public: Jakt::parser::ImportName module_name;public: JaktInternal::Optional<Jakt::parser::ImportName> alias_name;public: Jakt::parser::ImportList import_list;public: bool relative_path;public: size_t parent_path_count;public: bool is_equivalent_to(Jakt::parser::ParsedModuleImport const other) const;
public: bool has_same_import_semantics(Jakt::parser::ParsedModuleImport const other) const;
public: bool has_same_alias_than(Jakt::parser::ParsedModuleImport const other) const;
public: void merge_import_list(Jakt::parser::ImportList const list);
public: ParsedModuleImport(Jakt::parser::ImportName a_module_name, JaktInternal::Optional<Jakt::parser::ImportName> a_alias_name, Jakt::parser::ImportList a_import_list, bool a_relative_path, size_t a_parent_path_count);

public: ByteString debug_description() const;
};struct IncludeAction {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString name;
Jakt::utility::Span span;
ByteString value;
} Define;
struct {
ByteString name;
Jakt::utility::Span span;
} Undefine;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static IncludeAction Define(ByteString name, Jakt::utility::Span span, ByteString value);
[[nodiscard]] static IncludeAction Undefine(ByteString name, Jakt::utility::Span span);
~IncludeAction();
IncludeAction& operator=(IncludeAction const &);
IncludeAction& operator=(IncludeAction &&);
IncludeAction(IncludeAction const&);
IncludeAction(IncludeAction &&);
private: void __jakt_destroy_variant();
public:
private:
IncludeAction() {};
};
struct ParsedNamespace {
  public:
public: JaktInternal::Optional<ByteString> name;public: JaktInternal::Optional<Jakt::utility::Span> name_span;public: JaktInternal::DynamicArray<Jakt::parser::ParsedFunction> functions;public: JaktInternal::DynamicArray<Jakt::parser::ParsedRecord> records;public: JaktInternal::DynamicArray<Jakt::parser::ParsedTrait> traits;public: JaktInternal::DynamicArray<Jakt::parser::ParsedExternalTraitImplementation> external_trait_implementations;public: JaktInternal::DynamicArray<Jakt::parser::ParsedNamespace> namespaces;public: JaktInternal::DynamicArray<Jakt::parser::ParsedAlias> aliases;public: JaktInternal::DynamicArray<Jakt::parser::ParsedModuleImport> module_imports;public: JaktInternal::DynamicArray<Jakt::parser::ParsedExternImport> extern_imports;public: JaktInternal::DynamicArray<Jakt::parser::ParsedExport> exports;public: JaktInternal::Optional<ByteString> import_path_if_extern;public: JaktInternal::DynamicArray<Jakt::parser::IncludeAction> generating_import_extern_before_include;public: JaktInternal::DynamicArray<Jakt::parser::IncludeAction> generating_import_extern_after_include;public: JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter>,Jakt::parser::ParsedNamespace>> forall_chunks;public: bool is_generated_code;public: bool is_auto_extern_imported;public: Jakt::utility::Span keyword_span;public: bool is_equivalent_to(Jakt::parser::ParsedNamespace const other) const;
public: void add_module_import(Jakt::parser::ParsedModuleImport const import_);
public: void add_extern_import(Jakt::parser::ParsedExternImport const import_);
public: void add_child_namespace(Jakt::parser::ParsedNamespace const namespace_);
public: void add_alias(Jakt::parser::ParsedAlias const alias);
public: void merge_with(Jakt::parser::ParsedNamespace const namespace_);
public: ParsedNamespace(JaktInternal::Optional<ByteString> a_name, JaktInternal::Optional<Jakt::utility::Span> a_name_span, JaktInternal::DynamicArray<Jakt::parser::ParsedFunction> a_functions, JaktInternal::DynamicArray<Jakt::parser::ParsedRecord> a_records, JaktInternal::DynamicArray<Jakt::parser::ParsedTrait> a_traits, JaktInternal::DynamicArray<Jakt::parser::ParsedExternalTraitImplementation> a_external_trait_implementations, JaktInternal::DynamicArray<Jakt::parser::ParsedNamespace> a_namespaces, JaktInternal::DynamicArray<Jakt::parser::ParsedAlias> a_aliases, JaktInternal::DynamicArray<Jakt::parser::ParsedModuleImport> a_module_imports, JaktInternal::DynamicArray<Jakt::parser::ParsedExternImport> a_extern_imports, JaktInternal::DynamicArray<Jakt::parser::ParsedExport> a_exports, JaktInternal::Optional<ByteString> a_import_path_if_extern, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> a_generating_import_extern_before_include, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> a_generating_import_extern_after_include, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter>,Jakt::parser::ParsedNamespace>> a_forall_chunks, bool a_is_generated_code, bool a_is_auto_extern_imported, Jakt::utility::Span a_keyword_span);

public: ByteString debug_description() const;
};struct ParsedExternImport {
  public:
public: bool is_c;public: Jakt::parser::ParsedNamespace assigned_namespace;public: JaktInternal::DynamicArray<Jakt::parser::IncludeAction> before_include;public: JaktInternal::DynamicArray<Jakt::parser::IncludeAction> after_include;public: bool should_auto_import;public: ByteString get_path() const;
public: ByteString get_name() const;
public: bool is_equivalent_to(Jakt::parser::ParsedExternImport const other) const;
public: ParsedExternImport(bool a_is_c, Jakt::parser::ParsedNamespace a_assigned_namespace, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> a_before_include, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> a_after_include, bool a_should_auto_import);

public: ByteString debug_description() const;
};struct ParsedAlias {
  public:
public: JaktInternal::Optional<Jakt::parser::ParsedName> alias_name;public: JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> target;public: ParsedAlias(JaktInternal::Optional<Jakt::parser::ParsedName> a_alias_name, JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> a_target);

public: ByteString debug_description() const;
};struct ValueEnumVariant {
  public:
public: ByteString name;public: Jakt::utility::Span span;public: JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> value;public: ValueEnumVariant(ByteString a_name, Jakt::utility::Span a_span, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> a_value);

public: ByteString debug_description() const;
};struct SumEnumVariant {
  public:
public: ByteString name;public: Jakt::utility::Span span;public: JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl>> params;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>>>> default_values;public: SumEnumVariant(ByteString a_name, Jakt::utility::Span a_span, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl>> a_params, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>>>> a_default_values);

public: ByteString debug_description() const;
};struct RecordType {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<Jakt::parser::ParsedField> fields;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> super_type;
} Struct;
struct {
JaktInternal::DynamicArray<Jakt::parser::ParsedField> fields;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> super_type;
} Class;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> underlying_type;
JaktInternal::DynamicArray<Jakt::parser::ValueEnumVariant> variants;
} ValueEnum;
struct {
bool is_boxed;
JaktInternal::DynamicArray<Jakt::parser::ParsedField> fields;
JaktInternal::DynamicArray<Jakt::parser::SumEnumVariant> variants;
} SumEnum;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static RecordType Struct(JaktInternal::DynamicArray<Jakt::parser::ParsedField> fields, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> super_type);
[[nodiscard]] static RecordType Class(JaktInternal::DynamicArray<Jakt::parser::ParsedField> fields, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> super_type);
[[nodiscard]] static RecordType ValueEnum(NonnullRefPtr<typename Jakt::parser::ParsedType> underlying_type, JaktInternal::DynamicArray<Jakt::parser::ValueEnumVariant> variants);
[[nodiscard]] static RecordType SumEnum(bool is_boxed, JaktInternal::DynamicArray<Jakt::parser::ParsedField> fields, JaktInternal::DynamicArray<Jakt::parser::SumEnumVariant> variants);
[[nodiscard]] static RecordType Garbage();
~RecordType();
RecordType& operator=(RecordType const &);
RecordType& operator=(RecordType &&);
RecordType(RecordType const&);
RecordType(RecordType &&);
private: void __jakt_destroy_variant();
public:
ByteString record_type_name() const;
private:
RecordType() {};
};
struct ParsedRecord {
  public:
public: ByteString name;public: Jakt::utility::Span name_span;public: JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> generic_parameters;public: Jakt::parser::DefinitionLinkage definition_linkage;public: JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters>> implements_list;public: JaktInternal::DynamicArray<Jakt::parser::ParsedMethod> methods;public: Jakt::parser::RecordType record_type;public: JaktInternal::DynamicArray<Jakt::parser::ParsedRecord> nested_records;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: JaktInternal::Optional<ByteString> create_function_name;public: ParsedRecord(ByteString a_name, Jakt::utility::Span a_name_span, JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> a_generic_parameters, Jakt::parser::DefinitionLinkage a_definition_linkage, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters>> a_implements_list, JaktInternal::DynamicArray<Jakt::parser::ParsedMethod> a_methods, Jakt::parser::RecordType a_record_type, JaktInternal::DynamicArray<Jakt::parser::ParsedRecord> a_nested_records, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Optional<ByteString> a_create_function_name);

public: ByteString debug_description() const;
};struct FunctionType {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static FunctionType Normal();
[[nodiscard]] static FunctionType Constructor();
[[nodiscard]] static FunctionType Destructor();
[[nodiscard]] static FunctionType ImplicitConstructor();
[[nodiscard]] static FunctionType ImplicitEnumConstructor();
[[nodiscard]] static FunctionType ExternalClassConstructor();
[[nodiscard]] static FunctionType Expression();
[[nodiscard]] static FunctionType Closure();
~FunctionType();
FunctionType& operator=(FunctionType const &);
FunctionType& operator=(FunctionType &&);
FunctionType(FunctionType const&);
FunctionType(FunctionType &&);
private: void __jakt_destroy_variant();
public:
private:
FunctionType() {};
};
struct ArgumentStoreLevel {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
size_t argument_index;
} InObject;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ArgumentStoreLevel InObject(size_t argument_index);
[[nodiscard]] static ArgumentStoreLevel InReturnValue();
[[nodiscard]] static ArgumentStoreLevel InStaticStorage();
~ArgumentStoreLevel();
ArgumentStoreLevel& operator=(ArgumentStoreLevel const &);
ArgumentStoreLevel& operator=(ArgumentStoreLevel &&);
ArgumentStoreLevel(ArgumentStoreLevel const&);
ArgumentStoreLevel(ArgumentStoreLevel &&);
private: void __jakt_destroy_variant();
public:
private:
ArgumentStoreLevel() {};
};
struct InlineState {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static InlineState Default();
[[nodiscard]] static InlineState MakeDefinitionAvailable();
[[nodiscard]] static InlineState ForceInline();
~InlineState();
InlineState& operator=(InlineState const &);
InlineState& operator=(InlineState &&);
InlineState(InlineState const&);
InlineState(InlineState &&);
private: void __jakt_destroy_variant();
public:
private:
InlineState() {};
};
struct Visibility {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<Jakt::parser::VisibilityRestriction> whitelist;
Jakt::utility::Span span;
} Restricted;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static Visibility Public();
[[nodiscard]] static Visibility Private();
[[nodiscard]] static Visibility Restricted(JaktInternal::DynamicArray<Jakt::parser::VisibilityRestriction> whitelist, Jakt::utility::Span span);
~Visibility();
Visibility& operator=(Visibility const &);
Visibility& operator=(Visibility &&);
Visibility(Visibility const&);
Visibility(Visibility &&);
private: void __jakt_destroy_variant();
public:
private:
Visibility() {};
};
struct ParsedBlock {
  public:
public: JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> stmts;public: bool equals(Jakt::parser::ParsedBlock const rhs_block) const;
public: JaktInternal::Optional<Jakt::utility::Span> find_yield_span() const;
public: JaktInternal::Optional<Jakt::utility::Span> find_yield_keyword_span() const;
public: JaktInternal::Optional<Jakt::utility::Span> span(Jakt::parser::Parser const parser) const;
public: ParsedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> a_stmts);

public: ByteString debug_description() const;
};struct FunctionLinkage {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static FunctionLinkage Internal();
[[nodiscard]] static FunctionLinkage External();
~FunctionLinkage();
FunctionLinkage& operator=(FunctionLinkage const &);
FunctionLinkage& operator=(FunctionLinkage &&);
FunctionLinkage(FunctionLinkage const&);
FunctionLinkage(FunctionLinkage &&);
private: void __jakt_destroy_variant();
public:
private:
FunctionLinkage() {};
};
struct ParsedFunction {
  public:
public: size_t id;public: ByteString name;public: Jakt::utility::Span name_span;public: Jakt::parser::Visibility visibility;public: JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> params;public: JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> generic_parameters;public: Jakt::parser::ParsedBlock block;public: NonnullRefPtr<typename Jakt::parser::ParsedType> return_type;public: Jakt::utility::Span return_type_span;public: bool can_throw;public: Jakt::parser::FunctionType type;public: Jakt::parser::FunctionLinkage linkage;public: bool must_instantiate;public: bool is_comptime;public: bool is_fat_arrow;public: bool is_unsafe;public: bool has_varargs;public: bool is_jakt_main;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: JaktInternal::Optional<ByteString> deprecated_message;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>>> stores_arguments;public: Jakt::parser::InlineState force_inline;public: bool is_raw_constructor;public: bool equals(Jakt::parser::ParsedFunction const other, bool const ignore_block) const;
public: ParsedFunction(size_t a_id, ByteString a_name, Jakt::utility::Span a_name_span, Jakt::parser::Visibility a_visibility, JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> a_params, JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> a_generic_parameters, Jakt::parser::ParsedBlock a_block, NonnullRefPtr<typename Jakt::parser::ParsedType> a_return_type, Jakt::utility::Span a_return_type_span, bool a_can_throw, Jakt::parser::FunctionType a_type, Jakt::parser::FunctionLinkage a_linkage, bool a_must_instantiate, bool a_is_comptime, bool a_is_fat_arrow, bool a_is_unsafe, bool a_has_varargs, bool a_is_jakt_main, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Optional<ByteString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>>> a_stores_arguments, Jakt::parser::InlineState a_force_inline, bool a_is_raw_constructor);

public: ByteString debug_description() const;
};struct ParsedVariable {
  public:
public: ByteString name;public: NonnullRefPtr<typename Jakt::parser::ParsedType> parsed_type;public: bool is_mutable;public: Jakt::utility::Span span;public: bool equals(Jakt::parser::ParsedVariable const rhs_parsed_varible) const;
public: ParsedVariable(ByteString a_name, NonnullRefPtr<typename Jakt::parser::ParsedType> a_parsed_type, bool a_is_mutable, Jakt::utility::Span a_span);

public: ByteString debug_description() const;
};struct ParsedParameter {
  public:
public: bool requires_label;public: Jakt::parser::ParsedVariable variable;public: JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> default_argument;public: Jakt::utility::Span span;public: bool equals(Jakt::parser::ParsedParameter const rhs_param) const;
public: ParsedParameter(bool a_requires_label, Jakt::parser::ParsedVariable a_variable, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> a_default_argument, Jakt::utility::Span a_span);

public: ByteString debug_description() const;
};struct ParsedNameWithGenericParameters {
  public:
public: ByteString name;public: Jakt::utility::Span name_span;public: JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> generic_parameters;public: ParsedNameWithGenericParameters(ByteString a_name, Jakt::utility::Span a_name_span, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> a_generic_parameters);

public: ByteString debug_description() const;
};struct ParsedGenericParameter {
  public:
public: ByteString name;public: Jakt::utility::Span span;public: JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters>> requires_list;public: bool is_value;public: ParsedGenericParameter(ByteString a_name, Jakt::utility::Span a_span, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters>> a_requires_list, bool a_is_value);

public: ByteString debug_description() const;
};struct ParsedTraitRequirements {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<Jakt::parser::ParsedFunction> value;
} Methods;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> value;
} ComptimeExpression;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ParsedTraitRequirements Nothing();
[[nodiscard]] static ParsedTraitRequirements Methods(JaktInternal::DynamicArray<Jakt::parser::ParsedFunction> value);
[[nodiscard]] static ParsedTraitRequirements ComptimeExpression(NonnullRefPtr<typename Jakt::parser::ParsedExpression> value);
~ParsedTraitRequirements();
ParsedTraitRequirements& operator=(ParsedTraitRequirements const &);
ParsedTraitRequirements& operator=(ParsedTraitRequirements &&);
ParsedTraitRequirements(ParsedTraitRequirements const&);
ParsedTraitRequirements(ParsedTraitRequirements &&);
private: void __jakt_destroy_variant();
public:
private:
ParsedTraitRequirements() {};
};
struct ParsedTrait {
  public:
public: ByteString name;public: Jakt::utility::Span name_span;public: JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> generic_parameters;public: Jakt::parser::ParsedTraitRequirements requirements;public: ParsedTrait(ByteString a_name, Jakt::utility::Span a_name_span, JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> a_generic_parameters, Jakt::parser::ParsedTraitRequirements a_requirements);

public: ByteString debug_description() const;
};struct ParsedExternalTraitImplementation {
  public:
public: NonnullRefPtr<typename Jakt::parser::ParsedType> for_type;public: JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> traits;public: JaktInternal::DynamicArray<Jakt::parser::ParsedMethod> methods;public: ParsedExternalTraitImplementation(NonnullRefPtr<typename Jakt::parser::ParsedType> a_for_type, JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> a_traits, JaktInternal::DynamicArray<Jakt::parser::ParsedMethod> a_methods);

public: ByteString debug_description() const;
};struct ParsedVarDecl {
  public:
public: ByteString name;public: NonnullRefPtr<typename Jakt::parser::ParsedType> parsed_type;public: bool is_mutable;public: JaktInternal::Optional<Jakt::utility::Span> inlay_span;public: Jakt::utility::Span span;public: JaktInternal::Optional<Jakt::parser::ExternalName> external_name;public: bool equals(Jakt::parser::ParsedVarDecl const rhs_var_decl) const;
public: ParsedVarDecl(ByteString a_name, NonnullRefPtr<typename Jakt::parser::ParsedType> a_parsed_type, bool a_is_mutable, JaktInternal::Optional<Jakt::utility::Span> a_inlay_span, Jakt::utility::Span a_span, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name);

public: ByteString debug_description() const;
};struct ParsedStatement: public RefCounted<ParsedStatement> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::utility::Span span;
} Expression;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedStatement> statement;
Jakt::utility::Span span;
} Defer;
struct {
Jakt::parser::ParsedBlock block;
Jakt::utility::Span span;
} UnsafeBlock;
struct {
JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl> vars;
NonnullRefPtr<typename Jakt::parser::ParsedStatement> var_decl;
Jakt::utility::Span span;
} DestructuringAssignment;
struct {
Jakt::parser::ParsedVarDecl var;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> init;
Jakt::utility::Span span;
} VarDecl;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> condition;
Jakt::parser::ParsedBlock then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> else_statement;
Jakt::utility::Span span;
} If;
struct {
Jakt::parser::ParsedBlock block;
Jakt::utility::Span span;
} Block;
struct {
Jakt::parser::ParsedBlock block;
Jakt::utility::Span span;
} Loop;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> condition;
Jakt::parser::ParsedBlock block;
Jakt::utility::Span span;
} While;
struct {
ByteString iterator_name;
Jakt::utility::Span name_span;
bool is_destructuring;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> range;
Jakt::parser::ParsedBlock block;
Jakt::utility::Span span;
} For;
struct {
Jakt::utility::Span value;
} Break;
struct {
Jakt::utility::Span value;
} Continue;
struct {
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> expr;
Jakt::utility::Span span;
} Return;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::utility::Span span;
} Throw;
struct {
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> expr;
Jakt::utility::Span span;
} Yield;
struct {
Jakt::parser::ParsedBlock block;
Jakt::utility::Span span;
} InlineCpp;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::parser::ParsedBlock else_block;
Jakt::parser::ParsedBlock remaining_code;
Jakt::utility::Span span;
} Guard;
struct {
Jakt::utility::Span value;
} Garbage;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Expression(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Defer(NonnullRefPtr<typename Jakt::parser::ParsedStatement> statement, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> UnsafeBlock(Jakt::parser::ParsedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> DestructuringAssignment(JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl> vars, NonnullRefPtr<typename Jakt::parser::ParsedStatement> var_decl, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> VarDecl(Jakt::parser::ParsedVarDecl var, NonnullRefPtr<typename Jakt::parser::ParsedExpression> init, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> If(NonnullRefPtr<typename Jakt::parser::ParsedExpression> condition, Jakt::parser::ParsedBlock then_block, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> else_statement, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Block(Jakt::parser::ParsedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Loop(Jakt::parser::ParsedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> While(NonnullRefPtr<typename Jakt::parser::ParsedExpression> condition, Jakt::parser::ParsedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> For(ByteString iterator_name, Jakt::utility::Span name_span, bool is_destructuring, NonnullRefPtr<typename Jakt::parser::ParsedExpression> range, Jakt::parser::ParsedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Break(Jakt::utility::Span value);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Continue(Jakt::utility::Span value);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Return(JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Throw(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Yield(JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> InlineCpp(Jakt::parser::ParsedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Guard(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::parser::ParsedBlock else_block, Jakt::parser::ParsedBlock remaining_code, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedStatement> Garbage(Jakt::utility::Span value);
~ParsedStatement();
ParsedStatement& operator=(ParsedStatement const &);
ParsedStatement& operator=(ParsedStatement &&);
ParsedStatement(ParsedStatement const&);
ParsedStatement(ParsedStatement &&);
private: void __jakt_destroy_variant();
public:
bool equals(NonnullRefPtr<typename Jakt::parser::ParsedStatement> const rhs_statement) const;
Jakt::utility::Span span() const;
private:
ParsedStatement() {};
};
struct BinaryOperator {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static BinaryOperator Add();
[[nodiscard]] static BinaryOperator Subtract();
[[nodiscard]] static BinaryOperator Multiply();
[[nodiscard]] static BinaryOperator Divide();
[[nodiscard]] static BinaryOperator Modulo();
[[nodiscard]] static BinaryOperator LessThan();
[[nodiscard]] static BinaryOperator LessThanOrEqual();
[[nodiscard]] static BinaryOperator GreaterThan();
[[nodiscard]] static BinaryOperator GreaterThanOrEqual();
[[nodiscard]] static BinaryOperator Equal();
[[nodiscard]] static BinaryOperator NotEqual();
[[nodiscard]] static BinaryOperator BitwiseAnd();
[[nodiscard]] static BinaryOperator BitwiseXor();
[[nodiscard]] static BinaryOperator BitwiseOr();
[[nodiscard]] static BinaryOperator BitwiseLeftShift();
[[nodiscard]] static BinaryOperator BitwiseRightShift();
[[nodiscard]] static BinaryOperator ArithmeticLeftShift();
[[nodiscard]] static BinaryOperator ArithmeticRightShift();
[[nodiscard]] static BinaryOperator LogicalAnd();
[[nodiscard]] static BinaryOperator LogicalOr();
[[nodiscard]] static BinaryOperator NoneCoalescing();
[[nodiscard]] static BinaryOperator Assign();
[[nodiscard]] static BinaryOperator BitwiseAndAssign();
[[nodiscard]] static BinaryOperator BitwiseOrAssign();
[[nodiscard]] static BinaryOperator BitwiseXorAssign();
[[nodiscard]] static BinaryOperator BitwiseLeftShiftAssign();
[[nodiscard]] static BinaryOperator BitwiseRightShiftAssign();
[[nodiscard]] static BinaryOperator AddAssign();
[[nodiscard]] static BinaryOperator SubtractAssign();
[[nodiscard]] static BinaryOperator MultiplyAssign();
[[nodiscard]] static BinaryOperator ModuloAssign();
[[nodiscard]] static BinaryOperator DivideAssign();
[[nodiscard]] static BinaryOperator NoneCoalescingAssign();
[[nodiscard]] static BinaryOperator Garbage();
~BinaryOperator();
BinaryOperator& operator=(BinaryOperator const &);
BinaryOperator& operator=(BinaryOperator &&);
BinaryOperator(BinaryOperator const&);
BinaryOperator(BinaryOperator &&);
private: void __jakt_destroy_variant();
public:
bool equals(Jakt::parser::BinaryOperator const rhs_op) const;
bool is_assignment() const;
private:
BinaryOperator() {};
};
struct TypeCast {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> value;
} Fallible;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> value;
} Infallible;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static TypeCast Fallible(NonnullRefPtr<typename Jakt::parser::ParsedType> value);
[[nodiscard]] static TypeCast Infallible(NonnullRefPtr<typename Jakt::parser::ParsedType> value);
~TypeCast();
TypeCast& operator=(TypeCast const &);
TypeCast& operator=(TypeCast &&);
TypeCast(TypeCast const&);
TypeCast(TypeCast &&);
private: void __jakt_destroy_variant();
public:
NonnullRefPtr<typename Jakt::parser::ParsedType> parsed_type() const;
private:
TypeCast() {};
};
struct UnaryOperator {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::parser::TypeCast value;
} TypeCast;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> value;
} Is;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> inner;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> bindings;
} IsEnumVariant;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> value;
} Sizeof;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static UnaryOperator PreIncrement();
[[nodiscard]] static UnaryOperator PostIncrement();
[[nodiscard]] static UnaryOperator PreDecrement();
[[nodiscard]] static UnaryOperator PostDecrement();
[[nodiscard]] static UnaryOperator Negate();
[[nodiscard]] static UnaryOperator Dereference();
[[nodiscard]] static UnaryOperator RawAddress();
[[nodiscard]] static UnaryOperator Reference();
[[nodiscard]] static UnaryOperator MutableReference();
[[nodiscard]] static UnaryOperator LogicalNot();
[[nodiscard]] static UnaryOperator BitwiseNot();
[[nodiscard]] static UnaryOperator TypeCast(Jakt::parser::TypeCast value);
[[nodiscard]] static UnaryOperator Is(NonnullRefPtr<typename Jakt::parser::ParsedType> value);
[[nodiscard]] static UnaryOperator IsEnumVariant(NonnullRefPtr<typename Jakt::parser::ParsedType> inner, JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> bindings);
[[nodiscard]] static UnaryOperator Sizeof(NonnullRefPtr<typename Jakt::parser::ParsedType> value);
~UnaryOperator();
UnaryOperator& operator=(UnaryOperator const &);
UnaryOperator& operator=(UnaryOperator &&);
UnaryOperator(UnaryOperator const&);
UnaryOperator(UnaryOperator &&);
private: void __jakt_destroy_variant();
public:
bool equals(Jakt::parser::UnaryOperator const rhs_op) const;
private:
UnaryOperator() {};
};
struct EnumVariantPatternArgument {
  public:
public: JaktInternal::Optional<ByteString> name;public: JaktInternal::Optional<Jakt::utility::Span> name_span;public: ByteString binding;public: Jakt::utility::Span span;public: bool is_reference;public: bool is_mutable;public: ByteString name_in_enum() const;
public: Jakt::utility::Span name_in_enum_span() const;
public: bool equals(Jakt::parser::EnumVariantPatternArgument const rhs_variant_pattern_argument) const;
public: EnumVariantPatternArgument(JaktInternal::Optional<ByteString> a_name, JaktInternal::Optional<Jakt::utility::Span> a_name_span, ByteString a_binding, Jakt::utility::Span a_span, bool a_is_reference, bool a_is_mutable);

public: ByteString debug_description() const;
};struct ParsedPatternDefault {
  public:
public: Jakt::parser::ParsedVarDecl variable;public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> value;public: ParsedPatternDefault(Jakt::parser::ParsedVarDecl a_variable, NonnullRefPtr<typename Jakt::parser::ParsedExpression> a_value);

public: ByteString debug_description() const;
};struct ParsedMatchPattern {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Dictionary<ByteString,Jakt::parser::ParsedPatternDefault> defaults;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> variant_names;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> variant_arguments;
Jakt::utility::Span arguments_span;
} EnumVariant;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> value;
} Expression;
struct {
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> variant_arguments;
Jakt::utility::Span arguments_span;
} CatchAll;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ParsedMatchPattern EnumVariant(JaktInternal::Dictionary<ByteString,Jakt::parser::ParsedPatternDefault> defaults, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> variant_names, JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> variant_arguments, Jakt::utility::Span arguments_span);
[[nodiscard]] static ParsedMatchPattern Expression(JaktInternal::Dictionary<ByteString,Jakt::parser::ParsedPatternDefault> defaults, NonnullRefPtr<typename Jakt::parser::ParsedExpression> value);
[[nodiscard]] static ParsedMatchPattern CatchAll(JaktInternal::Dictionary<ByteString,Jakt::parser::ParsedPatternDefault> defaults, JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> variant_arguments, Jakt::utility::Span arguments_span);
[[nodiscard]] static ParsedMatchPattern Invalid(JaktInternal::Dictionary<ByteString,Jakt::parser::ParsedPatternDefault> defaults);
~ParsedMatchPattern();
ParsedMatchPattern& operator=(ParsedMatchPattern const &);
ParsedMatchPattern& operator=(ParsedMatchPattern &&);
ParsedMatchPattern(ParsedMatchPattern const&);
ParsedMatchPattern(ParsedMatchPattern &&);
private: void __jakt_destroy_variant();
public:
bool defaults_equal(JaktInternal::Dictionary<ByteString,Jakt::parser::ParsedPatternDefault> const defaults) const;
bool is_equal_pattern(Jakt::parser::ParsedMatchPattern const rhs_parsed_match_pattern) const;
bool equals(Jakt::parser::ParsedMatchPattern const rhs_parsed_match_pattern) const;
private:
ParsedMatchPattern() {};
};
struct ParsedMatchBody {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> value;
} Expression;
struct {
Jakt::parser::ParsedBlock value;
} Block;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static ParsedMatchBody Expression(NonnullRefPtr<typename Jakt::parser::ParsedExpression> value);
[[nodiscard]] static ParsedMatchBody Block(Jakt::parser::ParsedBlock value);
~ParsedMatchBody();
ParsedMatchBody& operator=(ParsedMatchBody const &);
ParsedMatchBody& operator=(ParsedMatchBody &&);
ParsedMatchBody(ParsedMatchBody const&);
ParsedMatchBody(ParsedMatchBody &&);
private: void __jakt_destroy_variant();
public:
bool equals(Jakt::parser::ParsedMatchBody const rhs_match_body) const;
private:
ParsedMatchBody() {};
};
struct ParsedMatchCase {
  public:
public: JaktInternal::DynamicArray<Jakt::parser::ParsedMatchPattern> patterns;public: Jakt::utility::Span marker_span;public: Jakt::parser::ParsedMatchBody body;public: bool has_equal_pattern(Jakt::parser::ParsedMatchCase const rhs_match_case) const;
public: bool equals(Jakt::parser::ParsedMatchCase const rhs_match_case) const;
public: ParsedMatchCase(JaktInternal::DynamicArray<Jakt::parser::ParsedMatchPattern> a_patterns, Jakt::utility::Span a_marker_span, Jakt::parser::ParsedMatchBody a_body);

public: ByteString debug_description() const;
};struct ParsedCapture {
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
[[nodiscard]] static ParsedCapture ByValue(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static ParsedCapture ByReference(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static ParsedCapture ByMutableReference(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static ParsedCapture ByComptimeDependency(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static ParsedCapture AllByReference(ByteString name, Jakt::utility::Span span);
~ParsedCapture();
ParsedCapture& operator=(ParsedCapture const &);
ParsedCapture& operator=(ParsedCapture &&);
ParsedCapture(ParsedCapture const&);
ParsedCapture(ParsedCapture &&);
private: void __jakt_destroy_variant();
public:
private:
ParsedCapture() {};
};
struct ParsedCall {
  public:
public: JaktInternal::DynamicArray<ByteString> namespace_;public: ByteString name;public: JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> args;public: JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> type_args;public: bool equals(Jakt::parser::ParsedCall const rhs_parsed_call) const;
public: ParsedCall(JaktInternal::DynamicArray<ByteString> a_namespace_, ByteString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> a_args, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> a_type_args);

public: ByteString debug_description() const;
};struct ParsedExpression: public RefCounted<ParsedExpression> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
bool val;
Jakt::utility::Span span;
} Boolean;
struct {
Jakt::parser::NumericConstant val;
Jakt::utility::Span span;
} NumericConstant;
struct {
ByteString val;
Jakt::utility::Span span;
} QuotedString;
struct {
ByteString val;
JaktInternal::Optional<ByteString> prefix;
Jakt::utility::Span span;
} SingleQuotedString;
struct {
Jakt::parser::ParsedCall call;
Jakt::utility::Span span;
} Call;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::parser::ParsedCall call;
bool is_optional;
Jakt::utility::Span span;
} MethodCall;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
size_t index;
bool is_optional;
Jakt::utility::Span span;
} IndexedTuple;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
ByteString field_name;
bool is_optional;
Jakt::utility::Span span;
} IndexedStruct;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> index;
bool is_optional;
Jakt::utility::Span span;
} ComptimeIndex;
struct {
ByteString name;
Jakt::utility::Span span;
} Var;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> base;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> index;
Jakt::utility::Span span;
} IndexedExpression;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::parser::UnaryOperator op;
Jakt::utility::Span span;
} UnaryOp;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> lhs;
Jakt::parser::BinaryOperator op;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> rhs;
Jakt::utility::Span span;
} BinaryOp;
struct {
Jakt::parser::BinaryOperator op;
Jakt::utility::Span span;
} Operator;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::utility::Span span;
} OptionalSome;
struct {
Jakt::utility::Span value;
} OptionalNone;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> values;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> fill_size;
Jakt::utility::Span span;
} JaktArray;
struct {
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> values;
Jakt::utility::Span span;
} JaktDictionary;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> values;
Jakt::utility::Span span;
} Set;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> values;
Jakt::utility::Span span;
} JaktTuple;
struct {
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> to;
Jakt::utility::Span span;
} Range;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::utility::Span span;
} ForcedUnwrap;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
JaktInternal::DynamicArray<Jakt::parser::ParsedMatchCase> cases;
Jakt::utility::Span span;
Jakt::utility::Span marker_span;
} Match;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::parser::EnumVariantPatternArgument arg;
NonnullRefPtr<typename Jakt::parser::ParsedType> enum_variant;
Jakt::utility::Span span;
} EnumVariantArg;
struct {
ByteString name;
JaktInternal::DynamicArray<ByteString> namespace_;
Jakt::utility::Span span;
} NamespacedVar;
struct {
JaktInternal::DynamicArray<Jakt::parser::ParsedCapture> captures;
JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> params;
bool can_throw;
bool is_fat_arrow;
NonnullRefPtr<typename Jakt::parser::ParsedType> return_type;
Jakt::parser::ParsedBlock block;
Jakt::utility::Span span;
} Function;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::utility::Span span;
} Must;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
JaktInternal::Optional<Jakt::parser::ParsedBlock> catch_block;
JaktInternal::Optional<Jakt::utility::Span> catch_span;
JaktInternal::Optional<ByteString> catch_name;
Jakt::utility::Span span;
} Try;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedStatement> stmt;
ByteString error_name;
Jakt::utility::Span error_span;
Jakt::parser::ParsedBlock catch_block;
Jakt::utility::Span span;
} TryBlock;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> type;
Jakt::utility::Span span;
} Reflect;
struct {
Jakt::utility::Span value;
} Garbage;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::utility::Span span;
} Unsafe;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Boolean(bool val, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> NumericConstant(Jakt::parser::NumericConstant val, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> QuotedString(ByteString val, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> SingleQuotedString(ByteString val, JaktInternal::Optional<ByteString> prefix, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Call(Jakt::parser::ParsedCall call, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> MethodCall(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::parser::ParsedCall call, bool is_optional, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> IndexedTuple(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, size_t index, bool is_optional, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> IndexedStruct(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, ByteString field_name, bool is_optional, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> ComptimeIndex(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, NonnullRefPtr<typename Jakt::parser::ParsedExpression> index, bool is_optional, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Var(ByteString name, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> IndexedExpression(NonnullRefPtr<typename Jakt::parser::ParsedExpression> base, NonnullRefPtr<typename Jakt::parser::ParsedExpression> index, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> UnaryOp(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::parser::UnaryOperator op, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> BinaryOp(NonnullRefPtr<typename Jakt::parser::ParsedExpression> lhs, Jakt::parser::BinaryOperator op, NonnullRefPtr<typename Jakt::parser::ParsedExpression> rhs, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Operator(Jakt::parser::BinaryOperator op, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> OptionalSome(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> OptionalNone(Jakt::utility::Span value);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> JaktArray(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> values, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> fill_size, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> JaktDictionary(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> values, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Set(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> values, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> JaktTuple(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> values, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Range(JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> from, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> to, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> ForcedUnwrap(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Match(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, JaktInternal::DynamicArray<Jakt::parser::ParsedMatchCase> cases, Jakt::utility::Span span, Jakt::utility::Span marker_span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> EnumVariantArg(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::parser::EnumVariantPatternArgument arg, NonnullRefPtr<typename Jakt::parser::ParsedType> enum_variant, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> NamespacedVar(ByteString name, JaktInternal::DynamicArray<ByteString> namespace_, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Function(JaktInternal::DynamicArray<Jakt::parser::ParsedCapture> captures, JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> params, bool can_throw, bool is_fat_arrow, NonnullRefPtr<typename Jakt::parser::ParsedType> return_type, Jakt::parser::ParsedBlock block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Must(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Try(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, JaktInternal::Optional<Jakt::parser::ParsedBlock> catch_block, JaktInternal::Optional<Jakt::utility::Span> catch_span, JaktInternal::Optional<ByteString> catch_name, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> TryBlock(NonnullRefPtr<typename Jakt::parser::ParsedStatement> stmt, ByteString error_name, Jakt::utility::Span error_span, Jakt::parser::ParsedBlock catch_block, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Reflect(NonnullRefPtr<typename Jakt::parser::ParsedType> type, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Garbage(Jakt::utility::Span value);
[[nodiscard]] static NonnullRefPtr<ParsedExpression> Unsafe(NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::utility::Span span);
~ParsedExpression();
ParsedExpression& operator=(ParsedExpression const &);
ParsedExpression& operator=(ParsedExpression &&);
ParsedExpression(ParsedExpression const&);
ParsedExpression(ParsedExpression &&);
private: void __jakt_destroy_variant();
public:
Jakt::utility::Span span() const;
i64 precedence() const;
bool equals(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const rhs_expression) const;
private:
ParsedExpression() {};
};
struct ParsedVarDeclTuple {
  public:
public: JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl> var_decls;public: Jakt::utility::Span span;public: ParsedVarDeclTuple(JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl> a_var_decls, Jakt::utility::Span a_span);

public: ByteString debug_description() const;
};struct ParsedField {
  public:
public: Jakt::parser::ParsedVarDecl var_decl;public: Jakt::parser::Visibility visibility;public: JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> default_value;public: ParsedField(Jakt::parser::ParsedVarDecl a_var_decl, Jakt::parser::Visibility a_visibility, JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> a_default_value);

public: ByteString debug_description() const;
};struct ParsedMethod {
  public:
public: Jakt::parser::ParsedFunction parsed_function;public: Jakt::parser::Visibility visibility;public: bool is_virtual;public: bool is_override;public: ParsedMethod(Jakt::parser::ParsedFunction a_parsed_function, Jakt::parser::Visibility a_visibility, bool a_is_virtual, bool a_is_override);

public: ByteString debug_description() const;
};struct ParsedTypeQualifiers {
  public:
public: bool is_mutable;public: bool is_immutable;public: ParsedTypeQualifiers(bool a_is_mutable, bool a_is_immutable);

public: ByteString debug_description() const;
};struct CheckedQualifiers {
  public:
public: bool is_immutable;public: bool equals(Jakt::parser::CheckedQualifiers const other) const;
public: CheckedQualifiers(bool a_is_immutable);

public: public: ByteString debug_description() const;
};struct ParsedType: public RefCounted<ParsedType> {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
ByteString name;
Jakt::utility::Span span;
} Name;
struct {
ByteString name;
JaktInternal::DynamicArray<ByteString> namespaces;
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> params;
Jakt::utility::Span span;
} NamespacedName;
struct {
ByteString name;
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> generic_parameters;
Jakt::utility::Span span;
} GenericType;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> inner;
Jakt::utility::Span span;
} JaktArray;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> key;
NonnullRefPtr<typename Jakt::parser::ParsedType> value;
Jakt::utility::Span span;
} Dictionary;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> types;
Jakt::utility::Span span;
} JaktTuple;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> inner;
Jakt::utility::Span span;
} Set;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> inner;
Jakt::utility::Span span;
} Optional;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> inner;
Jakt::utility::Span span;
} Reference;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> inner;
Jakt::utility::Span span;
} MutableReference;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> inner;
Jakt::utility::Span span;
} RawPtr;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> inner;
Jakt::utility::Span span;
} WeakPtr;
struct {
JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> params;
bool can_throw;
NonnullRefPtr<typename Jakt::parser::ParsedType> return_type;
Jakt::utility::Span span;
} Function;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr;
Jakt::utility::Span span;
} Const;
struct {
NonnullRefPtr<typename Jakt::parser::ParsedType> base;
ByteString name;
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> generic_args;
Jakt::utility::Span span;
} DependentType;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static NonnullRefPtr<ParsedType> Name(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, ByteString name, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> NamespacedName(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, ByteString name, JaktInternal::DynamicArray<ByteString> namespaces, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> params, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> GenericType(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, ByteString name, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> generic_parameters, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> JaktArray(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> inner, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> Dictionary(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> key, NonnullRefPtr<typename Jakt::parser::ParsedType> value, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> JaktTuple(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> types, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> Set(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> inner, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> Optional(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> inner, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> Reference(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> inner, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> MutableReference(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> inner, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> RawPtr(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> inner, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> WeakPtr(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> inner, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> Function(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> params, bool can_throw, NonnullRefPtr<typename Jakt::parser::ParsedType> return_type, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> Const(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedExpression> expr, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> DependentType(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename Jakt::parser::ParsedType> base, ByteString name, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> generic_args, Jakt::utility::Span span);
[[nodiscard]] static NonnullRefPtr<ParsedType> Empty(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> qualifiers);
~ParsedType();
ParsedType& operator=(ParsedType const &);
ParsedType& operator=(ParsedType &&);
ParsedType(ParsedType const&);
ParsedType(ParsedType &&);
private: void __jakt_destroy_variant();
public:
Jakt::utility::Span span() const;
bool equals(NonnullRefPtr<typename Jakt::parser::ParsedType> const rhs_parsed_type) const;
private:
ParsedType() {};
};
struct VisibilityRestriction {
  public:
public: JaktInternal::DynamicArray<ByteString> namespace_;public: ByteString name;public: VisibilityRestriction(JaktInternal::DynamicArray<ByteString> a_namespace_, ByteString a_name);

public: ByteString debug_description() const;
};struct ParsedAttributeArgument {
  public:
public: ByteString name;public: Jakt::utility::Span span;public: JaktInternal::Optional<ByteString> assigned_value;public: ParsedAttributeArgument(ByteString a_name, Jakt::utility::Span a_span, JaktInternal::Optional<ByteString> a_assigned_value);

public: ByteString debug_description() const;
};struct ParsedAttribute {
  public:
public: ByteString name;public: Jakt::utility::Span span;public: JaktInternal::Optional<ByteString> assigned_value;public: JaktInternal::DynamicArray<Jakt::parser::ParsedAttributeArgument> arguments;public: ParsedAttribute(ByteString a_name, Jakt::utility::Span a_span, JaktInternal::Optional<ByteString> a_assigned_value, JaktInternal::DynamicArray<Jakt::parser::ParsedAttributeArgument> a_arguments);

public: ByteString debug_description() const;
};struct Parser {
  public:
public: size_t index;public: JaktInternal::DynamicArray<Jakt::lexer::Token> tokens;public: NonnullRefPtr<Jakt::compiler::Compiler> compiler;public: bool can_have_trailing_closure;public: size_t next_function_id;public: static Jakt::parser::ParsedNamespace parse(NonnullRefPtr<Jakt::compiler::Compiler> const compiler, JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens);
public: Jakt::utility::Span span(size_t const start, size_t const end) const;
public: Jakt::utility::Span empty_span() const;
public: void error(ByteString const message, Jakt::utility::Span const span);
public: void error_with_hint(ByteString const message, Jakt::utility::Span const span, ByteString const hint, Jakt::utility::Span const hint_span);
public: bool eof() const;
public: bool eol() const;
public: Jakt::lexer::Token peek(size_t const steps) const;
public: Jakt::lexer::Token previous() const;
public: Jakt::lexer::Token current() const;
public: void inject_token(Jakt::lexer::Token const token);
public: JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter>,Jakt::parser::ParsedNamespace> parse_forall();
public: Jakt::parser::ParsedNamespace parse_namespace(bool const process_only_one_entity);
public: void apply_attributes(Jakt::parser::ParsedNamespace& namespace_, JaktInternal::DynamicArray<Jakt::parser::ParsedAttribute> const& active_attributes);
public: void apply_attributes(Jakt::parser::ParsedField& field, JaktInternal::DynamicArray<Jakt::parser::ParsedAttribute> const& active_attributes);
public: void apply_attributes(Jakt::parser::ParsedFunction& parsed_function, JaktInternal::DynamicArray<Jakt::parser::ParsedAttribute> const& active_attributes);
public: void apply_attributes(Jakt::parser::ParsedMethod& parsed_method, JaktInternal::DynamicArray<Jakt::parser::ParsedAttribute> const& active_attributes);
public: void apply_attributes(Jakt::parser::ParsedRecord& parsed_record, JaktInternal::DynamicArray<Jakt::parser::ParsedAttribute> const& active_attributes);
public: void parse_attribute_list(JaktInternal::DynamicArray<Jakt::parser::ParsedAttribute>& active_attributes);
public: JaktInternal::Optional<Jakt::parser::ParsedAttribute> parse_attribute();
public: Jakt::parser::ParsedAlias parse_using();
public: Jakt::parser::ParsedExternalTraitImplementation parse_external_trait_implementation();
public: Jakt::parser::ParsedTrait parse_trait();
public: Jakt::parser::ParsedRecord parse_record(Jakt::parser::DefinitionLinkage const definition_linkage);
public: void escape_toplevel();
public: void parse_export(Jakt::parser::ParsedNamespace& parent);
public: void parse_import(Jakt::parser::ParsedNamespace& parent);
public: Jakt::parser::ParsedExternImport parse_extern_import(Jakt::parser::ParsedNamespace& parent);
public: JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::IncludeAction>> parse_include_action();
public: Jakt::parser::ParsedModuleImport parse_module_import();
public: JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ValueEnumVariant>,JaktInternal::DynamicArray<Jakt::parser::ParsedMethod>> parse_value_enum_body(Jakt::parser::ParsedRecord const partial_enum, Jakt::parser::DefinitionLinkage const definition_linkage);
public: JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::SumEnumVariant>,JaktInternal::DynamicArray<Jakt::parser::ParsedField>,JaktInternal::DynamicArray<Jakt::parser::ParsedMethod>,JaktInternal::DynamicArray<Jakt::parser::ParsedRecord>> parse_sum_enum_body(Jakt::parser::ParsedRecord const partial_enum, Jakt::parser::DefinitionLinkage const definition_linkage, bool const is_boxed);
public: Jakt::parser::ParsedRecord parse_enum(Jakt::parser::DefinitionLinkage const definition_linkage, bool const is_boxed);
public: JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ParsedField>,JaktInternal::DynamicArray<Jakt::parser::ParsedMethod>,JaktInternal::DynamicArray<Jakt::parser::ParsedRecord>> parse_struct_class_body(Jakt::parser::DefinitionLinkage const definition_linkage, Jakt::parser::Visibility const default_visibility, bool const is_class);
public: Jakt::parser::ParsedRecord parse_struct(Jakt::parser::DefinitionLinkage const definition_linkage);
public: Jakt::parser::ParsedRecord parse_class(Jakt::parser::DefinitionLinkage const definition_linkage);
public: Jakt::parser::ParsedFunctionParameters parse_function_parameters(bool const for_trailing_closure);
public: Jakt::parser::ParsedFunction parse_function(Jakt::parser::FunctionLinkage const linkage, Jakt::parser::Visibility const visibility, bool const is_comptime, bool const is_destructor, bool const is_unsafe, bool const allow_missing_body);
public: Jakt::parser::ParsedBlock parse_fat_arrow();
public: Jakt::parser::ParsedField parse_field(Jakt::parser::Visibility const visibility);
public: Jakt::parser::ParsedMethod parse_method(Jakt::parser::FunctionLinkage const linkage, Jakt::parser::Visibility const visibility, bool const is_virtual, bool const is_override, bool const is_comptime, bool const is_destructor, bool const is_unsafe);
public: JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> parse_type_parameter_list();
public: NonnullRefPtr<typename Jakt::parser::ParsedType> parse_typename();
public: NonnullRefPtr<typename Jakt::parser::ParsedType> parse_typename_base();
public: NonnullRefPtr<typename Jakt::parser::ParsedType> parse_type_longhand(Jakt::parser::ParsedTypeQualifiers const qualifiers);
public: Jakt::parser::ParsedVarDeclTuple parse_destructuring_assignment(bool const is_mutable);
public: Jakt::parser::ParsedVarDecl parse_variable_declaration(bool const is_mutable);
public: NonnullRefPtr<typename Jakt::parser::ParsedType> parse_type_shorthand(Jakt::parser::ParsedTypeQualifiers const qualifiers);
public: NonnullRefPtr<typename Jakt::parser::ParsedType> parse_type_shorthand_array_or_dictionary(Jakt::parser::ParsedTypeQualifiers const qualifiers);
public: NonnullRefPtr<typename Jakt::parser::ParsedType> parse_type_shorthand_set(Jakt::parser::ParsedTypeQualifiers const qualifiers);
public: NonnullRefPtr<typename Jakt::parser::ParsedType> parse_type_shorthand_tuple(Jakt::parser::ParsedTypeQualifiers const qualifiers);
public: Jakt::parser::ParsedBlock parse_block();
public: NonnullRefPtr<typename Jakt::parser::ParsedStatement> parse_statement(bool const inside_block);
public: NonnullRefPtr<typename Jakt::parser::ParsedStatement> parse_guard_statement();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_try_block();
public: NonnullRefPtr<typename Jakt::parser::ParsedStatement> parse_for_statement();
public: NonnullRefPtr<typename Jakt::parser::ParsedStatement> parse_if_statement();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_expression(bool const allow_assignments, bool const allow_newlines);
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_operand_base();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_number(Jakt::lexer::LiteralPrefix const prefix, ByteString const number, Jakt::lexer::LiteralSuffix suffix, Jakt::utility::Span const span);
public: JaktInternal::Optional<Jakt::parser::NumericConstant> make_integer_numeric_constant(u64 const number, Jakt::lexer::LiteralSuffix const suffix, Jakt::utility::Span const span);
public: JaktInternal::Optional<Jakt::parser::NumericConstant> make_float_numeric_constant(f64 const number, Jakt::lexer::LiteralSuffix const suffix, Jakt::utility::Span const span);
public: JaktInternal::DynamicArray<Jakt::parser::ParsedCapture> parse_captures();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_lambda();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_asterisk();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_ampersand();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_range();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_unsafe_expr();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_set_literal();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_operand();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_operand_postfix_operator(Jakt::utility::Span const start, NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr);
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_postfix_colon_colon(Jakt::utility::Span const start, NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr);
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_operator(bool const allow_assignments);
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_match_expression();
public: JaktInternal::DynamicArray<Jakt::parser::ParsedMatchCase> parse_match_cases();
public: JaktInternal::DynamicArray<Jakt::parser::ParsedMatchPattern> parse_match_patterns();
public: Jakt::parser::ParsedMatchPattern parse_match_pattern();
public: JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> parse_variant_arguments();
public: JaktInternal::Optional<Jakt::parser::ParsedCall> parse_call();
public: void skip_newlines();
public: JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters>> parse_trait_list();
public: JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> parse_generic_parameters();
public: ByteString parse_argument_label();
public: Jakt::parser::Visibility parse_restricted_visibility_modifier();
public: NonnullRefPtr<typename Jakt::parser::ParsedExpression> parse_array_or_dictionary_literal();
public: Parser(size_t a_index, JaktInternal::DynamicArray<Jakt::lexer::Token> a_tokens, NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, bool a_can_have_trailing_closure, size_t a_next_function_id);

public: ByteString debug_description() const;
};template <typename T>
T u64_to_float(u64 const number);
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedFunctionParameters> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedFunctionParameters const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ExternalName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ExternalName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::NumericConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::NumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::DefinitionLinkage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::DefinitionLinkage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ImportName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ImportName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExport> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ImportList> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ImportList const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedModuleImport> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedModuleImport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::IncludeAction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::IncludeAction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExternImport> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExternImport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAlias> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAlias const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ValueEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ValueEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::SumEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::SumEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::RecordType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::RecordType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedRecord> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedRecord const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::FunctionType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::FunctionType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ArgumentStoreLevel> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ArgumentStoreLevel const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::InlineState> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::InlineState const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::Visibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::Visibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedBlock> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedBlock const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::FunctionLinkage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::FunctionLinkage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedFunction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedFunction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVariable> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVariable const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedNameWithGenericParameters> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedNameWithGenericParameters const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTraitRequirements> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTraitRequirements const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTrait> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTrait const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExternalTraitImplementation> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExternalTraitImplementation const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVarDecl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVarDecl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedStatement> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedStatement const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::BinaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::BinaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::TypeCast> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::TypeCast const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::UnaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::UnaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::EnumVariantPatternArgument> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::EnumVariantPatternArgument const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedPatternDefault> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedPatternDefault const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchPattern> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchPattern const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchBody> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchBody const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchCase> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchCase const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedCapture> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedCapture const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedCall> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedCall const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExpression> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExpression const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVarDeclTuple> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVarDeclTuple const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedField> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedField const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMethod> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMethod const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTypeQualifiers> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTypeQualifiers const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::CheckedQualifiers> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::CheckedQualifiers const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::VisibilityRestriction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::VisibilityRestriction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAttributeArgument> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAttributeArgument const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAttribute> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAttribute const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::Parser> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::Parser const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
