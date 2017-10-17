//struct to represent a sudoku
typedef struct {
    //'n' of sudoku (its size will be n x n)
    int n;
    //2d array to represent the sudoku
    int **puzzle;
} Sudoku;

//enum to represent what the checker can output
enum check_output {
    INVALID,
    INCOMPLETE,
    COMPLETE,
};

//enum to represent what the solver can output
enum solve_output {
    UNSOLVABLE,
    MULTIPLE,
    SOLVED,
};

//function that assigns all the elements of the sudoku to 0
int** freeSudoku(int** puzzle, int n);

//function that returns a copy of the given sudoku
int** copySudoku(int** puzzle, int n);

//function that checks if a number is valid in a given row and column in the sudoku, returning
// INVALID if it isn't, INCOMPLETE if the number is 0 and COMPLETE if the number is valid
enum check_output check_num(int **puzzle, int row, int col, int num, int n);

//function that uses check_num to check if the whole sudoku is complete, invalid or incomplete.
enum check_output check_sudoku(int** puzzle, int n);

//function that neatly prints out a given sudoku
void printSudoku(int** puzzle, int n);

//function that gets a sudoku from stdin and returns a Sudoku
Sudoku getSudoku();

//function that solves a sudoku (2 versions, depending if sudoku_solver or sudoku_advanced are used)
enum solve_output solve(Sudoku* sudoku, int n);