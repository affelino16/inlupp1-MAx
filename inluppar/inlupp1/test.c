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

    entry_t buckets[No_Buckets];
    ioopm_hash_function *hash_fn;
    ioopm_eq_function *key_eq_fn;
    size_t size;
};


static size_t ptr_hash(elem_t ptr) {
   
     return (size_t) &ptr.p;
}

int main () {
    elem_t a = int_elem(2);
    elem_t *pA = &a;
    size_t adress = ptr_hash(*pA);
    printf("%ld\n", adress);
}