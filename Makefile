all: main.exe test1
CC=g++
CFLAGS=-O2 -Wall -std=c++11

%.o: src/%.cpp inc/%.h
	$(CC) $(CFLAGS) -c $< -o $@

main.exe: main.cpp src/function.o
	$(CC) $(CFLAGS) $< -o $@ src/function.o 
test:
	@./main.exe data/testfile.csv 27 7

test1:
	@./main.exe data/01.csv 27 7 0.8 586 1500000
clean:
	rm *.exe *.o src/*.o
