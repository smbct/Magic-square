/**
 * \file CtAllDiff.hpp
 * \brief définition de la classe d'une contrainte "All different" du solver complet
 * \author S.B
 * \date 23/09/2016
 */

#ifndef CT_ALL_DIFF_COMPLET_HPP
#define CT_ALL_DIFF_COMPLET_HPP

#include "Contrainte.hpp"
#include <vector>

namespace complet {

/**
 * \class CtAllDiff
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
         * \brief filtrage de la contrainte -> met à jour le domaine des variables
         * \param aFiltrer les contraintes qui seront à filtrer après le filtrage de celle-ci
         * \param associees la liste des contraintes associées à chaque variable du problème
         * \return vrai ssi un domaine de variable est désormais vide
         */
        bool filtrer(std::list<Contrainte*>& aFiltrer, std::map<Variable*, std::list<Contrainte*>>& associees);


};

}

#endif // CT_ALL_DIFF_COMPLET_HPP
