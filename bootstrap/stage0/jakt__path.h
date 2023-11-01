#pragma once
#include "__unified_forward.h"
#include "jakt__platform.h"
#include "jakt__platform__unknown_path.h"
namespace Jakt {
namespace jakt__path {
struct Path {
  public:
private: DeprecatedString path;public: ErrorOr<jakt__path::Path> absolute() const;
public: ErrorOr<DeprecatedString> extension() const;
public: Path(DeprecatedString a_path);

public: ErrorOr<DeprecatedString> basename(bool const strip_extension) const;
public: ErrorOr<jakt__path::Path> join(DeprecatedString const path) const;
public: ErrorOr<jakt__path::Path> join(jakt__path::Path const path) const;
public: DeprecatedString to_string() const;
public: bool exists() const;
public: ErrorOr<jakt__path::Path> replace_extension(DeprecatedString const new_extension) const;
private: static JaktInternal::Optional<size_t> last_slash(DeprecatedString const path);
public: static ErrorOr<jakt__path::Path> from_string(DeprecatedString const string);
public: static ErrorOr<jakt__path::Path> from_parts(JaktInternal::DynamicArray<DeprecatedString> const parts);
private: ErrorOr<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> split_at_last_slash() const;
public: ErrorOr<jakt__path::Path> parent() const;
private: ErrorOr<void> normalize_separators();
public: ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> components() const;
public: ErrorOr<bool> is_dot() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__path::Path> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__path::Path const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
