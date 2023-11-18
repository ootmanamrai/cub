/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 03:55:48 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:39:30 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color(t_data *data, int x, int y)
{
	int		color;
	char	*pixel;
	int		m;

	m = data->nimg;
	pixel = data->imgs[m]->img_data + (y * data->imgs[m]->len + x
			* (data->imgs[m]->bits / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	init_data_txt(t_data *data)
{
	int		i;
	int		x;
	char	*img;

	x = 0;
	i = 0;
	while (i < 5)
	{
		data->imgs[i] = malloc(sizeof(t_all_txt));
		ft_lst_add_back(&data->garbage, ft_lst_new(data->imgs[i]));
		data->imgs[i]->path = data->txt->S[i];
		x = i;
		i++;
	}
	data->imgs[i] = NULL;
}

int	get_ntxtr(t_data *data)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = data->wall_hit_x / TILE;
	y = data->wall_hit_y / TILE;
	if (data->check == 1)
	{
		if (get_facingdirection(data->ray_angle) == 1)
			return (E);
		return (W);
	}
	else
	{
		if (get_updown(data->ray_angle) == 1)
			return (SO);
		return (N);
	}
	return (1);
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
	return (0);
}

void	sides(t_data *data)
{
	if (data->key_left == 1 || data->mouse_left == 1)
	{
		data->direction -= ROTATION_ANGLE;
		if (data->direction < 0)
			data->direction = 2 * M_PI + data->direction;
	}
	else if (data->key_right == 1 || data->mouse_right == 1)
	{
		data->direction += ROTATION_ANGLE;
		if (data->direction > 2 * M_PI)
			data->direction = data->direction - 2 * M_PI;
	}
	if (player_collision(data) == 1)
	{
		data->pos_x = data->old_x;
		data->pos_y = data->old_y;
		return ;
	}
}
