# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git rev-parse HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_VER
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Generate version_info.cpp
configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/version.jakt.in
  ${CMAKE_SOURCE_DIR}/selfhost/version.jakt
  @ONLY
)
