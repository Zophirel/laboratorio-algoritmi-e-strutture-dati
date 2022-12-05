CFLAGS 			= -g -O1 -Wall -Wextra -Wpedantic 
COMMON_DEPS 	= src/*.h Makefile

all: bin/edit_distance bin/edit_distance_test

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/edit_distance: build/edit_distance.o build/edit_distance_main.o build/collect_element.o build/edit_distance_definitive.o build/matrix.o build/edit_distance.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance build/edit_distance_main.o build/collect_element.o build/edit_distance_definitive.o build/matrix.o build/edit_distance.o

bin/edit_distance_test: build/edit_distance.o build/collect_element.o build/edit_distance_definitive.o build/matrix.o build/edit_distance.o build/unity.o build/edit_distance_test.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_test build/collect_element.o build/edit_distance_definitive.o build/matrix.o build/edit_distance.o build/unity.o build/edit_distance_test.o
clean:
	$(RM) build/*
	$(RM) bin/*