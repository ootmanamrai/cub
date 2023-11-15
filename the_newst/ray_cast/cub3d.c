/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:11:15 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/09 18:48:02 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
t_door *ft_lst_new_door(int x, int y, int open)
{
    t_door *new;

    new = malloc(sizeof(t_door));
    new->x = x;
    new->y = y;
    new->status = open;
    new->next = NULL;
    return (new);
}

void ft_lst_add_back_door(t_door **head, t_door *new)
{
    t_door *tmp;

    tmp = *head;
    if(!tmp)
    {
        *head = new;
        return ;
    }
    while(tmp->next)//segfuts here
    {
        tmp = tmp->next;
    }
    tmp->next = new;
}
int count_pinter(char **ptr)
{
    int i;
    i = 0;
    while(ptr[i])
    {
        i++;
    }
    return(i);
}
int count(char **str)
{
    int i;
    int x;
    int l;

    l = 0;
    i = 0;
    x = 0;
    if(strcmp(str[0], "F") && strcmp(str[0], "C"))
    {
        return (-1);
    }
    else
        i = 1;
    while(str[i][l])
    {
        if(str[i][l] == ',')
            x++;
        if (str[i][l] != ',' && (str[i][l] < '0' || str[i][l] > '9'))
        {
             return (-1);
        }
        l++;
    }
    if(x > 2 || x < 2)
        return (-1);
    return(0);
}

int check_final(t_textr *txtr)
{
    if(count_pinter(txtr->color_c) > 2 || count_pinter(txtr->color_f) > 2)
        return(-1);
    if(count(txtr->color_c) == -1 || count(txtr->color_f) == -1)
        return (-1);
    return(0);
}
void collect(t_garbage **garb, char **str)
{
    int i;
    i = 0;
    while(str[i])
    {
        ft_lst_add_back(garb, ft_lst_new(str[i]));
        i++;
    }
    ft_lst_add_back(garb, ft_lst_new(str));
}
int helper(long long *arr, char *str, t_garbage **garb)
{
    char **spl;
    int i;

    i = 0;
    spl = ft_split(str, ',');
    collect(garb, spl);
    while(spl[i])
    {
        arr[i] = ft_atoi(spl[i]);
        if(arr[i] > 255 || arr[i] < 0 || arr[i] == INT_MAX || arr[i] == INT_MIN)
        {
            printf("ERROR\n");
            return (-1);
        }
        i++;
    }
    return 0;
}
void  get_longest_line(t_all *all)
{
    char **tmp;
    int i;
    int x;

    x  = 0;
    tmp = all->map;
    i = 0;
    all->longest_line = ft_strlen(all->map[0]);
    while(tmp[x])
    {
        i = 0;
        while(tmp[x][i])
        {
            i++;
        }
        if(i > all->longest_line)
            all->longest_line = i;
        x++;
    }
}
void get_door(t_all **all)
{
    int i;
    int x;
    i = 0;
    x = 0;
    t_door *tmp;
    while((*all)->map[i])
    {
        x = 0;
        while((*all)->map[i][x])
        {
            if((*all)->map[i][x] == '2')//close
            {
                tmp = ft_lst_new_door(x, i, 0); 
                ft_lst_add_back_door(&(*all)->door, tmp);
            }
            else if((*all)->map[i][x] == '3')//open
            {
                 tmp = ft_lst_new_door(x, i, 1); 
                ft_lst_add_back_door(&(*all)->door, tmp);
            }
            x++;
        }
        i++;
    }
}
int just_for_doors(char *str)
{
    int i;
    i = 0;
    while(str[i])
    {
        if(str[i] == '2' || str[i] == '3')
        {
            return(-1);
        }
        i++;
    }
    return(0);
}
int check_end_of_line(char *str)
{
    int i;
    int len;

    len = ft_strlen(str);
    i = 0;
    while (str[i])
    {
        if(i == len - 1)
        {
            if(str[i] == '2' || str[i] == '3')
            {
                return(-1);
            }
        }
        i++;
    }
    return(0);
}
int check_for_doors(t_all *all)
{
    int i;
    int x;
    i = 0;
    x = 0;
    while(all->map[i])
    {
        x = 0;
        if(i == 0 || i == all->y_of_map - 1)
        {
            if(just_for_doors(all->map[i]) == -1)
            {
                printf("unvalid door\n");
                return(-1);
            }
        }
        while(all->map[i][x])
        {
            if(x == 0)
            {
                if(all->map[i][x] == '2' || all->map[i][x] == '3')
                {
                    printf("unvalid door\n");
                    return(-1);
                }
            }
            else if (check_end_of_line(all->map[i]) == -1)
            {
                printf("unvalid door\n");
                return(-1);
            }
            x++;
        }
        i++;
    }
    return(0);
}
int main(int argc, char *argv[])
{
    t_all *all;
    t_textr *txtr;
    t_garbage *garb;
    t_door *door;
    door = NULL;
    garb = malloc(sizeof(t_garbage));
    garb->next = NULL;
    int len;
    len = 0;
   if(argc > 1)
   {
   if (check_extionts(argv[1]) == -1 || all_in_one(&all, &txtr, argv, &garb) == -1)
   {
        return(0);
   }
   len = updatemap(all);
   all->garb = garb;
   all->door = door;
   count_x_y_of_the_map(&all);
   fix_map(&all, len);
    int i;

    i = 0;
    while(all->map[i])
    {
        printf("%s\n", all->map[i]);
        i++;
    }
   if(check_for_doors(all) == -1)
   {
       printf("unvalid\nERROR\n");
       return(-1);
   }
   get_door(&all);
    if(check_final(txtr) == -1)
    {
       printf("unvalid \nERROR\n");
        return (-1);
    }
    if(ft_atoi_num(txtr) ==  -1)
    {
        printf("unvalid \nERROR\n");
        return(-1);
    }
    get_colers(txtr);
    get_longest_line(all);
    show_map(all, txtr);
   }
   else 
    printf("messing file map ☠️ 👽\nERROR");
    return 0;
}
