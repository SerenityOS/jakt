#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "cpp_import__none.h"
namespace Jakt {
namespace cpp_import__none {
ByteString Jakt::cpp_import__none::CppImportProcessor::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CppImportProcessor("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
builder.append(")"sv);return builder.to_string(); }
Jakt::cpp_import__none::CppImportProcessor Jakt::cpp_import__none::CppImportProcessor::create() {
{
return Jakt::cpp_import__none::CppImportProcessor();
}
}

ErrorOr<Jakt::ids::ScopeId> Jakt::cpp_import__none::CppImportProcessor::process_cpp_import(NonnullRefPtr<Jakt::types::CheckedProgram>& program,Jakt::jakt__path::Path const import_path,Jakt::ids::ScopeId const scope_id,bool const is_c,JaktInternal::Dictionary<ByteString,ByteString> const defines) {
{
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not implemented"sv)));
}
}

Jakt::cpp_import__none::CppImportProcessor::CppImportProcessor(){}

}
} // namespace Jakt
