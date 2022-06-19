#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

#define HASHSIZE 101

/* yylex() -> function used to retrieve the next token
   yytext  -> lexeme associated with the most recently scanned token */
extern int yylex(void);
extern char* yytext;

struct nlist            /* table entry */
{
    struct nlist *next; /* next entry in chain */
    char         *name; /* defined name */
    char         *defn; /* replacement text */
};

static struct nlist *hashtab[HASHSIZE] = {NULL}; /* pointer table */

/* hash: form hash value for string s */
static unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; ++s)
        hashval = *s + 31 * hashval;
    return (hashval % HASHSIZE);
}

/* lookup: look for s in hashtab */
static struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np ->next) {
        if (strcmp(s, np->name) == 0)
            return np;
    }
    return NULL;
}

/* install: put (name, defn) in hashtab */
static struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *)malloc(sizeof(*np));
        if (NULL == np || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else { /* already there */
        free((void *) np->defn); /* free previous defn */
    }

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/*!
 * \brief Parse #define NAME VAL statements and insert (NAME, VAL) in hashtab.
 * \param text A preprocessor statement. \a text could be any preprocessor
 *             statement not necessarily the #define NAME VAL type.
 */
static void preproc(const char *text)
{
    static const char *delims = " \t\n#";
    char *cp   = strdup(text);
    char *word = strtok(cp, delims);
    if (strcmp(word, "define") != 0)
        goto Exit;

    char *name = strtok(NULL, delims);
    if (!name) {
        fprintf(stderr, "error missing preprocessor constant name\n");
        goto Exit;
    }

    char *defn = strtok(NULL, "\n");
    if (!defn) {
        fprintf(stderr, "error missing preprocessor constant value\n");
        goto Exit;
    }

    struct nlist *result = lookup(defn);
    if (result)
        /* If the preproc define references a previous preproc define, perform
           replacement. */
        install(name, result->defn);
    else
        install(name, defn);

Exit:
    free(cp);
}

int main(void)
{
    int token = yylex();
    while (token) {
        if (PREPROCESSOR == token) { /* process a potential #define preproc stmt */
            preproc(yytext);
            printf("%s", yytext);
        } else if (IDENTIFIER == token) { /* identifiers may need textual replacement */
            struct nlist *result = lookup(yytext);
            if (result) /* the identifier is a preproc constant */
                printf("%s", result->defn);
            else /* the identifier is not preproc constant */
                printf("%s", yytext);
        } else {
            printf("%s", yytext);
        }
        token = yylex();
    }

    return 0;
}
