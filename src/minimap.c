/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:40:35 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/27 13:04:31 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

static int		free_mmap(int **minimap)
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
	int	ii;
	int	jj;

	ii = 0;
	while (ii < scale)
	{
		jj = 0;
		while (jj < scale)
		{
			dlist->map->minimap[scale * i + ii][scale * j + jj] = dlist->map->raw_map[i][j];
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
	while (i < dlist->map->raw_height)
	{
		j = 0;
		while (j < dlist->map->raw_length)
		{
			scale_mmap(dlist, i , j, scale);
			j++;
		}
		i++;
	}
}

int		minimap(t_common *dlist)
{
	int		i;
	int		j;
	t_map	*map;

	map = dlist->map;

    map->minimap = (int **)malloc(map->raw_height * sizeof(int *) * dlist->map->scale);
    if (!map->minimap)
        return (cleanup(dlist), 0);

	i = 0;
    while (i < dlist->map->scale * map->raw_height)
    {
        map->minimap[i] = (int *)malloc(dlist->map->scale * map->raw_length * sizeof(int));
        if (map->minimap[i] == NULL)
            return (cleanup(dlist), 0);
        i++;
    }
	fill_mmap(dlist, dlist->map->scale);
	return (1);
}
