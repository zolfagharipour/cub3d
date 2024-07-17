/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:09:21 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 16:30:21 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	step_x(t_rc *rc, int i)
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

void	step_y(t_rc *rc, int i)
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

double	length_x(t_rc *rc)
{
	double	dir;

	if (rc->dir < 0.5)
		dir = rc->dir * M_PI;
	else if (rc->dir < 1.0)
		dir = (1.0 - rc->dir) * M_PI;
	else if (rc->dir < 1.5)
		dir = (rc->dir - 1.0) * M_PI;
	else if (rc->dir < 2.0)
		dir = (2.0 - rc->dir) * M_PI;
	return (fabs(rc->steps[0] / cos(dir)));
}

double	length_y(t_rc *rc)
{
	double	dir;

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

double	pyth(double b, double c)
{
	double  a;

	a = pow(c, 2) - pow(b, 2);
	return (sqrt(a));
}
