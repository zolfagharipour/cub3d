/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:27:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/03 12:45:10 by mzolfagh         ###   ########.fr       */
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
        rc->tmp[0] = W;
        rc->tmp[1] = S;
    }
    else if (rc->dir < 1)
    {
        rc->steps[0] = -modf(rc->pos[0], &trash);
        rc->steps[1] = -modf(rc->pos[1], &trash);
        rc->tmp[0] = E;
        rc->tmp[1] = S;
    }
    else if (rc->dir < 1.5)
    {
        rc->steps[0] = -modf(rc->pos[0], &trash);
        rc->steps[1] = 1 - modf(rc->pos[1], &trash);
        rc->tmp[0] = E;
        rc->tmp[1] = N;
    }
    else if (rc->dir < 2)
    {
        rc->steps[0] = 1 - modf(rc->pos[0], &trash);
        rc->steps[1] = 1 - modf(rc->pos[1], &trash);
        rc->tmp[0] = W;
        rc->tmp[1] = N;
    }
    rc->ray[0] = rc->pos[0];
    rc->ray[1] = rc->pos[1];
}

void    second_step(t_rc *rc)
{
    if (rc->dir == 0.5 || rc->dir == 1.5)
        rc->steps[0] = 10000.0;
    else if (rc->dir == 0.0 || rc->dir == 1.0)
        rc->steps[1] = 10000.0;
}

void    step_x(t_rc *rc, int i)
{
    if (rc->steps[0] > 0)
    {
        rc->steps[0] += 1;
        rc->tmp[0] = W;
    }
    else
    {
        rc->steps[0] -= 1;
        rc->tmp[0] = E;
    }
}

void    step_y(t_rc *rc, int i)
{
    if (rc->steps[1] < 0)
    {
        rc->steps[1] -= 1;
        rc->tmp[1] = S;
    }
    else
    {
        rc->steps[1] += 1;
        rc->tmp[1] = N;
    }
}

double  length_x(t_rc *rc)
{
    double  dir;

    if (rc->dir < 0.5)
        dir = rc->dir * M_PI;
    else if (rc->dir < 1.0)
        dir = (1.0 - rc->dir) * M_PI;    
    else if (rc->dir < 1.5)
        dir = (rc->dir - 1.0) * M_PI;
    else if (rc->dir < 2.0)
        dir = (2.0 - rc->dir) * M_PI;
    return fabs(rc->steps[0] / cos(dir));
}


double  length_y(t_rc *rc)
{
    double  dir;

    if (rc->dir < 0.5)
        dir = rc->dir * M_PI;
    else if (rc->dir < 1.0)
        dir = (1.0 - rc->dir) * M_PI;    
    else if (rc->dir < 1.5)
        dir = (rc->dir - 1.0) * M_PI;
    else if (rc->dir < 2.0)
        dir = (2.0 - rc->dir) * M_PI;
    return fabs(rc->steps[1] / sin(dir));
}

void    move_ray(t_rc *rc)
{
    if (rc->steps[1] > 1000.0 || (rc->steps[0] < 1000.0 && length_x(rc) < length_y(rc)))
    {
        if (rc->dir < 0.5 || rc->dir > 1.5)
            rc->ray[0] += 1;
        else
            rc->ray[0] -= 1;
    }
    else
    {
        if (rc->dir < 1)
            rc->ray[1] -= 1;
        else
            rc->ray[1] += 1;
    }
}

double  pyth(double b, double c)
{
    double  a;

    a = pow(c, 2) - pow(b, 2);
    return (sqrt(a));
}

void     shoot_ray(t_common *d_list, t_rc *rc, int pixel)
{
    first_step(rc);
    second_step(rc);
    move_ray(rc);
    int i = 0;
    while(d_list->map->raw_map[rc->ray[0]][rc->ray[1]] != 1 && d_list->map->raw_map[rc->ray[0]][rc->ray[1]] != 4)
    {
        
        if (rc->steps[1] > 1000.0 || (rc->steps[0] < 1000.0 && length_x(rc) < length_y(rc)))
            step_x(rc, pixel);
        else
            step_y(rc, pixel);
        move_ray(rc);
        i ++;
    }

    double angle = d_list->rc->dir - d_list->rc->look;
    if (d_list->rc->dir < 0.5 && d_list->rc->look > 1.5)
        angle += 2;
    else if (d_list->rc->look < 0.5 && d_list->rc->dir > 1.5)
        angle -= 2;
    if (rc->steps[1] > 1000.0 || (rc->steps[0] < 1000.0 && length_x(rc) < length_y(rc)))
    {
        rc->hit[pixel][3] = rc->tmp[0];
        if (rc->dir < 0.5 || rc->dir > 1.5)
            d_list->rc->hit[pixel][0] = rc->ray[0];
        else
            d_list->rc->hit[pixel][0] = rc->ray[0] + 1;
        if (rc->dir < 1.0)
            d_list->rc->hit[pixel][1] = rc->pos[1] - pyth(rc->steps[0], length_x(rc));
        else
            d_list->rc->hit[pixel][1] = rc->pos[1] + pyth(rc->steps[0], length_x(rc));
        d_list->rc->hit[pixel][5] = length_x(rc);
        d_list->rc->hit[pixel][2] = d_list->rc->hit[pixel][5] * (2 * cos(angle));
    }
    else
    {
        rc->hit[pixel][3] = rc->tmp[1];
        if (rc->dir < 1.0)
            d_list->rc->hit[pixel][1] = rc->ray[1] + 1;
        else
            d_list->rc->hit[pixel][1] = rc->ray[1];
        if (rc->dir < 0.5 || rc->dir > 1.5)
            d_list->rc->hit[pixel][0] = rc->pos[0] + pyth(rc->steps[1], length_y(rc));
        else
            d_list->rc->hit[pixel][0] = rc->pos[0] - pyth(rc->steps[1], length_y(rc));
        d_list->rc->hit[pixel][5] = length_y(rc);
        d_list->rc->hit[pixel][2] = d_list->rc->hit[pixel][5] * (2 * cos(angle));
    }
    if (rc->hit[pixel][3] == S)
        rc->hit[pixel][4] = modf(rc->hit[pixel][0], &angle);
    else if (rc->hit[pixel][3] == N)
        rc->hit[pixel][4] = 1 - modf(rc->hit[pixel][0], &angle);
    else if (rc->hit[pixel][3] == E)
        rc->hit[pixel][4] = 1 - modf(rc->hit[pixel][1], &angle);
    else if (rc->hit[pixel][3] == W)
        rc->hit[pixel][4] = modf(rc->hit[pixel][1], &angle);
    

    if (d_list->map->raw_map[rc->ray[0]][rc->ray[1]] == 4)
        rc->hit[pixel][3] = D;
    // printf("Dir %f\tlenX %f\tlenY %f\n", rc->dir, length_x(rc), length_y(rc));
    // printf("X %f\t%f\t%f\n", rc->pos[0], rc->steps[0], d_list->rc->hit[pixel][0]);
    // printf("Y %f\t%f\t%f\n\n", rc->pos[1], rc->steps[1], d_list->rc->hit[pixel][1]);
    
}

void    caster(t_common *d_list)
{
    int     i;
    double  angle;

    i = 0;
    d_list->rc->dir = d_list->rc->look + 0.0833335;
    angle = 0.166667 / WIDTH;
    
    if (d_list->rc->dir >= 2.0)
        d_list->rc->dir -= 2.0;
    
    while (i < WIDTH)
    {
        if (angle >= 2)
            angle -= 2;
        d_list->rc->dir -= angle;
        if (d_list->rc->dir < 0)
            d_list->rc->dir += 2;
        else if (d_list->rc->dir >= 2.0)
            d_list->rc->dir -= 2.0;
        shoot_ray(d_list, d_list->rc, i);
        i++;
    }

}
