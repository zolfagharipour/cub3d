#include "cubid.h"

int test_map(t_common *d_list)
{
    malloc_raw_map(d_list);
    print_map(d_list->map);
    minimap(d_list);
    write (1, "BINGO\n", 8);
    for (int i = 0; i < d_list->map->raw_height * d_list->map->scale; i++)
    {
        for (int j = 0; j < d_list->map->raw_length * d_list->map->scale; j++)
        {
            printf("%d", d_list->map->minimap[i][j]);
        }
        printf("\n");
    }
    return (1);

}

int malloc_raw_map(t_common *d_list)
{
    t_map   *map;
    int     i = 0;

    map = d_list->map;
    map->raw_height = 8;
    map->raw_length = 8;
    
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
    int map_values[8][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    for (i = 0; i < map->raw_height; i++)
    {
        for (int j = 0; j < map->raw_length; j++)
        {
            map->raw_map[i][j] = map_values[i][j];
        }
    }

    return 1;
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