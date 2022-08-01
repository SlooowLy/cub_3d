#include "parsing.h"

void	get_default_d(data *d)
{
	d->n_path = NULL;
	d->s_path = NULL;
	d->e_path = NULL;
	d->w_path = NULL;
}

void	map_name(char *file)
{
	int	i;

	i = ft_strlen(file) - 4;
	if (ft_strncmp(file + i, ".cub", 4))
		print_error(10);
}

data	parsing(char *file_name)
{
	int		fd;
	data	d;
	char	**map;
	int		i;

	map_name(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		print_error(errno);
	map = read_map(fd);
	i = 0;
	while (map[i][0] != ' ' && map[i][0] != '1')
		parse_line(map[i++], &d, map);
	d.map = map_checker(map + i, &d, map, i); 
	free_arr(map);
	close(fd);
	return (d);
}