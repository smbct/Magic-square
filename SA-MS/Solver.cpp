/**
 * \file Solver.cpp
 * \brief implementation of the Solver class
 */

#include "Solver.hpp"

#include <iostream>
#include <cmath>

#include <fstream>

using namespace std;

/*----------------------------------------------------------------------------*/
Solver::Solver(int size) :
_size(size)
{


}

/*----------------------------------------------------------------------------*/
void Solver::solve() {

    Grid grid(_size);

    double T0 = 100; /* initial temperature */
    double T = T0; /* the current temperature */
    int L = 50; /* number of iterations for a constant temperature */
    double alpha = 0.84; /* coefficient */

    int nbItMax = 100;

    int it = 1;
    bool stop = false;

    unsigned int scoreMin = grid.score();

    ofstream file("expe.dat");

    while(!stop) {

        int delta = -grid.score();

        grid.randomMove(); /* random neighbour */
        delta += grid.score();

        bool accepted = false;
        if(delta < 0) {
            accepted = true;
        } else {
            double limit = exp(-(double)delta/T);
            double rndChoice = (rand()%100)/100.;

            if(rndChoice < limit) {
                accepted = true;
            }
        }

        if(accepted) {

            file << it << " " << grid.score() << " " << scoreMin << endl;

            if(grid.score() == 0) {
                stop = true;
            }
            if(grid.score() < scoreMin) {
                scoreMin = grid.score();

                // cout << "score : " << scoreMin << endl;

                if(grid.score() <= 10) {
                    // cout << "tabuMode" << endl << endl;
                    tabuSearch(grid);
                    if(grid.score() == 0) {
                        stop = true;
                    }
                }
            }
        } else {
            grid.cancelMove();
        }

        it ++;

        if(it % L == 0) { // update temperature
            T *= alpha;
        }

        if(T < 1e-20) {
            T = T0;
            if(T0 > 1) {
                T0 *= 0.4;
            }
            if(L < 1e12) {
                L *= 1.5;
            }
        }

    }

    file.close();

    cout << "it : " << it << endl;

    cout << "best score found : " << grid.score() << endl;
    cout << grid.toString() << endl;
}

/*----------------------------------------------------------------------------*/
void Solver::localSearch(Grid& grid) {

    /* perform a simple local search */

    bool stop = false;
    int scoreMin = grid.score();

    while(!stop) {

        int eltaMin = -1, eltbMin = -1;
        int neighbourScore = -1;

        for(int i = 0; i < _size*_size; i++) {
            for(int j = i+1; j < _size*_size; j++) {

                grid.move(i, j);

                if(neighbourScore == -1 || grid.score() < neighbourScore) {
                    neighbourScore = grid.score();
                    eltaMin = i;
                    eltbMin = j;
                }

                grid.move(j, i); /* cancel this move */


            }
        }
        if(neighbourScore < scoreMin) {
            scoreMin = neighbourScore;
            grid.move(eltaMin, eltbMin);
        } else {
            stop = true;
        }

    }

}

/*----------------------------------------------------------------------------*/
void Solver::tabuSearch(Grid& grid) {

    const int tabuLength = 7;
    vector<vector<int>> tabuList(_size*_size);
    for(int i = 0; i < _size*_size; i++) {
        tabuList[i].resize(_size*_size, 1);
    }


    bool stop = false;
    int nbIt = 1;

    int bestScore = grid.score();

    while(!stop) {

        int eltaMin, eltbMin;
        unsigned int neighbourScore = -1;

        /* local search : explore all the neighbours */
        for(int i = 0; i < _size*_size; i++) {
            for(int j = i+1; j < _size*_size; j++) {

                /* if this move isn't tabu, we can try it */
                if(tabuList[i][j] <= nbIt || grid.score() < bestScore) {
                    grid.move(i, j);
                    if(neighbourScore == -1 || grid.score() < neighbourScore) {
                        neighbourScore = grid.score();
                        eltaMin = i;
                        eltbMin = j;
                    }
                    grid.move(j, i); /* cancel the move */
                }

            }
        }

        if(neighbourScore != -1) {

            grid.move(eltaMin, eltbMin);
            tabuList[eltaMin][eltbMin] = nbIt + tabuLength;

            if(grid.score() == 0) {
                stop = true;
            }

            if(grid.score() < bestScore) {
                bestScore = grid.score();
            }

            // cout << "tabu score : " << grid.score() << endl;

        } else {
            stop = true;
        }

        nbIt ++;
    }

    cout << "best found : " << grid.score() << endl;

}
