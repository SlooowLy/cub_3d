/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:13:35 by aaitoual          #+#    #+#             */
/*   Updated: 2022/08/15 20:30:32 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int mouse_move(int x, int y, t_info *info)
{
	if (x > 0 && x < 852)
		info->pa = info->pa + (((x - 462) / 200) * PI / 180.0);
	// info->pa = info->pa;
	y = 0;
	return (0);
}

void	free_2(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free (map[i]);
	free (map);
}

void	ft_exit(t_info *info, int i)
{
	if (i == 1)
	{
		free_2(info->k.map);
		free (info->k.e_path);
		free (info->k.w_path);
		free (info->k.s_path);
		free (info->k.n_path);
		free (info->rays);
		free (info->buff_ea);
		free (info->buff_so);
		free (info->buff_we);
		free (info->buff_no);
		system ("leaks cub3d");
		exit (1);
	}
}

int	key_press(int key, t_info *info)
{
	int	x;
	int	y;
	
	x = floor(info->px / 64);
	y = floor(info->py / 64);
	if (key == KEY_ENT)
	{
		if ((info->k.map[y][x + 1] == 'D' || info->k.map[y][x - 1] == 'D') && !info->animation)
			info->animation = 4;
	}
	if (key == KEY_W)
		info->up.k_w = 1;
	if (key == KEY_S)
		info->up.k_s = 1;
	if (key == KEY_A)
		info->up.k_a = 1;
	if (key == KEY_D)
		info->up.k_d = 1;
	if (key == KEY_RIGHT)
		info->up.k_right = 1;
	if (key == KEY_LEFT)
		info->up.k_left = 1;
	if (key == EXIT)
		ft_exit(info, 1);
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == KEY_W)
		info->up.k_w = 0;
	if (key == KEY_S)
		info->up.k_s = 0;
	if (key == KEY_A)
		info->up.k_a = 0;
	if (key == KEY_D)
		info->up.k_d = 0;
	if (key == KEY_RIGHT)
		info->up.k_right = 0;
	if (key == KEY_LEFT)
		info->up.k_left = 0;
	return (0);
}
