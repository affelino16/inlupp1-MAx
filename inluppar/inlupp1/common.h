#pragma once

#include <stdbool.h>
#include <stddef.h>
#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define ptr_elem(x)   ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })

/**
* @file common.h
* @author Alfred Ingvoldstad, Max Molund
* @date 29 september 2026
* @brief Simple hash table that maps string keys to integer values.
*/

typedef union elem elem_t;


union elem
{
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  char *s;
};

typedef bool ioopm_eq_function(elem_t a, elem_t b);


typedef size_t ioopm_hash_function(elem_t key);





