/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_step_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:33:39 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/22 13:18:44 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	first_quarter(t_rc *rc)
{
	double	trash;

	trash = 0;
	rc->steps[0] = 1 - modf(rc->pos[0], &trash);
	rc->steps[1] = -modf(rc->pos[1], &trash);
	rc->tmp[0] = W;
	rc->tmp[1] = S;
}

void	second_quarter(t_rc *rc)
{
	double	trash;

	trash = 0;
	rc->steps[0] = -modf(rc->pos[0], &trash);
	rc->steps[1] = -modf(rc->pos[1], &trash);
	rc->tmp[0] = E;
	rc->tmp[1] = S;
}
