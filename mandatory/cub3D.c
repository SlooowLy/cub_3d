/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:45:34 by aaitoual          #+#    #+#             */
/*   Updated: 2022/08/15 17:30:33 by aaitoual         ###   ########.fr       */
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
	while (info->k.map[++i])
	{
		j = 0;
		while (info->k.map[i][j])
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
	mlx_hook(info->window, 6, 0, mouse_move, info);
	mlx_hook(info->window, 3, 1L<<2, key_release, info);
	mlx_loop(info->ml);
}

void	get_default(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (info->k.map[++i])
	{
		j = -1;
		while (info->k.map[i][++j])
		{
			if (info->k.map[i][j] == 'N')
				info->pa = (3 * PI) / 2;
			if (info->k.map[i][j] == 'S')
				info->pa = (PI) / 2;
			if (info->k.map[i][j] == 'W')
				info->pa = PI;
			if (info->k.map[i][j] == 'E')
				info->pa = 0;
		}
	}
	info->animation = 0;
	info->rays = malloc (sizeof (t_calculations) * 320);
	info->buff_door = malloc (sizeof (int *) * 4);
	info->up.k_a = 0;
	info->up.k_d = 0;
	info->up.k_left = 0;
	info->up.k_right = 0;
	info->up.k_s = 0;
	info->up.k_w = 0;
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
	{
		printf ("error\n");
		exit (1);
	}
	info.k = parsing(av[1]);
	get_default(&info);
	creat_the_game(&info);
	return (0);
}
