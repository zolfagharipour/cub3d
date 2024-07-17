/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ninja.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:45:34 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 16:33:39 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	respone_ninja(t_common *d_list)
{
	int	i[2];

	i[0] = 0;
	while (i[0] < d_list->map->raw_length)
	{
		i[1] = 0;
		while (i[1] < d_list->map->raw_height)
		{
			if (d_list->map->raw_map[i[0]][i[1]] == 0 && rand() / (float)RAND_MAX > 0.97)
			{
				d_list->rc->sprite[0] = i[0] + 0.5;
				d_list->rc->sprite[1] = i[1] + 0.5;
				return;
			}
			i[1]++;
		}
		i[0]++;
		if (i[0] == d_list->map->raw_length - 1)
			i[0] = 0;
	}
}

void	ninja(t_common *d_list)
{
	if (d_list->rc->ninja_found < 4 && d_list->rc->sprite[2] < 5)
	{
		while(d_list->rc->frame < 9)
		{
			d_list->rc->frame++;
			put_image(d_list, d_list->mlx);
			usleep(70000);
		}
		respone_ninja(d_list);
		d_list->rc->frame = 0;
		d_list->rc->ninja_found++;
	}
	else if (d_list->rc->frame != 12)
	{
		d_list->rc->frame = 10;
		while (d_list->rc->frame < 13)
		{
			put_image(d_list, d_list->mlx);
			d_list->rc->frame++;
			usleep(100000);

		}
		d_list->rc->frame = 12;
	}
	put_image(d_list, d_list->mlx);
}
