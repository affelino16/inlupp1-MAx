#include "hash_table.h"
#include "hash_table_iterator.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define No_Buckets 17

struct entry
{
  char *key;     
  int value;     
  entry_t *next;
};

struct hash_table
{

  entry_t buckets[No_Buckets];
  int size;
};

struct hash_table_iterator {
    ioopm_hash_table_t *ht;
    int bucket;
    entry_t *current;
};


static entry_t * find_first_entry(ioopm_hash_table_t *ht, int *first_bucket) {
    for (int i = *first_bucket; i < No_Buckets; i++) {
        if(ht->buckets[i].next != NULL) {
            *first_bucket = i;
            return ht->buckets[*first_bucket].next;
        }
    } *first_bucket = No_Buckets;
      return NULL;

}

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht) {
    ioopm_hash_table_iterator_t *it = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;
    it->bucket = 0;
    it->current = find_first_entry(ht, &it->bucket);
    return it;
}


void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it) {
    free(it);
}


bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it) {
   if (it->current->next == NULL) {
    return true;
   } else return false;
}


void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it) {

}


char *ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it) {

}


int ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it) {

}