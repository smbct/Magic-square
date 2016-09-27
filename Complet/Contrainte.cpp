/**
 * \file Contrainte.cpp
 * \brief implémentation de la classe Contrainte du solver complet
 * \author S.B
 * \date 22/09/2016
 */

#include "Contrainte.hpp"

using namespace complet;

/*----------------------------------------------------------------------------*/
Contrainte::Contrainte() {

}

/*----------------------------------------------------------------------------*/
void Contrainte::ajouterVariable(Variable* variable) {
    _var.push_back(variable);
}

/*----------------------------------------------------------------------------*/
int Contrainte::nbVariableFixe() {

    int somme = 0;

    for(Variable* var : _var) {
        if(var->estAffectee()) {
            somme ++;
        }
    }

    return somme;
}

/*----------------------------------------------------------------------------*/
Contrainte::~Contrainte() {

}
