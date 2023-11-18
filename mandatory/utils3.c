/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:33:02 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:38:08 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initail_image(t_data *data)
{
	int	i;

	i = 0;
	init_data_txt(data);
	while (i < 5)
	{
		data->imgs[i]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
				data->imgs[i]->path, &data->imgs[i]->width,
				&data->imgs[i]->height);
		if (!data->imgs[i]->img_ptr)
		{
			printf("file not exist\n");
			exit(0);
		}
		data->imgs[i]->img_data = mlx_get_data_addr(data->imgs[i]->img_ptr,
				&data->imgs[i]->bits, &data->imgs[i]->len, &data->imgs[i]->end);
		i++;
	}
}

void	rest_direction(t_all *all, t_data *data, int x, int y)
{
	if (all->map[y][x] == 'S')
	{
		data->direction = M_PI / 2;
	}
	else if (all->map[y][x] == 'W')
	{
		data->direction = M_PI;
	}
	else if (all->map[y][x] == 'E')
	{
		data->direction = 0;
	}
}

void	find_player_position(t_all *all, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < all->y_of_map)
	{
		x = 0;
		while (x < all->longest_line)
		{
			if (all->map[y][x] == 'N' || all->map[y][x] == 'S'
				|| all->map[y][x] == 'W' || all->map[y][x] == 'E')
			{
				data->pos_x = x * TILE + TILE / 2;
				data->pos_y = y * TILE + TILE / 2;
				if (all->map[y][x] == 'N')
				{
					data->direction = 3 * M_PI / 2;
				}
				rest_direction(all, data, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	get_updown(double direction)
{
	if (direction >= 0 && direction <= M_PI)
		return (1);
	return (2);
}

int	get_facingdirection(double direction)
{
	if (direction <= M_PI / 2 || direction >= 2 * M_PI - M_PI / 2)
		return (1);
	return (2);
}
