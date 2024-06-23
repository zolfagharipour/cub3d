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
	tracer(d_list);
    put_red_square(d_list);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	move_window(int keycode, t_common *d_list)
{
	t_mlx	*mlx;
	mlx = d_list->mlx;
	double	adjusted;

	adjusted = 10;

	if (keycode == XK_Up)
	{
		mlx->shift_y -= adjusted;
		d_list->rc->pos[1] += 0.1;
	}
	else if (keycode == XK_Down)
	{
		mlx->shift_y += adjusted;
		d_list->rc->pos[1] -= 0.1;
	}
	else if (keycode == XK_Left)
	{
		d_list->rc->pos[0] -= 0.1;
		mlx->shift_x -= adjusted;
	}
	else if (keycode == XK_Right)
	{
		d_list->rc->pos[0] += 0.1;
		mlx->shift_x += adjusted;
	}
	put_image(d_list, mlx);
}
