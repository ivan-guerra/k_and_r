#include <stdio.h>
#include <stdlib.h>

#include "LineVector.h"

#define SCALE_FACTOR 2

struct LineVector *init_lines(size_t capacity)
{
    struct LineVector *vec =
        (struct LineVector *)malloc(sizeof(struct LineVector));
    if (!vec) {
        fprintf(stderr, "error insufficient memory to allocate vector\n");
        return NULL;
    }

    vec->size = 0;
    vec->capacity = capacity;

    vec->linenums = (int *)malloc(capacity * sizeof(char *));
    if (!vec->linenums) {
        fprintf(stderr, "error insufficient memory to allocate linenums\n");
        free(vec);
        return NULL;
    }
    return vec;
}

bool push_line(struct LineVector *vec, int lineno)
{
    if (vec->size >= vec->capacity) {
        vec->linenums =
            (int *)realloc(vec->linenums,
                             vec->capacity * SCALE_FACTOR * sizeof(char *));
        if (!vec->linenums) {
            fprintf(stderr, "error insufficient memory to grow vector\n");
            return false;
        }
        vec->capacity *= SCALE_FACTOR;
    }

    vec->linenums[vec->size++] = lineno;

    return true;
}

bool pop_line(struct LineVector *vec)
{
    if (0 == vec->size)
        return false;

    vec->size--;

    return true;
}

bool find_line(const struct LineVector *vec, int lineno)
{
    for (size_t i = 0; i < vec->size; ++i) {
        if (lineno == vec->linenums[i])
            return true;
    }
    return false;
}

void free_lines(struct LineVector *vec)
{
    if (!vec)
        return;

    free(vec->linenums);
    free(vec);
}
