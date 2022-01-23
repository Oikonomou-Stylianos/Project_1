##################################
# University: UoA DIT
# Course : [K23a] Software Development for Computer Systems
# Semester : Fall 2021-2022
# Professor : Yannis Ioannidis 
# Assistant : Sarantis Paskalis
# --------------------------------
# Students: Stylianos Oikonomou , Anastasios Triantafyllou
# ID : 1115201500243 , 1115201600173 
# --------------------------------
# File : Makefile
##################################

SF   = ./SourceFiles
HF   = ./HeaderFiles
OF   = ./ObjectFiles
EXE  = ./Executables
TEST = ./Tests

TESTS   = LinkedList_test BKTree_test HashTable_test constructors_test distance_test
TESTS_O = LinkedList_test.o BKTree_test.o HashTable_test.o constructors_test.o distance_test.o

OUT   = testdriver
CC    = gcc
CXX   = g++
FLAGS = -O3 -fPIC -Wall -Werror -g -I $(HF)

##################################

testdriver:

	$(CXX) $(FLAGS) -c $(SF)/test.cpp
	$(CC) $(FLAGS) -c $(SF)/core.c

	$(CC) $(FLAGS) -c $(SF)/LinkedList.c
	$(CC) $(FLAGS) -c $(SF)/BKTree.c
	$(CC) $(FLAGS) -c $(SF)/HashTable.c
	$(CC) $(FLAGS) -c $(SF)/constructors.c
	$(CC) $(FLAGS) -c $(SF)/distance.c

	$(CC) $(FLAGS) -c $(SF)/core_routines.c
	$(CC) $(FLAGS) -c $(SF)/Scheduler.c

	mv test.o core.o LinkedList.o BKTree.o HashTable.o constructors.o distance.o core_routines.o Scheduler.o $(OF)

	$(CC) $(FLAGS) -shared -pthread -o libcore.so $(OF)/core.o $(OF)/LinkedList.o $(OF)/BKTree.o $(OF)/HashTable.o $(OF)/constructors.o $(OF)/distance.o $(OF)/core_routines.o $(OF)/Scheduler.o
	mv libcore.so $(OF)
	
	$(CXX) $(FLAGS) -o $(OUT) $(OF)/test.o $(OF)/libcore.so
	mv $(OUT) $(EXE)

run:
	$(EXE)/$(OUT)
val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --gen-suppressions=yes $(EXE)/$(OUT)

##################################

tests:

	$(CC) $(FLAGS) -c $(TEST)/LinkedList_test.c
	$(CC) $(FLAGS) -c $(TEST)/BKTree_test.c
	$(CC) $(FLAGS) -c $(TEST)/HashTable_test.c
	$(CC) $(FLAGS) -c $(TEST)/constructors_test.c
	$(CC) $(FLAGS) -c $(TEST)/distance_test.c
	mv $(TESTS_O) $(OF)

	$(CC) $(FLAGS) -o LinkedList_test $(OF)/LinkedList_test.o $(OF)/LinkedList.o $(OF)/constructors.o
	$(CC) $(FLAGS) -o BKTree_test $(OF)/BKTree_test.o $(OF)/BKTree.o $(OF)/LinkedList.o $(OF)/constructors.o $(OF)/distance.o
	$(CC) $(FLAGS) -o HashTable_test $(OF)/HashTable_test.o $(OF)/HashTable.o $(OF)/LinkedList.o $(OF)/constructors.o
	$(CC) $(FLAGS) -o constructors_test $(OF)/constructors_test.o $(OF)/constructors.o $(OF)/LinkedList.o 
	$(CC) $(FLAGS) -o distance_test $(OF)/distance_test.o $(OF)/distance.o
	mv $(TESTS) $(EXE)

run-tests:
	$(EXE)/LinkedList_test
	$(EXE)/BKTree_test
	$(EXE)/HashTable_test
	$(EXE)/constructors_test
	$(EXE)/distance_test
	
val-tests:
#--leak-check=full --show-leak-kinds=all --track-origins=yes 
	valgrind $(EXE)/LinkedList_test
	valgrind $(EXE)/BKTree_test
	valgrind $(EXE)/HashTable_test
	valgrind $(EXE)/constructors_test
	valgrind $(EXE)/distance_test

##################################

testdriver-ref:

	$(CXX) $(FLAGS) -c $(SF)/test.cpp
	$(CXX) $(FLAGS) -c $(SF)/core_ref.cpp

	$(CC) $(FLAGS) -c $(SF)/LinkedList.c
	$(CC) $(FLAGS) -c $(SF)/BKTree.c
	$(CC) $(FLAGS) -c $(SF)/HashTable.c
	$(CC) $(FLAGS) -c $(SF)/constructors.c
	$(CC) $(FLAGS) -c $(SF)/distance.c
	mv test.o LinkedList.o BKTree.o HashTable.o constructors.o distance.o core_ref.o $(OF)

	$(CC) $(FLAGS) -shared -o libcore_ref.so $(OF)/core_ref.o $(OF)/LinkedList.o $(OF)/BKTree.o $(OF)/HashTable.o $(OF)/constructors.o $(OF)/distance.o
	mv libcore_ref.so $(OF)
	
	$(CXX) $(FLAGS) -o $(OUT) $(OF)/test.o $(OF)/libcore_ref.so
	mv $(OUT) $(EXE)

ref: testdriver-ref

val-ref: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/$(OUT)

##################################

clean:
	rm -f $(OF)/*.o $(OF)/*.so $(EXE)/$(OUT) $(EXE)/*_test ./*.o
count:
	wc $(SF)/* $(HF)/* $(TEST)/*

##################################