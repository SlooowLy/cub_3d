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
			splited[x][y++] = str[i++];
		splited[x][y] = 0;
		x++;
		if (str[i])
			i++;
	}
	splited[x] = 0;
	return splited;
}

char	**read_map(int fd)
{
	char	*buff;
	char	*file;
	char	**map;

	buff = malloc(2);
	file = malloc(1);
	if (!buff || !file)
		return (0);
	file[0] = 0;
	while (read(fd, buff, 1))
	{
		file = ft_strjoin(file, buff);
	}
	free((void *)buff);

	map = split_map(file);
	free((void *)file);
	return map;
}