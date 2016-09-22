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
    // création des n*n variables
    for(int ind = 0; ind < n; ind++) {
        for(int ind2 = 0; ind2 < n; ind2++) {
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
