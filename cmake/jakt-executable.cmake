#
# Build rules to build a jakt executable using the configured C++ compiler
# Note this file is used to build jakt itself and installed for jakt projects to use
#

# FIXME: Should this live in a toolchain file?
set(JAKT_TARGET_TRIPLE_IN "${CMAKE_SYSTEM_PROCESSOR}-unknown-${CMAKE_SYSTEM_NAME}-unknown")
string(TOLOWER ${JAKT_TARGET_TRIPLE_IN} JAKT_DEFAULT_TARGET_TRIPLE)
set(JAKT_TARGET_TRIPLE "${JAKT_DEFAULT_TARGET_TRIPLE}" CACHE STRING "Target triple for jakt compiler")

function(add_jakt_compiler_flags target)
  target_compile_options("${target}" PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wno-dangling-reference
    -Wno-deprecated-declarations
    -Wno-implicit-fallthrough # !!
    -Wno-invalid-offsetof     # LibJS JIT fallout; invalid offset_of on WeakLink (ignored in serenity proper)
    -Wno-literal-suffix
    -Wno-maybe-uninitialized
    -Wno-parentheses-equality
    -Wno-reorder-ctor
    -Wno-return-type
    -Wno-trigraphs
    -Wno-type-limits
    -Wno-unknown-attributes # Silence warning about `no_unique_address` -  It does not apply on windows, and clang-cl just warns about it.
    -Wno-unknown-warning-option
    -Wno-unqualified-std-cast-call
    -Wno-unused-but-set-variable
    -Wno-unused-command-line-argument
    -Wno-unused-function
    -Wno-unused-lambda-capture
    -Wno-unused-local-typedefs
    -Wno-unused-parameter
    -Wno-unused-result
    -Wno-unused-value        # FIXME: Diagnose/avoid this during code gen, as it might mean something
    -Wno-unused-variable
    -Wno-user-defined-literals
  )
  if (MSVC)
    # For clang-cl, which shows up to CMake as MSVC and accepts both kinds of arguments
    target_compile_options("${target}" PRIVATE /permissive- /utf-8 /EHsc-)
  else()
    target_compile_options("${target}" PRIVATE -fno-exceptions -fdiagnostics-color=always)
  endif()
  if (CYGWIN OR MSYS)
    target_compile_options("${target}" PRIVATE -Wa,-mbig-obj)
  endif()
  target_compile_features("${target}" PRIVATE cxx_std_23)

  if (WIN32)
    target_compile_options("${target}" PRIVATE
        # AK complains about having to include <memory>, not a problem for us.
        "-Wno-#warnings"
    )
    cmake_policy(GET CMP0091 msvc_runtime_prop_enabled)
    if (NOT msvc_runtime_prop_enabled STREQUAL "NEW")
      message(WARNING "CMake Policy CMP0091 is not set to NEW, linker errors from jakt_runtime may result")
    endif()
    set_property(TARGET "${target}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()
endfunction()

function(add_jakt_executable executable)
  cmake_parse_arguments(PARSE_ARGV 1 JAKT_EXECUTABLE "" "MAIN_SOURCE;RUNTIME_DIRECTORY;COMPILER;TARGET" "MODULE_SOURCES;STDLIB_SOURCES;INCLUDES;CONFIGS")
  set(main_source "${CMAKE_CURRENT_LIST_DIR}/${JAKT_EXECUTABLE_MAIN_SOURCE}" )
  get_filename_component(main_base "${main_source}" NAME_WE)
  get_filename_component(main_directory "${main_source}" DIRECTORY)

  if (NOT JAKT_EXECUTABLE_TARGET)
    set(JAKT_EXECUTABLE_TARGET "${JAKT_TARGET_TRIPLE}")
  endif()

  set(cpp_files
    "${main_base}.cpp"
    ${JAKT_EXECUTABLE_STDLIB_SOURCES}
  )

  file(TO_NATIVE_PATH "/" _separator)

  foreach(module_source IN LISTS JAKT_EXECUTABLE_MODULE_SOURCES)
    set(module_source_real "${CMAKE_CURRENT_LIST_DIR}/${module_source}")
    cmake_path(RELATIVE_PATH module_source_real BASE_DIRECTORY "${main_directory}" OUTPUT_VARIABLE module_base_relative)

    string(REPLACE "${_separator}" "__" module_source "${module_base_relative}")
    string(REPLACE "/" "__" module_source "${module_source}") # Slashes are technically valid on windows
    get_filename_component(module_base "${module_source}" NAME_WE)
    list(APPEND cpp_files "${module_base}.cpp")
  endforeach()

  if (NOT JAKT_EXECUTABLE_COMPILER)
    set(JAKT_EXECUTABLE_COMPILER Jakt::jakt)
  endif()

  if (TARGET JAKT_EXECUTABLE_COMPILER)
    set(JAKT_EXECUTABLE_COMPILER_PATH "$<TARGET_FILE:${JAKT_EXECUTABLE_COMPILER}>")
  else()
    set(JAKT_EXECUTABLE_COMPILER_PATH "${JAKT_EXECUTABLE_COMPILER}")
  endif()

  if (NOT JAKT_EXECUTABLE_RUNTIME_DIRECTORY)
    set(runtime_path "$<TARGET_PROPERTY:${JAKT_EXECUTABLE_COMPILER},INTERFACE_INCLUDE_DIRECTORIES>")
  else()
    set(runtime_path "${JAKT_EXECUTABLE_RUNTIME_DIRECTORY}")
  endif()

  set(JAKT_EXECUTABLE_COMPILER_INCLUDES
    "${main_directory}"
    "${runtime_path}"
    ${JAKT_EXECUTABLE_INCLUDES}
  )
  list(REMOVE_DUPLICATES JAKT_EXECUTABLE_COMPILER_INCLUDES)

  foreach(entry IN LISTS cpp_files)
    get_filename_component(entry_base "${entry}" NAME_WE)
    list(APPEND cpp_files "${entry_base}_specializations.cpp")
  endforeach()

  set(configs)
  foreach(config IN LISTS JAKT_EXECUTABLE_CONFIGS)
    list(APPEND configs "--config" "${config}")
  endforeach()

  set(binary_tmp_dir "${CMAKE_CURRENT_BINARY_DIR}/${executable}_tmp")
  list(TRANSFORM cpp_files PREPEND "${binary_tmp_dir}/")

  file(MAKE_DIRECTORY "${binary_tmp_dir}")

  add_custom_command(
    OUTPUT ${cpp_files}
    COMMAND "${JAKT_EXECUTABLE_COMPILER_PATH}"
      -S
      $<$<CONFIG:Release>:-O>
      -T "${JAKT_EXECUTABLE_TARGET}"
      --binary-dir "${binary_tmp_dir}"
      --runtime-path "${runtime_path}"
      -I "$<JOIN:${JAKT_EXECUTABLE_COMPILER_INCLUDES},;-I>"
      ${configs}
      "${main_source}"
    VERBATIM
    COMMENT "Building jakt file ${JAKT_EXECUTABLE_MAIN_SOURCE} with ${JAKT_EXECUTABLE_COMPILER}"
    MAIN_DEPENDENCY "${main_source}"
    DEPENDS ${JAKT_EXECUTABLE_MODULE_SOURCES}
    COMMAND_EXPAND_LISTS
  )
  add_custom_target("generate_${executable}" DEPENDS ${cpp_files})

  add_executable("${executable}")
  foreach(file IN LISTS cpp_files)
    target_sources("${executable}" PRIVATE "${file}")
    set_source_files_properties("${file}" PROPERTIES GENERATED TRUE)
  endforeach()

  add_jakt_compiler_flags("${executable}")

  target_include_directories("${executable}" BEFORE PRIVATE "$<BUILD_INTERFACE:${runtime_path}>")
  foreach(path IN LISTS JAKT_EXECUTABLE_INCLUDES)
    target_include_directories("${executable}" PRIVATE "$<BUILD_INTERFACE:${path}>")
  endforeach()

  target_link_libraries("${executable}" PRIVATE Jakt::jakt_main_${JAKT_EXECUTABLE_TARGET})
  target_link_libraries("${executable}" PRIVATE Jakt::jakt_runtime_${JAKT_EXECUTABLE_TARGET})
  add_dependencies("${executable}" "generate_${executable}")
endfunction()
