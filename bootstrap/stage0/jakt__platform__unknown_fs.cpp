#include "jakt__platform__unknown_fs.h"
namespace Jakt {
namespace jakt__platform__unknown_fs {
ErrorOr<DeprecatedString> current_directory() {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: current_directory"sv)));
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<void> make_directory(DeprecatedString const path) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: make_directory {}"sv)),path);
return Error::from_errno(static_cast<i32>(38));
}
return {};
}

ErrorOr<DeprecatedString> real_path(DeprecatedString const path) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: real_path {}"sv)),path);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<DeprecatedString> jakt__platform__unknown_fs::DirectoryIterator::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("DirectoryIterator("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<NonnullRefPtr<jakt__platform__unknown_fs::DirectoryIterator>>> jakt__platform__unknown_fs::DirectoryIterator::from_path(jakt__path::Path const path) {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: DirectoryIterator::from_path(path: {})"sv)),path);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<jakt__path::Path,bool>>> jakt__platform__unknown_fs::DirectoryIterator::next() {
{
warnln((StringView::from_string_literal("NOT IMPLEMENTED: DirectoryIterator::next()"sv)));
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
ErrorOr<NonnullRefPtr<DirectoryIterator>> jakt__platform__unknown_fs::DirectoryIterator::__jakt_create() { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) DirectoryIterator ())); return o; }
}
} // namespace Jakt
