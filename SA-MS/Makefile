CXX= g++
CXXFLAGS= -std=c++11 -W -Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter -O3

.PHONY = clean

run:
	./solver

plot:
	gnuplot script.plot -p

solver: main.o Grid.o Solver.o
	$(CXX) $(CXXFLAGS) main.o Grid.o Solver.o -o solver

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -c

Grid.o: Grid.cpp Grid.hpp
	$(CXX) $(CXXFLAGS) Grid.cpp -c

Solver.o: Solver.cpp
	$(CXX) $(CXXFLAGS) Solver.cpp -c

clean:
	rm *.o solver
