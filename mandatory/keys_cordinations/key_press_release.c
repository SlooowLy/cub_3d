/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:13:35 by aaitoual          #+#    #+#             */
/*   Updated: 2022/07/31 10:54:28 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int mouse_move(int x, int y, t_info *info)
{
	x = 0;
	// info->pa = info->pa + (((x) / 200) * PI / 180.0);
	info->pa = info->pa;
	y = 0;
	return (0);
}

void	ft_exit(t_info *info, int i)
{
	// int	i;

	// i = -1;
	if (i == 1)
	{
		free (info->rays);
		free (info->buff_ea);
		free (info->buff_so);
		free (info->buff_we);
		free (info->buff_no);
		// mlx_destroy_image(info->ml, info->img1.img);
		// mlx_destroy_image(info->ml, info->img_d.img);
		// mlx_destroy_image(info->ml, info->img_u.img);
		// mlx_destroy_image(info->ml, info->mini_map.img);
		// mlx_destroy_image(info->ml, info->img_tmp.img);
		system ("leaks cub3d");
		// mlx_destroy_window(info->ml, info->window2);
		// mlx_destroy_window(info->ml, info->window);
		exit (1);
	}
}

int	key_press(int key, t_info *info)
{
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
