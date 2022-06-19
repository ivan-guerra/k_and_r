#ifndef _DOC_TREE_H_
#define _DOC_TREE_H_

#include <stdbool.h>

#include "LineVector.h"

/*!
 * \struct DocumentTree
 * \brief The DocumentTree struct is a BST containing words and their lineno(s).
 */
struct DocumentTree
{
    char                *word;  /*!< A word in the doc. */
    struct LineVector   *lines; /*!< Line(s) at which word appears in the doc. */
    struct DocumentTree *left;
    struct DocumentTree *right;
}; // end DocumentTree

/*!
 * \brief Locate \a word in the document tree.
 * \return A pointer to the DocumentTree node corresponding to \a word. If
 *         \a word does not exist, NULL is returned.
 */
struct DocumentTree *find_word(struct DocumentTree *root, const char *word);

/*!
 * \brief Add \a word to the document tree.
 * \details add_word() includes logic to avoid adding a lineno twice to an
 *          existing word's line number vector.
 * \return Pointer to an updated \a root.
 */
struct DocumentTree *add_word(
    struct DocumentTree *root,
    const char *word,
    int lineno);

/*!
 * \brief Print words and the lineno(s) they appear in the document.
 */
void print_words(const struct DocumentTree *root);

/*!
 * \brief Free document tree resources.
 */
void free_doc(struct DocumentTree *root);

#endif
