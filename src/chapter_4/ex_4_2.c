#include <stdio.h>
#include <ctype.h>

/*!
 * \brief atof as described in the text with added support for scientific
 *        notation.
 */
double atof(const char *s);

int main(void)
{
    const char *value = "314e-2";
    double result = atof(value);

    printf("original string is '%s'\n", value);
    printf("converted value is %lf\n", result);

    return 0;
}

double atof(const char *s)
{
    double val   = 0.0;
    double power = 0.0;
    int i    = 0;
    int sign = 0;

    for (i = 0; isspace(s[i]); ++i)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (('+' == s[i]) || ('-' == s[i]))
        i++;
    for (val = 0.0; isdigit(s[i]); ++i)
        val = 10.0 * val + (s[i] - '0');
    if ('.' == s[i])
        i++;
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    /* Identify whether this floating point value is using scientific
       notation. */
    int is_scientific = 0;
    if (('e' == s[i]) || ('E' == s[i])) {
        is_scientific = 1;
        i++;
    }

    /* Determine whether the exponent is negative or positive. Default is
       positive. */
    int exp_sign = ('-' == s[i]) ? -1 : 1;
    if (('-' == s[i]) || ('+' == s[i]))
        i++;

    /* Compute the exponent value. */
    int exp = 0;
    for (; isdigit(s[i]); ++i)
        exp += exp * 10 + (s[i] - '0');

    /* Compute 10^exp */
    double exp_power = 1.0;
    while (exp--)
        exp_power *= 10.0;

    /* Compute the 'base' value without any exponentiation. */
    double base = sign * val / power;

    /* If the number was in scientific notiation, apply the exponent to
       the 'base' value and return. */
    if (is_scientific)
        return (exp_sign < 0) ? (base / exp_power) : (base * exp_power);

    /* The argument was not in scientific notation, just return the base. */
    return base;
}
