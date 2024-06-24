#include "cubid.h"

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
    put_red_square(d_list);
	// draw_walls(d_list);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

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


void	move_window(int keycode, t_common *d_list)
{
	t_mlx	*mlx;
	double	px_move;
	int		adjusted;

	mlx = d_list->mlx;
	px_move = 10;
	if (exceeds_boundaries_of_image(keycode, d_list, px_move) == TRUE)
		return ;
	// if (player_run_into_walls(keycode, d_list, px_move) == TRUE)
	// 	return;

	adjusted = d_list->map->scale / 10;

	if (keycode == XK_w)
	{
		mlx->shift_y -= adjusted;
		d_list->rc->pos[1] -= 0.1;
	}
	else if (keycode == XK_s)
	{
		mlx->shift_y += adjusted;
		d_list->rc->pos[1] += 0.1;
	}
	else if (keycode == XK_a)
	{
		mlx->shift_x -= adjusted;
		d_list->rc->pos[0] -= 0.1;
	}
	else if (keycode == XK_d)
	{
		mlx->shift_x += adjusted;
		d_list->rc->pos[0] += 0.1;
	}
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
