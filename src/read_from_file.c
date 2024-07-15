/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:11 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/02 19:51:01 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

char *valid_map_boundaries(t_common *d_list)
{
    int x;
    int y;
    t_map *map;

    x = 0;
    y = 0;
    map = d_list->map;
    while (x < d_list->map->raw_length)
    {
        if (map->raw_map[x][y] != ft_atoi("1") && map->raw_map[x][y] != ft_atoi("6"))
            return ("Invalid map boundaries\n");
        x++;
    }
    y = d_list->map->raw_height - 1;
    x--;
    while (x >= 0)
    {
        if (map->raw_map[x][y] != ft_atoi("1") && map->raw_map[x][y] != ft_atoi("6"))
            return ("Invalid map boundaries\n");
        x--;
    }
    x++;
    y = 0;
    while (y < d_list->map->raw_height)
    {
        if (map->raw_map[x][y] != ft_atoi("1") && map->raw_map[x][y] != ft_atoi("6"))
            return ("Invalid map boundaries\n");
        y++;
    }
    y--;
    x = d_list->map->raw_length - 1;
    while (y >= 0)
    {
        if (map->raw_map[x][y] != ft_atoi("1") && map->raw_map[x][y] != ft_atoi("6"))
            return ("Invalid map boundaries\n");
        y--;
    }
    y++;
    
    //player checking
    //why was that necessary?
    // x = 1;
    // y = 1;
    // while (y < map->raw_height - 1)
    // {
    //     x = 1;
    //     while (x < map->raw_length - 1)
    //     {
    //         if (x == d_list->rc->pos[0] - 0.5 && y == d_list->rc->pos[1] - 0.5)
    //         {
    //             if (map->raw_map[x + 1][y] == ft_atoi("6")
    //                 || map->raw_map[x - 1][y] == ft_atoi("6")
    //                 || map->raw_map[x][y + 1] == ft_atoi("6")
    //                 || map->raw_map[x][y - 1] == ft_atoi("6"))
    //                 return("Player ist outside of the map\n");
    //         }
    //         x++;
    //     }
    //     y++;
    // }
    //zero checking
    x = 1;
    y = 1;
    while (y < map->raw_height - 1)
    {
        x = 1;
        while (x < map->raw_length - 1)
        {
            if (map->raw_map[x][y] == ft_atoi("0"))
            {
                if (map->raw_map[x + 1][y] == ft_atoi("6")
                    || map->raw_map[x - 1][y] == ft_atoi("6")
                    || map->raw_map[x][y + 1] == ft_atoi("6")
                    || map->raw_map[x][y - 1] == ft_atoi("6"))
                    return ("Invalid map boundaries\n");
            }
            x++;
        }
        y++;
    }

    //door checking
    x = 1;
    y = 1;
    while (y < map->raw_height - 1)
    {
        x = 1;
        while (x < map->raw_length - 1)
        {
            if (map->raw_map[x][y] == ft_atoi("4"))
            {
                if (!((map->raw_map[x + 1][y] == ft_atoi("1")
                    && map->raw_map[x - 1][y] == ft_atoi("1"))
                    || (map->raw_map[x][y + 1] == ft_atoi("1")
                    && map->raw_map[x][y - 1] == ft_atoi("1")))
                    || (map->raw_map[x + 1][y] == ft_atoi("4"))
                    || (map->raw_map[x - 1][y] == ft_atoi("4"))
                    || (map->raw_map[x][y + 1] == ft_atoi("4"))
                    || (map->raw_map[x][y - 1] == ft_atoi("4")))
                    return ("Invalid placement of doors in the map\n");
            }
            x++;
        }
        y++;
    }
    return (NULL);
}

int read_map_from_file(t_common *d_list)
{
    if (!determine_map_size(d_list))
        return 0;
    if (!malloc_raw_map(d_list))
        return 0;
    if (!fill_raw_map(d_list))
        return 0;
    check_all_parts_found_and_valid(d_list);
    print_map(d_list->map);
    //find_the_players_position(d_list);
    ft_printf("raw_length: %d\n", d_list->map->raw_length);
    ft_printf("raw_height: %d\n", d_list->map->raw_height);
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
            ft_printf("%d", map->raw_map[x][y]);
        }
        ft_printf("\n");
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
    while (x < map->file_length - map->raw_height )
    {
        free(line);
        line = get_next_line(map->fd);
        x++;
    }
    x = 0;
    while (line && y < map->raw_height)
    {
        for (x = 0; x < map->raw_length; x++)
            map->raw_map[x][y] = RESIDUUM;  // Initialize the row first
        x = 0;
        while (line[x] && x < map->raw_length)
        {
            if (line[x] == '1')
                map->raw_map[x][y] = 1;
            else if (line[x] == '0')
                map->raw_map[x][y] = 0;
            else if (line[x] == '4')
                map->raw_map[x][y] = 4;
            else if (line[x] == '3')
            {
                d_list->rc->sprite[0] = x + 0.5;
                d_list->rc->sprite[1] = y + 0.5;
                map->raw_map[x][y] = 0;
            }
            else if (line[x] == 'N')
            {
                d_list->rc->pos[0] = x + 0.5;
                d_list->rc->pos[1] = y + 0.5;
                d_list->rc->look = 0.5;
                map->raw_map[x][y] = 0;
            }
            else if (line[x] == 'S')
            {
                d_list->rc->pos[0] = x + 0.5;
                d_list->rc->pos[1] = y + 0.5;
                d_list->rc->look = 1;
                map->raw_map[x][y] = 0;
            }
            else if (line[x] == 'W')
            {
                d_list->rc->pos[0] = x + 0.5;
                d_list->rc->pos[1] = y + 0.5;
                d_list->rc->look = 1.5;
                map->raw_map[x][y] = 0;
            }
            else if (line[x] == 'E')
            {
                d_list->rc->pos[0] = x + 0.5;
                d_list->rc->pos[1] = y + 0.5;
                d_list->rc->look = 0;              
                map->raw_map[x][y] = 0;
            }
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
    return (1);
}

//calculates if the minimap exceedes the bounds
//reduces the scale factor if it does
//- scale/2 because the minimap is placed sale/2 to the right and down
void    check_map_scale_factor(t_common *d_list)
{
    //!!!
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
    int i;

    i = 0;
    while (line[i] && line[i] == ' ')
        i++;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    while (line[i] && line[i] == ' ')
        i++;
    return (i);
}

void validate_map_line(char *line, t_common *d_list)
{
    int i;
    int digit_sequence_start;

    i = 0;
    digit_sequence_start = 0;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] == 'S' || line[i] == 'N' || line[i] == 'W' || line[i] == 'E')
        {
            if (d_list->map->player_found)
                d_list->map->val_map[MULTIPLE_PLAYERS] = 1;
            else
                d_list->map->player_found = 1;
        }
        else if (line[i] != '0' && line[i] != '1' && line[i] != '3' && line[i] != '4'
            && line[i] != ' ')
            d_list->map->val_map[INV_CHAR] = 1;
        i++;
    }
}

int line_empty(char *line)
{
    int i = 0;

    while (line[i] && line[i] == ' ')
        i++;
    if (line[i] == '\n')
        return (1);
    return (0);
}

int suitable_color_range(t_common *d_list, char *r, char *g, char *b)
{
    int red;
    int blue;
    int green;
    int color;

    red = ft_atoi(r);
    if (red < 0 || red > 255)
        return (0);
    green = ft_atoi(g);
    if (green < 0 || green > 255)
        return (0);
    blue = ft_atoi(b);
    if (blue < 0 || blue > 255)
        return (0);
    color = (red << 16) | (green << 8) | blue;
    ft_printf("color: %d\n", color);
    return 1;
}

int determine_map_size(t_common *d_list)
{
    char    *line;
    t_map   *map;

    map = d_list->map;
    map->fd = open(d_list->map->file, O_RDONLY);
    if (map->fd == -1)
        return (0);
    line = NULL;
    line = get_next_line(map->fd);
    while (line)
    {
        if (line_empty(line) && d_list->map->map_started == 1)
            d_list->map->val_map[INV_NL] = 1;
        //skip nl and space
        if (!line_empty(line))
        {
            //check each individual line
            if (d_list->map->map_started == 0)
                evaluate_line(line, d_list);
            //starts checking map if map has started
            if (d_list->map->map_started == 1)
            {
                validate_map_line(line, d_list);
                if (find_line_length(line) > map->raw_length)
                    map->raw_length = find_line_length(line);
                //check noch dass das zählen bei der letzten ziffer endet
                map->raw_height++;
            }
        }
        d_list->map->file_length++;
        free(line);
        line = NULL;
        line = get_next_line(map->fd);
    }
    if (d_list->map->map_started == 0)
        p_error("Error\nNo map found\n", d_list);
    check_map_scale_factor(d_list);
    close(map->fd);
    return (1);
}
