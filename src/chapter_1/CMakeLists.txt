cmake_minimum_required(VERSION 3.13...3.22)

project(chapter_1 DESCRIPTION "Chapter 1"
                  LANGUAGES   C
)

set(TARGET_NAMES
    ex_1_1
)

foreach(NAME ${TARGET_NAMES})
    add_executable(${NAME} ${NAME}.c)
endforeach(NAME ${TARGET_NAMES})

install(TARGETS ${TARGET_NAMES}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PROJECT_NAME}"
)
