/**
 * \file Solver.cpp
 * \brief implémentation de la classe Solver (incomplet)
 * \author S.B
 * \date 26/09/2016
 */


#include "Solver.hpp"
#include "CtSomme.hpp"

#include <iostream>

using namespace incomplet;

using namespace std;

/*----------------------------------------------------------------------------*/
Solver::Solver(int taille) :
_taille(taille),
_M( (taille* (taille*taille+1))/2 )
{
    creerContraintes();
}

/*----------------------------------------------------------------------------*/
void Solver::creerContraintes() {

    // contrainte des lignes
    for(int ligne = 0; ligne < _taille; ligne ++) {
        _contraintes.push_back(new CtSomme(_M));
        for(int col = 0; col < _taille; col ++) {
            _contraintes.back()->ajouterVariable(ligne*_taille + col);
        }
    }

    // contraintes des colonnes
    for(int col = 0; col < _taille; col ++) {
        _contraintes.push_back(new CtSomme(_M));
        for(int ligne = 0; ligne < _taille; ligne ++) {
            _contraintes.back()->ajouterVariable(ligne*_taille + col);
        }
    }

    // contraintes des diagonales
    _contraintes.push_back(new CtSomme(_M));
    for(int ligne = 0; ligne < _taille; ligne ++) {
        _contraintes.back()->ajouterVariable(ligne*_taille + ligne);
    }

    _contraintes.push_back(new CtSomme(_M));
    for(int ligne = 0; ligne < _taille; ligne ++) {
        _contraintes.back()->ajouterVariable(ligne*_taille + (_taille - ligne - 1));
    }


}

/*----------------------------------------------------------------------------*/
void Solver::resoudre() {

    Configuration config(_taille);
    config.generer();

    bool continuer = true;
    int iter = 0;
    int scoreActuel = calculerScore(config);

    while(continuer) {

        list<Configuration> voisins;
        config.genererVoisinage(voisins);

        Configuration* meilleure;
        int meilleurScore = -1;

        for(Configuration& config : voisins) {

            int score = calculerScore(config);
            cout << config.toString() << "  :  " << score << endl;

            if((meilleurScore == -1 || score < meilleurScore) && score < scoreActuel) {
                meilleurScore = score;
                meilleure = &config;
            }
        }

        if(meilleurScore != -1) {
            config = *meilleure;
            scoreActuel = meilleurScore;
        } else {
            continuer = false;
            // modifier par faire un saut
        }

        if(meilleurScore == 0 || iter > 10000) {
            continuer = false;
        }

        iter ++;

    }

    cout << "meilleur score : " << scoreActuel << endl;



}

/*----------------------------------------------------------------------------*/
int Solver::calculerScore(Configuration& config) {

    int score = 0;

    for(Contrainte* contrainte : _contraintes) {
        score += contrainte->score(config);
    }
    return score;
}

/*----------------------------------------------------------------------------*/
Solver::~Solver() {

    for(Contrainte* contrainte : _contraintes) {
        delete contrainte;
    }

}
