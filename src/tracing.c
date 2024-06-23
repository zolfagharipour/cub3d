/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:27:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/23 14:50:28 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    first_step(t_rc *rc)
{
    double  trash;

    trash = 0;
    if (rc->dir < 0.5)
    {
        rc->steps[0] = 1 - modf(rc->pos[0], &trash);
        rc->steps[1] = -modf(rc->pos[1], &trash);
    }
    else if (rc->dir < 1)
    {
        rc->steps[0] = -modf(rc->pos[0], &trash);
        rc->steps[1] = -modf(rc->pos[1], &trash);
    }
    else if (rc->dir < 1.5)
    {
        rc->steps[0] = -modf(rc->pos[0], &trash);
        rc->steps[1] = 1 - modf(rc->pos[1], &trash);
    }
    else if (rc->dir < 2)
    {
        rc->steps[0] = 1 - modf(rc->pos[0], &trash);
        rc->steps[1] = 1 - modf(rc->pos[1], &trash);
    }
    //  CHECK THIS!!
    rc->ray[0] = rc->pos[0];
    rc->ray[1] = rc->pos[1];
}

void    step_x(t_rc *rc, int i)
{
    if (rc->dir < 0.5 && rc->dir > 1.5)
    {
        rc->steps[0] += 1;
        rc->hit[i][3] = W;
    }
    else if (rc->dir > 0.5 && rc->dir < 1.5)
    {
        rc->steps[0] -= 1;
        rc->hit[i][3] = E;
    }
}

void    step_y(t_rc *rc, int i)
{
    if (rc->dir < 1)
    {
        rc->steps[1] + 1;
        rc->hit[i][3] = S;
    }
    else if (rc->dir > 1)
    {
        rc->steps[1] - 1;
        rc->hit[i][3] = N;
    }
}

double  lenght_x(t_rc *rc)
{
    if (rc->dir < 0.5)
        return abs(rc->steps[0] / cos(rc->dir * M_PI));
    else if (rc->dir < 1.0)
        return abs(rc->steps[0] / cos((1 - rc->dir) * M_PI));
    else if (rc->dir < 1.5)
        return abs(rc->steps[0] / cos((rc->dir - 1) * M_PI));
    else if (rc->dir < 2.0)
        return abs(rc->steps[0] / cos((2 - rc->dir) * M_PI));
}


double  lenght_y(t_rc *rc)
{
    if (rc->dir < 0.5)
        return abs(rc->steps[1] / tan(rc->dir * M_PI));
    else if (rc->dir < 1.0)
        return abs(rc->steps[1] / tan((1 - rc->dir) * M_PI));
    else if (rc->dir < 1.5)
        return abs(rc->steps[1] / tan((rc->dir - 1) * M_PI));
    else if (rc->dir < 2.0)
        return abs(rc->steps[1] / tan((2 - rc->dir) * M_PI));
}

void    move_ray(t_rc *rc)
{
    if (lenght_x(rc) < lenght_y(rc))
    {
        if (rc->dir < 0.5 || rc->dir > 1.5)
            rc->ray[0] += 1;
        else
           rc->ray[0] -= 1;
    }
    else
    {
        if (rc->dir < 1)
            rc->ray[1] - 1;
        else
            rc->ray[1] + 1;
    }
}

double  hit_x(double x, double angle)
{
    if (angle < 0.5)
        return (x * tan(angle * M_PI));
    else if (angle < 1.0)
        return abs(x * tan((1 - angle) * M_PI));
    else if (angle < 1.5)
        return abs(x * tan((angle - 1) * M_PI));
    else if (angle < 2.0)
        return abs(x * tan((2 - angle) * M_PI));
}

double  hit_y(double y, double angle)
{
    if (angle < 0.5)
        return (y / tan(angle * M_PI));
    else if (angle < 1.0)
        return abs(y / tan((1 - angle) * M_PI));
    else if (angle < 1.5)
        return abs(y / tan((angle - 1) * M_PI));
    else if (angle < 2.0)
        return abs(y / tan((2 - angle) * M_PI));
}


void     shoot_ray(t_common *d_list, t_rc *rc, int pixel)
{
    first_step(rc);
    move_ray(rc);
    while(d_list->map->raw_map[rc->ray[0]][rc->ray[1]] == 0)
    {
        if (lenght_x(rc) < lenght_y(rc))
            step_x(rc, pixel);
        else
            step_y(rc, pixel);
        move_ray;
    }
    if (lenght_x(rc) < lenght_y(rc))
    {
        d_list->rc->hit[pixel][0] = rc->pos[0] + rc->steps[0];
        d_list->rc->hit[pixel][1] = hit_x(d_list->rc->hit[pixel][0], rc->dir);
    }
    else
    {
        d_list->rc->hit[pixel][1] = rc->pos[1] + rc->steps[1];
        d_list->rc->hit[pixel][0] = hit_y(d_list->rc->hit[pixel][1], rc->dir);
    }
}

void    tracer(t_common *d_list)
{
    int     i;
    double  angle;

    i = 0;
    d_list->rc->dir = d_list->rc->look - 0.2618;
    if (d_list->rc->dir < 0)
        d_list->rc->dir += 2;
    angle = 30 / WIDTH * 0.0174533;
    while (i < WIDTH)
    {
        shoot_ray(d_list, d_list->rc, i);
        i++;
        d_list->rc->dir += angle;
        if (d_list->rc->dir > 2)
            d_list->rc->dir -= 2;
    }
}
