#include "cubid.h"

int read_map_from_file(t_common *d_list)
{
    determine_map_size(d_list);
    malloc_raw_map(d_list);
    printf("raw_length: %d\n", d_list->map->raw_length);
    printf("raw_height: %d\n", d_list->map->raw_height);
    fill_raw_map(d_list);
    print_map(d_list->map);
    return (1);
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

    d_list->map->fd = open(d_list->map->file, O_RDONLY);
    line = get_next_line( d_list->map->fd);
    while (line && i < d_list->map->raw_height)
    {
        j = 0;
        while (line[j] && j < d_list->map->raw_length)
        {
            if (line[j] == '1')
                d_list->map->raw_map[i][j] = 1;
            else if (line[j] == '0')
                d_list->map->raw_map[i][j] = 0;
            else if (line[j] == '2')
                d_list->map->raw_map[i][j] = 2;
            j++;
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

    //allow for array of row ptr
    map->raw_map = (int **)malloc(map->raw_height * sizeof(int *));
    if (!map->raw_map)
        return (cleanup(d_list), 0);

    //alloc for for each row
    while (i < map->raw_height)
    {
        map->raw_map[i] = (int *)malloc(map->raw_length * sizeof(int));
        if (map->raw_map[i] == NULL)
            return (cleanup(d_list), 0);
        i++;
    }
    return (1);
    // int map_values[16][16] = {
    //     {1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1},
    //     {1, 0, 0, 0, 0, 0, 0, 1,0,0,0,1,0,0,0,1},
    //     {1, 0, 0, 0, 1, 0, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 0, 0, 1, 0, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 0, 0, 1, 0, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 0, 0, 1, 0, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 0, 0, 1, 0, 0, 0,0,1,0,1,0,1,0,1},
    //     {1, 0, 0, 0, 1, 1, 1, 1,0,1,0,1,0,1,0,1},
    //     {1, 1, 1, 1, 1, 1, 1, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 1, 0, 0, 2, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 1, 0, 1, 0, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 1, 0, 1, 0, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 1, 0, 1, 0, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 0, 0, 1, 0, 0, 1,0,1,0,1,0,1,0,1},
    //     {1, 0, 0, 0, 1, 0, 0, 0,0,1,0,0,0,1,0,1},
    //     {1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1}
    // };

    // for (i = 0; i < map->raw_height; i++)
    // {
    //     for (int j = 0; j < map->raw_length; j++)
    //     {
    //         map->raw_map[i][j] = map_values[i][j];
    //     }
    // }
    // return 1;
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
        if (ft_strlen(line) > map->raw_length)
            map->raw_length = ft_strlen(line);
        free(line);
        line = NULL;
        line = get_next_line(map->fd);
        i++;
    }
    map->raw_height = i;
    //close again after reading
    close(map->fd);
    return (1);
}