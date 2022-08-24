#
# Build rules to build a jakt executable using the configured C++ compiler
# Note this file is used to build jakt itself and installed for jakt projects to use
#

function(add_jakt_compiler_flags target)
  target_compile_options("${target}" PRIVATE
    -Wno-unused-local-typedefs
    -Wno-unused-function
    -Wno-unused-variable
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
endfunction()

function(add_jakt_executable executable)
  cmake_parse_arguments(PARSE_ARGV 1 JAKT_EXECUTABLE "" "MAIN_SOURCE;RUNTIME_DIRECTORY;COMPILER" "MODULE_SOURCES")
  set(main_source "${CMAKE_CURRENT_LIST_DIR}/${JAKT_EXECUTABLE_MAIN_SOURCE}" )
  get_filename_component(main_base "${main_source}" NAME_WE)
  set(cpp_output "${executable}_${main_base}.cpp")

  if (NOT JAKT_EXECUTABLE_COMPILER)
    set(JAKT_EXECUTABLE_COMPILER Jakt::jakt_stage1)
  endif()

  if (NOT JAKT_EXECUTABLE_RUNTIME_DIRECTORY)
    set(JAKT_EXECUTABLE_RUNTIME_DIRECTORY "$<TARGET_PROPERTY:${JAKT_EXECUTABLE_COMPILER},INTERFACE_INCLUDE_DIRECTORIES>")
  endif()

  set(binary_tmp_dir "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp")


  add_custom_command(
    OUTPUT "${cpp_output}"
    COMMAND "${CMAKE_COMMAND}" -E make_directory ${binary_tmp_dir}
    COMMAND "$<TARGET_FILE:${JAKT_EXECUTABLE_COMPILER}>" -S --binary-dir "${binary_tmp_dir}" -R "${JAKT_EXECUTABLE_RUNTIME_DIRECTORY}" "${main_source}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp/${main_base}.cpp" "${cpp_output}"
    COMMAND "${CMAKE_COMMAND}" -E remove "${CMAKE_CURRENT_BINARY_DIR}/jakt_tmp/${main_base}.cpp"
    VERBATIM
    COMMENT "Building jakt file ${JAKT_EXECUTABLE_MAIN_SOURCE} with ${JAKT_EXECUTABLE_COMPILER}"
    MAIN_DEPENDENCY "${main_source}"
    DEPENDS ${JAKT_EXECUTABLE_MODULE_SOURCES}
  )
  add_custom_target("generate_${executable}" DEPENDS "${cpp_output}")

  add_executable("${executable}" "${cpp_output}")
  target_include_directories("${executable}" PRIVATE "$<BUILD_INTERFACE:${JAKT_EXECUTABLE_RUNTIME_DIRECTORY}>")
  add_dependencies("${executable}" "generate_${executable}")
  add_jakt_compiler_flags("${executable}")
endfunction()
