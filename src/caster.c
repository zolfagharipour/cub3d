/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:27:59 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 16:50:08 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	vertical(t_common *d_list, t_rc *rc, int pixel, double angle)
{
	rc->hit[pixel][3] = rc->tmp[0];
	if (rc->dir < 0.5 || rc->dir > 1.5)
		d_list->rc->hit[pixel][0] = rc->ray[0];
	else
		d_list->rc->hit[pixel][0] = rc->ray[0] + 1;
	if (rc->dir < 1.0)
		d_list->rc->hit[pixel][1]
			= rc->pos[1] - pyth(rc->steps[0], length_x(rc));
	else
		d_list->rc->hit[pixel][1]
			= rc->pos[1] + pyth(rc->steps[0], length_x(rc));
	d_list->rc->hit[pixel][5] = length_x(rc);
	d_list->rc->hit[pixel][2] = d_list->rc->hit[pixel][5] * (2 * cos(angle));
}

void	horizontal(t_rc *rc, int pixel, double angle)
{
	rc->hit[pixel][3] = rc->tmp[1];
	if (rc->dir < 1.0)
		rc->hit[pixel][1] = rc->ray[1] + 1;
	else
		rc->hit[pixel][1] = rc->ray[1];
	if (rc->dir < 0.5 || rc->dir > 1.5)
		rc->hit[pixel][0] = rc->pos[0] + pyth(rc->steps[1], length_y(rc));
	else
		rc->hit[pixel][0] = rc->pos[0] - pyth(rc->steps[1], length_y(rc));
	rc->hit[pixel][5] = length_y(rc);
	rc->hit[pixel][2] = rc->hit[pixel][5] * (2 * cos(angle));
}

void	where_hit(t_common *d_list, t_rc *rc, int pixel)
{
	double	angle;

	angle = d_list->rc->dir - d_list->rc->look;
	if (d_list->rc->dir < 0.5 && d_list->rc->look > 1.5)
		angle += 2;
	else if (d_list->rc->look < 0.5 && d_list->rc->dir > 1.5)
		angle -= 2;
	if (rc->steps[1] > 1000.0 || (rc->steps[0] < 1000.0
			&& length_x(rc) < length_y(rc)))
		vertical(d_list, rc, pixel, angle);
	else
		horizontal(rc, pixel, angle);
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
}

void	caster(t_common *d_list)
{
	int		i;
	double	angle;

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
		shoot_ray(d_list, d_list->rc);
		where_hit(d_list, d_list->rc, i);
		i++;
	}
}
