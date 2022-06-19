cmake_minimum_required(VERSION 3.13...3.22)

set(PARENT_PROJECT_NAME ${PROJECT_NAME})

project(ex_6_4 DESCRIPTION "ex_6_4"
               LANGUAGES   C
)

add_executable(${PROJECT_NAME}
    ${PROJECT_NAME}.c
    WordTree.c
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE -D_POSIX_C_SOURCE=200809L # Required to use getline().
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PARENT_PROJECT_NAME}"
)
