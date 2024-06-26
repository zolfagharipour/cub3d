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
            if (d_list->map->raw_map[i][j] == E
                || d_list->map->raw_map[i][j] == S
                || d_list->map->raw_map[i][j] == W
                || d_list->map->raw_map[i][j] == N)
            {
                d_list->rc->pos[0] = j + 0.5;
                d_list->rc->pos[1] = i + 0.5;
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
    while (line && i < map->raw_height)
    {
        j = 0;
        while (line[j] && j < map->raw_length)
        {
            if (line[j] == '1')
                map->raw_map[i][j] = 1;
            else if (line[j] == '0')
                map->raw_map[i][j] = 0;
            else if (line[j] == 'N')
                map->raw_map[i][j] = N;
            else if (line[j] == 'S')
                map->raw_map[i][j] = S;
            else if (line[j] == 'W')
                map->raw_map[i][j] = W;
            else if (line[j] == 'E')
                map->raw_map[i][j] = E;
            else
                map->raw_map[i][j] = RESIDUUM;
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
    map->raw_map = (int **)malloc(map->raw_height * sizeof(int *));
    if (!map->raw_map)
        return (cleanup(d_list), 0);

    while (i < map->raw_height)
    {
        map->raw_map[i] = (int *)malloc(map->raw_length * sizeof(int));
        if (map->raw_map[i] == NULL)
            return (cleanup(d_list), 0);
        i++;
    }
    return (1);
}

//calculates if the minimap exceedes the bounds
//reduces the scale factor if it does
//- scale/2 because the minimap is placed sale/2 to the right and down
void    check_map_scale_factor(t_common *d_list)
{
    t_map   *map;
    int     scale;
    int     reduction;

    reduction = 0;
    map = d_list->map;
    if (map->raw_length * map->scale >= WIDTH / 2 ||
        map->raw_height * map->scale >= HEIGHT / 2)
        {
            while ((map->raw_length * map->scale >= WIDTH / 2 ||
                map->raw_height * map->scale >= HEIGHT / 2) && map->scale > 2)
            {
                map->scale = map->scale - 2;
                reduction++;
            }
        }
    if (reduction > 0)
    {
        map->s_square -= reduction / 2;
        if (map->s_square < 1)
            map->s_square = 1;
    }
}

int    find_line_length(char *line)
{
    int i = 0;

    while (line[i] && line[i] == ' ')
        i++;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    return (i);
}

int validate_map_line(char *line, t_common *d_list)
{
    //i is indicating wether it's the first line of the map
    //i cannot be under 3 then it's not a valid map
    //check white spaces?
    int i;
    int digit_sequence_start;

    i = 0;
    digit_sequence_start = 0;
    while (line[i] && line[i] != '\n')
    {
        if (ft_isdigit(line[i]))
            digit_sequence_start = 1;
        else if (line[i] == ' ')
        {
            if (digit_sequence_start)
                return (p_error("Invalid map", d_list), 0);
        }
        else if (line[i] == 'S' || line[i] == 'N' || line[i] == 'W' || line[i] == 'E')
        {
            if (d_list->map->player_found)
                return (p_error("More than one player", d_list), 0);
            else
                d_list->map->player_found = 1;
        }
        else
            return (write (1, &line[i], 2), p_error("Invalid character in map", d_list), 0);
        i++;
    }
    d_list->map->previous_line_valid = 1;
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
        if (!validate_map_line(line, d_list))
            return (0);
        if (find_line_length(line) > map->raw_length)
            map->raw_length = find_line_length(line);
    //check noch dass das zählen bei der letzten ziffer endet
        free(line);
        line = NULL;
        line = get_next_line(map->fd);
        i++;
    }
    map->raw_height = i;
    if (d_list->map->player_found == 0)
        return (p_error("No player found", d_list), 0);
    check_map_scale_factor(d_list);
    close(map->fd);
    return (1);
}
