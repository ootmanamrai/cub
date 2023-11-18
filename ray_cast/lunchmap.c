/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunchmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:30:44 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 02:34:38 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1111111111111111111
// 1000000000000100001
// 1111111111110N11101
// 1000000000000000101
// 1111111111111111101
// 1000000000000000001
// 1011111110011111101
// 1010000010010000001
// 1111011111111111111
// 1000000000000000001
// 1111111111111111111
void	my_mlx_pixel_put(t_data *data, int x, int y, t_all_txt img)
{
	char	*dst;
	int		rect_x;
	int		rect_y;
	int		y1;
	int		x1;
	int		i;
	int		j;

	y1 = MINI_TILE;
	x1 = MINI_TILE;
	rect_x = x * x1;
	rect_y = y * y1;
	i = rect_x;
	j = rect_y;
	while (j < rect_y + y1)
	{
		i = rect_x;
		while (i < rect_x + x1)
		{
			dst = img.img_data + (j * img.len + i * (img.bits / 8));
			*(unsigned int *)dst = data->color;
			i++;
		}
		j++;
	}
}
void	draw_line(t_data *data, double x_intercept, double y_intercept)
{
	char	*dst;
	double	dx;
	double	dy;
	double	steps;
	double	xIncrement;
	double	yIncrement;
	double	x;
	double	y;

	// Assuming that mlx_ptr and win_ptr are properly initialized
	// if(data->hi == 1)
	printf("x = %f y = %f\n", x_intercept / TILE, y_intercept / TILE);
	printf("x_player %d y_player %d\n", (int)(data->pos_x / TILE),
		(int)(data->pos_y / TILE));
	dx = x_intercept - (data->pos_x);
	dy = y_intercept - (data->pos_y);
	steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	xIncrement = dx / steps;
	yIncrement = dy / steps;
	x = (data->pos_x);
	y = (data->pos_y);
	for (int i = 0; i < steps; i++)
	{
		if (x < 0 || y < 0 || x >= TILE * 41 || y >= TILE * 10)
			break ;
		dst = data->mini.img_data + ((int)(y)*data->mini.len + ((int)x)
				* (data->mini.bits / 8));
		*(unsigned int *)dst = 0x0000FF;
		x += xIncrement;
		y += yIncrement;
	}
}

int	getupdown(double direction)
{
	if (direction >= 0 && direction <= M_PI)
		return (1);
	return (2);
}

int	getFacingDirection(double direction)
{
	if (direction <= M_PI / 2 || direction >= 2 * M_PI - M_PI / 2)
		return (1);
	return (2);
}

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
	if (distanceh < distancev)
	{
		data->check = 0;
		data->wall_hit_x = data->x_hor;
		data->wall_hit_y = data->y_hor;
		data->distance = distanceh;
	}
	else
	{
		data->check = 1;
		data->wall_hit_x = data->x_ver;
		data->wall_hit_y = data->y_ver;
		data->distance = distancev;
	}
	data->distance *= cos(data->direction - direction);
}

void	vert_cord(t_data *data, double direction)
{
	double	ray_angle;

	data->found_wallv = 0;
	ray_angle = direction;
	data->x_intercept = floor(data->pos_x / TILE) * TILE;
	if (getFacingDirection(ray_angle) == 1)
		data->x_intercept += TILE;
	else
		data->x_intercept -= 0.000001;
	data->y_intercept = data->pos_y + (data->x_intercept - data->pos_x)
		* tan(ray_angle);
	data->x_step = TILE;
	if (getFacingDirection(ray_angle) == 2)
		data->x_step *= -1;
	data->y_step = TILE * tan(ray_angle);
	if (getupdown(ray_angle) == 2 && data->y_step > 0)
		data->y_step *= -1;
	else if (getupdown(ray_angle) == 1 && data->y_step < 0)
		data->y_step *= -1;
	if (getFacingDirection(ray_angle) == 2)
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
				&& (data->all->map[y][x] == '1' || data->all->map[y][x] == 'D'
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
	double	x_step;
	double	y_step;
	char	*dst;

	x = data->pos_x;
	y = data->pos_y;
	data->found_wallh = 0;
	ray_angle = direction;
	data->y_intercept = floor(data->pos_y / TILE) * TILE;
	if (getupdown(ray_angle) == 1)
		data->y_intercept += TILE;
	if (getupdown(ray_angle) == 2)
		data->y_intercept -= 0.000001;
	data->x_intercept = data->pos_x + (data->y_intercept - data->pos_y)
		/ tan(ray_angle);
	data->y_step = TILE;
	if (getupdown((ray_angle)) == 2)
		data->y_step *= -1;
	data->x_step = TILE / tan(ray_angle);
	if (getFacingDirection(ray_angle) == 2 && data->x_step > 0)
		data->x_step *= -1;
	else if (getFacingDirection(ray_angle) == 1 && data->x_step < 0)
		data->x_step *= -1;
	intercept_h(data);
	vert_cord(data, direction);
}

int	get_pixel_color(t_data *data, int x, int y)
{
	int		color;
	char	*pixel;
	int		m;

	m = data->Nimg;
	pixel = data->imgs[m]->img_data + (y * data->imgs[m]->len + x
			* (data->imgs[m]->bits / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	init_data_txt(t_data *data)// take path
{
	int		i;
	int		x;
	char	*img;

	x = 0;
	i = 0;

	while (i < 37)
	{
		data->imgs[i] = malloc(sizeof(t_all_txt));
		ft_lst_add_back(&data->garbage, ft_lst_new(data->imgs[i]));
		if (i < 5)
			data->imgs[i]->path = data->txt->S[i];
		else
		{
			img = ft_strjoin(ft_itoa(i), "img.xpm");
			ft_lst_add_back(&data->garbage, ft_lst_new(img));
			data->imgs[i]->path = ft_strjoin("./tool_bonus/", img);
			ft_lst_add_back(&data->garbage, ft_lst_new(data->imgs[i]->path));
		}
		x = i;
		i++;
	}
	data->imgs[i] = NULL;
}

void	initail_image(t_data *data)//lead images
{
	int	i;

	i = 0;
	init_data_txt(data);
	while (i < 37)
	{
		data->imgs[i]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
				data->imgs[i]->path, &data->imgs[i]->width,
				&data->imgs[i]->height);
		if (!data->imgs[i]->img_ptr)
		{
			printf("file not exist\n");
			exit(0);
		}
		data->imgs[i]->img_data = mlx_get_data_addr(data->imgs[i]->img_ptr,
				&data->imgs[i]->bits, &data->imgs[i]->len, &data->imgs[i]->end);
		i++;
	}
}

int	get_color_at_coord(t_data *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->mini.img_data + (y * data->mini.len + x * (data->mini.bits
				/ 8));
	color = *(unsigned int *)dst;
	return (color);
}

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
			if (x + j < data->all->x_of_map * MINI_TILE && y
				+ i < data->all->y_of_map * MINI_TILE)
			{
				dst = data->mini.img_data + ((y + i) * data->mini.len + (x + j)
						* (data->mini.bits / 8));
				*(unsigned int *)dst = 0xFF0F00;
			}
			j++;
		}
		i++;
	}
}

void	draw_around_player(t_data *data)
{
	int				i;
	int				j;
	char			*dst;
	unsigned int	color;
	char			*pixel;
	int				x;
	int				y;

	i = 0;
	j = 0;
	x = ((data->pos_x / TILE) * MINI_TILE) - 100;
	if (x < 0)
		x = 0;
	y = ((data->pos_y / TILE) * MINI_TILE) - 100;
	if (y < 0)
		y = 0;
	data->big.img_ptr = mlx_new_image(data->mlx_ptr, 400, 200);
	data->big.img_data = mlx_get_data_addr(data->big.img_ptr, &data->big.bits,
			&data->big.len, &data->big.end);
	while (i < 200)
	{
		j = 0;
		while (j < 400)
		{
			if (x + j < data->all->x_of_map * MINI_TILE && y
				+ i < data->all->y_of_map * MINI_TILE)
				color = get_color_at_coord(data, x + j, i + y);
			else
				color = 0x0000FF;
			dst = data->big.img_data + (i * data->big.len + j * (data->big.bits
						/ 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->big.img_ptr, 50,
		50);
}

void	renderMiniMap(t_data *data)
{
	int		x;
	int		y;
	char	*dst;
	int		width;
	int		height;

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
			if (data->all->map[y][x] == '1' || data->all->map[y][x] == 'A')
			{
				data->color = 0x0000FF;
				my_mlx_pixel_put(data, x, y, data->mini);
			}
			else if (data->all->map[y][x] == 'D') // for bonus
			{
				data->color = 0xA52A2A;
				my_mlx_pixel_put(data, x, y, data->mini);
			}
			else
			{
				data->color = 0xFFFFFF;
				my_mlx_pixel_put(data, x, y, data->mini);
			}
			x++;
		}
		y++;
	}
	draw_square_player(data);
	draw_around_player(data);
}
int	get_ntxtr(t_data *data)
{
	int	x;
	int	y;
	int i;

	i = 0;
	x = data->wall_hit_x / TILE;
	y = data->wall_hit_y / TILE;
	if (data->all->map[y][x] == 'D')
	{
		return (4);
	}
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
	if (data->check == 1)
	{
		if (getFacingDirection(data->ray_angle) == 1)
		{
			if(data->space == 0)
				return (E);
			if (data->frame1 == 8000)
				data->frame1 = 0;
			if (data->frame1 % 8000 == 0)
			{
				data->frame1++;
				if (data->ani1 > 36)//24
				{
					data->ani1 = 26;
				}
				return (data->ani1++);
			}
			data->frame1++;
			if (data->ani1 > 36)
				data->ani1 = 26;
			return (data->ani1);
		
		}
		return (W);
	}
	else
	{
		if (getupdown(data->ray_angle) == 1)
			return (SO);
		return (N);
	}
	return (1);
}

void	draw_img(t_data *data)
{
	int	m;

	if (data->wall_height > HEIGHT_WIN)
	{
		m = HEIGHT_WIN;
		data->y_img = (data->wall_height - HEIGHT_WIN) / 2 / data->wall_height
			* data->imgs[data->Nimg]->height;
	}
	else
		m = (HEIGHT_WIN / 2) + (data->wall_height / 2);
	while (data->y_wind < m)
	{
		if (data->check == 1)
			data->x_img = ((data->wall_hit_y / TILE) - floor(data->wall_hit_y
						/ TILE)) * data->imgs[data->Nimg]->width;
		else if (data->check == 0)
			data->x_img = ((data->wall_hit_x / TILE) - floor(data->wall_hit_x
						/ TILE)) * data->imgs[data->Nimg]->width;
		data->dst = data->addr + (data->y_wind * data->line_length + data->i
				* (data->bits_per_pixel / 8));
		if (data->y_img >= data->imgs[data->Nimg]->height)
			data->y_img = data->imgs[data->Nimg]->height - 1;
		if (data->x_img >= data->imgs[data->Nimg]->width)
			data->x_img = data->imgs[data->Nimg]->width - 1;
		*(unsigned int *)data->dst = get_pixel_color(data, (int)data->x_img,
				(int)data->y_img);
		data->y_img += data->imgs[data->Nimg]->height / data->wall_height;
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
		data->Nimg = get_ntxtr(data);
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

void	line_door(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->dx = (int)data->pos_x + (60) * cos(data->direction);
	data->dy = (int)data->pos_y + (60) * sin(data->direction);
	x = data->dx / TILE;
	y = data->dy / TILE;
	if (data->all->map[y][x] == 'D')
	{
		data->all->map[y][x] = 'T';
		data->xd = x;
		data->yd = y;
	}
	else
	{
		x = ((int)data->pos_x);
		y = ((int)data->pos_y);
		if ((data->all->map[y / TILE][x / TILE] != 'T') && (data->all->map[(y
					+ TILE) / TILE][x / TILE] != 'T') && (data->all->map[y
				/ TILE][(x + TILE) / TILE] != 'T') && (data->all->map[(y - TILE)
				/ TILE][x / TILE] != 'T') && (data->all->map[y / TILE][(x
					- TILE) / TILE] != 'T') // side
			&& (data->all->map[(y + TILE) / TILE][(x + TILE) / TILE] != 'T')
				&& (data->all->map[(y + TILE) / TILE][(x - TILE) / TILE] != 'T')
				&& (data->all->map[(y - TILE) / TILE][(x + TILE) / TILE] != 'T')
				&& (data->all->map[(y - TILE) / TILE][(x - TILE)
				/ TILE] != 'T'))
		{
			close_doors(data);
		}
	}
}
void	draw_3D(t_data *data)
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
	renderMiniMap(data);
}

int	player_collision(t_data *data)
{
	int	x;
	int	y;
	int	y1;
	int	x1;

	x = data->pos_x;
	y = data->pos_y;
	y1 = TILE;
	x1 = TILE;
	if (data->all->map[(y + 5) / y1][(x + 5) / x1] == 'A')
		return (1);
	if (data->all->map[(y - 5) / y1][(x - 5) / x1] == 'A')
		return (1);
	if (data->all->map[(y - 5) / y1][x / x1] == 'A')
		return (1);
	if (data->all->map[y / y1][(x - 5) / x1] == 'A')
		return (1);
	if (data->all->map[y / y1][x / TILE] == 'A')
		return (1);
	if (data->all->map[(y + 5) / y1][(x + 5) / x1] == '1')
		return (1);
	if (data->all->map[(y - 5) / y1][(x - 5) / x1] == '1')
		return (1);
	if (data->all->map[(y - 5) / y1][x / x1] == '1')
		return (1);
	if (data->all->map[y / y1][(x - 5) / x1] == '1')
		return (1);
	if (data->all->map[y / y1][x / TILE] == '1')
		return (1);
	if (data->all->map[(y + 5) / y1][x / x1] == 'D')
		return (1);
	if (data->all->map[y / y1][(x + 5) / x1] == 'D')
		return (1);
	if (data->all->map[(y - 5) / y1][x / x1] == 'D')
		return (1);
	if (data->all->map[y / y1][(x - 5) / x1] == 'D')
		return (1);
	if (data->all->map[(y + 5) / y1][(x + 5) / x1] == 'D')
		return (1);
	return (0);
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
	if(key == SPACE && data->space == 0)
		data->space = 1;
	else if(key == SPACE && data->space == 1)
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
	draw_3D(data);
	return (0);
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
				if (all->map[y][x] == 'N')
				{
					data->direction = 3 * M_PI / 2;
				}
				else if (all->map[y][x] == 'S')
				{
					data->direction = M_PI / 2;
				}
				else if (all->map[y][x] == 'W')
				{
					data->direction = M_PI;
				}
				else if (all->map[y][x] == 'E')
				{
					data->direction = 0;
				}
				return ;
			}
			x++;
		}
		y++;
	}
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

void	show_map(t_all *all, t_textr *txt)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->hi = 0;
	data->xd = 0;
	data->yd = 0;
	data->check = 0;
	data->ani = 7;
	data->frame = 0;
	data->ani1 = 26;
	data->frame1 = 0;
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
// note to do ...
// 1, player in other direction
// 2, optimise the width and height of map
// convert to square
// optimise the window size
// in check if texture is null 225 line dont add mlx destroy becausw it will sgv in it