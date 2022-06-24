cmake_minimum_required(VERSION 3.13...3.22)

project(chapter_7 DESCRIPTION "Chapter 7"
                  LANGUAGES   C
)

set(TARGET_NAMES
    ex_7_1
    ex_7_2
    ex_7_3
    ex_7_5
    ex_7_6
    ex_7_7
    ex_7_8
    ex_7_9
)

foreach(NAME ${TARGET_NAMES})
    add_executable(${NAME} ${NAME}.c)
endforeach(NAME ${TARGET_NAMES})

target_compile_options(ex_7_9
    # The function/macro defined in ex_7_9 is intentionally unused.
    PRIVATE -Wno-unused-function
)

install(TARGETS ${TARGET_NAMES}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PROJECT_NAME}"
)
