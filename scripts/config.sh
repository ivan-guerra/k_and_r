#!/bin/bash

# This script configures the default search paths for many of the binaries
# and configuration files used by the project. Other scripts may source this
# file to find the resources that they need.

LGREEN='\033[1;32m'
LRED='\033[1;31m'
NC='\033[0m'

CWD=$(pwd)

# Root directory.
KNR_PROJECT_PATH=$(dirname ${CWD})

# Scripts directory.
KNR_SCRIPTS_PATH="${KNR_PROJECT_PATH}/scripts"

# Binary directory.
KNR_BIN_DIR="${KNR_PROJECT_PATH}/bin"

# CMake build files (see build.sh for more info).
KNR_BUILD_DIR="${KNR_PROJECT_PATH}/build"
