/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cordinations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 07:58:54 by aaitoual          #+#    #+#             */
/*   Updated: 2022/07/29 18:56:00 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	player_next_position_1(t_info *info)
{
	int	x;
	int	y;

	x = round(info->px + (cos(info->pa)) * 5);
	y = round(info->py + (sin(info->pa)) * 5);
	if (check_wall(info, x, y))
	{
		info->px = x;
		info->py = y;
	}
}

void	player_next_position_2(t_info *info)
{
	int	x;
	int	y;

	x = round(info->px + cos(info->pa) * -5);
	y = round(info->py + sin(info->pa) * -5);
	if (check_wall(info, x, y))
	{
		info->px = x;
		info->py = y;
	}
}

void	player_next_position_3(t_info *info)
{
	int	x;
	int	y;

	x = round(info->px + sin(info->pa) * 5);
	y = round(info->py - cos(info->pa) * 5);
	if (check_wall(info, x, y))
	{
		info->px = x;
		info->py = y;
	}
}

void	player_next_position_4(t_info *info)
{
	int	x;
	int	y;

	x = round(info->px - sin(info->pa) * 5);
	y = round(info->py + cos(info->pa) * 5);
	if (check_wall(info, x, y))
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
		// if (info->pa > PI * 2)
		// 	info->pa = info->pa - (2 * PI);
	}
	if (info->up.k_left)
	{
		info->pa = info->pa - 0.041;
		// if (info->pa < 0)
		// 	info->pa = info->pa + (2 * PI);
	}
}
