CC=g++

all: do

do: main.o BigInt.o
	$(CC) -o do.out main.o BigInt.o

main.o: main.cpp  
	$(CC) -std=c++11 -c main.cpp

BigInt.o: BigInt.cpp BigInt.hpp 
	$(CC) -std=c++11 -c BigInt.cpp


test:
	./do.out

clean:
	rm -rf *.o do.out