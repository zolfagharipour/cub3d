/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:53:35 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:53:37 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

char	*valid_map_boundaries(t_common *d_list)
{
	if (minimap_vertical_boundaries(d_list) == 0)
		return ("Invalid map boundaries\n");
	if (minimap_horizontal_boundaries(d_list) == 0)
		return ("Invalid map boundaries\n");
	if (minimap_zero_check(d_list) == 0)
		return ("Invalid map boundaries\n");
	if (minimap_door_check(d_list) == 0)
		return ("Invalid placement of doors in the map\n");
	return (NULL);
}

//player checking
//why was that necessary?
// x = 1;
// y = 1;
// while (y < map->raw_height - 1)
// {
//     x = 1;
//     while (x < map->raw_length - 1)
//     {
//         if (x == d_list->rc->pos[0] - 0.5 && y == d_list->rc->pos[1] - 0.5)
//         {
//             if (map->raw_map[x + 1][y] == ft_atoi("6")
//                 || map->raw_map[x - 1][y] == ft_atoi("6")
//                 || map->raw_map[x][y + 1] == ft_atoi("6")
//                 || map->raw_map[x][y - 1] == ft_atoi("6"))
//                 return("Player ist outside of the map\n");
//         }
//         x++;
//     }
//     y++;
// }

int	minimap_vertical_boundaries(t_common *d_list)
{
	int		x;
	int		y;
	t_map	*map;

	map = d_list->map;
	y = d_list->map->raw_height - 1;
	x = 0;
	while (y < d_list->map->raw_height)
	{
		if (map->raw_map[x][y] != ft_atoi("1")
			&& map->raw_map[x][y] != ft_atoi("6"))
			return (0);
		y++;
	}
	x = d_list->map->raw_length - 1;
	while (--y >= 0)
	{
		if (map->raw_map[x][y] != ft_atoi("1")
			&& map->raw_map[x][y] != ft_atoi("6"))
			return (0);
	}
	return (1);
}

int	minimap_horizontal_boundaries(t_common *d_list)
{
	int		x;
	int		y;
	t_map	*map;

	x = 0;
	y = 0;
	map = d_list->map;
	while (x < d_list->map->raw_length)
	{
		if (map->raw_map[x][y] != ft_atoi("1")
			&& map->raw_map[x][y] != ft_atoi("6"))
			return (0);
		x++;
	}
	y = d_list->map->raw_height - 1;
	while (--x >= 0)
	{
		if (map->raw_map[x][y] != ft_atoi("1")
			&& map->raw_map[x][y] != ft_atoi("6"))
			return (0);
	}
	return (1);
}

int	minimap_door_check(t_common *d_list)
{
	int	x;
	int	y;

	y = 0;
	while (++y < d_list->map->raw_height - 1)
	{
		x = 0;
		while (++x < d_list->map->raw_length - 1)
		{
			if (d_list->map->raw_map[x][y] == ft_atoi("4"))
			{
				if (!((d_list->map->raw_map[x + 1][y] == ft_atoi("1")
						&& d_list->map->raw_map[x - 1][y] == ft_atoi("1"))
					|| (d_list->map->raw_map[x][y + 1] == ft_atoi("1")
					&& d_list->map->raw_map[x][y - 1] == ft_atoi("1")))
					|| (d_list->map->raw_map[x + 1][y] == ft_atoi("4"))
					|| (d_list->map->raw_map[x - 1][y] == ft_atoi("4"))
					|| (d_list->map->raw_map[x][y + 1] == ft_atoi("4"))
					|| (d_list->map->raw_map[x][y - 1] == ft_atoi("4")))
					return (0);
			}
		}
	}
	return (1);
}

int	minimap_zero_check(t_common *d_list)
{
	int	x;
	int	y;

	y = 0;
	while (++y < d_list->map->raw_height - 1)
	{
		x = 0;
		while (++x < d_list->map->raw_length - 1)
		{
			if (d_list->map->raw_map[x][y] == ft_atoi("0"))
			{
				if (d_list->map->raw_map[x + 1][y] == ft_atoi("6")
					|| d_list->map->raw_map[x - 1][y] == ft_atoi("6")
					|| d_list->map->raw_map[x][y + 1] == ft_atoi("6")
					|| d_list->map->raw_map[x][y - 1] == ft_atoi("6"))
					return (0);
			}
		}
	}
	return (1);
}
