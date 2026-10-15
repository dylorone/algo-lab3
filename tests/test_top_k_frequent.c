#include "top_k_frequent.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void assert_top_k(const int *input, size_t length, size_t k,
                         const int *expected, size_t expected_length) {
    Vector result = {0};
    assert(top_k_frequent(input, length, k, &result));
    assert(result.size == expected_length);

    for (size_t i = 0; i < expected_length; i++) {
        int *actual = vector_get(&result, i);
        assert(actual != NULL);
        assert(*actual == expected[i]);
    }

    vector_free(&result);
}

void test_examples_and_tie_breaking() {
    const int first[] = {1, 1, 1, 2, 2, 3};
    const int first_expected[] = {1, 2};
    assert_top_k(first, 6, 2, first_expected, 2);

    const int second[] = {4, 4, 1, 1, 1, 7};
    const int second_expected[] = {1, 4};
    assert_top_k(second, 6, 2, second_expected, 2);

    const int third[] = {5, 5, 5};
    const int third_expected[] = {5};
    assert_top_k(third, 3, 1, third_expected, 1);

    const int negative[] = {-1, -1, 2, 2, 3};
    const int negative_expected[] = {-1, 2};
    assert_top_k(negative, 5, 2, negative_expected, 2);

    const int all_tied[] = {10, 20, 30};
    const int all_tied_expected[] = {10, 20};
    assert_top_k(all_tied, 3, 2, all_tied_expected, 2);
}

void test_empty_and_invalid_inputs() {
    Vector empty_result = {0};
    assert(top_k_frequent(NULL, 0, 0, &empty_result));
    assert(empty_result.size == 0);
    vector_free(&empty_result);

    const int values[] = {7, 7, 8};
    Vector too_many = {0};
    assert(!top_k_frequent(values, 3, 3, &too_many));
    assert(too_many.data == NULL);

    Vector null_input = {0};
    assert(!top_k_frequent(NULL, 1, 1, &null_input));
    assert(null_input.data == NULL);
}

int main() {
    test_examples_and_tie_breaking();
    test_empty_and_invalid_inputs();

    printf("Все тесты пройдены!\n");
    return 0;
}
