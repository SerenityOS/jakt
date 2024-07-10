#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "ids.h"
namespace Jakt {
namespace ids {
ByteString Jakt::ids::ModuleId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ModuleId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::ModuleId::ModuleId(size_t a_id): id(move(a_id)){}


ByteString Jakt::ids::VarId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("VarId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::VarId::VarId(Jakt::ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ByteString Jakt::ids::FunctionId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FunctionId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::FunctionId::FunctionId(Jakt::ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ByteString Jakt::ids::StructId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("StructId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::StructId::StructId(Jakt::ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}


ByteString Jakt::ids::EnumId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("EnumId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::EnumId::EnumId(Jakt::ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ByteString Jakt::ids::TypeId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("TypeId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::TypeId::TypeId(Jakt::ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}


ByteString Jakt::ids::TraitId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("TraitId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module: {}, ", module);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::TraitId::TraitId(Jakt::ids::ModuleId a_module, size_t a_id): module(move(a_module)), id(move(a_id)){}

ByteString Jakt::ids::ScopeId::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ScopeId("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module_id: {}, ", module_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}", id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::ScopeId::ScopeId(Jakt::ids::ModuleId a_module_id, size_t a_id): module_id(move(a_module_id)), id(move(a_id)){}


}
} // namespace Jakt
