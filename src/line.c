/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:54:51 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/23 23:07:39 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    line(t_common *d_list, double p1[2], double p2[2], int color)
{
	int	step;
	double	x;
	double	y;
	int	i;
	double	delta[2];
	
	delta[0] = p2[0] - p1[0];
	delta[1] = p2[1] - p1[1];
	if (fabs(delta[0]) >= fabs(delta[1]))
		step = fabs(delta[0]);
	else
		step = fabs(delta[1]);
	delta[0] /= step;
	delta[1] /= step;
	x = p1[0];
	y = p1[1];
	i = 0;
	while (i < step)
	{
        my_mlx_pixel_put(d_list->mlx, x, y, color);
		x += delta[0];
		y += delta[1];
		i++;
	}
}
