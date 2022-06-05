#include <stdio.h>
#include <string.h>

#define BUFSIZE 100 /* ungetch max buffer size */

int getch(void);
void ungetch(int);

int main(void)
{
    ungetch(EOF);
    int is_eof = getch();
    /* Change the type of buf below to int or char. See if you get different
       output depending on the type of buf. */
    if (EOF == is_eof)
        printf("successfully ungetch() EOF\n");
    else
        printf("failed to ungetch() EOF\n");

    return 0;
}

/* We change the type of buf from array of char to array of int. This allows
   us to handle the EOF correctly. On some implementations, this change doesn't
   matter given that char is by default signed and EOF is a value that exists
   in the signed char range. That said, you shouldn't depend on implementation
   details. */
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
