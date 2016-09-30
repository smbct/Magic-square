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

    int meilleurScore = scoreActuel;
    bool explore = false;
    int exploreIt;

    while(continuer) {

        cout << "jusque là : meilleur score = " << meilleurScore << endl;

        cout << config.toString() << endl;
        cout << "score : " << scoreActuel << endl;
        list<Configuration> voisins;
        config.genererVoisinage(voisins);

        Configuration voisinMin(_taille);
        int scoreMinVoisin = -1;
        for(Configuration& voisin : voisins) {

            int score = calculerScore(voisin);

            // un voisin ayant un meilleur score a été trouvé
            if(scoreMinVoisin == -1 || score < scoreMinVoisin) {
                scoreMinVoisin = score;
                voisinMin = voisin;

            }
        }

        cout << "scoreActuel : " << scoreActuel << endl;
        cout << "scoreMin : " << scoreMinVoisin << endl;
        cout << "sortir ? " << explore << " : " << exploreIt << endl;

        if(scoreMinVoisin < scoreActuel || (explore && exploreIt < 10)) {
            config = voisinMin;
            scoreActuel = scoreMinVoisin;
        }

        if(explore) {
            exploreIt ++;
        }

        if(explore && exploreIt > 10) {
            explore = false;
            config.regenerer();
            scoreActuel = calculerScore(config);
            cout << endl << endl << "saut" << endl << endl;
        }

        if (scoreMinVoisin > scoreActuel){
            config.regenerer();
            scoreActuel = calculerScore(config);
            cout << endl << endl << "saut" << endl << endl;
        }

        if(scoreMinVoisin == scoreActuel && !explore) {
            explore = true;
            exploreIt = 0;
            cout << "sortir du min local ?" << endl;
        }

        /*else if(scoreMinVoisin == scoreActuel) {
            if(!rechappe) {
                rechappe = true;
                rechappeIt = 0;
            } else {
                rechappeIt ++;
            }
        } else {
            rechappe = false;
        }*/

        /*if(scoreMinVoisin > scoreActuel) { // min local -> un saut est effectué
            rechappe = false;
            rechappeIt = 0;
            config.regenerer();
            scoreActuel = calculerScore(config);
            cout << endl << endl << "saut" << endl << endl;
        }*/


        if(scoreActuel < meilleurScore) {
            meilleurScore = scoreActuel;
        }

        if(meilleurScore == 0 || iter > 100000) {
            continuer = false;
        }

        iter ++;

    }

    cout << "meilleur score : " << meilleurScore << endl;



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
