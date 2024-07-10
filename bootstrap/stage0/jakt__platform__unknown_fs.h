#pragma once
#include <lib.h>
#include "jakt__path.h"
namespace Jakt {
namespace jakt__platform__unknown_fs {
class DirectoryIterator;
ErrorOr<void> make_directory(ByteString const path);

ErrorOr<ByteString> current_directory();

ErrorOr<ByteString> real_path(ByteString const path);

}
namespace jakt__platform__unknown_fs {
class DirectoryIterator :public RefCounted<DirectoryIterator>, public Weakable<DirectoryIterator> {
  public:
virtual ~DirectoryIterator() = default;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::jakt__path::Path,bool>>> next();
public: static ErrorOr<JaktInternal::Optional<NonnullRefPtr<Jakt::jakt__platform__unknown_fs::DirectoryIterator>>> from_path(Jakt::jakt__path::Path const path);
public: ErrorOr<Jakt::jakt__path::Path> get_path() const;
public: protected:
explicit DirectoryIterator();
public:
static NonnullRefPtr<DirectoryIterator> __jakt_create();

public: ByteString debug_description() const;
};}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::jakt__platform__unknown_fs::DirectoryIterator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::jakt__platform__unknown_fs::DirectoryIterator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());return format_error;}
};
namespace Jakt {
} // namespace Jakt
