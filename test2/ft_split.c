#include "cub_3d.h"

static int	check(char *src, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] != c && (src[i + 1] == c || src[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static int	ft_mal(char *str, int k, char c)
{
	int	i;

	i = 0;
	while (str[k++] != c && str[k] != '\0')
		i++;
	return (i);
}

static int	makeit(char	**f, char *str, char c)
{
	int	k;
	int	j;
	int	i;

	k = 0;
	i = 0;
	while (str[k])
	{
		j = 0;
		if (str[k] != c)
		{
			f[i] = (char *)malloc (sizeof(char) * ft_mal(str, k, c) + 1);
			if (f[i] == NULL)
				return (1);
			while (str[k] != c && str[k] != '\0')
				f[i][j++] = str[k++];
			f[i][j] = '\0';
			i++;
		}
		else
			k++;
	}
	return (0);
}

static	void	ft_freee(char **f)
{
	int	i;

	i = 0;
	while (f[i])
		free (f[i++]);
	free (f);
}

char	**ft_split(char const *x, char c)
{
	char	**f;
	int		ln;
	int		i;

	if (x == NULL)
		return (NULL);
	ln = check((char *)x, c);
	i = 0;
	f = (char **)malloc(sizeof(char *) * (ln + 1));
	if (f == NULL)
		return (NULL);
	i = makeit(f, (char *)x, c);
	if (i == 1)
	{
		ft_freee (f);
		return (NULL);
	}
	f[ln] = NULL;
	return (f);
}
