#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXFILES       100
#define LINES_PER_PAGE 10

struct File
{
    FILE *handle;
    char *name;
};

/* Credit to Steve Huang
   https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_7:Exercise_8 */
static void print_page(struct File *file)
{
    int page_number = 1;
    int line_count  = 0;
    int c           = 0;
    int new_page    = 1;
    while ((c = fgetc(file->handle)) != EOF) {
        if (new_page) {
            /* print out the header */
            printf("[%s] page %d starts\n", file->name, page_number);
            new_page = 0;
            line_count = 1;
        }
        putchar(c);
        if (c == '\n' && ++line_count > LINES_PER_PAGE) {
            /* print out the footer */
            printf("[%s] page %d ends\n", file->name, page_number);
            /* skip another line so we can see it on screen */
            putchar('\n');
            new_page = 1;
            page_number++;
        }
    }

    if (!new_page) {
        /* file ended in the middle of a page, so we still need to
           print a footer */
        printf("[%s] page %d ends\n", file->name, page_number);
    }

    /* skip another line so we can see it on screen */
    putchar('\n');
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "usage: %s FILE...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pageno = 1;
    int nfiles = 0;
    struct File files[MAXFILES] = {{.handle=NULL, .name=NULL}};
    while (*(++argv)) {
        files[nfiles].handle = fopen(*argv, "r");
        if (!files[nfiles].handle) {
            fprintf(stderr, "could not open '%s'", *argv);
            perror("");
            exit(EXIT_FAILURE);
        }
        files[nfiles].name = *argv;

        print_page(&files[nfiles]);
        nfiles++;
        pageno++;
    }

    while (nfiles--)
        fclose(files[nfiles].handle);

    exit(EXIT_SUCCESS);
}
