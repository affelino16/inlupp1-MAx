#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
/**
* @file hash_table.h
* @author Alfred Ingvoldstad, Max Molund
* @date 16 september 2026
* @brief Generic Hash table with a hash function and a equal function
* 
*/

typedef struct hash_table ioopm_hash_table_t;
typedef struct entry entry_t;



/// @brief Create a new hash table with size 0
/// @param hash_fn function that hashes
/// @param key_eq_fn function that checks equality
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result where the value mapped to by key is written if key exists
/// @return true if key is in hash table, else false
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key or int_elem(0) if key doesnt exist
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if key is in hash table
/// @param ht hash table operated upon
/// @param key key to check
/// @return boolean if key is in hash table
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if hash table is empty
/// @param ht hash table operated upon
/// @return boolean if hash table is empty or not
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief get the size of hash table
/// @param ht hash table operated upon
/// @return the size of hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);