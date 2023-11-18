/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:12:22 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:27:52 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	move_player_left_right(int x, int y, t_data *data)
{
	static double	mousse_position = 0;

	if (mousse_position == 0)
	{
		mousse_position = x;
		return (0);
	}
	if (x > WIDTH_WIN || y > HEIGHT_WIN || x < 0 || y < 0)
		return (0);
	if (x >= mousse_position)
	{
		data->direction += (0.009) * fabs((double)x - mousse_position);
		if (data->direction < 0)
			data->direction = 2 * M_PI + data->direction;
	}
	else
	{
		data->direction -= (0.009) * fabs((double)x - mousse_position);
		if (data->direction < 0)
			data->direction = 2 * M_PI + data->direction;
	}
	mousse_position = x;
	return (1);
}

void	inistaill_data(t_data *data)
{
	data->hi = 0;
	data->xd = 0;
	data->yd = 0;
	data->check = 0;
	data->ani = 7;
	data->frame = 0;
	data->ani1 = 26;
	data->frame1 = 0;
}
