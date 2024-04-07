#include "compiler.h"
namespace Jakt {
namespace compiler {
ByteString compiler::Compiler::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Compiler("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("files: {}, ", files);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("file_ids: {}, ", file_ids);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("errors: {}, ", errors);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_file: {}, ", current_file);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_file_contents: {}, ", current_file_contents);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dump_lexer: {}, ", dump_lexer);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dump_parser: {}, ", dump_parser);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("ignore_parser_errors: {}, ", ignore_parser_errors);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("debug_print: {}, ", debug_print);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("std_include_path: {}, ", std_include_path);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("include_paths: {}, ", include_paths);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("json_errors: {}, ", json_errors);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dump_type_hints: {}, ", dump_type_hints);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dump_try_hints: {}, ", dump_try_hints);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("optimize: {}, ", optimize);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("target_triple: {}, ", target_triple);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("user_configuration: {}, ", user_configuration);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("binary_dir: {}, ", binary_dir);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("assume_main_file_path: {}", assume_main_file_path);
}
builder.append(")"sv);return builder.to_string(); }
[[noreturn]] void compiler::Compiler::panic(ByteString const message) const {
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
JaktInternal::Optional<jakt__path::Path> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
jakt__path::Path file = (_magic_value.value());
{
JaktInternal::Optional<JaktInternal::DynamicArray<u8>> file_contents = JaktInternal::OptionalNone();
ByteString const file_name = ((file).to_string());
{
JaktInternal::ArrayIterator<error::JaktError> _magic = ((((*this).errors)).iterator());
for (;;){
JaktInternal::Optional<error::JaktError> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
error::JaktError error = (_magic_value.value());
{
utility::Span const span = ((error).span());
if (((((((span).file_id)).id)) == (idx))){
if (((*this).json_errors)){
error::print_error_json(file_name,error);
}
else {
if ((!(((file_contents).has_value())))){
auto __jakt_var_2 = [&]() -> ErrorOr<void> {{
NonnullRefPtr<File> file = TRY((File::open_for_reading(file_name)));
(file_contents = TRY((((file)->read_all()))));
}

;return {};}();
if (__jakt_var_2.is_error()) {auto error = __jakt_var_2.release_error();{
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

JaktInternal::Optional<jakt__path::Path> compiler::Compiler::get_file_path(utility::FileId const file_id) const {
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((file_id).id),((((*this).files)).size()))){
return JaktInternal::OptionalNone();
}
return ((((*this).files))[((file_id).id)]);
}
}

JaktInternal::Optional<utility::FileId> compiler::Compiler::current_file_id() const {
{
return ((*this).current_file);
}
}

JaktInternal::Optional<jakt__path::Path> compiler::Compiler::current_file_path() const {
{
if (((((*this).current_file)).has_value())){
return ((((*this).files))[(((((*this).current_file).value())).id)]);
}
return JaktInternal::OptionalNone();
}
}

utility::FileId compiler::Compiler::get_file_id_or_register(jakt__path::Path const file) {
{
ByteString const path = ((file).to_string());
JaktInternal::Optional<utility::FileId> file_id = ((((*this).file_ids)).get(path));
if (((file_id).has_value())){
return (file_id.value());
}
((((*this).files)).push(file));
(file_id = utility::FileId(JaktInternal::checked_sub(((((*this).files)).size()),static_cast<size_t>(1ULL))));
((((*this).file_ids)).set(path,(file_id.value())));
return (file_id.value());
}
}

ErrorOr<bool> compiler::Compiler::set_current_file(utility::FileId const file_id) {
{
i32 const ErrNOENT = static_cast<i32>(2);
i32 const ErrACCES = static_cast<i32>(13);
i32 const ErrFBIG = static_cast<i32>(27);
i32 const ErrNAMETOOLONG = static_cast<i32>(36);
JaktInternal::Optional<utility::FileId> const old_file_id = ((*this).current_file);
(((*this).current_file) = file_id);
auto __jakt_var_3 = [&]() -> ErrorOr<void> {{
NonnullRefPtr<File> file = TRY((File::open_for_reading(((((((*this).files))[((file_id).id)])).to_string()))));
(((*this).current_file_contents) = TRY((((file)->read_all()))));
}

;return {};}();
if (__jakt_var_3.is_error()) {auto error = __jakt_var_3.release_error();{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<bool>> {
auto __jakt_enum_value = (((error).code()));
if (__jakt_enum_value == ErrNOENT) {
return (warnln((StringView::from_string_literal("\u001b[31;1mError\u001b[0m Could not access {}: File not found"sv)),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrACCES) {
return (warnln((StringView::from_string_literal("\u001b[31;1mError\u001b[0m Could not access {}: Permission denied"sv)),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrFBIG) {
return (warnln((StringView::from_string_literal("\u001b[31;1mError\u001b[0m Could not access {}: File too big"sv)),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == ErrNAMETOOLONG) {
return (warnln((StringView::from_string_literal("\u001b[31;1mError\u001b[0m Could not access {}: Name too long"sv)),((((*this).files))[((file_id).id)]))), JaktInternal::ExplicitValue<void>();
}
else {
{
utility::panic((ByteString::from_utf8_without_validation("Incurred unrecognized error while trying to open file"sv)));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((*this).current_file) = old_file_id);
return false;
}
};
return true;
}
}

JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> compiler::Compiler::current_file_state() const {
{
return (Tuple{((*this).current_file), ((*this).current_file_contents)});
}
}

void compiler::Compiler::restore_file_state(JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> const state) {
{
(((*this).current_file) = ((state).template get<0>()));
(((*this).current_file_contents) = ((state).template get<1>()));
}
}

void compiler::Compiler::dbg_println(ByteString const message) const {
{
if (((*this).debug_print)){
outln((StringView::from_string_literal("{}"sv)),message);
}
}
}

ErrorOr<void> compiler::Compiler::load_prelude() {
{
ByteString const module_name = (ByteString::from_utf8_without_validation("__prelude__"sv));
jakt__path::Path const file_name = jakt__path::Path::from_string(module_name);
((*this).get_file_id_or_register(file_name));
}
return {};
}

ErrorOr<JaktInternal::Optional<jakt__path::Path>> compiler::Compiler::search_for_path(ByteString const input_module_name,bool const relative_import,size_t const parent_path_count) const {
{
ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append(static_cast<u8>(47)));
ByteString const separator = ((builder).to_string());
ByteString const module_name = ((input_module_name).replace((ByteString::from_utf8_without_validation("::"sv)),separator));
if ((!(relative_import))){
{
JaktInternal::ArrayIterator<ByteString> _magic = ((((*this).include_paths)).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString include_path = (_magic_value.value());
{
jakt__path::Path const candidate_path = jakt__path::Path::from_parts(DynamicArray<ByteString>::create_with({include_path, ((module_name) + ((ByteString::from_utf8_without_validation(".jakt"sv))))}));
if (((candidate_path).exists())){
return candidate_path;
}
}

}
}

}
ByteString const standard_module_name = (ByteString::from_utf8_without_validation("jakt"sv));
if (((module_name).starts_with(standard_module_name))){
ByteString const std_module_name_path = ((module_name).substring(JaktInternal::checked_add(((standard_module_name).length()),static_cast<size_t>(1ULL)),JaktInternal::checked_sub(((module_name).length()),JaktInternal::checked_add(((standard_module_name).length()),static_cast<size_t>(1ULL)))));
jakt__path::Path const candidate_path = jakt__path::Path::from_parts(DynamicArray<ByteString>::create_with({((((*this).std_include_path)).to_string()), ((std_module_name_path) + ((ByteString::from_utf8_without_validation(".jakt"sv))))}));
if (((candidate_path).exists())){
return candidate_path;
}
}
return ((((*this).find_in_search_paths(jakt__path::Path::from_string(((module_name) + ((ByteString::from_utf8_without_validation(".jakt"sv))))),relative_import,parent_path_count))));
}
}

ErrorOr<JaktInternal::Optional<jakt__path::Path>> compiler::Compiler::find_in_search_paths(jakt__path::Path const path,bool const relative_import,size_t const parent_path_count) const {
{
{
JaktInternal::ArrayIterator<ByteString> _magic = ((((*this).include_paths)).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString include_path = (_magic_value.value());
{
jakt__path::Path const candidate_path = ((jakt__path::Path::from_string(include_path)).join(path));
if (((candidate_path).exists())){
return candidate_path;
}
}

}
}

JaktInternal::Optional<jakt__path::Path> const current_file_path = ((*this).assume_main_file_path).value_or_lazy_evaluated_optional([&] { return ((*this).current_file_path()); });
if (((current_file_path).has_value())){
jakt__path::Path candidate_path = ((((TRY(((((current_file_path.value())).absolute())))).parent())).join(path));
if ((relative_import && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(parent_path_count,static_cast<size_t>(0ULL)))){
size_t parent_count = parent_path_count;
jakt__path::Path parent = ((candidate_path).parent());
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(parent_count,static_cast<size_t>(0ULL))){
(parent = ((parent).parent()));
((parent_count--));
}
(candidate_path = ((parent).join(path)));
}
if (((candidate_path).exists())){
return candidate_path;
}
}
return JaktInternal::OptionalNone();
}
}

compiler::Compiler::Compiler(JaktInternal::DynamicArray<jakt__path::Path> a_files, JaktInternal::Dictionary<ByteString,utility::FileId> a_file_ids, JaktInternal::DynamicArray<error::JaktError> a_errors, JaktInternal::Optional<utility::FileId> a_current_file, JaktInternal::DynamicArray<u8> a_current_file_contents, bool a_dump_lexer, bool a_dump_parser, bool a_ignore_parser_errors, bool a_debug_print, jakt__path::Path a_std_include_path, JaktInternal::DynamicArray<ByteString> a_include_paths, bool a_json_errors, bool a_dump_type_hints, bool a_dump_try_hints, bool a_optimize, JaktInternal::Optional<ByteString> a_target_triple, JaktInternal::Dictionary<ByteString,ByteString> a_user_configuration, jakt__path::Path a_binary_dir, JaktInternal::Optional<jakt__path::Path> a_assume_main_file_path): files(move(a_files)), file_ids(move(a_file_ids)), errors(move(a_errors)), current_file(move(a_current_file)), current_file_contents(move(a_current_file_contents)), dump_lexer(move(a_dump_lexer)), dump_parser(move(a_dump_parser)), ignore_parser_errors(move(a_ignore_parser_errors)), debug_print(move(a_debug_print)), std_include_path(move(a_std_include_path)), include_paths(move(a_include_paths)), json_errors(move(a_json_errors)), dump_type_hints(move(a_dump_type_hints)), dump_try_hints(move(a_dump_try_hints)), optimize(move(a_optimize)), target_triple(move(a_target_triple)), user_configuration(move(a_user_configuration)), binary_dir(move(a_binary_dir)), assume_main_file_path(move(a_assume_main_file_path)){}
NonnullRefPtr<Compiler> compiler::Compiler::__jakt_create(JaktInternal::DynamicArray<jakt__path::Path> files, JaktInternal::Dictionary<ByteString,utility::FileId> file_ids, JaktInternal::DynamicArray<error::JaktError> errors, JaktInternal::Optional<utility::FileId> current_file, JaktInternal::DynamicArray<u8> current_file_contents, bool dump_lexer, bool dump_parser, bool ignore_parser_errors, bool debug_print, jakt__path::Path std_include_path, JaktInternal::DynamicArray<ByteString> include_paths, bool json_errors, bool dump_type_hints, bool dump_try_hints, bool optimize, JaktInternal::Optional<ByteString> target_triple, JaktInternal::Dictionary<ByteString,ByteString> user_configuration, jakt__path::Path binary_dir, JaktInternal::Optional<jakt__path::Path> assume_main_file_path) { auto o = adopt_ref(*new Compiler (move(files), move(file_ids), move(errors), move(current_file), move(current_file_contents), move(dump_lexer), move(dump_parser), move(ignore_parser_errors), move(debug_print), move(std_include_path), move(include_paths), move(json_errors), move(dump_type_hints), move(dump_try_hints), move(optimize), move(target_triple), move(user_configuration), move(binary_dir), move(assume_main_file_path))); return o; }
}
} // namespace Jakt
