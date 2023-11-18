/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 03:52:20 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:38:53 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	release_key(int key, t_data *data)
{
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_A)
		data->key_a = 0;
	if (key == KEY_D)
		data->key_d = 0;
	if (key == KEY_W)
		data->key_w = 0;
	if (key == KEY_S)
		data->key_s = 0;
	if (key == KEY_LEFT)
		data->key_left = 0;
	if (key == KEY_RIGHT)
		data->key_right = 0;
	data->mouse_left = 0;
	data->mouse_right = 0;
	return (0);
}

void	keys_init(t_data *data)
{
	data->key_a = 0;
	data->space = 0;
	data->mouse_left = 0;
	data->mouse_right = 0;
	data->key_s = 0;
	data->key_d = 0;
	data->key_w = 0;
	data->key_left = 0;
	data->key_right = 0;
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
}

void	show_map(t_all *all, t_textr *txt)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->check = 0;
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
	mlx_hook(data->mlx_win, 17, 0L, close_window, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, press_key, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, release_key, data);
	mlx_loop_hook(data->mlx_ptr, move_player, data);
	mlx_loop(data->mlx_ptr);
}
