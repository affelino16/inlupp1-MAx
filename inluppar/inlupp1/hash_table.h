#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
/**
* @file hash_table.h
* @author write both your names here
* @date write the date you started working on this
* @brief Simple hash table that maps string keys to integer values.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@.
*
*/

typedef struct hash_table ioopm_hash_table_t;
typedef struct entry entry_t;



/// @brief Create a new hash table with size 0
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return boolean if key is in hash table or not and value of key
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key
int ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key);

/// @brief check if key is in hash table
/// @param ht hash table operated upon
/// @param key key to check
/// @return boolean if key is in hash table
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key);

/// @brief check if hash table is empty
/// @param ht hash table operated upon
/// @return boolean if hash table is empty or not
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief get the size of hash table
/// @param ht hash table operated upon
/// @return the size of hash table
int ioopm_hash_table_size(ioopm_hash_table_t *ht);