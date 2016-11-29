CXX= g++
CXXFLAGS= -std=c++11 -W -Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter -O3 -Ofast

.PHONY = clean

run:
	./solver

plot:
	gnuplot script.plot -p

solver: main.o Grille.o Solver.o
	$(CXX) $(CXXFLAGS) main.o Grille.o Solver.o -o solver

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -c

Grille.o: Grille.cpp Grille.hpp
	$(CXX) $(CXXFLAGS) Grille.cpp -c

Solver.o: Solver.cpp
	$(CXX) $(CXXFLAGS) Solver.cpp -c

clean:
	rm *.o solver
