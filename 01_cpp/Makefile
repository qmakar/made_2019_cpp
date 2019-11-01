CC=g++

all: calc

calc: main.o base_operation.o expression.o Exception.o
	$(CC) -o calc.out main.o base_operation.o expression.o Exception.o

main.o: main.cpp main.hpp
	$(CC) -c main.cpp

base_operation.o: base_operation.cpp base_operation.hpp
	$(CC) -c base_operation.cpp

expression.o: expression.cpp expression.hpp
	$(CC) -c expression.cpp

Exception.o: Exception.cpp Exception.hpp
	$(CC) -c Exception.cpp


run:
	./calc.out "$(var)"

test:
	python3 test.py

clean:
	rm -rf *.o calc.out