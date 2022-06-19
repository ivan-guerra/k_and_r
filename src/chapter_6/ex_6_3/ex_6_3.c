#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "DocumentTree.h"

/*!
 * \brief Remove punctiation from the tail end of \a word.
 * \details Punctuation is defined as any non alphanumeric character.
 *          remove_punctuation() trims punctuation characters off the right
 *          hand side of \a word.
 */
static void remove_punctuation(char *word, size_t len);

/*!
 * \brief Return \c true if \a word contains only alphabetic characters.
 */
static bool is_english_word(const char *word);

/*!
 * \brief Return a DocumentTree populated "noise" words.
 * \details Noise words are words that appear frequently in the English
 *          language. get_noise_words() returns the top 50 noise words (see
 *          https://en.wikipedia.org/wiki/Most_common_words_in_English).
 */
static struct DocumentTree *get_noise_words(void);

static void remove_punctuation(char *word, size_t len)
{
    for (int i = len; i >= 0 && !isalnum(word[i]); --i)
        word[i] = '\0';
}

static bool is_english_word(const char *word)
{
    if ('\0' == *word)
        return false;

    for (size_t i = 0; word[i]; ++i) {
        if (!isalpha(word[i]))
            return false;
    }
    return true;
}

static struct DocumentTree *get_noise_words(void)
{
    static const char *NOISE_WORDS[] = {
        "the", "be", "to", "of", "and", "a", "in", "that", "have", "I", "it",
        "for", "not", "on", "with", "he", "as", "you", "do", "at", "this",
        "but", "his", "by", "from", "they", "we", "say", "her", "she", "or",
        "an", "will", "my", "one", "all", "would", "there", "their", "what",
        "so", "up", "out", "if", "about", "who", "get", "which", "go", "me",
        NULL
    };

    struct DocumentTree *noise = NULL;
    for (size_t i = 0; NOISE_WORDS[i]; ++i)
        noise = add_word(noise, NOISE_WORDS[i], 0);

    return noise;
}

int main(void)
{
    struct DocumentTree *noise = get_noise_words();
    struct DocumentTree *doc   = NULL;    /* BST of unique words in the doc. */
    char                *line  = NULL;    /* Input line buffer. */
    size_t              len    = 0;       /* Length of the input line. */
    int                 lineno = 1;       /* Current lineno in the doc. */
    const char          *ws    = " \t\n"; /* strtok() delimiter string. */
    while (-1 != getline(&line, &len, stdin)) {
        char *word = strtok(line, ws);
        while (word) {
            remove_punctuation(word, strlen(word));
            if (!find_word(noise, word) && is_english_word(word))
                doc = add_word(doc, word, lineno);
            word = strtok(NULL, ws);
        }
        lineno++;
    }
    print_words(doc); /* Print words in the doc and their line number(s). */

    free_doc(noise);
    free_doc(doc);
    free(line);

    return 0;
}
