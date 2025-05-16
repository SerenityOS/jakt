#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "main.h"
#include "ids.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
ByteString usage() {
{
return ByteString::from_utf8_without_validation("usage: jakt [cross] [-h] [OPTIONS] <filename>"sv);
}
}

ByteString help() {
{
ByteString output = ByteString::from_utf8_without_validation(""sv);
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("Non-cross mode:\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("= General:\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -h,--help\t\t\t\tPrint this help and exit.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -v,--version\t\t\t\tPrint the compiler's version and exit.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -cr,--compile-run\t\t\tBuild and run an executable file.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -r,--run\t\t\t\tRun the given file without compiling it (all positional arguments after the file name will be passed to main).\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --repl\t\t\t\tStart a Read-Eval-Print loop session.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --create NAME\t\t\t\tCreate sample project in $PWD/NAME\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("= Compilation:\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --config KEY=VALUE\t\t\tSet a user configuration value.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -c,--check-only\t\t\tOnly check the code for errors.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -d\t\t\t\t\tInsert debug statement spans in generated C++ code.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -O\t\t\t\t\tBuild an optimized executable.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -S,--emit-cpp-source-only\t\tOnly output source (do not build).\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --ak-is-my-only-stdlib\t\tForget about interop, AK is the one and only STL.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --cxx-compiler-path PATH\t\tPath of the C++ compiler to use when compiling the generated sources.\n\t\t\t\t\tDefaults to clang++.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -M,--dep-file FILE\t\t\tEmit a depfile listing dependencies of the main output.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --extra-cpp-flagFLAG\t\t\tPass FLAG to the compiler. Can be specified multiple times.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --use-ccache\t\t\t\tUse ccache when compiling.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -o,--output-filename FILE\t\tName of the output binary.\n\t\t\t\t\tDefaults to the input-filename without the extension.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -B,--binary-dir PATH\t\t\tOutput directory for compiled files.\n\t\t\t\t\tDefaults to $PWD/build.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -E,--exports-dir PATH\t\t\tOutput directory for exported files, relative to $PWD.\n\t\t\t\t\tDefaults to '$PWD/exports'.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -I PATH\t\t\t\tAdd PATH to compiler's include list. Can be specified multiple times.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -J,--jobs NUMBER\t\t\tSpecify the number of jobs to run in parallel, defaults to 2 (1 on windows).\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -L PATH\t\t\t\tAdd PATH to linker's search list. Can be specified multiple times.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -l,--link-with LIB\t\t\tLink executable with LIB. Can be specified multiple times.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -T,--target-triple TARGET\t\tSpecify the target triple used for the build, defaults to native.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -WlARG\t\t\t\tPass ARG to the linker. Can be specified multiple times.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -X FILE\t\t\t\tPass FILE to the compiler. Can be specified multiple times.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("= Debugging:\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -dl\t\t\t\t\tPrint debug info for the lexer.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -dp\t\t\t\t\tPrint debug info for the parser.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -dt\t\t\t\t\tPrint debug info for the typechecker.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -fd,--format-debug\t\t\tOutput debug info for the formatter.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -p,--prettify-cpp-source\t\tRun emitted C++ source through clang-format.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -D,--dot-clang-format-path PATH\tPath to the .clang-format file to use.\n\t\t\t\t\tDefaults to none, invoking clangs default .clang-format file handling.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -F,--clang-format-path PATH\t\tPath to clang-format executable.\n\t\t\t\t\tDefaults to clang-format\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --debug-print\t\t\t\tOutput debug print.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --debug-print-cpp-import\t\t\t\tOutput debug print for the c++ import processor.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("= Formatting:\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -f,--format\t\t\t\tFormat a file or directory and output the result.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -fi,--format-inplace\t\t\tFormat a file or directory and save the result inplace.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -fr,--format-range RANGE\t\tEmit part of the document with formatting applied.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("= IDE integration:\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -e,--hover INDEX\t\t\tReturn the type of element at index.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -g,--goto-def INDEX\t\t\tReturn the span for the definition at index.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -H,--type-hints\t\t\tEmit machine-readable type hints (for IDE integration).\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -m,--completions INDEX\t\tReturn dot completions at index.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --print-symbols\t\t\tEmit a machine-readable (JSON) symbol tree.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --try-hints\t\t\t\tEmit machine-readable try hints (for IDE integration).\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -t,--goto-type-def INDEX\t\tReturn the span for the type definition at index.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("= Misc:\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --discover\t\t\t\tDiscover all files in the project, print the dependencies and outputs, then exit.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -j,--json-errors\t\t\tEmit machine-readable (JSON) errors.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --runtime-library-path PATH\t\tSpecify the path to the runtime library.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --runtime-path PATH\t\t\tSpecify the path to the host runtime headers.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -R,--runtime-path PATH\t\tPath of the Jakt runtime headers.\n\t\t\t\t\tDefaults to $PWD/runtime.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --assume-main-file-path PATH\t\tAssume the main file is at PATH.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("\nCross mode:\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("All other given options and flags will be passed to the compiler invocation verbatim.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --source-file PATH\t\t\tSpecify the path to the source file to compile.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  -T,--target-triple TARGET\t\tSpecify the target triple used for the build, defaults to native.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --sysroot PATH\t\t\tSpecify the sysroot used for the build.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --system-include-dir PATH\t\tSpecify a system include directory to use.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --system-lib-dir PATH\t\t\tSpecify a system library directory to use.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --compiler-include-dir PATH\t\tSpecify a compiler include directory to use.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --compiler-lib-dir PATH\t\tSpecify a compiler library directory to use.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --install-root PATH\t\t\tSpecify the root directory to install to.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --only-support-libs\t\t\tOnly build and install support libraries for the target platform.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --target-links-ak\t\t\t\tAssume AK will be provided by the target platform.\n"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("  --runtime-lib-path PATH\t\tSpecify the path to the host runtime library.\n"sv));
return output;
}
}

ByteString indent(size_t const level) {
{
ByteString output = ByteString::from_utf8_without_validation(""sv);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(level)};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("    "sv));
}

}
}

return output;
}
}

JaktInternal::Optional<Jakt::FormatRange> parse_format_range(ByteString const range,size_t const input_file_length) {
{
JaktInternal::DynamicArray<ByteString> const parts = range.split(':');
if (parts.is_empty()){
return Jakt::FormatRange(static_cast<size_t>(0ULL),input_file_length);
}
JaktInternal::Optional<u32> const start_input = parts[static_cast<i64>(0LL)].template to_number<u32>();
if (!start_input.has_value()){
return JaktInternal::OptionalNone();
}
size_t const start = infallible_integer_cast<size_t>(start_input.value());
size_t const end = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, JaktInternal::Optional<Jakt::FormatRange>>{
auto __jakt_enum_value = parts.size();
if (__jakt_enum_value == static_cast<size_t>(1ULL)) {return JaktInternal::ExplicitValue(input_file_length);
}else if (__jakt_enum_value == static_cast<size_t>(2ULL)) {{
JaktInternal::Optional<u32> const end_input = parts[static_cast<i64>(1LL)].template to_number<u32>();
if (!end_input.has_value()){
return JaktInternal::OptionalNone();
}
return JaktInternal::ExplicitValue<size_t>(infallible_integer_cast<size_t>(end_input.value()));
}
VERIFY_NOT_REACHED();
}else {{
return JaktInternal::OptionalNone();
}
}}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Jakt::FormatRange(start,end);
}
}

ErrorOr<int> main(JaktInternal::DynamicArray<ByteString> const args) {


            #ifdef _WIN32
            #ifndef CP_UTF8
            static constexpr unsigned int CP_UTF8 = 65001;
            #endif
            SetConsoleOutputCP(CP_UTF8);
            // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
            setvbuf(stdout, nullptr, _IOFBF, 1000);
            #endif
{
if (args.size() <= static_cast<size_t>(1ULL)){
warnln(StringView::from_string_literal("{}"sv),Jakt::usage());
return static_cast<int>(1);
}
if (args[static_cast<i64>(1LL)] == ByteString::from_utf8_without_validation("cross"sv)){
return Jakt::selfhost_crosscompiler_main(args);
}
return Jakt::compiler_main(args);
}
return 0;
}

ErrorOr<void> install(Jakt::jakt__path::Path const from,Jakt::jakt__path::Path const to) {
{
AK::Queue<JaktInternal::Tuple<Jakt::jakt__path::Path,Jakt::jakt__path::Path>> directories_to_copy = AK::Queue<JaktInternal::Tuple<Jakt::jakt__path::Path,Jakt::jakt__path::Path>>();
directories_to_copy.enqueue(Tuple{from, Jakt::jakt__path::Path::from_string(ByteString::from_utf8_without_validation("."sv))});
while (!directories_to_copy.is_empty()){
JaktInternal::Tuple<Jakt::jakt__path::Path,Jakt::jakt__path::Path> const directory_relative_dir_ = directories_to_copy.dequeue();
Jakt::jakt__path::Path const directory = directory_relative_dir_.template get<0>();
Jakt::jakt__path::Path const relative_dir = directory_relative_dir_.template get<1>();

{
NonnullRefPtr<Jakt::jakt__platform__unknown_fs::DirectoryIterator> _magic = TRY((Jakt::jakt__platform__unknown_fs::DirectoryIterator::from_path(directory))).value();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::jakt__path::Path,bool>> const _magic_value = TRY((_magic->next()));
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::jakt__path::Path,bool> entry__is_directory__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::jakt__path::Path,bool> const jakt__entry__is_directory__ = entry__is_directory__;
Jakt::jakt__path::Path const entry = jakt__entry__is_directory__.template get<0>();
bool const is_directory = jakt__entry__is_directory__.template get<1>();

Jakt::jakt__path::Path const path = directory.join(entry);
Jakt::jakt__path::Path const path_relative_to_target = relative_dir.join(entry);
if (is_directory){
auto __jakt_var_160 = [&]() -> ErrorOr<void> { return TRY((Jakt::jakt__platform__unknown_fs::make_directory(to.join(path_relative_to_target.to_string()).to_string()))), ErrorOr<void>{}; }();
;
directories_to_copy.enqueue(Tuple{path, path_relative_to_target});
continue;
}
auto __jakt_var_162 = [&]() -> ErrorOr<void> { return TRY((Jakt::mkdir_p(to.join(path_relative_to_target.to_string()).parent()))), ErrorOr<void>{}; }();
;
Jakt::jakt__path::Path const target_path = to.join(path_relative_to_target.to_string());
NonnullRefPtr<File> input_file = TRY((File::open_for_reading(path.to_string())));
NonnullRefPtr<File> output_file = TRY((File::open_for_writing(target_path.to_string())));
JaktInternal::DynamicArray<u8> buffer = DynamicArray<u8>::filled(static_cast<i64>(4096LL), static_cast<u8>(0));
while (true){
size_t const bytes_read = TRY((input_file->read(buffer)));
if (bytes_read == static_cast<size_t>(0ULL)){
break;
}
size_t bytes_written = static_cast<size_t>(0ULL);
while (bytes_written < bytes_read){
bytes_written += TRY((output_file->write(buffer[JaktInternal::Range<size_t>{static_cast<size_t>(bytes_written),static_cast<size_t>(bytes_read)}].to_array())));
}
if (bytes_written != bytes_read){
return Error::__jakt_from_string_literal(StringView::from_string_literal("Failed to write to file"sv));
}
}
}

}
}

}
}
return {};
}

ErrorOr<int> selfhost_crosscompiler_main(JaktInternal::DynamicArray<ByteString> const args) {
{
JaktInternal::DynamicArray<ByteString> compiler_args = DynamicArray<ByteString>::create_with({});
JaktInternal::Optional<ByteString> target_triple = JaktInternal::OptionalNone();
JaktInternal::Optional<ByteString> sysroot = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<ByteString> system_lib_dirs = DynamicArray<ByteString>::create_with({});
JaktInternal::DynamicArray<ByteString> system_include_dirs = DynamicArray<ByteString>::create_with({});
JaktInternal::Optional<ByteString> compiler_include_dir = JaktInternal::OptionalNone();
JaktInternal::Optional<ByteString> compiler_lib_dir = JaktInternal::OptionalNone();
JaktInternal::Optional<ByteString> install_root = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::jakt__path::Path> runtime_lib_path = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::jakt__path::Path> runtime_path = JaktInternal::OptionalNone();
JaktInternal::Optional<ByteString> source_file = JaktInternal::OptionalNone();
JaktInternal::Optional<ByteString> output_filename = JaktInternal::OptionalNone();
bool only_support_libs = false;
bool target_links_ak = false;
AK::Queue<ByteString> args_to_process = AK::Queue<ByteString>();
{
JaktInternal::ArrayIterator<ByteString> _magic = args[JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)}].iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString arg = _magic_value.value();
{
args_to_process.enqueue(arg);
}

}
}

while (!args_to_process.is_empty()){
ByteString const arg = args_to_process.dequeue();
{auto __jakt_enum_value = arg;
if ((__jakt_enum_value == ByteString::from_utf8_without_validation("--target-triple"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("-T"sv))) {{
target_triple = args_to_process.dequeue();
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--sysroot"sv)) {{
sysroot = args_to_process.dequeue();
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--system-lib-dir"sv)) {{
system_lib_dirs.push(args_to_process.dequeue());
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--system-include-dir"sv)) {{
system_include_dirs.push(args_to_process.dequeue());
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--compiler-include-dir"sv)) {{
compiler_include_dir = args_to_process.dequeue();
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--compiler-lib-dir"sv)) {{
compiler_lib_dir = args_to_process.dequeue();
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--install-root"sv)) {{
install_root = args_to_process.dequeue();
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--runtime-lib-path"sv)) {{
runtime_lib_path = Jakt::jakt__path::Path::from_string(args_to_process.dequeue());
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--runtime-path"sv)) {{
runtime_path = Jakt::jakt__path::Path::from_string(args_to_process.dequeue());
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--source-file"sv)) {{
source_file = args_to_process.dequeue();
}
goto __jakt_label_203;}else if ((__jakt_enum_value == ByteString::from_utf8_without_validation("--output-filename"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("-o"sv))) {{
output_filename = args_to_process.dequeue();
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--target-links-ak"sv)) {{
target_links_ak = true;
}
goto __jakt_label_203;}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("--only-support-libs"sv)) {{
only_support_libs = true;
}
goto __jakt_label_203;}else {{
compiler_args.push(arg);
}
goto __jakt_label_203;}}goto __jakt_label_203; __jakt_label_203:;;
}
if (!source_file.has_value() && (!only_support_libs)){
warnln(StringView::from_string_literal("error: Expected --source_file to be passed"sv));
return static_cast<int>(1);
}
if (!install_root.has_value()){
warnln(StringView::from_string_literal("error: Expected --install-root to be passed"sv));
return static_cast<int>(1);
}
if (!target_triple.has_value()){
warnln(StringView::from_string_literal("error: Expected --target-triple to be passed"sv));
return static_cast<int>(1);
}
ByteString const abbreviated_triple = TRY((TRY((Jakt::jakt__platform::Target::from_triple(target_triple.value()))).name(true)));
Jakt::jakt__path::Path const install_dir = Jakt::jakt__path::Path::from_string(install_root.value());
Jakt::jakt__path::Path const install_lib_dir = install_dir.join(ByteString::from_utf8_without_validation("lib"sv)).join(target_triple.value());
Jakt::jakt__path::Path const install_runtime_dir = install_dir.join(ByteString::from_utf8_without_validation("include/runtime"sv));
Jakt::jakt__path::Path const install_bin_dir = install_dir.join(ByteString::from_utf8_without_validation("bin"sv));
Jakt::jakt__path::Path const current_executable_path = Jakt::jakt__path::Path::from_string(TRY((File::current_executable_path())));
Jakt::jakt__path::Path const local_install_base_path = current_executable_path.parent().parent();
if (!runtime_path.has_value()){
runtime_path = local_install_base_path.join(ByteString::from_utf8_without_validation("include/runtime"sv));
}
if (!runtime_lib_path.has_value()){
runtime_lib_path = local_install_base_path.join(ByteString::from_utf8_without_validation("lib"sv)).join(TRY((TRY((Jakt::jakt__platform::Target::active())).name(false))));
}
Function<JaktInternal::DynamicArray<ByteString>()> const compiler_invocation_args = [&compiler_args, &abbreviated_triple, &sysroot, &compiler_include_dir, &compiler_lib_dir, &system_include_dirs, &system_lib_dirs, &runtime_lib_path, &runtime_path]() -> JaktInternal::DynamicArray<ByteString> {{
JaktInternal::DynamicArray<ByteString> args = compiler_args[JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}].to_array();
args.push(ByteString::from_utf8_without_validation("--target-triple"sv));
args.push(__jakt_format(StringView::from_string_literal("{}-unknown"sv),abbreviated_triple));
if (sysroot.has_value()){
args.push(ByteString::from_utf8_without_validation("--extra-cpp-flag"sv));
args.push(__jakt_format(StringView::from_string_literal("--sysroot={}"sv),sysroot.value()));
}
if (compiler_include_dir.has_value()){
args.push(ByteString::from_utf8_without_validation("-I"sv));
args.push(compiler_include_dir.value());
}
if (compiler_lib_dir.has_value()){
args.push(ByteString::from_utf8_without_validation("-L"sv));
args.push(compiler_lib_dir.value());
}
{
JaktInternal::ArrayIterator<ByteString> _magic = system_include_dirs.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString system_include_dir = _magic_value.value();
{
args.push(ByteString::from_utf8_without_validation("-I"sv));
args.push(system_include_dir);
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = system_lib_dirs.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString system_lib_dir = _magic_value.value();
{
args.push(ByteString::from_utf8_without_validation("-L"sv));
args.push(system_lib_dir);
}

}
}

if (runtime_lib_path.has_value()){
args.push(ByteString::from_utf8_without_validation("--runtime-library-path"sv));
args.push(runtime_lib_path.value().to_string());
}
if (runtime_path.has_value()){
args.push(ByteString::from_utf8_without_validation("--runtime-path"sv));
args.push(runtime_path.value().to_string());
}
return args;
}
}
;
if (!install_lib_dir.exists()){
TRY((Jakt::mkdir_p(install_lib_dir)));
}
TRY((Jakt::install(runtime_path.value(),install_runtime_dir)));
if (!install_bin_dir.exists()){
TRY((Jakt::mkdir_p(install_bin_dir)));
}
Jakt::jakt__path::Path const runtime_archive_path = install_lib_dir.join(__jakt_format(StringView::from_string_literal("libjakt_runtime_{}.a"sv),target_triple.value()));
Jakt::jakt__path::Path const main_archive_path = install_lib_dir.join(__jakt_format(StringView::from_string_literal("libjakt_main_{}.a"sv),target_triple.value()));
Function<ErrorOr<int>(JaktInternal::DynamicArray<Jakt::jakt__path::Path>, Jakt::jakt__path::Path)> const build_archive = [&compiler_invocation_args](JaktInternal::DynamicArray<Jakt::jakt__path::Path> sources, Jakt::jakt__path::Path target) -> ErrorOr<int> {{
JaktInternal::DynamicArray<ByteString> invocation_args = compiler_invocation_args();
{
JaktInternal::ArrayIterator<Jakt::jakt__path::Path> _magic = sources.iterator();
for (;;){
JaktInternal::Optional<Jakt::jakt__path::Path> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::jakt__path::Path source = _magic_value.value();
{
invocation_args.push(ByteString::from_utf8_without_validation("-X"sv));
invocation_args.push(source.to_string());
}

}
}

invocation_args.push(ByteString::from_utf8_without_validation("--static"sv));
invocation_args.push(ByteString::from_utf8_without_validation("--link-archive"sv));
invocation_args.push(target.to_string());
invocation_args.push(ByteString::from_utf8_without_validation("/dev/null"sv));
return Jakt::compiler_main(invocation_args);
}
}
;
if (!runtime_archive_path.exists()){
warnln(StringView::from_string_literal("Building jakt runtime for target {}..."sv),abbreviated_triple);
JaktInternal::DynamicArray<Jakt::jakt__path::Path> sources = DynamicArray<Jakt::jakt__path::Path>::create_with({runtime_path.value().join(ByteString::from_utf8_without_validation("IO/File.cpp"sv))});
if (!target_links_ak){
sources.push_values(TRY((Jakt::find_with_extension(runtime_path.value().join(ByteString::from_utf8_without_validation("AK"sv)),ByteString::from_utf8_without_validation("cpp"sv)))));
}
sources.push_values(TRY((Jakt::find_with_extension(runtime_path.value().join(ByteString::from_utf8_without_validation("Jakt"sv)),ByteString::from_utf8_without_validation("cpp"sv)))));
if (TRY((build_archive(sources,runtime_archive_path))) != static_cast<int>(0)){
return static_cast<int>(1);
}
}
if (!main_archive_path.exists()){
warnln(StringView::from_string_literal("Building jakt main for target {}..."sv),abbreviated_triple);
JaktInternal::DynamicArray<Jakt::jakt__path::Path> sources = DynamicArray<Jakt::jakt__path::Path>::create_with({runtime_path.value().join(ByteString::from_utf8_without_validation("Main.cpp"sv))});
if (TRY((build_archive(sources,main_archive_path))) != static_cast<int>(0)){
return static_cast<int>(1);
}
}
runtime_lib_path = install_lib_dir.parent();
runtime_path = install_runtime_dir;
if (!only_support_libs){
JaktInternal::DynamicArray<ByteString> compiler_args = compiler_invocation_args();
Jakt::jakt__path::Path const source_path = Jakt::jakt__path::Path::from_string(source_file.value());
compiler_args.push(source_path.to_string());
compiler_args.push(ByteString::from_utf8_without_validation("-o"sv));
ByteString const default_output_filename = install_bin_dir.join(output_filename.value_or_lazy_evaluated([&] { return source_path.basename(true); })).to_string();
compiler_args.push(default_output_filename);
return Jakt::compiler_main(compiler_args);
}
return static_cast<int>(0);
}
}

ErrorOr<void> mkdir_p(Jakt::jakt__path::Path const path) {
{
JaktInternal::DynamicArray<ByteString> const components = path.components();
if (components.is_empty()){
return {};
}
Jakt::jakt__path::Path current_path = Jakt::jakt__path::Path::from_string(components[static_cast<i64>(0LL)]);
{
JaktInternal::ArrayIterator<ByteString> _magic = components[JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)}].iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString part = _magic_value.value();
{
if (!current_path.exists()){
warnln(StringView::from_string_literal("- mkdir {}"sv),current_path);
TRY((Jakt::jakt__platform__unknown_fs::make_directory(current_path.to_string())));
}
current_path = current_path.join(part);
}

}
}

if (!current_path.exists()){
TRY((Jakt::jakt__platform__unknown_fs::make_directory(current_path.to_string())));
}
}
return {};
}

ErrorOr<JaktInternal::DynamicArray<Jakt::jakt__path::Path>> find_with_extension(Jakt::jakt__path::Path const path,ByteString const extension) {
{
AK::Queue<Jakt::jakt__path::Path> directories_to_search = AK::Queue<Jakt::jakt__path::Path>();
directories_to_search.enqueue(path);
JaktInternal::DynamicArray<Jakt::jakt__path::Path> files_found = DynamicArray<Jakt::jakt__path::Path>::create_with({});
while (!directories_to_search.is_empty()){
Jakt::jakt__path::Path const directory = directories_to_search.dequeue();
{
NonnullRefPtr<Jakt::jakt__platform__unknown_fs::DirectoryIterator> _magic = TRY((Jakt::jakt__platform__unknown_fs::DirectoryIterator::from_path(directory))).value();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::jakt__path::Path,bool>> const _magic_value = TRY((_magic->next()));
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::jakt__path::Path,bool> entry__is_directory__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::jakt__path::Path,bool> const jakt__entry__is_directory__ = entry__is_directory__;
Jakt::jakt__path::Path const entry = jakt__entry__is_directory__.template get<0>();
bool const is_directory = jakt__entry__is_directory__.template get<1>();

Jakt::jakt__path::Path const path = directory.join(entry);
if (is_directory){
directories_to_search.enqueue(path);
}
else if (entry.extension() == extension){
files_found.push(path);
}
}

}
}

}
return files_found;
}
}

ByteString escape_for_depfile(ByteString const input) {
{
return input.replace(ByteString::from_utf8_without_validation("$"sv),ByteString::from_utf8_without_validation("$$"sv)).replace(ByteString::from_utf8_without_validation("#"sv),ByteString::from_utf8_without_validation("\\#"sv)).replace(ByteString::from_utf8_without_validation(" "sv),ByteString::from_utf8_without_validation("\\ "sv));
}
}

ErrorOr<int> compiler_main(JaktInternal::DynamicArray<ByteString> const args) {
{
Jakt::jakt__arguments::ArgsParser args_parser = Jakt::jakt__arguments::ArgsParser::from_args(args);
if (TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-h"sv), ByteString::from_utf8_without_validation("--help"sv)}))))){
outln(StringView::from_string_literal("{}\n"sv),Jakt::usage());
outln(StringView::from_string_literal("{}"sv),Jakt::help());
return static_cast<int>(0);
}
if (TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-v"sv), ByteString::from_utf8_without_validation("--version"sv)}))))){
outln(StringView::from_string_literal("{}"sv),TRY((Jakt::git::commit_hash())));
return static_cast<int>(0);
}
Jakt::jakt__path::Path const current_executable_path = Jakt::jakt__path::Path::from_string(TRY((File::current_executable_path())));
Jakt::jakt__path::Path const install_base_path = current_executable_path.parent().parent();
Jakt::jakt__path::Path const default_runtime_path = install_base_path.join(ByteString::from_utf8_without_validation("include/runtime"sv));
Jakt::jakt__path::Path const default_runtime_library_path = install_base_path.join(ByteString::from_utf8_without_validation("lib"sv));
ByteString const default_compiler_path = [&]() -> ByteString { auto __jakt_enum_value = false;
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("clang-cl"sv);}else {return ByteString::from_utf8_without_validation("clang++"sv);} 
}();
bool const optimize = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-O"sv)}))));
bool const lexer_debug = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-dl"sv)}))));
bool const parser_debug = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-dp"sv)}))));
bool const typechecker_debug = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-dt"sv)}))));
bool const build_executable = !TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-S"sv), ByteString::from_utf8_without_validation("--emit-cpp-source-only"sv)}))));
bool const run_executable = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-cr"sv), ByteString::from_utf8_without_validation("--compile-run"sv)}))));
bool const codegen_debug = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-d"sv)}))));
bool const debug_print = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--debug-print"sv)}))));
bool const debug_print_cpp_import = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--debug-print-cpp-import"sv)}))));
bool const prettify_cpp_source = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-p"sv), ByteString::from_utf8_without_validation("--prettify-cpp-source"sv)}))));
bool const json_errors = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-j"sv), ByteString::from_utf8_without_validation("--json-errors"sv)}))));
bool const dump_type_hints = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-H"sv), ByteString::from_utf8_without_validation("--type-hints"sv)}))));
bool const dump_try_hints = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--try-hints"sv)}))));
bool const check_only = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-c"sv), ByteString::from_utf8_without_validation("--check-only"sv)}))));
JaktInternal::Optional<ByteString> const generate_depfile = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-M"sv), ByteString::from_utf8_without_validation("--dep-file"sv)}))));
JaktInternal::Optional<ByteString> const target_triple = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-T"sv), ByteString::from_utf8_without_validation("--target-triple"sv)}))));
ByteString const runtime_library_path = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-RLP"sv), ByteString::from_utf8_without_validation("--runtime-library-path"sv)})))).value_or_lazy_evaluated([&] { return default_runtime_library_path.to_string(); });
ByteString compiler_job_count = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-J"sv), ByteString::from_utf8_without_validation("--jobs"sv)})))).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("2"sv); });
if (false){
compiler_job_count = ByteString::from_utf8_without_validation("1"sv);
}
ByteString const clang_format_path = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-F"sv), ByteString::from_utf8_without_validation("--clang-format-path"sv)})))).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("clang-format"sv); });
ByteString const runtime_path = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-R"sv), ByteString::from_utf8_without_validation("--runtime-path"sv)})))).value_or_lazy_evaluated([&] { return default_runtime_path.to_string(); });
JaktInternal::Optional<ByteString> const assume_main_file_path = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--assume-main-file-path"sv)}))));
Jakt::jakt__path::Path const binary_dir = Jakt::jakt__path::Path::from_string(TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-B"sv), ByteString::from_utf8_without_validation("--binary-dir"sv)})))).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("build"sv); }));
Jakt::jakt__path::Path const exports_dir = Jakt::jakt__path::Path::from_string(TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-E"sv), ByteString::from_utf8_without_validation("--exports-dir"sv)})))).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("exports"sv); }));
JaktInternal::Optional<ByteString> const dot_clang_format_path = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-D"sv), ByteString::from_utf8_without_validation("--dot-clang-format-path"sv)}))));
ByteString const cxx_compiler_path = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-C"sv), ByteString::from_utf8_without_validation("--cxx-compiler-path"sv)})))).value_or_lazy_evaluated([&] { return default_compiler_path; });
JaktInternal::Optional<ByteString> const archiver_path = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-A"sv), ByteString::from_utf8_without_validation("--archiver"sv)}))));
JaktInternal::Optional<ByteString> const link_archive = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-a"sv), ByteString::from_utf8_without_validation("--link-archive"sv)}))));
bool const archive_link_support_libs = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--archive-link-support-libs"sv)}))));
bool const build_static = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--static"sv)}))));
JaktInternal::DynamicArray<ByteString> const extra_include_paths = TRY((args_parser.option_multiple(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-I"sv)}))));
JaktInternal::DynamicArray<ByteString> const extra_lib_paths = TRY((args_parser.option_multiple(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-L"sv)}))));
JaktInternal::DynamicArray<ByteString> const extra_link_libs = TRY((args_parser.option_multiple(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-l"sv)}))));
JaktInternal::DynamicArray<ByteString> const extra_linker_args = TRY((args_parser.option_multiple(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-Wl"sv)}))));
JaktInternal::DynamicArray<ByteString> const extra_cpp_files = TRY((args_parser.option_multiple(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-X"sv)}))));
JaktInternal::DynamicArray<ByteString> const extra_cpp_flags = TRY((args_parser.option_multiple(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--extra-cpp-flag"sv)}))));
JaktInternal::Optional<ByteString> const set_output_filename = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-o"sv), ByteString::from_utf8_without_validation("--output-filename"sv)}))));
JaktInternal::Optional<ByteString> const goto_def = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-g"sv), ByteString::from_utf8_without_validation("--goto-def"sv)}))));
JaktInternal::Optional<ByteString> const goto_type_def = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-t"sv), ByteString::from_utf8_without_validation("--goto-type-def"sv)}))));
JaktInternal::Optional<ByteString> const hover = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-e"sv), ByteString::from_utf8_without_validation("--hover"sv)}))));
JaktInternal::Optional<ByteString> const completions = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-m"sv), ByteString::from_utf8_without_validation("--completions"sv)}))));
bool const print_symbols = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--print-symbols"sv)}))));
JaktInternal::Optional<ByteString> const project_name = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--create"sv)}))));
bool const use_ccache = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--use-ccache"sv)}))));
JaktInternal::DynamicArray<ByteString> const user_configuration_specs = TRY((args_parser.option_multiple(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--config"sv)}))));
JaktInternal::Dictionary<ByteString,ByteString> user_configuration = Dictionary<ByteString, ByteString>::create_with_entries({});
{
JaktInternal::ArrayIterator<ByteString> _magic = user_configuration_specs.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString spec = _magic_value.value();
{
JaktInternal::DynamicArray<ByteString> const parts = spec.split('=');
{auto __jakt_enum_value = parts.size();
if (__jakt_enum_value == static_cast<size_t>(1ULL)) {{
user_configuration.set(parts[static_cast<i64>(0LL)], ByteString::from_utf8_without_validation("true"sv));
}
goto __jakt_label_204;}else if (__jakt_enum_value == static_cast<size_t>(2ULL)) {{
user_configuration.set(parts[static_cast<i64>(0LL)], parts[static_cast<i64>(1LL)]);
}
goto __jakt_label_204;}else {{
warnln(StringView::from_string_literal("error: invalid configuration specification: {}"sv),spec);
return static_cast<int>(1);
}
goto __jakt_label_204;}}goto __jakt_label_204; __jakt_label_204:;;
}

}
}

bool const interpret_run = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-r"sv), ByteString::from_utf8_without_validation("--run"sv)}))));
bool const format = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-f"sv), ByteString::from_utf8_without_validation("--format"sv)}))));
bool const format_inplace = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-fi"sv), ByteString::from_utf8_without_validation("--format-inplace"sv)}))));
bool const format_debug = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-fd"sv), ByteString::from_utf8_without_validation("--format-debug"sv)}))));
ByteString const input_format_range = TRY((args_parser.option(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-fr"sv), ByteString::from_utf8_without_validation("--format-range"sv)})))).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); });
bool const ak_stdlib = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--ak-is-my-only-stdlib"sv)}))));
bool const discover_only = TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--discover"sv)}))));
size_t const max_concurrent = infallible_integer_cast<size_t>(({ Optional<u32> __jakt_var_163;
auto __jakt_var_164 = [&]() -> ErrorOr<u32> { return Jakt::value_or_throw<u32>(compiler_job_count.template to_number<u32>()); }();
if (__jakt_var_164.is_error()) {{
warnln(StringView::from_string_literal("error: invalid value for --jobs: {}"sv),compiler_job_count);
return static_cast<int>(1);
}
} else {__jakt_var_163 = __jakt_var_164.release_value();
}
__jakt_var_163.release_value(); }));
if (TRY((args_parser.flag(DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("--repl"sv)}))))){
Jakt::repl::REPL repl = TRY((Jakt::repl::REPL::create(Jakt::jakt__path::Path::from_parts(DynamicArray<ByteString>::create_with({runtime_path, ByteString::from_utf8_without_validation("jaktlib"sv)})),Jakt::jakt__path::Path::from_parts(DynamicArray<ByteString>::create_with({runtime_path, ByteString::from_utf8_without_validation("prelude.jakt"sv)})),target_triple,user_configuration)));
TRY((repl.run()));
return static_cast<int>(0);
}
JaktInternal::DynamicArray<ByteString> const positional_arguments = args_parser.remaining_arguments();
if (project_name.has_value()){
Jakt::project::Project const project = Jakt::project::Project(project_name.value());
TRY((project.populate()));
return static_cast<int>(0);
}
Function<ErrorOr<bool>(ByteString)> const compiler_is = [cxx_compiler_path](ByteString name) -> ErrorOr<bool> {{
return Jakt::jakt__path::Path::from_string(cxx_compiler_path).basename(false).contains(name);
}
}
;
JaktInternal::Optional<ByteString> file_name = JaktInternal::OptionalNone();
bool first_arg = true;
JaktInternal::DynamicArray<ByteString> interpreted_main_arguments = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = positional_arguments.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString arg = _magic_value.value();
{
if (first_arg){
first_arg = false;
continue;
}
if (!file_name.has_value()){
file_name = arg;
continue;
}
if (!interpret_run){
warnln(StringView::from_string_literal("Extra unknown argument '{}', you can only pass one source file (was '{}')"sv),arg,file_name);
warnln(StringView::from_string_literal("{}"sv),Jakt::usage());
return static_cast<int>(1);
}
interpreted_main_arguments.push(arg);
}

}
}

if (!file_name.has_value()){
warnln(StringView::from_string_literal("you must pass a source file"sv));
warnln(StringView::from_string_literal("{}"sv),Jakt::usage());
return static_cast<int>(1);
}
Jakt::jakt__path::Path const file_path = Jakt::jakt__path::Path::from_string(file_name.value());
ByteString const guessed_output_filename = file_path.basename(true);
ByteString const output_filename = binary_dir.join(set_output_filename.value_or_lazy_evaluated([&] { return guessed_output_filename; })).to_string();
JaktInternal::DynamicArray<Jakt::error::JaktError> errors = DynamicArray<Jakt::error::JaktError>::create_with({});
NonnullRefPtr<Jakt::compiler::Compiler> compiler = Jakt::compiler::Compiler::__jakt_create(DynamicArray<Jakt::jakt__path::Path>::create_with({}),Dictionary<ByteString, Jakt::utility::FileId>::create_with_entries({}),DynamicArray<Jakt::error::JaktError>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<u8>::create_with({}),lexer_debug,parser_debug,false,debug_print,debug_print_cpp_import,Jakt::jakt__path::Path::from_parts(DynamicArray<ByteString>::create_with({runtime_path, ByteString::from_utf8_without_validation("jaktlib"sv)})),Jakt::jakt__path::Path::from_parts(DynamicArray<ByteString>::create_with({runtime_path, ByteString::from_utf8_without_validation("prelude.jakt"sv)})),extra_include_paths,extra_cpp_flags,json_errors,dump_type_hints,dump_try_hints,optimize,target_triple,user_configuration,binary_dir,exports_dir,[&]() -> JaktInternal::Optional<Jakt::jakt__path::Path> { auto __jakt_enum_value = assume_main_file_path.has_value();
if (__jakt_enum_value) {return static_cast<JaktInternal::Optional<Jakt::jakt__path::Path>>(Jakt::jakt__path::Path::from_string(assume_main_file_path.value()));}else if (!__jakt_enum_value) {return JaktInternal::OptionalNone();}VERIFY_NOT_REACHED();
 
}(),Set<ByteString>::create_with_values({}));
TRY((compiler->load_prelude()));
if ((format || format_debug) || format_inplace){
NonnullRefPtr<Jakt::jakt__file_iterator::RecursiveFileIterator> const directory_or_file_paths = TRY((Jakt::jakt__file_iterator::RecursiveFileIterator::make(file_path,ByteString::from_utf8_without_validation("jakt"sv))));
{
NonnullRefPtr<Jakt::jakt__file_iterator::RecursiveFileIterator> _magic = directory_or_file_paths;
for (;;){
JaktInternal::Optional<Jakt::jakt__path::Path> const _magic_value = TRY((_magic->next()));
if (!_magic_value.has_value()){
break;
}
Jakt::jakt__path::Path directory_or_file_path = _magic_value.value();
{
Jakt::utility::FileId const file_id = compiler->get_file_id_or_register(directory_or_file_path);
bool const file_is_set = TRY((compiler->set_current_file(file_id)));
if (!file_is_set){
return static_cast<int>(1);
}
JaktInternal::Optional<Jakt::FormatRange> const format_range = Jakt::parse_format_range(input_format_range,compiler->current_file_contents.size());
if (!format_range.has_value()){
warnln(StringView::from_string_literal("invalid format range '{}', expected <start>(:<end>?)"sv),input_format_range);
return static_cast<int>(1);
}
JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens = Jakt::lexer::Lexer::lex(compiler);
TRY((Jakt::format_output(directory_or_file_path,tokens,format_range,format_debug,format_inplace)));
}

}
}

return static_cast<int>(0);
}
Jakt::utility::FileId const main_file_id = compiler->get_file_id_or_register(file_path);
bool const file_is_set = TRY((compiler->set_current_file(main_file_id)));
if (!file_is_set){
return static_cast<int>(1);
}
JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens = Jakt::lexer::Lexer::lex(compiler);
if (lexer_debug){
{
JaktInternal::ArrayIterator<Jakt::lexer::Token> _magic = tokens.iterator();
for (;;){
JaktInternal::Optional<Jakt::lexer::Token> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::lexer::Token token = _magic_value.value();
{
outln(StringView::from_string_literal("token: {}"sv),token);
}

}
}

}
Jakt::parser::ParsedNamespace const parsed_namespace = Jakt::parser::Parser::parse(compiler,tokens);
if (parser_debug){
outln(StringView::from_string_literal("{:#}"sv),parsed_namespace);
}
if (print_symbols){
JaktInternal::DynamicArray<Jakt::ide::JaktSymbol> const symbols = TRY((Jakt::ide::find_symbols_in_namespace(parsed_namespace)));
JaktInternal::DynamicArray<ByteString> symbol_representations = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ide::JaktSymbol> _magic = symbols.iterator();
for (;;){
JaktInternal::Optional<Jakt::ide::JaktSymbol> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ide::JaktSymbol symbol = _magic_value.value();
{
symbol_representations.push(symbol.to_json());
}

}
}

outln(StringView::from_string_literal("[{}]"sv),Jakt::utility::join(symbol_representations,ByteString::from_utf8_without_validation(","sv)));
return static_cast<int>(0);
}
Jakt::typechecker::Typechecker typechecker = TRY((Jakt::typechecker::Typechecker::typecheck(compiler,parsed_namespace)));
NonnullRefPtr<Jakt::types::CheckedProgram> const checked_program = typechecker.program;
if (interpret_run){
NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter = typechecker.interpreter();
Jakt::ids::ScopeId const main_module_scope_id = Jakt::ids::ScopeId(Jakt::ids::ModuleId(static_cast<size_t>(1ULL)),static_cast<size_t>(0ULL));
JaktInternal::Optional<Jakt::ids::FunctionId> main_function_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::Module>> _magic = checked_program->modules.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::Module>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::Module> module = _magic_value.value();
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::Scope>> _magic = module->scopes.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::Scope>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::Scope> scope = _magic_value.value();
{
if (!scope->parent.map([&](auto&& _value) { return _value.equals(main_module_scope_id); }).value_or_lazy_evaluated([&] { return false; })){
continue;
}
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = scope->functions.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> function_name__overload_set__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const jakt__function_name__overload_set__ = function_name__overload_set__;
ByteString const function_name = jakt__function_name__overload_set__.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set = jakt__function_name__overload_set__.template get<1>();

if (function_name == ByteString::from_utf8_without_validation("main"sv)){
main_function_id = overload_set[static_cast<i64>(0LL)];
break;
}
}

}
}

if (main_function_id.has_value()){
break;
}
}

}
}

if (main_function_id.has_value()){
break;
}
}

}
}

if (!main_function_id.has_value()){
warnln(StringView::from_string_literal("Error: No main function  found in program"sv));
return static_cast<int>(1);
}
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> const namespace_ = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
Jakt::utility::Span const call_span = Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL));
JaktInternal::Optional<Jakt::types::CheckedParameter> const first_main_param = checked_program->get_function(main_function_id.value())->params.first();
JaktInternal::DynamicArray<Jakt::types::Value> const arguments = [&]() -> JaktInternal::DynamicArray<Jakt::types::Value> { auto __jakt_enum_value = first_main_param.has_value();
if (__jakt_enum_value) {{
JaktInternal::DynamicArray<Jakt::types::Value> passed_arguments = DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::JaktString(file_name.value()),call_span)});
{
JaktInternal::ArrayIterator<ByteString> _magic = interpreted_main_arguments.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString argument = _magic_value.value();
{
passed_arguments.push(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(argument),call_span));
}

}
}

return DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(passed_arguments,first_main_param.value().variable->type_id),call_span)});
}
VERIFY_NOT_REACHED();
}else if (!__jakt_enum_value) {return DynamicArray<Jakt::types::Value>::create_with({});}VERIFY_NOT_REACHED();
 
}();
Jakt::interpreter::ExecutionResult const main_result = TRY((interpreter->execute(main_function_id.value(),namespace_,JaktInternal::OptionalNone(),arguments,call_span,JaktInternal::OptionalNone(),true)));
{auto&& __jakt_match_variant = main_result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& x = __jakt_match_value.value;
{auto&& __jakt_match_variant = *x.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& ret_val = __jakt_match_value.value;
{
return static_cast<int>(ret_val);
}
goto __jakt_label_206;};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& ret_val = __jakt_match_value.value;
{
return infallible_integer_cast<int>(ret_val);
}
goto __jakt_label_206;};/*case end*/
case 0 /* Void */:{
return static_cast<int>(0);
}
goto __jakt_label_206;default:{
warnln(StringView::from_string_literal("Error: Main function  must return an integer"sv));
return static_cast<int>(1);
}
goto __jakt_label_206;}/*switch end*/
}goto __jakt_label_206; __jakt_label_206:;;goto __jakt_label_205;};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& x = __jakt_match_value.value;
{
warnln(StringView::from_string_literal("Error: Main function  threw: {}"sv),TRY((Jakt::repl::serialize_ast_node(TRY((Jakt::interpreter::value_to_checked_expression(x,interpreter)))))));
return static_cast<int>(1);
}
goto __jakt_label_205;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_205; __jakt_label_205:;;
}
if (goto_def.has_value()){
size_t const index = infallible_integer_cast<size_t>(goto_def.value().template to_number<u32>().value());
Jakt::utility::Span const result = TRY((Jakt::ide::find_definition_in_program(checked_program,Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(1ULL)),index,index))));
if (result.file_id.id == static_cast<size_t>(1ULL)){
outln(StringView::from_string_literal("{{\"start\": {}, \"end\": {}}}"sv),result.start,result.end);
}
else {
JaktInternal::Optional<Jakt::jakt__path::Path> const file_path = compiler->get_file_path(result.file_id);
outln(StringView::from_string_literal("{{\"start\": {}, \"end\": {}, \"file\": \"{}\"}}"sv),result.start,result.end,Jakt::utility::escape_for_quotes(file_path.value().to_string()));
}

return static_cast<int>(0);
}
if (goto_type_def.has_value()){
size_t const index = infallible_integer_cast<size_t>(goto_type_def.value().template to_number<u32>().value());
Jakt::utility::Span const result = TRY((Jakt::ide::find_type_definition_in_program(checked_program,Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(1ULL)),index,index))));
if (result.file_id.id == static_cast<size_t>(1ULL)){
outln(StringView::from_string_literal("{{\"start\": {}, \"end\": {}}}"sv),result.start,result.end);
}
else {
JaktInternal::Optional<Jakt::jakt__path::Path> const file_path = compiler->get_file_path(result.file_id);
outln(StringView::from_string_literal("{{\"start\": {}, \"end\": {}, \"file\": \"{}\"}}"sv),result.start,result.end,Jakt::utility::escape_for_quotes(file_path.value().to_string()));
}

return static_cast<int>(0);
}
if (hover.has_value()){
size_t const index = infallible_integer_cast<size_t>(hover.value().template to_number<u32>().value());
JaktInternal::Optional<ByteString> const result = TRY((Jakt::ide::find_typename_in_program(checked_program,Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(1ULL)),index,index))));
if (result.has_value()){
outln(StringView::from_string_literal("{{\"hover\": \"{}\"}}"sv),result.value());
}
return static_cast<int>(0);
}
if (completions.has_value()){
size_t const index = infallible_integer_cast<size_t>(completions.value().template to_number<u32>().value());
JaktInternal::DynamicArray<ByteString> const result = TRY((Jakt::ide::find_dot_completions(checked_program,Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(1ULL)),index,index))));
out(StringView::from_string_literal("{{\"completions\": ["sv));
bool first = true;
{
JaktInternal::ArrayIterator<ByteString> _magic = result.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString completion = _magic_value.value();
{
if (!first){
out(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

out(StringView::from_string_literal("\"{}\""sv),completion);
}

}
}

outln(StringView::from_string_literal("]}}"sv));
return static_cast<int>(0);
}
if (typechecker_debug){
outln(StringView::from_string_literal("{:#}"sv),checked_program);
}
TRY((compiler->print_errors()));
if (!compiler->errors.is_empty()){
return static_cast<int>(1);
}
if (check_only){
return static_cast<int>(0);
}
if (!binary_dir.exists()){
TRY((Jakt::jakt__platform__unknown_fs::make_directory(binary_dir.to_string())));
}
if (!exports_dir.exists()){
TRY((Jakt::jakt__platform__unknown_fs::make_directory(exports_dir.to_string())));
}
JaktInternal::Dictionary<ByteString,ByteString> exported_files = Dictionary<ByteString, ByteString>::create_with_entries({});
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>> const codegen_result = TRY((Jakt::codegen::CodeGenerator::generate(compiler,checked_program,codegen_debug,exported_files)));
if (discover_only){
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Tuple<ByteString,ByteString>> _magic = codegen_result.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> file__contents_and_path__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> const jakt__file__contents_and_path__ = file__contents_and_path__;
ByteString const file = jakt__file__contents_and_path__.template get<0>();
JaktInternal::Tuple<ByteString,ByteString> const contents_and_path = jakt__file__contents_and_path__.template get<1>();

JaktInternal::Tuple<ByteString,ByteString> const __module_file_path_ = contents_and_path;
ByteString const _ = __module_file_path_.template get<0>();
ByteString const module_file_path = __module_file_path_.template get<1>();

if (module_file_path == ByteString::from_utf8_without_validation("__prelude__"sv)){
continue;
}
Jakt::jakt__path::Path const path = binary_dir.join(file);
outln(StringView::from_string_literal("{}:{}"sv),path.to_string(),module_file_path);
}

}
}

return static_cast<int>(0);
}
ByteStringBuilder depfile_builder = ByteStringBuilder::create();
if (generate_depfile.has_value()){
if (link_archive.has_value()){
depfile_builder.append(Jakt::escape_for_depfile(binary_dir.join(link_archive.value()).to_string()));
}
else {
depfile_builder.append(Jakt::escape_for_depfile(output_filename));
}

depfile_builder.append(StringView::from_string_literal(" : "sv));
JaktInternal::Set<ByteString> seen_files = Set<ByteString>::create_with_values({});
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Tuple<ByteString,ByteString>> _magic = codegen_result.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> ___contents_and_path__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> const jakt_____contents_and_path__ = ___contents_and_path__;
ByteString const _ = jakt_____contents_and_path__.template get<0>();
JaktInternal::Tuple<ByteString,ByteString> const contents_and_path = jakt_____contents_and_path__.template get<1>();

JaktInternal::Tuple<ByteString,ByteString> const contents_module_file_path_ = contents_and_path;
ByteString const contents = contents_module_file_path_.template get<0>();
ByteString const module_file_path = contents_module_file_path_.template get<1>();

if (module_file_path == ByteString::from_utf8_without_validation("__prelude__"sv)){
continue;
}
ByteString const file = Jakt::escape_for_depfile(module_file_path);
if (seen_files.contains(file)){
continue;
}
seen_files.add(file);
depfile_builder.append(StringView::from_string_literal(" \\\n  "sv));
depfile_builder.append(file);
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::ScopeId> _magic = typechecker.cpp_import_cache.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId> path_____ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId> const jakt__path_____ = path_____;
ByteString const path = jakt__path_____.template get<0>();
Jakt::ids::ScopeId const _ = jakt__path_____.template get<1>();

JaktInternal::Optional<Jakt::jakt__path::Path> const full_path = TRY((compiler->find_in_search_paths(Jakt::jakt__path::Path::from_string(path),false,static_cast<size_t>(0ULL))));
ByteString entry = path;
if (full_path.has_value()){
entry = full_path.value().to_string();
}
depfile_builder.append(StringView::from_string_literal(" \\\n  "sv));
depfile_builder.append(Jakt::escape_for_depfile(entry));
}

}
}

{
JaktInternal::SetIterator<ByteString> _magic = compiler->files_used_in_build.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString path = _magic_value.value();
{
if (seen_files.contains(path)){
continue;
}
seen_files.add(path);
depfile_builder.append(StringView::from_string_literal(" \\\n  "sv));
depfile_builder.append(Jakt::escape_for_depfile(path));
}

}
}

depfile_builder.append(StringView::from_string_literal("\n"sv));
}
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Tuple<ByteString,ByteString>> _magic = codegen_result.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> file__contents_and_path__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> const jakt__file__contents_and_path__ = file__contents_and_path__;
ByteString const file = jakt__file__contents_and_path__.template get<0>();
JaktInternal::Tuple<ByteString,ByteString> const contents_and_path = jakt__file__contents_and_path__.template get<1>();

JaktInternal::Tuple<ByteString,ByteString> const contents_module_file_path_ = contents_and_path;
ByteString const contents = contents_module_file_path_.template get<0>();
ByteString const module_file_path = contents_module_file_path_.template get<1>();

Jakt::jakt__path::Path const path = binary_dir.join(file);
auto __jakt_var_166 = [&]() -> ErrorOr<void> { return TRY((Jakt::write_only_if_updated(contents,path.to_string()))), ErrorOr<void>{}; }();
if (__jakt_var_166.is_error()) {auto error = __jakt_var_166.release_error();
{
warnln(StringView::from_string_literal("Error: Could not write to file: {} ({})"sv),file,error);
return static_cast<int>(1);
}
}
;
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ByteString> _magic = exported_files.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,ByteString> file__contents__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,ByteString> const jakt__file__contents__ = file__contents__;
ByteString const file = jakt__file__contents__.template get<0>();
ByteString const contents = jakt__file__contents__.template get<1>();

Jakt::jakt__path::Path const path = exports_dir.join(file);
auto __jakt_var_168 = [&]() -> ErrorOr<void> { return TRY((Jakt::write_only_if_updated(contents,path.to_string()))), ErrorOr<void>{}; }();
if (__jakt_var_168.is_error()) {auto error = __jakt_var_168.release_error();
{
warnln(StringView::from_string_literal("Error: Could not write to file: {} ({})"sv),file,error);
return static_cast<int>(1);
}
}
;
}

}
}

if (generate_depfile.has_value()){
auto __jakt_var_169 = [&]() -> ErrorOr<void> {
{
TRY((Jakt::write_only_if_updated(depfile_builder.to_string(),generate_depfile.value())));
}

;
return ErrorOr<void> {};}();
if (__jakt_var_169.is_error()) {auto error = __jakt_var_169.release_error();
{
warnln(StringView::from_string_literal("Error: Could not write to file list ({})"sv),error);
return static_cast<int>(1);
}
};
}
if (prettify_cpp_source){
ByteStringBuilder command = ByteStringBuilder::create();
command.appendff(ByteString::from_utf8_without_validation("{} -i"sv),clang_format_path);
if (dot_clang_format_path.has_value()){
command.appendff(ByteString::from_utf8_without_validation(" --style=file:{}"sv),dot_clang_format_path);
}
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Tuple<ByteString,ByteString>> _magic = codegen_result.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> file_____ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> const jakt__file_____ = file_____;
ByteString const file = jakt__file_____.template get<0>();
JaktInternal::Tuple<ByteString,ByteString> const _ = jakt__file_____.template get<1>();

Jakt::jakt__path::Path const path = binary_dir.join(file);
command.appendff(ByteString::from_utf8_without_validation(" {}"sv),path.to_string());
}

}
}

system(command.to_string().characters());
}
if (build_executable || run_executable){
JaktInternal::DynamicArray<ByteString> files = DynamicArray<ByteString>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Tuple<ByteString,ByteString>> _magic = codegen_result.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> file_name_____ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> const jakt__file_name_____ = file_name_____;
ByteString const file_name = jakt__file_name_____.template get<0>();
JaktInternal::Tuple<ByteString,ByteString> const _ = jakt__file_name_____.template get<1>();

if (file_name.ends_with(ByteString::from_utf8_without_validation(".h"sv))){
continue;
}
files.push(file_name);
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = extra_cpp_files.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString file = _magic_value.value();
{
files.push(file);
}

}
}

Jakt::build::Builder builder = TRY((Jakt::build::Builder::for_building(files,max_concurrent)));
JaktInternal::DynamicArray<ByteString> extra_compiler_flags = DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-c"sv)});
if (ak_stdlib){
extra_compiler_flags.push(ByteString::from_utf8_without_validation("-DJAKT_USING_AK_AS_STANDARD_LIBRARY=1"sv));
}
if (build_static){
extra_compiler_flags.push(ByteString::from_utf8_without_validation("-static"sv));
}
if (target_triple.has_value()){
if (TRY((compiler_is(ByteString::from_utf8_without_validation("clang++"sv)))) && [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(target_triple.value(),TRY((TRY((Jakt::jakt__platform::Target::active())).name(false))))){
extra_compiler_flags.push(ByteString::from_utf8_without_validation("-target"sv));
extra_compiler_flags.push(TRY((TRY((Jakt::jakt__platform::Target::from_triple(target_triple.value()))).name(true))));
}
}
{
JaktInternal::ArrayIterator<ByteString> _magic = extra_cpp_flags.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString flag = _magic_value.value();
{
extra_compiler_flags.push(flag);
}

}
}

auto __jakt_var_171 = [&]() -> ErrorOr<void> { return TRY((builder.build_all(binary_dir,[use_ccache, cxx_compiler_path, runtime_path, extra_include_paths, optimize, extra_compiler_flags](ByteString input_filename, ByteString output_filename) -> ErrorOr<JaktInternal::DynamicArray<ByteString>> {{
return Jakt::platform__unknown_compiler::run_compiler(cxx_compiler_path,input_filename,output_filename,runtime_path,extra_include_paths,DynamicArray<ByteString>::create_with({}),DynamicArray<ByteString>::create_with({}),optimize,extra_compiler_flags,use_ccache);
}
}
))), ErrorOr<void>{}; }();
if (__jakt_var_171.is_error()) {{
return static_cast<int>(1);
}
}
;
Jakt::jakt__path::Path const runtime_lib_path = Jakt::jakt__path::Path::from_string(runtime_library_path);
Jakt::jakt__platform::Target const target = TRY(([&]() -> ErrorOr<Jakt::jakt__platform::Target> { auto __jakt_enum_value = target_triple.has_value();
if (__jakt_enum_value) {return Jakt::jakt__platform::Target::from_triple(target_triple.value());}else if (!__jakt_enum_value) {return Jakt::jakt__platform::Target::active();}VERIFY_NOT_REACHED();
 
}()));
if (link_archive.has_value()){
JaktInternal::DynamicArray<ByteString> extra_arguments = DynamicArray<ByteString>::create_with({});
if (archive_link_support_libs){
extra_arguments.push(runtime_lib_path.join(TRY((Jakt::platform::library_name_for_target(ByteString::from_utf8_without_validation("main"sv),target)))).to_string());
extra_arguments.push(runtime_lib_path.join(TRY((Jakt::platform::library_name_for_target(ByteString::from_utf8_without_validation("runtime"sv),target)))).to_string());
}
auto __jakt_var_173 = [&]() -> ErrorOr<void> { return TRY((builder.link_into_archive(archiver_path.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("ar"sv); }),binary_dir.join(link_archive.value()).to_string(),extra_arguments))), ErrorOr<void>{}; }();
if (__jakt_var_173.is_error()) {{
return static_cast<int>(1);
}
}
;
}
else {
JaktInternal::DynamicArray<ByteString> extra_arguments = DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("-g"sv)});
{
JaktInternal::ArrayIterator<ByteString> _magic = extra_cpp_flags.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString flag = _magic_value.value();
{
extra_arguments.push(flag);
}

}
}

if (target_triple.has_value()){
if (TRY((compiler_is(ByteString::from_utf8_without_validation("clang++"sv)))) && [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(target_triple.value(),TRY((TRY((Jakt::jakt__platform::Target::active())).name(false))))){
extra_arguments.push(ByteString::from_utf8_without_validation("-target"sv));
extra_arguments.push(TRY((target.name(true))));
}
}
extra_arguments.push(runtime_lib_path.join(TRY((Jakt::platform::library_name_for_target(ByteString::from_utf8_without_validation("main"sv),target)))).to_string());
extra_arguments.push(runtime_lib_path.join(TRY((Jakt::platform::library_name_for_target(ByteString::from_utf8_without_validation("runtime"sv),target)))).to_string());
{
JaktInternal::ArrayIterator<ByteString> _magic = extra_lib_paths.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString path = _magic_value.value();
{
extra_arguments.push(ByteString::from_utf8_without_validation("-L"sv));
extra_arguments.push(path);
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = extra_link_libs.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString lib = _magic_value.value();
{
extra_arguments.push(ByteString::from_utf8_without_validation("-l"sv));
extra_arguments.push(lib);
}

}
}

if (false && TRY((compiler_is(ByteString::from_utf8_without_validation("clang-cl"sv))))){
extra_arguments.push(ByteString::from_utf8_without_validation("/link"sv));
extra_arguments.push(ByteString::from_utf8_without_validation("/subsystem:console"sv));
}
{
JaktInternal::ArrayIterator<ByteString> _magic = extra_linker_args.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString arg = _magic_value.value();
{
extra_arguments.push(__jakt_format(StringView::from_string_literal("-Wl,{}"sv),arg));
}

}
}

auto __jakt_var_175 = [&]() -> ErrorOr<void> { return TRY((builder.link_into_executable(cxx_compiler_path,output_filename,extra_arguments))), ErrorOr<void>{}; }();
if (__jakt_var_175.is_error()) {{
return static_cast<int>(1);
}
}
;
}

}
if (run_executable){
return system(output_filename.characters());
}
return static_cast<int>(0);
}
}

ErrorOr<void> format_output(Jakt::jakt__path::Path const file_path,JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens,JaktInternal::Optional<Jakt::FormatRange> const format_range,bool const format_debug,bool const format_inplace) {
{
ByteStringBuilder formatted_file = ByteStringBuilder::create();
bool on_new_line = true;
{
Jakt::formatter::Formatter _magic = TRY((Jakt::formatter::Formatter::for_tokens(tokens,format_debug,static_cast<size_t>(120ULL))));
for (;;){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::formatter::FormattedToken>> const _magic_value = TRY((_magic.next()));
if (!_magic_value.has_value()){
break;
}
JaktInternal::DynamicArray<Jakt::formatter::FormattedToken> formatted_line = _magic_value.value();
{
{
JaktInternal::ArrayIterator<Jakt::formatter::FormattedToken> _magic = formatted_line.iterator();
for (;;){
JaktInternal::Optional<Jakt::formatter::FormattedToken> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::formatter::FormattedToken formatted_token = _magic_value.value();
{
if (!formatted_token.token.span().is_in_offset_range(format_range.value().start,format_range.value().end)){
continue;
}
{
JaktInternal::ArrayIterator<u8> _magic = formatted_token.preceding_trivia.iterator();
for (;;){
JaktInternal::Optional<u8> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
u8 byte = _magic_value.value();
{
formatted_file.append(byte);
}

}
}

{auto&& __jakt_match_variant = formatted_token.token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
{
if (comment.has_value()){
u8 next_char = static_cast<u8>(u8' ');
if (comment.value().length() != static_cast<size_t>(0ULL)){
next_char = comment.value().byte_at(static_cast<size_t>(0ULL));
}
ByteString const space = [&]() -> ByteString { auto __jakt_enum_value = next_char;
if ((__jakt_enum_value == static_cast<u8>(u8' '))||(__jakt_enum_value == static_cast<u8>(u8'\t'))||(__jakt_enum_value == static_cast<u8>(u8'/'))) {return ByteString::from_utf8_without_validation(""sv);}else {return ByteString::from_utf8_without_validation(" "sv);} 
}();
ByteString const lhs_space = [&]() -> ByteString { auto __jakt_enum_value = on_new_line;
if (__jakt_enum_value) {return Jakt::indent(formatted_token.indent);}else {return ByteString::from_utf8_without_validation(" "sv);} 
}();
formatted_file.appendff(ByteString::from_utf8_without_validation("{}//{}{}"sv),lhs_space,space,comment.value());
}
on_new_line = true;
}
goto __jakt_label_207;};/*case end*/
case 114 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;JaktInternal::Optional<ByteString> const& consumed = __jakt_match_value.consumed;
{
if (consumed.has_value()){
formatted_file.appendff(ByteString::from_utf8_without_validation("{}"sv),consumed.value());
}
}
goto __jakt_label_207;};/*case end*/
default:{
if (on_new_line){
formatted_file.appendff(ByteString::from_utf8_without_validation("{}"sv),Jakt::indent(formatted_token.indent));
}
formatted_file.appendff(ByteString::from_utf8_without_validation("{}"sv),TRY((formatted_token.token_text())));
on_new_line = false;
}
goto __jakt_label_207;}/*switch end*/
break;}goto __jakt_label_207; __jakt_label_207:;;
{
JaktInternal::ArrayIterator<u8> _magic = formatted_token.trailing_trivia.iterator();
for (;;){
JaktInternal::Optional<u8> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
u8 byte = _magic_value.value();
{
formatted_file.appendff(ByteString::from_utf8_without_validation("{:c}"sv),byte);
}

}
}

if (formatted_token.token.__jakt_init_index() == 55 /* Eol */){
formatted_file.append(StringView::from_string_literal("\n"sv));
}
}

}
}

}

}
}

if (format_inplace){
TRY((Jakt::utility::write_to_file(formatted_file.to_string(),file_path.to_string())));
}
else {
out(StringView::from_string_literal("{}"sv),formatted_file.to_string());
}

}
return {};
}

ErrorOr<void> write_only_if_updated(ByteString const data,ByteString const output_filename) {
{
if (Jakt::file_needs_updating(output_filename,data)){
TRY((Jakt::utility::write_to_file(data,output_filename)));
}
}
return {};
}

bool file_needs_updating(ByteString const path,ByteString const new_contents) {
{
JaktInternal::Optional<NonnullRefPtr<File>> maybe_file = ({ Optional<NonnullRefPtr<File>> __jakt_var_176;
auto __jakt_var_177 = [&]() -> ErrorOr<NonnullRefPtr<File>> { return File::open_for_reading(path); }();
if (!__jakt_var_177.is_error()) __jakt_var_176 = __jakt_var_177.release_value();
__jakt_var_176; });
if (maybe_file.has_value()){
JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const contents = ({ Optional<JaktInternal::DynamicArray<u8>> __jakt_var_178;
auto __jakt_var_179 = [&]() -> ErrorOr<JaktInternal::DynamicArray<u8>> { return maybe_file.value()->read_all(); }();
if (!__jakt_var_179.is_error()) __jakt_var_178 = __jakt_var_179.release_value();
__jakt_var_178; });
if (contents.has_value()){
return [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(Jakt::utility::to_string(contents.value()),new_contents);
}
else {
return true;
}

}
else {
return true;
}

}
}

ByteString Jakt::FormatRange::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FormatRange("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("start: {}, ", start);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("end: {}", end);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::FormatRange::FormatRange(size_t a_start, size_t a_end): start(move(a_start)), end(move(a_end)){}

} // namespace Jakt
