/**
 * \file Variable.hpp
 * \brief définition de la classe Variable
 * \author S.B
 * \date 21/09/2016
 */

#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <list>
#include <string>
#include <stack>

/**
 * \class Variable
 * \brief Représente une variable du problème CSP
 */
class Variable {

    public:

        /**
         * \brief constructeur, spécification du domaine sous forme d'interval
         * \param min la valaeur minimale du domaine
         * \param max la valeur maximale du domaine
         */
        Variable(int min, int max);

        /**
         * \brief retourne l'ensemble des valeurs du domaine sous forme de chaîne
         */
        std::string toString();

        /**
         * \brief enleve un ensemble de valeur du domaine
         * \param val l'ensemble des valeurs à enlever
         */
        void enleveVal(int val);

        /**
         * \brief sauvegarde de l'état actuel du domaine
         */
        void sauvegardeDomaine();

        /**
         * \brief restoration du dernier filtrage
         */
        void restoreDomaine();

    private:
        bool _affectation;
        int _val;
        std::list<int> _domaine;
        std::stack<std::list<int> > _filtrees;
};

#endif
