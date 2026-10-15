#include "linked_list.h"

#include <stdlib.h>

static ListNode *create_node(void *data) {
    ListNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

static ListNode failed_node(void) {
    return (ListNode){NULL, NULL, NULL};
}

DoublyLinkedList linked_list_create(size_t element_size) {
    return (DoublyLinkedList){NULL, NULL, 0, element_size};
}

ListNode linked_list_append(DoublyLinkedList *list, void *data) {
    if (list == NULL) {
        return failed_node();
    }

    ListNode *node = create_node(data);
    if (node == NULL) {
        return failed_node();
    }

    node->prev = list->tail;
    if (list->tail != NULL) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
    list->size++;
    return *node;
}

ListNode linked_list_prepend(DoublyLinkedList *list, void *data) {
    if (list == NULL) {
        return failed_node();
    }

    ListNode *node = create_node(data);
    if (node == NULL) {
        return failed_node();
    }

    node->next = list->head;
    if (list->head != NULL) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }
    list->head = node;
    list->size++;
    return *node;
}

ListNode *linked_list_get(DoublyLinkedList *list, size_t idx) {
    if (list == NULL || idx >= list->size) {
        return NULL;
    }

    if (idx < list->size / 2) {
        ListNode *node = list->head;
        for (size_t i = 0; i < idx; i++) {
            node = node->next;
        }
        return node;
    }

    ListNode *node = list->tail;
    for (size_t i = list->size - 1; i > idx; i--) {
        node = node->prev;
    }
    return node;
}

ListNode linked_list_insert(DoublyLinkedList *list, void *data, size_t idx) {
    if (list == NULL || idx > list->size) {
        return failed_node();
    }
    if (idx == 0) {
        return linked_list_prepend(list, data);
    }
    if (idx == list->size) {
        return linked_list_append(list, data);
    }

    ListNode *target = linked_list_get(list, idx);
    if (target == NULL) {
        return failed_node();
    }

    ListNode *node = create_node(data);
    if (node == NULL) {
        return failed_node();
    }

    node->prev = target->prev;
    node->next = target;
    target->prev->next = node;
    target->prev = node;
    list->size++;
    return *node;
}

void linked_list_remove(DoublyLinkedList *list, size_t idx) {
    ListNode *node = linked_list_get(list, idx);
    if (node == NULL) {
        return;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    free(node);
    list->size--;
}

void *linked_list_pop(DoublyLinkedList *list) {
    if (list == NULL || list->tail == NULL) {
        return NULL;
    }

    ListNode *node = list->tail;
    void *data = node->data;
    list->tail = node->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    free(node);
    list->size--;
    return data;
}

void linked_list_free(DoublyLinkedList *list) {
    if (list == NULL) {
        return;
    }

    ListNode *node = list->head;
    while (node != NULL) {
        ListNode *next = node->next;
        free(node);
        node = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
