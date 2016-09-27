/**
 * \file Configuration.cpp
 * \brief implémentation de la classe Configuration (incomplet)
 * \author S.B
 * \date 26/09/2016
 */

#include "Configuration.hpp"

#include <iostream>
#include <sstream>

using namespace incomplet;

using namespace std;

/*----------------------------------------------------------------------------*/
Configuration::Configuration(int taille) :
_taille(taille),
_max(taille*taille),
_ctr( (taille*(taille*taille+1))/2 ),
_valeurs(taille*taille)
{

}

/*----------------------------------------------------------------------------*/
void Configuration::swap(int ind1, int ind2) {
    int temp = _valeurs[ind2];
    _valeurs[ind2] = _valeurs[ind1];
    _valeurs[ind1] = temp;
}

/*----------------------------------------------------------------------------*/
void Configuration::genererVoisinage(std::list<Configuration>& voisinage) {

    Configuration config(_taille);
    for(int ligne = 0; ligne < _taille; ligne ++) {
        config = *this;

        for(int ind = 0; ind < _taille/2; ind ++) {
            config.swap(ligne*_taille+ind, ligne*_taille + _taille - ind - 1);
        }
        voisinage.push_back(config);
    }
    for(int col = 0; col < _taille; col ++) {
        config = *this;

        for(int ind = 0; ind < _taille/2; ind ++) {
            int ind1 = _taille*ind + col;// décalage dans le tableau
            int ind2 = _taille*(_taille - ind - 1) + col;
            config.swap(ind1, ind2);
        }
        voisinage.push_back(config);
    }

}

/*----------------------------------------------------------------------------*/
int Configuration::operator()(int ind) {
    return _valeurs.at(ind);
}


/*----------------------------------------------------------------------------*/
void Configuration::generer() {

    // génération d'une bonne config initiale
    // prend du temps mais est effectué une seule fois
    // pas deux valeurs identiques et certaines contraintes respectées

    int val = 1;
    for(int& valeur : _valeurs) {
        valeur = val;
        val ++;
    }

}

/*----------------------------------------------------------------------------*/
string Configuration::toString() {

    string res = "(";

    for(auto it = _valeurs.begin(); it != _valeurs.end(); it ++) {
        ostringstream flux;
        flux << *it;
        res += flux.str();
        auto it2 = it;
        it2 ++;
        if(it2 == _valeurs.end()) {
            res += ")";
        } else {
            res += ", ";
        }
    }
    return res;
}

/*----------------------------------------------------------------------------*/
void Configuration::genererLignesValides(list<int>& valeurs, list<list<int>>& lignes) {

    bool continuer = true;

    /*while(continuer) {

        // recherche d'un ensemble de _taille variable dont la somme est _ctr
        int somme = 0;

        list<list<int>::iterator> _iter;
        _iter.push_back(valeurs.begin());
        bool trouve = false;


        if(trouve) {

        } else {
            continuer = false;
        }

    }*/

}

/*----------------------------------------------------------------------------*/
bool Configuration::trouverEgalite(list<int>& valeurs, list<int>& ligne) {

    list<list<int>::iterator> liste;
    int somme = 0;
    bool trouve = false;

    do {

        if(liste.size() < _taille) { // ajout de valeur

            if(liste.empty()) {
                liste.push_back(valeurs.begin());
            } else {
                liste.push_back(liste.back());
            }
            somme += *liste.back();

        } else { // comparaison, backtracking si nécessaire

            if(somme == _ctr && allDifferent(liste)) { // verif de all different
                trouve = true;
            } else { // backtrack

                bool backtrack = true;
                while(!liste.empty() && backtrack) {

                    somme -= *liste.back();
                    liste.back() ++;

                    if(liste.back() == valeurs.end()) {
                        liste.pop_back();
                    } else {
                        backtrack = false;
                    }

                }

                if(!liste.empty()) {
                    somme += *liste.back();
                }

            }

        }

    } while(!trouve && !liste.empty() && liste.front() != valeurs.end());

    if(trouve) {
        for(auto it : liste) {
            ligne.push_back(*it);
            valeurs.erase(it);
        }

    }

    return trouve;

}

/*----------------------------------------------------------------------------*/
bool Configuration::allDifferent(list< list<int>::iterator >& valeurs) {

    bool res = true;
    auto it = valeurs.begin();

    while(res && it != valeurs.end()) {

        auto it2 = valeurs.begin();
        while(res && it2 != valeurs.end()) {
            if(it != it2 && **it == **it2) {
                res = false;
            } else {
                it2 ++;
            }
        }

        if(res) {
            it ++;
        }

    }

    return res;
}
