#include <stdio.h>
#include <stdlib.h>
//#include "header.h"

typedef int bool;
#define true 1
#define false 0

/*checks input string is correct length and format*/
int	valid_input(char *str)
{
	int i;
	int j;
	j = 0;
	i = 0;

	//find string length
	while (str[i] != 0) i++;
	
	//if not 9: abort
	if (i != 9) return (0);

	//check string only contains characters 1-9 or '.'	
	for (i = 0; i < 9; i++)
		if ((str[i] >= '1' && str[i] <= '9') || str[i] == '.') j++;

	//if all valid inputs: validate
	if (j == 9) return (1);
	else return (0);
}

/*checks if num is present within the sub-square, column or row of current space[row][col]*/
bool	is_available(char **grid, int row, int col, char num)
{
	int rowStart = (row/3) * 3;
	int colStart = (col/3) * 3;

	for (int i = 0; i < 9; ++i)
	{
		if (grid[row][i] == num) return false;
		if (grid[i][col] == num) return false;
		if (grid[rowStart + (i%3)][colStart + (i/3)] == num) return false;
	}
	return true;
}

bool	is_alone(char **grid, int row, int col, char num)
{
	int rowStart = (row/3) * 3;
	int colStart = (col/3) * 3;
	bool checkrow = true, checkcol = true, checksquare = true;

	for (int i = 0; i < 9; ++i)
	{
		if (grid[row][i] == num) 
		{
			if (i != col) checkrow = false;
		}
		
		if (grid[i][col] == num) 
		{
			if (i != row) checkcol = false;
		}
		
		int r = rowStart + (i%3);
		int c = colStart + (i/3);

		if (grid[r][c] == num) 
		{
			if(!((r == row) && (c == col))) checksquare = false;
		}
	}
//	printf("\t | r:%d c:%d s:%d |", checkrow, checkcol, checksquare);
	return (checkrow || checkcol || checksquare);
}



/*prints out current state of sudoku*/
void	print_sudoku(char **grid)
{
	for (int row = 0; row < 9; row++)
	{
		if (row % 3 == 0) printf("\n");

		for (int col = 0; col < 9; col++)
		{
			if (col % 3 == 0) printf("  ");
			printf("%c ", grid[row][col]);
		}
		printf("\n");
	}
}

/*validates initial sudoku position*/
bool	validate_sudoku(char **sudoku)
{
	//checks sudoku rows for valid characters
	int sum = 0;
	for (int i = 1; i < 10; i++)
	{
		sum = sum + valid_input(sudoku[i]);
	}
	return (sum == 9);
}

/*generates a grid*/
char	**make_grid(int n, int m)
{	
	char *values = calloc(m * n, sizeof(char));
	char **grid = malloc(n * sizeof(char*));
	for (int i = 0; i < n; ++i) 
	{
		grid[i] = values + i * m;
	}
	return grid;
}

/*returns sudoku grid with numbers and 'empty' characters*/
char	**format_empty_spaces(char **sudoku, char empty)
{
	//creates 9x9 sudoku grid
	char **grid = make_grid(9, 9);

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			//swap '.' for 'empty' character
			if (sudoku[row+1][col] == '.') grid[row][col] = empty;
		
			//transfer number to grid
			else grid[row][col] = sudoku[row+1][col];
		}
	}
	return grid; 
}

/*if position already filled returns false*/
bool	is_empty(char **grid, int row, int col)
{
	return !(grid[row][col] >= '1' && grid[row][col] <= '9');	
}


char	**generate_boolgrid(char **grid, char number)
{
	char available = '-';
	char not_available = 'X';

	char **boolgrid = make_grid(9, 9);
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (is_empty(grid, row, col))
			{
				boolgrid[row][col] = is_available(grid, row, col, number) ? available: not_available;					
			}
			else	boolgrid[row][col] = not_available;
		}
	}
	return boolgrid;
}

char	**solve(char **sudoku, char **boolgrid, char number)
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (boolgrid[row][col] == '-')
			{
				if (is_alone(boolgrid, row, col, '-'))
				{
					sudoku[row][col] = number;
				//	printf("\nhit a %c at [%d][%d]", number, row+1, col+1);
				}
			}
		}
	}	
	return sudoku;
}

/*counts empty spaces*/
int	count_empty_spaces(char **sudoku, char empty)
{
	int sum = 0;
	
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (sudoku[row][col] == empty)
				sum++;
		}
	}
	return sum;
}

int	main(int argc, char **argv)
{
	char **sudoku;

	//exits if input isn't corqrect.
	if (argc != 10 || !validate_sudoku(argv)) 
	{
		printf("\n\nusage: ./a.out \"arguments\"x9; where arguments are either 1-9 or \'.\'\n\n");
		return 999;
	}

	//reformat input into more appropriate sudoku
	sudoku = format_empty_spaces(argv, '-');

	printf("\nStarting point:\n");
	print_sudoku(sudoku);

//	getchar();
	printf("\nSolving:");
	
	int epoch = 0;

	do
	{
		int last_empty_spaces = count_empty_spaces(sudoku, '-');
//		printf("\nempty spaces left: %d", last_empty_spaces);
		for (int i = 0; i < 9; i++)
		{
		
			char a = ('1' + i);
			char **boolgrid = generate_boolgrid(sudoku, a);
	
			solve(sudoku, boolgrid, a);
		}
		
		//terminates if no progress is made
		if (last_empty_spaces == count_empty_spaces(sudoku, '-'))
		{
			printf("\nUnsolvable.\n");
			break;
		}
		epoch++;
	}
	while(count_empty_spaces(sudoku, '-'));
	
	printf("\n");	
	print_sudoku(sudoku);

	printf("\nSolved in %d epochs.\n\n", epoch);
	
	return (0);
}




// example input
// ./a.out "1........" "2........" "3........" "4........" "5........" "6........" "7........" "8........" "9...55..."
// ./a.out "3.65.84.." "52......." ".87....31" "..3.1..8." "9..863..5" ".5..9.6.." "13....25." ".......74" "..52.63.."	
