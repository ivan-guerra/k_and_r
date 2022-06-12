#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100 /* ungetch max buffer size */

int getch(void);
void ungetch(int);
int getint(int *pn);

int main(void)
{
    int n       = 0;
    int retcode = 0;
    while ((retcode = getint(&n)) != EOF) {
        if (retcode)
            printf("int = %d\n", n);
        else
            printf("%c", getch());
    }

    return 0;
}

int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;     /* next free position in buf */

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

int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        char sign_char = c;     /* buffer the sign character */
        if (!isdigit(c = getch())) {
            ungetch(c);         /* replace non digit character */
            ungetch(sign_char); /* replace +/- sign */
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}
