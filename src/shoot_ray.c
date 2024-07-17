/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:18:43 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 16:34:03 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"


static void	first_step(t_rc *rc)
{
	double	trash;

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

static void	second_step(t_rc *rc)
{
	if (rc->dir == 0.5 || rc->dir == 1.5)
		rc->steps[0] = 10000.0;
	else if (rc->dir == 0.0 || rc->dir == 1.0)
		rc->steps[1] = 10000.0;
}
void	move_ray(t_rc *rc)
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

void	shoot_ray(t_common *d_list, t_rc *rc, int pixel)
{
	int i;

	first_step(rc);
	second_step(rc);
	move_ray(rc);
	i = 0;
	while(d_list->map->raw_map[rc->ray[0]][rc->ray[1]] != 1 && d_list->map->raw_map[rc->ray[0]][rc->ray[1]] != 4)
	{
		
		if (rc->steps[1] > 1000.0 || (rc->steps[0] < 1000.0 && length_x(rc) < length_y(rc)))
			step_x(rc, pixel);
		else
			step_y(rc, pixel);
		move_ray(rc);
		i++;
	}
}

