/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:17:53 by aaitoual          #+#    #+#             */
/*   Updated: 2022/07/31 09:05:21 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	draw(void *stru)
{
	t_info	*info;

	info = stru;
	mlx_clear_window(info->ml, info->window);
	update_player_cord(info);
	mlx_put_image_to_window(info->ml, info->window2,
		info->mini_map.img, get_x(info) - 120, get_y(info) - 120);
	mlx_put_image_to_window(info->ml, info->window2, info->img1.img, 118, 118);
	mlx_put_image_to_window(info->ml, info->window, info->img_u.img, 0, 0);
	mlx_put_image_to_window(info->ml, info->window, info->img_d.img, 0, 240);
	rays(info);
	rander_walls(info);
	return (0);
}
