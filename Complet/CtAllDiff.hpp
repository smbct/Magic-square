/**
 * \file CtAlldiff.hpp
 * \brief définition de la classe d'une contrainte "All different" du solver complet
 * \author S.B
 * \date 23/09/2016
 */

#ifndef CT_ALL_DIFF_COMPLET_HPP
#define CT_ALL_DIFF_COMPLET_HPP

#include "Contrainte.hpp"

namespace complet {

/**
 * \class CtAlldiff
 * \brief représente une contrainte All Different du solver complet
 */
class CtAllDiff : public Contrainte {

    public:

        /**
         * \brief contructeur par défaut
         */
        CtAllDiff();

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


};

}

#endif // CT_ALL_DIFF_COMPLET_HPP
