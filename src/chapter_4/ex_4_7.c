#include <stdio.h>
#include <string.h>

#define BUFSIZE 100 /* ungetch max buffer size */

int getch(void);
void ungetch(int);
void ungets(const char *s);

int main(void)
{
    int c = 0;
    size_t i = 0;
    char s[BUFSIZE] = {0};
    while ((c = getch()) != EOF) {
        /* '^' acts as a command to put the chars read since the last '^'
           command back on the input stream. */
        if ('^' == c) {
            s[i] = '\0';
            ungets(s);
            i = 0;
        } else {
            s[i++] = c;
            putchar(c);
        }
    }
    return 0;
}

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(const char *s)
{
    for (int i = strlen(s) - 1; i >= 0; --i)
        ungetch(s[i]);
}
