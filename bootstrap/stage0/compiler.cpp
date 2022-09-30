#include "compiler.h"
namespace Jakt {
namespace compiler {
ErrorOr<String> compiler::Compiler::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Compiler("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("files: "));TRY(builder.appendff("{}, ", files));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("file_ids: "));TRY(builder.appendff("{}, ", file_ids));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("errors: "));TRY(builder.appendff("{}, ", errors));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_file: "));TRY(builder.appendff("{}, ", current_file));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_file_contents: "));TRY(builder.appendff("{}, ", current_file_contents));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_lexer: "));TRY(builder.appendff("{}, ", dump_lexer));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_parser: "));TRY(builder.appendff("{}, ", dump_parser));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("ignore_parser_errors: "));TRY(builder.appendff("{}, ", ignore_parser_errors));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("debug_print: "));TRY(builder.appendff("{}, ", debug_print));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("include_paths: "));TRY(builder.appendff("{}, ", include_paths));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("json_errors: "));TRY(builder.appendff("{}, ", json_errors));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_type_hints: "));TRY(builder.appendff("{}, ", dump_type_hints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_try_hints: "));TRY(builder.appendff("{}, ", dump_try_hints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("optimize: "));TRY(builder.appendff("{}, ", optimize));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("target_triple: "));TRY(builder.appendff("{}", target_triple));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<void> compiler::Compiler::load_prelude() {
{
const String module_name = String("__prelude__");
const path::Path file_name = TRY((path::Path::from_string(module_name)));
TRY((((*this).get_file_id_or_register(file_name))));
}
return {};
}

ErrorOr<JaktInternal::Optional<path::Path>> compiler::Compiler::get_file_path(const utility::FileId file_id) const {
{
if ((((file_id).id) >= ((((*this).files)).size()))){
return (JaktInternal::OptionalNone());
}
return (((((*this).files))[((file_id).id)]));
}
}

bool compiler::Compiler::set_current_file(const utility::FileId file_id) {
{
const i32 ErrNOENT = static_cast<i32>(2);
const i32 ErrACCES = static_cast<i32>(13);
const i32 ErrFBIG = static_cast<i32>(27);
const i32 ErrNAMETOOLONG = static_cast<i32>(36);
const JaktInternal::Optional<utility::FileId> old_file_id = ((*this).current_file);
(((*this).current_file) = file_id);
auto __jakt_var_0 = [&]() -> ErrorOr<void> {{
NonnullRefPtr<File> file = TRY((File::open_for_reading(((((((*this).files))[((file_id).id)])).to_string()))));
(((*this).current_file_contents) = TRY((((file)->read_all()))));
}

;return {};}();
if (__jakt_var_0.is_error()) {auto error = __jakt_var_0.release_error();{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,bool>{
auto __jakt_enum_value = (((error).code()));
if (__jakt_enum_value == ErrNOENT) {
return (warnln(String("\u001b[31;1mError\u001b[0m Could not access {}: File not found"),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrACCES) {
return (warnln(String("\u001b[31;1mError\u001b[0m Could not access {}: Permission denied"),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrFBIG) {
return (warnln(String("\u001b[31;1mError\u001b[0m Could not access {}: File too big"),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrNAMETOOLONG) {
return (warnln(String("\u001b[31;1mError\u001b[0m Could not access {}: Name too long"),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else {
{
utility::panic(String("Incurred unrecognized error while trying to open file"));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
(((*this).current_file) = old_file_id);
return (false);
}
};
return (true);
}
}

ErrorOr<JaktInternal::Optional<path::Path>> compiler::Compiler::search_for_path(const String module_name) const {
{
{
JaktInternal::ArrayIterator<String> _magic = ((((*this).include_paths)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String include_path = (_magic_value.value());
{
const String candidate_path = (((include_path + String("/")) + module_name) + String(".jakt"));
if (File::exists(candidate_path)){
return (TRY((path::Path::from_string(candidate_path))));
}
}

}
}

return (JaktInternal::OptionalNone());
}
}

ErrorOr<utility::FileId> compiler::Compiler::get_file_id_or_register(const path::Path file) {
{
const String path = ((file).to_string());
JaktInternal::Optional<utility::FileId> file_id = ((((*this).file_ids)).get(path));
if (((file_id).has_value())){
return ((file_id.value()));
}
TRY((((((*this).files)).push(file))));
(file_id = utility::FileId((JaktInternal::checked_sub<size_t>(((((*this).files)).size()),static_cast<size_t>(1ULL)))));
TRY((((((*this).file_ids)).set(path,(file_id.value())))));
return ((file_id.value()));
}
}

JaktInternal::Optional<utility::FileId> compiler::Compiler::current_file_id() const {
{
return (((*this).current_file));
}
}

compiler::Compiler::Compiler(JaktInternal::Array<path::Path>&& a_files, JaktInternal::Dictionary<String,utility::FileId>&& a_file_ids, JaktInternal::Array<error::JaktError>&& a_errors, JaktInternal::Optional<utility::FileId>&& a_current_file, JaktInternal::Array<u8>&& a_current_file_contents, bool&& a_dump_lexer, bool&& a_dump_parser, bool&& a_ignore_parser_errors, bool&& a_debug_print, JaktInternal::Array<String>&& a_include_paths, bool&& a_json_errors, bool&& a_dump_type_hints, bool&& a_dump_try_hints, bool&& a_optimize, JaktInternal::Optional<String>&& a_target_triple): files(move(a_files)), file_ids(move(a_file_ids)), errors(move(a_errors)), current_file(move(a_current_file)), current_file_contents(move(a_current_file_contents)), dump_lexer(move(a_dump_lexer)), dump_parser(move(a_dump_parser)), ignore_parser_errors(move(a_ignore_parser_errors)), debug_print(move(a_debug_print)), include_paths(move(a_include_paths)), json_errors(move(a_json_errors)), dump_type_hints(move(a_dump_type_hints)), dump_try_hints(move(a_dump_try_hints)), optimize(move(a_optimize)), target_triple(move(a_target_triple)){}
ErrorOr<NonnullRefPtr<Compiler>> compiler::Compiler::create(JaktInternal::Array<path::Path> files, JaktInternal::Dictionary<String,utility::FileId> file_ids, JaktInternal::Array<error::JaktError> errors, JaktInternal::Optional<utility::FileId> current_file, JaktInternal::Array<u8> current_file_contents, bool dump_lexer, bool dump_parser, bool ignore_parser_errors, bool debug_print, JaktInternal::Array<String> include_paths, bool json_errors, bool dump_type_hints, bool dump_try_hints, bool optimize, JaktInternal::Optional<String> target_triple) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Compiler (move(files), move(file_ids), move(errors), move(current_file), move(current_file_contents), move(dump_lexer), move(dump_parser), move(ignore_parser_errors), move(debug_print), move(include_paths), move(json_errors), move(dump_type_hints), move(dump_try_hints), move(optimize), move(target_triple)))); return o; }
JaktInternal::Optional<path::Path> compiler::Compiler::current_file_path() const {
{
if (((((*this).current_file)).has_value())){
return (((((*this).files))[(((((*this).current_file).value())).id)]));
}
return (JaktInternal::OptionalNone());
}
}

[[noreturn]] ErrorOr<void> compiler::Compiler::panic(const String message) const {
{
MUST((((*this).print_errors())));
utility::panic(message);
}
}

ErrorOr<void> compiler::Compiler::print_errors() const {
{
size_t idx = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<path::Path> _magic = ((((*this).files)).iterator());
for (;;){
JaktInternal::Optional<path::Path> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
path::Path file = (_magic_value.value());
{
JaktInternal::Optional<JaktInternal::Array<u8>> file_contents = JaktInternal::OptionalNone();
const String file_name = ((file).to_string());
{
JaktInternal::ArrayIterator<error::JaktError> _magic = ((((*this).errors)).iterator());
for (;;){
JaktInternal::Optional<error::JaktError> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
error::JaktError error = (_magic_value.value());
{
const utility::Span span = ((error).span());
if ((((((span).file_id)).id) == idx)){
if (((*this).json_errors)){
TRY((error::print_error_json(file_name,error)));
}
else {
if ((!(((file_contents).has_value())))){
auto __jakt_var_1 = [&]() -> ErrorOr<void> {{
NonnullRefPtr<File> file = TRY((File::open_for_reading(file_name)));
(file_contents = TRY((((file)->read_all()))));
}

;return {};}();
if (__jakt_var_1.is_error()) {auto error = __jakt_var_1.release_error();{
}
};
}
TRY((error::print_error(file_name,file_contents,error)));
}

}
}

}
}

((idx++));
}

}
}

}
return {};
}

void compiler::Compiler::dbg_println(const String message) const {
{
if (((*this).debug_print)){
outln(String("{}"),message);
}
}
}

}
} // namespace Jakt
