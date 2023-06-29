#pragma once
#include "__unified_forward.h"
#include "jakt__prelude__hash.h"
namespace Jakt {
namespace ids {
struct ModuleId {
  public:
size_t id;__attribute__((always_inline)) inline u32 hash() const {
{
return [](size_t const& self) -> u32 {
{
return ((AK::Traits<size_t>()).hash(self));
}
}
(((*this).id));
}
}
__attribute__((always_inline)) inline bool equals(ids::ModuleId const rhs) const {
{
return ((((*this).id)) == (((rhs).id)));
}
}
ModuleId(size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct VarId {
  public:
ids::ModuleId module;size_t id;VarId(ids::ModuleId a_module, size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct TraitId {
  public:
ids::ModuleId module;size_t id;__attribute__((always_inline)) inline bool equals(ids::TraitId const other) const {
{
return (((((((*this).module)).id)) == (((((other).module)).id))) && ((((*this).id)) == (((other).id))));
}
}
TraitId(ids::ModuleId a_module, size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct ScopeId {
  public:
ids::ModuleId module_id;size_t id;__attribute__((always_inline)) inline u32 hash() const {
{
return pair_int_hash([](size_t const& self) -> u32 {
{
return ((AK::Traits<size_t>()).hash(self));
}
}
(((*this).id)),((((*this).module_id)).hash()));
}
}
__attribute__((always_inline)) inline bool equals(ids::ScopeId const other) const {
{
return (((((((*this).module_id)).id)) == (((((other).module_id)).id))) && ((((*this).id)) == (((other).id))));
}
}
ScopeId(ids::ModuleId a_module_id, size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct StructId {
  public:
ids::ModuleId module;size_t id;__attribute__((always_inline)) inline u32 hash() const {
{
return pair_int_hash([](size_t const& self) -> u32 {
{
return ((AK::Traits<size_t>()).hash(self));
}
}
(((*this).id)),((((*this).module)).hash()));
}
}
StructId(ids::ModuleId a_module, size_t a_id);

__attribute__((always_inline)) inline bool equals(ids::StructId const rhs) const {
{
return (((((((*this).module)).id)) == (((((rhs).module)).id))) && ((((*this).id)) == (((rhs).id))));
}
}
ErrorOr<DeprecatedString> debug_description() const;
};struct EnumId {
  public:
ids::ModuleId module;size_t id;__attribute__((always_inline)) inline bool equals(ids::EnumId const rhs) const {
{
return (((((((*this).module)).id)) == (((((rhs).module)).id))) && ((((*this).id)) == (((rhs).id))));
}
}
EnumId(ids::ModuleId a_module, size_t a_id);

ErrorOr<DeprecatedString> debug_description() const;
};struct FunctionId {
  public:
ids::ModuleId module;size_t id;FunctionId(ids::ModuleId a_module, size_t a_id);

__attribute__((always_inline)) inline bool equals(ids::FunctionId const rhs) const {
{
return (((((((*this).module)).id)) == (((((rhs).module)).id))) && ((((*this).id)) == (((rhs).id))));
}
}
ErrorOr<DeprecatedString> debug_description() const;
};struct TypeId {
  public:
ids::ModuleId module;size_t id;__attribute__((always_inline)) inline u32 hash() const {
{
return pair_int_hash([](size_t const& self) -> u32 {
{
return ((AK::Traits<size_t>()).hash(self));
}
}
(((*this).id)),((((*this).module)).hash()));
}
}
__attribute__((always_inline)) inline static JaktInternal::Optional<ids::TypeId> none() {
{
return JaktInternal::OptionalNone();
}
}
TypeId(ids::ModuleId a_module, size_t a_id);

__attribute__((always_inline)) inline bool equals(ids::TypeId const rhs) const {
{
return (((((((*this).module)).id)) == (((((rhs).module)).id))) && ((((*this).id)) == (((rhs).id))));
}
}
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
