/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:58:59 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:26:21 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_square_player(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	*dst;

	i = 0;
	j = 0;
	x = data->pos_x / TILE * MINI_TILE;
	y = data->pos_y / TILE * MINI_TILE;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			dst = data->mini.img_data + ((y + i) * data->mini.len + (x + j)
					* (data->mini.bits / 8));
			if (x + j < data->all->x_of_map * MINI_TILE && y
				+ i < data->all->y_of_map * MINI_TILE)
				*(unsigned int *)dst = 0xFF0F00;
			j++;
		}
		i++;
	}
}

void	draw_around_player(t_data *data)
{
	char	*dst;
	int		x;
	int		y;

	x = ((data->pos_x / TILE) * MINI_TILE) - 100;
	if (x < 0)
		x = 0;
	y = ((data->pos_y / TILE) * MINI_TILE) - 100;
	if (y < 0)
		y = 0;
	data->big.img_ptr = mlx_new_image(data->mlx_ptr, 400, 200);
	data->big.img_data = mlx_get_data_addr(data->big.img_ptr, &data->big.bits,
			&data->big.len, &data->big.end);
	store_pixles(data, dst, x, y);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->big.img_ptr, 50,
		50);
}

void	renderminimap(t_data *data)
{
	int	x;
	int	y;
	int	width;
	int	height;

	x = 0;
	y = 0;
	width = data->all->x_of_map * MINI_TILE;
	height = data->all->y_of_map * MINI_TILE;
	data->mini.img_ptr = mlx_new_image(data->mlx_ptr, width, height);
	data->mini.img_data = mlx_get_data_addr(data->mini.img_ptr,
			&data->mini.bits, &data->mini.len, &data->mini.end);
	while (y < data->all->y_of_map)
	{
		x = 0;
		while (x < data->all->x_of_map)
		{
			check_char(data, x, y);
			x++;
		}
		y++;
	}
	draw_square_player(data);
	draw_around_player(data);
}

int	animation_img(t_data *data, int x, int y)
{
	if (data->all->map[y][x] == 'A')
	{
		if (data->frame > 4000)
			data->frame = 0;
		if (data->ani > 21)
			data->ani = 5;
		if (data->frame % 4000 == 0)
		{
			data->frame++;
			if (data->ani > 21)
				data->ani = 4;
			return (data->ani++);
		}
		data->frame++;
		return (data->ani);
	}
	return (0);
}

int	animation_spider(t_data *data, int x, int y)
{
	if (data->check == 1)
	{
		if (get_facingdirection(data->ray_angle) == 1)
		{
			if (data->space == 0)
				return (E);
			if (data->frame1 == 8000)
				data->frame1 = 0;
			if (data->frame1 % 8000 == 0)
			{
				data->frame1++;
				if (data->ani1 > 36)
					data->ani1 = 26;
				return (data->ani1++);
			}
			data->frame1++;
			if (data->ani1 > 36)
				data->ani1 = 26;
			return (data->ani1);
		}
		return (W);
	}
	return (0);
}
