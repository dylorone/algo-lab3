#include "top_k_frequent.h"

#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} ValueCount;

static int compare_value_counts(const void *left, const void *right) {
    const ValueCount *a = left;
    const ValueCount *b = right;

    if (a->count > b->count) {
        return -1;
    }
    if (a->count < b->count) {
        return 1;
    }
    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    return 0;
}

int top_k_frequent(const int *values, size_t length, size_t k, Vector *result) {
    if (result == NULL || result->data != NULL || result->size != 0 ||
        result->capacity != 0 || result->element_size != 0 ||
        (length > 0 && values == NULL)) {
        return 0;
    }

    Vector output = vector_create(sizeof(int));
    if (output.data == NULL) {
        return 0;
    }

    if (k == 0) {
        *result = output;
        return 1;
    }

    Vector counts = vector_create(sizeof(ValueCount));
    if (counts.data == NULL) {
        vector_free(&output);
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        int found = 0;
        for (size_t j = 0; j < counts.size; j++) {
            ValueCount *entry = vector_get(&counts, j);
            if (entry->value == values[i]) {
                entry->count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            ValueCount entry = {values[i], 1};
            if (!vector_add(&counts, &entry)) {
                vector_free(&counts);
                vector_free(&output);
                return 0;
            }
        }
    }

    if (k > counts.size) {
        vector_free(&counts);
        vector_free(&output);
        return 0;
    }

    qsort(counts.data, counts.size, sizeof(ValueCount), compare_value_counts);

    for (size_t i = 0; i < k; i++) {
        const ValueCount *entry = vector_get(&counts, i);
        int value = entry->value;
        if (!vector_add(&output, &value)) {
            vector_free(&counts);
            vector_free(&output);
            return 0;
        }
    }

    vector_free(&counts);
    *result = output;
    return 1;
}
