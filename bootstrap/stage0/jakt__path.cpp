#include "jakt__path.h"
namespace Jakt {
namespace jakt__path {
ErrorOr<DeprecatedString> jakt__path::Path::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Path("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("path: \"{}\"", path));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<DeprecatedString> jakt__path::Path::extension() const {
{
{
JaktInternal::Range<size_t> _magic = (((JaktInternal::Range<size_t>{static_cast<size_t>(JaktInternal::checked_sub(((((*this).path)).length()),static_cast<size_t>(1ULL))),static_cast<size_t>(static_cast<size_t>(0ULL))})).inclusive());
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
u8 const c = ((((*this).path)).byte_at(i));
if (((c) == (static_cast<u8>(47)))){
break;
}
if (((c) == (static_cast<u8>(u8'.')))){
return ((((*this).path)).substring(JaktInternal::checked_add(i,static_cast<size_t>(1ULL)),JaktInternal::checked_sub(JaktInternal::checked_sub(((((*this).path)).length()),static_cast<size_t>(1ULL)),i)));
}
}

}
}

return TRY(DeprecatedString::from_utf8(""sv));
}
}

jakt__path::Path::Path(DeprecatedString a_path) :path(move(a_path)){}

ErrorOr<DeprecatedString> jakt__path::Path::basename(bool const strip_extension) const {
{
JaktInternal::Tuple<DeprecatedString,DeprecatedString> const parts = TRY((((*this).split_at_last_slash())));
if (strip_extension){
size_t ext_length = ((TRY((((*this).extension())))).length());
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(ext_length,static_cast<size_t>(0ULL))){
((ext_length) += (static_cast<size_t>(1ULL)));
}
return ((((parts).template get<1>())).substring(static_cast<size_t>(0ULL),JaktInternal::checked_sub(((((parts).template get<1>())).length()),ext_length)));
}
return ((parts).template get<1>());
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::join(DeprecatedString const path) const {
{
if ((((((*this).path)) == (TRY(DeprecatedString::from_utf8("."sv)))) || ((((((*this).path)).length())) == (static_cast<size_t>(0ULL))))){
return jakt__path::Path(path);
}
if (((path).is_empty())){
return *this;
}
u8 const separator = static_cast<u8>(47);
if (((((path).byte_at(static_cast<size_t>(0ULL)))) == (separator))){
return TRY((jakt__path::Path::from_string(path)));
}
DeprecatedStringBuilder join_builder = DeprecatedStringBuilder::create();
TRY((((join_builder).append_string(((*this).path)))));
if (((((((*this).path)).byte_at(JaktInternal::checked_sub(((((*this).path)).length()),static_cast<size_t>(1ULL))))) != (separator))){
TRY((((join_builder).append(separator))));
}
TRY((((join_builder).append_string(path))));
return TRY((jakt__path::Path::from_string(TRY((((join_builder).to_string()))))));
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::join(jakt__path::Path const path) const {
{
return TRY((((*this).join(((path).path)))));
}
}

DeprecatedString jakt__path::Path::to_string() const {
{
return ((*this).path);
}
}

bool jakt__path::Path::exists() const {
{
return File::exists(((*this).path));
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::replace_extension(DeprecatedString const new_extension) const {
{
JaktInternal::Tuple<DeprecatedString,DeprecatedString> const parts = TRY((((*this).split_at_last_slash())));
DeprecatedString const basename = TRY((((*this).basename(true))));
DeprecatedString const extension = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<jakt__path::Path>>{
auto __jakt_enum_value = (new_extension);
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8(""sv))) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
}
else {
return JaktInternal::ExplicitValue(TRY((((TRY(DeprecatedString::from_utf8("."sv))) + (new_extension)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return TRY((jakt__path::Path::from_parts((TRY((DynamicArray<DeprecatedString>::create_with({((parts).template get<0>()), TRY((((basename) + (extension))))})))))));
}
}

JaktInternal::Optional<size_t> jakt__path::Path::last_slash(DeprecatedString const path) {
{
size_t i = JaktInternal::checked_sub(((path).length()),static_cast<size_t>(1ULL));
u8 const separator = static_cast<u8>(47);
while (([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(i,static_cast<size_t>(1ULL)) && ((((path).byte_at(i))) != (separator)))){
((i) -= (static_cast<size_t>(1ULL)));
}
if ((((i) == (static_cast<size_t>(0ULL))) && ((((path).byte_at(i))) != (separator)))){
return JaktInternal::OptionalNone();
}
return i;
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::from_string(DeprecatedString const string) {
{
jakt__path::Path path = jakt__path::Path(string);
TRY((((path).normalize_separators())));
return path;
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::from_parts(JaktInternal::DynamicArray<DeprecatedString> const parts) {
{
jakt__path::Path path = jakt__path::Path(TRY(DeprecatedString::from_utf8("."sv)));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((parts).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString part = (_magic_value.value());
{
(path = TRY((((path).join(part)))));
}

}
}

return path;
}
}

ErrorOr<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> jakt__path::Path::split_at_last_slash() const {
{
size_t const len = ((((*this).path)).length());
JaktInternal::Optional<size_t> const last_slash = jakt__path::Path::last_slash(((*this).path));
if (((last_slash).has_value())){
DeprecatedString const dir = ((((*this).path)).substring(static_cast<size_t>(0ULL),(last_slash.value())));
DeprecatedString const base = ((((*this).path)).substring(JaktInternal::checked_add((last_slash.value()),static_cast<size_t>(1ULL)),JaktInternal::checked_sub(JaktInternal::checked_sub(len,(last_slash.value())),static_cast<size_t>(1ULL))));
return (Tuple{dir, base});
}
return (Tuple{TRY(DeprecatedString::from_utf8(""sv)), ((*this).path)});
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::parent() const {
{
JaktInternal::Tuple<DeprecatedString,DeprecatedString> const parts = TRY((((*this).split_at_last_slash())));
if (((((parts).template get<0>())) == (TRY(DeprecatedString::from_utf8(""sv))))){
return jakt__path::Path(TRY(DeprecatedString::from_utf8("."sv)));
}
return jakt__path::Path(((parts).template get<0>()));
}
}

ErrorOr<void> jakt__path::Path::normalize_separators() {
{
JaktInternal::DynamicArray<u8> separators = (TRY((DynamicArray<u8>::create_with({static_cast<u8>(47)}))));
u8 separator = static_cast<u8>(47);
DeprecatedStringBuilder normalized_builder = DeprecatedStringBuilder::create();
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).path)).length()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
u8 const ch = ((((*this).path)).byte_at(i));
if (((separators).contains(ch))){
TRY((((normalized_builder).append(separator))));
}
else {
TRY((((normalized_builder).append(ch))));
}

}

}
}

(((*this).path) = TRY((((normalized_builder).to_string()))));
}
return {};
}

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> jakt__path::Path::components() const {
{
JaktInternal::DynamicArray<DeprecatedString> parts = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
JaktInternal::Optional<size_t> last_slash = JaktInternal::OptionalNone();
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).path)).length()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((*this).path)).byte_at(i))) == (static_cast<u8>(47)))){
if (((last_slash).has_value())){
if (((i) == (JaktInternal::checked_add((last_slash.value()),static_cast<size_t>(1ULL))))){
(last_slash = i);
continue;
}
TRY((((parts).push(((((*this).path)).substring(JaktInternal::checked_add((last_slash.value()),static_cast<size_t>(1ULL)),JaktInternal::checked_sub(JaktInternal::checked_sub(i,(last_slash.value())),static_cast<size_t>(1ULL))))))));
}
else {
if (((i) == (static_cast<size_t>(0ULL)))){
TRY((((parts).push(TRY(DeprecatedString::from_utf8("/"sv))))));
}
else {
TRY((((parts).push(((((*this).path)).substring(static_cast<size_t>(0ULL),i))))));
}

}

(last_slash = i);
}
}

}
}

if (((last_slash).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(JaktInternal::checked_add((last_slash.value()),static_cast<size_t>(1ULL)),((((*this).path)).length()))){
TRY((((parts).push(((((*this).path)).substring(JaktInternal::checked_add((last_slash.value()),static_cast<size_t>(1ULL)),JaktInternal::checked_sub(JaktInternal::checked_sub(((((*this).path)).length()),(last_slash.value())),static_cast<size_t>(1ULL))))))));
}
}
else {
TRY((((parts).push(((*this).path)))));
}

return parts;
}
}

ErrorOr<bool> jakt__path::Path::is_dot() const {
{
return (((((*this).path)) == (TRY(DeprecatedString::from_utf8("."sv)))) || ((((*this).path)) == (TRY(DeprecatedString::from_utf8(".."sv)))));
}
}

}
} // namespace Jakt
