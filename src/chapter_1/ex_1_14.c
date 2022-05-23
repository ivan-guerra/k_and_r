#include <stdio.h>

#define MAX_CHARS 255

int main()
{
    int intervals[MAX_CHARS] = {0}; /* Table of char frequencies. */
    int c = 0;

    /* Count input character frequency. */
    while ((c = getchar()) != EOF)
        intervals[c]++;

    printf("\t\tHistogram of Input Char Frequencies\n");

    /* Compute the char with the highest frequency. */
    int max_frequency = intervals[0];
    for (int i = 1; i < MAX_CHARS; ++i) {
        if (intervals[i] > max_frequency)
            max_frequency = intervals[i];
    }

    /* Construct an array of blanks where blanks[i] tells us how
       many blanks need to be printed for each char frequency. */
    int blanks[MAX_CHARS] = {0};
    for (int i = 0; i < MAX_CHARS; ++i)
        blanks[i] = max_frequency - intervals[i];

    /* Print the bars of the histogram. */
    for (int i = 0; i< max_frequency; ++i) {
        for (int j = 0; j < MAX_CHARS; ++j) {
            /* Only print those characters whose freq > 0. */
            if (intervals[j]) {
                if (blanks[j]) {
                    printf("%2c ", ' ');
                    blanks[j]--;
                } else {
                    printf("%2c ", '+');
                }
            }
        }
        putchar('\n');
    }

    /* Print a bar to seperate frequency markers from characters. */
    for (int i = 0; i < MAX_CHARS; ++i) {
        if (intervals[i])
            printf("-- ");
    }
    putchar('\n');

    /* Print the charatcers at the bottom of the graph. */
    for (int i = 0; i < MAX_CHARS; ++i) {
        /* Only print those characters whose freq > 0. */
        if (intervals[i]) {
            /* Take special care when printing escaped chars. */
            if ('\n' == i)
                printf("\\n ");
            else if ('\t' == i)
                printf("\\t ");
            else if ('\b' == i)
                printf("\\b ");
            else if (' ' == i)
                printf("bl");
            else
                printf("%2c ", (char)i);
        }
    }
    putchar('\n');

    return 0;
}
