#include "hash_table.h"
#include "hash_table_iterator.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define No_Buckets 17


struct hash_table_iterator {
    
}

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht) {
    return calloc(1, sizeof(ioopm_hash_table_iterator_t))
}


void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it);


bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it);


void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it);


char *ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it);


int ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it);