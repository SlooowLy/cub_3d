#include "parsing.h"

char	*pass_spaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

int	is_meta(char c)
{
	if (c == '0' || c == 'N' 
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_sub_lines(char **s)
{
	int	last;
	int	i;

	i = 0;
	while (s[0][i])
		if (is_meta(s[0][i++]))
			return (1);
	i = 0;
	while (s[i])
	{
		last = ft_strlen(s[i]) - 1;
		if (is_meta(s[i][0]) || is_meta(s[i++][last]))
			return 1;
	}
	last = arrlen(s) - 1;
	i = 0;
	while (s[last][i])
		if (is_meta(s[0][i++]))
			return (1);
	return (0);
}

int	check_lines(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (is_meta(s[i][j]))
			{
				if (s[i - 1][j] == ' ' || s[i - 1][j + 1] == ' '
					|| s[i][j + 1] == ' ' || s[i + 1][j + 1] == ' '
					|| s[i + 1][j] == ' ' || s[i + 1][j - 1] == ' '
					|| s[i][j - 1] == ' ' || s[i - 1][j - 1] == ' ')
					{
						printf("i = %d, j = %d\n", i, j);
					return 1;
					}
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	**map_checker(char **str)
{
	if (check_lines(str))
		printf("Error1\n");
	if (check_sub_lines(str))
		printf("Error2\n");
	return str;
}
