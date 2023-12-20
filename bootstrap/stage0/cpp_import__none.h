#pragma once
#include "__unified_forward.h"
#include "types.h"
#include "jakt__path.h"
namespace Jakt {
namespace cpp_import__none {
struct CppImportProcessor {
  public:
public: static cpp_import__none::CppImportProcessor create();
public: ErrorOr<ids::ScopeId> process_cpp_import(NonnullRefPtr<types::CheckedProgram>& program, jakt__path::Path const import_path, ids::ScopeId const scope_id, bool const is_c, JaktInternal::Dictionary<ByteString,ByteString> const defines);
public: CppImportProcessor();

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::cpp_import__none::CppImportProcessor> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::cpp_import__none::CppImportProcessor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
