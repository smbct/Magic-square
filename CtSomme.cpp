/**
 * \file CtSomme.cpp
 * \brief implémentation de la classe CtSomme
 * \author S.B
 * \date 23/09/2016
 */

#include "CtSomme.hpp"
#include <iostream>

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

    // ensuite, parcours de toutes les variables libres. On cherche une affectation impossible

    // le test est fait pour chaque variable libre

    for(Variable* variable : libre) {

        list<int> aEnlever;

        list<Variable*> aTester(libre);
        aTester.remove(variable); //toutes les variables libres sauf celle en cours de test

        // pour chaque valeur possible de cette variable, on vérifie si on peut rendre la contrainte vraie
        while(variable->affecter()) {

            bool trouve = false; // indique si une affectations des valeurs permet de vérifier la contrainte
            int somme = 0;

            // TODO test à rajouter
            // attention ici la liste doit avoir au moins un élément
            auto it = aTester.begin();

            do {

                // si on n'est pas au bout, on continue à avancer dans la liste
                if(it != aTester.end()) { // s'il reste des variables à affecter, elle le sont

                    if((*it)->estAffectee()) {
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
                            it ++; // on vance à la prochaine variable à affecter
                        }

                    } else {
                        it --;
                    }

                } else { //toutes les variables ont été affectées, on vérifie si on peut valider la contrainte

                    if(somme == dte) { // si la contrainte est vérifiée, on peut sortir du test
                        trouve = true;
                        for(Variable* var : libre) {
                            cout << var->valeur() << " ; ";
                        }
                        cout << endl;
                    } else { // sinon, on recul pour tenter d'autres affectations
                        it --;
                    }
                }

            } while(!trouve && aTester.front()->estAffectee());

            if(trouve) {
                aEnlever.push_back(variable->valeur());
            }

        }
        // la variable est désaffectée automatiquement


        // les valeurs contradictoires sont ensuite supprimées du domaine de la variable
        /*for(int val : aEnlever) {
            variable->enleveVal(val);
        }*/
    }



    return res;
}
