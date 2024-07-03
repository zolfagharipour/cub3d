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

int is_valid_boundary(int x, int y, t_map *map) {
    return (x >= 0 && x < map->raw_length && y >= 0 && y < map->raw_height
    && map->raw_map[x][y] == 1);
}

int valid_map_boundaries(t_common *d_list)
{
    int x;
    int y;
    int x_start;
    int y_start;
    int x_prev;
    int y_prev;
    //int direction;
    int **raw_map;

    x_start = 0;
    y_start = 0;
    x_prev = 0;
    y_prev = 0;
    raw_map = d_list->map->raw_map;
    //valid start check
    while (x_start < d_list->map->raw_length && raw_map[x_start][y_start] == 6)
        x_start++;
    if (!is_valid_boundary(x_start, y_start, d_list->map))
        return (0);
    // while ()
    // while (x_start <= d_list->map->raw_length && raw_map[x_start][y_start] == 1)
    //     x_start++;
    
    
    // Starting point: top-left corner

   return (1);
}

int read_map_from_file(t_common *d_list)
{
    if (!determine_map_size(d_list))
        return 0;
    if (!malloc_raw_map(d_list))
        return 0;
    if (!fill_raw_map(d_list))
        return 0;
    if (!valid_map_boundaries(d_list))
        p_error("Invalid map boundaries", d_list);
    print_map(d_list->map);
    //find_the_players_position(d_list);
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
    while (line[i] && line[i] == ' ')
        i++;
    return (i);
}

int validate_map_line(char *line, t_common *d_list)
{
    int i;
    int digit_sequence_start;

    i = 0;
    digit_sequence_start = 0;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] == '0' || line[i] == '1' || line[i] == '3' || line[i] == '4')
            digit_sequence_start = 1;
        else if (line[i] == ' ')
        {
            if (digit_sequence_start)
            {
                while (line[i] && line[i] == ' ')
                    i++;
                if (line[i] == '\n' || line[i] == '\0')
                    break ;
                else if (line[i] == '1' || line[i] == '0' || line[i] == '3' || line[i] == '4')
                    d_list->map->val_map[INV_SPACE] = 1;
                else
                    d_list->map->val_map[INV_CHAR] = 1;
            }
        }
        else if (line[i] == 'S' || line[i] == 'N' || line[i] == 'W' || line[i] == 'E')
        {
            if (d_list->map->player_found)
                d_list->map->val_map[MULTIPLE_PLAYERS] = 1;
            else
                d_list->map->player_found = 1;
        }
        else
            d_list->map->val_map[INV_CHAR] = 1;
        i++;
    }
    //d_list->map->previous_line_valid = 1;
    return (1);
}


//1 for found and valid
//0 for not found
//2 for found but not valid/cant open
//3 for found but not valid/invalid identitfy format
int all_but_map_components_found(int *components)
{
    int i = 0;

    while (i < 6)
    {
        if (components[i] != 1)
            return (0);
        i++;
    }
    return (1);
}

int line_not_empty(char *line)
{
    int i = 0;

    while (line[i] && line[i] == ' ')
        i++;
    if (line[i] == '\n')
        return (0);
    return (1);
}

int find_texture(char *line, t_common *d_list, int identifyer, int start)
{
    int i;
    int texture_found;
    int fd;

    i = 0;
    fd = 0;
    texture_found = 0;
    while (line[start] && line[start] == ' ')
        start++;
    while (line[start + i] && line[start + i] != ' ' && line[start + i] != '\n')
        i++;
    d_list->map->textures[identifyer] = ft_substr(line, start, i);
    d_list->map->val_aspects[identifyer] = FOUND;
    if (d_list->map->textures[identifyer] == NULL)
        return (p_error("Malloc failed", d_list), 0);
    printf("texture: %s\n", d_list->map->textures[identifyer]);
    while (line[start + i] && line[start + i] == ' ')
        i++;
    if (line[start + i] && line[start + i] != '\n' && line[start + i] != ' ')
        d_list->map->val_aspects[identifyer] = INV_FORMAT;
    printf("line: %s", line);
    fd = open(d_list->map->textures[identifyer], O_RDONLY);
    if (fd < 0)
        d_list->map->val_aspects[identifyer] = INV_OPEN_COL;
    else
        close(fd);
    return 1;
}

void    evaluate_line(char *line, t_common *d_list)
{
    int i = 0;


    while (line[i] && line[i] == ' ')
        i++;
    if (line[i] == '\n')
        return ;
    if (line[i] && line[i+1] && line[i] == 'N' && line[i + 1] == 'O')
        find_texture(line, d_list, N, i + 2);
    else if (line[i] && line[i+1] && line[i] == 'S' && line[i + 1] == 'O')
        find_texture(line, d_list, S, i + 2);
    else if (line[i] && line[i+1] && line[i] == 'E' && line[i + 1] == 'A')
        find_texture(line, d_list, E, i + 2);
    else if (line[i] && line[i+1] && line[i] == 'W' && line[i + 1] == 'E')
        find_texture(line, d_list, W, i + 2);
    // else if (line[i] && line[i+1] && line[i] == 'C' && line[i + 1] == ' ')
    //     find_color(line, d_list, CEILING, i + 2);
    // else if (line[i] && line[i+1] && line[i] == 'F' && line[i + 1] == ' ')
    //     find_color(line, d_list, FLOOR_N, i + 2);
    else if (line[i] && line[i] == '1' || line[i] == '0' || line[i] == 'S' 
            || line[i] == 'W' || line[i] == 'E' || line[i] == 'N' || line[i] == '3' || line[i] == '4')
        d_list->map->map_started = 1;
    //check if this p_error format fits
    else
        p_error("Invalid identifier in the map file", d_list);
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
        //skip nl and space
        if (line_not_empty(line))
        {
            //check each individual line
            if (d_list->map->map_started == 0)
                evaluate_line(line, d_list);
            //starts checking map if map has started
            if (d_list->map->map_started == 1)
            {
                if (!validate_map_line(line, d_list))
                    return (0);
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
    check_all_parts_found_and_valid(d_list);
    check_map_scale_factor(d_list);
    close(map->fd);
    return (1);
}

void print_map_error(t_common *d_list, int error)
{
    if (error == INV_SPACE)
        write(1, "Error\nInvalid space in map\n", 28);
    else if (error == MULTIPLE_PLAYERS)
        write(1, "Error\nMultiple players found\n", 30);
    else if (error == INV_CHAR)
        write(1, "Error\nInvalid character in map\n", 33);
    else if (error == INV_OPEN_COL)
        write(1, "Error\nInvalid open color\n", 26);
    else if (error == INV_FORMAT)
        write(1, "Error\nInvalid format\n", 22);
}

void print_color_texture_error(t_common *d_list, int error)
{

    if (error == NOT_FOUND)
        write(1, "Error\nA Texture and/or color is missing\n", 40);
    else if (error == INV_OPEN_COL)
        write(1, "Error\nInvalid open of texture and/or invalid color\n", 52);
    else if (error == INV_FORMAT)
        write(1, "Error\nInvalid format of color and/or texture\n", 46);
}

void check_all_parts_found_and_valid(t_common *d_list)
{
    int at_least_one_error;
    int i;

    //change back to -1 if color check is implemented
    i = 1;
    at_least_one_error = 0;
    while (++i < 6)
    {
        if (d_list->map->val_aspects[i] == NOT_FOUND
            || d_list->map->val_aspects[i] == INV_OPEN_COL
            || d_list->map->val_aspects[i] == INV_FORMAT)
        {
            printf("i: %d\n", i);
            print_color_texture_error(d_list, i);
            at_least_one_error = 1;
        }
    }
    if (d_list->map->map_started == 0)
        write (1, "Error\nNo map found\n", 20);
    i = -1;
    while (++i < 5)
    {
        if (d_list->map->val_map[i] == 1)
        {
            print_map_error(d_list, i);
            at_least_one_error = 1;
        }
    }
    if (d_list->map->player_found == 0)
    {
        write(1, "Error\nNo player found\n", 22);
        at_least_one_error = 1;
    }
    if (at_least_one_error)
        cleanup(d_list);
}
