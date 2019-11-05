CC=g++

all: callback

callback: main.o parser.o token_processing.o test.o
	$(CC) -o callback.out main.o parser.o token_processing.o test.o

main.o: main.cpp
	$(CC) -std=c++11 -c main.cpp

parser.o: parser.cpp parser.hpp
	$(CC) -std=c++11 -c parser.cpp

token_processing.o: token_processing.cpp token_processing.hpp
	$(CC) -std=c++11 -c token_processing.cpp

test.o: test.cpp test.hpp
	$(CC) -std=c++11 -c test.cpp

run:
	./callback.out "run"

test:
	./callback.out "test"

clean:
	rm -rf *.o callback.out