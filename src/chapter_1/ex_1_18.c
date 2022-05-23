#include <stdio.h>

#define MAXLINE 1000

int getline_knr(char *line, int maxline);
int remove_trailing_whitespace(char *str, int len);
int is_blank_line(char *str, int len);

int main()
{
    int  len;               /* Current line length. */
    char line[MAXLINE + 1]; /* Current input line.*/

    while ((len = getline_knr(line, MAXLINE)) > 0) {
        len = remove_trailing_whitespace(line, len);
        if (!is_blank_line(line, len))
            printf("%s\n", line);
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

int remove_trailing_whitespace(char *str, int len)
{
    /* Do nothing if given an empty string or an invalid string length. */
    if (!str || (len < 0))
        return len;

    /* Walk the string in reverse until you hit the first non whitespace char
       or you have exhausted the entire length of the string. */
    int i = 0;
    for (i = len - 1; (i >= 0) && (('\t' == str[i]) || (' ' == str[i]) || ('\n' == str[i])); --i)
        ;

    /* Capture the case where the whole line is composed of whitespace. */
    if (i < 0) {
        str[0] = '\0';
        return 0;
    }

    /* Set the null terminator just after the first non whitespace char. */
    str[i + 1] = '\0';

    /* Return the length of the new string. */
    return (i + 1);
}

int is_blank_line(char *str, int len)
{
    /* The empty string or a string with a size <= 0 is considered blank. */
    if (!str || (len <= 0))
        return 1;

    return  ((1 == len) && ('\n' == str[0]));
}
