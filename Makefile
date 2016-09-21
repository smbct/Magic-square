EXEC=mafic-square

CC=g++
CXX=g++ -std=c++11
LDLIBS=
CPPFLAGS=-I include

OPTIONS= -std=c++11 -W -Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter

.PHONY = clean

OBJECTS_FILES = main.o Variable.o Solver.o

gcc : CXXFLAGS= $(OPTIONS) -O3
gcc : main

gcc-debug : CXXFLAGS=$(OPTIONS) -ggdb
gcc-debug : main

run :
	./main

debug : gcc-debug
release : gcc

main : $(OBJECTS_FILES)

clean :
	find . -name "*.o" -type f -delete
