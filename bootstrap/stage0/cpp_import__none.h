#pragma once
#include <lib.h>
#include "types.h"
#include "ids.h"
#include "compiler.h"
#include "jakt__path.h"
namespace Jakt {
namespace cpp_import__none {
struct CppImportProcessor;
}
namespace cpp_import__none {
struct CppImportProcessor {
  public:
public: static Jakt::cpp_import__none::CppImportProcessor create(bool const debug_print);
public: ErrorOr<Jakt::ids::ScopeId> process_cpp_import(NonnullRefPtr<Jakt::types::CheckedProgram>& program, Jakt::jakt__path::Path const import_path, Jakt::ids::ScopeId const scope_id, bool const is_c, JaktInternal::Dictionary<ByteString,ByteString> const defines);
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
