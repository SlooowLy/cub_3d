/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_first_cordinations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:13:38 by aaitoual          #+#    #+#             */
/*   Updated: 2022/07/28 08:13:39 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"

void	get_player_position(t_info *info)
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
			{
				info->px = j * WALL_SIZE;
				info->py = i * WALL_SIZE;
				return ;
			}
		}
	}
}
