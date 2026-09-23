
#include "hash_table.h"
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

static int string_knr_hash(char *key) {
    int sum = 0;
    for (int i = 0; i < strlen(key); i++) {
        sum = sum + key[i];
    }
    return sum;
}

ioopm_hash_table_t *ioopm_hash_table_create()
{
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->size = 0;
    return ht;
}
static void entry_destroy(entry_t *entry) {
    free(entry);
    return;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
    for (int i = 0; i < No_Buckets; i++) {
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


static entry_t *entry_create(char *key, int value, entry_t *next) {
    entry_t *new_entry = calloc(1, sizeof(entry_t));
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = next;
    return new_entry;
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key) {
    size_t bucket = string_knr_hash(key) % No_Buckets;
    entry_t *previous = &ht->buckets[bucket];
    entry_t *current = ht->buckets[bucket].next;
    while (current != NULL && strcmp(current->key, key) != 0)
    {
        previous = current;
        current = current->next;
    }
    return previous;

}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value) {

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



bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result) {
    entry_t *previous = find_previous_entry(ht, key);
    while (previous->next != NULL) {
        if (strcmp(key, previous->next->key) == 0) {
            *result = previous->next->value;
            return true;
        } else {
            previous = previous->next;
        }
    }
    *result = 0;
    return false;
}

int ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key) {
    entry_t *previous = find_previous_entry(ht, key);
    while (previous->next != NULL) {
        if (strcmp(key, previous->next->key) == 0) {
            entry_t *tmp =previous->next;
            int removed_value = tmp->value;
            previous->next =previous->next->next;
            entry_destroy(tmp);
            ht->size--;
            return removed_value;
        } else {
            previous = previous->next;
        }
    }
    return 0;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key) {
    int value;
    if (ioopm_hash_table_lookup(ht, key, &value)) {
        return true;
    } else return false;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht) {
    return ht->size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht) {
    if (ht->size == 0) {
        return true;
    } else return false;
}

void print_hash(ioopm_hash_table_t *ht) {
    printf("start\n");
    for (int i = 0; i < No_Buckets; i++) {
        entry_t *current = ht->buckets[i].next;
        if (current == NULL) {
            printf("        %d.  ---\n", i);
        } else {
            printf("        %d. value: %d, key: %s ", i, current->value, current->key);
            if (current->next == NULL) {
                printf("next: NULL\n");
            } else {
                entry_t *next = current->next;
                printf("next: key: %s, value: %d\n", next->key, next->value);
            }
        }
    }
    printf("End\n");
}


/* int main() {
  int value;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  print_hash(ht);
  ioopm_hash_table_insert(ht,"hej", 42);
    print_hash(ht);
  ioopm_hash_table_insert(ht,"hej", 22);
  ioopm_hash_table_insert(ht,"Jolmar", 42);
  ioopm_hash_table_insert(ht,"hje", 12);
  ioopm_hash_table_insert(ht,"tjoj", 42);
  ioopm_hash_table_lookup(ht, "tjoj", &value);
  printf("value: %d\n", value);
  print_hash(ht);
  value = ioopm_hash_table_remove(ht, "hje");
  printf("value: %d\n", value);
  print_hash(ht);
  value = ioopm_hash_table_remove(ht, "Skoba");
  printf("value: %d\n", value);
  print_hash(ht);
  ioopm_hash_table_destroy(ht);
  return 0;
} */



