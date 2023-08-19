#pragma once
#include "__unified_forward.h"
#include "jakt__prelude__configuration.h"
namespace Jakt {
namespace cpp_import__common {
struct CppImportErrors {
  public:
public: static StringView no_this_type();
public: static StringView path_not_found();
public: CppImportErrors();

public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::cpp_import__common::CppImportErrors> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::cpp_import__common::CppImportErrors const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
