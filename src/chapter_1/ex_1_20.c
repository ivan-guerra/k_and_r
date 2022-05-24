#include <stdio.h>

#define TABSTOP 4

/*!
 * \brief Return the distance from the current column to the next tabstop.
 *
 * \param col     Current cursor location or column index.
 * \param tabstop Width of a tabstop.
 *
 * \return The distance from the current cursor location to the next tabstop.
 */
int dist_to_tabstop(int col, int tabstop);

int main()
{
    int c   = 0;
    int col = 0;
    while ((c = getchar()) != EOF) {
        if ('\t' == c) {
            int dist = dist_to_tabstop(col, TABSTOP);
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
