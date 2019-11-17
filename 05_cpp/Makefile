CC=g++

all: do

do: main.o 
	$(CC) -o do.out main.o 

main.o: main.cpp base.hpp CheckFunction.hpp Deserializer.hpp Serializer.hpp
	$(CC) -std=c++17 -c main.cpp

test:
	./do.out

clean:
	rm -rf *.o do.out