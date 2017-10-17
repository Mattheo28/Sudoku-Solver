#include "sudoku.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    FILE *file = fopen("times.txt", "ab");
    //get the new sudoku and assign n
    Sudoku sudoku = getSudoku();
    int n = sudoku.n;

    clock_t start = clock();
    //solve the sudoku, get the output
    enum solve_output output1 = solve(&sudoku, n);

    clock_t finish = clock();
    double time_taken = (double)(finish - start) / CLOCKS_PER_SEC;
    //print to stdout according to output from solve
    switch(output1)
    {
        case UNSOLVABLE:
            printf("UNSOLVABLE\n");
            break;
        case MULTIPLE:
            printf("MULTIPLE\n");
            break;
        case SOLVED:
            if (file != NULL)
            {
                fprintf(file, "%lf seconds\n", time_taken);
                fflush(file);
                fclose(file);
            }
            printSudoku(sudoku.puzzle, n);
            break;
    }

    return 0;
}