/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cordinations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 07:58:54 by aaitoual          #+#    #+#             */
/*   Updated: 2022/07/28 10:49:18 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

tn ai azo rhox __cold

void	player_next_position_1(t_info *info)
{
	int	x;
	int	y;

	x = round(info->px + (cos(info->pa)) * 3);
	y = round(info->py + (sin(info->pa)) * 3);
	if (info->map[(int)floor (y / WALL_SIZE)]
		[(int)floor (x / WALL_SIZE)] != '1'
		&& info->map[(int)floor((y + 2) / WALL_SIZE)]
		[(int)floor((x + 2) / WALL_SIZE)] != '1'
		&& info->map[(int)floor((y - 2) / WALL_SIZE)]
		[(int)floor((x - 2) / WALL_SIZE)] != '1')
	{
		info->px = x;
		info->py = y;
	}
}

void	player_next_position_2(t_info *info)
{
	int	x;
	int	y;

	x = round(info->px + cos(info->pa) * -3);
	y = round(info->py + sin(info->pa) * -3);
	if (info->map[(int)floor (y / WALL_SIZE)]
		[(int)floor (x / WALL_SIZE)] != '1'
		&& info->map[(int)floor((y + 2) / WALL_SIZE)]
		[(int)floor((x + 2) / WALL_SIZE)] != '1'
		&& info->map[(int)floor((y - 2) / WALL_SIZE)]
		[(int)floor((x - 2) / WALL_SIZE)] != '1')
	{
		info->px = x;
		info->py = y;
	}
}

void	player_next_position_3(t_info *info)
{
	int	x;
	int	y;

	x = round(info->px + sin(info->pa) * 3);
	y = round(info->py - cos(info->pa) * 3);
	if (info->map[(int)floor (y / WALL_SIZE)]
		[(int)floor (x / WALL_SIZE)] != '1'
		&& info->map[(int)floor((y + 2) / WALL_SIZE)]
		[(int)floor((x + 2) / WALL_SIZE)] != '1'
		&& info->map[(int)floor((y - 2) / WALL_SIZE)]
		[(int)floor((x - 2) / WALL_SIZE)] != '1')
	{
		info->px = x;
		info->py = y;
	}
}

void	player_next_position_4(t_info *info)
{
	int	x;
	int	y;

	x = round(info->px - sin(info->pa) * 3);
	y = round(info->py + cos(info->pa) * 3);
	if (info->map[(int)floor (y / WALL_SIZE)]
		[(int)floor (x / WALL_SIZE)] != '1'
		&& info->map[(int)floor((y + 2) / WALL_SIZE)]
		[(int)floor((x + 2) / WALL_SIZE)] != '1'
		&& info->map[(int)floor((y - 2) / WALL_SIZE)]
		[(int)floor((x - 2) / WALL_SIZE)] != '1')
	{
		info->px = x;
		info->py = y;
	}
}

void	update_player_cord(t_info *info)
{
	if (info->up.k_w)
		player_next_position_1(info);
	if (info->up.k_s)
		player_next_position_2(info);
	if (info->up.k_a)
		player_next_position_3(info);
	if (info->up.k_d)
		player_next_position_4(info);
	if (info->up.k_right)
	{
		info->pa = info->pa + 0.041;
		if (info->pa > PI * 2)
			info->pa = info->pa - (2 * PI);
	}
	if (info->up.k_left)
	{
		info->pa = info->pa - 0.041;
		if (info->pa < 0)
			info->pa = info->pa + (2 * PI);
	}
}
