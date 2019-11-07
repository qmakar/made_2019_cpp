CC=g++

all: callback

callback: main.o Matrix.o
	$(CC) -o callback.out main.o Matrix.o 

main.o: main.cpp
	$(CC) -std=c++11 -c main.cpp

Matrix.o: Matrix.cpp Matrix.hpp
	$(CC) -std=c++11 -c Matrix.cpp


test:
	./callback.out

clean:
	rm -rf *.o callback.out