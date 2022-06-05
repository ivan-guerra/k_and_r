#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100 /* ungetch max buffer size */
#define MAX_VARS 26 /* max number of variables supported */

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);

int main(void)
{
    int type = 0;
    double op2 = 0.0;
    double most_recent_output = 0;
    char s[MAXOP] = {0};
    int variable_definition[MAX_VARS] = {0};
    double variable_values[MAX_VARS] = {0.0};

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
                most_recent_output = pop();
                printf("\t%.8g\n", most_recent_output);
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                /* Allow the User to define a variable. The way we are setup
                   here allows for one time initialization of the variable
                   (i.e., you cannot change the value of a variable once it's
                   set). */
                if (!variable_definition[type - 'a']) {
                    variable_definition[type - 'a'] = 1;
                    variable_values[type - 'a'] = pop();
                }
                /* Push the value of the referenced variable to the stack. */
                push(variable_values[type - 'a']);
                break;
            case '_':
                push(most_recent_output);
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

    if (!isdigit(c) && c != '.')
        return c;

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
