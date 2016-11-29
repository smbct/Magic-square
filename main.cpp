#include <iostream>
#include <ctime>

#include "Incomplet/Solver.hpp"
#include "Complet/Solver.hpp"

using namespace std;

/*----------------------------------------------------------------------------*/
int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    //incomplet::Solver solver(30);

    //solver.solverRecuit();
    // solver.solve();

    complet::Solver solver(6);

    solver.resoudre();

    return 0;
}
