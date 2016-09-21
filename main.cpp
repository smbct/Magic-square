#include <iostream>

#include "Variable.hpp"

using namespace std;

int main() {

    int size = 3;

    /*cout << "entrer la taille de la grille : ";
    cin >> size;*/

    cout << "La grille est de taille " << size << " * " << size << endl;

    Variable variable(1, size*size);

    cout << "au début : " << variable.toString() << endl;

    variable.sauvegardeDomaine();
    for(int i = 1; i < 4; i++) {
        variable.enleveVal(i);
    }

    cout << "après suppression : " << variable.toString() << endl;

    variable.restoreDomaine();

    cout << "après restoration : " << variable.toString() << endl;

    return 0;
}
