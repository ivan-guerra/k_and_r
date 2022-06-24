# Create a K&R developer's image. This Dockerfile will build an Alpine Linux
# image that can be used to build and run K&R solutions. To get the most out
# of this image, mount the repository as a volume under /k_and_r. You can
# then edit the source on your host machine in your IDE of choice and build/run
# your edits in the container using the included scripts. See dev.sh and
# README.md for more details.
FROM alpine:latest

# Install all the packages needed to build the solutions.
RUN apk add --no-cache \
        build-base     \
        gdb            \
        valgrind       \
        cmake          \
        bash

# Drop the User in the scripts directory so they can immediately call build.sh,
# run.sh, etc.
WORKDIR /k_and_r/scripts
