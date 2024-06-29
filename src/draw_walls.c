/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:50:02 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/29 14:07:37 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    wall(t_common *d_list, double p1[2], double p2[2], int x)
{
	int		i;
	int		color;
	double	w;
	double	len;
	double	step;
	
	step = d_list->mlx[(int)d_list->rc->hit[x][3]].tex_dim[1] / (p1[1] - p2[1]);
	len = 0;
	// if (p1[1] - p2[1] > HEIGHT)
	// {
	// 	// len = 
	// 	p1[1] = HEIGHT - 2;
	// 	p2[1] = 2;
	// }
	i = p2[1];
	while (i < fabs(p1[1]))
	{

		modf(len, &w);
		color = my_mlx_pixel_get(&d_list->mlx[(int)d_list->rc->hit[x][3]], d_list->rc->hit[x][4] * d_list->mlx[(int)d_list->rc->hit[x][3]].tex_dim[0], w);
		len += step;
		if (p1[0] >= 0 && p1[0] < HEIGHT)
        	my_mlx_pixel_put(d_list->mlx, p1[0], i, color);
		i++;
	}
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
		line_len = (HEIGHT / (d_list->rc->hit[i][2]));
		// if (line_len > HEIGHT)
		// {
		// 	p1[1] = HEIGHT - 2;
		// 	p2[1] = 2;
		// }
		// else
		// {
			p1[1] = (HEIGHT + line_len) / 2;
			p2[1] = (HEIGHT - line_len) / 2;
		// }
		p1[0] = i;
		p2[0] = i;
		// printf ("DIM::   %d\n", d_list->mlx[2].tex_dim[1]);
		// printf("%f\n", d_list->rc->hit[i][3]);
		wall (d_list, p1, p2, i);
		i++;
	}
}
