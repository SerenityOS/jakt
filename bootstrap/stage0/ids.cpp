#include "ids.h"
namespace Jakt {
namespace ids {
ErrorOr<DeprecatedString> ids::FunctionId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("FunctionId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::FunctionId::FunctionId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ErrorOr<DeprecatedString> ids::StructId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("StructId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::StructId::StructId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}


ErrorOr<DeprecatedString> ids::VarId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("VarId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::VarId::VarId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ErrorOr<DeprecatedString> ids::ScopeId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("ScopeId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module_id: {}, ", module_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }

ids::ScopeId::ScopeId(ids::ModuleId a_module_id, size_t a_id): module_id(move(a_module_id)), id(move(a_id)){}

ErrorOr<DeprecatedString> ids::TypeId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("TypeId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::TypeId::TypeId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}


ErrorOr<DeprecatedString> ids::ModuleId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("ModuleId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::ModuleId::ModuleId(size_t a_id): id(move(a_id)){}


ErrorOr<DeprecatedString> ids::EnumId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("EnumId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::EnumId::EnumId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ErrorOr<DeprecatedString> ids::TraitId::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("TraitId("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module: {}, ", module));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}", id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::TraitId::TraitId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

}
} // namespace Jakt
