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

    // astuce : retenir les valeurs des variables pour lesquelles on a trouvé une affectation

    vector<vector<bool>> dejaTeste(libre.size()); // tableau dans lequel les indices représentent les variables
    // les listes indiquent les valeurs des domaines pour lesquelles on a trouvé une affectation
    int indVar = 0;
    for(Variable* var : libre) {
        dejaTeste[indVar].resize(var->tailleDomaine(), false);
        indVar ++;
    }

    // ensuite, parcours de toutes les variables libres. On cherche une affectation impossible

    // le test est fait pour chaque variable non affectée

    indVar = 0;
    for(Variable* variable : libre) {

        list<int> aEnlever;

        // recherche d'une affectation des variables pour vérifier la contrainte
        while(variable->affecter()) {

            // tentative d'affectation vérifiant la contrainte
            //if(!dejaTeste[indVar][variable->indAffecte()]) {
                if(!satisfaire(libre, indVar, dte-variable->valeur(), dejaTeste)) {
                    // si aucune affectation des variables n'a permis de vérifier la contrainte, la valeur est inutile
                    aEnlever.push_back(variable->valeur());
                }
            //}
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

        indVar ++;
    }

    return res;
}

/*----------------------------------------------------------------------------*/
bool CtSomme::satisfaire(list<Variable*>& variables, int varTest, int dte, vector<vector<bool>>& dejaTeste) {

    // rajouter des bornes pour ne pas faire certains tests ?

    int somme = 0; // somme de toute les variables affectées

    auto it = variables.begin();
    int indVar = 0;

    if(indVar == varTest) {
        indVar ++;
        it ++;
    }

    bool continuer = true;
    bool trouve = false;

    while(continuer) {

        // si il y a des variables non affectées, on avance jusqu'au bout

        if(it != variables.end()) {

            // dé-mise à jour de la somme, cette valeur là n'est plus actuellement considérée
            if((*it)->estAffectee()) {
                somme -= (*it)->valeur();
            }

            if((*it)->affecter()) {
                somme += (*it)->valeur();
                it ++;
                indVar ++;
                if(indVar == varTest) { // saut pour ne pas passer la variable à tester
                    it ++;
                    indVar ++;
                }

            } else { // si l'affectation n'est pas possible, on revient en arrière
                if(it == variables.begin()) { // toutes les combi de valeurs ont été testées, l'algo s'arrête
                    continuer = false;
                } else {
                    it --;
                    indVar --;

                    if(indVar == varTest) {
                        if(it != variables.begin()) {
                            it --;
                            indVar --;
                        } else {
                            continuer = false;
                        }
                    }
                }
            }


        } else { // sinon vérifiction que la contrainte est vérifiée, sinon retour en arrière

            if(somme == dte) { // contrainte vérifiée, satisfaction réussie
                trouve = true;
                continuer = false;
            } else if(it != variables.begin()){ // contrainte non vérifiée mais il reste des valeurs à tester
                it --;
                indVar --;

                if(indVar == varTest) {
                    if(it != variables.begin()) {
                        it --;
                        indVar --;
                    } else {
                        continuer = false;
                    }
                }

            } else {
                continuer = false;
            }

        }

    }

    if(trouve) { // les variables redeviennent libres

        // mise à jour du tableau, l'affectation est utile pour plusieurs variables
        indVar = 0;
        int abc = 0;
        for(auto iter = variables.begin(); iter != variables.end(); iter ++) {
            // abc ++;
            indVar ++;
        }
        // for(Variable* var : variables) {
            // indVar += 1;

            /*if(indVar != varTest) {
                dejaTeste[indVar][var->indAffecte()] = true;
            }*/
        // }

        for(Variable* var : variables) {
            if(indVar != varTest) {
                var->desaffecter();
            }
            indVar ++;
        }
    }

    return trouve;
}
