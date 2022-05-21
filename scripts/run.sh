#!/bin/bash

# This script allows the User to run an exercise's corresponding executable.
# The script usage is as follows: run.sh EXERCISE_NAME
# where EXERCISE_NAME is an executable name of the form ex_[0-9]+_[0-9]+
# For example, run.sh ex_5_2 tells the script to run the solution for
# exercise 5-2.

source config.sh

if [ $# -eq 0 ]
then
    echo -e "${LRED}error missing executable name${NC}"
    echo -e "${LRED}usage: run.sh EXERCISE_NAME${NC}"
    echo -e "${LRED}EXAMPLE\n\trun.sh ex_1_1${NC}"
    exit 1
fi

EXE_NAME="$1"

# Parse the chapter number out of the executable name. The chapter number
# is always the decimal number between the '_' characters in the executable
# name. For example, given the name 'exe_123_1', the statement below will set
# CHAPTER_NUM=123
CHAPTER_NUM=$(echo ${EXE_NAME} | sed -n "s/^.*_\([0-9]\+\)_.*$/\1/p")

EXE_PATH="${KNR_BIN_DIR}/chapter_${CHAPTER_NUM}/${EXE_NAME}"
if [ -f "${EXE_PATH}" ]
then
    # The executable was found, run it.
    ${EXE_PATH}
else
    echo -e "${LRED}error executable '${EXE_PATH}' not found${NC}"
    echo -e "${LRED}make sure you run build.sh before running this script${NC}"
fi
