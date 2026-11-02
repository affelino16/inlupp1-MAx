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

// =====================================================================
// [CLAUDE] Tester nedan (till och med "[CLAUDE] slut") är skrivna av Claude
// =====================================================================

// ---------- Lista ----------

// [CLAUDE] get på varje index, inklusive första och sista
void test_get(void) {
    ioopm_list_t *list = ioopm_list_create();
    for (int i = 0; i < 5; i++) {
        ioopm_list_append(list, int_elem(i * 10));
    }
    for (int i = 0; i < 5; i++) {
        CU_ASSERT_EQUAL(ioopm_list_get(list, i).i, i * 10);
    }
    ioopm_list_destroy(list);
}

// [CLAUDE] insert mitt i listan (else-grenen i ioopm_list_insert)
void test_insert_middle(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(2));
    ioopm_list_append(list, int_elem(4));

    ioopm_list_insert(list, 2, int_elem(3));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 4);
    for (int i = 0; i < 4; i++) {
        CU_ASSERT_EQUAL(ioopm_list_get(list, i).i, i + 1);
    }
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 4);

    ioopm_list_destroy(list);
}

// [CLAUDE] insert på index 0 och index == size i en icke-tom lista
void test_insert_front_and_end(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(2));

    ioopm_list_insert(list, 0, int_elem(1));
    ioopm_list_insert(list, ioopm_list_size(list), int_elem(3));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 2);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 3);

    ioopm_list_destroy(list);
}

// [CLAUDE] remove mitt i listan, last ska inte ändras
void test_remove_middle(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(2));
    ioopm_list_append(list, int_elem(3));

    CU_ASSERT_EQUAL(ioopm_list_remove(list, 1).i, 2);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 3);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 3);

    ioopm_list_destroy(list);
}

// [CLAUDE] blandar prepend och append, kollar att head/last hänger med
void test_prepend_then_append(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_prepend(list, int_elem(2));
    ioopm_list_prepend(list, int_elem(1));
    ioopm_list_append(list, int_elem(3));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    for (int i = 0; i < 3; i++) {
        CU_ASSERT_EQUAL(ioopm_list_get(list, i).i, i + 1);
    }
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 3);

    ioopm_list_destroy(list);
}

// [CLAUDE] andra elem_t-typer än int (pekare och strängar)
void test_other_elem_types(void) {
    ioopm_list_t *list = ioopm_list_create();
    int x = 5;
    char *str = "hej";
    ioopm_list_append(list, ptr_elem(&x));
    ioopm_list_append(list, string_elem(str));
    ioopm_list_append(list, bool_elem(true));

    CU_ASSERT_PTR_EQUAL(ioopm_list_get(list, 0).p, &x);
    CU_ASSERT_STRING_EQUAL(ioopm_list_get(list, 1).s, "hej");
    CU_ASSERT_TRUE(ioopm_list_get(list, 2).b);

    ioopm_list_destroy(list);
}

// [CLAUDE] destroy på en lista med många element (kör med valgrind för läckor)
void test_destroy_nonempty(void) {
    ioopm_list_t *list = ioopm_list_create();
    for (int i = 0; i < 100; i++) {
        ioopm_list_append(list, int_elem(i));
    }
    CU_ASSERT_EQUAL(ioopm_list_size(list), 100);
    ioopm_list_destroy(list);
}

// ---------- Iterator ----------

// [CLAUDE] iterator på tom lista ska direkt vara at_end
void test_iterator_empty(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);

    CU_ASSERT_PTR_NOT_NULL(iter);
    CU_ASSERT_TRUE(ioopm_list_iterator_at_end(iter));

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// [CLAUDE] gå igenom hela listan med current/advance
void test_iterator_traverse(void) {
    ioopm_list_t *list = ioopm_list_create();
    for (int i = 0; i < 4; i++) {
        ioopm_list_append(list, int_elem(i));
    }

    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    int count = 0;
    while (!ioopm_list_iterator_at_end(iter)) {
        CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, count);
        ioopm_list_iterator_advance(iter);
        count++;
    }
    CU_ASSERT_EQUAL(count, 4);

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// [CLAUDE] iterator remove av första elementet (previous == NULL)
void test_iterator_remove_first(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(2));

    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    CU_ASSERT_EQUAL(ioopm_list_iterator_remove(iter).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 2);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 2);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 2);

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// [CLAUDE] iterator remove i mitten och sist, last ska uppdateras
void test_iterator_remove_middle_and_last(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(2));
    ioopm_list_append(list, int_elem(3));

    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_advance(iter);

    CU_ASSERT_EQUAL(ioopm_list_iterator_remove(iter).i, 2);
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 3);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);

    CU_ASSERT_EQUAL(ioopm_list_iterator_remove(iter).i, 3);
    CU_ASSERT_TRUE(ioopm_list_iterator_at_end(iter));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 1);

    // last måste peka rätt för att append ska fungera
    ioopm_list_append(list, int_elem(4));
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 4);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 4);

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// [CLAUDE] iterator remove av enda elementet, listan ska bli tom och fungera igen
void test_iterator_remove_only(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(7));

    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    CU_ASSERT_EQUAL(ioopm_list_iterator_remove(iter).i, 7);
    CU_ASSERT_TRUE(ioopm_list_iterator_at_end(iter));
    CU_ASSERT_TRUE(ioopm_list_is_empty(list));

    ioopm_list_append(list, int_elem(8));
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 8);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 8);

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// [CLAUDE] iterator insert i tom lista (previous == NULL och next == NULL)
void test_iterator_insert_empty(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);

    ioopm_list_iterator_insert(iter, int_elem(5));
    CU_ASSERT_FALSE(ioopm_list_iterator_at_end(iter));
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 5);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 5);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 5);

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// [CLAUDE] iterator insert först i en icke-tom lista
void test_iterator_insert_front(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(2));

    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_insert(iter, int_elem(1));

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 1);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 2);

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// [CLAUDE] iterator insert i mitten (previous != NULL, next != NULL)
void test_iterator_insert_middle(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(3));

    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    ioopm_list_iterator_advance(iter);
    ioopm_list_iterator_insert(iter, int_elem(2));

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 2);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    for (int i = 0; i < 3; i++) {
        CU_ASSERT_EQUAL(ioopm_list_get(list, i).i, i + 1);
    }
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 3);

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// [CLAUDE] iterator insert när iteratorn står i slutet, last ska uppdateras
void test_iterator_insert_at_end(void) {
    ioopm_list_t *list = ioopm_list_create();
    ioopm_list_append(list, int_elem(1));
    ioopm_list_append(list, int_elem(2));

    ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
    while (!ioopm_list_iterator_at_end(iter)) {
        ioopm_list_iterator_advance(iter);
    }
    ioopm_list_iterator_insert(iter, int_elem(3));

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 3);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 3);

    ioopm_list_append(list, int_elem(4));
    CU_ASSERT_EQUAL(ioopm_list_get(list, 3).i, 4);

    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(list);
}

// =====================================================================
// [CLAUDE] slut
// =====================================================================


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
    (CU_add_test(my_test_suite, "create and destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "empty list", test_empty_list) == NULL) ||
        (CU_add_test(my_test_suite, "append", test_append) == NULL) ||
        (CU_add_test(my_test_suite, "prepend", test_prepend) == NULL) ||
        (CU_add_test(my_test_suite, "remove and append", test_remove_and_append) == NULL) ||
        (CU_add_test(my_test_suite, "insert into empty", test_insert_into_empty) == NULL) ||
        (CU_add_test(my_test_suite, "remove first", test_remove_first) == NULL) ||
        (CU_add_test(my_test_suite, "remove last", test_remove_last) == NULL) ||
        (CU_add_test(my_test_suite, "remove only element", test_remove_only_element) == NULL) ||
        (CU_add_test(my_test_suite, "remove all", test_remove_all) == NULL) ||
        // [CLAUDE] registrering av Claudes tester
        (CU_add_test(my_test_suite, "get", test_get) == NULL) ||
        (CU_add_test(my_test_suite, "insert middle", test_insert_middle) == NULL) ||
        (CU_add_test(my_test_suite, "insert front and end", test_insert_front_and_end) == NULL) ||
        (CU_add_test(my_test_suite, "remove middle", test_remove_middle) == NULL) ||
        (CU_add_test(my_test_suite, "prepend then append", test_prepend_then_append) == NULL) ||
        (CU_add_test(my_test_suite, "other elem types", test_other_elem_types) == NULL) ||
        (CU_add_test(my_test_suite, "destroy nonempty", test_destroy_nonempty) == NULL) ||
        (CU_add_test(my_test_suite, "iterator empty", test_iterator_empty) == NULL) ||
        (CU_add_test(my_test_suite, "iterator traverse", test_iterator_traverse) == NULL) ||
        (CU_add_test(my_test_suite, "iterator remove first", test_iterator_remove_first) == NULL) ||
        (CU_add_test(my_test_suite, "iterator remove middle and last", test_iterator_remove_middle_and_last) == NULL) ||
        (CU_add_test(my_test_suite, "iterator remove only", test_iterator_remove_only) == NULL) ||
        (CU_add_test(my_test_suite, "iterator insert empty", test_iterator_insert_empty) == NULL) ||
        (CU_add_test(my_test_suite, "iterator insert front", test_iterator_insert_front) == NULL) ||
        (CU_add_test(my_test_suite, "iterator insert middle", test_iterator_insert_middle) == NULL) ||
        (CU_add_test(my_test_suite, "iterator insert at end", test_iterator_insert_at_end) == NULL) ||
        // [CLAUDE] slut på registrering
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