/**
 * \file Solver.cpp
 * \brief implémentation de la classe Solver
 */

#include "Solver.hpp"

#include <iostream>
#include <cmath>

#include <fstream>

using namespace std;
using namespace incomplet;

/*----------------------------------------------------------------------------*/
Solver::Solver(int taille) :
_taille(taille)
{


}

/*----------------------------------------------------------------------------*/
void Solver::solve() {

    Grille grille(_taille);
    int nbRestart = 0;

    do {

        rechercheLocale(grille);

        if(grille.score() > 0) {
            grille.restart();
            nbRestart ++;
            cout << "nombre de restart : " << nbRestart << endl;
        }

    } while(grille.score() != 0 && nbRestart < 500);

    if(grille.score() > 0) {
        cout << "La recherche locale n'a pas encore trouvée de solution, lancement de la recherche tabou." << endl;
        recherchTabou(grille);
    }

    cout << "résultat de la résolution" << endl;
    cout << "score : " << grille.score() << endl;
    cout << grille.toString() << endl;

}

/*----------------------------------------------------------------------------*/
void Solver::rechercheLocale(Grille& grille) {

    /* exécute une simple recherche locale */

    bool stop = false;
    int scoreMin = grille.score();

    while(!stop) {

        int eltaMin = -1, eltbMin = -1;
        int scoreVoisin = -1;

        for(int i = 0; i < _taille*_taille; i++) {
            for(int j = i+1; j < _taille*_taille; j++) {

                grille.echange(i, j);

                if(scoreVoisin == -1 || grille.score() < scoreVoisin) {
                    scoreVoisin = grille.score();
                    eltaMin = i;
                    eltbMin = j;
                }

                grille.echange(j, i); /* annule l'échange */
            }
        }
        if(scoreVoisin < scoreMin) {
            scoreMin = scoreVoisin;
            grille.echange(eltaMin, eltbMin);
        } else {
            stop = true;
        }

    }

}


/*----------------------------------------------------------------------------*/
void Solver::solverRecuit() {

    Grille grille(_taille);

    double T0 = 100; /* température initiale */
    double T = T0; /* la température actuelle */
    int L = 50; /* nombre d'itération pour une température constante */
    double alpha = 0.84; /* coefficient de refroidissement */

    int nbItMax = 100;

    int it = 1;
    bool stop = false;

    unsigned int scoreMin = grille.score();

    ofstream fichier("expe.dat");

    while(!stop) {

        int delta = -grille.score();

        grille.echangeAlea(); /* voisin aléatoire */
        delta += grille.score();

        bool accepte = false;
        if(delta < 0) {
            accepte = true;
        } else {
            double limite = exp(-(double)delta/T);
            double choixAlea = (rand()%100)/100.;

            if(choixAlea < limite) {
                accepte = true;
            }
        }

        if(accepte) {

            fichier << it << " " << grille.score() << " " << scoreMin << endl;

            if(grille.score() == 0) {
                stop = true;
            }
            if(grille.score() < scoreMin) {
                scoreMin = grille.score();

                // cout << "score : " << scoreMin << endl;

                if(grille.score() <= 10) {
                    // cout << "tabuMode" << endl << endl;
                    recherchTabou(grille);
                    if(grille.score() == 0) {
                        stop = true;
                    }
                }
            }
        } else {
            grille.annulerEchange();
        }

        it ++;

        if(it % L == 0) { // update temperature
            T *= alpha;
        }

        if(T < 1e-20) {
            T = T0;
            if(T0 > 1) {
                T0 *= 0.4;
            }
            if(L < 1e12) {
                L *= 1.5;
            }
        }

    }

    fichier.close();

    cout << "it : " << it << endl;

    cout << "meilleur score trouvé : " << grille.score() << endl;
    cout << grille.toString() << endl;

}

/*----------------------------------------------------------------------------*/
void Solver::recherchTabou(Grille& grille) {

    const int longueurTabou = 7;
    vector<vector<int>> listeTabou(_taille*_taille);
    for(int i = 0; i < _taille*_taille; i++) {
        listeTabou[i].resize(_taille*_taille, 1);
    }


    bool stop = false;
    int nbIt = 1;

    int meilleurScore = grille.score();

    while(!stop) {

        int eltaMin, eltbMin;
        unsigned int scoreVoisin = -1;

        /* recherche locale : exploration de tous les voisins */
        for(int i = 0; i < _taille*_taille; i++) {
            for(int j = i+1; j < _taille*_taille; j++) {

                /* si l'échange n'est pas tabou, on peut l'essayer */
                if(listeTabou[i][j] <= nbIt || grille.score() < meilleurScore) {
                    grille.echange(i, j);
                    if(scoreVoisin == -1 || grille.score() < scoreVoisin) {
                        scoreVoisin = grille.score();
                        eltaMin = i;
                        eltbMin = j;
                    }
                    grille.echange(j, i); /* annulation de l'échange */
                }

            }
        }

        if(scoreVoisin != -1) {

            grille.echange(eltaMin, eltbMin);
            listeTabou[eltaMin][eltbMin] = nbIt + longueurTabou;

            if(grille.score() == 0) {
                stop = true;
            }

            if(grille.score() < meilleurScore) {
                meilleurScore = grille.score();
            }

            // cout << "tabu score : " << grid.score() << endl;

        } else {
            stop = true;
        }

        nbIt ++;
    }

    cout << "meilleur trouvé : " << grille.score() << endl;

}
