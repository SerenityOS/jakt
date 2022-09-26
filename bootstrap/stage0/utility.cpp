#include "utility.h"
namespace Jakt {
namespace utility {
String join(const JaktInternal::Array<String> strings,const String separator) {
{
String output = String("");
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<String> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String s = (_magic_value.value());
{
(output += s);
if ((i < (JaktInternal::checked_sub<size_t>(((strings).size()),static_cast<size_t>(1ULL))))){
(output += separator);
}
((i++));
}

}
}

return (output);
}
}

ErrorOr<JaktInternal::Array<String>> prepend_to_each(const JaktInternal::Array<String> strings,const String prefix) {
{
JaktInternal::Array<String> output = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<String> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String str = (_magic_value.value());
{
TRY((((output).push((prefix + str)))));
}

}
}

return (output);
}
}

void todo(const String message) {
{
warnln(String("TODO: {}"),message);
abort();
}
}

ErrorOr<String> interpret_escapes(const String s) {
{
StringBuilder builder = TRY((StringBuilder::create()));
bool in_escape = false;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((s).length()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
const u8 c = ((s).byte_at(i));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<String>>{
auto __jakt_enum_value = (c);
if (__jakt_enum_value == '\\') {
{
if (in_escape){
TRY((((builder).append('\\'))));
(in_escape = false);
}
else {
(in_escape = true);
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == '"') {
{
if (in_escape){
TRY((((builder).append(c))));
(in_escape = false);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == '\'') {
{
if (in_escape){
TRY((((builder).append(c))));
(in_escape = false);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == 'n') {
{
if (in_escape){
TRY((((builder).append('\n'))));
(in_escape = false);
}
else {
TRY((((builder).append(c))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((builder).append(c))));
(in_escape = false);
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
}

}
}

return (TRY((((builder).to_string()))));
}
}

ErrorOr<JaktInternal::Array<String>> append_to_each(const JaktInternal::Array<String> strings,const String suffix) {
{
JaktInternal::Array<String> output = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<String> _magic = ((strings).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String str = (_magic_value.value());
{
TRY((((output).push((str + suffix)))));
}

}
}

return (output);
}
}

[[noreturn]] void panic(const String message) {
{
warnln(String("internal error: {}"),message);
abort();
}
}

ErrorOr<String> escape_for_quotes(const String s) {
{
StringBuilder builder = TRY((StringBuilder::create()));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((s).length()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
const u8 c = ((s).byte_at(i));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<String>>{
auto __jakt_enum_value = (c);
if (__jakt_enum_value == '"') {
{
TRY((((builder).append_string(String("\\\"")))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == '\\') {
{
TRY((((builder).append_string(String("\\\\")))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == '\n') {
{
TRY((((builder).append_string(String("\\n")))));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((builder).append(c))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
}

}
}

return (TRY((((builder).to_string()))));
}
}

ErrorOr<String> utility::Span::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Span("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("file_id: "));TRY(builder.appendff("{}, ", file_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("start: "));TRY(builder.appendff("{}, ", start));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("end: "));TRY(builder.appendff("{}", end));
}
TRY(builder.append(")"));return builder.to_string(); }
bool utility::Span::contains(const utility::Span span) const {
{
return (((((((*this).file_id)).equals(((span).file_id))) && (((span).start) >= ((*this).start))) && (((span).end) <= ((*this).end))));
}
}

bool utility::Span::is_in_offset_range(const size_t start,const size_t end) const {
{
return (((start <= ((*this).start)) && (end >= ((*this).end))));
}
}

utility::Span::Span(utility::FileId a_file_id, size_t a_start, size_t a_end) :file_id(a_file_id), start(a_start), end(a_end){}

ErrorOr<String> utility::FileId::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("FileId("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("id: "));TRY(builder.appendff("{}", id));
}
TRY(builder.append(")"));return builder.to_string(); }
bool utility::FileId::equals(const utility::FileId rhs) const {
{
return ((((*this).id) == ((rhs).id)));
}
}

utility::FileId::FileId(size_t a_id) :id(a_id){}

ErrorOr<String> utility::FilePath::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("FilePath("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("path: "));TRY(builder.appendff("\"{}\"", path));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<NonnullRefPtr<utility::FilePath>> utility::FilePath::make(const String filepath) {
{
return (TRY((utility::FilePath::create(filepath))));
}
}

ErrorOr<JaktInternal::Tuple<String,String>> utility::FilePath::split_at_last_slash() const {
{
const size_t len = ((((*this).path)).length());
const JaktInternal::Optional<size_t> last_slash = utility::FilePath::last_slash(((*this).path));
if (((last_slash).has_value())){
const String dir = TRY((((((*this).path)).substring(static_cast<size_t>(0ULL),(JaktInternal::checked_add<size_t>((last_slash.value()),static_cast<size_t>(1ULL)))))));
const String base = TRY((((((*this).path)).substring((JaktInternal::checked_add<size_t>((last_slash.value()),static_cast<size_t>(1ULL))),(JaktInternal::checked_sub<size_t>((JaktInternal::checked_sub<size_t>(len,(last_slash.value()))),static_cast<size_t>(1ULL)))))));
return ((Tuple{dir, base}));
}
return ((Tuple{String(""), ((*this).path)}));
}
}

ErrorOr<String> utility::FilePath::dirname() const {
{
const JaktInternal::Tuple<String,String> parts = TRY((((*this).split_at_last_slash())));
if ((((parts).get<0>()) == String(""))){
return (String("."));
}
return (((parts).get<0>()));
}
}

utility::FilePath::FilePath(String&& a_path): path(move(a_path)){}
ErrorOr<NonnullRefPtr<FilePath>> utility::FilePath::create(String path) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) FilePath (move(path)))); return o; }
JaktInternal::Optional<size_t> utility::FilePath::last_slash(const String path) {
{
size_t i = (JaktInternal::checked_sub<size_t>(((path).length()),static_cast<size_t>(1ULL)));
while (((i >= static_cast<size_t>(1ULL)) && (((path).byte_at(i)) != '/'))){
((i--));
}
if (((i == static_cast<size_t>(0ULL)) && (((path).byte_at(i)) != '/'))){
return (JaktInternal::OptionalNone());
}
return (i);
}
}

ErrorOr<String> utility::FilePath::basename(const bool strip_extension) const {
{
const JaktInternal::Tuple<String,String> parts = TRY((((*this).split_at_last_slash())));
if (strip_extension){
size_t ext_length = ((TRY((((*this).ext())))).length());
if ((ext_length > static_cast<size_t>(0ULL))){
({auto& _jakt_ref = ext_length;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
return (TRY((((((parts).get<1>())).substring(static_cast<size_t>(0ULL),(JaktInternal::checked_sub<size_t>(((((parts).get<1>())).length()),ext_length)))))));
}
return (((parts).get<1>()));
}
}

ErrorOr<String> utility::FilePath::ext() const {
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
const u8 c = ((((*this).path)).byte_at(i));
if ((c == '/')){
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

ErrorOr<String> utility::ArgsParser::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("ArgsParser("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("args: "));TRY(builder.appendff("{}, ", args));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("removed_indices: "));TRY(builder.appendff("{}, ", removed_indices));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("definitely_positional_args: "));TRY(builder.appendff("{}", definitely_positional_args));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<utility::ArgsParser> utility::ArgsParser::from_args(const JaktInternal::Array<String> args) {
{
utility::ArgsParser parser = utility::ArgsParser(args,(TRY((Array<size_t>::create_with({})))),(TRY((Array<String>::create_with({})))));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<String> _magic = ((((parser).args)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String arg = (_magic_value.value());
{
if ((arg == String("--"))){
(((parser).definitely_positional_args) = TRY((((((((parser).args))[(JaktInternal::Range<size_t>{static_cast<size_t>((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))),static_cast<size_t>(((((parser).args)).size()))})])).to_array()))));
(((parser).args) = TRY((((((((parser).args))[(JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(i)})])).to_array()))));
break;
}
({auto& _jakt_ref = i;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}

}
}

return (parser);
}
}

ErrorOr<JaktInternal::Array<String>> utility::ArgsParser::option_multiple(const JaktInternal::Array<String> names) {
{
JaktInternal::Array<String> result = (TRY((Array<String>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<String> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
if ((((((*this).args))[i]) == name)){
if ((((((*this).args)).size()) <= (JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))))){
warnln(String("The option '{}' requires a value, but none was supplied"),name);
return Error::from_errno(static_cast<i32>(200));
}
TRY((((((*this).removed_indices)).push(i))));
TRY((((((*this).removed_indices)).push((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))))));
TRY((((result).push(((((*this).args))[(JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))])))));
continue;
}
if (((((((*this).args))[i])).starts_with(name))){
TRY((((((*this).removed_indices)).push(i))));
TRY((((result).push(TRY((((((((*this).args))[i])).substring(((name).length()),(JaktInternal::checked_sub<size_t>(((((((*this).args))[i])).length()),((name).length())))))))))));
}
}

}
}

}

}
}

return (result);
}
}

ErrorOr<bool> utility::ArgsParser::flag(const JaktInternal::Array<String> names) {
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<String> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
if ((((((*this).args))[i]) == name)){
TRY((((((*this).removed_indices)).push(i))));
return (true);
}
}

}
}

}

}
}

return (false);
}
}

utility::ArgsParser::ArgsParser(JaktInternal::Array<String> a_args, JaktInternal::Array<size_t> a_removed_indices, JaktInternal::Array<String> a_definitely_positional_args) :args(a_args), removed_indices(a_removed_indices), definitely_positional_args(a_definitely_positional_args){}

ErrorOr<JaktInternal::Array<String>> utility::ArgsParser::remaining_arguments() const {
{
JaktInternal::Array<String> remaining = (TRY((Array<String>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((*this).removed_indices)).contains(i))))){
TRY((((remaining).push(((((*this).args))[i])))));
}
}

}
}

{
JaktInternal::ArrayIterator<String> _magic = ((((*this).definitely_positional_args)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String arg = (_magic_value.value());
{
TRY((((remaining).push(arg))));
}

}
}

return (remaining);
}
}

ErrorOr<JaktInternal::Optional<String>> utility::ArgsParser::option(const JaktInternal::Array<String> names) {
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<String> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
if ((((((*this).args))[i]) == name)){
if ((((((*this).args)).size()) <= (JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))))){
warnln(String("The option '{}' requires a value, but none was supplied"),name);
return Error::from_errno(static_cast<i32>(200));
}
TRY((((((*this).removed_indices)).push(i))));
TRY((((((*this).removed_indices)).push((JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))))));
return (((((*this).args))[(JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL)))]));
}
if (((((((*this).args))[i])).starts_with(name))){
TRY((((((*this).removed_indices)).push(i))));
return (TRY((((((((*this).args))[i])).substring(((name).length()),(JaktInternal::checked_sub<size_t>(((((((*this).args))[i])).length()),((name).length()))))))));
}
}

}
}

}

}
}

return (JaktInternal::OptionalNone());
}
}

}
} // namespace Jakt
