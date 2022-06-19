#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

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

/* undef: remove the (name, defn) from hashtab */
static void undef(char *name)
{
    if (!lookup(name)) /* name does not map to an entry in the table */
        return;

    unsigned     hashval = hash(name);
    struct nlist *head   = hashtab[hashval];

    /* Using a dummy node helps us avoid a lot of the edge cases that come
       up when deleting a node from a linked list. */
    struct nlist dummy;
    dummy.next = head;

    struct nlist *prev = &dummy;
    struct nlist *curr = head;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            prev->next = curr->next; /* this 'skips' over the deleted node */
            free(curr->defn);
            free(curr->name);
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    /* Update the head of the hash bucket's linked list. */
    hashtab[hashval] = dummy.next;
}

/* printtab: print hashtab (name, defn) pairs to STDOUT*/
static void printtab()
{
    for (size_t i = 0; i < HASHSIZE; ++i) {
        if (hashtab[i]) {
            struct nlist const *curr = hashtab[i];
            while (curr) {
                printf("key: %s\n", curr->name);
                printf("value: %s\n", curr->defn);
                curr = curr->next;
            }
        }
    }
}

int main(void)
{
    install("ONE",   "1");
    install("TWO",   "2");
    install("THREE", "3");
    install("FOUR",  "4");
    install("FIVE",  "5");

    printf("=== BEFORE UNDEF===\n");
    printtab();
    printf("===================\n");

    printf("\ndeleting THREE AND FOUR...\n\n");
    undef("THREE");
    undef("FOUR");

    printf("=== AFTER UNDEF ===\n");
    printtab();
    printf("===================\n");

    return 0;
}
