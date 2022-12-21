#include "jakt__path.h"
namespace Jakt {
namespace jakt__path {
ErrorOr<DeprecatedString> jakt__path::Path::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Path("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("path: "sv));TRY(builder.appendff("\"{}\"", path));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<jakt__path::Path> jakt__path::Path::from_parts(JaktInternal::DynamicArray<DeprecatedString> const parts) {
{
jakt__path::Path path = jakt__path::Path(Jakt::DeprecatedString("."sv));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((parts).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString part = (_magic_value.value());
{
(path = TRY((((path).join(part)))));
}

}
}

return (path);
}
}

JaktInternal::Optional<size_t> jakt__path::Path::last_slash(DeprecatedString const path) {
{
size_t i = (JaktInternal::checked_sub<size_t>(((path).length()),static_cast<size_t>(1ULL)));
u8 const separator = static_cast<u8>(47);
while (((i >= static_cast<size_t>(1ULL)) && (((path).byte_at(i)) != separator))){
({auto& _jakt_ref = i;_jakt_ref = JaktInternal::checked_sub<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
if (((i == static_cast<size_t>(0ULL)) && (((path).byte_at(i)) != separator))){
return (JaktInternal::OptionalNone());
}
return (i);
}
}

jakt__path::Path::Path(DeprecatedString a_path) :path(a_path){}

bool jakt__path::Path::is_dot() const {
{
return (((((*this).path) == Jakt::DeprecatedString("."sv)) || (((*this).path) == Jakt::DeprecatedString(".."sv))));
}
}

DeprecatedString jakt__path::Path::to_string() const {
{
return (((*this).path));
}
}

ErrorOr<DeprecatedString> jakt__path::Path::extension() const {
{
{
JaktInternal::Range<size_t> _magic = (((JaktInternal::Range<size_t>{static_cast<size_t>((JaktInternal::checked_sub<size_t>(((((*this).path)).length()),static_cast<size_t>(1ULL)))),static_cast<size_t>(static_cast<size_t>(0ULL))})).inclusive());
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
u8 const c = ((((*this).path)).byte_at(i));
if ((c == static_cast<u8>(47))){
break;
}
if ((c == '.')){
return (((((*this).path)).substring((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))),(JaktInternal::checked_sub<size_t>((JaktInternal::checked_sub<size_t>(((((*this).path)).length()),static_cast<size_t>(1ULL))),i)))));
}
}

}
}

return (Jakt::DeprecatedString(""sv));
}
}

ErrorOr<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> jakt__path::Path::split_at_last_slash() const {
{
size_t const len = ((((*this).path)).length());
JaktInternal::Optional<size_t> const last_slash = jakt__path::Path::last_slash(((*this).path));
if (((last_slash).has_value())){
DeprecatedString const dir = ((((*this).path)).substring(static_cast<size_t>(0ULL),(last_slash.value())));
DeprecatedString const base = ((((*this).path)).substring((JaktInternal::checked_add<size_t>((last_slash.value()),static_cast<size_t>(1ULL))),(JaktInternal::checked_sub<size_t>((JaktInternal::checked_sub<size_t>(len,(last_slash.value()))),static_cast<size_t>(1ULL)))));
return ((Tuple{dir, base}));
}
return ((Tuple{Jakt::DeprecatedString(""sv), ((*this).path)}));
}
}

ErrorOr<void> jakt__path::Path::normalize_separators() {
{
JaktInternal::DynamicArray<u8> separators = (TRY((DynamicArray<u8>::create_with({static_cast<u8>(47)}))));
u8 separator = static_cast<u8>(47);
DeprecatedStringBuilder normalized_builder = TRY((DeprecatedStringBuilder::create()));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).path)).length()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
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

ErrorOr<jakt__path::Path> jakt__path::Path::join(DeprecatedString const path) const {
{
if (((((*this).path) == Jakt::DeprecatedString("."sv)) || (((((*this).path)).length()) == static_cast<size_t>(0ULL)))){
return (jakt__path::Path(path));
}
if (((path).is_empty())){
return (*this);
}
u8 const separator = static_cast<u8>(47);
if ((((path).byte_at(static_cast<size_t>(0ULL))) == separator)){
return (TRY((jakt__path::Path::from_string(path))));
}
DeprecatedStringBuilder join_builder = TRY((DeprecatedStringBuilder::create()));
TRY((((join_builder).append_string(((*this).path)))));
if ((((((*this).path)).byte_at((JaktInternal::checked_sub<size_t>(((((*this).path)).length()),static_cast<size_t>(1ULL))))) != separator)){
TRY((((join_builder).append(separator))));
}
TRY((((join_builder).append_string(path))));
return (TRY((jakt__path::Path::from_string(TRY((((join_builder).to_string())))))));
}
}

ErrorOr<DeprecatedString> jakt__path::Path::basename(bool const strip_extension) const {
{
JaktInternal::Tuple<DeprecatedString,DeprecatedString> const parts = TRY((((*this).split_at_last_slash())));
if (strip_extension){
size_t ext_length = ((TRY((((*this).extension())))).length());
if ((ext_length > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ext_length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
return (((((parts).template get<1>())).substring(static_cast<size_t>(0ULL),(JaktInternal::checked_sub<size_t>(((((parts).template get<1>())).length()),ext_length)))));
}
return (((parts).template get<1>()));
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::parent() const {
{
JaktInternal::Tuple<DeprecatedString,DeprecatedString> const parts = TRY((((*this).split_at_last_slash())));
if ((((parts).template get<0>()) == Jakt::DeprecatedString(""sv))){
return (jakt__path::Path(Jakt::DeprecatedString("."sv)));
}
return (jakt__path::Path(((parts).template get<0>())));
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::replace_extension(DeprecatedString const new_extension) const {
{
JaktInternal::Tuple<DeprecatedString,DeprecatedString> const parts = TRY((((*this).split_at_last_slash())));
DeprecatedString const basename = TRY((((*this).basename(true))));
DeprecatedString const extension = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<jakt__path::Path>>{
auto __jakt_enum_value = (new_extension);
if (__jakt_enum_value == Jakt::DeprecatedString(""sv)) {
return JaktInternal::ExplicitValue(Jakt::DeprecatedString(""sv));
}
else {
return JaktInternal::ExplicitValue((Jakt::DeprecatedString("."sv) + new_extension));
}
}()))
;
return (TRY((jakt__path::Path::from_parts((TRY((DynamicArray<DeprecatedString>::create_with({((parts).template get<0>()), (basename + extension)}))))))));
}
}

bool jakt__path::Path::exists() const {
{
return (File::exists(((*this).path)));
}
}

ErrorOr<jakt__path::Path> jakt__path::Path::from_string(DeprecatedString const string) {
{
jakt__path::Path path = jakt__path::Path(string);
TRY((((path).normalize_separators())));
return (path);
}
}

}
} // namespace Jakt
