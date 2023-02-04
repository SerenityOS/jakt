#include "project.h"
namespace Jakt {
namespace project {
ErrorOr<DeprecatedString> project::Project::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Project("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("name: "sv));TRY(builder.appendff("\"{}\"", name));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> project::Project::populate() const {
{
DeprecatedString const current_directory = TRY((jakt__platform__unknown_fs::current_directory()));
DeprecatedString const project_directory = ((current_directory + Jakt::DeprecatedString("/"sv)) + ((*this).name));
outln(Jakt::DeprecatedString("Creating jakt project in {}.."sv),project_directory);
TRY((jakt__platform__unknown_fs::make_directory(project_directory)));
TRY((jakt__platform__unknown_fs::make_directory((project_directory + Jakt::DeprecatedString("/src"sv)))));
out(Jakt::DeprecatedString("\tGenerating CMakeLists.txt..."sv));
TRY((((*this).create_template_cmake_lists(project_directory))));
outln(Jakt::DeprecatedString(" done"sv));
out(Jakt::DeprecatedString("\tGenerating jakt source code..."sv));
TRY((((*this).create_sample_jakt_files(project_directory))));
outln(Jakt::DeprecatedString(" done"sv));
out(Jakt::DeprecatedString("\tGenerating README.md..."sv));
TRY((((*this).create_readme(project_directory))));
outln(Jakt::DeprecatedString(" done"sv));
outln(Jakt::DeprecatedString("Done!"sv));
}
return {};
}

ErrorOr<void> project::Project::create_readme(DeprecatedString const project_directory) const {
{
DeprecatedString const readme_text = ((((Jakt::DeprecatedString("# Example Jakt Project\n\nThis example jakt project has two modules, hurray!\n\n## Building with jakt\n\n```console\njakt src/main.jakt -o "sv) + ((*this).name)) + Jakt::DeprecatedString("\n```\n\n## Building with CMake\n\nMake sure to install the ``jakt`` compiler somewhere. For example, ``/path/to/jakt-install``.\n\nThis can be done by cloning ``jakt``, and running the following commands from its directory:\n\n```console\njakt> cmake -GNinja -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=/path/to/jakt-install\njakt> cmake --build build\njakt> cmake --install build\n```\n\nNext you can build this project by configuring CMake to know where to find the ``jakt`` cmake helper scripts.\n\n```console\n> cmake -GNinja -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_PREFIX_PATH=/path/to/jakt-install\n> cmake --build build\n```\n\n## Running the application\n\nAfter building, the program will be in the ``build`` directory\n\n```console\n./build/"sv)) + ((*this).name)) + Jakt::DeprecatedString("\n```\n\nWhich should print:\n\n```console\nHello, World!\n```\n"sv));
TRY((utility::write_to_file(readme_text,(project_directory + Jakt::DeprecatedString("/README.md"sv)))));
}
return {};
}

project::Project::Project(DeprecatedString a_name) :name(a_name){}

ErrorOr<void> project::Project::create_template_cmake_lists(DeprecatedString const project_directory) const {
{
DeprecatedString const cml_contents = ((((Jakt::DeprecatedString("cmake_minimum_required(VERSION 3.20)\nproject("sv) + ((*this).name)) + Jakt::DeprecatedString("\n   VERSION 1.0.0\n   LANGUAGES CXX\n)\n\nfind_package(Jakt REQUIRED)\n\nadd_jakt_executable("sv)) + ((*this).name)) + Jakt::DeprecatedString("\n   MAIN_SOURCE src/main.jakt\n   MODULE_SOURCES\n     src/second_module.jakt\n)\n"sv));
TRY((utility::write_to_file(cml_contents,(project_directory + Jakt::DeprecatedString("/CMakeLists.txt"sv)))));
}
return {};
}

ErrorOr<void> project::Project::create_sample_jakt_files(DeprecatedString const project_directory) const {
{
DeprecatedString const main_jakt = Jakt::DeprecatedString("import second_module { get_string }\n\nfn main() throws -> c_int {\n    println(\"{}!\", get_string())\n    return 0\n}\n"sv);
DeprecatedString const second_module_jakt = Jakt::DeprecatedString("fn get_string() throws -> String {\n    return \"Hello, World\"\n}\n"sv);
TRY((utility::write_to_file(main_jakt,(project_directory + Jakt::DeprecatedString("/src/main.jakt"sv)))));
TRY((utility::write_to_file(second_module_jakt,(project_directory + Jakt::DeprecatedString("/src/second_module.jakt"sv)))));
}
return {};
}

}
} // namespace Jakt
