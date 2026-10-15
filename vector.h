#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} Vector;

Vector vector_create(size_t element_size);
Vector vector_from(const void *data, size_t len, size_t element_size);
void *vector_get(Vector *vector, size_t idx);
void vector_set(Vector *vector, size_t idx, const void *item);
int vector_add(Vector *vector, const void *item);
void vector_remove(Vector *vector, size_t idx);
int vector_pop(Vector *vector, void *result);
void vector_free(Vector *vector);

#endif
