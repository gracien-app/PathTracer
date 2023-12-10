# Minimum version supporting Apple Silicon.
cmake_minimum_required(VERSION 3.19)

project(PathTracer
        VERSION 2.0
        DESCRIPTION "Unidirectional, CPU-based, non-Spectral, Path-Tracing rendering engine."
        LANGUAGES CXX)

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# External dependencies
add_subdirectory(external/SFML)

# Make sure user fetched the submodule while cloning.
# If they didn't, try to fetch for them.
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(CHECK_SUBMODULES "Check submodules during build" ON)
    if(CHECK_SUBMODULES)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/SFML/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! CHECK_SUBMODULES was turned off or failed. Please update submodules and try again.")
endif()

# Libraries
add_subdirectory(src)

# Applications, executable binaries.
add_subdirectory(apps)
