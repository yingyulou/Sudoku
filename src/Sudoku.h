/*
    Sudoku
    ======
        A Sudoku calculater for solving the sudoku puzzles.
*/

#ifndef __SUDOKU_H
#define __SUDOKU_H

#include <array>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Coord => Field Array
////////////////////////////////////////////////////////////////////////////////

const array<array<int, 9>, 9> COORD_TO_FIELD
{
    0, 0, 0, 1, 1, 1, 2, 2, 2,
    0, 0, 0, 1, 1, 1, 2, 2, 2,
    0, 0, 0, 1, 1, 1, 2, 2, 2,
    3, 3, 3, 4, 4, 4, 5, 5, 5,
    3, 3, 3, 4, 4, 4, 5, 5, 5,
    3, 3, 3, 4, 4, 4, 5, 5, 5,
    6, 6, 6, 7, 7, 7, 8, 8, 8,
    6, 6, 6, 7, 7, 7, 8, 8, 8,
    6, 6, 6, 7, 7, 7, 8, 8, 8,
};


////////////////////////////////////////////////////////////////////////////////
// Sudoku Class
////////////////////////////////////////////////////////////////////////////////

class Sudoku
{
    private:
        array<array<int, 9>, 9> sudokuList;
        array<array<int, 10>, 9> rowMark;
        array<array<int, 10>, 9> colMark;
        array<array<int, 10>, 9> fieldMark;

    public:
        void showHelp() const;
        void initSudokuFile(const char *sudokuFileName = "Sudoku.txt") const;
        void parseSudokuFile(const char *sudokuFileName = "Sudoku.txt");
        bool judgePoint(int x, int y, int nowNum) const;
        void markPoint(int x, int y, int markNum, int flagNum);
        void solvePoint(int x, int y);
        void showSudoku() const;
        void solveSudoku();
};


#endif