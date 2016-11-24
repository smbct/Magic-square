/**
 * \file CtInf.cpp
 * \brief implémentation de la classe CtInf implémentant une contrainte d'infériorité entre deux variables
 * \author S.B
 * \date 24/11/2016
 */

#include "CtInf.hpp"

using namespace std;
using namespace complet;


//------------------------------------------------------------------------------
CtInf::CtInf(Variable* varGch, Variable* varDte) :
_varGch(varGch),
_varDte(varDte)
{


}

//------------------------------------------------------------------------------
bool CtInf::evaluer() {
    return _varGch->valeur() < _varDte->valeur();
}

//------------------------------------------------------------------------------
bool CtInf::filtrer(std::list<Contrainte*>& aFiltrer, std::map<Variable*, std::list<Contrainte*>>& associees) {

    // tests rapides avec la borne inférieure et la borne supérieure des domaines
    bool res = false;
    if(_varGch->maxDomaine() >= _varDte->minDomaine()) {

        list<int> aEnleverGch, aEnleverDte;
        while(_varGch->affecterOrdre()) {
            if(_varGch->valeur() >= _varDte->maxDomaine()) {
                aEnleverGch.push_back(_varGch->valeur());
            }
        }

        while(_varDte->affecterOrdre()) {
            if(_varDte->valeur() <= _varGch->minDomaine()) {
                aEnleverDte.push_back(_varDte->valeur());
            }
        }

        for(int val : aEnleverGch) {
            _varGch->enleveVal(val);
        }
        for(int val : aEnleverDte) {
            _varDte->enleveVal(val);
        }

        if(_varGch->tailleDomaine() == 0 || _varGch->tailleDomaine() == 0) {
            res = true;
        }

        // mise à jour des contraintes à filtrer en fonction des domaines modifiés
        if(!aEnleverGch.empty()) {
            list<Contrainte*>& contraintes = associees[_varGch];
            for(Contrainte* ct : contraintes) {
                aFiltrer.push_back(ct);
            }
        }
        if(!aEnleverDte.empty()) {
            list<Contrainte*>& contraintes = associees[_varDte];
            for(Contrainte* ct : contraintes) {
                aFiltrer.push_back(ct);
            }
        }
    } else {
        // aucunes valeurs à filtrer
    }

    return res;
}
