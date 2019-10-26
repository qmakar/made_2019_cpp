CC=g++

all: calc

calc: main.o
	$(CC) -o calc.out main.o

main.o: main.cpp main.h
	$(CC) -c main.cpp


run:
	./calc.out "$(var)"

test:
	python3 test.py

clean:
	rm -rf *.o calc.out