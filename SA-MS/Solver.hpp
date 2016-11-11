 /**
 * \file Solver.hpp
 * \brief definition of a Solver class
 */

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Grid.hpp"

/**
 * \class Solver
 * \brief represent a solver that solve the magic square problem with simulated anealing
 */
class Solver {

    public:
        Solver(int size);

        /**
         * \solve the problem for the specified grid
         */
        void solve();

        /**
         * \brief perform a local search on a grid
         * \param grid the grid to work with
         */
        void localSearch(Grid& grid);

        /**
         * \brief perform a tabu search on the grid
         * \param grid the grid
         */
        void tabuSearch(Grid& grid);

    private:
        const int _size;


};

#endif /* SOLVER_HPP */
