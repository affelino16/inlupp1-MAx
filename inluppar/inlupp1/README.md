# Inlupp 1

Authors: Alfred Ingvoldstad, Max Molund

A generic hash table and linked list in C (both with iterators), plus a word
frequency counter built on top of the hash table.

## Building

build: `make all`

remove `make clean`


## Running the tests

- How to run all tests: `make test`
- How to run the tests with a memory checker: `make memtest`

- How to get a code coverage report: `make coverage`

## Running the program(s)

- How to run all programs: `make run`

### Frequency count

- How to run: `./freq_count file1 [file2 ... fileN]`
- Input: one or more text files.
- Output: every distinct word with how many times it appeared in all the
  files, most frequent first.

## Design decisions

- Errors are handled by: `assert`. 
- Ownership of keys and values: the hash table and the linked list never take
  ownership of keys or values. They only store the `elem_t` they are given.
- Memory is handled by `create`/`destroy` function.

# Initial Profiling Results

For each input, what are the top 3 functions?

small.txt - 1. ioopm_hash_table_iterator_at_end, 2. cmp_freq_words, 3. find_previous_entry

1k-long-words.txt - 1. string_eq, 2. find_previous_entry, 3. string_hash

10k-words.txt - 1. string_eq, 2. find_previous_entry, 3. string_hash

16k-words.txt - 1. find_previous_entry, 2. string_eq, 3. string_hash

For each input, are the top 3 functions in your code (that you have written), or is it in library functions?

it is ours

Are the top 3 functions in your code consistent across the inputs? Why? Why not?

for all except small.txt since it's not long enough to get a valid result.

Is there some kind of trend? (Possibly several)

string_eq, find_previous_entry and string_hash are the 3 most called functions

Do the results correspond with your expectations?

for the larger text files it more or less corresponded with our expectations, the small text file was more difficult to predict.

Based on these results, do you see a way to make your program go faster?

The way to make the program faster would be to focus on optimizing the 3 most used functions.

