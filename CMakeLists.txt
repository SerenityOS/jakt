cmake_minimum_required(VERSION 3.16..3.21)
cmake_policy(SET CMP0091 NEW)

project(Jakt
        VERSION 0.0.1
        LANGUAGES CXX C
        HOMEPAGE_URL https://github.com/SerenityOS/jakt
        DESCRIPTION "Jakt programming language compiler")

# FIXME: Serenity's CMake toolchain files don't seem to include these,
#        and not having them makes CMake find host packages for a serenity build...
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}" CACHE FILEPATH "Path to a compiler launcher program, e.g. ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}" CACHE FILEPATH "Path to a compiler launcher program, e.g. ccache")
endif()

find_package(Threads REQUIRED)

SET(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
SET(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
find_package(Clang CONFIG)

set(JAKT_CPP_AUTO_IMPORT_PROCESSOR_DEFAULT none)
if (Clang_FOUND)
  set(JAKT_CPP_AUTO_IMPORT_PROCESSOR_DEFAULT clang)
  find_program(CLANG_PATH clang REQUIRED
    PATHS "${CLANG_INSTALL_PREFIX}/bin"
    NO_DEFAULT_PATH
  )
  execute_process(
    COMMAND
      ${CLANG_PATH} -print-resource-dir
    OUTPUT_VARIABLE
      JAKT_CLANG_RESOURCE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

include(GNUInstallDirs)

set(NO_SYMLINKS_DEFAULT OFF)
if (CMAKE_HOST_WIN32)
  set(NO_SYMLINKS_DEFAULT ON)
endif()

set(FINAL_STAGE "1" CACHE STRING "Compiler stage to stop at, either 1 (default) or 2)")
option(NO_SYMLINKS "Use hard links instead of symlinks. Useful for unprivileged Windows users" "${NO_SYMLINKS_DEFAULT}")
option(SERENITY_SOURCE_DIR PATH "Path of an existing SerenityOS checkout to pull AK files from")
set(CPP_AUTO_IMPORT_PROCESSOR "${JAKT_CPP_AUTO_IMPORT_PROCESSOR_DEFAULT}" CACHE STRING "'import extern' processor to use (default=none/clang/libcpp/none)")

if (NO_SYMLINKS)
  set(LINK_COMMAND create_hardlink)
  set(LINK_GENEX TARGET_FILE)
else()
  set(LINK_COMMAND create_symlink)
  set(LINK_GENEX TARGET_FILE_NAME)
endif()

set(JAKT_USING_CLANG OFF)
set(JAKT_CPP_AUTO_IMPORT_PROCESSOR "${CPP_AUTO_IMPORT_PROCESSOR}")
set(JAKT_CPP_AUTO_IMPORT_EXTRA_SOURCES
  selfhost/cpp_import/none.jakt
)

if (CPP_AUTO_IMPORT_PROCESSOR STREQUAL "clang")
  set(JAKT_USING_CLANG ON)
  set(JAKT_CPP_AUTO_IMPORT_EXTRA_SOURCES
    selfhost/cpp_import/clang.jakt
    selfhost/cpp_import/clang_c.jakt
  )
elseif(CPP_AUTO_IMPORT_PROCESSOR STREQUAL "libcpp")
  set(JAKT_CPP_AUTO_IMPORT_EXTRA_SOURCES
    selfhost/cpp_import/libcpp.jakt
    selfhost/cpp_import/hashmap.jakt
    selfhost/cpp_import/vector.jakt
  )
endif()

message(STATUS "Using ${JAKT_CPP_AUTO_IMPORT_PROCESSOR} as the cpp import processor (using Clang=${JAKT_USING_CLANG}, resource dir=${JAKT_CLANG_RESOURCE_DIR})")

set(in_build_prefix "")
get_cmake_property(is_multi_config GENERATOR_IS_MULTI_CONFIG)
if (is_multi_config)
  set(in_build_prefix "$<CONFIG>/")
endif()

function(apply_output_rules target)
  cmake_parse_arguments(PARSE_ARGV 1 OUTPUT_RULES "" "TARGET_DIR" "")
  set(output_prefix "${PROJECT_BINARY_DIR}/${in_build_prefix}")
  set_property(TARGET ${target} PROPERTY "ARCHIVE_OUTPUT_DIRECTORY" "${output_prefix}lib/${OUTPUT_RULES_TARGET_DIR}")
  set_property(TARGET ${target} PROPERTY "LIBRARY_OUTPUT_DIRECTORY" "${output_prefix}lib/${OUTPUT_RULES_TARGET_DIR}")
  set_property(TARGET ${target} PROPERTY "RUNTIME_OUTPUT_DIRECTORY" "${output_prefix}bin/${OUTPUT_RULES_TARGET_DIR}")
endfunction()

include(cmake/jakt-executable.cmake)

add_subdirectory(runtime)

if (NOT ${JAKT_TARGET_TRIPLE} STREQUAL ${JAKT_DEFAULT_TARGET_TRIPLE})
  jakt_make_runtime_available(TARGET ${JAKT_TARGET_TRIPLE})
endif()

set(JAKT_BOOTSTRAP_COMPILER "" CACHE FILEPATH "Path to an existing bootstrap jakt compiler")
set(JAKT_BUILDING_STAGE0 NO)
if (CMAKE_CROSSCOMPILING OR NOT (JAKT_BOOTSTRAP_COMPILER STREQUAL ""))
  if (JAKT_BOOTSTRAP_COMPILER STREQUAL "")
    find_program(HOST_JAKT jakt REQUIRED HINTS jakt-install/bin)
  else()
    set(HOST_JAKT "${JAKT_BOOTSTRAP_COMPILER}")
  endif()
  add_executable(Jakt::jakt IMPORTED)
  set_target_properties(Jakt::jakt PROPERTIES IMPORTED_LOCATION "${HOST_JAKT}")
  set(BOOSTRAP_COMPILER ${HOST_JAKT})
  message(STATUS "Using host jakt at ${HOST_JAKT} to bootstrap")
else()
  set(JAKT_BUILDING_STAGE0 YES)
  file(GLOB JAKT_STAGE0_SOURCES CONFIGURE_DEPENDS "bootstrap/stage0/*.cpp")
  file(GLOB JAKT_STAGE0_RUNTIME_SOURCES CONFIGURE_DEPENDS "bootstrap/stage0/runtime/*.cpp")
  file(GLOB JAKT_STAGE0_RUNTIME_LIB_SOURCES CONFIGURE_DEPENDS "bootstrap/stage0/runtime/*/*.cpp")
  list(APPEND JAKT_STAGE0_ALL_SOURCES
      ${JAKT_STAGE0_SOURCES}
      ${JAKT_STAGE0_RUNTIME_SOURCES}
      ${JAKT_STAGE0_RUNTIME_LIB_SOURCES}
  )

  # Note: This currently does not build under windows, but it is not needed by the runtime.
  list(FILTER JAKT_STAGE0_ALL_SOURCES EXCLUDE REGEX ".*AK/Time\.cpp$")
  list(FILTER JAKT_STAGE0_ALL_SOURCES EXCLUDE REGEX ".*AK/DOSPackedTime\.cpp$")

  add_executable(jakt_stage0 "${JAKT_STAGE0_ALL_SOURCES}")
  add_executable(Jakt::jakt_stage0 ALIAS jakt_stage0)
  add_jakt_compiler_flags(jakt_stage0)
  target_link_libraries(jakt_stage0 PRIVATE Threads::Threads)
  target_include_directories(jakt_stage0
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/stage0/runtime>
    INTERFACE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bootstrap/stage0/runtime>
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/runtime>
  )
  apply_output_rules(jakt_stage0)
  if (MSVC)
      target_link_options(jakt_stage0 PRIVATE LINKER:/STACK:0x800000)
  endif()
  set(BOOSTRAP_COMPILER jakt_stage0)
endif()

message(STATUS "Building for target ${JAKT_TARGET_TRIPLE}")

set(SELFHOST_SOURCES
  selfhost/build.jakt
  selfhost/codegen.jakt
  selfhost/compiler.jakt
  selfhost/error.jakt
  selfhost/formatter.jakt
  selfhost/git.jakt
  selfhost/ide.jakt
  selfhost/ids.jakt
  selfhost/interpreter.jakt
  selfhost/lexer.jakt
  selfhost/parser.jakt
  selfhost/project.jakt
  selfhost/repl.jakt
  selfhost/repl_backend/common.jakt
  selfhost/repl_backend/default.jakt
  selfhost/typechecker.jakt
  selfhost/types.jakt
  selfhost/utility.jakt
  selfhost/platform.jakt
  selfhost/cpp_import/common.jakt
  ${JAKT_CPP_AUTO_IMPORT_EXTRA_SOURCES}
)

# FIXME: STDLIB target needed
set(SELFHOST_STDLIB_SOURCES
  jakt__libc__io.cpp
  jakt__arguments.cpp
  jakt__file_iterator.cpp
  jakt__platform.cpp
  jakt__platform__utility.cpp
  jakt__path.cpp
)

if(CMAKE_HOST_WIN32)
  list(APPEND SELFHOST_STDLIB_SOURCES
    jakt__platform__windows_fs.cpp
    jakt__platform__windows_errno.cpp
    jakt__platform__windows_process.cpp
  )
  list(APPEND SELFHOST_STDLIB_SOURCES platform__windows_compiler.cpp)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  list(APPEND SELFHOST_STDLIB_SOURCES
    jakt__platform__posix_fs.cpp
    jakt__platform__darwin_errno.cpp
    jakt__platform__posix_process.cpp
  )
  list(APPEND SELFHOST_STDLIB_SOURCES platform__posix_compiler.cpp)
elseif(CMAKE_HOST_UNIX)
  list(APPEND SELFHOST_STDLIB_SOURCES
    jakt__platform__posix_fs.cpp
    jakt__platform__posix_errno.cpp
    jakt__platform__posix_process.cpp
  )
  list(APPEND SELFHOST_STDLIB_SOURCES platform__posix_compiler.cpp)
else()
  list(APPEND SELFHOST_STDLIB_SOURCES
    jakt__platform__unknown_fs.cpp
    jakt__platform__unknown_process.cpp
  )
  list(APPEND SELFHOST_STDLIB_SOURCES platform__unknown_compiler.cpp)
endif()

set(SELFHOST_CONFIGS
  "jakt.cpp_import.processor=${JAKT_CPP_AUTO_IMPORT_PROCESSOR}"
)

if(NOT JAKT_CLANG_RESOURCE_DIR STREQUAL "")
  list(APPEND SELFHOST_CONFIGS "jakt.cpp_import.processor.clang.resource_dir=${JAKT_CLANG_RESOURCE_DIR}")
endif()


add_jakt_executable(jakt_stage1
  COMPILER "${BOOSTRAP_COMPILER}"
  MAIN_SOURCE selfhost/main.jakt
  MODULE_SOURCES ${SELFHOST_SOURCES}
  STDLIB_SOURCES ${SELFHOST_STDLIB_SOURCES}
  RUNTIME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime"
  CONFIGS ${SELFHOST_CONFIGS}
)

if (JAKT_USING_CLANG)
  target_link_libraries(jakt_stage1 PRIVATE libclang)
endif()

target_include_directories(jakt_stage1
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/runtime>
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/runtime>
  PRIVATE
    ${CLANG_INCLUDE_DIRS}
)
add_executable(Jakt::jakt_stage1 ALIAS jakt_stage1)
apply_output_rules(jakt_stage1)
if (MSVC)
    target_link_options(jakt_stage1 PRIVATE LINKER:/STACK:0x800000)
endif()

if (FINAL_STAGE GREATER_EQUAL 2)
  add_jakt_executable(jakt_stage2
    COMPILER jakt_stage1
    MAIN_SOURCE selfhost/main.jakt
    MODULE_SOURCES ${SELFHOST_SOURCES}
    STDLIB_SOURCES ${SELFHOST_STDLIB_SOURCES}
    RUNTIME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime"
    CONFIGS ${SELFHOST_CONFIGS}
  )
  target_include_directories(jakt_stage2
    INTERFACE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/runtime>
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/runtime>
    PRIVATE
      ${CLANG_INCLUDE_DIRS}
  )
  if (JAKT_USING_CLANG)
    target_link_libraries(jakt_stage2 PRIVATE libclang)
  endif()
  add_executable(Jakt::jakt_stage2 ALIAS jakt_stage2)
  apply_output_rules(jakt_stage2)
  if (MSVC)
    target_link_options(jakt_stage2 PRIVATE LINKER:/STACK:0x800000)
  endif()
endif()

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
add_executable(Jakt::jakt ALIAS jakt_stage${FINAL_STAGE})

if (NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
  jakt_install_runtime(${JAKT_TARGET_TRIPLE})
endif()

# FIXME: Remove if we decide to use CTest
option(JAKT_BUILD_TESTING "Whether to build tests or not, default on" ON)

if (JAKT_BUILD_TESTING AND NOT CMAKE_CROSSCOMPILING)
  add_jakt_executable(jakttest
    MAIN_SOURCE
      jakttest/jakttest.jakt
    MODULE_SOURCES
      jakttest/error.jakt
      jakttest/parser.jakt
      jakttest/utility.jakt
    INCLUDES
      "${CMAKE_CURRENT_SOURCE_DIR}/jakttest"
    RUNTIME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime"
  )
  add_jakt_compiler_flags(jakttest)
  target_sources(jakttest PRIVATE
     jakttest/fs.cpp
     jakttest/os.cpp
     jakttest/process.cpp
  )
  apply_output_rules(jakttest)
endif()
