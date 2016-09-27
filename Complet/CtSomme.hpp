/**
 * \file CtSomme.hpp
 * \brief définition de la classe d'une contrainte "somme" du solver complet
 * \author S.B
 * \date 23/09/2016
 */

#ifndef CT_SOMME_COMPLET_HPP
#define CT_SOMME_COMPLET_HPP

#include "Contrainte.hpp"

namespace complet {

/**
 * \class CtSomme
 * \brief représente une contrainte somme du carré magique (ligne, col ou diag) pour le solver complet
 */
class CtSomme : public Contrainte {

    public:

        /**
         * \brief constructeur par défaut
         */
        CtSomme(int M);

        /**
         * \brief évaluation de la contrainte
         * \pre toutes les variables doivent être affectées
         * \return vrai ssi la contrainte est respectée
         */
        bool evaluer();

        /**
         * \brief filtrage de la contrainte
         * \return vrai ssi des valeurs de variables ont été filtrées
         */
        bool filtrer();

    private: // méthodes privées

        /**
         * \brief tentative de satisfaction de la contrainte à partir d'une affectation
         * \param aTester les variables à tester
         * \param listeTest : la valeur fixée à tester
         * \param dte : le membre de droite de la contrainte de somme
         * \return vrai ssi il existe une affectation satisfaisant la contrainte
         */
        bool satisfaire(std::list<Variable*>& listeTest, int val, int dte);


    private: // attributs privés

        int _M; // membre de droite de la somme

};

}

#endif // CT_SOMME_COMPLET_HPP
