/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:54:36 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:54:37 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	check_all_parts_found_and_valid(t_common *d_list)
{
	int	amt_errors;
	int	i;

	i = -1;
	amt_errors = 0;
	while (++i < 6)
	{
		if (d_list->map->val_aspects[i] == NOT_FOUND
			|| d_list->map->val_aspects[i] == INV_OPEN_COL
			|| d_list->map->val_aspects[i] == INV_FORMAT)
		{
			if (amt_errors < 1)
				ft_printf("Error\n");
			print_color_texture_error(d_list, i);
			amt_errors++;
		}
	}
	catch_invalid_map(&amt_errors, d_list, -1);
	if (amt_errors)
		cleanup(d_list);
}

void	print_color_texture_error(t_common *d_list, int i)
{
	int	prev_error;

	prev_error = -1;
	if (d_list->map->val_aspects[i] == NOT_FOUND)
	{
		if (has_been_printed_before(d_list, NOT_FOUND, i) == 1)
			return ;
		write(1, "At least one texture and/or color is missing\n", 46);
	}
	else if (d_list->map->val_aspects[i] == INV_OPEN_COL)
	{
		if (has_been_printed_before(d_list, INV_OPEN_COL, i) == 1)
			return ;
		write(1, "Invalid open of texture and/or invalid color\n", 46);
	}
	else if (d_list->map->val_aspects[i] == INV_FORMAT)
	{
		if (has_been_printed_before(d_list, INV_FORMAT, i) == 1)
			return ;
		write(1, "Invalid format of color and/or texture\n", 40);
	}
}

void	catch_invalid_map(int *amt_errors, t_common *d_list, int i)
{
	while (++i < 6)
	{
		if (d_list->map->val_map[i] == 1)
		{
			if (*amt_errors < 1)
				ft_printf("Error\n");
			print_map_error(d_list, i);
			(*amt_errors)++;
		}
	}
	if (d_list->map->player_found == 0)
	{
		if (*amt_errors < 1)
			ft_printf("Error\n");
		write(1, "No player found\n", 17);
		(*amt_errors)++;
	}
	if (valid_map_boundaries(d_list) != NULL)
	{
		if (*amt_errors < 1)
			ft_printf("Error\n");
		ft_printf("%s", valid_map_boundaries(d_list));
		(*amt_errors)++;
	}
}

void	print_map_error(t_common *d_list, int error)
{
	if (error == MULTIPLE_PLAYERS)
		write(1, "Multiple players found\n", 24);
	else if (error == INV_CHAR)
		write(1, "Invalid character in map\n", 26);
	else if (error == INV_FORMAT)
		write(1, "Invalid format\n", 16);
	else if (error == INV_NL)
		write(1, "Invalid new line in the map\n", 29);
}

int	has_been_printed_before(t_common *d_list, int err_macro, int i)
{
	int	previous_error;

	previous_error = -1;
	while (++previous_error < i)
	{
		if (d_list->map->val_aspects[previous_error] == err_macro)
			return (1);
	}
	return (0);
}
