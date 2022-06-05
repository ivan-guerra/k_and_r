#include <stdio.h>
#include <string.h>

/*!
 * \brief Helper function used by reverse().
 *
 * reverse_helper() allows us to track our current index in the string through
 * the call stack using the parameter \a i.
 */
void reverse_helper(char *s, int n, int i);
void reverse(char *s);

int main(void)
{
    char str[] = "hello world";

    printf("reverse(%s) = ", str);
    reverse(str);
    printf("%s\n", str);

    return 0;
}

void reverse_helper(char *s, int n, int i)
{
    if (i == n)
        return;

    char c = s[i];
    reverse_helper(s, n, i + 1);
    s[n - i - 1] = c;
}

void reverse(char *s)
{
    reverse_helper(s, strlen(s), 0);
}
