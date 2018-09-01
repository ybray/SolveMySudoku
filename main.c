#include <stdio.h>
//#include "header.h"

int	valid_input(char *str)
{
	int i;
	int j;
	j = 0;
	i = 0;
	while (str[i] != 0)
		i++;
	if (i != 9)
		return (0);	
	for (i = 0; i < 9; i++)
		if ((str[i] >= '1' && str[i] <= '9') || str[i] == '.')
			j++;
//	printf("j:%d\n", j);
	if (j == 9)
		return (1);
	return (-1);
}

int	isavailable(char grid[][9], int row, int col, char num)
{
	int rowStart = (row/3) * 3;
	int colStart = (col/3) * 3;
	int i, j;

	for (i = 0; i < 9; ++i)
	{
		if (grid[row][i] == num) return (0);
		if (grid[i][col] == num) return (0);
		if (grid[rowStart + (i%3)][colStart + (i/3)] == num) return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int i;
	int j;
	int v;
	char grid[10][10];
	char *grid_ptr;

	grid_ptr = &(grid[10][10]);

	v = 0;
	if (argc == 10)
	{

/*
** Checks if arguments are valid.
** v is validity, if != 9; input is false
*/
		for (i = 1; i < 10; i++)
		{
			v = v + valid_input(argv[i]);
		}

		if (v == 9)
		{

		
		//Prints out the grid if input is valid (1-9 or '.') 
		
			printf("\nStarting point:\n\n");
			for (i = 1; i < 10; i++)
			{
				for (j = 0; j < 9; j++)
				{
					if (argv[i][j] == '.')
						grid[i][j] = '0';
					else
						grid[i][j] = (argv[i][j]);
					printf("%c ", grid[i][j]);
				}
				printf("\n");
			}
			printf("\n");

			//start changing sudoku
			
		for (i = 0; i < 9; ++i)
			{
			}

		}
	}
	else
		printf("usage: ./a.out \"arguments\"x9; where arguments are either 1-9 or \'.\'\n");

	return (0);
}

int	fillsudoku(char grid[][9], int row, int col)
{
	int i;
	if (row < 9 && col < 9)
		if (grid[row][col] != '0')
		{
			if ( (col + 1) < 9)
				return (fillsudoku(grid, row, col+1));
			else if ( (row + 1) < 9)
				return (fillsudoku(grid, row+1, 0));
			else 
				return (1);
		}
		else
		{
		}


	if (isavailable(grid, row, col, i+1))
		grid[row][col] = i+1;
	
			

}

/* 
** Wrong input 
*/


// example input
// ./a.out "1........" "2........" "3........" "4........" "5........" "6........" "7........" "8........" "9...55..."	
