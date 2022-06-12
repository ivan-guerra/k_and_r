#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES         50  /* max #lines to be sorted */
#define MAXLEN           100 /* max length of any input line */
#define DEFAULT_TAIL_NUM 10  /* default number of */

char *lineptr[MAXLINES];

int getline_knr(char *, int);
char *alloc(int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int start);

int main(int argc, char **argv)
{
    int n = DEFAULT_TAIL_NUM;

    ++argv; /* skip program string */
    while (--argc && argv) {
        switch (*argv[0]) {
            case '-':
                n = atoi((*argv) + 1);
                argv++;
                break;
            default:
                printf("usage: ex_5_13 -<NUM>");
                return 1;
        }
    }

    if (n < 0) {
        printf("error invalid n: %d\n", n);
        return 1;
    }

    int nlines = readlines(lineptr, MAXLINES);
    if (nlines < 0) {
        printf("error input exceeds line limit of %d\n", MAXLINES);
        return 1;
    }

    if (!nlines) /* there was no input to tail, just return */
        return 0;

    int delta = nlines - n;
    if (delta < 0) /* n exceeds number of available output lines */
        /* print all the strings in the buffer */
        writelines(lineptr, -delta, 0);
    else           /* print out last n lines */
        writelines(lineptr, n, delta);

    return 0;
}

/* getline_knr: get the next line of input */
int getline_knr(char *line, int maxline)
{
    int c = 0;
    int i = 0;
    for (i = 0; (i < maxline) && ((c = getchar()) != EOF) && ('\n' != c); ++i)
        line[i] = c;

    if ('\n' == c) {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    return 0;
}

/*readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN + 1];

    nlines = 0;
    while ((len = getline_knr(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int start)
{
    int j = start;
    for (int i = 0; i < nlines; ++i)
        printf ("%s\n", lineptr[j++]);
}
