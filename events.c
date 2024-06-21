#include "cubid.h"

void	events(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L << 0, (key_press), mlx);
	mlx_hook(mlx->win, 17, 1L << 8, (cleanup), mlx);
	mlx_loop(mlx->ptr);
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape)
		cleanup(mlx);
    else if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Left
		|| keycode == XK_Right)
	{
		move_window(keycode, mlx);
		return (0);
	}
	return (0);
}