#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "trie.h"

/* Wrapper functions around addword() and findword(). These are handy
   because they allow us to carry more information, namely the current
   index in the word, through successive recursive calls. */
static void addword_helper(struct Trie *root, const char *word, int i);
static bool findword_helper(const struct Trie *root, const char *word, int i);

static void addword_helper(struct Trie *root, const char *word, int i)
{
    if (word[i] == '\0') { /* Added all chars in the input word. */
        root->is_word = true;
        return;
    }

    if (!root->children[word[i] - '\0']) /* A new node needs to be added. */
        root->children[word[i] - '\0'] = init_trie(word[i + 1] == '\0');

    /* Process the next character in word. */
    addword_helper(root->children[word[i] - '\0'], word, i + 1);
}

static bool findword_helper(const struct Trie *root, const char *word, int i)
{
    if (!root)
        return false;

    struct Trie *child = root->children[word[i] - '\0'];
    if (!child) /* Hit a dead end in the tree. */
        return false;

    if (word[i + 1] == '\0') /* We have seen all the chars in word. */
        return child->is_word; /* Are we actually at word node? */

    /* Process the next character in word. */
    return findword_helper(child, word, i + 1);
}

struct Trie *init_trie(bool is_word)
{
    struct Trie *t = (struct Trie *)malloc(sizeof(struct Trie));
    if (!t) {
        fprintf(stderr, "error, insufficient memory to allocate trie node\n");
        return NULL;
    }

    t->is_word = is_word;
    for (int i = 0; i < ASCII_CHARS; ++i)
        t->children[i] = NULL;

    return t;
}

void free_trie(struct Trie *root)
{
    if (!root)
        return;

    for (size_t i = 0; i < ASCII_CHARS; ++i) {
        if (root->children[i])
            free_trie(root->children[i]);
    }
    free(root);
}

void addword(struct Trie *root, const char *word)
{
    addword_helper(root, word, 0);
}

bool findword(const struct Trie *root, const char *word)
{
    return findword_helper(root, word, 0);
}

int num_words(const struct Trie *root)
{
    if (!root)
        return 0;

    int nwords = (root->is_word) ? 1 : 0;
    for (size_t i = 0; i < ASCII_CHARS; ++i)
        nwords += num_words(root->children[i]);

    return nwords;
}

void print_words(
    const struct Trie *root,
    char letter,
    char *word,
    int i)
{
    if (!root)
        return;

    word[i] = letter;

    if (root->is_word) { /* We found a word, print it! */
        word[i + 1] = '\0';
        printf("%s ", word);
    }

    /* We continue trying to scan the tree for more word carefully tracking
       the prefix in the word buffer as we go through the recursive calls. */
    for (size_t j = 0; j < ASCII_CHARS; ++j) {
        if (root->children[j])
            print_words(root->children[j], (char)j, word, i + 1);
    }
}

void common_prefixes(
    struct Trie *root,
    int prefix_len,
    char letter,
    char *word,
    int i)
{
    if (!root)
        return;

    word[i] = letter; /* Add the current character to word. */

    if (0 == prefix_len) { /* We hit the prefix length requirement. */
        if (num_words(root) > 1) { /* There's more than one word with this prefix. */
            printf("{ ");
            if (root->is_word) {
                word[i + 1] = '\0';
                printf("%s ", word);
            }

            /* Print all the words that remain in this tree. */
            for (size_t j = 0; j < ASCII_CHARS; ++j) {
                if (root->children[j])
                    print_words(root->children[j], (char)j, word, i + 1);
            }
            printf("}\n");
            return;
        }
    }

    for (size_t j = 0; j < ASCII_CHARS; ++j) {
        if (root->children[j]) {
            common_prefixes(root->children[j],
                    prefix_len - 1,
                    (char)j,
                    word,
                    i + 1);
        }
    }
}
