/**
 * \file Grille.hpp
 * \brief définition d'une classe Grille qui représente le carré
 */

#ifndef GRILLE_INCOMPLET_HPP
#define GRILLE_INCOMPLET_HPP

#include <vector>
#include <string>

namespace incomplet {

/**
 * \class Grille
 * \brief Grille du carré magique
 */
class Grille {

    public:
        Grille(int taille);

        /**
         * \brief retourne des informations sur la grille sous forme de chaîne de caractère
         * \return la chaîne
         */
        std::string toString();

        /**
         * \brief intervertit deux éléments de la grille et met à jour le score
         */
        void echangeAlea();

        /**
         * \brief annule le dernier mouvement
         * \pre un mouvement aléatoire a été fait avant
         */
        void annulerEchange();

        /**
         * \brief saute vers une configuration voisine en échangeant deux éléments
         * \param elta indice du premier élément
         * \param eltb indice du deuxième élément
         */
        void echange(int elta, int eltb);

        /**
         * \brief réinitialise la grille
         */
        void restart();

        /**
         * \brief score de la grille actuelle
         * \return le score
         */
        int score();

    private: // méthodes provées
        /**
         * \brief intialise la somme des lignes, colonnes et diagonales
         */
        void initialiserSomme();

        /**
         * \brief initialise le score de la grille
         */
        void initialiserScore();

        /**
         * \brief mise à jour du score
         * \param elta indice d'un des éléments permutés
         * \param eltb indice du deuxième élément permuté
         */
        void majScore(int elta, int eltb);

        /**
         * \brief échange deux valeurs de la grille
         * \param elta indice de la première valeur
         * \param eltb indice de la deuxième valeur
         */
        void echangeValeurs(int elta, int eltb);

    private:

        const int _taille;
        const int _magique;
        std::vector<int> _grille;

        std::vector<unsigned int> _sommeLigne; // somme des lignes
        std::vector<unsigned int> _sommeCol; // somme des colonnes
        unsigned int _sommeDiag;
        unsigned int _sommeAntiDiag;

        unsigned int _score; // score de la grille

        int _elta, _eltb; // elements des échanges aléatoires

};

}

#endif /* GRILLE_INCOMPLET_HPP */
