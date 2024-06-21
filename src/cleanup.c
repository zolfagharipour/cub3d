#include "cubid.h"

int	cleanup(t_common *d_list)
{
	cleanup_mlx(d_list->mlx);
    cleanup_map(d_list->map);
    cleanup_d_list(d_list);
	exit (1);
    return (0);
}

void    cleanup_mlx(t_mlx *mlx)
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
	}
}

void    cleanup_map(t_map *map)
{
{
    if (map && map->raw_map)
    {
        for (int i = 0; i < map->raw_height; i++)
        {
            if (map->raw_map[i])
            {
                free(map->raw_map[i]);
                map->raw_map[i] = NULL;
            }
        }
        free(map->raw_map);
        map->raw_map = NULL;
    }
}
}

void    cleanup_d_list(t_common *d_list)
{
    if (d_list->map)
    {
        free(d_list->map);
        d_list->map = NULL;
    }
    if (d_list->mlx)
    {
        free(d_list->mlx);
        d_list->mlx = NULL;
    }
    d_list = NULL;
}