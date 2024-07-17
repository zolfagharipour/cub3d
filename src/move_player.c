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

int	check_entire_square(t_common *d_list, int new_x, int new_y)
{
	double	up_left_x;
	double	up_left_y;
	int		y;
	int		x;
	t_map	*map;

	//draw the square smaller
	map = d_list->map;
	up_left_x = new_x - SQUARE / 2;
	up_left_y = new_y - SQUARE / 2;
	y = -2;
	while (y < SQUARE)
	{
		x = -1;
		while (x < SQUARE + 2)
		{
			if (map->minimap[(int)up_left_x + x][(int)up_left_y + y] == 1)
				return (TRUE);
			x++;
		}
		y++;
	}
	return (FALSE);
}

int	move_check_x(t_common *d_list, double move_dir)
{
	double	trash;
	int		pos[2];
	t_map	*map;

	map = d_list->map;
	pos[0] = d_list->rc->pos[0];
	pos[1] = d_list->rc->pos[1];
	if (cos(move_dir * M_PI) > 0 && (map->raw_map[pos[0] + 1][pos[1]] == 1
		|| map->raw_map[pos[0] + 1][pos[1]] == 4)
		&& modf(d_list->rc->pos[0], &trash) > 0.6)
		return (FALSE);
	if (cos(move_dir * M_PI) < 0 && (map->raw_map[pos[0] - 1][pos[1]] == 1
		|| map->raw_map[pos[0] - 1][pos[1]] == 4)
		&& modf(d_list->rc->pos[0], &trash) < 0.4)
		return (FALSE);
	return (TRUE);
}

int	move_check_y(t_common *d_list, double move_dir)
{
	double	trash;
	int		pos[2];

	pos[0] = d_list->rc->pos[0];
	pos[1] = d_list->rc->pos[1];
	if (sin(move_dir * M_PI) < 0
		&& (d_list->map->raw_map[pos[0]][pos[1] + 1] == 1
		|| d_list->map->raw_map[pos[0]][pos[1] + 1] == 4)
		&& modf(d_list->rc->pos[1], &trash) >= 0.6)
		return (FALSE);
	if (sin(move_dir * M_PI) > 0
		&& (d_list->map->raw_map[pos[0]][pos[1] - 1] == 1
		|| d_list->map->raw_map[pos[0]][pos[1] - 1] == 4)
		&& modf(d_list->rc->pos[1], &trash) <= 0.4)
		return (FALSE);
	return (TRUE);
}

void	move_player(t_common *d_list, double move_dir)
{
	if (move_check_x(d_list, move_dir))
		d_list->rc->pos[0] += cos (move_dir * M_PI) * (MOVING_DIS);
	if (move_check_y(d_list, move_dir))
		d_list->rc->pos[1] -= sin (move_dir * M_PI) * (MOVING_DIS);
}

void	rotate_player(int keycode, t_common *d_list)
{
	if (keycode == XK_Left)
		d_list->rc->look += 0.02;
	else if (keycode == XK_Right)
		d_list->rc->look -= 0.02;
	if (d_list->rc->look >= 2.0)
		d_list->rc->look -= 2.0;
	else if (d_list->rc->look < 0.0)
		d_list->rc->look += 2.0;
	put_image(d_list, d_list->mlx);
}
