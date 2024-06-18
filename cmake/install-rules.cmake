
set(CMAKE_INSTALL_MESSAGE NEVER)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Allow package maintainers to freely override the path for the configs
set(Jakt_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/Jakt"
    CACHE PATH "CMake package config location relative to the install prefix")
mark_as_advanced(Jakt_INSTALL_CMAKEDIR)

configure_file(cmake/install-config.cmake.in JaktConfig.cmake @ONLY)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/JaktConfig.cmake"
    DESTINATION "${Jakt_INSTALL_CMAKEDIR}"
    COMPONENT Jakt_Development
)

install(
    FILES cmake/jakt-executable.cmake
    DESTINATION "${Jakt_INSTALL_CMAKEDIR}"
    COMPONENT Jakt_Development
)

if (NOT JAKT_BUILDING_STAGE0)
    set(stages 1)
else()
    set(stages 0 1 2)
endif()
foreach (stage IN LISTS stages)
  if (FINAL_STAGE LESS "${stage}")
    break()
  endif()
  set(target_name "jakt_stage${stage}")
  install(
    TARGETS ${target_name}
    EXPORT JaktTargets
    RUNTIME #
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Jakt_Runtime
    LIBRARY #
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT Jakt_Runtime
        NAMELINK_COMPONENT Jakt_Development
    ARCHIVE #
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT Jakt_Development
  )
endforeach()

# FIXME: foreach(target IN LISTS JAKT_RUNTIME_TARGETS) for this
function(jakt_install_runtime TARGET)
  if(NOT DEFINED TARGET)
    message(FATAL_ERROR "jakt_install_runtime called without a required target argument")
  endif()

  install(
      TARGETS "jakt_runtime_${TARGET}"
      EXPORT JaktTargets
      RUNTIME #
          DESTINATION "${CMAKE_INSTALL_BINDIR}/${TARGET}"
          COMPONENT Jakt_Runtime
      LIBRARY #
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/${TARGET}"
          COMPONENT Jakt_Runtime
          NAMELINK_COMPONENT Jakt_Development
      ARCHIVE #
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/${TARGET}"
          COMPONENT Jakt_Development
  )

  install(
      TARGETS "jakt_main_${TARGET}"
      EXPORT JaktTargets
      RUNTIME #
          DESTINATION "${CMAKE_INSTALL_BINDIR}/${TARGET}"
          COMPONENT Jakt_Runtime
      LIBRARY #
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/${TARGET}"
          COMPONENT Jakt_Runtime
          NAMELINK_COMPONENT Jakt_Development
      ARCHIVE #
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/${TARGET}"
          COMPONENT Jakt_Development
  )
endfunction(jakt_install_runtime)

# Install runtime files. In the future we should probably have a bazillion rules
#   for compiling this into a static archive for different configs
install(DIRECTORY "runtime"
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      COMPONENT Jakt_Development
      FILES_MATCHING PATTERN "*.h"
                     PATTERN "*.cpp"
                     PATTERN "*.jakt"
                     PATTERN "utility"
)

install(
    EXPORT JaktTargets
    NAMESPACE Jakt::
    DESTINATION "${Jakt_INSTALL_CMAKEDIR}"
    COMPONENT Jakt_Development
)

# Make a symlink bin/jakt to the final compiler we created, but install it after the real targets
# to make sure that if we're using hardlinks, the link can actually be created
set(final_stage_target "jakt_stage${FINAL_STAGE}")
set(final_stage_install_target "$<TARGET_FILE:${final_stage_target}>")
if (NO_SYMLINKS)
    set(final_stage_install_target "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${final_stage_install_target}")
endif()

install(CODE "include(\"${CMAKE_CURRENT_LIST_DIR}/symlink.cmake\")")
install(CODE "create_symlink(\"${final_stage_install_target}\" \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/jakt${CMAKE_EXECUTABLE_SUFFIX}\")")
