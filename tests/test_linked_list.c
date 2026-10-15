#include "linked_list.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

int node_value(const ListNode *node) {
    assert(node != NULL);
    return *(const int *)node->data;
}

void assert_list(DoublyLinkedList *list, const int *values, size_t count) {
    assert(list->size == count);
    assert((count == 0) == (list->head == NULL));
    assert((count == 0) == (list->tail == NULL));

    ListNode *previous = NULL;
    ListNode *node = list->head;
    for (size_t i = 0; i < count; i++) {
        assert(node != NULL);
        assert(node->prev == previous);
        assert(node_value(node) == values[i]);
        assert(linked_list_get(list, i) == node);
        previous = node;
        node = node->next;
    }

    assert(node == NULL);
    assert(previous == list->tail);
    if (list->tail != NULL) {
        assert(list->tail->next == NULL);
    }
}

void test_insert_remove_and_pop() {
    DoublyLinkedList list = linked_list_create(sizeof(int));
    assert(linked_list_get(&list, 0) == NULL);

    int one = 1;
    int two = 2;
    int zero = 0;
    int nine = 9;
    (void)linked_list_append(&list, &one);
    (void)linked_list_append(&list, &two);
    (void)linked_list_prepend(&list, &zero);
    (void)linked_list_insert(&list, &nine, 2);

    ListNode invalid = linked_list_insert(&list, &nine, list.size + 1);
    assert(invalid.data == NULL);

    const int expected[] = {0, 1, 9, 2};
    assert_list(&list, expected, 4);
    assert(linked_list_get(&list, list.size) == NULL);

    linked_list_remove(&list, 1);
    const int after_middle_remove[] = {0, 9, 2};
    assert_list(&list, after_middle_remove, 3);

    linked_list_remove(&list, 0);
    const int after_head_remove[] = {9, 2};
    assert_list(&list, after_head_remove, 2);

    linked_list_remove(&list, 100);
    assert_list(&list, after_head_remove, 2);

    int *popped = linked_list_pop(&list);
    assert(popped != NULL);
    assert(*popped == 2);
    const int after_pop[] = {9};
    assert_list(&list, after_pop, 1);

    linked_list_remove(&list, 0);
    assert_list(&list, NULL, 0);
    assert(linked_list_pop(&list) == NULL);

    assert_list(&list, NULL, 0);
}

void test_single_element_lifecycle() {
    DoublyLinkedList list = linked_list_create(sizeof(int));
    int value = 42;
    (void)linked_list_append(&list, &value);
    linked_list_remove(&list, 0);
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);

    (void)linked_list_append(&list, &value);
    assert(linked_list_pop(&list) == &value);
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);

    (void)linked_list_append(&list, &value);
    linked_list_free(&list);
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
}

int main() {
    test_insert_remove_and_pop();
    test_single_element_lifecycle();

    printf("Все тесты пройдены!\n");
    return 0;
}
