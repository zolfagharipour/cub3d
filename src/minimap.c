/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:40:35 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/21 16:14:48 by mzolfagh         ###   ########.fr       */
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
			dlist->map->minimap[i + ii][j + jj] = dlist->map->raw_map[i][j];
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
	t_map	*mmap;
	int		i;
	int		j;


	mmap = dlist->map;
	mmap->scale = 3;
	mmap->minimap = malloc(sizeof(int *) * mmap->scale * mmap->raw_height);
	if (!mmap->minimap)
		return (0);
	i = 0;
	while (i < mmap->scale * mmap->raw_length)
	{
		mmap->minimap[i] = malloc(sizeof(int) * mmap->scale * mmap->raw_length);
		if (!mmap->minimap[i])
			return (free_mmap(mmap->minimap));
	}
	fill_mmap(dlist, mmap->scale);
	return (1);
}

// void	set(t_common *dlist)
// {
// 	int arr[5][6] = {
// 		{1, 1, 1, 1, 1, 1},
// 		{1, 0, 0, 1, 0, 1},
// 		{1, 0, 1, 0, 0, 1},
// 		{1, 1, 0, 0, 1, 1},
// 		{1, 1, 1, 1, 1, 1}
// 	};
// 	t_map mmap;
// 	mmap.raw_map = malloc(sizeof(int *) * 6);
// 	for (int k = 0; k < 5; k++)
// 	{
// 		mmap.raw_map[k] = malloc(sizeof(int) * 5);
// 	}
// 	for (int i = 0; i < 5; i++)
// 	{
// 		for (int j = 0; j < 6; j++)
// 		{
// 			mmap.raw_map[i][j] = arr[i][j];
// 		}
// 		write (1, "\n", 1);
// 	}
// 	dlist->map = &mmap;
// }

// int main()
// {
// 	t_common	*dlist;

// 	set(dlist);
// 	minimap(dlist);
// 	for (int i = 0; i < 15; i++)
// 	{
// 		for (int j = 0; j < 18; j++)
// 		{
// 			printf("%d ", dlist->map->minimap[i][j]);
// 		}
// 		write (1, "\n", 1);
// 	}
// }