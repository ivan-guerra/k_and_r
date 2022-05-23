#include <stdio.h>

#define IN  1
#define OUT 0

int main()
{
    /* Potential Test Cases:
     * (1) Single line with no special chars and N words. -> PASS
     * (2) Single line with only special chars. -> FAIL doesn't
     *     handle \b character correctly.
     * (3) Single blank line. -> PASS
     * (4) [char, word, newline] count exceeding INT_MAX -> FAIL
     *     there are no checks for integer overflow.
     */
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);

    return 0;
}
