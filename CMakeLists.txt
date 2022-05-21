cmake_minimum_required(VERSION 3.13...3.22)

# Require out-of-source builds.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

project(k_and_r
    VERSION 1.0
    DESCRIPTION "The C Programming Language solutions"
)

set(KNR_BIN_DIR "${CMAKE_SOURCE_DIR}/bin"
    CACHE STRING "${PROJECT_NAME} binary directory.")

add_subdirectory(src)
