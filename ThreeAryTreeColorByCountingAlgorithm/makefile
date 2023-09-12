CC = clang++
CFLAGs = -std=c++20

main: main.o
	$(CC) $(CFLAGs) main.o -o main
	@echo Compiling Done ✅

main.o: main.cpp
	@echo Compiling Code 🎲
	$(CC) $(CFLAGs) -Wall -c main.cpp

clean:
	@echo cleaning 🗑️
	rm -rf main main.o
	@echo Done ✅
