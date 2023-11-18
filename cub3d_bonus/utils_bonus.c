/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:59:11 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:27:37 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	close_doors(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->all->y_of_map)
	{
		x = 0;
		while (x < data->all->longest_line)
		{
			if (data->all->map[y][x] == 'T')
				data->all->map[y][x] = 'D';
			x++;
		}
		y++;
	}
}

void	around_player(t_data *data, int x, int y)
{
	x = ((int)data->pos_x);
	y = ((int)data->pos_y);
	if ((data->all->map[y / TILE][x / TILE] != 'T') && (data->all->map[(y
				+ TILE) / TILE][x / TILE] != 'T') && (data->all->map[y
			/ TILE][(x + TILE) / TILE] != 'T') && (data->all->map[(y - TILE)
			/ TILE][x / TILE] != 'T') && (data->all->map[y / TILE][(x - TILE)
			/ TILE] != 'T') // side
		&& (data->all->map[(y + TILE) / TILE][(x + TILE) / TILE] != 'T')
			&& (data->all->map[(y + TILE) / TILE][(x - TILE) / TILE] != 'T')
			&& (data->all->map[(y - TILE) / TILE][(x + TILE) / TILE] != 'T')
			&& (data->all->map[(y - TILE) / TILE][(x - TILE) / TILE] != 'T'))
		close_doors(data);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, t_all_txt img)
{
	char	*dst;
	int		rect_x;
	int		rect_y;
	int		i;
	int		j;

	rect_x = x * MINI_TILE;
	rect_y = y * MINI_TILE;
	i = rect_x;
	j = rect_y;
	while (j < rect_y + MINI_TILE)
	{
		i = rect_x;
		while (i < rect_x + MINI_TILE)
		{
			dst = img.img_data + (j * img.len + i * (img.bits / 8));
			*(unsigned int *)dst = data->color;
			i++;
		}
		j++;
	}
}

void	check_char(t_data *data, int x, int y)
{
	if (data->all->map[y][x] == '1' || data->all->map[y][x] == 'A')
	{
		data->color = 0x0000FF;
		my_mlx_pixel_put(data, x, y, data->mini);
	}
	else if (data->all->map[y][x] == 'D')
	{
		data->color = 0xA52A2A;
		my_mlx_pixel_put(data, x, y, data->mini);
	}
	else
	{
		data->color = 0xFFFFFF;
		my_mlx_pixel_put(data, x, y, data->mini);
	}
}
