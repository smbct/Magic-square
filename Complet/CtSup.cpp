/**
 * \file CtSup.cpp
 * \brief implémentation de la classe CtSup implémentant une contrainte de supériorité entre deux variables
 * \author S.B
 * \date 24/11/2016
 */

#include "CtSup.hpp"

using namespace std;
using namespace complet;


//------------------------------------------------------------------------------
CtSup::CtSup(Variable* varGch, Variable* varDte) :
_varGch(varGch),
_varDte(varDte)
{


}

//------------------------------------------------------------------------------
bool CtSup::evaluer() {
    return _varGch->valeur() < _varDte->valeur();
}

//------------------------------------------------------------------------------
bool CtSup::filtrer(std::list<Contrainte*>& aFiltrer, std::map<Variable*, std::list<Contrainte*>>& associees) {

    // tests rapides avec la borne inférieure et la borne supérieure des domaines

    if(_varGch->maxDomaine() >= _varDte->minDomaine()) {

        /*while(_varGch->affecterOrdre()) {

        }*/


    } else {
        // aucunes valeurs à filtrer
    }

}
