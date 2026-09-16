
#include "hash_table.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct entry entry_t;

struct entry
{
  char *key;     
  int value;     
  entry_t *next; 
};

struct hash_table
{

  entry_t *buckets[17];
};

ioopm_hash_table_t *ioopm_hash_table_create()
{
  return calloc(1, sizeof(ioopm_hash_table_t));
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
 free(ht);
 return;
}

void test_create_destroy() {
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}