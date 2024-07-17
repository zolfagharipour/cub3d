/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:42 by fmarggra          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/17 18:29:45 by mzolfagh         ###   ########.fr       */
=======
/*   Updated: 2024/07/17 16:53:29 by fmarggra         ###   ########.fr       */
>>>>>>> efdb6dbecee381703cfd1288b96deafade3f3d62
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	init_structs(t_common *d_list, char *file)
{
	int	i;

	d_list->map = (t_map *)malloc(sizeof(t_map));
	d_list->mlx = (t_mlx *)malloc(sizeof(t_mlx) * 20);
	d_list->rc = (t_rc *)malloc(sizeof(t_rc));
	if (!d_list->map || !d_list->mlx || !d_list->rc)
		return (0);
	init_map(d_list->map, file);
	init_rc(d_list->rc);
	i = -1;
	while (i++ < 19)
		init_mlx(&d_list->mlx[i]);
	load_textures(d_list->mlx);
	return (1);
}

void	init_map(t_map *map, char *file)
{
	int	i;

	map->raw_map = NULL;
	map->minimap = NULL;
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
	map->close_door[0] = -1;
	map->close_door[1] = -1;
	map->map_started = 0;
	map->file_length = 0;
	i = -1;
	while (++i < 6)
		map->val_aspects[i] = NOT_FOUND;
	i = -1;
	while (++i < 6)
		map->val_map[i] = 0;
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
	mlx->texture = NULL;
	mlx->x = 0;
	mlx->y = 0;
	mlx->shift_x = 0;
	mlx->shift_y = 0;
	mlx->tex_d[0] = 0;
	mlx->tex_d[1] = 0;
}

void	init_rc(t_rc *rc)
{
	rc->look = 1;
	rc->pos[0] = 2.5;
	rc->pos[1] = 2.5;
	rc->tmp[0] = 0;
	rc->tmp[1] = 0;
	rc->sprite[0] = 1.5;
	rc->sprite[1] = 1.5;
	rc->frame = 0;
	rc->ninja_found = 0;
	rc->shuriken = 0;
}

int	init_mlx_functions(t_common *d_list, t_mlx *mlx)
{
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
