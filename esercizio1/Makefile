CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/*.h Makefile

all: bin/ordered_array bin/ordered_array_tests

tests: bin/ordered_array_tests

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/ordered_array: build/ordered_array.o build/ordered_array_main.o build/mergesort.o build/binaryinserionsort.o build/mergebinaryinsertionsort.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_array build/ordered_array.o build/ordered_array_main.o build/mergesort.o build/binaryinserionsort.o build/mergebinaryinsertionsort.o

bin/ordered_array_tests: build/ordered_array_tests.o build/ordered_array.o build/unity.o build/binaryinserionsort.o build/mergebinaryinsertionsort.o build/mergesort.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_array_tests build/ordered_array_tests.o build/ordered_array.o build/unity.o build/binaryinserionsort.o build/mergebinaryinsertionsort.o build/mergesort.o

clean:
	$(RM) build/*
	$(RM) bin/*
