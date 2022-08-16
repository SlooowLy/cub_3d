/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cordinations_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:40:58 by aaitoual          #+#    #+#             */
/*   Updated: 2022/08/16 17:53:25 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_wall(t_info *info, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (info->k.map[++i])
	{
		j = -1;
		while (info->k.map[i][++j])
		{
			if (info->k.map[i][j] == '1' || info->k.map[i][j] == 'D')
			{
				i = i + 1 - 1;
				if ((x >= (j * 64) - 10 && x <= ((j + 1) * 64) + 10)
					&& (y >= (i * 64) - 10 && y <= ((i + 1) * 64) + 10))
					return (0);
			}
		}
	}
	return (1);
}

int	check_door2(t_info *info, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (info->k.map[++i])
	{
		j = -1;
		while (info->k.map[i][++j])
		{
			if (info->k.map[i][j] == 'D' && info->door_statue == 1 && info->k.map[i][j + 1] != '1' && info->k.map[i][j - 1] != '1')
			{
				i = i + 1 - 1;
				if ((x >= (j * 64) - 10 && x <= ((j + 1) * 64) + 10)
					&& (y >= (i * 64) - 10 && y <= ((i + 1) * 64) + 10))
					return (1);
			}
		}
	}
	return (0);
}
