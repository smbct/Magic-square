/**
 * \file CtSomme.hpp
 * \brief déclaration de la classe pour la contrainte somme du solver incomplet
 * \author S.B
 * \date 27/09/2016
 */

#ifndef CT_SOMME_INCOMPLET_PREMIER_HPP
#define CT_SOMME_INCOMPLET_PREMIER_HPP

#include "Contrainte.hpp"

namespace incomplet_premier {

class CtSomme : public Contrainte {

    public:

        /**
         * \brief constructeur
         * \param M membre de droite de la contrainte
         */
        CtSomme(int M);

        /**
         * \brief calcule le score de la configuration
         * \param configuration la configuration testée
         */
        int score(Configuration& configuration);

    private:

        int _M;

};

}

#endif // CT_SOMME_INCOMPLET_PREMIER_HPP
