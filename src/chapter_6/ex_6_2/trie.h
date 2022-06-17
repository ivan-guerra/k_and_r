#ifndef _TRIE_H_
#define _TRIE_H_

#define ASCII_CHARS 256

#include <stdbool.h>

/*!
 * \struct Trie
 * \brief The Trie struct represents of a prefix tree of ASCII characters.
 */
struct Trie
{
    bool        is_word; /*!< Flag indicating whether the tree contains a word at this node. */
    struct Trie *children[ASCII_CHARS]; /*!< Child nodes. */
};

/*!
 * \brief Allocate a new Trie node.
 * \return A new Trie node if allocation succeeds, otherwise NULL is returned.
 */
struct Trie *init_trie(bool is_word);

/*!
 * \brief Free resources held by the Trie starting at \a root.
 * \details free_trie will recursively free the tree (i.e., child nodes,
 *          child's child nodes, etc. will be freed).
 */
void free_trie(struct Trie *root);

/*!
 * \brief Add \a word to the Trie starting at \a root.
 */
void addword(struct Trie *root, const char *word);

/*!
 * \brief Return \c true if \a word exists in the Trie starting at \a root.
 */
bool findword(const struct Trie *root, const char *word);

/*!
 * \brief Return the number of words in the prefix tree.
 */
int num_words(const struct Trie *root);

/*!
 * \brief Print all words in in this tree to STDOUT.
 */
void print_words(
    const struct Trie *root,
    char letter,
    char *word,
    int i);

/*!
 * \brief Print all words that have a common prefix of at least length \a prefix_len.
 * \details common_prefixes() performs a depth first search for the groups of
 *          words who have a matching prefix of at least length \a prefix_len.
 *          All latter groups are printed to STDOUT.
 * \param root       Prefix tree root.
 * \param prefix_len Minimum length of the common prefix.
 * \param letter     The character terminating the active prefix.
 * \param word       Character buffer used to construct the output word(s).
 * \param i          Current index in the \a word buffer.
 */
void common_prefixes(
    struct Trie *root,
    int prefix_len,
    char letter,
    char *word,
    int i);

#endif
