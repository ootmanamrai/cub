/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunchmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:08:26 by otamrani          #+#    #+#             */
/*   Updated: 2023/10/06 22:44:34 by otamrani         ###   ########.fr       */
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
           if(map[y][x] == 'P')
           {
                data->pos_x = x * (1300 /20);
                data->pos_y = y * (900 /10);
                data->direction = M_PI / 2;
           }
           my_mlx_pixel_put(data, x, y, color);
           x++;
       }
       y++;
   }
    color = 0x000000;
    printf("%f| %f\n", data->pos_x, data->pos_y);
    dst = data->addr + ((int)(data->pos_y)  * data->line_length + ((int)data->pos_x) * (data->bits_per_pixel / 8));
             *(unsigned int *)dst = color;
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
    printf("[%f] [%f]\n", data->pos_x, data->pos_y);
    color = 0x000000;
    // my_mlx_pixel_put(data, data->pos_x, data->pos_y, 0x000000);
    dst = data->addr + ((int)(data->pos_y)  * data->line_length + ((int)data->pos_x) * (data->bits_per_pixel / 8));
             *(unsigned int *)dst = color;
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
}
int move_player(int key, t_data *data)
{
    printf("%f  | %f\n", data->pos_x , data->pos_y);
    double x = data->pos_x;
    double y = data->pos_y;
    printf("{%d}+\n", key);
    if(key == 100)
    {
        data->pos_x += cos(data->direction + M_PI_2) * 10;
        data->pos_y += sin(data->direction + M_PI_2) * 10;
    }
    if(key == 97)
    {
        data->pos_x -= cos(data->direction + M_PI_2) * 10;
        data->pos_y -= sin(data->direction + M_PI_2) * 10;
    }
    if(key == 119)
    {
     data->pos_y -=  sin(data->direction) * 10;
     data->pos_x -=  cos(data->direction) * 10;
     printf("{sin = %f} cos = %f\n", sin(data->direction), cos(data->direction));
     printf("{%f} {%f}\n", data->pos_x , data->pos_y);
    }
    else if(key == 115)
    {
        data->pos_y += sin(data->direction) * 10;
        data->pos_x += cos(data->direction) * 10;
    }
    else if(key == 65361)
    {
        data->direction -= 0.6;
        // if(data->direction < 0)
        //     data->direction = 2 * M_PI;
    }
    else if(key == 65363)
    {
        data->direction += 0.6;
        // if(data->direction > 2 * M_PI)
        //     data->direction = 0;
    }
    if(x != data->pos_x || y != data->pos_y)
    {
    // map[y][x] = '0';
    // map[data->pos_y][data->pos_x] = 'P';
    mlx_destroy_image(data->mlx_ptr, data->img);
    data->img = mlx_new_image(data->mlx_ptr, 1300, 900);
    // my_mlx_pixel_put(data, data->pos_x, data->pos_y, 0x0000FF);
    draw_map_1(data);
    // mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
    }
    return (0);
}
void show_map()
{
    t_data data;
    data.mlx_ptr = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx_ptr, 1300,  900, "CUB3D");
    data.img = mlx_new_image(data.mlx_ptr, 1300, 900); 
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
    draw_map(&data);
    mlx_hook(data.mlx_win, 2, 1L<<0, move_player, &data);
    mlx_loop(data.mlx_ptr);
}

// void draw_map(t_data *data)
// {
//     int x = 0;
//     int y = 0;
//     int color;

//     while (y < 10)
//     {
//         x = 0;
//         while (x < 20)
//         {
//             // Calculate the coordinates for drawing
//             int draw_x = x * 60;
//             int draw_y = y * 60;
//             write(1, &map[y][x], 1);
//             if (map[y][x] == '1' || map[y][x] == '0')
//             {
//             write(1, "gsagsg", 6);
//                 map[y][x] == '1' ? color = 0x00FF0F : 0x000000;
//                 while(draw_y < y * 60 + 60)
//                 {
//                     draw_x = x * 60;
//                     while(draw_x < x * 60 + 60)
//                     {
//                         my_mlx_pixel_put(data, draw_x, draw_y, color);
//                         draw_x++;
//                     }
//                     draw_y++;
//                 }
//             }
//             else if (map[y][x] == 'P')
//             {
//                 // Draw player as one pixel
//                 my_mlx_pixel_put(data, draw_x + 30, draw_y + 30, 0x0000FF); // Centered pixel
//                 data->pos_x = draw_x + 30; // Update player position
//                 data->pos_y = draw_y + 30;
//             }
//             x++;
//         }
//         y++;
//     }
// }
