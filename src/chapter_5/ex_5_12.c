#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TABSTOP   4
#define DEFAULT_START_COL 0

/*!
 * \brief Return the distance from the current column to the next tabstop.
 *
 * \param col     Current cursor location or column index.
 * \param tabstop Width of a tabstop.
 *
 * \return The distance from the current cursor location to the next tabstop.
 */
int dist_to_tabstop(int col, int tabstop);

/* Feeling lazy... only providing a solution for entab. detab solution
   is very similar. */
int main(int argc, char **argv)
{
    int m = DEFAULT_START_COL;
    int n = DEFAULT_TABSTOP;

    ++argv; /* skip program string */
    while (--argc && argv) {
        switch (*argv[0]) {
            case '-':
                m = atoi((*argv) + 1);
                argv++;
                break;
            case '+':
                n = atoi((*argv) + 1);
                argv++;
                break;
            default:
                printf("usage: ex_5_12 -<START_COL_NUM> +<NUM_TABSTOPS>");
                return 1;
        }
    }

    int c   = 0; /* character under the cursor */
    int col = 0; /* current input column number */
    while ((c = getchar()) != EOF) {
        if ('\t' == c) {
            int dist = 0;
            if (m) { /* starting tabstop has not yet been consumed */
                dist = dist_to_tabstop(col, m);
                m = 0;
            } else { /* we need to apply the User supplied/default tabstop */
                dist = dist_to_tabstop(col, n);
            }
            col += dist;
            while (dist--)
                putchar(' ');
        } else if ('\n' == c) {
            col = 0;
            putchar('\n');
        } else {
            col++;
            putchar(c);
        }
    }

    return 0;
}

int dist_to_tabstop(int col, int tabstop)
{
    /* If you are at the very first column index, return a full tabstop. */
    if (!col)
        return tabstop;

    int i = 0;
    while (i < col)
        i += tabstop;

    return (i - col);
}
