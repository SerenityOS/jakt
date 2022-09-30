#pragma once
#include "__unified_forward.h"
#include "os.h"
#include "unknown_path.h"
namespace Jakt {
namespace path {
struct Path {
  public:
String path;static ErrorOr<path::Path> from_parts(const JaktInternal::Array<String> parts);
static JaktInternal::Optional<size_t> last_slash(const String path);
Path(String a_path);

String to_string() const;
ErrorOr<String> extension() const;
ErrorOr<JaktInternal::Tuple<String,String>> split_at_last_slash() const;
ErrorOr<void> normalize_separators();
ErrorOr<path::Path> join(const String path) const;
ErrorOr<String> basename(const bool strip_extension) const;
ErrorOr<path::Path> parent() const;
ErrorOr<path::Path> replace_extension(const String new_extension) const;
bool exists() const;
static ErrorOr<path::Path> from_string(const String string);
ErrorOr<String> debug_description() const;
};}
template<>struct Formatter<path::Path> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, path::Path const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
