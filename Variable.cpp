/**
 * \file Variable.cpp
 * \brief implémentation de la classe Variable
 * \author S.B
 */

#include "Variable.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

/*----------------------------------------------------------------------------*/
Variable::Variable(int min, int max) {

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
void Variable::enleveVal(int val) {
    // garde en mémoire la liste des valeurs enlevées
    _filtrees.top().push_back(val);
    // suppression des valeurs du domaine
    _domaine.remove(val);
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
