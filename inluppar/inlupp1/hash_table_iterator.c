#include "hash_table.h"
#include "hash_table_iterator.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define No_Buckets 17


struct entry
{
    elem_t key;
    elem_t value;
    entry_t *next;
};

struct hash_table {

    entry_t buckets[No_Buckets];
    ioopm_hash_function *hash_fn;
    ioopm_eq_function *key_eq_fn;
    size_t size;
};

struct hash_table_iterator {
    ioopm_hash_table_t *ht;
    size_t current_bucket;
    entry_t *current_entry;
};


static void advance_iterator_state(ioopm_hash_table_iterator_t *it)
{
    it->current_entry = it->current_entry->next;

    if (it->current_entry == NULL)
    {
        it->current_bucket += 1;

        /// After the last bucket current_entry stays NULL, which means the iterator is at its end
        if (it->current_bucket != No_Buckets)
        {
            it->current_entry = &it->ht->buckets[it->current_bucket];
        }
    }
}

static void skip_sentinel_nodes(ioopm_hash_table_iterator_t *it)
{
    while (it->current_bucket != No_Buckets &&
            it->current_entry == &it->ht->buckets[it->current_bucket])
    {
        advance_iterator_state(it);
    }
}


ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht) {
    ioopm_hash_table_iterator_t *it = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;
    it->current_bucket = 0;
    it->current_entry = &ht->buckets[0];
    skip_sentinel_nodes(it);
    return it;
}


void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it) {
    free(it);
}


bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it) {
    if (it->current_entry == NULL) {
        return true;
    } else return false;
}


void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it) {
    assert(!ioopm_hash_table_iterator_at_end(it) && "iterator at end when advancing");
    
    advance_iterator_state(it);
    skip_sentinel_nodes(it);
    
}


elem_t ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it) {
    assert(!ioopm_hash_table_iterator_at_end(it) && "current_entry = NULL");
    return it->current_entry->key;
}


elem_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it) {
    assert(!ioopm_hash_table_iterator_at_end(it) && "current_entry = NULL");
    return it->current_entry->value;
}
