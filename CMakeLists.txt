cmake_minimum_required(VERSION 3.13...3.22)

project(k_and_r
    VERSION 1.0
    DESCRIPTION "The C Programming Language 2nd Edition solutions"
)

set(KNR_BIN_DIR "${CMAKE_SOURCE_DIR}/bin"
    CACHE STRING "${PROJECT_NAME} binary directory.")

add_subdirectory(src)
