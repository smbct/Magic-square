#include <iostream>
#include <ctime>

#include "Incomplet/Solver.hpp"
#include "Complet/Solver.hpp"

using namespace std;


/*----------------------------------------------------------------------------*/
void afficherMenu() {

    cout << "Veuillez choisir le solver pour le résoudre : " << endl;
    cout << "\tSolver complet : 1" << endl;
    cout << "\tSolver incomplet (recherche locale) : 2" << endl;
    cout << "\tSolver incomplet (recuit simulé et tabou): 3" << endl;
    cout << "\tQuitter le programme : 4" << endl;

}

/*----------------------------------------------------------------------------*/
int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    clock_t begin = 0, end = 0;
    double elapsed_secs;

    cout << "temps écoulé : " << elapsed_secs << endl;

    unsigned int taille = 0, choix = 0;

    cout << "Bienvenue dans le solver du problèmes du carré magique !" << endl << endl;
    cout << "Veuillez entrer la taille du carré à résoudre : ";
    cin >> taille;
    cout << endl;

    do {

        afficherMenu();

        cout << endl << "Votre choix : ";
        cin >> choix;

        if(choix > 4 || choix < 1) {
            cout << "Oups, ce choix n'est pas valide :/" << endl;
        }

    } while(choix > 4 || choix < 1);

    switch(choix) {
        case 1:
            {
                complet::Solver solver(taille);
                begin = clock();
                solver.resoudre();
                end = clock();
            }
            break;
        case 2:
            {
                incomplet::Solver solver(taille);
                begin = clock();
                solver.solve();
                end = clock();
            }
            break;
        case 3:
            {
                incomplet::Solver solver(taille);
                begin = clock();
                solver.solverRecuit();
                end = clock();
            }
            break;
        default:
            break;
    }

    if(choix > 0 && choix < 4) {
        elapsed_secs = double(end-begin) / CLOCKS_PER_SEC;
        cout << "La résolution s'est terminée en " << elapsed_secs << " secondes" << endl;
    }

    return 0;
}
