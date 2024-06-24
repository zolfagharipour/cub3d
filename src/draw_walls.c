/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:50:02 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/06/24 15:58:25 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	draw_walls(t_common *d_list)
{
	int	i;
	double	p1[2];
	double	p2[2];

	i = 0;
	p2[1] = WIDTH / 2;
	while (i < WIDTH)
	{
		p1[0] = i;
		p2[0] = i;
		p1[1] = d_list->rc->hit[i][2] * 10;
		line (d_list, p1, p2, ORANGE);
		i++;
	}
}