/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:17:35 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/22 17:44:37 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

// void	floor_ceiling(t_common *d_list)
// {
// 	int		i[2];

// 	i[0] = 0;
// 	while (i[0] < WIDTH)
// 	{
// 		i = 0;
// 		while (i < HEIGHT / 2)
// 		{
// 			my_mlx_pixel_put(d_list->mlx,
// 				i[0], i, d_list->map->color[CEILING]);
// 			i++;
// 		}
// 		i[0]++;
// 	}
// 	i[0] = 0;
// 	while (i[0] < WIDTH)
// 	{
// 		i = HEIGHT / 2;
// 		while (i < HEIGHT)
// 			my_mlx_pixel_put(d_list->mlx,
// 				i[0], i++, d_list->map->color[FLOOR]);
// 		i[0]++;
// 	}
// }
void	floor_ceiling(t_common *d_list, double p1[2], double p2[2])
{
	int		i;

	i = 0;
	while (i < p2[1])
	{
		my_mlx_pixel_put(d_list->mlx,
			p2[0], i, d_list->map->color[CEILING]);
		i++;
	}
	i = p1[1];
	while (i < HEIGHT)
	{
		my_mlx_pixel_put(d_list->mlx,
			p1[0], i, d_list->map->color[FLOOR]);
		i++;
	}
}
