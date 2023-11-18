/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:30:44 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:28:03 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// void	draw_line(t_data *data, double x_intercept, double y_intercept)
// {
// 	char	*dst;
// 	double	dx;
// 	double	dy;
// 	double	steps;
// 	double	xIncrement;
// 	double	yIncrement;
// 	double	x;
// 	double	y;

// 	dx = x_intercept - (data->pos_x);
// 	dy = y_intercept - (data->pos_y);
// 	steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
// 	xIncrement = dx / steps;
// 	yIncrement = dy / steps;
// 	x = (data->pos_x);
// 	y = (data->pos_y);
// 	for (int i = 0; i < steps; i++)
// 	{
// 		if (x < 0 || y < 0 || x >= TILE * 41 || y >= TILE * 10)
// 			break ;
// 		dst = data->mini.img_data + ((int)(y)*data->mini.len + ((int)x)
// 				* (data->mini.bits / 8));
// 		*(unsigned int *)dst = 0x0000FF;
// 		x += xIncrement;
// 		y += yIncrement;
// 	}
// }

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

int	get_updown(double direction)
{
	if (direction >= 0 && direction <= M_PI)
		return (1);
	return (2);
}

int	get_facingdirection(double direction1)
{
	if (direction1 <= M_PI / 2 || direction1 >= 2 * M_PI - M_PI / 2)
		return (1);
	return (2);
}
