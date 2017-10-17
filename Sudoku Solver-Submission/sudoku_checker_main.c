#include <stdio.h>
#include "sudoku.h"

int main()
{
    //get the new sudoku, find n
    Sudoku sudoku = getSudoku();
    int n = sudoku.n;

    //print the new sudoku
    printSudoku(sudoku.puzzle, n);

    //check the sudoku and give output to stdout accordingly
    enum check_output output1 = check_sudoku(sudoku.puzzle, n);
    switch(output1)
    {
        case INVALID:
            printf("INVALID\n");
            break;
        case INCOMPLETE:
            printf("INCOMPLETE\n");
            break;
        case COMPLETE:
            printf("COMPLETE\n\n");
            break;
    }
    return 0;
}