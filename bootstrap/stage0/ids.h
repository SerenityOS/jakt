#pragma once
#include "__unified_forward.h"
#include "jakt__prelude__hash.h"
namespace Jakt {
namespace ids {
struct ModuleId {
  public:
size_t id;u32 hash() const;
bool equals(ids::ModuleId const rhs) const;
ModuleId(size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct VarId {
  public:
ids::ModuleId module;size_t id;VarId(ids::ModuleId a_module, size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct TraitId {
  public:
ids::ModuleId module;size_t id;bool equals(ids::TraitId const other) const;
TraitId(ids::ModuleId a_module, size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct ScopeId {
  public:
ids::ModuleId module_id;size_t id;u32 hash() const;
bool equals(ids::ScopeId const other) const;
ScopeId(ids::ModuleId a_module_id, size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct StructId {
  public:
ids::ModuleId module;size_t id;u32 hash() const;
StructId(ids::ModuleId a_module, size_t a_id);

bool equals(ids::StructId const rhs) const;
ErrorOr<DeprecatedString> debug_description() const;
};struct EnumId {
  public:
ids::ModuleId module;size_t id;bool equals(ids::EnumId const rhs) const;
EnumId(ids::ModuleId a_module, size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct FunctionId {
  public:
ids::ModuleId module;size_t id;FunctionId(ids::ModuleId a_module, size_t a_id);

bool equals(ids::FunctionId const rhs) const;
ErrorOr<DeprecatedString> debug_description() const;
};struct TypeId {
  public:
ids::ModuleId module;size_t id;u32 hash() const;
static JaktInternal::Optional<ids::TypeId> none();
TypeId(ids::ModuleId a_module, size_t a_id);

bool equals(ids::TypeId const rhs) const;
ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ids::ModuleId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ids::ModuleId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ids::VarId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ids::VarId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ids::TraitId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ids::TraitId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ids::ScopeId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ids::ScopeId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ids::StructId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ids::StructId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ids::EnumId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ids::EnumId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ids::FunctionId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ids::FunctionId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::ids::TypeId> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::ids::TypeId const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
