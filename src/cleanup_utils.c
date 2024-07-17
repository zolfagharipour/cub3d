/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:55 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:52:11 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	cleanup_map(t_map *map)
{
	int	i;

	if (map && map->raw_map)
	{
		i = -1;
		while (++i < map->raw_length)
		{
			if (map->raw_map[i])
			{
				free(map->raw_map[i]);
				map->raw_map[i] = NULL;
			}
		}
		free(map->raw_map);
		map->raw_map = NULL;
	}
	if (map && map->file)
		free(map->file);
	i = -1;
	while (++i < 4)
	{
		free(map->textures[i]);
		map->textures[i] = NULL;
	}
	cleanup_minimap(map);
}

void	cleanup_minimap(t_map *map)
{
	int	i;

	if (map && map->minimap)
	{
		i = -1;
		while (++i < map->raw_length * map->scale)
		{
			if (map->minimap[i])
			{
				free(map->minimap[i]);
				map->minimap[i] = NULL;
			}
		}
		free(map->minimap);
		map->minimap = NULL;
	}
}
