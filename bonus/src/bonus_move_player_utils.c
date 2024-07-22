/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:54:00 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:54:01 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

double	calc_dir(double dir)
{
	double	rdir;

	rdir = 0;
	if (dir >= 2)
		rdir -= 2;
	else if (dir < 0)
		rdir += 2;
	if (dir < 0.5)
		rdir = dir;
	else if (dir < 1.0)
		rdir = 1.0 - dir;
	else if (dir < 1.5)
		rdir = dir - 1;
	else if (dir < 2.0)
		rdir = 2 - dir;
	return (rdir);
}
