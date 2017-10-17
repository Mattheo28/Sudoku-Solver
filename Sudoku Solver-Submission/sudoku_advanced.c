#include <stdio.h>
#include "sudoku.h"

//return the valid num for a given cell, return -1 if more than one found
int findValidNums(int **puzzle, int row, int col, int n) {
    int square = n * n;
    int validNum = 0;
    for (int i = 1; i <= square; i++) {
        if (check_num(puzzle, row, col, i, n) != INVALID) {
            //return -1 if we already have a valid num
            if (validNum) {
                return -1;
            } else {
                validNum = i;
            }
        }
    }
    return validNum;
}

//function which tries to fill in the sudoku by assigning cells that could only have 1 value
// and returns the number of cells it has filled in
int solve_cells(Sudoku *sudoku, int n)
{
    int square = n * n;
    int value = 0;
    int numOfEdits = 0;
    for (int i = 0; i < square; i++) {
        for (int j = 0; j < square; j++) {
            //if the current cell is one that needs to be filled in
            if (sudoku->puzzle[i][j] == 0) {
                //find the valid number for the cell
                value = findValidNums(sudoku->puzzle, i, j, n);
                switch (value) {
                    case -1:
                        //not found
                        break;
                    case 0:
                        //if no num was found, sudoku is invalid
                        return -(n * n * n * n);
                    default:
                        sudoku->puzzle[i][j] = value;
                        numOfEdits++;
                }
            }
        }
    }
    return numOfEdits;
}

int solve_box(Sudoku *sudoku, int n) {
    int square = n * n;
    int possiblePlaces = 0;
    int possibleRow = 0;
    int possibleCol = 0;
    //flag to show that the current number was found in the box
    int foundCurrentNum = 0;
    int numOfEdits = 0;
    //array which holds all the numbers not found in a box
    int numsNotFound[square];

    //assign all the values of the array to 0
    for (int i = 0; i < square; ++i) {
        numsNotFound[i] = 0;
    }

    //outer loop increments number for box offset, the number of the box we are going to search
    for (int boxOffset = 0; boxOffset < square; ++boxOffset) {
	//for each box, we must have all numbers from 1 to square
        for (int possibleNum = 1; possibleNum <= square; ++possibleNum) {
            foundCurrentNum = 0;
	    //each box has 3 rows and 3 columns
            for (int row = 0; row < n; ++row) {
                for (int col = 0; col < n; ++col) {
                    //if the current num is found in the column set flag to true and break
                    if (sudoku->puzzle[row + (n * (boxOffset / n))]
                        [col + (n * (boxOffset % n))] == possibleNum) {
                        foundCurrentNum = 1;
                        break;
                    }
                }
                if (foundCurrentNum) {
                    break;
                }
            }
            //if num wasn't found, store in array
            if (!foundCurrentNum) {
                numsNotFound[possibleNum - 1] = possibleNum;
            }
        }
        //start again for given box
        for (int possibleNum = 1; possibleNum <= square; ++possibleNum) {
            possiblePlaces = 0;
            //if the possible num is in the array (so it wasn't found)
            if (numsNotFound[possibleNum - 1] == possibleNum) {
                for (int row = 0; row < n; ++row) {
                    for (int col = 0; col < n; ++col) {
                        //try find a possible place for the num
                        if (sudoku->puzzle[row + (n * (boxOffset / n))]
                            [col + (n * (boxOffset % n))] == 0) {
                            //check if the num is valid in the given position
                            if (check_num(sudoku->puzzle, row + (n * (boxOffset / n)),
                                           col + (n * (boxOffset % n)), possibleNum, n) != INVALID) {
                                possiblePlaces++;
                                possibleRow = row + (n * (boxOffset / n));
                                possibleCol = col + (n * (boxOffset % n));
                            }
                        }
                    }
                }
            }
            //if more than one places were found, discard and go to next num
            if (possiblePlaces == 1) {
                sudoku->puzzle[possibleRow][possibleCol] = possibleNum;
                numOfEdits++;
            }
        }
    }
    return numOfEdits;
}

//function which tries to fill in the sudoku by filling in cells by possible values within a row
// and returns the number of cells it has filled in
int solve_row(Sudoku *sudoku, int n) {
    int square = n * n;
    int possiblePlaces = 0;
    int possibleRow = 0;
    int possibleCol = 0;
    //flag to show that the current number was found in the row
    int foundCurrentNum = 0;
    int numOfEdits = 0;
    //array which holds all the numbers not found in a row
    int numsNotFound[square];

    //assign all the values of the array to 0
    for (int i = 0; i < square; ++i) {
        numsNotFound[i] = 0;
    }

    //outer loop increments row number
    for (int row = 0; row < square; ++row) {
        //for each new row, square number of possible nums
        for (int possibleNum = 1; possibleNum <= square; ++possibleNum) {
            //reset flag to 0 (false)
            foundCurrentNum = 0;
            //inner loop increments column number
            for (int col = 0; col < square; ++col) {
                //if the current num is found in the column set flag to true and break
                if (sudoku->puzzle[row][col] == possibleNum) {
                    foundCurrentNum = 1;
                    break;
                }
            }
            //if num wasn't found, store in array
            if (!foundCurrentNum) {
                numsNotFound[possibleNum - 1] = possibleNum;
            }
        }
        //start again for given row
        for (int possibleNum = 1; possibleNum <= square; ++possibleNum) {
            possiblePlaces = 0;
            //if the possible num is in the array (so it wasn't found)
            if (numsNotFound[possibleNum - 1] == possibleNum) {
                for (int col = 0; col < square; ++col) {
                    //try find a possible place for the num
                    if (sudoku->puzzle[row][col] == 0) {
                        //check if the num is valid in the given position
                        if (check_num(sudoku->puzzle, row, col, possibleNum, n) != INVALID) {
                            possiblePlaces++;
                            possibleRow = row;
                            possibleCol = col;
                        }
                    }
                }
            }
            //if more than one places were found, discard and go to next num
            if (possiblePlaces == 1) {
                sudoku->puzzle[possibleRow][possibleCol] = possibleNum;
                numOfEdits++;
            }
        }
    }
    return numOfEdits;
}

//function which tries to fill in the sudoku by filling in cells by possible values within a column
// and returns the number of cells it has filled in
int solve_col(Sudoku *sudoku, int n) {
    int square = n * n;
    int possiblePlaces = 0;
    int possibleRow = 0;
    int possibleCol = 0;
    //flag to show that the current number was found in the column
    int foundCurrentNum = 0;
    int numOfEdits = 0;
    //array which holds all the numbers not found in a column
    int numsNotFound[square];

    //assign all the values of the array to 0
    for (int i = 0; i < square; ++i) {
        numsNotFound[i] = 0;
    }

    //outer loop increments row number
    for (int col = 0; col < square; ++col) {
        //for each new row, square number of possible nums
        for (int possibleNum = 1; possibleNum <= square; ++possibleNum) {
            //reset flag to 0 (false)
            foundCurrentNum = 0;
            //inner loop increments row number
            for (int row = 0; row < square; ++row) {
                //if the current num is found in the row set flag to true and break
                if (sudoku->puzzle[row][col] == possibleNum) {
                    foundCurrentNum = 1;
                    break;
                }
            }
            //if num wasn't found, store in array
            if (!foundCurrentNum) {
                numsNotFound[possibleNum - 1] = possibleNum;
            }
        }
        //start again for given column
        for (int possibleNum = 1; possibleNum <= square; ++possibleNum) {
            possiblePlaces = 0;
            //if the possible num is in the array (so it wasn't found)
            if (numsNotFound[possibleNum - 1] == possibleNum) {
                for (int row = 0; row < square; ++row) {
                    //try find a possible place for the num
                    if (sudoku->puzzle[row][col] == 0) {
                        if (check_num(sudoku->puzzle, row, col, possibleNum, n) != INVALID) {
                            possiblePlaces++;
                            possibleRow = row;
                            possibleCol = col;
                        }
                    }
                }
            }
            //if more than one places were found, discard and go to next num
            if (possiblePlaces == 1) {
                sudoku->puzzle[possibleRow][possibleCol] = possibleNum;
                numOfEdits++;
            }
        }
    }
    return numOfEdits;
}

//function which returns 1 if the given sudoku is solved and 0 if it isn't (checks if it has any 0s)
int isSolved(int **puzzle, int n) {
    int square = n * n;
    for (int i = 0; i < square; ++i) {
        for (int j = 0; j < square; ++j) {
            if (puzzle[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

//almost same function as recursive solve in sudoku_solve.c
enum solve_output solve_recursive(Sudoku* sudoku, int n)
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
                //call other solve method with the value in the cell
                // to try and find other solutions faster with the given cell filled in
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

//iterative solve solution using the above functions to solve a sudoku,
// resorting to calling the recursive function if it gets stuck
enum solve_output solve(Sudoku *sudoku, int n) {
    int numOfEdits;
    //check if the sudoku is valid, invalid or incomplete
    enum check_output check_output1 = check_sudoku(sudoku->puzzle, n);
    //return if sudoku invalid
    if (check_output1 == INVALID) {
        return UNSOLVABLE;
    }
    //return if sudoku complete
    else if (check_output1 == COMPLETE) {
        return SOLVED;
    }
    //keep going until the sudoku has no 0s in it
    while (!isSolved(sudoku->puzzle, n)) {
        //use the above functions and store the number of edits they made to keep track
        // use each function twice in different orders to make sure each function has
        // the opportunity to look for values once the other functions have made edits
        numOfEdits = solve_cells(sudoku, n) + solve_box(sudoku, n) + solve_row(sudoku, n) +
                solve_col(sudoku, n) + solve_col(sudoku, n) + solve_row(sudoku, n) +
                solve_box(sudoku, n) + solve_cells(sudoku, n);
        //if no edits were found
        if (!numOfEdits) {
            //call the other solve function to add a possible value to a cell and recursively
            // check again
            return solve_recursive(sudoku, n);
        }
        if (numOfEdits < 0)
        {
            return UNSOLVABLE;
        }
    }
    return SOLVED;
}

