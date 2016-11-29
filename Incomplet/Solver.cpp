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

    /* tant que la solution n'a pas été trouvée et que le nombre de restart n'est pas trop important, une recherche locale est effectuée */
    do {

        rechercheLocale(grille);

        /* si à l'issue de la recherche locale une solution n'a pas été trouvée, un restart est effectué */
        if(grille.score() > 0) {
            grille.restart();
            nbRestart ++;
            cout << "nombre de restart : " << nbRestart << endl;
        }

    } while(grille.score() != 0 && nbRestart < 500);

    /* si la solution n'a toujours pas été trouvée, une recherche tabou est exécutée */
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

    /* tant qu'un voisin améliore le score, la recherche continue */
    while(!stop) {

        int eltaMin = -1, eltbMin = -1;
        int scoreVoisin = -1;

        /* calcul chaque permutation de deux éléments */
        for(int i = 0; i < _taille*_taille; i++) {
            for(int j = i+1; j < _taille*_taille; j++) {

                /* effectue la permutation */
                grille.echange(i, j);

                /* le meilleur score des voisins est retenu */
                if(scoreVoisin == -1 || static_cast<int>(grille.score()) < scoreVoisin) {
                    scoreVoisin = grille.score();
                    /* les élements permutés sont retenus pour retrouver la permutation */
                    eltaMin = i;
                    eltbMin = j;
                }

                /* l'échange est annulé pour procéder aux autres échanges */
                grille.echange(j, i);
            }
        }

        /* si un voisin avait un meilleur score, le score est mis à jour et la recherche continue, sinon la recherche s'arrête */
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

    int it = 1;
    bool stop = false;

    unsigned int scoreMin = grille.score();

    ofstream fichier("expe.dat");

    while(!stop) {

        int delta = -grille.score();

        grille.echangeAlea(); /* voisin aléatoire */
        delta += grille.score();

        /* calcul de la proba d'acceptation du voisin */

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

                /* si le score est assez petit, l'algorithme termine par une recherche tabou, pour grater vers la solution */
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

        /* la température est mise à jour */
        if(it % L == 0) {
            T *= alpha;
        }

        /* si la température est trop basse, un réchauffement est effectué */
        if(T < 1e-20) {
            T = T0;
            if(T0 > 1) {
                T0 *= 0.4;
            }
            if(L < 1e12) {
                L = static_cast<int> (static_cast<double>(L) * 1.5);
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

    /* longueur tabou classique */
    const int longueurTabou = 7;

    /* initialisation de la liste tabou */
    vector<vector<unsigned int>> listeTabou(_taille*_taille);
    for(int i = 0; i < _taille*_taille; i++) {
        listeTabou[i].resize(_taille*_taille, 1);
    }


    bool stop = false;
    unsigned int nbIt = 1;

    unsigned int meilleurScore = grille.score();

    while(!stop) {

        int eltaMin, eltbMin;
        int scoreVoisin = -1;

        /* recherche locale : exploration de tous les voisins */
        for(int i = 0; i < _taille*_taille; i++) {
            for(int j = i+1; j < _taille*_taille; j++) {

                /* si l'échange n'est pas tabou, on peut l'essayer */
                if(listeTabou[i][j] <= nbIt || grille.score() < meilleurScore) {
                    grille.echange(i, j);
                    if(scoreVoisin == -1 || static_cast<int>(grille.score()) < scoreVoisin) {
                        scoreVoisin = grille.score();
                        eltaMin = i;
                        eltbMin = j;
                    }
                    grille.echange(j, i); /* annulation de l'échange */
                }

            }
        }

        if(scoreVoisin != -1) {

            /* on bascule vers la configuration du voisin non tabou ayant le meilleur score */
            grille.echange(eltaMin, eltbMin);
            listeTabou[eltaMin][eltbMin] = nbIt + longueurTabou;

            /* si le score est de 0, la recherche s'arrête */
            if(grille.score() == 0) {
                stop = true;
            }

            if(grille.score() < meilleurScore) {
                meilleurScore = grille.score();
            }

        } else {
            /* si tous les éléments sont tabous, il n'y a plus de voisin à explorer, la recherche s'arrête */
            stop = true;
        }

        nbIt ++;
    }

    cout << "meilleur trouvé : " << grille.score() << endl;

}
