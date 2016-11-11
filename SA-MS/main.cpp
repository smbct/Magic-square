#include <iostream>
#include <ctime>

#include "Solver.hpp"

using namespace std;

/*----------------------------------------------------------------------------*/
int main() {

    srand(time(nullptr));

    Solver solver(20);

    solver.solve();

    return 0;
}
