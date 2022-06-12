#include <stdio.h>
#include <string.h>

#define SIZE 1024

int strend(const char *s, const char *t);

int main(void)
{
    const char *s = "hello world";
    const char *t = "world";

    printf("strend(%s, %s) = %d\n", s, t, strend(s, t));

    return 0;
}

int strend(const char *s, const char *t)
{
    if (!t || !(*t)) /* the empty string is a substring of every string */
        return 1;

    int i = strlen(s) - 1;
    int j = strlen(t) - 1;
    if (j > i) /* t cannot be larger than s and still be a substring */
        return 0;

    for (; i >= 0 && j >= 0; --i, --j) {
        if (s[i] != t[j])
            return 0;
    }

    return (j < 0);
}
