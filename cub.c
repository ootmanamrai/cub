
#include "file.h"
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
    if(x > 2)
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
// int helper(unsigned int *arr, char *str, t_garbage **garb)
// {
//     char **spl;
//     int i;

//     i = 0;
//     spl = ft_split(str, ',');
//     collect(garb, spl);
//     while(spl[i])
//     {
//         arr[i] = ft_atoi(spl[i]);
//         if(arr[i] > 255)
//         {   i = 0;
//             return (-1);
//         }
//         i++;
//     }
//     return 0;
// }


