/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:09:46 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:25:33 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	demons(t_data *data)
{
	if (data->y_img >= data->imgs[data->nimg]->height)
		data->y_img = data->imgs[data->nimg]->height - 1;
	if (data->x_img >= data->imgs[data->nimg]->width)
		data->x_img = data->imgs[data->nimg]->width - 1;
}

void	line_door(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->dx = (int)data->pos_x + (60) * cos(data->direction);
	data->dy = (int)data->pos_y + (60) * sin(data->direction);
	x = data->dx / TILE;
	y = data->dy / TILE;
	if (data->all->map[y][x] == 'D')
	{
		data->all->map[y][x] = 'T';
		data->xd = x;
		data->yd = y;
	}
	else
		around_player(data, x, y);
}

int	collision_animation(t_data *data, int x, int y)
{
	if (data->all->map[(y + 5) / TILE][(x + 5) / TILE] == 'A')
		return (1);
	if (data->all->map[(y - 5) / TILE][(x - 5) / TILE] == 'A')
		return (1);
	if (data->all->map[(y - 5) / TILE][x / TILE] == 'A')
		return (1);
	if (data->all->map[y / TILE][(x - 5) / TILE] == 'A')
		return (1);
	if (data->all->map[y / TILE][x / TILE] == 'A')
		return (1);
	return (0);
}

int	collision_door(t_data *data, int x, int y)
{
	if (data->all->map[(y + 5) / TILE][x / TILE] == 'D')
		return (1);
	if (data->all->map[y / TILE][(x + 5) / TILE] == 'D')
		return (1);
	if (data->all->map[(y - 5) / TILE][x / TILE] == 'D')
		return (1);
	if (data->all->map[y / TILE][(x - 5) / TILE] == 'D')
		return (1);
	if (data->all->map[(y + 5) / TILE][(x + 5) / TILE] == 'D')
		return (1);
	return (0);
}

int	player_collision(t_data *data)
{
	int	x;
	int	y;
	int	y1;
	int	x1;

	x = data->pos_x;
	y = data->pos_y;
	y1 = TILE;
	x1 = TILE;
	if (data->all->map[(y + 5) / y1][(x + 5) / x1] == '1')
		return (1);
	if (data->all->map[(y - 5) / y1][(x - 5) / x1] == '1')
		return (1);
	if (data->all->map[(y - 5) / y1][x / x1] == '1')
		return (1);
	if (data->all->map[y / y1][(x - 5) / x1] == '1')
		return (1);
	if (data->all->map[y / y1][x / TILE] == '1')
		return (1);
	if (collision_door(data, x, y) == 1)
		return (1);
	if (collision_animation(data, x, y) == 1)
		return (1);
	return (0);
}
