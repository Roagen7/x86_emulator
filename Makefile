CXXFLAGS=-g -Wall -pedantic

MAIN=src/main/main.cpp
SRC_LIST= src/main/Cpu.cpp
TEST_LIST=src/test/status.cpp src/test/register.cpp

all:
	mkdir _build
	g++ ${CXXFLAGS} ${MAIN} ${SRC_LIST} -o _build/main

test:
	mkdir _build
	mkdir _build/test
	g++ -Wall -g -pthread ${TEST_LIST} ${SRC_LIST} -lgtest_main  -lgtest -lpthread  -o _build/test/test
clean:
	rm -R _build