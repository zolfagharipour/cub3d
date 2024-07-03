/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:37:28 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/03 11:32:54 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	check_dim(t_common *d_list, int i[2])
{
	
	if (i[0] < 0)
		i[0] = 0;
	if (i[0] >= d_list->map->raw_length)
		i[0] = d_list->map->raw_length;
	if (i[1] < 0)
		i[1] = 0;
	if (i[1] >= d_list->map->raw_height)
		i[1] = d_list->map->raw_height;
}

void	open_door(t_common *d_list, int i[2])
{
	int		end[2];
	int		i1;
	
	end[0] = i[0] + 3;
	end[1] = i[1] + 3;
	check_dim(d_list, i);
	i1 = i[1];
	while (i[0] <= end[0])
	{
		while (i[1] <= end[1])
		{
			if (d_list->map->raw_map[i[0]][i[1]] == 4)
			{
				printf ("DOOR\n");
				d_list->map->raw_map[i[0]][i[1]] = 0;	
			}
			i[1]++;
		}
		i[1] = i1;
		i[0]++;
	}
	put_image(d_list, d_list->mlx);
}

void	door(t_common *d_list)
{
	int		i[2];

	i[0] = (int) d_list->rc->pos[0];
	i[1] = (int) d_list->rc->pos[1];
	if (d_list->rc->dir > 1.75 && d_list->rc->dir < 0.25)
	{
		i[0] += 1;
		i[1] -= 1;
	}
	else if (d_list->rc->dir > 0.25 && d_list->rc->dir < 0.75)
	{
		i[0] -= 1;
		i[1] -= 3;
	}
	else if (d_list->rc->dir > 0.75 && d_list->rc->dir < 1.25)
	{
		i[0] -= 3;
		i[1] -= 1;
	}
	else if (d_list->rc->dir > 1.25 && d_list->rc->dir < 1.75)
	{
		i[0] -= 1;
		i[1] += 1;
	}
	open_door(d_list, i);
}