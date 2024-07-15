#include "cubid.h"

void	evaluate_line(char *line, t_common *d_list)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\n')
		return ;
	if (line[i] && line[i + 1] && line [i + 2] && line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		find_texture(line, d_list, N, i + 2);
	else if (line[i] && line[i + 1] && line [i + 2] && line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		find_texture(line, d_list, S, i + 2);
	else if (line[i] && line[i + 1] && line [i + 2] && line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		find_texture(line, d_list, E, i + 2);
	else if (line[i] && line[i + 1] && line [i + 2] && line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		find_texture(line, d_list, W, i + 2);
	else if (line[i] && line[i + 1] && line[i] == 'C' && line[i + 1] == ' ')
		find_color(line, d_list, CEILING, i + 2);
	else if (line[i] && line[i + 1] && line[i] == 'F' && line[i + 1] == ' ')
		find_color(line, d_list, FLOOR_N, i + 2);
	else if (line[i] && line[i] == '1' || line[i] == '0' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E' || line[i] == 'N' || line[i] == '3' || line[i] == '4')
		d_list->map->map_started = 1;
	//check if this p_error format fits
	else
		p_error("Invalid identifier in the map file", d_list);
}

int	find_texture(char *line, t_common *d_list, int identifyer, int start)
{
	int	i;
	int	texture_found;
	int	fd;

	i = 0;
	fd = 0;
	texture_found = 0;
	while (line[start] && line[start] == ' ')
		start++;
	while (line[start + i] && line[start + i] != ' ' && line[start + i] != '\n')
		i++;
	d_list->map->textures[identifyer - 2] = ft_substr(line, start, i);
	if (d_list->map->textures[identifyer - 2] == NULL)
		return (p_error("Malloc failed", d_list), 0);
	d_list->map->val_aspects[identifyer] = FOUND;
	while (line[start + i] && line[start + i] == ' ')
		i++;
	if (line[start + i] && line[start + i] != '\n' && line[start + i] != ' ')
		d_list->map->val_aspects[identifyer] = INV_FORMAT;
	fd = open(d_list->map->textures[identifyer - 2], O_RDONLY);
	if (fd < 0)
		d_list->map->val_aspects[identifyer] = INV_OPEN_COL;
	else
		close(fd);
	return 1;
}

int	extract_color(char **color, char *line, int *s, int i)
{
	while (ft_isdigit(line[*s + i]))
		i++;
	if (i == 0) // No digits found
		return (0);
	*color = ft_substr(line, *s, i);
	*s += i;
	i = 0;
	if (line[*s] && line[*s] && line[*s] == ',' && ft_isdigit(line[*s + 1]))
	{
		(*s)++;
		return (1);
	}
	else
		return (0);
}

void	find_color(char *line, t_common *d_list, int identifier, int s)
{
	int		i;
	char	*red;
	char	*green;
	char	*blue;

	i = 0;
	while (line[s] && line[s] == ' ')
		s++;
	d_list->map->val_aspects[identifier] = INV_FORMAT;
	if (line[s] == '\0' || line[s] == '\n' || ft_isdigit(line[s]) == 0)
		return ;
	if (extract_color(&red, line, &s, i) == 0)
		return ;
	if (extract_color(&green, line, &s, i) == 0)
		return ;
	while (ft_isdigit(line[s + i]))
		i++;
	blue = ft_substr(line, s, i);
	s += i;
	while (line[++s])
	{
		if (line[s] != ' ' && line[s] != '\n' && line[s] != '\0')
			return ;
	}
	suitable_color_range(d_list, red, green, blue, identifier);
}

