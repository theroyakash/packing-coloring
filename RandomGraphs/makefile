CC = clang++
CFLAGs = -std=c++20

main: main.o
	$(CC) $(CFLAGs) main.o -o main
	@echo Compiling Done ✅

main.o: main.cpp
	@echo Compiling Code 🎲
	$(CC) $(CFLAGs) -Wall -c main.cpp

test: test_main.o
	$(CC) $(CFLAGs) test_main.o -o test
	./test
	@echo Tests are Done ✅

test_main.o: test_main.cpp
	@echo Starting Test 🧪
	$(CC) $(CFLAGs) -Wall -c test_main.cpp

clean:
	@echo cleaning 🗑️
	rm -rf main main.o test test_main.o
	@echo Done ✅
