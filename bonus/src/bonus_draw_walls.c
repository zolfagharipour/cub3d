/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:50:02 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/22 14:21:15 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

static void	check_boundries(int p1)
{
	if (p1 < 0)
		p1 = 0;
	else if (p1 >= WIDTH)
		p1 = WIDTH - 1;
}

void	wall(t_common *d_list, double p1[2], double p2[2], int x)
{
	int		i;
	int		color;
	double	w;
	double	len;
	double	step;

	step = d_list->mlx[(int)d_list->rc->hit[x][3]].tex_d[1] / (p1[1] - p2[1]);
	check_boundries(p1[0]);
	len = 0;
	i = p2[1];
	while (i < fabs(p1[1]))
	{
		modf(len, &w);
		color = my_mlx_pixel_get(&d_list->mlx[(int)d_list->rc->hit[x][3]],
				d_list->rc->hit[x][4]
				* d_list->mlx[(int)d_list->rc->hit[x][3]].tex_d[0], w);
		color = wall_lighting(d_list, color, x);
		len += step;
		my_mlx_pixel_put(d_list->mlx, p1[0], i, color);
		i++;
	}
}

static void	draw_line(t_common *d_list, int i[2])
{
	double	line_len;
	double	p1[2];
	double	p2[2];

	line_len = (HEIGHT * 2 / (d_list->rc->hit[i[0]][2]));
	p1[1] = (HEIGHT + line_len) / 2;
	p2[1] = (HEIGHT - line_len) / 2;
	p1[0] = i[0];
	p2[0] = i[0];
	wall (d_list, p1, p2, i[0]);
	floor_ceiling(d_list, p1, p2);
}

void	draw_walls(t_common *d_list)
{
	int		i[2];

	i[1] = 0;
	while (i[1] < 2)
	{
		i[0] = 0;
		while (i[0] < WIDTH)
		{
			if ((i[1] == 0 && d_list->rc->sprite[2] < d_list->rc->hit[i[0]][5])
				|| (i[1] == 1
				&& d_list->rc->sprite[2] >= d_list->rc->hit[i[0]][5]))
				draw_line(d_list, i);
			i[0]++;
		}
		if (i[1] % 2 == 0)
			sprite(d_list);
		i[1]++;
	}
}
