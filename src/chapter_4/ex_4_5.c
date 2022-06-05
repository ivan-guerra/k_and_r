#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found  */
#define MAXVAL  100 /* maximum depth of val stack      */
#define BUFSIZE 100 /* ungetch max buffer size         */

/* Symbols used to identify calculator function calls. */
#define SIN '1'
#define EXP '2'
#define POW '3'

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);

/*!
 * \brief Determine if \a buffer contains the string for a supported func call.
 * \return A function call symbolic constant (see #define's above) or -1 if
 *         \a buffer does not contain a supported function string.
 */
int get_func(const char *buffer, size_t i);

int main(void)
{
    int    type = 0;
    double op2  = 0.0;
    char s[MAXOP] = {0};

    while ((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            case SIN:
                push(sin(pop()));
                break;
            case EXP:
                push(exp(pop()));
                break;
            case POW:
                op2 = pop();
                push(pow(pop(), op2));
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.') {
        if (isalpha(c)) {
            size_t j = 0;
            char buffer[MAXOP] = {0};
            do {
                buffer[j++] = c;
            } while (isalpha(c = getch()));

            ungetch(c);
            buffer[j++] = '\0';

            return (1 == strlen(buffer)) ? buffer[0] : get_func(buffer, j);
        } else {
            return c; /* unknown command */
        }
    }

    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int get_func(const char *buffer, size_t i)
{
    static const char *SIN_FUNC = "sin";
    static const char *EXP_FUNC = "exp";
    static const char *POW_FUNC = "pow";

    if (0 == strncmp(SIN_FUNC, buffer, i))
        return SIN;
    else if (0 == strncmp(EXP_FUNC, buffer, i))
        return EXP;
    else if (0 == strncmp(POW_FUNC, buffer, i))
        return POW;
    else
        return -1;
}
