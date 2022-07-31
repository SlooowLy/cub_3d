/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:27:05 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/07/31 13:41:42 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		k;
	int		j;
	char	*a1;

	i = len(s1) + len(s2);
	j = 0;
	k = 0;
	a1 = malloc(i + 1);
	if (a1 == 0)
		return (0);
	while (s1 && s1[j] != '\0')
	{
		a1[j] = s1[j];
		j++;
	}
	while (s2 && s2[k] != '\0')
		a1[j++] = s2[k++];
	a1[j] = '\0';
	return (a1);
}
