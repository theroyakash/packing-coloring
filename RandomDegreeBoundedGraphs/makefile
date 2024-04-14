CC = clang++
CFLAGs = -std=c++20 -O2 -Wall -Wextra -Werror -Wpedantic -Wshadow -Wno-unused-variable -Wno-unused-parameter -Wno-unused-private-field

BUILD_DIR = ./build

run: main.o
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGs) $(BUILD_DIR)/main.o -o $(BUILD_DIR)/main
	@echo Compiling Done ✅
	./$(BUILD_DIR)/main
	@echo Cleaning Artefacts 🗑️
	rm -rf $(BUILD_DIR)
	@echo Done ✅

rerun:
	./$(BUILD_DIR)/main

make: main.o
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGs) $(BUILD_DIR)/main.o -o $(BUILD_DIR)/main
	@echo Compiling Done ✅

main.o: main.cpp
	@echo Compiling Code 🎲
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGs) -Wall -c main.cpp -o $(BUILD_DIR)/main.o

test: test_main.o
	$(CC) $(CFLAGs) $(BUILD_DIR)/test_main.o -o $(BUILD_DIR)/test
	./$(BUILD_DIR)/test
	@echo Tests are Done ✅
	@echo Cleaning Tests 🗑
	rm -rf $(BUILD_DIR)/test $(BUILD_DIR)/test_main.o
	@echo Done ✅

test_main.o: test_main.cpp
	@echo Starting Test 🧪
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGs) -Wall -c test_main.cpp -o $(BUILD_DIR)/test_main.o

clean:
	@echo cleaning 🗑️
	rm -rf main main.o test test_main.o
	@echo Done ✅

input: generate_input.cpp
	@echo generating input file for run 🧬
	$(CC) $(CFLAGs) -o input generate_input.cpp
	./input
	@echo removing executables
	rm -rf input
	@echo Done ✅
