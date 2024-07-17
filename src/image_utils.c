/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:25 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:32:59 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	fill_pixel(int ii, int jj, t_common *d_list)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = d_list->mlx->x * d_list->map->scale + ii;
	pixel_y = d_list->mlx->y * d_list->map->scale + jj;
	if (d_list->map->raw_map[d_list->mlx->x][d_list->mlx->y] == 1)
		my_mlx_pixel_put(d_list->mlx, pixel_x, pixel_y, DBLUE);
	else if (d_list->map->raw_map[d_list->mlx->x][d_list->mlx->y] == RESIDUUM)
		my_mlx_pixel_put(d_list->mlx, pixel_x, pixel_y, ORANGE);
	else
		my_mlx_pixel_put(d_list->mlx, pixel_x, pixel_y, LBLUE);
}

void	draw_minimap(t_common *d_list)
{
	int		x;
	int		y;
	int		ii;
	int		jj;

	x = -1;
	while (++x < d_list->map->raw_length)
	{
		y = -1;
		while (++y < d_list->map->raw_height)
		{
			ii = -1;
			while (++ii < d_list->map->scale)
			{
				jj = -1;
				while (++jj < d_list->map->scale)
				{
					d_list->mlx->x = x;
					d_list->mlx->y = y;
					fill_pixel(ii, jj, d_list);
				}
			}
		}
	}
}

void	draw_player(t_common *dlist)
{
	int		x;
	int		y;
	double	x_n;
	double	y_n;

	x_n = dlist->rc->pos[0] * dlist->map->scale - dlist->map->s_square / 2;
	y_n = dlist->rc->pos[1] * dlist->map->scale - dlist->map->s_square / 2;
	y = -1;
	while (++y < dlist->map->s_square)
	{
		x = -1;
		while (++x < dlist->map->s_square)
		{
			if ((x_n + x) >= 0
				&& (x_n + x) < dlist->map->raw_length * dlist->map->scale
				&& (y_n + y) >= 0
				&& (y_n + y) < dlist->map->raw_height * dlist->map->scale)
				my_mlx_pixel_put(dlist->mlx, (x_n + x), (y_n + y), ORANGE);
		}
	}
}
