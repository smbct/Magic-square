 /**
 * \file Solver.hpp
 * \brief définition d'une classe Solver
 */

#ifndef SOLVER_INCOMPLET_HPP
#define SOLVER_INCOMPLET_HPP

#include "Grille.hpp"

namespace incomplet {

/**
 * \class Solver
 * \brief représente un solver du problème de Carré Magique
 */
class Solver {

    public:
        Solver(int taille);

        /**
         * \brief résolution du problème pour une grille donnée
         */
        void solve();

        /**
         * \brief résolution d'une grille basée sur la métaheuristique du recuit simulé
         */
        void solverRecuit();

        /**
         * \brief exécute une recherche locale d'une configuration donnée
         * \param grille la grille sur laquelle faire la recherche
         */
        void rechercheLocale(Grille& grille);

        /**
         * \brief exécute une recherche tabou sur une grille
         * \param grille la grille sur laquelle faire la recherche
         */
        void rechercheTabou(Grille& grille);

    private:
        const int _taille;


};

}

#endif /* SOLVER_HPP */
