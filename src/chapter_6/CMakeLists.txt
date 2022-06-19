cmake_minimum_required(VERSION 3.13...3.22)

project(chapter_6 DESCRIPTION "Chapter 6"
                  LANGUAGES   C
)

set(TARGET_NAMES
    ex_6_5
)

foreach(NAME ${TARGET_NAMES})
    add_executable(${NAME} ${NAME}.c)
endforeach(NAME ${TARGET_NAMES})

install(TARGETS ${TARGET_NAMES}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PROJECT_NAME}"
)

add_subdirectory(ex_6_1)
add_subdirectory(ex_6_2)
add_subdirectory(ex_6_3)
add_subdirectory(ex_6_4)
add_subdirectory(ex_6_6)
