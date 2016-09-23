/**
 * \file Solver.cpp
 * \brief implémentation de la classe Solver
 * \author S.B
 * \date 21/09/2016
 */

 #include "Solver.hpp"

/*----------------------------------------------------------------------------*/
Solver::Solver(int n) :
_n(n),
_M( (n*(n*n+1))/2 )
{

    // création des contraintes
    _contraintes.resize(2*_n+3);
    

    // création des n*n variables
    for(int y = 0; y < n; y++) {
        for(int x = 0; x < n; x++) {
            Variable* variable = new Variable(1, n*n);

        }

    }

}


/*----------------------------------------------------------------------------*/
void Solver::resoudre() {


}

/*----------------------------------------------------------------------------*/
Solver::~Solver() {


}
