#include <stdio.h>

int main()
{
    int c = 0;
    while ((c = getchar()) != EOF) {
        if (' ' == c) {
            putchar(c);
            /* Skip subsequent blank chars. */
            while ((c = getchar()) == ' ')
                ;
        }
        putchar(c);
    }

    return 0;
}
