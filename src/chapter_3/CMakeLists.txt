cmake_minimum_required(VERSION 3.13...3.22)

project(chapter_3 DESCRIPTION "Chapter 3"
                  LANGUAGES   C
)

set(TARGET_NAMES
    ex_3_1
    ex_3_2
    ex_3_3
    ex_3_4
    ex_3_5
    ex_3_6
)

foreach(NAME ${TARGET_NAMES})
    add_executable(${NAME} ${NAME}.c)
endforeach(NAME ${TARGET_NAMES})

install(TARGETS ${TARGET_NAMES}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PROJECT_NAME}"
)
