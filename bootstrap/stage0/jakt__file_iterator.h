#pragma once
#include "__unified_forward.h"
#include "jakt__path.h"
#include "jakt__platform.h"
#include "jakt__platform__unknown_fs.h"
namespace Jakt {
namespace jakt__file_iterator {
class RecursiveFileIterator : public RefCounted<RecursiveFileIterator>, public Weakable<RecursiveFileIterator> {
  public:
virtual ~RecursiveFileIterator() = default;
DeprecatedString extension;JaktInternal::DynamicArray<jakt__path::Path> directory_list;JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>> current_directory;static ErrorOr<NonnullRefPtr<jakt__file_iterator::RecursiveFileIterator>> make(jakt__path::Path const directory, DeprecatedString const extension);
ErrorOr<JaktInternal::Optional<jakt__path::Path>> next();
protected:
explicit RecursiveFileIterator(DeprecatedString a_extension, JaktInternal::DynamicArray<jakt__path::Path> a_directory_list, JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>> a_current_directory);
public:
static ErrorOr<NonnullRefPtr<RecursiveFileIterator>> __jakt_create(DeprecatedString extension, JaktInternal::DynamicArray<jakt__path::Path> directory_list, JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>> current_directory);

ErrorOr<DeprecatedString> debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__file_iterator::RecursiveFileIterator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__file_iterator::RecursiveFileIterator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
