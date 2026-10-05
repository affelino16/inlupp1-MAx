#include <CUnit/Basic.h>
#include "linked_list.h"
#include "linked_list_iterator.h"

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test my_test_suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test my_test_suite
  return 0;
}



void test_create_destroy()
{
   ioopm_list_t *it = ioopm_list_create();
   CU_ASSERT_PTR_NOT_NULL(it);
   ioopm_list_destroy(it);
}


void test_empty_list(void) {
    ioopm_list_t *list = ioopm_list_create();
    CU_ASSERT_TRUE(ioopm_list_is_empty(list));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 0);
    ioopm_list_destroy(list);
}

void test_append(void) {
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, int_elem(1));
    CU_ASSERT_FALSE(ioopm_list_is_empty(list));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 1);

    ioopm_list_append(list, int_elem(2));
    ioopm_list_append(list, int_elem(3));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 3);

    ioopm_list_destroy(list);
}

void test_prepend(void) {
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_prepend(list, int_elem(1));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 1);

    ioopm_list_prepend(list, int_elem(2));
    ioopm_list_prepend(list, int_elem(3));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 3);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 1);

    ioopm_list_destroy(list);
}


void test_insert_into_empty(void) {
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_insert(list, 0, int_elem(42));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 42);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 42);

    ioopm_list_destroy(list);
}



void test_remove_first(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(2));
    ioopm_list_append(list, int_elem(3));

    elem_t removed = ioopm_list_remove(list, 0);
    CU_ASSERT_EQUAL(removed.i, 1);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 2);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 3);

    ioopm_list_destroy(list);
}



void test_remove_last(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(2));
    ioopm_list_append(list, int_elem(3));

    elem_t removed = ioopm_list_remove(list, 2);
    CU_ASSERT_EQUAL(removed.i, 3);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 2);

    ioopm_list_append(list, int_elem(4));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 4);

    ioopm_list_destroy(list);
}

void test_remove_only_element(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(7));

    elem_t removed = ioopm_list_remove(list, 0);
    CU_ASSERT_EQUAL(removed.i, 7);
    CU_ASSERT_TRUE(ioopm_list_is_empty(list));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 0);
    ioopm_list_destroy(list);
}

void test_remove_and_append(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(7));

    elem_t removed = ioopm_list_remove(list, 0);
    CU_ASSERT_EQUAL(removed.i, 7);
    CU_ASSERT_TRUE(ioopm_list_is_empty(list));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 0);

    ioopm_list_append(list, int_elem(8));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 8);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 8);

    ioopm_list_destroy(list);
}

void test_remove_all(void) {
    ioopm_list_t *list = ioopm_list_create();
    for (int i = 0; i < 10; i++) {
        ioopm_list_append(list, int_elem(i));
    }
    for (int i = 0; i < 10; i++) {
        CU_ASSERT_EQUAL(ioopm_list_remove(list, 0).i, i);
    }
    CU_ASSERT_TRUE(ioopm_list_is_empty(list));

    ioopm_list_destroy(list);
}



int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test my_test_suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Linked list tests", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test my_test_suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test my_test_suite.
  // For each call to CU_add_test we specify the test my_test_suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "A simple test", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "empty list", test_empty_list) == NULL) ||
        (CU_add_test(my_test_suite, "append", test_append) == NULL) ||
        (CU_add_test(my_test_suite, "prepend", test_prepend) == NULL) ||
        (CU_add_test(my_test_suite, "insert into empty", test_insert_into_empty) == NULL) ||
        (CU_add_test(my_test_suite, "remove first", test_remove_first) == NULL) ||
        (CU_add_test(my_test_suite, "remove last", test_remove_last) == NULL) ||
        (CU_add_test(my_test_suite, "remove only element", test_remove_only_element) == NULL) ||
        (CU_add_test(my_test_suite, "remove all", test_remove_all) == NULL) ||
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

// gcc -Wall linked_list.c linked_list_iterator.c linked_list_tests.c -o linked_list_tests -lcunit