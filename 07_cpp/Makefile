CC=g++

all: throw

throw: main.o 
	$(CC) -o throw.out main.o 

main.o: main.cpp Format.hpp
	$(CC) -std=c++11 -c  main.cpp

test:
	./throw.out

clean:
	rm -rf *.o throw.out