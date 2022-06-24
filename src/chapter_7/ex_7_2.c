#include <stdio.h>
#include <ctype.h>

#define FMT            "%#x"
#define MAX_LINE_WIDTH 80

int main(void)
{
    int c   = 0;
    int col = 0;
    while ((c = getchar()) != EOF) {
        if ('\n' == c) {
            col = 0;
        } else if (col >= MAX_LINE_WIDTH) {
            putchar('\n');
            col = 0;
        }

        /* isgraph() doesn't return true for spaces so we must check
           for space chars seperately. */
        if (isgraph(c) || isspace(c))
            putchar(c);
        else
            printf(FMT, c);

        col++;
    }
    return 0;
}
