#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100 /* ungetch max buffer size */

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);

/*!
 * \brief Return at an offset of \a i from the top of the stack.
 * \return The element in the stack \a i slot from the top. 0.0 is returned
 *         if an invalid index is provided and an error message is printed
 *         to STDOUT.
 */
double peek(int i);

/*!
 * \brief Duplicate the element at the top of the stack.
 *
 * dupe() prints an error message and returns immediately if the stack is
 * empty.
 */
void dupe();

/*!
 * \brief Swap the top two elements of the stack.
 *
 * swap() prints an error message and return immediately if the stack
 * has a size less than or equal to one.
 */
void swap();

/*!
 * \brief Clear the stack.
 */
void clear();

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
            case 'p':
                printf("%.8g", peek(0));
                break;
            case 'd':
                dupe();
                break;
            case 's':
                swap();
                break;
            case 'c':
                clear();
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

double peek(int i)
{
    int index = sp - i - 1;
    if (index < 0) {
        printf("error: cannot peek at index %d, index out of bounds\n", i);
        return 0.0;
    }
    return val[index];
}

void dupe()
{
    if (0 == sp) {
        printf("error: stack is empty, nothing to dupe\n");
        return;
    }
    val[sp] = val[sp - 1];
    sp++;
}

void swap()
{
    if (sp < 2) {
        printf("error: stack has less than two elements, nothing to swap\n");
        return;
    }
    int tmp = val[sp - 1];
    val[sp - 1] = val[sp - 2];
    val[sp - 2] = tmp;
}

void clear()
{
    sp = 0;
}
