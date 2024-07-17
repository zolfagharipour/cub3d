/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_icon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:12:39 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 18:36:14 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	smoke_icon(t_common *d_list, int start[2])
{
	int		i[2];
	int		color;
	double	scale[2];

	i[0] = 0;
	scale[0] = d_list->mlx[SMOKE].tex_d[0] / 50.0;
	scale[1] = d_list->mlx[SMOKE].tex_d[1] / 50.0;
	while (i[0] < 51)
	{
		i[1] = 0;
		while (i[1] < 52)
		{
			color = my_mlx_pixel_get(&d_list->mlx[SMOKE], i[0] * (int)scale[0], i[1] * (int)scale[1]);
			if (color != 0XFF000000)
				my_mlx_pixel_put(d_list->mlx, start[0] + i[0], start[1] + i[1], color);
			i[1]++;
		}
		i[0]++;
	}
}

void	draw_icon(t_common *d_list)
{
	int	p[2];
	int	end[2];
	int	i;

	p[0] = WIDTH - 60;
	p[1] = 10;
	i = 0;
	while (i < 4 - d_list->rc->ninja_found)
	{
		smoke_icon(d_list, p);
		p[0] -= 30 + 20;
		i++;
	}
}
