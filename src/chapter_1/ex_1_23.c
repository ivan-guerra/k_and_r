#include <stdio.h>

int main()
{
    /* We implement a state machine that removes comments from a C program
       input file. The state machine handles both inline and block comments. */
    int c = 0;
    int start_state = 1;
    int end_state   = 6;
    int state       = start_state;
    while (1) {
        if (start_state == state) {
            /* Print characters until you see the (possible) beginning of
               a comment. */
            c = getchar();
            while ((EOF != c) && ('/' != c)) {
                putchar(c);
                c = getchar();
            }
            state = (EOF == c) ? end_state : 2;
        } else if (2 == state) {
            c = getchar();
            if ('/' == c)
                state = 3; /* Inline comment start. */
            else if ('*' == c)
                state = 4; /* Block comment start. */
            else if (EOF == c)
                state = end_state;
            else {
                /* We just ran into a '/' in the input, go back to
                   the start state. */
                putchar(c);
                state = start_state;
            }
        } else if (3 == state) {
            /* Consume inline comment characters. */
            c = getchar();
            while ((EOF != c) && ('\n' != c))
                c = getchar();

            if (EOF == c) {
                state = end_state;
            } else {
                /* We hit the end of an inline comment, output the newline
                   and go to the start state to continue printing the
                   program. */
                putchar('\n');
                state = start_state;
            }
        } else if (4 == state) {
            /* Consume block comment characters. */
            c = getchar();
            while ((EOF != c) && ('*' != c)) {
                c = getchar();
            }
            state = (EOF == c) ? end_state : 5;
        } else if (5 == state) {
            /* Have we reached the end of a block comment? */
            c = getchar();
            if ('/' == c)
                state = start_state;
            else if (EOF == c)
                state = end_state;
            else
                state = 4;
        } else if (end_state == state) {
            /* EOF was encountered, exit.*/
            break;
        }
    }

    return 0;
}
