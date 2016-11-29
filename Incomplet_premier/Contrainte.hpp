/**
 * \file Contrainte.hpp
 * \brief déclaration de la classe Contrainte du solver incomplet
 * \author S.B
 * \date 27/09/2016
 */

#ifndef CONTRAINTE_INCOMPLET_PREMIER_HPP
#define CONTRAINTE_INCOMPLET_PREMIER_HPP

#include "Configuration.hpp"

namespace incomplet_premier {

/**
 * \class Contrainte
 * \brief classe représentant une contrainte du solver incomplet
 */
class Contrainte {

    public:

        /**
         * \brief constructeur par défaut
         */
        Contrainte();

        /**
         * \brief ajout d'une variable dans la contrainte
         * \param indice l'indice de la variable à ajouter
         */
        void ajouterVariable(int indice);

        /**
         * \brief calcule le score avec les valeurs d'une configuration'
         * \param configuration la configuration à tester
         */
        virtual int score(Configuration& configuration) = 0;

        /**
         * \brief destructeur
         */
        virtual ~Contrainte();

    protected:
        std::list<int> _indices; // indices des variables concernées dans une configuration

};

}

#endif // CONTRAINTE_INCOMPLET_PREMIER_HPP
