#include "file.h"
//200,200,??

void get_x_y_of_the_player(t_all **all)
{
    char c;
    while((*all)->map[(*all)->x])
    {
        (*all)->y = 0;
        while ((*all)->map[(*all)->x][(*all)->y])
        {
            c = (*all)->map[(*all)->x][(*all)->y];
            if(c == 'N')
            {
                return ;
            }
            if(c == 'S')
            {
                return ;
            }
            if(c == 'E')
            {
                return ;
            }
            if(c == 'W')
            {
                return ;
            }
        (*all)->y++;
        }
         (*all)->x++;
    }
}

int count_pinters(char **str)
{
    int i;
    if(!str)
        return(0);
    i = 0;
    while(str[i])
        i++;
    return(i);
}

int all_in_one(t_all **all, t_textr **txtr,  char **argv, t_garbage **garb)
{
    (*all) = malloc(sizeof(t_all));
    (*txtr) = malloc(sizeof(t_textr));
    (*all)->fd = open(argv[1], O_RDONLY);
    (*all)->txt = (*txtr);
    (*all)->garb = (*garb);
    (*txtr)->garb = (*garb);
    if((*all)->fd == -1)
    {
        perror("file not exist or unvalid\nERROR 1");
         return (-1);
    }
    init_all(all);
    get_map(all, (*all)->fd);
    init_txters(&(*txtr), (*all));
    if(check_errors((*all)->map))
    {
        printf("unvalid map:\nERROR 2 ");
        return(-1);
    }
    if(!(*txtr)->color_c || !(*txtr)->color_f || !(*txtr)->EA || !(*txtr)->NO || !(*txtr)->SO || !(*txtr)->WE)
    {
        printf("unvalid map:\nERROR 3");
        return(-1);
    }
    if(count_pinters((*txtr)->EA) != 2 || count_pinters((*txtr)->NO) != 2 || count_pinters((*txtr)->SO) != 2 || count_pinters((*txtr)->WE) != 2)
        return(-1);
    get_x_y_of_the_player((all));
    return(0);
}
void make_duble(t_textr *txtr, t_all *all)
{
    txtr->S = malloc(sizeof(char *) * 6);
    ft_lst_add_back(&all->garb, ft_lst_new(txtr->S));
    txtr->S[0] = txtr->NO[1];
    txtr->S[1] = txtr->SO[1];
    txtr->S[2] = txtr->WE[1];
    txtr->S[3] = txtr->EA[1];
    txtr->S[4] = txtr->DO[1];
    txtr->S[5] = NULL;
}
//tap path
//dublcte the path
char *remove_char(char *map)
{
    int i;
    i = 0;
    while((map[i] && map[i] == ' '))
        i++;
    if(i > 0)
        map = ft_substr(map, i, ft_strlen(map));
   return(map);
}
void init_arr(int *arr)
{
    int i;
    i = 0;
    while(i < 7)
    {
        arr[i] = 0;
        i++;
    }
}
char *replce_tab(char *map)
{
    int i;
    i = 0;
    while(map[i])
    {
        if(map[i] == '\t')
            map[i] = ' ';
        i++;
    }
    return(map);
}
void init_txters(t_textr **txtr, t_all *all)
{
    int i;
    int x;
    int arr[7];
    char *tmp1;
    int l;
    char *tmp;
    tmp = NULL;
    tmp1 = NULL;
    init_befor_init_hh(txtr);
    init_arr(arr);
    x = 0;
    i = 0;
    l = 0;
    while(all->map[i]) //split from the begining
    {
        l = 0;
       
        all->map[i] = remove_char(all->map[i]);
        if(start_reading_map(all->map[i]) == -1)
                break;
         if(ft_strnstr(all->map[i], "DO", 2))//bonus part
        {
            //x++;
            arr[6]++;
            all->map[i] = remove_char(all->map[i]);
            tmp = ft_strdup((all->map[i]));
            ft_lst_add_back(&all->garb, ft_lst_new(tmp));
            (*txtr)->DO = ft_split(tmp, ' ');
            ft_lst_add_back(&all->garb, ft_lst_new((*txtr)->EA));
            all->map[i] = ft_strdup("\0");
        }
        if(ft_strnstr(all->map[i], "NO", 2))
        {
            x++;
            arr[0]++;
            all->map[i] = remove_char(all->map[i]);
            tmp = ft_strdup((all->map[i]));
            ft_lst_add_back(&all->garb, ft_lst_new(tmp));
            (*txtr)->NO = ft_split(tmp, ' ');
            ft_lst_add_back(&all->garb, ft_lst_new((*txtr)->NO));
            all->map[i] = ft_strdup("\0");
        }
        else if(ft_strnstr(all->map[i], "SO", 2))
        {
            x++;
            arr[1]++;
            all->map[i] = remove_char(all->map[i]);
            tmp = ft_strdup((all->map[i]));
            ft_lst_add_back(&all->garb, ft_lst_new(tmp));
            (*txtr)->SO = ft_split(tmp, ' ');
            ft_lst_add_back(&all->garb, ft_lst_new((*txtr)->SO));
            all->map[i] = ft_strdup("\0");
        }
        else if(ft_strnstr(all->map[i], "WE", 2))
        {
            x++;
            arr[2]++;
            all->map[i] = remove_char(all->map[i]);
            tmp = ft_strdup((all->map[i]));
            ft_lst_add_back(&all->garb, ft_lst_new(tmp));
            (*txtr)->WE = ft_split(tmp, ' ');
            ft_lst_add_back(&all->garb, ft_lst_new((*txtr)->WE));
            all->map[i] = ft_strdup("\0");
        }
       else if(ft_strnstr(all->map[i], "EA", 2))
       {
            x++;
            arr[3]++;
            all->map[i] = remove_char(all->map[i]);
            tmp = ft_strdup((all->map[i]));
            ft_lst_add_back(&all->garb, ft_lst_new(tmp));
            (*txtr)->EA = ft_split(tmp, ' ');
            ft_lst_add_back(&all->garb, ft_lst_new((*txtr)->EA));
            all->map[i] = ft_strdup("\0");
       }
        else if(ft_strnstr(all->map[i], "F", 1))
        {
            x++;
            arr[4]++;
            all->map[i] = remove_char(all->map[i]);
            tmp = ft_strdup((all->map[i]));
            ft_lst_add_back(&all->garb, ft_lst_new(tmp));
            (*txtr)->color_f = ft_split(tmp, ' ');
            ft_lst_add_back(&all->garb, ft_lst_new((*txtr)->color_f[0]));
            all->map[i] = ft_strdup("\0");
        }
        else if(ft_strnstr(all->map[i], "C", 1))
        {
            x++;
            arr[5]++;
            all->map[i] = remove_char(all->map[i]);
            tmp = ft_strdup((all->map[i]));
            ft_lst_add_back(&all->garb, ft_lst_new(tmp));
            (*txtr)->color_c = ft_split(tmp, ' ');
            ft_lst_add_back(&all->garb, ft_lst_new((*txtr)->color_c));
            all->map[i] = ft_strdup("\0");
        }
        
      //  if(x == 6)//if we have all the pathes put in bonus
           // break;
        i++;
    }
    i = 0;
    if(x != 6)
    {
        printf("unvalid :(\nERROR");
        exit(0);
    }
    if(arr[0] > 1 || arr[1] > 1 || arr[2] > 1 || arr[3] > 1 || arr[4] > 1 || arr[5] > 1)
    {
        printf("unvalid :(\nERROR");
        exit(0);
    }
    make_duble(*txtr, all);
    all->map = &all->map[x];
    x = 0;
    i = 0;
    tmp1 = all->map[x];
    while(all->map[x][i] =='\0')
        x++;
    all->map = &all->map[x];
}
int check_errors(char **map)
{
    int i;
    int plr;
    int x;
    
    plr = 0;
    i = 0;
    while(map[i])
    {
        x = 0;
        while(map[i][x])
        {
    
            if(map[i][x] != 'N' && map[i][x] != 'E' && map[i][x] != 'S' && map[i][x] != 'W' && map[i][x] != '0' && map[i][x] != '1' && map[i][x] != ' ' /*just for BONUS*/&& map[i][x] != 'D')
            {
                    return(1);
            }
            if(map[i][x] == 'N' || map[i][x] == 'E' || map[i][x] == 'S' || map[i][x] == 'W')
                plr++;
            x++;
        }
        i++;
    }
    if(plr > 1 || plr == 0)
    {
        return(1);
    }
    return(0);
}