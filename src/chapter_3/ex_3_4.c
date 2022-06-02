#include <stdio.h>
#include <limits.h>

#define MAX_STR_LEN 32

void reverse(char *s, size_t n);
void itoa(int n, char s[]);

int main()
{
    int n = INT_MIN;
    char s[MAX_STR_LEN] = {0};

    itoa(n, s);

    printf("itoa(%d) = %s\n", n, s);

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

void itoa(int n, char s[])
{
    int i, sign, is_int_min;

    is_int_min = 0;
    if ((sign = n) < 0) {
        if (INT_MIN == n) {
            /* If given n = INT_MIN, then convert to INT_MAX and before
               returning check if is_int_min is high. If so, just add one to
               the last digit in s. */
            n = INT_MAX;
            is_int_min = 1;
        } else {
            n = -n;
        }
    }

    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    reverse(s, i);

    if (is_int_min)
        s[i - 1]++; /* Increment the last digit to account for n = INT_MIN. */
}
