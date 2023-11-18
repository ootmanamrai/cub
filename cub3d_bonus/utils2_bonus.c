/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:10:57 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:27:45 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_pixel_color(t_data *data, int x, int y)
{
	int		color;
	char	*pixel;
	int		m;

	m = data->nimg;
	pixel = data->imgs[m]->img_data + (y * data->imgs[m]->len + x
			* (data->imgs[m]->bits / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	init_data_txt(t_data *data)
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

void	initail_image(t_data *data)
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

int	get_ntxtr(t_data *data)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = data->wall_hit_x / TILE;
	y = data->wall_hit_y / TILE;
	if (data->all->map[y][x] == 'D')
	{
		return (4);
	}
	if (animation_img(data, x, y))
		return (animation_img(data, x, y));
	if (animation_spider(data, x, y))
		return (animation_spider(data, x, y));
	else
	{
		if (get_updown(data->ray_angle) == 1)
			return (SO);
		return (N);
	}
	return (1);
}
