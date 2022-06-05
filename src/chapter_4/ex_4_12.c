#include <stdio.h>
#include <limits.h>

#define MAX_LEN 32

/*!
 * \brief Helper function used by itoa().
 *
 * itoa_helper() tracks index location in the output parameter \a s. This
 * information allows us to place digits in the correct slot in \a s as we
 * return up the call stack.
 *
 * \return The next available (empty) index in \a s.
 */
int itoa_helper(int n, char s[], int i);

/*!
 * \brief Place the string representation of \a n in \a s.
 */
void itoa(int n, char s[]);

int main(void)
{
    int n = INT_MIN;
    char s[MAX_LEN] = {0};

    itoa(n, s); /* recrusive itoa implementation */

    printf("itoa(%d) = %s\n", n, s);

    return 0;
}

int itoa_helper(int n, char s[], int i)
{
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    if (n / 10)
        i = itoa_helper(n / 10, s, i);

    s[i++] = n % 10 + '0';

    return i;
}

void itoa(int n, char s[])
{
    int i = itoa_helper(n, s, 0);
    s[i] = '\0';
}
