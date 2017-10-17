#include <malloc.h>
#include "sudoku.h"

void printSudoku(int** puzzle, int n) {
    int square = n * n;
    for (int i = 0; i < square; i++) {
        //1 or 2 spaces printed before each number depending on the number, to fit output from
        // stacscheck
        printf(" ");
        for (int j = 0; j < square; j++) {
            if(puzzle[i][j] < 10)
            {
                printf(" ");
            }
            printf("%d ", puzzle[i][j]);
        }
        printf("\n");
    }
}

int** freeSudoku(int** puzzle, int n)
{
    //go through 2D array, set all values to 0.
    int square = n * n;
    for (int i = 0; i < square; ++i) {
        for (int j = 0; j < square; ++j) {
            puzzle[i][j] = 0;
        }
    }
    return puzzle;
}

int** copySudoku(int** puzzle, int n)
{
    int square = n * n;

    //malloc twice since it's a 2d array, once to get one array and once more in a for loop
    // for each element of the first array
    int** newPuzzle = (int **)malloc(sizeof(int *) * square);
    for(int i = 0; i < square; i++)
        newPuzzle[i] = (int *) malloc(sizeof(int) * square);

    for (int i = 0; i < square; ++i) {
        for (int j = 0; j < square; ++j) {
            newPuzzle[i][j] = puzzle[i][j];
        }
    }
    return newPuzzle;
}


