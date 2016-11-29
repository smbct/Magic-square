
.PHONY: clean
CC= g++
CFLAGS= -std=c++11 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra -O3 -Ofast

OBJECTS_FILES= Complet/Contrainte.o Complet/CtAllDiff.o Complet/CtInf.o Complet/CtSomme.o Complet/Solver.o Complet/Variable.o Incomplet/Grille.o Incomplet/Solver.o main.o

solver: $(OBJECTS_FILES)
	$(CC) $(CFLAGS) $(OBJECTS_FILES) -o solver

# Compilation des fichiers object
%.o: %.cpp %.h
	$(CC) $(CFLAGS) $< -c -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	@rm -rf Complet/*.o Incomplet/*.o solver
