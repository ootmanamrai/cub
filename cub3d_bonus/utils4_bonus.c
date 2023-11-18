/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:14:22 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:27:57 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	store_pixles(t_data *data, char *dst, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 400)
		{
			dst = data->big.img_data + (i * data->big.len + j * (data->big.bits
						/ 8));
			if (x + j < data->all->x_of_map * MINI_TILE && y
				+ i < data->all->y_of_map * MINI_TILE)
				*(unsigned int *)dst = get_color_at_coord(data, x + j, i + y);
			else
				*(unsigned int *)dst = 0x0000FF;
			j++;
		}
		i++;
	}
}

int	press_key(int key, t_data *data)
{
	if (key == KEY_A)
		data->key_a = 1;
	if (key == KEY_D)
		data->key_d = 1;
	if (key == KEY_W)
		data->key_w = 1;
	if (key == KEY_S)
		data->key_s = 1;
	if (key == KEY_LEFT)
		data->key_left = 1;
	if (key == KEY_RIGHT)
		data->key_right = 1;
	if (key == SPACE && data->space == 0)
		data->space = 1;
	else if (key == SPACE && data->space == 1)
		data->space = 0;
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

void	store_data(t_data *data, int x, int y)
{
	if (data->all->map[y][x] == 'N')
		data->direction = 3 * M_PI / 2;
	else if (data->all->map[y][x] == 'S')
		data->direction = M_PI / 2;
	else if (data->all->map[y][x] == 'W')
		data->direction = M_PI;
	else if (data->all->map[y][x] == 'E')
		data->direction = 0;
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
				return ;
			}
			x++;
		}
		y++;
	}
}
