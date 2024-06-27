/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:25 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/27 13:17:44 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    fill_pixel(int x, int y, int ii, int jj, t_common *d_list)
{
    int pixel_x = x * d_list->map->scale + ii + d_list->map->scale/2;
    int pixel_y = y * d_list->map->scale + jj + d_list->map->scale/2;
                    
    if (d_list->map->raw_map[y][x] == 1)
        my_mlx_pixel_put(d_list->mlx, pixel_x, pixel_y, DBLUE);
    else if (d_list->map->raw_map[y][x] == RESIDUUM)
        my_mlx_pixel_put(d_list->mlx, pixel_x, pixel_y, DDBLUE);
    else
        my_mlx_pixel_put(d_list->mlx, pixel_x, pixel_y, LBLUE);
}

void    draw_minimap(t_common *d_list)
{
    t_mlx   *mlx;
    int     x;
    int     y;
	int     ii;
    int      jj;

    mlx = d_list->mlx;
    y = -1;
    while (++y < d_list->map->raw_height)
	{
		x = -1;
		while (++x < d_list->map->raw_length)
		{
	        ii = -1;
            while (++ii < d_list->map->scale)
            {
                jj = -1;
                while (++jj < d_list->map->scale)
                {
                    fill_pixel(x, y, ii, jj, d_list);
                }
	        }
		}
	}
}

void    draw_player(t_common *dlist)
{
    int     x;
    int     y;
    double start_x;
    double start_y;

    start_x = dlist->rc->pos[0] * dlist->map->scale - dlist->map->s_square / 2;
    start_y = dlist->rc->pos[1] * dlist->map->scale - dlist->map->s_square / 2;
    y = -1;
    while (++y < dlist->map->s_square)
    {
        x = -1;
        while (++x < dlist->map->s_square)
        {
            int pixel_x = start_x + x + dlist->map->scale / 2;
            int pixel_y = start_y + y + dlist->map->scale / 2;
            if (pixel_x >= 0 && pixel_x < dlist->map->raw_length * dlist->map->scale &&
                pixel_y >= 0 && pixel_y < dlist->map->raw_height * dlist->map->scale)
                my_mlx_pixel_put(dlist->mlx, pixel_x, pixel_y, ORANGE);
        }
    }
}
