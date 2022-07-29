/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:45:34 by aaitoual          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:55 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_map_h_w(t_info *info)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = -1;
	while (info->map[++i])
	{
		j = 0;
		while (info->map[i][j])
			j++;
		if (j > k)
			k = j;
	}
	info->map_h = i;
	info->map_w = k;
}

void	creat_the_game(t_info *info)
{
	info->ml = mlx_init();
	get_texture_buff(info);
	get_map_h_w(info);
	info->window = mlx_new_window(info->ml, WINDOW_W, WINDOW_H, "cub_3D");
	info->window2 = mlx_new_window(info->ml, 240, 240, "mini_MAP");
	creat_imgs(info);
	get_player_position(info);
	mlx_loop_hook(info->ml, draw, info);
	mlx_hook(info->window, 2, 1L<<0, key_press, info);
	mlx_hook(info->window, 3, 1L<<2, key_release, info);
	mlx_loop(info->ml);
}

char	*cpy(char *dest, char *src)
{
	int		i;
	char	*tmp;

	(void)dest;
	tmp = malloc (sizeof (char) * (ft_strlen(src) + 2));
	i = -1;
	while (src[++i])
		tmp[i] = src[i];
	tmp[i] = '\0';
	return (tmp);
}

void	get_default(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (info->map[++i])
	{
		j = -1;
		while (info->map[i][++j])
		{
			if (info->map[i][j] == 'N')
				info->pa = (3 * PI) / 2;
			if (info->map[i][j] == 'S')
				info->pa = (PI) / 2;
			if (info->map[i][j] == 'W')
				info->pa = PI;
			if (info->map[i][j] == 'E')
				info->pa = 0;
		}
	}
	info->rays = malloc (sizeof (t_calculations) * 320);
	info->up.k_a = 0;
	info->up.k_d = 0;
	info->up.k_left = 0;
	info->up.k_right = 0;
	info->up.k_s = 0;
	info->up.k_w = 0;
}

char	**cpy_2(char **str, int j)
{
	int		i;
	int		k;
	char	**ret;

	i = -1;
	while (str[++i])
		i = i + 1 - 1;
	ret = malloc (sizeof (char *) * (i + 1));
	i = j - 2;
	k = -1;
	while (str[++i])
	{
		k++;
		ret[k] = cpy(ret[k], str[i]);
	}
	ret[k + 1] = NULL;
	return (ret);
}

int	get_map_info(t_info *info, char *map)
{
	int		i;
	char	**splited;

	i = -1;
	splited = ft_split(map, '\n');
	info->map = cpy_2(splited, 7);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;
	//tmp
	char	*map;
	int		fd;

	if (ac != 2)
	{
		printf ("error\n");
		exit (1);
	}
	fd = open(av[1], O_RDONLY);
	read_map(&map, fd);
	if (!get_map_info(&info, map))
		return (0);
	fd = -1;
	while (info.map[++fd])
		printf ("%s\n", info.map[fd]);
	//tmp
	get_default(&info);
	creat_the_game(&info);
	return (0);
}
