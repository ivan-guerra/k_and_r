#include <stdio.h>

#define IN  1
#define OUT 0
#define MAX_CHARS_IN_WORD 20 /* Max allowed word length. */

int main()
{
    int intervals[MAX_CHARS_IN_WORD] = {0};
    int state    = OUT;
    int c        = 0;
    int word_len = 0;
    while ((c = getchar()) != EOF) {
        if (' ' == c || '\t' == c || '\n' == c) {
            state = OUT;

            /* Guard against words that have a length longer than
               our hardcoded limit. This means we ignore words >
               MAX_CHARS_IN_WORD length. */
            if (word_len < MAX_CHARS_IN_WORD)
                intervals[word_len - 1]++;
            word_len = 0;
        } else {
            word_len++;
            state = IN;
        }
    }

    printf("\t\tHistogram of Word Lengths\n");

    /* Compute the word length with the highest frequency. */
    int max_frequency = intervals[0];
    for (int i = 1; i < MAX_CHARS_IN_WORD; ++i) {
        if (intervals[i] > max_frequency)
            max_frequency = intervals[i];
    }

    /* Construct an array of blanks where blanks[i] tells us how
       many blanks need to be printed for each word length. */
    int blanks[MAX_CHARS_IN_WORD] = {0};
    for (int i = 0; i < MAX_CHARS_IN_WORD; ++i)
        blanks[i] = max_frequency - intervals[i];

    for (int i = 0; i< max_frequency; ++i) {
        for (int j = 0; j < MAX_CHARS_IN_WORD; ++j) {
            if (blanks[j]) {
                printf("%2c ", ' ');
                blanks[j]--;
            } else {
                printf("%2c ", '+');
            }
        }
        putchar('\n');
    }

    /* Print a bar to seperate frequency markers from word lengths. */
    for (int i = 0; i < MAX_CHARS_IN_WORD; ++i)
        printf("-- ");
    putchar('\n');

    /* Print the word lengths. */
    for (int i = 0; i < MAX_CHARS_IN_WORD; ++i)
        printf("%2d ", i + 1);
    putchar('\n');

    return 0;
}
