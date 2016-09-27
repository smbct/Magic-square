/**
 * \file Contrainte.hpp
 * \brief déclaration de la classe Contrainte du solver incomplet
 * \author S.B
 * \date 27/09/2016
 */

#ifndef CONTRAINTE_INCOMPLET_HPP
#define CONTRAINTE_INCOMPLET_HPP

#include "Configuration.hpp"

namespace incomplet {

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
         * \brief calcule le score avec les valeurs d'une configuration'
         * \param configuration la configuration à tester
         */
        virtual int score(Configuration& configuration) = 0;

    protected:

};

}

#endif // CONTRAINTE_INCOMPLET_HPP
