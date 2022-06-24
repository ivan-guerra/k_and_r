# The C Programming Language 2nd Edition Solutions

This project contains solutions to exercises in [The C Programming Language
2nd Edition](https://en.wikipedia.org/wiki/The_C_Programming_Language) text.
The solutions cover chapters 1-7 (chapter 8 was excluded).

### Running the Solutions

This project includes a [Dockerfile](Dockerfile) for building a developer's
image. The developer's image can be used to build and run the solutions.
Optionally, you can edit the source on a host system and then build, run, and
debug your changes in the Docker container. The image includes GDB and
Valgrind. See [dev.sh](scripts/dev.sh) for more details.

The following commands are meant to be run from within a container executed
using the [dev.sh](scripts/dev.sh) script or from a Linux system with GCC
and CMake3.13+ installed.

To build all solutions

```
./build.sh
```

To run exercise X-Y

```
./run ex_X_Y
```
