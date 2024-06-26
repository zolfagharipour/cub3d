/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:55 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/26 20:28:57 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	cleanup(t_common *d_list)
{
	cleanup_mlx(d_list->mlx);
    cleanup_map(d_list->map);
    //cleanup_rc(d_list->rc);
    close (d_list->map->fd);
    cleanup_d_list(d_list);
	exit (1);
    return (0);
}

// void    cleanup_rc(t_rc *rc)
// {
//     if (rc)
//     {
//         free(rc);
//         rc = NULL;
//     }
// }

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
    if (map && map->file)
        free(map->file);
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
    // if (d_list->rc)
    // {
    //     free(d_list->rc);
    //     d_list->rc = NULL;
    // }
    d_list = NULL;
}
