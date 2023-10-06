/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:09:47 by otamrani          #+#    #+#             */
/*   Updated: 2023/10/04 17:20:08 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>
void    show_map();
typedef struct	s_data {
	double 	direction;
	double 	rotation_speed;
	void	*mlx;
	void	*mlx_win;
	void    *mlx_ptr;
	double	pos_x;
	double   pos_y;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#endif