#include <iostream>
#include <ctime>

#include "Solver.hpp"

using namespace std;

/*----------------------------------------------------------------------------*/
int main() {

    srand(time(nullptr));

    Solver solver(25);

    solver.solve();

    return 0;
}
