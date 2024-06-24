#include "cubid.h"

void	events(t_common *d_list)
{
	t_mlx	*mlx;
	mlx = d_list->mlx;
	mlx_hook(mlx->win, 2, 1L << 0, (key_press), d_list);
	//mlx_hook(mlx->win, 3, 1L << 1, (key_release), d_list);
	mlx_hook(mlx->win, 17, 1L << 8, (cleanup), d_list);
	mlx_loop(mlx->ptr);
}

// int	key_release(int keycode, t_common *d_list)
// {
// 	if (keycode == XK_space)
// 		d_list->mlx->player_running = FALSE;
// 	return (0);
// }

int	key_press(int keycode, t_common *d_list)
{
	if (keycode == XK_Escape)
		cleanup(d_list);
	// else if (keycode == XK_space)
	// 	d_list->mlx->player_running = TRUE;
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
