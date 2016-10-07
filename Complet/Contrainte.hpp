/**
 * \file Contrainte.hpp
 * \brief définition de classe Contrainte pour le solver complet
 * \author S.B
 * \date 22/02/2016
 */

#ifndef CONTRAINTE_COMPLET_HPP
#define CONTRAINTE_COMPLET_HPP

#include <list>

#include "Variable.hpp"

namespace complet {

/**
 * \class Contrainte
 * \brief classe représentant une contrainte du solver complet
 */
class Contrainte {

    public:

        /**
         * \brief contructeur par défaut
         */
        Contrainte();

        /**
         * \brief evaluation de la contrainte
         * \pre toutes les variables ont été affectées
         * \return vrai ssi la contrainte est vérifiée
         */
        virtual bool evaluer() = 0;

        /**
         * \brief filtrage de la contrainte -> met à jour le domaine des variables
         * \param aFiltrer les contraintes qui seront à filtrer après le filtrage de celle-ci
         * \param associees la liste des contraintes associées à chaque variable du problème
         * \return vrai ssi un changement a été effectué sur le domaine des variables
         */
        virtual bool filtrer(std::list<Contrainte*>& aFiltrer, std::map<Variable*, std::list<Contrainte*>>& associees) = 0;

        /**
         * \brief ajout d'une variable à la contrainte
         * \param var la variable à ajouter
         */
        void ajouterVariable(Variable* var);

        /**
         * \brief indique le nombre de variable fixé dans la contrainte
         */
        int nbVariableFixe();

        /**
         * \brief destructeur par défaut
         */
        virtual ~Contrainte();

    protected:
        std::list<Variable*> _var;

};

}

#endif // CONTRAINTE_COMPLET_HPP
