/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:27:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/23 22:50:47 by mzolfagh         ###   ########.fr       */
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

void    second_step(t_rc *rc)
{
    if (rc->dir == 0.5 || rc->dir == 1.5)
        rc->steps[0] = 10000.0;
    else if (rc->dir == 0.0 || rc->dir == 1.0)
        rc->steps[1] = 10000.0;
}

void    step_x(t_rc *rc, int i)
{
    if (rc->steps[0] == 0)
        return ;
    if (rc->steps[0] > 0)
    {
        rc->steps[0] += 1;
        rc->hit[i][3] = W;
    }
    else
    {
        rc->steps[0] -= 1;
        rc->hit[i][3] = E;
    }
}

void    step_y(t_rc *rc, int i)
{
    if (rc->steps[1] == 0)
        return ;
    if (rc->steps[1] < 1)
    {
        rc->steps[1] -= 1;
        rc->hit[i][3] = S;
    }
    else
    {
        rc->steps[1] += 1;
        rc->hit[i][3] = N;
    }
    // printf("Y: %f\n", rc->steps[1]);
}

double  length_x(t_rc *rc)
{
    if (rc->dir < 0.5)
        return fabs(rc->steps[0] / cos(rc->dir * M_PI));
    else if (rc->dir < 1.0)
        return fabs(rc->steps[0] / cos((1.0 - rc->dir) * M_PI));
    else if (rc->dir < 1.5)
        return fabs(rc->steps[0] / cos((rc->dir - 1.0) * M_PI));
    else if (rc->dir < 2.0)
        return fabs(rc->steps[0] / cos((2.0 - rc->dir) * M_PI));
}


double  length_y(t_rc *rc)
{
    if (rc->dir < 0.5)
        return fabs(rc->steps[1] / tan(rc->dir * M_PI));
    else if (rc->dir < 1.0)
        return fabs(rc->steps[1] / tan((1.0 - rc->dir) * M_PI));
    else if (rc->dir < 1.5)
        return fabs(rc->steps[1] / tan((rc->dir - 1.0) * M_PI));
    else if (rc->dir < 2.0)
        return fabs(rc->steps[1] / tan((2.0 - rc->dir) * M_PI));
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

double  hit_xy(double b, double c)
{
    double  a;

    a = pow(c, 2) - pow(b, 2);
    // printf("A %f\n", sqrt(a));
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

        
    if (rc->steps[1] > 1000.0 || (rc->steps[0] < 1000.0 && length_x(rc) < length_y(rc)))
    {
        if (rc->dir < 0.5 || rc->dir > 1.5)
            d_list->rc->hit[pixel][0] = rc->ray[0];
        else
            d_list->rc->hit[pixel][0] = rc->ray[0] + 1;
        if (rc->dir < 1.0)
            d_list->rc->hit[pixel][1] = rc->pos[1] - hit_xy(rc->steps[0], length_x(rc));
        else
            d_list->rc->hit[pixel][1] = rc->pos[1] + hit_xy(rc->steps[0], length_x(rc));
    }
    else
    {
        if (rc->dir < 1.0)
            d_list->rc->hit[pixel][1] = rc->ray[1] + 1;
        else
            d_list->rc->hit[pixel][1] = rc->ray[1];
        if (rc->dir < 0.5 || rc->dir > 1.5)
            d_list->rc->hit[pixel][0] = rc->pos[0] + hit_xy(rc->steps[1], length_y(rc));
        else
            d_list->rc->hit[pixel][0] = rc->pos[0] - hit_xy(rc->steps[1], length_y(rc));
    }
    
    // printf("x %f\ty %f\n", length_x(rc), length_y(rc));
    // printf("X %f\t%f\t%f\n", rc->pos[0], rc->steps[0], d_list->rc->hit[pixel][0]);
    // printf("Y %f\t%f\t%f\n\n", rc->pos[1], rc->steps[1], d_list->rc->hit[pixel][1]);
    
}

void    tracer(t_common *d_list)
{
    int     i;
    double  angle;
    double  pixle_width;
    double  screen_width;
    double  screen_dis;

    double  sum = 0;
    

    i = 0;
    screen_width = 50;
    screen_dis = 100;
    pixle_width = screen_dis / (WIDTH);
    angle = atan(screen_width / screen_dis) / M_PI;
    d_list->rc->dir = d_list->rc->look + angle;
// angle = 0.5 / WIDTH;
// d_list->rc->dir = d_list->rc->look + 0.5;
    if (d_list->rc->dir > 2)
        d_list->rc->dir -= 2;
    while (i < WIDTH)
    {
        screen_width -= pixle_width;
        angle = (d_list->rc->dir - d_list->rc->look - atan(screen_width / screen_dis) / M_PI);
        if (angle >= 2)
            angle -= 2;

        
        sum += fabs(angle);
    printf("dir: %f\tang: %f\n", d_list->rc->dir, angle);
        d_list->rc->dir -= angle;
        shoot_ray(d_list, d_list->rc, i);
        i++;
        if (d_list->rc->dir < 0)
            d_list->rc->dir += 2;
    }
    printf("sum %f\n", sum);
}
