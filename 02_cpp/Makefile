CC=g++

all: alloc

alloc: main.o allocator.o test.o 
	$(CC) -o alloc.out main.o allocator.o test.o

main.o: main.cpp
	$(CC) -std=c++11 -c  main.cpp

allocator.o: allocator.cpp allocator.hpp
	$(CC) -std=c++11 -c allocator.cpp

test.o: test.cpp test.hpp
	$(CC) -std=c++11 -c test.cpp

test:
	./alloc.out

clean:
	rm -rf *.o alloc.out