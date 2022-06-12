#include <stdio.h>
#include <stdlib.h>

#define MAX_TABSTOPS    64
#define DEFAULT_TABSTOP 4

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
    int c   = 0;              /* character under the cursor */
    int col = 0;              /* current input column number */
    int ti  = 0;              /* tabstop array index */
    int ntabstops = argc - 1; /* number of tabstops provided by the User */
    int tabstops[MAX_TABSTOPS] = {0};

    if (ntabstops > MAX_TABSTOPS) {
        printf("entab supports no more than %d tabstops\n", MAX_TABSTOPS);
        return 1;
    }

    if (ntabstops) { /* the User provided one or more tabstop values*/
        while (*++argv)
            tabstops[ti++] = atoi(*argv); /* parse tabstops */
    } else {         /* no tabstop values supplied, use the default */
        ntabstops = 1;
        tabstops[ti] = DEFAULT_TABSTOP;
    }

    ti = 0;
    while ((c = getchar()) != EOF) {
        if ('\t' == c) {
            ti = (ti % ntabstops);
            int dist = dist_to_tabstop(col, tabstops[ti++]);
            col += dist;
            while (dist--)
                putchar(' ');
        } else if ('\n' == c) {
            col = 0;
            ti = 0;
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
