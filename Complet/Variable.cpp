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
_ordre(max-min+1),
_min(min),
_max(max)
{

    for(int val = min; val <= max; val ++) {
        _domaine.push_back(val);
    }

    // création d'une permutation aléatoire pour déterminer l'ordre d'affectation des variables
    vector<int> dom(max-min+1);
    for(unsigned int i = 0; i < dom.size(); i++) {
        dom[i] = i+1;
    }

    int nbFait = 0;
    while(!dom.empty()) {
        int indice = rand()%static_cast<int>(dom.size());
        _ordre[nbFait] = dom[indice];
        dom.erase(dom.begin()+indice);

        nbFait ++;
    }



}

/*----------------------------------------------------------------------------*/
string Variable::toString() {

    string res;

    if(!estAffectee()) {
        res = "{";

        ostringstream flux;

        for(auto it = _domaine.begin(); it != _domaine.end(); it++) {
            flux.str(string());
            flux.clear();
            flux << *it;
            res += flux.str();
            auto it2 = it;
            it2 ++;
            if(it2 != _domaine.end()) {
                res += ", ";
            }
        }
        res += "}";
        res += "  min = ";


        res += flux.str() + " ; max = ";
        flux.str(string());
        flux.clear();
        flux << _max;
        res += flux.str();
    } else {
        ostringstream flux;
        flux.str(string());
        flux.clear();
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

    // le domaine n'est pas vide, on peut calculer les valeurs minimales et maximales
    if(_domaine.size() > 0) {
        // mise à jour des valeurs minimales et des valeurs maximales
        if(val == _min) {
            _min = *std::min_element(_domaine.begin(), _domaine.end());
        }
        if(val == _max) {
            _max = *std::max_element(_domaine.begin(), _domaine.end());
        }
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
    // réinsertion des valeurs supprimées
    _domaine.insert(_domaine.end(), supp.begin(), supp.end());
    // suppression des valeurs supprimées du backup
    _filtrees.pop();

    // mise à jour des valeurs min et max
    auto paire = std::minmax_element(_domaine.begin(), _domaine.end());
    _min = *(paire.first);
    _max = *(paire.second);

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
    } else {
        enleveVal(*_valIt);
    }

    // cout << "indDom : " << _indDom << endl;

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
        // cout << "fin domaine" << endl;
    } else { // la valeur est retirée du domaine
        // cout << "valeur : " << *_valIt << endl;
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
    return static_cast<int>(_domaine.size());
}

/*----------------------------------------------------------------------------*/
int Variable::indAffecte() {
    return _indDom;
}

/*----------------------------------------------------------------------------*/
bool Variable::memeDomaine(Variable& autre) {

    bool meme = true;
    if(_domaine.size() != autre._domaine.size()) {
        meme = false;
    } else {

        auto it = _domaine.begin();
        while(meme && it != _domaine.end()) {
            if(count(autre._domaine.begin(), autre._domaine.begin(), *it) == 1) {
                it ++;
            } else {
                meme = false;
            }
        }

    }

    return meme;
}


/*----------------------------------------------------------------------------*/
int Variable::minDomaine() {
    return _min;
}

/*----------------------------------------------------------------------------*/
int Variable::maxDomaine() {
    return _max;
}

/*----------------------------------------------------------------------------*/
void Variable::copieDomaine(list<int>& copie) {
    for(int val : _domaine) {
        copie.push_back(val);
    }
}
