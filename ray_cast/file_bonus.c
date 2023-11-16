#include "cub3d.h"
int extra_check(char **map)
{
    int i;
    int x;
    int boo;
    i = 0;
    x = 0;
    boo = 0;
    while(map[i])
    {
        x = 0;
        while(map[i][x])
        {
            if(map[i][x] == 'D')
            {
               if(map[i][x + 1] == '1' && map[i][x - 1] == '1')
               {
                    boo = 1;
               }
               else if(map[i + 1][x] == '1' && map[i - 1][x] == '1')
               {
                    boo = 1;
               }
               else
               {
                   printf("unvalid \nERROR\n");
                   return(-1);
               }
            }
            x++;
        }
        i++;
    }
    return(boo);
}