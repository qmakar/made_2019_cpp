CC=g++

all: vector

vector: main.o 
	$(CC) -o vector main.o 

main.o: main.cpp
	$(CC) -std=c++11 -c  main.cpp

test:
	./vector

clean:
	rm -rf *.o vector