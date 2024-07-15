#include "cubid.h"

void    evaluate_line(char *line, t_common *d_list)
{
    int i = 0;

    while (line[i] && line[i] == ' ')
        i++;
    if (line[i] == '\n')
        return ;
    if (line[i] && line[i+1]  && line [i + 2]&& line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
        find_texture(line, d_list, N, i + 2);
    else if (line[i] && line[i+1]  && line [i + 2]&& line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
        find_texture(line, d_list, S, i + 2);
    else if (line[i] && line[i+1] && line [i + 2] && line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
        find_texture(line, d_list, E, i + 2);
    else if (line[i] && line[i+1] && line [i + 2] && line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
        find_texture(line, d_list, W, i + 2);
    else if (line[i] && line[i+1] && line[i] == 'C' && line[i + 1] == ' ')
        find_color(line, d_list, CEILING, i + 2);
    else if (line[i] && line[i+1] && line[i] == 'F' && line[i + 1] == ' ')
        find_color(line, d_list, FLOOR_N, i + 2);
    else if (line[i] && line[i] == '1' || line[i] == '0' || line[i] == 'S' 
            || line[i] == 'W' || line[i] == 'E' || line[i] == 'N' || line[i] == '3' || line[i] == '4')
        d_list->map->map_started = 1;
    //check if this p_error format fits
    else
        p_error("Invalid identifier in the map file", d_list);
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
    if (d_list->map->textures[identifyer] == NULL)
        return (p_error("Malloc failed", d_list), 0);
    d_list->map->val_aspects[identifyer] = FOUND;
    while (line[start + i] && line[start + i] == ' ')
        i++;
    if (line[start + i] && line[start + i] != '\n' && line[start + i] != ' ')
        d_list->map->val_aspects[identifyer] = INV_FORMAT;
    fd = open(d_list->map->textures[identifyer], O_RDONLY);
    if (fd < 0)
        d_list->map->val_aspects[identifyer] = INV_OPEN_COL;
    else
        close(fd);
    return 1;
}

int extract_color(char **color, char *line, int *start, int i)
{
    while (ft_isdigit(line[*start + i]))
        i++;
    if (i == 0) // No digits found
        return 0;
    *color = ft_substr(line, *start, i);
    *start += i;
    i = 0;
    if (line[*start] && line[*start] && line[*start] == ',' && ft_isdigit(line[*start + 1]))
    {
        (*start)++;
       return (1);
    }
    else
        return 0;
}

//it doesnt stop if the colors arent found
void    find_color(char *line, t_common *d_list, int identifier, int start)
{
    int i;
    char    *red;
    char    *green;
    char    *blue;

    i = 0;
    while (line[start] && line[start] == ' ')
        start++;
    d_list->map->val_aspects[identifier] = INV_FORMAT;
    if (line[start] == '\0' || line[start] == '\n' || ft_isdigit(line[start]) == 0)
        return ;
    ft_printf("check");
    if (extract_color(&red, line, &start, i) == 0)
        return ;
    ft_printf("check");
    if (extract_color(&green, line, &start, i) == 0)
        return ;
    // while (ft_isdigit(line[start + i]))
    //     i++;
    // red = ft_substr(line, start, i);
    // start += i;
    // i = 0;
    // if (line[start] && line[start] && line[start] == ',' && ft_isdigit(line[start + 1]))
    //     start++;
    // else
    //     return ;
    
    // while (ft_isdigit(line[start + i]))
    //     i++;
    // green = ft_substr(line, start, i);
    // start += i;
    // i = 0;
    // if (line[start] && line[start] && line[start] == ',' && ft_isdigit(line[start + 1]))
    //     start++;
    // else
    //     return ;
   ft_printf("red:%d", red);
    while (ft_isdigit(line[start + i]))
        i++;
    blue = ft_substr(line, start, i);
    start += i;
    start++;
    while (line[start])
    {
        if (line[start] != ' ' && line[start] != '\n' && line[start] != '\0')
            return ;
    }
    if (suitable_color_range(d_list, red, green, blue) == 0)
        return ; 
    d_list->map->val_aspects[identifier] = FOUND;
} 
