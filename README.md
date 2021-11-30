 University: UoA DIT
 Course : [K23a] Software Development for Computer Systems
 Semester : Fall 2021-2022
 Professor : Yannis Ioannidis 
 --------------------------------
 Students: Stylianos Oikonomou , Anastasios Triantafyllou
 ID : 1115201500243 , 1115201600173 
 --------------------------------
 Project : Assignment_1
 File : README.md
 --------------------------------

Executionp
- To compile the program, run "make". To compile the tests, run "make tests".
- To run the program, run "make run". To run the tests, run "make run-tests".
- To run valgrind on the executables, run "make val" and make "val-tests".
- To remove all generated object and executable files, run "make clean".

CandidateList
- The candidate list data structure is a simple linked list implementation and it is used during the search of an index BKTree. It is the list that houses all the "candidate" words of the tree, meaning all the words that meet the range criteria to be explored, according to the definition of the BKTree. The functions implemented are self explanatory, no need to expand upon them.

BK-Tree
- The children of each node are initialized, during the creation of the node, as an array of MAX_WORD_LENGTH size and set to NULL.

EntryList

- NOTE: The data structures used in this file are all defined in the "DataStructs.h" header, in order to avoid recursive inclusion, as they are also used by the BKTree source file.

- The EntryList.c file contains implementation of functions that create and utilize a generic List data structure, which are built upon to create the Entry-List implementation. More specifically: 
- - create/destroy_list() act as the generic list's constructor and destructor, respectively
- - insert_list() pushes items of any form into the list by creating a listnode on which it attaches the given data and concatinating it to the list's tail
- - destroy_node() is called by the list's destructor and it recursively destroys every listnode contained in the list, as well as calling any item destructor for the listnode's data, if specified (for the needs of this project, it just supports an entry's destructor)
- The functions listed above would ideally have their own file, but this step was skipped.

- The entry_list (including add_entry()) functions are implemented by calling all generic list functions. They use/return the List data structure's pointers, as there is no EntryList specific data type (which we skipped creating, it would add better abstraction but provide zero extra functionality).
- The create_entry(), destroy_entry() and copy_entry() functions are simple constructor, destructor and copy-constructor for the entry data structure.
- The get_number_entries() function returns the amount of listnodes in a given list, which is saved in the List structure. The amount of listnodes should always equal the amount of entries in an EntryList.
- The get_first() and get_next() functions only work on EntryLists, as they typecast the (list's head) / (next of given listnode's) data to Entry* in order to return it.
- The print_entry_list() was created to serve as a debugging and program validation utility.

- The 3 entry_index related functions all use the BKTree implementation, which has been described.

Distance

- The distance.c file implements the hamming distance, edit distance and exact match functions, that are called by the generic function distance(), depending on its MatchType parameter. The file also includes a small min_int utility function that returns the smallest of 2 ints.

Tests

- Most test files were written post-implementation and are not structured in a quite readable manner. However, they do test their corresponding implementation to a good extend, checking most, if not all, edge cases and average cases, to an extent that makes us confident our implementation is fullproof as far as it is used to build this project.

Main

- The main.c file can also be viewed as a small testing unit, putting together everything implemented to support the project's demands.

References:
- For the edit distance algorithm, this video was consulted: https://www.youtube.com/watch?v=We3YDTzNXEk, which contains a variation of the algorithm found in some lecture slides by Professor Misyrlis. The original algorithm finds the longest common subsequence (ΜΚΥ - Μέγιστη Κοινή Υπακολουθία) between two sequences and I unfortunately cannot embed it here, but it's included in the repository.
- int prime_sizes[] used in hashtables was taken from https://github.com/chatziko-k08/lecture-code
- the djb2 algorithm: http://www.cse.yorku.ca/~oz/hash.html
