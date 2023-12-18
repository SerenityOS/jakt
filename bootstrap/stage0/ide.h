#pragma once
#include "__unified_forward.h"
#include "parser.h"
#include "typechecker.h"
#include "types.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace ide {
struct VarType {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
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
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
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
struct JaktSymbol {
  public:
public: ByteString name;public: JaktInternal::Optional<ByteString> detail;public: ByteString kind;public: utility::Span range;public: utility::Span selection_range;public: JaktInternal::DynamicArray<ide::JaktSymbol> children;public: JaktSymbol(ByteString a_name, JaktInternal::Optional<ByteString> a_detail, ByteString a_kind, utility::Span a_range, utility::Span a_selection_range, JaktInternal::DynamicArray<ide::JaktSymbol> a_children);

public: ErrorOr<ByteString> to_json() const;
public: ErrorOr<ByteString> debug_description() const;
};struct Mutability {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
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
struct Usage {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
utility::Span span;
ByteString name;
ids::TypeId type_id;
ide::Mutability mutability;
ide::VarType var_type;
ide::VarVisibility visibility;
JaktInternal::Optional<ids::TypeId> struct_type_id;
} Variable;
struct {
ids::FunctionId value;
} Call;
struct {
ids::TypeId value;
} Typename;
struct {
JaktInternal::DynamicArray<ByteString> value;
} NameSet;
struct {
utility::Span span;
ByteString name;
ids::TypeId type_id;
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> variants;
JaktInternal::Optional<types::NumberConstant> number_constant;
} EnumVariant;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<ByteString> debug_description() const;
[[nodiscard]] static Usage Variable(utility::Span span, ByteString name, ids::TypeId type_id, ide::Mutability mutability, ide::VarType var_type, ide::VarVisibility visibility, JaktInternal::Optional<ids::TypeId> struct_type_id);
[[nodiscard]] static Usage Call(ids::FunctionId value);
[[nodiscard]] static Usage Typename(ids::TypeId value);
[[nodiscard]] static Usage NameSet(JaktInternal::DynamicArray<ByteString> value);
[[nodiscard]] static Usage EnumVariant(utility::Span span, ByteString name, ids::TypeId type_id, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> variants, JaktInternal::Optional<types::NumberConstant> number_constant);
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
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::VarType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::VarType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::VarVisibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::VarVisibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::JaktSymbol> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::JaktSymbol const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::Mutability> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::Mutability const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ide::Usage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ide::Usage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
