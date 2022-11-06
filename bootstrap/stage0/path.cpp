#include "path.h"
namespace Jakt {
namespace path {
ErrorOr<String> path::Path::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Path("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("path: "));TRY(builder.appendff("\"{}\"", path));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<path::Path> path::Path::from_parts(JaktInternal::Array<String> const parts) {
{
path::Path path = path::Path(String("."));
{
JaktInternal::ArrayIterator<String> _magic = ((parts).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String part = (_magic_value.value());
{
(path = TRY((((path).join(part)))));
}

}
}

return (path);
}
}

JaktInternal::Optional<size_t> path::Path::last_slash(String const path) {
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

path::Path::Path(String a_path) :path(a_path){}

String path::Path::to_string() const {
{
return (((*this).path));
}
}

ErrorOr<String> path::Path::extension() const {
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
return (TRY((((((*this).path)).substring((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))),(JaktInternal::checked_sub<size_t>((JaktInternal::checked_sub<size_t>(((((*this).path)).length()),static_cast<size_t>(1ULL))),i)))))));
}
}

}
}

return (String(""));
}
}

ErrorOr<JaktInternal::Tuple<String,String>> path::Path::split_at_last_slash() const {
{
size_t const len = ((((*this).path)).length());
JaktInternal::Optional<size_t> const last_slash = path::Path::Path::last_slash(((*this).path));
if (((last_slash).has_value())){
String const dir = TRY((((((*this).path)).substring(static_cast<size_t>(0ULL),(last_slash.value())))));
String const base = TRY((((((*this).path)).substring((JaktInternal::checked_add<size_t>((last_slash.value()),static_cast<size_t>(1ULL))),(JaktInternal::checked_sub<size_t>((JaktInternal::checked_sub<size_t>(len,(last_slash.value()))),static_cast<size_t>(1ULL)))))));
return ((Tuple{dir, base}));
}
return ((Tuple{String(""), ((*this).path)}));
}
}

ErrorOr<void> path::Path::normalize_separators() {
{
JaktInternal::Array<u8> separators = (TRY((Array<u8>::create_with({static_cast<u8>(47)}))));
u8 separator = static_cast<u8>(47);
StringBuilder normalized_builder = TRY((StringBuilder::create()));
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

ErrorOr<path::Path> path::Path::join(String const path) const {
{
if (((((*this).path) == String(".")) || (((((*this).path)).length()) == static_cast<size_t>(0ULL)))){
return (path::Path(path));
}
if (((path).is_empty())){
return (*this);
}
u8 const separator = static_cast<u8>(47);
if ((((path).byte_at(static_cast<size_t>(0ULL))) == separator)){
return (TRY((path::Path::Path::from_string(path))));
}
StringBuilder join_builder = TRY((StringBuilder::create()));
TRY((((join_builder).append_string(((*this).path)))));
if ((((((*this).path)).byte_at((JaktInternal::checked_sub<size_t>(((((*this).path)).length()),static_cast<size_t>(1ULL))))) != separator)){
TRY((((join_builder).append(separator))));
}
TRY((((join_builder).append_string(path))));
return (TRY((path::Path::Path::from_string(TRY((((join_builder).to_string())))))));
}
}

ErrorOr<String> path::Path::basename(bool const strip_extension) const {
{
JaktInternal::Tuple<String,String> const parts = TRY((((*this).split_at_last_slash())));
if (strip_extension){
size_t ext_length = ((TRY((((*this).extension())))).length());
if ((ext_length > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ext_length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
return (TRY((((((parts).get<1>())).substring(static_cast<size_t>(0ULL),(JaktInternal::checked_sub<size_t>(((((parts).get<1>())).length()),ext_length)))))));
}
return (((parts).get<1>()));
}
}

ErrorOr<path::Path> path::Path::parent() const {
{
JaktInternal::Tuple<String,String> const parts = TRY((((*this).split_at_last_slash())));
if ((((parts).get<0>()) == String(""))){
return (path::Path(String(".")));
}
return (path::Path(((parts).get<0>())));
}
}

ErrorOr<path::Path> path::Path::replace_extension(String const new_extension) const {
{
JaktInternal::Tuple<String,String> const parts = TRY((((*this).split_at_last_slash())));
String const basename = TRY((((*this).basename(true))));
String const extension = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<path::Path>>{
auto __jakt_enum_value = (new_extension);
if (__jakt_enum_value == String("")) {
return JaktInternal::ExplicitValue(String(""));
}
else {
return JaktInternal::ExplicitValue((String(".") + new_extension));
}
}()))
;
return (TRY((path::Path::Path::from_parts((TRY((Array<String>::create_with({((parts).get<0>()), (basename + extension)}))))))));
}
}

bool path::Path::exists() const {
{
return (File::exists(((*this).path)));
}
}

ErrorOr<path::Path> path::Path::from_string(String const string) {
{
path::Path path = path::Path(string);
TRY((((path).normalize_separators())));
return (path);
}
}

}
} // namespace Jakt
