#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"

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

void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_destroy_with_entry()
{   char *key = "abc";
    int value = 123;

   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_insert(ht, key, value);
   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove()
{

  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;


  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);


  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, value);

  ioopm_hash_table_remove(ht, key);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);

    ioopm_hash_table_remove(ht, key);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result, 0);
 
 
  ioopm_hash_table_destroy(ht);
}


  void test_bool() 
{

  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *key = "abc";
  int value = 123;


  
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

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key1 = "Max";
  int value1 = 9;

  char *key2 = "Alfred";
  int value2 = 666;

    char *key3 = "Max2";
  int value3 = 73;
  
  char *key4 = "Alfred2";
  int value4 = 687;

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
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;

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