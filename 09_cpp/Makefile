CC=g++

all: threads

threads: main.o 
	$(CC) -o threads main.o 

main.o: main.cpp
	$(CC) -std=c++11 -c  main.cpp

test:
	./threads

clean:
	rm -rf *.o threads