/**
 * \file Contrainte.cpp
 * \brief implémentation de la classe Contrainte
 * \author S.B
 * \date 22/09/2016
 */

#include "Contrainte.hpp"

/*----------------------------------------------------------------------------*/
Contrainte::Contrainte() {


}

/*----------------------------------------------------------------------------*/
void Contrainte::ajouterVariable(Variable* variable) {
    _var.push_back(variable);
}

/*----------------------------------------------------------------------------*/
Contrainte::~Contrainte() {

}
