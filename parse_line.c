#include "parsing.h"

char	*rm_spaces(char *str, int n)
{
	char	*out;
	// int		i;

	// i = n;
	// while (str[i] == ' ')
	// 	i++;
	out = ft_strdup(str + n);
	free((void *)str);
	return out;
}

void	parse_line(char *line, data *d)
{
	if (!strncmp(line, "NO ", 3))
		d->n_path = rm_spaces(line, 3);
	else if (!strncmp(line, "SO ", 3))
		d->s_path = rm_spaces(line, 3);
	else if (!strncmp(line, "WE ", 3))
		d->w_path = rm_spaces(line, 3);
	else if (!strncmp(line, "EA ", 3))
		d->e_path = rm_spaces(line, 3);
	else if (!strncmp(line, "F ", 2))
		d->f_hexa = color_parse(line + 2);
	else if (!strncmp(line, "C ", 2))
		d->c_hexa = color_parse(line + 2);
	else if (line[0] != 0)
		print_error(11);
}