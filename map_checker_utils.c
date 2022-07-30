#include "parsing.h"

int	check_map_characters(char **map)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				p++;
			else if (!is_meta(map[i][j]) && map[i][j] != '1' && map[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	if (p != 1)
		return (1);
	return (0);
}

int	all_set(data *d)
{
	if (!d->n_path || !d->s_path || !d->w_path
		|| !d->e_path || !d->c_hexa || !d->f_hexa
		|| !d->map)
	{
		print_error(14);
	}
	if (check_map_characters(d->map))
	{
		print_error(15);
	}
	return 0;
}