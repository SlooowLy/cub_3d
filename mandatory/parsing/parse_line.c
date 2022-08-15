#include "parsing.h"

char	*rm_spaces(char *str, int n)
{
	char	*out;

	out = ft_strdup(str + n);
	return out;
}

void	parse_line(char *line, data *d, char **map)
{
	static int	i;

	if (!strncmp(line, "NO ", 3) && ++i)
		d->n_path = rm_spaces(line, 3);
	else if (!strncmp(line, "SO ", 3) && ++i)
		d->s_path = rm_spaces(line, 3);
	else if (!strncmp(line, "WE ", 3) && ++i)
		d->w_path = rm_spaces(line, 3);
	else if (!strncmp(line, "EA ", 3) && ++i)
		d->e_path = rm_spaces(line, 3);
	else if (!strncmp(line, "F ", 2) && ++i)
		d->f_hexa = color_parse(line + 2, d, map);
	else if (!strncmp(line, "C ", 2) && ++i)
		d->c_hexa = color_parse(line + 2, d, map);
	else if (i > 6)
		puts ("error");
	else if (line[0] != 0)
	{
		free_arr(map);
		free_data(d);
		print_error(11);
	}
}