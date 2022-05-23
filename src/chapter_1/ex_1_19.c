
#include <stdio.h>

#define MAXLINE 1000

int getline_knr(char *line, int maxline);
void reverse(char *str, int len);

int main()
{
    int  len;               /* Current line length. */
    char line[MAXLINE + 1]; /* Current input line.*/

    /* Reverse the User input in MAXLINE chunks. */
    while ((len = getline_knr(line, MAXLINE)) > 0) {
        if ('\n' == line[len - 1])
            /* If the line ends in a newline, reverse only those characters
               preceding the newline. */
            reverse(line, len - 1);
        else
            reverse(line, len);

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

void reverse(char *str, int len)
{
    /* Return if given an empty string or invalid length. */
    if (!str || (len <= 0))
        return;

    /* Swap characters as you traverse the string from the left and right
       ends. Stop once you meet (odd length string) or cross (even length
       string). */
    int i, j;
    for (i = 0, j = len - 1; i < j; ++i, --j) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}
