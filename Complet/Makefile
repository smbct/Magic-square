EXEC=magic-square

CC=g++ -pg
CXX=g++
LDLIBS=
CPPFLAGS=

OPTIONS= -std=c++11 -W -Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter -pg

LDFLAGS=$(OPTIIONS)

.PHONY = clean

OBJECTS_FILES = main.o Variable.o Solver.o Contrainte.o CtSomme.o CtAllDiff.o CtInf.o

gcc : CXXFLAGS= $(OPTIONS) -O3 -Ofast
gcc : main

gcc-debug : CXXFLAGS=$(OPTIONS) -g
gcc-debug : main

run :
	./main

debug : gcc-debug
release : gcc

main : $(OBJECTS_FILES)

clean :
	find . -name "*.o" -type f -delete
