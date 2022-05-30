#include <stdio.h>

/*!
 * \brief Find \a c in string \a s.
 * \return The index of a the first occurrence of \a c in \a s, -1 is returned
 *         if \a c doesn not appear in \a s.
 */
int find(char c, const char *s);

/*!
 * \brief Delete all chars in \a s1 that match any char in \a s2.
 * \return The size of \a s1 after the squeeze operation is performed.
 */
size_t squeeze(char *s1, const char *s2);

int main()
{
    char       s1[] = "reeeeee";
    const char *s2  = "eeeeee";
    printf("s1 = %s\ns2 = %s\n", s1, s2);

    squeeze(s1, s2);

    printf("squeeze(s1, s2) = %s\n", s1);

    return 0;
}

int find(char c, const char *s)
{
    if (!s)
        return 0;

    int i = 0;
    while ((s[i] != '\0') && (s[i] != c))
        i++;

    return (s[i] == c) ? i : -1;
}

size_t squeeze(char *s1, const char *s2)
{
    size_t i = 0;
    size_t j = 0;
    while (s1[i]) {
        if (-1 == find(s1[i], s2))
            s1[j++] = s1[i];
        i++;
    }

    s1[j] = '\0';

    return j;
}
