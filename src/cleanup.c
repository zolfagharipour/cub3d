/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:55 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/03 11:41:12 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	cleanup(t_common *d_list)
{
	//cleanup_mlx(d_list->mlx);
    cleanup_map(d_list->map);
    close (d_list->map->fd);
    cleanup_d_list(d_list);
	exit (1);
    return (0);
}

void    cleanup_rc(t_rc *rc)
{
    if (rc)
    {
        free(rc);
        rc = NULL;
    }
}

// void    cleanup_mlx(t_mlx *mlx)
// {
//     int i;

//     if (mlx->win)
//         mlx_destroy_window(mlx->ptr, mlx->win);
//     i = 0;
//     while (i < 13)
//     {
//         if (&mlx[i])
//         {
//             if (mlx[i].img)
//                 mlx_destroy_image(mlx[i].ptr, mlx[i].img);
//             if (mlx[i].texture)
//                 mlx_destroy_image(mlx[i].ptr, mlx[i].texture);
//             if (mlx[i].ptr)
//                 mlx_destroy_display(mlx[i].ptr);
//             if (mlx[i].ptr)
//                 free(mlx[i].ptr);
//             if (mlx[i].loop)
//                 free(mlx[i].loop);
//         }
//         i++;
//     }
// }

void    cleanup_map(t_map *map)
{
{
    if (map && map->raw_map)
    {
        for (int i = 0; i < map->raw_length; i++)
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
    if (map && map->minimap)
    {
        for (int i = 0; i < map->raw_length * map->scale; i++)
        {
            if (map->minimap[i])
            {
                free(map->minimap[i]);
                map->minimap[i] = NULL;
            }
        }
        free(map->minimap);
        map->minimap = NULL;
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
    if (d_list->rc)
    {
        free(d_list->rc);
        d_list->rc = NULL;
    }
    d_list = NULL;
}
