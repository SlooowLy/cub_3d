#include "parsing.h"

void	map_name(char *file)
{
	int	i;

	i = ft_strlen(file) - 4;
	if (ft_strncmp(file + i, ".cub", 4))
		print_error(10);
}

void print_data(data *d)
{
	printf("%s\n", d->n_path);
	printf("%s\n", d->s_path);
	printf("%s\n", d->e_path);
	printf("%s\n", d->w_path);
	printf("%lX\n", d->c_hexa);
	printf("%lX\n", d->f_hexa);
}

void    parsing(char *file_name)
{
	int		fd;
	data	*d;
	char	**map;

	d = malloc(sizeof(data));
	map_name(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		print_error(errno);
	map = read_map(fd);
	while (!is_map(*map))
		parse_line(*map++, d);
	print_data(d);
	close(fd);
}