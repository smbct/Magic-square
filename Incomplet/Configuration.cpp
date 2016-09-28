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
void Configuration::inverserLigne(int ligne) {
    for(int ind = 0; ind < _taille/2; ind ++) {
        swap(ligne*_taille + ind, ligne*_taille + _taille - ind - 1);
    }
}

/*----------------------------------------------------------------------------*/
void Configuration::inverserColonne(int colonne) {
    for(int ind = 0; ind < _taille/2; ind ++) {
        int ind1 = _taille*ind + colonne;
        int ind2 = _taille*(_taille-ind-1) + colonne;
        swap(ind1, ind2);
    }
}

/*----------------------------------------------------------------------------*/
void Configuration::inverserDiagonale() {
    for(int ind = 0; ind < _taille/2; ind ++) {
        int ind2 = _taille-ind-1;
        swap(ind*_taille+ind, ind2*_taille+ind2);
    }
}

/*----------------------------------------------------------------------------*/
void Configuration::inverserAntiDiagonale() {

    for(int ind = 0; ind < _taille/2; ind ++) {
        int ind2 = _taille-ind-1;
        swap(ind*_taille+_taille-ind-1, ind2*_taille+_taille-ind2-1);
    }

}

/*----------------------------------------------------------------------------*/
void Configuration::genererVoisinage(std::list<Configuration>& voisinage) {

    Configuration config(_taille);

    // génération de toutes les permut de deux éléments possible
    for(int ind = 0; ind < _taille*_taille; ind ++) {
        for(int ind2 = ind+1; ind2 < _taille*_taille; ind2 ++) {
            config = *this;
            config.swap(ind, ind2);
            voisinage.push_back(config);
        }
    }


    // génération des permutations de 3 éléments
    // exemple : permutations de 1 2 3 :
    // 2 1 3 ; 3 1 2 ; 3 2 1 On exclut les permutations de deux éléments
    for(int ind = 0; ind < _taille*_taille; ind ++) {
        for(int ind2 = ind+1; ind2 < _taille*_taille; ind2 ++) {
            for(int ind3 = ind2+1; ind3 < _taille*_taille; ind3 ++) {
                config = *this;
                config.swap(ind, ind3);
                config.swap(ind, ind2);
                voisinage.push_back(config);
                config = *this;
                config.swap(ind, ind2);
                config.swap(ind2, ind3);
                voisinage.push_back(config);
                config = *this;
                config.swap(ind, ind3);
                voisinage.push_back(config);
            }
        }
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
void Configuration::regenerer() {

    for(int ligne = 0; ligne < _taille; ligne +=2) {
        inverserLigne(ligne);
    }
    for(int col = 0; col < _taille; col ++) {
        inverserColonne(col);
    }

    inverserDiagonale();
    inverserAntiDiagonale();

    // int offset = -1;
    // for(int iter = 0; iter < _taille*_taille/2; iter ++) {
    //
    //     int ind = rand() % _taille*_taille;
    //     int ind2 = rand() % _taille*_taille;
    //
    //     swap(ind, ind2);
    // }

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
