/**
 * \file Solver.hpp
 * \brief définition d'une classe Solver
 * \author S.B
 * \date 21/09/2016
 */

#ifndef SOLVER_COMPLET_HPP
#define SOLVER_COMPLET_HPP

#include <vector>
#include <map>
#include <queue>

#include "Variable.hpp"
#include "Contrainte.hpp"

namespace complet {

/**
 * \class Solver
 * \brief représente le solver du problème de magic square
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

        /**
         * \brief met à jour la file d'attente des contraintes à filtrer
         * \param variable la variables qui a été modifiée (soit fixée, soit filtrée)
         */
        void majFileFiltre(Variable* variable);

    private:
        int _n;
        int _M;

        std::list<Variable*> _variables;
        std::vector<Contrainte*> _contraintes;

        std::map<Variable*, std::list<Contrainte*> > _associees; // pour chaque variable, les contraintes dans lesquelles elle apparaît

        std::list<Contrainte*> _aFiltrer; // liste des contraintes à filtrer, mise à jour après l'exploration


};

}

#endif // SOLVER_COMPLET_HPP
