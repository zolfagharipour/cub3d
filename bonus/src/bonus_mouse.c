/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:22:00 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/22 17:03:42 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	mouse_track(int x, int y, t_common *d_list)
{
	int	offset;

	y = 0;
	offset = x - (WIDTH / 2);
	if (abs(offset) < 30)
		return (0);
	d_list->rc->look -= 0.08 * (offset / (double)WIDTH);
	if (d_list->rc->look > 2)
		d_list->rc->look -= 2;
	else if (d_list->rc->look < 0)
		d_list->rc->look += 2;
	mlx_mouse_move(d_list->mlx->ptr, d_list->mlx->win, WIDTH / 2, HEIGHT / 2);
	put_image(d_list, d_list->mlx);
	return (1);
}
