#include <stdio.h>

#define MAXLINE 1000

int getline_knr(char *line, int maxline);
void copy(char *to, char *from);

int main()
{
    int  len;               /* Current line length. */
    char line[MAXLINE + 1]; /* Current input line.*/

    /* Space used to store first MAXLINE characters of an oversized input
       string. */
    char oversized_line[MAXLINE + 1];

    while ((len = getline_knr(line, MAXLINE)) > 0) {
        if (len == MAXLINE) {
            /* Save as much of the oversized line as possible. */
            copy(oversized_line, line);

            /* Consume the rest of the line up to and including the newline. */
            int i = len;
            while (line[i - 1] != '\n') {
                i = getline_knr(line, MAXLINE);
                len += i;
            }

            /* Print the length of the oversized string and the first MAXLINE
               characters of said string. */
            printf("length = %d\n", len);
            printf("%s\n", oversized_line);
        } else {
            printf("length = %d\n", len);
            printf("%s", line);
        }
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

void copy(char *to, char *from)
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
