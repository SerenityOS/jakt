#pragma once
#include "__unified_forward.h"
#include "path.h"
namespace Jakt {
namespace unknown_fs {
class DirectoryIterator : public RefCounted<DirectoryIterator>, public Weakable<DirectoryIterator> {
  public:
virtual ~DirectoryIterator() = default;
static ErrorOr<JaktInternal::Optional<NonnullRefPtr<unknown_fs::DirectoryIterator>>> from_path(path::Path const path);
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<path::Path,bool>>> next();
ErrorOr<path::Path> get_path() const;
protected:
explicit DirectoryIterator();
public:
static ErrorOr<NonnullRefPtr<DirectoryIterator>> create();

ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::unknown_fs::DirectoryIterator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::unknown_fs::DirectoryIterator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
namespace Jakt {
} // namespace Jakt
