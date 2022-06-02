#include <stdio.h>

#define MAX_STR_LEN 32

/*!
 * \brief Reverse \a s.
 */
void reverse(char *s, size_t n);

/*!
 * \brief Save the base \a b representation of \a n in string \a s.
 *
 * itob() currently support positive integers and common bases: binary,
 * octal, decimal, and hexadecimal. Passing itob() a base other than one
 * of the four listed will lead to undefined behavior.
 */
void itob(unsigned n, char *s, unsigned b);

int main()
{
    unsigned i = 3735928559U;
    unsigned b = 16U;
    char s[MAX_STR_LEN] = {0};

    itob(i, s, b);

    printf("itob(%u, s, %u) = %s\n", i, b, s);

    return 0;
}

void reverse(char *s, size_t n)
{
    size_t i = 0;
    size_t j = n - 1;
    for (; i < j; ++i, --j) {
        int tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

void itob(unsigned n, char *s, unsigned b)
{
    static const char DIGITS[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F'
    };

    size_t i = 0;
    do {
        s[i++] = DIGITS[n % b];
    } while (n /= b);

    s[i] = '\0';

    reverse(s, i);
}
