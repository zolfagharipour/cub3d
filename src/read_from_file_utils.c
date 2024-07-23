/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:54:28 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:54:30 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	determine_map_size_and_val(t_common *d_list)
{
	char	*line;
	t_map	*map;
	int		last;

	map = d_list->map;
	map->fd = open(d_list->map->file, O_RDONLY);
	if (map->fd == -1)
		return (0);
	line = NULL;
	line = get_next_line(map->fd);
	while (line)
	{
		gnl_loop(d_list, line, &last);
		free(line);
		line = get_next_line(map->fd);
		if (!line && last == TRUE)
			d_list->map->val_map[INV_NL] = 1;
	}
	if (d_list->map->map_started == 0)
		p_error("Error\nNo map found", d_list);
	check_map_scale_factor(d_list);
	close(map->fd);
	return (1);
}

void	gnl_loop(t_common *d_list, char *line, int *last)
{
	t_map	*map;

	*last = FALSE;
	map = d_list->map;
	if (d_list->map->map_started == 1
		&& line[ft_strlen(line) - 1] == '\n')
			*last = TRUE;
	if (line_empty(line) && d_list->map->map_started == 1)
		d_list->map->val_map[INV_NL] = 1;
	if (!line_empty(line))
	{
		if (d_list->map->map_started == 0)
			evaluate_line(line, d_list);
		if (d_list->map->map_started == 1)
		{
			validate_map_line(line, d_list);
			if ((int)ft_strlen(line) - 1 > map->raw_length)
				map->raw_length = ft_strlen(line) - 1;
			map->raw_height++;
		}
	}
	d_list->map->file_length++;
}

void	validate_map_line(char *line, t_common *d_list)
{
	int	i;
	int	digit_sequence_start;

	i = 0;
	digit_sequence_start = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'S' || line[i] == 'N' || line[i] == 'W'
			|| line[i] == 'E')
		{
			if (d_list->map->player_found)
				d_list->map->val_map[MULTIPLE_PLAYERS] = 1;
			else
				d_list->map->player_found = 1;
		}
		else if (line[i] != '0' && line[i] != '1'
			&& line[i] != ' ')
			(free(line), p_error("Error\nInvalid character in map", d_list));
		i++;
	}
}

int	line_empty(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (1);
	return (0);
}

void cut_ws(char *line, int *s)
{
	while (line[*s] && line[*s] == ' ')
		(*s)++;
	if (line[*s] && line[*s + 1] && line[*s] == ',')
		(*s)++;
	while (line[*s] && line[*s] == ' ')
		(*s)++;
}
