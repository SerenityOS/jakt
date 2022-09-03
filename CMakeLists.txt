
cmake_minimum_required(VERSION 3.16..3.21)
cmake_policy(SET CMP0091 NEW)
project(Jakt
        VERSION 0.0.1
        LANGUAGES CXX
        HOMEPAGE_URL https://github.com/SerenityOS/jakt
        DESCRIPTION "Jakt programming language compiler")

include(GNUInstallDirs)

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

set(in_build_prefix "")
get_cmake_property(is_multi_config GENERATOR_IS_MULTI_CONFIG)
if (is_multi_config)
  set(in_build_prefix "$<CONFIG>/")
endif()

function(apply_output_rules target)
  set_property(TARGET ${target} PROPERTY "ARCHIVE_OUTPUT_DIRECTORY" "${Jakt_BINARY_DIR}/${in_build_prefix}lib")
  set_property(TARGET ${target} PROPERTY "LIBRARY_OUTPUT_DIRECTORY" "${Jakt_BINARY_DIR}/${in_build_prefix}lib")
  set_property(TARGET ${target} PROPERTY "RUNTIME_OUTPUT_DIRECTORY" "${Jakt_BINARY_DIR}/${in_build_prefix}bin")
endfunction()

include(cmake/jakt-executable.cmake)

add_subdirectory(runtime)

add_executable(jakt_stage0 bootstrap/stage0/jakt.cpp)
add_executable(Jakt::jakt_stage0 ALIAS jakt_stage0)
add_jakt_compiler_flags(jakt_stage0)
target_include_directories(jakt_stage0
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/stage0/runtime>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/runtime>
)
apply_output_rules(jakt_stage0)

set(SELFHOST_SOURCES
  runtime/prelude.jakt
  selfhost/codegen.jakt
  selfhost/compiler.jakt
  selfhost/error.jakt
  selfhost/formatter.jakt
  selfhost/ide.jakt
  selfhost/interpreter.jakt
  selfhost/lexer.jakt
  selfhost/parser.jakt
  selfhost/repl.jakt
  selfhost/typechecker.jakt
  selfhost/types.jakt
  selfhost/utility.jakt
)

add_jakt_executable(jakt_stage1
  COMPILER jakt_stage0
  MAIN_SOURCE selfhost/main.jakt
  MODULE_SOURCES ${SELFHOST_SOURCES}
  RUNTIME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime"
)
target_include_directories(jakt_stage1 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/runtime>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/runtime>
)
add_executable(Jakt::jakt_stage1 ALIAS jakt_stage1)
apply_output_rules(jakt_stage1)

if (FINAL_STAGE GREATER_EQUAL 2)
  add_jakt_executable(jakt_stage2
    COMPILER jakt_stage1
    MAIN_SOURCE selfhost/main.jakt
    MODULE_SOURCES ${SELFHOST_SOURCES}
    RUNTIME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime"
  )
  target_include_directories(jakt_stage2 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/runtime>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/runtime>
  )
  add_executable(Jakt::jakt_stage2 ALIAS jakt_stage2)
  apply_output_rules(jakt_stage2)
endif()
add_executable(Jakt::jakt ALIAS jakt_stage${FINAL_STAGE})

# Link runtime into build directory(ies) for relative pathing usage
#    Note: "If a sequential execution of multiple commands is required, use multiple execute_process() calls with a single COMMAND argument."
if (CMAKE_CONFIGURATION_TYPES)
  foreach (build_type IN LISTS CMAKE_CONFIGURATION_TYPES)
    execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/${build_type}/include")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E ${LINK_COMMAND} "${CMAKE_CURRENT_SOURCE_DIR}/runtime" "${CMAKE_CURRENT_BINARY_DIR}/${build_type}/include/runtime")
  endforeach()
else()
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/include")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E ${LINK_COMMAND}  "${CMAKE_CURRENT_SOURCE_DIR}/runtime" "${CMAKE_CURRENT_BINARY_DIR}/include/runtime")
endif()

add_custom_command(
  TARGET "jakt_stage${FINAL_STAGE}"
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E ${LINK_COMMAND}  "$<${LINK_GENEX}:jakt_stage${FINAL_STAGE}>" "$<TARGET_FILE_DIR:jakt_stage${FINAL_STAGE}>/jakt${CMAKE_EXECUTABLE_SUFFIX}"
  VERBATIM
)

if (NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# FIXME: Remove if we decide to use CTest
option(JAKT_BUILD_TESTING "Whether to build tests or not, default on" ON)

if (JAKT_BUILD_TESTING)
  add_jakt_executable(jakttest
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
  apply_output_rules(jakttest)
endif()
