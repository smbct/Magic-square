/**
 * \file Grid.cpp
 * \brief Implementation of the class Grid
 */

#include "Grid.hpp"
#include <sstream>
#include <iostream>

using namespace std;

/*----------------------------------------------------------------------------*/
Grid::Grid(int size) :
_size(size),
_magic( (size*(size*size + 1)) / 2  ),
_grid(size*size),
_sumLine(size, 0),
_sumCol(size, 0),
_sumDiag(0),
_sumAntiDiag(0)
{

    /* fill the grid with bad initial solution */
    for(int i = 0; i < _grid.size(); i++) {
        _grid[i] = i+1;
    }

    initSums();
    initScore();
}

/*----------------------------------------------------------------------------*/
void Grid::initSums() {

    for(int i = 0; i < _size; i++) {
        _sumLine[i] = 0;
        _sumCol[i] = 0;
    }
    _sumDiag = 0;
    _sumAntiDiag = 0;

    for(int i = 0; i < _size; i++) {
        for(int j = 0; j < _size; j++) {
            _sumLine[i] += _grid[i*_size+j];
            _sumCol[j] += _grid[i*_size+j];

            if(i == j) {
                _sumDiag += _grid[i*_size+j];
            }

            if(i == _size-j-1) {
                _sumAntiDiag += _grid[i*_size+j];
            }
        }
    }

}

/*----------------------------------------------------------------------------*/
void Grid::updateScore(int elta, int eltb) {

    /* compute index of lines and cols */
    int linea = elta/_size;
    int cola = elta%_size;

    int lineb = eltb/_size;
    int colb = eltb%_size;

    /* update the two lines */
    if(linea != lineb) {

        _score -= (_sumLine[linea]-_magic)*(_sumLine[linea]-_magic);
        _sumLine[linea] += _grid[lineb*_size+colb] - _grid[linea*_size+cola];
        _score += (_sumLine[linea]-_magic)*(_sumLine[linea]-_magic);

        _score -= (_sumLine[lineb]-_magic)*(_sumLine[lineb]-_magic);
        _sumLine[lineb] += _grid[linea*_size+cola] - _grid[lineb*_size+colb];
        _score += (_sumLine[lineb]-_magic)*(_sumLine[lineb]-_magic);
    }

    /* update the two cols */
    if(cola != colb) {

        _score -= (_sumCol[colb]-_magic)*(_sumCol[colb]-_magic);
        _sumCol[colb] += _grid[linea*_size+cola] - _grid[lineb*_size+colb];
        _score += (_sumCol[colb]-_magic)*(_sumCol[colb]-_magic);

        _score -= (_sumCol[cola]-_magic)*(_sumCol[cola]-_magic);
        _sumCol[cola] += _grid[lineb*_size+colb] - _grid[linea*_size+cola];
        _score += (_sumCol[cola]-_magic)*(_sumCol[cola]-_magic);
    }

    /* the diagonal has been changed */
    if(linea == cola && lineb != colb) {
        _score -= (_sumDiag-_magic)*(_sumDiag-_magic);
        _sumDiag += _grid[lineb*_size+colb] - _grid[linea*_size+cola];
        _score += (_sumDiag-_magic)*(_sumDiag-_magic);
    }
    if(lineb == colb && linea != cola) {
        _score -= (_sumDiag-_magic)*(_sumDiag-_magic);
        _sumDiag += _grid[linea*_size+cola] - _grid[lineb*_size+colb];
        _score += (_sumDiag-_magic)*(_sumDiag-_magic);
    }

    /* the anti diagonal has been changed */
    if(linea == _size-cola-1 && lineb != _size-colb-1) {
        _score -= (_sumAntiDiag-_magic)*(_sumAntiDiag-_magic);
        _sumAntiDiag += _grid[lineb*_size+colb] - _grid[linea*_size+cola];
        _score += (_sumAntiDiag-_magic)*(_sumAntiDiag-_magic);
    }
    if(lineb == _size-colb-1 && linea != _size-cola-1) {
        _score -= (_sumAntiDiag-_magic)*(_sumAntiDiag-_magic);
        _sumAntiDiag += _grid[linea*_size+cola] - _grid[lineb*_size+colb];
        _score += (_sumAntiDiag-_magic)*(_sumAntiDiag-_magic);
    }

}

/*----------------------------------------------------------------------------*/
string Grid::toString() {

    string res = "";

    for(int i = 0; i < _size; i++) {
        for(int j = 0; j < _size; j++) {
            ostringstream oss;
            oss << _grid[i*_size+j];
            res += oss.str();
            if(j < _size-1) {
                res += " ";
            }
        }
        res += "\n";
    }

    return res;
}

/*----------------------------------------------------------------------------*/
void Grid::move(int elta, int eltb) {

    updateScore(elta, eltb);
    swapValues(elta, eltb);

}

/*----------------------------------------------------------------------------*/
void Grid::randomMove() {

    int elta;
    int eltb;

    elta = rand()%(_size*_size);
    eltb = rand()%(_size*_size);

    move(elta, eltb);
    _elta = elta;
    _eltb = eltb;
}

/*----------------------------------------------------------------------------*/
void Grid::cancelMove() {
    move(_eltb, _elta);
}

/*----------------------------------------------------------------------------*/
void Grid::swapValues(int elta, int eltb) {
    int temp = _grid[elta];
    _grid[elta] = _grid[eltb];
    _grid[eltb] = temp;
}

/*----------------------------------------------------------------------------*/
void Grid::initScore() {

    _score = 0;
    for(unsigned int& sum : _sumLine) {
        _score += (sum-_magic)*(sum-_magic);
    }
    for(unsigned int& sum : _sumCol) {
        _score += (sum-_magic)*(sum-_magic);
    }
    _score += (_sumDiag-_magic)*(_sumDiag-_magic);
    _score += (_sumAntiDiag-_magic)*(_sumAntiDiag-_magic);

}

/*----------------------------------------------------------------------------*/
int Grid::score() {

    return _score;
}
