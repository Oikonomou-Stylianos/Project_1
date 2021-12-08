all: clean test

test:
	gcc -o test LinkedList.c BKTree.c HashTable.c constructors.c distance.c libcore.c

run:
	./test

clean:
	rm -f test

val:
	valgrind ./test