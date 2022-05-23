#include <stdio.h>

int main()
{
    long blanks   = 0;
    long tabs     = 0;
    long newlines = 0;

    int c = 0;
    while ((c = getchar()) != EOF) {
        if (' ' == c)
            blanks++;
        else if ('\t' == c)
            tabs++;
        else if ('\n' == c)
            newlines++;
    }

    printf("blanks = %3ld; tabs = %3ld; newlines = %3ld",
           blanks, tabs, newlines);

    return 0;
}
