#include <iostream>

#include "Variable.hpp"
#include "CtAllDiff.hpp"
#include "CtSomme.hpp"
#include "Solver.hpp"

#include <vector>

#include <ctime>

using namespace std;

int main() {

    int size = 3;

    /*cout << "entrer la taille de la grille : ";
    cin >> size;*/

    // cout << "La grille est de taille " << size << " * " << size << endl;

    Solver solver(3);

    clock_t begin = clock();
    solver.resoudre();
    clock_t end = clock();
    double elapsed_secs = double(end-begin)/ CLOCKS_PER_SEC;

    cout << "temps écoulé : " << elapsed_secs << endl;

    /*int M = (size * (size*size + 1)) / 2;
    vector<Contrainte*> contraintes(2*size+3);
    for(int i = 0; i < 2*size + 2; i++) {
        contraintes[i] = new CtSomme(M);
    }
    contraintes.back() = new CtAllDiff();

    list<Variable*> variables;

    for(int l = 0; l < size; l++) {
        for(int col = 0; col < size; col ++) {
            Variable* var = new Variable(1, size*size);
            variables.push_back(var);

            contraintes[l]->ajouterVariable(var);
            contraintes[size + col]->ajouterVariable(var);
            contraintes.back()->ajouterVariable(var);

            if(l == col) {
                contraintes[2*size]->ajouterVariable(var);
            }
            if(l == size-col-1) {
                contraintes[2*size+1]->ajouterVariable(var);
            }
        }
    }

    for(Variable* variable : variables) {
        variable->sauvegardeDomaine();
    }

    variables.front()->affecter();
    variables.front()->affecter();
    variables.front()->affecter();

    bool filtrer = true;
    while(filtrer) {
        filtrer = false;

        for(auto it = contraintes.begin(); it != contraintes.end(); it ++) {
            if((*it)->filtrer()) {
                filtrer = true;
            }
        }
    }

    int ind = 0;
    for(Variable* var : variables) {
        cout << "Variable " << ind << " : " << var->toString() << endl;
        ind ++;
    }

    for(Contrainte* ctr : contraintes) {
        delete ctr;
    }
    for(Variable* var : variables) {
        delete var;
    }*/

    return 0;
}
