#include "ids.h"
namespace Jakt {
namespace ids {
ErrorOr<DeprecatedString> ids::FunctionId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("FunctionId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::FunctionId::FunctionId(ids::ModuleId a_module, size_t a_id) :module(move(a_module)), id(move(a_id)){}

bool ids::FunctionId::equals(ids::FunctionId const rhs) const {
{
return (((((((*this).module)).id)) == (((((rhs).module)).id))) && ((((*this).id)) == (((rhs).id))));
}
}

ErrorOr<DeprecatedString> ids::StructId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("StructId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
u32 ids::StructId::hash() const {
{
return pair_int_hash([](size_t const& self) -> u32 {
{
return ((AK::Traits<size_t>()).hash(self));
}
}
(((*this).id)),((((*this).module)).hash()));
}
}

ids::StructId::StructId(ids::ModuleId a_module, size_t a_id) :module(move(a_module)), id(move(a_id)){}

bool ids::StructId::equals(ids::StructId const rhs) const {
{
return (((((((*this).module)).id)) == (((((rhs).module)).id))) && ((((*this).id)) == (((rhs).id))));
}
}


ErrorOr<DeprecatedString> ids::VarId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("VarId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::VarId::VarId(ids::ModuleId a_module, size_t a_id) :module(move(a_module)), id(move(a_id)){}

ErrorOr<DeprecatedString> ids::ScopeId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("ScopeId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module_id: {}, ", module_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
u32 ids::ScopeId::hash() const {
{
return pair_int_hash([](size_t const& self) -> u32 {
{
return ((AK::Traits<size_t>()).hash(self));
}
}
(((*this).id)),((((*this).module_id)).hash()));
}
}

bool ids::ScopeId::equals(ids::ScopeId const other) const {
{
return (((((((*this).module_id)).id)) == (((((other).module_id)).id))) && ((((*this).id)) == (((other).id))));
}
}


ids::ScopeId::ScopeId(ids::ModuleId a_module_id, size_t a_id) :module_id(move(a_module_id)), id(move(a_id)){}

ErrorOr<DeprecatedString> ids::TypeId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("TypeId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
u32 ids::TypeId::hash() const {
{
return pair_int_hash([](size_t const& self) -> u32 {
{
return ((AK::Traits<size_t>()).hash(self));
}
}
(((*this).id)),((((*this).module)).hash()));
}
}

JaktInternal::Optional<ids::TypeId> ids::TypeId::none() {
{
return JaktInternal::OptionalNone();
}
}

ids::TypeId::TypeId(ids::ModuleId a_module, size_t a_id) :module(move(a_module)), id(move(a_id)){}

bool ids::TypeId::equals(ids::TypeId const rhs) const {
{
return (((((((*this).module)).id)) == (((((rhs).module)).id))) && ((((*this).id)) == (((rhs).id))));
}
}


ErrorOr<DeprecatedString> ids::ModuleId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("ModuleId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
u32 ids::ModuleId::hash() const {
{
return [](size_t const& self) -> u32 {
{
return ((AK::Traits<size_t>()).hash(self));
}
}
(((*this).id));
}
}

bool ids::ModuleId::equals(ids::ModuleId const rhs) const {
{
return ((((*this).id)) == (((rhs).id)));
}
}

ids::ModuleId::ModuleId(size_t a_id) :id(move(a_id)){}


ErrorOr<DeprecatedString> ids::EnumId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("EnumId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
bool ids::EnumId::equals(ids::EnumId const rhs) const {
{
return (((((((*this).module)).id)) == (((((rhs).module)).id))) && ((((*this).id)) == (((rhs).id))));
}
}

ids::EnumId::EnumId(ids::ModuleId a_module, size_t a_id) :module(move(a_module)), id(move(a_id)){}

ErrorOr<DeprecatedString> ids::TraitId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("TraitId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
bool ids::TraitId::equals(ids::TraitId const other) const {
{
return (((((((*this).module)).id)) == (((((other).module)).id))) && ((((*this).id)) == (((other).id))));
}
}

ids::TraitId::TraitId(ids::ModuleId a_module, size_t a_id) :module(move(a_module)), id(move(a_id)){}

}
} // namespace Jakt
