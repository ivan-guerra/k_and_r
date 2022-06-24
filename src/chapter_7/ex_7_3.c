#include <stdio.h>
#include <stdarg.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* pints to each unnamed arg in turn */
    char *p, *sval, format[3] = { '%', '\0', '\0' };
    int    ival;
    double dval;
    void   *pval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch (*++p) {
            case 'd':
            case 'i':
            case 'c':
                ival = va_arg(ap, int);
                format[1] = *p;
                printf(format, ival);
                break;
            case 'f':
            case 'e':
            case 'E':
            case 'g':
            case 'G':
                dval = va_arg(ap, double);
                format[1] = *p;
                printf(format, dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            case 'x':
            case 'X':
            case 'o':
            case 'u':
                ival = va_arg(ap, int);
                format[1] = *p;
                printf(format, ival);
                break;
            case 'p':
                pval = va_arg(ap, void *);
                printf("%p", pval);
                break;
            case '%':
                putchar(*p);
                break;
            default:
                putchar('%');
                putchar(*p);
                break;
        }
    }
    va_end(ap); /* clean up when done */
}

/* Credit to https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_7:Exercise_3
   written by anonymous. This main() driver and the modified minprintf() is
   their implementation. */
int main(void)
{
    char         *sval = "10";
    int          ival  = 11;
    double       dval  = 12.13;
    unsigned int uival = 14;
    char         cval  = 'F';
    void         *pval = sval;
    minprintf("%%s=%s, %%d=%d, %%i=%i, %%f=%f, %%e=%e, %%E=%E, %%g=%g, %%G=%G, %%o=%o, %%x=%x\n", sval, ival, ival, dval, dval, dval, dval, dval, uival, uival);
    printf("%%s=%s, %%d=%d, %%i=%i, %%f=%f, %%e=%e, %%E=%E, %%g=%g, %%G=%G, %%o=%o, %%x=%x\n", sval, ival, ival, dval, dval, dval, dval, dval, uival, uival);
    minprintf("%%X=%X, %%u=%u, %%c=%c, %%p=%p, %%%%=%%\n", uival, uival, cval, pval);
    printf("%%X=%X, %%u=%u, %%c=%c, %%p=%p, %%%%=%%\n", uival, uival, cval, pval);

    return 0;
}
