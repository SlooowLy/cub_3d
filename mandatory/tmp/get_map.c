#include "../cub3D.h"

int	len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		k;
	int		j;
	char	*a1;

	i = len(s1) + len(s2);
	j = 0;
	k = 0;
	a1 = malloc(i + 1);
	if (a1 == 0)
		return (0);
	while (s1 && s1[j] != '\0')
	{
		a1[j] = s1[j];
		j++;
	}
	while (s2 && s2[k] != '\0')
		a1[j++] = s2[k++];
	a1[j] = '\0';
	return (a1);
}

int	read_map(char **all, int fd)
{
	char	*curr;
	int		i;
	int		j;

	i = 0;
	j = 1;
	curr = malloc(1 + 1);
	*all = NULL;
	while (i == 0 && j != 0)
	{
		j = read(fd, curr, 1);
		// if (curr[0] != 'P' && curr[0] != 'E' && curr[0] != 'C'
		// 	&& curr[0] != '0' && curr[0] != '1')
		// 	return (2);
		if (j == -1)
			break ;
		if (j == 0)
			break ;
		curr[j] = '\0';
		*all = ft_strjoin(*all, curr);
	}
	if (j != -1)
		free (curr);
	return (1);
}
