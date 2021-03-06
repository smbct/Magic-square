/**
 * \file Configuration.hpp
 * \brief déclaration de la classe Configuration (incomplet)
 * \author S.B
 * \date 26/09/2016
 */

#ifndef CONFIGURATION_INCOMPLET_PREMIER_HPP
#define CONFIGURATION_INCOMPLET_PREMIER_HPP

#include <vector>
#include <list>
#include <string>

namespace incomplet_premier {

/**
 * \class Configuration
 * \brief représente une configuration des variables du problème
 */
class Configuration {

    public:

        /**
         * \brief constructeur
         */
        Configuration(int taille);

        /**
         * \brief construction à partir d'une liste de valeur
         * \param valeurs les valeurs de la configuration à construire
         * \param taille la taille du problème
         */
        Configuration(std::vector<int>& valeurs, int taille);

        /**
         * \brief génère le voisinage d'une configuration
         * \param voisinage la liste des voisins créés
         * \param etendre indique s'il faut générer un voisinage étendu ou non
         */
        void genererVoisinage(std::list<Configuration>& voisinage, bool etendre);

        /**
         * \brief retourne la valeur de la variable ind dans la configuration
         * \param ind l'indice de la variable
         */
        int operator()(int ind);

        /**
         * \brief génération d'une configuration initiale
         */
        void generer();

        /**
         * \brief regénère une configuration à partir de la configuration actuelle
         */
        void regenerer();

        /**
         * \brief retourne les valeurs de la configuration
         * \return la chaîne contenant ces informations
         */
        std::string toString();

        /**
         * \brief échange deux valeurs dans la configuration
         * \ind1 l'indice de la première valeur à échanger
         * \ind2 l'indice de la deuxième valeur à échanger
         */
        void swap(int ind1, int ind2);

        /**
         * \brief indique si les deux configurations sont égales
         * \return vrai ssi les deux configurations sont égales
         */
        bool operator==(const Configuration& autre);

    private: // méthodes privées

        /**
         * \brief génération d'affectations de lignes vérifiant les contraintes de somme
         * \param valeurs les valeurs restant à placer dans la grille
         * \param lignes les lignes valides générées
         */
        void genererLignesValides(std::list<int>& valeurs, std::list<std::list<int>>& lignes);

        /**
         * \brief recherche _taille valeurs telles que leur somme soit égale à M
         * \param valeurs les valeurs disponibles
         * \param lihne la liste si elle a pu être créée
         * \return vrai ssi les valeurs ont été trouvées
         */
        bool trouverEgalite(std::list<int>& valeurs, std::list<int>& ligne);

        /**
         * \brief infique si toutes les valeurs de la liste sont différentes
         * \param valeurs la liste des itérateurs vers les valeurs à tester
         * \return vrai ssi toutes les valeurs pointées par les itérateurs sont différentes
         */
        bool allDifferent(std::list< std::list<int>::iterator >& valeurs);

        /**
         * \brief inversion d'une ligne du carré magique
         * \pre 0 <= ligne < _taille
         */
        void inverserLigne(int ligne);

        /**
         * \brief inversione d'une colonne du carré magique
         * \pre 0 <= colonne < _taille
         */
        void inverserColonne(int colonne);

        /**
         * \brief inversion de la diagonale
         */
        void inverserDiagonale();

        /**
         * \brief inversione de l'antidiagonale
         */
        void inverserAntiDiagonale();

        /**
         * \brief echange d'une ligne avec une colonne
         * \param ligne la ligne à échanger
         * \param col la colonne à échanger
         */
        void echangerLigneColonne(int ligne, int col);

    private: // attributs privés

        int _taille;
        int _max; // valeur maximale prises par les variables
        int _ctr; // membre de droite des contraintes de somme
        std::vector<int> _valeurs;

};

}

#endif // CONFIGURATION_INCOMPLET_PREMIER_HPP
