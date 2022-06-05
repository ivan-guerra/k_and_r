#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

/*!
 * \brief getline as defined in the text.
 */
int getline_knr(char line[], int max);

/*!
 * \brief Return the right most index at which \a t appears in \a s.
 */
int strrindex(const char *s, const char *t);

/*!
 * \brief Compare \a s to \a t starting at index \a i in \a s.
 * \return 1 if the substring beginning at s[i] is equal to \a t, 0 otherwise.
 */
int cmp(const char *s, const char *t, int i);

int main()
{
    char line[MAXLINE] = {0};
    const char *pattern = "or";
    int index = -1;

    while (getline_knr(line, MAXLINE) > 0) {
        if ((index = strrindex(line, pattern)) >= 0) {
            printf("%s", line);
            printf("\tfound substr '%s' at rightmost index %d\n",
                   pattern, index);
        }
    }

    return 0;
}

int getline_knr(char line[], int max)
{
    int c = 0;
    int i = 0;
    while ((--max > 0) && ((c = getchar()) != EOF) && ('\n' != c))
        line[i++] = c;

    if ('\n' == c)
        line[i++] = c;

    line[i] = '\0';

    return i;
}

int strrindex(const char *s, const char *t)
{
    int slen = strlen(s);
    int tlen = strlen(t);
    for (int i = slen - 1; i >= 0; --i) {
        /* Return index i iff:
             (1) The current char in s matches the first char in t
             (2) There are enough characters to the right of i in s to
                 to potentially match all chars in t
             (3) t can be matched beginning at s[i] */
        if ((t[0] == s[i]) && ((slen + 1 - i - tlen) >= 0) && cmp(s, t, i))
            return i;
    }
    return -1;
}

int cmp(const char *s, const char *t, int i)
{
    /* Verify s == t */
    for (size_t j = 0; t[j]; ++j) {
        if (s[i++] != t[j])
            return 0;
    }

    return 1;
}
