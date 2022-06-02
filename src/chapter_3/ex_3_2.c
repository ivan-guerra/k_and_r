#include <stdio.h>

#define MAX_LEN 1000

/*!
 * \brief Copy \a t to \s replacing escaped chars with their raw version.
 *
 * escape() assume \a s is a buffer large enough to hold \a t along with
 * with escaped character expansions.
 */
void escape(char *s, const char *t);

/*!
 * \brief Perform the inverse operation of escape().
 */
void unescape(char *s, const char *t);

int main()
{
    const char *t = "Hello\tworld.\nMy name is Johnny.\nWhat is your name?";
    char escaped_str[MAX_LEN]   = {0};
    char unescaped_str[MAX_LEN] = {0};

    escape(escaped_str, t);
    printf("escaped str: %s\n", escaped_str);

    unescape(unescaped_str, escaped_str);
    printf("unescaped str: %s\n", unescaped_str);

    return 0;
}

void escape(char *s, const char *t)
{
    size_t j = 0;
    for (size_t i = 0; t[i]; ++i) {
        switch (t[i]) {
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\b':
                s[j++] = '\\';
                s[j++] = 'b';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
}

void unescape(char *s, const char *t)
{
    size_t j = 0;
    for (size_t i = 0; t[i]; ++i) {
        if (('\\' == t[i]) && ('\0' != t[i + 1])) {
            switch (t[i + 1]) {
                case 't':
                    s[j++] = '\t';
                    break;
                case 'n':
                    s[j++] = '\n';
                    break;
                case 'b':
                    s[j++] = '\b';
                    break;
                default:
                    s[j++] = t[i + 1];
            }
            i++;
        } else {
            s[j++] = t[i];
        }
    }
}
