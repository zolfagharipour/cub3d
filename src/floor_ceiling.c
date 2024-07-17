/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:17:35 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 16:32:20 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    floor_ceiling(t_common *d_list)
{
	int i[2];

	i[0] = 0;
	while (i[0] < WIDTH)
	{
		i[1] = 0;
		while (i[1] < HEIGHT / 2)
		{
			my_mlx_pixel_put(d_list->mlx, i[0], i[1], SKY);
			i[1]++;
		}
		i[0]++;
	}
	i[0] = 0;
	while (i[0] < WIDTH)
	{
		i[1] = HEIGHT / 2;
		while (i[1] < HEIGHT)
		{
			my_mlx_pixel_put(d_list->mlx, i[0], i[1], FLOOR);
			i[1]++;
		}
		i[0]++;
	}
}