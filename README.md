University: UoA DIT  
Course : [K23a] Software Development for Computer Systems  
Semester : Fall 2021-2022  
Professor : Yannis Ioannidis  
Assistant : Sarantis Paskalis  
---------------------------------
Students: Stylianos Oikonomou , Anastasios Triantafyllou  
ID : 1115201500243 , 1115201600173  
---------------------------------
Project : Assignment_2  
File : README.md  
---------------------------------

### *Commands*
$ make
>     Compile all modules, testDriver and test files

$ make run
>     Execute testDriver

$ make run-tests
>     Execute unit tests

$ make val
>     Execute testDriver with Valgrind

$ make val-tests
>     Execute unit tests with Valgrind

$ make clean
>     Remove .o .so and executables

$ make count
>     Print the lines, word count and character count of all files

### *Execution Time*
#####    Machine
- CPU : AMD Ryzen 5 5600X 6-core 3.7Ghz
- RAM : 16.0 GB
#####    Average Time
- Our implementation : ~5.2 secs
- Reference implementation : ~14.3 secs 
### *Interface Implementation*
- The implementation of core.h was written in C in the corresponding core.c source file.
- In order to support compatibility with the given testdriver executable, a static structure named INDEX is used.
- The INDEX structure contains a hashtable used in exact_match searching, 1 + (MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1) BKTrees to support edit + hamming type searches, correspondingly, and 3 lists, one to serve as the main storage structure of all entries, which all other structure reference, one for the same task for queries and one that holds the results to be returned by GetNextAvailRes() calls.
- All the InitializeIndex() and DestroyIndex() functions do is initialize and destroy properly the structures mentioned above.
- The StartQuery() function initializes a new Query structure and adds it to the main Query list located in INDEX. All the words of the query are created as entries, if they do not already exist in the main Entry list in the INDEX structure, and appended to it.
- The EndQuery() function sets the flag attribute of the query's structure to false for the given query. The flag is checked before attempting any search regarding the query, effectively rendering it invinsible to the MatchDocument() function.
- The GetNextAvailRes() function reads and returns the contents of the result_list located in the INDEX structure. It utilizes a static N variable to return the Nth item in the list. N is incremented after every call of this function.
- The MatchDocument() function follows the following process: It tokenizes and deduplicates the input document and then, for each active query, it applies a search set by the query's match_type and distance for each word of the given document. The search is skipped if a search of the same exact type and distance has already been run by a previous query. After the search is finished, all of the result entries are saved in temporary structures, one for each different match_type and match_distance. The query is appended to the result_list only if all of its words are found in the temporary structure that matches its type and distance.

### *Data Structures*
1. LinkedList
2. BKTree
3. HashTable
- All Data Structures have been generalized in order to avoid duplicate implementations. To achieve that, each Data Structure receives during its initialization the DataType that will be stored in it, a destroyFunction used to free the stored data and a compareFunction used to compare two data of the same dataType
- The data are stored as void * type
- If the destroyFunction argument is set to NULL the delete functions will not free the data but only the node instead

### *Memory Leaks*
- When running the testdriver on Valgrind, there is a memory leak of 28,536 bytes in 96 blocks. Half the bytes of this leak are lost due to inproper handling of the allocated memory of the testdriver itself and the other half is allocated by our core.c implementation, but the testdriver itself tries to deallocated that memory. In more detail, the unsigned int *array which is returned by GetNextAvailRes(), containing all the query_ids that match a given document, is allocated internally (int our implementation) before being returned. In the test.cpp source code (line 161 if I didn't mess up its structure), the allocated memory of the returned array is improperly free'd as part of the testdriver's execution sequence. Initially, we tried freeing this memory, but we got a double free error. Since we didn't want to mess with the test.cpp source, we left the leaks as is and made this note explaining everything.

### *Distance*
- The distance.c file implements the hamming distance, edit distance and exact match functions, that are called by the generic function distance(), depending on its MatchType parameter. The file also includes a small min_int utility function that returns the smallest of 2 ints.

### *Tests*
- Most test files were written post-implementation and are not structured in a quite readable manner. However, they do test their corresponding implementation to a good extend, checking most, if not all, edge cases and average cases, to an extent that makes us confident our implementation is fullproof as far as it is used to build this project.

### *References*
- For the edit distance algorithm, this video was consulted: https://www.youtube.com/watch?v=We3YDTzNXEk, which contains a variation of the algorithm found in some lecture slides by Professor Misyrlis. The original algorithm finds the longest common subsequence (ΜΚΥ - Μέγιστη Κοινή Υπακολουθία) between two sequences and I unfortunately cannot embed it here, but it's included in the repository.
- int prime_sizes[] used in hashtables was taken from https://github.com/chatziko-k08/lecture-code
- the djb2 algorithm: http://www.cse.yorku.ca/~oz/hash.html
