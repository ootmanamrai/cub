/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:26:57 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:27:04 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

int	extra_check(char **map)
{
	int i;
	int x;
	int boo;
	i = 0;
	x = 0;
	boo = 0;
	while (map[i])
	{
		x = 0;
		while (map[i][x])
		{
			if (map[i][x] == 'D')
			{
				if ((map[i][x + 1] == '1' && map[i][x - 1] == '1') || (map[i][x
					- 1] == 'A' || map[i][x + 1] == 'A'))
				{
					boo = 1;
				}
				else if ((map[i + 1][x] == '1' && map[i - 1][x] == '1')
					|| map[i][x - 1] == 'A' || map[i][x + 1] == 'A')
				{
					boo = 1;
				}
				// else
				// {
				// 	printf("unvalid \nERROR7\n");
				// 	return (-1);
				// }
			}
			x++;
		}
		i++;
	}
	return (boo);
}