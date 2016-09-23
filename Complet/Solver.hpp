/**
 * \file Solver.hpp
 * \brief définition d'une classe Solver
 * \author S.B
 * \date 21/09/2016
 */

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>

#include "Variable.hpp"
#include "Contrainte.hpp"

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

        /**
         * \brief destructeur, libération de la mémoire
         */
        ~Solver();

    private: // méthodes privées

        /**
         * \brief construction de l'instance du problème
         */
        void construireInstance();

        /**
         * \brief filtrage et propagation
         */
        void filtrerPropager();

        /**
         * \brief retour sur trace dans l'exploration de l'arbre
         * \param testees les variables actuellement affectées
         * \param aTester les variables pas encore affectées
         */
        void backtrack(std::stack<Variable*>& affectees, std::list<Variable*>& aAffecter);

        /**
         * \brief teste si l'affectation des variables est une solution au CSP
         * \return vrai ssi les valeurs des variables permettent de vérifier chaque contrainte
         * \pre toutes les valeurs des variables ont été affectées
         */
        bool estSolution();

        /**
         * \brief teste si la branche de résolution est contradictoire
         */
        bool contradiction();

    private:
        int _n;
        int _M;

        std::list<Variable*> _variables;
        std::vector<Contrainte*> _contraintes;


};

#endif // SOLVER_HPP
