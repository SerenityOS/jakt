#pragma once
#include "__unified_forward.h"
#include "jakt__platform.h"
#include "jakt__platform__unknown_path.h"
namespace Jakt {
namespace jakt__path {
struct Path {
  public:
DeprecatedString path;static ErrorOr<jakt__path::Path> from_parts(JaktInternal::DynamicArray<DeprecatedString> const parts);
static JaktInternal::Optional<size_t> last_slash(DeprecatedString const path);
Path(DeprecatedString a_path);

bool is_dot() const;
DeprecatedString to_string() const;
ErrorOr<DeprecatedString> extension() const;
ErrorOr<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> split_at_last_slash() const;
ErrorOr<void> normalize_separators();
ErrorOr<jakt__path::Path> join(DeprecatedString const path) const;
ErrorOr<DeprecatedString> basename(bool const strip_extension) const;
ErrorOr<jakt__path::Path> parent() const;
ErrorOr<jakt__path::Path> replace_extension(DeprecatedString const new_extension) const;
bool exists() const;
static ErrorOr<jakt__path::Path> from_string(DeprecatedString const string);
ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__path::Path> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__path::Path const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt