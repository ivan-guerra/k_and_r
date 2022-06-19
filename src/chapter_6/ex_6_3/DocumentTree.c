#include "DocumentTree.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_LINE_VEC_SIZE 8

struct DocumentTree *find_word(struct DocumentTree *root, const char *word)
{
    if (!root)
        return NULL;

    int cmp = strcmp(word, root->word);
    if (0 == cmp)
        return root;
    else if (cmp < 0)
        return find_word(root->left, word);
    else
        return find_word(root->right, word);
}


struct DocumentTree *add_word(
    struct DocumentTree *root,
    const char *word,
    int lineno)
{
    if (!root) {
        root = (struct DocumentTree *)malloc(sizeof(struct DocumentTree));
        if (!root) {
            fprintf(stderr, "error insufficient memory to allocate node\n");
            return NULL;
        }

        root->word  = strdup(word);
        root->left  = root->right = NULL;
        root->lines = init_lines(DEFAULT_LINE_VEC_SIZE);
        push_line(root->lines, lineno);

        return root;
    }

    int cmp = strcmp(word, root->word);
    if (0 == cmp) {
        /* Avoid adding duplicate line numbers. */
        if (!find_line(root->lines, lineno))
            push_line(root->lines, lineno);

        return root;
    } else if (cmp < 0) {
        root->left = add_word(root->left, word, lineno);
    } else {
        root->right = add_word(root->right, word, lineno);
    }

    return root;
}

void print_words(const struct DocumentTree *root)
{
    if (!root)
        return;

    print_words(root->left);

    printf("%s: { ", root->word);
    for (size_t i = 0; i < root->lines->size; ++i)
        printf("%d ", root->lines->linenums[i]);
    printf("}\n");

    print_words(root->right);
}

void free_doc(struct DocumentTree *root)
{
    if (!root)
        return;

    free_doc(root->left);
    free_doc(root->right);
    free_lines(root->lines);
    free(root->word);
    free(root);
}
