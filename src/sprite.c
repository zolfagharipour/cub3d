/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:39:49 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/05 15:40:12 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"


void    find_sprite(t_common *d_list)
{
    double  delta[2];
    double  angle;

    delta[0] = d_list->rc->sprite[0] - d_list->rc->pos[0];
    delta[1] = -d_list->rc->sprite[1] + d_list->rc->pos[1];
    angle = atan2(delta[1], delta[0]) / M_PI;
    
    d_list->rc->sprite[3] =  angle - d_list->rc->look;
    while (d_list->rc->sprite[3] < -1)
        d_list->rc->sprite[3] += 2;
    while (d_list->rc->sprite[3] > 1)
        d_list->rc->sprite[3] -= 2;

    d_list->rc->sprite[2] = magnitudes(delta);
}

void    draw_sprite(t_common *d_list, double center[2], double scale)
{
    double  i[2];
    double  dim[2];
    int     pos[2];
    double  steps;
    int     color;

    dim[0] = d_list->mlx[SP + d_list->rc->frame].tex_dim[0] * scale;
    dim[1] = d_list->mlx[SP + d_list->rc->frame].tex_dim[1] * scale;
    steps = 1.0 / scale;
    pos[0] = (int)center[0] - ((d_list->mlx[SP + d_list->rc->frame].tex_dim[0] * scale) / 2);
    i[0] = 0;
    while (i[0] < d_list->mlx[SP + d_list->rc->frame].tex_dim[0])
    {
        i[1] = 0;
        pos[1] = (int)center[1] - ((d_list->mlx[SP + d_list->rc->frame].tex_dim[0] * scale) / 2);
        while (i[1] < d_list->mlx[SP + d_list->rc->frame].tex_dim[1] && pos[1] < HEIGHT && pos[0] < WIDTH)
        {
            if (pos[0] > 0  && pos[1] > 0 )
            {
                color = my_mlx_pixel_get(&d_list->mlx[SP + d_list->rc->frame], (int)i[0], (int)i[1]);
                if (color != 0XFF000000)
                    my_mlx_pixel_put(&d_list->mlx[0], pos[0], pos[1], color);
            }
            i[1] += steps;
            pos[1]++;
        }
        i[0] += steps;
        pos[0]++;
    }
}

void	sprite(t_common *d_list)
{
    double  scale;
    double  pos[2];
    if (d_list->rc->frame !=12 && (fabs(d_list->rc->sprite[3]) > 0.25 || d_list->rc->sprite[2] > 5))
        return ;
    scale = 1.5 / d_list->rc->sprite[2];
    pos[1] = (HEIGHT + (HEIGHT / d_list->rc->sprite[2])) / 2;
    if (d_list->rc->frame == 12)
        pos[1] *= 1.01;
    else
        pos[1] *= 0.9;
    pos[0] = tan(d_list->rc->sprite[3] * M_PI) * WIDTH * 2;
    pos[0] = (WIDTH / 2) - pos[0];

    draw_sprite(d_list, pos, scale);
}