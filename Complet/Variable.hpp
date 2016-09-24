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
#include <map>

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
         * \brief tente d'enlever une valeur du domaine
         * \param val l'ensemble des valeurs à enlever
         * \return 0 si la valeur n'était pas présente, 1 si la valeur était présente et que le domaine n'est pas vide, deux si le domaine est désormais vide
         */
        int enleveVal(int val);

        /**
         * \brief sauvegarde de l'état actuel du domaine
         */
        void sauvegardeDomaine();

        /**
         * \brief restoration du dernier filtrage
         */
        void restoreDomaine();

        /**
         * \brief affectation de la variable à une valeur non encore affectée
         * \pre il existe une affectation possible pour cette variable
         */
        bool affecter();

        /**
         * \brief la variable redevient libre
         */
        void desaffecter();

        /**
         * \brief indique si la variable a été affectée à une valeur ou non
         */
        bool estAffectee();

        /**
         * \brief retourne la valeur affectée à la variable
         * \pre la variable a été affectée
         */
        int valeur();

        /**
         * \brief indique si l'affectation de cette variable n'est pas possible dans cet état (on peut éventuellement "backtracker")
         * \return vrai ssi la variable ne peut pas être affectée
         */
        bool impossible();

    private:
        bool _affectee;
        std::list<int> _domaine;
        std::stack<std::list<int> > _filtrees;
        std::list<int>::iterator _valIt; // itérateur vers la valeur en cours d'affectation
};

#endif
