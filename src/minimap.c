/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:40:35 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 16:33:26 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

static int	free_mmap(int **minimap)
{
	int		i;

	i = 0;
	while (minimap[i])
		free(minimap[i++]);
	free(minimap);
	return (0);
}

static void	scale_mmap(t_common *dlist, int i, int j, int scale)
{
	int		ii;
	int		jj;
	t_map	*map;

	map = dlist->map;
	ii = 0;
	while (ii < scale)
	{
		jj = 0;
		while (jj < scale)
		{
			map->minimap[scale * i + ii][scale * j + jj] = map->raw_map[i][j];
			jj++;
		}
		ii++;
	}
}

static void	fill_mmap(t_common *dlist, int scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < dlist->map->raw_length)
	{
		j = 0;
		while (j < dlist->map->raw_height)
		{
			scale_mmap(dlist, i, j, scale);
			j++;
		}
		i++;
	}
}

int	minimap(t_common *dlist)
{
	int		i;
	int		j;
	t_map	*map;

	map = dlist->map;
	map->minimap = (int **)malloc(map->raw_length * sizeof(int *) * map->scale);
	if (!map->minimap)
		return (cleanup(dlist), 0);
	i = 0;
	while (i < dlist->map->scale * map->raw_length)
	{
		map->minimap[i] = (int *)malloc(map->scale * map->raw_height * 4);
		if (map->minimap[i] == NULL)
			return (cleanup(dlist), 0);
		i++;
	}
	fill_mmap(dlist, dlist->map->scale);
	return (1);
}
