#include <stdio.h>

#define MAXLINE 1000

int getline_knr(char *line, int limit);

int main()
{
    int  len = 0;                 /* Current line length. */
    char line[MAXLINE + 1] = {0}; /* Current input line.*/
    while ((len = getline_knr(line, MAXLINE)) > 0)
        printf("%s", line);

    return 0;
}

int getline_knr(char *line, int limit)
{
    int c = 0;
    int i = 0;
    /* You can use */
    for (i = 0; i < limit; ++i) {
        if ((c = getchar()) != EOF) {
            if ('\n' != c)
                line[i] = c;
            else
                break;
        } else {
            break;
        }
    }

    if ('\n' == c) {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}
