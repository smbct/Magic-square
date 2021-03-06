/**
 * \file Variable.hpp
 * \brief définition de la classe Variable
 * \author S.B
 * \date 21/09/2016
 */

#ifndef VARIABLE_COMPLET_HPP
#define VARIABLE_COMPLET_HPP

#include <list>
#include <string>
#include <stack>
#include <map>
#include <vector>

namespace complet {

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
         * \param val la valeur à enlever
         * \return vrai ssi le domaine a été modifié
         */
        bool enleveVal(int val);

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
         * \brief affectation de la variable à une valeur non encore affectée, suivant l'ordre
         * \return faux ssi la dernière affectation a été faite
         */
        bool affecterOrdre();

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

        /**
         * \brief donne le nombre de valeurs du domaine
         * \return le nombre de valeur du domaine
         */
        int tailleDomaine();

        /**
         * \brief retourne l'indice dans le domaine de la valeur affectée à la variable
         * \return l'indice dans le domaine de la valeur affectée à la variable
         * \pre la variable a été affectée
         */
        int indAffecte();

        /**
         * \brief indique si les domaines des deux variables sont identiques
         * \param autre la variable à comparer
         */
        bool memeDomaine(Variable& autre);

        /**
         * \brief retourne une copie du domaine dans la liste copie
         * \param copie la liste contenant les valeurs du domaine
         */
        void copieDomaine(std::list<int>& copie);

        /**
         * \brief retourne la valeur minimale du domaine de la variable
         * \return la valeur maximale
         */
        int minDomaine();

        /**
         * \brief retourne la valeur maximale du domaine de la variable
         * \return la valeur maximale
         */
        int maxDomaine();

    private:
        bool _affectee;
        std::list<int> _domaine;
        std::stack<std::list<int> > _filtrees;
        std::list<int>::iterator _valIt; // itérateur vers la valeur en cours d'affectation
        unsigned int _indDom; // indice de l'élément du domaine actuellement affecté

        std::vector<int> _ordre;

        int _min; // conservation des valeurs minimales et maximales du domaine
        int _max;
};

}

#endif // VARIABLE_COMPLET_HPP
