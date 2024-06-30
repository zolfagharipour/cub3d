/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:39:49 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/30 18:36:34 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    find_sprite(t_common *d_list)
{
    double  cos_theta;
    double  p1[2];
    double  p2[2];

    p1[0] = cos(d_list->rc->look * M_PI);
    p1[1] = -sin(d_list->rc->look * M_PI);
    p2[0] = d_list->rc->sprite[0] - d_list->rc->pos[0];
    p2[1] = d_list->rc->sprite[1] - d_list->rc->pos[1];

    d_list->rc->sprite[4] = magnitudes(p2);
    cos_theta = (dot_product(p1, p2) / (magnitudes(p1) * d_list->rc->sprite[4]));
    d_list->rc->sprite[3] = acos(cos_theta) / M_PI;
    if (cross_product(p1, p2) < 0)
        d_list->rc->sprite[3] *= -1;
}

void    draw_sprite(t_common *d_list, double center[2], double scale)
{
    double  i[2];
    double  dim[2];
    int     pos[2];
    double  steps;
    int     color;

    dim[0] = d_list->mlx[1].tex_dim[0] * scale;
    dim[1] = d_list->mlx[1].tex_dim[1] * scale;
    steps = 1 / scale;
    pos[0] = (int)center[0] - ((d_list->mlx[1].tex_dim[0] * scale) / 2);
    i[0] = 0;
    while (i[0] < d_list->mlx[1].tex_dim[0])
    {
        i[1] = 0;
        pos[1] = (int)center[1] - ((d_list->mlx[1].tex_dim[0] * scale) / 2);
        while (i[1] < d_list->mlx[1].tex_dim[1])
        {
                // printf("%f\t%f\n", i[0], i[1]);
                // printf("%f\t%f\n", pos[0], pos[1]);
            if (pos[0] > 0 && pos[0] < WIDTH && pos[1] > 0 && pos[1] < HEIGHT)
            {
                color = my_mlx_pixel_get(&d_list->mlx[1], (int)i[0], (int)i[1]);
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

void	sprite(t_common *d_list, int x)
{
    double  scale;
    double  pos[2];

    scale = 10 / d_list->rc->sprite[4];
    pos[1] = (HEIGHT / 2) + (HEIGHT / 20);
    pos[1] += 1.0 / d_list->rc->sprite[4];// * cos(d_list->rc->sprite[3] * M_PI);
    pos[0] = tan(d_list->rc->sprite[3] * M_PI) * WIDTH * 2;
    pos[0] = (WIDTH / 2) + pos[0];
    draw_sprite(d_list, pos, scale);
}
