#include <stdio.h>

#define COL_WIDTH 80

int isspace_knr(char c);

int main()
{
    int col       = 0;
    int c         = 0;
    int prev_char = 0;
    while ((c = getchar()) != EOF) {
        /* Handle the cases when we are reaching the COL_WIDTH limit. */
        if ((COL_WIDTH - 1) == col) {
            if (isspace_knr(c)) {
                /* If whitespace is at the boundary, just replace with a
                   newline to force a wrap before the next word. */
                c = '\n';
            } else {
                if (isspace_knr(prev_char)) {
                    /* If a letter is at the boundary and it is preceded by a
                       space, output a newline to fold the line and cause the
                       beginning of the word to start on the next line. */
                    prev_char = '\n';
                    putchar('\n');
                    col = 0;
                } else {
                    /* If a letter is on the boundary preceded by another
                       letter, we are mid word. Output a dash and newline
                       to indicate continuation on the next line. */
                    prev_char = '\n';
                    putchar('-');
                    putchar('\n');
                    col = 0;
                }
            }
        }

        prev_char = c;
        putchar(c);
        col = ('\n' == c) ? 0 : col + 1;
    }

    return 0;
}

int isspace_knr(char c)
{
    return ((' ' == c) || ('\t' == c) || ('\n' == c));
}
