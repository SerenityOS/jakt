#pragma once
#include <lib.h>
#include "typechecker.h"
#include "types.h"
#include "ids.h"
#include "parser.h"
#include "compiler.h"
#include "utility.h"
#include "jakt__arguments.h"
namespace Jakt {
namespace ide {
struct JaktSymbol;
struct Mutability;

struct VarType;

struct VarVisibility;

struct Usage;

ErrorOr<JaktInternal::DynamicArray<Jakt::ide::JaktSymbol>> find_symbols_in_namespace(Jakt::parser::ParsedNamespace const namespace_);

Jakt::ide::JaktSymbol record_to_symbol(Jakt::parser::ParsedRecord const record);

Jakt::ide::JaktSymbol function_to_symbol(Jakt::parser::ParsedFunction const function, ByteString const kind);

ErrorOr<Jakt::utility::Span> find_definition_in_program(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::utility::Span const span);

ErrorOr<Jakt::utility::Span> find_type_definition_for_type_id(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::ids::TypeId const type_id, Jakt::utility::Span const span);

ErrorOr<Jakt::utility::Span> find_type_definition_in_program(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<ByteString>> find_typename_in_program(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::utility::Span const span);

ErrorOr<JaktInternal::DynamicArray<ByteString>> completions_for_type_id(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::ids::TypeId const type_id);

ErrorOr<JaktInternal::DynamicArray<ByteString>> find_function_completions_in_scope(NonnullRefPtr<Jakt::types::Scope> const scope, NonnullRefPtr<Jakt::types::CheckedProgram> const program);

ErrorOr<JaktInternal::DynamicArray<ByteString>> find_dot_completions(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_program(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_scope(NonnullRefPtr<Jakt::types::CheckedProgram> const program, NonnullRefPtr<Jakt::types::Scope> const scope, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_enum(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::types::CheckedEnum const checked_enum, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_struct(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::types::CheckedStruct const checked_struct, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_function(NonnullRefPtr<Jakt::types::CheckedProgram> const program, NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_block(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::types::CheckedBlock const block, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_statement(NonnullRefPtr<Jakt::types::CheckedProgram> const program, NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement, Jakt::utility::Span const span);

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_expression(NonnullRefPtr<Jakt::types::CheckedProgram> const program, NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr, Jakt::utility::Span const span);

ErrorOr<ByteString> get_function_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::ids::FunctionId const function_id);

ErrorOr<ByteString> get_var_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program, ByteString const name, Jakt::ids::TypeId const var_type_id, Jakt::ide::Mutability const mutability, Jakt::ide::VarType const var_type, Jakt::ide::VarVisibility const visibility, JaktInternal::Optional<Jakt::ids::TypeId> const struct_type_id);

ErrorOr<ByteString> get_type_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::ids::TypeId const type_id);

ErrorOr<ByteString> get_enum_variant_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program, ByteString const name, Jakt::ids::TypeId const type_id, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const variants, JaktInternal::Optional<Jakt::types::NumberConstant> const number_constant);

ErrorOr<ByteString> get_enum_variant_signature_from_type_id_and_name(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::ids::TypeId const type_id, ByteString const name);

Jakt::ide::Usage get_enum_variant_usage_from_type_id_and_name(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::ids::TypeId const type_id, ByteString const name);

JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> enum_variant_fields(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::types::CheckedEnumVariant const checked_enum_variant);

ErrorOr<ByteString> get_constructor_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program, Jakt::ids::FunctionId const function_id);

}
namespace ide {
struct Mutability {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static Mutability DoesNotApply();
[[nodiscard]] static Mutability Immutable();
[[nodiscard]] static Mutability Mutable();
~Mutability();
Mutability& operator=(Mutability const &);
Mutability& operator=(Mutability &&);
Mutability(Mutability const&);
Mutability(Mutability &&);
private: void __jakt_destroy_variant();
public:
private:
Mutability() {};
};
struct VarType {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static VarType Variable();
[[nodiscard]] static VarType Field();
~VarType();
VarType& operator=(VarType const &);
VarType& operator=(VarType &&);
VarType(VarType const&);
VarType(VarType &&);
private: void __jakt_destroy_variant();
public:
private:
VarType() {};
};
struct VarVisibility {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static VarVisibility DoesNotApply();
[[nodiscard]] static VarVisibility Public();
[[nodiscard]] static VarVisibility Private();
[[nodiscard]] static VarVisibility Restricted();
~VarVisibility();
VarVisibility& operator=(VarVisibility const &);
VarVisibility& operator=(VarVisibility &&);
VarVisibility(VarVisibility const&);
VarVisibility(VarVisibility &&);
private: void __jakt_destroy_variant();
public:
private:
VarVisibility() {};
};
struct Usage {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
Jakt::utility::Span span;
ByteString name;
Jakt::ids::TypeId type_id;
Jakt::ide::Mutability mutability;
Jakt::ide::VarType var_type;
Jakt::ide::VarVisibility visibility;
JaktInternal::Optional<Jakt::ids::TypeId> struct_type_id;
} Variable;
struct {
Jakt::ids::FunctionId value;
} Call;
struct {
Jakt::ids::TypeId value;
} Typename;
struct {
JaktInternal::DynamicArray<ByteString> value;
} NameSet;
struct {
Jakt::utility::Span span;
ByteString name;
Jakt::ids::TypeId type_id;
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> variants;
JaktInternal::Optional<Jakt::types::NumberConstant> number_constant;
} EnumVariant;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ByteString debug_description() const;
[[nodiscard]] static Usage Variable(Jakt::utility::Span span, ByteString name, Jakt::ids::TypeId type_id, Jakt::ide::Mutability mutability, Jakt::ide::VarType var_type, Jakt::ide::VarVisibility visibility, JaktInternal::Optional<Jakt::ids::TypeId> struct_type_id);
[[nodiscard]] static Usage Call(Jakt::ids::FunctionId value);
[[nodiscard]] static Usage Typename(Jakt::ids::TypeId value);
[[nodiscard]] static Usage NameSet(JaktInternal::DynamicArray<ByteString> value);
[[nodiscard]] static Usage EnumVariant(Jakt::utility::Span span, ByteString name, Jakt::ids::TypeId type_id, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> variants, JaktInternal::Optional<Jakt::types::NumberConstant> number_constant);
~Usage();
Usage& operator=(Usage const &);
Usage& operator=(Usage &&);
Usage(Usage const&);
Usage(Usage &&);
private: void __jakt_destroy_variant();
public:
private:
Usage() {};
};
struct JaktSymbol {
  public:
public: ByteString name;public: JaktInternal::Optional<ByteString> detail;public: ByteString kind;public: Jakt::utility::Span range;public: Jakt::utility::Span selection_range;public: JaktInternal::DynamicArray<Jakt::ide::JaktSymbol> children;public: ByteString to_json() const;
public: JaktSymbol(ByteString a_name, JaktInternal::Optional<ByteString> a_detail, ByteString a_kind, Jakt::utility::Span a_range, Jakt::utility::Span a_selection_range, JaktInternal::DynamicArray<Jakt::ide::JaktSymbol> a_children);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::Mutability> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::Mutability const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::VarType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::VarType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::VarVisibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::VarVisibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::Usage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::Usage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::JaktSymbol> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::JaktSymbol const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
