#include "parsing.h"

void	map_name(char *file)
{
	int	i;

	i = ft_strlen(file) - 4;
	if (ft_strncmp(file + i, ".cub", 4))
		print_error(10);
}

void    parsing(char *map)
{
	int fd;
	data	*d;

	d = malloc(sizeof(data));
	map_name(map);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		print_error(errno);
	char **map = read_map(fd);
	while (!is_map(*map))
		

			
}