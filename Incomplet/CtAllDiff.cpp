/**
 * \file CtAllDiff.cpp
 * \brief déclaration de la classe pour la contrainte all different du solver incomplet
 * \author S.B
 * \date 27/09/2016
 */

#include "CtAllDiff.hpp"

using namespace incomplet;

/*----------------------------------------------------------------------------*/
CtAllDiff::CtAllDiff() {

}

/*----------------------------------------------------------------------------*/
int CtAllDiff::score(Configuration& config) {

    // calcule du score en fonction du nombre de variables égales

    int score = 0;

    for(int ind : _indices) {
        for(int ind2 : _indices) {
            if(ind != ind2 && config(ind) == config(ind2)) {
                score += 2;
            }
        }

    }

    return score;
}
