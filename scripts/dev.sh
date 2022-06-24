#!/bin/bash

# This script launches a docker container that is ready to build and run the
# K&R exercise solutions. The docker container will launch with the host user's
# permissions and will mount the project directory as a volume under /k_and_r.
# The idea here is that you can edit files on a host PC in your IDE of
# choice. When you are ready to build/run, execute this launch script and
# build/run cosmo from within the container.

# Source the project configuration.
source config.sh

# Use the latest K&R development container. If you don't want to pull
# from the repo, build the latest image using the Dockerfile at the project
# root and then update KNR_IMAGE to point to the new image.
KNR_IMAGE="iguerra130154/k_and_r:latest"

docker run --rm -it                      \
    -v "${KNR_PROJECT_PATH}":/k_and_r    \
    -u $(id -u ${USER}):$(id -g ${USER}) \
    ${KNR_IMAGE}                         \
    /bin/sh
