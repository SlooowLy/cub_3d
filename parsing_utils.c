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
	else if (error == 12)
		printf("Color Parsing Error!\n");
	else if (error == 13)
		printf("Unown map character!\n");
	else if (error == 14)
		printf("Map element messing!\n");
	else if (error == 15)
		printf("Map characters error!\n");
	else
		printf("%s\n", strerror(error));
	exit(1);
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

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if(arr)
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = 0;
			i++;
		}
	free(arr);
}

void	free_data(data *d)
{
	if (d->n_path)
		free(d->n_path);
	if (d->e_path)
		free(d->e_path);
	if (d->w_path)
		free(d->w_path);
	if (d->s_path)
		free(d->s_path);
	d->n_path = 0;
	d->e_path = 0;
	d->w_path = 0;
	d->s_path = 0;
	free_arr(d->map);
	free(d);
}
