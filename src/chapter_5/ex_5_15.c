#include <stdio.h>
#include <string.h>
#include <strings.h> /* strcasecmp() */
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN   1000 /* max input line length */
#define MAXLINES 5000 /* max #lines to be sorted */

char *lineptr[MAXLINES] = {NULL}; /* pointers to text lines */
int fold = 0;                     /* 1 for case insensitivity */

int getline_knr(char *, int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
char *alloc(int n);

/* the asc (ascending) field tells whether the sort should be done in
   ascending order (asc=0) or descending order (asc=1) */
void qsort_knr(void *v[], int left, int right,
           int (*comp)(void *, void *), int asc);
int numcmp(char *, char *);

int main(int argc, char **argv)
{
    int nlines  = 0; /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    int reverse = 0; /* 1 if sorting in descending order */

    ++argv;
    while (--argc && argv) {
        switch (*argv[0]) {
            case '-':
                if (!strcmp("-n", *argv))
                    numeric = 1;
                else if (!strcmp("-r", *argv))
                    reverse = 1;
                else if (!strcmp("-f", *argv))
                    fold = 1;
                break;
            default:
                printf("usage: ex_5_15 [-r] [-n] [-f]\n");
                return 1;
        }
        argv++;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (numeric) {
            qsort_knr((void **)lineptr, 0, nlines - 1,
                    (int (*)(void *, void*))numcmp, reverse);
        } else {
            qsort_knr((void **)lineptr, 0, nlines - 1,
                    (int (*)(void *, void*))(fold ? strcasecmp : strcmp),
                    reverse);
        }
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void qsort_knr(void *v[], int left, int right,
           int (*comp)(void *, void *), int asc)
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if (asc) {
            if ((*comp)(v[i], v[left]) > 0)
                swap(v, ++last, i);
        } else {
            if ((*comp)(v[i], v[left]) < 0)
                swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort_knr(v, left, last - 1, comp, asc);
    qsort_knr(v, last + 1, right, comp, asc);
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
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
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; ++i)
        printf ("%s\n", lineptr[i]);
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
