#include "jakt__platform__unknown_fs.h"
namespace Jakt {
namespace jakt__platform__unknown_fs {
ErrorOr<void> make_directory(ByteString const path) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: make_directory {}"sv)),path);
return Error::from_errno(static_cast<i32>(38));
}
return {};
}

ErrorOr<ByteString> current_directory() {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: current_directory"sv)));
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<ByteString> real_path(ByteString const path) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: real_path {}"sv)),path);
return Error::from_errno(static_cast<i32>(38));
}
}

ByteString jakt__platform__unknown_fs::DirectoryIterator::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("DirectoryIterator("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<jakt__path::Path,bool>>> jakt__platform__unknown_fs::DirectoryIterator::next() {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: DirectoryIterator::next()"sv)));
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>>> jakt__platform__unknown_fs::DirectoryIterator::from_path(jakt__path::Path const path) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: DirectoryIterator::from_path(path: {})"sv)),path);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<jakt__path::Path> jakt__platform__unknown_fs::DirectoryIterator::get_path() const {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: DirectoryIterator::get_path()"sv)));
return Error::from_errno(static_cast<i32>(38));
}
}

jakt__platform__unknown_fs::DirectoryIterator::DirectoryIterator(){}
NonnullRefPtr<DirectoryIterator> jakt__platform__unknown_fs::DirectoryIterator::__jakt_create() { auto o = adopt_ref(*new DirectoryIterator ()); return o; }
}
} // namespace Jakt
