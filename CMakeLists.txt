
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(Jakt
        VERSION 0.0.1
        LANGUAGES CXX
        HOMEPAGE_URL https://github.com/SerenityOS/jakt
        DESCRIPTION "Jakt programming language compiler")

include(FetchContent)

FetchContent_Declare(
  Corrosion
  GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
  GIT_TAG v0.2.1
)
FetchContent_MakeAvailable(Corrosion)

corrosion_import_crate(MANIFEST_PATH "Cargo.toml")
corrosion_set_hostbuild(jakt)

# Create an alias for the rust binary, with extra steps because corrosion uses imported targets under the hood
add_executable(jakt_stage1 IMPORTED)
add_dependencies(jakt_stage1 jakt)
# FIXME: handle CMAKE_CONFIGURATION_TYPES.. boy this sure is a lot of work to alias an imported target
set(location_property IMPORTED_LOCATION)
if (CMAKE_BUILD_TYPE)
  string(TOUPPER "${CMAKE_BUILD_TYPE}" build_type_upper)
  set(location_property "IMPORTED_LOCATION_${build_type_upper}")
endif()
get_property(stage_one_location TARGET jakt PROPERTY "${location_property}")
set_property(TARGET jakt_stage1 PROPERTY "${location_property}" "${stage_one_location}")

# Helper to use Stage N-1 to build Stage N. Outputs stage N source as C++, and adds a C++ executable
function(compile_selfhost prev_stage_compiler new_compiler)
  cmake_parse_arguments(PARSE_ARGV 2 SELFHOST "" "MAIN_SOURCE" "MODULE_SOURCES")
  set(main_source "${CMAKE_CURRENT_LIST_DIR}/${SELFHOST_MAIN_SOURCE}" )
  get_filename_component(main_base "${main_source}" NAME_WE)
  set(cpp_output "${new_compiler}_${main_base}.cpp")

  add_custom_command(
    OUTPUT "${cpp_output}"
    COMMAND "$<TARGET_FILE:${prev_stage_compiler}>" -S --binary-dir "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp" "${main_source}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp/${main_base}.cpp" "${cpp_output}"
    COMMAND "${CMAKE_COMMAND}" -E remove "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp/${main_base}.cpp"
    VERBATIM
    COMMENT "Building jakt file ${SELFHOST_MAIN_SOURCE} with ${prev_stage_compiler}"
    MAIN_DEPENDENCY "${main_source}"
    DEPENDS ${SELFHOST_MODULE_SOURCES}
  )
  add_custom_target("generate_${new_compiler}" DEPENDS "${cpp_output}")

  add_executable("${new_compiler}" "${cpp_output}")
  add_dependencies("${new_compiler}" "generate_${new_compiler}")
  target_include_directories("${new_compiler}"
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/runtime>
      $<INSTALL_INTERFACE:runtime>
  )
  target_compile_options("${new_compiler}" PRIVATE
    -Wno-unused-local-typedefs
    -Wno-unused-function
    -Wno-unknown-warning-option
    -Wno-trigraphs
    -Wno-parentheses-equality
    -Wno-unqualified-std-cast-call
    -Wno-user-defined-literals
    -Wno-deprecated-declarations
  )
  target_compile_features("${new_compiler}" PRIVATE cxx_std_20)
endfunction()

set(SELFHOST_SOURCES
  selfhost/codegen.jakt
  selfhost/compiler.jakt
  selfhost/error.jakt
  selfhost/lexer.jakt
  selfhost/parser.jakt
  selfhost/prelude.jakt
  selfhost/typechecker.jakt
  selfhost/utility.jakt
)

compile_selfhost(jakt_stage1 jakt_stage2
  MAIN_SOURCE selfhost/main.jakt
  MODULE_SOURCES ${SELFHOST_SOURCES}
)

compile_selfhost(jakt_stage2 jakt_stage3
  MAIN_SOURCE selfhost/main.jakt
  MODULE_SOURCES ${SELFHOST_SOURCES}
)

if (NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()
