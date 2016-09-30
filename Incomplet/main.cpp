#include <iostream>

#include "Solver.hpp"

using namespace std;

using namespace incomplet;

#include <ctime>

int main() {

    srand(time(0));

    Solver solver(9);

    solver.resoudre();

    return 0;
}
