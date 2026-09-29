#include "linked_list.h"
#include "linked_list_iterator.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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


struct list_iterator {

    ioopm_list_t *list;
    node_t *current;
    node_t *previous;
};

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *list) {
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));
    iter->list = list;
    iter->current = list->head;
    return iter;
}


void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter){
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter) {
    if (iter->current == NULL) {
        return true;
    } else {
        return false;
    }
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter) {
    assert(!ioopm_list_iterator_at_end(iter));
    iter->previous = iter->current;
    iter->current = iter->current->next;
    
}

elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter) {
    assert(!ioopm_list_iterator_at_end(iter));
    return iter->current->value;
    
}


elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter) {
    
    node_t *removed = iter->current;
    elem_t value = removed->value;
    node_t *next = removed->next;

    if (iter->previous == NULL) {
        iter->list->head = iter->current->next;
    }
    else {
        iter->previous->next = iter->current->next;
    }

    if (removed == iter->list->last) {
        iter->list->last = iter->previous;  
    }
    
    free(removed);
    iter->current = next;
    iter->list->size--;

    return value;
}


void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element) {
    node_t *next = iter->current;
    node_t *new = new_node(element, next);
    if (iter->previous == NULL) {
        iter->list->head = new;
    } else  {
        iter->previous->next = new; 
    } if (next == NULL) {
        iter->list->last = new;
    }
        iter->current = new;
        iter->list->size++;
}