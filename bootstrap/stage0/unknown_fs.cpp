#include "unknown_fs.h"
namespace Jakt {
namespace unknown_fs {
ErrorOr<void> make_directory(String const path) {
{
warnln(Jakt::String("NOT IMPLEMENTED: make_directory {}"),path);
return Error::from_errno(static_cast<i32>(38));
}
return {};
}

ErrorOr<String> current_directory() {
{
warnln(Jakt::String("NOT IMPLEMENTED: current_directory"));
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<String> unknown_fs::DirectoryIterator::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("DirectoryIterator("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<NonnullRefPtr<unknown_fs::DirectoryIterator>>> unknown_fs::DirectoryIterator::from_path(path::Path const path) {
{
warnln(Jakt::String("NOT IMPLEMENTED: DirectoryIterator::from_path(path: {})"),path);
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<path::Path,bool>>> unknown_fs::DirectoryIterator::next() {
{
warnln(Jakt::String("NOT IMPLEMENTED: DirectoryIterator::next()"));
return Error::from_errno(static_cast<i32>(38));
}
}

ErrorOr<path::Path> unknown_fs::DirectoryIterator::get_path() const {
{
warnln(Jakt::String("NOT IMPLEMENTED: DirectoryIterator::get_path()"));
return Error::from_errno(static_cast<i32>(38));
}
}

unknown_fs::DirectoryIterator::DirectoryIterator(){}
ErrorOr<NonnullRefPtr<DirectoryIterator>> unknown_fs::DirectoryIterator::create() { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) DirectoryIterator ())); return o; }
}
} // namespace Jakt
