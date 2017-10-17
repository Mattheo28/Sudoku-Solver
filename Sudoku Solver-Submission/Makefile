all: sudoku_check sudoku_solver sudoku_advanced 

clean:
	rm -f sudoku_check sudoku_solver sudoku_advanced

sudoku_check: sudoku_checker_main.c sudoku_checker.c sudoku_io.c sudoku.h
	gcc sudoku_checker_main.c sudoku_checker.c sudoku_io.c sudoku.h -o sudoku_check

sudoku_solver: sudoku_solver_main.c sudoku_solver.c sudoku_checker.c sudoku_io.c sudoku.h
	gcc sudoku_solver_main.c sudoku_solver.c sudoku_checker.c sudoku_io.c sudoku.h -o sudoku_solver

sudoku_advanced: sudoku_solver_main.c sudoku_advanced.c sudoku_checker.c sudoku_io.c sudoku.h
	gcc sudoku_solver_main.c sudoku_advanced.c sudoku_checker.c sudoku_io.c sudoku.h -o sudoku_advanced


