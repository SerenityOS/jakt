include(FetchContent)

FetchContent_Declare(Serenity
    GIT_REPOSITORY https://github.com/serenityos/serenity.git
    GIT_TAG origin/master
    GIT_SHALLOW TRUE
    SOURCE_DIR serenity
    EXCLUDE_FROM_ALL
)

if (SERENITY_SOURCE_DIR)
    set(FETCHCONTENT_SOURCE_DIR_SERENITY
        ${SERENITY_SOURCE_DIR}
        CACHE PATH
        "Developer's preexisting SerenityOS source directory" FORCE
    )
    message(STATUS
        "Using preexisting AK directory from SERENITY_SOURCE_DIR: ${SERENITY_SOURCE_DIR}/AK"
    )
endif()

FetchContent_GetProperties(Serenity)
if (NOT serenity_POPULATED)
    FetchContent_Populate(Serenity)
endif()

file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/AK)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AK)
file(GLOB serenity_AK_FILES "${serenity_SOURCE_DIR}/AK/*")
foreach(file IN LISTS serenity_AK_FILES)
    get_filename_component(name ${file} NAME)
    create_symlink(${file} ${CMAKE_CURRENT_SOURCE_DIR}/AK/${name})
endforeach()

configure_file("AK/Debug.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/AK/Debug.h")

set(JAKT_AK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "jakt_ak_source_dir")

# Needed by AK's CMakeLists.
function(serenity_install_headers name)
endfunction()
function(serenity_install_sources name)
endfunction()

add_subdirectory(${JAKT_AK_SOURCE_DIR}/AK)

list(FILTER AK_SOURCES EXCLUDE REGEX ".*Time.cpp") # None of these build on windows, but they're not necessary for the runtime anyway.
set(IMPORTED_AK_SOURCES ${AK_SOURCES})

set(RUNTIME_SOURCES
    ${IMPORTED_AK_SOURCES}
    IO/File.cpp
    Jakt/PrettyPrint.cpp
    Jakt/ByteStringBuilder.cpp
)

# FIXME: create a new external_project foreach(target IN LISTS JAKT_RUNTIME_TARGETS)
function(make_jakt_runtime_available JAKT_RUNTIME_TARGET)
  if (NOT DEFINED JAKT_RUNTIME_TARGET)
    message(FATAL_ERROR "make_jakt_runtime_available called without a required target argument")
  endif()

  cmake_parse_arguments(PARSE_ARGV 1 JAKT_RUNTIME "" "" "VAR_NAME")
  message(STATUS "Making the jakt runtime available for ${JAKT_RUNTIME_TARGET}")
  set(library_name jakt_runtime_${JAKT_RUNTIME_TARGET})
  add_library(${library_name} STATIC ${RUNTIME_SOURCES})

  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND WIN32)
      # Need to also link in libclang_rt.
      execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -target ${JAKT_RUNTIME_TARGET} -print-resource-dir
        OUTPUT_VARIABLE CLANG_RESOURCE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
      )
      string(REGEX MATCH "^[^-]*" arch ${JAKT_RUNTIME_TARGET})
      if (arch STREQUAL "amd64")
        set(arch "x86_64")
      elseif(arch STREQUAL "x86")
        set(arch "i686")
      elseif(arch STREQUAL "arm64")
        set(arch "aarch64")
      endif()
      set(libclang_rt_path "${CLANG_RESOURCE_DIR}/lib/windows/clang_rt.builtins-${arch}.lib")
      message(STATUS "Linking in libclang_rt: ${libclang_rt_path}")
      target_link_libraries(${library_name} PUBLIC "${libclang_rt_path}")

      set("LIBCLANG_RT_PATH_${JAKT_RUNTIME_TARGET}" ${libclang_rt_path} CACHE FILEPATH "Path to libclang_rt for ${JAKT_RUNTIME_TARGET}" FORCE)
  endif()

  add_jakt_compiler_flags(${library_name})
  target_include_directories(${library_name}
  PRIVATE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  PUBLIC
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/runtime>"
  )

  apply_output_rules(${library_name} TARGET_DIR ${JAKT_RUNTIME_TARGET})
  target_link_libraries(${library_name} PRIVATE Threads::Threads)

  set(main_name jakt_main_${JAKT_RUNTIME_TARGET})
  add_library(${main_name} STATIC Main.cpp)
  add_jakt_compiler_flags(${main_name})
  target_include_directories(${main_name}
  PRIVATE
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  PUBLIC
      "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/runtime>"
  )

  apply_output_rules(${main_name} TARGET_DIR ${JAKT_RUNTIME_TARGET})

  set_target_properties(${runtime_name} ${main_name} PROPERTIES POSITION_INDEPENDENT_CODE ON)

  add_library(Jakt::jakt_runtime_${JAKT_RUNTIME_TARGET} ALIAS jakt_runtime_${JAKT_RUNTIME_TARGET})
  add_library(Jakt::jakt_main_${JAKT_RUNTIME_TARGET} ALIAS jakt_main_${JAKT_RUNTIME_TARGET})

  if (JAKT_RUNTIME_VAR_NAME)
    set(${JAKT_RUNTIME_VAR_NAME}
        ${library_name}
        ${main_name}
        PARENT_SCOPE)
  endif()
endfunction(make_jakt_runtime_available)

make_jakt_runtime_available("${JAKT_TARGET_TRIPLE}")

add_library(Jakt::jakt_runtime ALIAS jakt_runtime_${JAKT_TARGET_TRIPLE})
add_library(Jakt::jakt_main ALIAS jakt_main_${JAKT_TARGET_TRIPLE})
