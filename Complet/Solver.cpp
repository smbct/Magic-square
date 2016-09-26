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
    construireInstance();
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

        cout << "itération : " << iteration << endl;
        iteration ++;

        if(!aAffecter.empty()) { // parcours en profondeur

            // filtrage/propagation
            filtrerPropager();

            // cout << "contradiction ? " << contradiction() << endl;

            if(!contradiction()) {
                // exploration
                affectees.push(aAffecter.front());
                aAffecter.pop_front();
                affectees.top()->affecter(); // affectation de la variable à la première valeur

                // une affectation -> sauvegarde des domaines
                for(Variable* var : _variables) {
                    var->sauvegardeDomaine();
                }

                majFileFiltre(affectees.top()); // une affectation -> des contraintes à filtrer
            } else { // verif si contradiction, backtracking si nécessaire
                backtrack(affectees, aAffecter);
                if(affectees.empty()) {
                    arret = true;
                }
            }

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
    do {

        // rétablissement des domaines
        for(Variable* var : _variables) {
            var->restoreDomaine();
        }

        // tentative d'affectation une fois de plus
        if(affectees.top()->estAffectee()) {
            affectees.top()->affecter();
            cout << "affectation" << endl;
        }

        if(!affectees.top()->estAffectee()) { // pas possible d'affecter, on remonte
            // la variable redevient libre
            aAffecter.push_front(affectees.top());
            // toutes les valeurs possibles de la variable ont été testées
            affectees.pop();
            cout << "retrait" << endl;
        }

    } while(!affectees.empty() && !affectees.top()->estAffectee());


    if(!affectees.empty()) {
        majFileFiltre(affectees.top()); // une affectation => des contraintes à filtrer

        // sauvegarde des domaines
        for(Variable* variable : _variables) {
            variable->sauvegardeDomaine();
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

    // FIXME Pas normal que le nb d'itération change en fonction du sens de parcours des contraintes
    // Il doit y avoir un problème dans le filtrage des contraintes

    // affichage de debug : résultat du filtrage et position dans l'arbre de résolution
    int ind = 0;
    cout << "avant filtrage : " << endl << endl;
    for(Variable* variable : _variables) {
        cout << "Variable " << ind << " : " << variable->toString() << endl;
        ind ++;
    }
    cout << endl << endl;

    bool continuer = true;
    while(continuer) {
        auto it = _contraintes.rbegin();
        continuer = false;
        while(it != _contraintes.rend()) { // filtrage des contraintes jusqu'au point fixe
            if((*it)->filtrer()) {
                //continuer = true;
            }
            it ++;
        }

    }

    // affichage de debug : résultat du filtrage et position dans l'arbre de résolution
    ind = 0;
    cout << endl << endl << "après filtrage : " << endl;
    for(Variable* variable : _variables) {
        cout << "Variable " << ind << " : " << variable->toString() << endl;
        ind ++;
    }
    cout << endl << endl << endl;

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
