#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct ListNode {
    void *data;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;

    size_t size;
    size_t element_size;
} DoublyLinkedList;

DoublyLinkedList linked_list_create(size_t element_size);
ListNode linked_list_append(DoublyLinkedList *list, void *data);
ListNode linked_list_prepend(DoublyLinkedList *list, void *data);
void linked_list_remove(DoublyLinkedList *list, size_t idx);
ListNode *linked_list_get(DoublyLinkedList *list, size_t idx);
ListNode linked_list_insert(DoublyLinkedList *list, void *data, size_t idx);
void *linked_list_pop(DoublyLinkedList *list);
void linked_list_free(DoublyLinkedList *list);

#endif
