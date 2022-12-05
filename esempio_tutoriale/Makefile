CFLAGS		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS	= src/*.h Makefile

all: bin/ordered_array_main bin/ordered_array_test

test: bin/ordered_array_test
	bin/ordered_array_test

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/ordered_array_main: build/ordered_array.o build/ordered_array_main.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_array_main build/ordered_array.o build/ordered_array_main.o


bin/ordered_array_test: build/ordered_array_test.o build/ordered_array.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/ordered_array_test build/ordered_array_test.o build/ordered_array.o build/unity.o


clean:
	$(RM) build/*
	$(RM) bin/*
