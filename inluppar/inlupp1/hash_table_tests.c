#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "common.h"

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}
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

void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_destroy_with_entry()
{   elem_t key = string_elem("abc");
    elem_t value = int_elem(123);

  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_insert(ht, key, value);
   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  // create new hash table

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);

  // check that key is not in ht
  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, int_elem(0).i);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_ptr_keys()
{
  int a = 1, b = 2;
  ioopm_hash_table_t *ht = ioopm_hash_table_create(ptr_hash, ptr_eq);
  elem_t result = int_elem(0);

  ioopm_hash_table_insert(ht, ptr_elem(&a), int_elem(10));
  ioopm_hash_table_insert(ht, ptr_elem(&b), int_elem(20));

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, ptr_elem(&a), &result));
  CU_ASSERT_EQUAL(result.i, 10);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, ptr_elem(&b), &result));
  CU_ASSERT_EQUAL(result.i, 20);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

  ioopm_hash_table_destroy(ht);
}

void test_remove()
{


  elem_t key = int_elem(34);
  elem_t value = int_elem(123);

  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash, int_eq);


  elem_t result = int_elem(0);
  
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, int_elem(0).i);
  

  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  ioopm_hash_table_remove(ht, key);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, int_elem(123).i);

    ioopm_hash_table_remove(ht, key);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, int_elem(123).i);
 
 
  ioopm_hash_table_destroy(ht);
}


  void test_bool() 
{

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);

  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);


  
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));



  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  ioopm_hash_table_remove(ht, key);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
 
  ioopm_hash_table_destroy(ht);
}
void test_size_function() {

ioopm_hash_table_t *ht = ioopm_hash_table_create(string_hash, string_eq);
  elem_t key1 = string_elem("Max");
  elem_t value1 = string_elem("123");

  elem_t key2 = string_elem("Alfred");
  elem_t value2 = int_elem(666);

  elem_t key3 = string_elem("Max2");
  elem_t value3 = bool_elem(false);
  
  elem_t key4 = string_elem("Alfred2");
  elem_t value4 = ptr_elem(&value2);

  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key1));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key4));
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 0);



  ioopm_hash_table_insert(ht, key1, value1);
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 1);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));


  ioopm_hash_table_insert(ht, key2, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 2);

  ioopm_hash_table_insert(ht, key3, value3);
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 3);


  ioopm_hash_table_insert(ht, key4, value4);
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 4);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key3));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key4));


  ioopm_hash_table_insert(ht, key3, value3);
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 4);

  ioopm_hash_table_remove(ht, key1);
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 3);

   ioopm_hash_table_remove(ht, key2);
  ioopm_hash_table_remove(ht, key3);
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 1);

  ioopm_hash_table_remove(ht,key4);
  CU_ASSERT_TRUE(ioopm_hash_table_size(ht) == 0);

  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
 
  ioopm_hash_table_destroy(ht);
}

 void test_iterator_several_entries()
{
  int a = 4;
  int *pA = &a;
   int b = 7;
  int *pB = &b;
   int c = 6;
  int *pC = &c;
  elem_t keys[3] = {ptr_elem(pA),ptr_elem(pB),ptr_elem(pC)};
  elem_t values[3] = {int_elem(0), string_elem("tjo"), bool_elem(true)};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(ptr_hash, ptr_eq);
  for (size_t i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  size_t iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
  CU_ASSERT_EQUAL(iteration_count, 3);
} 

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Test hashtable and iterator", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "test Size", test_size_function) == NULL) ||
    (CU_add_test(my_test_suite, "test has key and is empty", test_bool) == NULL) || 
    (CU_add_test(my_test_suite, "test Create and destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "test insert", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "test remove", test_remove) == NULL) ||
    (CU_add_test(my_test_suite, "test destroy with entry", test_destroy_with_entry) == NULL) ||
    (CU_add_test(my_test_suite, "test destroy with entry", test_ptr_keys) == NULL) || 
    (CU_add_test(my_test_suite, "test destroy with entry", test_iterator_several_entries) == NULL) || 
    0

  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
} 

// gcc -Wall hash_table.c hash_table_tests.c -o hash_table_tests -lcunit
// gcc -Wall hash_table.c hash_table_iterator.c hash_table_tests.c -o hash_table_tests -lcunit
// gcov hash_table_tests-hash_table.gcno hash_table_tests-hash_table_iterator.gcno