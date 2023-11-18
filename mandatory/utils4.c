/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:41:22 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:58:17 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_distence(t_data *data, double distv, double disth, double direction)
{
	if (disth < distv)
	{
		data->check = 0;
		data->wall_hit_x = data->x_hor;
		data->wall_hit_y = data->y_hor;
		data->distance = disth;
	}
	else
	{
		data->check = 1;
		data->wall_hit_x = data->x_ver;
		data->wall_hit_y = data->y_ver;
		data->distance = distv;
	}
	data->distance *= cos(data->direction - direction);
}

void	demons(t_data *data)
{
	if (data->y_img >= data->imgs[data->nimg]->height)
		data->y_img = data->imgs[data->nimg]->height - 1;
	if (data->x_img >= data->imgs[data->nimg]->width)
		data->x_img = data->imgs[data->nimg]->width - 1;
}

int	check_height(t_data *data)
{
	int	m;

	if (data->wall_height > HEIGHT_WIN)
	{
		m = HEIGHT_WIN;
		data->y_img = (data->wall_height - HEIGHT_WIN) / 2 / data->wall_height
			* data->imgs[data->nimg]->height;
	}
	else
		m = (HEIGHT_WIN / 2) + (data->wall_height / 2);
	return (m);
}
