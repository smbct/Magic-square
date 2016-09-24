/**
 * \file CtSomme.cpp
 * \brief implémentation de la classe CtSomme
 * \author S.B
 * \date 23/09/2016
 */

#include "CtSomme.hpp"
#include <iostream>
#include <cassert>

using namespace std;

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
bool CtSomme::filtrer() {


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

    // TODO enlever
    // assert(libre.size() != 0);

    // ensuite, parcours de toutes les variables libres. On cherche une affectation impossible

    // le test est fait pour chaque variable libre

    for(Variable* variable : libre) {

        list<int> aEnlever;

        list<Variable*> aTester(libre);
        aTester.remove(variable); //toutes les variables libres sauf celle en cours de test

        // pour chaque valeur possible de cette variable, on vérifie si on peut rendre la contrainte vraie
        while(variable->affecter()) {

            bool trouve = true;
            if(aTester.size() > 0) { // tentative d'affectation vérifiant la contrainte
                trouve = satisfaire(aTester, variable->valeur(), dte);
            } else { // test facile, il suffit de voir si la valeur correspond
                trouve = (variable->valeur() == dte); // on peut mettre ce test autre part pour améliorer les perf ? TODO
            }

            if(!trouve) {
                aEnlever.push_back(variable->valeur());
            }
        }

        if(aEnlever.size() > 0 && !res) {
            res = true;
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

    auto it = listeTest.begin();

    int somme = val; // somme de toute les variables affectées

    bool trouve = false;

    // rajouter des bornes pour ne pas faire certains tests ?

    do { // tant qu'une affectation n'a pas été trouvée et qu'elles n'ont pas toutes été testées

        if(it != listeTest.end()) { // s'il reste des variables à affecter, elle le sont

            if((*it)->estAffectee()) { // si la variable était déjà affectée, on met à jour la valeur de la somme
                somme -= (*it)->valeur();
            }

            if((*it)->affecter()) { // si possible l'affectation suivante est faîte

                // mise à jour de la somme des variables affectées
                somme += (*it)->valeur();

                // si la somme des affectées est > à la valeur de dte, pas possible de vérifier la contrainte
                if(somme > dte) {
                    somme -= (*it)->valeur();
                    (*it)->desaffecter();
                    it --;
                } else {
                    it ++; // on avance à la prochaine variable à affecter
                }

            } else {
                it --;
            }

        } else { //toutes les variables ont été affectées, on vérifie si on peut valider la contrainte

            if(somme == dte) { // si la contrainte est vérifiée, on peut sortir du test
                trouve = true;
            } else { // sinon, on recul pour tenter d'autres affectations
                it --;
            }
        }

    } while(!trouve && listeTest.front()->estAffectee());

    if(trouve) {
        for(Variable* var : listeTest) {
            var->desaffecter();
        }
    }

    return trouve;
}
