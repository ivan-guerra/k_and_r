#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

static FILE *open_file(const char *filename, const char *mode)
{

    FILE *f = fopen(filename, mode);
    if (!f) {
        fprintf(stderr, "unable to open file '%s':", filename);
        perror("");
        return NULL;
    }
    return f;
}

static int filecmp(FILE *f1, FILE *f2)
{
    static char str1[MAXLINE] = {0};
    static char str2[MAXLINE] = {0};
    char *read1 = NULL;
    char *read2 = NULL;
    int line = 1;

    do {
        read1 = fgets(str1, MAXLINE, f1);
        read2 = fgets(str2, MAXLINE, f2);

        if (!read1 || !read2) /* exit if EOF of one or both files is reached */
            break;

        if (strcmp(str1, str2))
            return line;

        line++;
    } while (read1 && read2);

    return (!read1 && !read2) ? 0 : line;
}

int main(int argc, char *argv[])
{
    if (3 != argc) {
        fprintf(stderr, "usage: %s FILE1 FILE2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *f1 = open_file(argv[1], "r");
    if (!f1)
        exit(EXIT_FAILURE);

    FILE *f2 = open_file(argv[2], "r");
    if (!f2) {
        fclose(f1);
        exit(EXIT_FAILURE);
    }

    int diff_line = filecmp(f1, f2);
    if (diff_line)
        printf("%s and %s differ at line %d\n", argv[1], argv[2], diff_line);

    fclose(f1);
    fclose(f2);

    exit(EXIT_SUCCESS);
}
