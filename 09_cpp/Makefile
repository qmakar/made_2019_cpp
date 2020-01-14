CC=g++

all: threads

threads: main.o 
	$(CC) -o threads main.o 

main.o: main.cpp Threads.h
	$(CC) -std=c++11 -c  main.cpp Threads.h

test:
	./threads

clean:
	rm -rf *.o threads