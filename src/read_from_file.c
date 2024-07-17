/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:11 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 18:36:59 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	read_map_from_file(t_common *d_list)
{
	if (!determine_map_size_and_val(d_list))
		return (0);
	if (!malloc_raw_map(d_list))
		return (0);
	if (!fill_raw_map(d_list))
		return (0);
	check_all_parts_found_and_valid(d_list);
	print_map(d_list->map);
	load_textures(d_list, d_list->mlx);
	return (1);
}

void	find_the_players_position(t_common *d_list)
{
	int	x;
	int	y;

	x = 0;
	while (x < d_list->map->raw_length)
	{
		y = 0;
		while (y < d_list->map->raw_height)
		{
			if (d_list->map->raw_map[x][y] == E
				|| d_list->map->raw_map[x][y] == S
				|| d_list->map->raw_map[x][y] == W
				|| d_list->map->raw_map[x][y] == N)
			{
				d_list->rc->pos[0] = x + 0.5;
				d_list->rc->pos[1] = y + 0.5;
				return ;
			}
			y++;
		}
		x++;
	}
}

// void	print_map(t_map *map)
// {
// 	for (int y = 0; y < map->raw_height; y++)
// 	{
// 		for (int x = 0; x < map->raw_length; x++)
// 			ft_printf("%d", map->raw_map[x][y]);
// 		ft_printf("\n");
// 	}
// }

int	malloc_raw_map(t_common *d_list)
{
	t_map	*map;
	int		i;
	int		rows_y;
	int		columns_x;

	i = 0;
	rows_y = d_list->map->raw_height;
	map = d_list->map;
	columns_x = d_list->map->raw_length;
	map->raw_map = (int **)malloc(columns_x * sizeof(int *));
	if (!map->raw_map)
		return (cleanup(d_list), 0);
	i = 0;
	while (i < columns_x)
	{
		map->raw_map[i] = (int *)malloc(rows_y * sizeof(int));
		if (!map->raw_map[i])
			return (cleanup(d_list), 0);
		i++;
	}
	return (1);
}

//calculates if the minimap exceedes the bounds
//reduces the scale factor if it does
//- scale/2 because the minimap is placed sale/2 to the right and down
void	check_map_scale_factor(t_common *d_list)
{
	t_map	*map;
	int		scale;
	int		reduction;

	//!!!
	reduction = 0;
	map = d_list->map;
	if (map->raw_length * map->scale >= WIDTH / 2
		|| map->raw_height * map->scale >= HEIGHT / 2)
	{
		while ((map->raw_length * map->scale >= WIDTH / 2
				|| map->raw_height * map->scale >= HEIGHT / 2)
			&& map->scale > 2)
		{
			map->scale = map->scale - 2;
			reduction++;
		}
	}
	if (reduction > 0)
	{
		map->s_square -= reduction / 2;
		if (map->s_square < 1)
			map->s_square = 1;
	}
}
