/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:27:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/24 14:33:03 by mzolfagh         ###   ########.fr       */
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
    // if (rc->steps[0] == 0)
    //     return ;
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
    // if (rc->steps[1] == 0)
    //     return ;
    if (rc->steps[1] < 0)
    {
        rc->steps[1] -= 1;
        rc->hit[i][3] = S;
    }
    else
    {
        rc->steps[1] += 1;
        rc->hit[i][3] = N;
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
    double  sing;
    double  dir;

    if (rc->dir < 0.5)
        // dir = rc->dir * M_PI;
        return fabs(rc->steps[1] / sin(rc->dir * M_PI));
    else if (rc->dir < 1.0)
        // dir = (1.0 - rc->dir) * M_PI;
        return fabs(rc->steps[1] / sin((1.0 - rc->dir) * M_PI));
    else if (rc->dir < 1.5)
        // dir = (rc->dir - 1.0) * M_PI;
        return fabs(rc->steps[1] / sin((rc->dir - 1.0) * M_PI));
    else if (rc->dir < 2.0)
    // dir = (2.0 - rc->dir) * M_PI;
        return fabs(rc->steps[1] / sin((2.0 - rc->dir) * M_PI));

    // return (rc->steps[1] * (1/dir - dir/3 - pow(dir, 3)/45));
    
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
    // printf("B %f\tC %f\tA %f\n", b, c, sqrt(a));
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
    
    printf("Dir %f\tlenX %f\tlenY %f\n", rc->dir, length_x(rc), length_y(rc));
    printf("X %f\t%f\t%f\n", rc->pos[0], rc->steps[0], d_list->rc->hit[pixel][0]);
    printf("Y %f\t%f\t%f\n\n", rc->pos[1], rc->steps[1], d_list->rc->hit[pixel][1]);
    
}

void    caster(t_common *d_list)
{
    int     i;
    double  angle;
    double  pixle_width;
    double  screen_width;
    double  screen_dis;

    i = 0;
    screen_width = 50;
    screen_dis = 100;
    pixle_width = screen_dis / (WIDTH);
    angle = asin(screen_width / screen_dis) / M_PI;
    d_list->rc->dir = d_list->rc->look + angle;
    
    // d_list->rc->dir = d_list->rc->look + 0.5;
    // angle = 2.0 / WIDTH;

    if (d_list->rc->dir > 2)
        d_list->rc->dir -= 2;
    while (i < WIDTH)
    {
        screen_width -= pixle_width;
        angle = (d_list->rc->dir - d_list->rc->look - asin(screen_width / screen_dis) / M_PI);
        if (angle >= 2)
            angle -= 2;
        d_list->rc->dir -= angle;
        if (d_list->rc->dir < 0)
            d_list->rc->dir += 2;
        
    // printf("dir: %f\sing: %f\n", d_list->rc->dir, angle);
        shoot_ray(d_list, d_list->rc, i);
        i++;
    }
}
