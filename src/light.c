/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:45:03 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 16:32:07 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	light_adjust(int rgb, double light)
{
	int	color[3];
	int	i;

	color[0] = (rgb >> 16) & 0XFF;
	color[1] = (rgb >> 8) & 0XFF;
	color[2] = rgb & 0XFF;
	i = 0;
	while (i < 3)
	{
		color[i] *= light;
		if (color[i] > 0XFF)
			color[i] = 0XFF;
		i++;
	}
	return ((color[0] << 16) | (color[1] << 8) | color[2]);
}

int	wall_lighting(t_common *d_list, int color, int x)
{
	if (d_list->rc->hit[x][3] == N)
		return (color);
	if (d_list->rc->hit[x][3] == S)
		return (light_adjust(color, 0.1));
	if (d_list->rc->hit[x][3] == E)
		return (light_adjust(color, 0.3));
	if (d_list->rc->hit[x][3] == W)
		return (light_adjust(color, 0.7));
	return (color);
}
