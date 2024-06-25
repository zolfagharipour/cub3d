#include "cubid.h"

int	check_entire_square(t_common *d_list, int new_x, int new_y)
{
	double upper_left_x = new_x - SQUARE / 2;
    double upper_left_y = new_y - SQUARE / 2;

	for (int y = - 2; y < SQUARE + 2; y++)
    {
        for (int x = -1; x < SQUARE + 2; x++)
        {
			if  (d_list->map->minimap[(int)upper_left_x + x][(int)upper_left_y + y] == 1)
            	return TRUE;
        }
    }
	return FALSE;
}

int	player_run_into_walls(int keycode, t_common *d_list, float move)
{
	t_rc	*map;
	int		scaled_x;
	int		scaled_y;
	float	scaled_move;

	map = d_list->rc;
	scaled_move = move * d_list->map->scale;
	scaled_x = map->pos[0] * d_list->map->scale;
	scaled_y = map->pos[1] * d_list->map->scale;
	if (keycode == XK_w)
		return (check_entire_square(d_list, scaled_x, scaled_y - 3));
	else if (keycode == XK_s)
		return (check_entire_square(d_list, scaled_x, scaled_y + 3));
	else if (keycode == XK_a)
		return (check_entire_square(d_list, scaled_x - 3, scaled_y));
	else if (keycode == XK_d)
		return (check_entire_square(d_list, scaled_x + 3, scaled_y));
	return (FALSE);
}


void	move_window(int keycode, t_common *d_list)
{
	t_mlx	*mlx;
	double	px_move;
	float	move;
	int		adjusted;

	mlx = d_list->mlx;
	move = 0.1;
	if (player_run_into_walls(keycode, d_list, move) == TRUE)
		return ;
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

	if (d_list->rc->look >= 2.0)
		d_list->rc->look -= 2.0;
	else if (d_list->rc->look < 0.0)
		d_list->rc->look += 2.0;
		// printf ("look %f\n", d_list->rc->look);
	put_image(d_list, d_list->mlx);
}