#ifndef _WORD_TREE_H_
#define _WORD_TREE_H_

#include <stddef.h>

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *add_tree(struct tnode *root, const char *word);
size_t size_tree(const struct tnode *root);
int enumerate_tree(struct tnode *root, struct tnode *nodes[], size_t i);
void free_tree(struct tnode *root);

#endif
