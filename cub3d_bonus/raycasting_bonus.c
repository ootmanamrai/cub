/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:58:48 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:27:25 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	intercept_v(t_data *data)
{
	int	x;
	int	y;

	while (data->y_intercept >= 0 && data->y_intercept < TILE
		* data->all->y_of_map && data->x_intercept >= 0
		&& data->x_intercept < TILE * data->all->x_of_map)
	{
		x = data->x_intercept / TILE;
		y = data->y_intercept / TILE;
		if (y < data->all->y_of_map && x < data->all->x_of_map
			&& (data->all->map[y][x] == '1' || data->all->map[y][x] == 'D'
				|| data->all->map[y][x] == 'A'))
		{
			data->found_wallv = 1;
			break ;
		}
		data->y_intercept += data->y_step;
		data->x_intercept += data->x_step;
	}
	data->x_ver = data->x_intercept;
	data->y_ver = data->y_intercept;
}

void	distance(t_data *data, double direction)
{
	double	distancev;
	double	distanceh;

	distancev = INT_MAX;
	distanceh = INT_MAX;
	if (data->found_wallh == 1)
		distanceh = sqrt(pow(data->x_hor - data->pos_x, 2) + pow(data->y_hor
					- data->pos_y, 2));
	if (data->found_wallv == 1)
		distancev = sqrt(pow(data->x_ver - data->pos_x, 2) + pow(data->y_ver
					- data->pos_y, 2));
	ft_distence(data, distancev, distanceh, direction);
}

void	vert_cord(t_data *data, double direction)
{
	double	ray_angle;

	data->found_wallv = 0;
	ray_angle = direction;
	data->x_intercept = floor(data->pos_x / TILE) * TILE;
	if (get_facingdirection(ray_angle) == 1)
		data->x_intercept += TILE;
	else
		data->x_intercept -= 0.000001;
	data->y_intercept = data->pos_y + (data->x_intercept - data->pos_x)
		* tan(ray_angle);
	data->x_step = TILE;
	if (get_facingdirection(ray_angle) == 2)
		data->x_step *= -1;
	data->y_step = TILE * tan(ray_angle);
	if (get_updown(ray_angle) == 2 && data->y_step > 0)
		data->y_step *= -1;
	else if (get_updown(ray_angle) == 1 && data->y_step < 0)
		data->y_step *= -1;
	if (get_facingdirection(ray_angle) == 2)
		data->x_intercept -= 0.00000001;
	intercept_v(data);
	distance(data, direction);
}

void	intercept_h(t_data *data)
{
	int	x;
	int	y;

	while (data->y_intercept >= 0 && data->y_intercept < TILE
		* data->all->y_of_map && data->x_intercept >= 0
		&& data->x_intercept < TILE * data->all->x_of_map)
	{
		x = data->x_intercept / TILE;
		y = data->y_intercept / TILE;
		if ((y < data->all->y_of_map && x < data->all->x_of_map
				&& (data->all->map[y][x] == '1' || data->all->map[y][x] == 'D' \
					|| data->all->map[y][x] == 'A')))
		{
			data->found_wallh = 1;
			break ;
		}
		data->y_intercept += data->y_step;
		data->x_intercept += data->x_step;
	}
	data->x_hor = data->x_intercept;
	data->y_hor = data->y_intercept;
}

void	draw_ray(t_data *data, double direction)
{
	double	ray_angle;
	double	x;
	double	y;

	x = data->pos_x;
	y = data->pos_y;
	data->found_wallh = 0;
	ray_angle = direction;
	data->y_intercept = floor(data->pos_y / TILE) * TILE;
	if (get_updown(ray_angle) == 1)
		data->y_intercept += TILE;
	if (get_updown(ray_angle) == 2)
		data->y_intercept -= 0.000001;
	data->x_intercept = data->pos_x + (data->y_intercept - data->pos_y)
		/ tan(ray_angle);
	data->y_step = TILE;
	if (get_updown((ray_angle)) == 2)
		data->y_step *= -1;
	data->x_step = TILE / tan(ray_angle);
	if (get_facingdirection(ray_angle) == 2 && data->x_step > 0)
		data->x_step *= -1;
	else if (get_facingdirection(ray_angle) == 1 && data->x_step < 0)
		data->x_step *= -1;
	intercept_h(data);
	vert_cord(data, direction);
}
