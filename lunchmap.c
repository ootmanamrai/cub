/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunchmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:08:26 by otamrani          #+#    #+#             */
/*   Updated: 2023/10/23 00:49:45 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[10][20] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 'P', 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
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
void draw_line(t_data *data, double x_intercept, double y_intercept, char *dst)
{

    // Assuming that mlx_ptr and win_ptr are properly initialized

    double dx = x_intercept - data->pos_x;
    double dy = y_intercept - data->pos_y;
    double steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    double xIncrement = dx / steps;
    double yIncrement = dy / steps;
    double x = data->pos_x;
    double y = data->pos_y;

    for (int i = 0; i < steps; i++) {
        // printf("xx= %f yy= %f\n", x, y);
        if(x < 0 || y < 0 || x >= 1300 || y >= 900)
            break;
         dst = data->addr + ((int)(y)  * data->line_length + ((int)x) * (data->bits_per_pixel / 8));
             *(unsigned int *)dst = 0x000000;
        x += xIncrement;
        y += yIncrement;
    }
}
int getupdown(double direction)
{
    if(direction > 0 && direction < M_PI)
        return(1);
    else if(direction > M_PI && direction < 2 * M_PI)
    {
        printf("fsdsd\n");
        return(2);
    }
    return(0);
}
int getFacingDirection(double direction) {
   int m = 0;
    if(direction < M_PI /2 || direction > 2 * M_PI - M_PI / 2)
        return(1);
    else if(direction > M_PI / 2)
       return(2);
    return(0);
}

void draw_ray(t_data *data, char *dst)
{
    int i = 0;
    double ray_angle;
    double y_intercept;
    double x_intercept;
    double x = data->pos_x;
    double y = data->pos_y;
    double x_step;
    double y_step;
    
    
    printf("direction '=' %f\n", data->direction);
    data->fov = 60 * (M_PI / 180);
    ray_angle = data->direction;
    
    y_intercept = floor(data->pos_y / (900 / 10)) * (900 / 10);
    printf("y_intercept = %f\n", y_intercept);
    if(getupdown(data->direction) == 1)
        y_intercept += (900 / 10);
    if(getupdown(data->direction) == 2)
        y_intercept--;
    printf("y_intercept-2- = %f\n", y_intercept);
    x_intercept = data->pos_x + (y_intercept - data->pos_y) / tan(ray_angle);
    printf("x ==== %f intr===%f\n", x_intercept / (1300 / 20), y_intercept / (900 / 10));
    y_step = (900/ 10);
    if(getupdown(data->direction) == 2)
        y_step *= -1;
    // y_step *= (data->direction > M_PI) ? -1 : 1;
    x_step = (900 / 10)/ tan(ray_angle);
    printf("xstep = %f\n", x_step);
    if(getFacingDirection(data->direction) == 2 && x_step > 0)
        x_step *= -1;
    else if(getFacingDirection(data->direction) == 1 && x_step < 0)
        x_step *= -1;
    // printf("x = %d y = %d\n", 900 / 10, 1300 / 20);
    printf("%f ||{} %f\n", x_step, y_step);
    printf(" inter = %f [] inter =%f\n", x_intercept, y_intercept);
    while (y_intercept >= 0 && y_intercept < 900 && x_intercept >= 0 && x_intercept < 1300)
    {
        int x = (x_intercept / (1300 / 20));
        int y =  (y_intercept / (900 / 10));
        if (map[y][x] == 1)
        {
            break;
            printf("x = %f y = %f\n", x_intercept, y_intercept);
        }
        y_intercept += y_step;
        x_intercept += x_step;
         i++;
    }
    printf("%f first && %f\n", x_intercept, y_intercept);
    // if((int)x_intercept >= 1300 || (int)x_intercept <=  -1300)
    //     x_intercept = 1299;
    // if((int)y_intercept >= 900 || (int)y_intercept <=  -900)
    //     y_intercept = 899;
     if(x_intercept < 0)
    {
         x_intercept = 0;
    }
    if(y_intercept < 0)
            y =0 ;
    // if(y_intercept < 0)
    //     y_intercept *= -1 ;
    printf("%f && %f\n", round(x_intercept / (1300 /20)), round(y_intercept / (900 / 10)));
    printf("%f\n", floor(y_intercept));
    draw_line(data, round(x_intercept) , round(y_intercept), dst);
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
    draw_ray(data, dst);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);

}

int move_player(int key, t_data *data)
{
    printf("[%d]\n", key);
    double direction;
    printf("%f  | %f\n", data->pos_x , data->pos_y);
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
    else if(key == 1 || key == 13)
    {
        direction = data->direction;
        if(key == 1)
            direction = data->direction + M_PI;
        data->pos_y += sin(direction) * 10;
        data->pos_x += cos(direction) * 10;
    }
    else if(key == 123)
    {
        data->direction -= 0.2;
        if(data->direction < 0)
            data->direction = 2 * M_PI + data->direction;
    }
    else if(key == 124)
    {
        data->direction += 0.2;
        if(data->direction > 2 * M_PI)
            data->direction = data->direction - data->direction;
    }
    if(map[(int)(data->pos_y / (900 / 10))][(int)data->pos_x / (1300 /20)] == 1)
    {
        data->pos_x = x;
        data->pos_y = y;
        return (0);
    }
    printf("direction ==%f\n", data->direction);
    // if(key != 123 && key != 124)
    {
    draw_map(data);
    }
    // printf("facing in: %s\n", getFacingDirection(data->direction));
    // printf("facing up: %s\n", getupdown(data->direction));
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
