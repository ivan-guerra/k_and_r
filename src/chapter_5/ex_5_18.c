#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { OK, ERROR };

int dcl(void);
int dirdcl(void);

int getch(void);
void ungetch(int c);
int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];          /* output string */

int main(void)
{
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        if ((OK == dcl()) && ('\n' == tokentype)) {
            printf("%s: %s %s\n", name, out, datatype);
        } else { /* an error occurred, skip the rest of the line */
            if (tokentype != '\n')
                printf("syntax error\n");
            for (int c = '\0'; c != '\n' && c != EOF;) {
                if ((c = getch()) == EOF)
                    ungetch(c);
            }
        }
    }
    return 0;
}

/* dcl: parse a declarator */
int dcl(void)
{
    int ns;
    for (ns = 0; gettoken() == '*';)
        ns++;

    if (ERROR == dirdcl())
        return ERROR;

    while (ns-- > 0)
        strcat(out, " pointer to");

    return OK;
}

/* dirdcl: parse a direct declarator */
int dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        if (ERROR == dcl())
            return ERROR;

        if (tokentype != ')') {
            printf("error: missing )\n");
            return ERROR;
        }
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
        return ERROR;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
    return OK;
}

/* gettoken: return next token */
int gettoken()
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

#define BUFSIZE 100 /* ungetch max buffer size */

int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;     /* next free position in buf */

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
