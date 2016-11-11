/**
 * \file Variable.cpp
 * \brief implémentation de la classe Variable
 * \author S.B
 */

#include "Variable.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>

#include <cassert>

using namespace std;

using namespace complet;

/*----------------------------------------------------------------------------*/
Variable::Variable(int min, int max) :
_affectee(false),
_ordre(max-min+1)
{

    for(int val = min; val <= max; val ++) {
        _domaine.push_back(val);
    }

    // création d'une permutation aléatoire pour déterminer l'ordre d'affectation des variables
    /*vector<int> dom(max-min+1);
    for(int i = 0; i < dom.size(); i++) {
        dom[i] = i+1;
    }

    int nbFait = 0;
    while(!dom.empty()) {
        int indice = rand()%dom.size();
        _ordre[nbFait] = dom[indice];
        dom.erase(dom.begin()+indice);

        nbFait ++;
    }*/

}

/*----------------------------------------------------------------------------*/
string Variable::toString() {

    string res;

    if(!estAffectee()) {
        res = "{";

        for(auto it = _domaine.begin(); it != _domaine.end(); it++) {
            ostringstream flux;
            flux << *it;
            res += flux.str();
            auto it2 = it;
            it2 ++;
            if(it2 != _domaine.end()) {
                res += ", ";
            }
        }
        res += "}";
    } else {
        ostringstream flux;
        flux << valeur();
        res += ":= " + flux.str();
    }

    return res;
}

/*----------------------------------------------------------------------------*/
bool Variable::enleveVal(int val) {

    bool res = false;
    auto it = find(_domaine.begin(), _domaine.end(), val);

    if(it != _domaine.end()) {
        // garde en mémoire la liste des valeurs enlevées
        _filtrees.top().push_back(val);

        // suppression des valeurs du domaine
        _domaine.erase(it);

        // la valeur était bien présente
        res = true;
    }

    return res;
}

/*----------------------------------------------------------------------------*/
void Variable::sauvegardeDomaine() {
    _filtrees.push(list<int>());
}

/*----------------------------------------------------------------------------*/
void Variable::restoreDomaine() {

    list<int>& supp = _filtrees.top();
    // réinsertion des valeurs supprimmées
    _domaine.insert(_domaine.end(), supp.begin(), supp.end());
    // suppression des valeurs supprimées du backup
    _filtrees.pop();
}

/*----------------------------------------------------------------------------*/
bool Variable::affecter() {

    // si pas d'affectation, on affecte au début de la liste
    if(!_affectee) {
        _affectee = true;
        _valIt = _domaine.begin();
        _indDom = 0;
    } else {
        _valIt ++;
        _indDom ++;
    }

    // si toutes les valeurs ont été affectées, la variable n'est plus affectable pour le moment
    if(_valIt == _domaine.end()) {
        _affectee = false;
    }

    return _affectee;
}

/*----------------------------------------------------------------------------*/
bool Variable::affecterOrdre() {

    // si pas d'affectation, on affecte au début de la liste
    if(!_affectee) {
        _affectee = true;
        _valIt = _domaine.begin();
        _indDom = 0;
    }
    cout << "indDom : " << _indDom << endl;

    bool continuer = true;
    while(continuer && _indDom < _ordre.size()) {
        _valIt = find(_domaine.begin(), _domaine.end(), _ordre[_indDom]);
        if(_valIt == _domaine.end()) {
            _indDom ++;
        } else {
            continuer = false;
        }
    }

    _affectee = true;

    // si toutes les valeurs ont été affectées, la variable n'est plus affectable pour le moment
    if(_indDom == _ordre.size()) {
        _affectee = false;
        cout << "fin domaine" << endl;
    } else { // la valeur est retirée du domaine
        cout << "valeur : " << *_valIt << endl;
        enleveVal(*_valIt);
    }


    return _affectee;

}

/*----------------------------------------------------------------------------*/
void Variable::desaffecter() {
    _affectee = false;
}

/*----------------------------------------------------------------------------*/
bool Variable::estAffectee() {
    return _affectee;
}

/*----------------------------------------------------------------------------*/
int Variable::valeur() {

    return *_valIt;
}

/*----------------------------------------------------------------------------*/
bool Variable::impossible() {
    return tailleDomaine() == 0;
}

/*----------------------------------------------------------------------------*/
int Variable::tailleDomaine() {
    return _domaine.size();
}

/*----------------------------------------------------------------------------*/
int Variable::indAffecte() {
    return _indDom;
}
