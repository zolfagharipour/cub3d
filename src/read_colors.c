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

void	find_color(char *line, t_common *d_list, int id, int s)
{
	int		i;
	char	*red;
	char	*green;
	char	*blue;

	i = 0;
	while (line[s] && line[s] == ' ')
		s++;
	if (cut_lines(d_list, line, s, id) == 0)
		return ;
	if (extract_color(&red, line, &s, i) == 0)
		return ;
	if (extract_color(&green, line, &s, i) == 0)
		return ;
	while (ft_isdigit(line[s + i]))
		i++;
	blue = ft_substr(line, s, i);
	s = s + i - 1;
	while (line[++s])
	{
		if (line[s] != ' ' && line[s] != '\n' && line[s] != '\0')
			return ;
	}
	if (suitable_color_range(&d_list->map->color[id], red, green, blue))
		d_list->map->val_aspects[id] = FOUND;
}

int	cut_lines(t_common *d_list, char *line, int s, int identifier)
{
	d_list->map->val_aspects[identifier] = INV_FORMAT;
	if (line[s] == '\0' || line[s] == '\n' || ft_isdigit(line[s]) == 0)
		return (0);
	return (1);
}

int	extract_color(char **color, char *line, int *s, int i)
{
	while (ft_isdigit(line[*s + i]))
		i++;
	if (i == 0)
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

int	suitable_color_range(int *store_location, char *r, char *g, char *b)
{
	int	red;
	int	blue;
	int	green;
	int	color;

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
	*store_location = color;

	return (1);
}
