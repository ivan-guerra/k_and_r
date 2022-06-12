cmake_minimum_required(VERSION 3.13...3.22)

project(chapter_5 DESCRIPTION "Chapter 5"
                  LANGUAGES   C
)

set(TARGET_NAMES
    ex_5_1
    ex_5_2
    ex_5_3
    ex_5_4
    ex_5_5
    ex_5_7
    ex_5_8
    ex_5_9
    ex_5_10
    ex_5_11
    ex_5_12
    ex_5_13
    ex_5_14
    ex_5_15
    ex_5_16
    ex_5_17
    ex_5_18
)

foreach(NAME ${TARGET_NAMES})
    add_executable(${NAME} ${NAME}.c)
endforeach(NAME ${TARGET_NAMES})

install(TARGETS ${TARGET_NAMES}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PROJECT_NAME}"
)
