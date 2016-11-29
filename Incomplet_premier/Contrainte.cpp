/**
 * \file Contrainte.cpp
 * \brief implémentation de la classe Contrainte du solver incomplet
 * \author S.B
 * \date 27/09/2016
 */

#include "Contrainte.hpp"

using namespace incomplet_premier;

/*----------------------------------------------------------------------------*/
Contrainte::Contrainte() {

}

/*----------------------------------------------------------------------------*/
void Contrainte::ajouterVariable(int indice) {
    _indices.push_back(indice);
}


/*----------------------------------------------------------------------------*/
Contrainte::~Contrainte() {

}
