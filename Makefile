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

OBJECT = test.o core.o LinkedList.o BKTree.o HashTable.o constructors.o distance.o 
TESTS  = LinkedList_test.o

OUT   = testdriver
CC    = gcc
CXX   = g++
FLAGS = -O3 -fPIC -Wall -Werror -g -I

all: clean testdriver tests

testdriver: $(OBJECT)
	$(CXX) $(FLAGS) -o $(OUT) $(OF)/test.o $(OF)/core.so $(OF)/LinkedList.so $(OF)/BKTree.so $(OF)/HashTable.so $(OF)/constructors.so $(OF)/distance.so 
	mv $(OUT) $(EXE)
test.o:
	$(CXX) $(FLAGS) -c -o test.o test.cpp
	mv test.o $(OF)
core.o:
	$(CC) $(FLAGS) -c -o $(SF)/core.c
	$(CC) $(FLAGS) -shared -o core.so core.o
	mv core.o core.so $(OF)
LinkedList.o:
	$(CC) $(FLAGS) -c -o $(SF)/LinkedList.c
	$(CC) $(FLAGS) -shared -o LinkedList.so LinkedList.o
	mv BKTree.o LinkedList.so $(OF)
BKTree.o:
	$(CC) $(FLAGS) -c -o $(SF)/BKTree.c
	$(CC) $(FLAGS) -shared -o BKTree.so BKTree.o
	mv BKTree.o BKTree.so $(OF)
HashTable.o:
	$(CC) $(FLAGS) -c -o $(SF)/HashTable.c
	$(CC) $(FLAGS) -shared -o HashTable.so HashTable.o
	mv BKTree.o HashTable.so $(OF)
constructors.o:
	$(CC) $(FLAGS) -c -o $(SF)/constructors.c
	$(CC) $(FLAGS) -shared -o constructors.so constructors.o
	mv BKTree.o constructors.so $(OF)
distance.o:
	$(CC) $(FLAGS) -c -o $(SF)/distance.c
	$(CC) $(FLAGS) -shared -o distance.so distance.o
	mv BKTree.o distance.so $(OF)

run:
	./$(EXE)/testdriver

tests: tests.o
	$(CC) $(FLAGS) -o LinkedList_test $(OF)/LinkedList_test.o $(OF)/LinkedList.c $(OF)/constructors.o
	mv LinkedList_test $(EXE)
tests.o:
	$(CC) $(FLAGS) -c $(TEST)/LinkedList.c
	mv $(TESTS) $(OF)
	
run-tests:
	./$(EXE)/LinkedList_test

clean:
	rm -f $(OF)/*.o $(OF)/*.so $(EXE)/$(OUT) $(EXE)/*_test
val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/$(OUT)
count:
	wc $(SF)/* $(HF)/* $(TEST)/*
