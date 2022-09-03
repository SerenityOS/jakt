
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

set(stages 0 1 2)
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

install(
    TARGETS jakt_runtime
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

# Install runtime files. In the future we should probably have a bazillion rules
#   for compiling this into a static archive for different configs
install(DIRECTORY "runtime"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT Jakt_Development
        FILES_MATCHING PATTERN "*.h"
                       PATTERN "*.cpp"
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
set(final_stage_install_target "$<TARGET_FILE_NAME:${final_stage_target}>")
if (NO_SYMLINKS)
    set(final_stage_install_target "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${final_stage_install_target}")
endif()

install(CODE "execute_process(COMMAND \
                              ${CMAKE_COMMAND} -E ${LINK_COMMAND} \
                                                  \"${final_stage_install_target}\" \
                                                  ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/jakt${CMAKE_EXECUTABLE_SUFFIX})"
)
