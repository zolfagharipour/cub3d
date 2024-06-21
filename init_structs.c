#include "cubid.h"

void	init_structs(t_common *d_list)
{
	t_mlx	mlx;
	t_map	map;

	d_list->map = &map;
	d_list->mlx = &mlx;
	init_mlx(d_list->mlx);
	init_map(d_list->map);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->loop = NULL;
	mlx->img = NULL;
	mlx->addr = NULL;
    mlx->x = 0;
	mlx->y = 0;
    mlx->shift_x = 0;
    mlx->shift_y = 0;
}

int	init_struct(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (0);
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "MINIMAP");
	if (!mlx->win)
		return (cleanup(mlx), 0);
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->img)
		return (cleanup(mlx), 0);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		return (cleanup(mlx), 0);
	return (1);
}

int	cleanup(t_mlx *mlx)
{
	if (mlx)
	{
		if (mlx->img)
			mlx_destroy_image(mlx->ptr, mlx->img);
		if (mlx->win)
			mlx_destroy_window(mlx->ptr, mlx->win);
		if (mlx->ptr)
			mlx_destroy_display(mlx->ptr);
		if (mlx->ptr)
			free(mlx->ptr);
		if (mlx->loop)
			free(mlx->loop);
		exit(1);
	}
	return (0);
}