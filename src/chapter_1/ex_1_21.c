#include <stdio.h>

#define TABSTOP 8

/*!
 * \brief Return the number of blanks/tabs seen before the next character.
 *
 * dist_to_next_char() counts the blanks/tabs seen before the next non
 * blank/tab character or EOF. The first non blank/tab character or EOF is
 * stored in \a next_char on exit.
 *
 * \param next_char Address where the next non blank/tab character will be
 *                  saved on return.
 *
 * \return The number of blanks/tabs before the next non blank/tab char.
 */
int dist_to_next_char(int *next_char);

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
    int col = 0;
    int c   = 0;
    while ((c = getchar()) != EOF) {
        if ((' ' == c) || ('\t' == c)) {
            int next_char = 0;
            int nwhitespace = dist_to_next_char(&next_char);

            int dtots = 0;
            while ((dtots = dist_to_tabstop(col, TABSTOP)) &&
                   ((nwhitespace - dtots) >= 0)) {
                col += dtots;
                putchar('\t');
                nwhitespace -= dtots;
            }

            while (nwhitespace--) {
                col++;
                putchar(' ');
            }

            if (EOF != next_char) {
                col = ('\n' == next_char) ? 0 : col + 1;
                putchar(next_char);
            }
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

int dist_to_next_char(int *next_char)
{
    int dist = 0;
    int c    = 0;
    for (; (c = getchar()) && (EOF != c) && ((' ' == c) || ('\t' == c)); dist++)
        ;

    *next_char = c;

    return (dist + 1);
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
