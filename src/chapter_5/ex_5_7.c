#define _XOPEN_SOURCE 700 /* Used to make sure we get time.h features. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINES 50  /* max #lines to be sorted */
#define MAXLEN   100 /* max length of any input line */

char *lineptr[MAXLINES];

int getline_knr(char *, int);
char *alloc(int);
int readlines(char *lineptr[], int nlines);
int readlines_prealloc(char *linebuf, char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort_knr(char *lineptr[], int left, int right);
long get_timediff_nsec(const struct timespec *t1, const struct timespec *t2);
int sort_strings(char *linebuf, int prealloc);

int main(void)
{
    struct timespec start, end;

    /* time the code using readlines with calls to alloc */
    long delta_no_alloc;
    clock_gettime(CLOCK_MONOTONIC, &start);
    sort_strings(NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &end);

    delta_no_alloc = get_timediff_nsec(&end, &start);
    printf("execution time (no pre-allocation) = %ld ns.\n", delta_no_alloc);

    /* time the code with string buffer pre allocation */
    // long delta_alloc;
    // char linebuf[(MAXLEN + 1) * MAXLINES];

    // clock_gettime(CLOCK_MONOTONIC, &start);
    // sort_strings(linebuf, 1);
    // clock_gettime(CLOCK_MONOTONIC, &end);

    // delta_alloc = get_timediff_nsec(&end, &start);
    // printf("execution time (with pre-allocation) = %ld ns.\n", delta_alloc);

    return 0;
}

int sort_strings(char *linebuf, int prealloc)
{
    int nlines;
    if (prealloc)
        nlines = readlines_prealloc(linebuf, lineptr, MAXLINES);
    else
        nlines = readlines(lineptr, MAXLINES);

    if (nlines < 0) {
        printf("error: input too big to sort\n");
        return 1;
    }

    qsort_knr(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);

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

/* readlines: read input lines and store them in linebuf */
int readlines_prealloc(char *linebuf, char *lineptr[], int maxlines)
{
    int len, nlines;

    nlines = 0;
    while ((len = getline_knr(linebuf, MAXLEN)) > 0) {
        if (nlines >= maxlines) {
            return -1;
        } else {
            linebuf[len - 1] = '\0';
            lineptr[nlines++] = linebuf;
            linebuf += MAXLEN + 1; /* quite wasteful but sufficient for the exercise */
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

/* qsort: sort v[left]...v[right] into increasing order */
void qsort_knr(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort_knr(v, left, last - 1);
    qsort_knr(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

long get_timediff_nsec(const struct timespec *t1, const struct timespec *t2)
{
    static const long SEC_TO_NSEC = 1000000000L;
    long t1_nsec = t1->tv_sec * SEC_TO_NSEC + t1->tv_nsec;
    long t2_nsec = t2->tv_sec * SEC_TO_NSEC + t2->tv_nsec;

    return (t1_nsec - t2_nsec);
}
