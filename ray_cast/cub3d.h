/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:09:47 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 02:30:02 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include "../file.h"
#define TILE 64
#define MINI_TILE 20
#define WIDTH_WIN 1200
#define HEIGHT_WIN 1200
#if defined(__linux__)
    #define KEY_ESC 65307
    #define KEY_UP 5
    #define KEY_DOWN 5
    #define KEY_LEFT 65361
    #define KEY_RIGHT 65363
    #define KEY_W 119
    #define KEY_A 97
    #define KEY_S 115
    #define KEY_D 100
    #define SHIFT 1
    #define E 3
    #define W 2
    #define N 0
    #define SO 1
#elif defined(__APPLE__)
    #define KEY_ESC 53
    #define KEY_UP 126
    #define KEY_DOWN 125
    #define KEY_LEFT 123
    #define KEY_RIGHT 124
    #define KEY_W 13
    #define KEY_A 0
    #define KEY_S 1
    #define KEY_D 2
    #define SPEED 8
    #define SIDES_SPEED 10
    #define ROTATION_ANGLE 0.05
    #define SHIFT 0
    #define E 3
    #define W 2
    #define N 0
    #define SO 1
    #define SPACE 49
#endif
void    show_map();
int extra_check(char **map);
typedef struct s_txt_data
{
    void *img_ptr;
    char *img_data;
   int width;
   int height;
   int end;
   int len;
   int bits;
   char *path;
}   t_all_txt;

typedef struct	s_data {
    t_all_txt *imgs[37];
    t_all_txt mini;
    t_all_txt big;
    int frame1;
    int Nimg1;
    int frame2;
    int ani1;
    int xd;
    int yd;
    int dx;
    int dy;
    int ani;
    int space;
    int frame;
    int color;
    int mouse_left;
    int mouse_right;
    int hi;
	double 	direction;
    char *dst;
    int old_x;
    int old_y;
    int i;
    int y_wind;
    double y_img;
    double x_img;
    int x_wind;
    int Nimg;
    int check;
    int key_press;
    char **img_data;
    void **img_ptr;
    int *checke;
    double *all_xrays;
    double *all_yrays;
    double *mytable;
    double x_ver;
    double y_ver;
    double x_hor;
    double y_hor;
    double x_low;
    
    double y_low;
    double dist_proj_plane;
    double *all_rays;
    double found_wallh;
    double found_wallv;
    double     fov;
    double    ray_x;
    double    ray_y;
    double    angle;
    double    ray_angle;
    double    wall_hit_x;
    double    wall_hit_y;
    double    distance;
    double    wall_height;
    double    next_touch_x;
    double    next_touch_y;
    double    x_to_check;
    double    y_to_check;
    double    x_intercept;
    double    y_intercept;
    double    x_step;
    double    y_step;
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
    t_all *all;
    t_textr *txt;
    t_garbage *garbage;
    int  key_right;
    int key_left;
    int key_a;
    int key_d;
    int key_w;
    int key_s;
    
}				t_data;

#endif