#include "vector.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

int vector_int_at(Vector *vector, size_t idx) {
    int *value = vector_get(vector, idx);
    assert(value != NULL);
    return *value;
}

void test_create_and_from() {
    Vector empty = vector_create(sizeof(int));
    assert(empty.data != NULL);
    assert(empty.size == 0);
    assert(vector_get(&empty, 0) == NULL);

    int values[] = {1, 0, -4, 8};
    Vector copy = vector_from(values, 4, sizeof(values[0]));
    assert(copy.data != NULL);
    assert(copy.size == 4);
    values[0] = 99;
    assert(vector_int_at(&copy, 0) == 1);
    assert(vector_int_at(&copy, 1) == 0);
    assert(vector_int_at(&copy, 2) == -4);
    assert(vector_int_at(&copy, 3) == 8);
    assert(vector_get(&copy, copy.size) == NULL);

    vector_free(&copy);
    vector_free(&empty);
    assert(copy.data == NULL && copy.size == 0 && copy.capacity == 0);
}

void test_add_growth_and_set() {
    Vector vector = vector_create(sizeof(int));
    assert(vector.data != NULL);

    for (int value = 0; value < 8; value++) {
        assert(vector_add(&vector, &value));
    }

    assert(vector.size == 8);
    assert(vector.capacity >= vector.size);
    assert(vector.capacity == 8);
    for (int value = 0; value < 8; value++) {
        assert(vector_int_at(&vector, (size_t)value) == value);
    }

    int replacement = -7;
    vector_set(&vector, 4, &replacement);
    assert(vector_int_at(&vector, 4) == -7);

    vector_set(&vector, vector.size, &replacement);
    assert(vector.size == 8);
    assert(vector_int_at(&vector, 4) == -7);

    vector_free(&vector);
}

void test_remove_and_pop() {
    int values[] = {10, 20, 30, 40};
    Vector vector = vector_from(values, 4, sizeof(values[0]));
    assert(vector.data != NULL);

    vector_remove(&vector, vector.size);
    assert(vector.size == 4);

    vector_remove(&vector, 1);
    assert(vector.size == 3);
    assert(vector_int_at(&vector, 0) == 10);
    assert(vector_int_at(&vector, 1) == 30);
    assert(vector_int_at(&vector, 2) == 40);

    vector_remove(&vector, 0);
    vector_remove(&vector, vector.size - 1);
    assert(vector.size == 1);
    assert(vector_int_at(&vector, 0) == 30);

    int popped = 0;
    assert(vector_pop(&vector, &popped));
    assert(popped == 30);
    assert(vector.size == 0);
    assert(!vector_pop(&vector, &popped));

    vector_free(&vector);
}

void test_empty_vectors_and_invalid_arguments() {
    Vector invalid_create = vector_create(0);
    assert(invalid_create.data == NULL);
    assert(invalid_create.element_size == 0);

    int value = 17;
    Vector empty = vector_from(NULL, 0, sizeof(value));
    assert(empty.data == NULL);
    assert(empty.size == 0);
    assert(empty.element_size == sizeof(value));

    assert(vector_get(&empty, 0) == NULL);
    assert(vector_add(&empty, &value));
    vector_set(&empty, 0, NULL);
    assert(!vector_add(&empty, NULL));
    assert(!vector_pop(&empty, NULL));
    assert(vector_int_at(&empty, 0) == value);

    int popped = 0;
    assert(vector_pop(&empty, &popped));
    assert(popped == value);
    assert(!vector_pop(&empty, &popped));

    Vector invalid_from = vector_from(NULL, 1, sizeof(value));
    assert(invalid_from.data == NULL);

    assert(vector_get(NULL, 0) == NULL);
    vector_set(NULL, 0, &value);
    assert(!vector_add(NULL, &value));
    vector_remove(NULL, 0);
    assert(!vector_pop(NULL, &popped));
    vector_free(NULL);

    vector_free(&invalid_create);
    vector_free(&invalid_from);
    vector_free(&empty);
}

int main() {
    test_create_and_from();
    test_add_growth_and_set();
    test_remove_and_pop();
    test_empty_vectors_and_invalid_arguments();

    printf("Все тесты пройдены!\n");
    return 0;
}
