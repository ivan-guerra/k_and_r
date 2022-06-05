#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */
#define MAXVAL   100  /* maximum depth of val stack */
#define MAXLINE  1024 /* maximum length of an input line */

int getline_knr(char line[], int max);
int getop(char [], const char *);
void push(double);
double pop(void);

size_t loc = 0; /* index in the current input line */

int main(void)
{
    int    type = 0;
    double op2  = 0.0;
    char s[MAXOP] = {0};
    char input[MAXLINE] = {0};

    while (getline_knr(input, MAXLINE) > 0) {
        loc = 0;
        /* process the contents of a new input line */
        while (loc < strlen(input)) {
            switch((type = getop(s, input))) {
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
                default:
                    printf("error: unknown command %s\n", s);
                    break;
            }
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

int getop(char s[], const char *input)
{
    int i, c;

    while ((s[0] = c = input[loc++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c; /* not a number */

    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = input[loc++]))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = input[loc++]))
            ;

    s[i] = '\0';
    if (c != EOF)
        loc--;

    return NUMBER;
}

int sp = 0;
double val[MAXVAL] = {0.0};

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
