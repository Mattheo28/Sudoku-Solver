#include "sudoku.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

enum check_output check_num(int **puzzle, int row, int col, int num, int n) {
    //no use checking if the number is valid if the number is 0, so return incomplete
    if (num == 0)
    {
        return INCOMPLETE;
    }
    int square = n * n;
    //check to see if the number is already in the row
    for (int i = 0; i < square; i++) {
        if (i != row && puzzle[i][col] == num) {
            return INVALID;
        }
    }
    //check to see if the number is already in the column
    for (int i = 0; i < square; i++) {
        if (i != col && puzzle[row][i] == num) {
            return INVALID;
        }
    }
    //check to see if the number is already in the box
    //variables that work as an 'offset' to find each box in the sudoku
    int rowPosVal = row % n;
    int colPosVal = col % n;
    //check contents of all numbers in the box, except the one of the current cell
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            //left hand side of the && checks that the current cell we are checking is not the
            // one of the number we are checking, and the right hand side checks that the
            // number we are checking is equal to the one in the cell we are checking,
            // in which case we return invalid
            if ((((row + i) - rowPosVal) != row && ((col + j) - colPosVal) != col) &&
                puzzle[(row + i) - rowPosVal][(col + j) - colPosVal] == num) {
                return INVALID;
            }
        }
    }
    return COMPLETE;
}

enum check_output check_sudoku(int** puzzle, int n) {
    int square = n * n;
    int incomplete = 0;
    enum check_output output1 = COMPLETE;
    //use check_num on all the values in the sudoku
    for (int i = 0; i < square; ++i) {
        for (int j = 0; j < square; ++j) {
            output1 = check_num(puzzle, i, j, puzzle[i][j], n);
            //if any value is invalid, return invalid
            if (output1 == INVALID)
            {
                return output1;
            }
            // if a value is incomplete (0), set the flag to 1 (true), but wait til the end to
            // return incomplete, in case we find an invalid value first
            else if(output1 == INCOMPLETE)
            {
                incomplete = 1;
            }
        }
    }
    //no invalid value was found, so if there was a 0 in the sudoku, return incomplete
    if(incomplete)
    {
        return INCOMPLETE;
    }
    //if no invalid or incomplete values were found, output1 won't have changed, and so we return
    // COMPLETE
    return output1;
}

Sudoku getSudoku() {
    Sudoku sudoku;
    // this string will be used to get the value of n, the first value given.
    char *inputN = malloc(sizeof(int));
    fgets(inputN, 50, stdin);
    // use 'atoi' to get the int value from the string, assign it to n
    int n = atoi(inputN);
    free(inputN);
    // assign the 'n' to the sudoku
    sudoku.n = n;
    int square = n * n;

    //malloc twice since it's a 2d array, once to get one array and once more in a for loop
    // for each element of the first array
    sudoku.puzzle = (int **)malloc(sizeof(int *) * square);
    for(int i = 0; i < square; i++)
        sudoku.puzzle[i] = (int *) malloc(sizeof(int) * square);

    //make another string which will be used to get the contents of each line in the input
    char *inputSud = malloc(sizeof(int) * square * square);
    int i = 0;
    //use fgets to read from stdin, maximum number of characters is square * square
    while (fgets(inputSud, square * square, stdin)) {
        //use strtok_r function to copy a number into currentVal from restOfLine
        char *restOfLine;
        char *currentVal = strtok_r(inputSud, " ", &restOfLine);
        while (currentVal) {
            //assign value from currentVal into the sudoku puzzle using strtol
            sudoku.puzzle[i / square][i % square] = (int)strtol(currentVal, NULL, 10);
            i++;
            //get the next value
            currentVal = strtok_r(NULL, " ", &restOfLine);
        }
        //if i is greater than the number of elements in the sudoku, break out of while loop
        if (i >= square * square) {
            break;
        }
    }
    free(inputSud);
    return sudoku;
}
