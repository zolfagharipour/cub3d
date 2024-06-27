/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:11 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/27 16:25:43 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    for (int x = 0; x < d_list->map->raw_length; x++)
    {
        for (int y = 0; y < d_list->map->raw_height; y++)
        {
            if (d_list->map->raw_map[x][y] == E
                || d_list->map->raw_map[x][y] == S
                || d_list->map->raw_map[x][y] == W
                || d_list->map->raw_map[x][y] == N)
            {
                d_list->rc->pos[0] = x + 0.5;
                d_list->rc->pos[1] = y + 0.5;
                return ;
            }
        }
    }
}

void print_map(t_map *map)
{
    for (int y = 0; y < map->raw_height; y++)
    {
        for (int x = 0; x < map->raw_length; x++)
        {
            printf("%d", map->raw_map[x][y]);
        }
        printf("\n");
    }
}

int fill_raw_map(t_common *d_list)
{
    char    *line;
    int     x = 0;
    int     y = 0;
    t_map   *map;

    //cleanup stuff
    map = d_list->map;
    map->fd = open(map->file, O_RDONLY);
    if (map->fd < 0)
        return (cleanup(d_list), 0);
    line = get_next_line(map->fd);
    while (line && y < map->raw_height)
    {
        printf("Processing line y %d\n", y);
        for (x = 0; x < map->raw_length; x++)
        {
            map->raw_map[x][y] = RESIDUUM;  // Initialize the row first
        }

        x = 0;
        while (line[x] && x < map->raw_length)
        {
            if (line[x] == '1')
                map->raw_map[x][y] = 1;
            else if (line[x] == '0')
                map->raw_map[x][y] = 0;
            else if (line[x] == 'N')
                map->raw_map[x][y] = N;
            else if (line[x] == 'S')
                map->raw_map[x][y] = S;
            else if (line[x] == 'W')
                map->raw_map[x][y] = W;
            else if (line[x] == 'E')
                map->raw_map[x][y] = E;
            else
                map->raw_map[x][y] = RESIDUUM;
            x++;
        }
        free(line);
        line = get_next_line(map->fd);
        y++;
    }
    close(d_list->map->fd);
    return (1);
}


int malloc_raw_map(t_common *d_list)
{
    t_map *map;
    int i = 0;
    int rows_y = d_list->map->raw_height;
    int columns_x = d_list->map->raw_length;

    map = d_list->map;
    map->raw_map = (int **)malloc(columns_x * sizeof(int *));
    if (!map->raw_map)
        return (cleanup(d_list), 0);

    i = 0;
    while (i < columns_x)
    {
        map->raw_map[i] = (int *)malloc(rows_y * sizeof(int));
        if (!map->raw_map[i])
            return (cleanup(d_list), 0);
        i++;
    }
    // map = d_list->map;
    // map->raw_map = (int **)malloc(map->raw_height * sizeof(int *));
    // if (!map->raw_map)
    //     return (cleanup(d_list), 0);
    // printf("malloced height/y: %d\n", map->raw_height);
    // while (i < map->raw_height)
    // {
    //     map->raw_map[i] = (int *)malloc(map->raw_length * sizeof(int));
    //     if (map->raw_map[i] == NULL)
    //         return (cleanup(d_list), 0);
    //     i++;
    // }
    // printf("malloced length/x: %d\n", map->raw_length);
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
    if (map->raw_length * map->scale >= WIDTH -100 ||
        map->raw_height * map->scale >= HEIGHT -100)
        {
            while ((map->raw_length * map->scale >= WIDTH -100 ||
                map->raw_height * map->scale >= HEIGHT -100) && map->scale > 2)
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
        if (line[i] == '0' || line[i] == '1')
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
            return (p_error("Invalid character in map", d_list), 0);
        i++;
    }
    //d_list->map->previous_line_valid = 1;
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
