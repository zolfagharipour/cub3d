/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:54:08 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:54:10 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	find_color(char *line, t_common *d_list, int id, int s)
{
	int		i;
	int		rgb;

	while (line[s] && line[s] == ' ')
		s++;
	if (cut_lines(d_list, line, s, id) == 0)
		return (0);
	rgb = decipher_colors(d_list, s, id, line);
	if (rgb == -1)
		return (0);
	d_list->map->color[id] = rgb;
	d_list->map->val_aspects[id] = FOUND;
	return (1);
}

int	decipher_colors(t_common *d_list, int s, int id, char *line)
{
	int	red;
	int	green;
	int	blue;
	int	rgb;

	red = extract_color(d_list, line, &s);
	if (line[s] && line[s + 1] && line[s] == ',' && ft_isdigit(line[s + 1]))
		s++;
	green = extract_color(d_list, line, &s);
	if (line[s] && line[s + 1] && line[s] == ',' && ft_isdigit(line[s + 1]))
		s++;
	blue = extract_color(d_list, line, &s);
	s = s - 1;
	if (red == -1 || green == -1 || blue == -1)
		return (-1);
	while (line[++s])
	{
		if (line[s] != ' ' && line[s] != '\n' && line[s] != '\0')
			return (-1);
	}
	rgb = (red << 16) | (green << 8) | blue;
	return (rgb);
}

int	extract_color(t_common *d_list, char *line, int *s)
{
	char	*color;
	int		rgb;
	int		i;

	color = NULL;
	i = 0;
	while (ft_isdigit(line[*s + i]))
		i++;
	if (i == 0)
		return (-1);
	color = ft_substr(line, *s, i);
	if (!color)
		p_error("Error\nMalloc failed", d_list);
	*s += i;
	rgb = ft_atoi(color);
	free(color);
	if (rgb < 0 || rgb > 255)
		return (-1);
	return (rgb);
}

int	cut_lines(t_common *d_list, char *line, int s, int identifier)
{
	d_list->map->val_aspects[identifier] = INV_FORMAT;
	if (line[s] == '\0' || line[s] == '\n' || ft_isdigit(line[s]) == 0)
		return (0);
	return (1);
}
