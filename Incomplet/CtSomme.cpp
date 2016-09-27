/**
 * \file CtSomme.cpp
 * \brief implementation de la classe pour la contrainte somme du solver incomplet
 * \author S.B
 * \date 27/09/2016
 */

#include "CtSomme.hpp"

using namespace incomplet;

/*----------------------------------------------------------------------------*/
CtSomme::CtSomme(int M) :
_M(M)
{

}

/*----------------------------------------------------------------------------*/
int CtSomme::score(Configuration& configuration) {

    int score = 0;
    int somme = 0;

    for(int ind : _indices) {
        somme += configuration(ind);
    }

    score = _M-somme;
    score *= score;

    return score;
}
