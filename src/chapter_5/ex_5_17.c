#include <stdio.h>
#include <string.h>
#include <strings.h> /* strcasecmp() */
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN     1000 /* max input line length */
#define MAXLINES   5000 /* max #lines to be sorted */
#define MAX_FIELDS 100  /* max number of fields within a line */

char *lineptr[MAXLINES] = {NULL}; /* pointers to text lines */

/* program options */
int numeric = 0; /* 1 if numeric sort */
int reverse = 0; /* 1 if sorting in descending order */
int fold    = 0; /* 1 for case insensitivity */
int dir     = 0; /* 1 if directory order is to be used */

/* input line field related variables */
char sep[MAXLEN] = {0}; /* field seperator */
int field        = 0;   /* field number (0 indicates no active field) */

int getline_knr(char *, int);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
char *alloc(int n);
void qsort_knr(void *v[], int left, int right,
           int (*comp)(void *, void *));
int get_fields(char *field_strs[], char *src);
void print_usage();

/* comparator function prototypes */
int numcmp(char *s1, char *s2);
int dircmp(const char *s1, const char *s2);
int fieldcmp(const char *s1, const char *s2);

/* See https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_5:Exercise_17#Solution_by_anonymous
   for a breakdown of two approaches to this problem. This program implements
   the first interpretation of the problem listed in the latter post:
   (1) Given no field specification switch, the program sorts the input lines
       applying any optional modifiers detected on the command line.
   (2) Given one or more -k switches, the program applies each field operation
       in the order they are given on the commandline. Each field operation
       sorts _entire input lines_ using the specified field as the sort key.
*/
int main(int argc, char **argv)
{
    int nlines  = 0; /* number of input lines read */

    /* read the User's input */
    if ((nlines = readlines(lineptr, MAXLINES)) < 0)
        printf("input too big to sort\n");

    ++argv; /* ignore the program name */
    while (--argc && argv) {
        switch (*argv[0]) {
            case '-':
                if (!strcmp("-n", *argv))
                    numeric = 1;
                else if (!strcmp("-r", *argv))
                    reverse = 1;
                else if (!strcmp("-f", *argv))
                    fold = 1;
                else if (!strcmp("-d", *argv))
                    dir = 1;
                else if ('t' == (*argv)[1])
                    strcpy(sep, (*argv) + 2);
                else if ('k' == (*argv)[1]) {
                    field = (*argv)[2] - '0';
                    for (size_t i = 3; (*argv)[i]; ++i) {
                        switch ((*argv)[i]) {
                            case 'n':
                                numeric = 1;
                                break;
                            case 'r':
                                reverse = 1;
                                break;
                            case 'f':
                                fold = 1;
                                break;
                            case 'd':
                                dir = 1;
                                break;
                            default:
                                print_usage();
                                return 1;
                        }
                    }
                    qsort_knr((void **)lineptr, 0, nlines - 1,
                            (int (*)(void *, void*))fieldcmp);

                    /* reset sort options in preparation for the next field
                       argument (if any) */
                    numeric = reverse = fold = dir = 0;
                }
                break;
            default:
                print_usage();
                return 1;
        }
        argv++;
    }

    if (!field) { /* only execute if field sorting hasn't occurred. */
        if (numeric) {
            qsort_knr((void **)lineptr, 0, nlines - 1,
                    (int (*)(void *, void*))numcmp);
        } else if (dir) {
            /* note, dircmp accounts for folding using the 'fold' global flag */
            qsort_knr((void **)lineptr, 0, nlines - 1,
                    (int (*)(void *, void*))dircmp);
        } else {
            qsort_knr((void **)lineptr, 0, nlines - 1,
                    (int (*)(void *, void*))(fold ? strcasecmp : strcmp));
        }
    }
    writelines(lineptr, nlines);

    return 0;
}

/* qsort: sort [vleft]...v[right] order is determined by the reverse global
   which is set to 0 for ascending and 1 for descending */
void qsort_knr(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if (reverse) { /* reverse: global set by the User via the -r switch */
            if ((*comp)(v[i], v[left]) > 0)
                swap(v, ++last, i);
        } else {
            if ((*comp)(v[i], v[left]) < 0)
                swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort_knr(v, left, last - 1, comp);
    qsort_knr(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
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

/* dircmp: compare only letters, numbers, and blanks */
int dircmp(const char *s1, const char *s2)
{
    while (*s1 && *s2) {
        while (*s1 && !isalpha(*s1) && !isdigit(*s1) && isspace(*s1))
            s1++;
        while (*s2 && !isalpha(*s2) && !isdigit(*s2) && isspace(*s2))
            s2++;

        char c1 = (fold) ? tolower(*s1) : *s1;
        char c2 = (fold) ? tolower(*s2) : *s2;
        if (c1 != c2)
            return (c1 - c2);

        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int fieldcmp(const char *s1, const char *s2)
{
    /* We make a temp copy of s1 before extracting the fields. This is
       because get_fields() alters its source string when it tokenizs the
       source string into its output parameter. */
    char s1_cpy[MAXLEN] = {0};
    strcpy(s1_cpy, s1);
    char *s1_fields[MAX_FIELDS] = {NULL};
    get_fields(s1_fields, s1_cpy);

    char s2_cpy[MAXLEN] = {0};
    strcpy(s2_cpy, s2);
    char *s2_fields[MAX_FIELDS] = {NULL};
    get_fields(s2_fields, s2_cpy);

    char *s1_field = s1_fields[field - 1];
    char *s2_field = s2_fields[field - 1];

    if (numeric)
        return numcmp(s1_field, s2_field);
    else if (dir)
        return dircmp(s1_field, s2_field);

    return (fold) ? strcasecmp(s1_field, s2_field) : strcmp(s1_field, s2_field);
}

/* get_fields: extract the fields seperated by the global seperator string
   sep */
int get_fields(char *fields_strs[], char *src)
{
    size_t i = 0;
    char *field = strtok(src, sep);
    while (field) {
        fields_strs[i++] = field;
        field = strtok(NULL, sep);
    }
    return i;
}

void print_usage()
{
    printf("usage: ex_5_17 [-r] [-n] [-f] [-d] "
           "[-t<SEP> -k<NUM>[n][r][f][d]]\n");
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
