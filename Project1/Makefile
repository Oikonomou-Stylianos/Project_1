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

SF  = ./SourceFiles
HF  = ./HeaderFiles
OF  = ./ObjectFiles
EXE = ./Executables
AD  = ./AppData

OBJECT = Main.o BKTree.o WordList.o CandidateList.o distance.o
# SOURCE = Main.c BKTree.c WordList.c CandidateList.c distance.c
# HEADER = BKTree.c WordList.c CandidateList.c common_types.h

OUT    = Main
CC     = gcc
FLAGS  = -Wall -Werror -g

Main: Main.o BKTree.o WordList.o CandidateList.o distance.o
	$(CC) $(FLAGS) -o $(OUT) $(OF)/Main.o $(OF)/BKTree.o $(OF)/WordList.o $(OF)/CandidateList.o $(OF)/distance.o
	mv $(OUT) $(EXE) 	
Main.o: 
	$(CC) $(FLAGS) -c $(SF)/Main.c
	mv Main.o $(OF) 
BKTree.o: 
	$(CC) $(FLAGS) -c $(SF)/BKTree.c
	mv BKTree.o $(OF) 
WordList.o: 
	$(CC) $(FLAGS) -c $(SF)/WordList.c
	mv WordList.o $(OF) 
CandidateList.o: 
	$(CC) $(FLAGS) -c $(SF)/CandidateList.c
	mv CandidateList.o $(OF) 
distance.o:
	$(CC) $(FLAGS) -c $(SF)/distance.c
	mv distance.o $(OF) 

run:
	$(EXE)/$(OUT)

val:
	valgrind -s --leak-check=full --track-origins=yes $(EXE)/$(OUT)

clean:
	rm -f $(EXE)/$(OUT) $(OF)/$(OBJECT)

count:
	wc $(SF)/* $(HF)/*