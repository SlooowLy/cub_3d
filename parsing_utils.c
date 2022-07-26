#include "parsing.h"

void	print_error(int error)
{
	printf("Error\n");
	if (error == 9)
		printf("Map not found!\n");
	else
		printf("%s\n", strerror(error));
	exit(1);
}