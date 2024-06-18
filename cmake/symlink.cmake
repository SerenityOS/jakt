# On windows, use `mklink /J` to create a junction point for directories, and `mklink /H` for files.
# because literally everything else is broken one way or another.
# Everywhere else, just ask cmake.
if (WIN32)
    function(create_symlink source target)
        cmake_parse_arguments(CSL "DIRECTORY" "" "" ${ARGN})
        set(LINK_FLAG "/H")
        if (CSL_DIRECTORY)
            set(LINK_FLAG "/J")
        endif()
        cmake_path(NATIVE_PATH source NORMALIZE source_native)
        cmake_path(NATIVE_PATH target NORMALIZE target_native)
        execute_process(COMMAND cmd /c ${CMAKE_COMMAND} -E rm -f ${target_native} && mklink ${LINK_FLAG} ${target_native} ${source_native} RESULT_VARIABLE result)
        if (NOT ${result} EQUAL 0)
            message(FATAL_ERROR "Failed to create symlink ${target} -> ${source}")
        endif()
    endfunction()
    function(add_symlink_command source target)
        cmake_parse_arguments(ASL "DIRECTORY" "" "" ${ARGN})
        set(LINK_FLAG "/H")
        if (ASL_DIRECTORY)
            set(LINK_FLAG "/J")
        endif()
        cmake_path(NATIVE_PATH source NORMALIZE source_native)
        cmake_path(NATIVE_PATH target NORMALIZE target_native)
        add_custom_command(
            COMMAND cmd /c ${CMAKE_COMMAND} -E rm -f ${target_native} && mklink ${LINK_FLAG} ${target_native} ${source_native}
            DEPENDS ${source}
            ${ASL_UNPARSED_ARGUMENTS}
        )
    endfunction()
else()
    function(create_symlink source target)
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${target} RESULT_VARIABLE result)
        if (NOT ${result} EQUAL 0)
            message(FATAL_ERROR "Failed to create symlink ${target} -> ${source}")
        endif()
    endfunction()
    function(add_symlink_command source target)
        cmake_parse_arguments(ASL "DIRECTORY" "" "" ${ARGN})
        add_custom_command(
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${target}
            DEPENDS ${source}
            ${ASL_UNPARSED_ARGUMENTS}
        )
    endfunction()
endif()
