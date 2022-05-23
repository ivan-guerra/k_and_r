#include <stdio.h>

int main()
{
    int c = 0;
    while ((c = getchar()) != EOF) {
        if ('\t' == c) {
            putchar('\\');
            putchar('t');
        } else if ('\b' == c) {
            putchar('\\');
            putchar('b');
        } else if ('\\' == c) {
            putchar('\\');
            putchar('\\');
        } else {
            putchar(c);
        }
    }

    return 0;
}
