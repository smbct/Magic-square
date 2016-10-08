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

using namespace complet;

/*----------------------------------------------------------------------------*/
Solver::Solver(int n) :
_n(n),
_M( (n*(n*n+1))/2 )
{
    construireInstance();
}

/*----------------------------------------------------------------------------*/
void Solver::construireInstance() {

    // organisation des contraintes :
    // n contraintes ligne
    // n contraintes colonne
    // contraintes de diagonale
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

            // création de la paire pour la liste associative
            _associees.insert(pair<Variable*, list<Contrainte*>>(variable, list<Contrainte*>()));

            // ajout de la variable à la contrainte ligne
            _contraintes[ligne]->ajouterVariable(variable);
            _associees[variable].push_back(_contraintes[ligne]);

            // ajout de la variable à une contrainte colonne
            _contraintes[_n+col]->ajouterVariable(variable);
            _associees[variable].push_back(_contraintes[_n+col]);

            // si nécessaire ajout aux contraintes diagonales
            if(ligne == col) {
                _contraintes[2*_n]->ajouterVariable(variable);
                _associees[variable].push_back(_contraintes[2*_n]);
            }
            if(ligne == _n-col-1) { // anti-diagonale
                _contraintes[2*_n+1]->ajouterVariable(variable);
                _associees[variable].push_back(_contraintes[2*_n+1]);
            }

            // enfin ajout à la contrainte AllDiff
            _contraintes.back()->ajouterVariable(variable);
            _associees[variable].push_back(_contraintes.back());
        }

    }

}

/*----------------------------------------------------------------------------*/
void Solver::resoudre() {

    bool arret = false;
    bool solution = false;


    list<Variable*> aAffecter(_variables); // les variables restant à affecter

    stack<Variable*> affectees; // les variables déjà affectées

    int iteration = 0;

    while(!arret) {

        // affichage courant
        int ind = 0;
        for(Variable* variable : _variables) {

            cout << ind << " : " << variable->toString() << endl;
            ind ++;
        }
        cout << endl << endl;

        cout << "itération : " << iteration << endl;
        iteration ++;

        if(!aAffecter.empty()) { // parcours en profondeur

            // filtrage/propagation
            bool contrad = contrad = filtrerPropager();

            // cout << "contradiction ? " << contradiction() << endl;

            if(!contrad) {

                // exploration
                affectees.push(aAffecter.front());
                aAffecter.pop_front();
                affectees.top()->affecter(); // affectation de la variable à la première valeur

                // mise à jour de la liste des contraites à filtrer
                list<Contrainte*>& cont = _associees[affectees.top()];
                _aFiltrer.insert(_aFiltrer.end(), cont.begin(), cont.end());

                // une affectation -> sauvegarde des domaines
                for(Variable* var : aAffecter) {
                    var->sauvegardeDomaine();
                }

            } else { // verif si contradiction, backtracking si nécessaire
                backtrack(affectees, aAffecter);
                if(affectees.empty()) {
                    arret = true;
                }
            }

        } else { // on est dans une feuille de l'arbre

            // toutes les variables ont été fixées

            // vérification que les contraintes sont respectées
            if(estSolution()) {
                solution = true;
                arret = true;
            } else {
                backtrack(affectees, aAffecter);

                if(affectees.empty()) {
                    arret = true;
                }
            }
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
        cout << "Hélas, aucune solution n'a été trouvée :( Il n'en existe pas" << endl;
    }

}

/*----------------------------------------------------------------------------*/
void Solver::backtrack(std::stack<Variable*>& affectees, std::list<Variable*>& aAffecter) {

    bool arret = false;

    while(!arret) { // remontée vers une variable qui peut encore être affectée et l'affecter

        if(!affectees.empty()) {

            // rétablissement des domaines car une modification est faite
            for(Variable* var : aAffecter) {
                var->restoreDomaine();
            }

            affectees.top()->affecter(); // le premier est forcément affecté (car en cours de résolution)

            if(!affectees.top()->estAffectee()) { // pas possible de l'affecter, il faut remonter

                // mise à jour de la pile et de la liste
                aAffecter.push_front(affectees.top());
                affectees.pop();
            } else { // l'affectation est réussie, arret du backtrack

                // sauvegarde des domaines
                for(Variable* variable : aAffecter) {
                    variable->sauvegardeDomaine();
                }

                // mise à jour de la liste des contraintes à filtrer
                list<Contrainte*>& cont = _associees[affectees.top()];
                _aFiltrer.insert(_aFiltrer.end(), cont.begin(), cont.end());

                arret = true;
            }
        } else {
            arret = true;
        }
    }


}

/*----------------------------------------------------------------------------*/
bool Solver::filtrerPropager() {

    bool res = false;

    while(!res && !_aFiltrer.empty()) {
        Contrainte * cont = _aFiltrer.front();
        _aFiltrer.pop_front();

        if(cont->filtrer(_aFiltrer, _associees)) {
            res = true;
        }
    }

    return res;
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
void Solver::majFileFiltre(Variable* variable) {
    list<Contrainte*>& liste = _associees[variable];
    for(Contrainte* contrainte : liste) {
        if(find(_aFiltrer.begin(), _aFiltrer.end(), contrainte) == _aFiltrer.end()) {
            _aFiltrer.push_front(contrainte);
        }
    }
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
