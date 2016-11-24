/**
 * \file CtInf.hpp
 * \brief définition de la classe CtInf implémentant une contrainte d'infériorité' entre deux variables
 * \author S.B
 * \date 24/11/2016
 */

#ifndef CT_INF_HPP
#define CT_INF_HPP

#include "Contrainte.hpp"

namespace complet {

/**
 * \class CtInf
 * \brief définition d'un classe représentant une contrainte d'infériorité'
 */
class CtInf : public Contrainte {


    public:

        /**
         * \brief constructeur par défaut, la contrainte est : varGch < varDte
         * \param varGch la variable de gauche
         * \param varDte la variable de droite
         */
        CtInf(Variable* varGch, Variable* varDte);

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


    private: // attributs privés

        Variable* _varGch;
        Variable* _varDte;

};

}

#endif // CT_SUP_HPP
