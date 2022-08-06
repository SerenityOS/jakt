
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(Jakt
        VERSION 0.0.1
        LANGUAGES CXX
        HOMEPAGE_URL https://github.com/SerenityOS/jakt
        DESCRIPTION "Jakt programming language compiler")

set(NO_SYMLINKS_DEFAULT OFF)
if (CMAKE_HOST_WIN32)
  set(NO_SYMLINKS_DEFAULT ON)
endif()

set(FINAL_STAGE "1" CACHE STRING "Compiler stage to stop at, either 1 (default) or 2)")
option(NO_SYMLINKS "Use hard links instead of symlinks. Useful for unprivileged Windows users" "${NO_SYMLINKS_DEFAULT}")

if (NO_SYMLINKS)
  set(LINK_COMMAND create_hardlink)
  set(LINK_GENEX TARGET_FILE)
else()
  set(LINK_COMMAND create_symlink)
  set(LINK_GENEX TARGET_FILE_NAME)
endif()

macro(add_jakt_compiler_flags target)
  target_compile_options("${target}" PRIVATE
    -Wno-unused-local-typedefs
    -Wno-unused-function
    -Wno-unknown-warning-option
    -Wno-trigraphs
    -Wno-parentheses-equality
    -Wno-unqualified-std-cast-call
    -Wno-user-defined-literals
    -Wno-return-type
    -Wno-deprecated-declarations
    -fcolor-diagnostics
  )
  if (MSVC)
    # For clang-cl, which shows up to CMake as MSVC and accepts both kinds of arguments
    target_compile_options("${target}" PRIVATE /permissive- /utf-8 /EHsc-)
  else()
    target_compile_options("${target}" PRIVATE -fno-exceptions)  
  endif()
  target_compile_features("${target}" PRIVATE cxx_std_20)
endmacro()

function(add_jakt_executable compiler executable)
  cmake_parse_arguments(PARSE_ARGV 2 SELFHOST "" "MAIN_SOURCE;RUNTIME_DIRECTORY" "MODULE_SOURCES")
  set(main_source "${CMAKE_CURRENT_LIST_DIR}/${SELFHOST_MAIN_SOURCE}" )
  get_filename_component(main_base "${main_source}" NAME_WE)
  set(cpp_output "${executable}_${main_base}.cpp")

  if (NOT SELFHOST_RUNTIME_DIRECTORY)
    set(SELFHOST_RUNTIME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime")
  endif()

  set(binary_tmp_dir "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp")

  add_custom_command(
    OUTPUT "${cpp_output}"
    COMMAND "${CMAKE_COMMAND}" -E make_directory ${binary_tmp_dir}
    COMMAND "$<TARGET_FILE:${compiler}>" -S --binary-dir "${binary_tmp_dir}" -R "${SELFHOST_RUNTIME_DIRECTORY}" "${main_source}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp/${main_base}.cpp" "${cpp_output}"
    COMMAND "${CMAKE_COMMAND}" -E remove "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp/${main_base}.cpp"
    VERBATIM
    COMMENT "Building jakt file ${SELFHOST_MAIN_SOURCE} with ${compiler}"
    MAIN_DEPENDENCY "${main_source}"
    DEPENDS ${SELFHOST_MODULE_SOURCES}
  )
  add_custom_target("generate_${executable}" DEPENDS "${cpp_output}")

  add_executable("${executable}" "${cpp_output}")
  add_dependencies("${executable}" "generate_${executable}")
  add_jakt_compiler_flags("${executable}")
endfunction()

add_executable(jakt_stage0 bootstrap/stage0/jakt.cpp)
add_jakt_compiler_flags(jakt_stage0)
target_include_directories(jakt_stage0
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/stage0/runtime>
    $<INSTALL_INTERFACE:runtime>
)

set(SELFHOST_SOURCES
  runtime/prelude.jakt
  selfhost/codegen.jakt
  selfhost/compiler.jakt
  selfhost/error.jakt
  selfhost/ide.jakt
  selfhost/interpreter.jakt
  selfhost/lexer.jakt
  selfhost/parser.jakt
  selfhost/repl.jakt
  selfhost/typechecker.jakt
  selfhost/types.jakt
  selfhost/utility.jakt
)

add_jakt_executable(jakt_stage0 jakt_stage1
  MAIN_SOURCE selfhost/main.jakt
  MODULE_SOURCES ${SELFHOST_SOURCES}
  RUNTIME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/stage0/runtime"
)
target_include_directories(jakt_stage1
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/runtime>
    $<INSTALL_INTERFACE:runtime>
)

if (FINAL_STAGE GREATER_EQUAL 2)
  add_jakt_executable(jakt_stage1 jakt_stage2
    MAIN_SOURCE selfhost/main.jakt
    MODULE_SOURCES ${SELFHOST_SOURCES}
  )
  target_include_directories(jakt_stage2
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/runtime>
      $<INSTALL_INTERFACE:runtime>
  )
endif()

add_custom_command(
  TARGET "jakt_stage${FINAL_STAGE}"
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E ${LINK_COMMAND}  "$<${LINK_GENEX}:jakt_stage${FINAL_STAGE}>" "${CMAKE_BINARY_DIR}/jakt"
  VERBATIM
)

if (NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# FIXME: Remove if we decide to use CTest
option(BUILD_TESTING "Whether to build tests or not, default on" ON)

if (BUILD_TESTING)
  add_jakt_executable("jakt_stage${FINAL_STAGE}" jakttest
    MAIN_SOURCE
      jakttest/jakttest.jakt
    MODULE_SOURCES
      jakttest/error.jakt
      jakttest/lexer.jakt
      jakttest/parser.jakt
      jakttest/utility.jakt
  )
  target_sources(jakttest PRIVATE
     jakttest/fs.cpp
     jakttest/os.cpp
     jakttest/process.cpp
  )
  target_include_directories(jakttest PRIVATE jakttest
    $<TARGET_PROPERTY:jakt_stage${FINAL_STAGE},INCLUDE_DIRECTORIES>
  )
endif()
