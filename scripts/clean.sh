#!/bin/bash

# This script cleans up the source tree leaving it as if a fresh clone of
# the repository was made.

# Source the project configuration.
source config.sh

# Remove the binary directory.
if [ -d $KNR_BIN_DIR ]
then
    echo -e "${LGREEN}Removing '$KNR_BIN_DIR'${NC}"
    rm -r $KNR_BIN_DIR
fi

# Remove the CMake build directory.
if [ -d $KNR_BUILD_DIR ]
then
    echo -e "${LGREEN}Removing '$KNR_BUILD_DIR'${NC}"
    rm -r $KNR_BUILD_DIR
fi
