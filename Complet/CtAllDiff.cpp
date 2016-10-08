/**
 * \file CtAlldiff.cpp
 * \brief implémentation de la contrainte "All different" du solver complet
 * \author S.B
 * \date 23/09/2016
 */

#include "CtAllDiff.hpp"

#include <iostream>
#include <algorithm>

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
bool CtAllDiff::filtrer(list<Contrainte*>& aFiltrer, std::map<Variable*, list<Contrainte*>>& associees) {

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

    vector<bool> modifiee(libre.size(), false);

    for(Variable* var : affect) {

        int indVar = 0;
        // la valeur de cette variable ne peut être proposées aux variables libres
        for(Variable* varLibre : libre) {

            if(varLibre->enleveVal(var->valeur()) > 0) {
                // un changement a eu lieu
                modifiee[indVar] = true;
            }
            indVar ++;
        }

    }

    // mise à jour des contraintes à filtrer
    int indVar = 0;
    for(Variable* varLibre : libre) { // revue de chaque variable qui a pu être modifiée
        if(modifiee[indVar]) { // s'il y a eu une modification, des nouvelles contraintes sont peut être à filtrer
            list<Contrainte*>& cont = associees[varLibre];
            for(Contrainte* contrainte : cont) {
                if(find(aFiltrer.begin(), aFiltrer.end(), contrainte) == aFiltrer.end()) {
                    // si la contrainte n'est pas dans la liste de filtre, elle est ajoutée
                    aFiltrer.push_back(contrainte);
                }
            }
        }

        // si le domaine est vide, l'information est trasférée
        if(varLibre->impossible()) {
            res = true;
        }

        indVar ++;
    }

    return res;
}
