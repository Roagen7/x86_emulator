CXXFLAGS=-g -Wall -pedantic -pthread

MAIN=src/main/main.cpp
SRC_LIST= src/main/Cpu.cpp
TEST_LIST=src/test/status.cpp src/test/register.cpp

GTEST_LIBS=-lgtest_main  -lgtest -lpthread 
LIBS=-lpthread

BUILD_DIR=_build/
TEST_SUBDIR=test/

all:
	mkdir ${BUILD_DIR}
	g++ ${CXXFLAGS} ${MAIN} ${SRC_LIST} ${LIBS} -o ${BUILD_DIR}main

test:
	mkdir ${BUILD_DIR}
	mkdir ${BUILD_DIR}${TEST_SUBDIR}
	g++ ${CXXFLAGS} ${TEST_LIST} ${SRC_LIST} ${LIBS} ${GTEST_LIBS} -o ${BUILD_DIR}${TEST_SUBDIR}test
clean:
	rm -R ${BUILD_DIR}