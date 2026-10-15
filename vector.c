#include "vector.h"

#include <stdlib.h>
#include <string.h>

Vector vector_create(size_t element_size) {
    if (element_size == 0) {
        return (Vector){NULL, 0, 0, 0};
    }

    void *data = malloc(element_size);
    if (data == NULL) {
        return (Vector){NULL, 0, 0, 0};
    }

    return (Vector){data, 0, 1, element_size};
}

Vector vector_from(const void *data, size_t len, size_t element_size) {
    if (element_size == 0 || (len > 0 && data == NULL)) {
        return (Vector){NULL, 0, 0, 0};
    }

    if (len == 0) {
        return (Vector){NULL, 0, 0, element_size};
    }

    void *vdata = malloc(len * element_size);
    if (vdata == NULL) {
        return (Vector){NULL, 0, 0, 0};
    }

    memcpy(vdata, data, len * element_size);
    return (Vector){vdata, len, len, element_size};
}

void *vector_get(Vector *vector, size_t idx) {
    if (vector == NULL || vector->data == NULL ||
        vector->element_size == 0 || idx >= vector->size) {
        return NULL;
    }

    return (unsigned char *)vector->data + idx * vector->element_size;
}

void vector_set(Vector *vector, size_t idx, const void *item) {
    if (vector == NULL || vector->data == NULL || item == NULL ||
        vector->element_size == 0 || idx >= vector->size) {
        return;
    }

    memmove((unsigned char *)vector->data + idx * vector->element_size,
            item,
            vector->element_size);
}

int vector_add(Vector *vector, const void *item) {
    if (vector == NULL || item == NULL || vector->element_size == 0 ||
        vector->size > vector->capacity) {
        return 0;
    }

    if (vector->size == vector->capacity) {
        size_t new_capacity = 1;
        if (vector->capacity != 0) {
            new_capacity = vector->capacity * 2;
        }

        void *new_data = realloc(vector->data,
                                 new_capacity * vector->element_size);
        if (new_data == NULL) {
            return 0;
        }

        vector->data = new_data;
        vector->capacity = new_capacity;
    } else if (vector->data == NULL) {
        return 0;
    }

    memmove((unsigned char *)vector->data
                + vector->size * vector->element_size,
            item,
            vector->element_size);
    vector->size++;
    return 1;
}

void vector_remove(Vector *vector, size_t idx) {
    if (vector == NULL || vector->data == NULL ||
        vector->element_size == 0 || idx >= vector->size) {
        return;
    }

    size_t elements_after = vector->size - idx - 1;
    if (elements_after > 0) {
        unsigned char *data = vector->data;
        memmove(data + idx * vector->element_size,
                data + (idx + 1) * vector->element_size,
                elements_after * vector->element_size);
    }

    vector->size--;
}

int vector_pop(Vector *vector, void *result) {
    if (vector == NULL || vector->data == NULL || result == NULL ||
        vector->element_size == 0 || vector->size == 0) {
        return 0;
    }

    memmove(result,
            (unsigned char *)vector->data
                + (vector->size - 1) * vector->element_size,
            vector->element_size);
    vector->size--;
    return 1;
}

void vector_free(Vector *vector) {
    if (vector == NULL) {
        return;
    }

    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;
    vector->element_size = 0;
}
