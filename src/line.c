/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:54:51 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/29 13:46:16 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    line(t_common *d_list, double p1[2], double p2[2], int color)
{
	int		step;
	int		i;
	double	delta[2];
	
	delta[0] = p2[0] - p1[0];
	delta[1] = p2[1] - p1[1];
	if (fabs(delta[0]) >= fabs(delta[1]))
		step = fabs(delta[0]);
	else
		step = fabs(delta[1]);
	delta[0] /= step;
	delta[1] /= step;
	i = 0;
	while (i < step)
	{
        my_mlx_pixel_put(d_list->mlx, p1[0], p1[1], color);
		p1[0] += delta[0];
		p1[1] += delta[1];
		i++;
	}
}

void    wall(t_common *d_list, double p1[2], double p2[2], int fd, int x)
{
	int		i;
	int		color;
	double	w;
	double	len;
	double	step;
	
	step = d_list->mlx[fd].tex_dim[1] / (p1[1] - p2[1]);
	len = 0;
	i = p2[1];
	while (i < fabs(p1[1]))
	{
		modf(len, &w);
		color = my_mlx_pixel_get(&d_list->mlx[fd], d_list->rc->hit[x][4] * d_list->mlx[fd].tex_dim[0], w);
		len += step;
        my_mlx_pixel_put(d_list->mlx, p1[0], i, color);
		i++;
	}
}
