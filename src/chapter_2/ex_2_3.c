#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define HEX_DIGITS 16 /* Number of digits in base 16. */

/*!
 * \brief Return 1 if \a s starts with the hex prefix '0x' or '0X'.
 */
int has_hex_prefix(const char *s);

/*!
 * \brief Convert the hexadecimal string \a s to an integer.
 */
unsigned long htoi(const char *s);

int main()
{
    const char *value = "0xDEADBEEF";
    printf("%s = %lu\n", value, htoi(value));
}

int has_hex_prefix(const char *s)
{
    if (strlen(s) < 2)
        return 0;

    return (('0' == s[0]) && ('x' == tolower(s[1])));
}

unsigned long htoi(const char *s)
{
    unsigned long ret = 0;
    size_t i = (has_hex_prefix(s) ? 2 : 0);
    for (; i < strlen(s); ++i) {
        if (isalpha(s[i]))
            ret = (ret * HEX_DIGITS) + (tolower(s[i]) - 'a' + 10);
        else if (isdigit(s[i]))
            ret = (ret * HEX_DIGITS) + (s[i] - '0');
        else
            return -1; /* Invalid character. */
    }

    return ret;
}
