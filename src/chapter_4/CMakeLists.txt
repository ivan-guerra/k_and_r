cmake_minimum_required(VERSION 3.13...3.22)

project(chapter_4 DESCRIPTION "Chapter 4"
                  LANGUAGES   C
)

set(TARGET_NAMES
    ex_4_1
    ex_4_2
    ex_4_3
    ex_4_4
    ex_4_5
    ex_4_6
    ex_4_7
    ex_4_8
    ex_4_9
    ex_4_10
    ex_4_11
    ex_4_12
    ex_4_13
    ex_4_14
)

foreach(NAME ${TARGET_NAMES})
    add_executable(${NAME} ${NAME}.c)
endforeach(NAME ${TARGET_NAMES})

target_link_libraries(ex_4_5
    PUBLIC m
)

install(TARGETS ${TARGET_NAMES}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PROJECT_NAME}"
)
