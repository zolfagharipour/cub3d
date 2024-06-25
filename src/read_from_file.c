#include "cubid.h"

int read_map_from_file(t_common *d_list)
{
    if (!determine_map_size(d_list))
        return 0;
    if (!malloc_raw_map(d_list))
        return 0;
    if (!fill_raw_map(d_list))
        return 0;
    print_map(d_list->map);
    find_the_players_position(d_list);
    printf("raw_length: %d\n", d_list->map->raw_length);
    printf("raw_height: %d\n", d_list->map->raw_height);

    return (1);
}

void find_the_players_position(t_common *d_list)
{
    for (int i = 0; i < d_list->map->raw_height; i++)
    {
        for (int j = 0; j < d_list->map->raw_length; j++)
        {
            if (d_list->map->raw_map[i][j] == 2)
            {
                d_list->rc->pos[0] = i + 0.5;
                d_list->rc->pos[1] = j + 0.5;
                return ;
            }
        }
    }
}

void print_map(t_map *map)
{
    for (int i = 0; i < map->raw_height; i++)
    {
        for (int j = 0; j < map->raw_length; j++)
        {
            printf("%d", map->raw_map[i][j]);
        }
        printf("\n");
    }
}

int fill_raw_map(t_common *d_list)
{
    char    *line;
    int     i = 0;
    int     j = 0;
    t_map   *map;

    //cleanup stuff
    map = d_list->map;
    map->fd = open(map->file, O_RDONLY);
    line = get_next_line(map->fd);
    while (line && i <map->raw_height)
    {
        for (int j = 0; j < map->raw_length; j++)
        {
            if (line[j] == '1')
                map->raw_map[i][j] = 1;
            else if (line[j] == '0')
                map->raw_map[i][j] = 0;
            else if (line[j] == '2')
                map->raw_map[i][j] = 2;
            else
                map->raw_map[i][j] = 4;
        }
        free(line);
        line = NULL;
        line = get_next_line( d_list->map->fd);
        i++;
    }
    close(d_list->map->fd);
    return (1);
}


int malloc_raw_map(t_common *d_list)
{
    t_map   *map;
    int     i = 0;

    map = d_list->map;

    map->raw_map = (int **)malloc(map->raw_height * sizeof(int *) + 1);
    if (!map->raw_map)
        return (cleanup(d_list), 0);

    while (i < map->raw_height)
    {
        map->raw_map[i] = (int *)malloc(map->raw_length * sizeof(int) + 1);
        if (map->raw_map[i] == NULL)
            return (cleanup(d_list), 0);
        i++;
    }
    return (1);
}


int determine_map_size(t_common *d_list)
{
    char    *line;
    int     i = 0;
    t_map   *map;

    map = d_list->map;
    map->fd = open(d_list->map->file, O_RDONLY);
    if (map->fd == -1)
        return (0);
    map = d_list->map;
    line = NULL;
    line = get_next_line(map->fd);
    while (line)
    {
        if (ft_strlen(line) - 1 > map->raw_length)
            map->raw_length = ft_strlen(line) - 1;
        free(line);
        line = NULL;
        line = get_next_line(map->fd);
        i++;
    }
    map->raw_height = i;
    close(map->fd);
    return (1);
}
