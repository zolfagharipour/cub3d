/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:50:02 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/30 15:28:58 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    wall(t_common *d_list, double p1[2], double p2[2], int x)
{
	int		i[2];
	int		color;
	double	w;
	double	len;
	double	step;
	
	step = d_list->mlx[(int)d_list->rc->hit[x][3]].tex_dim[1] / (p1[1] - p2[1]);
	len = 0;
	i[1] = 0;
	while (i[1] < 2)
	{
		i[0] = p2[1];
		while (i[0] < fabs(p1[1]))
		{
			if ((i[1] == 0 && d_list->rc->sprite[4] > d_list->rc->hit[x][2]) || (i[1] == 1 && d_list->rc->sprite[4] < d_list->rc->hit[x][2]))
			{
				modf(len, &w);
				color = my_mlx_pixel_get(&d_list->mlx[(int)d_list->rc->hit[x][3]], d_list->rc->hit[x][4] * d_list->mlx[(int)d_list->rc->hit[x][3]].tex_dim[0], w);
				len += step;
				if (p1[0] >= 0 && p1[0] < HEIGHT)
					my_mlx_pixel_put(d_list->mlx, p1[0], i[0], color);
			}
			i[0]++;
		}
		i[1]++;	
	}
		sprite(d_list, x);
}


void	draw_walls(t_common *d_list)
{
	int	i;
	double	p1[2];
	double	p2[2];
	double	line_len;

	i = 0;

	while (i < WIDTH)
	{
		line_len = (HEIGHT * 2 / (d_list->rc->hit[i][2]));

			p1[1] = (HEIGHT + line_len) / 2;
			p2[1] = (HEIGHT - line_len) / 2;
		p1[0] = i;
		p2[0] = i;

		wall (d_list, p1, p2, i);
		i++;
	}
}
