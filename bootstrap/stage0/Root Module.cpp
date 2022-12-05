#include "Root Module.h"
namespace Jakt {
ErrorOr<void> format_output(path::Path const file_path,JaktInternal::Array<lexer::Token> const tokens,JaktInternal::Optional<FormatRange> const format_range,bool const format_debug,bool const format_inplace) {
{
StringBuilder formatted_file = TRY((StringBuilder::create()));
bool on_new_line = true;
{
formatter::Formatter _magic = TRY((formatter::Formatter::Formatter::for_tokens(tokens,format_debug,static_cast<size_t>(120ULL))));
for (;;){
JaktInternal::Optional<JaktInternal::Array<formatter::FormattedToken>> _magic_value = TRY((((_magic).next())));
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Array<formatter::FormattedToken> formatted_line = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<formatter::FormattedToken> _magic = ((formatted_line).iterator());
for (;;){
JaktInternal::Optional<formatter::FormattedToken> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
formatter::FormattedToken formatted_token = (_magic_value.value());
{
if ((!(((((((formatted_token).token)).span())).is_in_offset_range((((format_range.value())).start),(((format_range.value())).end)))))){
continue;
}
{
JaktInternal::ArrayIterator<u8> _magic = ((((formatted_token).preceding_trivia)).iterator());
for (;;){
JaktInternal::Optional<u8> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u8 byte = (_magic_value.value());
{
TRY((((formatted_file).append(byte))));
}

}
}

JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((formatted_token).token);
switch(__jakt_match_variant.index()) {
case 56: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Eol>();JaktInternal::Optional<String> const& comment = __jakt_match_value.comment;
{
if (((comment).has_value())){
u8 next_char = ' ';
if (((((comment.value())).length()) != static_cast<size_t>(0ULL))){
(next_char = (((comment.value())).byte_at(static_cast<size_t>(0ULL))));
}
String const space = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<void>>{
auto __jakt_enum_value = (next_char);
if (__jakt_enum_value == ' ') {
return JaktInternal::ExplicitValue(Jakt::String(""));
}
else if (__jakt_enum_value == '\t') {
return JaktInternal::ExplicitValue(Jakt::String(""));
}
else if (__jakt_enum_value == '/') {
return JaktInternal::ExplicitValue(Jakt::String(""));
}
else {
return JaktInternal::ExplicitValue(Jakt::String(" "));
}
}()))
;
String const lhs_space = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<void>>{
auto __jakt_enum_value = (on_new_line);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((indent(((formatted_token).indent)))));
}
else {
return JaktInternal::ExplicitValue(Jakt::String(" "));
}
}()))
;
TRY((((formatted_file).append_string(TRY((String::formatted(Jakt::String("{}//{}{}"),lhs_space,space,(comment.value()))))))));
}
(on_new_line = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 109: {
auto&& __jakt_match_value = __jakt_match_variant.template get<lexer::Token::Garbage>();JaktInternal::Optional<String> const& consumed = __jakt_match_value.consumed;
{
if (((consumed).has_value())){
TRY((((formatted_file).append_string(TRY((String::formatted(Jakt::String("{}"),(consumed.value()))))))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
if (on_new_line){
TRY((((formatted_file).append_string(TRY((String::formatted(Jakt::String("{}"),TRY((indent(((formatted_token).indent)))))))))));
}
TRY((((formatted_file).append_string(TRY((String::formatted(Jakt::String("{}"),TRY((((formatted_token).token_text()))))))))));
(on_new_line = false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
{
JaktInternal::ArrayIterator<u8> _magic = ((((formatted_token).trailing_trivia)).iterator());
for (;;){
JaktInternal::Optional<u8> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u8 byte = (_magic_value.value());
{
TRY((((formatted_file).append_string(TRY((String::formatted(Jakt::String("{:c}"),byte)))))));
}

}
}

if (((((formatted_token).token)).index() == 56 /* Eol */)){
TRY((((formatted_file).append_string(Jakt::String("\n")))));
}
}

}
}

}

}
}

if (format_inplace){
TRY((utility::write_to_file(TRY((((formatted_file).to_string()))),((file_path).to_string()))));
}
else {
out(Jakt::String("{}"),TRY((((formatted_file).to_string()))));
}

}
return {};
}


ErrorOr<String> indent(size_t const level) {
{
String output = Jakt::String("");
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(level)});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += Jakt::String("    "));
}

}
}

return (output);
}
}


String help() {
{
String output = Jakt::String("Flags:\n");
(output += Jakt::String("  -h,--help\t\t\t\tPrint this help and exit.\n"));
(output += Jakt::String("  -O\t\t\t\t\tBuild an optimized executable.\n"));
(output += Jakt::String("  -dl\t\t\t\t\tPrint debug info for the lexer.\n"));
(output += Jakt::String("  -dp\t\t\t\t\tPrint debug info for the parser.\n"));
(output += Jakt::String("  -dt\t\t\t\t\tPrint debug info for the typechecker.\n"));
(output += Jakt::String("  -S\t\t\t\t\tOnly output source (do not build).\n"));
(output += Jakt::String("  -T,--target-triple TARGET\t\tSpecify the target triple used for the build, defaults to native.\n"));
(output += Jakt::String("  --runtime-library-path PATH\t\tSpecify the path to the runtime library.\n"));
(output += Jakt::String("  -J,--jobs NUMBER\t\t\tSpecify the number of jobs to run in parallel, defaults to 2 (1 on windows).\n"));
(output += Jakt::String("  -cr, --compile-run\t\t\tBuild and run an executable file.\n"));
(output += Jakt::String("  -r, --run\t\t\t\tRun the given file without compiling it (all positional arguments after the file name will be passed to main).\n"));
(output += Jakt::String("  -d\t\t\t\t\tInsert debug statement spans in generated C++ code.\n"));
(output += Jakt::String("  --debug-print\t\t\t\tOutput debug print.\n"));
(output += Jakt::String("  -p --prettify-cpp-source\t\tRun emitted C++ source through clang-format.\n"));
(output += Jakt::String("  -S,--emit-cpp-source-only\t\tWrite the C++ source to file, even when not building.\n"));
(output += Jakt::String("  -c,--check-only\t\t\tOnly check the code for errors.\n"));
(output += Jakt::String("  -j,--json-errors\t\t\tEmit machine-readable (JSON) errors.\n"));
(output += Jakt::String("  -H,--type-hints\t\t\tEmit machine-readable type hints (for IDE integration).\n"));
(output += Jakt::String("  -f,--format\t\t\t\tFormat a file or directory and output the result.\n"));
(output += Jakt::String("  -fi,--format-inplace\t\t\t\tFormat a file or directory and save the result inplace.\n"));
(output += Jakt::String("  -fd,--format-debug\t\t\tOutput debug info for the formatter.\n"));
(output += Jakt::String("  -fr,--format-range\t\t\tEmit part of the document with formatting applied.\n"));
(output += Jakt::String("  --try-hints\t\t\t\tEmit machine-readable try hints (for IDE integration).\n"));
(output += Jakt::String("  --repl\t\t\t\tStart a Read-Eval-Print loop session.\n"));
(output += Jakt::String("  --print-symbols\t\t\tEmit a machine-readable (JSON) symbol tree.\n"));
(output += Jakt::String("\nOptions:\n"));
(output += Jakt::String("  -F,--clang-format-path PATH\t\tPath to clang-format executable.\n\t\t\t\t\tDefaults to clang-format\n"));
(output += Jakt::String("  -D,--dot-clang-format-path PATH\tPath to the .clang-format file to use.\n\t\t\t\t\tDefaults to none, invoking clangs default .clang-format file handling.\n"));
(output += Jakt::String("  -R,--runtime-path PATH\t\tPath of the Jakt runtime headers.\n\t\t\t\t\tDefaults to $PWD/runtime.\n"));
(output += Jakt::String("  -B,--binary-dir PATH\t\t\tOutput directory for compiled files.\n\t\t\t\t\tDefaults to $PWD/build.\n"));
(output += Jakt::String("  -C,--cxx-compiler-path PATH\t\tPath of the C++ compiler to use when compiling the generated sources.\n\t\t\t\t\tDefaults to clang++.\n"));
(output += Jakt::String("  -I PATH\t\t\t\tAdd PATH to compiler's include list. Can be specified multiple times.\n"));
(output += Jakt::String("  -L PATH\t\t\t\tAdd PATH to linker's search list. Can be specified multiple times.\n"));
(output += Jakt::String("  -l,--link-with LIB\t\t\tLink executable with LIB. Can be specified multiple times.\n"));
(output += Jakt::String("  -o,--output-filename FILE\t\tName of the output binary.\n\t\t\t\t\tDefaults to the input-filename without the extension.\n"));
(output += Jakt::String("  -g,--goto-def INDEX\t\t\tReturn the span for the definition at index.\n"));
(output += Jakt::String("  -t,--goto-type-def INDEX\t\tReturn the span for the type definition at index.\n"));
(output += Jakt::String("  -e,--hover INDEX\t\t\tReturn the type of element at index.\n"));
(output += Jakt::String("  -m,--completions INDEX\t\tReturn dot completions at index.\n"));
(output += Jakt::String("  --create NAME\t\tCreate sample project in $PWD/NAME\n"));
return (output);
}
}

String usage() {
{
return (Jakt::String("usage: jakt [-h] [OPTIONS] <filename>"));
}
}

ErrorOr<JaktInternal::Optional<FormatRange>> parse_format_range(String const range,size_t const input_file_length) {
{
JaktInternal::Array<String> const parts = TRY((((range).split(':'))));
if (((parts).is_empty())){
return (FormatRange(static_cast<size_t>(0ULL),input_file_length));
}
JaktInternal::Optional<u32> const start_input = ((((parts)[static_cast<i64>(0LL)])).to_uint());
if ((!(((start_input).has_value())))){
return (JaktInternal::OptionalNone());
}
size_t const start = (infallible_integer_cast<size_t>(((start_input.value()))));
size_t const end = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<JaktInternal::Optional<FormatRange>>>{
auto __jakt_enum_value = (((parts).size()));
if (__jakt_enum_value == static_cast<size_t>(1ULL)) {
return JaktInternal::ExplicitValue(input_file_length);
}
else if (__jakt_enum_value == static_cast<size_t>(2ULL)) {
return JaktInternal::ExplicitValue(({ Optional<size_t> __jakt_var_724; {
JaktInternal::Optional<u32> const end_input = ((((parts)[static_cast<i64>(1LL)])).to_uint());
if ((!(((end_input).has_value())))){
return (JaktInternal::OptionalNone());
}
__jakt_var_724 = (infallible_integer_cast<size_t>(((end_input.value())))); goto __jakt_label_661;

}
__jakt_label_661:; __jakt_var_724.release_value(); }));
}
else {
{
return (JaktInternal::OptionalNone());
}
}
}()))
;
return (FormatRange(start,end));
}
}

ErrorOr<int> main(JaktInternal::Array<String> const args) {


            #ifdef _WIN32
            SetConsoleOutputCP(CP_UTF8);
            // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
            setvbuf(stdout, nullptr, _IOFBF, 1000);
            #endif
{
if ((((args).size()) <= static_cast<size_t>(1ULL))){
warnln(Jakt::String("{}"),usage());
return (static_cast<i64>(1LL));
}
jakt__arguments::ArgsParser args_parser = TRY((jakt__arguments::ArgsParser::ArgsParser::from_args(args)));
if (TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-h"), Jakt::String("--help")}))))))))){
outln(Jakt::String("{}\n"),usage());
outln(Jakt::String("{}"),help());
return (static_cast<i64>(0LL));
}
if (TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-v"), Jakt::String("--version")}))))))))){
outln(Jakt::String("unreleased"));
return (static_cast<i64>(0LL));
}
path::Path const current_executable_path = TRY((path::Path::Path::from_string(TRY((File::current_executable_path())))));
path::Path const install_base_path = TRY((((TRY((((current_executable_path).parent())))).parent())));
path::Path const default_runtime_path = TRY((((install_base_path).join(Jakt::String("include/runtime")))));
path::Path const default_runtime_library_path = TRY((((install_base_path).join(Jakt::String("lib")))));
String const default_compiler_path = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<int>>{
auto __jakt_enum_value = (false);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::String("clang-cl"));
}
else {
return JaktInternal::ExplicitValue(Jakt::String("clang++"));
}
}()))
;
bool const optimize = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-O")}))))))));
bool const lexer_debug = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-dl")}))))))));
bool const parser_debug = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-dp")}))))))));
bool const typechecker_debug = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-dt")}))))))));
bool const build_executable = (!(TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-S")}))))))))));
bool const run_executable = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-cr"), Jakt::String("--compile-run")}))))))));
bool const codegen_debug = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-d")}))))))));
bool const debug_print = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("--debug-print")}))))))));
bool const prettify_cpp_source = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-p"), Jakt::String("--prettify-cpp-source")}))))))));
bool const json_errors = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-j"), Jakt::String("--json-errors")}))))))));
bool const dump_type_hints = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-H"), Jakt::String("--type-hints")}))))))));
bool const dump_try_hints = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("--try-hints")}))))))));
bool const check_only = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-c"), Jakt::String("--check-only")}))))))));
bool const write_source_to_file = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-S"), Jakt::String("--emit-cpp-source-only")}))))))));
JaktInternal::Optional<String> const generate_depfile = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-M"), Jakt::String("--dep-file")}))))))));
JaktInternal::Optional<String> const target_triple = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-T"), Jakt::String("--target-triple")}))))))));
String const runtime_library_path = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-RLP"), Jakt::String("--runtime-library-path")})))))))).value_or_lazy_evaluated([&] { return ((default_runtime_library_path).to_string()); });
String compiler_job_count = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-J"), Jakt::String("--jobs")})))))))).value_or_lazy_evaluated([&] { return Jakt::String("2"); });
String const clang_format_path = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-F"), Jakt::String("--clang-format-path")})))))))).value_or_lazy_evaluated([&] { return Jakt::String("clang-format"); });
String const runtime_path = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-R"), Jakt::String("--runtime-path")})))))))).value_or_lazy_evaluated([&] { return ((default_runtime_path).to_string()); });
path::Path const binary_dir = TRY((path::Path::Path::from_string(TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-B"), Jakt::String("--binary-dir")})))))))).value_or_lazy_evaluated([&] { return Jakt::String("build"); }))));
JaktInternal::Optional<String> const dot_clang_format_path = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-D"), Jakt::String("--dot-clang-format-path")}))))))));
String const cxx_compiler_path = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-C"), Jakt::String("--cxx-compiler-path")})))))))).value_or_lazy_evaluated([&] { return default_compiler_path; });
JaktInternal::Optional<String> const archiver_path = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-A"), Jakt::String("--archiver")}))))))));
JaktInternal::Optional<String> const link_archive = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-a"), Jakt::String("--link-archive")}))))))));
JaktInternal::Array<String> const extra_include_paths = TRY((((args_parser).option_multiple((TRY((Array<String>::create_with({Jakt::String("-I")}))))))));
JaktInternal::Array<String> const extra_lib_paths = TRY((((args_parser).option_multiple((TRY((Array<String>::create_with({Jakt::String("-L")}))))))));
JaktInternal::Array<String> const extra_link_libs = TRY((((args_parser).option_multiple((TRY((Array<String>::create_with({Jakt::String("-l")}))))))));
JaktInternal::Optional<String> const set_output_filename = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-o"), Jakt::String("--output-filename")}))))))));
JaktInternal::Optional<String> const goto_def = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-g"), Jakt::String("--goto-def")}))))))));
JaktInternal::Optional<String> const goto_type_def = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-t"), Jakt::String("--goto-type-def")}))))))));
JaktInternal::Optional<String> const hover = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-e"), Jakt::String("--hover")}))))))));
JaktInternal::Optional<String> const completions = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-m"), Jakt::String("--completions")}))))))));
bool const print_symbols = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("--print-symbols")}))))))));
JaktInternal::Optional<String> const project_name = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("--create")}))))))));
bool const interpret_run = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-r"), Jakt::String("--run")}))))))));
bool const format = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-f"), Jakt::String("--format")}))))))));
bool const format_inplace = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-fi"), Jakt::String("--format-inplace")}))))))));
bool const format_debug = TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("-fd"), Jakt::String("--format-debug")}))))))));
String const input_format_range = TRY((((args_parser).option((TRY((Array<String>::create_with({Jakt::String("-fr"), Jakt::String("--format-range")})))))))).value_or_lazy_evaluated([&] { return Jakt::String(""); });
size_t const max_concurrent = (infallible_integer_cast<size_t>((({ Optional<u32> __jakt_var_725;
auto __jakt_var_726 = [&]() -> ErrorOr<u32> { return TRY((value_or_throw<u32>(((compiler_job_count).to_uint())))); }();
if (__jakt_var_726.is_error()) {{
warnln(Jakt::String("error: invalid value for --jobs: {}"),compiler_job_count);
return (static_cast<i64>(1LL));
}
} else {__jakt_var_725 = __jakt_var_726.release_value();
}
__jakt_var_725.release_value(); }))));
if (TRY((((args_parser).flag((TRY((Array<String>::create_with({Jakt::String("--repl")}))))))))){
repl::REPL repl = TRY((repl::REPL::REPL::create(TRY((path::Path::Path::from_parts((TRY((Array<String>::create_with({runtime_path, Jakt::String("jaktlib")}))))))),target_triple)));
TRY((((repl).run())));
return (static_cast<i64>(0LL));
}
JaktInternal::Array<String> const positional_arguments = TRY((((args_parser).remaining_arguments())));
if (((project_name).has_value())){
project::Project const project = project::Project((project_name.value()));
TRY((((project).populate())));
return (static_cast<i64>(0LL));
}
if (false){
(compiler_job_count = Jakt::String("1"));
}
JaktInternal::Optional<String> file_name = JaktInternal::OptionalNone();
bool first_arg = true;
JaktInternal::Array<String> interpreted_main_arguments = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<String> _magic = ((positional_arguments).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String arg = (_magic_value.value());
{
if (first_arg){
(first_arg = false);
continue;
}
if ((!(((file_name).has_value())))){
(file_name = arg);
continue;
}
if ((!(interpret_run))){
warnln(Jakt::String("Extra unknown argument '{}', you can only pass one source file (was '{}')"),arg,file_name);
warnln(Jakt::String("{}"),usage());
return (static_cast<i64>(1LL));
}
TRY((((interpreted_main_arguments).push(arg))));
}

}
}

if ((!(((file_name).has_value())))){
warnln(Jakt::String("you must pass a source file"));
warnln(Jakt::String("{}"),usage());
return (static_cast<i64>(1LL));
}
path::Path const file_path = TRY((path::Path::Path::from_string((file_name.value()))));
String const guessed_output_filename = TRY((((file_path).basename(true))));
String const output_filename = ((TRY((((binary_dir).join(set_output_filename.value_or_lazy_evaluated([&] { return guessed_output_filename; })))))).to_string());
JaktInternal::Array<error::JaktError> errors = (TRY((Array<error::JaktError>::create_with({}))));
NonnullRefPtr<compiler::Compiler> compiler = TRY((compiler::Compiler::create((TRY((Array<path::Path>::create_with({})))),(TRY((Dictionary<String, utility::FileId>::create_with_entries({})))),(TRY((Array<error::JaktError>::create_with({})))),JaktInternal::OptionalNone(),(TRY((Array<u8>::create_with({})))),lexer_debug,parser_debug,false,debug_print,TRY((path::Path::Path::from_parts((TRY((Array<String>::create_with({runtime_path, Jakt::String("jaktlib")}))))))),extra_include_paths,json_errors,dump_type_hints,dump_try_hints,optimize,target_triple)));
TRY((((compiler)->load_prelude())));
if (((format || format_debug) || format_inplace)){
NonnullRefPtr<jakt__file_iterator::RecursiveFileIterator> const directory_or_file_paths = TRY((jakt__file_iterator::RecursiveFileIterator::RecursiveFileIterator::make(file_path,Jakt::String("jakt"))));
{
NonnullRefPtr<jakt__file_iterator::RecursiveFileIterator> _magic = directory_or_file_paths;
for (;;){
JaktInternal::Optional<path::Path> _magic_value = TRY((((_magic)->next())));
if ((!(((_magic_value).has_value())))){
break;
}
path::Path directory_or_file_path = (_magic_value.value());
{
utility::FileId const file_id = TRY((((compiler)->get_file_id_or_register(directory_or_file_path))));
bool const file_is_set = ((compiler)->set_current_file(file_id));
if ((!(file_is_set))){
return (static_cast<i64>(1LL));
}
JaktInternal::Optional<FormatRange> const format_range = TRY((parse_format_range(input_format_range,((((compiler)->current_file_contents)).size()))));
if ((!(((format_range).has_value())))){
warnln(Jakt::String("invalid format range '{}', expected <start>(:<end>?)"),input_format_range);
return (static_cast<i64>(1LL));
}
JaktInternal::Array<lexer::Token> const tokens = TRY((lexer::Lexer::Lexer::lex(compiler)));
TRY((format_output(directory_or_file_path,tokens,format_range,format_debug,format_inplace)));
}

}
}

return (static_cast<i64>(0LL));
}
utility::FileId const main_file_id = TRY((((compiler)->get_file_id_or_register(file_path))));
bool const file_is_set = ((compiler)->set_current_file(main_file_id));
if ((!(file_is_set))){
return (static_cast<i64>(1LL));
}
JaktInternal::Array<lexer::Token> const tokens = TRY((lexer::Lexer::Lexer::lex(compiler)));
if (lexer_debug){
{
JaktInternal::ArrayIterator<lexer::Token> _magic = ((tokens).iterator());
for (;;){
JaktInternal::Optional<lexer::Token> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
outln(Jakt::String("token: {}"),token);
}

}
}

}
parser::ParsedNamespace const parsed_namespace = TRY((parser::Parser::Parser::parse(compiler,tokens)));
if (parser_debug){
outln(Jakt::String("{:#}"),parsed_namespace);
}
if (print_symbols){
JaktInternal::Array<ide::JaktSymbol> const symbols = TRY((ide::find_symbols_in_namespace(parsed_namespace)));
JaktInternal::Array<String> symbol_representations = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<ide::JaktSymbol> _magic = ((symbols).iterator());
for (;;){
JaktInternal::Optional<ide::JaktSymbol> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ide::JaktSymbol symbol = (_magic_value.value());
{
TRY((((symbol_representations).push(TRY((((symbol).to_json())))))));
}

}
}

outln(Jakt::String("[{}]"),utility::join(symbol_representations,Jakt::String(",")));
return (static_cast<i64>(0LL));
}
NonnullRefPtr<types::CheckedProgram> const checked_program = TRY((typechecker::Typechecker::Typechecker::typecheck(compiler,parsed_namespace)));
if (interpret_run){
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((interpreter::Interpreter::Interpreter::create(compiler,checked_program,(TRY((Array<utility::Span>::create_with({})))))));
types::ScopeId const prelude_scope_id = types::ScopeId(types::ModuleId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL));
JaktInternal::Optional<types::FunctionId> main_function_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = ((((checked_program)->modules)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Scope>> _magic = ((((module)->scopes)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Scope>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Scope> scope = (_magic_value.value());
{
if ((!(((((scope)->parent)).map([&](auto& _value) { return _value.equals(prelude_scope_id); })).value_or_lazy_evaluated([&] { return false; })))){
continue;
}
{
JaktInternal::DictionaryIterator<String,JaktInternal::Array<types::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Array<types::FunctionId>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Array<types::FunctionId>> function_name__overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Array<types::FunctionId>> const jakt__function_name__overload_set__ = function_name__overload_set__;
String const function_name = ((jakt__function_name__overload_set__).template get<0>());
JaktInternal::Array<types::FunctionId> const overload_set = ((jakt__function_name__overload_set__).template get<1>());

if ((function_name == Jakt::String("main"))){
(main_function_id = ((overload_set)[static_cast<i64>(0LL)]));
break;
}
}

}
}

if (((main_function_id).has_value())){
break;
}
}

}
}

if (((main_function_id).has_value())){
break;
}
}

}
}

if ((!(((main_function_id).has_value())))){
warnln(Jakt::String("Error: No main function found in program"));
return (static_cast<i64>(1LL));
}
JaktInternal::Array<types::ResolvedNamespace> const namespace_ = (TRY((Array<types::ResolvedNamespace>::create_with({}))));
utility::Span const call_span = utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL));
JaktInternal::Optional<types::CheckedParameter> const first_main_param = ((((((checked_program)->get_function((main_function_id.value()))))->params)).first());
JaktInternal::Array<types::Value> const arguments = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<types::Value>,ErrorOr<int>>{
auto __jakt_enum_value = (((first_main_param).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<types::Value>> __jakt_var_727; {
JaktInternal::Array<types::Value> passed_arguments = (TRY((Array<types::Value>::create_with({types::Value(TRY((types::ValueImpl::template create<typename types::ValueImpl::JaktString>((file_name.value())))),call_span)}))));
{
JaktInternal::ArrayIterator<String> _magic = ((interpreted_main_arguments).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String argument = (_magic_value.value());
{
TRY((((passed_arguments).push(types::Value(TRY((types::ValueImpl::template create<typename types::ValueImpl::JaktString>(argument))),call_span)))));
}

}
}

__jakt_var_727 = (TRY((Array<types::Value>::create_with({types::Value(TRY((types::ValueImpl::template create<typename types::ValueImpl::JaktArray>(passed_arguments,(((((first_main_param.value())).variable)).type_id)))),call_span)})))); goto __jakt_label_662;

}
__jakt_label_662:; __jakt_var_727.release_value(); }));
}
else {
return JaktInternal::ExplicitValue((TRY((Array<types::Value>::create_with({})))));
}
}()))
;
interpreter::ExecutionResult const main_result = TRY((((interpreter)->execute((main_function_id.value()),namespace_,JaktInternal::OptionalNone(),arguments,call_span,JaktInternal::OptionalNone()))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<int>>{
auto&& __jakt_match_variant = main_result;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::ExecutionResult::Return>();
types::Value const& x = __jakt_match_value.value;
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<int>>{
auto&& __jakt_match_variant = *((x).impl);
switch(__jakt_match_variant.index()) {
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CInt>();
int const& ret_val = __jakt_match_value.value;
{
return (ret_val);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I64>();
i64 const& ret_val = __jakt_match_value.value;
{
return (ret_val);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::Void>();
{
return (static_cast<i64>(0LL));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
warnln(Jakt::String("Error: Main function must return an integer"));
return (static_cast<i64>(1LL));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::ExecutionResult::Throw>();
types::Value const& x = __jakt_match_value.value;
{
warnln(Jakt::String("Error: Main function threw: {}"),TRY((repl::serialize_ast_node(TRY((interpreter::value_to_checked_expression(x,interpreter)))))));
return (static_cast<i64>(1LL));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}
if (((goto_def).has_value())){
size_t const index = (infallible_integer_cast<size_t>((((((goto_def.value())).to_uint()).value()))));
utility::Span const result = TRY((ide::find_definition_in_program(checked_program,utility::Span(utility::FileId(static_cast<size_t>(1ULL)),index,index))));
if ((((((result).file_id)).id) == static_cast<size_t>(1ULL))){
outln(Jakt::String("{{\"start\": {}, \"end\": {}}}"),((result).start),((result).end));
}
else {
JaktInternal::Optional<path::Path> const file_path = TRY((((compiler)->get_file_path(((result).file_id)))));
outln(Jakt::String("{{\"start\": {}, \"end\": {}, \"file\": \"{}\"}}"),((result).start),((result).end),TRY((utility::escape_for_quotes((((file_path.value())).to_string())))));
}

return (static_cast<i64>(0LL));
}
if (((goto_type_def).has_value())){
size_t const index = (infallible_integer_cast<size_t>((((((goto_type_def.value())).to_uint()).value()))));
utility::Span const result = TRY((ide::find_type_definition_in_program(checked_program,utility::Span(utility::FileId(static_cast<size_t>(1ULL)),index,index))));
if ((((((result).file_id)).id) == static_cast<size_t>(1ULL))){
outln(Jakt::String("{{\"start\": {}, \"end\": {}}}"),((result).start),((result).end));
}
else {
JaktInternal::Optional<path::Path> const file_path = TRY((((compiler)->get_file_path(((result).file_id)))));
outln(Jakt::String("{{\"start\": {}, \"end\": {}, \"file\": \"{}\"}}"),((result).start),((result).end),TRY((utility::escape_for_quotes((((file_path.value())).to_string())))));
}

return (static_cast<i64>(0LL));
}
if (((hover).has_value())){
size_t const index = (infallible_integer_cast<size_t>((((((hover.value())).to_uint()).value()))));
JaktInternal::Optional<String> const result = TRY((ide::find_typename_in_program(checked_program,utility::Span(utility::FileId(static_cast<size_t>(1ULL)),index,index))));
if (((result).has_value())){
outln(Jakt::String("{{\"hover\": \"{}\"}}"),(result.value()));
}
return (static_cast<i64>(0LL));
}
if (((completions).has_value())){
size_t const index = (infallible_integer_cast<size_t>((((((completions.value())).to_uint()).value()))));
JaktInternal::Array<String> const result = TRY((ide::find_dot_completions(checked_program,utility::Span(utility::FileId(static_cast<size_t>(1ULL)),index,index))));
out(Jakt::String("{{\"completions\": ["));
bool first = true;
{
JaktInternal::ArrayIterator<String> _magic = ((result).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String completion = (_magic_value.value());
{
if ((!(first))){
out(Jakt::String(", "));
}
else {
(first = false);
}

out(Jakt::String("\"{}\""),completion);
}

}
}

outln(Jakt::String("]}}"));
return (static_cast<i64>(0LL));
}
if (typechecker_debug){
outln(Jakt::String("{:#}"),checked_program);
}
TRY((((compiler)->print_errors())));
if ((!(((((compiler)->errors)).is_empty())))){
return (static_cast<i64>(1LL));
}
if (check_only){
return (static_cast<i64>(0LL));
}
JaktInternal::Dictionary<String,JaktInternal::Tuple<String,String>> const codegen_result = TRY((codegen::CodeGenerator::CodeGenerator::generate(compiler,checked_program,codegen_debug)));
StringBuilder depfile_builder = TRY((StringBuilder::create()));
if ((!(((binary_dir).exists())))){
TRY((unknown_fs::make_directory(((binary_dir).to_string()))));
}
{
JaktInternal::DictionaryIterator<String,JaktInternal::Tuple<String,String>> _magic = ((codegen_result).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Tuple<String,String>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Tuple<String,String>> file__contents_and_path__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Tuple<String,String>> const jakt__file__contents_and_path__ = file__contents_and_path__;
String const file = ((jakt__file__contents_and_path__).template get<0>());
JaktInternal::Tuple<String,String> const contents_and_path = ((jakt__file__contents_and_path__).template get<1>());

JaktInternal::Tuple<String,String> const contents_module_file_path_ = contents_and_path;
String const contents = ((contents_module_file_path_).template get<0>());
String const module_file_path = ((contents_module_file_path_).template get<1>());

path::Path const path = TRY((((binary_dir).join(file))));
auto __jakt_var_729 = [&]() -> ErrorOr<void> { return TRY((utility::write_to_file(contents,((path).to_string())))), ErrorOr<void>{}; }();
if (__jakt_var_729.is_error()) {auto error = __jakt_var_729.release_error();
{
warnln(Jakt::String("Error: Could not write to file: {} ({})"),file,error);
return (static_cast<i64>(1LL));
}
}
;
if ((((generate_depfile).has_value()) && ((file).ends_with(Jakt::String(".cpp"))))){
String const escaped = TRY((((file).replace(Jakt::String(" "),Jakt::String("\\ ")))));
String const escaped_module_file_path = TRY((((module_file_path).replace(Jakt::String(" "),Jakt::String("\\ ")))));
TRY((((depfile_builder).append_string(TRY((String::formatted(Jakt::String("{} {}.h: {}"),escaped,TRY((((escaped).substring(static_cast<size_t>(0ULL),(JaktInternal::checked_sub<size_t>(((file).length()),static_cast<size_t>(4ULL))))))),escaped_module_file_path)))))));
TRY((((depfile_builder).append('\n'))));
}
}

}
}

if (((generate_depfile).has_value())){
auto __jakt_var_730 = [&]() -> ErrorOr<void> {{
TRY((utility::write_to_file(TRY((((depfile_builder).to_string()))),(generate_depfile.value()))));
}

;return {};}();
if (__jakt_var_730.is_error()) {auto error = __jakt_var_730.release_error();{
warnln(Jakt::String("Error: Could not write to file list ({})"),error);
return (static_cast<i64>(1LL));
}
};
}
if ((build_executable || run_executable)){
JaktInternal::Array<String> files = (TRY((Array<String>::create_with({}))));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Tuple<String,String>> _magic = ((codegen_result).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Tuple<String,String>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Tuple<String,String>> file_name_____ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Tuple<String,String>> const jakt__file_name_____ = file_name_____;
String const file_name = ((jakt__file_name_____).template get<0>());
JaktInternal::Tuple<String,String> const _ = ((jakt__file_name_____).template get<1>());

if (((file_name).ends_with(Jakt::String(".h")))){
continue;
}
TRY((((files).push(file_name))));
}

}
}

build::Builder builder = TRY((build::Builder::Builder::for_building(files,max_concurrent)));
auto __jakt_var_732 = [&]() -> ErrorOr<void> { return TRY((((builder).build_all(binary_dir,(([cxx_compiler_path, runtime_path, extra_include_paths, optimize](String input_filename, String output_filename) -> ErrorOr<JaktInternal::Array<String>> {
return (TRY((unknown_compiler::run_compiler(cxx_compiler_path,input_filename,output_filename,runtime_path,extra_include_paths,(TRY((Array<String>::create_with({})))),(TRY((Array<String>::create_with({})))),optimize,(TRY((Array<String>::create_with({Jakt::String("-c")}))))))));
}
)))))), ErrorOr<void>{}; }();
if (__jakt_var_732.is_error()) {{
return (static_cast<i64>(1LL));
}
}
;
if (((link_archive).has_value())){
auto __jakt_var_734 = [&]() -> ErrorOr<void> { return TRY((((builder).link_into_archive(archiver_path.value_or_lazy_evaluated([&] { return Jakt::String("ar"); }),(link_archive.value()))))), ErrorOr<void>{}; }();
if (__jakt_var_734.is_error()) {{
return (static_cast<i64>(1LL));
}
}
;
}
else {
JaktInternal::Array<String> extra_arguments = (TRY((Array<String>::create_with({}))));
path::Path const runtime_lib_path = TRY((path::Path::Path::from_string(runtime_library_path)));
TRY((((extra_arguments).push(((TRY((((runtime_lib_path).join(Jakt::String("libjakt_main.a")))))).to_string())))));
TRY((((extra_arguments).push(((TRY((((runtime_lib_path).join(Jakt::String("libjakt_runtime.a")))))).to_string())))));
{
JaktInternal::ArrayIterator<String> _magic = ((extra_lib_paths).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String path = (_magic_value.value());
{
TRY((((extra_arguments).push(Jakt::String("-L")))));
TRY((((extra_arguments).push(path))));
}

}
}

{
JaktInternal::ArrayIterator<String> _magic = ((extra_link_libs).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String lib = (_magic_value.value());
{
TRY((((extra_arguments).push(Jakt::String("-l")))));
TRY((((extra_arguments).push(lib))));
}

}
}

if ((false && (TRY((((TRY((path::Path::Path::from_string(cxx_compiler_path)))).basename(false)))) == Jakt::String("clang-cl")))){
TRY((((extra_arguments).push(Jakt::String("/link")))));
TRY((((extra_arguments).push(Jakt::String("/subsystem:console")))));
}
auto __jakt_var_736 = [&]() -> ErrorOr<void> { return TRY((((builder).link_into_executable(cxx_compiler_path,output_filename,extra_arguments)))), ErrorOr<void>{}; }();
if (__jakt_var_736.is_error()) {{
return (static_cast<i64>(1LL));
}
}
;
}

}
if (run_executable){
return (system(((output_filename).c_string())));
}
}
return 0;
}

ErrorOr<String> FormatRange::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("FormatRange("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("start: "));TRY(builder.appendff("{}, ", start));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("end: "));TRY(builder.appendff("{}", end));
}
TRY(builder.append(")"));return builder.to_string(); }
FormatRange::FormatRange(size_t a_start, size_t a_end) :start(a_start), end(a_end){}

} // namespace Jakt
