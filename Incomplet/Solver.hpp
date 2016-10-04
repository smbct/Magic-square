/**
 * \file Solver.hpp
 * \brief déclaration de la classe solver (incomplet)
 * \author S.B
 * \date 26/09/2016
 */

#ifndef SOLVER_INCOMPLET_HPP
#define SOLVER_INCOMPLET_HPP

#include "Contrainte.hpp"
#include "Configuration.hpp"

namespace incomplet {

/**
 *\class Solver
 *\brief classe représenter le solver incomplet du carré magique
 */
class Solver {

    public:

        /**
         * \brief constructeur
         * \param taille largeur de la grille
         */
        Solver(int taille);

        /**
         * \brief tente de résoudre la grille du carré magique
         */
        void resoudre();

        /**
         * \brief destructeur, libère la mémoire
         */
        ~Solver();

    private: // méthodes privées

        /**
         * \brief création des contraintes du problème
         */
        void creerContraintes();

        /**
         * \brief calcule le score d'une configuration
         * \param config la config à tester
         * \return le score de la configuration
         */
        int calculerScore(Configuration& configs);

        /**
         * \brief explore un minimum local pour tenter d'en sortir
         * \param confMin la configuration du min
         * \param confEqui la configuration pour en sortir, qui a le même score
         * \param scoreActuel le score des deux configurations
         */
        bool explorerMinLocal(Configuration& confMin, Configuration confEqui, int& scoreActuel);

        /**
         * \brief recherche du meilleu voisin d'une configuration
         * \param config la configuration étudiée
         * \param voisin le meilleur voisin retourné
         * \param scoreVoisin le score du meilleur voisin trouvé
         * \param tabou vrai ssi le tabou est activé
         * \param iter le nb d'itération de l'algorithme
         */
        void trouverMeilleurVoisin(Configuration& config, Configuration& voisin, int& scoreVoisin, bool tabou, int iter);

    private: // attributs privés

        int _taille;
        int _M;
        std::list<Contrainte*> _contraintes;
        const int _tailleTabou;
        const int _maxTabouIt; // nombre d'itération maxi autorisé dans un min local pour en sortir
        std::vector<int> _tabou; // liste tabou, mouvements interdits

};


}

#endif // SOLVER_INCOMPLET_HPP
