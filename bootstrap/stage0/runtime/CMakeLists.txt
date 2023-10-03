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
file(COPY ${serenity_SOURCE_DIR}/AK DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("AK/Debug.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/AK/Debug.h")

set(JAKT_AK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "jakt_ak_source_dir")

# Needed by AK's CMakeLists.
function(serenity_install_headers name)
endfunction()
function(serenity_install_sources name)
endfunction()

add_subdirectory(${JAKT_AK_SOURCE_DIR}/AK)

if(CMAKE_HOST_WIN32)
  list(FILTER AK_SOURCES EXCLUDE REGEX ".*Time.cpp") # None of these build on windows, but they're not necessary for the runtime anyway.
endif()
set(IMPORTED_AK_SOURCES ${AK_SOURCES})

set(RUNTIME_SOURCES
    ${IMPORTED_AK_SOURCES}
    IO/File.cpp
    Jakt/PrettyPrint.cpp
    Jakt/DeprecatedStringBuilder.cpp
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
