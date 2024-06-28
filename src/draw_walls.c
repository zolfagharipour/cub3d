/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:50:02 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/28 19:17:30 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

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
		if (line_len > HEIGHT)
		{
			p1[1] = HEIGHT - 2;
			p2[1] = 2;
		}
		else
		{
			p1[1] = (HEIGHT + line_len) / 2;
			p2[1] = (HEIGHT - line_len) / 2;
		}
		p1[0] = i;
		p2[0] = i;
		// printf ("DIM::   %d\n", d_list->mlx[2].tex_dim[1]);
		// printf("%f\n", d_list->rc->hit[i][3]);
		wall (d_list, p1, p2, d_list->rc->hit[i][3], i);
		i++;
	}
}
