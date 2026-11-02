CC      = gcc
CFLAGS  = -Wall -pedantic -g -std=c11
LDLIBS  = -lcunit

HT_OBJS = hash_table.o hash_table_iterator.o
LL_OBJS = linked_list.o linked_list_iterator.o

.PHONY: all test memtest coverage run clean

all: freq_count hash_table_tests linked_list_tests

# --- Executables ---
freq_count: freq_count.o $(HT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

hash_table_tests: hash_table_tests.o $(HT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

linked_list_tests: linked_list_tests.o $(LL_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

# --- Object files ---
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

hash_table.o:          hash_table.c hash_table.h common.h
hash_table_iterator.o: hash_table_iterator.c hash_table_iterator.h hash_table.h common.h
linked_list.o:         linked_list.c linked_list.h common.h
linked_list_iterator.o: linked_list_iterator.c linked_list_iterator.h linked_list.h common.h
freq_count.o:          freq_count.c hash_table.h hash_table_iterator.h common.h
hash_table_tests.o:    hash_table_tests.c hash_table.h hash_table_iterator.h common.h
linked_list_tests.o:   linked_list_tests.c linked_list.h linked_list_iterator.h common.h

# --- Running ---
test: hash_table_tests linked_list_tests
	./hash_table_tests
	./linked_list_tests

memtest: hash_table_tests linked_list_tests
	valgrind --leak-check=full --error-exitcode=1 ./hash_table_tests
	valgrind --leak-check=full --error-exitcode=1 ./linked_list_tests

run: freq_count
	./freq_count text.txt

# --- Coverage (gcov) ---
coverage:
	$(CC) $(CFLAGS) --coverage hash_table_tests.c hash_table.c hash_table_iterator.c -o hash_table_tests_cov $(LDLIBS)
	./hash_table_tests_cov
	gcov hash_table_tests_cov-hash_table.c hash_table_tests_cov-hash_table_iterator.c

clean:
	rm -f *.o *.gcda *.gcno *.gcov freq_count hash_table_tests linked_list_tests hash_table_tests_cov
