/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:19 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/27 12:50:41 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	draw_image(t_common *d_list)
{
	draw_minimap(d_list);
	draw_player(d_list);
}

void	put_image(t_common *d_list, t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->ptr, mlx->img);
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (mlx->img == NULL)
		cleanup(d_list);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_length, &mlx->endian);
	if (mlx->addr == NULL)
		cleanup(d_list);
	caster(d_list);
	draw_walls(d_list);
    put_red_square(d_list);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

int	exceeds_boundaries_of_image(int keycode, t_common *d_list, int px_move)
{
	t_mlx	*mlx;
	int		scale_factor;

	mlx = d_list->mlx;
	scale_factor = d_list->map->scale;
	if (keycode == XK_Up && mlx->shift_y - px_move < -scale_factor)
		return (TRUE);
	else if (keycode == XK_Down && mlx->shift_y + px_move > d_list->map->raw_height * scale_factor - scale_factor * 2)
		return (TRUE);
	else if (keycode == XK_Left && mlx->shift_x - px_move < -scale_factor)
		return (TRUE);
	else if (keycode == XK_Right && mlx->shift_x + px_move > d_list->map->raw_length * scale_factor - scale_factor * 2)
		return (TRUE);
	return (FALSE);
}

// int	player_run_into_walls(int keycode, t_common *d_list, int px_move)
// {
// 	t_map	*map;
// 	int		new_x;
// 	int		new_y;

// 	map = d_list->map;

// 	// Calculate the new position based on the keycode
// 	new_x = map->player_x * map->scale;
// 	new_y = map->player_y * map->scale;
// 	if (keycode == XK_Up)
// 		new_y -= 1;
// 	else if (keycode == XK_Down)
// 		new_y += (1 + map->scale);
// 	else if (keycode == XK_Left)
// 		new_x -= 1;
// 	else if (keycode == XK_Right)
// 		new_x += (1 + map->scale);

// 	// Check if the new position is a wall
// 	if (map->minimap[new_y][new_x] == 1)
// 		return (TRUE);

// 	return (FALSE);
// }

double	calc_dir(double dir)
{
	double	rdir;
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



int	move_check_x(t_common *d_list, double move_dir)
{
	double	trash;
	int		pos[2];

	pos[0] = d_list->rc->pos[0];
	pos[1] = d_list->rc->pos[1];

	if (cos(move_dir * M_PI) > 0 && d_list->map->raw_map[pos[0] + 1][pos[1]] == 1
		&& modf(d_list->rc->pos[0], &trash) > 0.8)
	{
		printf("p %f\n", cos(move_dir));
		printf("Dir %f\n", move_dir);
		printf("X %f\t%f\n", d_list->rc->pos[0], modf(d_list->rc->pos[0], &trash));
		return (FALSE);
	}
	if (cos(move_dir * M_PI) < 0 && d_list->map->raw_map[pos[0] - 1][pos[1]] == 1
		&& modf(d_list->rc->pos[0], &trash) < 0.2)
	{
		printf("n %f\n", cos(move_dir));
		printf("Dir %f\n", move_dir);
		printf("X %f\t%f\n", d_list->rc->pos[0], modf(d_list->rc->pos[0], &trash));
		return (FALSE);
	}
	return (TRUE);
}
int	move_check_y(t_common *d_list, double move_dir)
{
	double	trash;
	int		pos[2];

	pos[0] = d_list->rc->pos[0];
	pos[1] = d_list->rc->pos[1];

	if (sin(move_dir * M_PI) < 0 && d_list->map->raw_map[pos[0]][pos[1] + 1] == 1
		&& modf(d_list->rc->pos[1], &trash) >= 0.8)
		return (FALSE);
	if (sin(move_dir * M_PI) > 0 && d_list->map->raw_map[pos[0]][pos[1] - 1] == 1
		&& modf(d_list->rc->pos[1], &trash) <= 0.2)
		return (FALSE);
	return (TRUE);
}
void	move_player(t_common *d_list, double move_dir)
{
	if (move_check_x(d_list, move_dir))
		d_list->rc->pos[0] += cos (move_dir * M_PI) * (MOVING_DIS);
	if (move_check_y(d_list, move_dir))
		d_list->rc->pos[1] -= sin (move_dir* M_PI) * (MOVING_DIS);

}

void	move_window(int keycode, t_common *d_list)
{
	t_mlx	*mlx;
	double	px_move;

	mlx = d_list->mlx;
	px_move = 10;
	if (exceeds_boundaries_of_image(keycode, d_list, px_move) == TRUE)
		return ;

	if (keycode == XK_w)
		move_player(d_list, d_list->rc->look);
	else if (keycode == XK_s)
		move_player(d_list, d_list->rc->look + 1.0);
	else if (keycode == XK_a)
		move_player(d_list, d_list->rc->look + 0.5);
	else if (keycode == XK_d)
		move_player(d_list, d_list->rc->look - 0.5);
	put_image(d_list, mlx);
}

void	rotate_player(int keycode, t_common *d_list)
{
	if (keycode == XK_Left)
		d_list->rc->look += 0.05;
	else if (keycode == XK_Right)
		d_list->rc->look -= 0.05;

	if (d_list->rc->look >= 2.0)
		d_list->rc->look -= 2.0;
	else if (d_list->rc->look < 0.0)
		d_list->rc->look += 2.0;
	put_image(d_list, d_list->mlx);
}
