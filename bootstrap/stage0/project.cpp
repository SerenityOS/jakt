#include "project.h"
namespace Jakt {
namespace project {
ErrorOr<String> project::Project::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Project("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("name: "));TRY(builder.appendff("\"{}\"", name));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<void> project::Project::populate() const {
{
String const current_directory = TRY((unknown_fs::current_directory()));
String const project_directory = ((current_directory + String("/")) + ((*this).name));
outln(String("Creating jakt project in {}.."),project_directory);
TRY((unknown_fs::make_directory(project_directory)));
TRY((unknown_fs::make_directory((project_directory + String("/src")))));
out(String("\tGenerating CMakeLists.txt..."));
TRY((((*this).create_template_cmake_lists(project_directory))));
outln(String(" done"));
out(String("\tGenerating jakt source code..."));
TRY((((*this).create_sample_jakt_files(project_directory))));
outln(String(" done"));
out(String("\tGenerating README.md..."));
TRY((((*this).create_readme(project_directory))));
outln(String(" done"));
outln(String("Done!"));
}
return {};
}

ErrorOr<void> project::Project::create_readme(String const project_directory) const {
{
String const readme_text = ((((String("# Example Jakt Project\n\nThis example jakt project has two modules, hurray!\n\n## Building with jakt\n\n```console\njakt src/main.jakt -o ") + ((*this).name)) + String("\n```\n\n## Building with CMake\n\nMake sure to install the ``jakt`` compiler somewhere. For example, ``/path/to/jakt-install``.\n\nThis can be done by cloning ``jakt``, and running the following commands from its directory:\n\n```console\njakt> cmake -GNinja -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=/path/to/jakt-install\njakt> cmake --build build\njakt> cmake --install build\n```\n\nNext you can build this project by configuring CMake to know where to find the ``jakt`` cmake helper scripts.\n\n```console\n> cmake -GNinja -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_PREFIX_PATH=/path/to/jakt-install\n> cmake --build build\n```\n\n## Running the application\n\nAfter building, the program will be in the ``build`` directory\n\n```console\n./build/")) + ((*this).name)) + String("\n```\n\nWhich should print:\n\n```console\nHello, World!\n```\n"));
TRY((utility::write_to_file(readme_text,(project_directory + String("/README.md")))));
}
return {};
}

project::Project::Project(String a_name) :name(a_name){}

ErrorOr<void> project::Project::create_template_cmake_lists(String const project_directory) const {
{
String const cml_contents = ((((String("cmake_minimum_required(VERSION 3.20)\nproject(") + ((*this).name)) + String("\n   VERSION 1.0.0\n   LANGUAGES CXX\n)\n\nfind_package(Jakt REQUIRED)\n\nadd_jakt_executable(")) + ((*this).name)) + String("\n   MAIN_SOURCE src/main.jakt\n   MODULE_SOURCES\n     src/second_module.jakt\n)\n"));
TRY((utility::write_to_file(cml_contents,(project_directory + String("/CMakeLists.txt")))));
}
return {};
}

ErrorOr<void> project::Project::create_sample_jakt_files(String const project_directory) const {
{
String const main_jakt = String("import second_module { get_string }\n\nfunction main() throws -> c_int {\n    println(\"{}!\", get_string())\n    return 0\n}\n");
String const second_module_jakt = String("function get_string() throws -> String {\n    return \"Hello, World\"\n}\n");
TRY((utility::write_to_file(main_jakt,(project_directory + String("/src/main.jakt")))));
TRY((utility::write_to_file(second_module_jakt,(project_directory + String("/src/second_module.jakt")))));
}
return {};
}

}
} // namespace Jakt
