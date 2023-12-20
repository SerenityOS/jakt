#pragma once
#include "__unified_forward.h"
#include "jakt__path.h"
namespace Jakt {
namespace jakt__platform__unknown_fs {
class DirectoryIterator :public RefCounted<DirectoryIterator>, public Weakable<DirectoryIterator> {
  public:
virtual ~DirectoryIterator() = default;
public: ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<jakt__path::Path,bool>>> next();
public: static ErrorOr<JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>>> from_path(jakt__path::Path const path);
public: ErrorOr<jakt__path::Path> get_path() const;
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
