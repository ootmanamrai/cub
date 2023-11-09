/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunchmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:30:44 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/09 15:56:55 by otamrani         ###   ########.fr       */
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
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;
    int rect_x;
    int rect_y;
    int y1 = (900 / data->all->y_of_map) *0.2;
    int x1 = (1300 / data->all->x_of_map) *0.2;
    rect_x = x * x1;
    rect_y = y * y1;
    int i = rect_x;
    int j = rect_y;
    while(j < rect_y + y1)
    {
        i = rect_x;
        while(i < rect_x + x1)
        {
            dst = data->addr + (j * data->line_length + i * (data->bits_per_pixel / 8));
            *(unsigned int *)dst = color;
            i++;
        }
        j++;
    }
    
}
void draw_line(t_data *data, double x_intercept, double y_intercept)
{

    // Assuming that mlx_ptr and win_ptr are properly initialized
    char *dst;
    double dx = x_intercept - (data->pos_x *0.2);
    double dy = y_intercept - (data->pos_y*0.2 );
    double steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    double xIncrement = dx / steps;
    double yIncrement = dy / steps;
    double x = data->pos_x *0.2;
    double y = data->pos_y*0.2 ;

    for (int i = 0; i < steps; i++) {
        if(x < 0 || y < 0 || x >= 1300 || y >= 900)
            break;
         dst = data->addr + ((int)(y)  * data->line_length + ((int)x) * (data->bits_per_pixel / 8));
             *(unsigned int *)dst = 0x0000FF;
        x += xIncrement;
        y += yIncrement;
    }
}

int getupdown(double direction)
{
    if(direction >= 0 && direction <= M_PI)
        return(1);
    return(2);
}

int getFacingDirection(double direction) {
    if(direction <= M_PI / 2 || direction >= 2 * M_PI - M_PI / 2)
            return(1);
    return(2);
}
void intercept_v(t_data *data)
{
    while (data->y_intercept >= 0 && data->y_intercept < 900 && data->x_intercept >= 0 && data->x_intercept < 1300) {
    int x = data->x_intercept / (1300 / data->all->x_of_map);
    int y = data->y_intercept / (900 / data->all->y_of_map);
    if (y < data->all->y_of_map && x < data->all->x_of_map && data->all->map[y][x] == '1') {
        data->found_wallv = 1;
        break;
    }
    data->y_intercept += data->y_step;
    data->x_intercept += data->x_step;
}
    data->x_ver = data->x_intercept;
    data->y_ver = data->y_intercept;

}
void distance(t_data *data, double direction)
{

    double distancev;
    double distanceh;
    distancev = INT_MAX;
    distanceh = INT_MAX;
    if (data->found_wallh == 1) 
        distanceh = sqrt(pow(data->x_hor - data->pos_x, 2) + pow(data->y_hor - data->pos_y, 2));
    if (data->found_wallv == 1)
        distancev = sqrt(pow(data->x_ver - data->pos_x, 2) + pow(data->y_ver - data->pos_y, 2));
    if (distanceh < distancev) {
        data->check = 0;
        data->wall_hit_x = data->x_hor;
        data->wall_hit_y = data->y_hor;
        data->distance = distanceh;
    } else {
        data->check = 1;
        data->wall_hit_x = data->x_ver;
        data->wall_hit_y = data->y_ver;
        data->distance = distancev;
        }
    data->distance *= cos(data->direction - direction);
}
void  vert_cord(t_data *data, double direction)
{
    double ray_angle;
    data->found_wallv = 0;
    ray_angle = direction;
    data->x_intercept = floor(data->pos_x / (1300 / data->all->x_of_map)) * (1300 / data->all->x_of_map);
    if (getFacingDirection(ray_angle) == 1)
        data->x_intercept += (1300 / data->all->x_of_map);
    else 
        data->x_intercept -= 0.00000001;
    data->y_intercept = data->pos_y + (data->x_intercept - data->pos_x) * tan(ray_angle);
    data->x_step = (1300 / data->all->x_of_map);
    if (getFacingDirection(ray_angle) == 2)
        data->x_step *= -1;
    data->y_step = (1300 / data->all->x_of_map) * tan(ray_angle);
    if (getupdown(ray_angle) == 2 && data->y_step > 0) 
        data->y_step *= -1;
    else if (getupdown(ray_angle) == 1 && data->y_step < 0) 
        data->y_step *= -1;
    if (getFacingDirection(ray_angle) == 2) 
        data->x_intercept -= 0.00000001;
        intercept_v(data);
        distance(data, direction);
}
void intercept_h(t_data *data)
{
    while (data->y_intercept >= 0 && data->y_intercept < 900 && data->x_intercept >= 0 && data->x_intercept < 1300)
    {
        int x = data->x_intercept / (1300 / data->all->x_of_map);
        int y = data->y_intercept / (900 / data->all->y_of_map);
        if ((y < data->all->y_of_map && x < data->all->x_of_map && data->all->map[y][x] == '1'))
        {
            data->found_wallh = 1;
            break;
        }
        data->y_intercept += data->y_step;
        data->x_intercept += data->x_step;
    }
    data->x_hor = data->x_intercept;
    data->y_hor = data->y_intercept;
   
}
void draw_ray(t_data *data, double direction)
{
    double ray_angle;
    double x = data->pos_x;
    double y = data->pos_y;
    double x_step;
    double y_step;
    data->found_wallh = 0;
    char *dst;
    ray_angle = direction;
    data->y_intercept = floor(data->pos_y / (900 / data->all->y_of_map)) * (900 / data->all->y_of_map);
    if(getupdown(ray_angle) == 1)
        data->y_intercept += (900 / data->all->y_of_map);
    if(getupdown(ray_angle) == 2)
        data->y_intercept -= 0.000001;
    data->x_intercept = data->pos_x + (data->y_intercept - data->pos_y) / tan(ray_angle);
    data->y_step = (900/ data->all->y_of_map);
    if(getupdown((ray_angle)) == 2)
        data->y_step *= -1;
    data->x_step = (900 / data->all->y_of_map)/ tan(ray_angle);
    if(getFacingDirection(ray_angle) == 2 && data->x_step > 0)
        data->x_step *= -1;
    else if(getFacingDirection(ray_angle) == 1 && data->x_step < 0)
        data->x_step *= -1;
    intercept_h(data);
    vert_cord(data, direction);
}


int get_pixel_color(t_data *data, int x, int y)
{
    int color;
    char *pixel;
    int m = data->Nimg;
    pixel = data->imgs[m]->img_data + (y * data->imgs[m]->len + x * (data->imgs[m]->bits / 8));
    color = *(unsigned int *)pixel;
    return color;
}
void init_data_txt(t_data *data)
{
  int i;
  i = 0;
  while(i < 4)
  {
    data->imgs[i] = malloc(sizeof(t_all_txt));
    ft_lst_add_back(&data->garbage, ft_lst_new(data->imgs[i]));
    data->imgs[i]->path = data->txt->S[i];
    i++;
  }
    data->imgs[i] = NULL;
}
void initail_image(t_data *data)
{
    char *tmp;
    char *tmp1;
    int i = 0;
   init_data_txt(data);
    while(i < 4)
    {
    data->imgs[i]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->imgs[i]->path, &data->imgs[i]->width, &data->imgs[i]->height);
    if(data->imgs[i]->img_ptr == NULL)
        {
            printf("file not exist\n");
            mlx_destroy_window(data->mlx_ptr, data->mlx_win);
            exit(4);
        }
    if(!data->imgs[i]->img_ptr)
    {
       mlx_destroy_window(data->mlx_ptr, data->mlx_win);
         exit(0);
    }
    data->imgs[i]->img_data = mlx_get_data_addr(data->imgs[i]->img_ptr, &data->imgs[i]->bits, &data->imgs[i]->len, &data->imgs[i]->end);
        i++;
    }
}

void renderMiniMap(t_data *data)
{
    int x = 0;
    int y = 0;
    int y1 = (900 / data->all->y_of_map);
    int x1 = (1300 / data->all->x_of_map);
    int color;
    while(y < data->all->y_of_map)
    {
        x = 0;
        while(x < data->all->x_of_map)
        {
            color = (data->all->map[y][x] == '1') ? 0x000000 : 0xFFFFFF;
            my_mlx_pixel_put(data, x * x1, y * y1, color);
            x++;
        }
        y++;
    }
    color = 0x000000;
    my_mlx_pixel_put(data, (int)(data->pos_x * 0.2), (int)(data->pos_y * 0.2), color);
}

int get_ntxtr(t_data *data)
{
    if(data->check == 1)
    {
        if(getFacingDirection(data->ray_angle) == 1)
            return(E);
        return(W);
    }
    else{
        if(getupdown(data->ray_angle) == 1)
            return(SO);
        return(N);
        }
}
void draw_img(t_data *data)
{
    int m;
     if (data->wall_height > 900) {
            m = 900;
            data->y_img = (data->wall_height - 900) / 2 / data->wall_height * data->imgs[data->Nimg]->height;
        } else
            m = (900 / 2) + (data->wall_height / 2);
         while (data->y_wind < m) {
            if (data->check == 1) {
                data->x_img = ((data->wall_hit_y / (900 / 7) ) - floor(data->wall_hit_y / (900 / 7))) * data->imgs[data->Nimg]->width;
            } else if (data->check == 0)
                data->x_img = ((data->wall_hit_x / (1300 / 17)) - floor(data->wall_hit_x / (1300 / 17))) * data->imgs[data->Nimg]->width;
            data->dst = data->addr + (data->y_wind * data->line_length + data->i * (data->bits_per_pixel / 8));
            if (data->y_img >= data->imgs[data->Nimg]->height)
                data->y_img = data->imgs[data->Nimg]->height - 1;
            if (data->x_img >= data->imgs[data->Nimg]->width)
                data->x_img = data->imgs[data->Nimg]->width - 1;
            *(unsigned int *)data->dst = get_pixel_color(data, (int)data->x_img, (int)data->y_img);
            data->y_img += data->imgs[data->Nimg]->height / data->wall_height;
            data->y_wind++;
        }
}
void wall(t_data *data)
{
    data->i = 0;
    while(data->i < 1300)
    {
    if(data->ray_angle > 2 * M_PI)
        data->ray_angle = data->ray_angle - 2 * M_PI;
    draw_ray(data, data->ray_angle);
    data->Nimg = get_ntxtr(data);
    data->ray_angle += data->fov / 1300;
    data->dist_proj_plane = (900 / 2) / tan(data->fov / 2);
    data->wall_height = ((900 / 10) / data->distance) * data->dist_proj_plane;
    data->y_wind = (900 / 2) - (data->wall_height / 2);
    if (data->y_wind < 0)
         data->y_wind = 0;
    data->y_img = 0;
    draw_img(data);
       data->i++;
    }
}
void floor_sky(t_data *data)
{
    int x = 0;
    unsigned int sky;
    unsigned int gorund;
    sky = data->all->txt->F_CLOR;
    gorund = data->all->txt->C_CLOR;
    while (x < 1300 * 900)
    {
        char *dst;
        dst = data->addr + (x * (data->bits_per_pixel / 8));
        if(x < 450 * 1300)
            *(unsigned int *)dst = 0xFF00FF;
        else
            *(unsigned int *)dst = 0xFF0F00;
            x++;
    }
}
void draw_3D(t_data *data)
{
    int x = 0;
    int i = 0;
    char *dst;
    int y = 0;
    data->fov = 60 * (M_PI / 180);
    data->ray_angle = data->direction - (data->fov / 2);
    data->all_rays = malloc(sizeof(double) * 1300);
    ft_lst_add_back(&data->garbage, ft_lst_new(data->all_rays));
    floor_sky(data);
    initail_image(data);
    wall(data);
    int color;
   while(y < data->all->y_of_map)
   {
       x = 0;
       while(x < data->all->longest_line)
       {
           color = (data->all->map[y][x] == '1') ? 0x000000 : 0xFFFFFF;
           my_mlx_pixel_put(data, x, y, color);
           x++;
       }
       y++;
   }
    color = 0x000000;
    dst = data->addr + ((int)(data->pos_y * 0.2) * data->line_length + ((int)(data->pos_x * 0.2) * (data->bits_per_pixel / 8)));
             *(unsigned int *)dst = color;
   //  renderMiniMap(data);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
}

int player_collision(t_data *data)
{
    int x = data->pos_x;
    int y = data->pos_y;
    int y1 = (900 / data->all->y_of_map);
    int x1 = (1300 / data->all->x_of_map);
    // printf("first %c\n", data->all->map[y / y1][x / x1]);
    // printf("twoo %c\n", data->all->map[(y + 10) / y1][(x + 10) / x1]);
    // printf("three %c\n", data->all->map[(y + 10) / y1][x / x1]);
    // printf("four %c\n", data->all->map[y / y1][(x + 10) / x1]);
    if(data->all->map[y / y1][x / x1] == '1')
        return(1);
    // else if(data->all->map[(y + 1) / y1][(x + 1) / x1] == '1')
    //     return(1);
    // else if(data->all->map[(y + 1) / y1][x / x1] == '1')
    //         return(1);
    // else if(data->all->map[y / y1][(x + 1) / x1] == '1')

    //             return(1);
    return(0);
}

int press_key(int key, t_data *data)
{
    if(key == KEY_A)
        data->key_a = 1;
    if(key == KEY_D)
        data->key_d = 1;
    if(key == KEY_W)
        data->key_w = 1;
    if(key == KEY_S)
        data->key_s = 1;
    if(key == KEY_LEFT)
        data->key_left = 1;
    if(key == KEY_RIGHT)
        data->key_right = 1;
    return(0);
}
void sides(t_data *data)
{
    if(data->key_left == 1)
    {
        data->direction -= ROTATION_ANGLE;
        if(data->direction < 0)
            data->direction = 2 * M_PI + data->direction;
    }
    else if(data->key_right == 1)
    {
        data->direction += ROTATION_ANGLE;
        if(data->direction > 2 * M_PI )
            data->direction = data->direction - 2 * M_PI;
    }
  if(player_collision(data) == 1)
    {
        data->pos_x = data->old_x;
        data->pos_y = data->old_y;
        return ;
    }
    draw_3D(data);
}
int move_player(t_data *data)
{
    double direction;
    data->old_x = data->pos_x;
    data->old_y = data->pos_y;
    if(data->key_a == 1)
    {
        data->pos_x -= cos(data->direction + M_PI_2) * SIDES_SPEED;
        data->pos_y  -= sin(data->direction + M_PI_2) * SIDES_SPEED;
    }
    if(data->key_d == 1)
    {
        data->pos_x += cos(data->direction + M_PI_2) * SIDES_SPEED;
        data->pos_y += sin(data->direction + M_PI_2) * SIDES_SPEED;
    }
    else if(data->key_w  == 1 || data->key_s == 1)
    {
        direction = data->direction;
        if(data->key_s == 1)
            direction = data->direction + M_PI;
        data->pos_y += sin(direction) * SPEED;
        data->pos_x += cos(direction) * SPEED;
    }
    sides(data);
    return (0);
}

void find_player_position(t_all *all, t_data *data) {
    int y = 0;
    int x;
    while (y < all->y_of_map) {
        x = 0;
        while (x < all->longest_line) {
            if (all->map[y][x] == 'N' || all->map[y][x] == 'S' || all->map[y][x] == 'W' || all->map[y][x] == 'E') {
                data->pos_x = x * (1300 / all->x_of_map);
                data->pos_y = y * (900 / all->y_of_map);
                if (all->map[y][x] == 'N') {
                    data->direction = 3 * M_PI / 2;
                } else if (all->map[y][x] == 'S') {
                    data->direction = M_PI / 2;  
                } else if (all->map[y][x] == 'W') {
                    data->direction = M_PI;  
                } else if (all->map[y][x] == 'E') {
                    data->direction = 0;  
                }
                return;
            }
            x++;
        }
        y++;
    }
}

int release_key(int key, t_data *data)
{
    if(key == KEY_A)
        data->key_a = 0;
    if(key == KEY_D)
        data->key_d = 0;
    if(key == KEY_W)
        data->key_w = 0;
    if(key == KEY_S)
        data->key_s = 0;
    if(key == KEY_LEFT)
        data->key_left = 0;
    if(key == KEY_RIGHT)
        data->key_right = 0;
    return(0);
}
void	keys_init(t_data *data)
{

	data->key_a = 0;
	data->key_s = 0;
	data->key_d = 0;
	data->key_w = 0;
	data->key_left = 0;
	data->key_right = 0;
}
int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    exit(0);
}
void show_map(t_all *all, t_textr *txt)
{
    t_data *data;
    data = malloc(sizeof(t_data));
    data->mytable = malloc(sizeof(double) * (1300 * 2));
    data->garbage = all->garb;
    ft_lst_add_back(&data->garbage, ft_lst_new(data->mytable));
    data->checke = malloc(sizeof(int) * 1300);
    data->all = all;
    data->txt = txt;
    all->x_of_map = all->longest_line;
    find_player_position(all, data);
    keys_init(data);
    data->mlx_ptr = mlx_init();
    data->mlx_win = mlx_new_window(data->mlx_ptr, 1300,  900, "CUB3D");
    data->img = mlx_new_image(data->mlx_ptr, 1300, 900);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
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