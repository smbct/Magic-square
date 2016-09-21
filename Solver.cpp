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
    for(int ind = 0; ind < n*n; ind++) {
        Variable* variable

    }

}


/*----------------------------------------------------------------------------*/
Solver::resoudre() {


}


Solver::~Solver() {


}
