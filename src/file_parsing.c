/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:53:00 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:53:03 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	evaluate_line(char *line, t_common *d_list)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return ;
	if (is_texture(i, line, 'N', 'O') && d_list->map->val_aspects[N] == 6)
		find_texture(line, d_list, N, i + 2);
	else if (is_texture(i, line, 'S', 'O') && d_list->map->val_aspects[S] == 6)
		find_texture(line, d_list, S, i + 2);
	else if (is_texture(i, line, 'E', 'A') && d_list->map->val_aspects[E] == 6)
		find_texture(line, d_list, E, i + 2);
	else if (is_texture(i, line, 'W', 'E') && d_list->map->val_aspects[W] == 6)
		find_texture(line, d_list, W, i + 2);
	else if (is_color(i, line, 'C') && d_list->map->val_aspects[CEILING] == 6)
		find_color(line, d_list, CEILING, i + 2);
	else if (is_color(i, line, 'F') && d_list->map->val_aspects[FLOOR] == 6)
		find_color(line, d_list, FLOOR, i + 2);
	else if (line[i] && (line[i] == '1' || line[i] == '0' || line[i] == '3'
			|| line[i] == '4') && all_ids_found(d_list))
		d_list->map->map_started = 1;
	else
		p_error("Error\nInvalid or missing identifier in the map file", d_list);
}

int	find_texture(char *line, t_common *d_list, int identifyer, int start)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	d_list->map->val_aspects[identifyer] = FOUND;
	while (line[start] && line[start] == ' ')
		start++;
	if (line[start] == '\0' || line[start] == '\n')
		return (d_list->map->val_aspects[identifyer] = INV_FORMAT);
	while (line[start + i] && line[start + i] != ' ' && line[start + i] != '\n')
		i++;
	d_list->map->textures[identifyer - 2] = ft_substr(line, start, i);
	if (d_list->map->textures[identifyer - 2] == NULL)
		return (p_error("Error\nMalloc failed", d_list), 0);
	while (line[start + i] && line[start + i] == ' ')
		i++;
	if (line[start + i] && line[start + i] != '\n' && line[start + i] != ' ')
		d_list->map->val_aspects[identifyer] = INV_FORMAT;
	fd = open(d_list->map->textures[identifyer - 2], O_RDONLY);
	if (fd < 0)
		d_list->map->val_aspects[identifyer] = INV_OPEN_COL;
	else
		close(fd);
	return (1);
}
