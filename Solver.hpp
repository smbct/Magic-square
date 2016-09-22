/**
 * \file Solver.hpp
 * \brief définition d'une classe Solver
 * \author S.B
 * \date 21/09/2016
 */

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Variable.hpp"

/**
 * \class Solver
 * \brief représente le solver du problème magic square
 */
class Solver {

    public:

        /**
         * \brief constructeur
         */
        Solver(int n);

        /**
         * \brief résolution du problème
         */
        void resoudre();

        ~Solver();

    private:
        int _n;
        int _M;

        std::list<Variable*> _variables;

};

#endif
