#include <stdio.h>

#define MAXLINE    1000
#define CHAR_LIMIT 80

int getline_knr(char *line, int maxline);

int main()
{
    int  len;               /* Current line length. */
    char line[MAXLINE + 1]; /* Current input line.*/

    while ((len = getline_knr(line, MAXLINE)) > 0) {
        if (len > CHAR_LIMIT)
            printf("%s", line);
    }

    return 0;
}

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
