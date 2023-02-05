#include "compiler.h"
namespace Jakt {
namespace compiler {
ErrorOr<DeprecatedString> compiler::Compiler::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Compiler("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("files: "sv));TRY(builder.appendff("{}, ", files));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("file_ids: "sv));TRY(builder.appendff("{}, ", file_ids));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("errors: "sv));TRY(builder.appendff("{}, ", errors));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_file: "sv));TRY(builder.appendff("{}, ", current_file));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_file_contents: "sv));TRY(builder.appendff("{}, ", current_file_contents));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_lexer: "sv));TRY(builder.appendff("{}, ", dump_lexer));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_parser: "sv));TRY(builder.appendff("{}, ", dump_parser));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("ignore_parser_errors: "sv));TRY(builder.appendff("{}, ", ignore_parser_errors));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("debug_print: "sv));TRY(builder.appendff("{}, ", debug_print));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("std_include_path: "sv));TRY(builder.appendff("{}, ", std_include_path));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("include_paths: "sv));TRY(builder.appendff("{}, ", include_paths));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("json_errors: "sv));TRY(builder.appendff("{}, ", json_errors));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_type_hints: "sv));TRY(builder.appendff("{}, ", dump_type_hints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_try_hints: "sv));TRY(builder.appendff("{}, ", dump_try_hints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("optimize: "sv));TRY(builder.appendff("{}, ", optimize));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("target_triple: "sv));TRY(builder.appendff("{}", target_triple));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> compiler::Compiler::load_prelude() {
{
DeprecatedString const module_name = Jakt::DeprecatedString("__prelude__"sv);
jakt__path::Path const file_name = TRY((jakt__path::Path::from_string(module_name)));
TRY((((*this).get_file_id_or_register(file_name))));
}
return {};
}

ErrorOr<JaktInternal::Optional<jakt__path::Path>> compiler::Compiler::get_file_path(utility::FileId const file_id) const {
{
if ((((file_id).id) >= ((((*this).files)).size()))){
return (JaktInternal::OptionalNone());
}
return (((((*this).files))[((file_id).id)]));
}
}

bool compiler::Compiler::set_current_file(utility::FileId const file_id) {
{
i32 const ErrNOENT = static_cast<i32>(2);
i32 const ErrACCES = static_cast<i32>(13);
i32 const ErrFBIG = static_cast<i32>(27);
i32 const ErrNAMETOOLONG = static_cast<i32>(36);
JaktInternal::Optional<utility::FileId> const old_file_id = ((*this).current_file);
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
return (warnln(Jakt::DeprecatedString("\u001b[31;1mError\u001b[0m Could not access {}: File not found"sv),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrACCES) {
return (warnln(Jakt::DeprecatedString("\u001b[31;1mError\u001b[0m Could not access {}: Permission denied"sv),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrFBIG) {
return (warnln(Jakt::DeprecatedString("\u001b[31;1mError\u001b[0m Could not access {}: File too big"sv),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrNAMETOOLONG) {
return (warnln(Jakt::DeprecatedString("\u001b[31;1mError\u001b[0m Could not access {}: Name too long"sv),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else {
{
utility::panic(Jakt::DeprecatedString("Incurred unrecognized error while trying to open file"sv));
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

JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> compiler::Compiler::current_file_state() const {
{
return ((Tuple{((*this).current_file), ((*this).current_file_contents)}));
}
}

ErrorOr<JaktInternal::Optional<jakt__path::Path>> compiler::Compiler::search_for_path(DeprecatedString const input_module_name) const {
{
DeprecatedStringBuilder builder = TRY((DeprecatedStringBuilder::create()));
TRY((((builder).append(static_cast<u8>(47)))));
DeprecatedString const separator = TRY((((builder).to_string())));
DeprecatedString const module_name = ((input_module_name).replace(Jakt::DeprecatedString("::"sv),separator));
DeprecatedString const standard_module_name = Jakt::DeprecatedString("jakt"sv);
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((((*this).include_paths)).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString include_path = (_magic_value.value());
{
jakt__path::Path const candidate_path = TRY((jakt__path::Path::from_parts((TRY((DynamicArray<DeprecatedString>::create_with({include_path, (module_name + Jakt::DeprecatedString(".jakt"sv))})))))));
if (((candidate_path).exists())){
return (candidate_path);
}
}

}
}

if (((module_name).starts_with(standard_module_name))){
DeprecatedString const std_module_name_path = ((module_name).substring((JaktInternal::checked_add<size_t>(((standard_module_name).length()),static_cast<size_t>(1ULL))),(JaktInternal::checked_sub<size_t>(((module_name).length()),(JaktInternal::checked_add<size_t>(((standard_module_name).length()),static_cast<size_t>(1ULL)))))));
jakt__path::Path const candidate_path = TRY((jakt__path::Path::from_parts((TRY((DynamicArray<DeprecatedString>::create_with({((((*this).std_include_path)).to_string()), (std_module_name_path + Jakt::DeprecatedString(".jakt"sv))})))))));
if (((candidate_path).exists())){
return (candidate_path);
}
}
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((((*this).include_paths)).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString include_path = (_magic_value.value());
{
jakt__path::Path const candidate_path = TRY((jakt__path::Path::from_parts((TRY((DynamicArray<DeprecatedString>::create_with({include_path, (module_name + Jakt::DeprecatedString(".jakt"sv))})))))));
if (((candidate_path).exists())){
return (candidate_path);
}
}

}
}

JaktInternal::Optional<jakt__path::Path> const current_file_path = ((*this).current_file_path());
if (((current_file_path).has_value())){
jakt__path::Path const candidate_path = TRY((jakt__path::Path::from_parts((TRY((DynamicArray<DeprecatedString>::create_with({((TRY(((((current_file_path.value())).parent())))).to_string()), (module_name + Jakt::DeprecatedString(".jakt"sv))})))))));
if (((candidate_path).exists())){
return (candidate_path);
}
}
return (JaktInternal::OptionalNone());
}
}

ErrorOr<utility::FileId> compiler::Compiler::get_file_id_or_register(jakt__path::Path const file) {
{
DeprecatedString const path = ((file).to_string());
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

void compiler::Compiler::restore_file_state(JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> const state) {
{
(((*this).current_file) = ((state).template get<0>()));
(((*this).current_file_contents) = ((state).template get<1>()));
}
}

compiler::Compiler::Compiler(JaktInternal::DynamicArray<jakt__path::Path>&& a_files, JaktInternal::Dictionary<DeprecatedString,utility::FileId>&& a_file_ids, JaktInternal::DynamicArray<error::JaktError>&& a_errors, JaktInternal::Optional<utility::FileId>&& a_current_file, JaktInternal::DynamicArray<u8>&& a_current_file_contents, bool&& a_dump_lexer, bool&& a_dump_parser, bool&& a_ignore_parser_errors, bool&& a_debug_print, jakt__path::Path&& a_std_include_path, JaktInternal::DynamicArray<DeprecatedString>&& a_include_paths, bool&& a_json_errors, bool&& a_dump_type_hints, bool&& a_dump_try_hints, bool&& a_optimize, JaktInternal::Optional<DeprecatedString>&& a_target_triple): files(move(a_files)), file_ids(move(a_file_ids)), errors(move(a_errors)), current_file(move(a_current_file)), current_file_contents(move(a_current_file_contents)), dump_lexer(move(a_dump_lexer)), dump_parser(move(a_dump_parser)), ignore_parser_errors(move(a_ignore_parser_errors)), debug_print(move(a_debug_print)), std_include_path(move(a_std_include_path)), include_paths(move(a_include_paths)), json_errors(move(a_json_errors)), dump_type_hints(move(a_dump_type_hints)), dump_try_hints(move(a_dump_try_hints)), optimize(move(a_optimize)), target_triple(move(a_target_triple)){}
ErrorOr<NonnullRefPtr<Compiler>> compiler::Compiler::__jakt_create(JaktInternal::DynamicArray<jakt__path::Path> files, JaktInternal::Dictionary<DeprecatedString,utility::FileId> file_ids, JaktInternal::DynamicArray<error::JaktError> errors, JaktInternal::Optional<utility::FileId> current_file, JaktInternal::DynamicArray<u8> current_file_contents, bool dump_lexer, bool dump_parser, bool ignore_parser_errors, bool debug_print, jakt__path::Path std_include_path, JaktInternal::DynamicArray<DeprecatedString> include_paths, bool json_errors, bool dump_type_hints, bool dump_try_hints, bool optimize, JaktInternal::Optional<DeprecatedString> target_triple) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Compiler (move(files), move(file_ids), move(errors), move(current_file), move(current_file_contents), move(dump_lexer), move(dump_parser), move(ignore_parser_errors), move(debug_print), move(std_include_path), move(include_paths), move(json_errors), move(dump_type_hints), move(dump_try_hints), move(optimize), move(target_triple)))); return o; }
JaktInternal::Optional<jakt__path::Path> compiler::Compiler::current_file_path() const {
{
if (((((*this).current_file)).has_value())){
return (((((*this).files))[(((((*this).current_file).value())).id)]));
}
return (JaktInternal::OptionalNone());
}
}

[[noreturn]] ErrorOr<void> compiler::Compiler::panic(DeprecatedString const message) const {
{
MUST((((*this).print_errors())));
utility::panic(message);
}
}

ErrorOr<void> compiler::Compiler::print_errors() const {
{
size_t idx = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<jakt__path::Path> _magic = ((((*this).files)).iterator());
for (;;){
JaktInternal::Optional<jakt__path::Path> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
jakt__path::Path file = (_magic_value.value());
{
JaktInternal::Optional<JaktInternal::DynamicArray<u8>> file_contents = JaktInternal::OptionalNone();
DeprecatedString const file_name = ((file).to_string());
{
JaktInternal::ArrayIterator<error::JaktError> _magic = ((((*this).errors)).iterator());
for (;;){
JaktInternal::Optional<error::JaktError> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
error::JaktError error = (_magic_value.value());
{
utility::Span const span = ((error).span());
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

void compiler::Compiler::dbg_println(DeprecatedString const message) const {
{
if (((*this).debug_print)){
outln(Jakt::DeprecatedString("{}"sv),message);
}
}
}

}
} // namespace Jakt
