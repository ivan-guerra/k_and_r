#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 1000

/*!
 * \brief Check if the range [start, end] is valid.
 *
 * A valid range is defined as one where:
 *   (1) start <= end
 *   (2) The range is composed of digits or alpha characters.
 *     (2.1) If alphabetic, the casing must match (i.e., a-Z is not considered
 *           a valid range).
 * \return 1 if [\a start, \a end] defines a valid range.
 */
int is_valid_range(char start, char end);

/*!
 * \brief Copy \a t into \a s expanding any shorthand notations.
 *
 * expand() assumes there enough space in \a s to hold \a t and its notation
 * expansions.
 */
void expand(char *s, const char *t);

int main()
{
    char s[MAX_STR_LEN] = {0};
    const char *t = "misc chars -A-Z0-9a-za-b-c- more misc chars";

    expand(s, t);

    printf("t = %s\n", t);
    printf("s = %s\n", s);

    return 0;
}

int is_valid_range(char start, char end)
{
    /* A descending range is considered invalid. */
    if (start > end)
        return 0;

    /* Check for a digit start and end value. */
    if (isdigit(start))
        return isdigit(end);

    /* Check for an alphabetic start and end value. Make sure case matches. */
    if (isalpha(start) && isalpha(end))
        return ((islower(start) && islower(end)) ||
                (isupper(start) && isupper(end)));

    return 0;
}

void expand(char *s, const char *t)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int len = strlen(t);
    for (; i < len; ++i) {
        if ('-' == t[i]) {
            if (((i - 1) < 0)    ||
                ((i + 1) >= len) ||
                !is_valid_range(t[i - 1], t[i + 1])) {
                /* Handle the case where we have an unterminated '-'.*/
                s[j++] = t[i];
            } else {
                /* Step back one slot in s to capture the start of
                   range char. */
                j--;

                /* Copy the range of characters specified in t to s. */
                k = t[i - 1];
                while (k <= t[i + 1])
                    s[j++] = (char)k++;

                i++; /* Skip the end of range char in t on the next iter. */
            }
        } else {
            s[j++] = t[i]; /* Copy any chars that are not part of a range. */
        }
    }
}
