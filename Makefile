all: main.exe test1
CC=g++
CFLAGS=-O2 -Wall -std=c++11

%.o: src/%.cpp inc/%.h
	$(CC) $(CFLAGS) -c $< -o $@

main.exe: main.cpp function.o
	$(CC) $(CFLAGS) $< -o $@ function.o
test: main.exe
	@./main.exe data/testfile.csv 5000000 

test1: main.exe
		@cat>01.out<<"eof"
	@./main.exe data/01.csv 15000000  

clean:
	rm *.exe *.o src/*.o