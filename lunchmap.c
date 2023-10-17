/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunchmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:08:26 by otamrani          #+#    #+#             */
/*   Updated: 2023/10/18 00:57:13 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[10][20] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 'P', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
// void key_hok(int key, t_data *data)
// {
//     if(key == 53)
//         exit(0);
//     if(key == 13)
//     {
//         data->pos_x += cos(data->angle) * 0.1;
//         data->pos_y += sin(data->angle) * 0.1;
//     }
//     if(key == 1)
//     {
//         data->pos_x -= cos(data->angle) * 0.1;
//         data->pos_y -= sin(data->angle) * 0.1;
//     }
//     if(key == 0)
//     {
//         data->pos_x -= cos(data->angle + M_PI_2) * 0.1;
//         data->pos_y -= sin(data->angle + M_PI_2) * 0.1;
//     }
//     if(key == 2)
//     {
//         data->pos_x += cos(data->angle + M_PI_2) * 0.1;
//         data->pos_y += sin(data->angle + M_PI_2) * 0.1;
//     }
//     if(key == 123)
//         data->angle -= 0.1;
//     if(key == 124)
//         data->angle += 0.1;
//     if(key == 126)
//     {
//         data->pos_x += cos(data->angle) * 0.1;
//         data->pos_y += sin(data->angle) * 0.1;
//     }
//     if(key == 125)
//     {
//         data->pos_x -= cos(data->angle) * 0.1;
//         data->pos_y -= sin(data->angle) * 0.1;
//     }
//     mlx_destroy_image(data->mlx_ptr, data->img);
//     data->img = mlx_new_image(data->mlx_ptr, 1300, 900);
//     data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
//                                 &data->endian);
//     draw_map(data);
//     mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
// }

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;
    int rect_x;
    int rect_y;
    rect_x = x * (1300 / 20);
    rect_y = y * (900 / 10);
    int i = rect_x;
    int j = rect_y;
    while(j < rect_y + (900 / 10))
    {
        i = rect_x;
        while(i < rect_x + (1300 / 20))
        {
            dst = data->addr + (j * data->line_length + i * (data->bits_per_pixel / 8));
            *(unsigned int *)dst = color;
            i++;
        }
        j++;
    }
}

void draw_ray(t_data *data)
{
    int i = 0;
    int j = 0;
    char *dst;
    double ray_angle;
    double x = data->pos_x;
    double y = data->pos_y;
    data->fov = 60 * (M_PI / 180);
    ray_angle = data->direction - (data->fov / 2);
    // data.ray_x += cos(data.ray_angle) * 10;
    // data.ray_y += sin(data.ray_angle) * 10;
    // ray_angle = data->direction;
    while(i < 20)
    {   
        j = 0;
        while(j < 60)
        {
        x = x + cos(ray_angle);
        y = y + sin(ray_angle);
        dst = data->addr + ((int)y  * data->line_length + (int)x * (data->bits_per_pixel / 8));
            *(unsigned int *)dst = 0xFF0000;
            j++;
        }
        ray_angle += data->fov / 10;
        x = data->pos_x;
        y = data->pos_y;
        printf("ray _ eng  %f\n", ray_angle);
        i++;
    }
    printf("after x =%f y = %f\n", x, y);
}

void draw_map(t_data *data)
{
    int x = 0;
    char *dst;
    int y = 0;
    int color;
   while(y < 10)
   {
       x = 0;
       while(x < 20)
       {
           color = (map[y][x] == 1) ? 0x00FF0F : 0xFFFFFF;
           my_mlx_pixel_put(data, x, y, color);
           x++;
       }
       y++;
   }
    color = 0x000000;
    printf("%f| %f\n", data->pos_x, data->pos_y);
    dst = data->addr + ((int)(data->pos_y)  * data->line_length + ((int)data->pos_x) * (data->bits_per_pixel / 8));
             *(unsigned int *)dst = color;
    draw_ray(data);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);

}
void draw_map_1(t_data *data)
{
    int x = 0;
    char *dst;
    int y = 0;
    int color;
   while(y < 10)
   {
       x = 0;
       while(x < 20)
       {
        
           color = (map[y][x] == 1) ? 0x00FF0F : 0xFFFFFF;
           my_mlx_pixel_put(data, x, y, color);
           x++;
       }
       y++;
   }
    printf("[%f] [%f]\n", data->pos_x / (1300 /20), data->pos_y / (900 /10));
    color = 0x000000;
    dst = data->addr + ((int)(data->pos_y)  * data->line_length + ((int)data->pos_x) * (data->bits_per_pixel / 8));
             *(unsigned int *)dst = color;
    // dst = data->addr + ((int)(data->ray_y)  * data->line_length + ((int)data->ray_x) * (data->bits_per_pixel / 8));
    //         *(unsigned int *)dst = color;
    
    draw_ray(data);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
}


int move_player(int key, t_data *data)
{
    printf("[%d]\n", key);
    double direction;
    printf("%f  | %f\n", data->pos_x , data->pos_y);
    double ray_angle;
    data->ray_x = data->pos_x;
    data->ray_y = data->pos_y;
    data->fov = 60 * (M_PI / 180);
    ray_angle = data->direction - (data->fov / 2);
    data->ray_x += cos(data->ray_angle);
    data->ray_y += sin(data->ray_angle);
    printf("%f  ++ %f\n", data->ray_x , data->ray_y);
    double x = data->pos_x;
    int i = 0;
    double y = data->pos_y;
    if(key == 53)
        exit(0);
    if(key == 0)
    {
        data->pos_x -= cos(data->direction + M_PI_2) * 10;
        data->pos_y  -= sin(data->direction + M_PI_2) * 10;
    }
    if(key == 2)
    {
        data->pos_x += cos(data->direction + M_PI_2) * 10;
        data->pos_y += sin(data->direction + M_PI_2) * 10;
    }
    // if(key == 13)
    // {
    //     printf("%f() %f", sin(data->direction) * 10, cos(data->direction) * 10);
    //     printf("%f | %f\n", data->pos_x, data->pos_y);
    //  data->pos_y -=  sin(data->direction) * 10;
    //  data->pos_x -=  cos(data->direction) * 10;
    //  printf("%f |}| %f\n", data->pos_x, data->pos_y);
    // }
    else if(key == 1 || key == 13)
    {
        printf("fds %d, %f", 1, data->direction);
        direction = data->direction;
        printf("first =%f\n", direction);
        if(key == 1)
            direction = data->direction + M_PI;
        printf("direction%f\n", direction);
        data->pos_y += sin(direction) * 10;
        data->pos_x += cos(direction) * 10;
    }
    else if(key == 123)
        data->direction -= 0.3;
    else if(key == 124)
        data->direction += 0.3;
    if(map[(int)(data->pos_y / (900 / 10))][(int)data->pos_x / (1300 /20)] == 1)
    {
        data->pos_x = x;
        data->pos_y = y;
        return (0);
    }
    // if(key != 123 && key != 124)
    {
    mlx_destroy_image(data->mlx_ptr, data->img);
    data->img = mlx_new_image(data->mlx_ptr, 1300, 900);
    draw_map(data);
    }
    // draw_ray(data);
    return (0);
}
void cast_ray(t_data data)
{
    double ray_angle;
    char *dst;
    data.fov = 60 * (M_PI / 180);
    ray_angle = data.direction - (data.fov / 2);
    data.ray_x += cos(data.ray_angle) * 10;
    data.ray_y += sin(data.ray_angle) * 10;
    mlx_pixel_put(data.mlx_ptr, data.mlx_win, data.ray_x, data.ray_y, 0x00000);
  
}
void show_map()
{
    t_data data;
    // int i = -1;
    // i -= 3;
    // printf("%d\n", i);
    // exit(0);
    data.direction = M_PI / 2;
    data.pos_x = 5;
    data.pos_y = 2;
    data.pos_y = data.pos_y * (900 / 10);
    data.pos_x = data.pos_x * (1300 / 20);
    data.mlx_ptr = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx_ptr, 1300,  900, "CUB3D");
    data.img = mlx_new_image(data.mlx_ptr, 1300, 900); 
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
    draw_map(&data);
    // draw_ray(&data);
    mlx_hook(data.mlx_win, 2, 1L<<0, move_player, &data);
    mlx_loop(data.mlx_ptr);
}
