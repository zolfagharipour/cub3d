/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:42 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/27 12:51:00 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	init_structs(t_common *d_list, char *file)
{
	d_list->map = (t_map *)malloc(sizeof(t_map));
	d_list->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	d_list->rc = (t_rc *)malloc(sizeof(t_rc));
	d_list->texture = (t_texture *)malloc(sizeof(t_texture));
	if (!d_list->map || !d_list->mlx || !d_list->rc || !d_list->texture)
		return 0;
	init_mlx(d_list->mlx);
	init_map(d_list->map, file);
	init_rc(d_list->rc);
	int	i = 0;
	d_list->texture->img = NULL;
	d_list->texture->mlx = NULL;
	while (i < 4)
	{
		d_list->texture->texture_buffer[i] = NULL;
		d_list->texture->path[i] = "NULL";
		i++;
	}
	//can be taken out later
	d_list->texture->path[0] = "textures/east.xpm";
	d_list->texture->path[1] = "textures/west.xpm";
	d_list->texture->path[2] = "textures/north.xpm";
	d_list->texture->path[3] = "textures/south.xpm";
	return 1;
}

void	init_map(t_map *map, char *file)
{
	map->raw_map = NULL,
	map->minimap = NULL,
	map->raw_length = 0;
	map->raw_height = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_size = 0;
	map->s_square = 10;
	map->scale = 25;
	map->player_size = map->scale / 2;
	map->file = ft_strdup(file);
	map->player_found = 0;
	map->previous_line_valid = 0;
	if (!map->file)
		return ;
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

void	init_rc(t_rc *rc)
{
	rc->look = 0.0;
	rc->pos[0] = 1.5;
	rc->pos[1] = 1.5;
	rc->tmp[0] = 0;
	rc->tmp[1] = 0;
}

int	init_mlx_functions(t_common *d_list)
{
	t_mlx *mlx;
	mlx = d_list->mlx;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (0);
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "MINIMAP");
	if (!mlx->win)
		return (cleanup(d_list), 0);
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->img)
		return (cleanup(d_list), 0);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		return (cleanup(d_list), 0);
	return (1);
}

