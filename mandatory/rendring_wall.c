/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 03:49:39 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:57:16 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_img(t_data *data)
{
	int	m;

	m = check_height(data);
	while (data->y_wind < m)
	{
		if (data->check == 1)
			data->x_img = ((data->wall_hit_y / TILE) - floor(data->wall_hit_y
						/ TILE)) * data->imgs[data->nimg]->width;
		else if (data->check == 0)
			data->x_img = ((data->wall_hit_x / TILE) - floor(data->wall_hit_x
						/ TILE)) * data->imgs[data->nimg]->width;
		data->dst = data->addr + (data->y_wind * data->line_length + data->i
				* (data->bits_per_pixel / 8));
		demons(data);
		*(unsigned int *)data->dst = get_pixel_color(data, (int)data->x_img,
				(int)data->y_img);
		data->y_img += data->imgs[data->nimg]->height / data->wall_height;
		data->y_wind++;
	}
}

void	wall(t_data *data)
{
	data->i = 0;
	while (data->i < WIDTH_WIN)
	{
		if (data->ray_angle > 2 * M_PI)
			data->ray_angle = data->ray_angle - 2 * M_PI;
		draw_ray(data, data->ray_angle);
		data->nimg = get_ntxtr(data);
		data->ray_angle += data->fov / WIDTH_WIN;
		data->dist_proj_plane = (HEIGHT_WIN / 2) / tan(data->fov / 2);
		data->wall_height = (TILE / data->distance) * data->dist_proj_plane;
		data->y_wind = (HEIGHT_WIN / 2) - (data->wall_height / 2);
		if (data->y_wind < 0)
			data->y_wind = 0;
		data->y_img = 0;
		draw_img(data);
		data->i++;
	}
}

void	floor_sky(t_data *data)
{
	int				x;
	unsigned int	sky;
	unsigned int	gorund;
	char			*dst;

	x = 0;
	sky = data->all->txt->F_CLOR;
	gorund = data->all->txt->C_CLOR;
	while (x < WIDTH_WIN * HEIGHT_WIN)
	{
		dst = data->addr + (x * (data->bits_per_pixel / 8));
		if (x < (HEIGHT_WIN / 2) * WIDTH_WIN)
			*(unsigned int *)dst = sky;
		else
			*(unsigned int *)dst = gorund;
		x++;
	}
}

void	draw_3d(t_data *data)
{
	int		x;
	int		i;
	char	*dst;
	int		y;

	x = 0;
	i = 0;
	y = 0;
	data->fov = 60 * (M_PI / 180);
	data->ray_angle = data->direction - (data->fov / 2);
	floor_sky(data);
	wall(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
}

int	move_player(t_data *data)
{
	double	direction;

	data->old_x = data->pos_x;
	data->old_y = data->pos_y;
	if (data->key_a == 1)
	{
		data->pos_x -= cos(data->direction + M_PI_2) * SIDES_SPEED;
		data->pos_y -= sin(data->direction + M_PI_2) * SIDES_SPEED;
	}
	if (data->key_d == 1)
	{
		data->pos_x += cos(data->direction + M_PI_2) * SIDES_SPEED;
		data->pos_y += sin(data->direction + M_PI_2) * SIDES_SPEED;
	}
	else if (data->key_w == 1 || data->key_s == 1)
	{
		direction = data->direction;
		if (data->key_s == 1)
			direction = data->direction + M_PI;
		data->pos_y += sin(direction) * SPEED;
		data->pos_x += cos(direction) * SPEED;
	}
	sides(data);
	draw_3d(data);
	return (0);
}
