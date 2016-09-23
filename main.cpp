#include <iostream>

#include "Variable.hpp"
#include "CtAllDiff.hpp"
#include "CtSomme.hpp"

#include <vector>

using namespace std;

int main() {

    int size = 3;

    /*cout << "entrer la taille de la grille : ";
    cin >> size;*/

    // cout << "La grille est de taille " << size << " * " << size << endl;

    Variable variable(1, size*size);

    /*cout << "au début : " << variable.toString() << endl;

    variable.sauvegardeDomaine();
    for(int i = 1; i < 4; i++) {
        variable.enleveVal(i);
    }

    cout << "après suppression : " << variable.toString() << endl;

    variable.restoreDomaine();

    cout << "après restoration : " << variable.toString() << endl;*/

    Variable var2(1, size*size);

    CtAllDiff contrainte;
    contrainte.ajouterVariable(&variable);
    contrainte.ajouterVariable(&var2);

    /*variable.sauvegardeDomaine();
    var2.sauvegardeDomaine();

    cout << "domaine variable 2 : " << var2.toString() << endl << endl;

    cout << "variable 1 affectée" << endl << endl;
    if(variable.affecter()) {

        cout << "filtrage de la contrainte" << endl;
        if(contrainte.filtrer()) {
            cout << "le filtrage est un succes" << endl;
            cout << "domaine de la variable 2 : " << var2.toString() << endl << endl;
        }

    }

    cout << "backtracking" << endl;
    variable.restoreDomaine();
    var2.restoreDomaine();
    cout << "domaine de la variable 2 : " << var2.toString() << endl;*/

    cout << "tentative de deux affectations" << endl;
    if(variable.affecter() && var2.affecter()) {
        cout << "valeurs : " << variable.valeur() << " ; " << var2.valeur() << endl;
        cout << "Contrainte respectée ? " << contrainte.evaluer() << endl;
    }

    CtSomme cont((size*(size*size+1))/2);

    vector<Variable*> var(3);
    for(Variable*& variable : var) {
        variable = new Variable(1, size*size);
        cont.ajouterVariable(variable);
        variable->sauvegardeDomaine();
    }

    for(int i = 1; i <= 2; i++) {
        var[0]->affecter();
    }
    for(int i = 1; i <= 6; i++) {
        var[1]->affecter();
    }

    cout << "filtrage : " << cont.filtrer() << endl;
    cout << "domaine après filtrage : " << var[2]->toString() << endl;


    for(Variable* variable : var) {
        delete variable;
    }

    return 0;
}
