#pragma once
#include "__unified_forward.h"
#include "jakt__platform__unknown_fs.h"
#include "jakt__path.h"
#include "jakt__platform.h"
namespace Jakt {
namespace jakt__file_iterator {
class RecursiveFileIterator :public RefCounted<RecursiveFileIterator>, public Weakable<RecursiveFileIterator> {
  public:
virtual ~RecursiveFileIterator() = default;
private: ByteString extension;private: JaktInternal::DynamicArray<jakt__path::Path> directory_list;private: JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>> current_directory;public: static ErrorOr<NonnullRefPtr<jakt__file_iterator::RecursiveFileIterator>> make(jakt__path::Path const directory, ByteString const extension);
public: ErrorOr<JaktInternal::Optional<jakt__path::Path>> next();
public: protected:
explicit RecursiveFileIterator(ByteString a_extension, JaktInternal::DynamicArray<jakt__path::Path> a_directory_list, JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>> a_current_directory);
public:
static NonnullRefPtr<RecursiveFileIterator> __jakt_create(ByteString extension, JaktInternal::DynamicArray<jakt__path::Path> directory_list, JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>> current_directory);

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__file_iterator::RecursiveFileIterator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__file_iterator::RecursiveFileIterator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
