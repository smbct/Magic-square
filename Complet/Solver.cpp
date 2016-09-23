/**
 * \file Solver.cpp
 * \brief implémentation de la classe Solver
 * \author S.B
 * \date 21/09/2016
 */

#include "Solver.hpp"
#include "CtSomme.hpp"
#include "CtAllDiff.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

/*----------------------------------------------------------------------------*/
Solver::Solver(int n) :
_n(n),
_M( (n*(n*n+1))/2 )
{
    cout << "test1" << endl;
    construireInstance();
    cout << "test2" << endl;
}

/*----------------------------------------------------------------------------*/
void Solver::construireInstance() {

    // organisation des contraintes :
    // n contraintes ligne
    // puis n contraintes colonne
    // 2 contraintes de diagonale
    // enfin 1 contrainte alldiff

    // création des contraintes
    _contraintes.resize(2*_n+3);

    // création des contraintes
    for(int indCt = 0; indCt < 2*_n+2; indCt ++) {
        _contraintes[indCt] = new CtSomme(_M);
    }

    _contraintes.back() = new CtAllDiff();

    // création des n*n variables
    for(int ligne = 0; ligne < _n; ligne++) {
        for(int col = 0; col < _n; col++) {
            Variable* variable = new Variable(1, _n*_n);
            _variables.push_back(variable);

            // ajout de la variable à la contrainte ligne
            _contraintes[ligne]->ajouterVariable(variable);

            // ajout de la variable à une contrainte colonne
            _contraintes[_n+col]->ajouterVariable(variable);

            // si nécessaire ajout aux contraintes diagonales
            if(ligne == col) {
                _contraintes[2*_n]->ajouterVariable(variable);
            }
            if(ligne == _n-col-1) { // anti-diagonale
                _contraintes[2*_n+1]->ajouterVariable(variable);
            }

            // enfin ajout à la contrainte AllDiff
            _contraintes.back()->ajouterVariable(variable);
        }

    }

    cout << "variables size : " << _variables.size() << endl;

}

/*----------------------------------------------------------------------------*/
void Solver::resoudre() {

    bool arret = false;
    bool solution = false;

    list<Variable*> aAffecter(_variables); // les variables restant à affecter
    stack<Variable*> affectees; // les variables déjà affectées

    while(!arret) {

        // sauvegarde de l'état des domaines
        for(Variable* var : _variables) {
            var->sauvegardeDomaine();
        }

        if(!aAffecter.empty()) { // parcours en profondeur

            // filtrage/propagation
            filtrerPropager();

            // cout << "contradiction ? " << contradiction() << endl;

            // exploration
            affectees.push(aAffecter.front());
            aAffecter.pop_front();
            affectees.top()->affecter(); // affectation de la variable à la première valeur
        } else { // on est dans une feuille de l'arbre

            // toutes les variables ont été fixées

            // vérification que les contraintes sont respectées
            if(estSolution()) { // feuille de l'arbre, vérif si c'est une solution
                solution = true;
                arret = true;
            } else {
                backtrack(affectees, aAffecter);

                if(affectees.empty()) { // tout a été testé, il n'y a pas de solution
                    arret = true;
                }
            }
        }

        // verif si contradiction, backtracking si nécessaire
        if(contradiction()) {
            backtrack(affectees, aAffecter);
        }

    }

    if(solution) {
        cout << "Une solution a été trouvée : " << endl;

        auto it = _variables.begin();
        for(int ligne = 0; ligne < _n; ligne ++) {
            for(int col = 0; col < _n; col ++) {

                cout << (*it)->valeur() << " ";
                it ++;
            }
            cout << endl;
        }
    } else {
        cout << "Hélas, aucune solution n'a été trouvée :(" << endl;
    }

}

/*----------------------------------------------------------------------------*/
void Solver::backtrack(std::stack<Variable*>& affectees, std::list<Variable*>& aAffecter) {


    // remontée vers une variable qui peut encore être affectée et l'affecter
    while(!affectees.empty() && !affectees.top()->affecter()) { // tentative d'affectation de la variable en tête de pile

        aAffecter.push_front(affectees.top());

        // toutes les valeurs possibles de la variable ont été testées
        affectees.pop();

        // mise à jour des domaines
        for(Variable* var : _variables) {
            var->restoreDomaine();
        }

    }

}

/*----------------------------------------------------------------------------*/
void Solver::filtrerPropager() {

    // choix de l'ordre des contraintes
    // on choisit de filtrer d'abord les contraintes qui ont le plus de variables affectes

    // vector<Contrainte*> contraintesTri(_contraintes);
    // sort(contraintesTri.begin(), contraintesTri.end(), [](Contrainte* gch, Contrainte* dte)
                                                            // { return gch->nbVariableFixe() >= dte->nbVariableFixe(); });



    bool continuer = true;
    while(continuer) {
        auto it = _contraintes.begin();
        continuer = false;
        while(it != _contraintes.end()) { // filtrage des contraintes jusqu'au point fixe
            if((*it)->filtrer()) {
                continuer = true;
            }
            it ++;
        }

    }

}

/*----------------------------------------------------------------------------*/
bool Solver::estSolution() {
    bool res = true;
    auto it = _contraintes.begin();

    while(res && it != _contraintes.end()) {
        if(!(*it)->evaluer()) {
            res = false;
        } else {
            it ++;
        }
    }
    return res;
}

/*----------------------------------------------------------------------------*/
bool Solver::contradiction() {

    bool res = false;
    auto it = _variables.begin();
    while(!res && it != _variables.end()) {
        if((*it)->impossible()) {
            res = true;
        } else {
            it ++;
        }
    }
    return res;
}

/*----------------------------------------------------------------------------*/
Solver::~Solver() {

    // destruction des contraintes
    for(Contrainte* ctr : _contraintes) {
        delete ctr;
    }

    // destruction des variables
    for(Variable* var : _variables) {
        delete var;
    }

}
