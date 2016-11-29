/**
 * \file Grille.cpp
 * \brief implémentation de la classe Grille
 */

#include "Grille.hpp"
#include <sstream>
#include <iostream>

using namespace incomplet;
using namespace std;

/*----------------------------------------------------------------------------*/
Grille::Grille(int taille) :
_taille(taille),
_magique( (taille*(taille*taille + 1)) / 2  ),
_grille(taille*taille),
_sommeLigne(taille, 0),
_sommeCol(taille, 0),
_sommeDiag(0),
_sommeAntiDiag(0)
{

    /* remplissage de la grille avec une mauvaise solution initiale */
    for(int i = 0; i < taille*taille; i++) {
        _grille[i] = i+1;
    }

    initialiserSomme();
    initialiserScore();
}

/*----------------------------------------------------------------------------*/
void Grille::initialiserSomme() {

    for(int i = 0; i < _taille; i++) {
        _sommeLigne[i] = 0;
        _sommeCol[i] = 0;
    }
    _sommeDiag = 0;
    _sommeAntiDiag = 0;

    for(int i = 0; i < _taille; i++) {
        for(int j = 0; j < _taille; j++) {
            _sommeLigne[i] += _grille[i*_taille+j];
            _sommeCol[j] += _grille[i*_taille+j];

            if(i == j) {
                _sommeDiag += _grille[i*_taille+j];
            }

            if(i == _taille-j-1) {
                _sommeAntiDiag += _grille[i*_taille+j];
            }
        }
    }

}

/*----------------------------------------------------------------------------*/
void Grille::majScore(int elta, int eltb) {

    /* calcul les indices des lignes et de colonnes */
    int lignea = elta/_taille;
    int cola = elta%_taille;

    int ligneb = eltb/_taille;
    int colb = eltb%_taille;

    /* mise à jour des deux lignes */
    if(lignea != ligneb) {

        _score -= (_sommeLigne[lignea]-_magique)*(_sommeLigne[lignea]-_magique);
        _sommeLigne[lignea] += _grille[ligneb*_taille+colb] - _grille[lignea*_taille+cola];
        _score += (_sommeLigne[lignea]-_magique)*(_sommeLigne[lignea]-_magique);

        _score -= (_sommeLigne[ligneb]-_magique)*(_sommeLigne[ligneb]-_magique);
        _sommeLigne[ligneb] += _grille[lignea*_taille+cola] - _grille[ligneb*_taille+colb];
        _score += (_sommeLigne[ligneb]-_magique)*(_sommeLigne[ligneb]-_magique);
    }

    /* mise à jour des deux colonnes */
    if(cola != colb) {

        _score -= (_sommeCol[colb]-_magique)*(_sommeCol[colb]-_magique);
        _sommeCol[colb] += _grille[lignea*_taille+cola] - _grille[ligneb*_taille+colb];
        _score += (_sommeCol[colb]-_magique)*(_sommeCol[colb]-_magique);

        _score -= (_sommeCol[cola]-_magique)*(_sommeCol[cola]-_magique);
        _sommeCol[cola] += _grille[ligneb*_taille+colb] - _grille[lignea*_taille+cola];
        _score += (_sommeCol[cola]-_magique)*(_sommeCol[cola]-_magique);
    }

    /* si la diagonale a été modifiée */
    if(lignea == cola && ligneb != colb) {
        _score -= (_sommeDiag-_magique)*(_sommeDiag-_magique);
        _sommeDiag += _grille[ligneb*_taille+colb] - _grille[lignea*_taille+cola];
        _score += (_sommeDiag-_magique)*(_sommeDiag-_magique);
    }
    if(ligneb == colb && lignea != cola) {
        _score -= (_sommeDiag-_magique)*(_sommeDiag-_magique);
        _sommeDiag += _grille[lignea*_taille+cola] - _grille[ligneb*_taille+colb];
        _score += (_sommeDiag-_magique)*(_sommeDiag-_magique);
    }

    /* si l'anti diagonale a été changée */
    if(lignea == _taille-cola-1 && ligneb != _taille-colb-1) {
        _score -= (_sommeAntiDiag-_magique)*(_sommeAntiDiag-_magique);
        _sommeAntiDiag += _grille[ligneb*_taille+colb] - _grille[lignea*_taille+cola];
        _score += (_sommeAntiDiag-_magique)*(_sommeAntiDiag-_magique);
    }
    if(ligneb == _taille-colb-1 && lignea != _taille-cola-1) {
        _score -= (_sommeAntiDiag-_magique)*(_sommeAntiDiag-_magique);
        _sommeAntiDiag += _grille[lignea*_taille+cola] - _grille[ligneb*_taille+colb];
        _score += (_sommeAntiDiag-_magique)*(_sommeAntiDiag-_magique);
    }

}

/*----------------------------------------------------------------------------*/
string Grille::toString() {

    string res = "";

    for(int i = 0; i < _taille; i++) {
        for(int j = 0; j < _taille; j++) {
            ostringstream oss;
            oss << _grille[i*_taille+j];
            res += oss.str();
            if(j < _taille-1) {
                res += " ";
            }
        }
        res += "\n";
    }

    return res;
}

/*----------------------------------------------------------------------------*/
void Grille::echange(int elta, int eltb) {

    majScore(elta, eltb);
    echangeValeurs(elta, eltb);

}

/*----------------------------------------------------------------------------*/
void Grille::echangeAlea() {

    int elta;
    int eltb;

    elta = rand()%(_taille*_taille);
    eltb = rand()%(_taille*_taille);

    echange(elta, eltb);
    _elta = elta;
    _eltb = eltb;
}

/*----------------------------------------------------------------------------*/
void Grille::annulerEchange() {
    echange(_eltb, _elta);
}

/*----------------------------------------------------------------------------*/
void Grille::echangeValeurs(int elta, int eltb) {
    int temp = _grille[elta];
    _grille[elta] = _grille[eltb];
    _grille[eltb] = temp;
}

/*----------------------------------------------------------------------------*/
void Grille::initialiserScore() {

    _score = 0;
    for(unsigned int& somme : _sommeLigne) {
        _score += (somme-_magique)*(somme-_magique);
    }
    for(unsigned int& somme : _sommeCol) {
        _score += (somme-_magique)*(somme-_magique);
    }
    _score += (_sommeDiag-_magique)*(_sommeDiag-_magique);
    _score += (_sommeAntiDiag-_magique)*(_sommeAntiDiag-_magique);

}

/*----------------------------------------------------------------------------*/
void Grille::restart() {

    vector<int> valeursDispos(_taille*_taille);
    for(int i = 0; i < valeursDispos.size(); i++) {
        valeursDispos[i] = i+1;
    }
    int nbRestantes = valeursDispos.size();

    for(int i = 0; i < _taille*_taille; i++) {
        int indice = rand()%nbRestantes;
        _grille[i] = valeursDispos[indice];
        nbRestantes --;
        valeursDispos[indice] = valeursDispos[nbRestantes];
    }
    initialiserSomme();
    initialiserScore();

}

/*----------------------------------------------------------------------------*/
int Grille::score() {

    return _score;
}
