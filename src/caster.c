/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:27:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/25 15:34:20 by mzolfagh         ###   ########.fr       */
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
        rc->tmp[0] = W;
        rc->tmp[1] = N;
    }
    else if (rc->dir < 2)
    {
        rc->steps[0] = 1 - modf(rc->pos[0], &trash);
        rc->steps[1] = 1 - modf(rc->pos[1], &trash);
        rc->tmp[0] = E;
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
    rc->hit[i][3] = rc->tmp[1];
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
    // if (rc->dir < 0 || rc->dir >= 2)
    //     printf ("bad dir: %f\n", rc->dir);
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
    while(d_list->map->raw_map[rc->ray[0]][rc->ray[1]] == 0)
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
        d_list->rc->hit[pixel][2] = length_x(rc) * fabs(cos(angle));
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
        d_list->rc->hit[pixel][2] = length_y(rc) * fabs(cos(angle));
    }
    
    // printf("Dir %f\tlenX %f\tlenY %f\n", rc->dir, length_x(rc), length_y(rc));
    // printf("X %f\t%f\t%f\n", rc->pos[0], rc->steps[0], d_list->rc->hit[pixel][0]);
    // printf("Y %f\t%f\t%f\n\n", rc->pos[1], rc->steps[1], d_list->rc->hit[pixel][1]);
    
}

void    caster(t_common *d_list)
{
    int     i;
    double  angle;
    double  pixle_width;
    double  screen_width;
    double  screen_dis;

    i = 0;
    screen_width = 5;
    // screen_dis = 10;
    screen_dis = 8.66025403784;
    pixle_width = screen_dis / (WIDTH);
    angle = asin(screen_width / screen_dis) / M_PI;
    d_list->rc->dir = d_list->rc->look + angle;
    
    // d_list->rc->dir = d_list->rc->look + 0.5;
    // angle = 2.0 / WIDTH;

    if (d_list->rc->dir >= 2.0)
        d_list->rc->dir -= 2.0;
    
    while (i < WIDTH)
    {
        screen_width -= pixle_width;
        angle = d_list->rc->dir - d_list->rc->look - (asin(screen_width / screen_dis) / M_PI);
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
