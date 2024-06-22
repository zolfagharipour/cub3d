/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:27:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/22 13:00:26 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    first_step(t_rc *rc)
{
    if (rc->dir < 0.5)
    {
        rc->steps[0] = 1 - modf(rc->pos[0], NULL);
        rc->steps[1] = 1 - modf(rc->pos[1], NULL);
    }
    else if (rc->dir < 1)
    {
        rc->steps[0] = -modf(rc->pos[0], NULL);
        rc->steps[1] = 1 - modf(rc->pos[1], NULL);
    }
    else if (rc->dir < 1.5)
    {
        rc->steps[0] = - modf(rc->pos[0], NULL);
        rc->steps[1] = - modf(rc->pos[1], NULL);
    }
    else if (rc->dir < 2)
    {
        rc->steps[0] = 1 - modf(rc->pos[0], NULL);
        rc->steps[1] = - modf(rc->pos[1], NULL);
    }
    rc->ray[0] = rc->pos[0];
    rc->ray[1] = rc->pos[1];
}

int    step_x(t_rc *rc)
{
    if (rc->dir < 0.5 && rc->dir > 1.5)
    {
        rc->steps[0] + 1;
        rc->ray[0] + 1;
    }
    else if (rc->dir > 0.5 && rc->dir < 1.5)
    {
        rc->steps[0] - 1;
        rc->ray[0] - 1;
    }
}

int    step_y(t_rc *rc)
{
    if (rc->dir < 1)
    {
        rc->steps[1] + 1;
        rc->ray[1] + 1;
    }
    else if (rc->dir > 1)
        return (-1);
    {
        rc->steps[1] - 1;
        rc->ray[1] - 1;
    }
}

double  lenght_x(t_rc *rc)
{
    return (rc->steps[0] / cos(rc->dir * M_PI));
}


double  lenght_y(t_rc *rc)
{
    return (rc->steps[1] / tan(rc->dir * M_PI));
}

void     shoot_ray(t_common *d_list, t_rc *rc, int pixel)
{
    first_step(rc);
    while(d_list->map->raw_map[rc->ray[0]][rc->ray[1]] == 0)
    {
        if (lenght_x(rc) > lenght_y(rc))
            step_x(rc);
        else
            step_y(rc);
    }
    d_list->rc->hit[pixel][0] = max(lenght_x(rc), lenght_y(rc));
}

void    tracer(t_common *d_list)
{
    int     i;
    double  angle;

    i = 0;
    d_list->rc->dir = d_list->rc->look - 0.2618;
    angle = 30 / WIDTH * 0.0174533;
    while (i < WIDTH)
    {
        shoot_ray(d_list, d_list->rc, i);
        i++;
        d_list->rc->dir += angle;
    }
}