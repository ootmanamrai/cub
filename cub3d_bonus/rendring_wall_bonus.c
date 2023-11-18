/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_wall_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:58:24 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:27:32 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	line_door(data);
	floor_sky(data);
	wall(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	renderminimap(data);
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

void	show_map(t_all *all, t_textr *txt)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	inistaill_data(data);
	data->mytable = malloc(sizeof(double) * (WIDTH_WIN * 2));
	data->garbage = all->garb;
	ft_lst_add_back(&data->garbage, ft_lst_new(data->mytable));
	data->all = all;
	data->txt = txt;
	all->x_of_map = all->longest_line;
	find_player_position(all, data);
	keys_init(data);
	data->mlx_ptr = mlx_init();
	initail_image(data);
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIDTH_WIN, HEIGHT_WIN,
			"CUB3D");
	data->img = mlx_new_image(data->mlx_ptr, WIDTH_WIN, HEIGHT_WIN);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	mlx_hook(data->mlx_win, 6, 1L, move_player_left_right, data);
	mlx_hook(data->mlx_win, 17, 0L, close_window, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, press_key, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, release_key, data);
	mlx_loop_hook(data->mlx_ptr, move_player, data);
	mlx_loop(data->mlx_ptr);
}
