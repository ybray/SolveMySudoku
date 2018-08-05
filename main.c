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
		printf("10 arguments\n");

//		check if arguments are valid.
		for (i = 1; i < 10; i++)
		{
			v = v + valid_input(argv[i]);
//			printf("v = %d\n", v);
		}

		if (v == 9)
		{
			printf("valid inputs\n");
			for (i = 1; i < 10; i++)
			{
				for (j = 1; j < 10; j++)
				{
					if (argv[i][j] == '.')
						grid[i][j] = '0';
					else
						grid[i][j] = (argv[i][j] + '0');
					printf("%c ", grid[i][j]);
				}
				printf("\n");
			}
			
//			print_grid();
		}
	}
	else
		printf("usage: ./a.out \"arguments\"x9; where arguments are either 1-9 or \'.\'\n");

	return (0);
}
	
