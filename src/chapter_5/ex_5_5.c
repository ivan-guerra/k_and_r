#include <stdio.h>
#include <string.h>

#define SIZE 1024

char *strncpy(char *dst, const char *src, size_t num);
char *strncat(char *dst, const char *src, size_t num);
int strncmp(const char *s1, const char *s2, size_t num);

int main(void)
{
    char dst[SIZE] = {'h', 'e', 'l', 'l', 'o', '\0'};
    const char *src = "world";
    size_t n = strlen(src);

    printf("strncpy(dst=%s, src=%s, n=%lu) = ", dst, src, n);
    printf("%s\n", strncpy(dst, src, n));
    printf("strncat(dst=%s, src=%s, n=%lu) = ", dst, src, n);
    printf("%s\n", strncat(dst, src, n));
    printf("strncmp(dst=%s, src=%s, n=%lu) = ", src, src, n);
    printf("%d\n", strncmp(src, src, n));

    return 0;
}

char *strncpy(char *dst, const char *src, size_t num)
{
    char *ret = dst;

    while (src && num) {
        *dst++ = *src++;
        num--;
    }

    while (num)
        *dst++ = 0;

    return ret;
}

char *strncat(char *dst, const char *src, size_t num)
{
    char *ret = dst;
    while (*dst) /* move the dst pointer to the end of the string */
        dst++;

    while (src && num--)
        *dst++ = *src++; /* append src characters to the end of dst */

    if (!num)
        *dst = '\0'; /* append the terminator if strlen(src) >= num */

    return ret;
}

int strncmp(const char *s1, const char *s2, size_t num)
{
    while (s1 && s2 && num) {
        if (*s1 != *s2)
            return (*s1 - *s2);

        s1++;
        s2++;
        num--;
    }

    return (!num) ? 0 : (*s1 - *s2);
}
