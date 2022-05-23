cmake_minimum_required(VERSION 3.13...3.22)

project(chapter_1 DESCRIPTION "Chapter 1"
                  LANGUAGES   C
)

set(TARGET_NAMES
    ex_1_1
    ex_1_2
    ex_1_3
    ex_1_4
    ex_1_5
    ex_1_6
    ex_1_7
    ex_1_8
    ex_1_9
    ex_1_10
    ex_1_11
    ex_1_12
    ex_1_13
    ex_1_14
    ex_1_15
    ex_1_16
    ex_1_17
    ex_1_18
    ex_1_19
)

foreach(NAME ${TARGET_NAMES})
    add_executable(${NAME} ${NAME}.c)
endforeach(NAME ${TARGET_NAMES})

# Exercise 1-2 has us put an undefined escape sequence in the
# printf format string which triggers a warning and causes
# compilation to fail with -Werror. We disable -Werror just for that
# exercise.
target_compile_options(ex_1_2
    PRIVATE -Wno-error
)

# Disable warning regarding 'unused' state variable.
target_compile_options(ex_1_13
    PRIVATE -Wno-unused-but-set-variable
)

install(TARGETS ${TARGET_NAMES}
    RUNTIME DESTINATION "${KNR_BIN_DIR}/${PROJECT_NAME}"
)
