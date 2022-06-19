#include "WordTree.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

struct tnode *add_tree(struct tnode *root, const char *word)
{
    int cond;

    if (root == NULL) {
        root = talloc();
        root->word = strdup(word);
        root->count = 1;
        root->left = root->right = NULL;
    } else if ((cond = strcmp(word, root->word)) == 0)
        root->count++;
    else if (cond < 0)
        root->left = add_tree(root->left, word);
    else
        root->right = add_tree(root->right, word);
    return root;
}

size_t size_tree(const struct tnode *root)
{
    if (!root)
        return 0;

    return (1 + size_tree(root->left) + size_tree(root->right));
}

int enumerate_tree(struct tnode *root, struct tnode *nodes[], size_t i)
{
    if (!root)
        return i;

    i = enumerate_tree(root->left, nodes, i);
    nodes[i++] = root;
    i = enumerate_tree(root->right, nodes, i);

    return i;
}

void free_tree(struct tnode *root)
{
    if (!root)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root->word);
    free(root);
}
