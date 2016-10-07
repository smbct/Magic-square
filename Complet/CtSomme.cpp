/**
 * \file CtSomme.cpp
 * \brief implémentation de la classe CtSomme du solver complet
 * \author S.B
 * \date 23/09/2016
 */

#include "CtSomme.hpp"
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

using namespace complet;

/*----------------------------------------------------------------------------*/
CtSomme::CtSomme(int M) :
Contrainte(), _M(M)
{

}

/*----------------------------------------------------------------------------*/
bool CtSomme::evaluer() {

    bool res = false;

    // accumulateur des sommes
    int somme = 0;

    // calcul de la somme des valeurs des variables
    for(Variable* var : _var) {
        somme += var->valeur();
    }

    // varification du respect de la contrainte
    if(somme == _M) {
        res = true;
    }

    return res;
}

/*----------------------------------------------------------------------------*/
bool CtSomme::filtrer(list<Contrainte*>& aFiltrer, map<Variable*, std::list<Contrainte*>>& associees) {


    bool res = false;

    // 1ère étape : calcul du membre de droite en fonction des valeurs affectées
    int dte = _M;

    list<Variable*> libre;
    for(Variable* variable : _var) {
        if(variable->estAffectee()) {
            dte -= variable->valeur();
        } else {
            libre.push_back(variable);
        }
    }

    // ensuite, parcours de toutes les variables libres. On cherche une affectation impossible

    // le test est fait pour chaque variable non affectée

    for(Variable* variable : libre) {

        list<int> aEnlever;

        list<Variable*> aTester(libre);
        aTester.remove(variable); //toutes les variables libres sauf celle qui est en cours de test


        // recherche d'une affectation des variables pour vérifier la contrainte
        while(variable->affecter()) {

            // tentative d'affectation vérifiant la contrainte
            if(!satisfaire(aTester, variable->valeur(), dte)) {
                // si aucune affectation des variables n'a permis de vérifier la contrainte, la valeur est inutile
                aEnlever.push_back(variable->valeur());
            }
        }

        if(aEnlever.size() > 0 && !res) {
            res = true;

            // mise à jour des contraintes à filtrer

            list<Contrainte*>& cont = associees[variable];
            for(Contrainte* contrainte : cont) {
                if(find(aFiltrer.begin(), aFiltrer.end(), contrainte) == aFiltrer.end()) {
                    aFiltrer.push_back(contrainte); // la contrainte est ajoutée si elle n'était pas présente
                }
            }

        }

        // les valeurs contradictoires sont ensuite supprimées du domaine de la variable
        for(int val : aEnlever) {
            variable->enleveVal(val);
        }

    }

    return res;
}

/*----------------------------------------------------------------------------*/
bool CtSomme::satisfaire(std::list<Variable*>& listeTest, int val, int dte) {

    // rajouter des bornes pour ne pas faire certains tests ?

    int somme = val; // somme de toute les variables affectées

    auto it = listeTest.begin();
    bool continuer = true;
    bool trouve = false;

    while(continuer) {

        // si il y a des variables non affectées, on avance jusqu'au bout

        if(it != listeTest.end()) {

            if((*it)->estAffectee()) {
                somme -= (*it)->valeur();
            }

            if((*it)->affecter()) {
                somme += (*it)->valeur();
                it ++;
            } else { // si l'affectation n'est pas possible, on revient en arrière
                if(it == listeTest.begin()) { // toutes les combi de valeurs ont été testées, l'algo s'arrête
                    continuer = false;
                } else {
                    it --;
                }
            }

        } else { // sinon vérifiction que la contrainte est vérifiée, sinon retour en arrière

            if(somme == dte) { // contrainte vérifiée, satisfaction réussie
                trouve = true;
                continuer = false;
            } else if(it != listeTest.begin()){ // contrainte non vérifiée mais il reste des valeurs à tester
                it --;
            } else {
                continuer = false;
            }

        }

    }

    if(trouve) { // les variables redeviennent libres
        for(Variable* var : listeTest) {
            var->desaffecter();
        }
    }

    return trouve;
}
