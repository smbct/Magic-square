/**
 * \file CtAlldiff.cpp
 * \brief implémentation de la contrainte "All different" du solver complet
 * \author S.B
 * \date 23/09/2016
 */

#include "CtAllDiff.hpp"

#include <iostream>

using namespace std;

using namespace complet;

/*----------------------------------------------------------------------------*/
CtAllDiff::CtAllDiff() :
Contrainte()
{

}

/*----------------------------------------------------------------------------*/
bool CtAllDiff::evaluer() {

    bool res = true;

    auto it = _var.begin();

    while(res && it != _var.end()) {

        // aucune autre variable ne doit avoir la même valeur
        auto it2 = _var.begin();
        bool contr = false;

        while(!contr && it2 != _var.end()) {

            // si deux variables ont la même valeur, le test échoue
            if(it != it2 && (*it)->valeur() == (*it2)->valeur()) {
                contr = true;
            } else {
                it2 ++;
            }
        }

        if(contr) {
            res = false;
        } else {
            it ++;
        }
    }

    return res;
}

/*----------------------------------------------------------------------------*/
bool CtAllDiff::filtrer() {

    // auncun changement pour l'instant
    bool res = false;

    list<Variable*> affect, libre;

    // construction de listes utiles
    for(Variable* var : _var) {
        if(var->estAffectee()) {
            affect.push_back(var);
        } else {
            libre.push_back(var);
        }
    }

    for(Variable* var : affect) {
        // la valeur de cette variable ne peut être proposées aux variables libres
        for(Variable* varLibre : libre) {

            if(varLibre->enleveVal(var->valeur()) > 0) {
                // un changement a eu lieu
                res = true;
            }
        }

    }

    return res;
}
