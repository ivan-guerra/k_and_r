#include <stdio.h>
#include <string.h>

#define MAXOP   100 /* max size of operand or operator */
#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0;
double val[MAXVAL];

void push(double);
double pop(void);

int main(void)
{
    double op2 = 0.0;
    double num = 0.0;
    char   c   = '\0';
    char s[MAXOP] = {0};

    while (scanf("%s%c", s, &c) == 2) {
        if (sscanf(s, " %lf", &num) == 1)
            push(num);
        else if (strlen(s) == 1) {
            switch(*s) {
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
                default:
                    printf("error: unknown command %s\n", s);
                    break;
            }
        } else
            printf("unsupported operator: %s\n", s);

        if ('\n' == c)
            printf("\t%.8g\n", pop());

    }
    return 0;
}

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
