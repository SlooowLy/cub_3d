#include "parsing.h"

int map_len(char *str)
{
	int	out;

	out = 0;
	while (*str)
		if (*str++ == '\n')
			out++;
	return out;
}

int split_len(char *str)
{
	int	out;

	out = 0;
	while (*str != '\n' && *str++)
		out++;
	return out;
}

char **split_map(char *str)
{
	int 	i;
	int		x;
	int		y ;
	char	**splited;
  
	i = 0;
	splited = (char **)malloc((map_len(str) + 2) * sizeof(char **));
	if (!splited)
		return (0);
	x = 0;
	while (str[i])
	{
		y = 0;
		splited[x] = malloc(split_len(str+i) + 1);
		while (str[i] != '\n' && str[i])
		{
			splited[x][y] = str[i];
			i++;
			y++;
		}
		splited[x][y] = '\0';
		x++;
		if (str[i])
			i++;
	}
	splited[x] = 0;
	return splited;
}

char	**read_map(int fd)
{
	char	buff[2];
	char	*file;
	char	**map;
	int		i;

	file = malloc(1);
	if (!file)
		return (0);
	file[0] = 0;
	i = read(fd, buff, 1);
	while (i == 1)
	{
		buff[1] = '\0';
		file = ft_strjoin(file, buff);
		i = read(fd, buff, 1);
	}
	map = split_map(file);
	free((void *)file);
	return map;
}