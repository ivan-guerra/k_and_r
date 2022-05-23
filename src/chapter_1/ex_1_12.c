#include <stdio.h>

#define IN  1
#define OUT 0

int main()
{
    int c     = 0;
    int state = OUT;
    while ((c = getchar()) != EOF) {
        if (' ' == c || '\t' == c || '\n' == c) {
            if (IN == state)
                putchar('\n');
            state = OUT;
        } else {
            putchar(c);
            state = IN;
        }
    }

    return 0;
}
