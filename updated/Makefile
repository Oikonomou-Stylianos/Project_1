all: clean test

test:

# gcc -c LinkedList.c
# gcc -c BKTree.c
# gcc -c HashTable.c
# gcc -c constructors.c
# gcc -c distance.c
# gcc -c libcore.c

# $(CXX) $(CXXFLAGS) -shared -o lib$(LIBRARY).so $(IMPL_O)
	gcc -O3 -fPIC -g -I. -c -o libcore.o libcore.c
	gcc -O3 -fPIC -g -I. -shared -o libcore.so libcore.o
	gcc -O3 -fPIC -g -I. -c -o BKTree.o BKTree.c
	gcc -O3 -fPIC -g -I. -shared -o BKTree.so BKTree.o
	gcc -O3 -fPIC -g -I. -c -o LinkedList.o LinkedList.c
	gcc -O3 -fPIC -g -I. -shared -o LinkedList.so LinkedList.o
	gcc -O3 -fPIC -g -I. -c -o HashTable.o HashTable.c
	gcc -O3 -fPIC -g -I. -shared -o HashTable.so HashTable.o
	gcc -O3 -fPIC -g -I. -c -o constructors.o constructors.c
	gcc -O3 -fPIC -g -I. -shared -o constructors.so constructors.o
	gcc -O3 -fPIC -g -I. -c -o distance.o distance.c
	gcc -O3 -fPIC -g -I. -shared -o distance.so distance.o

	g++ -O3 -fPIC -g -I. -c -o test.o test.cpp 
	
	g++ -O3 -fPIC -g -I. -o testdriver test.o ./libcore.so ./LinkedList.so ./BKTree.so ./HashTable.so ./constructors.so ./distance.so
# gcc libcore.c LinkedList.o BKTree.o HashTable.o constructors.o distance.o

# gcc -o test LinkedList.c BKTree.c HashTable.c constructors.c distance.c
# gcc -c LinkedList.c
# gcc -c BKTree.c
# g++ -O3 -fPIC -Wall -g -I -c -o testdriver test.so libcore.so LinkedList.so BKTree.so HashTable.so constructors.so distance.so
test:
	gcc -O3 -fPIC -g -I. -c -o libcore1.o libcore1.c
	gcc -O3 -fPIC -g -I. -shared -o libcore1.so libcore1.o
	gcc -O3 -fPIC -g -I. -c -o BKTree.o BKTree.c
	gcc -O3 -fPIC -g -I. -shared -o BKTree.so BKTree.o
	gcc -O3 -fPIC -g -I. -c -o LinkedList.o LinkedList.c
	gcc -O3 -fPIC -g -I. -shared -o LinkedList.so LinkedList.o
	gcc -O3 -fPIC -g -I. -c -o HashTable.o HashTable.c
	gcc -O3 -fPIC -g -I. -shared -o HashTable.so HashTable.o
	gcc -O3 -fPIC -g -I. -c -o constructors.o constructors.c
	gcc -O3 -fPIC -g -I. -shared -o constructors.so constructors.o
	gcc -O3 -fPIC -g -I. -c -o distance.o distance.c
	gcc -O3 -fPIC -g -I. -shared -o distance.so distance.o

	g++ -O3 -fPIC -g -I. -c -o test.o test.cpp 
	
	g++ -O3 -fPIC -g -I. -o testdriver test.o ./libcore1.so ./LinkedList.so ./BKTree.so ./HashTable.so ./constructors.so ./distance.so	

run:
	./testdriver

clean:
	rm -f testdriver *.o *.so

val:
	valgrind ./testdriver