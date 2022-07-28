#include "parsing.h"

void	print_error(int error)
{
	printf("Error\n");
	if (error == 9)
		printf("Map not found!\n");
	else if (error == 10)
		printf("Invalid file extension!\n");
	else if (error == 11)
		printf("Unown map element!\n");
	else
		printf("%s\n", strerror(error));
	// exit(1);
}

int	is_map(char *str)
{
	int	len;

	if (!str)
		return 1;
	len = ft_strlen(str);
	while (*str == '1' || *str == ' ')
		str++;
	if (!(*str) && len)
		return (1);
	return (0);
}

unsigned long	rgb_to_hexa(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}