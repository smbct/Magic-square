#include <iostream>

#include "Solver.hpp"

using namespace std;

using namespace incomplet;

#include <ctime>

int main() {

    srand(time(0));

    Solver solver(20);

    clock_t begin = clock();
    solver.resoudre();
    clock_t end = clock();
    double elapsed_secs = double(end-begin)/ CLOCKS_PER_SEC;

    cout << "temps écoulé : " << elapsed_secs << endl;

    return 0;
}
