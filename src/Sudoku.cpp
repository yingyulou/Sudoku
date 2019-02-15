/*
    Implementaion of the sudoku calculater.
*/

#include <array>
#include <cstdio>
#include <cstring>

#include "Sudoku.h"

using namespace std;

// Return Bool
bool END = false;

////////////////////////////////////////////////////////////////////////////////
// Show Help Info
////////////////////////////////////////////////////////////////////////////////

void Sudoku::showHelp() const
{
    printf("Usage: \n\n");
    printf("    Step 1: Run 'Sudoku init [sudokuFileName]' to create a new sudoku file. The default filename is 'Sudoku.txt'.\n\n");
    printf("    Step 2: Modify then save the sudoku file.\n\n");
    printf("    Step 3: Run 'Sudoku solve [sudokuFileName]' to solve the sudoku. The default filename is 'Sudoku.txt'.\n\n");
}


////////////////////////////////////////////////////////////////////////////////
// Init Sudoku File
////////////////////////////////////////////////////////////////////////////////

void Sudoku::initSudokuFile(const char *sudokuFileName) const
{
    FILE *fo = fopen(sudokuFileName, "w");

    fprintf(fo, "000 000 000\n000 000 000\n000 000 000\n\n000 000 000\n000 000 000\n000 000 000\n\n000 000 000\n000 000 000\n000 000 000\n");

    fclose(fo);
}


////////////////////////////////////////////////////////////////////////////////
// Parse Sudoku File
////////////////////////////////////////////////////////////////////////////////

void Sudoku::parseSudokuFile(const char *sudokuFileName)
{
    sudokuList = array<array<int, 9>, 9> {};
    rowMark    = array<array<int, 10>, 9> {};
    colMark    = array<array<int, 10>, 9> {};
    fieldMark  = array<array<int, 10>, 9> {};

    FILE *f = fopen(sudokuFileName, "r");
    int x = 0, y = 0, nowNum;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int m = 0; m < 3; m++)
                {
                    nowNum = fgetc(f) - '0';

                    if (nowNum)
                    {
                        markPoint(x, y, nowNum, 1);
                    }

                    y++;
                }

                fgetc(f);
            }

            x++;
            y = 0;
        }

        fgetc(f);
    }

    fclose(f);
}


////////////////////////////////////////////////////////////////////////////////
// Judge A Point
////////////////////////////////////////////////////////////////////////////////

bool Sudoku::judgePoint(int x, int y, int nowNum) const
{
    if (rowMark[x][nowNum] == 0 &&
        colMark[y][nowNum] == 0 &&
        fieldMark[COORD_TO_FIELD[x][y]][nowNum] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


////////////////////////////////////////////////////////////////////////////////
// Mark A Point
////////////////////////////////////////////////////////////////////////////////

void Sudoku::markPoint(int x, int y, int nowNum, int flagNum)
{
    if (flagNum == 0)
    {
        sudokuList[x][y] = 0;
    }
    else
    {
        sudokuList[x][y] = nowNum;
    }

    rowMark[x][nowNum] = flagNum;
    colMark[y][nowNum] = flagNum;
    fieldMark[COORD_TO_FIELD[x][y]][nowNum] = flagNum;
}


////////////////////////////////////////////////////////////////////////////////
// Solve A Point
////////////////////////////////////////////////////////////////////////////////

void Sudoku::solvePoint(int x, int y)
{
    if (x == 9)
    {
        showSudoku();
        END = true;
    }
    else if (y == 9)
    {
        solvePoint(x + 1, 0);
    }
    else if (sudokuList[x][y])
    {
        solvePoint(x, y + 1);
    }
    else
    {
        for (int nowNum = 1; nowNum <= 9; nowNum++)
        {
            if (judgePoint(x, y, nowNum))
            {
                markPoint(x, y, nowNum, 1);
                solvePoint(x, y + 1);

                if (END)
                {
                    return;
                }

                markPoint(x, y, nowNum, 0);
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// Show Sudoku
////////////////////////////////////////////////////////////////////////////////

void Sudoku::showSudoku() const
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", sudokuList[i][j]);
        }

        printf("%d\n", sudokuList[i][8]);
    }
}


////////////////////////////////////////////////////////////////////////////////
// Solve Sudoku
////////////////////////////////////////////////////////////////////////////////

void Sudoku::solveSudoku()
{
    solvePoint(0, 0);
}


////////////////////////////////////////////////////////////////////////////////
// Main Program Define
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    Sudoku s;

    if (argc < 2)
    {
        s.showHelp();
    }
    else if (strcmp(argv[1], "init") == 0)
    {
        if (argc == 3)
        {
            s.initSudokuFile(argv[2]);
        }
        else
        {
            s.initSudokuFile();
        }
    }
    else if (strcmp(argv[1], "solve") == 0)
    {
        if (argc == 3)
        {
            s.parseSudokuFile(argv[2]);
        }
        else
        {
            s.parseSudokuFile();
        }

        s.solveSudoku();
    }
    else
    {
        s.showHelp();
    }

    return 0;
}