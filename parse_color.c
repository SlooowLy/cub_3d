#include "parsing.h"

int	ft_atoi2(char *str)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		out = out * 10 + (str[i] - 48);
		i++;
	}
	if (!str[i] && i >= 1 && i <=3)
		return (out);
	return (-1);
}

int	count_separator(char *str)
{
	int	i;
	int	sep;

	i = 0;
	sep = 0;
	while (str[i])
	{
		if (str[i] == ',')
			sep++;
		i++;
	}
	return (sep);
}

int	*parse_str_color(char *str)
{
	int		i;
	char	**arr;
	int		*out;

	if (count_separator(str) != 2)
		return (0);
	arr = ft_split(str, ',');
	if (arrlen(arr) != 3)
		return (0);
	i = 0;
	out = malloc(3 * sizeof(int));
	while (arr[i])
	{
		out[i] = ft_atoi2(arr[i]);
		i++;
	}
	return out;
}

unsigned long	color_parse(char *str)
{
	int	*rgb;
	int	i;

	rgb = parse_str_color(str);
	if (!rgb)
		return (0);
	i = 0;
	while (i < 3)
		if (rgb[i] < 0 || rgb[i++] > 255)
			return (0);	
	return (rgb_to_hexa(rgb[0], rgb[1], rgb[2]));
}
