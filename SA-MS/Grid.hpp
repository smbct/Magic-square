/**
 * \file Grid.hpp
 * \brief definition of a class Grid that represent the square
 */

#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>

/**
 * \class Grid
 * \brief Grid of the magic square
 */
class Grid {

    public:
        Grid(int size);

        /**
         * \brief return the informations of the grid in a string
         * \return the string
         */
        std::string toString();

        /**
         * \brief swap two random cells in the grid and update the score
         */
        void randomMove();

        /**
         * \brief cancel last random move
         * \pre a random move has been done
         */
        void cancelMove();

        /**
         * \brief jump to a neghbour by swaping two values
         * \param elta index of the first value
         * \param eltb index of the second value
         */
        void move(int elta, int eltb);

        /**
         * \brief score of the actual grid
         * \return the score
         */
        int score();

    private: // private methods

        /**
         * \brief init the sum of all lines cols ent diagonals
         */
        void initSums();

        /**
         * \brief init the score of the grid
         */
        void initScore();

        /**
         * \brief update the score
         * \param elta index of one of the elements swaped
         * \param eltb index of the other element
         */
        void updateScore(int elta, int eltb);

        /**
         * \brief swap two values in the grid
         * \param elta index of the first value
         * \param eltb index of the 2nd value
         */
        void swapValues(int elta, int eltb);

    private:

        const int _size;
        const int _magic;
        std::vector<int> _grid;

        std::vector<unsigned int> _sumLine; // sum of lines
        std::vector<unsigned int> _sumCol; // sum of cols
        unsigned int _sumDiag;
        unsigned int _sumAntiDiag;

        unsigned int _score; // score of this grid

        int _elta, _eltb; // elements of the random move

};

#endif /* GRID_HPP */
