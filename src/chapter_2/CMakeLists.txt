cmake_minimum_required(VERSION 3.13...3.22)

project(chapter_2 DESCRIPTION "Chapter 2"
                  LANGUAGES   C
)

set(TARGET_NAMES
    ex_2_1
    ex_2_2
    ex_2_3
    ex_2_4
    ex_2_5
    ex_2_6
    ex_2_7
    ex_2_8
    ex_2_9
    ex_2_10
)

foreach(NAME ${TARGET_NAMES})
    add_executable(${NAME} ${NAME}.c)
endforeach(NAME ${TARGET_NAMES})

install(TARGETS ${TARGET_NAMES}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PROJECT_NAME}"
)
