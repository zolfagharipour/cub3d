/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:02 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/28 18:27:48 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	events(t_common *d_list)
{
	t_mlx	*mlx;
	mlx = &d_list->mlx[0];
	mlx_hook(mlx->win, 2, 1L << 0, (key_press), d_list);
	mlx_hook(mlx->win, 17, 1L << 8, (cleanup), d_list);
	mlx_loop(mlx->ptr);
}

int	key_press(int keycode, t_common *d_list)
{
	if (keycode == XK_Escape)
		cleanup(d_list);

    else if (keycode == XK_w || keycode == XK_s || keycode == XK_a
		|| keycode == XK_d)
	{
		move_window(keycode, d_list);
		return (0);
	}
	else if (keycode == XK_Left || keycode == XK_Right)
	{
		rotate_player(keycode, d_list);
		return (0);
	}
	return (0);
}
