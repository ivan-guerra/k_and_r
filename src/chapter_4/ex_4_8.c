#include <stdio.h>

int getch(void);
void ungetch(int);

int main(void)
{
    int c = 0;
    int prev_c = 0;
    while ((c = getch()) != EOF) {
        /* '^' acts as a command to put the chars read since the last '^'
           command back on the input stream. */
        if ('^' == c)
            ungetch(prev_c);
        else {
            putchar(c);
            prev_c = c;
        }
    }
    return 0;
}

char buf = 0; /* buffer for ungetch */

int getch(void)
{
    char ret = buf;
    buf = 0;
    return (0 == ret) ? getchar() : ret;
}

void ungetch(int c)
{
    buf = c;
}
