#include <stdio.h>
#include <limits.h>

/*!
 * \brief Return the index of the first occurrence of \a c in \a s.
 * \return The index of the first occurrence of \a c in \a s. -1 is returned
 *         if \a c never appears in \a s.
 */
int find_first_occurrence(char c, const char *s);

/*!
 * \brief Return first location in \a s1 where any char in \a s2 appears.
 * \return The index of the first location in \a s1 where any char in \a s2
 *         appears or -1 if no such location exists.
 */
int any(const char *s1, const char *s2);

int main()
{
    const char *s1 = "hello";
    const char *s2 = "world";
    printf("s1          = %s\n", s1);
    printf("s2          = %s\n", s2);

    int result = any(s1, s2);
    printf("any(s1, s2) = %d\n", result);

    return 0;
}

int find_first_occurrence(char c, const char *s)
{
    if (!s)
        return -1;

    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == c)
            return i;
    }

    return -1;
}

int any(const char *s1, const char *s2)
{
    int min_index  = INT_MAX;
    for (size_t i = 0; s2[i] != '\0'; ++i) {
        int index = find_first_occurrence(s2[i], s1);
        if ((index >= 0) && (index < min_index))
            min_index = index;
    }

    return ((INT_MAX == min_index) ? -1 : min_index);
}
