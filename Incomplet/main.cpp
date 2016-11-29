#include <iostream>
#include <ctime>

#include "Solver.hpp"

using namespace std;
using namespace incomplet;

/*----------------------------------------------------------------------------*/
int main() {

    srand(time(nullptr));

    Solver solver(20);

    solver.solverRecuit();

    return 0;
}
