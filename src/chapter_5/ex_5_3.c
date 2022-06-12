#include <stdio.h>

#define SIZE 1024

void strcat_knr(char *s, const char *t);

int main(void)
{
    char s[SIZE] = {'h', 'e', 'l', 'l', 'o', '\0'};
    const char *t = " world";

    printf("before strcat: %s\n", s);
    strcat_knr(s, t);
    printf("after strcat: %s\n", s);

    return 0;
}

void strcat_knr(char *s, const char *t)
{
    while (*s)
        s++; /* consume all chars in s upto '\0' */

    while (*t)
        *s++ = *t++; /* copy characters from s to t */

    *s = '\0';
}
