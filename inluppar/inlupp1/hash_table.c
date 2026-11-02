
#include "hash_table.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#define No_Buckets 17




struct entry {

    elem_t key;
    elem_t value;
    entry_t *next;
};

struct hash_table {

    /// Each bucket is a sentinel entry that holds no data; real entries start at buckets[i].next
    entry_t buckets[No_Buckets];
    ioopm_hash_function *hash_fn;
    ioopm_eq_function *key_eq_fn;
    size_t size;
};

static size_t string_hash(elem_t str) {

  size_t result = 0;
  while (*str.s != '\0') {
    
    result = result * 31 + ((unsigned char) *str.s);
    (str.s)++;
  }
  return result;
}

static size_t int_hash (elem_t intg) { 
    return (size_t) intg.i;
}

static size_t ptr_hash(elem_t ptr) {
     return (size_t) ptr.p;
}

static bool ptr_eq (elem_t a, elem_t b) {
     if (a.p == b.p) {
        return true;
    } return false; 
}

static bool int_eq (elem_t a, elem_t b) {
    if (a.i == b.i) {
        return true;
    } return false;
}

static bool string_eq (elem_t a, elem_t b) {

    return strcmp(a.s, b.s) == 0;
} 



ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->hash_fn = hash_fn;
    ht->key_eq_fn = key_eq_fn;
    ht->size = 0;
    return ht;
}


static void entry_destroy(entry_t *entry) {
    free(entry);
    return;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
    for (size_t i = 0; i < No_Buckets; i++) {
        entry_t *current = ht->buckets[i].next;

        while (current != NULL) {
            entry_t *next = current->next;

            entry_destroy(current);
            current = next;
        }
    }
    free(ht);
    return;
}


static entry_t *entry_create(elem_t key, elem_t value, entry_t *next) {
    entry_t *new_entry = calloc(1, sizeof(entry_t));
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = next;
    return new_entry;
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t key) {
    size_t bucket = ht->hash_fn(key) % No_Buckets;
    
    entry_t *previous = &ht->buckets[bucket];
    entry_t *current = previous->next;
    while (current != NULL && !ht->key_eq_fn(current->key, key))
    {
        previous = current;
        current = current->next;
    }
    return previous;

}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value) {

    entry_t *previous = find_previous_entry(ht, key);

    if (previous->next != NULL)
    {
        previous->next->value = value;
    }
    else
    {
        previous->next = entry_create(key, value, NULL);
        ht->size++;
    }
}



bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result) {
    entry_t *previous = find_previous_entry(ht, key);
    
    if(previous->next != NULL) {
        *result = previous->next->value;
        return true;
    }
    return false;
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key) {
    entry_t *previous = find_previous_entry(ht, key);
    
    if(previous->next != NULL) {
        entry_t *tmp = previous->next;
        elem_t removed_value = tmp->value;

        previous->next = tmp->next;
        entry_destroy(tmp);
        ht->size--;

        return removed_value;
    }    
    return int_elem(0);
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key) {
    elem_t value;
    return ioopm_hash_table_lookup(ht, key, &value);
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) {
    return ht->size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht) {
    if (ht->size == 0) {
        return true;
    } else return false;
}




