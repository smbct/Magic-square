/**
 * \file CtAllDiff.hpp
 * \brief déclaration de la classe pour la contrainte all different du solver incomplet
 * \author S.B
 * \date 27/09/2016
 */

#ifndef CT_ALL_DIFF_INCOMPLET
#define CT_ALL_DIFF_INCOMPLET

#include "Contrainte.hpp"

namespace incomplet {

class CtAllDiff : public Contrainte {

    public:

        /**
         * \brief constructeur par défaut
         */
        CtAllDiff();

        /**
         * \brief calcule le score de la configuration
         * \param configuration la configuration testée
         */
        int score(Configuration& configuration);

    private:

};


#endif // CT_ALL_DIFF_INCOMPLET
