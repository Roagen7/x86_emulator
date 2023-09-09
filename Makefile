CXXFLAGS=-g -std=c++20 -Wall -pedantic

all:
	mkdir _build
	gcc -lstdc++ -g main.cpp src/Cpu.cpp -o _build/main

clean:
	rm -R _build