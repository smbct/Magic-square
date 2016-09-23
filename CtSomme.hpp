/**
 * \file CtSomme.hpp
 * \brief définition de la classe d'une contrainte "somme"
 * \author S.B
 * \date 23/09/2016
 */

#ifndef CT_SOMME_HPP
#define CT_SOMME_HPP

#include "Contrainte.hpp"

/**
 * \class CtSomme
 * \brief représente une contrainte somme du carré magique (ligne, col ou diag)
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

    private:
        int _M; // membre de droite de la somme

};

#endif // CT_SOMME_HPP
