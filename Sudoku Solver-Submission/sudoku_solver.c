#include <stdio.h>
#include "sudoku.h"

enum solve_output solve(Sudoku* sudoku, int n)
{
    int square = n * n;
    int found = 0;
    //check if the sudoku is valid, invalid or incomplete
    enum check_output check_output1 = check_sudoku(sudoku->puzzle, n);
    //set default value of solve_output to UNSOLVABLE
    enum solve_output solve_output1 = UNSOLVABLE;
    //return if sudoku invalid
    if(check_output1 == INVALID)
    {
        return UNSOLVABLE;
    }
    //return if sudoku complete
    if(check_output1 == COMPLETE)
    {
        return SOLVED;
    }
    //make a new sudoku to be used for the copies
    Sudoku newSudoku = *sudoku;
    int** correctPuzzle = NULL;
    //get the position of the first zero
    int zeroRow = -1;
    int zeroCol = -1;
    for (int i = 0; i < square; ++i) {
        for (int j = 0; j < square; ++j) {
            if(sudoku->puzzle[i][j] == 0)
            {
                //first zero found, so stop searching
                zeroRow = i;
                zeroCol = j;
                found = 1;
                break;
            }
        }
        if(found)
        {
            found = 0;
            break;
        }
    }
    if (zeroRow != -1)
    {
        //loop over all possible values
        for (int i = 1; i <= square; ++i) {
            //only go on if the value is valid in that position
            if(check_num(sudoku->puzzle, zeroRow, zeroCol, i, n) != INVALID)
            {
                //make a copy of the sudoku
                newSudoku.puzzle = copySudoku(sudoku->puzzle, n);
                newSudoku.puzzle[zeroRow][zeroCol] = i;
                //recursive call with the value in the cell, to try and find other solutions
                solve_output1 = solve(&newSudoku, n);
                //return if multiple
                if(solve_output1 == MULTIPLE)
                {
                    return MULTIPLE;
                }
                if(solve_output1 == SOLVED)
                {
                    //if found is 1 (true), a solution has already been found, so return multiple
                    if(found)
                    {
                        return MULTIPLE;
                    }
                    else
                    {
                        //assign found to 1 (true) and assign the correct puzzle to current puzzle
                        found = 1;
                        correctPuzzle = copySudoku(newSudoku.puzzle, n);
                    }
                }
            }
        }
    }
    //if a correct puzzle has been assigned
    if (correctPuzzle)
    {
        //assign the correct puzzle to the sudoku
        sudoku->puzzle = copySudoku(correctPuzzle, n);
        return SOLVED;
    }
    //if no correct puzzle was found, solve_output1 will still be assigned to UNSOLVABLE
    return solve_output1;
}

