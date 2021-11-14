##################################
# University: UoA DIT
# Course : [K23a] Software Development for Computer Systems
# Semester : Fall 2021-2022
# Professor : Yannis Ioannidis 
# --------------------------------
# Students: Stylianos Oikonomou , Anastasios Triantafyllou
# ID : 1115201500243 , 1115201600173 
# --------------------------------
# Project : Assignment_1
# File : 
##################################

SF   = ./SourceFiles
HF   = ./HeaderFiles
OF   = ./ObjectFiles
EXE  = ./Executables
AD   = ./AppData
TEST = ./Tests

OBJECT = Main.o BKTree.o WordList.o CandidateList.o distance.o EntryList.o HashTable.o
TESTS = BKTree_test.o CandidateList_test.o WordList_test.o distance_test.o EntryList_test.o HashTable_test.o

OUT   = Main
CC    = gcc
FLAGS = -Wall -Werror -g

all: Main tests

Main: $(OBJECT)
	$(CC) $(FLAGS) -o $(OUT) $(OF)/Main.o $(OF)/BKTree.o $(OF)/WordList.o $(OF)/CandidateList.o $(OF)/distance.o $(OF)/EntryList.o $(OF)/HashTable.o
	mv $(OUT) $(EXE)

Main.o: 
	$(CC) -I $(HF) $(FLAGS) -c $(SF)/Main.c
	mv Main.o $(OF) 
BKTree.o: 
	$(CC) -I $(HF) $(FLAGS) -c $(SF)/BKTree.c
	mv BKTree.o $(OF) 
WordList.o: 
	$(CC) -I $(HF) $(FLAGS) -c $(SF)/WordList.c
	mv WordList.o $(OF) 
CandidateList.o: 
	$(CC) -I $(HF) $(FLAGS) -c $(SF)/CandidateList.c
	mv CandidateList.o $(OF) 
distance.o:
	$(CC) -I $(HF) $(FLAGS) -c $(SF)/distance.c
	mv distance.o $(OF)
EntryList.o:
	$(CC) -I $(HF) $(FLAGS) -c $(SF)/EntryList.c
	mv EntryList.o $(OF)
HashTable.o:
	$(CC) -I $(HF) $(FLAGS) -c $(SF)/HashTable.c
	mv HashTable.o $(OF)


run:
	$(EXE)/$(OUT)

tests: tests.o
	$(CC) $(FLAGS) -o distance_test $(OF)/distance_test.o $(OF)/distance.o
	mv distance_test $(EXE)
	$(CC) $(FLAGS) -o WordList_test $(OF)/WordList_test.o $(OF)/WordList.o
	mv WordList_test $(EXE)
	$(CC) $(FLAGS) -o CandidateList_test $(OF)/CandidateList_test.o $(OF)/CandidateList.o
	mv CandidateList_test $(EXE)
	$(CC) $(FLAGS) -o BKTree_test $(OF)/BKTree_test.o $(OF)/BKTree.o $(OF)/EntryList.o $(OF)/CandidateList.o $(OF)/WordList.o $(OF)/distance.o
	mv BKTree_test $(EXE)
	$(CC) $(FLAGS) -o EntryList_test $(OF)/EntryList_test.o $(OF)/EntryList.o $(OF)/BKTree.o $(OF)/distance.o $(OF)/CandidateList.o 
	mv EntryList_test $(EXE)
	$(CC) $(FLAGS) -o HashTable_test $(OF)/HashTable_test.o $(OF)/HashTable.o $(OF)/WordList.o
	mv HashTable_test $(EXE)
tests.o:
	$(CC) -I $(HF) $(FLAGS) -c $(TEST)/distance_test.c
	$(CC) -I $(HF) $(FLAGS) -c $(TEST)/WordList_test.c
	$(CC) -I $(HF) $(FLAGS) -c $(TEST)/CandidateList_test.c
	$(CC) -I $(HF) $(FLAGS) -c $(TEST)/BKTree_test.c
	$(CC) -I $(HF) $(FLAGS) -c $(TEST)/EntryList_test.c
	$(CC) -I $(HF) $(FLAGS) -c $(TEST)/HashTable_test.c
	mv $(TESTS) $(OF)

run-tests:
	$(EXE)/distance_test
	$(EXE)/WordList_test
	$(EXE)/CandidateList_test
	$(EXE)/HashTable_test
	$(EXE)/EntryList_test
	$(EXE)/BKTree_test

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/$(OUT)

val-tests:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/distance_test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/WordList_test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/CandidateList_test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/BKTree_test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/HashTable_test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(EXE)/EntryList_test

clean:
	rm -f $(OF)/*.o $(EXE)/$(OUT) $(EXE)/*_test

count:
	wc $(SF)/* $(HF)/*