#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"
#include <assert.h>
#include "common.h"

struct node {
    elem_t value;
    struct node *next;
};

struct list {
    node_t *head;
    node_t *last;
    size_t size;
};

ioopm_list_t *ioopm_list_create() {
    ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));
    return list;
}

void ioopm_list_destroy(ioopm_list_t *list) {

    while(list->size > 0) {
        node_t *next = list->head->next;
        free(list->head);
        list->head = next;
        list->size--;
    }
    free(list);
}

 node_t *new_node(elem_t value, node_t *next) {
    node_t *node = calloc(1, sizeof(node_t));
    node->value= value;
    node->next = next;
    return node;
}

void ioopm_list_append(ioopm_list_t *list, elem_t value) {
    node_t *node = new_node(value, NULL);
    if (list->head == NULL) {
        list->head = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
    list->size++;
}

void ioopm_list_prepend(ioopm_list_t *list, elem_t value) {
    node_t *head = new_node(value, list->head);
    if (list->head == NULL) {
        list->head = head;
        list->last = head;
    } else {
        list->head = head;
    }
    list->size++;
}

size_t ioopm_list_size(ioopm_list_t *list) {
    return list->size;
}

elem_t ioopm_list_get(ioopm_list_t *list, size_t index) {

    assert(!ioopm_list_is_empty(list));
    assert(index < list->size);

    node_t *element = list->head;
    for (size_t i = 0; i < index; i++) {
        element = element->next;
    }
    return element->value;

}


elem_t ioopm_list_head(ioopm_list_t *list) {
    assert(list->head!=NULL);
    return list->head->value;
}

elem_t ioopm_list_last(ioopm_list_t *list) {
    assert(list->last!=NULL);
    return list->last->value;
}



bool ioopm_list_is_empty(ioopm_list_t *list) {
    if (list->size == 0) {
        return true;
    }

    return false;
}

void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t value) {
    assert(index<=list->size);
    if (index == 0) {
        ioopm_list_prepend(list, value);
    } else if (index == list->size) {
        ioopm_list_append(list, value);
    } else {
        node_t *inserted_node;
        node_t *previous = list->head;
        for (size_t i = 0; i < index-1; i++) {
            previous = previous->next;
        }
        inserted_node = new_node(value, previous->next);
        previous->next = inserted_node;
        list->size++;
    }

}


elem_t ioopm_list_remove(ioopm_list_t *list, size_t index) {

    assert(!ioopm_list_is_empty(list));
    assert(index<list->size);

    node_t *removed_node;

    if (index == 0) {
        removed_node = list->head;
        list->head = removed_node->next;
        if(list->head == NULL) {
            list->last = NULL;
        }
    }
    else {
        node_t *prev = list->head;
        for (size_t i = 0; i < index-1; i++) {
            prev = prev->next;
        }

        removed_node = prev->next;
        prev->next = removed_node->next;
        if (removed_node == list->last) {
            list->last = prev;
        }
    }
    elem_t value = removed_node->value;
    free(removed_node);
    list->size--;
    return value;
}
