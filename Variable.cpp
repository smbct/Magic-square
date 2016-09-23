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

/*----------------------------------------------------------------------------*/
Variable::Variable(int min, int max) :
_affectee(false)
{

    for(int val = min; val <= max; val ++) {
        _domaine.push_back(val);
    }

}

/*----------------------------------------------------------------------------*/
string Variable::toString() {

    string res;

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

    if(!_affectee) {
        _affectee = true;
        _valIt = _domaine.begin();
    } else {
        _valIt ++;
    }

    if(_valIt == _domaine.end()) {
        _affectee = false;
        return false;
    } else {
        return true;
    }
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

    // TODO remplacer par des exceptions
    assert(_affectee);

    return *_valIt;
}
