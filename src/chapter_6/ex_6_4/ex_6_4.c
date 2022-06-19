#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "WordTree.h"

static int cmp_word_node(const void *w1, const void *w2)
{
    struct tnode* const *word1 = (struct tnode* const *)w1;
    struct tnode* const *word2 = (struct tnode* const *)w2;

    return ((*word2)->count - (*word1)->count);
}

/*
 * Not the most efficient or elegant approach but it works... We make a
 * BST counting the frequencies of each word in the input just as is done
 * in Section 6.5. The twist is that we enumerate the tree in an array
 * of nodes that is sorted in descending order based on frequency using qsort.
 */
int main(void)
{
    struct tnode *words = NULL;    /* BST of words and their frequency. */
    char         *line  = NULL;    /* Input line buffer. */
    size_t       len    = 0;       /* Length of the input line. */
    const char   *ws    = " \t\n"; /* strtok() delimiter string. */
    while (-1 != getline(&line, &len, stdin)) {
        char *word = strtok(line, ws);
        while (word) {
            /* There's no conditioning of the input words here. An improvement
               to this program would be to 'preprocess' each word before
               adding it to the tree. */
            words = add_tree(words, word);
            word = strtok(NULL, ws);
        }
    }

    size_t nnodes = size_tree(words);
    if (nnodes > 0) { /* Is the word tree non empty? */
        /* Allocate an array of struct tnodes large enough to contain all
           nodes in the tree. */
        struct tnode **nodes =
            (struct tnode **)malloc(sizeof(struct tnode *) * nnodes);
        if (!nodes) {
            fprintf(stderr, "error insufficient memory to allocate node arr\n");
            free_tree(words);
            free(line);
            return 1;
        }

        enumerate_tree(words, nodes, 0); /* Init nodes. */

        /* Sort the nodes in descending order based on word frequency. */
        qsort(nodes, nnodes, sizeof(struct tnode *), cmp_word_node);

        for (size_t i = 0; i < nnodes; ++i)
            printf("%d: %s\n", nodes[i]->count, nodes[i]->word);

        free(nodes);
    }
    free_tree(words);
    free(line);

    return 0;
}
