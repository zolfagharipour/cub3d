/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:02 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:31:31 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	events(t_common *d_list)
{
	t_mlx	*mlx;

	mlx = &d_list->mlx[0];
	// mlx_mouse_hide(mlx->ptr, mlx->win);
	mlx_hook(mlx->win, 2, 1L << 0, (key_press), d_list);
	mlx_hook(mlx->win, 6, 1L << 6, mouse_track, d_list);
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
	else if (keycode == XK_e)
	{
		ninja(d_list);
		return (0);
	}
	else if (keycode == XK_space)
	{
		door(d_list);
		return (0);
	}
	return (0);
}
