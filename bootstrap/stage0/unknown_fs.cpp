#include "unknown_fs.h"
namespace Jakt {
namespace unknown_fs {
ErrorOr<void> make_directory(DeprecatedString const path) {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: make_directory {}"sv),path);
return Error::from_errno(static_cast<i32>(38));
}
return {};
}

ErrorOr<DeprecatedString> current_directory() {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: current_directory"sv));
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<DeprecatedString> unknown_fs::DirectoryIterator::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("DirectoryIterator("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<NonnullRefPtr<unknown_fs::DirectoryIterator>>> unknown_fs::DirectoryIterator::from_path(path::Path const path) {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: DirectoryIterator::from_path(path: {})"sv),path);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<path::Path,bool>>> unknown_fs::DirectoryIterator::next() {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: DirectoryIterator::next()"sv));
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<path::Path> unknown_fs::DirectoryIterator::get_path() const {
{
warnln(Jakt::DeprecatedString("NOT IMPLEMENTED: DirectoryIterator::get_path()"sv));
return Error::from_errno(static_cast<i32>(38));
}
}

unknown_fs::DirectoryIterator::DirectoryIterator(){}
ErrorOr<NonnullRefPtr<DirectoryIterator>> unknown_fs::DirectoryIterator::create() { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) DirectoryIterator ())); return o; }
}
} // namespace Jakt
