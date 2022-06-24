#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE  1000 /* max length of any input line */
#define MAXFILES 100  /* max number of input files supported */

struct File
{
    FILE *handle;
    char *name;
};

static void print_usage(const char *err)
{
    fprintf(stderr, "%s", err);
    fprintf(stderr, "usage: find -x -n pattern [FILE]...\n");
}

static void find_pattern(
    const char *line,
    const char *pattern,
    int except,
    int number,
    long lineno,
    char *filename)
{
    /* code below is nearly identical to that given in the original example */
    if ((strstr(line, pattern) != NULL) != except) {
        if (filename) /* print the filename if its specified */
            printf("(%s) ", filename);

        if (number)
            printf("%ld:", lineno);
        printf("%s", line);
    }
}

int main(int argc, char *argv[])
{
    int c         = '\0';
    int except    = 0;
    int number    = 0;
    int use_stdin = 0;

    if (argc <= 1) {
        print_usage("");
        exit(EXIT_FAILURE);
    }

    while ((--argc > 0) && ((*++argv)[0] == '-')) {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    fprintf(stderr, "error illegal option %c\n", c);
                    print_usage("");
                    exit(EXIT_FAILURE);
            }
        }
    }

   if (!*argv) { /* did the user specify a search pattern? */
        print_usage("error missing search pattern\n");
        exit(EXIT_FAILURE);
    }
    char *pattern = *argv;

    argv++;
    int nfiles = 0;
    struct File files[MAXFILES] = {{.handle=NULL, .name=NULL}};
    if (*argv) { /* did the user specify one or more files to search? */
        for(nfiles = 0; *argv; ++nfiles, ++argv) {
            files[nfiles].handle = fopen(*argv, "r");
            if (!files[nfiles].handle) {
                fprintf(stderr, "unable to open '%s'", *argv);
                perror("");
                exit(EXIT_FAILURE);
            }
            files[nfiles].name = *argv;
        }
    } else { /* no filenames given, read from STDIN */
        use_stdin = 1;
    }

    char line[MAXLINE] = {0};
    int lineno = 1;
    if (use_stdin) {
        while (fgets(line, MAXLINE, stdin)) {
            find_pattern(line, pattern, except, number, lineno, NULL);
            lineno++;
        }
    } else {
        for (int i = 0; i < nfiles; ++i) {
            while (fgets(line, MAXLINE, files[i].handle)) {
                find_pattern(line, pattern, except, number, lineno,
                             files[i].name);
                lineno++;
            }
            lineno = 1; /* reset line number in prep for the next file */
        }
    }

    while (nfiles--) /* release all file handles if any */
        fclose(files[nfiles].handle);

    exit(EXIT_SUCCESS);
}
