#include <iostream>

#include "Variable.hpp"
#include "CtAllDiff.hpp"
#include "CtSomme.hpp"
#include "Solver.hpp"

#include <vector>

#include <ctime>

using namespace std;

int main() {

    int size = 3;

    /*cout << "entrer la taille de la grille : ";
    cin >> size;*/

    // cout << "La grille est de taille " << size << " * " << size << endl;

    complet::Solver solver(4);

    clock_t begin = clock();
    solver.resoudre();
    clock_t end = clock();
    double elapsed_secs = double(end-begin)/ CLOCKS_PER_SEC;

    cout << "temps écoulé : " << elapsed_secs << endl;

    return 0;
}
