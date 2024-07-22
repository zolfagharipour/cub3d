/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:53:09 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:53:11 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	is_texture(int i, char *line, char id, char id2)
{
	if (line[i] && line[i + 1] && line [i + 2] && line[i] == id
		&& line[i + 1] == id2 && line[i + 2] == ' ')
		return (1);
	return (0);
}

int	is_color(int i, char *line, char id)
{
	if (line[i] && line[i + 1] && line[i] == id && line[i + 1] == ' ')
		return (1);
	return (0);
}

int	all_ids_found(t_common *d_list)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (d_list->map->val_aspects[i] == NOT_FOUND)
			return (0);
		i++;
	}
	return (1);
}
