/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:49 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/26 20:28:51 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	check_entire_square(t_common *d_list, int new_x, int new_y)
{
	double upper_left_x = new_x - d_list->map->s_square / 2;
    double upper_left_y = new_y - d_list->map->s_square / 2;

	for (int y = - 2; y < d_list->map->s_square + 2; y++)
    {
        for (int x = -1; x < d_list->map->s_square + 2; x++)
        {
			if  (d_list->map->minimap[(int)upper_left_x + x][(int)upper_left_y + y] == 1)
            	return TRUE;
        }
    }
	return FALSE;
}

void	move_window(int keycode, t_common *d_list)
{
	t_mlx	*mlx;
	double	px_move;
	float	move;
	int		adjusted;

	mlx = d_list->mlx;
	move = 0.1;
	// if (d_list->mlx->player_running == TRUE)
	// 	move = 0.3;
	if (keycode == XK_w)
		d_list->rc->pos[1] -= move;
	else if (keycode == XK_s)
		d_list->rc->pos[1] += move;
	else if (keycode == XK_a)
		d_list->rc->pos[0] -= move;
	else if (keycode == XK_d)
		d_list->rc->pos[0] += move;
	put_image(d_list, mlx);
}

void	rotate_player(int keycode, t_common *d_list)
{
	if (keycode == XK_Left)
		d_list->rc->look -= 0.05;
	else if (keycode == XK_Right)
		d_list->rc->look += 0.05;
	put_image(d_list, d_list->mlx);
}
