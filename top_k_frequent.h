#ifndef TOP_K_FREQUENT_H
#define TOP_K_FREQUENT_H

#include "vector.h"

#include <stddef.h>

/*
 * Builds a Vector of the k most frequent values, ordered by descending
 * frequency and then ascending value. `result` must point to a zero-initialized
 * Vector. Returns 1 on success and 0 for invalid input or allocation failure.
 */
int top_k_frequent(const int *values, size_t length, size_t k, Vector *result);

#endif
