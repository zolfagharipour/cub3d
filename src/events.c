/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:02 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/02 17:19:28 by mzolfagh         ###   ########.fr       */
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

void	ninja(t_common *d_list)
{
	d_list->rc->smoke = 1;
	put_image(d_list, d_list->mlx);
	// REMOVE THE NINJA FROM RAWMAP
	// d_list->rc->smoke = 0;
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
	return (0);
}
