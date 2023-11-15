#include <stdio.h>
#include "file.h"
void collext(t_all **all)
{
     int i = 0; 
    while((*all)->map[i])
    {
        ft_lst_add_back(&(*all)->garb, ft_lst_new((*all)->map[i]));
        i++;
    }
}
void count_new_lines(t_all **all)
{
    int i;
    int x;

    x = 0;
    i = 0;
    while((*all)->line[i])
    {
        if((*all)->line[i] == '\n')
        {
            x++;
        }
        i++;
    }
    (*all)->num_ptr = x;
}
void get_long_line(t_all **all)
{
    int i;
    int x;
    
    x = 0;
    i = 0;
    while((*all)->line[i])
    {
        if((*all)->line[i] == '\n')
        {
            if(x > (*all)->lon)
                (*all)->lon = x;
            x = 0;
        }
        else
            x++;
        i++;
    }
    if(x > (*all)->lon)
        (*all)->lon = x;
}
void allocate_new_lines(t_all **all)
{
    int i;
    int y;

    y = 0;
    i = 0;
    (*all)->map = ft_calloc(sizeof(char *) , ((*all)->num_ptr + 3));
    while((*all)->line[i])
    {
        if((*all)->line[i] == '\n')
        {
            (*all)->map[y] = ft_calloc(sizeof(char) , (*all)->lon + 1);
            y++;
        }
        i++;
    }
    (*all)->map[y] = ft_calloc(sizeof(char) , (*all)->lon + 1);
}
void copy_to_map(t_all **all)
{
    int i;
    int x;
    int l;

    l = 0;
    i = 0;
    x = 0;

    while ((*all)->line[i])
    {
        if ((*all)->line[i] == '\n')
        {
            (*all)->map[x][l] = '\0';
            x++;
            l = 0;
        }
        else
        {
            (*all)->map[x][l] = (*all)->line[i];
            l++;
        }
        i++;
    }
    (*all)->map[x][l] = '\0';
    x++;
}

void get_map(t_all **all, int fd)
{
    char *tmp;

    tmp = NULL;
    (*all)->line = NULL;
    tmp = get_next_line(fd);
    ft_lst_add_back(&(*all)->garb, ft_lst_new(tmp));
    if(!tmp)
        exit(4);
    while(tmp)
    {
        tmp = ft_strjoin((*all)->line, tmp);
        ft_lst_add_back(&(*all)->garb, ft_lst_new(tmp));
        (*all)->line = ft_strdup(tmp);
        ft_lst_add_back(&(*all)->garb, ft_lst_new((*all)->line));
        tmp = get_next_line(fd);
        ft_lst_add_back(&(*all)->garb, ft_lst_new(tmp));
    }
    count_new_lines(all);
    get_long_line(all);
    allocate_new_lines(all);
    copy_to_map(all);
    ft_lst_add_back(&(*all)->garb, ft_lst_new((*all)->map));
}

void init_befor_init_hh(t_textr **txtr)
{
    (*txtr)->color_c = NULL;
    (*txtr)->color_f = NULL;
    (*txtr)->EA = NULL;
    (*txtr)->NO = NULL;
    (*txtr)->SO = NULL;
    (*txtr)->WE = NULL;
    (*txtr)->DO = NULL;
    (*txtr)->C = calloc(sizeof(long long) , 3);
    (*txtr)->F = calloc(sizeof(long long) , 3);
    ft_lst_add_back(&(*txtr)->garb, ft_lst_new((*txtr)->C));
    ft_lst_add_back(&(*txtr)->garb, ft_lst_new((*txtr)->F));
}
int start_reading_map(char *line)
{
   // printf("line = %s\n", line);
    if(ft_strlen(line) == 0 && line[0] == '\0')
        return (1);
    if(!ft_strnstr(line, "NO", ft_strlen(line)) && !ft_strnstr(line, "SO", ft_strlen(line)) &&\
    !ft_strnstr(line, "WE", ft_strlen(line)) && !ft_strnstr(line, "EA", ft_strlen(line)) &&\
    !ft_strnstr(line, "F", ft_strlen(line)) && !ft_strnstr(line, "C", ft_strlen(line)) &&\
    !ft_strnstr(line, "\n", ft_strlen(line)) && !ft_strnstr(line, "DO", ft_strlen(line)))//bonus only
        return (-1);
    return(0);
}







