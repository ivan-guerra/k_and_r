#ifndef _LINE_VECTOR_H_
#define _LINE_VECTOR_H_

#include <stddef.h>
#include <stdbool.h>

/*!
 * \struct LineVector
 * \brief The LineVector struct is a vector of document line numbers.
 */
struct LineVector
{
    size_t capacity;   /*!< Total number of slots. */
    size_t size;       /*!< Number of stored linenums. */
    int    *linenums;  /*!< Array of line numbers. */
};

/*!
 * \brief Initialize a line number vector with capacity \a capacity.
 * \param capacity Number of element slots to pre-allocate.
 * \return A pointer to a LineVector with the parameter capacity. NULL is
 *         returned if the latter vector could not be allocated.
 */
struct LineVector *init_lines(size_t capacity);

/*!
 * \brief Push \a lineno into \a vec.
 * \details If the size of \a vec equals or exceeds the capacity of \a vec,
 *          then push_lines() will automatically create space to accomodate
 *          \a lineno.
 * \return \c true if \a lineno was pushed into \a vec.
 */
bool push_line(struct LineVector *vec, int lineno);

/*!
 * \brief Remove the line number at the back of \a vec.
 * \return \c true if the element at the back of \a vec is popped.
 */
bool pop_line(struct LineVector *vec);

/*!
 * \brief Return \c true if \a lineno exists in \a vec.
 */
bool find_line(const struct LineVector *vec, int lineno);

/*!
 * \brief Free all resources held by \a vec.
 */
void free_lines(struct LineVector *vec);

#endif
