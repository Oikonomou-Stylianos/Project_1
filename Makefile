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
# Project : Assignment_2
# File : Makefile
##################################

SF   = ./SourceFiles
HF   = ./HeaderFiles
OF   = ./ObjectFiles
EXE  = ./Executables
AD   = ./AppData
TEST = ./Tests

OBJECT  = test.o core.o LinkedList.o BKTree.o HashTable.o constructors.o distance.o 
TESTS   = LinkedList_test BKTree_test HashTable_test
TESTS_O = LinkedList_test.o BKTree_test.o HashTable_test.o

OUT   = testdriver
CC    = gcc
CXX   = g++
FLAGS = -O3 -fPIC -Wall -Werror -g -I $(HF)

all: testdriver tests

testdriver: test.o core.o LinkedList.o BKTree.o HashTable.o constructors.o distance.o 
	$(CXX) $(FLAGS) -o $(OUT) $(OF)/test.o $(OF)/core.so $(OF)/LinkedList.so $(OF)/BKTree.so $(OF)/HashTable.so $(OF)/constructors.so $(OF)/distance.so 
	mv $(OUT) $(EXE)
test.o:
	$(CXX) $(FLAGS) -c -o test.o $(SF)/test.cpp
	mv test.o $(OF)
core.o:
	$(CC) $(FLAGS) -c $(SF)/core.c
	$(CC) $(FLAGS) -shared -o core.so core.o
	mv core.o core.so $(OF)
LinkedList.o:
	$(CC) $(FLAGS) -c $(SF)/LinkedList.c
	$(CC) $(FLAGS) -shared -o LinkedList.so LinkedList.o
	mv LinkedList.o LinkedList.so $(OF)
BKTree.o:
	$(CC) $(FLAGS) -c $(SF)/BKTree.c
	$(CC) $(FLAGS) -shared -o BKTree.so BKTree.o
	mv BKTree.o BKTree.so $(OF)
HashTable.o:
	$(CC) $(FLAGS) -c $(SF)/HashTable.c
	$(CC) $(FLAGS) -shared -o HashTable.so HashTable.o
	mv HashTable.o HashTable.so $(OF)
constructors.o:
	$(CC) $(FLAGS) -c $(SF)/constructors.c
	$(CC) $(FLAGS) -shared -o constructors.so constructors.o
	mv constructors.o constructors.so $(OF)
distance.o:
	$(CC) $(FLAGS) -c $(SF)/distance.c
	$(CC) $(FLAGS) -shared -o distance.so distance.o
	mv distance.o distance.so $(OF)

run:
	$(EXE)/testdriver

tests: tests.o
	$(CC) $(FLAGS) -o LinkedList_test $(OF)/LinkedList_test.o $(OF)/LinkedList.o $(OF)/constructors.o
	$(CC) $(FLAGS) -o BKTree_test $(OF)/BKTree_test.o $(OF)/BKTree.o $(OF)/LinkedList.o $(OF)/constructors.o $(OF)/distance.o
	$(CC) $(FLAGS) -o HashTable_test $(OF)/HashTable_test.o $(OF)/HashTable.o $(OF)/LinkedList.o $(OF)/constructors.o
	mv $(TESTS) $(EXE)
tests.o:
	$(CC) $(FLAGS) -c $(TEST)/LinkedList_test.c
	$(CC) $(FLAGS) -c $(TEST)/BKTree_test.c
	$(CC) $(FLAGS) -c $(TEST)/HashTable_test.c
	mv $(TESTS_O) $(OF)
	
run-tests:
	$(EXE)/LinkedList_test
	$(EXE)/BKTree_test
	$(EXE)/HashTable_test

clean:
	rm -f $(OF)/*.o $(OF)/*.so $(EXE)/$(OUT) $(EXE)/*_test
val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/$(OUT)
val-tests:
#--leak-check=full --show-leak-kinds=all --track-origins=yes 
	valgrind $(EXE)/LinkedList_test
	valgrind $(EXE)/BKTree_test
	valgrind $(EXE)/HashTable_test

count:
	wc $(SF)/* $(HF)/* $(TEST)/*
