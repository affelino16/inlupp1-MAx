CC      = gcc
CFLAGS  = -Wall -pedantic -g -std=c11
LDLIBS  = -lcunit

HT_OBJS = hash_table.o hash_table_iterator.o
LL_OBJS = linked_list.o linked_list_iterator.o

.PHONY: all test memtest coverage run prof clean

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
	$(CC) $(CFLAGS) --coverage linked_list_tests.c linked_list.c linked_list_iterator.c -o linked_list_tests_cov $(LDLIBS)
	./hash_table_tests_cov
	./linked_list_tests_cov
	gcov hash_table_tests_cov-hash_table.c hash_table_tests_cov-hash_table_iterator.c linked_list_tests_cov-linked_list.c linked_list_tests_cov-linked_list_iterator.c

# --- Profiling (gprof) ---
PROF_INPUTS = small.txt 1k-long-words.txt 10k-words.txt 16k-words.txt
PROF_SRCS   = freq_count.c hash_table.c hash_table_iterator.c

freq_count_prof: $(PROF_SRCS) hash_table.h hash_table_iterator.h common.h
	$(CC) $(CFLAGS) -pg $(PROF_SRCS) -o $@

# Kör freq_count_prof på varje indatafil och sparar en gprof-rapport per fil
prof: freq_count_prof
	@for f in $(PROF_INPUTS); do \
		echo "== Profilerar $$f =="; \
		./freq_count_prof $$f > /dev/null; \
		gprof ./freq_count_prof gmon.out > gprof_$${f%.txt}.txt; \
		echo "   -> gprof_$${f%.txt}.txt"; \
	done
	@rm -f gmon.out

clean:
	rm -f *.o *.gcda *.gcno *.gcov freq_count hash_table_tests linked_list_tests hash_table_tests_cov linked_list_tests_cov \
	      freq_count_prof gmon.out gprof_*.txt
