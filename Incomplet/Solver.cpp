/**
 * \file Solver.cpp
 * \brief implémentation de la classe Solver (incomplet)
 * \author S.B
 * \date 26/09/2016
 */


#include "Solver.hpp"
#include "CtSomme.hpp"

#include <iostream>
#include <algorithm>

using namespace incomplet;

using namespace std;

/*----------------------------------------------------------------------------*/
Solver::Solver(int taille) :
_taille(taille),
_M( (taille* (taille*taille+1))/2 ),
_tailleTabou(10),
_maxTabouIt(50),
_tabou(taille*taille, 0)
{
    creerContraintes();

    // vector<int> valeurs = {34, 10, 20, 13, 28, 6, 1, 32, 33, 9, 4, 31, 25, 12, 19, 22, 16, 17, 24, 18, 21, 8, 26, 14, 5, 36, 11, 30, 2, 27, 23, 3, 7, 29, 35, 15};

    // vector<int> valeurs = {4, 9, 2, 3, 5, 7, 8, 1, 6};

    // vector<int> valeurs = {16, 3, 2, 13, 5, 10, 11, 8, 9, 6, 7, 12, 4, 15, 14, 1};

    // Configuration config(valeurs, 4);
    // list<Configuration> voisins;
    // config.genererVoisinage(voisins, false);
    //
    // vector<int> scores;
    // for(Configuration& config : voisins) {
    //     scores.push_back(calculerScore(config));
    // }
    // sort(scores.begin(), scores.end());
    // for(int score : scores) {
    //     cout << score << endl;
    // }

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

    list<Configuration> voisinsEgaux; // liste des voisins de même score
    int scoreMinVoisin;

    bool tabou = false;
    int tabouIt;
    int scoreTabou;

    while(continuer) {

        // cout << "jusque là : meilleur score = " << meilleurScore << endl;

        // cout << config.toString() << endl;
        list<Configuration> voisins;
        config.genererVoisinage(voisins, false);

        Configuration voisinMin(_taille);
        scoreMinVoisin = -1;

        // calcul du meilleur voisin
        trouverMeilleurVoisin(config, voisinMin, scoreMinVoisin, tabou, iter);

        // cout << "scoreActuel : " << scoreActuel << endl;
        // cout << "scoreMin voisins : " << scoreMinVoisin << endl;
        // cout << "tabou : " << tabou << "  -  nbIt : " << tabouIt << " score min tabou : " << scoreTabou << endl;

        config = voisinMin;
        // scoreActuel = scoreMinVoisin;

        // si on est très proche d'un min, on peut essayer de renforcer la recherche
        // autour des variables problématiques dans la grille

        if(tabou) {

            tabouIt ++;

            if(scoreMinVoisin < scoreTabou) { // amélioration locale
                scoreTabou = scoreMinVoisin;

                if(scoreTabou < scoreActuel) { // arêt du tabou, un meilleur score a été trouvé
                    tabou = false;
                    scoreActuel = scoreTabou;
                }
            } else {
                if(tabouIt > _maxTabouIt) { // tabou terminé, pas d'amélioration
                    tabou = false;
                    config.regenerer();
                    scoreActuel = calculerScore(config);
                    // cout << endl << endl << "restart!" << endl << endl;
                }
            }

        } else {

            if(scoreMinVoisin < scoreActuel) { // le score est amélioré
                scoreActuel = scoreMinVoisin;

                if(scoreActuel < meilleurScore) {
                    meilleurScore = scoreActuel;
                }

            } else { // min local trouvé, activation du tabou
                if(!tabou) {
                    tabou = true;
                    tabouIt = 0;
                    scoreTabou = scoreActuel;
                }
            }
        }

        if(scoreActuel < meilleurScore) {
            meilleurScore = scoreActuel;
        }

        if(meilleurScore == 0 || iter > 100000) {
            continuer = false;
        }

        iter ++;

    }

    // cout << "meilleur score : " << meilleurScore << endl;



}

/*----------------------------------------------------------------------------*/
void Solver::trouverMeilleurVoisin(Configuration& config, Configuration& voisin, int& scoreVoisin, bool tabou, int iter) {

    int indMax = -1, ind2Max = -1;
    Configuration meilleure(config);
    int meilleurScore = -1;

    int ind = 0, ind2;
    while(ind < _taille*_taille) {

        ind2 = ind+1;
        while(ind2 < _taille*_taille) {

            if(!tabou || (_tabou[ind] <= iter && _tabou[ind2] <= iter)) { // on peut sélectionner ces éléments
                Configuration voisin = config;
                voisin.swap(ind, ind2);
                int score = calculerScore(voisin);

                if(meilleurScore == -1 || score < meilleurScore) {
                    meilleure = voisin;
                    meilleurScore = score;
                    indMax = ind;
                    ind2Max = ind2;
                }
            }
            ind2 ++;
        }
        ind ++;
    }

    if(meilleurScore != -1) { // peut arriver à cause des tabous
        //mise à jour des tabous
        if(tabou) {
            _tabou[indMax] = iter+_tailleTabou;
            _tabou[ind2Max] = iter+_tailleTabou;
        }
        voisin = meilleure;
        scoreVoisin = meilleurScore;

    }

}

/*----------------------------------------------------------------------------*/
int Solver::calculerScore(Configuration& config) {

    int somme = 0;

    for(Contrainte* contrainte : _contraintes) {
        int score = contrainte->score(config);
        somme += score;
    }

    return somme;
}


/*----------------------------------------------------------------------------*/
bool Solver::explorerMinLocal(Configuration& confMin, Configuration confEqui, int& scoreActuel) {

    list<Configuration> interdites;
    interdites.push_back(confMin);

    int it = 0;

    cout << "exploration d'un minimum" << endl;

    bool ameliore = false;

    while(it < 10 && scoreActuel != 0) {

        list<Configuration> voisins;
        confEqui.genererVoisinage(voisins, false);

        int scoreMinVoisin = -1;
        Configuration voisinMin(confMin);
        for(Configuration& voisin : voisins) {

            int score = calculerScore(voisin);
            if(score < scoreActuel) {
                scoreActuel = score;
                voisinMin = voisin;
                // ameliore = true;
                // cout << "amélioration du minimum trouvé" << endl;
            } else {

                if(count(interdites.begin(), interdites.end(), voisin) == 0) {

                    if(scoreMinVoisin == -1 || score < scoreMinVoisin) {
                        scoreMinVoisin = score;
                        voisinMin = voisin;
                    }


                }
            }
        }

        if(scoreMinVoisin == scoreActuel) {
            interdites.push_back(voisinMin);

        }
        scoreActuel = scoreMinVoisin;
        confEqui = voisinMin;

        it ++;
    }

    cout << "fin de l'exploration d'un minimum : nbIteration : " << it << endl;

    return ameliore;
}

/*----------------------------------------------------------------------------*/
Solver::~Solver() {

    for(Contrainte* contrainte : _contraintes) {
        delete contrainte;
    }

}
