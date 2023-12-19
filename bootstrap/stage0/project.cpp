#include "project.h"
namespace Jakt {
namespace project {
ErrorOr<ByteString> project::Project::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Project("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\"", name);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<void> project::Project::populate() const {
{
ByteString const current_directory = TRY((jakt__platform__unknown_fs::current_directory()));
ByteString const project_directory = TRY((((TRY((((current_directory) + ((ByteString::must_from_utf8("/"sv))))))) + (((*this).name)))));
outln((StringView::from_string_literal("Creating jakt project in {}.."sv)),project_directory);
TRY((jakt__platform__unknown_fs::make_directory(project_directory)));
TRY((jakt__platform__unknown_fs::make_directory(TRY((((project_directory) + ((ByteString::must_from_utf8("/src"sv)))))))));
out((StringView::from_string_literal("\tGenerating CMakeLists.txt..."sv)));
TRY((((*this).create_template_cmake_lists(project_directory))));
outln((StringView::from_string_literal(" done"sv)));
out((StringView::from_string_literal("\tGenerating jakt source code..."sv)));
TRY((((*this).create_sample_jakt_files(project_directory))));
outln((StringView::from_string_literal(" done"sv)));
out((StringView::from_string_literal("\tGenerating README.md..."sv)));
TRY((((*this).create_readme(project_directory))));
outln((StringView::from_string_literal(" done"sv)));
outln((StringView::from_string_literal("Done!"sv)));
}
return {};
}

ErrorOr<void> project::Project::create_template_cmake_lists(ByteString const project_directory) const {
{
ByteString const cml_contents = TRY((((TRY((((TRY((((TRY(((((ByteString::must_from_utf8("cmake_minimum_required(VERSION 3.20)\nproject("sv))) + (((*this).name)))))) + ((ByteString::must_from_utf8("\n   VERSION 1.0.0\n   LANGUAGES CXX\n)\n\nfind_package(Jakt REQUIRED)\n\nadd_jakt_executable("sv))))))) + (((*this).name)))))) + ((ByteString::must_from_utf8("\n   MAIN_SOURCE src/main.jakt\n   MODULE_SOURCES\n     src/second_module.jakt\n)\n"sv))))));
TRY((utility::write_to_file(cml_contents,TRY((((project_directory) + ((ByteString::must_from_utf8("/CMakeLists.txt"sv)))))))));
}
return {};
}

ErrorOr<void> project::Project::create_sample_jakt_files(ByteString const project_directory) const {
{
ByteString const main_jakt = (ByteString::must_from_utf8("import second_module { get_string }\n\nfn main() throws -> c_int {\n    println(\"{}!\", get_string())\n    return 0\n}\n"sv));
ByteString const second_module_jakt = (ByteString::must_from_utf8("fn get_string() throws -> String {\n    return \"Hello, World\"\n}\n"sv));
TRY((utility::write_to_file(main_jakt,TRY((((project_directory) + ((ByteString::must_from_utf8("/src/main.jakt"sv)))))))));
TRY((utility::write_to_file(second_module_jakt,TRY((((project_directory) + ((ByteString::must_from_utf8("/src/second_module.jakt"sv)))))))));
}
return {};
}

ErrorOr<void> project::Project::create_readme(ByteString const project_directory) const {
{
ByteString const readme_text = TRY((((TRY((((TRY((((TRY(((((ByteString::must_from_utf8("# Example Jakt Project\n\nThis example jakt project has two modules, hurray!\n\n## Building with jakt\n\n```console\njakt src/main.jakt -o "sv))) + (((*this).name)))))) + ((ByteString::must_from_utf8("\n```\n\n## Building with CMake\n\nMake sure to install the ``jakt`` compiler somewhere. For example, ``/path/to/jakt-install``.\n\nThis can be done by cloning ``jakt``, and running the following commands from its directory:\n\n```console\njakt> cmake -GNinja -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=/path/to/jakt-install\njakt> cmake --build build\njakt> cmake --install build\n```\n\nNext you can build this project by configuring CMake to know where to find the ``jakt`` cmake helper scripts.\n\n```console\n> cmake -GNinja -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_PREFIX_PATH=/path/to/jakt-install\n> cmake --build build\n```\n\n## Running the application\n\nAfter building, the program will be in the ``build`` directory\n\n```console\n./build/"sv))))))) + (((*this).name)))))) + ((ByteString::must_from_utf8("\n```\n\nWhich should print:\n\n```console\nHello, World!\n```\n"sv))))));
TRY((utility::write_to_file(readme_text,TRY((((project_directory) + ((ByteString::must_from_utf8("/README.md"sv)))))))));
}
return {};
}

project::Project::Project(ByteString a_name): name(move(a_name)){}

}
} // namespace Jakt
