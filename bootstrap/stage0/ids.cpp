#include "ids.h"
namespace Jakt {
namespace ids {
ErrorOr<ByteString> ids::ModuleId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ModuleId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
ids::ModuleId::ModuleId(size_t a_id): id(move(a_id)){}


ErrorOr<ByteString> ids::VarId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("VarId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
ids::VarId::VarId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ErrorOr<ByteString> ids::FunctionId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FunctionId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
ids::FunctionId::FunctionId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ErrorOr<ByteString> ids::StructId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("StructId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
ids::StructId::StructId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}


ErrorOr<ByteString> ids::EnumId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("EnumId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
ids::EnumId::EnumId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ErrorOr<ByteString> ids::TypeId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("TypeId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
ids::TypeId::TypeId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}


ErrorOr<ByteString> ids::TraitId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("TraitId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
ids::TraitId::TraitId(ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ErrorOr<ByteString> ids::ScopeId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ScopeId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module_id: {}, ", module_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
ids::ScopeId::ScopeId(ids::ModuleId a_module_id, size_t a_id): module_id(move(a_module_id)), id(move(a_id)){}


}
} // namespace Jakt
