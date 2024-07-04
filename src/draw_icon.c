/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_icon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:12:39 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/04 14:04:23 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	smoke_icon(t_common *d_list, int start[2])
{
	int	i[2];

	i[0] = 0;
	while(i[0] < 30)
	{
		i[1] = 0;
		while(i[1] < 30)
		{
			my_mlx_pixel_put(d_list->mlx, start[0] + i[0], start[1] + i[1], 0XFFAACC);
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
	p[1] = 30;
	i = 0;
	while (i < 4 - d_list->rc->ninja_found)
	{
		smoke_icon(d_list, p);
		// p[0] -= d_list->mlx[5].tex_dim[1] + 20;
		
		p[0] -= 30 + 20;
		i++;
	}
}
